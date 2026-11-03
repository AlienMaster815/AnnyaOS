#include <LouAPI.h>

uint64_t LouKeGetRamSize();

typedef struct _PAGE_FRAME_FAST_ALLOCATION_TRACKER{
    ListHeader  Peers;
    UINT64      Map;
    UINT64      Address;
    UINT8       Allocations : 7;
    UINT8       Full        : 1;
}PAGE_FRAME_FAST_ALLOCATION_TRACKER, * PPAGE_FRAME_FAST_ALLOCATION_TRACKER;

static ListHeader KbPageFrameTrackerList = {0};
static mutex_t KbPageFrameTrackerListLock = {0};

static PPAGE_FRAME_FAST_ALLOCATION_TRACKER LouKeMallocPageFrameTracker(
    SIZE        PageSize,
    PListHeader TrackerList
){
    PPAGE_FRAME_FAST_ALLOCATION_TRACKER NewTracker = LouGeneralAllocateMemoryEx(sizeof(PAGE_FRAME_FAST_ALLOCATION_TRACKER), GET_ALIGNMENT(PAGE_FRAME_FAST_ALLOCATION_TRACKER));
    NewTracker->Address = (UINT64)(UINT8*)LouKeRatAllocate64BitPhysicalAddress(PageSize * 64, PageSize);
    LouKeListAddTail(&NewTracker->Peers, TrackerList);
    return NewTracker;
}

static void LouKeFreePageFrameTracker(PPAGE_FRAME_FAST_ALLOCATION_TRACKER Tracker){
    LouKeListDeleteItem(&Tracker->Peers);
    LouKeRatFreeAddress(Tracker->Address);
    LouGeneralFreeMemory(Tracker);
}

static void LouKeFreePageFrameItem(SIZE PageFrameSize, SIZE FrameAddress, UINT64* Item, PVOID Address){
    SIZE szAddress = (SIZE)(UINT8*)Address;
    SIZE i = (szAddress - FrameAddress) / PageFrameSize;
    *Item = ((*Item) & ~(1 << i));
}

static PVOID LouKeMallocPageFrameItem(SIZE PageFrameSize, SIZE FrameAddress, UINT64* Item){
    SIZE AddressMap = *Item;
    SIZE i;
    PVOID Result;
    for(i = 0 ; i < 64; i++){
        if(!(AddressMap & (1 << i))){
            break;
        }
    }
    if(i >= 64){
        return 0x00;
    }
    *Item = ((*Item) | (1 << i));
    Result = (PVOID)(UINT8*)(FrameAddress + (i * PageFrameSize));
    memset(Result, 0, PageFrameSize);
    return Result;
}

PVOID LouKeMallocKbPageFrame(){
    PVOID Result = 0x00;
    MutexLock(&KbPageFrameTrackerListLock);
    PPAGE_FRAME_FAST_ALLOCATION_TRACKER Tracker;
    ForEachListEntry(Tracker, &KbPageFrameTrackerList, Peers){        
        if(Tracker->Full){
            continue;
        }
        Result = LouKeMallocPageFrameItem(
            KILOBYTE_PAGE,
            Tracker->Address,
            &Tracker->Map
        );
        if(Result){
            Tracker->Allocations++;
            goto _DONE;
        }
        Tracker->Full = 1;
    }
    if(!Result){
        Tracker = LouKeMallocPageFrameTracker(
            KILOBYTE_PAGE, 
            &KbPageFrameTrackerList
        );
        if(!Tracker){
            goto _DONE;
        }
        Result = LouKeMallocPageFrameItem(
            KILOBYTE_PAGE,
            Tracker->Address,
            &Tracker->Map
        );
        if(!Result){
            goto _DONE;
        }
        Tracker->Allocations++;
    }
_DONE:
    MutexUnlock(&KbPageFrameTrackerListLock);
    return (PVOID)(UINT8*)(((UINT64)(UINT8*)Result) + KSpaceBase); 
}

void LouKeFreeKbPageFrame(PVOID Address){
    Address = (PVOID)(UINT8*)(((UINT64)(UINT8*)Address) - KSpaceBase);
    MutexLock(&KbPageFrameTrackerListLock);
    PPAGE_FRAME_FAST_ALLOCATION_TRACKER Tracker;
    ForEachListEntry(Tracker, &KbPageFrameTrackerList, Peers){
        if(!RangeInterferes((UINT64)Address, 1, Tracker->Address, 64 * KILOBYTE_PAGE)){
            continue;
        }
        Tracker->Allocations--;
        if(Tracker->Allocations){
            LouKeFreePageFrameItem(
                KILOBYTE_PAGE,
                Tracker->Address,
                &Tracker->Map,
                Address
            );
            Tracker->Full = 0;
            break;
        } 
        LouKeFreePageFrameTracker(Tracker);
        break;
    }
    MutexUnlock(&KbPageFrameTrackerListLock);
}

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
    LouKeMapContinuousMemoryBlockMb(PhysicalAddres, (UINT64)Result, (KILOBYTE_PAGE * PageCount), PageFlags);
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
    LouKeMapContinuousMemoryBlockMb(PhysicalAddres, (uint64_t)Result, (KILOBYTE_PAGE * PageCount) , PageFlags);
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
    LouKeMapContinuousMemoryBlockMb(PhysicalAddres, (uint64_t)Result, (KILOBYTE_PAGE * PageCount) , PageFlags);
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
    return LouKeMallocMbPageExVirt64(PageCount, PageFlags, (UINT64)Result, CreateDevSection);
}


