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
    POOL NewPool = (POOL)LouKeMallocType(sizeof(LMPOOL_DIRECTORY), KERNEL_GENERIC_MEMORY);
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