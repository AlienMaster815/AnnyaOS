#include <LouDDK.h>

KERNEL_EXPORT 
void 
LouKeExFreePool( //export as NTOSKRNL.EXE:ExFreePool
    PVOID P
){
    LouPrint("LouKeExFreePool()\n");
    while(1);
}
