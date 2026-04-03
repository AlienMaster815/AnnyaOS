#include <LouAPI.h>

typedef struct _VMM_DATA{
    KERNEL_REFERENCE            ItemsUsed;
    UINT64                      Flags;
    PLAZY_ALLOCATION_TRACKER    AllocationTracker;
}VMM_DATA, * PVMM_DATA;

typedef struct _VMM_ALLOCATION_TRACKER{
    ListHeader                  Peers;
    KERNEL_REFERENCE            ProcessesHandling;
    BOOLEAN                     Shared;
    UINTPTR                     VBase;
    SIZE                        VSize;
    UINTPTR                     PBase;//only if Shared is true
    UINT64                      Flags;//only if Shared is true
    XARRAY                      VmmData;  
    PLAZY_ALLOCATION_TRACKER    SharedTracker;
}VMM_ALLOCATION_TRACKER, * PVMM_ALLOCATION_TRACKER;

typedef struct _VMM_MEMORY_MANAGER{
    mutex_t             Lock;
    ListHeader          AllocationTrackers;
}VMM_MEMORY_MANAGER, * PVMM_MEMORY_MANAGER;

static VMM_MEMORY_MANAGER VmmMemoryManager64 = {0};
static VMM_MEMORY_MANAGER VmmMemoryManager32 = {0};

void LouKeRegisterPAddressToReserveVAddresses(
    UINT64 PAddress,
    UINT64 PageSize,
    UINT64 PageCount
);

void RemoveAddressFromReservePool(UINT64 Address);
bool IsAddressRemaped(UINT64 Address);

UNUSED
static 
PVMM_ALLOCATION_TRACKER
LouKeAlocateVmmAllocationTracker(
    SIZE    Size,
    SIZE    Alignment,
    BOOLEAN Shared,
    UINT64  Flags,
    BOOLEAN HighMem
){
    PVMM_ALLOCATION_TRACKER NewTracker = LouKeMallocType(VMM_ALLOCATION_TRACKER, KERNEL_GENERIC_MEMORY);
    Size = ROUND_UP64(Size, MEGABYTE_PAGE);
    PVOID NewVSpace = 0x00;
    PVOID NewPSpace = 0x00;
    if(HighMem){
        NewVSpace = LouAllocatePhysical64UpEx(Size, ROUND_UP64(Alignment, MEGABYTE_PAGE));
        //use the Page manager to make sure we dont waste memory
        LouKeRegisterPAddressToReserveVAddresses((UINT64)NewVSpace, MEGABYTE_PAGE, Size / MEGABYTE_PAGE);
        if(Shared){
            NewPSpace = LouAllocatePhysical64UpEx(Size, ROUND_UP64(Alignment, MEGABYTE_PAGE));
            LouKeMapContinuousMemoryBlock((UINT64)NewPSpace, (UINT64)NewVSpace, Size, Flags);
            NewTracker->SharedTracker = LouKeAllocateLazyBuffer(NewVSpace, Size, Flags);
        }
        LouKeListAddTail(&NewTracker->Peers, &VmmMemoryManager64.AllocationTrackers);
    }else{
        NewVSpace = LouAllocatePhysical32UpEx(Size, ROUND_UP64(Alignment, MEGABYTE_PAGE));
        //use the Page manager to make sure we dont waste memory
        LouKeRegisterPAddressToReserveVAddresses((UINT64)NewVSpace, MEGABYTE_PAGE, Size / MEGABYTE_PAGE);
        if(Shared){
            NewPSpace = LouAllocatePhysical64UpEx(Size, ROUND_UP64(Alignment, MEGABYTE_PAGE));
            LouKeMapContinuousMemoryBlock((UINT64)NewPSpace, (UINT64)NewVSpace, Size, Flags);
            NewTracker->SharedTracker = LouKeAllocateLazyBuffer(NewVSpace, Size, Flags);
        }
        LouKeListAddTail(&NewTracker->Peers, &VmmMemoryManager32.AllocationTrackers);
    }
    NewTracker->VBase = (UINTPTR)NewVSpace;
    NewTracker->VSize = Size;
    NewTracker->PBase = (UINTPTR)NewPSpace;
    NewTracker->Shared = Shared;
    return NewTracker;
}

