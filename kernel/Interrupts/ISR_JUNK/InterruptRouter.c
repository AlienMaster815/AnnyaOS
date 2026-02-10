#include <LouAPI.h>

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
    uint64_t fq;
    uint64_t FaultStack;
    uint64_t ss;
} CPUContext;

void LouKeSendIcEOI();
bool GetAPICStatus();

typedef struct _INTERRUPT_ROUTER_ENTRY{
    ListHeader  List;
    uint32_t    ListCount;
    bool        NeedFlotationSave;
    void        (*InterruptHandler)(uint64_t);
    uint64_t    OverideData;
    bool        InterruptUnMasked;
    mutex_t     InterruptMutex;
}INTERRUPT_ROUTER_ENTRY, * PINTERRUPT_ROUTER_ENTRY;

static INTERRUPT_ROUTER_ENTRY InterruptRouterTable[256] = {0};
uint64_t GetAdvancedRegisterInterruptsStorage();

void LouKeIcUnmaskIrq(uint8_t irq);

void InterruptWrapper(uint64_t Handler,uint8_t InterruptNumber, bool NeedFlotationSave, uintptr_t OverideData) {
	RegisterInterruptHandler((void(*)(uint64_t))Handler, InterruptNumber, NeedFlotationSave, OverideData);
}

void InitializeInterruptRouter(){
    LouKeCreateFastObjectClass("IRQROUTE", 256, sizeof(INTERRUPT_ROUTER_ENTRY), GET_ALIGNMENT(INTERRUPT_ROUTER_ENTRY), 0, KERNEL_GENERIC_MEMORY);
}

void RegisterInterruptHandler(void(*Handler)(uint64_t),uint8_t InterruptNumber, bool NeedFlotationSave, uint64_t OverideData) {
    //LouPrint("Handler:%h Installed For Vector:%d\n", Handler, InterruptNumber);

    PINTERRUPT_ROUTER_ENTRY TmpRouter = &InterruptRouterTable[InterruptNumber]; 
	if(NeedFlotationSave){
        InterruptRouterTable[InterruptNumber].NeedFlotationSave = true;
    }
    while(TmpRouter->List.NextHeader){
        TmpRouter = (PINTERRUPT_ROUTER_ENTRY)TmpRouter->List.NextHeader;
    }
    TmpRouter->List.NextHeader = LouKeAllocateFastObject("IRQROUTE");
    if(!TmpRouter->List.NextHeader){
        TmpRouter->List.NextHeader = (PListHeader)LouKeMallocType(INTERRUPT_ROUTER_ENTRY, KERNEL_GENERIC_MEMORY);
    }
    TmpRouter = (PINTERRUPT_ROUTER_ENTRY)TmpRouter->List.NextHeader;
    TmpRouter->InterruptHandler = Handler;
    TmpRouter->OverideData = OverideData;
	InterruptRouterTable[InterruptNumber].ListCount++;
    if((InterruptNumber > 32) && (!InterruptRouterTable[InterruptNumber].InterruptUnMasked)){
        InterruptNumber -= 32;
        LouKeIcUnmaskIrq(InterruptNumber);
        InterruptRouterTable[InterruptNumber].InterruptUnMasked = true;
    }
}


uint8_t GetTotalHardwareInterrupts();

int LouPrintPanic(char* format, ...);

void StoreAdvancedRegisters(uint64_t ContextHandle);
void RestoreAdvancedRegisters(uint64_t ContextHandle);

typedef struct _PROCESSOR_CALLBACKS{
    void        (*SaveHandler)(uint8_t*);
    void        (*RestoreHandler)(uint8_t*);
    void        (*InitializeThreadDataHandler)(uint8_t*, uint8_t*);
    uint64_t    (*AllocateSaveContext)();
    void        (*DeAllocateSaveContext)(uint64_t);
}PROCESSOR_CALLBACKS, * PPROCESSOR_CALLBACKS;

static PPROCESSOR_CALLBACKS ProcessorCallbacks;

void LouKeRegisterProcessorCallback(PPROCESSOR_CALLBACKS Callback){
    ProcessorCallbacks = Callback;
}

//Fuck It Well do it live
void SaveEverythingWithInterruptBuffer(uint64_t* ContextHandle){
    if(!ContextHandle)return;   
    *ContextHandle = GetAdvancedRegisterInterruptsStorage();
    if(!(*ContextHandle))return;
    ProcessorCallbacks->SaveHandler((uint8_t*)(*ContextHandle));
}

void RestoreEverythingWithInterruptBuffer(uint64_t* ContextHandle){
    if(!ContextHandle)return;
    if(!(*ContextHandle))return;
    ProcessorCallbacks->RestoreHandler((uint8_t*)(*ContextHandle));
}

void SaveEverything(uint64_t ContextHandle){
    if(!ContextHandle)return;
    ProcessorCallbacks->SaveHandler((uint8_t*)ContextHandle);
}

void RestoreEverything(uint64_t ContextHandle){
    if(!ContextHandle)return;
    ProcessorCallbacks->RestoreHandler((uint8_t*)ContextHandle);
}

uint64_t AllocateSaveContext(){
    if(!ProcessorCallbacks->AllocateSaveContext){
        return 0x00;
    }
    return ProcessorCallbacks->AllocateSaveContext();
}

void DeAllocateSaveContext(uint64_t Context){
    if(!ProcessorCallbacks->DeAllocateSaveContext){
        return;
    }
    ProcessorCallbacks->DeAllocateSaveContext(Context);
}

void LouKeThrowPc();

void LouKeSetIrqlNoFlagUpdate(
    LouKIRQL  NewIrql,
    LouKIRQL* OldIrql
);

void InterruptRouter(uint64_t Interrupt, uint64_t Args) {
    LouKIRQL Irql;
    LouKeSetIrqlNoFlagUpdate(HIGH_LEVEL, &Irql);
    uint64_t ContextHandle = 0x00;
    PINTERRUPT_ROUTER_ENTRY TmpEntry = &InterruptRouterTable[Interrupt]; 
    if(InterruptRouterTable[Interrupt].ListCount){
        if(InterruptRouterTable[Interrupt].NeedFlotationSave){
            SaveEverythingWithInterruptBuffer(&ContextHandle);
        }
        while(TmpEntry){
            if(TmpEntry->InterruptHandler){
                if(TmpEntry->OverideData){
                    TmpEntry->InterruptHandler(TmpEntry->OverideData);
                }
                else{
                    TmpEntry->InterruptHandler(Args);
                }
            }
            TmpEntry = (PINTERRUPT_ROUTER_ENTRY)TmpEntry->List.NextHeader;
        }
        if(InterruptRouterTable[Interrupt].NeedFlotationSave){
            RestoreEverythingWithInterruptBuffer(&ContextHandle);
        }
        LouKeSetIrqlNoFlagUpdate(Irql, 0x00);
        LouKeSendIcEOI();
        return;
    }
    LouKeSetIrqlNoFlagUpdate(Irql, 0x00);
    LouKeSendIcEOI();
    return;
    
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

