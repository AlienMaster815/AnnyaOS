#include <LouAPI.h>

UNUSED static XARRAY DmaThresholdTree[2] = {0};

typedef PVOID (*DMA_PHY_ALLOCATOR)(SIZE Size, SIZE Alignment);

#define DMA_PHY64_ALLOCATOR 0
#define DMA_PHY32_ALLOCATOR 1

typedef struct _DMA_ALLOCATION_LIST_HEAD{
    mutex_t     LockOutTagOut;
    ListHeader  Entries;
}DMA_ALLOCATION_LIST_HEAD, * PDMA_ALLOCATION_LIST_HEAD;

typedef struct _DMA_ALLOCATION_LIST_ENTRY{
    ListHeader  Peers;
    POOL        Pool;
}DMA_ALLOCATION_LIST_ENTRY, * PDMA_ALLOCATION_LIST_ENTRY;

static const DMA_PHY_ALLOCATOR DmaPhyAllocators[2] = {
    LouAllocatePhysical64UpEx,
    LouAllocatePhysical32UpEx,
};

static PVOID LouKeDmaCreateNewGenericDmaSegment(
    SIZE    DmaVersion,
    SIZE    Threshold
){
    return DmaPhyAllocators[DmaVersion](Threshold, Threshold);
}

static PVOID LouKeDmaCreateNewGenericDmaSegmentVirtual(
    SIZE    DmaVersion,
    SIZE    Threshold,
    PVOID*  PhyAddress
){
    PVOID Phys = LouKeDmaCreateNewGenericDmaSegment(ROUND_UP64(DmaVersion, KILOBYTE_PAGE), Threshold);
    if(PhyAddress){
        *PhyAddress = Phys;
    }
    return LouKeMallocPageEx(KILOBYTE_PAGE, ROUND_UP64(DmaVersion, KILOBYTE_PAGE) / KILOBYTE_PAGE, KERNEL_DMA_MEMORY, (UINT64)(UINT8*)Phys);
}

UNUSED static POOL LouKeDmaCreateNewGenericDmaSegmentPool(
    SIZE DmaVersion,
    SIZE Threshold
){
    PVOID PhysAddr = 0x00;
    PVOID VirtAddr = LouKeDmaCreateNewGenericDmaSegmentVirtual(
        DmaVersion,
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

static LOUSTATUS LouKeDmaCreateDmaAllocationHead(
    PXARRAY Array, 
    UINT64  Index, 
    PVOID   Context
){
    PDMA_ALLOCATION_LIST_HEAD NewHead;
    UINT64* Out;
    if(!Context){
        return STATUS_INVALID_PARAMETER;
    }
    NewHead = LouKeMallocType(DMA_ALLOCATION_LIST_HEAD, KERNEL_GENERIC_MEMORY);
    if(!NewHead){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    LouKeXaStoreEx(Array, Index, (PVOID)NewHead, KERNEL_GENERIC_MEMORY);
    Out = (UINT64*)Context; 
    *Out = (UINT64)(UINTPTR)(UINT8*)NewHead; 
    return STATUS_SUCCESS;
}



static PVOID LouKeDmaAllocateDmaMemoryInternal(
    UINT64  DmaVersion,
    UINT64  DataSize,
    UINT64  Alignment,
    UINT64  Threshold
){
    if(DataSize > Threshold){
        return 0x00;
    }
    UINT64 ThreshData;
    if(LouKeXaGetOrDoSomthing(&DmaThresholdTree[DmaVersion], Threshold, &ThreshData, LouKeDmaCreateDmaAllocationHead, &ThreshData) != STATUS_SUCCESS){
        return 0x00;
    }
    PDMA_ALLOCATION_LIST_HEAD ThreshListHead = (PDMA_ALLOCATION_LIST_HEAD)ThreshData;
    PDMA_ALLOCATION_LIST_ENTRY TmpEntry;
    MutexLock(&ThreshListHead->LockOutTagOut);
    PVOID Result = 0x00;
    ForEachListEntry(TmpEntry, &ThreshListHead->Entries, Peers){
        Result = LouKeMallocFromDynamicPoolEx(TmpEntry->Pool, DataSize, Alignment);
        if(Result){
            break;
        }
    }
    if(!Result){
        TmpEntry = LouKeMallocType(DMA_ALLOCATION_LIST_ENTRY, KERNEL_GENERIC_MEMORY);
        if(TmpEntry){
            TmpEntry->Pool = LouKeDmaCreateNewGenericDmaSegmentPool(DmaVersion, Threshold);
            if(!TmpEntry->Pool){
                LouKeFree(TmpEntry);
            }else{
                LouKeListAddTail(&TmpEntry->Peers, &ThreshListHead->Entries);
                Result = LouKeMallocFromDynamicPoolEx(TmpEntry->Pool, DataSize, Alignment);
            }
        }
    }
    MutexUnlock(&ThreshListHead->LockOutTagOut);
    return Result;
}

KERNEL_EXPORT
PVOID 
LouKeDmaAllocateGenericDmaMemory(
    UINT64  DataSize,
    UINT64  Alignment,
    UINT64  Threshold
){
    return LouKeDmaAllocateDmaMemoryInternal(
        DMA_PHY64_ALLOCATOR,
        DataSize,
        Alignment,
        Threshold
    );
}

KERNEL_EXPORT
PVOID 
LouKeDmaAllocateGenericDmaMemory32(
    UINT64  DataSize,
    UINT64  Alignment,
    UINT64  Threshold
){
    return LouKeDmaAllocateDmaMemoryInternal(
        DMA_PHY32_ALLOCATOR,
        DataSize,
        Alignment,
        Threshold
    );
}