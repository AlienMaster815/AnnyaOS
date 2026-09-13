#include "AtaCore.h"

//TODO seperate the READ10 and READ16 CDBs

LOUSTATUS 
AtaCoreGetEndpointCapacity(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice,
    UINT32*                     OutLba,
    UINT32*                     OutSectorSize 
){
    if(!EndpointDevice){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS Status;
    
    if(EndpointDevice->DeviceCap & ATA_ENDPOINT_DEVCAP_ATAPI){
        if(EndpointDevice->SectorSize && EndpointDevice->MaxLba){
            if(OutLba){
                *OutLba = EndpointDevice->MaxLba;
            }
            if(OutSectorSize){
                *OutSectorSize = EndpointDevice->SectorSize;
            }
            return STATUS_SUCCESS;
        }

        UINT8 CapacityData[8] = {0};
        PATA_PORT_DEVICE_OBJECT AtaPort = EndpointDevice->Port;
        PATA_COMMAND_PACKET CommandPacket = AtaCoreAllocateAtaCommandPacket();
        LouKeSetAtomicBoolean(&CommandPacket->CommandDone, 0);
        ScsiCoreEncodeReadCapacity10Command((PSCSI_READ_CAPACITY10_COMMAND_STRUCTURE)CommandPacket->PacketData, 0, 0, 0);
        CommandPacket->CommandFlags = ATA_COMMAND_PACKET_FLAGS_TRAN_CMD | ATA_COMMAND_PACKET_FLAGS_POLL | ATA_COMMAND_PACKET_FLAGS_PACKET_CMD; 
        CommandPacket->PacketSize = 12;
        CommandPacket->PioDataIn = CapacityData;
        CommandPacket->PioSize = 8;
        AtaCoreEncodePacketCommand((PATA_COMMAND_PACKET_STRUCTURE)&CommandPacket->Packet, EndpointDevice->ChannelDev, 8, 0, 0, 0);
        if(AtaPort->Operations->AtaPortDevicePrepCommand){
            Status = AtaPort->Operations->AtaPortDevicePrepCommand(AtaPort, CommandPacket);
            if(Status != STATUS_SUCCESS){
                CommandPacket->CommandStatus = STATUS_IO_DEVICE_ERROR;
                LouKeSetAtomicBoolean(&CommandPacket->CommandDone, 1);
            }
        }

        MutexLock(AtaPort->ChannelLock);
        
        LouKeListAddTail(&CommandPacket->QueuedCommands, &AtaPort->QueuedCommands);

        LouKeUnblockThread(AtaPort->CommandWorkerThread);

        MutexUnlock(AtaPort->ChannelLock);

        while(!LouKeGetAtomicBoolean(&CommandPacket->CommandDone)){
            sleep(10);
        }

        Status = CommandPacket->CommandStatus;

        AtaCoreFreeAtaCommandPacket(CommandPacket);

        if(Status != STATUS_SUCCESS){
            LouPrint("AtaCoreGetEndpointCapacity():COMMAND_ERROR\n");
            return Status;
        }
        EndpointDevice->SectorSize = ((UINT32)CapacityData[4] << 24) | ((UINT32)CapacityData[5] << 16) | ((UINT32)CapacityData[6] << 8) | (UINT32)CapacityData[7];
        EndpointDevice->MaxLba = ((UINT32)CapacityData[0] << 24) | ((UINT32)CapacityData[1] << 16) | ((UINT32)CapacityData[2] << 8) | (UINT32)CapacityData[3];
        if(OutLba){
            *OutLba = EndpointDevice->MaxLba;
        } 
        if(OutSectorSize){ 
            *OutSectorSize = EndpointDevice->SectorSize;
        } 
        return STATUS_SUCCESS;
    }



    return STATUS_INVALID_PARAMETER;
}

LOUSTATUS 
AtaCoreReadSectorsFromEndpointDevice(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice,
    UINT32                      Lba,
    UINT32                      SectorCount,
    PVOID                       OutBuffer
){
    UINT32 MaxLba;
    UINT32 SectorSize;
    LOUSTATUS Status = AtaCoreGetEndpointCapacity(EndpointDevice, &MaxLba, &SectorSize);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(((Lba + SectorCount) > MaxLba) || ((SectorCount * SectorSize) > UINT16_MAX)){
        return STATUS_INVALID_PARAMETER;
    }
    
    if(EndpointDevice->DeviceCap & ATA_ENDPOINT_DEVCAP_ATAPI){
        PATA_PORT_DEVICE_OBJECT AtaPort = EndpointDevice->Port;
        PATA_COMMAND_PACKET CommandPacket = AtaCoreAllocateAtaCommandPacket();
        LouKeSetAtomicBoolean(&CommandPacket->CommandDone, 0);
        ScsiCoreEncodeRead10Command((PSCSI_READ10_COMMAND_STRUCTURE)CommandPacket->PacketData, 0, 0, 0, 0, Lba, 0, SectorCount, 0x00);
        CommandPacket->CommandFlags = ATA_COMMAND_PACKET_FLAGS_TRAN_CMD | ATA_COMMAND_PACKET_FLAGS_POLL | ATA_COMMAND_PACKET_FLAGS_PACKET_CMD; 
        CommandPacket->PacketSize = 12;
        CommandPacket->PioDataIn = OutBuffer;
        CommandPacket->PioSize = SectorCount * SectorSize;
        AtaCoreEncodePacketCommand((PATA_COMMAND_PACKET_STRUCTURE)&CommandPacket->Packet, EndpointDevice->ChannelDev, SectorCount * SectorSize, 0, 0, 0);
        if(AtaPort->Operations->AtaPortDevicePrepCommand){
            Status = AtaPort->Operations->AtaPortDevicePrepCommand(AtaPort, CommandPacket);
            if(Status != STATUS_SUCCESS){
                CommandPacket->CommandStatus = STATUS_IO_DEVICE_ERROR;
                LouKeSetAtomicBoolean(&CommandPacket->CommandDone, 1);
            }
        }

        MutexLock(AtaPort->ChannelLock);
        
        LouKeListAddTail(&CommandPacket->QueuedCommands, &AtaPort->QueuedCommands);

        LouKeUnblockThread(AtaPort->CommandWorkerThread);

        MutexUnlock(AtaPort->ChannelLock);

        while(!LouKeGetAtomicBoolean(&CommandPacket->CommandDone)){
            sleep(10);
        }

        Status = CommandPacket->CommandStatus;

        AtaCoreFreeAtaCommandPacket(CommandPacket);

        if(Status != STATUS_SUCCESS){
            LouPrint("AtaCoreGetEndpointCapacity():COMMAND_ERROR\n");
            return Status;
        }

        return STATUS_SUCCESS;
    }

    return STATUS_UNSUCCESSFUL;
}

LOUSTATUS AtaCoreBlkdevFlushDevice(PBLOCK_DEVICE_OBJECT BlockDevice){

    LouPrint("ATACORE.SYS:AtaCoreBlkdevFlushDevice()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AtaCoreBlkdevReadDeviceSegment(PBLOCK_DEVICE_OBJECT BlockDevice, PBLKDEV_OPENED_BLOCK_SEGMENT Segment){


    LouPrint("ATACORE.SYS:AtaCoreBlkdevReadDeviceSegment()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AtaCoreBlkdevWriteDeviceSegment(PBLOCK_DEVICE_OBJECT BlockDevice, PBLKDEV_OPENED_BLOCK_SEGMENT Segment){

    LouPrint("ATACORE.SYS:AtaCoreBlkdevWriteDeviceSegment()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AtaCoreBlkdevReadDeviceBlock(PBLOCK_DEVICE_OBJECT BlockDevice, PBLKDEV_OPENED_BLOCK Block){

    LouPrint("ATACORE.SYS:AtaCoreBlkdevReadDeviceBlock()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AtaCoreBlkdevWriteDeviceBlock(PBLOCK_DEVICE_OBJECT BlockDevice, PBLKDEV_OPENED_BLOCK Block){

    LouPrint("ATACORE.SYS:AtaCoreBlkdevWriteDeviceBlock()\n");
    while(1);
    return STATUS_SUCCESS;
}

static BLKDEV_OPERATIONS AtaCoreBlkdevOperations = {
    //TODO Flush device
    .ReadDeviceSegment = AtaCoreBlkdevReadDeviceSegment,
    .WriteDeviceSegment = AtaCoreBlkdevWriteDeviceSegment,
    .ReadDeviceBlock = AtaCoreBlkdevReadDeviceBlock,
    .WriteDeviceBlock = AtaCoreBlkdevWriteDeviceBlock,
};

static LOUSINE_DMA_DEVICE DefaultAtaEndpointDmaDevice = {
    .MaxScatterCount = 1,
    .AllocatorData = {
        .DmaLimit = 64,
        .DmaThreshold = 64 * KILOBYTE,
    },
};

LOUSTATUS AtaCoreRegisterEndpointDevice(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice
){
        
    if(!EndpointDevice->Port->OptionalDmaDevice){
        EndpointDevice->Port->OptionalDmaDevice = &DefaultAtaEndpointDmaDevice;
    }
    return BlkdevApiCreateDeviceObject(
        0x00,
        EndpointDevice->Port->OptionalDmaDevice,
        EndpointDevice->SectorSize,
        EndpointDevice->MaxLba,
        &AtaCoreBlkdevOperations,
        (PVOID)EndpointDevice
    );
}