#include "AtaCore.h"

//TODO seperate the READ10 and READ16 CDBs

LOUSTATUS 
AtaCoreGetEndpointCapacity(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice,
    UINT64*                     OutLba,
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
        UINT32 tLastLba, tSectorSize;
        LOUSTATUS Status = AtaCoreAtapiEndpointReadCapacity10(
            EndpointDevice, 
            &tLastLba, &tSectorSize
        );
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        EndpointDevice->MaxLba = tLastLba;
        EndpointDevice->SectorSize = tSectorSize;
        if(OutLba){
            *OutLba = tLastLba;
        }
        if(OutSectorSize){
            *OutSectorSize = tSectorSize;
        }
        return STATUS_SUCCESS;
    }
    if(OutLba){
        *OutLba = EndpointDevice->MaxLba;
    } 
    if(OutSectorSize){ 
        *OutSectorSize = EndpointDevice->SectorSize;
    } 
    return STATUS_SUCCESS;
}

LOUSTATUS 
AtaCoreReadSectorsFromEndpointAtapiDevicePolled(
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice,
    UINT64                      Lba,
    UINT32                      SectorCount,
    PLOUSINE_DMA_TRANSFER       Transfer
){
    UINT64 MaxLba;
    UINT32 SectorSize;
    LOUSTATUS Status = AtaCoreGetEndpointCapacity(EndpointDevice, &MaxLba, &SectorSize);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(((Lba + SectorCount) > MaxLba) || ((SectorCount * SectorSize) > UINT16_MAX)){
        return STATUS_INVALID_PARAMETER;
    }
    
    if(EndpointDevice->DeviceCap & ATA_ENDPOINT_DEVCAP_ATAPI){
        if((Lba > UINT32_MAX) || (SectorCount > UINT16_MAX)){
            return STATUS_INTEGER_OVERFLOW;
        }
        return AtaCoreAtapiEndpointRead10(
            EndpointDevice,
            (UINT32)(Lba & UINT32_MAX),
            (UINT16)(SectorCount & UINT16_MAX),
            Transfer
        );
    }
    return STATUS_UNSUCCESSFUL;
}

LOUSTATUS AtaCoreBlkdevFlushDevice(PBLOCK_DEVICE_OBJECT BlockDevice){

    LouPrint("ATACORE.SYS:AtaCoreBlkdevFlushDevice()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS AtaCoreBlkdevReadDeviceSegment(PBLOCK_DEVICE_OBJECT BlockDevice, PBLKDEV_OPENED_BLOCK_SEGMENT Segment){
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice = (PATA_ENDPOINT_DEVICE_OBJECT)BlockDevice->PrivateData;
    if(BlockDevice->DeviceFlags & BLKDEV_FLAGS_COMPLETION_INTERRUPT){
        LouPrint("ATACORE.SYS:AtaCoreBlkdevReadDeviceSegment()\n");
        while(1);
    }


    if(EndpointDevice->DeviceCap & ATA_ENDPOINT_DEVCAP_ATAPI){
        return AtaCoreReadSectorsFromEndpointAtapiDevicePolled(
            EndpointDevice, 
            Segment->BlockSegment.BlockNumber, 
            Segment->BlockSegment.BlockCount, 
            Segment->DmaTransfer
        );
    }
        
    LouPrint("ATACORE.SYS:AtaCoreBlkdevReadDeviceSegment():ATA\n");
    while(1);
    return STATUS_INVALID_PARAMETER; 
}

LOUSTATUS AtaCoreBlkdevWriteDeviceSegment(PBLOCK_DEVICE_OBJECT BlockDevice, PBLKDEV_OPENED_BLOCK_SEGMENT Segment){

    LouPrint("ATACORE.SYS:AtaCoreBlkdevWriteDeviceSegment()\n");
    while(1);
    return STATUS_SUCCESS;
}


static BLKDEV_OPERATIONS AtaCoreBlkdevOperations = {
    //TODO Flush device
    .ReadDeviceSegment = AtaCoreBlkdevReadDeviceSegment,
    .WriteDeviceSegment = AtaCoreBlkdevWriteDeviceSegment,
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
        (SIZE)EndpointDevice->SectorSize,
        (SIZE)EndpointDevice->MaxLba,
        &AtaCoreBlkdevOperations,
        (PVOID)EndpointDevice
    );
}