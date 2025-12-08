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

void PsmProcessScedualManagerObject::PsmSchedual(UINT64 IrqState){
    UNUSED PGENERIC_THREAD_DATA    NextThread;
    UNUSED PGENERIC_THREAD_DATA    CurrentThread = this->CurrentThread ? this->CurrentThread : this->OwnerThread;
    /*
    PGENERIC_PROCESS_DATA   CurrentProcess = this->CurrentProcess;
    if(CurrentProcess->CurrentMsSlice < CurrentProcess->TotalMsSlice){
        CurrentProcess->CurrentMsSlice += 10;
        NextThread = CurrentProcess->ThreadObjects[this->ProcessorID].TsmSchedual();
        LouKeSwitchToTask(
            IrqState,
            CurrentThread,
            NextThread
        );
        this->CurrentThread = NextThread;
        return;
    }else{
        CurrentProcess->CurrentMsSlice = 0;
        PPROCESS_RING CurrentProcessRing;
        PPROCESS_RING TmpProcessRing;
        UINT64 CurrentRing = this->LoadDistributer.CurrentIndexor;
        UINT64 NextRing = EulerCurveIndexor(&this->LoadDistributer);
        while(1){
            CurrentProcessRing = this->Processes[NextRing];
            if(CurrentProcessRing){
                if(CurrentProcessRing->Peers.NextHeader){
                    TmpProcessRing = (PPROCESS_RING)CurrentProcessRing->Peers.NextHeader;
                    while(TmpProcessRing != CurrentProcessRing){
                        if(
                            (!LouKeIsTimeoutNull(&TmpProcessRing->ProcessData->BlockTimeout)) &&
                            (LouKeDidTimeoutExpire(&TmpProcessRing->ProcessData->BlockTimeout))
                        ){
                            TmpProcessRing->ProcessData->ProcessState = PROCESS_READY;
                        }
                        if(TmpProcessRing->ProcessData->ProcessState == PROCESS_READY){
                            this->CurrentProcess = TmpProcessRing->ProcessData;
                            PsmSetProcessTransitionState();
                            NextThread = this->CurrentProcess->ThreadObjects[this->ProcessorID].TsmSchedual();
                            LouKeSwitchToTask(
                                IrqState,
                                CurrentThread,
                                NextThread
                            );
                            this->CurrentThread = NextThread;
                            return;
                        }
                        TmpProcessRing = (PPROCESS_RING)CurrentProcessRing->Peers.NextHeader;
                    }
                }
            }
            NextRing = EulerCurveIndexor(&this->LoadDistributer);
            if(NextRing == CurrentRing){
                //if no tasks are ready just idle
                break;
            }        
        }
    }*/

    //this->CurrentProcess = this->SystemProcess;    
    //PsmSetProcessTransitionState();
    //NextThread = this->SystemProcess->ThreadObjects[this->ProcessorID].TsmSchedual();
    //LouKeSwitchToTask(
    //    IrqState,
    //    CurrentThread,
    //    NextThread
    //);
    //this->CurrentThread = NextThread;
}

void PsmProcessScedualManagerObject::PsmAsignProcessToSchedual(PGENERIC_PROCESS_DATA Process){
    LouPrint("PsmAsignProcessToSchedual()\n");
    while(1);
}
void PsmProcessScedualManagerObject::PsmDeasignProcessFromSchedual(PGENERIC_PROCESS_DATA Process, bool SelfIdentifiing){

    LouPrint("PsmDeasignProcessFromSchedual()\n");
    while(1);
}

UINT64 PsmProcessScedualManagerObject::PsmGetCurrentProcessID(){
    return this->CurrentProcess->ProcessID;
}

UINT64 PsmProcessScedualManagerObject::PsmGetCurrentSubsystem(){
    return this->CurrentProcess->Subsystem;
}

void PsmProcessScedualManagerObject::PsmSetSystemProcess(HANDLE ProcessHandle){
    if(this->SystemProcess){
        return;
    }
    this->SystemProcess = (PGENERIC_PROCESS_DATA)ProcessHandle;
    this->CurrentProcess = (PGENERIC_PROCESS_DATA)ProcessHandle;
}


LOUDDK_API_ENTRY uint64_t UpdateProcessManager(uint64_t CpuCurrentState){

    //INTEGER ProcessorID = GetCurrentCpuTrackMember();
    //UNUSED PSCHEDUAL_MANAGER Schedualer = &ProcessBlock.ProcStateBlock[ProcessorID].Schedualer;
    //Schedualer->PsmSchedual(CpuCurrentState);

    
    //LouKeMemoryBarrier();
    //LouKeSendIcEOI();
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

    PTHREAD NewThread = LouKeCreateDeferedDemonEx(
        (PVOID)0x00,
        0x00,
        16 * KILOBYTE,
        31,
        true,
        InitializationProcessor,
        0
    );
    ((PGENERIC_THREAD_DATA)NewThread)->State = THREAD_RUNNING;
    ProcessBlock.ProcStateBlock[InitializationProcessor].Schedualer.OwnerThread = (PGENERIC_THREAD_DATA)NewThread;
    /*;

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

}

LOUDDK_API_ENTRY
uint64_t LouKeGetThreadIdentification(){    
    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    return ProcessBlock.ProcStateBlock[ProcessorID].Schedualer.CurrentThread->ThreadID;
}

LOUDDK_API_ENTRY
uint64_t GetAdvancedRegisterInterruptsStorage(){
    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    return ProcessBlock.ProcStateBlock[ProcessorID].Schedualer.CurrentThread->InterruptStorage;
}


LOUDDK_API_ENTRY uint64_t LouKeYeildExecution(uint64_t CpuCurrentState){



    return CpuCurrentState;
}