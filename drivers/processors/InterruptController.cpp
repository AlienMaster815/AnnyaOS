#include <LouDDK.h>

static void (*EoiHandler[512])() = {0x00};
static void (*UnmaskHandler[512])(UINT8 Irq) = {0x00};
static void (*MaskHandler[512])(UINT8 Irq) = {0x00};

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

void LouKeInitializeEoiHandler(PVOID Handler, UINT16 Cpu){
    EoiHandler[Cpu] = (void(*)())Handler;
    LouKeMemoryBarrier();
}

void LouKeInitializeUnmaskHandler(PVOID Handler, UINT16 Cpu){
    UnmaskHandler[Cpu] = (void(*)(UINT8))Handler;
    LouKeMemoryBarrier();
}

void LouKeInitializeMaskHandler(PVOID Handler, UINT16 Cpu){
    MaskHandler[Cpu] = (void(*)(UINT8))Handler;
    LouKeMemoryBarrier();
}

KERNEL_IMPORT void LouKeSendIcEOI(){
    if(EoiHandler[get_processor_id()]){
        EoiHandler[get_processor_id()]();
        LouKeMemoryBarrier();
    }
}

KERNEL_IMPORT void LouKeIcUnmaskIrq(UINT8 Irq){
    if(UnmaskHandler[get_processor_id()]){
        UnmaskHandler[get_processor_id()](Irq);
        LouKeMemoryBarrier();
    }
}

KERNEL_IMPORT void LouKeIcMaskIrq(UINT8 Irq){
    if(MaskHandler[get_processor_id()]){
        MaskHandler[get_processor_id()](Irq);
        LouKeMemoryBarrier();
    }
}