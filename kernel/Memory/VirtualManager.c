#include <LouAPI.h>

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
        LouKeUnMapContinuousMemoryBlock((UINT64)PageAddress, NewRemap->PageSize * NewRemap->PageCount); 
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
        LouKeUnMapContinuousMemoryBlock((UINT64)PageAddress, NewRemap->PageSize * NewRemap->PageCount); 
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
    if(((UINTPTR)PageAddress > (4 * GIGABYTE))){
        Status = LouKeVmmCreatePageReserveVm64(PageAddress, PageSize, PageCount, SetPhysUser, SetVirtUser);
    }else{
        Status = LouKeVmmCreatePageReserveVm32(PageAddress, PageSize, PageCount, SetPhysUser, SetVirtUser);
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
    if(((UINTPTR)PAddress > (4 * GIGABYTE))){
        Status = LouKeVmmPutPPageReserveAddressVm64(PAddress, Callback);
    }else{
        Status = LouKeVmmPutPPageReserveAddressVm32(PAddress, Callback);
    }
    return Status;
}


LOUSTATUS 
LouKeVmmPutVPageReserveAddressVm(
    PVOID                       VAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
){
    LOUSTATUS Status;
    if(((UINTPTR)VAddress > (4 * GIGABYTE))){
        Status = LouKeVmmPutVPageReserveAddressVm64(VAddress, Callback);
    }else{
        Status = LouKeVmmPutVPageReserveAddressVm32(VAddress, Callback);
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
        uint8_t* Foo = (uint8_t*)(GetKSpaceBase() + PhyOut);
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
        uint8_t* Foo = (uint8_t*)(GetKSpaceBase() + PhyOut);
        memcpy(Foo, Source, Count);
    }
    return STATUS_SUCCESS;
}