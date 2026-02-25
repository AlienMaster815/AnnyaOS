#include <LouAPI.h>


static LAZY_ALLOCATION_TRACKER MasterList = {0};
static mutex_t MasterLock = {0};

static PLAZY_ALLOCATION_TRACKER AllocateLazyTracker(){
    PLAZY_ALLOCATION_TRACKER TmpTracker = &MasterList;
    MutexLock(&MasterLock);
    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PLAZY_ALLOCATION_TRACKER)TmpTracker->Peers.NextHeader;
    }
    TmpTracker->Peers.NextHeader = (PListHeader)LouKeMallocType(LAZY_ALLOCATION_TRACKER, KERNEL_GENERIC_MEMORY);
    ((PLAZY_ALLOCATION_TRACKER)TmpTracker->Peers.NextHeader)->Peers.LastHeader = (PListHeader)TmpTracker;
    TmpTracker = (PLAZY_ALLOCATION_TRACKER)TmpTracker->Peers.NextHeader;
    MutexUnlock(&MasterLock);
    return TmpTracker;
}

static void FreeLazyTracker(PLAZY_ALLOCATION_TRACKER TrackMember){
    PLAZY_ALLOCATION_TRACKER TmpTracker = &MasterList;
    PLAZY_ALLOCATION_TRACKER Follower;
    MutexLock(&MasterLock);
    while(TmpTracker->Peers.NextHeader){
        Follower = TmpTracker;
        TmpTracker = (PLAZY_ALLOCATION_TRACKER)TmpTracker->Peers.NextHeader;
        if(TmpTracker == TrackMember){
            Follower->Peers.NextHeader = TmpTracker->Peers.NextHeader;
            LouKeFree(TmpTracker);
            break;
        }
    }
    MutexUnlock(&MasterLock);
}

PLAZY_ALLOCATION_TRACKER LouKeAllocateLazyBuffer(PVOID VirtualLocation, SIZE VirtualSize, UINT64 PageFlags){

    UINT64 PageSize = 0;
    if(ROUND_UP64(VirtualSize, MEGABYTE_PAGE) == VirtualSize){
        PageSize = MEGABYTE_PAGE;
    }else if(ROUND_UP64(VirtualSize, KILOBYTE_PAGE) == VirtualSize){
        PageSize = KILOBYTE_PAGE;
    }else {
        LouPrint("LouKeAllocateLazyBufferEx() ERROR EINVAL\n");
        return 0x00;
    }
    
    PLAZY_ALLOCATION_TRACKER NewTracker = AllocateLazyTracker();
    NewTracker->VirtualSize = VirtualSize;
    NewTracker->VirtualLocation = VirtualLocation;
    NewTracker->PageSize = PageSize;
    NewTracker->PageFlags = PageFlags;
    NewTracker->PhyMappingCount = VirtualSize / PageSize;
    NewTracker->PhysicalMappings = LouKeMallocArray(PVOID, NewTracker->PhyMappingCount, KERNEL_GENERIC_MEMORY);
    NewTracker->DynamicAllocations = LouKeMapDynamicPool((UINT64)VirtualLocation, VirtualSize, "LAZY_POOL", 0);
    return NewTracker;
}

void LouKeFreeLazyBuffer(PLAZY_ALLOCATION_TRACKER Tracker){
    LouKeFree(Tracker->PhysicalMappings);
    LouKeDestroyDynamicPool(Tracker->DynamicAllocations);
    FreeLazyTracker(Tracker);
}

BOOL LouKePageFaultIsDueToLazyBuffer(PVOID Location){
    BOOL Result = false;
    PLAZY_ALLOCATION_TRACKER TmpTracker = &MasterList;
    MutexLock(&MasterLock);
    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PLAZY_ALLOCATION_TRACKER)TmpTracker->Peers.NextHeader;
        if(RangeInterferes((UINT64)TmpTracker->VirtualLocation, TmpTracker->VirtualSize, (UINT64)Location, 1)){
            Result = true;
            break;
        }
    }
    MutexUnlock(&MasterLock);
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