#include "UsbCore.h"

LOUSTATUS UsbCoreCreateDefaultInEndpoint(PUSB_PIPE_OBJECT Pipe);
LOUSTATUS UsbCoreCreateDefaultOutEndpoint(PUSB_PIPE_OBJECT Pipe);

LOUSTATUS UsbCoreCreateDefaultPipe(PUSB_DEVICE_OBJECT UsbDevice){
    LOUSTATUS Status;
    UsbDevice->DefaultControlPipe.UsbDevice = UsbDevice;
    UsbDevice->DefaultControlPipe.PipeID = 0;
    PUSB_ENDPOINT_OBJECT NewEndpoint = LouKeMallocArray(USB_ENDPOINT_OBJECT, 2, KERNEL_GENERIC_MEMORY);
    if(!NewEndpoint){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    UsbDevice->DefaultControlPipe.EpoHandle = (PVOID)NewEndpoint;
    UsbDevice->DefaultControlPipe.EndpointObject[0] = &NewEndpoint[0];
    UsbDevice->DefaultControlPipe.EndpointObject[1] = &NewEndpoint[1];
    UsbDevice->DefaultControlPipe.PipeFlags = USB_PIPE_FLAGS_SET_INOUT(USB_PIPE_FLAGS_HAS_INPUT | USB_PIPE_FLAGS_HAS_OUTPUT);
    Status = UsbCoreCreateDefaultInEndpoint(&UsbDevice->DefaultControlPipe);    
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    return UsbCoreCreateDefaultOutEndpoint(&UsbDevice->DefaultControlPipe);    
}