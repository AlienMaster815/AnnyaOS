#include "Blkdev.h"

LOUSTATUS BlkDevReadDeviceSegment(PBLOCK_DEVICE_OBJECT BlockDevice, PBLKDEV_OPENED_BLOCK_SEGMENT Segment){
    if(!BlockDevice->Operations->ReadDeviceSegment){
        return STATUS_REQUEST_NOT_ACCEPTED;
    }
    LOUSTATUS Status;
    MutexLock(&BlockDevice->Loto);
    MutexLock(&Segment->Loto);
    Status = BlockDevice->Operations->ReadDeviceSegment(BlockDevice, Segment);
    MutexUnlock(&Segment->Loto);
    MutexUnlock(&BlockDevice->Loto);
    return Status;
}