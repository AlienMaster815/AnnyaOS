#include "UsbCore.h"

DRIVER_EXPORT SIZE UsbCoreGetEndpointId(PUSB_ENDPOINT_OBJECT EndpointObject){
    return EndpointObject->PipeObject->PipeID;
}

DRIVER_EXPORT SIZE UsbCoreGetEndpointDeviceAddress(PUSB_ENDPOINT_OBJECT EndpointObject){
    return EndpointObject->PipeObject->UsbDevice->DeviceAddress;
}

PUSB_HCD_OBJECT UsbGetHcdObjectFromEndpoint(PUSB_ENDPOINT_OBJECT EndpointObject){
    return EndpointObject->PipeObject->UsbDevice->Hcd;
}

LOUSTATUS UsbCoreCreateDefaultInEndpoint(PUSB_PIPE_OBJECT Pipe){
    LOUSTATUS Status;
    if(!(USB_PIPE_FLAGS_GET_INOUT(Pipe->PipeFlags) & USB_PIPE_FLAGS_HAS_INPUT)){
        return STATUS_INVALID_PARAMETER;
    }
    PUSB_ENDPOINT_OBJECT InputEndpoint = Pipe->EndpointObject[USB_PIPE_FLAGS_IOFLAG_TO_VECTOR(USB_PIPE_FLAGS_HAS_INPUT)];
    if(!InputEndpoint){
        return STATUS_UNSUCCESSFUL;
    }   
    InputEndpoint->PipeObject = Pipe;
    InputEndpoint->Direction = USB_ENDPOINT_DIRECTION_IN;

    PUSB_HCD_OBJECT HcdObject = UsbGetHcdObjectFromEndpoint(InputEndpoint);
    
    if(HcdObject->Operations->HcdCreateEndpoint){
        Status = HcdObject->Operations->HcdCreateEndpoint(HcdObject, InputEndpoint);
        if(Status != STATUS_SUCCESS){
            LouPrint("UsbCoreCreateDefaultInEndpoint():Unable To Create Endpoint\n");
            return Status;
        }
    }
    LouPrint("UsbCoreCreateDefaultInEndpoint():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS UsbCoreCreateDefaultOutEndpoint(PUSB_PIPE_OBJECT Pipe){
    LOUSTATUS Status;
    if(!(USB_PIPE_FLAGS_GET_INOUT(Pipe->PipeFlags) & USB_PIPE_FLAGS_HAS_OUTPUT)){
        return STATUS_INVALID_PARAMETER;
    }
    PUSB_ENDPOINT_OBJECT OutputEndpoint = Pipe->EndpointObject[USB_PIPE_FLAGS_IOFLAG_TO_VECTOR(USB_PIPE_FLAGS_HAS_INPUT)];
    if(!OutputEndpoint){
        return STATUS_UNSUCCESSFUL;
    }   
    OutputEndpoint->PipeObject = Pipe;
    OutputEndpoint->Direction = USB_ENDPOINT_DIRECTION_OUT;


    PUSB_HCD_OBJECT HcdObject = UsbGetHcdObjectFromEndpoint(OutputEndpoint);
    
    if(HcdObject->Operations->HcdCreateEndpoint){
        Status = HcdObject->Operations->HcdCreateEndpoint(HcdObject, OutputEndpoint);
        if(Status != STATUS_SUCCESS){
            LouPrint("UsbCoreCreateDefaultOutEndpoint():Unable To Create Endpoint\n");
            return Status;
        }
    }
    LouPrint("UsbCoreCreateDefaultOutEndpoint():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}