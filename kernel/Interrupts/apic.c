#include <LouAPI.h>

void LouKeInitializeSmpLouPrint();
LOUAPI void HandleApProccessorInitialization();
LOUAPI void LouKeInitializeApProcessorInitLock();
extern void SetCr3(uint64_t Value);
LOUAPI void ApInitializeProcessManager(ULONG ProcessorID);
LOUSTATUS SetupGDT(UINT32 ProcessorID);
void HaltAndCatchFile();
LOUAPI LOUSTATUS SetUpTimers();

static KERNEL_REFERENCE IdleingAps = {0};

ULONG LouKeGetIdleingApCount(){
    return LouKeGetReferenceCount(&IdleingAps);
}

static void (*ApInitializationFunction)() = 0; 

static mutex_t InitLock = {0};

void LouKeApIdleTillApInitFunction(){
    LouKeAcquireReference(&IdleingAps);
    while(!ApInitializationFunction){
        LouKeMemoryBarrier();
    }
    ApInitializationFunction();
}


void LouKeApInitializationFunction(){    
    UINT32 ApProcessorID;
    LOUSTATUS Status;

    AtomicLock(&InitLock);

    HandleApProccessorInitialization();

    ApicInitializeAdvancedProgramableInterruptControllerAbstraction(&ApProcessorID);

    Status = SetupGDT(ApProcessorID);
    if(Status != STATUS_SUCCESS){
        HaltAndCatchFile();
    }

    PLKPCB KernelProcBlock = (PLKPCB)GetLKPCB();
    KernelProcBlock->ProcID = ApProcessorID;

    UpdateIDT();

    SetUpTimers();

    MutexUnlock(&InitLock);

    LouKeReleaseReference(&IdleingAps);
    
    ApInitializeProcessManager(ApProcessorID);

    while(1){
        asm("hlt");
    }
}

void LouKeApIdleTillApicInitializationTask(){
    
    
    
    
    while(1){
        asm("hlt");
    }    
}

LOUSTATUS LouKeInitalizeApicSubsystem(){
    
    LouPrint("LouKeInitalizeApicSubsystem()\n");
    
    LouKeInitializeApProcessorInitLock();

    ApicInitializeAdvancedProgramableInterruptControllerAbstraction(0);

    ApInitializationFunction = LouKeApInitializationFunction;
    LouKeMemoryBarrier();

    while(LouKeGetIdleingApCount()){
        LouKeMemoryBarrier();
    }

    //test the ID
    UINT32 ApicID;
    LOUSTATUS Status = ApicHalGetLocalApicIdRegister(&ApicID);
    if(Status != STATUS_SUCCESS){
        LouPrint("LouKeInitalizeApicSubsystem():Apic Failed To Initialize\n");
        while(1);
    }


    if(GetNPROC() > 1){
        LouKeInitializeSmpLouPrint();
    }

    LouPrint("Successfully Initialized Apic:%h\n", ApicID);

    LouPrint("LouKeInitalizeApicSubsystem():STATUS_SUCCESS\n");
    
    return STATUS_SUCCESS;
}