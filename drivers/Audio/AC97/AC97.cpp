
#define _KERNEL_MODULE_

#include <LouDDK.h>
#include "AC97.h"

#define SB16 1

UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedSoundBalsters[] = {

    {0},
};

LOUDDK_API_ENTRY 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("SBMOD::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("SBMOD::UnloadDriver() STATUS_SUCCESS\n");
}


NTSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    PDEVICE_OBJECT PlatformDevice
){


    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("SBMOD::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the losine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)SupportedSoundBalsters;

    LouPrint("SBMOD::DriverEntry() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}

