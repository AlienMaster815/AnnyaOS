#include <LouAPI.h>

uint64_t LouKeGetRamSize();

KERNEL_EXPORT
PVOID LouKeMallocKbPageEx(
    SIZE    PageCount, 
    UINT64  PageFlags, 
    UINT64  PhysicalAddres
){  
    if(!PhysicalAddres || !PageCount){
        return 0x00;
    }
    PVOID Result = LouVMallocEx(KILOBYTE_PAGE * PageCount, KILOBYTE_PAGE);
    if(!Result){
        return 0x00;
    }
    LouKeMapContinuousMemoryBlockKB(PhysicalAddres, (UINT64)Result, (KILOBYTE_PAGE * PageCount), PageFlags);
    return Result;
}

KERNEL_EXPORT
PVOID LouKeMallocMbPageEx(
    SIZE    PageCount,
    UINT64  PageFlags,
    UINT64  PhysicalAddres
){
    if(!PhysicalAddres || !PageCount){
        return 0x00;
    }
    PVOID Result = LouVMallocEx(MEGABYTE_PAGE * PageCount, MEGABYTE_PAGE);
    if(!Result){
        return 0x00;
    }
    LouKeMapContinuousMemoryBlockMb(PhysicalAddres, (UINT64)Result, (MEGABYTE_PAGE * PageCount), PageFlags);
    return Result;
}

KERNEL_EXPORT
PVOID
LouKeMallocKbPage( 
    UINT64 PageCount, 
    UINT64 PageFlags
){    
    if(!PageCount){
        return 0x00;
    }
    void* Resurve = 0x00;
    LouKeVmmGetPPageReserveVm64(KILOBYTE_PAGE, PageCount, &Resurve);
    if(!Resurve){
        Resurve = LouAllocatePhysical64UpEx(KILOBYTE_PAGE * PageCount, KILOBYTE_PAGE);
        LouKeVmmCreatePageReserveVm(Resurve, KILOBYTE_PAGE, PageCount, true, false);
    }
    return LouKeMallocKbPageEx(PageCount, PageFlags, (uint64_t)Resurve);
}

KERNEL_EXPORT
PVOID
LouKeMallocMbPage( 
    UINT64 PageCount, 
    UINT64 PageFlags
){    
    if(!PageCount){
        return 0x00;
    }
    PVOID Resurve = 0x00;
    LouKeVmmGetPPageReserveVm64(MEGABYTE_PAGE, PageCount, &Resurve);
    if(!Resurve){
        Resurve = LouAllocatePhysical64UpEx(MEGABYTE_PAGE * PageCount, MEGABYTE_PAGE);
        LouKeVmmCreatePageReserveVm(Resurve, MEGABYTE_PAGE, PageCount, true, false);
    }
    return LouKeMallocMbPageEx(PageCount, PageFlags, (UINT64)Resurve);
}

KERNEL_EXPORT
PVOID LouKeMallocKbPageExVirt32(UINT64 PageCount, UINT64 PageFlags, UINT64 PhysicalAddres, BOOLEAN CreateDevSection){
    if((!PageCount) || (!PhysicalAddres)){
        return 0x00;
    }

    void* Result = 0x00;
    LouKeVmmGetVPageReserveVm32(KILOBYTE_PAGE, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical32UpEx(KILOBYTE_PAGE * PageCount, KILOBYTE_PAGE);
        LouKeVmmCreatePageReserveVm(Result, KILOBYTE_PAGE, PageCount, false, true);
    }

    if(CreateDevSection)LouKeCreateDeviceSection((PVOID)PhysicalAddres, Result, (KILOBYTE_PAGE * PageCount), LouPageFlagsToNtPageFlags(PageFlags, false, false));
    LouKeMapContinuousMemoryBlockKB(PhysicalAddres, (uint64_t)Result, (KILOBYTE_PAGE * PageCount) , PageFlags);
    return Result;
}

KERNEL_EXPORT
PVOID LouKeMallocMbPageExVirt32(UINT64 PageCount, UINT64 PageFlags, UINT64 PhysicalAddres, BOOLEAN CreateDevSection){
    if((!PageCount) || (!PhysicalAddres)){
        return 0x00;
    }

    void* Result = 0x00;
    LouKeVmmGetVPageReserveVm32(MEGABYTE_PAGE, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical32UpEx(MEGABYTE_PAGE * PageCount, MEGABYTE_PAGE);
        LouKeVmmCreatePageReserveVm(Result, MEGABYTE_PAGE, PageCount, false, true);
    }

    if(CreateDevSection)LouKeCreateDeviceSection((PVOID)PhysicalAddres, Result, (MEGABYTE_PAGE * PageCount), LouPageFlagsToNtPageFlags(PageFlags, false, false));
    LouKeMapContinuousMemoryBlockMb(PhysicalAddres, (uint64_t)Result, (MEGABYTE_PAGE * PageCount) , PageFlags);
    return Result;
}

