//Copyright GPL-2 Tyler Grenier (2025 - 2026)

#include "Xhci.h"

LOUSTATUS XhciResetHcdDevice(PUSB_HCD_OBJECT Hcd);
LOUSTATUS XhciStartHcdDevice(PUSB_HCD_OBJECT Hcd);
LOUSTATUS XhciStopHcdDevice(PUSB_HCD_OBJECT Hcd);
LOUSTATUS XhciHcdCreateEndpoint(PUSB_HCD_OBJECT Hcd, PUSB_ENDPOINT_OBJECT NewEndpoint);
LOUSTATUS XhciHcdDestroyEndpoint(PUSB_ENDPOINT_OBJECT Endpoint);


RHPORT_STATUS XhciGetHcdRhPortStatus(PUSB_HCD_OBJECT Hcd, UINT32 Port);
LOUSTATUS XhciResetRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port);
LOUSTATUS XhciStartRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port);
LOUSTATUS XhciStopRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port);

LOUSTATUS XhciPrepTransfer(PUSB_TRANSFER_DATA Transfer);
LOUSTATUS XhciCommitTransfer(PUSB_TRANSFER_DATA Transfer);

#define XHCI_INTEL_PANTHER_POINT_QUIRK 1

static USB_HCD_OPERATIONS XhciHcdOperations = {
    //Host Operations
    .ResetHcdDevice = XhciResetHcdDevice,
    .StartHcdDevice = XhciStartHcdDevice,
    .StopHcdDevice = XhciStopHcdDevice,
    .HcdCreateEndpoint = XhciHcdCreateEndpoint,
    .HcdDestroyEndpoint = XhciHcdDestroyEndpoint,
    //Roothub Operations
    .GetHcdRhPortStatus = XhciGetHcdRhPortStatus,
    .ResetRhPort = XhciResetRhPort,
    .StartRhPort = XhciStartRhPort,
    .StopRhPort = XhciStopRhPort,
    //Transfer Operations
    .PrepTransfer = XhciPrepTransfer,
    .CommitTransfer = XhciCommitTransfer,
};

LOUSINE_PCI_DEVICE_TABLE SupportedXhciPciDevices[] = {
    //{.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x1E31, .BoardID = XHCI_INTEL_PANTHER_POINT_QUIRK, .SimpleEntry = true},
    {.BaseClass = 0x0C, .SubClass = 0x03, .ProgIf = 0x30, .BoardID = 0, .GenericEntry = true},
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

    //if(SupportedXhciPciDevices[PDEV->DeviceID].BoardID){
    //    LouPrint("Quirk Detected\n");
    //    while(1);
    //}

    PciHalEnableMemorySpace(PDEV);

    PciHalEnableBusMaster(PDEV);
    
    PciHalMapPciResource(PDEV, XHCI_MMIO_REGISTERS_BAR, PCI_IOMAP_FLAGS_DEFAULT_MAPPING);

    NewXhciDevice->CapRegisters = (PXHCI_CAPABILITIES_REGISTER)PciHalGetIoRegion(PDEV, XHCI_MMIO_REGISTERS_BAR, XHCI_MMIO_REGISTERS_OFFSET);

    LouPrint("XHCI.SYS:CAP_REG:%h\n", NewXhciDevice->CapRegisters);

    NewXhciDevice->OperationalRegisters = GET_XHCI_OPERATIONAL_REGISTERS(NewXhciDevice->CapRegisters);
    NewXhciDevice->DoorbellRegisters = XHCI_GET_DOORBELL_REGISTERS(NewXhciDevice->CapRegisters);
    NewXhciDevice->RuntimeRegisters = XHCI_GET_RUNTIME_REGISTERS(NewXhciDevice->CapRegisters);

    XhciGetCapabilities(NewXhciDevice);
    
    PLOUSINE_DMA_DEVICE DmaDevice;
    Status = XhciInitializeMemoryManagement(NewXhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS::AddDevice():XhciInitializeMemoryManagement():FAILED\n");
        while(1);
    }    

    Status = XhciAllocatePageSizeDmaMemory(
        NewXhciDevice, 
        XHCI_DEVICE_CONTEXT_BASE_ADDRESS_ARRAY_ALLOCATION_SIZE(NewXhciDevice->Capabilities.MaxSlots), 
        64, 
        &NewXhciDevice->VirtualDcbaapAddress
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:AddDevice():Could Not Allocate Data For Dcbaa\n");
        while(1);
    }

    LouPrint("XHCI.SYS:New Dcbaa Virtual Address :%h\n", NewXhciDevice->VirtualDcbaapAddress);
    LouPrint("XHCI.SYS:New Dcbaa Physical Address:%h\n", XhciGetDmaAddress(NewXhciDevice->VirtualDcbaapAddress));

    XhciInitializeCommandRingManager(NewXhciDevice);

    //PAGE 80

    //NOTE: Page 104 is the Command Ring Operation Information

    //NOTE: Page 439 is a table of all the data structures

    //TODO: Initialize Interrupts    

    LouPrint("XHCI.SYS::AddDevice():HERE\n\n");
    while(1);

    Status = UsbCoreCreateHcdObject(
        NewXhciDevice->PDEV,
        USBHCD_FLAGS_SET_VERSION(3),
        NewXhciDevice,
        &NewXhciDevice->TransferDmaDevice,
        &XhciHcdOperations
    );
    if(Status != STATUS_SUCCESS){
        LouKeFree(NewXhciDevice);
        return STATUS_INSUFFICIENT_RESOURCES;
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
