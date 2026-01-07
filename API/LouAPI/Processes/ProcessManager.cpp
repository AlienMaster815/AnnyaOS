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

LOUDDK_API_ENTRY VOID LouKeDestroyThread(PVOID ThreadHandle);

KERNEL_IMPORT PGENERIC_THREAD_DATA LouKeThreadIdToThreadData(UINT64 ThreadID);

static mutex_t CoreIrqReadyLock = {0};
static LOUSINE_PROCESS_MANAGER_BLOCK     ProcessBlock = {0};
static INTEGER                           InitializationProcessor = 0; 

KERNEL_IMPORT void SetCr3(UINT64);
KERNEL_IMPORT UINT64 GetCr3();

static UINT64 SystemCr3 = 0;

//static LouKeManagerProcessSwap();
void PsmProcessScedualManagerObject::PsmSetProcessTransitionState(){
    SetCr3(this->CurrentProcess->PMLTree - GetKSpaceBase());
    SetPEB((UINT64)&this->CurrentProcess->Peb);
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

void PsmProcessScedualManagerObject::PsmYeildThread(UINT64 IrqState){
    UNUSED PGENERIC_THREAD_DATA    NextThread;
    UNUSED PGENERIC_THREAD_DATA    CurrentThread = this->CurrentThread;
    NextThread = CurrentProcess->ThreadObjects[this->ProcessorID].TsmYeild(CurrentThread);
    LouKeSwitchToTask(
        IrqState,
        CurrentThread,
        NextThread
    );
    this->CurrentThread = NextThread;
}

void PsmProcessScedualManagerObject::PsmSchedual(UINT64 IrqState){
    if(SpinlockIsLocked(&this->LockOutTagOut)){
        return;
    }
    MutexLock(&this->LockOutTagOut.Lock);


    UNUSED PGENERIC_THREAD_DATA    NextThread;
    UNUSED PGENERIC_THREAD_DATA    CurrentThread = this->CurrentThread;
    
    PGENERIC_PROCESS_DATA   CurrentProcess = this->CurrentProcess;
    if(
        (CurrentProcess->CurrentMsSlice < CurrentProcess->TotalMsSlice) &&
        (CurrentProcess->ProcessState == PROCESS_RUNNING)
    ){
        CurrentProcess->CurrentMsSlice += 10;
        NextThread = CurrentProcess->ThreadObjects[this->ProcessorID].TsmSchedual(CurrentThread);
        LouKeSwitchToTask(
            IrqState,
            CurrentThread,
            NextThread
        );
        this->CurrentThread = NextThread;
        MutexUnlock(&this->LockOutTagOut.Lock);
        return;
    }else{
        CurrentProcess->CurrentMsSlice = 0;
        PPROCESS_RING CurrentProcessRing;
        PPROCESS_RING TmpProcessRing;
        UINT64 CurrentRing = this->LoadDistributer.CurrentIndexor;
        UINT64 NextRing;
        while(1){
            NextRing = EulerCurveIndexor(&this->LoadDistributer);
            CurrentProcessRing = this->Processes[NextRing];
            if(CurrentProcessRing){
                if(CurrentProcessRing->Peers.NextHeader){
                    TmpProcessRing = (PPROCESS_RING)CurrentProcessRing->Peers.NextHeader;
                    while(TmpProcessRing != CurrentProcessRing){
                        if(
                            (!LouKeIsTimeoutNull(&TmpProcessRing->ProcessData->BlockTimeout)) &&
                            (LouKeDidTimeoutExpire(&TmpProcessRing->ProcessData->BlockTimeout)) &&
                            (TmpProcessRing->ProcessData->ProcessState == PROCESS_BLOCKED)
                        ){
                            TmpProcessRing->ProcessData->ProcessState = PROCESS_RUNNING;
                        }
                        if(TmpProcessRing->ProcessData->ProcessState == PROCESS_RUNNING){
                            this->CurrentProcess = TmpProcessRing->ProcessData;
                            PsmSetProcessTransitionState();
                            NextThread = this->CurrentProcess->ThreadObjects[this->ProcessorID].TsmSchedual(CurrentThread);
                            LouKeSwitchToTask(
                                IrqState,
                                CurrentThread,
                                NextThread
                            );
                            this->CurrentThread = NextThread;
                            MutexUnlock(&this->LockOutTagOut.Lock);
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
    }

    this->CurrentProcess = this->SystemProcess;    
    PsmSetProcessTransitionState();
    
    NextThread = this->SystemProcess->ThreadObjects[this->ProcessorID].TsmSchedual(CurrentThread);


    LouKeSwitchToTask(
        IrqState,
        CurrentThread,
        NextThread
    );

    this->CurrentThread = NextThread;
    MutexUnlock(&this->LockOutTagOut.Lock);

}


static PPROCESS_RING LouKePsmCreateProcessRing(PGENERIC_PROCESS_DATA ProcessHandle){
    PPROCESS_RING NewProcessRing = LouKeMallocType(PROCESS_RING, KERNEL_GENERIC_MEMORY);
    NewProcessRing->ProcessData = ProcessHandle;
    return NewProcessRing;
}

UNUSED static void LouKePsmDestroyProcessRing(PPROCESS_RING ProcessRing){
    LouKeFree(ProcessRing);
}



void PsmProcessScedualManagerObject::PsmAsignProcessToSchedual(PGENERIC_PROCESS_DATA Process){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&this->LockOutTagOut, &Irql);

    PPROCESS_RING NewProcessRing = LouKePsmCreateProcessRing(Process); 
    PPROCESS_RING TmpProcessRing = this->Processes[Process->ProcessPriority];
    PPROCESS_RING CurrentProcessRing = TmpProcessRing;

    if(!TmpProcessRing){
        this->Processes[Process->ProcessPriority] = NewProcessRing;
        NewProcessRing->Peers.NextHeader = (PListHeader)NewProcessRing;
        NewProcessRing->Peers.LastHeader = (PListHeader)NewProcessRing;
        goto _PROCESS_ASSIGNMENT_DONE;
    }

    while(TmpProcessRing->Peers.NextHeader != (PListHeader)CurrentProcessRing){
        TmpProcessRing = (PPROCESS_RING)TmpProcessRing->Peers.NextHeader;
    }

    CurrentProcessRing->Peers.LastHeader = (PListHeader)NewProcessRing;
    NewProcessRing->Peers.NextHeader = (PListHeader)CurrentProcessRing;
    TmpProcessRing->Peers.NextHeader = (PListHeader)NewProcessRing;

    _PROCESS_ASSIGNMENT_DONE:
    this->CurrentProcess->ProcessState = PROCESS_RUNNING;
    LouKeReleaseSpinLock(&this->LockOutTagOut, &Irql);
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
        PsmSetProcessTransitionState();
        return;
    }
    this->SystemProcess = (PGENERIC_PROCESS_DATA)ProcessHandle;
    this->CurrentProcess = (PGENERIC_PROCESS_DATA)ProcessHandle;
    PsmSetProcessTransitionState();
}

void PsmProcessScedualManagerObject::PsmSetCurrentThread(PGENERIC_THREAD_DATA Thread){
    this->CurrentThread = Thread;
}

KERNEL_IMPORT void LouKeSetIrqlNoFlagUpdate(
    LouKIRQL  NewIrql,
    LouKIRQL* OldIrql
);

static mutex_t UpmLock = {0};

LOUDDK_API_ENTRY void UpdateProcessManager(uint64_t CpuCurrentState){

    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    PSCHEDUAL_MANAGER Schedualer = &ProcessBlock.ProcStateBlock[ProcessorID].Schedualer;

    MutexLock(&UpmLock);
    Schedualer->PsmSchedual(CpuCurrentState);
    MutexUnlock(&UpmLock);

    LouKeSendIcEOI();

    return;
}


UNUSED static void ProcessorIdleTask(){
    SetCr3(SystemCr3);
    HandleApProccessorInitialization();
    SetupGDT();
    UpdateIDT(true);
    SetUpTimers();
    LouKeInitializeCurrentApApic();

    LouPrint("AP Now Idleing\n");
    MutexSynchronize(&CoreIrqReadyLock);
    LouPrint("AP Interrupts Enabled\n");
    LouKeSetIrql(PASSIVE_LEVEL, 0x00);
    LouKeDestroyThread(LouKeThreadIdToThreadData(LouKeGetThreadIdentification()));
    
    while(1){

    }
}

KERNEL_IMPORT void SignalProcessorsInitialized();
KERNEL_IMPORT void SignalProcessorsInitPending();

UNUSED static void InitializeIdleProcess(){
    SetCr3(SystemCr3);
    HandleApProccessorInitialization();
    SetupGDT();
    UpdateIDT(true);
    SetUpTimers();
    LouKeInitializeCurrentApApic();

    INTEGER CurrentCpu = GetCurrentCpuTrackMember();
    PTHREAD NewThread;
    for(INTEGER i = 0 ; i < ProcessBlock.ProcessorCount; i++){
        if((i != InitializationProcessor) && (i != CurrentCpu)){
            NewThread = LouKeCreateDeferedDemonEx(
                0x00,
                0x00,
                16 * KILOBYTE,
                31,
                true,
                i,
                0
            );
            ((PGENERIC_THREAD_DATA)NewThread)->State = THREAD_RUNNING;
            ProcessBlock.ProcStateBlock[i].Schedualer.PsmSetCurrentThread((PGENERIC_THREAD_DATA)NewThread);
            LouKeSmpWakeAssistant(i, ((PGENERIC_THREAD_DATA)NewThread)->StackTop, (UINT64)ProcessorIdleTask);
        }
    }

    LouPrint("AP Now Idleing\n");
    MutexSynchronize(&CoreIrqReadyLock);
    LouPrint("AP Interrupts Enabled\n");
    LouKeSetIrql(PASSIVE_LEVEL, 0x00);
    SignalProcessorsInitialized();
    LouKeDestroyThread(LouKeThreadIdToThreadData(LouKeGetThreadIdentification()));
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
        KERNEL_PROCESS_NAME,
        0x00, 
        PROCESS_PRIORITY_HIGH,
        0x00,
        0x00
    );

    InitializationProcessor = GetCurrentCpuTrackMember();
    HANDLE KernelProcess = 0x00;
    LouKePsmGetProcessHandle(KERNEL_PROCESS_NAME, &KernelProcess);
    for(size_t i = 0 ; i < ProcessBlock.ProcessorCount; i++){
        ProcessBlock.ProcStateBlock[i].Schedualer.PsmSetSystemProcess(KernelProcess);
        ProcessBlock.ProcStateBlock[i].Schedualer.PsmInitializeSchedualerObject(
            (UINT64)i, 
            PROCESS_PRIORITY_RINGS, 
            PROCESS_DEFAULT_DISTRIBUTER_INCREMENTER
        );
    }

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
    ProcessBlock.ProcStateBlock[InitializationProcessor].Schedualer.PsmSetCurrentThread((PGENERIC_THREAD_DATA)NewThread);
    
    SystemCr3 = GetCr3();

    for(size_t i = 0 ; i < ProcessBlock.ProcessorCount; i++){
        //first available AP gets a procInit and idle
        if(i != InitializationProcessor){
            SignalProcessorsInitPending();
            NewThread = LouKeCreateDeferedDemonEx(
                0x00,
                0x00,
                16 * KILOBYTE,
                31,
                true,
                i,
                0
            );
            ((PGENERIC_THREAD_DATA)NewThread)->State = THREAD_RUNNING;
            ProcessBlock.ProcStateBlock[i].Schedualer.PsmSetCurrentThread((PGENERIC_THREAD_DATA)NewThread);
            LouKeSmpWakeAssistant(i, ((PGENERIC_THREAD_DATA)NewThread)->StackTop, (UINT64)InitializeIdleProcess);

            break;
        }
    }

    MutexUnlock(&ProcessBlock.ProcStateBlock[InitializationProcessor].LockOutTagOut);

    LouPrint("Finished Initializing Process Manager\n");

}

LOUDDK_API_ENTRY
uint64_t LouKeGetThreadIdentification(){    
    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    if(!ProcessBlock.ProcStateBlock){
        return 0;
    }else if(!ProcessBlock.ProcStateBlock[ProcessorID].Schedualer.CurrentThread){
        return 0;
    }
    return ProcessBlock.ProcStateBlock[ProcessorID].Schedualer.CurrentThread->ThreadID;
}

LOUDDK_API_ENTRY
uint64_t GetAdvancedRegisterInterruptsStorage(){
    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    return ProcessBlock.ProcStateBlock[ProcessorID].Schedualer.CurrentThread->InterruptStorage;
}


LOUDDK_API_ENTRY void LouKeYeildExecution(uint64_t CpuCurrentState){
    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    PSCHEDUAL_MANAGER Schedualer = &ProcessBlock.ProcStateBlock[ProcessorID].Schedualer;
    
    Schedualer->PsmYeildThread(CpuCurrentState);

    LouKeMemoryBarrier();
}

void LouKeInitProceSchedTail(PGENERIC_PROCESS_DATA Process, size_t Proc){
    ProcessBlock.ProcStateBlock[Proc].Schedualer.PsmAsignProcessToSchedual(Process); 
}