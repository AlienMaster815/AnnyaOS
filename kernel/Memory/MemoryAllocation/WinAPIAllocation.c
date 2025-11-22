#include <LouAPI.h>

typedef struct _HEAP_ALLOCATION_TABLE_ENTRY{
    ListHeader  Neighbors;
    uint64_t    AllocationFlags;
    uintptr_t   Address;
    size_t      size;
}HEAP_ALLOCATION_TABLE_ENTRY, * PHEAP_ALLOCATION_TABLE_ENTRY;

typedef struct _HEAP_PHY_TRACK{
    ListHeader  Neighbors;
    uint64_t    AllocationFlags;
    uintptr_t   VirtualOffset;
    uintptr_t   PhyAddress;
}HEAP_PHY_TRACK, * PHEAP_PHY_TRACK;

typedef struct _HEAP_TRACK{
    ListHeader                      Neighbors;
    uint64_t                        HeapFlags;
    uintptr_t                       VirtualAddress;
    size_t                          VirtualSize; //Heap Reserved
    uint64_t                        PhyTracksCount;
    HEAP_PHY_TRACK                  PhyTracks;
    uint64_t                        AllocationsCount;
    HEAP_ALLOCATION_TABLE_ENTRY     Allocations;
}HEAP_TRACK, * PHEAP_TRACK;

static HEAP_TRACK  HeapTracks = {0};
static uint64_t    HeapsManaged = 0;

//returns a void* to a new heap
void* LouKeVirtualAllocUser(
    size_t      CommitSize,     //allocated PhysicalMemory
    size_t      ReservedSize,   //AllocatedVirtual
    uint64_t    PageFlags
){
    PHEAP_TRACK TmpHeapTrack = &HeapTracks;
    uint64_t i = 0;
    for(i = 0; i < HeapsManaged; i++){
        if(!TmpHeapTrack->Neighbors.NextHeader){
            TmpHeapTrack->Neighbors.NextHeader = (PListHeader)LouKeMallocType(HEAP_TRACK, USER_GENERIC_MEMORY);
        }
        TmpHeapTrack = (PHEAP_TRACK)TmpHeapTrack->Neighbors.NextHeader;
    }

    TmpHeapTrack->VirtualAddress = (uintptr_t)LouVMallocEx(ReservedSize, KILOBYTE_PAGE);
    TmpHeapTrack->VirtualSize = ReservedSize;
    
    TmpHeapTrack->PhyTracks.VirtualOffset = 0;    
    TmpHeapTrack->PhyTracks.PhyAddress = (uintptr_t)LouAllocatePhysical64UpEx(CommitSize, KILOBYTE_PAGE);

    LouKeMapContinuousMemoryBlock(TmpHeapTrack->PhyTracks.PhyAddress, TmpHeapTrack->VirtualAddress, CommitSize, PageFlags);
    HeapsManaged++;
    return (void*)TmpHeapTrack;
}

static uint64_t LouKeAllocHeapFreeAddress(
    PHEAP_TRACK HeapTrack,
    uint64_t AllocationSize,
    uint64_t Alignment  
){
    uint64_t HeapEndAddress = HeapTrack->VirtualAddress + HeapTrack->VirtualSize;
    uint64_t HeapBase = HeapTrack->VirtualAddress;

    uint64_t FreeAllocation = HeapBase;
    FreeAllocation = ROUND_UP64(FreeAllocation, Alignment);
    while((FreeAllocation + AllocationSize) <= HeapEndAddress){
        bool ValidAddress = true;
        PHEAP_ALLOCATION_TABLE_ENTRY TmpAllocationTrack = &HeapTrack->Allocations;
        uint64_t start;
        uint64_t end;
        for(uint64_t i = 0; i < HeapTrack->AllocationsCount; i++){
            start = TmpAllocationTrack->Address;
            end = start + TmpAllocationTrack->size;
            if((FreeAllocation >= start && FreeAllocation <= end) ||  // Start within an existing block
            ((FreeAllocation + AllocationSize) >= start && (FreeAllocation + AllocationSize) <= end) || // End within an existing block
            (FreeAllocation <= start && (FreeAllocation + AllocationSize) >= end)){
                ValidAddress = false;
                FreeAllocation += ROUND_UP64(Alignment, TmpAllocationTrack->size);
                break;
            }
            if(!TmpAllocationTrack->Neighbors.NextHeader){
                TmpAllocationTrack->Neighbors.NextHeader = (PListHeader)LouKeMallocType(HEAP_ALLOCATION_TABLE_ENTRY, USER_GENERIC_MEMORY);
            }
            TmpAllocationTrack = (PHEAP_ALLOCATION_TABLE_ENTRY)TmpAllocationTrack->Neighbors.NextHeader;
        }
        if(ValidAddress){
            PHEAP_ALLOCATION_TABLE_ENTRY Entry = &HeapTrack->Allocations;
            for(uint64_t i = 0; i < HeapTrack->AllocationsCount; i++) {
                Entry = (PHEAP_ALLOCATION_TABLE_ENTRY)Entry->Neighbors.NextHeader;
            }
            // Create new entry
            Entry->Address = FreeAllocation;
            Entry->size = AllocationSize;
            HeapTrack->AllocationsCount++;
            return FreeAllocation;
        }
    }
    return 0x00;
}

