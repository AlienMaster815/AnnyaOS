#define _VMM_ALLOCATION_INTERNALS_

#include <LouAPI.h>

void RemoveAddressFromReservePool(UINT64 Address);
bool IsAddressRemaped(UINT64 Address);

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
    BOOLEAN                     HighMem;
    UINTPTR                     PBase;//only if Shared is true
    UINT64                      Flags;//only if Shared is true
    XARRAY                      VmmData;//
    PLAZY_ALLOCATION_TRACKER    SharedTracker;
}VMM_ALLOCATION_TRACKER, * PVMM_ALLOCATION_TRACKER;

typedef struct _VMM_MEMORY_MANAGER{
    mutex_t             Lock;
    ListHeader          AllocationTrackers;
}VMM_MEMORY_MANAGER, * PVMM_MEMORY_MANAGER;

static VMM_MEMORY_MANAGER VmmMemoryManager64 = {0};
static VMM_MEMORY_MANAGER VmmMemoryManager32 = {0};

static void LouKeVmmFreeHelper(PVOID Address){
    LouGeneralFreeMemory(Address);
}

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
    SIZE PageSize = (Size >= MEGABYTE_PAGE) ? MEGABYTE_PAGE : KILOBYTE_PAGE;
    PVOID NewVSpace = 0x00;
    PVOID NewPSpace = 0x00;


    if(Shared){
        if(HighMem){
            NewVSpace = LouKeMallocPageVirt64(PageSize, Size / PageSize, Flags, true); //create device section AKA use in all VMs
        }else{
            NewVSpace = LouKeMallocPageVirt32(PageSize, Size / PageSize, Flags, true); //create device section AKA use in all VMs
        }
        if(!NewVSpace){
            LouKeFree(NewTracker);  //LouKeFree:    for the Kernel Global Allocator
            return 0x00;
        }
        UINT64 TmpOut;
        RequestPhysicalAddress((UINT64)NewVSpace, &TmpOut);
        NewPSpace = (PVOID)TmpOut;
        
        NewTracker->SharedTracker = LouKeAllocateLazyBuffer(NewVSpace, Size, 0, Flags);
        if(!NewTracker->SharedTracker){
            LouKeFreePage(NewVSpace);
            LouKeFree(NewTracker);  //LouKeFree:    for the Kernel Global Allocator
            return 0x00;
        }
    }else{
        if(HighMem){
            LouKeVmmGetVPageReserveVm64(PageSize, Size / PageSize, &NewVSpace);
            if(!NewVSpace){
                NewVSpace = LouAllocatePhysical64UpEx(Size, ROUND_UP64(Alignment, PageSize));
            }
        }else {
            LouKeVmmGetVPageReserveVm32(PageSize, Size / PageSize, &NewVSpace);
            if(!NewVSpace){
                NewVSpace = LouAllocatePhysical32UpEx(Size, ROUND_UP64(Alignment, PageSize));
            }
        }
        if(!NewVSpace){
            LouKeFree(NewTracker);  //LouKeFree:    for the Kernel Global Allocator
            return 0x00;
        }
        else if((((UINTPTR)NewVSpace + Size) >= (4 * GIGABYTE)) && (!HighMem)){
            LouFree(NewVSpace);     //LouFree:      for the RAT (Ram Allocation Table) kernel Driver
            LouKeFree(NewTracker);  //LouKeFree:    for the Kernel Global Allocator
            return 0x00;
        }
        LouKeVmmCreatePageReserveVm(
            NewVSpace,
            PageSize,
            Size / PageSize,
            false, 
            true 
        );
    }
    NewTracker->VBase = (UINTPTR)NewVSpace;
    NewTracker->VSize = Size;
    NewTracker->PBase = (UINTPTR)NewPSpace;
    NewTracker->Shared = Shared;
    NewTracker->HighMem = HighMem;
    LouKeListAddTail(&NewTracker->Peers, HighMem ?  &VmmMemoryManager64.AllocationTrackers : &VmmMemoryManager32.AllocationTrackers);
    return NewTracker;
}

UNUSED
static 
void 
LouKeFreeVmmAllocationTracker(
    PVMM_ALLOCATION_TRACKER     Tracker
){
    LouKeListDeleteItem(&Tracker->Peers);
    if(Tracker->Shared){
        LouKeFreeLazyBuffer(Tracker->SharedTracker);
        LouKeFreePage((PVOID)Tracker->VBase);
    }else{
        LouKeVmmPutVPageReserveAddressVm((PVOID)Tracker->VBase, LouKeVmmFreeHelper);
    }   
    LouKeFree(Tracker);  //LouKeFree:    for the Kernel Global Allocator
}    


