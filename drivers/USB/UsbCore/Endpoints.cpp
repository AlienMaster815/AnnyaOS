#include "UsbCore.h"

SIZE UsbCoreGetEndpointId(PUSB_ENDPOINT_OBJECT EndpointObject){
    return EndpointObject->PipeObject->PipeID;
}

SIZE UsbCoreGetEndpointDeviceAddress(PUSB_ENDPOINT_OBJECT EndpointObject){
    return EndpointObject->PipeObject->UsbDevice->DeviceAddress;
}