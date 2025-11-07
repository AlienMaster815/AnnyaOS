#include "OHCI.h"



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
    LouPrint("Operational Reg:%h\n", OhciDevice->OperationalRegisters);

    UINT32 Revision = OhciDevice->OperationalRegisters->HcRevision;
    Revision &= 0xFF;

    if(Revision != 0x10){
        LouPrint("ERROR Invalid Revision Reset Data:%h\n", Revision);
        LouKeFree(OhciDevice);
        return STATUS_NO_SUCH_DEVICE;
    }

    Status = OhciCreateEdPool(OhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("ERROR Unable To Allocate Driver Resources\n");
        return Status;
    }

    Status = OhciInitialzeEndpointHeaders(OhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("ERROR Unable To Initialize Device Data\n");
        goto _ERROR_COULD_NOT_DESIGNATE_RESOURCES;
    }

    //allocate system resources
    
    //take control of Hc

    //set up registers

    //start SOF tokens

    LouPrint("OHCI.SYS::AddDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;

    _ERROR_COULD_NOT_DESIGNATE_RESOURCES:
    //TODO:
    LouPrint("_ERROR_COULD_NOT_DESIGNATE_RESOURCES\n");
    while(1);
    return Status;
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

