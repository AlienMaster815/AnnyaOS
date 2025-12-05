#include <LouDDK.h>
#include "ProcessPrivate.h"

KERNEL_IMPORT
void SetupGDT();

KERNEL_IMPORT
void HandleApProccessorInitialization();

KERNEL_IMPORT
LOUSTATUS InitializeStartupInterruptHandleing();

KERNEL_IMPORT
LOUSTATUS SetUpTimers();

LOUDDK_API_ENTRY
void LouKeInitializeCurrentApApic();

KERNEL_IMPORT
LOUSTATUS UpdateIDT(bool Init);

static mutex_t CoreIrqReadyLock = {0};
UNUSED static LOUSINE_PROCESS_MANAGER_BLOCK     ProcessBlock = {0};
static INTEGER                           InitializationProcessor = 0; 
UNUSED static PEB                               KPeb = {0};

KERNEL_IMPORT void SetCr3(UINT64);

//static LouKeManagerProcessSwap();
void PsmProcessScedualManagerObject::PsmSetProcessTransitionState(){
    SetCr3(this->CurrentProcess->PMLTree - GetKSpaceBase());
    SetPEB((UINT64)&this->CurrentProcess->Peb);
    this->CurrentProcess->ProcessState = PROCESS_RUNNING;
}

LOUSTATUS PsmProcessScedualManagerObject::PsmInitializeSchedualerObject(
    UINT64 ProcessorID, 
    UINT64 DistibutionLimitor,
    UINT64 DistributerIncrementation
){
    LouPrint("PsmInitializeSchedualerObject()\n");   
    if((!DistibutionLimitor) || (!DistributerIncrementation)){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS Status;
    this->ProcessorID = ProcessorID;

    Status = CreateShecdualerObject(
        &this->LoadDistributer,
        DistibutionLimitor,
        DistributerIncrementation
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("PSM ERROR:Unable To Initialize Schedualer Object\n");
    }

    LouPrint("PsmInitializeSchedualerObject() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

PGENERIC_THREAD_DATA PsmProcessScedualManagerObject::PsmSchedual(){


    this->CurrentProcess = this->SystemProcess;    
    PsmSetProcessTransitionState();
    return this->SystemProcess->ThreadObjects[this->ProcessorID].TsmSchedual();
}

void PsmProcessScedualManagerObject::PsmAsignProcessToSchedual(PGENERIC_PROCESS_DATA Process){

}
void  PsmProcessScedualManagerObject::PsmDeasignProcessFromSchedual(PGENERIC_PROCESS_DATA Process, bool SelfIdentifiing){

}

UINT64 PsmProcessScedualManagerObject::PsmGetCurrentProcessID(){

    return 0x00;
}

UINT64 PsmProcessScedualManagerObject::PsmGetCurrentSubsystem(){



    return 0x00;
}

void PsmProcessScedualManagerObject::PsmSetSystemProcess(HANDLE ProcessHandle){
    if(this->SystemProcess){
        return;
    }
    this->SystemProcess = (PGENERIC_PROCESS_DATA)ProcessHandle;
    this->CurrentProcess = (PGENERIC_PROCESS_DATA)ProcessHandle;
}


LOUDDK_API_ENTRY uint64_t UpdateProcessManager(uint64_t CpuCurrentState){

    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    UNUSED PSCHEDUAL_MANAGER Schedualer = &ProcessBlock.ProcStateBlock[ProcessorID].Schedualer;
    UINT64 NewThread = (UINT64)Schedualer->PsmSchedual();
    
    LouPrint("UpdateProcessManager():%h\n", NewThread);



    //_SCHEDUALR_FINISHED:
    LouKeMemoryBarrier();
    LouKeSendIcEOI();
    return CpuCurrentState;
}

UNUSED static void ProcessorIdleTask(){
    HandleApProccessorInitialization();
    SetupGDT();
    UpdateIDT(true);
    SetUpTimers();
    LouKeInitializeCurrentApApic();

    LouPrint("AP Now Idleing\n");
    MutexSynchronize(&CoreIrqReadyLock);
    LouKeSetIrql(PASSIVE_LEVEL, 0x00);
    LouPrint("AP Interrupts Enabled\n");
    while(1){

    }
}

UNUSED static void InitializeIdleProcess(){
    HandleApProccessorInitialization();
    SetupGDT();
    UpdateIDT(true);
    SetUpTimers();
    LouKeInitializeCurrentApApic();

    /*
    INTEGER CurrentCpu = GetCurrentCpuTrackMember();
    for(INTEGER i = 0 ; i < ProcessBlock.ProcessorCount; i++){
        //first available AP gets a procInit and idle
        if((i != InitializationProcessor) && (i != CurrentCpu)){
            
            UNUSED PTHREAD NewThread = LouKeCreateDeferedDemonEx(
                (PVOID)ProcessorIdleTask,
                0x00,
                16 * KILOBYTE,
                true,
                i,
                0
            );
            
            ProcessBlock.ProcStateBlock[i].LegacyCurrentDemon = (PDEMON_THREAD_RING)NewThread;
            LouKeSetAtomicBoolean(&ProcessBlock.ProcStateBlock[i].RingSelector, 1);
            ProcessBlock.ProcStateBlock[i].LegacyCurrentDemon->DemonData.State = THREAD_RUNNING;

            memset(&ProcessBlock.ProcStateBlock[i].LegacyCurrentDemon->DemonData.SavedState, 0, sizeof(CPUContext));

            LouKeSmpWakeAssistant(i, (UINT64)ProcessBlock.ProcStateBlock[i].LegacyCurrentDemon->DemonData.CurrentState, (UINT64)ProcessorIdleTask);
        }
    }*/
    LouPrint("AP Now Idleing\n");
    MutexSynchronize(&CoreIrqReadyLock);
    LouKeSetIrql(PASSIVE_LEVEL, 0x00);
    LouPrint("AP Interrupts Enabled\n");
    while(1){

    }
}

LOUDDK_API_ENTRY
void LouKeUnmaskSmpInterrupts(){
    MutexUnlock(&CoreIrqReadyLock);

}

LOUDDK_API_ENTRY void InitializeProcessManager(){
    LouPrint("Initializing Process Manager\n");
    ProcessBlock.ProcessorCount = GetNPROC();
    ProcessBlock.ProcStateBlock = LouKeMallocArray(PROCESSOR_STATE_BLOCK, ProcessBlock.ProcessorCount, KERNEL_GENERIC_MEMORY);
    
    InitializationProcessor = GetCurrentCpuTrackMember();
    
    MutexLock(&ProcessBlock.ProcStateBlock[InitializationProcessor].LockOutTagOut);
    MutexLock(&CoreIrqReadyLock);
    
    LouKePmCreateProcessEx(
        0x00,
        "The Lousine Kernel",
        0x00, 
        PROCESS_PRIORITY_HIGH,
        0x00,
        0x00
    );
    InitializationProcessor = GetCurrentCpuTrackMember();
    HANDLE KernelProcess = 0x00;
    LouKePsmGetProcessHandle(KERNEL_PROCESS_NAME, &KernelProcess);
    ProcessBlock.ProcStateBlock[InitializationProcessor].Schedualer.PsmSetSystemProcess(KernelProcess);
    ProcessBlock.ProcStateBlock[InitializationProcessor].Schedualer.PsmInitializeSchedualerObject(
        (UINT64)InitializationProcessor, 
        PROCESS_PRIORITY_RINGS, 
        PROCESS_DEFAULT_DISTRIBUTER_INCREMENTER
    );
    
    /*;


    PTHREAD NewThread = LouKeCreateDeferedDemonEx(
        (PVOID)0x00,
        0x00,
        16 * KILOBYTE,
        31,
        true,
        InitializationProcessor,
        0
    );


    ProcessBlock.ProcStateBlock[InitializationProcessor].CurrentDemonThreads[0] = (PTHREAD_RING)NewThread;
    ProcessBlock.ProcStateBlock[InitializationProcessor].CurrentDemonThreads[0]->Demon.DemonData.NewThread = false;
    LouKeSetAtomicBoolean(&ProcessBlock.ProcStateBlock[InitializationProcessor].RingSelector, 1);
    ProcessBlock.ProcStateBlock[InitializationProcessor].CurrentDemonThreads[0]->Demon.DemonData.State = THREAD_RUNNING;

    memset(&ProcessBlock.ProcStateBlock[InitializationProcessor].CurrentDemonThreads[0]->Demon.DemonData.SavedState, 0, sizeof(CPUContext));

    for(size_t i = 0 ; i < ProcessBlock.ProcessorCount; i++){
        //first available AP gets a procInit and idle
        if(i != InitializationProcessor){
            NewThread = LouKeCreateDeferedDemonEx(
                (PVOID)InitializeIdleProcess,
                0x00,
                16 * KILOBYTE,
                31,
                true,
                i,
                0
            );

            ProcessBlock.ProcStateBlock[i].CurrentDemonThreads[0] = (PTHREAD_RING)NewThread;
            LouKeSetAtomicBoolean(&ProcessBlock.ProcStateBlock[i].RingSelector, 1);
            ProcessBlock.ProcStateBlock[i].CurrentDemonThreads[0]->Demon.DemonData.State = THREAD_RUNNING;

            memset(&ProcessBlock.ProcStateBlock[i].CurrentDemonThreads[0]->Demon.DemonData.SavedState, 0, sizeof(CPUContext));

            LouKeSmpWakeAssistant(i, (UINT64)ProcessBlock.ProcStateBlock[i].CurrentDemonThreads[0]->Demon.DemonData.CurrentState, (UINT64)InitializeIdleProcess);

            break;
        }
    }*/

    MutexUnlock(&ProcessBlock.ProcStateBlock[InitializationProcessor].LockOutTagOut);

    LouPrint("Finished Initializing Process Manager\n");
    while(1){
        sleep(1000);
        asm("INT $32");
    }
}

LOUDDK_API_ENTRY
uint64_t LouKeGetThreadIdentification(){    
    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    return ProcessBlock.ProcStateBlock[ProcessorID].CurrentThreadID;
}

LOUDDK_API_ENTRY
uint64_t GetAdvancedRegisterInterruptsStorage(){
    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    return ProcessBlock.ProcStateBlock[ProcessorID].CurrentContextStorage;
}


LOUDDK_API_ENTRY uint64_t LouKeYeildExecution(uint64_t CpuCurrentState){



    return CpuCurrentState;
}