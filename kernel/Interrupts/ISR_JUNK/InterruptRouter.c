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

void LouKeIcUnmaskIrq(uint8_t irq);


KERNEL_EXPORT
void RegisterInterruptHandler(void(*Handler)(uint64_t),uint8_t InterruptNumber, bool NeedFlotationSave, uint64_t OverideData) {

}


uint8_t GetTotalHardwareInterrupts();

int LouPrintPanic(char* format, ...);

void StoreAdvancedRegisters(uint64_t ContextHandle);
void RestoreAdvancedRegisters(uint64_t ContextHandle);




void InterruptRouter(uint64_t Interrupt, uint64_t Args) {
    //LouKIRQL Irql;
    //LouKeSetIrqlNoFlagUpdate(HIGH_LEVEL, &Irql);
    //uint64_t ContextHandle = 0x00;
    PINTERRUPT_ROUTER_ENTRY TmpEntry = &InterruptRouterTable[Interrupt]; 
    if(InterruptRouterTable[Interrupt].ListCount){
        if(InterruptRouterTable[Interrupt].NeedFlotationSave){
            //SaveEverythingWithInterruptBuffer(&ContextHandle);
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
            //RestoreEverythingWithInterruptBuffer(&ContextHandle);
        }
        //LouKeSetIrqlNoFlagUpdate(Irql, 0x00);
        ApicHalSignalLocalApicEoi();
        return;
    }
    //LouKeSetIrqlNoFlagUpdate(Irql, 0x00);
    ApicHalSignalLocalApicEoi();
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