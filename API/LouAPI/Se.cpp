#include <LouDDK.h>

KERNEL_EXPORT
BOOLEAN 
LouKeSeSinglePrivilegeCheck(
   LUID            PrivilegeValue,
   KPROCESSOR_MODE PreviousMode
){
    LouPrint("LouKeSeSinglePrivilegeCheck()\n");
    while(1);
    return false;
}