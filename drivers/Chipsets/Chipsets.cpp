#include <LouDDK.h>
#include <Hal.h>

void InitializeAmdVendorChipset(PPCI_DEVICE_GROUP Chipsets);

LOUDDK_API_ENTRY
void InitializeInternalChipsetHostDriver(){
    LouPrint("Initializing Main Chipset Driver\n");
    PCI_COMMON_CONFIG Config;

    LouKeInitializePciCommonPacketAnyType(&Config);

    Config.Header.BaseClass = 0x06;

    UNUSED uint8_t ChipsetCount = LouKeGetPciCountByType(&Config);
    PPCI_DEVICE_GROUP* ChipsetGroup = LouKeOpenPciDeviceGroup(&Config);

    if(!ChipsetGroup){
        return;
    }

    P_PCI_DEVICE_OBJECT PDEV = ChipsetGroup[0]->PDEV;
    PPCI_COMMON_CONFIG PConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
    
    switch(PConfig->Header.VendorID){
        case 0x1002:
            InitializeAmdVendorChipset(ChipsetGroup[0]);
            break;
        default:
            break;
    }
    LouPrint("Done Initializing Main Chipset Driver\n");
}