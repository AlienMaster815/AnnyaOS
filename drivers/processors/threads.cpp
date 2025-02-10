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



    uint64_t rip;      // Instruction Pointer
    uint64_t cs;       // Code Segment
    uint64_t rflags;   // Flags Register
    uint64_t rsp;      // Stack Pointer
    uint64_t ss;       // Stack Segment
    //uint64_t error;    // Error Code (only if applicable)
} CPUContext;

KERNEL_IMPORT
void FuckItRestoreEverything(uint64_t* ContextHandle);
KERNEL_IMPORT
void FuckItSaveEverything(uint64_t* ContextHandle);

typedef struct {
    ListHeader Neighbors;
    uint64_t KERNEL_STACK;
    bool NewTask;
    CPUContext* cpu_state;
    thread_state_t state;
    void* StackTop;
    uint64_t AdvancedRegisterStorage;
    uint64_t AdvancedRegisterInterruptsStorage;
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
    TmpThreadHandle->Neighbors.NextHeader = (PListHeader)LouKeMalloc(sizeof(thread_t), USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);
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

KERNEL_IMPORT void StoreAdvancedRegisters(uint64_t ContextHandle);
KERNEL_IMPORT void RestoreAdvancedRegisters(uint64_t ContextHandle);

KERNEL_IMPORT spinlock_t* LouKeGetInterruptGlobalLock();

LOUDDK_API_ENTRY
uint64_t GetAdvancedRegisterInterruptsStorage(){
    return current_thread[get_processor_id()]->AdvancedRegisterInterruptsStorage;
}

//static mutex_t FOO;
LOUDDK_API_ENTRY uint64_t UpdateThreadManager(uint64_t CpuCurrentState) {

    if(NumberOfThreads < 1){
        if((uint64_t)current_thread[get_processor_id()] != (uint64_t)&MasterThreadTable){
            RestoreAdvancedRegisters(MasterThreadTable.AdvancedRegisterStorage);
            current_thread[get_processor_id()] = &MasterThreadTable;
            local_apic_send_eoi();
            return (uint64_t)MasterThreadTable.cpu_state;
        }else{
            local_apic_send_eoi();
            return CpuCurrentState;
        }
    }

    LouKIRQL Irql;
    LouKeSetIrql(HIGH_LEVEL, &Irql);  

    uint8_t ProcessorID = get_processor_id();
    thread_t* CurrentThread = current_thread[ProcessorID];

    if(timeQuantum[ProcessorID] < 5){
        timeQuantum[ProcessorID]++;
        local_apic_send_eoi();
        LouKeReleaseSpinLock(LouKeGetInterruptGlobalLock(), &Irql);
        return CpuCurrentState;
    }

    timeQuantum[ProcessorID] = 0;

    if(IsThreadInThreadTable(CurrentThread)){
        CurrentThread->cpu_state = (CPUContext*)CpuCurrentState;
        CurrentThread->state = THREAD_READY;
        StoreAdvancedRegisters(CurrentThread->AdvancedRegisterStorage);
    }



    thread_t* NextThread = GetNextThread(CurrentThread);
    while((!IsThreadInThreadTable(NextThread)) && (NextThread->state == THREAD_READY)){
        NextThread = GetNextThread(NextThread);
    }


    if(!NextThread->NewTask){
        RestoreAdvancedRegisters(NextThread->AdvancedRegisterStorage);
        NextThread->NewTask = false;
    }

    NextThread->state = THREAD_RUNNING;
    CpuCurrentState = (uint64_t)NextThread->cpu_state;

    current_thread[ProcessorID] = NextThread;

    local_apic_send_eoi();
    LouKeSetIrql(Irql, 0x00);  

    return CpuCurrentState;
}

LOUDDK_API_ENTRY void RegisterLastKnownStackLocation(CPUContext* State){
    //threads[0].cpu_state = State;
}



LOUDDK_API_ENTRY LOUSTATUS InitThreadManager() {
    
    LOUSTATUS Status = LOUSTATUS_GOOD;

    if (!GetNPROC()) return STATUS_UNSUCCESSFUL;

    LouPrint("Thread Manager Starting\nNumber Of Processors: %d\n", GetNPROC());

    LouPrint("Initialized Processor:%d as Thread 0\n", get_processor_id());

    current_thread[get_processor_id()] = &MasterThreadTable;
    current_thread[get_processor_id()]->AdvancedRegisterStorage = (uintptr_t)LouMallocEx(2688, 64);
    current_thread[get_processor_id()]->AdvancedRegisterInterruptsStorage = (uintptr_t)LouMallocEx(2688, 64);
    current_thread[get_processor_id()]->NewTask = false;
    current_thread[get_processor_id()]->state = THREAD_RUNNING;

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


LOUDDK_API_ENTRY uintptr_t LouKeCreateUserStackThread(void (*Function)(), PVOID FunctionParameters, uint32_t Pages) {
    //allocate New Stack
    //void* NewStack = LouKeMallocEx(Pages * KILOBYTE_PAGE,KILOBYTE_PAGE, WRITABLE_PAGE | PRESENT_PAGE | USER_PAGE);
    
    //Allocate New Thread
    //thread_t* NewThread = CreateThreadHandle();
    //if(!NewThread){
    //    return 0x00;
    //}
    //store the top of the stack
    //NewThread->StackTop = NewStack;
    //set the context pointer
    //CPUContext* NewContext = (CPUContext*)NewStack + (KILOBYTE_PAGE * Pages) - KILOBYTE; //leave a kilobyte for wiggle room
    //set the New Threads Context
    //NewThread->cpu_state = NewContext;
    //Allocate Space For XSAVE and XRSTOR
    //NewThread->AdvancedRegisterStorage = (uintptr_t)LouMallocEx(1688, 64);//1688 bytes by a 64 byte alignment
    //Mark the Register Storage As Clean
    //NewThread->NewTask = true;
    //Get the Stub Address
    //uintptr_t StubAddress = RetriveThreadStubAddress();
    //fill the Context...
    //NewContext->rcx = (uint64_t)Function;           //first parameter  MSVC
    //NewContext->rdx = (uint64_t)FunctionParameters; //Second Parameter MSVC
    //NewContext->r8  = (uint64_t)NewThread;          //Third Parameter  MSVC
    //NewContext->rip = (uint64_t)StubAddress;        //Liftoff Address  
    //NewContext->rbp = (uint64_t)NewContext;         //Base Pointer
    //NewContext->rsp = (uint64_t)NewContext;         //Current Pointer
    //Fill Segments and flags
    //NewContext->cs  = 0x08;
    //NewContext->ss  = 0x10;  
    //NewContext->rflags = 0x202;  
    //Increment Thread Counter
    //NumberOfThreads++;
    //return the handle to the new thread
    return (uintptr_t)0;//NewThread;
}
