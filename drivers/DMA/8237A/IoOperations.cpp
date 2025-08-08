#include "8237A.h"

static spinlock_t IoLock = {0};

//just to make my life easier
static inline LOUSTATUS ReleaseIoLock(LOUSTATUS Status, LouKIRQL* Irql){
    LouKeReleaseSpinLock(&IoLock, Irql);
    return Status;
}


LOUSTATUS Write8237AStartAddressRegister(UINT8 Channel, UINT16 Address){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&IoLock, &Irql);
    switch(Channel){
        case 1:
            outw(DMA16_ST_ADDR_REG_C1, Address);
            return ReleaseIoLock(STATUS_SUCCESS, &Irql);
        case 5:
            outw(DMA16_ST_ADDR_REG_C5, Address);
            return ReleaseIoLock(STATUS_SUCCESS, &Irql);
        case 2:
            outw(DMA16_ST_ADDR_REG_C2, Address);
            return ReleaseIoLock(STATUS_SUCCESS, &Irql);
        case 6:
            outw(DMA16_ST_ADDR_REG_C6, Address);
            return ReleaseIoLock(STATUS_SUCCESS, &Irql);
        case 3:
            outw(DMA16_ST_ADDR_REG_C3, Address);
            return ReleaseIoLock(STATUS_SUCCESS, &Irql);
        case 7:
            outw(DMA16_ST_ADDR_REG_C7, Address);
            return ReleaseIoLock(STATUS_SUCCESS, &Irql);
        default:
            LouPrint("Invalid Channel\n");
            break;
    }
    return ReleaseIoLock(STATUS_INVALID_PARAMETER, &Irql);
}



LOUSTATUS Write8237AStartAddress(UINT8 Channel, UINT32 DmaAddress){
    LOUSTATUS Status = Write8237AStartAddressRegister(Channel, DmaAddress & UINT16_MAX);
    if(Status != STATUS_SUCCESS){
        return Status;
    }


    return STATUS_SUCCESS;
}