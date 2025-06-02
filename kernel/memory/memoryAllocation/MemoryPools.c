#include <LouAPI.h>

//static LMPOOL_DIRECTORY PoolDirectory;
//static uint64_t AllocatedPools = 0;

PLMPOOL_DIRECTORY LouKeMapPool(
    uint64_t LocationOfPool,
    uint64_t LocationOfVMem,
    uint64_t PoolSize,
    uint64_t ObjectSize,
    string Tag,
    uint64_t Flags
){
    LouPrint("LouKeMapPool()\n");
    while(1);
}

void* LouKeMallocFromPool(
    PLMPOOL_DIRECTORY Pool, 
    uint64_t size, 
    uint64_t* Offset
){
    LouPrint("LouKeMallocFromPool()\n");
    while(1);
    return 0;
}


void LouKeFreeFromPool(PLMPOOL_DIRECTORY Pool, void* Address, uint64_t size) {
    LouPrint("LouKeFreeFromPool()\n");
    while(1);
}

void* LouKeMallocFromFixedPool(
    PLMPOOL_DIRECTORY Pool
){
    if(!Pool->FixedSizePool){
        LouPrint("LouKeMallocFromFixedPool() : ERROR Input Is Not A Fixed Pool\n");
        return 0x00;
    }
    PPOOL_MEMORY_TRACKS TmpPoolMemTrack = &Pool->MemoryTracks;
    TmpPoolMemTrack = (PPOOL_MEMORY_TRACKS)TmpPoolMemTrack->Peers.NextHeader;

    for(uint64_t i = 0 ; i < Pool->PoolSize; i++){
        if(!TmpPoolMemTrack[i].AddressInUse){
            TmpPoolMemTrack[i].AddressInUse = true;
            return (void*)TmpPoolMemTrack[i].Address;
        }
    }
    return 0x00;
}

PLMPOOL_DIRECTORY LouKeCreateFixedPool(
    uint64_t NumberOfPoolMembers,
    uint64_t ObjectSize,
    uint64_t Alignment,
    string Tag,
    uint64_t Flags,
    uint64_t PageFlags
){
    POOL NewPool = (POOL)LouKeMallocType(LMPOOL_DIRECTORY, KERNEL_GENERIC_MEMORY);
    NewPool->VLocation = (uint64_t)LouKeMallocEx(ROUND_UP64(ObjectSize, Alignment) * NumberOfPoolMembers, Alignment, PageFlags);
    NewPool->FixedSizePool = true;
    NewPool->Flags = Flags;
    NewPool->Tag = Tag;
    NewPool->ObjectSize = ObjectSize;
    NewPool->PoolSize = NumberOfPoolMembers;
    NewPool->DirtyAllocations = 0; //counts the Fragmentation for trim
    PPOOL_MEMORY_TRACKS TmpPoolMemTrack = &NewPool->MemoryTracks;
    TmpPoolMemTrack->Peers.NextHeader = (PListHeader)LouKeMallocArray(POOL_MEMORY_TRACKS, NumberOfPoolMembers, KERNEL_GENERIC_MEMORY); 
    TmpPoolMemTrack = (PPOOL_MEMORY_TRACKS)TmpPoolMemTrack->Peers.NextHeader;
    for(uint64_t i = 0; i < NumberOfPoolMembers; i++){
        TmpPoolMemTrack[i].Address = NewPool->VLocation + (ROUND_UP64(ObjectSize, Alignment) * i);
        TmpPoolMemTrack[i].AddressInUse = false;
    }
    return NewPool;
}

void LouKeMallocTrimFixedPool(
    PLMPOOL_DIRECTORY Pool
){

}

void LouKeFreePool(PLMPOOL_DIRECTORY PoolToFree){
    LouPrint("LouKeFreePool()\n");
    while(1);
}

PLMPOOL_DIRECTORY LouKeCreateDynamicPoolEx(
    size_t PoolSize,
    size_t CachedTracks,
    size_t PagedTypeAlignement,
    string Tag,
    uint64_t Flags,
    uint64_t PageFlags
){
    POOL NewPool = (POOL)LouKeMallocType(LMPOOL_DIRECTORY, KERNEL_GENERIC_MEMORY);
    NewPool->VLocation = (uint64_t)LouKeMallocEx(PoolSize, PagedTypeAlignement, PageFlags);
    NewPool->LastOut = NewPool->VLocation;
    NewPool->FixedSizePool = false;
    NewPool->Flags = Flags;
    NewPool->Tag = Tag;
    NewPool->ObjectSize = CachedTracks;
    NewPool->PoolSize = PoolSize;
    PPOOL_MEMORY_TRACKS TmpPoolMemTrack = &NewPool->MemoryTracks;
    TmpPoolMemTrack->Peers.NextHeader = (PListHeader)LouKeMallocArray(POOL_MEMORY_TRACKS, CachedTracks, KERNEL_GENERIC_MEMORY);    
    return NewPool;
}

PLMPOOL_DIRECTORY LouKeCreateDynamicPool(
    size_t PoolSize,
    size_t PagedTypeAlignement,
    string Tag,
    uint64_t Flags,
    uint64_t PageFlags
){
    return LouKeCreateDynamicPoolEx(
        PoolSize,
        PoolSize / 512, //for each 512 default one cache
        PagedTypeAlignement,
        Tag,
        Flags,
        PageFlags
    );
}

