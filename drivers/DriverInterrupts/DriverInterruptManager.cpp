#include <LouDDK.h>
#include <NtAPI.h>

KERNEL_IMPORT uint8_t GetGlobalInterrupt();
KERNEL_IMPORT void ioapic_unmask_irq(uint8_t irq);
KERNEL_IMPORT void PS2KeyboardHandler();
KERNEL_IMPORT uint8_t GetTotalHardwareInterrupts();


#pragma pack(push, 1) // Pack structs on 1-byte boundary

class HWILM{
    public:
    HWILM();
    ~HWILM();

    LOUSTATUS InitializeHWilmEntry(void(*Handler)(uint64_t), bool ERS);
    LOUSTATUS DestroyHWilmEntry(void(*Handler)(uint64_t));
    void HandleHWilms(uint64_t Rsp);
    bool DoesInterruptNeedToSaveFloatPoints();

    private:
    void(*Handlers[32])(uint64_t Rsp) = {0x00};
    bool ExtraRegisterSavePriv;

};

#pragma pack(pop) // Restore previous packing

//class HWILM{
    //public:
HWILM::HWILM(){

}
    
HWILM::~HWILM(){

}

LOUSTATUS HWILM::InitializeHWilmEntry(void(*Handler)(uint64_t), bool ERS){

    for(uint8_t i = 0; i < 32; i++){
        if(Handlers[i] == 0x00){
            Handlers[i] = Handler;
            return STATUS_SUCCESS;
        }
    }

    if(!ExtraRegisterSavePriv){
        ExtraRegisterSavePriv = ERS;
    }

    return STATUS_UNSUCCESSFUL;
}

LOUSTATUS HWILM::DestroyHWilmEntry(void(*Handler)(uint64_t)){


    return STATUS_SUCCESS;
}

void HWILM::HandleHWilms(uint64_t Rsp){

    for(uint8_t i = 0 ; i < 32; i++){
        if(Handlers[i] != 0x00){
            Handlers[i](Rsp);
        }
    }

}

bool HWILM::DoesInterruptNeedToSaveFloatPoints(){
    return ExtraRegisterSavePriv;
}


    //private:
    //void(*Handler[32])();
//};

static HWILM* hwilms;

LOUDDK_API_ENTRY LOUSTATUS InitializeDynamicHardwareInterruptHandleing(){

    uint8_t TotalHardwareInterrupts = GetTotalHardwareInterrupts();

    hwilms = (HWILM*)LouMallocEx(sizeof(HWILM) * TotalHardwareInterrupts, sizeof(HWILM));

	return STATUS_SUCCESS;
}

KERNEL_IMPORT uint8_t FindTrueIRQ(uint8_t IRQ);

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

LOUDDK_API_ENTRY LOUSTATUS RegisterHardwareInterruptHandler(void(*InterruptHandler)(uint64_t), uint8_t PIN, bool ExtraRegisterSave){

    LOUSTATUS Status = STATUS_SUCCESS;

    uint8_t IRQ = FindTrueIRQ(PIN);

    LouPrint("Registering Interrupt Handler To Interrupt Request:%d Via Pin:%d\n", IRQ ,PIN);

    Status = hwilms[IRQ].InitializeHWilmEntry(InterruptHandler, ExtraRegisterSave);

    if(NT_SUCCESS(Status)){
        ioapic_unmask_irq(PIN);
        return Status;
    }
    else {
        return Status;
    }
}

LOUDDK_API_ENTRY void HardwareInterruptManager(uint64_t Interrupt, uint64_t Rsp){

    uint8_t IRQ = (Interrupt - 0x20);
    
    hwilms[IRQ].HandleHWilms(Rsp);
}

LOUDDK_API_ENTRY
bool DoesHardwareInterruptNeedFloatPointSaves(uint8_t InterruptNumber){
    bool Result = hwilms[InterruptNumber].DoesInterruptNeedToSaveFloatPoints();
    return Result;
}