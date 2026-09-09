#include <LouAPI.h>



void InitializePoolsPool(){
    LouKeCreateFastObjectClass(
        "DYNAMIC_POOL_HELPER",
        512,
        sizeof(POOL_MEMORY_TRACKS),
        GET_ALIGNMENT(POOL_MEMORY_TRACKS),
        0,
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

KERNEL_EXPORT
PLMPOOL_DIRECTORY LouKeMapDynamicPoolEx(
    uint64_t    LocationOfPool,
    size_t      PoolSize,
    size_t      CachedTracks,
    string      Tag,
    uint64_t    Flags
){
    CachedTracks = CachedTracks ? CachedTracks : 1;
    POOL NewPool = (POOL)LouKeMallocEx(GetStructureSize(LMPOOL_DIRECTORY, MemoryTracks, CachedTracks), GET_ALIGNMENT(LMPOOL_DIRECTORY), KERNEL_GENERIC_MEMORY);
    NewPool->VLocation = LocationOfPool;
    NewPool->FixedSizePool = false;
    NewPool->Flags = Flags;
    NewPool->Tag = Tag;
    NewPool->ObjectSize = 0;
    NewPool->PoolSize = PoolSize;
    NewPool->FixedSizePool = false;
    NewPool->CachedTracks = CachedTracks;
    return NewPool;
}


KERNEL_EXPORT
PLMPOOL_DIRECTORY LouKeMapDynamicPool(
    uint64_t    LocationOfPool,
    size_t      PoolSize,
    string      Tag,
    uint64_t    Flags
){
    size_t CachedTracks = 1;
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

KERNEL_EXPORT
void LouKeFreeFromFixedPool(
    PLMPOOL_DIRECTORY Pool, 
    void* Object
){
    if(!Pool->FixedSizePool){
        LouPrint("LouKeMallocFromFixedPool() : ERROR Input Is Not A Fixed Pool\n");
        return;
    }
    PPOOL_MEMORY_TRACKS TmpPoolMemTrack = Pool->MemoryTracks;
    MutexLock(&Pool->PoolLock);
    uint64_t Index = ((uint64_t)Object - Pool->VLocation) / ROUND_UP64(Pool->ObjectSize, Pool->Alignment);    

    if(TmpPoolMemTrack[Index].Address != (uint64_t)Object){
        LouPrint("LouKeMallocFromFixedPool() : Error Memory Leak\n");
        MutexUnlock(&Pool->PoolLock);
        return;
    } 
    TmpPoolMemTrack[Index].AddressInUse = false;
    MutexUnlock(&Pool->PoolLock);
}

KERNEL_EXPORT
void* LouKeMallocFromFixedPool(
    PLMPOOL_DIRECTORY Pool
){
    if(!Pool->FixedSizePool){
        LouPrint("LouKeMallocFromFixedPool() : ERROR Input Is Not A Fixed Pool\n");
        return 0x00;
    }
    PPOOL_MEMORY_TRACKS TmpPoolMemTrack = Pool->MemoryTracks;
    MutexLock(&Pool->PoolLock);
    for(uint64_t i = 0 ; i < Pool->PoolSize; i++){
        if(!TmpPoolMemTrack[i].AddressInUse){
            TmpPoolMemTrack[i].AddressInUse = true;
            MutexUnlock(&Pool->PoolLock);
            memset((void*)TmpPoolMemTrack[i].Address, 0x00, Pool->ObjectSize);
            return (void*)TmpPoolMemTrack[i].Address;
        }
    }
    MutexUnlock(&Pool->PoolLock);
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
    POOL NewPool = (POOL)LouKeMallocExSafe(GetStructureSize(LMPOOL_DIRECTORY, MemoryTracks, NumberOfPoolMembers), GET_ALIGNMENT(LMPOOL_DIRECTORY), KERNEL_GENERIC_MEMORY);
    NewPool->VLocation = (uint64_t)LouKeMallocExSafe(ROUND_UP64(ObjectSize, Alignment) * NumberOfPoolMembers, Alignment, PageFlags);
    RequestPhysicalAddress(NewPool->VLocation, &NewPool->Location);
    NewPool->FixedSizePool = true;
    NewPool->Flags = Flags;
    NewPool->Tag = Tag;
    NewPool->ObjectSize = ObjectSize;
    NewPool->PoolSize = NumberOfPoolMembers;
    NewPool->Alignment = Alignment;
    PPOOL_MEMORY_TRACKS TmpPoolMemTrack = NewPool->MemoryTracks;
    for(uint64_t i = 0; i < NumberOfPoolMembers; i++){
        TmpPoolMemTrack[i].Address = NewPool->VLocation + (ROUND_UP64(ObjectSize, Alignment) * i);
        TmpPoolMemTrack[i].AddressInUse = false;
    }
    return NewPool;
}

KERNEL_EXPORT
void LouKeDestroyFixedPool(PLMPOOL_DIRECTORY Pool){
    LouKeFreeSafe((void*)Pool->VLocation);
    LouKeFreeSafe((void*)Pool);
}

void LouKeMallocTrimFixedPool(
    PLMPOOL_DIRECTORY Pool
){

}

void LouKeFreePool(PLMPOOL_DIRECTORY PoolToFree){
    LouPrint("LouKeFreePool()\n");
    while(1);
}

KERNEL_EXPORT
PLMPOOL_DIRECTORY LouKeCreateDynamicPoolEx(
    size_t PoolSize,
    size_t CachedTracks,
    size_t PagedTypeAlignement,
    string Tag,
    uint64_t Flags,
    uint64_t PageFlags
){
    CachedTracks = CachedTracks ? CachedTracks : 1;
    POOL NewPool = (POOL)LouKeMallocEx(GetStructureSize(LMPOOL_DIRECTORY, MemoryTracks, CachedTracks), GET_ALIGNMENT(LMPOOL_DIRECTORY), KERNEL_GENERIC_MEMORY);
    NewPool->VLocation = (uint64_t)LouKeMallocEx(PoolSize, PagedTypeAlignement, PageFlags);
    RequestPhysicalAddress(NewPool->VLocation, &NewPool->Location);
    NewPool->LastOut = NewPool->VLocation;
    NewPool->FixedSizePool = false;
    NewPool->Flags = Flags;
    NewPool->Tag = Tag;
    NewPool->PoolSize = PoolSize;
    NewPool->CachedTracks = CachedTracks;
    return NewPool;
}

PLMPOOL_DIRECTORY LouKeCreateDynamicPool(
    size_t PoolSize,
    size_t PagedTypeAlignement,
    string Tag,
    uint64_t Flags,
    uint64_t PageFlags
){
    size_t CachedTracks = 1;
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

KERNEL_EXPORT
void LouKeFreeFromDynamicPool(POOL Pool, void* Address){

    PPOOL_MEMORY_TRACKS Node;
    PPOOL_MEMORY_TRACKS sNode;
    UNUSED SIZE CachedMember = Pool->CachedTracks;
    MutexLock(&Pool->PoolLock);
    Node = Pool->MemoryTracks;
    for(SIZE i = 0 ; i < CachedMember; i++){
        if((Node[i].AddressInUse) && (Node[i].Address == (UINTPTR)Address)){
            Node[i].Address = 0x00;
            Node[i].MemorySize = 0x00;
            Node[i].AddressInUse = false;
            MutexUnlock(&Pool->PoolLock);
            return;
        }
    }
    ForEachListEntrySafe(Node, sNode, &Pool->MemoryTracks->Peers, Peers){
        if(Node->Address == (uint64_t)Address) {
            LouKeListDeleteItem(&Node->Peers);
            LouKeFreeFastObject("DYNAMIC_POOL_HELPER", Node);
            MutexUnlock(&Pool->PoolLock);
            return;
        }
    }
    MutexUnlock(&Pool->PoolLock);
    LouPrint("LouKeFreeFromDynamicPool(): ERROR - Address not found: %h\n", Address);
}


KERNEL_EXPORT
void* LouKeMallocFromDynamicPoolEx(POOL Pool, size_t AllocationSize, size_t Alignment){
    if(Pool->FixedSizePool) {
        LouPrint("LouKeMallocFromDynamicPoolEx(): ERROR - FixedSizePool input\n");
        return NULL;
    }   
    BOOLEAN NoWrapArround = Pool->Flags & POOL_FLAG_NO_WRAP_ARROUND;
    BOOLEAN NoMemset = Pool->Flags & POOL_FLAG_NO_MEMSET; 
    size_t Base = Pool->VLocation;
    size_t Limit = Base + Pool->PoolSize;
    uint64_t Start;
    MutexLock(&Pool->PoolLock);
    if(!NoWrapArround){
        Start = ROUND_UP64(Pool->LastOut ? Pool->LastOut : Base, Alignment);
    }else{
        Start = ROUND_UP64(Base, Alignment);
    }
    uint64_t Result = Start;
    bool Wrapped = false;
    UNUSED SIZE CachedMembers = Pool->CachedTracks;
    PPOOL_MEMORY_TRACKS Node = Pool->MemoryTracks;
    PPOOL_MEMORY_TRACKS nNode = 0x00;
    for(SIZE i = 0; i < CachedMembers; i++){
        if(!Node[i].AddressInUse){
            nNode = &Node[i];
            break;
        }
    }

_RETRY_SEARCH:
    while((Result + AllocationSize) <= Limit){
        bool Conflict = false;
        Node = Pool->MemoryTracks;
        for(SIZE i = 0; i < CachedMembers; i++){
            if((Node[i].AddressInUse) && (RangeInterferes(Result, AllocationSize, Node[i].Address, Node[i].MemorySize))){
                Result = ROUND_UP64(Node[i].Address + Node[i].MemorySize, Alignment);
                Conflict = true;
                goto _NEXT_CHECK;
            }
        }    
_NEXT_CHECK:
        if(Conflict){
            continue;
        }
        ForEachListEntry(Node, &Pool->MemoryTracks->Peers, Peers){
            if (RangeInterferes(Result, AllocationSize, Node->Address, Node->MemorySize)) {
                Result = ROUND_UP64(Node->Address + Node->MemorySize, Alignment);
                Conflict = true;
                goto _DONE_CHECKING;
            }
        }
_DONE_CHECKING:
        if(!Conflict){
            if(!nNode){
                nNode = LouKeAllocateFastObject("DYNAMIC_POOL_HELPER");
                LouKeListAddTail(&nNode->Peers, &Pool->MemoryTracks->Peers);
            }
            nNode->AddressInUse = true;
            nNode->Address = Result;
            nNode->MemorySize = AllocationSize;
            if(!NoWrapArround){
                Pool->LastOut = Result;
            }
            if(!NoMemset){
                memset((PVOID)Result, 0, AllocationSize);
            }
            MutexUnlock(&Pool->PoolLock);
            return (PVOID)Result;
        }
    }
    if((!Wrapped && Start != Base) && (!NoWrapArround)) {
        Result = ROUND_UP64(Base, Alignment);
        Wrapped = true;
        goto _RETRY_SEARCH;
    }
    MutexUnlock(&Pool->PoolLock);
    return 0x00;
}


KERNEL_EXPORT
void* LouKeMallocFromDynamicPool(
    POOL Pool, 
    size_t AllocationSize
){
    return LouKeMallocFromDynamicPoolEx(Pool, AllocationSize, GetAlignmentBySize(AllocationSize));
}

void LouKeDestroyDynamicPool(
    POOL Pool
){
    PPOOL_MEMORY_TRACKS Node;
    ForEachListEntry(Node, &Pool->MemoryTracks->Peers, Peers){
        LouKeFreeFastObject("DYNAMIC_POOL_HELPER", Node);
    }
    LouKeFree((void*)Pool->VLocation);
    LouKeFree((void*)Pool);
}

KERNEL_EXPORT
POOL LouKeCreateGenericPool(
    uint64_t VLocation,
    uint64_t Location,
    uint64_t size,
    uint64_t Flags
){

    POOL NewPool = LouKeMapDynamicPool(
        VLocation,
        size,
        0x00,
        Flags
    );
    NewPool->Location = Location;
    return NewPool;
}

KERNEL_EXPORT
void* LouKeGenericPoolGetPhyAddress(
    POOL Pool,
    void* Address
){
    return (void*)Pool->Location + ((uint64_t)Address - Pool->VLocation);
}

KERNEL_EXPORT
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

KERNEL_EXPORT
void* LouKeGenericAllocateFixedDmaPool(
    POOL Pool,
    size_t* Offset
){
    uint64_t Result = (uint64_t)LouKeMallocFromFixedPool(Pool);

    if(Offset){
        *Offset = (uint64_t)LouKeGenericPoolGetPhyAddress(Pool, (void*)Result);
    }

    return (void*)Result;
}