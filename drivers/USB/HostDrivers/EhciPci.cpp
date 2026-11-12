//Copyright GPL-2 Tyler Grenier (2025 - 2026)

#include "EHCI.h"

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


LOUSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){
    LouPrint("EHCI.SYS::AddDevice()\n");
    while(1);
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

/*







*/