void LouKeFreeFromDynamicPool(
    POOL Pool, 
    void* Address
){
    register uint64_t Address64 = (uint64_t)Address;

    register size_t CurrentCache = Pool->DirtyAllocations;
    register PPOOL_MEMORY_TRACKS CacheTracks = (PPOOL_MEMORY_TRACKS)Pool->MemoryTracks.Peers.NextHeader;
    for (register size_t i = 0; i < CurrentCache; i++) {
        if (CacheTracks[i].Address == Address64) {
            CurrentCache--;
            if (i != CurrentCache) {
                CacheTracks[i] = CacheTracks[CurrentCache];
            }
            Pool->DirtyAllocations = CurrentCache;
            return;
        }
    }

    register PPOOL_MEMORY_TRACKS Node = (PPOOL_MEMORY_TRACKS)Pool->MemoryTracks.Peers.NextHeader;
    while (Node && Node->Peers.NextHeader) {
        PPOOL_MEMORY_TRACKS Next = (PPOOL_MEMORY_TRACKS)Node->Peers.NextHeader;
        if (Next->Address == Address64) {
            Node->Peers.NextHeader = Next->Peers.NextHeader;
            LouKeFree((void*)Next);
            return;
        }
        Node = Next;
    }

    LouPrint("LouKeFreeFromDynamicPool(): ERROR - Address not found\n");
}

void* LouKeMallocFromDynamicPoolEx(POOL Pool, size_t AllocationSize, size_t Alignment)
{
    if (Pool->FixedSizePool) {
        LouPrint("LouKeMallocFromDynamicPoolEx() : ERROR Input Is A Fixed Pool\n");
        return 0x00;
    }

    register size_t CachedTracks = Pool->ObjectSize;
    register size_t CurrentCache = Pool->DirtyAllocations;
    register size_t Base = Pool->VLocation;
    register size_t Limit = Base + Pool->PoolSize;
    register PPOOL_MEMORY_TRACKS CacheTracks = (PPOOL_MEMORY_TRACKS)Pool->MemoryTracks.Peers.NextHeader;
    register PPOOL_MEMORY_TRACKS Node = 0;
    register size_t Result = ROUND_UP64(Pool->LastOut, Alignment);
    register size_t BlockBase, BlockSize;

    if ((Result + AllocationSize <= Limit) && (CurrentCache < CachedTracks)) {
        CacheTracks[CurrentCache].Address = Result;
        CacheTracks[CurrentCache].MemorySize = AllocationSize;
        Pool->DirtyAllocations++;
        Pool->LastOut = Result + AllocationSize;
        return (void*)Result;
    }

    Result = ROUND_UP64(Base, Alignment);

    while ((Result + AllocationSize) <= Limit) {
        register bool Conflict = false;

        // Check against cache entries
        for (register size_t i = 0; i < CurrentCache; i++) {
            BlockBase = CacheTracks[i].Address;
            BlockSize = CacheTracks[i].MemorySize;
            if (BlockBase && RangeInterferes(Result, AllocationSize, BlockBase, BlockSize)) {
                Result = ROUND_UP64(BlockBase + BlockSize, Alignment);
                Conflict = true;
                break;
            }
        }

        if (Conflict) continue;

        Node = (PPOOL_MEMORY_TRACKS)Pool->MemoryTracks.Peers.NextHeader;
        while (Node && Node->Peers.NextHeader) {
            Node = (PPOOL_MEMORY_TRACKS)Node->Peers.NextHeader;
            BlockBase = Node->Address;
            BlockSize = Node->MemorySize;
            if (BlockBase && RangeInterferes(Result, AllocationSize, BlockBase, BlockSize)) {
                Result = ROUND_UP64(BlockBase + BlockSize, Alignment);
                Conflict = true;
                break;
            }
        }

        if (Conflict) continue;

        if (CurrentCache < CachedTracks) {
            CacheTracks[CurrentCache].Address = Result;
            CacheTracks[CurrentCache].MemorySize = AllocationSize;
            Pool->DirtyAllocations++;
            return (void*)Result;
        }

        for (register size_t i = CurrentCache; i < CachedTracks; i++) {
            if (!CacheTracks[i].Address) {
                CacheTracks[i].Address = Result;
                CacheTracks[i].MemorySize = AllocationSize;
                return (void*)Result;
            }
        }

        Node->Peers.NextHeader = LouKeMallocType(POOL_MEMORY_TRACKS, KERNEL_GENERIC_MEMORY);
        Node = (PPOOL_MEMORY_TRACKS)Node->Peers.NextHeader;
        Node->Address = Result;
        Node->MemorySize = AllocationSize;
        Node->Peers.NextHeader = 0;
        return (void*)Result;
    }

    LouPrint("LouKeMallocFromDynamicPoolEx(): Out of memory\n");
    return 0x00;
}

void* LouKeMallocFromDynamicPool(
    POOL Pool, 
    size_t AllocationSize
){
    return LouKeMallocFromDynamicPoolEx(Pool, AllocationSize, GetAlignmentBySize(AllocationSize));
}