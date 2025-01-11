#include <LouAPI.h>


int ScatterGatherElementCount(
    PSCATTER_LIST ScatterGather
){
    int Result = 0;
    for(; ScatterGather; ScatterGather = ScatterGatherGetNext(ScatterGather)){
        Result++;
    }
    return Result;
}

int ScatterGatherElementCountForLength(
    PSCATTER_LIST ScatterGather, 
    uint64_t Length
){
    if(!Length){
        return 0;
    }

    uint64_t Total = 0;
    int ElementCount = 0;
    for(; ScatterGather ;ScatterGather = ScatterGatherGetNext(ScatterGather)){
        ElementCount++;
        Total += ScatterGather->Length;
        if(Total >= Length){
            return ElementCount;
        }
    }

    return -1;
}

PSCATTER_LIST ScatterGatherGetNext(
    PSCATTER_LIST ScatterGatherCurrent
){

    if(ScatterGatherIsEnd(ScatterGatherCurrent)){
        return 0;
    }
    //plus sizeof for packing and -O0
    ScatterGatherCurrent += sizeof(SCATTER_LIST);

    if(ScatterGatherIsChain(ScatterGatherCurrent)){
        ScatterGatherCurrent = (PSCATTER_LIST)(uintptr_t)ScatterGatherChainPointer(ScatterGatherCurrent);
    }

    return ScatterGatherCurrent;
}

PSCATTER_LIST ScatterGatherLast(
    PSCATTER_LIST ScaterGatherCurrent,
    unsigned int ElementCount
){
    UNUSED PSCATTER_LIST TmpList, Result = NULL;
    UNUSED size_t Index = 0;

    ForEachScatterGatherList(
        ScaterGatherCurrent, 
        TmpList, 
        ElementCount, 
        Index
    ){
        Result = TmpList;
    }

    return Result;
}

void ScatterGatherInitializeTable(
    PSCATTER_LIST ScatterGatherList, 
    uint64_t ElementCount
){
    memset((void*)ScatterGatherList, 0, sizeof(SCATTER_LIST) * ElementCount);
    ScatterGatherInitializeMarker(ScatterGatherList, ElementCount);
}

void ScatterGatherInitializeObject(
    PSCATTER_LIST ScatterGatherList, 
    void* Buffer, 
    uint64_t BufferLength
){
    ScatterGatherInitializeTable(ScatterGatherList, 1);
    ScatterGatherSetBuffer(ScatterGatherList,Buffer,BufferLength);
}

//static int ScatterGatherCalculateSplit(
//    PSCATTER_LIST               InputList,
//    int                         ElementCount,
//    uint64_t                    NumberOfSplits,
//    uint64_t                    Offset,
//    uint64_t*                   SizesReference,
//    PSCATTER_GATHER_SPLITER     Splitters,
//    bool                        Mapped
//){


//    return 0;  
//}

int ScatterGatherSplit(
    PSCATTER_LIST InputList,
    int InputElementCount, 
    int NbSplits, 
    uint64_t SkipToOffset, 
    uint64_t* SplitSizes, 
    PSCATTER_LIST* OutputList, 
    int* OutputElementCount, 
    uint64_t AllocationFlags
){
    int Result = 0;

    return Result;
}

void ScatterGatherFreeTableEx(
    PSCATTER_GATHER_TABLE       ScatterGatherTable, 
    unsigned int                MaximumEntries, 
    unsigned int                FirstChunkElements, 
    ScatterGatherFreeCallback   ScatterGatherFree, 
    unsigned int                ElementCount
){

}

void ScatterGatherFreeTable(
    PSCATTER_GATHER_TABLE ScatterGatherTable
){

}


void ScatterGatherFreeAppendTable(
    PSCATTER_GATHER_APPENED_TABLE CcatterGatherAppendTable
){

}

int ScatterGatherAllocTableEx(
    PSCATTER_GATHER_TABLE           ScatterGatherTable,
    unsigned int                    ElementCount, 
    unsigned int                    MaximumEntries, 
    PSCATTER_LIST                   FirstChunk,
    unsigned int                    FirstChunkElementCount, 
    uint64_t                        AllocationFlags, 
    ScatterGatherAllocCallback      ScatterGatherAlloc
){

    return 0;
}

