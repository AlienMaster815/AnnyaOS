#include <LouDDK.h>
#include "ProcessPrivate.h"

LOUDDK_API_ENTRY
PGENERIC_THREAD_DATA
LouKeGetCurrentThreadData();
KERNEL_IMPORT PGENERIC_THREAD_DATA LouKeThreadIdToThreadData(UINT64 ThreadID);
LOUDDK_API_ENTRY VOID LouKeDestroyThread(PVOID ThreadHandle);

KERNEL_IMPORT UINT64 GetRFLAGS();
void LouKeLockProcManager(LouKIRQL* Irql);
void LouKeUnlockProcManager(LouKIRQL* Irql);

void KernelThreadStub(DWORD(*Work)(PVOID), PVOID Param, PGENERIC_THREAD_DATA Thread){
    DWORD Result = 0;
    LouPrint("Thread:%d Has Started\n", Thread->ThreadID);
    Result = Work(Param);
    LouPrint("Thread:%d Exited With Code:%h\n", Thread->ThreadID, Result);
    LouKeDestroyThread(Thread);
    while(1){
        asm("hlt");
    }
}

DWORD 
ThreadManagerIdleFallback(
    PVOID   Params
){
    while(1){
        asm("hlt");
    }
    return -1;
}

PGENERIC_THREAD_DATA* ProcessorIdleThreads = 0;

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

void ContextSwitchFrom(
    CPUContext*         SavedFromState,
    CPUContext*         IstState
){
    //Save Current State
    SavedFromState->rax     = IstState->rax;
    SavedFromState->rbx     = IstState->rbx;
    SavedFromState->rcx     = IstState->rcx;
    SavedFromState->rdx     = IstState->rdx;

    SavedFromState->rbp     = IstState->rbp;
    SavedFromState->rsi     = IstState->rsi;
    SavedFromState->rdi     = IstState->rdi;

    SavedFromState->r8      = IstState->r8;
    SavedFromState->r9      = IstState->r9;
    SavedFromState->r10     = IstState->r10;
    SavedFromState->r11     = IstState->r11;
    SavedFromState->r12     = IstState->r12;
    SavedFromState->r13     = IstState->r13;
    SavedFromState->r14     = IstState->r14;
    SavedFromState->r15     = IstState->r15;

    SavedFromState->rip     = IstState->rip;
    SavedFromState->cs      = IstState->cs;
    SavedFromState->rflags  = IstState->rflags;
    SavedFromState->rsp     = IstState->rsp;
    SavedFromState->ss      = IstState->ss;
    
}


void ContextSwitchTo(
    CPUContext*         SavedToState,
    CPUContext*         IstState
){

    //Change To New State
    IstState->rax          = SavedToState->rax;
    IstState->rbx          = SavedToState->rbx;
    IstState->rcx          = SavedToState->rcx;
    IstState->rdx          = SavedToState->rdx;

    IstState->rbp          = SavedToState->rbp;
    IstState->rsi          = SavedToState->rsi;
    IstState->rdi          = SavedToState->rdi;
    IstState->r8           = SavedToState->r8;

    IstState->r9           = SavedToState->r9;
    IstState->r10          = SavedToState->r10;
    IstState->r11          = SavedToState->r11;
    IstState->r12          = SavedToState->r12;

    IstState->r13          = SavedToState->r13;
    IstState->r14          = SavedToState->r14;
    IstState->r15          = SavedToState->r15;

    IstState->rip          = SavedToState->rip;
    IstState->cs           = SavedToState->cs;
    IstState->rflags       = SavedToState->rflags;
    IstState->rsp          = SavedToState->rsp;
    IstState->ss           = SavedToState->ss;
}

