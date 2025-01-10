#include <LouAPI.h>


int ScatterGatherElementCount(
    PSCATTER_LIST ScatterGather
){

    return 0;
}
int ScatterGatherElementCountForLength(
    PSCATTER_LIST ScatterGather, 
    uint64_t Length
){

    return 0;
}

PSCATTER_LIST ScatterGatherGetNext(
    PSCATTER_LIST ScaterGatherCurrent
){

    return 0x00;
}

PSCATTER_LIST ScatterGatheLast(
    PSCATTER_LIST ScaterGatherCurrent
){

    return 0x00;
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
