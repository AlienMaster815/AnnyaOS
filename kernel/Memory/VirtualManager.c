#include <LouAPI.h>


typedef struct _KERNEL_VM_ALLOCATION_DEFRAGMENTER{
    ListHeader          Peers;
    UINT64              PageAddress;
    UINT64              PageCount;
}KERNEL_VM_ALLOCATION_DEFRAGMENTER, * PKERNEL_VM_ALLOCATION_DEFRAGMENTER;

typedef struct _KERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE{
    ListHeader                          Peers;
    UINT64                              DefragmenterMap;
    KERNEL_VM_ALLOCATION_DEFRAGMENTER   DefragmenterNodeItems[64];
}KERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE, * PKERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE;

typedef struct _KERNEL_VM_ALLOCATION_TRACKER{
    ListHeader          Peers;
    ListHeader          VirtualDefragmenters;
    ListHeader          PhysicalDefragmenters;
    UINT64              PageAddress;
    UINT64              PageCount;
}KERNEL_VM_ALLOCATION_TRACKER, * PKERNEL_VM_ALLOCATION_TRACKER;

typedef struct _KERNEL_VM_ALLOCATION_TRACKER_NODE{
    ListHeader                      Peers;
    UINT64                          TrackerNodeMap;
    KERNEL_VM_ALLOCATION_TRACKER    TrackerNodeItems[64];
}KERNEL_VM_ALLOCATION_TRACKER_NODE, * PKERNEL_VM_ALLOCATION_TRACKER_NODE;

static ListHeader KernelVmAllocationTrackerList = {0};
static mutex_t KernelVmAllocationTrackerListLock = {0}; 

static ListHeader KernelVmAllocationDefragmenterList = {0};
static mutex_t KernelVmAllocationDefragmenterListLock = {0}; 


static PKERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE LouKeVmmAllocateVmDefragmenterNode(){
    PKERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE NewDefragmenter = (PKERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE)LouGeneralAllocateMemoryEx(sizeof(KERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE), GET_ALIGNMENT(KERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE));
    if(!NewDefragmenter){
        return 0x00;
    }
    LouKeListAddTail(&NewDefragmenter->Peers, &KernelVmAllocationDefragmenterList);
    return NewDefragmenter;
}

static void LouKeVmmFreeVmDefragmenterNode(PKERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE Node){
    LouKeListDeleteItem(&Node->Peers);
    LouGeneralFreeMemory(Node);
}

static PKERNEL_VM_ALLOCATION_DEFRAGMENTER _LouKeVmmAllocateVmDefragmenter(
    PKERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE Node 
){
    PKERNEL_VM_ALLOCATION_DEFRAGMENTER Result = 0x00;
    UINT64 NodeMap;
    SIZE i;
    if(!Node){
        return 0x00; 
    }else if(Node->DefragmenterMap == UINT64_MAX){
        return 0x00;
    }
    NodeMap = Node->DefragmenterMap;
    for(i = 0 ; i < 64; i++){
        if(!(NodeMap & (1 << i))){
            NodeMap |= (1 << i);
            Node->DefragmenterMap = NodeMap;
            Result = &Node->DefragmenterNodeItems[i];
            break;
        }
    }
    if(i >= 64){
        return 0x00;
    }
    memset(Result, 0, sizeof(KERNEL_VM_ALLOCATION_DEFRAGMENTER));
    return Result;
}

PKERNEL_VM_ALLOCATION_DEFRAGMENTER LouKeVmmAllocateVmDefragmenter(){
    PKERNEL_VM_ALLOCATION_DEFRAGMENTER NewDefragmenter;
    PKERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE TmpNode;
    MutexLock(&KernelVmAllocationDefragmenterListLock);
    ForEachListEntry(TmpNode, &KernelVmAllocationDefragmenterList, Peers){
        NewDefragmenter = _LouKeVmmAllocateVmDefragmenter(TmpNode);
        if(NewDefragmenter){
            break;
        }
    }
    if(!NewDefragmenter){
        TmpNode = LouKeVmmAllocateVmDefragmenterNode();
        NewDefragmenter = _LouKeVmmAllocateVmDefragmenter(TmpNode);
    }
    MutexUnlock(&KernelVmAllocationDefragmenterListLock);
    return NewDefragmenter;
}


