#include <LouDDK.h>
#include <Hal.h>

LOUSTATUS LouKeInitializeNetworkManager(){

    LouPrint("Looking For Network Devices\n");
    //Scan For Eithernet Controllers
    LouPrint("Scanning For Ethernet Controllers\n");

    PCI_COMMON_CONFIG PciConfig;
    LouKeInitializePciCommonPacketAnyType(&PciConfig);

    PciConfig.Header.BaseClass = 0x02;
    PciConfig.Header.SubClass =  0x00;

    PPCI_DEVICE_GROUP PciDevices = LouKeOpenPciDeviceGroup(&PciConfig);
    uint8_t NumDev = LouKeGetPciCountByType(&PciConfig);

    for(uint8_t i = 0; i < NumDev; i++){
        P_PCI_DEVICE_OBJECT PDEV = PciDevices[i].PDEV;
        UNUSED PPCI_COMMON_CONFIG DeviceConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
        LouPrint("VendorID:%h\n", DeviceConfig->Header.VendorID);
        LouPrint("DeviceID:%h\n", DeviceConfig->Header.DeviceID);

    }

    LouPrint("Done Inuitializing Network Devices\n");
    return STATUS_SUCCESS;
}