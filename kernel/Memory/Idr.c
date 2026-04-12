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
    return LouKeXarrayAllocateInt(
        Array, 
        Start,
        Pointer,
        End,
        PageFlags
    );
}