#include <LouAPI.h>

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
    uint64_t fq;
    uint64_t FaultStack;
    uint64_t ss;
} CPUContext;

void LouKeRunOnNewStack(void (*func)(void*), void* FunctionParameters, size_t stack_size);
void AdvancedInterruptRouter(uint64_t InterruptNumber, uint64_t Args);

void(*InterruptHandler[256])(uint64_t);

void local_apic_send_eoi();
bool GetAPICStatus();

void initializeInterruptRouter(){
	for(uint8_t i = 0 ; i < 255 ; i ++){
		InterruptHandler[i] = 0x00;
	}
}

void InterruptWrapper(uint64_t Handler, uint8_t InterruptNumber) {
	RegisterInterruptHandler((void(*)())Handler, InterruptNumber);
}

void RegisterInterruptHandler(void(*Handler),uint8_t InterruptNumber) {
	
	InterruptHandler[InterruptNumber] = Handler;

}

void UnRegisterInterruptHandler(uint8_t InterruptNumber) {
	InterruptHandler[InterruptNumber] = 0x00;
}

static uint8_t InterruptGlobalCheck;

uint8_t GetGlobalInterrupt(){
	return InterruptGlobalCheck;
}

LouKIRQL InterruptSwitch(LouKIRQL New);

uint8_t GetTotalHardwareInterrupts();

//static inline uint32_t get_processor_id() {
//    uint32_t eax, ebx, ecx, edx;
//    eax = 1; // Processor info and feature bits
//    __asm__ volatile(
//        "cpuid"
//        : "=b" (ebx), "=d" (edx), "=c" (ecx)
//        : "a" (eax)
//    );
//    uint32_t processor_id = ebx >> 24;
//    return processor_id;
//}

void IfYouCanReadThisGetOutOfMyFuckingKernelBinary(){

}

void StoreAdvancedRegisters(uint64_t ContextHandle);
void RestoreAdvancedRegisters(uint64_t ContextHandle);

//Fuck It Well do it live
void FuckItSaveEverything(uint64_t* ContextHandle){
    *ContextHandle = (uint64_t)LouMallocEx(2688, 64);
    StoreAdvancedRegisters(*ContextHandle);
}

void FuckItRestoreEverything(uint64_t* ContextHandle){
    if(!(*ContextHandle))return;
    RestoreAdvancedRegisters(*ContextHandle);
    LouFree((RAMADD)*ContextHandle);
}

bool DoesHardwareInterruptNeedFloatPointSaves(uint8_t InterruptNumber);

static spinlock_t InterruptLock;

spinlock_t* LouKeGetInterruptGlobalLock(){
    return &InterruptLock;
}

void InterruptRouter(uint64_t Interrupt, uint64_t Args) {

	LouKIRQL PreInterruptIrql;
    LouKeAcquireSpinLock(&InterruptLock, &PreInterruptIrql);


    uint64_t ContextHandle;

	if (0x00 != InterruptHandler[Interrupt]) {

        if(HardwareInterruptManager == InterruptHandler[Interrupt]){
            void (*HardwareHandler)(uint64_t Interrupt, uint64_t Rsp) = (void (*)(uint64_t Interrupt, uint64_t Rsp))InterruptHandler[Interrupt];
            bool SlowSave = DoesHardwareInterruptNeedFloatPointSaves(Interrupt);

            if(SlowSave){
                FuckItSaveEverything(&ContextHandle);
            }

            HardwareHandler(Interrupt, Args);

            if(SlowSave){
                FuckItRestoreEverything(&ContextHandle);
            }

            local_apic_send_eoi();
            LouKeReleaseSpinLock(&InterruptLock, &PreInterruptIrql);
            return;
        }

        FuckItSaveEverything(&ContextHandle);
		InterruptHandler[Interrupt](Args);
        FuckItRestoreEverything(&ContextHandle);
		local_apic_send_eoi();
		LouKeReleaseSpinLock(&InterruptLock, &PreInterruptIrql);
		return;
	}

	LouPrint("Interrupt Number: %d Was Called\n",Interrupt);
	CPUContext* FaultData = (CPUContext*)((uint64_t)Args);
    LouPrint(
        "RAX:%h :: RBX:%h :: RCX:%h :: RDX:%h\n", 
        FaultData->rax, 
        FaultData->rbx, 
        FaultData->rcx, 
        FaultData->rdx
    );

    LouPrint(
        "RBP:%h :: RSI:%h :: RDI:%h ::  R8:%h\n",
        FaultData->rbp,
        FaultData->rsi,
        FaultData->rdi,
        FaultData->r8
    );

    LouPrint(
        "R9:%h :: R10:%h :: R11:%h :: R12:%h\n",
        FaultData->r9,
        FaultData->r10,
        FaultData->r11,
        FaultData->r12
    );

    LouPrint(
        "R13:%h :: R14:%h :: R15:%h :: RIP:%h\n",
        FaultData->r13,
        FaultData->r14,
        FaultData->r15,
        FaultData->rip
    );

    LouPrint(
        "CS:%h :: FQ:%h :: RSP:%h :: SS:%h\n",
        FaultData->cs,
        FaultData->fq,
        FaultData->FaultStack,
        FaultData->ss
    );
	while(1){
		asm("hlt");
	}
}


void PrintRegister(uint64_t Register){
    LouPrint("Register Is :: %h\n", Register);
}