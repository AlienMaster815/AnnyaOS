#include <LouAPI.h>


void* LouKeMemReMap(void* PhyAddress, size_t Length, uint64_t Flags){
    EnforceSystemMemoryMap((uint64_t)PhyAddress, Length);
    uintptr_t AlignedAddress = ((uintptr_t)PhyAddress & ~(KILOBYTE_PAGE - 1));
    size_t Offset = (uintptr_t)PhyAddress - AlignedAddress;
    size_t TotalSize = ROUND_UP64(((size_t)Offset + (size_t)Length), KILOBYTE_PAGE);

    //LouPrint("PhysicalAddress:%h\n", PhyAddress);
    //LouPrint("AlignedAddress :%h\n", AlignedAddress);
    //LouPrint("Offset         :%h\n", Offset);
    //LouPrint("TotalSize      :%h\n", TotalSize);

    return (void*)((uintptr_t)LouKeMallocPageEx(
        KILOBYTE_PAGE, 
        TotalSize / KILOBYTE_PAGE, 
        KERNEL_DMA_MEMORY, 
        AlignedAddress) + Offset
    );
}

void LouKeMemReleaseReMap(void* Address){
    uint64_t PhyAddress = 0x00;
    uintptr_t AlignedAddress = ((uintptr_t)Address & ~(KILOBYTE_PAGE - 1));
    LouKeFreePage((void*)AlignedAddress);
    RequestPhysicalAddress((uint64_t)Address, &PhyAddress);
    LouFree((uint8_t*)PhyAddress);
}