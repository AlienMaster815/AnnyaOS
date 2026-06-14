//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "Xhci.h"

static const USB_HOST_OPERATIONS XhciOperations = {
    .UsbHcdResetHostController = XhciResetHostController,
    .UsbHcdStopHostController = XhciStopHostController,
    .UsbHcdStartHostController = XhciStartHostController,
    .UsbHcdProbeRootHub = XhciProbeRootHub,
    .UsbHcdCommitRequest = XhciCommitRequest,
};


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
    LOUSTATUS Status;
    PXHCI_DEVICE NewXhciDevice = LouKeMallocType(XHCI_DEVICE, KERNEL_GENERIC_MEMORY);
    PPCI_DEVICE_OBJECT PDEV = PciHalGetPciDeviceObjectFromLdmDeviceObject(PlatformDevice);    
    NewXhciDevice->PDEV = PDEV;
    
    NewXhciDevice->HostDevice.BusAddresses = LouKeCreateIdentificationRange(1, 256);

    PciHalEnableMemorySpace(PDEV);

    PciHalEnableBusMaster(PDEV);
    
    PciHalMapPciResource(PDEV, XHCI_MMIO_REGISTERS_BAR, PCI_IOMAP_FLAGS_DEFAULT_MAPPING);

    NewXhciDevice->CapRegisters = (PXHCI_CAPABILITIES_REGISTER)PciHalGetIoRegion(PDEV, XHCI_MMIO_REGISTERS_BAR, XHCI_MMIO_REGISTERS_OFFSET);

    LouPrint("XHCI.SYS:CAP_REG:%h\n", NewXhciDevice->CapRegisters);

    NewXhciDevice->OperationalRegisters = (PXHCI_OPERATIONAL_REGISTERS)GET_XHCI_OPERATIONAL_REGISTERS(NewXhciDevice->CapRegisters);
    NewXhciDevice->DoorbellRegisters = XHCI_GET_DOORBELL_REGISTERS(NewXhciDevice->CapRegisters);
    NewXhciDevice->RuntimeRegisters = XHCI_GET_RUNTIME_REGISTERS(NewXhciDevice->CapRegisters);

    XhciGetCapabilities(NewXhciDevice);

    Status = XhciInitializeMemoryManagement(NewXhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS::AddDevice():XhciInitializeMemoryManagement():FAILED\n");
        while(1);
    }

    Status = PciHalAllocatePciIrqVectors(
        PDEV,
        1, //TODO:check spec to see how many interrupts XHCI actually supports
        PCI_IRQ_USE_LEGACY
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS::AddDevice():Unable To Allocate IRQs\n");
        while(1);
    }

    NewXhciDevice->HostDevice.Operations = XhciOperations;
    
    RegisterInterruptHandler(XhciInterruptHandler, PciHalGetIrqVector(PDEV, 0), false, (uint64_t)NewXhciDevice);

    Status = LouKeUsbAddHcd(&NewXhciDevice->HostDevice);

    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS::AddDevice():Unable To Register XHCI Host Device\n");
    }

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

    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;

    LOUSTATUS Status = PciHalRegisterLousinePciDeviceTable(DriverObject, SupportedXhciPciDevices);
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS::DriverEntry():ERROR Unable To Register Pci Device Table\n");
    }    

    LouPrint("XHCI.SYS::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

