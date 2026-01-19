#include <LouDDK.h>
#include "ProcessPrivate.h"

void LouKeLockProcessManager();
void LouKeUnlockProcessManager();

LOUDDK_API_ENTRY
PGENERIC_THREAD_DATA
LouKeGetCurrentThreadData();
KERNEL_IMPORT PGENERIC_THREAD_DATA LouKeThreadIdToThreadData(UINT64 ThreadID);
LOUDDK_API_ENTRY VOID LouKeDestroyThread(PVOID ThreadHandle);

static void KernelThreadStub(DWORD(*Work)(PVOID), PVOID Param, PGENERIC_THREAD_DATA Thread){
    DWORD Result = 0;
    LouPrint("Thread:%d Has Started\n", Thread->ThreadID);
    Result = Work(Param);
    LouPrint("Thread:%d Exited With Code:%h\n", Thread->ThreadID, Result);
    LouKeDestroyThread(Thread);
    while(1){

    }
}

LOUDDK_API_ENTRY
semaphore_t* LouKeCreateSemaphore(int initial, int limit){
    semaphore_t* NewSemaphore = (semaphore_t*)LouKeMallocType(semaphore_t, KERNEL_GENERIC_MEMORY);
    SemaphoreInitialize(NewSemaphore, initial, limit);
    return NewSemaphore;
}

static PTHREAD_RING LouKeTsmCreateThreadRing(PGENERIC_THREAD_DATA ThreadHandle){
    PTHREAD_RING NewThreadRing = LouKeMallocType(THREAD_RING, KERNEL_GENERIC_MEMORY);
    NewThreadRing->ThreadData = ThreadHandle;
    return NewThreadRing;
}

UNUSED static void LouKeTsmDestroyThreadRing(PTHREAD_RING ThreadRing){
    LouKeFree(ThreadRing);
}

STRIP_OPTIMIZATIONS static void KernelContextSwitch(
    CPUContext*         SavedFromState,
    CPUContext*         SavedToState,
    CPUKernelContext*   Ist1State
){
    //Save Current State
    SavedFromState->rax     = Ist1State->rax;
    SavedFromState->rbx     = Ist1State->rbx;
    SavedFromState->rcx     = Ist1State->rcx;
    SavedFromState->rdx     = Ist1State->rdx;

    SavedFromState->rbp     = Ist1State->rbp;
    SavedFromState->rsi     = Ist1State->rsi;
    SavedFromState->rdi     = Ist1State->rdi;
    SavedFromState->r8      = Ist1State->r8;

    SavedFromState->r9      = Ist1State->r9;
    SavedFromState->r10     = Ist1State->r10;
    SavedFromState->r11     = Ist1State->r11;
    SavedFromState->r12     = Ist1State->r12;

    SavedFromState->r13     = Ist1State->r13;
    SavedFromState->r14     = Ist1State->r14;
    SavedFromState->r15     = Ist1State->r15;

    SavedFromState->rip     = Ist1State->rip;
    SavedFromState->cs      = Ist1State->cs;
    SavedFromState->rflags  = Ist1State->rflags;
    SavedFromState->rsp     = Ist1State->rsp;

    //Change To New State
    Ist1State->rax          = SavedToState->rax;
    Ist1State->rbx          = SavedToState->rbx;
    Ist1State->rcx          = SavedToState->rcx;
    Ist1State->rdx          = SavedToState->rdx;

    Ist1State->rbp          = SavedToState->rbp;
    Ist1State->rsi          = SavedToState->rsi;
    Ist1State->rdi          = SavedToState->rdi;
    Ist1State->r8           = SavedToState->r8;

    Ist1State->r9           = SavedToState->r9;
    Ist1State->r10          = SavedToState->r10;
    Ist1State->r11          = SavedToState->r11;
    Ist1State->r12          = SavedToState->r12;

    Ist1State->r13          = SavedToState->r13;
    Ist1State->r14          = SavedToState->r14;
    Ist1State->r15          = SavedToState->r15;

    Ist1State->rip          = SavedToState->rip;
    Ist1State->cs           = SavedToState->cs;
    Ist1State->rflags       = SavedToState->rflags;
    Ist1State->rsp          = SavedToState->rsp;
    
}

