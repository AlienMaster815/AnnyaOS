#include <LouLoad.h>
#include <bootloader/grub/multiboot2.h>


LOULOAD_MEMORY_TRACKER MemoryTracker[512] = {0};

extern LOUSINE_LOADER_INFO KernelLoaderInfo;



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
            MemoryTracker[i].Address,
            MemoryTracker[i].size,
            Address,
            size
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

    //struct master_multiboot_mmap_entry* mmap = (struct master_multiboot_mmap_entry*)MBOOT;


}