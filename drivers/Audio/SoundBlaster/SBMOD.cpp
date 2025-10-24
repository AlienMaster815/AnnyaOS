#include "SBMOD.h"

UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedSoundBalsters[] = {
    {0},
};


DRIVER_EXPORT
LOUSTATUS 
LouKeAddSbIsaDevice(){
    LouPrint("SBMOD.SYS::LouKeAddSbIsaDevice()\n");
    LouKeLoadDriver("8237A.SYS", 0x00);



    LouPrint("SBMOD.SYS::LouKeAddSbIsaDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}


LOUDDK_API_ENTRY 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("SBMOD.SYS::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("SBMOD.SYS::UnloadDriver() STATUS_SUCCESS\n");
}

NTSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){


    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("SBMOD.SYS::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)SupportedSoundBalsters;

    LouPrint("SBMOD.SYS::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

