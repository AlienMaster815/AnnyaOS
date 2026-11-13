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

LOUSTATUS XhciInterruptHandler(UINT64 Data);

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

    Status = XhciAllocateScratchpadMemory(NewXhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:Unable To Allocate Stratchpad Memory\n");
        while(1);
    }
    if(NewXhciDevice->VirtualScratchpadArrayAddress){
        *(UINT64*)NewXhciDevice->VirtualDcbaapAddress = XhciGetDmaAddress(NewXhciDevice->VirtualScratchpadArrayAddress);
    }

    Status = XhciInitializeCommandRingManager(NewXhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:Fatal Error:Unable To Allocate Command Ring\n");
        while(1);
    }

    Status = PciHalAllocatePciIrqVectors(PDEV, 1, PCI_IRQ_USE_LEGACY | PCI_IRQ_USE_MSI | PCI_IRQ_USE_MSI_X);
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:Fatal Error:Unable To Allocate Interrupt Vectors\n");
        while(1);
    }
    Status = PciHalConnectIrqHandler(
        PDEV,
        (OPAQUE_PTR)XhciInterruptHandler,
        LirRoutine,
        (UINT64)(UINTPTR)(UINT8*)NewXhciDevice,
        0
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:Fatal Error:Unable To Connect Interrupt Handler\n");
        while(1);
    }
    Status = XhciAllocateUnrestrictedDmaMemory(
        NewXhciDevice, 
        sizeof(XHCI_EVENT_RING_SEGMENT_TABLE_ENTRY), 
        64, 
        &NewXhciDevice->VirtualErstbaAddress
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:Fatal Error:Unable To Allocate Event Ring Table\n");
        while(1);
    }
    Status = XhciInitializeEventRingManager(NewXhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:Fatal Error:Unable To Allocate Event Ring\n");
        while(1);
    }

    //PAGE 80

    //NOTE: Page 104 is the Command Ring Operation Information

    //NOTE: Page 439 is a table of all the data structures

    Status = UsbCoreCreateHcdObject(
        NewXhciDevice->PDEV,
        USBHCD_FLAGS_SET_VERSION(3),
        NewXhciDevice,
        &NewXhciDevice->TransferDmaDevice,
        &XhciHcdOperations
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:Fatal Error:Unable To Allocate Register Controller\n");
        while(1);
    }

    LouPrint("XHCI.SYS::AddDevice() STATUS_SUCCESS\n");
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
