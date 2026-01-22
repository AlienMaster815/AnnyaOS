#include <LouDDK.h>
#include "ProcessPrivate.h"

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



    return STATUS_SUCCESS;
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