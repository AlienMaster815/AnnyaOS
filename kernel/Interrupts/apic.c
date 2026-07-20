#include <LouAPI.h>

LOUAPI void HandleApProccessorInitialization();
LOUAPI void LouKeInitializeApProcessorInitLock();
extern void SetCr3(uint64_t Value);
LOUAPI void ApInitializeProcessManager(ULONG ProcessorID);
LOUSTATUS SetupGDT(UINT32 ProcessorID);
void HaltAndCatchFile();
LOUAPI LOUSTATUS SetUpTimers();

void LouKeApInitializationFunction(PLKSEB TrampolineLkseb){    
    LOUSTATUS Status;
    UNUSED PLKSEB PhysicalLkseb = TrampolineLkseb;
    TrampolineLkseb = (PLKSEB)(UINT8*)((UINT64)(UINT8*)TrampolineLkseb  + KSpaceBase);
    SetCr3(TrampolineLkseb->KernelPml4);
    HandleApProccessorInitialization();
    ULONG ApProcessorID = LouKeGetCurrentProcessorNumber();
    Status = SetupGDT(ApProcessorID);
    if(Status != STATUS_SUCCESS){
        HaltAndCatchFile();
    }
    PLKPCB KernelProcBlock = (PLKPCB)GetLKPCB();
    KernelProcBlock->ProcID = ApProcessorID;
    UpdateIDT();
    SetUpTimers();

    ApicInitializeAdvancedProgramableInterruptControllerAbstraction(ApProcessorID);

    LouPrint("Hello AP World\n");
    
    ApInitializeProcessManager(ApProcessorID);

    while(1){
        asm("hlt");
    }
}

KERNEL_EXPORT UINT64 LouKeGetMultibootTrampolineEntrance(){
    return (UINT64)LouKeApInitializationFunction;
}

LOUSTATUS LouKeInitalizeApicSubsystem(){
    LouPrint("LouKeInitalizeApicSubsystem()\n");
    
    LouKeInitializeApProcessorInitLock();

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