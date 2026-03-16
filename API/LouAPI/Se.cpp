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

KERNEL_EXPORT 
void 
LouKeSeFreePrivileges(
    PPRIVILEGE_SET Privileges
){
    LouPrint("LouKeSeFreePrivileges()\n");
    while(1);
}
