#include <LouAPI.h>

uint64_t LouKeGetRamSize();

void* LouKeMallocPageEx(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres){
    if(((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)) || (!PhysicalAddres) || ((PageSize == KILOBYTE_PAGE) && (PageCount >= 512))){
        return 0x00;
    }
    void* Result = LouVMallocEx(PageSize * PageCount, PageSize);

    LouKeMapContinuousMemoryBlock(PhysicalAddres, (uint64_t)Result, (PageSize * PageCount) , PageFlags);

    return Result;
}

KERNEL_EXPORT
void* 
LouKeMallocPage(
    uint64_t PageSize, 
    uint64_t PageCount, 
    uint64_t PageFlags
){    
    if((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)){
        return 0x00;
    }
    void* Resurve = 0x00;
    LouKeVmmGetPPageReserveVm64(PageSize, PageCount, &Resurve);
    if(!Resurve){
        Resurve = LouAllocatePhysical64UpEx(PageSize * PageCount, PageSize);
        LouKeVmmCreatePageReserveVm(Resurve, PageSize, PageCount, true, false);
    }
    return LouKeMallocPageEx(PageSize, PageCount, PageFlags, (uint64_t)Resurve);
}

void* LouKeMallocPageExVirt32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres, BOOLEAN CreateDevSection){
    if(((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)) || (!PhysicalAddres) || ((PageSize == KILOBYTE_PAGE) && (PageCount >= 512))){
        return 0x00;
    }

    void* Result = 0x00;
    LouKeVmmGetVPageReserveVm32(PageSize, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical32UpEx(PageSize * PageCount, PageSize);
        LouKeVmmCreatePageReserveVm(Result, PageSize, PageCount, false, true);
    }

    if(CreateDevSection)LouKeCreateDeviceSection((PVOID)PhysicalAddres, Result, (PageSize * PageCount), LouPageFlagsToNtPageFlags(PageFlags, false, false));
    LouKeMapContinuousMemoryBlock(PhysicalAddres, (uint64_t)Result, (PageSize * PageCount) , PageFlags);
    return Result;
}

void* LouKeMallocPageVirt32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, BOOLEAN CreateDevSection){
    if((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)){
        return 0x00;
    }
    PVOID Result = 0x00;
    LouKeVmmGetPPageReserveVm(PageSize, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical64UpEx(PageSize * PageCount, PageSize);
        LouKeVmmCreatePageReserveVm(Result, PageSize, PageCount, true, false);
    }
    return LouKeMallocPageExVirt32(PageSize, PageCount, PageFlags, (UINT64)Result, CreateDevSection);
}

KERNEL_EXPORT
void* LouKeMallocPagePhy32(UINT64 PageSize, UINT64 PageCount, UINT64 PageFlags){
    PVOID Result = 0x00;
    LouKeVmmGetPPageReserveVm32(PageSize, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical32UpEx(PageSize * PageCount, PageSize);
        if((UINTPTR)Result > (4 * GIGABYTE)){
            LouFree(Result);
            return 0x00;
        }
        LouKeVmmCreatePageReserveVm(Result, PageSize, PageCount, true, false);
    }
    return LouKeMallocPageEx(PageSize, PageCount, PageFlags, (UINT64)Result);
}

//this is specifically for NON kernel 64 bit memory e.g. sections, heaps, stacks, ect...
KERNEL_EXPORT 
PVOID
LouKeMallocPageExVirt64(
    UINT64  PageSize,
    UINT64  PageCount,
    UINT64  PageFlags,
    UINT64  PhysicalAddres,
    BOOLEAN CreateDevSection
){ 
    if(((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)) || (!PhysicalAddres) || ((PageSize == KILOBYTE_PAGE) && (PageCount >= 512))){
        return 0x00;
    }
    void* Result = 0x00; 
    LouKeVmmGetVPageReserveVm64(PageSize, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical64UpEx(PageSize * PageCount, PageSize);
        LouKeVmmCreatePageReserveVm(Result, PageSize, PageCount, false, true);
    }

    if(CreateDevSection)LouKeCreateDeviceSection((PVOID)PhysicalAddres, Result, (PageSize * PageCount), LouPageFlagsToNtPageFlags(PageFlags, false, false));
    LouKeMapContinuousMemoryBlock(PhysicalAddres, (uint64_t)Result, (PageSize * PageCount) , PageFlags);
    return Result;
}

//this is specifically for NON kernel 64 bit memory e.g. sections, heaps, stacks, ect...
void* LouKeMallocPageVirt64(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, BOOLEAN CreateDevSection){
    if((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)){
        return 0x00;
    }
    PVOID Result = 0x00;
    LouKeVmmGetPPageReserveVm64(PageSize, PageCount, &Result); 
    if(!Result){
        Result = LouAllocatePhysical64UpEx(PageSize * PageCount, PageSize);
        LouKeVmmCreatePageReserveVm(Result, PageSize, PageCount, true, false);
    }
    return LouKeMallocPageExVirt64(PageSize, PageCount, PageFlags, (UINT64)Result, CreateDevSection);
}

uint64_t GetAllocationBlockSize(uint64_t Address);

static void LouKePutPage(PVOID Address){
    LouFree(Address);
}

KERNEL_EXPORT
void LouKeFreePage(void* PageAddress){
    uint64_t PhysicalAddres = 0;
    RequestPhysicalAddress((uint64_t)PageAddress, &PhysicalAddres);

    LouKeVmmPutPPageReserveAddressVm((PVOID)PhysicalAddres, LouKePutPage);
    LouKeVmmPutVPageReserveAddressVm(PageAddress, LouKePutPage);
}
