#include <LouDDK.h>
#include <NtAPI.h>
#include "Processors.h"

#define MAX_THREADS 512
#define MAX_CORES 256

typedef enum {
    THREAD_READY = 0,
    THREAD_RUNNING = 1,
    THREAD_TERMINATED = 2,
} thread_state_t;

typedef struct  __attribute__((packed)) _CPUContext{
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
    uint64_t ThreadIdentification;
} thread_t;

static thread_t MasterThreadTable;
static uint64_t NumberOfThreads = 0;
//static uint64_t CurrentRoundRobin = 0;

static inline thread_t* CreateThreadHandle(){
    thread_t* TmpThreadHandle = &MasterThreadTable;
    for(uint64_t i = 0 ; i < NumberOfThreads;i++){
        if(TmpThreadHandle->Neighbors.NextHeader){
            TmpThreadHandle = (thread_t*)TmpThreadHandle->Neighbors.NextHeader;
        }
    }
    TmpThreadHandle->Neighbors.NextHeader = (PListHeader)LouKeMallocEx(sizeof(thread_t), GET_ALIGNMENT(thread_t), USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);
    return(thread_t*)TmpThreadHandle->Neighbors.NextHeader;
}

static inline thread_t* GetNextThread(thread_t* CurrentThread){
    if(CurrentThread->Neighbors.NextHeader == 0x00){
        //CurrentRoundRobin = 0;
        return (thread_t*)&MasterThreadTable;
    }else {
        //CurrentRoundRobin++;
        return (thread_t*)CurrentThread->Neighbors.NextHeader; 
    }
}

static inline bool IsThreadInThreadTable(thread_t* Thread){
    thread_t* TmpThread = &MasterThreadTable;
    for(size_t i = 0 ; i <= NumberOfThreads; i++){
        if(TmpThread == Thread)return true;
        if(TmpThread->Neighbors.NextHeader){
            TmpThread = (thread_t*)TmpThread->Neighbors.NextHeader;
        }
    }
    return false;
}

UNUSED static thread_t* current_thread[MAX_CORES] = {0}; // Track current thread per core
UNUSED static int thread_count = 0;

UNUSED static uint16_t core_count = 1;

KERNEL_IMPORT void SetInterruptFlags();
KERNEL_IMPORT void UnSetInterruptFlags();
KERNEL_IMPORT void LouKeRunThreadContext(
    uint64_t Ctex,
    uint64_t CCTex,
    uint64_t StorAddress
);

static inline uint32_t get_processor_id() {
    uint32_t eax, ebx, ecx, edx;
    eax = 1; // Processor info and feature bits
    __asm__ volatile(
        "cpuid"
        : "=b" (ebx), "=d" (edx), "=c" (ecx)
        : "a" (eax)
    );
    uint32_t processor_id = ebx >> 24;
    return processor_id;
}

KERNEL_IMPORT void local_apic_send_eoi();


UNUSED static uint32_t timeQuantum[MAX_CORES] = {0}; // Array to track the load on each core

// Placeholder function for finding the next thread to run across all cores
static inline int find_next_thread(int CurrentThread) {
    return 0;
}

LOUDDK_API_ENTRY void local_apic_send_eoi();

KERNEL_IMPORT spinlock_t* LouKeGetInterruptGlobalLock();

LOUDDK_API_ENTRY
uint64_t GetAdvancedRegisterInterruptsStorage(){
    return current_thread[get_processor_id()]->AdvancedRegisterInterruptsStorage;
}


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

