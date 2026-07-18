#include <LouAPI.h>

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