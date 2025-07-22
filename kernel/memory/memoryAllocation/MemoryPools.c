#include <LouAPI.h>


static POOL PoolsPool = 0x00;

void InitializePoolsPool(){
    PoolsPool = LouKeCreateFixedPool(
        (32 * MEGABYTE) / sizeof(POOL_MEMORY_TRACKS), 
        sizeof(POOL_MEMORY_TRACKS), 
        GET_ALIGNMENT(POOL_MEMORY_TRACKS), 
        "PoolsPool", 
        0 , 
        KERNEL_GENERIC_MEMORY
    );
}

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

PLMPOOL_DIRECTORY LouKeMapDynamicPoolEx(
    uint64_t    LocationOfPool,
    size_t      PoolSize,
    size_t      CachedTracks,
    string      Tag,
    uint64_t    Flags
){
    POOL NewPool = (POOL)LouKeMallocType(LMPOOL_DIRECTORY, KERNEL_GENERIC_MEMORY);
    NewPool->VLocation = LocationOfPool;
    NewPool->FixedSizePool = false;
    NewPool->Flags = Flags;
    NewPool->Tag = Tag;
    NewPool->ObjectSize = CachedTracks;
    NewPool->PoolSize = PoolSize;
    PPOOL_MEMORY_TRACKS TmpPoolMemTrack = &NewPool->MemoryTracks;
    TmpPoolMemTrack->Peers.NextHeader = (PListHeader)LouKeMallocArray(POOL_MEMORY_TRACKS, CachedTracks, KERNEL_GENERIC_MEMORY);  
    NewPool->FixedSizePool = false;
    return NewPool;
}

