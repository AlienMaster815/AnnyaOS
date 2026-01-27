#include <stdlib.h>
#include <kernel/interrupts.h>
#include <kernel/errors.h>
#include <kernel/pic.h>

LOUSTATUS InitApicSystems();

LOUSTATUS InitializeMainInterruptHandleing(){
    LOUSTATUS Status;
    Status = InitApicSystems();
    if (Status == STATUS_SUCCESS) {
        LouPrint("Advance Interrupts Setup\n");
    }
    return Status;
}

void InvalidOpcode(uint64_t Rsp);
void DoubleFault();
void GPF();
void PageFault();
void TimerHandler();

LOUSTATUS InitializeStartupInterruptHandleing(){
    
    if(SetBasicInterrupts(true) != LOUSTATUS_GOOD)LouPanic("Error Setting Basic Interrupts",BAD);

    UpdateIDT(true);

    LouPrint("Basic Interrupts Setup\n");

    //SetInterruptFlags();

    return 0;
}
