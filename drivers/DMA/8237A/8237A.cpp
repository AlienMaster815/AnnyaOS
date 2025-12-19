#define _INTERNAL_
#include "8237A.h"

LOUSTATUS 
Write8237AStartAddress(
    UINT8 Channel, 
    UINT32 DmaAddress
);
LOUSTATUS 
Mask8237ADrq(
    UINT8 Channel
);
LOUSTATUS 
UnMask8237ADrq(
    UINT8 Channel
);
LOUSTATUS 
Set8237ADmaMode(
    UINT8 Channel, 
    UINT8 ModeConfig
);
LOUSTATUS 
Set8237ACount(
    UINT8 Channel, 
    UINT16 Count
);

static mutex_t OperationLock = {0};

DRIVER_EXPORT
LOUSTATUS Initialize8237ADmaTransfer(
    PDMA16_TRANSFER_PACKET Packet
){
    LOUSTATUS Status;
    UINT8 DmaMode;
    MutexLock(&OperationLock);
    Status = Mask8237ADrq(Packet->Channel);
    if(Status != STATUS_SUCCESS){
        goto _DMA_TRANSFER_OPERATION_ERROR;
    }
    Status = Write8237AStartAddress(Packet->Channel, Packet->DmaAddress);
    if(Status != STATUS_SUCCESS){
        goto _DMA_TRANSFER_OPERATION_ERROR;
    }
    Status = Set8237ACount(Packet->Channel, Packet->Transferlength);
    if(Status != STATUS_SUCCESS){
        goto _DMA_TRANSFER_OPERATION_ERROR;
    }

    DmaMode = ((Packet->Channel > 3) ? (Packet->Channel - 4) : (Packet->Channel)) & 0b11;
    DmaMode |= ((Packet->Transfer & 0b11) << 2);
    DmaMode |= ((Packet->Auto & 0b1) << 4);
    DmaMode |= ((Packet->Down & 0b1) << 5);
    DmaMode |= ((Packet->Mode & 0b11) << 6);

    Status = Set8237ADmaMode(Packet->Channel, DmaMode);
    if(Status != STATUS_SUCCESS){
        goto _DMA_TRANSFER_OPERATION_ERROR;
    }
    Status = UnMask8237ADrq(Packet->Channel);
    MutexUnlock(&OperationLock);
    return Status;

    _DMA_TRANSFER_OPERATION_ERROR:
        MutexUnlock(&OperationLock);
        return Status;
}

LOUDDK_API_ENTRY
NTSTATUS 
DriverEntry(
    PDRIVER_OBJECT DrvObj,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("8237A.SYS:DriverEntry()\n");
    
    LouPrint("8237A.SYS:DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}