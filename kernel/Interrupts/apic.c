#include <LouAPI.h>

void LouKeApInitializationFunction(PLKSEB TrampolineLkseb){

    while(1){
        asm("hlt");
    }
}

KERNEL_EXPORT UINT64 LouKeGetMultibootTrampolineEntrance(){
    return (UINT64)LouKeApInitializationFunction;
}

LOUSTATUS LouKeInitalizeApicSubsystem(){
    LouPrint("LouKeInitalizeApicSubsystem()\n");
    
    ApicInitializeAdvancedProgramableInterruptControllerAbstraction(0);

    //test the ID
    UINT32 ApicID;
    LOUSTATUS Status = ApicHalGetLocalApicIdRegister(&ApicID);
    if(Status != STATUS_SUCCESS){
        LouPrint("LouKeInitalizeApicSubsystem():Apic Failed To Initialize\n");
        while(1);
    }

    
    LouPrint("Successfully Initialized Apic:%h\n", ApicID);

    LouPrint("LouKeInitalizeApicSubsystem():STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}