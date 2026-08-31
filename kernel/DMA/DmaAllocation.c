#include <LouAPI.h>

typedef struct _DMA_ALLOCATION_LIST_ENTRY{
    ListHeader  Peers;
    POOL        Pool;
}DMA_ALLOCATION_LIST_ENTRY, * PDMA_ALLOCATION_LIST_ENTRY;

typedef struct _DMA_THRESHOLD_MANAGER{
    mutex_t     LockOutTagOut;    
    ListHeader  Entries;  
}DMA_THRESHOLD_MANAGER, * PDMA_THRESHOLD_MANAGER;

typedef struct _DMA_LIMIT_MANAGER{

    XARRAY DmaThresholdTree;
}DMA_LIMIT_MANAGER, * PDMA_LIMIT_MANAGER;

UNUSED static XARRAY DmaLimitTree = {0};

static LOUSTATUS CreateDmaLimitManager(
    PXARRAY Array, 
    UINT64  Index, 
    PVOID   Context
){
    PDMA_LIMIT_MANAGER NewHead;
    UINT64* Out;
    if(!Context){
        return STATUS_INVALID_PARAMETER;
    }
    NewHead = LouKeMallocType(DMA_LIMIT_MANAGER, KERNEL_GENERIC_MEMORY);
    if(!NewHead){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    LouKeXaStoreEx(Array, Index, (PVOID)NewHead, KERNEL_GENERIC_MEMORY);
    Out = (UINT64*)Context; 
    *Out = (UINT64)(UINTPTR)(UINT8*)NewHead; 
    return STATUS_SUCCESS;
}

static LOUSTATUS CreateThresholdManager(
    PXARRAY Array, 
    UINT64  Index, 
    PVOID   Context
){
    PDMA_THRESHOLD_MANAGER NewHead;
    UINT64* Out;
    if(!Context){
        return STATUS_INVALID_PARAMETER;
    }
    NewHead = LouKeMallocType(DMA_THRESHOLD_MANAGER, KERNEL_GENERIC_MEMORY);
    if(!NewHead){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    LouKeXaStoreEx(Array, Index, (PVOID)NewHead, KERNEL_GENERIC_MEMORY);
    Out = (UINT64*)Context; 
    *Out = (UINT64)(UINTPTR)(UINT8*)NewHead; 
    return STATUS_SUCCESS;
}

UNUSED static PDMA_LIMIT_MANAGER GetLimitManager(ULONG DmaLimit){
    UINT64 LimitData;
    if(LouKeXaGetOrDoSomthing(&DmaLimitTree, DmaLimit, &LimitData, CreateDmaLimitManager, &LimitData) != STATUS_SUCCESS){
        return 0x00;
    }
    return (PDMA_LIMIT_MANAGER)(UINT8*)LimitData;
}

UNUSED static PDMA_THRESHOLD_MANAGER GetThresholdManager(PDMA_LIMIT_MANAGER LimitManager, ULONG Threshold){
    UINT64 ThreshData;
    if(LouKeXaGetOrDoSomthing(&LimitManager->DmaThresholdTree, Threshold, &ThreshData, CreateThresholdManager, &ThreshData) != STATUS_SUCCESS){
        return 0x00;
    }
    return (PDMA_THRESHOLD_MANAGER)(UINT8*)ThreshData;
}

static PVOID LouKeDmaCreateNewGenericDmaSegment(
    PDMA_THRESHOLD_MANAGER  ThresholdManager,
    ULONG                   Limit,
    ULONG                   Threshold
){
    return LouKeRatAllocateXBitPhysicalAddress(Threshold, Threshold, Limit);
}

static PVOID LouKeDmaCreateNewGenericDmaSegmentVirtual(
    PDMA_THRESHOLD_MANAGER  ThresholdManager,
    ULONG                   Limit,
    SIZE                    Threshold,
    PVOID*                  PhyAddress
){
    PVOID Phys = LouKeDmaCreateNewGenericDmaSegment(ThresholdManager, Limit, Threshold);
    if(PhyAddress){
        *PhyAddress = Phys;
    }
    return LouKeMallocPageEx(KILOBYTE_PAGE, ROUND_UP64(Threshold, KILOBYTE_PAGE) / KILOBYTE_PAGE, KERNEL_DMA_MEMORY, (UINT64)(UINT8*)Phys);
}

UNUSED static POOL LouKeDmaCreateNewGenericDmaSegmentPool(
    PDMA_THRESHOLD_MANAGER  ThresholdManager,
    ULONG                   Limit,
    SIZE                    Threshold
){
    PVOID PhysAddr = 0x00;
    PVOID VirtAddr = LouKeDmaCreateNewGenericDmaSegmentVirtual(
        ThresholdManager,
        Limit,
        Threshold,
        &PhysAddr
    );
    return LouKeCreateGenericPool(
        (uint64_t)VirtAddr,
        (uint64_t)PhysAddr,
        (uint64_t)Threshold,
        (uint64_t)0
    );
}


KERNEL_EXPORT 
PVOID 
LouKeDmaAllocateGenericDmaMemory(
    SIZE    Size,
    SIZE    Alignment,
    ULONG   Limit,
    ULONG   Threshold
){
    PDMA_LIMIT_MANAGER LimitManager = GetLimitManager(Limit); 
    PDMA_THRESHOLD_MANAGER ThresholdManager = GetThresholdManager(LimitManager, Threshold);
    
    PDMA_ALLOCATION_LIST_ENTRY TmpEntry;
    MutexLock(&ThresholdManager->LockOutTagOut);
    PVOID Result = 0x00;
    ForEachListEntry(TmpEntry, &ThresholdManager->Entries, Peers){
        Result = LouKeMallocFromDynamicPoolEx(TmpEntry->Pool, Size, Alignment);
        if(Result){
            break;
        }
    }
    if(!Result){
        TmpEntry = LouKeMallocType(DMA_ALLOCATION_LIST_ENTRY, KERNEL_GENERIC_MEMORY);
        if(TmpEntry){
            TmpEntry->Pool = LouKeDmaCreateNewGenericDmaSegmentPool(ThresholdManager, Limit, Threshold);
            if(!TmpEntry->Pool){
                LouKeFree(TmpEntry);
            }else{
                LouKeListAddTail(&TmpEntry->Peers, &ThresholdManager->Entries);
                Result = LouKeMallocFromDynamicPoolEx(TmpEntry->Pool, Size, Alignment);
            }
        }
    }
    MutexUnlock(&ThresholdManager->LockOutTagOut);
    return Result;
}

KERNEL_EXPORT 
void
LouKeDmaFreeGenericDmaMemory(
    PVOID Data, 
    ULONG Limit, 
    ULONG Threshold
){
    PDMA_LIMIT_MANAGER LimitManager = GetLimitManager(Limit); 
    PDMA_THRESHOLD_MANAGER ThresholdManager = GetThresholdManager(LimitManager, Threshold);
    
    PDMA_ALLOCATION_LIST_ENTRY TmpEntry;
    MutexLock(&ThresholdManager->LockOutTagOut);
    ForEachListEntry(TmpEntry, &ThresholdManager->Entries, Peers){
        POOL TmpPool = TmpEntry->Pool;
        if(RangeInterferes((UINT64)TmpPool->VLocation, (UINT64)Threshold, (UINT64)Data, (UINT64)1)){
            LouKeFreeFromDynamicPool(TmpPool, Data);
            break;
        }
    }
    MutexUnlock(&ThresholdManager->LockOutTagOut);
}