void LouKeAllocHeapPhysical(
    PHEAP_TRACK HeapTrack,
    uint64_t Offset, 
    size_t size
){
    
    uint64_t Offset1 = ROUND_UP64(Offset, KILOBYTE_PAGE) - KILOBYTE_PAGE;
    uint64_t Offset2 = ROUND_UP64(Offset + size, KILOBYTE_PAGE);

    PHEAP_PHY_TRACK PhyTrack = &HeapTrack->PhyTracks;
    
    for(uint64_t i = 0; i < HeapTrack->PhyTracksCount; i++){
        if(Offset1 == PhyTrack->VirtualOffset){
            Offset1 += KILOBYTE_PAGE; 
            PhyTrack = &HeapTrack->PhyTracks;
            i = 0;
        }
        if(Offset1 >= Offset2){
            //all addresses needed have already been mapped
            return;
        }
        if(!PhyTrack->Neighbors.NextHeader){
            PhyTrack = (PHEAP_PHY_TRACK)LouKeMallocType(HEAP_PHY_TRACK, USER_GENERIC_MEMORY);
        }
        PhyTrack = (PHEAP_PHY_TRACK)PhyTrack->Neighbors.NextHeader;
    }
    size_t NeededPhysicalSize = Offset2 - Offset1;
    for(uint64_t i = 0; i < NeededPhysicalSize; i += KILOBYTE_PAGE){
        uint64_t NewPhysical = (uint64_t)LouAllocatePhysical64UpEx(KILOBYTE_PAGE, KILOBYTE_PAGE);
        LouKeMapContinuousMemoryBlock(NewPhysical, Offset1, KILOBYTE_PAGE, USER_GENERIC_MEMORY);
        PhyTrack->PhyAddress = NewPhysical;
        PhyTrack->VirtualOffset = Offset1 + i;
        if (!PhyTrack->Neighbors.NextHeader) {
            PhyTrack->Neighbors.NextHeader = (PListHeader)LouKeMallocType(HEAP_PHY_TRACK,  USER_GENERIC_MEMORY);
        }
        PhyTrack = (PHEAP_PHY_TRACK)PhyTrack->Neighbors.NextHeader;
        HeapTrack->PhyTracksCount++;
    }
}

void* LouKeGenericAllocateHeapEx(
    void* HeapHandle, 
    size_t AllocationSize,
    size_t Alignment
){
    PHEAP_TRACK TmpHeapHandle = (PHEAP_TRACK)HeapHandle;

    uint64_t AllocatedHeapAddress = LouKeAllocHeapFreeAddress(TmpHeapHandle, AllocationSize, Alignment);

    if(!AllocatedHeapAddress){
        return (void*)AllocatedHeapAddress;
    }
    uint64_t Offset = AllocatedHeapAddress - TmpHeapHandle->VirtualAddress;
    LouKeAllocHeapPhysical(TmpHeapHandle, Offset, AllocationSize);
    return (void*)AllocatedHeapAddress;
}

void LouKeGenericHeapFree(void* heap, void* Address) {
    PHEAP_TRACK TmpHeapHandle = (PHEAP_TRACK)heap;
    uint64_t AddressToFree = (uint64_t)Address;

    PHEAP_ALLOCATION_TABLE_ENTRY TmpEntry = &TmpHeapHandle->Allocations;
    PHEAP_ALLOCATION_TABLE_ENTRY PrevEntry = NULL;

    for (uint64_t i = 0; i < TmpHeapHandle->AllocationsCount; i++) {
        
        if (TmpEntry->Address == AddressToFree) {

            // Found the allocation to free
            if (PrevEntry) {
                PrevEntry->Neighbors.NextHeader = TmpEntry->Neighbors.NextHeader;
            } else {
                if (TmpEntry->Neighbors.NextHeader) {
                    memcpy(&TmpHeapHandle->Allocations, TmpEntry->Neighbors.NextHeader, sizeof(HEAP_ALLOCATION_TABLE_ENTRY));
                } else {
                    memset(&TmpHeapHandle->Allocations, 0, sizeof(HEAP_ALLOCATION_TABLE_ENTRY));
                }
            }

            LouKeFree(TmpEntry);
            TmpHeapHandle->AllocationsCount--;
            return;
        }

        PrevEntry = TmpEntry;
        TmpEntry = (PHEAP_ALLOCATION_TABLE_ENTRY)TmpEntry->Neighbors.NextHeader;
    }
}
