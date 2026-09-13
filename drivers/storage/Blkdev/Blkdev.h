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

#endif
