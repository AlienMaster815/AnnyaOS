#include "UsbCore.h"

SIZE UsbCoreGetEndpointId(PUSB_ENDPOINT_OBJECT EndpointObject){
    return EndpointObject->PipeObject->PipeID;
}

SIZE UsbCoreGetEndpointDeviceAddress(PUSB_ENDPOINT_OBJECT EndpointObject){
    return EndpointObject->PipeObject->UsbDevice->DeviceAddress;
}

LOUSTATUS UsbCoreCreateDefaultInEndpoint(PUSB_PIPE_OBJECT Pipe){
    LouPrint("UsbCoreCreateDefaultInEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS UsbCoreCreateDefaultOutEndpoint(PUSB_PIPE_OBJECT Pipe){
    LouPrint("UsbCoreCreateDefaultOutEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}