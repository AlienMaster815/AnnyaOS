
#define _KERNEL_MODULE_

#include <LouDDK.h>
#include "HDAPCI.h"


UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedHdaPciDevices[] = {

    {0},
};

LOUAPI 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("HDAPCI::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("HDAPCI::UnloadDriver() STATUS_SUCCESS\n");
}


LOUSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){
    LouPrint("HDAPCI::AddDevice()\n");
    while(1);
    //PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    //uint8_t DeviceID = PlatformDevice->DeviceID;

    //LouPrint("Pci Device ID:%d\n", DeviceID);

    //LouPrint("PCI Device Flags:%bl\n", SupportedHdaPciDevices[DeviceID].DriverData);

    LouPrint("HDAPCI::AddDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("HDAPCI::DriverEntry()\n");
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    
    LOUSTATUS Status = PciHalRegisterLousinePciDeviceTable(DriverObject, SupportedHdaPciDevices);
    if(Status != STATUS_SUCCESS){
        LouPrint("HDAPCI::DriverEntry():ERROR Unable To Register Pci Device Table\n");
    }

    LouPrint("HDAPCI::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

