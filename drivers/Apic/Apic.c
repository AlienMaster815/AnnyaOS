#include <LouDDK.h>

DRIVER_EXPORT 
LOUSTATUS 
ApicInitializeAdvancedProgramableInterruptController(
    SIZE Cpu
){


    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS 
ApicSubsystemEntry(){
    LouPrint("APICS.SYS:ApicSubsystemEntry()\n");

    

    LouPrint("APICS.SYS:ApicSubsystemEntry():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}