//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include <LouDDK.h>
#include <Hal.h>

LOUAPI
UINT16 
LouKeHalGetChipsetVendor(){
    UINT16 Vendor = 0xFFFF;
    /*PCI_COMMON_CONFIG Config;
    LouKeInitializePciCommonPacketAnyType(&Config);
    Config.Header.BaseClass = 0x06;
    Config.Header.SubClass = 0x01;

    UINT16 Members = LouKeGetPciCountByType(&Config);
    if(!Members){
        return Vendor;
    }
    PPCI_DEVICE_GROUP* Group = LouKeOpenPciDeviceGroup(&Config);

    LouKeClosePciDeviceGroup(Group);

    Vendor = ((PPCI_COMMON_CONFIG)Group[0]->PDEV->CommonConfig)->Header.VendorID;*/
    LouPrint("LouKeHalGetChipsetVendor()\n");
    while(1);
    return Vendor;
}
