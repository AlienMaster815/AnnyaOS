//Copyright GPL-2 Tyler Grenier (2025 - 2026)

#include "Ehci.h"

UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedEhciPciDevices[] = {
    {.BaseClass = 0x0C, .SubClass = 0x03, .ProgIf = 0x20, .GenericEntry = true},
    {0},
};

LOUAPI 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("EHCI.SYS::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("EHCI.SYS::UnloadDriver() STATUS_SUCCESS\n");
}

LOUSTATUS EhciResetHcdDevice(PUSB_HCD_OBJECT Hcd);
LOUSTATUS EhciStartHcdDevice(PUSB_HCD_OBJECT Hcd);
LOUSTATUS EhciStopHcdDevice(PUSB_HCD_OBJECT Hcd);
LOUSTATUS EhciHcdCreateEndpoint(PUSB_HCD_OBJECT Hcd, PUSB_ENDPOINT_OBJECT NewEndpoint);
LOUSTATUS EhciHcdDestroyEndpoint(PUSB_ENDPOINT_OBJECT Endpoint);


RHPORT_STATUS EhciGetHcdRhPortStatus(PUSB_HCD_OBJECT Hcd, UINT32 Port);
LOUSTATUS EhciResetRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port);
LOUSTATUS EhciStartRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port);
LOUSTATUS EhciStopRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port);

LOUSTATUS EhciPrepTransfer(PUSB_TRANSFER_DATA Transfer);
LOUSTATUS EhciCommitTransfer(PUSB_TRANSFER_DATA Transfer);

LOUSTATUS EhciInterruptHandler(UINT64 Data);

static USB_HCD_OPERATIONS EhciHcdOperations = {
    //Host Operations
    .ResetHcdDevice = EhciResetHcdDevice,
    .StartHcdDevice = EhciStartHcdDevice,
    .StopHcdDevice = EhciStopHcdDevice,
    .HcdCreateEndpoint = EhciHcdCreateEndpoint,
    .HcdDestroyEndpoint = EhciHcdDestroyEndpoint,
    //Roothub Operations
    .GetHcdRhPortStatus = EhciGetHcdRhPortStatus,
    .ResetRhPort = EhciResetRhPort,
    .StartRhPort = EhciStartRhPort,
    .StopRhPort = EhciStopRhPort,
    //Transfer Operations
    .PrepTransfer = EhciPrepTransfer,
    .CommitTransfer = EhciCommitTransfer,
};

LOUSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){
    LouPrint("EHCI.SYS::AddDevice()\n");
    LOUSTATUS Status;
    PEHCI_DEVICE_OBJECT NewEhciDevice = LouKeMallocType(EHCI_DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
    if(!NewEhciDevice){
        LouPrint("EHCI.SYS::AddDevice():ERROR:Unable To Allocate New Device Object\n");
        while(1);
    }

    NewEhciDevice->PDEV = PciHalGetPciDeviceObjectFromLdmDeviceObject(PlatformDevice);
    
    PciHalEnableMemorySpace(NewEhciDevice->PDEV);
    PciHalEnableIoSpace(NewEhciDevice->PDEV);

    PciHalEnableBusMaster(NewEhciDevice->PDEV);

    PciHalMapPciResource(NewEhciDevice->PDEV, EHCI_OPERATIONAL_REGISTER_BAR, PCI_IOMAP_FLAGS_DEFAULT_MAPPING);

    NewEhciDevice->CapabilitiesRegisters = (PEHCI_CAPABILITY_REGISTERS)PciHalGetIoRegion(
        NewEhciDevice->PDEV,
        EHCI_OPERATIONAL_REGISTER_BAR,
        EHCI_CAP_REGISTER_OFFSET
    );

    LouPrint("NewEhciDevice->CapabilitiesRegisters:%h\n", NewEhciDevice->CapabilitiesRegisters);

    EhciGetHostCapabilities(NewEhciDevice);

    LouPrint("NewEhciDevice->OperationalRegisters:%h\n", NewEhciDevice->OperationalRegisters);

    Status = EhciInitializeEhciMemoryManagement(NewEhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("EHCI.SYS::Unable to initialize Memory Management\n");
        while(1);
    }

    Status = EhciAllocatePeriodicFrameListBase(NewEhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("EHCI.SYS::Unable to allocate Frame List Base\n");
        while(1);
    }

    //TODO Allocate Interrupts

    Status = UsbCoreCreateHcdObject(
        NewEhciDevice->PDEV,
        USBHCD_FLAGS_SET_VERSION(2),
        NewEhciDevice,
        &NewEhciDevice->MainDmaDev,
        &EhciHcdOperations
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("EHCI.SYS:Fatal Error:Unable To Allocate Register Controller\n");
        while(1);
    }
    LouPrint("EHCI.SYS::AddDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("EHCI.SYS::DriverEntry()\n");

    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    
    LOUSTATUS Status = PciHalRegisterLousinePciDeviceTable(DriverObject, SupportedEhciPciDevices);
    if(Status != STATUS_SUCCESS){
        LouPrint("EHCI.SYS::DriverEntry():ERROR Unable To Register Pci Device Table\n");
    }
    LouPrint("EHCI.SYS::DriverEntry() STATUS_SUCCESS\n");    
    return STATUS_SUCCESS;
}
