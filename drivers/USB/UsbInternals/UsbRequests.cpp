#include <LouDDK.h>
#include <usb.h>

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

LOUSTATUS LouKeUsbCommitRequest(PUSB_HOST_IO_PACKET IoPacket){
    
    PUSB_TOPOLOGY_TREE Topology = CONTAINER_OF(IoPacket->FunctionDevice, USB_TOPOLOGY_TREE, FunctionDevice);
    PUSB_HOST_DEVICE Host = Topology->HostIdentifier; 
    
    if(Host->Operations.UsbHcdCommitRequest){
        return Host->Operations.UsbHcdCommitRequest(IoPacket);
    }

    return STATUS_UNSUCCESSFUL;
}

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