KERNEL_EXPORT
PVOID LouKeMallocKbPageVirt32(UINT64 PageCount, UINT64 PageFlags, BOOLEAN CreateDevSection){
    if(!PageCount){
        return 0x00;
    }
    PVOID Result = 0x00;
    LouKeVmmGetPPageReserveVm(KILOBYTE_PAGE, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical64UpEx(KILOBYTE_PAGE * PageCount, KILOBYTE_PAGE);
        LouKeVmmCreatePageReserveVm(Result, KILOBYTE_PAGE, PageCount, true, false);
    }
    return LouKeMallocKbPageExVirt32(PageCount, PageFlags, (UINT64)Result, CreateDevSection);
}

KERNEL_EXPORT
PVOID LouKeMallocMbPageVirt32(UINT64 PageCount, UINT64 PageFlags, BOOLEAN CreateDevSection){
    if(!PageCount){
        return 0x00;
    }
    PVOID Result = 0x00;
    LouKeVmmGetPPageReserveVm(MEGABYTE_PAGE, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical64UpEx(MEGABYTE_PAGE * PageCount, MEGABYTE_PAGE);
        LouKeVmmCreatePageReserveVm(Result, MEGABYTE_PAGE, PageCount, true, false);
    }
    return LouKeMallocMbPageExVirt32(PageCount, PageFlags, (UINT64)Result, CreateDevSection);
}

KERNEL_EXPORT
PVOID LouKeMallocKbPagePhy32(UINT64 PageCount, UINT64 PageFlags){
    PVOID Result = 0x00;
    LouKeVmmGetPPageReserveVm32(KILOBYTE_PAGE, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical32UpEx(KILOBYTE_PAGE * PageCount, KILOBYTE_PAGE);
        if((UINTPTR)Result > (4 * GIGABYTE)){
            LouFree(Result);
            return 0x00;
        }
        LouKeVmmCreatePageReserveVm(Result, KILOBYTE_PAGE, PageCount, true, false);
    }
    return LouKeMallocKbPageEx(PageCount, PageFlags, (UINT64)Result);
}

KERNEL_EXPORT
PVOID LouKeMallocMbPagePhy32(UINT64 PageCount, UINT64 PageFlags){
    PVOID Result = 0x00;
    LouKeVmmGetPPageReserveVm32(MEGABYTE_PAGE, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical32UpEx(MEGABYTE_PAGE * PageCount, MEGABYTE_PAGE);
        if((UINTPTR)Result > (4 * GIGABYTE)){
            LouFree(Result);
            return 0x00;
        }
        LouKeVmmCreatePageReserveVm(Result, MEGABYTE_PAGE, PageCount, true, false);
    }
    return LouKeMallocMbPageEx(PageCount, PageFlags, (UINT64)Result);
}

KERNEL_EXPORT 
PVOID
LouKeMallocKbPageExVirt64(
    UINT64  PageCount,
    UINT64  PageFlags,
    UINT64  PhysicalAddres,
    BOOLEAN CreateDevSection
){ 
    if((!PageCount) || (!PhysicalAddres)){
        return 0x00;
    }
    void* Result = 0x00; 
    LouKeVmmGetVPageReserveVm64(KILOBYTE_PAGE, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical64UpEx(KILOBYTE_PAGE * PageCount, KILOBYTE_PAGE);
        LouKeVmmCreatePageReserveVm(Result, KILOBYTE_PAGE, PageCount, false, true);
    }

    if(CreateDevSection)LouKeCreateDeviceSection((PVOID)PhysicalAddres, Result, (KILOBYTE_PAGE * PageCount), LouPageFlagsToNtPageFlags(PageFlags, false, false));
    LouKeMapContinuousMemoryBlockKB(PhysicalAddres, (uint64_t)Result, (KILOBYTE_PAGE * PageCount) , PageFlags);
    return Result;
}

