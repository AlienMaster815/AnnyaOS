#include "EHCI.h"

UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedEhciPciDevices[] = {
    {.BaseClass = 0x0C, .SubClass = 0x03, .ProgIf = 0x20, .GenericEntry = true},
    {0},
};

LOUDDK_API_ENTRY 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("EHCI.SYS::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("EHCI.SYS::UnloadDriver() STATUS_SUCCESS\n");
}


NTSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){
    LouPrint("EHCI.SYS::AddDevice()\n");
    PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    PEHCI_CAPABILITY_REGISTERS CapRegs = (PEHCI_CAPABILITY_REGISTERS)LouKePciGetIoRegion(PDEV, EHCI_OPERATIONAL_REGISTER_BAR, EHCI_CAP_REGISTER_OFFSET);
    PEHCI_HOST_OPERATIONAL_REGISTERS OpRegs;
    LouPrint("EHCI.SYS:Cap Version:%h\n", CapRegs->HciVersion);
    
    if(CapRegs->HciVersion != 0x100){
        LouPrint("EHCI.SYS:This Driver Does Not Support This Controller Version\n");
        return STATUS_NO_SUCH_DEVICE;
    }
    UINT64 Base = (UINT64)(UINTPTR)CapRegs;
    Base += (UINT64)CapRegs->CapLength;
    OpRegs = (PEHCI_HOST_OPERATIONAL_REGISTERS)Base;
    
    PEHCI_DEVICE EhciDevice = LouKeMallocType(EHCI_DEVICE, KERNEL_GENERIC_MEMORY);

    EhciDevice->PDEV = PDEV;
    EhciDevice->Capabilities = CapRegs;
    EhciDevice->OperationalRegisters = OpRegs;

    EhciGetHostCapabilities(EhciDevice);

    EhciStopHostController(EhciDevice);    

    LouPrint("EHCI.SYS::AddDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("EHCI.SYS::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)SupportedEhciPciDevices;

    LouPrint("EHCI.SYS::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

