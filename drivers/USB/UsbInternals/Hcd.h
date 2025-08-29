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