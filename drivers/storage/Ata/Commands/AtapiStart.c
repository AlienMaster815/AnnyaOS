#include "../AtaCore.h"

LOUSTATUS 
_AtaCoreAtapiEndpointStartReadCapacity10(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice, 
    PATA_COMMAND_PACKET*        pCommandPacket
){
    PATA_PORT_DEVICE_OBJECT AtaPort = EndpointDevice->Port;
    PATA_COMMAND_PACKET CommandPacket = AtaCoreAllocateAtaCommandPacket();
    LOUSTATUS Status;
    if(!CommandPacket){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    LouKeSetAtomicBoolean(&CommandPacket->CommandDone, 0);
    ScsiCoreEncodeReadCapacity10Command((PSCSI_READ_CAPACITY10_COMMAND_STRUCTURE)CommandPacket->PacketData, 0, 0, 0);
    CommandPacket->OpCode = ATA_COMMAND_CODE_PACKET;
    CommandPacket->CommandFlags = ATA_COMMAND_PACKET_FLAGS_TRAN_CMD | ATA_COMMAND_PACKET_FLAGS_POLL | ATA_COMMAND_PACKET_FLAGS_PACKET_CMD; 
    CommandPacket->PacketSize = 12;
    CommandPacket->TransferData = LouKeCreateDmaTransfer(AtaPort->AtaCoreDmaDevice, 8, 2);
    CommandPacket->TransferSize = 8;
    AtaCoreEncodePacketCommand((PATA_COMMAND_PACKET_STRUCTURE)&CommandPacket->Packet, EndpointDevice->ChannelDev, 8, 0, 0, 0);
    LouKeSetupDmaTransferFence(CommandPacket->TransferData, 5000, true);
    if(AtaPort->Operations->AtaPortDevicePrepCommand){
        Status = AtaPort->Operations->AtaPortDevicePrepCommand(AtaPort, CommandPacket);
        if(Status != STATUS_SUCCESS){
            CommandPacket->CommandStatus = STATUS_IO_DEVICE_ERROR;
            LouKeSetAtomicBoolean(&CommandPacket->CommandDone, 1);
        }
    }
    AtaCoreCommitCommandPacketToPort(CommandPacket, AtaPort);
    *pCommandPacket = CommandPacket;
    return STATUS_SUCCESS;
}

DRIVER_EXPORT 
LOUSTATUS 
AtaCoreAtapiEndpointStartReadCapacity10(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice, 
    PATA_COMMAND_PACKET*        CommandPacket
){  
    if((!EndpointDevice) || (!CommandPacket)){
        return STATUS_INVALID_PARAMETER;
    }else if(!(EndpointDevice->DeviceCap & ATA_ENDPOINT_DEVCAP_ATAPI)){
        return STATUS_INVALID_PARAMETER;
    }
    return _AtaCoreAtapiEndpointStartReadCapacity10(EndpointDevice, CommandPacket);
}


LOUSTATUS
_AtaCoreAtapiEndpointStartRead10(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice,
    UINT32                      Lba,
    UINT16                      SectorCount,
    PLOUSINE_DMA_TRANSFER       Transfer,
    PATA_COMMAND_PACKET*        pCommandPacket
){
    UINT64 MaxLba;
    UINT32 SectorSize;
    LOUSTATUS Status = AtaCoreGetEndpointCapacity(EndpointDevice, &MaxLba, &SectorSize);
    if(SectorCount > ((UINT16_MAX - SectorSize) / SectorSize)){
        return STATUS_INTEGER_OVERFLOW;
    }else if(Lba > MaxLba){
        return STATUS_INVALID_PARAMETER;
    }
    PATA_PORT_DEVICE_OBJECT AtaPort = EndpointDevice->Port;
    PATA_COMMAND_PACKET CommandPacket = AtaCoreAllocateAtaCommandPacket();
    LouKeSetAtomicBoolean(&CommandPacket->CommandDone, 0);
    ScsiCoreEncodeRead10Command((PSCSI_READ10_COMMAND_STRUCTURE)CommandPacket->PacketData, 0, 0, 0, 0, (UINT32)Lba, 0, (UINT16)SectorCount, 0x00);
    CommandPacket->OpCode = ATA_COMMAND_CODE_PACKET;
    CommandPacket->CommandFlags = ATA_COMMAND_PACKET_FLAGS_TRAN_CMD | ATA_COMMAND_PACKET_FLAGS_POLL | ATA_COMMAND_PACKET_FLAGS_PACKET_CMD | ATA_COMMAND_PACKET_FLAGS_FETCH_DYNAMIC_RETURN; 
    CommandPacket->PacketSize = 12;
    CommandPacket->TransferData = Transfer;
    CommandPacket->TransferSize = SectorCount * SectorSize;
    CommandPacket->SectorSize = SectorSize;
    AtaCoreEncodePacketCommand((PATA_COMMAND_PACKET_STRUCTURE)&CommandPacket->Packet, EndpointDevice->ChannelDev, SectorCount * SectorSize, 0, 0, 0);
    if(AtaPort->Operations->AtaPortDevicePrepCommand){
        Status = AtaPort->Operations->AtaPortDevicePrepCommand(AtaPort, CommandPacket);
        if(Status != STATUS_SUCCESS){
            CommandPacket->CommandStatus = STATUS_IO_DEVICE_ERROR;
            LouKeSetAtomicBoolean(&CommandPacket->CommandDone, 1);
        }
    }

    AtaCoreCommitCommandPacketToPort(CommandPacket, AtaPort);

    *pCommandPacket = CommandPacket;
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS
AtaCoreAtapiEndpointStartRead10(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice,
    UINT32                      Lba,
    UINT16                      SectorCount,
    PLOUSINE_DMA_TRANSFER       Transfer,
    PATA_COMMAND_PACKET*        CommandPacket
){
    if((!EndpointDevice) || (!Transfer) || (!SectorCount) || (!CommandPacket)){
        return STATUS_INVALID_PARAMETER;
    }if(!(EndpointDevice->DeviceCap & ATA_ENDPOINT_DEVCAP_ATAPI)){
        return STATUS_INVALID_PARAMETER;
    }
    return _AtaCoreAtapiEndpointStartRead10(EndpointDevice, Lba, SectorCount, Transfer, CommandPacket);
}


