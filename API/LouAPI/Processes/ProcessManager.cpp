#include <LouDDK.h>
#include "ProcessPrivate.h"



UNUSED static LOUSINE_PROCESS_MANAGER_BLOCK ProcessBlock = {0};

static INTEGER          InitializationProcessor = 0; 
static PEB KPeb = {0};

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
    NewThread->DemonData.KPeb = &KPeb;
    NewThread->DemonData.Cs = 0x08;
    NewThread->DemonData.Ss = 0x10;
    NewThread->DemonData.InstructionMode = LONG_MODE;
    NewThread->DemonData.State = THREAD_BLOCKED;
    NewThread->DemonData.NewThread = true;
    LouKeGetTime(&NewThread->DemonData.ThreadStart);
    NewThread->DemonData.ThreadID = AllocateDemonId((PVOID)NewThread);
    NewThread->DemonData.AfinityBitmap = LouKeMallocArray(UINT8, (ROUND_UP64(ProcessBlock.ProcessorCount, 8) / 8), KERNEL_GENERIC_MEMORY);
    return NewThread;
}

LOUDDK_API_ENTRY uint64_t UpdateProcessManager(uint64_t CpuCurrentState){



    return CpuCurrentState;
}

UNUSED static ProcessorIdleTask(){



    LouPrint("Processor Now Idleing\n");
    while(1){


    }
}

UNUSED static void InitializeIdleProcess(){



    ProcessorIdleTask();
}

LOUDDK_API_ENTRY void InitializeProcessManager(){
    LouPrint("Initializing Process Manager\n");
    ProcessBlock.ProcessorCount = GetNPROC();
    ProcessBlock.ProcStateBlock = LouKeMallocArray(PROCESSOR_STATE_BLOCK, ProcessBlock.ProcessorCount, KERNEL_GENERIC_MEMORY);
    InitializationProcessor = GetCurrentCpuTrackMember();

    MutexLock(&ProcessBlock.ProcStateBlock[InitializationProcessor].LockOutTagOut);

    ProcessBlock.DemonIDPool.IdRange = LouKeCreateIdentificationRange(1, ProcessBlock.ProcessorCount + 1);
    


    for(size_t i = 0 ; i < ProcessBlock.ProcessorCount; i++){
        //first available AP gets a procInit and idle
        if(i != InitializationProcessor){
            UINT64 InitStack = (UINT64)((UINT64)LouKeMallocPhysicalEx(16 * KILOBYTE, 16, KERNEL_GENERIC_MEMORY) + (UINT64)((16 * KILOBYTE) - 16));
            LouKeSmpWakeAssistant(i, InitStack, (UINT64)InitializeIdleProcess);

            LouKeCreateDeferedDemonEx(
                (PVOID)InitializeIdleProcess,
                0x00,
                16 * KILOBYTE,
                i,
                0
            );

            break;
        }
    }


    LouPrint("Finished Initializing Process Manager\n");
    while(1);
}