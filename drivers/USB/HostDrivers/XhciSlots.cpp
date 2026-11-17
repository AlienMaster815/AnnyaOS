#include "Xhci.h"


LOUSTATUS 
XhciEnableSlot(
    PXHCI_DEVICE    XhciDevice,
    UINT32*         SlotOut
){
    if((!XhciDevice) || (!SlotOut)){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS Status;    
    TRB_RING_HANDLE RingHandle;
    TRB_RING_HANDLE EventHandle;
    MutexLock(&XhciDevice->CommandRingManager.RingLock);
    MutexLock(&XhciDevice->EventRingManager.RingLock);
    Status = XhciAllocateCommandTrb(
        XhciDevice,
        &RingHandle
    );

    XhciEncodeEnableSlotTrb(
        (PXHCI_ENABLE_SLOT_COMMAND_TRB)RingHandle.Trb,
        RingHandle.TrbCycleBit
    );

    XhciDevice->DoorbellRegisters->Doorbell[0] = 0;

_TRY_AGAIN:

    SIZE Timeout = 1000;
    Status = XhciGetNextEventTrb(XhciDevice, &EventHandle);
    while((Status != STATUS_SUCCESS) && (Timeout)){
        Status = XhciGetNextEventTrb(XhciDevice, &EventHandle);
        sleep(100);
        Timeout -= 100;
    }
    if(Status != STATUS_SUCCESS){
        LouPrint("XhciEnableSlot():NO EVENT\n");
        while(1);
    }
    UINT8 TrbType = (EventHandle.Trb->DWord[3] >> 10) & 0x3F;
    if(TrbType != 33){
        goto _TRY_AGAIN;
    }
    UINT8 CompletionCode = (EventHandle.Trb->DWord[2] >> 24) & 0xFF;
    if(CompletionCode != 1){
        LouPrint("XhciEnableSlot():BAD COMPLETION\n");
        while(1);
    }
    *SlotOut = (EventHandle.Trb->DWord[3] >> 24) & 0xFF;

    MutexUnlock(&XhciDevice->CommandRingManager.RingLock);
    MutexUnlock(&XhciDevice->EventRingManager.RingLock);
    return STATUS_SUCCESS;

//_ERROR_OUT:

}