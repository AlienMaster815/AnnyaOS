#include <LouDDK.h>
#include "ProcessPrivate.h"

#define USER_THREAD_STUB "AnnyaUserThreadStub"

LOUDDK_API_ENTRY
uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

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
KERNEL_IMPORT void SetLKPCB(UINT64 KernelProcBlock);
KERNEL_IMPORT UINT64 GetLKPCB();

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

UINT64 PsmProcessScedualManagerObject::PsmSchedual(UINT64 IrqState){
    BOOL ProcessSwitch = false;
    UNUSED PGENERIC_THREAD_DATA    NextThread;
    UNUSED PGENERIC_THREAD_DATA    CurrentThread = this->CurrentThread;

    /*PGENERIC_PROCESS_DATA   CurrentProcess = this->CurrentProcess;
    if(
        (CurrentProcess->CurrentMsSlice < CurrentProcess->TotalMsSlice) &&
        (CurrentProcess->ProcessState == PROCESS_RUNNING)
    ){
        CurrentProcess->CurrentMsSlice += 10;
        NextThread = CurrentProcess->ThreadObjects[this->ProcessorID].TsmSchedual(CurrentThread, false);
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
                            this->Processes[NextRing] = TmpProcessRing;
                            this->CurrentProcess = TmpProcessRing->ProcessData;
                            PsmSetProcessTransitionState();
                            NextThread = this->CurrentProcess->ThreadObjects[this->ProcessorID].TsmSchedual(CurrentThread, true);
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

    if(this->CurrentProcess != this->SystemProcess){
        this->CurrentProcess = this->SystemProcess;    
        PsmSetProcessTransitionState();
        ProcessSwitch = true;
    }
        
    NextThread = this->SystemProcess->ThreadObjects[this->ProcessorID].TsmSchedual(CurrentThread, ProcessSwitch);

    IrqState = LouKeSwitchToTask(
        IrqState,
        CurrentThread,
        NextThread
    );

    this->CurrentThread = NextThread;

    return IrqState;
}


static PPROCESS_RING LouKePsmCreateProcessRing(PGENERIC_PROCESS_DATA ProcessHandle){
    PPROCESS_RING NewProcessRing = LouKeMallocType(PROCESS_RING, KERNEL_GENERIC_MEMORY);
    NewProcessRing->ProcessData = ProcessHandle;
    return NewProcessRing;
}

UNUSED static void LouKePsmDestroyProcessRing(PPROCESS_RING ProcessRing){
    LouKeFree(ProcessRing);
}

static spinlock_t AsignLock = {0};

void PsmProcessScedualManagerObject::PsmAsignProcessToSchedual(PGENERIC_PROCESS_DATA Process){

    LouKIRQL Irql;
    PPROCESS_RING NewProcessRing = LouKePsmCreateProcessRing(Process); 
    LouKeAcquireSpinLock(&AsignLock, &Irql);
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
    NewProcessRing->Peers.LastHeader = (PListHeader)TmpProcessRing;

    _PROCESS_ASSIGNMENT_DONE:
    Process->ProcessState = PROCESS_RUNNING;
    LouKeReleaseSpinLock(&AsignLock, &Irql);
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

//static SIZE Foo = 0;

LOUDDK_API_ENTRY UINT64 UpdateProcessManager(uint64_t CpuCurrentState){
    if(LouKeGetIrql() >= CLOCK_LEVEL){
        LouKeSendIcEOI();
        return CpuCurrentState;
    }
    PSCHEDUAL_MANAGER Schedualer = (PSCHEDUAL_MANAGER)((PLKPCB)GetLKPCB())->Schedualer;
    CpuCurrentState = Schedualer->PsmSchedual(CpuCurrentState);
    LouKeMemoryBarrier();
    LouKeSendIcEOI();
    return CpuCurrentState;
}

static mutex_t InitLock = {0};

UNUSED static void ProcessorIdleTask(){
    SetCr3(SystemCr3);
    HandleApProccessorInitialization();
    SetupGDT();
    UpdateIDT(true);
    SetUpTimers();
    LouKeInitializeCurrentApApic();

    LouPrint("AP Now Idleing\n");
    MutexUnlock(&InitLock);
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
            MutexLock(&InitLock);
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
    LouKeDestroyThread(LouKeThreadIdToThreadData(LouKeGetThreadIdentification()));
    while(1){

    }
}

LOUDDK_API_ENTRY
void LouKeUnmaskSmpInterrupts(){
    MutexUnlock(&CoreIrqReadyLock);

}

KERNEL_IMPORT UINT64 GetRSP();
KERNEL_IMPORT UINT64 GetRBP();
KERNEL_IMPORT void SetNewBootStack(UINT64 Base, UINT64 Pointer);

LOUDDK_API_ENTRY void InitializeProcessManager(){
    LouPrint("Initializing Process Manager\n");

    ProcessBlock.ProcessorCount = GetNPROC();
    ProcessBlock.ProcStateBlock = LouKeMallocArray(PROCESSOR_STATE_BLOCK, ProcessBlock.ProcessorCount, KERNEL_GENERIC_MEMORY);

    InitializationProcessor = GetCurrentCpuTrackMember();
    
    PLKPCB KernelProcBlock = (PLKPCB)GetLKPCB();
    KernelProcBlock->ProcID = InitializationProcessor;
    KernelProcBlock->Schedualer = (UINT64)&ProcessBlock.ProcStateBlock[InitializationProcessor].Schedualer;

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
    
    UINT8* NewStackTop = (UINT8*)((PGENERIC_THREAD_DATA)NewThread)->SavedState->rbp;
    SIZE   CurrentStackOffset = (GetBootStackTop() - GetRSP());
    UINT8* OldStackCurrent = (UINT8*)GetRSP();
    UINT8* NewStackCurrent = NewStackTop - CurrentStackOffset; 

    memcpy(NewStackCurrent, OldStackCurrent, CurrentStackOffset);

    UINT64 NewRbp = (GetRBP() - GetRSP()) + (UINT64)NewStackCurrent;

    SetNewBootStack(NewRbp, (UINT64)NewStackCurrent);

    /*for(size_t i = 0 ; i < ProcessBlock.ProcessorCount; i++){
        //first available AP gets a procInit and idle
        if(i != InitializationProcessor){
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
    }*/

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
PGENERIC_THREAD_DATA
LouKeGetCurrentThreadData(){
    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    return ProcessBlock.ProcStateBlock[ProcessorID].Schedualer.CurrentThread;
}

LOUDDK_API_ENTRY
uint64_t GetAdvancedRegisterInterruptsStorage(){
    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    return ProcessBlock.ProcStateBlock[ProcessorID].Schedualer.CurrentThread->InterruptStorage;
}


void LouKeInitProceSchedTail(PGENERIC_PROCESS_DATA Process, size_t Proc){
    ProcessBlock.ProcStateBlock[Proc].Schedualer.PsmAsignProcessToSchedual(Process); 
}

LOUSTATUS LouKeProcessCreateEntryThread(PHPROCESS Process, PVOID Entry){
    if((!Entry) || (!Process)){
        return STATUS_INVALID_PARAMETER;
    }

    PGENERIC_PROCESS_DATA ProcessData = (PGENERIC_PROCESS_DATA)Process;
    PVOID ImpStub = (PVOID)LouKeLinkerGetAddress("LOUDLL.DLL", USER_THREAD_STUB);

    if(!ImpStub){
        LouPrint("ERROR ImpStub Was Not Found\n");
        return STATUS_UNSUCCESSFUL;
    }

    PGENERIC_THREAD_DATA ThreadOut;
    LOUSTATUS Status = LouKeTsmCreateThreadHandle(
        &ThreadOut,
        ProcessData,
        ImpStub,
        Entry,
        &ProcessData->Peb,
        15,
        (ProcessData->StackSize ? ProcessData->StackSize : (16 * KILOBYTE)),
        10,
        0x18 | 0b11,
        0x20 | 0b11,
        LONG_MODE,
        0x00,
        0x00
    );

    INTEGER Processors = GetNPROC();
    for(size_t i = 0 ; i < Processors; i++){
        if(IS_PROCESSOR_AFFILIATED(ThreadOut->AfinityBitmap, i)){
            ProcessData->ThreadObjects[i].TsmAsignThreadToSchedual(ThreadOut);
        }
    }

    return Status;
}