PLMPOOL_DIRECTORY LouKeMapDynamicPool(
    uint64_t    LocationOfPool,
    size_t      PoolSize,
    string      Tag,
    uint64_t    Flags
){
    size_t CachedTracks = 0;
    if(PoolSize > KILOBYTE_PAGE){
        CachedTracks = PoolSize/KILOBYTE_PAGE;
    }
    return LouKeMapDynamicPoolEx(
        LocationOfPool,
        PoolSize,
        CachedTracks,
        Tag,
        Flags
    );  
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

void LouKeFreeFromFixedPool(
    PLMPOOL_DIRECTORY Pool, 
    void* Object
){
    if(!Pool->FixedSizePool){
        LouPrint("LouKeMallocFromFixedPool() : ERROR Input Is Not A Fixed Pool\n");
        return;
    }
    PPOOL_MEMORY_TRACKS TmpPoolMemTrack = &Pool->MemoryTracks;
    TmpPoolMemTrack = (PPOOL_MEMORY_TRACKS)TmpPoolMemTrack->Peers.NextHeader;
    
    uint64_t Index = ((uint64_t)Object - Pool->VLocation) / Pool->ObjectSize;    

    if(TmpPoolMemTrack[Index].Address != (uint64_t)Object){
        LouPrint("LouKeMallocFromFixedPool() : Error Memory Leak\n");
        return;
    } 
    TmpPoolMemTrack[Index].AddressInUse = false;
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
    NewPool->PoolSize = PoolSize;
    return NewPool;
}

PLMPOOL_DIRECTORY LouKeCreateDynamicPool(
    size_t PoolSize,
    size_t PagedTypeAlignement,
    string Tag,
    uint64_t Flags,
    uint64_t PageFlags
){
    size_t CachedTracks = 0;
    if(PoolSize > KILOBYTE_PAGE){
        CachedTracks = PoolSize/KILOBYTE_PAGE;
    }
    return LouKeCreateDynamicPoolEx(
        PoolSize,
        CachedTracks, //for each kilobyte page memory expands default one cache
        PagedTypeAlignement,
        Tag,
        Flags,
        PageFlags
    );
}

void LouKeFreeFromDynamicPool(POOL Pool, void* Address)
{
    PPOOL_MEMORY_TRACKS Prev = (PPOOL_MEMORY_TRACKS)&Pool->MemoryTracks;
    PPOOL_MEMORY_TRACKS Node = (PPOOL_MEMORY_TRACKS)Prev->Peers.NextHeader;

    while (Node) {
        if (Node->Address == (uint64_t)Address) {
            Prev->Peers.NextHeader = Node->Peers.NextHeader;
            LouKeFreeFromFixedPool(PoolsPool, Node);
            return;
        }
        Prev = Node;
        Node = (PPOOL_MEMORY_TRACKS)Node->Peers.NextHeader;
    }

    LouPrint("LouKeFreeFromDynamicPool(): ERROR - Address not found: %h\n", Address);
}


void* LouKeMallocFromDynamicPoolEx(POOL Pool, size_t AllocationSize, size_t Alignment)
{
    if (Pool->FixedSizePool) {
        LouPrint("LouKeMallocFromDynamicPoolEx(): ERROR - FixedSizePool input\n");
        return NULL;
    }

    size_t Base = Pool->VLocation;
    size_t Limit = Base + Pool->PoolSize;
    uint64_t Start = Pool->LastOut ? Pool->LastOut : Base;
    uint64_t Result = Start;
    bool Wrapped = false;

retry_search:
    while ((Result + AllocationSize) <= Limit) {
        bool Conflict = false;
        PPOOL_MEMORY_TRACKS Node = (PPOOL_MEMORY_TRACKS)Pool->MemoryTracks.Peers.NextHeader;

        while (Node) {
            if (RangeInterferes(Result, AllocationSize, Node->Address, Node->MemorySize)) {
                Result = ROUND_UP64(Node->Address + Node->MemorySize, Alignment);
                Conflict = true;
                break;
            }
            Node = (PPOOL_MEMORY_TRACKS)Node->Peers.NextHeader;
        }

        if (!Conflict) {
            PPOOL_MEMORY_TRACKS NewTrack = (PPOOL_MEMORY_TRACKS)LouKeMallocFromFixedPool(PoolsPool);
            NewTrack->Address = Result;
            NewTrack->MemorySize = AllocationSize;
            NewTrack->Peers.NextHeader = Pool->MemoryTracks.Peers.NextHeader;
            Pool->MemoryTracks.Peers.NextHeader = (PListHeader)NewTrack;

            Pool->LastOut = Result + AllocationSize;
            return (void*)Result;
        }
    }

    if (!Wrapped && Start != Base) {
        Result = Base;
        Wrapped = true;
        goto retry_search;
    }

    LouPrint("LouKeMallocFromDynamicPoolEx(): OUT OF MEMORY: Requested=%h PoolSize=%h\n", AllocationSize, Pool->PoolSize);
    return NULL;
}


void* LouKeMallocFromDynamicPool(
    POOL Pool, 
    size_t AllocationSize
){
    return LouKeMallocFromDynamicPoolEx(Pool, AllocationSize, GetAlignmentBySize(AllocationSize));
}

POOL LouKeCreateGenericPool(
    uint64_t VLocation,
    uint64_t Location,
    uint64_t size,
    uint64_t Flags
){

    POOL NewPool = LouKeMapDynamicPoolEx(
        VLocation,
        size,
        1,
        0x00,
        Flags
    );
    NewPool->Location = Location;
    return NewPool;
}

void* LouKeGenericPoolGetPhyAddress(
    POOL Pool,
    void* Address
){
    return (void*)Pool->Location + ((uint64_t)Address - Pool->VLocation);
}

void* LouKeGenricAllocateDmaPool(
    POOL Pool,
    size_t size,
    size_t* Offset
){

    uint64_t Result = (uint64_t)LouKeMallocFromDynamicPool(Pool, size);
    if(Offset){
        *Offset = (uint64_t)LouKeGenericPoolGetPhyAddress(Pool, (void*)Result);
    }

    return (void*)Result;
}