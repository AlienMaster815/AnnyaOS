#ifndef _BLKDEV_INTERNALS_H
#define _BLKDEV_INTERNALS_H

#define _KERNEL_MODULE_

#include <LouDDK.h>

DRIVER_EXPORT 
LOUSTATUS 
BlkdevApiCreateDeviceObject(
    ULONG               DeviceFlags, 
    PLOUSINE_DMA_DEVICE DmaDevice, 
    SIZE                BlockSize, 
    SIZE                BlockCount, 
    PBLKDEV_OPERATIONS  Operations, 
    PVOID               PrivateData
);

DRIVER_EXPORT void BlkDevApiReleaseDeviceReference(PBLOCK_DEVICE_OBJECT BlockDevice);
DRIVER_EXPORT LOUSTATUS BlkDevApiAcquireDeviceReference(PBLOCK_DEVICE_OBJECT BlockDevice);
DRIVER_EXPORT SIZE BlkdevApiGetBlockSize(PBLOCK_DEVICE_OBJECT BlockDevice);

LOUSTATUS BlkDevReadDeviceSegment(PBLOCK_DEVICE_OBJECT BlockDevice, PBLKDEV_OPENED_BLOCK_SEGMENT Segment);
void BlkDevDbgPrint(char* format, ...);


#endif
