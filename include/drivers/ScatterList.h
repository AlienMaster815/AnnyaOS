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

uint64_t LouKeGetPageAddress(uint64_t* Page);

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
    return (LouKeGetPageAddress(ScatterGatherPage(ScatterGather)) + ScatterGather->Offset);
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
void ScatterGatherInitializeTable(PSCATTER_LIST ScatterGatherList, uint64_t ElementCount);
void ScatterGatherInitializeObject(PSCATTER_LIST ScatterGatherList, void* Buffer, uint64_t BufferLength);
int ScatterGatherSplit(
    PSCATTER_LIST InputList,
    int InputElementCount, 
    int NbSplits, 
    uint64_t SkipToOffset, 
    uint64_t* SplitSizes, 
    PSCATTER_LIST* OutputList, 
    int* OutputElementCount, 
    uint64_t AllocationFlags
);

typedef SCATTER_LIST (*ScatterGatherAllocCallback)(uint64_t BlockSize, uint64_t AllocationFlags);
typedef void (*ScatterGatherFreeCallback)(PSCATTER_LIST ScatterList, uint64_t Size);

void ScatterGatherFreeTableEx(
    PSCATTER_GATHER_TABLE       ScatterGatherTable, 
    unsigned int                MaximumEntries, 
    unsigned int                FirstChunkElements, 
    ScatterGatherFreeCallback   ScatterGatherFree, 
    unsigned int                ElementCount
);
void ScatterGatherFreeTable(
    PSCATTER_GATHER_TABLE ScatterGatherTable
);
void ScatterGatherFreeAppendTable(
    PSCATTER_GATHER_APPENED_TABLE CcatterGatherAppendTable
);
int ScatterGatherAllocTableEx(
    PSCATTER_GATHER_TABLE           ScatterGatherTable,
    unsigned int                    ElementCount, 
    unsigned int                    MaximumEntries, 
    PSCATTER_LIST                   FirstChunk,
    unsigned int                    FirstChunkElementCount, 
    uint64_t                        AllocationFlags, 
    ScatterGatherAllocCallback      ScatterGatherAlloc
);
int ScatterGatherAllocTable(
    PSCATTER_GATHER_TABLE   ScatterGatherTable, 
    unsigned int            ElementCount, 
    uint64_t                AllocationFlags
);
int ScatterGatherAllocApendTableFromPages(
    PSCATTER_GATHER_TABLE   ScatterGatherTable, 
    uint64_t**              PageReference,
    unsigned int            PageCount, 
    unsigned int            Offset, 
    uint64_t                Size,
    uint64_t                MaximumSegments, 
    uint64_t                LeftPages,
    uint64_t                AllocationFlags
);
int ScatterGatherAllocTableFromPagesSegment(
    PSCATTER_GATHER_TABLE   ScatterGatherTable, 
    uint64_t**              PageReference,
    unsigned int            PageCount,
    unsigned int            Offset,
    uint64_t                Size, 
    uint64_t                MaximumSegments,
    uint64_t                AllocationFlags
);

static inline int ScatterGatherAllocTableFromPages(
    PSCATTER_GATHER_TABLE   ScatterGatherTable,
    uint64_t**              PageReference,
    unsigned int            PageCount,
    unsigned int            Offset,
    uint64_t                Size,
    uint64_t                AllocationFlags
){
    return ScatterGatherAllocTableFromPagesSegment(
        ScatterGatherTable,
        PageReference,
        PageCount,
        Offset,
        Size,
        0xFFFFFFFF,
        AllocationFlags
    );
}

PSCATTER_LIST ScatterGatherAllocOrder(
    uint64_t        Length,
    unsigned int    Order,
    bool            ChainAble,
    uint64_t        AllocationFlags,
    uint64_t*       ElementCountReference
);

PSCATTER_LIST ScatterGatherAlloc(
    uint64_t        Length,
    uint64_t        AllocationFlags,
    unsigned int*   ElementCountReference
);

void ScatterGatherFreeCountOrder(
    PSCATTER_LIST   ScatterGatherList,
    int             ElementCount,
    int             Order
);

void ScatterGatherFreeOrder(
    PSCATTER_LIST   ScatterGatherList,
    int             Order
);

void ScatterGatherFree(
    PSCATTER_LIST   ScatterGatherList
);


uint64_t ScatterGatherCopyBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    void*           Buffer,
    uint64_t        BufferLength
);

uint64_t ScatterGatherCopyFromBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    void*           Buffer,
    uint64_t        BufferLength
);

uint64_t ScatterGatherCopyToBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    void*           Buffer,
    uint64_t        BufferLength
);

uint64_t ScatterGatherPCopyFromBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    void*           Buffer,
    uint64_t        BufferLength,
    uint64_t        Offset
);

uint64_t ScatterGatherPCopyToBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    void*           Buffer,
    uint64_t        BufferLength,
    uint64_t        Offset
);

uint64_t ScatterGatherZeroBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    uint64_t        BufferLength,
    uint64_t        Offset
);

#define SCATTER_GATHER_MAXIMUM_SINGLE_ALLOCATION    (MEGABYTE_PAGE / sizeof(SCATTER_LIST))

#define SCATTER_GATHER_CHINL_SIZE       128

