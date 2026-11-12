#include "Uhci.h"

UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedUhciPciDevices[] = {
    {.BaseClass = 0x0C, .SubClass = 0x03, .ProgIf = 0x00, .GenericEntry = true},
    {0},
};

LOUAPI 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("UHCI.SYS::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("UHCI.SYS::UnloadDriver() STATUS_SUCCESS\n");
}


LOUSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){
    LouPrint("UHCI.SYS::AddDevice()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("UHCI.SYS::DriverEntry()\n");

    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    
    LOUSTATUS Status = PciHalRegisterLousinePciDeviceTable(DriverObject, SupportedUhciPciDevices);
    if(Status != STATUS_SUCCESS){
        LouPrint("UHCI.SYS::DriverEntry():ERROR Unable To Register Pci Device Table\n");
    }
    LouPrint("UHCI.SYS::DriverEntry() STATUS_SUCCESS\n");    
    return STATUS_SUCCESS;
}