void LouKeSwitchToTask(
    UINT64                  CpuCurrentState,
    PGENERIC_THREAD_DATA    ThreadFrom,
    PGENERIC_THREAD_DATA    ThreadTo
){
    if(ThreadFrom == ThreadTo){
        return;
    }
    SaveEverything(ThreadFrom->ContextStorage);    
    if((ThreadFrom->State != THREAD_BLOCKED) && (ThreadFrom->State != THREAD_TERMINATED)){
        ThreadFrom->State = THREAD_READY;
    }

    if(ThreadTo->Cs == 0x08){
        
        KernelContextSwitch(
            &ThreadFrom->SavedState,
            &ThreadTo->SavedState,
            (CPUKernelContext*)(UINT8*)CpuCurrentState
        );

    }else{

        LouPrint("HERE User\n");
        while(1);
    }
    //CpuCurrentState

    ThreadFrom->Resting = true;
    ThreadTo->Resting = false;

    ThreadTo->State = THREAD_RUNNING;
    SetTEB((UINT64)&ThreadTo->Teb);
    RestoreEverything(ThreadTo->ContextStorage);    

}

static GENERIC_THREAD_DATA MasterThreadList = {0};

void DebugThreadContext(){
    PGENERIC_THREAD_DATA TmpThreadHandle = &MasterThreadList;
    while(TmpThreadHandle->Peers.NextHeader){
        TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
        LouPrint("TmpThreadHandle->ThreadID         :%h\n", TmpThreadHandle->ThreadID);
        LouPrint("TmpThreadHandle->ContextStorage   :%h\n", TmpThreadHandle->ContextStorage);
        LouPrint("TmpThreadHandle->InterruptStorage :%h\n", TmpThreadHandle->InterruptStorage);
    }
}

static UINT64 AllocateThreadID(){
    UINT64 Result = 1;
    BOOL FoundID = false;
    while(!FoundID){
        FoundID = true;
        PGENERIC_THREAD_DATA TmpThreadHandle = &MasterThreadList;
        while(TmpThreadHandle->Peers.NextHeader){
            TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
            if(Result == TmpThreadHandle->ThreadID){
                Result++;
                FoundID = false;
                break;
            }
        }
    }
    return Result;
}

static PGENERIC_THREAD_DATA AllocateThreadHandle(){
    PGENERIC_THREAD_DATA TmpThreadHandle = &MasterThreadList;
    while(TmpThreadHandle->Peers.NextHeader){
        TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
    }
    TmpThreadHandle->Peers.NextHeader = (PListHeader)LouKeMallocType(GENERIC_THREAD_DATA, KERNEL_GENERIC_MEMORY);
    TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
    return TmpThreadHandle;
}

