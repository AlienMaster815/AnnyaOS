#include <LouDDK.h>
#include "ProcessPrivate.h"


PGENERIC_THREAD_DATA LouKeThreadIdToThreadData(UINT64 ThreadID);

static void KernelThreadStub(DWORD(*Work)(PVOID), PVOID Param, PGENERIC_THREAD_DATA Thread){
    DWORD Result = 0;
    LouPrint("Thread:%d Started\n", Thread->ThreadID);
    Result = Work(Param);
    LouPrint("Thread:%d Exited With Code:%h\n", Thread->ThreadID, Result);
    while(1){

    }
}

LOUDDK_API_ENTRY
semaphore_t* LouKeCreateSemaphore(int initial, int limit){
    semaphore_t* NewSemaphore = (semaphore_t*)LouKeMallocType(semaphore_t, KERNEL_GENERIC_MEMORY);
    SemaphoreInitialize(NewSemaphore, initial, limit);
    return NewSemaphore;
}

UNUSED static void CopyStack(UINT8* To, UINT8* From){
    for(uint8_t i = 0; i < 160; i++){
        To[i] = From[i];
    }
}

static PTHREAD_RING LouKeTsmCreateThreadRing(PGENERIC_THREAD_DATA ThreadHandle){
    PTHREAD_RING NewThreadRing = LouKeMallocType(THREAD_RING, KERNEL_GENERIC_MEMORY);
    NewThreadRing->ThreadData = ThreadHandle;
    return NewThreadRing;
}

UNUSED static void LouKeTsmDestroyThreadRing(PTHREAD_RING ThreadRing){
    LouKeFree(ThreadRing);
}

void LouKeSwitchToTask(
    UINT64                  CpuCurrentState,
    PGENERIC_THREAD_DATA    ThreadFrom,
    PGENERIC_THREAD_DATA    ThreadTo
){

    CopyStack((UINT8*)&ThreadFrom->SavedState, (UINT8*)CpuCurrentState);
    SaveEverything(ThreadFrom->ContextStorage);    
    if((ThreadFrom->State != THREAD_BLOCKED) && (ThreadFrom->State != THREAD_TERMINATED)){
        ThreadFrom->State = THREAD_READY;
    }
    ThreadTo->State = THREAD_RUNNING;
    RestoreEverything(ThreadTo->ContextStorage);
    SetTEB((UINT64)&ThreadTo->Teb);
    CopyStack((UINT8*)CpuCurrentState, (UINT8*)&ThreadTo->SavedState);
}

static GENERIC_THREAD_DATA MasterThreadList = {0};
static mutex_t ThreadListLock = {0};

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
    MutexLock(&ThreadListLock);
    while(TmpThreadHandle->Peers.NextHeader){
        TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
    }
    TmpThreadHandle->Peers.NextHeader = (PListHeader)LouKeMallocType(GENERIC_THREAD_DATA, KERNEL_GENERIC_MEMORY);
    TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
    MutexUnlock(&ThreadListLock);
    return TmpThreadHandle;
}

