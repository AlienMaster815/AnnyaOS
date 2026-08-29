#include "AtaCore.h"

DRIVER_EXPORT void AtaCoreFreeHostDevice(PATA_HOST_DEVICE_OBJECT HostDevice){
    if(!HostDevice){
        return;
    }
    if(HostDevice->HostPrivateData){
        LouKeFree(HostDevice->HostPrivateData);
    }
    LouKeFree(HostDevice);
}

DRIVER_EXPORT LOUSTATUS AtaCoreAllocateHostDevice(
    PATA_HOST_DEVICE_OBJECT*    HostDeviceOut,
    SIZE                        PrivateDataSize,
    SIZE                        PrivateDataAlignment
){
    PATA_HOST_DEVICE_OBJECT NewDeviceObject = LouKeMallocType(ATA_HOST_DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
    if(!NewDeviceObject){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    PVOID PrivateData = LouKeMallocEx(PrivateDataSize, PrivateDataAlignment, KERNEL_GENERIC_MEMORY);
    if(!PrivateData){
        AtaCoreFreeHostDevice(NewDeviceObject);
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    NewDeviceObject->HostPrivateData = PrivateData;
    return STATUS_SUCCESS;
}

