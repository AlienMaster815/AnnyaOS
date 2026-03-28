//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include <Hal.h>

KERNEL_EXPORT 
LOUSTATUS 
LouKeHalQuerySystemInformation(
    HAL_QUERY_INFORMATION_CLASS InfoClass, 
    ULONG BufferSize, 
    PVOID Buffer, 
    PULONG ReturnedLength
){//export as HalQuerySystemInformation as NTOSKRNL.EXE 

    LouPrint("LouKeHalQuerySystemInformation()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeHalSetSystemInformation(
    HAL_QUERY_INFORMATION_CLASS InfoClass, 
    ULONG BufferSize, 
    PVOID Buffer
){//export as HalSetSystemInformation as NTOSKRNL.EXE 
    LouPrint("LouKeHalSetSystemInformation()\n");
    while(1);
    return STATUS_SUCCESS;
}