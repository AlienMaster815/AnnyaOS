
#define _KERNEL_MODULE_

#include <LouDDK.h>
#include "HDAPCI.h"


UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedHdaPciDevices[] = {

    {0},
};

LOUDDK_API_ENTRY 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("HDAPCI::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("HDAPCI::UnloadDriver() STATUS_SUCCESS\n");
}


NTSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){
    LouPrint("HDAPCI::AddDevice()\n");
    PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    uint8_t DeviceID = PlatformDevice->DeviceID;

    LouPrint("Pci Device ID:%d\n", DeviceID);

    LouPrint("PCI Device Flags:%bl\n", SupportedHdaPciDevices[DeviceID].DriverData);

    LouPrint("HDAPCI::AddDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("HDAPCI::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)SupportedHdaPciDevices;

    LouPrint("HDAPCI::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

