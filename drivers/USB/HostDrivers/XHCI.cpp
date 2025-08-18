#define _KERNEL_MODULE_
#include <LouDDK.h>
#include "Xhci.h"
#include "XhciTrace.h"
#include "XhciPci.h"

UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedXhciPciDevices[] = {
    {.BaseClass = 0x0C, .SubClass = 0x03, .BoardID = 0x00, .GenericEntry = true},
    {0},
};

LOUDDK_API_ENTRY 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("XHCI::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("XHCI::UnloadDriver() STATUS_SUCCESS\n");
}


NTSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    PDEVICE_OBJECT PlatformDevice
){
    LouPrint("XHCI::AddDevice()\n");
    P_PCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;


    

    LouPrint("XHCI::AddDevice() STATUS_SUCCESS\n");

    //while(1);
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("XHCI::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)SupportedXhciPciDevices;

    LouPrint("XHCI::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}