#include <Compiler.h>

static POOL PoolsPool = 0x00;

#define MEGABYTE (1ULL << 20)  // 1 MB in bytes

void* LouKeGenericPoolGetPhyAddress(
    POOL Pool,
    void* Address
){
    return (void*)Pool->Location + ((uint64_t)Address - Pool->VLocation);
}

PLMPOOL_DIRECTORY LouKeCreateFixedPool(
    uint64_t NumberOfPoolMembers,
    uint64_t ObjectSize,
    uint64_t Alignment,
    string Tag,
    uint64_t Flags,
    UNUSED uint64_t PageFlags //unused for user mode
){
    POOL NewPool = (POOL)LouKeMallocType(LMPOOL_DIRECTORY, KERNEL_GENERIC_MEMORY);
    NewPool->VLocation = (uint64_t)LouKeMallocEx(ROUND_UP64(ObjectSize, Alignment) * NumberOfPoolMembers, Alignment, PageFlags);
    
    //physical address ignored in userspace
    //RequestPhysicalAddress(NewPool->VLocation, &NewPool->Location);
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

void LouKeDestroyFixedPool(
    PLMPOOL_DIRECTORY Pool
){
    LouKeFree((PVOID)Pool->VLocation);
    LouKeFree(Pool->MemoryTracks.Peers.NextHeader);
    LouKeFree(Pool);
}


void InitializePoolsPool(){
    PoolsPool = LouKeCreateFixedPool(
        (8 * MEGABYTE) / sizeof(POOL_MEMORY_TRACKS), 
        sizeof(POOL_MEMORY_TRACKS), 
        GET_ALIGNMENT(POOL_MEMORY_TRACKS), 
        "PoolsPool", 
        0 , 
        KERNEL_GENERIC_MEMORY
    );
}

void DeInitializePoolsPool(){
    LouKeDestroyFixedPool(PoolsPool);
}

void LouKeFreeFromFixedPool(
    PLMPOOL_DIRECTORY Pool, 
    void* Object
){
    if(!Pool->FixedSizePool){
        printf("LouKeMallocFromFixedPool() : ERROR Input Is Not A Fixed Pool\n");
        return;
    }
    PPOOL_MEMORY_TRACKS TmpPoolMemTrack = &Pool->MemoryTracks;
    TmpPoolMemTrack = (PPOOL_MEMORY_TRACKS)TmpPoolMemTrack->Peers.NextHeader;
    
    uint64_t Index = ((uint64_t)Object - Pool->VLocation) / Pool->ObjectSize;    

    if(TmpPoolMemTrack[Index].Address != (uint64_t)Object){
        printf("LouKeMallocFromFixedPool() : Error Memory Leak\n");
        return;
    } 
    TmpPoolMemTrack[Index].AddressInUse = false;
}

void* LouKeMallocFromFixedPool(
    PLMPOOL_DIRECTORY Pool
){
    if(!Pool->FixedSizePool){
        printf("LouKeMallocFromFixedPool() : ERROR Input Is Not A Fixed Pool\n");
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

PLMPOOL_DIRECTORY LouKeCreateDynamicPoolEx(
    size_t PoolSize,
    UNUSED size_t CachedTracks,
    UNUSED size_t PagedTypeAlignement,
    string Tag,
    uint64_t Flags,
    UNUSED uint64_t PageFlags
){
    POOL NewPool = (POOL)LouKeMallocType(LMPOOL_DIRECTORY, KERNEL_GENERIC_MEMORY);
    NewPool->VLocation = (uint64_t)LouKeMallocEx(PoolSize, PagedTypeAlignement, PageFlags);
    //RequestPhysicalAddress(NewPool->VLocation, &NewPool->Location);
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

void LouKeFreeFromDynamicPool(POOL Pool, void* Address){
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

    printf("LouKeFreeFromDynamicPool(): ERROR - Address not found: %zu\n", (size_t)Address);
}


void* LouKeMallocFromDynamicPoolEx(POOL Pool, size_t AllocationSize, size_t Alignment)
{
    if (Pool->FixedSizePool) {
        printf("LouKeMallocFromDynamicPoolEx(): ERROR - FixedSizePool input\n");
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

    printf("LouKeMallocFromDynamicPoolEx(): OUT OF MEMORY: Requested=%zu PoolSize=%zu\n", AllocationSize, Pool->PoolSize);
    return NULL;
}


void* LouKeMallocFromDynamicPool(
    POOL Pool, 
    size_t AllocationSize
){
    return LouKeMallocFromDynamicPoolEx(Pool, AllocationSize, GetAlignmentBySize(AllocationSize));
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

