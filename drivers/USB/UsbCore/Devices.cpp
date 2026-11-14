#include "UsbCore.h"

LOUSTATUS UsbCoreCreateDefaultPipe(PUSB_DEVICE_OBJECT UsbDevice);

PUSB_DEVICE_OBJECT UsbCoreGetDeviceFromEndpoint(PUSB_ENDPOINT_OBJECT EndpointObject){
    return EndpointObject->PipeObject->UsbDevice;
}

LOUSTATUS 
UsbCoreCreateDefaultUsbDeviceObject(
    PUSB_HCD_OBJECT HostObject
){
    HostObject->DefaultDevice.Hcd = HostObject;
    HostObject->DefaultDevice.DeviceAddress = 0x00;
    return UsbCoreCreateDefaultPipe(&HostObject->DefaultDevice);
}