void* LouKeMallocPageEx(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres){
    if(PageSize == MEGABYTE_PAGE){
        return LouKeMallocMbPageEx(PageCount, PageFlags, PhysicalAddres);
    }else if((PageSize == KILOBYTE_PAGE) && (ROUND_UP64(PageCount, 512) == PageCount)){//if the kilobyte page is a multiple of 512 it can be mapped as a megabyte
        return LouKeMallocMbPageEx(PageCount / 512, PageFlags, PhysicalAddres);
    }
    return LouKeMallocKbPageEx(PageCount, PageFlags, PhysicalAddres);
}

KERNEL_EXPORT
void* 
LouKeMallocPage(
    uint64_t PageSize, 
    uint64_t PageCount, 
    uint64_t PageFlags
){    
    if(PageSize == MEGABYTE_PAGE){
        return LouKeMallocMbPage(PageCount, PageFlags);
    }
    else if((PageSize == KILOBYTE_PAGE) && (ROUND_UP64(PageCount, 512) == PageCount)){//if the kilobyte page is a multiple of 512 it can be mapped as a megabyte
        return LouKeMallocMbPage(PageCount / 512, PageFlags);
    }
    return LouKeMallocKbPage(PageCount, PageFlags);
}

void* LouKeMallocPageExVirt32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres, BOOLEAN CreateDevSection){
    if(PageSize == MEGABYTE_PAGE){
        return LouKeMallocMbPageExVirt32(PageCount, PageFlags, PhysicalAddres, CreateDevSection);
    }
    else if((PageSize == KILOBYTE_PAGE) && (ROUND_UP64(PageCount, 512) == PageCount)){ //if the kilobyte page is a multiple of 512 it can be mapped as a megabyte
        return LouKeMallocMbPageExVirt32(PageCount / 512, PageFlags, PhysicalAddres, CreateDevSection);
    }
    return LouKeMallocKbPageExVirt32(PageCount, PageFlags, PhysicalAddres, CreateDevSection);
}

void* LouKeMallocPageVirt32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, BOOLEAN CreateDevSection){
    if(PageSize == MEGABYTE_PAGE){
        return LouKeMallocMbPageVirt32(PageCount, PageFlags, CreateDevSection);
    }
    else if((PageSize == KILOBYTE_PAGE) && (ROUND_UP64(PageCount, 512) == PageCount)){ //if the kilobyte page is a multiple of 512 it can be mapped as a megabyte
        return LouKeMallocMbPageVirt32(PageCount / 512, PageFlags, CreateDevSection);
    }
    return LouKeMallocKbPageVirt32(PageCount, PageFlags, CreateDevSection);
}

KERNEL_EXPORT
void* LouKeMallocPagePhy32(UINT64 PageSize, UINT64 PageCount, UINT64 PageFlags){
    if(PageSize == MEGABYTE_PAGE){
        return LouKeMallocMbPagePhy32(PageCount, PageFlags);
    }
    else if((PageSize == KILOBYTE_PAGE) && (ROUND_UP64(PageCount, 512) == PageCount)){ //if the kilobyte page is a multiple of 512 it can be mapped as a megabyte
        return LouKeMallocMbPagePhy32(PageCount / 512, PageFlags);
    }
    return LouKeMallocKbPagePhy32(PageCount, PageFlags);
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
    if(PageSize == MEGABYTE_PAGE){
        return LouKeMallocMbPageExVirt64(PageCount, PageFlags, PhysicalAddres, CreateDevSection);
    }
    else if((PageSize == KILOBYTE_PAGE) && (ROUND_UP64(PageCount, 512) == PageCount)){ //if the kilobyte page is a multiple of 512 it can be mapped as a megabyte
        return LouKeMallocMbPageExVirt64(PageCount / 512, PageFlags, PhysicalAddres, CreateDevSection);
    }
    return LouKeMallocKbPageExVirt64(PageCount, PageFlags, PhysicalAddres, CreateDevSection);
}

//this is specifically for NON kernel 64 bit memory e.g. sections, heaps, stacks, ect...
void* LouKeMallocPageVirt64(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, BOOLEAN CreateDevSection){
    if(PageSize == MEGABYTE_PAGE){
        return LouKeMallocMbPageVirt64(PageCount, PageFlags, CreateDevSection);
    }
    else if((PageSize == KILOBYTE_PAGE) && (ROUND_UP64(PageCount, 512) == PageCount)){ //if the kilobyte page is a multiple of 512 it can be mapped as a megabyte
        return LouKeMallocMbPageVirt64(PageCount / 512, PageFlags, CreateDevSection);
    }
    return LouKeMallocKbPageVirt64(PageCount, PageFlags, CreateDevSection);
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