int ScatterGatherAllocTable(
    PSCATTER_GATHER_TABLE   ScatterGatherTable, 
    unsigned int            ElementCount, 
    uint64_t                AllocationFlags
){

    return 0;
}


int ScatterGatherAllocApendTableFromPages(
    PSCATTER_GATHER_TABLE   ScatterGatherTable, 
    uint64_t**              PageReference,
    unsigned int            PageCount, 
    unsigned int            Offset, 
    uint64_t                Size,
    uint64_t                MaximumSegments, 
    uint64_t                LeftPages,
    uint64_t                AllocationFlags
){

    return 0;
}

int ScatterGatherAllocTableFromPagesSegment(
    PSCATTER_GATHER_TABLE   ScatterGatherTable, 
    uint64_t**              PageReference,
    unsigned int            PageCount,
    unsigned int            Offset,
    uint64_t                Size, 
    uint64_t                MaximumSegments,
    uint64_t                AllocationFlags
){

    return 0;
}


PSCATTER_LIST ScatterGatherAllocOrder(
    uint64_t        Length,
    unsigned int    Order,
    bool            ChainAble,
    uint64_t        AllocationFlags,
    uint64_t*       ElementCountReference
){

    return 0x00;
}

PSCATTER_LIST ScatterGatherAlloc(
    uint64_t        Length,
    uint64_t        AllocationFlags,
    unsigned int*   ElementCountReference
){

    return 0x00;
}

void ScatterGatherFreeCountOrder(
    PSCATTER_LIST   ScatterGatherList,
    int             ElementCount,
    int             Order
){

}

void ScatterGatherFreeOrder(
    PSCATTER_LIST   ScatterGatherList,
    int             Order
){

}

void ScatterGatherFree(
    PSCATTER_LIST   ScatterGatherList
){

}



uint64_t ScatterGatherCopyBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    void*           Buffer,
    uint64_t        BufferLength
){

    return 0;
}

uint64_t ScatterGatherCopyFromBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    void*           Buffer,
    uint64_t        BufferLength
){

    return 0;
}

uint64_t ScatterGatherCopyToBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    void*           Buffer,
    uint64_t        BufferLength
){

    return 0;
}

uint64_t ScatterGatherPCopyFromBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    void*           Buffer,
    uint64_t        BufferLength,
    uint64_t        Offset
){

    return 0;
}

uint64_t ScatterGatherPCopyToBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    void*           Buffer,
    uint64_t        BufferLength,
    uint64_t        Offset
){

    return 0;
}

uint64_t ScatterGatherZeroBuffer(
    PSCATTER_LIST   ScatterGatherList,
    unsigned int    ElementCount,
    uint64_t        BufferLength,
    uint64_t        Offset
){

    return 0;
}

void ScatterGatherFreeTableChained(
    PSCATTER_LIST   ScatterGatherTable,
    uint64_t        ElementsInFirstChunk
){

}

void ScatterGatherAllocTableChained(
    PSCATTER_LIST   ScatterGatherTable,
    int             ElementCount,
    PSCATTER_LIST   FirstChunk,
    uint64_t        FirstChunkElementCount
){

}

bool ScatterGatherPageIterateNextEx(
    PSCATTER_GATHER_PAGE_ITERATOR PageIterator
){

    return false;
}
bool ScatterGatherPageIterateDmaNextEx(
    PSCATTER_GATHER_DMA_PAGE_ITERATOR DmaIterator
){

    return false;
}
void ScatterGatherPageIterateStartEx(
    PSCATTER_GATHER_PAGE_ITERATOR   PageIterator, 
    PSCATTER_LIST                   ScatterGatherList,
    unsigned int                    ElementCount,
    uint64_t                        PageOffset
){
    
}


void ScatterGatherMappingIterationStart(
    SCATTER_GATHER_MAPPING_ITERATION MappingIteration, 
    PSCATTER_LIST ScatterGatherList, 
    unsigned int ElementCount, 
    unsigned int Flags
){

}
void ScatterGatherMappingIterationSkip(
    SCATTER_GATHER_MAPPING_ITERATION MappingIteration, 
    uint64_t Offset
){
    
}
void ScatterGatherMappingIterationNext(
    SCATTER_GATHER_MAPPING_ITERATION MappingIteration
){

}
void ScatterGatherMappingIterationStop(
    SCATTER_GATHER_MAPPING_ITERATION MappingIteration
){

}
