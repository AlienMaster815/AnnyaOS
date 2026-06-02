#include "Pci.h"

static PCI_MANAGER_DATA PciData = {0};
static size_t RegisteredPciDevices = 0;
static mutex_t PciDataLock = {0};

//TODO Implement Registry loopkup

DRIVER_EXPORT LOUSTATUS PciHalRegisterPciDevice(
    PPCI_DEVICE_OBJECT  PDEV,
    string              RegistryEntry,
    string              DeviceManagerString
){

    PPCI_MANAGER_DATA Tmp = LouKeMallocType(PCI_MANAGER_DATA, KERNEL_GENERIC_MEMORY);
    Tmp->PDEV = PDEV;
    Tmp->RegistryEntry = (string)RegistryEntry;
    Tmp->DeviceManagerString = (string)DeviceManagerString;

    MutexLock(&PciDataLock);
    LouKeListAddTail(&Tmp->Peers, &PciData.Peers);
    RegisteredPciDevices++;
    MutexUnlock(&PciDataLock);

    PciHalPciDbgPrint("Registered Pci Device:%d\n", RegisteredPciDevices);
    PciHalPciDbgPrint("PCI BUS:%d :: SLOT:%d :: FUNC:%d\n", (UINT64)PDEV->Bus, (UINT64)PDEV->Slot, (UINT64)PDEV->Function);

    return STATUS_SUCCESS;
}

DRIVER_EXPORT PPCI_MANAGER_DATA PciHalGetPciDataTable(){
    return (PPCI_MANAGER_DATA)&PciData;
}

DRIVER_EXPORT uint8_t PciHalGetPciGlobalMembers(){
    return RegisteredPciDevices;
}

