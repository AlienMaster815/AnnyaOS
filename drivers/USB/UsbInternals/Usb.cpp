#include <LouDDK.h>
#include <Hal.h>
#include <usb.h>
#include "Hcd.h"

void LouKeUsbEnableEnpoint(
    PUSB_DEVICE                 UsbDevice,
    PUSB_HOST_ENDPOINT          Ep,
    BOOL                        ResetEp
);

static bool UsbDeviceAuthorized(PUSB_DEVICE Device, PUSB_HOST_CONTROLLER_DEVICE Hcd){

	if (!Device->Parent){
		return true;
    }

    switch(Hcd->DevicePolicy){
        case USB_DEVICE_AUTHORITY_NONE:
        default: 
            return false;
        case USB_DEVICE_AUTHORITY_ALL:
            return true;
    }

    return false;
}

PUSB_DEVICE LouKeAllocateUsbDevice(
    PUSB_DEVICE Parrent,
    PUSB_BUS    Bus,
    UINT64      Port
){
    PUSB_DEVICE NewDevice;
    PUSB_HOST_CONTROLLER_DEVICE Hcd = UsbBusToHcd(Bus);
    UNUSED UINT64 RawPort = Port;
    
    NewDevice = LouKeMallocType(USB_DEVICE, KERNEL_GENERIC_MEMORY);

    if(!LouKeUsbGetHcd(Hcd)){
        LouKeFree(NewDevice);
        return 0x00;
    }

    if((Hcd->HcdDriver->LouKeMallocDevice) && (Parrent) && (!Hcd->HcdDriver->LouKeMallocDevice(Hcd, NewDevice))){
        LouKeUsbPutHcd(Hcd);
        LouKeFree(NewDevice);
        return 0x00;
    }

    NewDevice->UsbDeviceState = USB_STATE_ATTACHED;
    NewDevice->LowPowerModeDisableCount = 1;
    LouKeSetAtomic(&NewDevice->UrbNumber, 0);

    NewDevice->Endpoint0.EndpointDescriptor.Length = USB_DT_ENDPOINT_SIZE;
    NewDevice->Endpoint0.EndpointDescriptor.DescriptorType = USB_DT_ENDPOINT;
    NewDevice->UsbBus = Bus;

    LouKeUsbEnableEnpoint(NewDevice, &NewDevice->Endpoint0, false);
    NewDevice->UsbDeviceFlags1 |= 1;//submitable

    if(UsbDeviceAuthorized(NewDevice, Hcd)){
        NewDevice->UsbDeviceFlags1 |= (1 << 4); //authorized
    }
    return NewDevice;
}
