#include <LouAPI.h>


LOUSTATUS LouKeInitalizeApicSubsystem();

LOUSTATUS LouKeInitializeInterruptSubsystems(){
    SetBasicInterrupts();
    UpdateIDT();

    LouKeInitalizeApicSubsystem();

    

    return STATUS_SUCCESS;
}