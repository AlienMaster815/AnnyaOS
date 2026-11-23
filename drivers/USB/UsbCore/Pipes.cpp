#include "UsbCore.h"

LOUSTATUS UsbCoreCreateDefaultInEndpoint(PUSB_PIPE_OBJECT Pipe);
LOUSTATUS UsbCoreCreateDefaultOutEndpoint(PUSB_PIPE_OBJECT Pipe);
LOUSTATUS UsbCoreCreateDualDirectionEndpoint(PUSB_PIPE_OBJECT Pipe);

DRIVER_EXPORT
UINT8 
UsbCoreGetEndpointsPipeType(
    PUSB_ENDPOINT_OBJECT    Endpoint
){
    return USB_PIPE_FLAGS_GET_TYPE(Endpoint->PipeObject->PipeFlags);
}

LOUSTATUS UsbCoreCreateDefaultControlPipe(PUSB_DEVICE_OBJECT UsbDevice){
    LOUSTATUS Status;
    UsbDevice->DefaultControlPipe.UsbDevice = UsbDevice;
    UsbDevice->DefaultControlPipe.PipeID = 0;
    PUSB_ENDPOINT_OBJECT NewEndpoint = LouKeMallocType(USB_ENDPOINT_OBJECT, KERNEL_GENERIC_MEMORY);
    if(!NewEndpoint){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    UsbDevice->DefaultControlPipe.EpoHandle = (PVOID)NewEndpoint;
    UsbDevice->DefaultControlPipe.EndpointObject[0] = NewEndpoint;
    UsbDevice->DefaultControlPipe.PipeFlags = USB_PIPE_FLAGS_HAS_DUAL_DIRECTION | USB_PIPE_FLAGS_SET_TYPE(USB_PIPE_TYPE_CONTROL);
    return UsbCoreCreateDualDirectionEndpoint(&UsbDevice->DefaultControlPipe);
}