UNUSED
static 
void 
LouKeFreeVmmAllocationTracker(
    PVMM_ALLOCATION_TRACKER     Tracker
){
    LouKeListDeleteItem(&Tracker->Peers);
    if(Tracker->PBase)LouFree((PVOID)Tracker->PBase);
    LouFree((PVOID)Tracker->VBase);
    LouKeFree(Tracker);
}    


UNUSED
static
PVOID 
VmmAllocationTrackerAllocate(
    PVMM_ALLOCATION_TRACKER     AllocationTracker,
    SIZE                        Size,
    SIZE                        Alignment,
    UINT64                      Flags
){
    PVOID Result = 0x00;
    if(AllocationTracker->Shared){
        Result = LouKeMallocFromLazyBufferEx(
            AllocationTracker->SharedTracker,
            Size,
            Alignment
        );
        if(Result){
            LouKeAcquireReference(&AllocationTracker->ProcessesHandling);
        }
    }else {
        if(!LouKeXaIsIndexUsed(
            &AllocationTracker->VmmData,
            LouKeGetCurrentProcessorNumber()
        )){ 
            PVMM_DATA NewData = LouKeMallocType(VMM_DATA, KERNEL_GENERIC_MEMORY);
            NewData->Flags = Flags;
            NewData->AllocationTracker = LouKeAllocateLazyBuffer((PVOID)AllocationTracker->VBase, AllocationTracker->VSize, Flags);
            LouKeXaStore(
                &AllocationTracker->VmmData,
                LouKeGetCurrentProcessorNumber(),
                NewData,
                KERNEL_GENERIC_MEMORY
            );
            
            Result = LouKeMallocFromLazyBufferEx(NewData->AllocationTracker, Size, Alignment);

            if(Result){
                LouKeAcquireReference(&NewData->ItemsUsed);
                LouKeAcquireReference(&AllocationTracker->ProcessesHandling);
            }
        }else{
            UINT64 VmmOutData = 0x00;
            LouKeXaGet(
                &AllocationTracker->VmmData,
                LouKeGetCurrentProcessorNumber(),
                &VmmOutData
            );
            if(VmmOutData){
                PVMM_DATA Tracker = (PVMM_DATA)VmmOutData;
                if(Tracker->Flags == Flags){
                    Result = LouKeMallocFromLazyBufferEx(Tracker->AllocationTracker, Size, Alignment);
                    if(Result){
                        LouKeAcquireReference(&Tracker->ItemsUsed);
                    } 
                }
            }
        }
    }
    return Result;
}

KERNEL_EXPORT 
PVOID 
LouKeAllocateVmmBufferEx64(
    SIZE    Size,
    SIZE    Alignment,
    BOOLEAN Shared,
    UINT64  Flags
){
    PVMM_ALLOCATION_TRACKER TmpTracker;
    PVMM_ALLOCATION_TRACKER ForwardTmpTracker;
    PVOID Result = 0x00;
    MutexLock(&VmmMemoryManager64.Lock);
    ForEachListEntrySafe(TmpTracker, ForwardTmpTracker, &VmmMemoryManager64.AllocationTrackers, Peers){
        ForEachIf((!TmpTracker->Shared) && (TmpTracker->VSize >= Size)){
            Result = VmmAllocationTrackerAllocate(
                TmpTracker,
                Size,
                Alignment,
                Flags
            );        
            if(Result){
                goto _FOUND_NEW_ALLOCATION;            
            }
        }
    }
    _FOUND_NEW_ALLOCATION:
    if(!Result){
        PVMM_ALLOCATION_TRACKER NewTracker = LouKeAlocateVmmAllocationTracker(
            Size,
            Alignment,
            false,
            Flags,
            true
        );
        Result = VmmAllocationTrackerAllocate(
            NewTracker,
            Size,
            Alignment,
            Flags
        );        
    }
    MutexUnlock(&VmmMemoryManager64.Lock);
    return Result;
}

KERNEL_EXPORT 
PVOID 
LouKeAllocateVmmBufferEx32(
    SIZE    Size,
    SIZE    Alignment,
    BOOLEAN Shared,
    UINT64  Flags
){

    

    return 0x00;
}