UNUSED 
static void DeallocateThreadHandle(PGENERIC_THREAD_DATA Thread){
    PGENERIC_THREAD_DATA TmpThreadHandle = &MasterThreadList;
    while(TmpThreadHandle->Peers.NextHeader){
        if((PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader == Thread){
            TmpThreadHandle->Peers.NextHeader = ((PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader)->Peers.NextHeader;
            LouKeFree(Thread);
            return;
        }
        TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
    }
}

KERNEL_IMPORT uint64_t AllocateSaveContext();

LOUSTATUS LouKeTsmCreateThreadHandle(
    PGENERIC_THREAD_DATA*   OutHandle,    
    PGENERIC_PROCESS_DATA   Process,
    PVOID                   CtxEntry,
    PVOID                   CtxFunction,
    PVOID                   CtxParams,
    UINT8                   ThreadPriority,
    UINT64                  StackSize,
    UINT64                  TimeSliceMs,
    UINT8                   CodeSegment,
    UINT8                   StackSegment,
    INSTRUCTION_MODE        InstructionMode,
    PTIME_T                 StartTime,
    UINT8*                  AfinityBitmap
){

    //check for certain required parameters/values
    if(
        (!OutHandle)    || (!StackSize) || 
        (!CtxEntry)     || (!CodeSegment) || 
        (!StackSegment) || (!Process)
    ){
        LouPrint("LouKeTsmCreateThreadHandle(): Invalid Parameters\n");
        return STATUS_INVALID_PARAMETER;
    }
    bool User = ((CodeSegment & 0b11) == 3); 

    //alocate thread handler
    PGENERIC_THREAD_DATA NewThreadHandle = AllocateThreadHandle();
    //place output
    *OutHandle = NewThreadHandle;
    //initialize contexts for accelerated CPU cmponents
    NewThreadHandle->ContextStorage = (UINT64)AllocateSaveContext();
    NewThreadHandle->InterruptStorage = (UINT64)AllocateSaveContext();

    //Allocate a new stack
    NewThreadHandle->StackBase = (UINT64)LouKeMallocEx(StackSize, 64, (User ? USER_GENERIC_MEMORY : KERNEL_GENERIC_MEMORY));
    NewThreadHandle->StackTop = NewThreadHandle->StackBase + StackSize;
    //thread prioirties are backwards 0 being the highest +x being lowest 
    NewThreadHandle->ThreadPriority = (THREAD_PRIORITY_RINGS - 1) - ThreadPriority;

    NewThreadHandle->Process = Process;
    //allocate thread ID
    NewThreadHandle->ThreadID = AllocateThreadID();
    NewThreadHandle->TotalMsSlice = TimeSliceMs;
    NewThreadHandle->Cs = CodeSegment;
    NewThreadHandle->Ss = StackSegment;
    //tells the VM Manager what instructions set to operate in    
    NewThreadHandle->InstructionMode = InstructionMode;

    if(StartTime){ //if delayed or defered work this is used for blocking/unblocking
        memcpy(&NewThreadHandle->BlockTimeout, StartTime, sizeof(TIME_T));
        NewThreadHandle->State = THREAD_BLOCKED; //thread state is managed by schedualer
    }else{
        NewThreadHandle->State = THREAD_READY; //thread state is managed by schedualer
    }

    //Afinity mask tells the schedualer 
    //what core/s the thread may run on
    if(AfinityBitmap){
        NewThreadHandle->AfinityBitmap = AfinityBitmap;
    }else{
        NewThreadHandle->AfinityBitmap = LouKeMallocArray(UINT8, PROCESSOR_BITMAP_LENGTH, KERNEL_GENERIC_MEMORY);
        for(size_t i = 0; i < GetNPROC(); i++){
            MARK_PROCESSOR_AFFILIATED(NewThreadHandle->AfinityBitmap, i);
        }
    }

    NewThreadHandle->SavedState.rip = (UINT64)CtxEntry;                 //worker subsystem liftoff stub     : iretq Location
    NewThreadHandle->SavedState.rcx = (UINT64)CtxFunction;              //requested work                    : MSVC PARAM 1
    NewThreadHandle->SavedState.rdx = (UINT64)CtxParams;                //work params                       : MSVC PARAM 2
    NewThreadHandle->SavedState.r8  = (UINT64)NewThreadHandle;          //Identity for worker subsystem     : MSVC PARAM 3
    NewThreadHandle->SavedState.rsp = NewThreadHandle->StackTop;        //stack pointer
    NewThreadHandle->SavedState.rbp = NewThreadHandle->SavedState.rsp;  //stack base

    NewThreadHandle->SavedState.cs = CodeSegment;       //Desired Code Segment
    NewThreadHandle->SavedState.ss = StackSegment;      //Desired Stack segment
    NewThreadHandle->SavedState.rflags = 0x202;         //interrupts enabled no operation normal

    LouKeGetTime(&NewThreadHandle->ThreadStart); //time of creation for thread object manager
    
    return STATUS_SUCCESS;
}

KERNEL_IMPORT PGENERIC_THREAD_DATA LouKeThreadIdToThreadData(UINT64 ThreadID){
    if(ThreadID == 0){
        return 0x00;
    }
    PGENERIC_THREAD_DATA TmpThreadHandle = &MasterThreadList;
    while(TmpThreadHandle->Peers.NextHeader){
        TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
        if(TmpThreadHandle->ThreadID == ThreadID){
            return TmpThreadHandle;
        }
    }
    return 0x00;
}

KERNEL_IMPORT void DeAllocateSaveContext(uint64_t Context);

void LouKeTsmDestroyThreadHandle(
    PGENERIC_THREAD_DATA Thread
){
    LouKeFree(Thread->AfinityBitmap);
    LouKeFree((PVOID)Thread->StackBase);
    DeAllocateSaveContext(Thread->ContextStorage);
    DeAllocateSaveContext(Thread->InterruptStorage);
    DeallocateThreadHandle(Thread);
}

DWORD 
ThreadManagerIdleFallback(
    PVOID   Params
){
    while(1){
        //LouKeYeildExecution();
    }
    return -1;
}

PGENERIC_THREAD_DATA TsmThreadSchedualManagerObject::TsmGetNext(PGENERIC_THREAD_DATA CurrentThread, bool ProcessSwitch){

    UINT64 CurrentRing = this->LoadDistributer.CurrentIndexor;
    CurrentThread->CurrentMsSlice = 0;
    
    UINT64 NextRing;
    PTHREAD_RING CurrentThreadRing;
    PTHREAD_RING TmpThreadRing;
    while(1){
        NextRing = EulerCurveIndexor(&this->LoadDistributer);
        CurrentThreadRing = this->Threads[NextRing];
        if(CurrentThreadRing){
            if(CurrentThreadRing->Peers.NextHeader){
                TmpThreadRing = (PTHREAD_RING)CurrentThreadRing->Peers.NextHeader;
                while(TmpThreadRing != CurrentThreadRing){
                    if(TmpThreadRing->ThreadData->State == THREAD_BLOCKED){
                        if(
                            (!LouKeIsTimeoutNull(&TmpThreadRing->ThreadData->BlockTimeout)) &&
                            (LouKeDidTimeoutExpire(&TmpThreadRing->ThreadData->BlockTimeout))
                        ){
                            memset(&TmpThreadRing->ThreadData->BlockTimeout, 0, sizeof(TIME_T));
                            TmpThreadRing->ThreadData->State = THREAD_READY;
                        }
                    }
                    if(TmpThreadRing->ThreadData->State == THREAD_READY){
                        this->Threads[NextRing] = TmpThreadRing;
                        return TmpThreadRing->ThreadData;
                    }
                    TmpThreadRing = (PTHREAD_RING)TmpThreadRing->Peers.NextHeader;
                }
            }
            if(CurrentThreadRing->ThreadData->State == THREAD_READY){
                return CurrentThreadRing->ThreadData;
            }    
        }
        if(NextRing == CurrentRing){
            //if no tasks are ready just idle
            break;
        }        
    }

    if((CurrentThread->State == THREAD_RUNNING) && (!ProcessSwitch)){
        return CurrentThread;
    }

    return this->IdleTask;
}

PGENERIC_THREAD_DATA TsmThreadSchedualManagerObject::TsmYeild(PGENERIC_THREAD_DATA CurrentThread, bool ProcessSwitch){
    return TsmGetNext(CurrentThread, ProcessSwitch);
}


PGENERIC_THREAD_DATA TsmThreadSchedualManagerObject::TsmSchedual(PGENERIC_THREAD_DATA CurrentThread, bool ProcessSwitch){
    /*if(
        (CurrentThread->CurrentMsSlice < CurrentThread->TotalMsSlice) &&
        (!ProcessSwitch) &&
        (CurrentThread->State == THREAD_RUNNING)
    ){
        CurrentThread->CurrentMsSlice += 10;
        return CurrentThread;
    }*/

    return TsmGetNext(CurrentThread, ProcessSwitch);
}


LOUSTATUS TsmThreadSchedualManagerObject::TsmInitializeSchedualerObject(
    UINT64                  ProcessorID, 
    PGENERIC_PROCESS_DATA   ProcessData,
    UINT64                  DistibutionLimitor,
    UINT64                  DistributerIncrementation
){
    LOUSTATUS Status;
    LouPrint("TsmInitializeSchedualerObject()\n");

    this->ProcessorID = ProcessorID;
    
    Status = CreateShecdualerObject(
        &this->LoadDistributer,
        DistibutionLimitor,
        DistributerIncrementation
    );
    
    if(Status != STATUS_SUCCESS){
        LouPrint("TSM ERROR:Unable To Initialize Schedualer Object\n");
        return Status;
    }

    UINT8* AfinityBitmap = LouKeMallocArray(UINT8, PROCESSOR_BITMAP_LENGTH, KERNEL_GENERIC_MEMORY);

    MARK_PROCESSOR_AFFILIATED(AfinityBitmap, ProcessorID);

    Status = LouKeTsmCreateThreadHandle(
        &this->IdleTask,
        ProcessData,
        (PVOID)KernelThreadStub,
        (PVOID)ThreadManagerIdleFallback,
        0,
        0,
        2048,
        20,
        0x08,
        0x10,
        LONG_MODE,
        0x00,
        AfinityBitmap
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("TSM ERROR:Unable To Initialize Process Idle\n");
        return Status;
    }

    LouPrint("TsmInitializeSchedualerObject() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

static spinlock_t AsignLock = {0};

void TsmThreadSchedualManagerObject::TsmAsignThreadToSchedual(PGENERIC_THREAD_DATA Thread){
    LouKIRQL Irql;
    PTHREAD_RING NewThreadRing = LouKeTsmCreateThreadRing(Thread);
    LouKeAcquireSpinLock(&AsignLock, &Irql);
    LouKeLockProcessManager();
    PTHREAD_RING TmpThreadRing = this->Threads[Thread->ThreadPriority];
    PTHREAD_RING CurrentThread = TmpThreadRing;

    if(!TmpThreadRing){
        this->Threads[Thread->ThreadPriority] = NewThreadRing;
        NewThreadRing->Peers.NextHeader = (PListHeader)NewThreadRing;
        NewThreadRing->Peers.LastHeader = (PListHeader)NewThreadRing;
        goto _ASERT_FINISHED;
    }

    while(TmpThreadRing->Peers.NextHeader != (PListHeader)CurrentThread){
        TmpThreadRing = (PTHREAD_RING)TmpThreadRing->Peers.NextHeader;
    }

    CurrentThread->Peers.LastHeader = (PListHeader)NewThreadRing;
    NewThreadRing->Peers.NextHeader = (PListHeader)CurrentThread;
    TmpThreadRing->Peers.NextHeader = (PListHeader)NewThreadRing;
    NewThreadRing->Peers.LastHeader = (PListHeader)TmpThreadRing;

    _ASERT_FINISHED:
    LouKeUnlockProcessManager();
    LouKeReleaseSpinLock(&AsignLock, &Irql);
}

static spinlock_t DeasignLock = {0};

void TsmThreadSchedualManagerObject::TsmDeasignThreadFromSchedual(PGENERIC_THREAD_DATA Thread){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&DeasignLock, &Irql);
    LouKeLockProcessManager();

    UINT64 Limitors = this->LoadDistributer.TotalLimiters;

    for(UINT64 i = 0; i < Limitors; i++){
        if(!this->Threads[i]){
            continue;
        }

        PTHREAD_RING CurrentThreadRing = this->Threads[i];
        PTHREAD_RING TmpThreadRing = (PTHREAD_RING)CurrentThreadRing;
        PTHREAD_RING TailRing = (PTHREAD_RING)TmpThreadRing->Peers.LastHeader;
        if(CurrentThreadRing->ThreadData == Thread){
            if((PTHREAD_RING)CurrentThreadRing->Peers.NextHeader == CurrentThreadRing){
                this->Threads[i] = 0x00;
            }else{
                this->Threads[i] = (PTHREAD_RING)CurrentThreadRing->Peers.NextHeader;
                TailRing->Peers.NextHeader = CurrentThreadRing->Peers.NextHeader;
                TmpThreadRing = (PTHREAD_RING)TailRing->Peers.NextHeader;
                TmpThreadRing->Peers.LastHeader = (PListHeader)TailRing;
            }
            LouKeFree(CurrentThreadRing);
            goto _DEASERT_FINISHED;
        }
        
        TmpThreadRing = (PTHREAD_RING)CurrentThreadRing->Peers.NextHeader;
        TailRing = (PTHREAD_RING)CurrentThreadRing;

        while(TmpThreadRing != CurrentThreadRing){
            if(TmpThreadRing->ThreadData == Thread){
                CurrentThreadRing = TmpThreadRing;
                TailRing->Peers.NextHeader = TmpThreadRing->Peers.NextHeader;
                TmpThreadRing = (PTHREAD_RING)TmpThreadRing->Peers.NextHeader;
                TmpThreadRing->Peers.LastHeader = (PListHeader)TailRing;
                LouKeFree(CurrentThreadRing);
                goto _DEASERT_FINISHED;
            }            
            TailRing = TmpThreadRing;
            TmpThreadRing = (PTHREAD_RING)TmpThreadRing->Peers.NextHeader;
        }

    }

    _DEASERT_FINISHED:
    LouKeUnlockProcessManager();
    LouKeReleaseSpinLock(&DeasignLock, &Irql);
}



static spinlock_t SleepLock = {0};

KERNEL_IMPORT void LouKeThreadSleep(SIZE Ms){
    uint64_t ThreadID = LouKeGetThreadIdentification();
    if(!ThreadID){
        LouPrint("LouKeThreadSleep() ERROR: Thread Non Existent\n");
        return;
    }
    LouKIRQL Irql;
    TIME_T Time;
    PGENERIC_THREAD_DATA ThreadData = LouKeThreadIdToThreadData(ThreadID);
    LouKeAcquireSpinLock(&SleepLock, &Irql);
    LouKeLockProcessManager();
    memset(&ThreadData->BlockTimeout, 0, sizeof(TIME_T));
    ThreadData->State = THREAD_BLOCKED;
    LouKeGetFutureTime(&Time, Ms);
    memcpy(&ThreadData->BlockTimeout, &Time, sizeof(TIME_T));
    LouKeUnlockProcessManager();
    LouKeReleaseSpinLock(&SleepLock, &Irql);
    asm("INT $32");
}

static spinlock_t YeildLock = {0};


KERNEL_IMPORT
void 
LouKeYeildExecution(){
    PGENERIC_THREAD_DATA ThreadData = LouKeGetCurrentThreadData();
    if(LouKeGetReferenceCount(&ThreadData->EFBY)){
        LouKeReleaseReference(&ThreadData->EFBY);
        return;
    }
    LouKIRQL Irql;
    TIME_T Time;
    LouKeAcquireSpinLock(&YeildLock, &Irql);
    LouKeLockProcessManager();
    memset(&ThreadData->BlockTimeout, 0, sizeof(TIME_T));
    ThreadData->State = THREAD_BLOCKED;
    LouKeGetFutureTime(&Time, ThreadData->TotalMsSlice);
    memcpy(&ThreadData->BlockTimeout, &Time, sizeof(TIME_T));
    LouKeUnlockProcessManager();
    LouKeReleaseSpinLock(&YeildLock, &Irql);
    asm("INT $32");
}

static spinlock_t UnblockLock = {0};

KERNEL_IMPORT void LouKeUnblockThread(UINT64 ThreadID){
    LouKIRQL Irql;
    PGENERIC_THREAD_DATA ThreadData = LouKeThreadIdToThreadData(ThreadID);
    LouKeAcquireSpinLock(&UnblockLock, &Irql);
    LouKeLockProcessManager();
    LouKeAcquireReference(&ThreadData->EFBY);
    memset(&ThreadData->BlockTimeout, 0, sizeof(TIME_T));
    ThreadData->State = THREAD_READY;
    LouKeUnlockProcessManager();
    LouKeReleaseSpinLock(&UnblockLock, &Irql);
}


LOUDDK_API_ENTRY DWORD LouKeThreadManagerDemon(PVOID Params){
    LouPrint("Thread Manager Demon Started\n");
    UNUSED INTEGER Processors = GetNPROC();

    while(1){
        //PGENERIC_THREAD_DATA TmpThreadHandle = &MasterThreadList;
        //PGENERIC_THREAD_DATA TailThread = 0;
        //while(TmpThreadHandle->Peers.NextHeader){
        //    TailThread = TmpThreadHandle;
        //    TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
        //    if((TmpThreadHandle->State == THREAD_TERMINATED) && (TmpThreadHandle->Resting)){
        //       TailThread->Peers.NextHeader = TmpThreadHandle->Peers.NextHeader;
        //        ((PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader)->Peers.LastHeader = (PListHeader)TailThread;
        //        PGENERIC_PROCESS_DATA ProcessData = TmpThreadHandle->Process;         
        //        for(INTEGER i = 0 ; i < Processors; i++){
        //            if(IS_PROCESSOR_AFFILIATED(TmpThreadHandle->AfinityBitmap, i)){
        //                ProcessData->ThreadObjects[i].TsmDeasignThreadFromSchedual(TmpThreadHandle);
        //            }
        //        }
        //        LouPrint("Thread:%d Has Retired\n", TmpThreadHandle->ThreadID);
        //        LouKeTsmDestroyThreadHandle(TmpThreadHandle);
        //    }
        //}
        //LouKeYeildExecution();
    }
    return -1;
}