KERNEL_EXPORT 
PVOID
LouKeMallocMbPageExVirt64(
    UINT64  PageCount,
    UINT64  PageFlags,
    UINT64  PhysicalAddres,
    BOOLEAN CreateDevSection
){ 
    if((!PageCount) || (!PhysicalAddres)){
        return 0x00;
    }
    void* Result = 0x00; 
    LouKeVmmGetVPageReserveVm64(MEGABYTE_PAGE, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical64UpEx(MEGABYTE_PAGE * PageCount, MEGABYTE_PAGE);
        LouKeVmmCreatePageReserveVm(Result, MEGABYTE_PAGE, PageCount, false, true);
    }

    if(CreateDevSection)LouKeCreateDeviceSection((PVOID)PhysicalAddres, Result, (MEGABYTE_PAGE * PageCount), LouPageFlagsToNtPageFlags(PageFlags, false, false));
    LouKeMapContinuousMemoryBlockMb(PhysicalAddres, (uint64_t)Result, (MEGABYTE_PAGE * PageCount) , PageFlags);
    return Result;
}

void* LouKeMallocKbPageVirt64(uint64_t PageCount, uint64_t PageFlags, BOOLEAN CreateDevSection){
    if(!PageCount){
        return 0x00;
    }
    PVOID Result = 0x00;
    LouKeVmmGetPPageReserveVm64(KILOBYTE_PAGE, PageCount, &Result); 
    if(!Result){
        Result = LouAllocatePhysical64UpEx(KILOBYTE_PAGE * PageCount, KILOBYTE_PAGE);
        LouKeVmmCreatePageReserveVm(Result, KILOBYTE_PAGE, PageCount, true, false);
    }
    return LouKeMallocKbPageExVirt64(PageCount, PageFlags, (UINT64)Result, CreateDevSection);
}

void* LouKeMallocMbPageVirt64(uint64_t PageCount, uint64_t PageFlags, BOOLEAN CreateDevSection){
    if(!PageCount){
        return 0x00;
    }
    PVOID Result = 0x00;
    LouKeVmmGetPPageReserveVm64(MEGABYTE_PAGE, PageCount, &Result); 
    if(!Result){
        Result = LouAllocatePhysical64UpEx(MEGABYTE_PAGE * PageCount, MEGABYTE_PAGE);
        LouKeVmmCreatePageReserveVm(Result, MEGABYTE_PAGE, PageCount, true, false);
    }
    return LouKeMallocKbPageExVirt64(PageCount, PageFlags, (UINT64)Result, CreateDevSection);
}


//TODO:Update Functions To Use New Paging System 
void* LouKeMallocPageEx(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres){
    if((PageSize != KILOBYTE_PAGE) || (!PhysicalAddres)){
        return 0x00;
    }
    void* Result = LouVMallocEx(PageSize * PageCount, PageSize);

    LouKeMapContinuousMemoryBlockKB(PhysicalAddres, (uint64_t)Result, (PageSize * PageCount) , PageFlags);

    return Result;
}

KERNEL_EXPORT
void* 
LouKeMallocPage(
    uint64_t PageSize, 
    uint64_t PageCount, 
    uint64_t PageFlags
){    
    if(PageSize != KILOBYTE_PAGE){
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
    if((PageSize != KILOBYTE_PAGE) || (!PhysicalAddres)){
        return 0x00;
    }

    void* Result = 0x00;
    LouKeVmmGetVPageReserveVm32(PageSize, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical32UpEx(PageSize * PageCount, PageSize);
        LouKeVmmCreatePageReserveVm(Result, PageSize, PageCount, false, true);
    }

    if(CreateDevSection)LouKeCreateDeviceSection((PVOID)PhysicalAddres, Result, (PageSize * PageCount), LouPageFlagsToNtPageFlags(PageFlags, false, false));
    LouKeMapContinuousMemoryBlockKB(PhysicalAddres, (uint64_t)Result, (PageSize * PageCount) , PageFlags);
    return Result;
}

void* LouKeMallocPageVirt32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, BOOLEAN CreateDevSection){
    if(PageSize != KILOBYTE_PAGE){
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
    if((PageSize != KILOBYTE_PAGE) || (!PhysicalAddres)){
        return 0x00;
    }
    void* Result = 0x00; 
    LouKeVmmGetVPageReserveVm64(PageSize, PageCount, &Result);
    if(!Result){
        Result = LouAllocatePhysical64UpEx(PageSize * PageCount, PageSize);
        LouKeVmmCreatePageReserveVm(Result, PageSize, PageCount, false, true);
    }

    if(CreateDevSection)LouKeCreateDeviceSection((PVOID)PhysicalAddres, Result, (PageSize * PageCount), LouPageFlagsToNtPageFlags(PageFlags, false, false));
    LouKeMapContinuousMemoryBlockKB(PhysicalAddres, (uint64_t)Result, (PageSize * PageCount) , PageFlags);
    return Result;
}

//this is specifically for NON kernel 64 bit memory e.g. sections, heaps, stacks, ect...
void* LouKeMallocPageVirt64(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, BOOLEAN CreateDevSection){
    if(PageSize != KILOBYTE_PAGE){
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