UNUSED 
static void DeallocateThreadHandle(PGENERIC_THREAD_DATA Thread){
    PGENERIC_THREAD_DATA TmpThreadHandle = &MasterThreadList;
    MutexLock(&ThreadListLock);
    while(TmpThreadHandle->Peers.NextHeader){
        if((PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader == Thread){
            TmpThreadHandle->Peers.NextHeader = ((PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader)->Peers.NextHeader;
            LouKeFree(Thread);
            MutexUnlock(&ThreadListLock);
            return;
        }
        TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
    }
    MutexUnlock(&ThreadListLock);
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
    //alocate thread handler
    PGENERIC_THREAD_DATA NewThreadHandle = AllocateThreadHandle();
    //place output
    *OutHandle = NewThreadHandle;
    //initialize contexts for accelerated CPU cmponents
    NewThreadHandle->ContextStorage = (UINT64)AllocateSaveContext();
    NewThreadHandle->InterruptStorage = (UINT64)AllocateSaveContext();



    //Allocate a new stack
    NewThreadHandle->StackBase = (UINT64)LouKeMallocEx(StackSize, 64, KERNEL_GENERIC_MEMORY);
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

PGENERIC_THREAD_DATA LouKeThreadIdToThreadData(UINT64 ThreadID){
    PGENERIC_THREAD_DATA TmpThreadHandle = &MasterThreadList;
    MutexLock(&ThreadListLock);
    while(TmpThreadHandle->Peers.NextHeader){
        TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
        if(TmpThreadHandle->ThreadID == ThreadID){
            MutexUnlock(&ThreadListLock);
            return TmpThreadHandle;
        }
    }
    MutexUnlock(&ThreadListLock);
    return 0x00;
}

void LouKeTsmDestroyThreadHandle(
    PGENERIC_THREAD_DATA Thread
){
    LouKeFree(Thread->AfinityBitmap);
    LouKeFree((PVOID)Thread->StackBase);
    LouGeneralFreeMemory((PVOID)Thread->ContextStorage);
    LouGeneralFreeMemory((PVOID)Thread->InterruptStorage);
    DeallocateThreadHandle(Thread);
}

DWORD 
ThreadManagerIdleFallback(
    PVOID   Params
){
    while(1){
        
    }
    return -1;
}

PGENERIC_THREAD_DATA TsmThreadSchedualManagerObject::TsmYeild(){
    UINT64 CurrentRing = this->LoadDistributer.CurrentIndexor;
    this->Threads[CurrentRing]->ThreadData->CurrentMsSlice = 0;
    
    UINT64 NextRing = EulerCurveIndexor(&this->LoadDistributer);
    PTHREAD_RING CurrentThreadRing;
    PTHREAD_RING TmpThreadRing;
    while(1){
        CurrentThreadRing = this->Threads[NextRing];
        if(CurrentThreadRing){
            if(CurrentThreadRing->Peers.NextHeader){
                TmpThreadRing = (PTHREAD_RING)CurrentThreadRing->Peers.NextHeader;
                while(TmpThreadRing != CurrentThreadRing){
                    if(
                        (!LouKeIsTimeoutNull(&TmpThreadRing->ThreadData->BlockTimeout)) &&
                        (LouKeDidTimeoutExpire(&TmpThreadRing->ThreadData->BlockTimeout))
                    ){
                        TmpThreadRing->ThreadData->State = THREAD_READY;
                    }
                    if(TmpThreadRing->ThreadData->State == THREAD_READY){
                        CurrentThreadRing->ThreadData->State = THREAD_READY;
                        return TmpThreadRing->ThreadData;
                    }
                    TmpThreadRing = (PTHREAD_RING)CurrentThreadRing->Peers.NextHeader;
                }
                if(CurrentThreadRing->ThreadData->State == THREAD_READY){
                    return CurrentThreadRing->ThreadData;
                }
            }
        }
        NextRing = EulerCurveIndexor(&this->LoadDistributer);
        if(NextRing == CurrentRing){
            //if no tasks are ready just idle
            break;
        }        
    }

    return this->IdleTask;
}


PGENERIC_THREAD_DATA TsmThreadSchedualManagerObject::TsmSchedual(){
    UINT64 CurrentRing = this->LoadDistributer.CurrentIndexor;
    if(this->Threads[CurrentRing]->ThreadData->CurrentMsSlice < this->Threads[CurrentRing]->ThreadData->TotalMsSlice){
        this->Threads[CurrentRing]->ThreadData->CurrentMsSlice += 10;
        return this->Threads[CurrentRing]->ThreadData;
    }
    this->Threads[CurrentRing]->ThreadData->CurrentMsSlice = 0;
    
    UINT64 NextRing = EulerCurveIndexor(&this->LoadDistributer);
    PTHREAD_RING CurrentThreadRing;
    PTHREAD_RING TmpThreadRing;
    while(1){
        CurrentThreadRing = this->Threads[NextRing];
        if(CurrentThreadRing){
            if(CurrentThreadRing->Peers.NextHeader){
                TmpThreadRing = (PTHREAD_RING)CurrentThreadRing->Peers.NextHeader;
                while(TmpThreadRing != CurrentThreadRing){
                    if(
                        (!LouKeIsTimeoutNull(&TmpThreadRing->ThreadData->BlockTimeout)) &&
                        (LouKeDidTimeoutExpire(&TmpThreadRing->ThreadData->BlockTimeout))
                    ){
                        TmpThreadRing->ThreadData->State = THREAD_READY;
                    }
                    if(TmpThreadRing->ThreadData->State == THREAD_READY){
                        CurrentThreadRing->ThreadData->State = THREAD_READY;
                        return TmpThreadRing->ThreadData;
                    }
                    TmpThreadRing = (PTHREAD_RING)CurrentThreadRing->Peers.NextHeader;
                }
                if(CurrentThreadRing->ThreadData->State == THREAD_READY){
                    return CurrentThreadRing->ThreadData;
                }
            }
        }
        NextRing = EulerCurveIndexor(&this->LoadDistributer);
        if(NextRing == CurrentRing){
            //if no tasks are ready just idle
            break;
        }        
    }

    return this->IdleTask;
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

    Status = LouKeTsmCreateThreadHandle(
        &this->IdleTask,
        ProcessData,
        (PVOID)KernelThreadStub,
        (PVOID)ThreadManagerIdleFallback,
        0,
        0,
        512,
        20,
        0x08,
        0x10,
        LONG_MODE,
        0x00,
        0x00
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("TSM ERROR:Unable To Initialize Process Idle\n");
        return Status;
    }

    LouPrint("TsmInitializeSchedualerObject() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

void TsmThreadSchedualManagerObject::TsmAsignThreadToSchedual(PGENERIC_THREAD_DATA Thread){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&this->LockOutTagOut, &Irql);
    PTHREAD_RING NewThreadRing = LouKeTsmCreateThreadRing(Thread);
    PTHREAD_RING TmpThreadRing = this->Threads[Thread->ThreadPriority];
    PTHREAD_RING CurrentThread = TmpThreadRing;

    if(!TmpThreadRing){
        this->Threads[Thread->ThreadPriority] = NewThreadRing;
        NewThreadRing->Peers.NextHeader = (PListHeader)NewThreadRing;
        NewThreadRing->Peers.LastHeader = (PListHeader)NewThreadRing;
        goto _THREAD_ASIGNMENT_DONE;
    }

    while(TmpThreadRing->Peers.NextHeader != (PListHeader)CurrentThread){
        TmpThreadRing = (PTHREAD_RING)TmpThreadRing->Peers.NextHeader;
    }

    CurrentThread->Peers.LastHeader = (PListHeader)NewThreadRing;
    NewThreadRing->Peers.NextHeader = (PListHeader)CurrentThread;
    TmpThreadRing->Peers.NextHeader = (PListHeader)NewThreadRing;

    _THREAD_ASIGNMENT_DONE:
    LouKeReleaseSpinLock(&this->LockOutTagOut, &Irql);
}

void TsmThreadSchedualManagerObject::TsmDeasignThreadFromSchedual(PGENERIC_THREAD_DATA Thread, bool SelfIdentifiing){


    LouPrint("TsmDeasignThreadFromSchedual()\n");
    while(1);
}

UINT64 TsmThreadSchedualManagerObject::TsmGetCurrentThreadID(){


    LouPrint("TsmGetCurrentThreadID()\n");
    while(1);
    return 0x00;
}

UINT64 TsmThreadSchedualManagerObject::TsmGetCurrentInterruptStorage(){
    

    LouPrint("TsmGetCurrentInterruptStorage()\n");
    while(1);
    return 0x00;
}

UINT64 TsmThreadSchedualManagerObject::TsmGetCurrentContextStorage(){
    

    LouPrint("TsmGetCurrentContextStorage()\n");
    while(1);
    return 0x00;
}

static spinlock_t SleepLock = {0};



KERNEL_IMPORT void LouKeThreadSleep(SIZE Ms){
    uint64_t ThreadID = LouKeGetThreadIdentification();
    if(!ThreadID){
        LouPrint("LouKeThreadSleep() ERROR: Thread Non Existent\n");
        return;
    }
    PGENERIC_THREAD_DATA ThreadData = LouKeThreadIdToThreadData(ThreadID);
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&SleepLock, &Irql);
    TIME_T Time;
    LouKeGetFutureTime(&Time, Ms);
    memcpy(&ThreadData->BlockTimeout, &Time, sizeof(TIME_T));
    ThreadData->State = THREAD_BLOCKED;
    LouKeReleaseSpinLock(&SleepLock, &Irql);
    asm("INT $200");
    LouPrint("LouKeThreadSleep:%d\n", Ms);
    while(1);
}