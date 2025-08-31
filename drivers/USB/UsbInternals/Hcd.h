#ifndef _HCD_H
#define _HCD_H

#include <LouDDK.h>
#include <usb.h>
#include <Hal.h>

#define HCD_BUFFER_POOLS 4

BOOL AmdUsbHcdHasWakeupQuirk(PPCI_DEVICE_OBJECT PDEV);

LOUSTATUS
LouKeCreateHcdBuffer(
    PUSB_HOST_CONTROLLER_DEVICE Hcd
);

LOUSTATUS 
LouKeUsbAddHcd(
    PUSB_HOST_CONTROLLER_DEVICE Hcd,
    UINT8                       Irq
);

void LouKeUsbNotifyAddBus(PUSB_BUS Bus);

PUSB_DEVICE LouKeAllocateUsbDevice(
    PUSB_DEVICE Parrent,
    PUSB_BUS    Bus,
    UINT64      Port
);

static inline PUSB_HOST_CONTROLLER_DEVICE UsbBusToHcd(PUSB_BUS Bus){
    return CONTAINER_OF(Bus, USB_HOST_CONTROLLER_DEVICE, UsbSelf);
}

PUSB_HOST_CONTROLLER_DEVICE LouKeUsbGetHcd(PUSB_HOST_CONTROLLER_DEVICE Hcd);

void LouKeUsbPutHcd(PUSB_HOST_CONTROLLER_DEVICE Hcd);

static 
inline 
bool 
AmdHcdResumeBug(
    PPCI_DEVICE_OBJECT PDEV, 
    const USB_HOST_CONTROLLER_DRIVER* HcdDriver
){

    if(!AmdUsbHcdHasWakeupQuirk(PDEV)){
        return false;
    }if(HcdDriver->DriverFlags & (HCD_USB1_1 | HCD_USB3_0)){
        return true;
    }
    return false;
}


#endif