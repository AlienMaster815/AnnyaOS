#include "UsbCore.h"

PUSB_TRANSFER_OBJECT UsbCoreAllocateUsbTransferObject(){
    return (PUSB_TRANSFER_OBJECT)LouKeAllocateFastObject("USB_TRANSFER_OBJECT");
}

void UsbCoreFreeUsbTransferObject(PUSB_TRANSFER_OBJECT Transfer){
    LouKeFreeFastObject("USB_TRANSFER_OBJECT", Transfer);
}

LOUSTATUS
UsbCoreAllocateUsbControlTransfer(
    PUSB_TRANSFER_OBJECT*   OutTransfer,
    PUSB_DEVICE_OBJECT      Device,
    PUSB_PIPE_OBJECT        Pipe,
    ULONG                   TransferFlags,
    SIZE                    DataSize,
    SIZE                    DataAlignment
){
    if((!OutTransfer) || (!Device) || (!Pipe)){
        return STATUS_INVALID_PARAMETER;
    }
    PUSB_TRANSFER_OBJECT NewTransferObject = UsbCoreAllocateUsbTransferObject();
    if(!NewTransferObject){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    NewTransferObject->ObjectType = USB_TRANSFER_OBJECT_CONTROL;
    PUSB_HCD_OBJECT HcdObject = Device->Hcd;

    NewTransferObject->UsbDevice = Device;
    NewTransferObject->Pipe = Pipe;
    NewTransferObject->TransferFlags = TransferFlags;    
    NewTransferObject->SetupData = LouKeDmaDeviceAllocateDmaMemory(&HcdObject->DmaDevice, sizeof(UINT64), GET_ALIGNMENT(UINT64));
    if(!NewTransferObject->SetupData){
        UsbCoreFreeUsbTransferObject(NewTransferObject);
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    if(DataSize){
        NewTransferObject->Transfer = LouKeCreateDmaTransfer(&HcdObject->DmaDevice, DataSize, DataAlignment);
        if(!NewTransferObject->Transfer){
            LouKeDmaDeviceFreeDmaMemory(&HcdObject->DmaDevice, NewTransferObject->SetupData);
            UsbCoreFreeUsbTransferObject(NewTransferObject);
            return STATUS_INSUFFICIENT_RESOURCES;
        }   
    }
    *OutTransfer = NewTransferObject;
    return STATUS_SUCCESS;
}

LOUSTATUS
UsbCoreFreeUsbControlTransfer(
    PUSB_TRANSFER_OBJECT Transfer
){
    if((!Transfer) || (Transfer->ObjectType != USB_TRANSFER_OBJECT_CONTROL)){
        return STATUS_INVALID_PARAMETER;
    }
    PUSB_HCD_OBJECT HcdObject = Transfer->UsbDevice->Hcd;
    if(Transfer->Transfer){
        LouKeDestroyDmaTransfer(Transfer->Transfer);
    }
    LouKeDmaDeviceFreeDmaMemory(&HcdObject->DmaDevice, Transfer->SetupData);
    UsbCoreFreeUsbTransferObject(Transfer);
    return STATUS_SUCCESS;
}