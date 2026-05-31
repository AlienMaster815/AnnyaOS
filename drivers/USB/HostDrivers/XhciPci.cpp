//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "Xhci.h"


UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedXhciPciDevices[] = {
    {.BaseClass = 0x0C, .SubClass = 0x03, .ProgIf = 0x30, .GenericEntry = true},
    {0},
};

LOUAPI 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("XHCI.SYS::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("XHCI.SYS::UnloadDriver() STATUS_SUCCESS\n");
}


LOUSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){
    LouPrint("XHCI.SYS::AddDevice()\n");
    PXHCI_DEVICE NewXhciDevice = LouKeMallocType(XHCI_DEVICE, KERNEL_GENERIC_MEMORY);
    PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    NewXhciDevice->PDEV = PDEV;
    
    LouKeHalEnablePciDevice(PDEV);
    LouKeHalPciSetMaster(PDEV);

    LouKeHalMapPciResource(PDEV, XHCI_MMIO_REGISTERS_BAR, KERNEL_DMA_MEMORY);

    NewXhciDevice->CapRegisters = (PXHCI_CAPABILITIES_REGISTER)LouKePciGetIoRegion(PDEV, XHCI_MMIO_REGISTERS_BAR, XHCI_MMIO_REGISTERS_OFFSET);
    NewXhciDevice->OperationalRegisters = (PXHCI_OPERATIONAL_REGISTERS)GET_XHCI_OPERATIONAL_REGISTERS(NewXhciDevice->CapRegisters);
    NewXhciDevice->DoorbellRegisters = XHCI_GET_DOORBELL_REGISTERS(NewXhciDevice->CapRegisters);
    NewXhciDevice->RuntimeRegisters = XHCI_GET_RUNTIME_REGISTERS(NewXhciDevice->CapRegisters);

    XhciGetCapabilities(NewXhciDevice);


    LouPrint("XHCI.SYS::AddDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("XHCI.SYS::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)SupportedXhciPciDevices;

    LouPrint("XHCI.SYS::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

