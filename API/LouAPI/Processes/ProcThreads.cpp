#include <LouDDK.h>
#include "ProcessPrivate.h"
#define USER_THREAD_STUB "AnnyaUserThreadStub"

LOUDDK_API_ENTRY
uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

LOUDDK_API_ENTRY
LOUSTATUS 
LouKePsmCreateDeferedThreadForProcessEx(
    PHANDLE     ThreadOut,
    HPROCESS    Process,
    PVOID       Entry,
    PVOID       Params,
    UINT8       Priority,
    UINT8*      ProcMask,
    PVOID       UnblockTime
){

    LOUSTATUS Status = LouKeTsmCreateThreadHandle(
        (PGENERIC_THREAD_DATA*)ThreadOut,
        (PGENERIC_PROCESS_DATA)Process,
        (PVOID)LouKeLinkerGetAddress("LOUDLL.DLL", USER_THREAD_STUB),
        Entry,
        Params,
        Priority,
        2 * MEGABYTE,
        30,
        0x1B,
        0x23,
        LONG_MODE,
        (PTIME_T)UnblockTime,
        (UINT8*)ProcMask
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("LouKePsmCreateDeferedThreadForProcessEx() ERROR:Unable To Create Thread Handle\n");
        return Status;
    }

    PGENERIC_PROCESS_DATA ProcessData = (PGENERIC_PROCESS_DATA)Process;
    INTEGER Processors = GetNPROC();
    for(size_t i = 0 ; i < Processors; i++){
        if(IS_PROCESSOR_AFFILIATED((*(PGENERIC_THREAD_DATA*)ThreadOut)->AfinityBitmap, i)){
            ProcessData->ThreadObjects[i].TsmAsignThreadToSchedual(*(PGENERIC_THREAD_DATA*)ThreadOut);
        }
    }

    return Status;
}

LOUDDK_API_ENTRY
LOUSTATUS 
LouKePsmCreateDeferedThreadForProcess(
    PHANDLE     ThreadOut,
    HPROCESS    Process,
    PVOID       Entry,
    PVOID       Params,
    UINT8       Priority,
    PVOID       UnblockTime
){
    return LouKePsmCreateDeferedThreadForProcessEx(
        ThreadOut,
        Process,
        Entry,
        Params,
        Priority,
        0x00,
        UnblockTime
    );
}

LOUDDK_API_ENTRY
LOUSTATUS 
LouKePsmCreateThreadForProcessEx(
    PHANDLE     ThreadOut,
    HPROCESS    Process,
    PVOID       Entry,
    PVOID       Params,
    UINT8       Priority,
    UINT8*      ProcMask
){
    TIME_T CurrentTime = {0};
    LouKeGetTime(&CurrentTime);
    return LouKePsmCreateDeferedThreadForProcessEx(
        ThreadOut,
        Process,
        Entry, 
        Params,
        Priority,
        ProcMask,
        (PVOID)&CurrentTime
    );
}

LOUDDK_API_ENTRY
LOUSTATUS 
LouKePsmCreateThreadForProcess(
    PHANDLE     ThreadOut,
    HPROCESS    Process,
    PVOID       Entry,
    PVOID       Params,
    UINT8       Priority
){
    return LouKePsmCreateThreadForProcessEx(
        ThreadOut,
        Process,
        Entry,
        Params,
        Priority,
        0x00
    );
}