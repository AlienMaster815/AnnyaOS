#include "UsbCore.h"

PUSB_DEVICE_OBJECT UsbCoreGetDeviceFromEndpoint(PUSB_ENDPOINT_OBJECT EndpointObject){
    return EndpointObject->PipeObject->UsbDevice;
}