#define _KERNEL_MODULE_
#include <LouDDK.h>
#include "VirtualBoxDriver.h"
#include "HgsmiDefinitions.h"
#include "VBoxVideo.h"

static LOUSINE_PCI_DEVICE_TABLE PiixPciDeviceTable[] = {
    //PATA Devices
    {0x80EE, 0xBEEF, ANY_PCI_ID, ANY_PCI_ID, 0, 0, 0},
    {0},
};

LOUDDK_API_ENTRY
VOID
UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("Unloaded VBOXGPU\n");
}

LOUDDK_API_ENTRY
NTSTATUS
AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT PlatformDevice){
    LouPrint("VBOXGPU::AddDevice()\n");

    LouPrint("VBOXGPU::AddDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS
DriverEntry(
    PDRIVER_OBJECT DriverObject, 
    PUNICODE_STRING RegistryEntry
){

    LouPrint("VBOXGPU::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the losine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)PiixPciDeviceTable;
    LouPrint("VBOXGPU::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}