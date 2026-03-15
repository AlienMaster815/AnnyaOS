#include <LouDDK.h>

KERNEL_EXPORT 
BOOLEAN 
LouKeLheaSignalHandlerOverrideCallback( //export KULA as NTOSKRNL.EXE:WheaSignalHandlerOverrideCallback
    UINT_PTR    Context    
){
    LouPrint("LheaSignalHandlerOverrideCallback()\n");
    while(1);
    return false;
}