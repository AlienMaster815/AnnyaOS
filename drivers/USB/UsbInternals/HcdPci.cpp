#include <LouDDK.h>
#include <Hal.h>
#include <usb.h>
#include "Hcd.h"

BOOL AmdUsbHcdHasWakeupQuirk(PPCI_DEVICE_OBJECT PDEV);


LOUDDK_API_ENTRY
LOUSTATUS 
LouKeUsbHcdPciProbe(
    PPCI_DEVICE_OBJECT PDEV, 
    const USB_HOST_CONTROLLER_DRIVER* HcdDriver
){
    LOUSTATUS Status;
    PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
    LouPrint("LouKeUsbHcdPciProbe()\n");
    if(!HcdDriver){
        return STATUS_INVALID_PARAMETER;
    }

    if(LouKeHalEnablePciDevice(PDEV) != STATUS_SUCCESS){
        return STATUS_NO_SUCH_DEVICE;
    }

    if((HcdDriver->DriverFlags & HCD_MASK) < HCD_USB3_0){
        LouPrint("HcdPci.cpp:Unfinished Function\n");//TODO:
        while(1);
    } 

    PUSB_HOST_CONTROLLER_DEVICE Hcd = LouKeCreateUsbHostControllerDevice(HcdDriver, PDEV);
    if(!Hcd){
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto _USB_HCD_PROBE_FAILED_RELEASE_IRQS;
    }

    Hcd->AmdResumeBug = AmdHcdResumeBug(PDEV, HcdDriver);

    if(HcdDriver->DriverFlags & (HCD_MEMORY)){
        //non UHCI
        Hcd->IoRegionBase   = (UINTPTR)LouKePciGetIoRegion(PDEV, 0, 0x00);
        Hcd->IoRegionLimit  = LouKeHalGetPciBaseAddressSize(PDEV, 0);

        if(!Hcd->IoRegionBase){
            Status = STATUS_DEVICE_CONFIGURATION_ERROR;
            goto _HCD_FAILED_RELEASE_HCD;
        }

    }else{
        //UHCI...
    }

    if(LouKeHalEnablePciDevice(PDEV) != STATUS_SUCCESS){
        Status = STATUS_DEVICE_CONFIGURATION_ERROR;
        goto _HCD_FAILED_RELEASE_HCD;
    }

    if(Config->Header.SubClass == 0x20){

    }else{
        Status = LouKeUsbAddHcd(Hcd, 0);
    }

    LouPrint("LouKeUsbHcdPciProbe() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;

_HCD_FAILED_RELEASE_HCD:


_USB_HCD_PROBE_FAILED_RELEASE_IRQS:
    if((HcdDriver->DriverFlags & HCD_MASK) < HCD_USB3_0){
        LouPrint("HcdPci.cpp:Unfinished Function\n");//TODO:
        while(1);
    } 
    return Status;
}