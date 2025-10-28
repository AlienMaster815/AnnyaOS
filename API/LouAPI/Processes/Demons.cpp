#include "ProcessPrivate.h"

static void ThreadStub(int(*Thread)(PVOID), PVOID FunctionParam, PTHREAD ThreadHandle){    
    int Result = Thread(FunctionParam);
    LouPrint("Thread:%h Exited With Code:%h\n", ThreadHandle, Result);
    while(1);
}


LOUDDK_API_ENTRY
PTHREAD
LouKeCreateDeferedDemonEx(
    PVOID   Function,
    PVOID   Params,
    SIZE    StackSize,
    BOOL    ProcessorSpcific,
    INTEGER Processor,
    PVOID   UnblockTime
){
    LouPrint("Creating Demon\n");
    PDEMON_THREAD_RING NewThread = LouKeCreateDemonThreadHandle();
    void* NewStack = LouKeMallocPhysicalEx(StackSize, 64, KERNEL_GENERIC_MEMORY);

    NewThread->DemonData.StackTop = (UINT64)NewStack;
    NewThread->DemonData.StackBase = (UINT64)NewStack + StackSize;

    CPUContext* NewContext = (CPUContext*)((UINT64)NewStack + (StackSize - (ROUND_UP64(sizeof(CPUContext), 64))));
    NewThread->DemonData.CurrentState = NewContext;

    NewThread->DemonData.SavedState.rcx = (uint64_t)Function;                           //first parameter  MSVC
    NewThread->DemonData.SavedState.rdx = (uint64_t)Params;                             //Second Parameter MSVC
    NewThread->DemonData.SavedState.r8  = (uint64_t)NewThread;                          //Third Parameter  MSVC
    NewThread->DemonData.SavedState.rip = (uint64_t)ThreadStub;                         //Liftoff Address  
    NewThread->DemonData.SavedState.rbp = (uint64_t)NewThread->DemonData.StackBase;     //Base Pointer
    NewThread->DemonData.SavedState.rsp = (uint64_t)NewContext;                         //Current Pointer

    NewThread->DemonData.SavedState.cs  = NewThread->DemonData.Cs;
    NewThread->DemonData.SavedState.ss  = NewThread->DemonData.Ss;  
    NewThread->DemonData.SavedState.rflags = 0x202;  

    if(ProcessorSpcific){
        MARK_PROCESSOR_AFFILIATED(NewThread->DemonData.AfinityBitmap, Processor);
    }else{
        for(size_t i = 0; i < GetNPROC(); i++){
            MARK_PROCESSOR_AFFILIATED(NewThread->DemonData.AfinityBitmap, i);
        }
    }

    if(UnblockTime){
        memcpy(&NewThread->DemonData.BlockTimeout, UnblockTime, sizeof(TIME_T));
    }

    //LouPrint("Demon Handle:%h\nStack Top:%h\nStack Base:%h\nCurrentState:%h\n", NewThread, NewThread->DemonData.StackTop, NewThread->DemonData.StackBase, (UINT64)NewThread->DemonData.CurrentState );

    return (PTHREAD)NewThread;
}

LOUDDK_API_ENTRY
PTHREAD
LouKeCreateDemonEx(
    PVOID   Function,
    PVOID   Params,
    SIZE    StackSize,
    BOOL    ProcessorSpcific,
    INTEGER Processor
){
    TIME_T CurrentTime = {0}; 
    LouKeGetTime(&CurrentTime);
    return LouKeCreateDeferedDemonEx(
        Function,
        Params,
        StackSize,
        ProcessorSpcific,
        Processor,
        (PVOID)&CurrentTime
    );
}

LOUDDK_API_ENTRY 
PTHREAD 
LouKeCreateDemon(
    PVOID Function,
    PVOID Params,
    SIZE  StackSize
){
    return LouKeCreateDemonEx(
        Function,
        Params,
        StackSize,
        false,
        0
    );
};