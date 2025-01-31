#include <LouDDK.h>

#define DEVICE_TABLE_TERMINATOR (DeviceTable[DeviceNumber].VendorID == 0x00) && (DeviceTable[DeviceNumber].DeviceID == 0x00) && (DeviceTable[DeviceNumber].GenericEntry == false)
#define ANY_PCI_CLASS 255


uint64_t LouKeGetLdmModuleDeviceID(PPCI_COMMON_CONFIG Config, PLOUSINE_PCI_DEVICE_TABLE DeviceTable){

    UNUSED uint16_t DeviceID, VendorID, SubVendorID, SubDeviceID;
    UNUSED uint8_t BaseClass, SubClass, Progif;

    DeviceID = Config->Header.DeviceID;
    VendorID = Config->Header.VendorID;
    SubDeviceID = Config->Header.u.type0.SubSystemID;
    SubVendorID = Config->Header.u.type0.SubVendorID;

    BaseClass = Config->Header.BaseClass;
    SubClass = Config->Header.SubClass;
    Progif = Config->Header.ProgIf;

    uint64_t DeviceNumber = 0;

    while(1){   

        if(
            ((DeviceTable[DeviceNumber].DeviceID == DeviceID || DeviceTable[DeviceNumber].DeviceID == ANY_PCI_ID) &&
            (DeviceTable[DeviceNumber].VendorID == VendorID || DeviceTable[DeviceNumber].VendorID == ANY_PCI_ID) &&
            (DeviceTable[DeviceNumber].SubVendorID == VendorID || DeviceTable[DeviceNumber].SubVendorID == ANY_PCI_ID) &&
            (DeviceTable[DeviceNumber].SubVendorID == VendorID || DeviceTable[DeviceNumber].SubVendorID == ANY_PCI_ID) &&
            (DeviceTable[DeviceNumber].BaseClass == BaseClass || DeviceTable[DeviceNumber].BaseClass == ANY_PCI_CLASS) &&
            (DeviceTable[DeviceNumber].SubClass == SubClass || DeviceTable[DeviceNumber].SubClass == ANY_PCI_CLASS)) || 
            (
                (DeviceTable[DeviceNumber].SimpleEntry) && 
                (DeviceTable[DeviceNumber].DeviceID == DeviceID || DeviceTable[DeviceNumber].DeviceID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].VendorID == VendorID || DeviceTable[DeviceNumber].VendorID == ANY_PCI_ID)
            ) ||
            (
                (DeviceTable[DeviceNumber].SimpleWithClass) && 
                (DeviceTable[DeviceNumber].DeviceID == DeviceID || DeviceTable[DeviceNumber].DeviceID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].VendorID == VendorID || DeviceTable[DeviceNumber].VendorID == ANY_PCI_ID) && 
                (DeviceTable[DeviceNumber].BaseClass == BaseClass || DeviceTable[DeviceNumber].BaseClass == ANY_PCI_CLASS) &&
                (DeviceTable[DeviceNumber].SubClass == SubClass || DeviceTable[DeviceNumber].SubClass == ANY_PCI_CLASS)
            ) ||  
            (
                (DeviceTable[DeviceNumber].AdvancedEntry) && 
                (DeviceTable[DeviceNumber].DeviceID == DeviceID || DeviceTable[DeviceNumber].DeviceID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].VendorID == VendorID || DeviceTable[DeviceNumber].VendorID == ANY_PCI_ID) && 
                (DeviceTable[DeviceNumber].SubVendorID == VendorID || DeviceTable[DeviceNumber].SubVendorID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].SubVendorID == VendorID || DeviceTable[DeviceNumber].SubVendorID == ANY_PCI_ID)
            ) || 
            (
                (DeviceTable[DeviceNumber].GenericEntry) && 
                (DeviceTable[DeviceNumber].BaseClass == BaseClass || DeviceTable[DeviceNumber].BaseClass == ANY_PCI_CLASS) &&
                (DeviceTable[DeviceNumber].SubClass == SubClass || DeviceTable[DeviceNumber].SubClass == ANY_PCI_CLASS)
            )
        ){
            return DeviceNumber;
        }

        if(DEVICE_TABLE_TERMINATOR){
            return (uint64_t)-1;
        }
        DeviceNumber++;
    }
}