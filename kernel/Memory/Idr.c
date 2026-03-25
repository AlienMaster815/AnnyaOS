#include <LouAPI.h>

KERNEL_EXPORT 
LOUSTATUS 
LouKeXaIdrAllocate(
    PXARRAY     Array,
    PVOID       Pointer,
    int*        Start,
    int         End,
    UINT64      PageFlags 
){
    LouPrint("LouKeXaIdrAllocate()\n");
    while(1);
    return STATUS_SUCCESS;
}