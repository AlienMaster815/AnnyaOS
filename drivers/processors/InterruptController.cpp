#include <LouDDK.h>

static void (*EoiHandler[512])() = {0x00};
static void (*UnmaskHandler[512])(UINT8 Irq) = {0x00};
static void (*MaskHandler[512])(UINT8 Irq) = {0x00};

KERNEL_IMPORT UINT64 GetLKPCB();

    //EoiHandler      = (void (**)())     LouKeMallocArray(void**, Cpus, KERNEL_GENERIC_MEMORY);
    //UnmaskHandler   = (void (**)(UINT8))LouKeMallocArray(void**, Cpus, KERNEL_GENERIC_MEMORY);
    //MaskHandler     = (void (**)(UINT8))LouKeMallocArray(void**, Cpus, KERNEL_GENERIC_MEMORY);

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
    UINT8 ProcID = ((PLKPCB)GetLKPCB())->ProcID;
    if(EoiHandler[ProcID]){
        EoiHandler[ProcID]();
        LouKeMemoryBarrier();
    }
}

KERNEL_IMPORT void LouKeIcUnmaskIrq(UINT8 Irq){
    UINT8 ProcID = ((PLKPCB)GetLKPCB())->ProcID;
    if(UnmaskHandler[ProcID]){
        UnmaskHandler[ProcID](Irq);
        LouKeMemoryBarrier();
    }
}

KERNEL_IMPORT void LouKeIcMaskIrq(UINT8 Irq){
    UINT8 ProcID = ((PLKPCB)GetLKPCB())->ProcID;
    if(MaskHandler[ProcID]){
        MaskHandler[ProcID](Irq);
        LouKeMemoryBarrier();
    }
}