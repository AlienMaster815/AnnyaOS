/*
#include <LouDDK.h>
#include <NtAPI.h>
#include "Processors.h"


typedef enum {
    THREAD_READY = 0,
    THREAD_RUNNING = 1,
    THREAD_TERMINATED = 2,
} thread_state_t;

typedef struct  PACKED _CPUContext{
    // General-Purpose Registers    
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;

    uint64_t rbp;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r8;

    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;

    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;

    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} CPUContext;

KERNEL_IMPORT void SaveEverything(uint64_t* ContextHandle);
KERNEL_IMPORT void RestoreEverything(uint64_t* ContextHandle);

typedef struct {
    ListHeader Neighbors;
    uint64_t KERNEL_STACK;
    bool NewTask;
    CPUContext* cpu_state;
    thread_state_t state;
    void* StackTop;
    uint64_t AdvancedRegisterStorage;
    uint64_t AdvancedRegisterInterruptsStorage;
    uint64_t WinTEBData;
    CPUContext SavedContext;
    uint64_t StackSegment;
    uint64_t ThreadIdentification;
} thread_t;

static thread_t MasterThreadTable;
static uint64_t NumberOfThreads = 0;
//static uint64_t CurrentRoundRobin = 0;
static spinlock_t ThreadCreationLock;

UNUSED static thread_t** current_thread = 0; // Track current thread per core
UNUSED static uint32_t* timeQuantum = 0; // Array to track the load on each core
UNUSED static int thread_count = 0;


KERNEL_IMPORT void LouKeSendIcEOI();
KERNEL_IMPORT void SetInterruptFlags();
KERNEL_IMPORT void UnSetInterruptFlags();

KERNEL_IMPORT mutex_t* LouKeGetInterruptGlobalLock();

KERNEL_IMPORT
void SetTEB(uint64_t Teb);
KERNEL_IMPORT LouKIRQL LouKeGetIrql();


LOUDDK_API_ENTRY uint64_t GetThreadContext(
    int Thread
);


KERNEL_IMPORT void ThreadStart(void(*Function)(PVOID), PVOID Parameters);



LOUDDK_API_ENTRY uint64_t GetThreadContext(
    int Thread
){
    //return (uint64_t)threads[Thread].cpu_state;
    return 0x00;
}

unsigned long long get_rsp() {
    unsigned long long rsp_value;
    
    __asm__ __volatile__ (
        "mov %%rsp, %0"
        : "=r" (rsp_value) // Output operand
    );
    
    return rsp_value;
}

LOUDDK_API_ENTRY void ManualContextSwitch(uint64_t Context_1, uint64_t Context_2){

    //current_thread[GetCurrentCpuTrackMember()] = Context_1;

    //threads[Context_2].cpu_state = (CPUContext*)(get_rsp() + 120);

    //LouKeRunThreadContext(GetThreadContext(Context_1), 0, 0);

}

//real stuff starts here 

static inline thread_t* CreateThreadHandle(){
    thread_t* TmpThreadHandle = &MasterThreadTable;
    while(TmpThreadHandle->Neighbors.NextHeader){
        TmpThreadHandle = (thread_t*)TmpThreadHandle->Neighbors.NextHeader;
    }
    TmpThreadHandle->Neighbors.NextHeader = (PListHeader)LouKeMallocType(thread_t,  USER_GENERIC_MEMORY);
    return(thread_t*)TmpThreadHandle->Neighbors.NextHeader;
}

static inline thread_t* GetNextThread(thread_t* CurrentThread){
    if(CurrentThread->Neighbors.NextHeader == 0x00){
        //CurrentRoundRobin = 0;
        return (thread_t*)MasterThreadTable.Neighbors.NextHeader;
    }else {
        //CurrentRoundRobin++;
        return (thread_t*)CurrentThread->Neighbors.NextHeader; 
    }
}

static inline bool IsThreadInThreadTable(thread_t* Thread){
    thread_t* TmpThreadHandle = &MasterThreadTable;
    while(TmpThreadHandle->Neighbors.NextHeader){
        TmpThreadHandle = (thread_t*)TmpThreadHandle->Neighbors.NextHeader;
        if(TmpThreadHandle == Thread){
            return true;
        }
    }
    return false;
}



UNUSED 
static void SaveContext(CPUContext* TMContext, CPUContext* ProgramContext){

    ProgramContext->rax = TMContext->rax;
    ProgramContext->rbx = TMContext->rbx;
    ProgramContext->rcx = TMContext->rcx;
    ProgramContext->rdx = TMContext->rdx;

    ProgramContext->rbp = TMContext->rbp;
    ProgramContext->rsi = TMContext->rsi;
    ProgramContext->rdi = TMContext->rdi;
    ProgramContext->r8 = TMContext->r8;

    ProgramContext->r9 = TMContext->r9;
    ProgramContext->r10 = TMContext->r10;
    ProgramContext->r11 = TMContext->r11;
    ProgramContext->r12 = TMContext->r12;

    ProgramContext->r13 = TMContext->r13;
    ProgramContext->r14 = TMContext->r14;
    ProgramContext->r15 = TMContext->r15;
    ProgramContext->rip = TMContext->rip;

    ProgramContext->cs = TMContext->cs;
    ProgramContext->rflags = TMContext->rflags;
    ProgramContext->rsp = TMContext->rsp;
    ProgramContext->ss = TMContext->ss;

}

UNUSED
static void RestoreContext(CPUContext* TMContext, CPUContext* ProgramContext, thread_t* NextThread){

    TMContext->rax = ProgramContext->rax;
    TMContext->rbx = ProgramContext->rbx;
    TMContext->rcx = ProgramContext->rcx;
    TMContext->rdx = ProgramContext->rdx;

    TMContext->rbp = ProgramContext->rbp;
    TMContext->rsi = ProgramContext->rsi; 
    TMContext->rdi = ProgramContext->rdi;
    TMContext->r8 = ProgramContext->r8;

    TMContext->r9 = ProgramContext->r9;
    TMContext->r10 = ProgramContext->r10;
    TMContext->r11 = ProgramContext->r11;
    TMContext->r12 = ProgramContext->r12;

    TMContext->r13 = ProgramContext->r13;
    TMContext->r14 = ProgramContext->r14;
    TMContext->r15 = ProgramContext->r15;
    TMContext->rip = ProgramContext->rip;

    TMContext->cs = ProgramContext->cs;
    TMContext->rflags = ProgramContext->rflags;
    TMContext->rsp = ProgramContext->rsp;
    TMContext->ss = ProgramContext->ss;

}



LOUDDK_API_ENTRY uint64_t UpdateThreadManager(uint64_t CpuCurrentState) {
    
    uint8_t ProcessorID = GetCurrentCpuTrackMember();
    thread_t* CurrentThread = current_thread[ProcessorID];
    thread_t* NextThread = 0;

    UNUSED CPUContext* Ct = (CPUContext*)CpuCurrentState;

    if(timeQuantum[ProcessorID] < 5){
        timeQuantum[ProcessorID]++;
        goto _UPDATE_THREAD_MANAGER_FINISHED;
    }

    if(MutexIsLocked(&ThreadCreationLock.Lock) || (LouKeGetIrql() == HIGH_LEVEL)){
        goto _UPDATE_THREAD_MANAGER_FINISHED;
    }

    ProcessorID = GetCurrentCpuTrackMember();
    CurrentThread = current_thread[ProcessorID];

    timeQuantum[ProcessorID] = 0;

    NextThread = GetNextThread(CurrentThread);
    if((uintptr_t)NextThread == (uintptr_t)CurrentThread){
        goto _UPDATE_THREAD_MANAGER_FINISHED;
    }

    if(IsThreadInThreadTable(CurrentThread)){
        SaveContext((CPUContext*)(uint8_t*)CpuCurrentState, (CPUContext*)(uint8_t*)LouKeCastToUnalignedPointer((void*)&CurrentThread->SavedContext));
        CurrentThread->state = THREAD_READY;
        SaveEverything(&CurrentThread->AdvancedRegisterStorage);
    }

    while((!IsThreadInThreadTable(NextThread)) && (NextThread->state != THREAD_READY)){
        NextThread = GetNextThread(NextThread);
    }

    RestoreEverything(&NextThread->AdvancedRegisterStorage);

    NextThread->state = THREAD_RUNNING;
    RestoreContext((CPUContext*)(uint8_t*)CpuCurrentState, (CPUContext*)(uint8_t*)LouKeCastToUnalignedPointer((void*)&NextThread->SavedContext), NextThread);

    if(NextThread->WinTEBData){
        SetTEB(NextThread->WinTEBData);
    }

    current_thread[ProcessorID] = NextThread;
    
    _UPDATE_THREAD_MANAGER_FINISHED:
    LouKeSendIcEOI();
    return CpuCurrentState;
}




KERNEL_IMPORT
void UsrJmp(uint64_t Entry);


LOUDDK_API_ENTRY uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

extern "C" void EXECUTE_THREAD_JUMP();

uintptr_t RetriveThreadStubAddress(){
    uintptr_t FunctionAddress;
    FunctionAddress = LouKeLinkerGetAddress(
        "LouDll.dll",
        "AnnyaUserThreadStub"
    );
    return FunctionAddress;
}

KERNEL_IMPORT uint64_t GetPEB();






LOUDDK_API_ENTRY 
PTHREAD 
LouKeCreateUserStackDemon(
    PVOID Function,
    PVOID Params,
    SIZE  StackSize
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&ThreadCreationLock, &Irql);
    void* NewStack = LouKeMallocPhysicalEx(StackSize, 64, USER_GENERIC_MEMORY);
    thread_t* NewThread = CreateThreadHandle();

    if(!NewThread){
        LouKeFree(NewStack);
        LouKeReleaseSpinLock(&ThreadCreationLock, &Irql);
        return 0x00;
    }

    //store the top of the stack
    NewThread->StackTop = NewStack;
    //set the context pointer
    CPUContext* NewContext = (CPUContext*)(uint8_t*)(((uintptr_t)(((uint8_t*)NewStack) + StackSize) - 64) & ~(64 - 1)); //leave a kilobyte for wiggle room
    //set the New Threads Context
    NewThread->cpu_state = NewContext;
    //Allocate Space For Safe Context Handling
    NewThread->AdvancedRegisterStorage              = (uintptr_t)LouKeMallocPhysicalEx(1688, 64, KERNEL_GENERIC_MEMORY);//1688 bytes by a 64 byte alignment
    NewThread->AdvancedRegisterInterruptsStorage    = (uintptr_t)LouKeMallocPhysicalEx(1688, 64, KERNEL_GENERIC_MEMORY);//1688 bytes by a 64 byte alignment
    //Mark the Register Storage As Clean
    NewThread->NewTask = true;
    NewThread->state = THREAD_READY;
    NewThread->ThreadIdentification = NumberOfThreads + 2;

    //Get the Stub Address
    uintptr_t StubAddress = (uintptr_t)ThreadStub;
    //fill the Context...
    NewThread->SavedContext.rcx = (uint64_t)Function;           //first parameter  MSVC
    NewThread->SavedContext.rdx = (uint64_t)Params;             //Second Parameter MSVC
    NewThread->SavedContext.r8  = (uint64_t)NewThread;          //Third Parameter  MSVC
    NewThread->SavedContext.rip = (uint64_t)StubAddress;        //Liftoff Address  
    NewThread->SavedContext.rbp = (uint64_t)NewContext;         //Base Pointer
    NewThread->SavedContext.rsp = (uint64_t)NewContext;         //Current Pointer
    //Fill Segments and flags
    NewThread->SavedContext.cs  = 0x08;
    NewThread->SavedContext.ss  = 0x10;  
    NewThread->SavedContext.rflags = 0x202;  

    NewThread->StackSegment = 0x10;

    //Increment Thread Counter
    NumberOfThreads++;
    //return the handle to the new thread

    LouKeReleaseSpinLock(&ThreadCreationLock, &Irql);
    return (PTHREAD)NewThread;
}




LOUDDK_API_ENTRY LOUSTATUS InitThreadManager() {
    
    LOUSTATUS Status = LOUSTATUS_GOOD;
    size_t CpuCount = GetNPROC();
    if (!CpuCount) return STATUS_UNSUCCESSFUL;

    LouPrint("Thread Manager Starting\nNumber Of Processors: %d\n", CpuCount);

    LouPrint("Initialized Processor:%d as Thread 1\n", GetCurrentCpuTrackMember());

    current_thread = LouKeMallocArray(thread_t*, CpuCount, KERNEL_GENERIC_MEMORY);    
    timeQuantum = LouKeMallocArray(uint32_t, CpuCount, KERNEL_GENERIC_MEMORY);

    current_thread[GetCurrentCpuTrackMember()] = CreateThreadHandle();
    current_thread[GetCurrentCpuTrackMember()]->AdvancedRegisterStorage = (uintptr_t)LouKeMallocPhysicalEx(2688, 64, KERNEL_GENERIC_MEMORY);
    current_thread[GetCurrentCpuTrackMember()]->AdvancedRegisterInterruptsStorage = (uintptr_t)LouKeMallocPhysicalEx(2688, 64, KERNEL_GENERIC_MEMORY);
    current_thread[GetCurrentCpuTrackMember()]->NewTask = false;
    current_thread[GetCurrentCpuTrackMember()]->state = THREAD_RUNNING;
    current_thread[GetCurrentCpuTrackMember()]->ThreadIdentification = NumberOfThreads + 1;

    LouPrint("Thread Manager Successfully Started\n");

    return Status;
}
*/