UINT64 LouKeSwitchToTask(
    UINT64                  CpuCurrentState,
    PGENERIC_THREAD_DATA    ThreadFrom,
    PGENERIC_THREAD_DATA    ThreadTo
){
    if(ThreadFrom == ThreadTo){
        return CpuCurrentState;
    }

    SaveEverything(ThreadFrom->ContextStorage);    
    if((ThreadFrom->State != THREAD_BLOCKED) && (ThreadFrom->State != THREAD_TERMINATED)){
        ThreadFrom->State = THREAD_READY;
    }

    ContextSwitchFrom(
        &ThreadFrom->SavedState,
        (CPUContext*)CpuCurrentState
    );

    ContextSwitchTo(
        &ThreadTo->SavedState,
        (CPUContext*)CpuCurrentState
    );

    ThreadFrom->Resting = true;
    ThreadTo->Resting = false;

    ThreadTo->State = THREAD_RUNNING;

    SetTEB((UINT64)&ThreadTo->Teb);
    RestoreEverything(ThreadTo->ContextStorage);

    return CpuCurrentState;
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
    TmpThreadHandle->Peers.NextHeader = (PListHeader)LouKeMallocType(GENERIC_THREAD_DATA, USER_GENERIC_MEMORY);
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

LOUSTATUS LouKeTsmCreateThreadHandleNs(
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
        (!StackSegment) 
    ){
        LouPrint("LouKeTsmCreateThreadHandle(): Invalid Parameters\n");
        return STATUS_INVALID_PARAMETER;
    }
     
    UINT64 PageFlags;
    if((CodeSegment & 0b11) == 3){
        PageFlags = USER_GENERIC_MEMORY;
    } else{
        PageFlags = KERNEL_GENERIC_MEMORY;
    }
    //alocate thread handler
    PGENERIC_THREAD_DATA NewThreadHandle = AllocateThreadHandle();
    //place output
    *OutHandle = NewThreadHandle;
    //initialize contexts for accelerated CPU cmponents
    NewThreadHandle->ContextStorage = (UINT64)AllocateSaveContext();
    NewThreadHandle->InterruptStorage = (UINT64)AllocateSaveContext();

    //Allocate a new stack
    NewThreadHandle->StackBase = (UINT64)LouKeMallocEx(StackSize, 16, PageFlags);
    NewThreadHandle->StackTop = (NewThreadHandle->StackBase + (StackSize - 16)) & ~(16);
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
    NewThreadHandle->SavedState.rflags = 0x0202;        //interrupts enabled no operation normal

    LouKeGetTime(&NewThreadHandle->ThreadStart); //time of creation for thread object manager
    
    return STATUS_SUCCESS;
}

LOUSTATUS LouKeTsmInitializeIdleThreads(){
    LOUSTATUS Status = STATUS_SUCCESS;
    size_t ProcCount = GetNPROC();
    ProcessorIdleThreads = LouKeMallocArray(PGENERIC_THREAD_DATA, ProcCount, KERNEL_GENERIC_MEMORY);
    for(size_t i = 0 ; i < ProcCount; i++){
    
        UINT8* AfinityBitmap = LouKeMallocArray(UINT8, PROCESSOR_BITMAP_LENGTH, KERNEL_GENERIC_MEMORY);

        MARK_PROCESSOR_AFFILIATED(AfinityBitmap, i);

        Status = LouKeTsmCreateThreadHandleNs(
            &ProcessorIdleThreads[i],
            0x00,
            (PVOID)KernelThreadStub,
            (PVOID)ThreadManagerIdleFallback,
            0,
            0,
            2048,
            10,
            0x08,
            0x10,
            LONG_MODE,
            0x00,
            AfinityBitmap
        );
        
    }

    return Status;
}

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
    if(!Process){
        LouPrint("LouKeTsmCreateThreadHandle(): Invalid Parameters\n");
        return STATUS_INVALID_PARAMETER;
    }

    return LouKeTsmCreateThreadHandleNs(
        OutHandle,
        Process,
        CtxEntry,
        CtxFunction,
        CtxParams,
        ThreadPriority,
        StackSize,
        TimeSliceMs,
        CodeSegment,
        StackSegment,
        InstructionMode,
        StartTime,
        AfinityBitmap
    );

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



