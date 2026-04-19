#include <LouAPI.h>


static ListHeader MasterList = {0};
static mutex_t MasterLock = {0};

static PLAZY_ALLOCATION_TRACKER AllocateLazyTracker(){
    PLAZY_ALLOCATION_TRACKER NewTracker = LouKeMallocType(LAZY_ALLOCATION_TRACKER, KERNEL_GENERIC_MEMORY);
    MutexLock(&MasterLock);
    LouKeListAddTail(&NewTracker->Peers, &MasterList);
    MutexUnlock(&MasterLock);
    return NewTracker;
}

static void FreeLazyTracker(PLAZY_ALLOCATION_TRACKER TrackMember){
    MutexLock(&MasterLock);
    LouKeListDeleteItem(&TrackMember->Peers);
    MutexUnlock(&MasterLock);
    LouKeFree(TrackMember);
}

PLAZY_ALLOCATION_TRACKER LouKeAllocateLazyBuffer(PVOID VirtualLocation, SIZE VirtualSize, SIZE CommitSize, UINT64 PageFlags){

    SIZE PageSize = 0; 
    if(ROUND_UP64(VirtualSize, MEGABYTE_PAGE) == VirtualSize){
        PageSize = MEGABYTE_PAGE;
    }else if(ROUND_UP64(VirtualSize, KILOBYTE_PAGE) == VirtualSize){
        PageSize = KILOBYTE_PAGE;
    }else {
        LouPrint("LouKeAllocateLazyBuffer() ERROR EINVAL\n");
        return 0x00;
    }
    
    if(PageSize == MEGABYTE_PAGE && CommitSize){
        if(ROUND_UP64(CommitSize, MEGABYTE_PAGE) != CommitSize){
            PageSize = KILOBYTE_PAGE;
        }else if(ROUND_UP64(CommitSize, KILOBYTE_PAGE) != CommitSize){
            return 0x00;
        }
    }

    PLAZY_ALLOCATION_TRACKER NewTracker = AllocateLazyTracker();
    NewTracker->VirtualSize = VirtualSize;
    NewTracker->VirtualLocation = VirtualLocation;
    NewTracker->PageSize = PageSize;
    NewTracker->PageFlags = PageFlags;
    NewTracker->PhyMappingCount = VirtualSize / PageSize;
    NewTracker->PhysicalMappings = LouKeMallocArray(PVOID, NewTracker->PhyMappingCount, KERNEL_GENERIC_MEMORY);
    NewTracker->DynamicAllocations = LouKeMapDynamicPool((UINT64)VirtualLocation, VirtualSize, "LAZY_POOL", POOL_FLAG_LAZY_POOL);
    if(CommitSize){
        PVOID CommitPhyAddress = LouAllocatePhysical64UpEx(CommitSize, PageSize);//TODO: add 32 bit buffers too
        for(SIZE i = 0 ; i < NewTracker->PhyMappingCount; i++){
            NewTracker->PhysicalMappings[i]= CommitPhyAddress + (i * PageSize);
        }
    }
    return NewTracker;
}

BOOL LouKePageFaultIsDueToLazyBuffer(PVOID Location, PLAZY_ALLOCATION_TRACKER* Out){
    BOOL Result = false;
    PLAZY_ALLOCATION_TRACKER TmpTracker;
    ForEachListEntry(TmpTracker, &MasterList, Peers){
        if(RangeInterferes((UINT64)TmpTracker->VirtualLocation, TmpTracker->VirtualSize, (UINT64)Location, 1)){
            Result = true;
            *Out = TmpTracker;
            break;
        }
    }
    return Result;
}

PVOID LouKeMallocFromLazyBufferEx(
    PLAZY_ALLOCATION_TRACKER    LazyBuffer,
    SIZE                        Size,
    SIZE                        Alignment
){
    return (PVOID)LouKeMallocFromDynamicPoolEx(
        LazyBuffer->DynamicAllocations, 
        Size, 
        Alignment
    );
}

