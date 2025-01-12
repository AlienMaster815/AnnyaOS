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
    ScatterGatherCurrent = &ScatterGatherCurrent[1];

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

//TODO:This
static int ScatterGatherSplitPhysical(
    PSCATTER_GATHER_SPLITTER    Splitters,
    uint64_t                    SplitterCount
){
    int i = 0, j = 0;
    PSCATTER_LIST InputScatterGather, OutputScatterGather;
    PSCATTER_GATHER_SPLITTER    Splitter;

    for(i = 0, Splitter = Splitters; i < SplitterCount; i++, Splitter = &Splitter[1]){
        InputScatterGather = Splitter->InputScatterGather0;
        OutputScatterGather = Splitter->OutputScatterGather;
        for(j = 0; j < Splitter->ElementCount; j++, OutputScatterGather = &OutputScatterGather[1]){
            *OutputScatterGather = *InputScatterGather;
            if(!j){
                OutputScatterGather->Offset += Splitter->OffsetSg0;
                OutputScatterGather->Length -= Splitter->OffsetSg0;
            }
            else{
                OutputScatterGather->Offset = 0;
            }
            SCATTER_GATHER_DMA_ADDRESS(OutputScatterGather) = 0;
            SCATTER_GATHER_DMA_LENGTH(OutputScatterGather) = 0;
            InputScatterGather = ScatterGatherGetNext(InputScatterGather);
        }
        OutputScatterGather[-1].Length = Splitter->LengthOfLastSg;
        ScatterGatherMarkEnd(&OutputScatterGather[-1]);
    }

    return 0;
}


static void ScatterGatherSplitMapped(
    PSCATTER_GATHER_SPLITTER    Splitters,
    int                         SplitterCount
){
    int i = 0, j = 0;
    PSCATTER_LIST InputScatterGather, OutputScatterGather;
    PSCATTER_GATHER_SPLITTER    Splitter;

    for(i = 0 , Splitter = Splitters; i < SplitterCount;i++){
        InputScatterGather = Splitter->InputScatterGather0;
        OutputScatterGather = Splitter->OutputScatterGather;
        for(j = 0; j < Splitter->ElementCount; j++, OutputScatterGather = &OutputScatterGather[1]){
            SCATTER_GATHER_DMA_ADDRESS(OutputScatterGather) = SCATTER_GATHER_DMA_ADDRESS(InputScatterGather);
            SCATTER_GATHER_DMA_LENGTH(OutputScatterGather) = SCATTER_GATHER_DMA_LENGTH(InputScatterGather);
            if(!j){
                SCATTER_GATHER_DMA_ADDRESS(OutputScatterGather) += Splitter->OffsetSg0;
                SCATTER_GATHER_DMA_LENGTH(OutputScatterGather) -= Splitter->OffsetSg0;
            }
            InputScatterGather = ScatterGatherGetNext(InputScatterGather);
        }
    }
}

