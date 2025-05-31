#include <LouAPI.h>

void* LouKeMallocPageEx(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres){
    if(((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)) || (!PhysicalAddres) || ((PageSize == KILOBYTE_PAGE) && (PageCount >= 512))){
        return 0x00;
    }
    void* Result = LouVMallocEx(PageSize * PageCount, PageSize);
    LouKeMapContinuousMemoryBlock(PhysicalAddres, (uint64_t)Result, (PageSize * PageCount) , PageFlags);

    return Result;
}

void* LouKeMallocPage(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags){    
    
    if((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)){
        return 0x00;
    }

    return LouKeMallocPageEx(PageSize, PageCount, PageFlags, (uint64_t)LouMallocEx(PageSize * PageCount, PageSize));
}

void* LouKeMallocPageEx32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres){
    if(((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)) || ((PageSize == KILOBYTE_PAGE) && (PageCount >= 512))){
        return 0x00;
    }
    void* Result = (void*)LouMallocEx(PageSize * PageCount, PageSize);
    if((uint64_t)Result >= 0xFFFFFFFF){
        LouFree((RAMADD)Result);
        return 0x00;
    }

    if(PhysicalAddres){
        LouKeMapContinuousMemoryBlock(PhysicalAddres, (uint64_t)Result, (PageSize * PageCount) , PageFlags);
    }else{
        LouKeMapContinuousMemoryBlock((uint64_t)Result, (uint64_t)Result, (PageSize * PageCount) , PageFlags);
    }

    return Result;
}

void* LouKeMallocPage32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags){
    if((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)){
        return 0x00;
    }
    return LouKeMallocPageEx32(PageSize, PageCount, PageFlags, 0x00);
}

uint64_t GetAllocationBlockSize(uint64_t Address);

void LouKeFreePage(void* PageAddress){
    uint64_t PhysicalAddres = 0;
    RequestPhysicalAddress((uint64_t)PageAddress, &PhysicalAddres);
    
    uint64_t AllocationBlockSize = GetAllocationBlockSize((uint64_t)PageAddress);
    LouKeUnMapContinuousMemoryBlock(
        (uint64_t)PageAddress,
        AllocationBlockSize
    );
    if(PhysicalAddres != (uint64_t)PageAddress){
        LouFree((RAMADD)PhysicalAddres);
    }
    LouFree((RAMADD)PageAddress);
}