static BOOLEAN _LouKeVmmFreeVmDefragmenter(
    PKERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE Node,
    PKERNEL_VM_ALLOCATION_DEFRAGMENTER      Defragmenter 
){
    if(!RangeInterferes((UINT64)(UINT8*)Defragmenter, 1, (UINT64)(UINT8*)Node, sizeof(KERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE))){
        return false;
    }
    SIZE Entry = (((UINT64)(UINT8*)Defragmenter) - ((UINT64)(UINT8*)&Node->DefragmenterNodeItems[0])) / sizeof(KERNEL_VM_ALLOCATION_DEFRAGMENTER);
    Node->DefragmenterMap &= ~(1 << Entry);
    return true;
}

void LouKeVmmFreeVmDefragmenter(
    PKERNEL_VM_ALLOCATION_DEFRAGMENTER Defragmenter
){
    PKERNEL_VM_ALLOCATION_DEFRAGMENTER_NODE TmpNode;
    MutexLock(&KernelVmAllocationDefragmenterListLock);
    ForEachListEntry(TmpNode, &KernelVmAllocationDefragmenterList, Peers){
        if(_LouKeVmmFreeVmDefragmenter(TmpNode, Defragmenter)){
            if(!TmpNode->DefragmenterMap){
                LouKeVmmFreeVmDefragmenterNode(TmpNode);
            }
            break;
        }
    }
    MutexUnlock(&KernelVmAllocationDefragmenterListLock);
}

static PKERNEL_VM_ALLOCATION_TRACKER_NODE LouKeVmmAllocateVmTrackerNode(){
    PKERNEL_VM_ALLOCATION_TRACKER_NODE NewTracker = (PKERNEL_VM_ALLOCATION_TRACKER_NODE)LouGeneralAllocateMemoryEx(sizeof(KERNEL_VM_ALLOCATION_TRACKER_NODE), GET_ALIGNMENT(KERNEL_VM_ALLOCATION_TRACKER_NODE));
    if(!NewTracker){
        return 0x00;
    }
    LouKeListAddTail(&NewTracker->Peers, &KernelVmAllocationTrackerList);
    return NewTracker;
}

static void LouKeVmmFreeVmTrackerNode(PKERNEL_VM_ALLOCATION_TRACKER_NODE Node){
    LouKeListDeleteItem(&Node->Peers);
    LouGeneralFreeMemory(Node);
}

static PKERNEL_VM_ALLOCATION_TRACKER _LouKeVmmAllocateVmTracker(
    PKERNEL_VM_ALLOCATION_TRACKER_NODE Node 
){
    PKERNEL_VM_ALLOCATION_TRACKER Result = 0x00;
    UINT64 NodeMap;
    SIZE i;
    if(!Node){
        return 0x00; 
    }else if(Node->TrackerNodeMap == UINT64_MAX){
        return 0x00;
    }
    NodeMap = Node->TrackerNodeMap;
    for(i = 0 ; i < 64; i++){
        if(!(NodeMap & (1 << i))){
            NodeMap |= (1 << i);
            Node->TrackerNodeMap = NodeMap;
            Result = &Node->TrackerNodeItems[i];
            break;
        }
    }
    if(i >= 64){
        return 0x00;
    }
    memset(Result, 0, sizeof(KERNEL_VM_ALLOCATION_TRACKER));
    return Result;
}

PKERNEL_VM_ALLOCATION_TRACKER LouKeVmmAllocateVmTracker(){
    PKERNEL_VM_ALLOCATION_TRACKER       NewTracker;
    PKERNEL_VM_ALLOCATION_TRACKER_NODE  TmpNode;
    MutexLock(&KernelVmAllocationTrackerListLock);
    ForEachListEntry(TmpNode, &KernelVmAllocationTrackerList, Peers){
        NewTracker = _LouKeVmmAllocateVmTracker(TmpNode);
        if(NewTracker){
            break;
        }
    }
    if(!NewTracker){
        TmpNode = LouKeVmmAllocateVmTrackerNode();
        NewTracker = _LouKeVmmAllocateVmTracker(TmpNode);
    }
    MutexUnlock(&KernelVmAllocationTrackerListLock);
    return NewTracker;
}


