#include "ProcessPrivate.h"

LOUDDK_API_ENTRY VOID LouKeDestroyThread(PVOID ThreadHandle){
    PGENERIC_THREAD_DATA ThreadData = (PGENERIC_THREAD_DATA)ThreadHandle;
    ThreadData->State = THREAD_TERMINATED;

    if(ThreadData->ThreadID == LouKeGetThreadIdentification()){
        asm("INT $200");
        while(1);
    }

}


UNUSED static void ThreadStub(int(*Thread)(PVOID), PVOID FunctionParam, PTHREAD ThreadHandle){    
    PGENERIC_THREAD_DATA Tmp = (PGENERIC_THREAD_DATA)ThreadHandle;
    LouPrint("Demon:%d Has Started\n", Tmp->ThreadID);
    int Result = Thread(FunctionParam);
    LouPrint("Demon:%d Exited With Code:%d\n", Tmp->ThreadID, Result);
    LouKeDestroyThread(ThreadHandle);
    while(1);
}


static LOUSTATUS CreateDemonThreadHandle(
    PTHREAD*    ThreadOut, 
    PVOID       WorkEntry, 
    PVOID       WorkParam, 
    SIZE        StackSize,
    UINT8       Prioirty,
    PVOID       AfinityBitmap,
    PVOID       UnblockTime
){
    PGENERIC_PROCESS_DATA ProcessData = 0x00;
    LouKePsmGetProcessHandle(KERNEL_PROCESS_NAME, (PHANDLE)&ProcessData);    
    
    LOUSTATUS Status = LouKeTsmCreateThreadHandle(
        (PGENERIC_THREAD_DATA*)ThreadOut,
        ProcessData,
        (PVOID)ThreadStub,
        WorkEntry,
        WorkParam,
        Prioirty,
        StackSize,
        10,
        0x08,
        0x10,
        LONG_MODE,
        (PTIME_T)UnblockTime,
        (UINT8*)AfinityBitmap
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("CreateDemonThreadHandle() ERROR:Unable To Create Thread Handle\n");
    }

    return Status;
}


LOUDDK_API_ENTRY
PTHREAD
LouKeCreateDeferedDemonEx(
    PVOID   Function,
    PVOID   Params,
    SIZE    StackSize,
    UINT8   Priority,
    BOOL    ProcessorSpcific,
    INTEGER Processor,
    PVOID   UnblockTime
){
    UINT8* AfinityMask = 0x00;
    if(Priority > 31){
        LouPrint("Unable To Create Thread: INVALID_PRIORITY\n");
        return 0x00;
    }
    LouPrint("Creating Demon\n");
    if(ProcessorSpcific){
        AfinityMask = LouKeMallocArray(UINT8, PROCESSOR_BITMAP_LENGTH, KERNEL_GENERIC_MEMORY);
        MARK_PROCESSOR_AFFILIATED(AfinityMask, Processor);
    }


    LOUSTATUS Status;
    PGENERIC_THREAD_DATA NewThread; 
    Status = CreateDemonThreadHandle(
        (PTHREAD*)&NewThread,
        Function,
        Params,
        StackSize,
        Priority,
        AfinityMask,
        UnblockTime
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("LouKeCreateDeferedDemonEx() Unable To Create Thread\n");
        return 0x00;
    }

    PGENERIC_PROCESS_DATA ProcessData = 0x00;
    Status = LouKePsmGetProcessHandle(KERNEL_PROCESS_NAME, (PHANDLE)&ProcessData);
    if(Status != STATUS_SUCCESS){
        LouPrint("LouKeCreateDeferedDemonEx() Unable To Get Kernel Process Handle\n");
        return 0x00;
    }
    INTEGER Processors = GetNPROC();
    for(size_t i = 0 ; i < Processors; i++){
        if(IS_PROCESSOR_AFFILIATED(NewThread->AfinityBitmap, i)){
            ProcessData->ThreadObjects[i].TsmAsignThreadToSchedual(NewThread);
        }
    }
    return NewThread;
}

LOUDDK_API_ENTRY
PTHREAD
LouKeCreateDemonEx(
    PVOID   Function,
    PVOID   Params,
    SIZE    StackSize,
    UINT8   Prioirty,
    BOOL    ProcessorSpcific,
    INTEGER Processor
){
    TIME_T CurrentTime = {0}; 
    LouKeGetTime(&CurrentTime);
    return LouKeCreateDeferedDemonEx(
        Function,
        Params,
        StackSize,
        Prioirty,
        ProcessorSpcific,
        Processor,
        (PVOID)&CurrentTime
    );
}

LOUDDK_API_ENTRY 
PTHREAD 
LouKeCreateDemon(
    PVOID   Function,
    PVOID   Params,
    SIZE    StackSize,
    UINT8   Prioirty
){
    return LouKeCreateDemonEx(
        Function,
        Params,
        StackSize,
        Prioirty,
        false,
        0
    );
};
