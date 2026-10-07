#include "../AtaCore.h"

LOUSTATUS AtaCoreAtapiEndpointTestUnitReady(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice
){
    //PATA_PORT_DEVICE_OBJECT AtaPort = EndpointDevice->Port;
    //PATA_COMMAND_PACKET CommandPacket

    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS 
AtaCoreAtapiEndpointReadCapacity10(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice,
    UINT32*                     pLastLba,
    UINT32*                     pSectorSize
){
    if(!EndpointDevice){
        return STATUS_INVALID_PARAMETER;
    }else if(!(EndpointDevice->DeviceCap & ATA_ENDPOINT_DEVCAP_ATAPI)){
        return STATUS_INVALID_PARAMETER;
    }
    PATA_COMMAND_PACKET CommandPacket;
    LOUSTATUS Status = _AtaCoreAtapiEndpointStartReadCapacity10(EndpointDevice, &CommandPacket);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    return _AtaCoreAtapiEndpointEndCapacity10(EndpointDevice, CommandPacket, pLastLba, pSectorSize);
}

DRIVER_EXPORT 
LOUSTATUS
AtaCoreAtapiEndpointRead10(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice,
    UINT32                      Lba,
    UINT16                      SectorCount,
    PLOUSINE_DMA_TRANSFER       Transfer
){
    if((!EndpointDevice) || (!Transfer) || (!SectorCount)){
        return STATUS_INVALID_PARAMETER;
    }else if(!(EndpointDevice->DeviceCap & ATA_ENDPOINT_DEVCAP_ATAPI)){
        return STATUS_INVALID_PARAMETER;
    }
    PATA_COMMAND_PACKET CommandPacket;
    LOUSTATUS Status = _AtaCoreAtapiEndpointStartRead10(EndpointDevice, Lba, SectorCount, Transfer, &CommandPacket);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    return _AtaCoreAtapiEndpointEndRead10(EndpointDevice, CommandPacket);
}