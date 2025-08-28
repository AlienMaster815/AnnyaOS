#include <LouAPI.h>
#include <Hal.h>

static PCI_MANAGER_DATA PciData = {0};
static size_t RegisteredPciDevices = 0;

LOUSTATUS RegisterPciDeviceToDeviceManager(
    PPCI_DEVICE_OBJECT PDEV,
    string RegistryEntry,
    string DeviceManagerString
){

    LouPrint("Registered Pci Device:%d\n", RegisteredPciDevices);
    LouPrint("PCI BUS:%h :: SLOT:%h :: FUNC:%h\n", PDEV->bus, PDEV->slot, PDEV->func);


    PPCI_MANAGER_DATA Tmp = &PciData;
    while(Tmp->Neigbors.NextHeader){
        Tmp = (PPCI_MANAGER_DATA)Tmp->Neigbors.NextHeader;
    }

    Tmp->Neigbors.NextHeader = (PListHeader)LouKeMallocType(PCI_MANAGER_DATA, KERNEL_GENERIC_MEMORY);

    Tmp = (PPCI_MANAGER_DATA)Tmp->Neigbors.NextHeader;

    Tmp->PDEV = PDEV;
    Tmp->RegistryEntry = (string)RegistryEntry;
    Tmp->DeviceManagerString = (string)DeviceManagerString;

    RegisteredPciDevices++;

    return STATUS_SUCCESS;
}

PPCI_MANAGER_DATA LouKeGetPciDataTable(){
    return (PPCI_MANAGER_DATA)PciData.Neigbors.NextHeader;
}

uint8_t LouKeGetPciGlobalMembers(){
    return RegisteredPciDevices;
}

