#include <LouAPI.h>

typedef struct _VADDRESS_RESERVE_POOL_TRACKER{
    ListHeader  Peers;
    bool        AddressUsed;
    UINT64      VAddress;
    UINT64      PAddress;
    UINT64      PageSize;
    UINT64      PageCount;
}VADDRESS_RESERVE_POOL_TRACKER, * PVADDRESS_RESERVE_POOL_TRACKER;

static VADDRESS_RESERVE_POOL_TRACKER VaPoolTracker = {0};
static mutex_t VaPoolMutex = {0};

uint64_t GetRamSize();

UNUSED static void LouKeRegisterPAddressToReserveVAddresses(
    UINT64 PAddress,
    UINT64 PageSize,
    UINT64 PageCount
){
    PVADDRESS_RESERVE_POOL_TRACKER TmpTracker = &VaPoolTracker;
    MutexLock(&VaPoolMutex);
    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PVADDRESS_RESERVE_POOL_TRACKER)TmpTracker->Peers.NextHeader;
    }

    TmpTracker->Peers.NextHeader = (PListHeader)LouGeneralAllocateMemoryEx(sizeof(VADDRESS_RESERVE_POOL_TRACKER), GET_ALIGNMENT(VADDRESS_RESERVE_POOL_TRACKER));
    TmpTracker->PAddress = PAddress; 
    TmpTracker->VAddress = (UINT64)LouVMallocEx(PageSize * PageCount, PageSize);
    TmpTracker->PageSize = PageSize;
    TmpTracker->PageCount = PageCount;

    LouKeMapContinuousMemoryBlock(PAddress, TmpTracker->VAddress, (PageSize * PageCount), KERNEL_GENERIC_MEMORY);

    MutexUnlock(&VaPoolMutex);
}

static void* LouKeGetFreeReservePage(
    UINT64 PageSize,
    UINT64 PageCount
){
    PVADDRESS_RESERVE_POOL_TRACKER TmpTracker = &VaPoolTracker;
    void* Result = 0x00;
    MutexLock(&VaPoolMutex);
    while(TmpTracker->Peers.NextHeader){
        if((TmpTracker->PageCount == PageCount) && (TmpTracker->PageSize == PageSize)){
            Result = (void*)TmpTracker->VAddress;
            TmpTracker->AddressUsed = true;
            break; 
        }
        TmpTracker = (PVADDRESS_RESERVE_POOL_TRACKER)TmpTracker->Peers.NextHeader;
    }
    MutexUnlock(&VaPoolMutex);
    return Result;
}

static bool IsAddressBeingUsed(UINT64 Address){
    PVADDRESS_RESERVE_POOL_TRACKER TmpTracker = &VaPoolTracker;
    bool Result = false;
    MutexLock(&VaPoolMutex);
    while(TmpTracker->Peers.NextHeader){

        if(TmpTracker->VAddress == Address){
            Result = TmpTracker->AddressUsed;
            break;             
        }
        TmpTracker = (PVADDRESS_RESERVE_POOL_TRACKER)TmpTracker->Peers.NextHeader;
    }
    MutexUnlock(&VaPoolMutex);
    return Result;
}

static void RemoveAddressFromReservePool(UINT64 Address){
    PVADDRESS_RESERVE_POOL_TRACKER TmpTracker = &VaPoolTracker;
    PVADDRESS_RESERVE_POOL_TRACKER Follower = &VaPoolTracker;

    MutexLock(&VaPoolMutex);
    while(TmpTracker->Peers.NextHeader){

        if(TmpTracker->PAddress == Address){
            if(Follower == TmpTracker){
                LouFree((RAMADD)TmpTracker->PAddress);
                LouFree((RAMADD)TmpTracker->VAddress);
                TmpTracker->PageCount = 0;
                TmpTracker->PageSize = 0;
                TmpTracker->VAddress = 0x00;
                TmpTracker->PAddress = 0x00;
                break;
            }else{
                LouFree((RAMADD)TmpTracker->PAddress);
                LouFree((RAMADD)TmpTracker->VAddress);
                Follower->Peers.NextHeader = TmpTracker->Peers.NextHeader;
                LouFree((RAMADD)TmpTracker);
                break;
            }
        }
        Follower = TmpTracker;
        TmpTracker = (PVADDRESS_RESERVE_POOL_TRACKER)TmpTracker->Peers.NextHeader;
    }
    MutexUnlock(&VaPoolMutex);
}

static bool IsAddressRemaped(UINT64 Address){
    PVADDRESS_RESERVE_POOL_TRACKER TmpTracker = &VaPoolTracker;
    bool Result = false;
    MutexLock(&VaPoolMutex);
    while(TmpTracker->Peers.NextHeader){

        if(TmpTracker->PAddress == Address){
            Result = true;
            break;             
        }
        TmpTracker = (PVADDRESS_RESERVE_POOL_TRACKER)TmpTracker->Peers.NextHeader;
    }
    MutexUnlock(&VaPoolMutex);
    return Result;
}


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
    void* Resurve = LouKeGetFreeReservePage(PageSize, PageCount);
    if(Resurve){
        return Resurve;
    }
    return LouKeMallocPageEx(PageSize, PageCount, PageFlags, (uint64_t)LouAllocatePhysical64UpEx(PageSize * PageCount, PageSize));
}

void* LouKeMallocPageExVirt32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres){
    if(((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)) || (!PhysicalAddres) || ((PageSize == KILOBYTE_PAGE) && (PageCount >= 512))){
        return 0x00;
    }
    void* Result = LouAllocatePhysical32UpEx(PageSize * PageCount, PageSize);

    LouKeRegisterPAddressToReserveVAddresses((UINT64)Result, PageSize, PageCount);

    LouKeMapContinuousMemoryBlock(PhysicalAddres, (uint64_t)Result, (PageSize * PageCount) , PageFlags);

    return Result;
}

void* LouKeMallocPageVirt32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags){
    if((PageSize != KILOBYTE_PAGE) && (PageSize != MEGABYTE_PAGE)){
        return 0x00;
    }

    return LouKeMallocPageExVirt32(PageSize, PageCount, PageFlags, (uint64_t)LouAllocatePhysical64UpEx(PageSize * PageCount, PageSize));
}


void* LouKeMallocPagePhy32(UINT64 PageSize, UINT64 PageCount, UINT64 PageFlags){
    return LouKeMallocPageEx(PageSize, PageCount, PageFlags, (UINT64)LouAllocatePhysical32UpEx(PageSize * PageCount, PageSize));
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
    LouKeMapContinuousMemoryBlock(PhysicalAddres, PhysicalAddres, AllocationBlockSize, KERNEL_GENERIC_MEMORY);
    if(PhysicalAddres != (uint64_t)PageAddress){
        LouFree((RAMADD)PhysicalAddres);
    }
    
    if(IsAddressRemaped((UINT64)PageAddress)){
        RemoveAddressFromReservePool((UINT64)PageAddress);
    }
    else if(!IsAddressBeingUsed((UINT64)PageAddress)){
        LouFree((RAMADD)PageAddress);
    }
}