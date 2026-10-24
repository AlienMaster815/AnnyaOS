//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "UsbCore.h"

void _UsbCoreDestroyUsbTransferDataHandle(
    PUSB_TRANSFER_DATA  TransferOut
){
    LouKeFree(TransferOut);
}

LOUSTATUS _UsbCoreCreateUsbTransferDataHandle(
    PUSB_HCD_OBJECT         HcdObject,
    USB_TRANSFER_DATA_TYPE  Type,
    PVOID                   Data,
    SIZE                    DataSize,
    PUSB_TRANSFER_DATA*     TransferOut
){

    PUSB_TRANSFER_DATA NewTransferItem = LouKeMallocType(USB_TRANSFER_DATA, KERNEL_GENERIC_MEMORY);
    if(!NewTransferItem){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    UINT64 DmaAddress;
    switch(Type){
        case USB_TRANSFER_DATA_TYPE_SETUP:
            RequestPhysicalAddress((UINT64)(UINT8*)Data, &DmaAddress);
            NewTransferItem->Setup.VAddress = Data;
            NewTransferItem->Setup.PAddress = (PVOID)(UINT8*)DmaAddress;
            break;
        case USB_TRANSFER_DATA_TYPE_DATA:
            RequestPhysicalAddress((UINT64)(UINT8*)Data, &DmaAddress);
            NewTransferItem->Data.VAddress = Data;
            NewTransferItem->Data.PAddress = (PVOID)(UINT8*)DmaAddress;
            NewTransferItem->Data.Size = DataSize;
            break;
        default:
            break;
    }
    NewTransferItem->Type = Type;
    *TransferOut = NewTransferItem;
    return STATUS_SUCCESS;
}

LOUSTATUS UsbCoreCreateUsbTransferDataHandle(
    PUSB_HCD_OBJECT         HcdObject,
    USB_TRANSFER_DATA_TYPE  Type,
    PVOID                   Data,
    SIZE                    DataSize,
    PUSB_TRANSFER_DATA*     TransferOut
){
    if((!HcdObject) || (!TransferOut) || (Type == USB_TRANSFER_DATA_TYPE_UNKOWN)){
        return STATUS_INVALID_PARAMETER;
    }
    return _UsbCoreCreateUsbTransferDataHandle(
        HcdObject, 
        Type,
        Data,
        DataSize,
        TransferOut
    );
}

void 
_UsbCoreCreateUsbDeviceRequestSetupPacketDataEx(
    PUSB_HCD_OBJECT HcdObject,   
    PVOID           UsbSetupOut
){
    LouKeDmaDeviceFreeDmaMemory(&HcdObject->DmaDevice, UsbSetupOut);
}

LOUSTATUS 
_UsbCoreCreateUsbDeviceRequestSetupPacketDataEx(
    PUSB_HCD_OBJECT HcdObject,
    UINT8           RequestType,
    UINT8           Request,
    UINT16          Value,
    UINT16          Index,
    UINT16          Length,   
    PVOID*          UsbSetupOut
){
    UINT8* NewSetupPacket = (UINT8*)LouKeDmaDeviceAllocateDmaMemory(&HcdObject->DmaDevice, 8, MAX(8, HcdObject->DmaTransferMinimumAlignment));
    if(!NewSetupPacket){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    NewSetupPacket[0] = RequestType;
    NewSetupPacket[1] = Request;
    NewSetupPacket[2] = Value & UINT8_MAX;
    NewSetupPacket[3] = (Value >> 8) & UINT8_MAX;
    NewSetupPacket[4] = Index & UINT8_MAX;
    NewSetupPacket[5] = (Index >> 8) & UINT8_MAX;
    NewSetupPacket[6] = Length & UINT8_MAX;
    NewSetupPacket[7] = (Length >> 8) & UINT8_MAX;
    return STATUS_SUCCESS;
}

LOUSTATUS 
_UsbCoreCreateUsbDeviceRequestSetupPacketEx(
    PUSB_HCD_OBJECT     HcdObject,
    UINT8               RequestType,
    UINT8               Request,
    UINT16              Value,
    UINT16              Index,
    UINT16              Length,   
    PUSB_TRANSFER_DATA* TransferOut
){
    PVOID SetupOut;
    LOUSTATUS Status = _UsbCoreCreateUsbDeviceRequestSetupPacketDataEx(
        HcdObject,
        RequestType,
        Request,
        Value,
        Index,
        Length,
        &SetupOut
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    return _UsbCoreCreateUsbTransferDataHandle(
        HcdObject, 
        USB_TRANSFER_DATA_TYPE_SETUP,
        SetupOut,
        8,
        TransferOut
    );
}

DRIVER_EXPORT
LOUSTATUS
UsbCoreCreateUsbDeviceRequestSetupPacketDataEx(
    PUSB_HCD_OBJECT HcdObject,
    UINT8           RequestType,
    UINT8           Request,
    UINT16          Value,
    UINT16          Index,
    UINT16          Length,   
    PVOID*          UsbSetupOut
){
    if((!HcdObject) || (!UsbSetupOut)){
        return STATUS_INVALID_PARAMETER;
    }
    return _UsbCoreCreateUsbDeviceRequestSetupPacketDataEx(
        HcdObject,
        RequestType,
        Request,
        Value,
        Index,
        Length,
        UsbSetupOut
    );
}

LOUSTATUS 
_UsbCoreCreateUsbDeviceRequestSetupPacketData(
    PUSB_HCD_OBJECT HcdObject,
    UINT8           Recipiant,
    UINT8           TypeOfRequest,
    UINT8           Direction,
    UINT8           Request,
    UINT16          Value,
    UINT16          Index,
    UINT16          Length,
    PVOID*          UsbSetupOut
){
    return _UsbCoreCreateUsbDeviceRequestSetupPacketDataEx(
        HcdObject,
        USB_DEVREQ_ENCODE_REQUEST_TYPE(Recipiant, TypeOfRequest, Direction),
        Request,
        Value,
        Index,
        Length,
        UsbSetupOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
UsbCoreCreateUsbDeviceRequestSetupPacketData(
    PUSB_HCD_OBJECT HcdObject,
    UINT8           Recipiant,
    UINT8           TypeOfRequest,
    UINT8           Direction,
    UINT8           Request,
    UINT16          Value,
    UINT16          Index,
    UINT16          Length,
    PVOID*          UsbSetupOut
){
    if((!HcdObject) || (!UsbSetupOut)){
        return STATUS_INVALID_PARAMETER;
    }
    return _UsbCoreCreateUsbDeviceRequestSetupPacketData(
        HcdObject,
        Recipiant,
        TypeOfRequest,
        Direction,
        Request,
        Value,
        Index,
        Length,
        UsbSetupOut
    );
}

LOUSTATUS 
UsbCoreCreateUsbDeviceRequestSetupPacketEx(
    PUSB_HCD_OBJECT     HcdObject,
    UINT8               RequestType,
    UINT8               Request,
    UINT16              Value,
    UINT16              Index,
    UINT16              Length,   
    PUSB_TRANSFER_DATA* TransferOut
){
    if((!HcdObject) || (!TransferOut)){
        return STATUS_INVALID_PARAMETER;
    }
    return _UsbCoreCreateUsbDeviceRequestSetupPacketEx(
        HcdObject,
        RequestType,
        Request,
        Value,
        Index,
        Length,
        TransferOut
    );
}

DRIVER_EXPORT
LOUSTATUS 
UsbCoreCreateSetAddressPacket(
    PUSB_DEVICE_OBJECT  UsbDevice,
    UINT16              NewAddress,
    PUSB_TRANSFER_DATA* TransferOut
){
    if(!UsbDevice){
        return STATUS_INVALID_PARAMETER;
    }
    PUSB_HCD_OBJECT HcdObject = UsbDevice->Hcd;
    if((!HcdObject) || (!TransferOut)){
        return STATUS_INVALID_PARAMETER;
    } 
    PUSB_TRANSFER_DATA NewTransferItem;
    LOUSTATUS Status = _UsbCoreCreateUsbDeviceRequestSetupPacketEx(
        HcdObject,
        0b00000000,
        USB_DEVREQ_REQUEST_SET_ADDRESS,
        NewAddress,
        0,
        0,
        TransferOut
    );
    Status = _UsbCoreCreateUsbTransferDataHandle(
        HcdObject,
        USB_TRANSFER_DATA_TYPE_STATUS,
        0x00,
        0x00,
        &NewTransferItem
    );
    if(Status != STATUS_SUCCESS){
        _UsbCoreCreateUsbDeviceRequestSetupPacketDataEx(HcdObject, (*TransferOut)->Setup.VAddress);
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    LouKeListAddTail(&NewTransferItem->Peers, &(*TransferOut)->Peers);
    return STATUS_SUCCESS;
}



/*

DRIVER_EXPORT
LOUSTATUS LouKeUsbCreateRequest(
    PUSB_FUNCTION_DEVICE    FunctionDevice,
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   Recipiant,
    UINT8                   RequestType,
    UINT8                   XferDirection,
    UINT8                   Request,
    UINT16                  Value,
    UINT16                  Index,
    UINT16                  Length,
    PVOID                   Data
){
    //LouPrint("LouKeUsbCreateRequest()\n");
    if((!FunctionDevice) || (!IoPacket) || (Recipiant > 0x0F) || (RequestType > 0x03) || (XferDirection > 1)){
        LouPrint("Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }
    
    memset(IoPacket, 0, sizeof(USB_HOST_IO_PACKET));

    IoPacket->FunctionDevice = FunctionDevice;
    IoPacket->RequestType |= (Recipiant << USB_REQUEST_RECIPIANT_SHIFT);
    IoPacket->RequestType |= (RequestType << USB_REQUEST_TYPE_SHIFT);
    IoPacket->RequestType |= (XferDirection << USB_REQUEST_XFER_DIRECTION_SHIFT);
    IoPacket->Request = Request;
    IoPacket->Value = Value;
    IoPacket->Index = Index;
    IoPacket->Length = Length;
    IoPacket->Data = Data;

    //LouPrint("LouKeUsbCreateRequest() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS LouKeUsbCommitRequest(PUSB_HOST_IO_PACKET IoPacket){
    
    PUSB_TOPOLOGY_TREE Topology = CONTAINER_OF(IoPacket->FunctionDevice, USB_TOPOLOGY_TREE, FunctionDevice);
    PUSB_HOST_DEVICE Host = Topology->HostIdentifier; 
    
    if(Host->Operations.UsbHcdCommitRequest){
        return Host->Operations.UsbHcdCommitRequest(IoPacket);
    }

    return STATUS_UNSUCCESSFUL;
}

DRIVER_EXPORT
LOUSTATUS LouKeUsbGetDescriptorRequest(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   DescriptorType,
    UINT8                   DescriptorIndex,
    UINT16                  Length,
    UINT16                  LanguageId,
    PVOID                   Data
){
    //LouPrint("LouKeUsbGetDescriptorRequest()\n");
    if((!FunctionDevice) || (!IoPacket)){
        LouPrint("Invalid Parameter\n");
        return STATUS_SUCCESS;
    }
    LOUSTATUS Status;
    UINT16 Value = (DescriptorType << 8) | DescriptorIndex;

    Status = LouKeUsbCreateRequest(
        FunctionDevice,
        IoPacket,
        USB_RECIPIANT_DEVICE,
        USB_TYPE_STANDARD,
        USB_XFER_D2H,
        USB_REQUEST_GET_DESCRIPTOR,
        Value,
        LanguageId,
        Length,
        Data
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("Error Initializing Usb Request\n");
        return Status;
    }

    IoPacket->TransferType = USB_TRANSFER_TYPE_CONTROL;

    Status = LouKeUsbCommitRequest(IoPacket);
    if(Status != STATUS_SUCCESS){
        LouPrint("Error Commiting Request\n");
        return Status;
    }

    //LouPrint("LouKeUsbGetDescriptorRequest() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS LouKeUsbSetAddress(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   NewAddress
){
    LOUSTATUS Status =  LouKeUsbCreateRequest(
        FunctionDevice,
        IoPacket,
        USB_RECIPIANT_DEVICE,
        USB_TYPE_STANDARD,
        USB_XFER_H2D,
        USB_REQUEST_SET_ADDRESS,
        NewAddress,
        0,
        0,
        0x00
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("Error Initializing Usb Request\n");
        return Status;
    }

    IoPacket->TransferType = USB_TRANSFER_TYPE_CONTROL;

    Status = LouKeUsbCommitRequest(IoPacket);
    if(Status != STATUS_SUCCESS){
        LouPrint("Error Commiting Request\n");
        return Status;
    }

    return Status;
}

DRIVER_EXPORT
LOUSTATUS LouKeUsbSetConfiguration(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   NewConfig
){
    LOUSTATUS Status =  LouKeUsbCreateRequest(
        FunctionDevice,
        IoPacket,
        USB_RECIPIANT_DEVICE,
        USB_TYPE_STANDARD,
        USB_XFER_H2D,
        USB_REQUEST_SET_CONFIGURATION,
        NewConfig,
        0,
        0,
        0x00
    );
    
    if(Status != STATUS_SUCCESS){
        LouPrint("Error Initializing Usb Request\n");
        return Status;
    }

    IoPacket->TransferType = USB_TRANSFER_TYPE_CONTROL;

    Status = LouKeUsbCommitRequest(IoPacket);
    if(Status != STATUS_SUCCESS){
        LouPrint("Error Commiting Request\n");
        return Status;
    }
    
    return Status;
}
*/