UNUSED
static
PVOID 
VmmAllocationTrackerAllocate(
    UINT32                      ProcessID,
    PVMM_ALLOCATION_TRACKER     AllocationTracker,
    SIZE                        Size,
    SIZE                        Alignment,
    BOOLEAN                     Zero,
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
            ProcessID
        )){ 
            //allocate new tracker for current process
            PVMM_DATA NewData = LouKeMallocType(VMM_DATA, KERNEL_GENERIC_MEMORY);
            NewData->Flags = Flags;
            NewData->AllocationTracker = LouKeAllocateLazyBuffer((PVOID)AllocationTracker->VBase, AllocationTracker->VSize, 0, Flags);
            //store the new process tracker in its xarray
            LouKeXaStore(
                &AllocationTracker->VmmData,
                ProcessID,
                NewData,
                KERNEL_GENERIC_MEMORY
            );
            //alloctate the needed buffer
            Result = LouKeMallocFromLazyBufferEx(NewData->AllocationTracker, Size, Alignment);
            //if successfull acquire references to the process counter AND the Item counter
            if(Result){
                LouKeAcquireReference(&NewData->ItemsUsed);
                LouKeAcquireReference(&AllocationTracker->ProcessesHandling);
            }
        }else{
            UINT64 VmmOutData = 0x00;
            //get the pre allocated xarray data
            LouKeXaGet(
                &AllocationTracker->VmmData,
                ProcessID,
                &VmmOutData
            );
            //sanity check data
            if(VmmOutData){
                PVMM_DATA Tracker = (PVMM_DATA)VmmOutData;
                //IF the flags match for this tracker allocate from the pool
                if(Tracker->Flags == Flags){
                    Result = LouKeMallocFromLazyBufferEx(Tracker->AllocationTracker, Size, Alignment);
                    if(Result){
                        //if the pool successully allocates data acquire a item reference
                        LouKeAcquireReference(&Tracker->ItemsUsed);
                    } 
                }
            }
        }
    }
    if(Result && Zero){
        if(LouKeGetProcessIdentification() == ProcessID){
            memset(Result, 0, Size);
        }else{
            LouKeMemSetVmSpace(ProcessID, Result, 0, Size);
        }
    }
    return Result;
}

UNUSED
static 
PVMM_ALLOCATION_TRACKER
LouKeVmmGetAllocationTracker64(
    PVOID   Address
){
    PVMM_ALLOCATION_TRACKER TmpTracker;
    ForEachListEntry(TmpTracker, &VmmMemoryManager64.AllocationTrackers, Peers){
        if(RangeInterferes(TmpTracker->VBase, TmpTracker->VSize, (UINT64)Address, 1)){
            return TmpTracker;
        }
    }
    return 0x00;
}

KERNEL_EXPORT 
PVOID 
LouKeAllocateVmmBuffer64Ex2(
    UINT32  ProcessID,
    SIZE    Size,
    SIZE    Alignment,
    BOOLEAN Zero,
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
                ProcessID,
                TmpTracker,
                Size,
                Alignment,
                Zero,
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
        if(NewTracker){
            Result = VmmAllocationTrackerAllocate(
                ProcessID,
                NewTracker,
                Size,
                Alignment,
                Zero,
                Flags
            );        
        }
    }
    MutexUnlock(&VmmMemoryManager64.Lock);
    return Result;
}

KERNEL_EXPORT 
PVOID 
LouKeAllocateVmmBuffer32Ex2(
    UINT32  ProcessID,
    SIZE    Size,
    SIZE    Alignment,
    BOOLEAN Zero,
    BOOLEAN Shared,
    UINT64  Flags
){

    PVMM_ALLOCATION_TRACKER TmpTracker;
    PVMM_ALLOCATION_TRACKER ForwardTmpTracker;
    PVOID Result = 0x00;
    MutexLock(&VmmMemoryManager32.Lock);
    ForEachListEntrySafe(TmpTracker, ForwardTmpTracker, &VmmMemoryManager64.AllocationTrackers, Peers){
        ForEachIf((!TmpTracker->Shared) && (TmpTracker->VSize >= Size)){
            Result = VmmAllocationTrackerAllocate(
                ProcessID,
                TmpTracker,
                Size,
                Alignment,
                Zero,
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
            false
        );
        if(NewTracker){
            Result = VmmAllocationTrackerAllocate(
                ProcessID,
                NewTracker,
                Size,
                Alignment,
                Zero,
                Flags
            );        
        }
    }
    MutexUnlock(&VmmMemoryManager32.Lock);
    return Result;
}

BOOLEAN
LouKeVmmAddressCausePageFault(
    PVOID Address, 
    PVMM_ALLOCATION_TRACKER* Out
){
    *Out = LouKeVmmGetAllocationTracker64(Address);
    return *Out ?  true : false;
}

LOUSTATUS
LouKeVmmCommitPageAddress(
    PVOID                   Address, 
    PVMM_ALLOCATION_TRACKER In
){
    if(In->Shared){
        LouPrint("LouKeVmmCommitPageAddress():Address Is Shared\n");
        return STATUS_INVALID_PARAMETER;
    }
    if(!LouKeXaIsIndexUsed(
        &In->VmmData,
        LouKeGetProcessIdentification()
    )){     

        LouPrint("LouKeVmmCommitPageAddress():Address Not Used By Process:%d\n", LouKeGetProcessIdentification());
        return STATUS_INVALID_PARAMETER;
    }

    UINT64 VmmOutData = 0x00;
    //get the pre allocated xarray data
    LouKeXaGet(
        &In->VmmData,
        LouKeGetProcessIdentification(),
        &VmmOutData
    );
    //sanity check data
    if(!VmmOutData){
        LouPrint("LouKeVmmCommitPageAddress():VM Data NULL\n");
        return STATUS_UNSUCCESSFUL;
    }
    PVMM_DATA Tracker = (PVMM_DATA)VmmOutData;

    return LouKeLazyBufferCommitPage(Tracker->AllocationTracker, Address, 1);
}