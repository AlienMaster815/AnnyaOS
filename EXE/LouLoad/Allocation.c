#include <LouLoad.h>
#include <LoaderPrivate.h>


LOULOAD_MEMORY_TRACKER MemoryTracker[512] = {0};

extern LOUSINE_LOADER_INFO KernelLoaderInfo;

static uint64_t mlimit = 0;

size_t GetRamSize(){
    return  mlimit;
}

static inline
bool RangeInterferes(
    uint64_t AddressForCheck, 
    uint64_t SizeOfCheck,
    uint64_t AddressOfBlock, 
    uint64_t SizeOfBlock
) {   
    uint64_t Start = AddressOfBlock;
    uint64_t End = AddressOfBlock + SizeOfBlock;
    if (
        ((AddressForCheck >= Start) && (AddressForCheck < End)) ||
        (((AddressForCheck + SizeOfCheck) >= Start) && ((AddressForCheck + SizeOfCheck) < End)) ||
        ((AddressForCheck <= Start) && ((AddressForCheck + SizeOfCheck) >= End))
    ) {
        return true;
    }
    return false;
}

void 
EnforceLoaderMemoryMap(
    UINT64  Address,
    UINT64  size
){
    UINT16  PartitionItems = KernelLoaderInfo.RatPartition.PartitionItems;
    UINT64  SmallestAddress = 0;
    UINT64  LargestAddress = 0;

    for(UINT64 i = 0 ; i < PartitionItems; i++){
        if(RangeInterferes(
            Address,
            size,
            MemoryTracker[i].Address,
            MemoryTracker[i].size
        )){
            if(
                (MemoryTracker[i].Address == Address) && 
                (MemoryTracker[i].size == size)
            ){
                return;
            }
            
            SmallestAddress = MIN(MemoryTracker[i].Address, Address);
            LargestAddress = MAX(MemoryTracker[i].Address + MemoryTracker[i].size, Address + size);

            MemoryTracker[i].Address = SmallestAddress;
            MemoryTracker[i].size = LargestAddress - SmallestAddress;
            return;
        }
    }

    MemoryTracker[PartitionItems].Address = Address;
    MemoryTracker[PartitionItems].size = size;

    PartitionItems++; 
    KernelLoaderInfo.RatPartition.PartitionItems = PartitionItems;
    
}


void ParseRamMap(
    struct multiboot_tag* RamMap
){
    struct master_multiboot_mmap_entry* mmap = (struct master_multiboot_mmap_entry*)RamMap;
    UINT64  EntryCount = (UINT64)((mmap->tag.size - sizeof(struct master_multiboot_mmap_entry)) / mmap->entry_size);

    struct multiboot_mmap_entry* MapEntry;
    for(UINT64 i = 0 ; i < EntryCount; i++){
        MapEntry = MapIndexToEntry(mmap, i);
        if((MapEntry->addr + MapEntry->len) > mlimit){
            mlimit = MapEntry->addr + MapEntry->len;
        }
        if(MapEntry->type != 1){
            EnforceLoaderMemoryMap(MapEntry->addr, MapEntry->len);
            EnforceLoaderMemoryMap(MapEntry->addr + GetKSpaceBase(), MapEntry->len);
        }
    }

}

static void* RunThroughAllocationCheck(
    struct multiboot_mmap_entry*    MapEntry,
    size_t                          RequestSize,
    size_t                          Alignment
){

    if((MapEntry->addr + MapEntry->len) <= (64 * MEGABYTE)){
        return 0x00;
    }        

    const UINT16  PartitionItems = KernelLoaderInfo.RatPartition.PartitionItems;
    UINT64 Base = MAX(MapEntry->addr, 64 * MEGABYTE);
    const UINT64 Limit = MapEntry->addr + MapEntry->len;
    Base = ROUND_UP64(Base, Alignment);

    while((Base + RequestSize) <= Limit){
        UINT16 i;
        for(i = 0 ; i < PartitionItems; i++){
            if(RangeInterferes(
                Base,
                RequestSize,
                MemoryTracker[i].Address,
                MemoryTracker[i].size
            )){
                goto _RETRY_ALLOCATION;
            }
        }

        MemoryTracker[PartitionItems].Address = Base;
        MemoryTracker[PartitionItems].size = RequestSize;
        KernelLoaderInfo.RatPartition.PartitionItems++;
        return (void*)Base;

        _RETRY_ALLOCATION:
        Base += ROUND_UP64(MemoryTracker[i].size, Alignment); 
    }
    return 0x00;
}

void* LoaderAllocateMemoryEx(
    size_t  size,
    size_t  Alignment
){
    struct master_multiboot_mmap_entry* mmap = (struct master_multiboot_mmap_entry*)(UINT8*)KernelLoaderInfo.RatPartition.RamMap;
    UINT16  EntryCount = (mmap->tag.size - sizeof(struct master_multiboot_mmap_entry)) / mmap->entry_size;
    void* Result = 0;
    struct multiboot_mmap_entry* MapEntry;
    for(UINT16 i = 0 ; i < EntryCount; i++){
        MapEntry = MapIndexToEntry(mmap, i);
        if(MapEntry->type == 1){
            Result = RunThroughAllocationCheck(MapEntry, size, Alignment);
            if(Result){
                memzero(Result, size);
                return Result;
            }        
        }
    }
    return 0x00;
}

void* LoaderAllocateMemory(
    size_t  size
){
    return LoaderAllocateMemoryEx(
        size,
        ROUND_UP64(size, 8)
    );
}

bool 
LoaderRequestMemory(
    void* Address,
    size_t size
){
    struct master_multiboot_mmap_entry* mmap = (struct master_multiboot_mmap_entry*)(UINT8*)KernelLoaderInfo.RatPartition.RamMap;
    UINT16  EntryCount = (mmap->tag.size - sizeof(struct master_multiboot_mmap_entry)) / mmap->entry_size;

    const UINT16 PartitionItems = KernelLoaderInfo.RatPartition.PartitionItems;
    size_t j;
    for(j = 0 ; j < PartitionItems; j++){
        if(RangeInterferes(
            MemoryTracker[j].Address,
            MemoryTracker[j].size,
            (UINT64)Address,
            size
        )){
            return false;
        }
    }

    struct multiboot_mmap_entry* MapEntry;
    for(UINT16 i = 0 ; i < EntryCount; i++){
        MapEntry = MapIndexToEntry(mmap, i);
        if(MapEntry->type == 1){
            if((MapEntry->addr <= (UINT64)Address) && 
               (MapEntry->addr + MapEntry->len) >= ((UINT64)Address + size)
            ){
                MemoryTracker[PartitionItems].Address = (UINT64)Address;
                MemoryTracker[PartitionItems].size = size;
                KernelLoaderInfo.RatPartition.PartitionItems++;
                memzero(Address, size);

                return true;
            }       
        }
    }


    return false;
}