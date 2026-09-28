#include "Blkdev.h"

LOUSTATUS BlkDevReadDeviceSegment(PBLOCK_DEVICE_OBJECT BlockDevice, PBLKDEV_OPENED_BLOCK_SEGMENT Segment){
    if(!BlockDevice->Operations->ReadDeviceSegment){
        return STATUS_REQUEST_NOT_ACCEPTED;
    }
    LOUSTATUS Status;
    MutexLock(&Segment->Loto);
    LouKeSetupDmaTransferFence(Segment->DmaTransfer, 5000, ((BlockDevice->DeviceFlags & BLKDEV_FLAGS_COMPLETION_INTERRUPT) ? false : true));
    Status = BlockDevice->Operations->ReadDeviceSegment(BlockDevice, Segment);
    if(Status == STATUS_SUCCESS){
        Status = LouKeFenceDmaTransfer(Segment->DmaTransfer);
    }
    //LouKeFinishDmaTransferFence(Segment->DmaTransfer); TODO
    MutexUnlock(&Segment->Loto);
    return Status;
}