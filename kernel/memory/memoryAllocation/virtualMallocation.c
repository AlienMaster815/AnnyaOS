#include <LouAPI.h>

void* LouVMallocEx(size_t BytesToAllocate, uint64_t Alignment);
void* LouVMalloc(size_t BytesToAllocate);

typedef struct _AllocationBlock{
    uint64_t VAddress;
    uint64_t PAddress;
    uint64_t size;
}VAllocationBlock;

static uint8_t IOSlab[9 * MEGABYTE];

static VAllocationBlock* IOBlock = (VAllocationBlock*)&IOSlab;

static uint32_t VAllocations = 0x00;

uint64_t LouKeVMemmorySearchPhysicalSpace(
    uint64_t VAddress
){
    for(uint32_t i = 0 ; i < VAllocations; i++){
        if(IOBlock[i].VAddress == VAddress){
            return IOBlock[i].PAddress;
        }
    }
    return 0x00;
}

uint64_t LouKeVMemmorySearchVirtualSpace(
    uint64_t PAddress
){
    for(uint32_t i = 0 ; i < VAllocations; i++){
        if(IOBlock[i].PAddress == PAddress){
            return IOBlock[i].VAddress;
        }
    }
    return 0x00;
}

uint64_t LouKeVMemmoryGetSize(uint64_t VAddress){
    for(uint32_t i = 0 ; i < VAllocations; i++){
        if(IOBlock[i].VAddress == VAddress){
            return IOBlock[i].size;
        }
    }
    return 0x00;
}

void LouKeMapContinuousMemoryBlock(
    uint64_t PAddress, 
    uint64_t VAddress,
    uint64_t size, 
    uint64_t FLAGS
    ){
    uint64_t i = 0;

    while(i < size){
        if(((PAddress + i) == ((PAddress + i) & ~(MEGABYTE_PAGE-1))) && ((i + MEGABYTE_PAGE) <= size)){
            LouMapAddress(PAddress + i, VAddress + i, FLAGS, MEGABYTE_PAGE);
            i += MEGABYTE_PAGE;
        }
        else{
            LouMapAddress(PAddress + i, VAddress + i, FLAGS, KILOBYTE_PAGE);
            i += KILOBYTE_PAGE;
        }
        //LouPrint("I:%h : Size:%h\n",i, size);
    }
}


void LouKeUnMapContinuousMemoryBlock(
    uint64_t VAddress,
    uint64_t size
){
    uint64_t i = 0;
    uint64_t Count = 0;
    while(i < size){
        LouUnMapAddress(VAddress + i, 0x00, &Count, 0x00);
        i += Count;
        Count = 0;
    }
}

//allocates Virtual Page 

void LouKeMallocVMmIO(
    uint64_t PAddress,
    uint64_t size,
    uint64_t FLAGS
){

    uint64_t VAddress = (uint64_t)LouVMalloc(size);

    LouKeMapContinuousMemoryBlock(
        PAddress,
        VAddress,
        size,
        FLAGS
    );

    if(VAllocations == 0){
        IOBlock[0].VAddress = VAddress;
        IOBlock[0].PAddress = PAddress;
        IOBlock[0].size = size;
        VAllocations++;
        return;// (void*)VAddress;
    }

    for(uint64_t i = 0; i < VAllocations; i++){
        if(IOBlock[i].VAddress == 0x00){
            IOBlock[i].VAddress = VAddress;
            IOBlock[i].PAddress = PAddress;
            IOBlock[i].size = size;
            return;// (void*)VAddress;
        }
    }

    IOBlock[VAllocations].VAddress = VAddress;
    IOBlock[VAllocations].PAddress = PAddress;
    IOBlock[VAllocations].size = size;
    VAllocations++;

    return;// (void*)VAddress;
}


void* LouKeAllocateUncachedVMemoryEx(
    uint64_t NumberOfBytes,
    uint64_t Alignment
){
    void* AllocatedPMemory = LouMallocEx(sizeof(NumberOfBytes), Alignment);
    void* AllocatedVMemory = LouVMallocEx(sizeof(NumberOfBytes), Alignment);

    LouKeMapContinuousMemoryBlock((uint64_t)AllocatedPMemory, (uint64_t)AllocatedVMemory, NumberOfBytes, KERNEL_PAGE_WRITE_PRESENT | CACHE_DISABLED_PAGE);

    return AllocatedVMemory;
}

void* LouKeAllocateUncachedVMemory(
    uint64_t NumberOfBytes
){
    return LouKeAllocateUncachedVMemoryEx(NumberOfBytes, NumberOfBytes);
}