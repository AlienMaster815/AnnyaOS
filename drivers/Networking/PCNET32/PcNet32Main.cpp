
#define _KERNEL_MODULE_

#include <LouDDK.h>
#include "PCNETII.h"

UNUSED LOUSINE_PCI_DEVICE_TABLE PcNet32SupportedDevices[] = {
    {.VendorID = 0x1022, .DeviceID = 0x2000, .SimpleEntry = true},
    {.VendorID = 0x103C, .DeviceID = 0x1064, .SimpleEntry = true},
    {.VendorID = 0x1022, .DeviceID = 0x2625, .SimpleEntry = true},
    {.VendorID = 0x1022, .DeviceID = 0x2627, .SimpleEntry = true},
    {0},
};

LOUDDK_API_ENTRY 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("PCNET32::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("PCNET32::UnloadDriver() STATUS_SUCCESS\n");
}


LOUDDK_API_ENTRY
NTSTATUS 
AddDevice(
    PDRIVER_OBJECT DriverObject,
    struct _DEVICE_OBJECT* PlatformDevice
){
    LouPrint("PCNET32::AddDevice()\n");
    uint8_t DeviceID = PlatformDevice->DeviceID;
    NTSTATUS Status = STATUS_SUCCESS;
    LouPrint("DeviceID:%d\n", DeviceID);

    if(DeviceID < 2){
        //PCNET 2
        Status = InitializePcNetIIDevice(DriverObject, PlatformDevice);
        if(!NT_SUCCESS(Status)){
            LouPrint("Device Initialization Failed\n");
            return Status;
        }
    }else{
        //PCNET 3
        return STATUS_UNSUCCESSFUL;
    }

    LouPrint("PCNET32::AddDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}


LOUDDK_API_ENTRY
NTSTATUS 
DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("PCNET32::DriverEntry()\n");

    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)PcNet32SupportedDevices;

    LouPrint("PCNET32::DriverEntry() STATUS SUCCESS\n");
    return STATUS_SUCCESS;
}

