#include "ProcessPrivate.h"

#define USER_THREAD_STUB "AnnyaUserThreadStub"

LOUDDK_API_ENTRY
uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

static LOUSTATUS CreateImpThreadHandle(
    PTHREAD*    ThreadOut, 
    PVOID       WorkEntry, 
    PVOID       WorkParam, 
    SIZE        StackSize,
    UINT8       Prioirty,
    PVOID       AfinityBitmap,
    PVOID       UnblockTime
){

    PVOID ImpStub = (PVOID)LouKeLinkerGetAddress("LOUDLL.DLL", USER_THREAD_STUB);

    if(!ImpStub){
        LouPrint("ERROR ImpStub Was Not Found\n");
        return STATUS_UNSUCCESSFUL;
    }

    PGENERIC_PROCESS_DATA ProcessData = 0x00;
    LouKePsmGetProcessHandle(KERNEL_PROCESS_NAME, (PHANDLE)&ProcessData);    
    
    LOUSTATUS Status = LouKeTsmCreateThreadHandle(
        (PGENERIC_THREAD_DATA*)ThreadOut,
        ProcessData,
        ImpStub,
        WorkEntry,
        WorkParam,
        Prioirty,
        StackSize,
        10,
        0x18 | 0b11,
        0x20 | 0b11,
        LONG_MODE,
        (PTIME_T)UnblockTime,
        (UINT8*)AfinityBitmap
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("CreateImpThreadHandle() ERROR:Unable To Create Thread Handle\n");
    }

    return Status;
}


LOUDDK_API_ENTRY
PTHREAD
LouKeCreateDeferedImpEx(
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
    LouPrint("Creating Imp\n");
    if(ProcessorSpcific){
        AfinityMask = LouKeMallocArray(UINT8, PROCESSOR_BITMAP_LENGTH, KERNEL_GENERIC_MEMORY);
        MARK_PROCESSOR_AFFILIATED(AfinityMask, Processor);
    }


    LOUSTATUS Status;
    PGENERIC_THREAD_DATA NewThread; 
    Status = CreateImpThreadHandle(
        (PTHREAD*)&NewThread,
        Function,
        Params,
        StackSize,
        Priority,
        AfinityMask,
        UnblockTime
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("LouKeCreateDeferedImpEx() Unable To Create Thread\n");
        return 0x00;
    }

    PGENERIC_PROCESS_DATA ProcessData = 0x00;
    Status = LouKePsmGetProcessHandle(KERNEL_PROCESS_NAME, (PHANDLE)&ProcessData);
    if(Status != STATUS_SUCCESS){
        LouPrint("LouKeCreateDeferedImpEx() Unable To Get Kernel Process Handle\n");
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
LouKeCreateImpEx(
    PVOID   Function,
    PVOID   Params,
    SIZE    StackSize,
    UINT8   Prioirty,
    BOOL    ProcessorSpcific,
    INTEGER Processor
){
    TIME_T CurrentTime = {0}; 
    LouKeGetTime(&CurrentTime);
    return LouKeCreateDeferedImpEx(
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
LouKeCreateImp(
    PVOID   Function,
    PVOID   Params,
    SIZE    StackSize,
    UINT8   Prioirty
){
    return LouKeCreateImpEx(
        Function,
        Params,
        StackSize,
        Prioirty,
        false,
        0
    );
};
