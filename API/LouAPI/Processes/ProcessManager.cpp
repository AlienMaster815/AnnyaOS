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

static mutex_t CoreIrqReadyLock = {0};

UNUSED static LOUSINE_PROCESS_MANAGER_BLOCK ProcessBlock = {0};

static INTEGER          InitializationProcessor = 0; 
static PEB              KPeb = {0};

static INTEGER AllocateDemonId(PVOID ThreadHandle){
    PPM_ID_RANGE_POOL Range = &ProcessBlock.DemonIDPool;
    INTEGER Result = (INTEGER)-1;
    size_t Index = 0;
    while(1){
        Result = LouKeAcquireIdFromRange(Range->IdRange, ThreadHandle);
        if(Result != (INTEGER)-1){
            return Result;
        }
        else if(!Range->Peers.NextHeader){
            break;
        }
        Index++;
        Range = (PPM_ID_RANGE_POOL)Range->Peers.NextHeader;
    }
    if(Result == (INTEGER)-1){
        Range->Peers.NextHeader = (PListHeader)LouKeMallocType(PM_ID_RANGE_POOL, KERNEL_GENERIC_MEMORY);
        Range = (PPM_ID_RANGE_POOL)Range->Peers.NextHeader;
        Range->IdRange = LouKeCreateIdentificationRange(Index * (ProcessBlock.ProcessorCount + 1), (Index * (ProcessBlock.ProcessorCount + 1)) + (ProcessBlock.ProcessorCount + 1));
    }
    Result = LouKeAcquireIdFromRange(Range->IdRange, ThreadHandle);
    return Result;
}

PDEMON_THREAD_RING LouKeCreateDemonThreadHandle(){
    PDEMON_THREAD_RING NewThread = LouKeMallocType(DEMON_THREAD_RING, KERNEL_GENERIC_MEMORY);
    PDEMON_THREAD_RING TmpRing = ProcessBlock.DemonRing;
    PDEMON_THREAD_RING BaseRing = TmpRing;
    NewThread->DemonData.Peb = &KPeb;
    NewThread->DemonData.Cs = 0x08;
    NewThread->DemonData.Ss = 0x10;
    NewThread->DemonData.InstructionMode = LONG_MODE;
    NewThread->DemonData.State = THREAD_BLOCKED;
    NewThread->DemonData.NewThread = true;
    NewThread->DemonData.InterruptStorage = (uintptr_t)LouKeMallocPhysicalEx(1688, 64, KERNEL_GENERIC_MEMORY);
    NewThread->DemonData.ContextStorage = (uintptr_t)LouKeMallocPhysicalEx(1688, 64, KERNEL_GENERIC_MEMORY);
    LouKeGetTime(&NewThread->DemonData.ThreadStart);
    NewThread->DemonData.ThreadID = AllocateDemonId((PVOID)NewThread);
    NewThread->DemonData.AfinityBitmap = LouKeMallocArray(UINT8, (ROUND_UP64(ProcessBlock.ProcessorCount, 8) / 8), KERNEL_GENERIC_MEMORY);
    NewThread->DemonData.TotalMsSlice = 50;
    NewThread->DemonData.CurrentMsSlice = 0;
    
    LouKeMemoryBarrier();

    if(TmpRing){
        BaseRing->Peers.LastHeader = (PListHeader)NewThread;
        NewThread->Peers.NextHeader = (PListHeader)BaseRing;
        while(TmpRing->Peers.NextHeader != (PListHeader)BaseRing){
            TmpRing = (PDEMON_THREAD_RING)TmpRing->Peers.NextHeader;
        }
        TmpRing->Peers.NextHeader = (PListHeader)NewThread;
        NewThread->Peers.LastHeader = (PListHeader)TmpRing;
    }else{
        ProcessBlock.DemonRing = NewThread;
        ProcessBlock.DemonRing->Peers.NextHeader = (PListHeader)NewThread;
        ProcessBlock.DemonRing->Peers.LastHeader = (PListHeader)NewThread;
    }
    
    LouKeMemoryBarrier();
    
    return NewThread;
}

static bool AbortTaskSwap(INTEGER ProcessorID){
    if((MutexIsLocked(&ProcessBlock.ProcStateBlock[ProcessorID].LockOutTagOut) || (LouKeGetIrql() == HIGH_LEVEL))){
        return true;
    }
    return false;
}

//static LouKeManagerProcessSwap();