static void RestoreContext(CPUContext* TMContext, CPUContext* ProgramContext){

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

KERNEL_IMPORT
void SetTEB(uint64_t Teb);

LOUDDK_API_ENTRY uint64_t UpdateThreadManager(uint64_t CpuCurrentState) {
    uint8_t ProcessorID = get_processor_id();
    thread_t* CurrentThread = current_thread[ProcessorID];
    thread_t* NextThread = 0;
    CPUContext* CurrentContext = (CPUContext*)(uint8_t*)CpuCurrentState;

    if((CurrentContext->cs & 0b11) == 0){
        //tasks shall not switch when running
        //in the kernel segment to eliminate
        //stack curruoption and add better 
        //prediction to switching states
        goto _UPDATE_THREAD_MANAGER_FINISHED;
    }

    if(timeQuantum[ProcessorID] < 5){
        timeQuantum[ProcessorID]++;
        goto _UPDATE_THREAD_MANAGER_FINISHED;
    }

    ProcessorID = get_processor_id();
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
    RestoreContext((CPUContext*)(uint8_t*)CpuCurrentState, (CPUContext*)(uint8_t*)LouKeCastToUnalignedPointer((void*)&NextThread->SavedContext));

    if(NextThread->WinTEBData){
        SetTEB(NextThread->WinTEBData);
    }

    current_thread[ProcessorID] = NextThread;
    
    _UPDATE_THREAD_MANAGER_FINISHED:
    local_apic_send_eoi();
    return CpuCurrentState;
}

LOUDDK_API_ENTRY void RegisterLastKnownStackLocation(CPUContext* State){
    //threads[0].cpu_state = State;
}



LOUDDK_API_ENTRY LOUSTATUS InitThreadManager() {
    
    LOUSTATUS Status = LOUSTATUS_GOOD;

    if (!GetNPROC()) return STATUS_UNSUCCESSFUL;

    LouPrint("Thread Manager Starting\nNumber Of Processors: %d\n", GetNPROC());

    LouPrint("Initialized Processor:%d as Thread 1\n", get_processor_id());

    current_thread[get_processor_id()] = &MasterThreadTable;
    current_thread[get_processor_id()]->AdvancedRegisterStorage = (uintptr_t)LouMallocEx(2688, 64);
    current_thread[get_processor_id()]->AdvancedRegisterInterruptsStorage = (uintptr_t)LouMallocEx(2688, 64);
    current_thread[get_processor_id()]->NewTask = false;
    current_thread[get_processor_id()]->state = THREAD_RUNNING;
    current_thread[get_processor_id()]->ThreadIdentification = NumberOfThreads + 1;

    LouPrint("Thread Manager Successfully Started\n");

    return Status;
}

//static spinlock_t UserThreadCreationLock;


LOUDDK_API_ENTRY VOID LouKeDestroyThread(thread_t* Thread) {
    //LouKIRQL Irql;
    //LouKeAcquireSpinLock(&UserThreadCreationLock, &Irql);
    //thread_t* TmpThreadHandle = &MasterThreadTable;
    //for(uint64_t i = 0 ; i < NumberOfThreads; i++){
    //    TmpThreadHandle = (thread_t*)TmpThreadHandle->Neighbors.NextHeader;
    //    if(TmpThreadHandle == Thread){
    //        thread_t* TmpThreadHandle2 = &MasterThreadTable;
    //        for(uint64_t j = 0 ; j < i; j++){
    //            TmpThreadHandle2 = (thread_t*)TmpThreadHandle2->Neighbors.NextHeader;
    //        }
    //        TmpThreadHandle2->Neighbors.NextHeader = TmpThreadHandle->Neighbors.NextHeader;
    //        LouKeUserFree((RAMADD)Thread);
    //        NumberOfThreads--;
    //        LouKeReleaseSpinLock(&UserThreadCreationLock, &Irql);   
    //        return;
    //        //Endof SystemCall
    //    }
    //}
    //LouKeReleaseSpinLock(&UserThreadCreationLock, &Irql);
    //Endof SystemCall
}
LOUDDK_API_ENTRY uint64_t GetThreadContext(
    int Thread
);


KERNEL_IMPORT void ThreadStart(void(*Function)(PVOID), PVOID Parameters);


void ThreadStub(int(*Thread)(PVOID), PVOID FunctionParam, thread_t* ThreadHandle){
    int Result = Thread(FunctionParam);
    LouPrint("Thread:%h Exited With Code:%h\n", ThreadHandle, Result);
    LouKeDestroyThread(ThreadHandle);
    while(1);
}


LOUDDK_API_ENTRY LOUSTATUS LouKeCreateThread(void (*Function)(), PVOID FunctionParameters, uint32_t StackSize) {

    return STATUS_SUCCESS;
}

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

    //current_thread[get_processor_id()] = Context_1;

    //threads[Context_2].cpu_state = (CPUContext*)(get_rsp() + 120);

    //LouKeRunThreadContext(GetThreadContext(Context_1), 0, 0);

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

LOUDDK_API_ENTRY uintptr_t LouKeCreateUserStackThreadWin(void (*Function)(), PVOID FunctionParameters, size_t StackSize, uint64_t TEBPointer) {
    
    //allocate New Stack
    void* NewStack = LouKeMallocPhysical(StackSize, WRITEABLE_PAGE | PRESENT_PAGE | USER_PAGE);
    
    //Allocate New Thread
    thread_t* NewThread = CreateThreadHandle();
    if(!NewThread){
        LouKeFree(NewStack);
        return 0x00;
    }
    //store the top of the stack
    NewThread->StackTop = NewStack;
    //set the context pointer
    CPUContext* NewContext = (CPUContext*)(uint8_t*)(((uintptr_t)((uint8_t*)NewStack) + StackSize) - KILOBYTE); //leave a kilobyte for wiggle room
    //set the New Threads Context
    NewThread->cpu_state = NewContext;
    //Allocate Space For Safe Context Handling
    NewThread->AdvancedRegisterStorage              = (uintptr_t)LouMallocEx(1688, 64);//1688 bytes by a 64 byte alignment
    NewThread->AdvancedRegisterInterruptsStorage    = (uintptr_t)LouMallocEx(1688, 64);//1688 bytes by a 64 byte alignment
    //Mark the Register Storage As Clean
    NewThread->NewTask = true;
    NewThread->state = THREAD_READY;
    //Get the Stub Address
    uintptr_t StubAddress = RetriveThreadStubAddress();
    //fill the Context...
    NewThread->SavedContext.rcx = (uint64_t)Function;           //first parameter  MSVC
    NewThread->SavedContext.rdx = (uint64_t)FunctionParameters; //Second Parameter MSVC
    NewThread->SavedContext.r8  = (uint64_t)NewThread;          //Third Parameter  MSVC
    NewThread->SavedContext.rip = (uint64_t)StubAddress;        //Liftoff Address  
    NewThread->SavedContext.rbp = (uint64_t)NewContext;         //Base Pointer
    NewThread->SavedContext.rsp = (uint64_t)NewContext;         //Current Pointer
    //Fill Segments and flags
    NewThread->SavedContext.cs  = 0x1B;
    NewThread->SavedContext.ss  = 0x23;  
    NewThread->SavedContext.rflags = 0x202;  
    NewThread->ThreadIdentification = NumberOfThreads + 1;
    NewThread->WinTEBData = TEBPointer;

    PWIN_TEB Teb = (PWIN_TEB)(uint8_t*)TEBPointer;
    Teb->TebNtTibStackBase = (uint64_t)NewContext;
    Teb->TebNtTibStackLimit = (uint64_t)NewContext - (2 * MEGABYTE); //this thread is 2 Megs
    Teb->TebProcessEnvironmentBlock = GetPEB();
    //Increment Thread Counter
    NumberOfThreads++;
    //return the handle to the new thread
    return (uintptr_t)NewThread;//NewThread;
}

LOUDDK_API_ENTRY uintptr_t LouKeCreateUserStackThread(void (*Function)(), PVOID FunctionParameters, size_t StackSize) {
     
    //allocate New Stack
    void* NewStack = LouKeMallocPhysical(StackSize, WRITEABLE_PAGE | PRESENT_PAGE | USER_PAGE);
    
    //Allocate New Thread
    thread_t* NewThread = CreateThreadHandle();
    if(!NewThread){
        LouKeFree(NewStack);
        return 0x00;
    }
    //store the top of the stack
    NewThread->StackTop = NewStack;
    //set the context pointer
    CPUContext* NewContext = (CPUContext*)(uint8_t*)(((uintptr_t)((uint8_t*)NewStack) + StackSize) - KILOBYTE); //leave a kilobyte for wiggle room
    //set the New Threads Context
    NewThread->cpu_state = NewContext;
    //Allocate Space For Safe Context Handling
    NewThread->AdvancedRegisterStorage              = (uintptr_t)LouMallocEx(1688, 64);//1688 bytes by a 64 byte alignment
    NewThread->AdvancedRegisterInterruptsStorage    = (uintptr_t)LouMallocEx(1688, 64);//1688 bytes by a 64 byte alignment
    //Mark the Register Storage As Clean
    NewThread->NewTask = true;
    NewThread->state = THREAD_READY;
    NewThread->ThreadIdentification = NumberOfThreads + 2;

    //Get the Stub Address
    uintptr_t StubAddress = RetriveThreadStubAddress();
    //fill the Context...
    NewThread->SavedContext.rcx = (uint64_t)Function;           //first parameter  MSVC
    NewThread->SavedContext.rdx = (uint64_t)FunctionParameters; //Second Parameter MSVC
    NewThread->SavedContext.r8  = (uint64_t)NewThread;          //Third Parameter  MSVC
    NewThread->SavedContext.rip = (uint64_t)StubAddress;        //Liftoff Address  
    NewThread->SavedContext.rbp = (uint64_t)NewContext;         //Base Pointer
    NewThread->SavedContext.rsp = (uint64_t)NewContext;         //Current Pointer
    //Fill Segments and flags
    NewThread->SavedContext.cs  = 0x1B;
    NewThread->SavedContext.ss  = 0x23;  
    NewThread->SavedContext.rflags = 0x202;  
    //Increment Thread Counter
    NumberOfThreads++;
    //return the handle to the new thread
    return (uintptr_t)NewThread;//NewThread;
}

LOUDDK_API_ENTRY
uint64_t LouKeGetThreadIdentification(){
    return current_thread[get_processor_id()]->ThreadIdentification;
}

LOUDDK_API_ENTRY
semaphore_t* LouKeCreateSemaphore(int initial, int limit){
    semaphore_t* NewSemaphore = (semaphore_t*)LouKeMallocType(semaphore_t, KERNEL_GENERIC_MEMORY);
    SemaphoreInitialize(NewSemaphore, initial, limit);
    return NewSemaphore;
}
