//Copyright GPL-2 Tyler Grenier (2025 - 2026)

#include "OHCI.h"

LOUSTATUS OhciResetHcdDevice(PUSB_HCD_OBJECT Hcd);
LOUSTATUS OhciStartHcdDevice(PUSB_HCD_OBJECT Hcd);
LOUSTATUS OhciStopHcdDevice(PUSB_HCD_OBJECT Hcd);
LOUSTATUS OhciHcdCreateEndpoint(PUSB_HCD_OBJECT Hcd, PUSB_ENDPOINT_OBJECT NewEndpoint);
LOUSTATUS OhciHcdDestroyEndpoint(PUSB_ENDPOINT_OBJECT Endpoint);
LOUSTATUS OhciHcdChangeEndpointPacketSize(PUSB_ENDPOINT_OBJECT Endpoint, SIZE PacketSize);

SIZE OhciGetHcdRhPortCount(PUSB_HCD_OBJECT Hcd);
RHPORT_STATUS OhciGetHcdRhPortStatus(PUSB_HCD_OBJECT Hcd, UINT32 Port);
ULONG OhciGetHcdRhPortSpeed(PUSB_HCD_OBJECT Hcd, UINT32 Port);

LOUSTATUS OhciResetRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port);
LOUSTATUS OhciStartRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port);
LOUSTATUS OhciStopRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port);

LOUSTATUS OhciPrepTransfer(PUSB_TRANSFER_OBJECT Transfer);
LOUSTATUS OhciCommitTransfer(PUSB_TRANSFER_OBJECT Transfer);
LOUSTATUS OhciGetTransferStatus(PUSB_TRANSFER_OBJECT Transfer);
LOUSTATUS OhciCleanupTransfer(PUSB_TRANSFER_OBJECT Transfer);

static LOUSINE_DMA_DEVICE TypicalOhciBusMasterDevice = {
    .DmaDeviceFlags = LOUSINE_DMA_DEVICE_FLAGS_SCATTER_DMA_SUPPORTED,
    .MaxScatterCount = 8320,
    .AllocatorData = {
        .DmaLimit = 32,
        .DmaThreshold = 8 * KILOBYTE,
    },
};

static USB_HCD_OPERATIONS OhciHcdOperations = {
    //Host Operations
    .ResetHcdDevice = OhciResetHcdDevice,
    .StartHcdDevice = OhciStartHcdDevice,
    .StopHcdDevice = OhciStopHcdDevice,
    .HcdCreateEndpoint = OhciHcdCreateEndpoint,
    .HcdDestroyEndpoint = OhciHcdDestroyEndpoint,
    .HcdChangeEndpointPacketSize = OhciHcdChangeEndpointPacketSize,
    //Roothub Operations
    .GetHcdRhPortCount = OhciGetHcdRhPortCount,
    .GetHcdRhPortStatus = OhciGetHcdRhPortStatus,
    .ResetRhPort = OhciResetRhPort,
    .StartRhPort = OhciStartRhPort,
    .StopRhPort = OhciStopRhPort,
    //Transfer Operations
    .PrepTransfer = OhciPrepTransfer,
    .CommitTransfer = OhciCommitTransfer,
    .GetTransferStatus = OhciGetTransferStatus,
    .CleanupTransfer = OhciCleanupTransfer,
};

UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedOhciPciDevices[] = {
    {.VendorID = PCI_VENDOR_ID_STMICRO, .DeviceID = 0xCC01, .SimpleEntry = true},
    {.BaseClass = 0x0C, .SubClass = 0x03, .ProgIf = 0x10, .GenericEntry = true},
    {0},
};

LOUAPI 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("OHCI.SYS::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("OHCI.SYS::UnloadDriver() STATUS_SUCCESS\n");
}

LOUSTATUS AddDevice(
    PDRIVER_OBJECT  DriverObject, 
    PDEVICE_OBJECT  PlatformDevice
){
    LOUSTATUS Status;
    LouPrint("OHCI.SYS::AddDevice()\n");

    POHCI_DEVICE OhciDevice = LouKeMallocType(OHCI_DEVICE, KERNEL_GENERIC_MEMORY);
    OhciDevice->PDEV = PciHalGetPciDeviceObjectFromLdmDeviceObject(PlatformDevice);
 
    PciHalEnableMemorySpace(OhciDevice->PDEV);
    PciHalEnableIoSpace(OhciDevice->PDEV);

    PciHalEnableBusMaster(OhciDevice->PDEV);

    PciHalMapPciResource(OhciDevice->PDEV, OHCI_OPERATIONAL_REGISTER_BAR, PCI_IOMAP_FLAGS_DEFAULT_MAPPING);

    OhciDevice->OperationalRegisters = (POHCI_OPERATIONAL_REGISTERS)PciHalGetIoRegion(
        OhciDevice->PDEV,
        OHCI_OPERATIONAL_REGISTER_BAR,
        OHCI_OPERATIONAL_REGISTER_OFFSET
    );
    if(!OhciDevice->OperationalRegisters){
        LouPrint("OHCI.SYS:Legacy BIOS Hc Bug Controller Did Not Handoff\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    
    LouPrint("OHCI.SYS:Operational Reg:%h\n", OhciDevice->OperationalRegisters);
 
    //TODO: Allocate Interrupt Handler
    
    Status = UsbCoreCreateHcdObject(
        OhciDevice->PDEV,
        USBHCD_FLAGS_SET_VERSION(1),
        OhciDevice,
        &TypicalOhciBusMasterDevice,
        &OhciHcdOperations
    );
    if(Status != STATUS_SUCCESS){
        LouKeFree(OhciDevice);
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    LouPrint("OHCI.SYS::AddDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("OHCI.SYS::DriverEntry()\n");

    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;

    LOUSTATUS Status = PciHalRegisterLousinePciDeviceTable(DriverObject, SupportedOhciPciDevices);
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS::DriverEntry():ERROR Unable To Register Pci Device Table\n");
        return STATUS_UNSUCCESSFUL;
    }

    LouPrint("OHCI.SYS::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}
