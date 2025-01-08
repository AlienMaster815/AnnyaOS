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
    uint64_t        Page          
){
    uint64_t TmpPageLink = ScatterGatherList->PageLink & SCATTER_GATHER_PAGE_BITS;    
    ScatterGatherList->PageLink = TmpPageLink | Page;
}

static inline void ScatterGatherSetPage(
    PSCATTER_LIST   ScatterGatherList, 
    uint64_t Page,
    unsigned int Length,
    unsigned int Offset
){
    ScatterGatherAssignPage(ScatterGatherList, Page);
    ScatterGatherList->Offset = Offset;
    ScatterGatherList->Length = Length;
}

static inline uint64_t ScaterGatherPage(PSCATTER_LIST ScatterGatherList){
    return (uint64_t)ScatterGatherList->PageLink & ~(SCATTER_GATHER_PAGE_BITS);
}


uint64_t LouKeVirtualAddresToPageValue(
    uint64_t VAddress
);

uint64_t LouKeGetOffsetInPage(
    uint64_t VAddress
);

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



#ifdef __cplusplus
}
#endif
#pragma pack(pop)
#endif //_SCATTER_LIST_H