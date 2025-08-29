#include <LouDDK.h>
#include <usb.h>
#include <Hal.h>
#include "Hcd.h"

BOOL AmdUsbHcdHasWakeupQuirk(PPCI_DEVICE_OBJECT PDEV){

    UINT16 VendorID = (((PPCI_COMMON_CONFIG)PDEV->CommonConfig)->Header.VendorID);

    if(LouKeHalGetChipsetVendor() == 0x1002){
        switch(VendorID){
            case 0x1E49:
            case 0x2063:
                return true;
        }
    }
    return false;
}