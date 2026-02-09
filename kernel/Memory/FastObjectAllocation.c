#include "PrivMem.h"



PVOID LouKeFastAllocateObjectArray(
    LOUSTR  ObjectLookup,
    SIZE    ObjectCount
){



    return 0x00;
}

PVOID LouKeFastAllocateObject(
    LOUSTR  ObjectLookup
){
    return LouKeFastAllocateObjectArray(
        ObjectLookup, 
        1
    );
}

