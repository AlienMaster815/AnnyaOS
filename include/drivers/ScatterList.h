#ifndef _SCATTER_LIST_H
#define _SCATTER_LIST_H
#pragma pack(push,1)
#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif

typedef struct _SCATTER_LIST{
    unsigned long       PageLink;
    unsigned int        Offset;
    unsigned int        Length;
    uint64_t            DmaAddress;
    #ifdef CONFIGURATION_NEED_SCATTER_GATHER_DMA_LENGTH
    unsigned int        DmaLength;
    #endif
    #ifdef CONFIGURATION_NEED_SCATTER_GATHER_DMA_FLAGS
    unsigned int        DmaFlags;
    #endif
}SCATTER_LIST, * PSCATTER_LIST;

#define SCATTER_GATHER_DMA_ADDRESS(ScatterList) ((ScatterList)->DmaAddress)

#ifdef CONFIGURATION_NEED_SCATTER_GATHER_DMA_LENGTH
#define SCATTER_GATHER_DMA_LENGTH(ScatterList) ((ScatterList)->DmaLength)
#else 
#define SCATTER_GATHER_DMA_LENGTH(ScatterList) ((ScatterList)->Length)
#endif

typedef struct _SCATTER_GATHER_TABLE{
    PSCATTER_LIST   ScatterGatherList;
    unsigned int    EntryCount;
    unsigned int    OriginalEntryCount;
}SCATTER_GATHER_TABLE, * PSCATTER_GATHER_TABLE;

typedef struct _SCATTER_GATHER_APPENED_TABLE{
    SCATTER_GATHER_TABLE    ScatterGatherTable;
    PSCATTER_LIST           Private;
    unsigned int            TotalEntries;
}SCATTER_GATHER_APPENED_TABLE, * PSCATTER_GATHER_APPENED_TABLE;

#define SCATTER_GATHER_CHAIN        0x01
#define SCATTER_GATHER_END          0x02

#define SCATTER_GATHER_PAGE_BITS    0x03

#define ScatterGatherFlags(ScatterGatherList) (unsigned int)((ScatterGatherList->PageLink) & SCATTER_GATHER_PAGE_BITS);
#define ScatterGatherChainPointer(ScatterGatherList) (unsigned int)((ScatterGatherList)->PageLink & ~(SCATTER_GATHER_PAGE_BITS))
#define ScatterGatherIsChain(ScatterGatherList) (bool)((ScatterGatherList)->PageLink & SCATTER_GATHER_CHAIN)
#define ScatterGatherIsEnd(ScatterGatherList)   (bool)((ScatterGatherList)->PageLink & SCATTER_GATHER_END)


static inline void ScatterGatherAssignPage(
    PSCATTER_LIST   ScatterGatherList,
    uint64_t*        Page          
){
    uint64_t TmpPageLink = ScatterGatherList->PageLink & SCATTER_GATHER_PAGE_BITS;    
    ScatterGatherList->PageLink = TmpPageLink | (uint64_t)Page;
}

static inline void ScatterGatherSetPage(
    PSCATTER_LIST   ScatterGatherList, 
    uint64_t* Page,
    unsigned int Length,
    unsigned int Offset
){
    ScatterGatherAssignPage(ScatterGatherList, Page);
    ScatterGatherList->Offset = Offset;
    ScatterGatherList->Length = Length;
}

static inline uint64_t* ScatterGatherPage(PSCATTER_LIST ScatterGatherList){
    return (uint64_t*)((uint64_t)ScatterGatherList->PageLink & ~(SCATTER_GATHER_PAGE_BITS));
}


uint64_t* LouKeVirtualAddresToPageValue(
    uint64_t VAddress
);

uint64_t LouKeGetOffsetInPage(
    uint64_t VAddress
);

uint64_t LouKePageToPhysicalAddres(uint64_t* Page);

static inline void ScatterGatherSetBuffer(
    PSCATTER_LIST   ScatterGatherList,
    void*           Buffer,
    unsigned int    BufferLength
){
    ScatterGatherSetPage(
        ScatterGatherList,
        LouKeVirtualAddresToPageValue((uint64_t)Buffer),
        BufferLength,
        LouKeGetOffsetInPage((uint64_t)Buffer)
    );
}

#define ForEachScatterGatherList(ScatterList, ScatterGather, Nr, i) \
    for(i = 0, ScatterGather = (ScatterList); i < (Nr); i++, ScatterGather = ScatterGatherGetNext(ScatterGather))

#define ForEachScatterGatherTable(ScatterGatherTable, ScatterGather, i) \
    ForEachScatterGatherList((ScatterGatherTable)-ScatterGatherList, ScatterGather, i)

#define ForEachScatterGatherTableDma(ScatterGatherTable, ScatterGather, i)  \
    ForEachScatterGatherList((ScatterGatherTable)->ScatterGatherList, ScatterGather, (ScatterGatherTable)->ElementCount, i)


static inline void ScatterGatherChain(
    PSCATTER_LIST    ScatterListChain, 
    PSCATTER_LIST    ScatterGatherList
){
    ScatterListChain->Offset = 0;
    ScatterListChain->Length = 0;
    ScatterListChain->PageLink = (((unsigned long)(uint64_t)ScatterGatherList | SCATTER_GATHER_CHAIN) & ~SCATTER_GATHER_END);
}

static inline void ScatterGatherMarkEnd(PSCATTER_LIST ScatterGather){
    ScatterGather->PageLink |= SCATTER_GATHER_END;
    ScatterGather->PageLink &= ~(SCATTER_GATHER_CHAIN);
}

