#include "AtaCore.h"

DRIVER_EXPORT void AtaCoreFreeAtaPortsFromHost(PATA_HOST_DEVICE_OBJECT HostDevice){
    PATA_PORT_DEVICE_OBJECT Ports = HostDevice->PortDevices;
    SIZE PortCount = HostDevice->PortCount;
    HostDevice->PortCount = 0;
    HostDevice->PortDevices = 0x00;
    if(!Ports){
        return;
    }
    if(Ports->PortPrivateData){
        LouKeFree(Ports->PortPrivateData);
    }
    LouKeFree(Ports);
}

DRIVER_EXPORT LOUSTATUS AtaCoreAllocatePortsForHost(
    PATA_HOST_DEVICE_OBJECT HostDevice,
    SIZE                    PortCount,
    SIZE                    PrivateDataSize,
    SIZE                    PrivateDataAlignment
){
    HostDevice->PortDevices = LouKeMallocArray(ATA_PORT_DEVICE_OBJECT, PortCount, KERNEL_GENERIC_MEMORY);
    if(HostDevice->PortDevices){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    HostDevice->PortCount = PortCount;
    if(PrivateDataSize){
        HostDevice->PortDevices->PortPrivateData = LouKeMallocEx(ROUND_UP64(PrivateDataSize, PrivateDataAlignment) * PortCount, PrivateDataAlignment, KERNEL_GENERIC_MEMORY);
        if(!HostDevice->PortDevices->PortPrivateData){
            AtaCoreFreeAtaPortsFromHost(HostDevice);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        for(SIZE i = 0 ; i < PortCount; i++){
            HostDevice->PortDevices[i].PortPrivateData = ((UINT64)(UINT8*)HostDevice->PortDevices->PortPrivateData + (ROUND_UP64(PrivateDataSize, PrivateDataAlignment) * i));
        }
    }
    return STATUS_SUCCESS;
}
