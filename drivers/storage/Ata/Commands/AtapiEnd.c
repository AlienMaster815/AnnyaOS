#include "../AtaCore.h"


LOUSTATUS 
_AtaCoreAtapiEndpointEndCapacity10(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice, 
    PATA_COMMAND_PACKET         CommandPacket,
    UINT32*                     pLastLba,
    UINT32*                     pSectorSize
){
    LOUSTATUS Status;
    UINT8 CapacityData[8] = {0};
    Status = LouKeFenceDmaTransfer(CommandPacket->TransferData);
    if(Status == STATUS_SUCCESS){
        Status = CommandPacket->CommandStatus;
    }
    if(Status == STATUS_SUCCESS){
        memcpy(CapacityData, LouKeDmaTransferGetOffsetVa(CommandPacket->TransferData, 0, 0), 8);
        if(pLastLba){
            *pLastLba = ((UINT32)CapacityData[4] << 24) | ((UINT32)CapacityData[5] << 16) | ((UINT32)CapacityData[6] << 8) | (UINT32)CapacityData[7];
        }
        if(pSectorSize){
            *pSectorSize = ((UINT32)CapacityData[0] << 24) | ((UINT32)CapacityData[1] << 16) | ((UINT32)CapacityData[2] << 8) | (UINT32)CapacityData[3];    
        }
    }
    LouKeDestroyDmaTransfer(CommandPacket->TransferData);
    AtaCoreFreeAtaCommandPacket(CommandPacket);
    return Status;
}


DRIVER_EXPORT 
LOUSTATUS 
AtaCoreAtapiEndpointEndCapacity10(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice, 
    PATA_COMMAND_PACKET         CommandPacket,
    UINT32*                     pLastLba,
    UINT32*                     pSectorSize
){
    if((!EndpointDevice) || (!CommandPacket)){
        return STATUS_INVALID_PARAMETER;
    }if(!(EndpointDevice->DeviceCap & ATA_ENDPOINT_DEVCAP_ATAPI) || (CommandPacket->OpCode != ATA_COMMAND_CODE_PACKET)){
        return STATUS_INVALID_PARAMETER;
    }
    return _AtaCoreAtapiEndpointEndCapacity10(EndpointDevice, CommandPacket, pLastLba, pSectorSize);
}

LOUSTATUS
_AtaCoreAtapiEndpointEndRead10(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice,
    PATA_COMMAND_PACKET         CommandPacket
){
    LOUSTATUS Status = LouKeFenceDmaTransfer(CommandPacket->TransferData);
    if(Status == STATUS_SUCCESS){
        Status = CommandPacket->CommandStatus;
    }
    AtaCoreFreeAtaCommandPacket(CommandPacket);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT 
LOUSTATUS
AtaCoreAtapiEndpointEndRead10(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice,
    PATA_COMMAND_PACKET         CommandPacket
){
    if((!EndpointDevice) || (!CommandPacket)){
        return STATUS_INVALID_PARAMETER;
    }if(!(EndpointDevice->DeviceCap & ATA_ENDPOINT_DEVCAP_ATAPI) || (CommandPacket->OpCode != ATA_COMMAND_CODE_PACKET)){
        return STATUS_INVALID_PARAMETER;
    }
    return _AtaCoreAtapiEndpointEndRead10(EndpointDevice, CommandPacket);
}