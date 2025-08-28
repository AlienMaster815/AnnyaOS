#include <LouDDK.h>
#include <Hal.h>
#include <usb.h>

LOUDDK_API_ENTRY
LOUSTATUS 
LouKeUsbHcdPciProbe(
    PPCI_DEVICE_OBJECT PDEV, 
    const USB_HOST_CONTROLLER_DRIVER* HcdDriver
){
    LOUSTATUS Status;
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

    PUSB_HOST_CONTROLLER_DEVICE Hcd = LouKeAllocateUsbHostControllerDevice(HcdDriver, PDEV);
    if(!Hcd){
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto _USB_HCD_PROBE_FAILED_RELEASE_IRQS;
    }

    LouPrint("Chipset Vendor:%h\n", LouKeHalGetChipsetVendor());

    LouPrint("LouKeUsbHcdPciProbe() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;

_USB_HCD_PROBE_FAILED_RELEASE_IRQS:
    if((HcdDriver->DriverFlags & HCD_MASK) < HCD_USB3_0){
        LouPrint("HcdPci.cpp:Unfinished Function\n");//TODO:
        while(1);
    } 
    return Status;
}