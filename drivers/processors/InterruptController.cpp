#include <LouDDK.h>

static void (*EoiHandler[512])() = {0x00};
static void (*UnmaskHandler[512])(UINT8 Irq) = {0x00};
static void (*MaskHandler[512])(UINT8 Irq) = {0x00};



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
    if(EoiHandler[GetCurrentCpuTrackMember()]){
        EoiHandler[GetCurrentCpuTrackMember()]();
        LouKeMemoryBarrier();
    }
}

KERNEL_IMPORT void LouKeIcUnmaskIrq(UINT8 Irq){
    if(UnmaskHandler[GetCurrentCpuTrackMember()]){
        UnmaskHandler[GetCurrentCpuTrackMember()](Irq);
        LouKeMemoryBarrier();
    }
}

KERNEL_IMPORT void LouKeIcMaskIrq(UINT8 Irq){
    if(MaskHandler[GetCurrentCpuTrackMember()]){
        MaskHandler[GetCurrentCpuTrackMember()](Irq);
        LouKeMemoryBarrier();
    }
}