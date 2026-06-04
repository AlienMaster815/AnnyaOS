
#define _KERNEL_MODULE_

#include <LouDDK.h>
#include "AC97.h"

#define SB16 1

UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedSoundBalsters[] = {

    {0},
};

LOUAPI 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("SBMOD::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("SBMOD::UnloadDriver() STATUS_SUCCESS\n");
}


LOUSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){


    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("SBMOD::DriverEntry()\n");
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;

    LOUSTATUS Status = PciHalRegisterLousinePciDeviceTable(DriverObject, SupportedSoundBalsters);
    if(Status != STATUS_SUCCESS){
        LouPrint("SBMOD::DriverEntry():ERROR Unable To Register Pci Device Table\n");
    }

    LouPrint("SBMOD::DriverEntry() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}

