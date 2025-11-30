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
UNUSED static INTEGER                           InitializationProcessor = 0; 
UNUSED static PEB                               KPeb = {0};

//static LouKeManagerProcessSwap();

LOUDDK_API_ENTRY uint64_t UpdateProcessManager(uint64_t CpuCurrentState){

    //INTEGER ProcessorID = GetCurrentCpuTrackMember();
    



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
    /*InitializationProcessor = GetCurrentCpuTrackMember();

    MutexLock(&ProcessBlock.ProcStateBlock[InitializationProcessor].LockOutTagOut);
    MutexLock(&CoreIrqReadyLock);
    
    ProcessBlock.DemonSchedualer = CreateShecdualerObject();

    ProcessBlock.DemonIDPool.IdRange = LouKeCreateIdentificationRange(1, ProcessBlock.ProcessorCount + 1);
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
    while(1);
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