int ScatterGatherCalculateSplit(
    PSCATTER_LIST               InputList,
    int                         ElementCount,
    uint64_t                    NumberOfSplits,
    uint64_t                    Offset,
    uint64_t*                   SizesReference,
    PSCATTER_GATHER_SPLITTER    Splitters,
    bool                        Mapped
){
    int             i = 0;
    unsigned int    ScatterGatherLength = 0;
    uint64_t size = SizesReference[0], Length;
    PSCATTER_GATHER_SPLITTER     Current = Splitters;
    PSCATTER_LIST                ScatterGather;

    for(i = 0 ; i < NumberOfSplits; i++){
        Splitters[i].InputScatterGather0 = 0x00;
        Splitters[i].ElementCount = 0;
    }

    ForEachScatterGatherList(InputList, ScatterGather, NumberOfSplits, i){
        ScatterGatherLength = Mapped ? SCATTER_GATHER_DMA_LENGTH(ScatterGather) : ScatterGather->Length;
    
        if(ScatterGatherLength < Offset){
            Offset -= ScatterGatherLength;
        }

        Length = MinimumOfTwo(uint64_t, size, ScatterGatherLength - Offset);
        if(!Current->InputScatterGather0){
            Current->InputScatterGather0 = ScatterGather;
            Current->OffsetSg0 = Offset;        
        }
        
        size -= Length;
        Current->ElementCount++;
        Current->LengthOfLastSg = Length;
       
        while(!size && ((Offset + Length) < ScatterGatherLength) && (--NumberOfSplits > 0)){
            Current++;
            size = *(++SizesReference);
            Offset += Length;
            Length = MinimumOfTwo(uint64_t, size, ScatterGatherLength - Offset);
            Current->InputScatterGather0 = ScatterGather;
            Current->OffsetSg0 = Offset;      
            Current->ElementCount = 1;
            Current->LengthOfLastSg = Length;
            size -= Length;
        }

        Offset = 0;
        
        if((!size) && (--NumberOfSplits > 0)){
            Current++;
            size= *(++SizesReference);   
        }
        
        if(!NumberOfSplits){
            break;            
        }

    }

    return (size || !Splitters[0].InputScatterGather0) ? -1 : 0;  
}

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
    int i = 0;

    PSCATTER_GATHER_SPLITTER Splitters;
    //my array is packed so just use LouMalloc
    Splitters = (PSCATTER_GATHER_SPLITTER)LouMallocEx(NbSplits * sizeof(SCATTER_GATHER_SPLITTER),sizeof(SCATTER_GATHER_SPLITTER));

    Result = ScatterGatherCalculateSplit(
        InputList,
        ScatterGatherElementCount(InputList),
        NbSplits,        
        SkipToOffset,
        SplitSizes,
        Splitters,
        false                
    );    
    if(Result < 0){
        goto _SCATTER_GATHER_SPLIT_ERROR;
    }

    Result = -2;
    for(i = 0; i < NbSplits; i++){
        //my array is packed so just use LouMalloc
        Splitters[i].OutputScatterGather = (PSCATTER_LIST)LouMallocEx(Splitters[i].ElementCount,sizeof(PSCATTER_LIST));
        if(!Splitters[i].OutputScatterGather){
            goto _SCATTER_GATHER_SPLIT_ERROR;
        }
    }

    ScatterGatherSplitPhysical(
        Splitters, 
        NbSplits
    );
    if(InputElementCount){
        Result = ScatterGatherCalculateSplit(
            InputList,
            InputElementCount,
            NbSplits,
            SkipToOffset,
            SplitSizes, 
            Splitters,
            true
        );

        if(Result < 0){
            goto _SCATTER_GATHER_SPLIT_ERROR;
        }
        ScatterGatherSplitMapped(
            Splitters,
            SkipToOffset
        );
    }

    for(i = 0;i < NbSplits;i++){
        OutputList[i] = Splitters[i].OutputScatterGather;
        if(OutputElementCount){
            OutputElementCount[i] = Splitters[i].ElementCount;
        }
    }

    LouFree((RAMADD)Splitters);
    return 0;

    _SCATTER_GATHER_SPLIT_ERROR:

        for(i = 0 ; i < NbSplits; i++){
            LouFree((RAMADD)Splitters[i].OutputScatterGather);
        }
        LouFree((RAMADD)Splitters);
    return Result;
}
 
void ScatterGatherLouFree(
    PSCATTER_LIST   ScatterGather,
    uint64_t        ElementCount
){

}

void ScatterGatherFreeTableEx(
    PSCATTER_GATHER_TABLE       ScatterGatherTable, 
    unsigned int                MaximumEntries, 
    unsigned int                FirstChunkElements, 
    ScatterGatherFreeCallback   ScatterGatherFree, 
    unsigned int                ElementCount
){
    if(!ScatterGatherTable->ScatterGatherList){
        return;
    }
    unsigned int CurrentMaxEntries = FirstChunkElements ?: MaximumEntries;
    PSCATTER_LIST ScatterGatherList = ScatterGatherTable->ScatterGatherList, NextList;

    while(ElementCount){
        unsigned int AllocationSize = ElementCount;
        unsigned int ScatterGatherSize;

        if(AllocationSize > CurrentMaxEntries){
            NextList = (PSCATTER_LIST)(uintptr_t)ScatterGatherChainPointer(&ScatterGatherList[CurrentMaxEntries - 1]);
            AllocationSize = CurrentMaxEntries;
            ScatterGatherSize = AllocationSize - 1;   
        } 
        else {
            ScatterGatherSize = AllocationSize;
            NextList = 0x00;
        }

        ElementCount -= ScatterGatherSize;
        if(FirstChunkElements){
            FirstChunkElements = 0;
        }
        else{
            ScatterGatherFree(ScatterGatherList, AllocationSize);
        }
        ScatterGatherList = NextList;
        CurrentMaxEntries = MaximumEntries;
    }
    ScatterGatherTable->ScatterGatherList = 0x00;
}

void ScatterGatherFreeTable(
    PSCATTER_GATHER_TABLE ScatterGatherTable
){
    ScatterGatherFreeTableEx(
        ScatterGatherTable, 
        SCATTER_GATHER_MAXIMUM_SINGLE_ALLOCATION,
        0, 
        ScatterGatherLouFree,
        ScatterGatherTable->OriginalEntryCount
    );
}


void ScatterGatherFreeAppendTable(
    PSCATTER_GATHER_APPENED_TABLE ScatterGatherAppendTable
){
    ScatterGatherFreeTableEx(
        &ScatterGatherAppendTable->ScatterGatherTable, 
        SCATTER_GATHER_MAXIMUM_SINGLE_ALLOCATION,
        0, 
        ScatterGatherLouFree,
        ScatterGatherAppendTable->TotalEntries
    );
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