PVOID LouKeMallocFromLazyBuffer(
    PLAZY_ALLOCATION_TRACKER    LazyBuffer,
    SIZE                        Size
){
    return LouKeMallocFromLazyBufferEx(
        LazyBuffer,
        Size, 
        GetAlignmentBySize(Size)
    );
}

void LouKeFreeFromLazyBuffer(
    PLAZY_ALLOCATION_TRACKER    LazyBuffer,
    PVOID                       Address
){
    LouKeFreeFromDynamicPool(
        LazyBuffer->DynamicAllocations, 
        Address
    );
}

LOUSTATUS 
LouKeLazyBufferCommitPage(
    PLAZY_ALLOCATION_TRACKER    LazyBuffer,
    PVOID                       Address, //Optional
    SIZE                        Count    //Optional
){
    SIZE i;
    if(!Count){
        Count = 1;
    }
    if(!Address){
        BOOLEAN Found = false;
        for(i = 0 ; (i + Count) < LazyBuffer->PhyMappingCount; i++){
            Found = true;
            for(SIZE j = 0 ; j < Count; j++){
                if(!LazyBuffer->PhysicalMappings[i + j]){
                    Found = false;
                    break;
                }
            }
            if(Found){
                break;
            }
        }
        if(!Found){
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        Address = (PVOID)(LazyBuffer->VirtualLocation + i * LazyBuffer->PageSize);
    }else{
        if(RangeDoesNotInterfere((UINT64)Address, 1, (UINT64)LazyBuffer->VirtualLocation, (UINT64)LazyBuffer->VirtualSize)){
            LouPrint("LouKeLazyBufferCommitPage():INVALID_PARAMETER:Not In Scope\n");
            return STATUS_INVALID_PARAMETER;
        }
        Address = (PVOID)ROUND_DOWN64((UINT64)Address, LazyBuffer->PageSize);
        i = ((UINT64)(Address - LazyBuffer->VirtualLocation) / LazyBuffer->PageSize);
        for(SIZE j = 0; j < Count; j++){
            if(LazyBuffer->PhysicalMappings[i + j]){
                LouPrint("LouKeLazyBufferCommitPage():INVALID_PARAMETER:Address Taken\n");
                return STATUS_INVALID_PARAMETER;
            }
        }
    }
    for(SIZE foo = 0; foo < Count; foo++){
        PVOID NewPAddress = LouAllocatePhysical64UpEx(LazyBuffer->PageSize, LazyBuffer->PageSize);
        LazyBuffer->PhysicalMappings[i + foo] = NewPAddress;
        LouMapAddress((UINT64)NewPAddress, (UINT64)(LazyBuffer->VirtualLocation + ((i + foo) * LazyBuffer->PageSize)), LazyBuffer->PageFlags, LazyBuffer->PageSize);
        memset((PVOID)(LazyBuffer->VirtualLocation + ((i + foo) * LazyBuffer->PageSize)), 0, LazyBuffer->PageSize);
        LouKeVmmCreatePageReserveVm(NewPAddress, LazyBuffer->PageSize, 1, true, false);
    }
    return STATUS_SUCCESS;
}

void LouKeLazyBufferUnCommitPage(PLAZY_ALLOCATION_TRACKER Tracker, PVOID VAddress){
    LouPrint("LouKeLazyBufferUnCommitPage()\n");
    while(1);
}

void LouKeLazyBufferUnCommitAllPages(PLAZY_ALLOCATION_TRACKER Tracker){
    for(SIZE i = 0; i < Tracker->PhyMappingCount; i++){
        LouKeLazyBufferUnCommitPage(Tracker, Tracker->VirtualLocation + (i * Tracker->PageSize));
    }
}

void LouKeFreeLazyBuffer(PLAZY_ALLOCATION_TRACKER Tracker){
    LouKeLazyBufferUnCommitAllPages(Tracker);
    LouKeFree(Tracker->PhysicalMappings);
    LouKeDestroyDynamicPool(Tracker->DynamicAllocations);
    FreeLazyTracker(Tracker);
}