//Copyright GPL-2 Tyler Grenier (2026)
#include <LouDDK.h>

KERNEL_EXPORT
void 
LouKeExRaiseDatatypeMisalignment(){ //export As NTOSKRNL.EXE:ExRaiseDatatypeMisalignment
    LouPrint("LouKeExRaiseDatatypeMisalignment()\n");
    while(1);
}

KERNEL_EXPORT
void 
LouKeExRaiseAccessViolation(){ //export as NTOSKRNL.EXE:ExRaiseAccessViolation
    LouPrint("LouKeExRaiseAccessViolation()\n");
    while(1);
}