static BOOLEAN _LouKeVmmFreeVmTracker(
    PKERNEL_VM_ALLOCATION_TRACKER_NODE Node,
    PKERNEL_VM_ALLOCATION_TRACKER      Tracker 
){
    if(!RangeInterferes((UINT64)(UINT8*)Tracker, 1, (UINT64)(UINT8*)Node, sizeof(KERNEL_VM_ALLOCATION_TRACKER_NODE))){
        return false;
    }
    SIZE Entry = (((UINT64)(UINT8*)Tracker) - ((UINT64)(UINT8*)&Node->TrackerNodeItems[0])) / sizeof(KERNEL_VM_ALLOCATION_TRACKER);
    Node->TrackerNodeMap &= ~(1 << Entry);
    return true;
}

void LouKeVmmFreeVmTracker(
    PKERNEL_VM_ALLOCATION_TRACKER Tracker
){
    PKERNEL_VM_ALLOCATION_TRACKER_NODE TmpNode;
    MutexLock(&KernelVmAllocationTrackerListLock);
    ForEachListEntry(TmpNode, &KernelVmAllocationTrackerList, Peers){
        if(_LouKeVmmFreeVmTracker(TmpNode, Tracker)){
            if(!TmpNode->TrackerNodeMap){
                LouKeVmmFreeVmTrackerNode(TmpNode);
            }
            break;
        }
    }
    MutexUnlock(&KernelVmAllocationTrackerListLock);
}

//LouGeneralAllocateMemoryEx();




typedef struct _KERNEL_PAGE_REMAP{
    ListHeader          Peers;
    PVOID               PageAddress;
    SIZE                PageCount;
    SIZE                PageSize;
    ATOMIC_BOOLEAN      PhysicalUser;
    ATOMIC_BOOLEAN      VirtualUser;
}KERNEL_PAGE_REMAP, * PKERNEL_PAGE_REMAP;

typedef struct _KERNEL_PAGE_REMAP_MANAGER{
    mutex_t             Lock;
    ListHeader          Remaps;
}KERNEL_PAGE_REMAP_MANAGER, * PKERNEL_PAGE_REMAP_MANAGER;

static KERNEL_PAGE_REMAP_MANAGER KernelPageRemap64 = {0};
static KERNEL_PAGE_REMAP_MANAGER KernelPageRemap32 = {0};

