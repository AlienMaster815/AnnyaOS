#ifndef _BLKDEV_H
#define _BLKDEV_H

#include <cstdlib.h>
#include <Modulation.h>
#include <kernel/Dma.h>
#include <kernel/XArray.h>

typedef struct _BLOCK_SEGMENT{
    SIZE    BlockNumber;
    SIZE    BlockCount;
}BLOCK_SEGMENT, * PBLOCK_SEGMENT;

struct _BLKDEV_OPENED_BLOCK_SEGMENT;
struct _BLOCK_DEVICE_OBJECT;

typedef struct _BLKDEV_OPENED_BLOCK{
    ListHeader                                  Peers;
    SIZE                                        BlockNumber;
    SIZE                                        BlockSize;
    BOOLEAN                                     BlockInSegment;
    KERNEL_REFERENCE                            References;
    mutex_t                                     Loto;
    struct _BLOCK_DEVICE_OBJECT*                Device;
    union{
        PLOUSINE_DMA_TRANSFER                   DmaTransfer;
        struct _BLKDEV_OPENED_BLOCK_SEGMENT*    OwnerSegment;
    };
}BLKDEV_OPENED_BLOCK, * PBLKDEV_OPENED_BLOCK;

typedef struct _BLKDEV_OPENED_BLOCK_SEGMENT{
    ListHeader                      Peers;
    BLOCK_SEGMENT                   BlockSegment;
    SIZE                            BlockSize;
    SIZE                            TotalSize;
    KERNEL_REFERENCE                References;
    mutex_t                         Loto;
    struct _BLOCK_DEVICE_OBJECT*    Device;
    PLOUSINE_DMA_TRANSFER           DmaTransfer;
    BLKDEV_OPENED_BLOCK             Blocks[];
}BLKDEV_OPENED_BLOCK_SEGMENT, * PBLKDEV_OPENED_BLOCK_SEGMENT;

#define BLKDEV_FLAGS_READ_ONLY_DEVICE   (1 << 0)
#define BLKDEV_FLAGS_

struct _BLKDEV_OPERATIONS;

typedef struct _BLOCK_DEVICE_OBJECT{
    ListHeader                  Peers;
    ULONG                       DeviceFlags;
    PLOUSINE_DMA_DEVICE         DmaDevice;
    SIZE                        BlockSize;
    SIZE                        BlockCount;
    mutex_t                     Loto;
    struct _BLKDEV_OPERATIONS*  Operations;
    PVOID                       PrivateData;
    ListHeader                  OpenedSegments;
    ListHeader                  OpenedBlocksList;
    XARRAY                      OpenedBlocksXa;
    KERNEL_REFERENCE            DeviceReference;
}BLOCK_DEVICE_OBJECT, * PBLOCK_DEVICE_OBJECT;


typedef struct _BLKDEV_OPERATIONS{
    LOUSTATUS (*FlushDevice)(PBLOCK_DEVICE_OBJECT Device);
    LOUSTATUS (*ReadDeviceSegment)(PBLOCK_DEVICE_OBJECT Device, PBLKDEV_OPENED_BLOCK_SEGMENT Segment);
    LOUSTATUS (*WriteDeviceSegment)(PBLOCK_DEVICE_OBJECT Device, PBLKDEV_OPENED_BLOCK_SEGMENT Segment);
    LOUSTATUS (*ReadDeviceBlock)(PBLOCK_DEVICE_OBJECT Device, PBLKDEV_OPENED_BLOCK Block);
    LOUSTATUS (*WriteDeviceBlock)(PBLOCK_DEVICE_OBJECT Device, PBLKDEV_OPENED_BLOCK Block);
}BLKDEV_OPERATIONS, * PBLKDEV_OPERATIONS;


#define ForEachBlockDevice(t, l)        ForEachListEntry(t, l, Peers)
#define ForEachBlockDeviceSafe(t, s, l) ForEachListEntrySafe(t, s, l)

#ifndef _BLKDEV_INTERNALS_H

DRIVER_IMPORT 
LOUSTATUS 
BlkdevApiCreateDeviceObject(
    ULONG               DeviceFlags, 
    PLOUSINE_DMA_DEVICE DmaDevice, 
    SIZE                BlockSize, 
    SIZE                BlockCount, 
    PBLKDEV_OPERATIONS  Operations, 
    PVOID               PrivateData
);

DRIVER_IMPORT LOUSTATUS BlkDevApiFlushBlockDevice(PBLOCK_DEVICE_OBJECT Device);
DRIVER_IMPORT LOUSTATUS BlkDevApiSoftwareDefragment(PBLOCK_DEVICE_OBJECT Device);
DRIVER_IMPORT LOUSTATUS BlkDevApiHardwareDefragment(PBLOCK_DEVICE_OBJECT Device);

DRIVER_IMPORT LOUSTATUS BlkDevApiReadBlock(PBLKDEV_OPENED_BLOCK Block, PVOID Buffer, SIZE ByteOffset, SIZE ByteCount);
DRIVER_IMPORT LOUSTATUS BlkDevApiWriteBlock(PBLKDEV_OPENED_BLOCK Block, PVOID Buffer, SIZE ByteOffset, SIZE ByteCount);
DRIVER_IMPORT LOUSTATUS BlkDevApiCloseBlock(PBLKDEV_OPENED_BLOCK Block);
DRIVER_IMPORT LOUSTATUS BlkDevApiOpenBlock(PBLOCK_DEVICE_OBJECT Device, SIZE Block, PBLKDEV_OPENED_BLOCK* BlockOut);

DRIVER_IMPORT LOUSTATUS BlkDevApiReadBlockSegment(PBLKDEV_OPENED_BLOCK_SEGMENT Segment, PVOID Buffer, SIZE ByteOffset, SIZE ByteCount);
DRIVER_IMPORT LOUSTATUS BlkDevApiWriteBlockSegment(PBLKDEV_OPENED_BLOCK_SEGMENT Segment, PVOID Buffer, SIZE ByteOffset, SIZE ByteCount);
DRIVER_IMPORT LOUSTATUS BlkDevApiCloseBlockSegment(PBLKDEV_OPENED_BLOCK_SEGMENT Segment);
DRIVER_IMPORT LOUSTATUS BlkDevApiOpenBlockSegment(PBLOCK_DEVICE_OBJECT Device, PBLOCK_SEGMENT BlockSegment, PBLKDEV_OPENED_BLOCK_SEGMENT* SegmentOut);

DRIVER_IMPORT PListHeader BlkDevGetBlockDevices();
DRIVER_IMPORT void BlkDevPutBlockDevices();

DRIVER_IMPORT SIZE BlkdevApiGetBlockSize(PBLOCK_DEVICE_OBJECT BlockDevice);

DRIVER_IMPORT LOUSTATUS BlkDevApiAcquireDeviceReference(PBLOCK_DEVICE_OBJECT BlockDevice);
DRIVER_IMPORT void BlkDevApiReleaseDeviceReference(PBLOCK_DEVICE_OBJECT BlockDevice);


#endif
#endif