#ifdef CONFIGURATION_ARHCITECTURE_NO_SCATTER_GATHER_CHAIN
#define SCATTER_GATHER_MAX_SEGMENTS     SCATTER_GATHER_CHINL_SIZE
#else
#define SCATTER_GATHER_MAX_SEGMENTS     2048
#endif

void ScatterGatherFreeTableChained(
    PSCATTER_LIST   ScatterGatherTable,
    uint64_t        ElementsInFirstChunk
);

void ScatterGatherAllocTableChained(
    PSCATTER_LIST   ScatterGatherTable,
    int             ElementCount,
    PSCATTER_LIST   FirstChunk,
    uint64_t        FirstChunkElementCount
);

typedef struct _SCATTER_GATHER_PAGE_ITERATOR{
    PSCATTER_LIST   ScatterGatherList;
    unsigned int    PageOffset;
    unsigned int    ElementCount;
    int             PageAdvancement;
}SCATTER_GATHER_PAGE_ITERATOR, * PSCATTER_GATHER_PAGE_ITERATOR;

typedef struct _SCATTER_GATHER_DMA_PAGE_ITERATOR{
    SCATTER_GATHER_PAGE_ITERATOR Base;
}SCATTER_GATHER_DMA_PAGE_ITERATOR, * PSCATTER_GATHER_DMA_PAGE_ITERATOR;

bool ScatterGatherPageIterateNextEx(PSCATTER_GATHER_PAGE_ITERATOR PageIterator);
bool ScatterGatherPageIterateDmaNextEx(PSCATTER_GATHER_DMA_PAGE_ITERATOR DmaIterator);
void ScatterGatherPageIterateStartEx(
    PSCATTER_GATHER_PAGE_ITERATOR   PageIterator, 
    PSCATTER_LIST                   ScatterGatherList,
    unsigned int                    ElementCount,
    uint64_t                        PageOffset
);

static inline uint64_t ScatterGatherPageIteratePage(
    PSCATTER_GATHER_PAGE_ITERATOR   PageIterator
){
    //scatter driver uses megabte pages
    return ((uint64_t)ScatterGatherPage(PageIterator->ScatterGatherList) + ((2 * (1024 * 1024)) * PageIterator->PageOffset));
}

static inline uint64_t ScatterGatherPageIterateDmaAddres(PSCATTER_GATHER_DMA_PAGE_ITERATOR  DmaIterator){
    return (SCATTER_GATHER_DMA_ADDRESS(DmaIterator->Base.ScatterGatherList) + (DmaIterator->Base.PageAdvancement * (2 * (1024 * 1024))));
}

#define ForEachScatterGatherPage(ScatterGatherList, PageIteration, ElementCount, PageOffset)    \
    for(ScatterGatherPageIterateStartEx((PageIteration), (ScatterGatherList), (ElementCount), (PageOffset)); ScatterGatherPageIterateNextEx(PageIteration);)

#define ForEachScatterGatherDmaPage(ScatterGatherList, DmaIteration, DmaElementCount, PageOffset)   \
    for(ScatterGatherPageIterateStartEx(&(DmaIteration)->Base, (ScatterGatherList), (ElementCount), (PageOffset)); ScatterGatherPageIterateDmaNextEx(DmaIteration);)
    
#define ForEachScatterGatherTableDmaPage(Sgt,DmaIteration,PageOffset) ForEachScatterGatherDmaPage((Sgt)->ScatterGatherList, DmaIteration, (Sgt)->ElementCount, PageOffset)

#define SCATTER_GATHER_MAPPING_ITERATION_ATOMIC     1 << 0
#define SCATTER_GATHER_MAPPING_ITERATION_TO_SG      1 << 1
#define SCATTER_GATHER_MAPPING_ITERATION_FROM_SG    1 << 2

typedef struct _SCATTER_GATHER_MAPPING_ITERATION{
    uint64_t*                       Page;
    void*                           Address;
    uint64_t                        Length;
    uint64_t                        Consumed;
    SCATTER_GATHER_PAGE_ITERATOR    PageInterations;
    unsigned int                    Offset;
    unsigned int                    Remaining;
    unsigned int                    Flags;
}SCATTER_GATHER_MAPPING_ITERATION, * PSCATTER_GATHER_MAPPING_ITERATION;

void ScatterGatherMappingIterationStart(SCATTER_GATHER_MAPPING_ITERATION MappingIteration, PSCATTER_LIST ScatterGatherList, unsigned int ElementCount, unsigned int Flags);
void ScatterGatherMappingIterationSkip(SCATTER_GATHER_MAPPING_ITERATION MappingIteration, uint64_t Offset);
void ScatterGatherMappingIterationNext(SCATTER_GATHER_MAPPING_ITERATION MappingIteration);
void ScatterGatherMappingIterationStop(SCATTER_GATHER_MAPPING_ITERATION MappingIteration);

typedef struct _SCATTER_GATHER_SPLITTER{
    PSCATTER_LIST   InputScatterGather0;
    int             ElementCount;
    uint64_t        OffsetSg0;
    unsigned int    LengthOfLastSg;
    PSCATTER_LIST   OutputScatterGather;
}SCATTER_GATHER_SPLITTER, * PSCATTER_GATHER_SPLITTER;

#ifdef __cplusplus
}
#endif
#pragma pack(pop)
#endif //_SCATTER_LIST_H
