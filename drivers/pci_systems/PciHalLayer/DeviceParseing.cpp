#include <LouDDK.h>
#include <Hal.h>




KERNEL_IMPORT
PPCI_MANAGER_DATA LouKeGetPciDataTable();
KERNEL_IMPORT
uint8_t LouKeGetPciGlobalMembers();

#define DEVICE_ID_MATCH ((SearchConfig->Header.DeviceID == DeviceConfig->Header.DeviceID) || (SearchConfig->Header.DeviceID == ANY_PCI_ID))
#define VENDOR_ID_MATCH ((SearchConfig->Header.VendorID == DeviceConfig->Header.VendorID) || (SearchConfig->Header.VendorID == ANY_PCI_ID))
#define SUBVEN_ID_MATCH ((SearchConfig->Header.u.type0.SubVendorID == DeviceConfig->Header.u.type0.SubVendorID) || (SearchConfig->Header.u.type0.SubVendorID == ANY_PCI_ID))
#define SUBSYS_ID_MATCH ((SearchConfig->Header.u.type0.SubSystemID == DeviceConfig->Header.u.type0.SubSystemID) || (SearchConfig->Header.u.type0.SubSystemID == ANY_PCI_ID))
#define SUBCLA_ID_MATCH ((SearchConfig->Header.SubClass == DeviceConfig->Header.SubClass) || (SearchConfig->Header.SubClass == ANY_PCI_CLASS))
#define CLASSC_ID_MATCH ((SearchConfig->Header.BaseClass == DeviceConfig->Header.BaseClass) || (SearchConfig->Header.BaseClass == ANY_PCI_CLASS))
#define PROGIF_ID_MATCH ((SearchConfig->Header.ProgIf == DeviceConfig->Header.ProgIf) || (SearchConfig->Header.ProgIf == ANY_PCI_CLASS))


static inline 
bool IsConfigValid(
    PPCI_COMMON_CONFIG SearchConfig, 
    PPCI_COMMON_CONFIG DeviceConfig
){

    if(!DEVICE_ID_MATCH){
        //LouPrint("Wrong Device\n");
        return false;
    }
    else if(!VENDOR_ID_MATCH){
        //LouPrint("Wrong Vendor\n");
        return false;
    }
    else if(!SUBVEN_ID_MATCH){
        //LouPrint("Wrong SubVendor\n");
        return false;
    }
    else if(!SUBSYS_ID_MATCH){
        //LouPrint("Wrong SubSys\n");
        return false;
    }
    else if (!SUBCLA_ID_MATCH){
        //LouPrint("Wrong SubClass\n");
        return false;
    }
    else if(!CLASSC_ID_MATCH){
        //LouPrint("Wrong Class\n");
        return false;
    }
    else if(!PROGIF_ID_MATCH){
        //LouPrint("Wrong ProgIf\n");
        return false;
    }

    return true;
}

LOUDDK_API_ENTRY 
uint8_t LouKeGetPciCountByType(
    PPCI_COMMON_CONFIG PciConfig
) {
    PPCI_MANAGER_DATA PciData = LouKeGetPciDataTable();
    uint8_t GlobalMembers = LouKeGetPciGlobalMembers();
    uint8_t LocalMembers = 0;

    // First pass: Count matching devices
    for (uint8_t i = 0; i < GlobalMembers; i++) {
        if (PciData->Neigbors.NextHeader) {
            PciData = (PPCI_MANAGER_DATA)PciData->Neigbors.NextHeader;
        } else {
            break;
        }
        if (IsConfigValid(PciConfig, (PPCI_COMMON_CONFIG)PciData->PDEV->CommonConfig)) {
            LocalMembers++;
        }
    }

    return LocalMembers;
}


LOUDDK_API_ENTRY 
PPCI_DEVICE_GROUP* LouKeOpenPciDeviceGroup(
    PPCI_COMMON_CONFIG PciConfig
) {

    PPCI_MANAGER_DATA PciData = LouKeGetPciDataTable();
    uint8_t GlobalMembers = LouKeGetPciGlobalMembers();
    uint8_t LocalMembers = LouKeGetPciCountByType(PciConfig);

    LouPrint("Global Members:%d\n", GlobalMembers);
    LouPrint("Local Members:%d\n", LocalMembers);

    // Allocate memory for result group based on number of matching devices
    if(!LocalMembers){
        return 0x00;
    }
    PciData = LouKeGetPciDataTable();

    PPCI_DEVICE_GROUP* Result = LouKeMallocArray(PPCI_DEVICE_GROUP, LocalMembers, KERNEL_GENERIC_MEMORY);

    // Second pass: Populate Result with matching devices
    uint8_t index = 0;
    for (uint8_t i = 0; i < GlobalMembers && index < LocalMembers; i++) {
        if (PciData->Neigbors.NextHeader) {
            PciData = (PPCI_MANAGER_DATA)PciData->Neigbors.NextHeader;
        } else {
            break;
        }        
        if (IsConfigValid(PciConfig, (PPCI_COMMON_CONFIG)PciData->PDEV->CommonConfig)) {
            Result[index] = PciData;
            index++;
        }
    }

    return Result;
}


void LouKeInitializePciCommonPacketAnyType(PPCI_COMMON_CONFIG PciCommon){

    PciCommon->Header.DeviceID = ANY_PCI_ID;
    PciCommon->Header.VendorID = ANY_PCI_ID;
    PciCommon->Header.u.type0.SubVendorID = ANY_PCI_ID;
    PciCommon->Header.u.type0.SubSystemID = ANY_PCI_ID;
    PciCommon->Header.BaseClass = ANY_PCI_CLASS;
    PciCommon->Header.SubClass = ANY_PCI_CLASS;
    PciCommon->Header.ProgIf = ANY_PCI_CLASS;

}

PPCI_DEVICE_OBJECT LouKeGetPDEV(uint8_t Bus, uint8_t Slot, uint8_t Function){

    PPCI_MANAGER_DATA PciData = LouKeGetPciDataTable();
    uint8_t GlobalMembers = LouKeGetPciGlobalMembers();

    for(uint8_t i = 0 ; i  < GlobalMembers; i++){

        if(
            (PciData->PDEV->bus == Bus) &&
            (PciData->PDEV->slot == Slot) &&
            (PciData->PDEV->func == Function)
        ){
            return PciData->PDEV;
        }
        if (PciData->Neigbors.NextHeader) {
            PciData = (PPCI_MANAGER_DATA)PciData->Neigbors.NextHeader;
        } else {
            break;
        }
    }

    return 0x00;
}