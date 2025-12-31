#include "OHCI.h"


static const USB_HOST_OPERATIONS OhciOperations = {
    .UsbHcdResetHostController = OhciResetHostController,
    .UsbHcdStopHostController = OhciStopHostController,
    .UsbHcdStartHostController = OhciStartHostController,
    .UsbHcdProbeRootHub = OhciProbeRootHub,
};

UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedOhciPciDevices[] = {
    {.BaseClass = 0x0C, .SubClass = 0x03, .ProgIf = 0x10, .GenericEntry = true},
    {0},
};

LOUDDK_API_ENTRY 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("OHCI.SYS::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("OHCI.SYS::UnloadDriver() STATUS_SUCCESS\n");
}


NTSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){
    LOUSTATUS Status;
    PPCI_DEVICE_OBJECT PDEV = (PPCI_DEVICE_OBJECT)PlatformDevice->PDEV;
    LouPrint("OHCI.SYS::AddDevice()\n");

    POHCI_DEVICE OhciDevice = LouKeMallocType(OHCI_DEVICE, KERNEL_GENERIC_MEMORY);

    LouKeHalEnablePciDevice(PDEV);
    LouKeHalPciSetMaster(PDEV);

    OhciDevice->OperationalRegisters = (POHCI_OPERATIONAL_REGISTERS)LouKePciGetIoRegion(
        PDEV,
        OHCI_OPERATIONAL_REGISTER_BAR,
        OHCI_OPERATIONAL_REGISTER_OFFSET
    );
    if(!OhciDevice->OperationalRegisters){
        LouPrint("OHCI.SYS:Legacy BIOS Hc Bug Controller Did Not Handoff\n");
        return STATUS_IO_DEVICE_ERROR;
    }

    LouPrint("OHCI.SYS:Operational Reg:%h\n", OhciDevice->OperationalRegisters);

    UINT32 Revision = OhciDevice->OperationalRegisters->HcRevision;
    Revision &= 0xFF;

    if(Revision < 0x10){
        LouPrint("OHCI.SYS:ERROR Invalid Revision Reset Data:%h\n", Revision);
        LouKeFree(OhciDevice);
        return STATUS_NO_SUCH_DEVICE;
    }


    OhciDevice->UsbHost.Operations = OhciOperations;

    Status = LouKeHalMallocPciIrqVectors(
        PDEV,
        1,
        PCI_IRQ_USE_LEGACY
    );

    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:ERROR Could Not Allocate Interrupt Vector\n");
        return Status;
    }

    RegisterInterruptHandler(OhciInterruptHandler, LouKeHalGetPciIrqVector(PDEV, 0), false, (uint64_t)OhciDevice);

    Status = OhciInitializeLists(OhciDevice);
    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Error Initializing Lists\n");
        return STATUS_SUCCESS;
    }

    Status = LouKeUsbAddHcd(&OhciDevice->UsbHost);

    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Error Adding Host Controller\n");
        return Status;
    }

    LouPrint("OHCI.SYS::AddDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("OHCI.SYS::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)SupportedOhciPciDevices;

    LouPrint("OHCI.SYS::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