LOUSTATUS
LouKeVmmCreatePageReserveVm64(
    PVOID   PageAddress, 
    SIZE    PageSize,  
    SIZE    PageCount,
    BOOLEAN SetPhysUser,
    BOOLEAN SetVirtUser
){
    if((!PageAddress) || (!PageSize) || (!PageCount)){
        return STATUS_INVALID_PARAMETER;
    }

    PKERNEL_PAGE_REMAP  TmpRemap;

    MutexLock(&KernelPageRemap64.Lock);
    ForEachListEntry(TmpRemap, &KernelPageRemap64.Remaps, Peers){
        if(RangeInterferes((UINT64)TmpRemap->PageAddress, TmpRemap->PageSize * TmpRemap->PageCount, (UINT64)PageAddress, PageSize * PageCount)){
            LouPrint("Map%h:%h:%h Temp:%h:%h:%h\n", TmpRemap->PageAddress, TmpRemap->PageSize, TmpRemap->PageCount, PageAddress, PageSize, PageCount);
            return STATUS_UNSUCCESSFUL;
        }
    }   
    MutexUnlock(&KernelPageRemap64.Lock);

    PKERNEL_PAGE_REMAP NewRemap = LouGeneralAllocateMemoryEx(sizeof(KERNEL_PAGE_REMAP), GET_ALIGNMENT(KERNEL_PAGE_REMAP));
    if(!NewRemap){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    NewRemap->PageAddress = PageAddress;
    NewRemap->PageSize = PageSize;
    NewRemap->PageCount = PageCount;
    if(SetVirtUser){
        LouKeSetAtomicBoolean(&NewRemap->VirtualUser, 1);
    }
    if(SetPhysUser){
        LouKeSetAtomicBoolean(&NewRemap->PhysicalUser, 1);
    }
    LouKeListAddTail(&NewRemap->Peers, &KernelPageRemap64.Remaps);
    return STATUS_SUCCESS;
}

LOUSTATUS
LouKeVmmCreatePageReserveVm32(
    PVOID   PageAddress, 
    SIZE    PageSize,  
    SIZE    PageCount,
    BOOLEAN SetPhysUser,
    BOOLEAN SetVirtUser
){
    if((!PageAddress) || (!PageSize) || (!PageCount)){
        return STATUS_INVALID_PARAMETER;
    }

    PKERNEL_PAGE_REMAP  TmpRemap;

    MutexLock(&KernelPageRemap32.Lock);
    ForEachListEntry(TmpRemap, &KernelPageRemap32.Remaps, Peers){
        if(RangeInterferes((UINT64)TmpRemap->PageAddress, TmpRemap->PageSize * TmpRemap->PageCount, (UINT64)PageAddress, PageSize * PageCount)){
            return STATUS_UNSUCCESSFUL;
        }
    }   
    MutexUnlock(&KernelPageRemap32.Lock);

    PKERNEL_PAGE_REMAP NewRemap = LouGeneralAllocateMemoryEx(sizeof(KERNEL_PAGE_REMAP), GET_ALIGNMENT(KERNEL_PAGE_REMAP));
    if(!NewRemap){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    NewRemap->PageAddress = PageAddress;
    NewRemap->PageSize = PageSize;
    NewRemap->PageCount = PageCount;
    if(SetVirtUser){
        LouKeSetAtomicBoolean(&NewRemap->VirtualUser, 1);
    }
    if(SetPhysUser)LouKeSetAtomicBoolean(&NewRemap->PhysicalUser, 1);
    LouKeListAddTail(&NewRemap->Peers, &KernelPageRemap32.Remaps);
    return STATUS_SUCCESS;
}


LOUSTATUS
LouKeVmmGetVPageReserveVm64(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
){
    if((!PageSize) || (!PageCount) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }

    *Out = 0;

    PKERNEL_PAGE_REMAP  TmpRemap;

    MutexLock(&KernelPageRemap64.Lock);
    ForEachListEntry(TmpRemap, &KernelPageRemap64.Remaps, Peers){
        if(
            (TmpRemap->PageSize == PageSize) && 
            (TmpRemap->PageCount == PageCount) &&
            (!LouKeGetAtomicBoolean(&TmpRemap->VirtualUser))
        ){
            LouKeSetAtomicBoolean(&TmpRemap->VirtualUser, 1);
            *Out = TmpRemap->PageAddress;
            break;
        }
    }
    MutexUnlock(&KernelPageRemap64.Lock);
    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeVmmGetPPageReserveVm64(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
){
    if((!PageSize) || (!PageCount) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }

    *Out = 0;

    PKERNEL_PAGE_REMAP  TmpRemap;

    MutexLock(&KernelPageRemap64.Lock);
    ForEachListEntry(TmpRemap, &KernelPageRemap64.Remaps, Peers){
        if(
            (TmpRemap->PageSize == PageSize) && 
            (TmpRemap->PageCount == PageCount) &&
            (!LouKeGetAtomicBoolean(&TmpRemap->PhysicalUser))
        ){
            LouKeSetAtomicBoolean(&TmpRemap->PhysicalUser, 1);
            *Out = TmpRemap->PageAddress;
            break;
        }
    }
    MutexUnlock(&KernelPageRemap64.Lock);
    return STATUS_SUCCESS;
}


LOUSTATUS
LouKeVmmGetVPageReserveVm32(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
){
    if((!PageSize) || (!PageCount) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }

    *Out = 0;

    PKERNEL_PAGE_REMAP  TmpRemap;

    MutexLock(&KernelPageRemap32.Lock);
    ForEachListEntry(TmpRemap, &KernelPageRemap32.Remaps, Peers){
        if(
            (TmpRemap->PageSize == PageSize) && 
            (TmpRemap->PageCount == PageCount) &&
            (!LouKeGetAtomicBoolean(&TmpRemap->VirtualUser))
        ){
            LouKeSetAtomicBoolean(&TmpRemap->VirtualUser, 1);
            *Out = TmpRemap->PageAddress;
            break;
        }
    }
    MutexUnlock(&KernelPageRemap32.Lock);
    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeVmmGetPPageReserveVm32(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
){
    if((!PageSize) || (!PageCount) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }

    *Out = 0;

    PKERNEL_PAGE_REMAP  TmpRemap;

    MutexLock(&KernelPageRemap32.Lock);
    ForEachListEntry(TmpRemap, &KernelPageRemap32.Remaps, Peers){
        if(
            (TmpRemap->PageSize == PageSize) && 
            (TmpRemap->PageCount == PageCount) &&
            (!LouKeGetAtomicBoolean(&TmpRemap->PhysicalUser))
        ){
            LouKeSetAtomicBoolean(&TmpRemap->PhysicalUser, 1);
            *Out = TmpRemap->PageAddress;
            break;
        }
    }
    MutexUnlock(&KernelPageRemap32.Lock);
    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeVmmPutVPageReserveAddressVm64(
    PVOID                       VAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
){
    if(!VAddress){
        return STATUS_INVALID_PARAMETER;
    }

    PKERNEL_PAGE_REMAP  TmpRemap;
    PKERNEL_PAGE_REMAP  ForwardTmpRemap;

    MutexLock(&KernelPageRemap64.Lock);
    ForEachListEntrySafe(TmpRemap, ForwardTmpRemap, &KernelPageRemap64.Remaps, Peers){
        if(
            TmpRemap->PageAddress == VAddress
        ){
            LouKeSetAtomicBoolean(&TmpRemap->VirtualUser, 0);
            if(!LouKeGetAtomicBoolean(&TmpRemap->PhysicalUser)){
                LouKeListDeleteItem(&TmpRemap->Peers);
                if(Callback){
                    Callback(TmpRemap->PageAddress);
                }
                LouGeneralFreeMemory(TmpRemap);
            }
            break;
        }
    }
    MutexUnlock(&KernelPageRemap64.Lock);
    return STATUS_SUCCESS;
}


LOUSTATUS 
LouKeVmmPutPPageReserveAddressVm64(
    PVOID                       PAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
){
    if(!PAddress){
        return STATUS_INVALID_PARAMETER;
    }

    PKERNEL_PAGE_REMAP  TmpRemap;
    PKERNEL_PAGE_REMAP  ForwardTmpRemap;

    MutexLock(&KernelPageRemap64.Lock);
    ForEachListEntrySafe(TmpRemap, ForwardTmpRemap, &KernelPageRemap64.Remaps, Peers){
        if(
            TmpRemap->PageAddress == PAddress
        ){
            LouKeSetAtomicBoolean(&TmpRemap->PhysicalUser, 0);
            if(!LouKeGetAtomicBoolean(&TmpRemap->VirtualUser)){
                LouKeListDeleteItem(&TmpRemap->Peers);
                if(Callback){
                    Callback(TmpRemap->PageAddress);
                }
                LouGeneralFreeMemory(TmpRemap);
            }
            break;
        }
    }
    MutexUnlock(&KernelPageRemap64.Lock);
    return STATUS_SUCCESS;
}


LOUSTATUS 
LouKeVmmPutVPageReserveAddressVm32(
    PVOID                       VAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
){
    if(!VAddress){
        return STATUS_INVALID_PARAMETER;
    }

    PKERNEL_PAGE_REMAP  TmpRemap;
    PKERNEL_PAGE_REMAP  ForwardTmpRemap;

    MutexLock(&KernelPageRemap32.Lock);
    ForEachListEntrySafe(TmpRemap, ForwardTmpRemap, &KernelPageRemap32.Remaps, Peers){
        if(
            TmpRemap->PageAddress == VAddress
        ){
            LouKeSetAtomicBoolean(&TmpRemap->VirtualUser, 0);
            if(!LouKeGetAtomicBoolean(&TmpRemap->PhysicalUser)){
                LouKeListDeleteItem(&TmpRemap->Peers);
                if(Callback){
                    Callback(TmpRemap->PageAddress);
                }
                LouGeneralFreeMemory(TmpRemap);
            }
            break;
        }
    }
    MutexUnlock(&KernelPageRemap32.Lock);
    return STATUS_SUCCESS;
}


LOUSTATUS 
LouKeVmmPutPPageReserveAddressVm32(
    PVOID                       PAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
){
    if(!PAddress){
        return STATUS_INVALID_PARAMETER;
    }

    PKERNEL_PAGE_REMAP  TmpRemap;
    PKERNEL_PAGE_REMAP  ForwardTmpRemap;

    MutexLock(&KernelPageRemap32.Lock);
    ForEachListEntrySafe(TmpRemap, ForwardTmpRemap, &KernelPageRemap32.Remaps, Peers){
        if(
            TmpRemap->PageAddress == PAddress
        ){
            LouKeSetAtomicBoolean(&TmpRemap->PhysicalUser, 0);
            if(!LouKeGetAtomicBoolean(&TmpRemap->VirtualUser)){
                LouKeListDeleteItem(&TmpRemap->Peers);
                if(Callback){
                    Callback(TmpRemap->PageAddress);
                }
                LouGeneralFreeMemory(TmpRemap);
            }
            break;
        }
    }
    MutexUnlock(&KernelPageRemap32.Lock);
    return STATUS_SUCCESS;
}

LOUSTATUS
LouKeVmmCreatePageReserveVm(
    PVOID   PageAddress, 
    SIZE    PageSize,  
    SIZE    PageCount,
    BOOLEAN SetPhysUser,
    BOOLEAN SetVirtUser
){
    LOUSTATUS Status;
    if(((UINTPTR)PageAddress < (4 * GIGABYTE))){
        Status = LouKeVmmCreatePageReserveVm32(PageAddress, PageSize, PageCount, SetPhysUser, SetVirtUser);
    }else{
        Status = LouKeVmmCreatePageReserveVm64(PageAddress, PageSize, PageCount, SetPhysUser, SetVirtUser);
    }
    return Status;
}

LOUSTATUS 
LouKeVmmGetPPageReserveVm(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
){
    if((!PageSize) || (!PageCount) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    *Out = 0x00;    
    LouKeVmmGetPPageReserveVm64(PageSize, PageCount, Out);
    if(Out){
        return STATUS_SUCCESS;
    }
    return LouKeVmmGetPPageReserveVm32(PageSize, PageCount, Out);
}

LOUSTATUS 
LouKeVmmGetVPageReserveVm(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
){
    if((!PageSize) || (!PageCount) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    *Out = 0x00;    
    LouKeVmmGetVPageReserveVm64(PageSize, PageCount, Out);
    if(Out){
        return STATUS_SUCCESS;
    }
    return LouKeVmmGetVPageReserveVm32(PageSize, PageCount, Out);
}



LOUSTATUS 
LouKeVmmPutPPageReserveAddressVm(
    PVOID                       PAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
){
    LOUSTATUS Status;
    if(((UINTPTR)PAddress < (4 * GIGABYTE))){
        Status = LouKeVmmPutPPageReserveAddressVm32(PAddress, Callback);
    }else{
        Status = LouKeVmmPutPPageReserveAddressVm64(PAddress, Callback);
    }
    return Status;
}


LOUSTATUS 
LouKeVmmPutVPageReserveAddressVm(
    PVOID                       VAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
){
    LOUSTATUS Status;
    if(((UINTPTR)VAddress < (4 * GIGABYTE))){
        Status = LouKeVmmPutVPageReserveAddressVm32(VAddress, Callback);
    }else{
        Status = LouKeVmmPutVPageReserveAddressVm64(VAddress, Callback);
    }
    return Status;
}

LOUAPI
uint64_t 
LouKePsmGetProcessPml4(uint32_t ProcessID);

LOUSTATUS 
LouKeMemSetVmSpace(UINT32 ProcessID, PVOID Addres, int v, SIZE Count){
    uint64_t TmpPml = LouKePsmGetProcessPml4(ProcessID);
    if(!TmpPml){
        return STATUS_NO_SUCH_DEVICE;
    }
    uint64_t PhyOut;
    if(RequestPhysicalAddressEx((uint64_t)Addres, &PhyOut, TmpPml) != STATUS_SUCCESS){
        return STATUS_NO_SUCH_DEVICE;
    }
    if(PhyOut){
        uint8_t* Foo = (uint8_t*)(KSpaceBase + PhyOut);
        memset(Foo, v, Count);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeMemCpyVmSpace(UINT32 ProcessID, PVOID Destination, PVOID Source, SIZE Count){
    uint64_t TmpPml = LouKePsmGetProcessPml4(ProcessID);
    if(!TmpPml){
        return STATUS_NO_SUCH_DEVICE;
    }
    uint64_t PhyOut;
    if(RequestPhysicalAddressEx((uint64_t)Destination, &PhyOut, TmpPml) != STATUS_SUCCESS){
        return STATUS_NO_SUCH_DEVICE;
    }
    if(PhyOut){
        uint8_t* Foo = (uint8_t*)(KSpaceBase + PhyOut);
        memcpy(Foo, Source, Count);
    }
    return STATUS_SUCCESS;
}