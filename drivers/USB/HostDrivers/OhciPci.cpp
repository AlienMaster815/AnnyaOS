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
    UINT32 HcRhDescriptorA;
    UINT8 Ports;
    UINT32 Fm;
    UINT16 FrameInterval;
    UINT16 PeriodicStart;
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

    OhciDevice->OperationalRegisters->HcCommandStatus |= OHCI_COMMAND_STATUS_OCR;
    OhciDevice->Fminterval = OhciDevice->OperationalRegisters->HcFmInterval;

    OhciDevice->OperationalRegisters->HcCommandStatus |= OHCI_COMMAND_STATUS_HCR;

    Status = LouKeWaitForUlongRegisterCondition(
        (PULONG)LouKeCastToUnalignedPointer(&OhciDevice->OperationalRegisters->HcCommandStatus),//it actually is aligned the compiler just gives a warning
        10,
        OHCI_COMMAND_STATUS_HCR,
        0
    );

    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Ohci Controller Hung On Reset\n");
        LouKeFree(OhciDevice);
        return Status;
    }
    LouPrint("OHCI.SYS:Bringing Up Controller\n");

    OhciDevice->OperationalRegisters->HcFmInterval = OhciDevice->Fminterval;
    OhciDevice->OperationalRegisters->HcControl = SET_OHCI_COTROL_HCFS(OhciDevice->OperationalRegisters->HcControl , OHCI_HCFS_USBRESUME);

    if(OhciDevice->OperationalRegisters->HcCommandStatus & OHCI_COMMAND_STATUS_HCR){
        LouPrint("OHCI.SYS:ERROR:Host Re Entered Reset\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    else if(OhciDevice->OperationalRegisters->HcFmInterval != OhciDevice->Fminterval){
        LouPrint("OHCI.SYS:ERROR:Host Clock Stuck\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    else if(GET_OHCI_CONTROL_HCFS(OhciDevice->OperationalRegisters->HcControl) != OHCI_HCFS_USBRESUME){
        LouPrint("OHCI.SYS:ERROR:Host Did Not Re Enter Resume\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    LouPrint("OHCI.SYS:Host Initialized Successfully\n");

    Status = OhciInitialzeHcca(OhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:ERROR Unable To Initialize Device Data\n");
        goto _ERROR_COULD_NOT_DESIGNATE_RESOURCES;
    }

    OhciDevice->OperationalRegisters->HcControl &= ~((1 << OHCI_CONTROL_CLE_BIT) | (1 << OHCI_CONTROL_BLE_BIT) | (1 << OHCI_CONTROL_PLE_BIT)); 

    Fm = OhciDevice->OperationalRegisters->HcFmInterval;
    FrameInterval = Fm & 0x3FFF;   // mask bits 0–13
    PeriodicStart = (FrameInterval * 9) / 10;
    OhciDevice->OperationalRegisters->HcPeriodicStart = PeriodicStart;
    OhciDevice->OperationalRegisters->HcRhStatus |= OHCI_RH_STATUS_LPSC;

    OhciDevice->OperationalRegisters->HcControl = SET_OHCI_COTROL_HCFS(OhciDevice->OperationalRegisters->HcControl , OHCI_HCFS_USBOPERATIONAL);


    if(GET_OHCI_CONTROL_HCFS(OhciDevice->OperationalRegisters->HcControl) != OHCI_HCFS_USBOPERATIONAL){
        LouPrint("OHCI.SYS:ERROR:Host Did Not Become Operational\n");
        return STATUS_IO_DEVICE_ERROR;
    }

    HcRhDescriptorA = OhciDevice->OperationalRegisters->HcRhDescriptorA;
    Ports = HcRhDescriptorA & 0x0F;

    LouPrint("OHCI.SYS:Ports:%d\n", Ports);


    for(size_t i = 0 ; i < Ports; i++){
        UINT32 TmpPortStatus = OhciDevice->OperationalRegisters->HcRhPortStatus[i];

        if(TmpPortStatus & OHCI_PORT_STATUS_CCS){
            OhciDevice->Port[i].PortAttatched = true;

            LouPrint("Port:%d Is Connected To Somthing\n", i);

            OhciInitializePort(
                OhciDevice,
                i
            );            
        }

    }

    LouPrint("OHCI.SYS::AddDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;

    _ERROR_COULD_NOT_DESIGNATE_RESOURCES:
    //TODO:
    LouPrint("OHCI.SYS:_ERROR_COULD_NOT_DESIGNATE_RESOURCES\n");
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

