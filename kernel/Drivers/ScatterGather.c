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


    return 0;
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
    uint64_t Size
){

}

void ScatterGatherInitializeObject(
    PSCATTER_LIST ScatterGatherList, 
    void* Element, 
    uint64_t Size
){

}

int ScatterGatherSplit(
    PSCATTER_LIST InputList,
    int InputElementCount, 
    uint64_t SkipToOffset, 
    int NbSplits, 
    uint64_t* SplitSizes, 
    PSCATTER_LIST* OutputList, 
    int* OutputElementCount, 
    uint64_t AllocationFlags
){

    return 0;
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