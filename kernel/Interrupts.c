#include <LouAPI.h>


LOUSTATUS LouKeInitalizeApicSubsystem();

LOUSTATUS LouKeInitializeInterruptSubsystems(){
    SetBasicInterrupts();
    UpdateIDT();

    LouKeInitalizeApicSubsystem();

    

    LouPrint("LouKeInitializeInterruptSubsystems()\n");
    while(1);
    return STATUS_SUCCESS;
}