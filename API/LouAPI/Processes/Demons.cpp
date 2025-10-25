#include "ProcessPrivate.h"

LOUDDK_API_ENTRY
PTHREAD
LouKeCreateDeferedDemonEx(
    PVOID   Function,
    PVOID   Params,
    SIZE    StackSize,
    INTEGER Processor,
    PVOID UnblockTime
){

    return 0x00;
}

LOUDDK_API_ENTRY
PTHREAD
LouKeCreateDemonEx(
    PVOID   Function,
    PVOID   Params,
    SIZE    StackSize,
    INTEGER Processor
){
    TIME_T CurrentTime = {0}; 
    LouKeGetTime(&CurrentTime);
    return LouKeCreateDeferedDemonEx(
        Function,
        Params,
        StackSize,
        Processor,
        (PVOID)&CurrentTime
    );
}