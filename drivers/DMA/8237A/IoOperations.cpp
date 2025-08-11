#include "8237A.h"

static spinlock_t IoLock = {0};

static inline LOUSTATUS ReleaseIoLock(LOUSTATUS Status, LouKIRQL* Irql) {
    LouKeReleaseSpinLock(&IoLock, Irql);
    return Status;
}

static const UINT16 DmaBaseAddrReg[8] = {
    0, DMA16_ST_ADDR_REG_C1, DMA16_ST_ADDR_REG_C2, DMA16_ST_ADDR_REG_C3,
    0, DMA16_ST_ADDR_REG_C5, DMA16_ST_ADDR_REG_C6, DMA16_ST_ADDR_REG_C7
};

static const UINT16 DmaPageReg[8] = {
    0, C1_PAGE_ADDRESS_REGISTER, C2_PAGE_ADDRESS_REGISTER, C3_PAGE_ADDRESS_REGISTER,
    0, C5_PAGE_ADDRESS_REGISTER, C6_PAGE_ADDRESS_REGISTER, C7_PAGE_ADDRESS_REGISTER
};

LOUSTATUS Write8237AStartAddress(UINT8 Channel, UINT32 DmaAddress) {
    if (Channel > 7 || Channel == 0 || Channel == 4) {
        LouPrint("Invalid Channel %u\n", Channel);
        return STATUS_INVALID_PARAMETER;
    }

    LouKIRQL Irql;
    LouKeAcquireSpinLock(&IoLock, &Irql);

    UINT32 AddrForController = DmaAddress;
    if (Channel >= 5) {
        AddrForController >>= 1;
    }

    UINT8 Controller = (Channel < 4) ? 0 : 1;
    outb(DMA_CLEAR_FF_REG(Controller), 0x00);

    outb(DmaBaseAddrReg[Channel], AddrForController & 0xFF);
    outb(DmaBaseAddrReg[Channel], (AddrForController >> 8) & 0xFF);
    outb(DmaPageReg[Channel], (DmaAddress >> 16) & 0xFF);

    return ReleaseIoLock(STATUS_SUCCESS, &Irql);
}
