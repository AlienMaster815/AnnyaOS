#include "../UsbCore.h"

DRIVER_EXPORT
LOUSTATUS 
UsbCoreDeviceRequestSetAddress(
    PUSB_DEVICE_OBJECT  UsbDevice,
    UINT8               Address
){
    if((!UsbDevice) || (!Address)){
        return STATUS_INVALID_PARAMETER;
    }
    PUSB_TRANSFER_OBJECT Transfer;
    LOUSTATUS Status = _UsbCoreDeviceRequestSetAddressStart(&Transfer, UsbDevice, Address);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    return _UsbCoreDeviceRequestSetAddressEnd(Transfer);
}