PGENERIC_THREAD_DATA TsmThreadSchedualManagerObject::TsmGetNext(PGENERIC_THREAD_DATA CurrentThread, bool ProcessSwitch){

    UNUSED UINT64 CurrentRing = this->LoadDistributer.CurrentIndexor;
    CurrentThread->CurrentMsSlice = 0;
    
    UNUSED UINT64 NextRing;
    UNUSED PTHREAD_RING CurrentThreadRing;
    UNUSED PTHREAD_RING TmpThreadRing;
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
            if(CurrentThreadRing->ThreadData->State == THREAD_BLOCKED){
                if(
                    (!LouKeIsTimeoutNull(&CurrentThreadRing->ThreadData->BlockTimeout)) &&
                    (LouKeDidTimeoutExpire(&CurrentThreadRing->ThreadData->BlockTimeout))
                ){
                    memset(&CurrentThreadRing->ThreadData->BlockTimeout, 0, sizeof(TIME_T));
                    CurrentThreadRing->ThreadData->State = THREAD_READY;
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

    this->IdleTask = ProcessorIdleThreads[ProcessorID];

    LouPrint("TsmInitializeSchedualerObject() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

void TsmThreadSchedualManagerObject::TsmAsignThreadToSchedual(PGENERIC_THREAD_DATA Thread){

    LouKIRQL Irql;
    PTHREAD_RING NewThreadRing = LouKeTsmCreateThreadRing(Thread);

    LouKeLockProcManager(&Irql);

    PTHREAD_RING TmpThreadRing = this->Threads[Thread->ThreadPriority];
    PTHREAD_RING CurrentThread = TmpThreadRing;

    if(!TmpThreadRing){

        NewThreadRing->Peers.NextHeader = (PListHeader)NewThreadRing;
        NewThreadRing->Peers.LastHeader = (PListHeader)NewThreadRing;
        this->Threads[Thread->ThreadPriority] = NewThreadRing;
        goto _ASERT_FINISHED;
    }

    while(TmpThreadRing->Peers.NextHeader != (PListHeader)CurrentThread){
        TmpThreadRing = (PTHREAD_RING)TmpThreadRing->Peers.NextHeader;
    }

    CurrentThread->Peers.LastHeader = (PListHeader)NewThreadRing;
    NewThreadRing->Peers.NextHeader = (PListHeader)CurrentThread;
    NewThreadRing->Peers.LastHeader = (PListHeader)TmpThreadRing;
    TmpThreadRing->Peers.NextHeader = (PListHeader)NewThreadRing;

    _ASERT_FINISHED:
    LouKeUnlockProcManager(&Irql);

}

void TsmThreadSchedualManagerObject::TsmDeasignThreadFromSchedual(PGENERIC_THREAD_DATA Thread){
    LouKIRQL Irql;

    PVOID FreeItem = 0x00;

    UINT64 Limitors = this->LoadDistributer.TotalLimiters;

    for(UINT64 i = 0; i < Limitors; i++){
        if(!this->Threads[i]){
            continue;
        }

        PTHREAD_RING CurrentThreadRing = this->Threads[i];
        PTHREAD_RING TmpThreadRing = (PTHREAD_RING)CurrentThreadRing;
        PTHREAD_RING TailRing = (PTHREAD_RING)TmpThreadRing->Peers.LastHeader;
        if(CurrentThreadRing->ThreadData == Thread){
            LouKeLockProcManager(&Irql);
            if((PTHREAD_RING)CurrentThreadRing->Peers.NextHeader == CurrentThreadRing){
                this->Threads[i] = 0x00;
            }else{
                this->Threads[i] = (PTHREAD_RING)CurrentThreadRing->Peers.NextHeader;
                TailRing->Peers.NextHeader = CurrentThreadRing->Peers.NextHeader;
                TmpThreadRing = (PTHREAD_RING)TailRing->Peers.NextHeader;
                TmpThreadRing->Peers.LastHeader = (PListHeader)TailRing;
            }
            //LouKeFree(CurrentThreadRing);
            FreeItem = (PVOID)CurrentThreadRing;
            goto _DEASERT_FINISHED;
        }
        
        TmpThreadRing = (PTHREAD_RING)CurrentThreadRing->Peers.NextHeader;
        TailRing = (PTHREAD_RING)CurrentThreadRing;

        while(TmpThreadRing != CurrentThreadRing){
            if(TmpThreadRing->ThreadData == Thread){
                LouKeLockProcManager(&Irql);
                CurrentThreadRing = TmpThreadRing;
                TailRing->Peers.NextHeader = TmpThreadRing->Peers.NextHeader;
                TmpThreadRing = (PTHREAD_RING)TmpThreadRing->Peers.NextHeader;
                TmpThreadRing->Peers.LastHeader = (PListHeader)TailRing;
                //LouKeFree(CurrentThreadRing);
                FreeItem = (PVOID)CurrentThreadRing;
                goto _DEASERT_FINISHED;
            }            
            TailRing = TmpThreadRing;
            TmpThreadRing = (PTHREAD_RING)TmpThreadRing->Peers.NextHeader;
        }

    }

    _DEASERT_FINISHED:
    LouKeUnlockProcManager(&Irql);
    if(FreeItem){
        LouKeFree(FreeItem);
    }
}

KERNEL_IMPORT void LouKeThreadSleep(SIZE Ms){
    uint64_t ThreadID = LouKeGetThreadIdentification();
    if(!ThreadID){
        LouPrint("LouKeThreadSleep() ERROR: Thread Non Existent\n");
        return;
    }
    LouKIRQL Irql;
    TIME_T Time;
    PGENERIC_THREAD_DATA ThreadData = LouKeThreadIdToThreadData(ThreadID);
    LouKeLockProcManager(&Irql);
    memset(&ThreadData->BlockTimeout, 0, sizeof(TIME_T));
    if(ThreadData->State < THREAD_BLOCKED){
        ThreadData->State = THREAD_BLOCKED;
    }
    LouKeGetFutureTime(&Time, Ms);
    memcpy(&ThreadData->BlockTimeout, &Time, sizeof(TIME_T));
    LouKeUnlockProcManager(&Irql);
    asm("INT $32");
}

KERNEL_IMPORT
void 
LouKeYeildExecution(){
    PGENERIC_THREAD_DATA ThreadData = LouKeGetCurrentThreadData();
    LouKIRQL Irql;
    TIME_T Time;
    LouKeLockProcManager(&Irql);
    memset(&ThreadData->BlockTimeout, 0, sizeof(TIME_T));
    if(ThreadData->State < THREAD_BLOCKED){
        ThreadData->State = THREAD_BLOCKED;
    }    
    LouKeGetFutureTime(&Time, ThreadData->TotalMsSlice);
    memcpy(&ThreadData->BlockTimeout, &Time, sizeof(TIME_T));
    LouKeUnlockProcManager(&Irql);
    asm("INT $32");
}

KERNEL_IMPORT void LouKeUnblockThread(UINT64 ThreadID){
    LouKIRQL Irql;
    PGENERIC_THREAD_DATA ThreadData = LouKeThreadIdToThreadData(ThreadID);
    LouKeLockProcManager(&Irql);
    memset(&ThreadData->BlockTimeout, 0, sizeof(TIME_T));
    ThreadData->State = THREAD_READY;    
    LouKeUnlockProcManager(&Irql);
}

LOUDDK_API_ENTRY DWORD LouKeThreadManagerDemon(PVOID Params){
    LouPrint("Thread Manager Demon Started\n");
    UNUSED INTEGER Processors = GetNPROC();

    while(1){
        PGENERIC_THREAD_DATA TmpThreadHandle = &MasterThreadList;
        while(TmpThreadHandle->Peers.NextHeader){
            TmpThreadHandle = (PGENERIC_THREAD_DATA)TmpThreadHandle->Peers.NextHeader;
            if((TmpThreadHandle->State == THREAD_TERMINATED) && (TmpThreadHandle->Resting)){
                PGENERIC_PROCESS_DATA ProcessData = TmpThreadHandle->Process;         
                if(ProcessData){
                    for(INTEGER i = 0 ; i < Processors; i++){
                        if(IS_PROCESSOR_AFFILIATED(TmpThreadHandle->AfinityBitmap, i)){
                            ProcessData->ThreadObjects[i].TsmDeasignThreadFromSchedual(TmpThreadHandle);
                        }
                    }
                }
                LouPrint("Thread:%d Has Retired\n", TmpThreadHandle->ThreadID);
                LouKeTsmDestroyThreadHandle(TmpThreadHandle);
            }
        }
    }
    return -1;
}