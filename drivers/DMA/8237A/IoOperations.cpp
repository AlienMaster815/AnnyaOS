#include "8237A.h"

static spinlock_t IoLock = {0};

static const UINT16 DmaBaseAddrReg[8] = {
    0, DMA16_ST_ADDR_REG_C1, DMA16_ST_ADDR_REG_C2, DMA16_ST_ADDR_REG_C3,
    0, DMA16_ST_ADDR_REG_C5, DMA16_ST_ADDR_REG_C6, DMA16_ST_ADDR_REG_C7
};

static const UINT16 DmaPageReg[8] = {
    0, C1_PAGE_ADDRESS_REGISTER, C2_PAGE_ADDRESS_REGISTER, C3_PAGE_ADDRESS_REGISTER,
    0, C5_PAGE_ADDRESS_REGISTER, C6_PAGE_ADDRESS_REGISTER, C7_PAGE_ADDRESS_REGISTER
};

void Write16Bit8237ARegister(UINT8 Channel, UINT16 Port, UINT16 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&IoLock, &Irql);
    UINT8 Controller = (Channel < 4) ? 0 : 1;
    outb(DMA_CLEAR_FF_REG(Controller), 0x00);
    outb(Port, Value & 0xFF);
    outb(Port, (Value >> 8) & 0xFF);
    LouKeReleaseSpinLock(&IoLock, &Irql);
}

void Write8Bit8237ARegister(UINT16 Port, UINT8 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&IoLock, &Irql);
    outb(Port, Value);
    LouKeReleaseSpinLock(&IoLock, &Irql);
}

UINT8 Read8Bit8237ARegister(UINT16 Port){
    UINT8 Result;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&IoLock, &Irql);
    Result = inb(Port);
    LouKeReleaseSpinLock(&IoLock, &Irql);
    return Result;
}

LOUSTATUS Write8237AStartAddress(UINT8 Channel, UINT32 DmaAddress) {
    if (Channel > 7 || Channel == 0 || Channel == 4) {
        LouPrint("Invalid Channel %u\n", Channel);
        return STATUS_INVALID_PARAMETER;
    }
    UINT32 AddrForController = DmaAddress;
    if (Channel >= 5) {
        AddrForController >>= 1;
    }
    Write16Bit8237ARegister(Channel, DmaBaseAddrReg[Channel], AddrForController);
    Write8Bit8237ARegister(DmaPageReg[Channel], (DmaAddress >> 16) & 0xFF);
    return STATUS_SUCCESS;
}


LOUSTATUS Mask8237ADrq(UINT8 Channel){
    if(Channel > 7){
        LouPrint("Invalid Channel:%d\n", Channel);
        return STATUS_INVALID_PARAMETER;
    }

    UINT16 Port = (Channel > 3) ? (DMA16_MASK_RESET_4_7) : (DMA16_MASK_RESET_0_3);
    UINT8 Register = Read8Bit8237ARegister(Port);
    Register |= ((Channel > 3) ? (1 << (Channel - 4)) : (1 << Channel));
    Write8Bit8237ARegister(
        Port,
        Register
    );
    return STATUS_SUCCESS;
}

LOUSTATUS SetDmaMode(UINT8 Channel, UINT8 ModeConfig){
    if(Channel > 7 || (Channel == 0) || (Channel == 4)){
        LouPrint("Invalid Channel\n");
        return STATUS_INVALID_PARAMETER;
    }
    
    return STATUS_SUCCESS;
}