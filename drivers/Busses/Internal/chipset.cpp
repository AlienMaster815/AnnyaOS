#include <LouDDK.h>
#include <Hal.h>

LOUDDK_API_ENTRY
UINT16 
LouKeHalGetChipsetVendor(){
    PCI_COMMON_CONFIG Config;
    UINT16 Vendor = 0xFFFF;
    LouKeInitializePciCommonPacketAnyType(&Config);
    Config.Header.BaseClass = 0x06;
    Config.Header.SubClass = 0x01;

    UINT16 Members = LouKeGetPciCountByType(&Config);
    if(!Members){
        return Vendor;
    }
    PPCI_DEVICE_GROUP* Group = LouKeOpenPciDeviceGroup(&Config);

    LouKeClosePciDeviceGroup(Group);

    Vendor = ((PPCI_COMMON_CONFIG)Group[0]->PDEV->CommonConfig)->Header.VendorID;
    return Vendor;
}