static inline void ScatterGatherUnmarkEnd(PSCATTER_LIST ScatterGather){
    ScatterGather->PageLink &= ~(SCATTER_GATHER_END);
}

#ifdef CONFIGURATION_NEED_SCATTER_GATHER_DMA_FLAGS

#define SCATTER_GATHER_DMA_BUS_ADDRESS  1 << 0
#define SCATTER_GATHER_DMA_SWIOTLB      1 << 1

static inline bool ScatterGatherDmaIsBusAddress(PSCATTER_LIST ScatterGather){
    return (ScatterGather->DmaFlags & SCATTER_GATHER_DMA_BUS_ADDRESS) ? true : false;
}

static inline void ScatterGatherMarkBusAddress(PSCATTER_LIST ScatterGather){
    ScatterGather->DmaFlags |= SCATTER_GATHER_DMA_BUS_ADDRESS;
}

static inline void ScatterGatherDmaUnmarkBusAddress(PSCATTER_LIST ScatterGather){
    ScatterGather->DmaFlags &= ~(SCATTER_GATHER_DMA_BUS_ADDRESS);
}

static inline bool ScatterGatherIsSwioTbl(PSCATTER_LIST ScatterGather){
    return (ScaterGather->DmaFlags & SCATTER_GATHER_DMA_SWIOTLB) ? true : false;
}

static inline void ScatterGatherDmaMarkSwioTbl(PSCATTER_LIST ScatterGather){
    ScatterGather->DmaFlags |= SCATTER_GATHER_DMA_SWIOTLB;
}

static inline void ScatterGatherDmaUnmarkSwioTbl(PSCATTER_LIST ScatterGather){
    ScaterGather->DmaFlags &= ~(SCATTER_GATHER_DMA_SWIOTLB);
}
#else

static inline bool ScatterGatherDmaIsBusAddress(PSCATTER_LIST ScatterGather){
    return false;
}

static inline void ScatterGatherMarkBusAddress(PSCATTER_LIST ScatterGather){
}

static inline void ScatterGatherDmaUnmarkBusAddress(PSCATTER_LIST ScatterGather){
}

static inline bool ScatterGatherIsSwioTbl(PSCATTER_LIST ScatterGather){
    return false;
}

static inline void ScatterGatherDmaMarkSwioTbl(PSCATTER_LIST ScatterGather){
}

static inline void ScatterGatherDmaUnmarkSwioTbl(PSCATTER_LIST ScatterGather){
}

#endif

static inline uint64_t ScatterGatherPhysicalAddress(PSCATTER_LIST ScatterGather){
    return (LouKePageToPhysicalAddres(ScatterGatherPage(ScatterGather)) + ScatterGather->Offset);
}

static inline uint64_t ScatterGatherVirtualAddress(PSCATTER_LIST ScatterGather){
    return (LouKePageToPhysicalAddres(ScatterGatherPage(ScatterGather)) + ScatterGather->Offset);
}

static inline void ScatterGatherInitializeMarker(
    PSCATTER_LIST ScatterGatherList,
    unsigned int EntryCount
){
    ScatterGatherMarkEnd(&ScatterGatherList[EntryCount - 1]);
}

int ScatterGatherElementCount(PSCATTER_LIST ScatterGather);
int ScatterGatherElementCountForLength(PSCATTER_LIST ScatterGather, uint64_t Length);
PSCATTER_LIST ScatterGatherGetNext(PSCATTER_LIST ScatterGatherCurrent);
PSCATTER_LIST ScatterGatherLast(PSCATTER_LIST ScatterGatherCurrent, unsigned int ElementCount);
void ScatterGatherInitializeTable(PSCATTER_LIST ScatterGatherList, uint64_t Size);
void ScatterGatherInitializeObject(PSCATTER_LIST ScatterGatherList, void* Element, uint64_t Size);
int ScatterGatherSplit(PSCATTER_LIST InputList,int InputElementCount, uint64_t SkipToOffset, int NbSplits, uint64_t* SplitSizes, PSCATTER_LIST* OutputList, int* OutputElementCount, uint64_t AllocationFlags);

typedef SCATTER_LIST (*ScatterGatherAllocCallback)(uint64_t BlockSize, uint64_t AllocationFlags);
typedef void (*ScatterGatherFreeCallback)(PSCATTER_LIST ScatterList, uint64_t Size);

void ScatterGatherFreeTableEx(PSCATTER_GATHER_TABLE ScatterGatherTable, unsigned int, unsigned int, ScatterGatherFreeCallback, unsigned int);
void ScatterGatherFreeTable(PSCATTER_GATHER_TABLE);
void ScatterGatherFreeAppendTable(PSCATTER_GATHER_APPENED_TABLE);
int ScatterGatherAllocTableEx(PSCATTER_GATHER_TABLE,unsigned int, unsigned int, PSCATTER_LIST,unsigned int, uint64_t AllocationFlags, ScatterGatherAllocCallback);
int ScatterGatherAllocTable(PSCATTER_GATHER_TABLE, unsigned int, uint64_t);
int ScatterGatherAllocApendTableFromPages(PSCATTER_GATHER_TABLE, uint64_t**, unsigned int, unsigned int, uint64_t ,uint64_t, uint64_t);
int ScatterGatherAllocTableFromPagesSegment(PSCATTER_GATHER_TABLE, uint64_t**,unsigned int,unsigned int,uint64_t, uint64_t,uint64_t);


#ifdef __cplusplus
}
#endif
#pragma pack(pop)
#endif //_SCATTER_LIST_H