LOUDDK_API_ENTRY uint64_t UpdateProcessManager(uint64_t CpuCurrentState){

    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    PDEMON_THREAD_RING TmpRing = 0x00;
    PDEMON_THREAD_RING CurrentRing = TmpRing; 

    if( //if in a demon and a processor ring exist check for a process
        (LouKeCheckAtomicBoolean(&ProcessBlock.ProcStateBlock[ProcessorID].RingSelector)) && 
        (ProcessBlock.ProcessRing)
    ){

        //TODO: im going to implement actual processes after
        //the coff specification is fully implemented

        LouPrint("PROCESS_TASK_SWAP\n");
        while(1);

    }else{
        CurrentRing = ProcessBlock.ProcStateBlock[ProcessorID].CurrentDemon;

        if(CurrentRing->DemonData.CurrentMsSlice < CurrentRing->DemonData.TotalMsSlice){
            CurrentRing->DemonData.CurrentMsSlice += 10;//timer in 10MS increments
            goto _SCHEDUALR_FINISHED;
        }

        if(AbortTaskSwap(ProcessorID)){
            goto _SCHEDUALR_FINISHED;
        }

        CurrentRing->DemonData.CurrentMsSlice = 0;

        TmpRing = (PDEMON_THREAD_RING)CurrentRing->Peers.NextHeader;
        while((TmpRing) && (TmpRing != CurrentRing)){

            if((!MutexIsLocked(&TmpRing->DemonData.LockOutTagOut)) && (TmpRing->DemonData.State != THREAD_RUNNING)){
                if(
                    (TmpRing->DemonData.State == THREAD_BLOCKED) && 
                    (LouKeDidTimeoutExpired(&TmpRing->DemonData.BlockTimeout)) && 
                    (!LouKeIsTimeoutNull(&TmpRing->DemonData.BlockTimeout))
                ){
                    TmpRing->DemonData.State = THREAD_READY;
                }
                
                if((TmpRing->DemonData.State == THREAD_READY) && (IS_PROCESSOR_AFFILIATED(TmpRing->DemonData.AfinityBitmap, ProcessorID))){
                    break;
                }   
            }

            TmpRing = (PDEMON_THREAD_RING)TmpRing->Peers.NextHeader;
        }
        if(TmpRing == CurrentRing){
            goto _SCHEDUALR_FINISHED;
        }
        if(!TmpRing){
            LouPrint("Thread Destroyed\n");
            while(1);
        }else{
            LouKeSwitchToTask(CpuCurrentState, &CurrentRing->DemonData, &TmpRing->DemonData, true);        
        }
        ProcessBlock.ProcStateBlock[ProcessorID].CurrentInterruptStorage = TmpRing->DemonData.InterruptStorage; 
        ProcessBlock.ProcStateBlock[ProcessorID].CurrentContextStorage = TmpRing->DemonData.ContextStorage; 
        ProcessBlock.ProcStateBlock[ProcessorID].CurrentThreadID = TmpRing->DemonData.ThreadID;
        ProcessBlock.ProcStateBlock[ProcessorID].CurrentDemon = TmpRing;

    }



    _SCHEDUALR_FINISHED:
    LouKeSendIcEOI();
    return CpuCurrentState;
}

UNUSED static void ProcessorIdleTask(){
    LouPrint("Initializing Processor()\n");

    SetupGDT();
    HandleApProccessorInitialization();
    InitializeStartupInterruptHandleing();
    SetUpTimers();
    LouKeInitializeCurrentApApic();

    LouKeSetIrql(PASSIVE_LEVEL, 0x00);
    LouPrint("AP Now Idleing\n");
    MutexSynchronize(&CoreIrqReadyLock);
    LouPrint("AP Interrupts Enabled\n");
    while(1){

    }
}

UNUSED static void InitializeIdleProcess(){
    LouPrint("Initializing Processor()\n");

    SetupGDT();
    HandleApProccessorInitialization();
    InitializeStartupInterruptHandleing();
    SetUpTimers();
    LouKeInitializeCurrentApApic();

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
            
            ProcessBlock.ProcStateBlock[i].CurrentDemon = (PDEMON_THREAD_RING)NewThread;
            LouKeSetAtomicBoolean(&ProcessBlock.ProcStateBlock[i].RingSelector, 1);
            ProcessBlock.ProcStateBlock[i].CurrentDemon->DemonData.State = THREAD_RUNNING;

            memset(&ProcessBlock.ProcStateBlock[i].CurrentDemon->DemonData.SavedState, 0, sizeof(CPUContext));

            LouKeSmpWakeAssistant(i, (UINT64)ProcessBlock.ProcStateBlock[i].CurrentDemon->DemonData.CurrentState, (UINT64)ProcessorIdleTask);
        }
    }
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

    ProcessBlock.DemonIDPool.IdRange = LouKeCreateIdentificationRange(1, ProcessBlock.ProcessorCount + 1);
    PTHREAD NewThread = LouKeCreateDeferedDemonEx(
        (PVOID)0x00,
        0x00,
        16 * KILOBYTE,
        true,
        InitializationProcessor,
        0
    );
    ProcessBlock.ProcStateBlock[InitializationProcessor].CurrentDemon->DemonData.NewThread = false;
    ProcessBlock.ProcStateBlock[InitializationProcessor].CurrentDemon = (PDEMON_THREAD_RING)NewThread;
    LouKeSetAtomicBoolean(&ProcessBlock.ProcStateBlock[InitializationProcessor].RingSelector, 1);
    ProcessBlock.ProcStateBlock[InitializationProcessor].CurrentDemon->DemonData.State = THREAD_RUNNING;

    memset(&ProcessBlock.ProcStateBlock[InitializationProcessor].CurrentDemon->DemonData.SavedState, 0, sizeof(CPUContext));

    for(size_t i = 0 ; i < ProcessBlock.ProcessorCount; i++){
        //first available AP gets a procInit and idle
        if(i != InitializationProcessor){
            NewThread = LouKeCreateDeferedDemonEx(
                (PVOID)InitializeIdleProcess,
                0x00,
                16 * KILOBYTE,
                true,
                i,
                0
            );
            
            ProcessBlock.ProcStateBlock[i].CurrentDemon = (PDEMON_THREAD_RING)NewThread;
            LouKeSetAtomicBoolean(&ProcessBlock.ProcStateBlock[i].RingSelector, 1);
            ProcessBlock.ProcStateBlock[i].CurrentDemon->DemonData.State = THREAD_RUNNING;

            memset(&ProcessBlock.ProcStateBlock[i].CurrentDemon->DemonData.SavedState, 0, sizeof(CPUContext));

            LouKeSmpWakeAssistant(i, (UINT64)ProcessBlock.ProcStateBlock[i].CurrentDemon->DemonData.CurrentState, (UINT64)InitializeIdleProcess);

            break;
        }
    }

    MutexUnlock(&ProcessBlock.ProcStateBlock[InitializationProcessor].LockOutTagOut);

    LouPrint("Finished Initializing Process Manager\n");
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