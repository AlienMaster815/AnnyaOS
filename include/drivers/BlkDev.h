#ifndef _BLKDEV_H
#define _BLKDEV_H

#include <cstdlib.h>
#include <Modulation.h>
#include <kernel/Dma.h>
#include <kernel/XArray.h>

typedef struct _BLOCK_SEGMENT{
    SIZE    BlockID;
    SIZE    Blocks;
}BLOCK_SEGMENT, * PBLOCK_SEGMENT;

struct _BLKDEV_OPENED_BLOCK_SEGMENT;

typedef struct _BLKDEV_OPENED_BLOCK{
    SIZE                                        BlockID;
    BOOLEAN                                     BlockInSegment;
    PVOID                                       BlockData;
    KERNEL_REFERENCE                            References;
    mutex_t                                     Loto;
    LOUSINE_DMA_TRANSFER                        DmaTransfer;
    union{
        SIZE                                    BlockSize;
        struct _BLKDEV_OPENED_BLOCK_SEGMENT*    OwnerSegment;
    };
}BLKDEV_OPENED_BLOCK, * PBLKDEV_OPENED_BLOCK;

typedef struct _BLKDEV_OPENED_BLOCK_SEGMENT{
    ListHeader                      Peers;
    BLOCK_SEGMENT                   BlockSegment;
    PVOID                           BlockData;
    SIZE                            BlockSize;
    SIZE                            BlockCount;
    SIZE                            BlockSizeTotal;
    KERNEL_REFERENCE                References;
    mutex_t                         Loto;
    LOUSINE_DMA_TRANSFER            DmaTransfer;
    BLKDEV_OPENED_BLOCK             Blocks[];
}BLKDEV_OPENED_BLOCK_SEGMENT, * PBLKDEV_OPENED_BLOCK_SEGMENT;

#define BLKDEV_FLAGS_READ_ONLY_DEVICE   (1 << 0)

struct _BLKDEV_OPERATIONS;

typedef struct _BLOCK_DEVICE_OBJECT{
    ListHeader                  Peers;
    ULONG                       DeviceFlags;
    PLOUSINE_DMA_DEVICE         DmaDevice;
    SIZE                        BlockSize;
    SIZE                        BlockCount;
    struct _BLKDEV_OPERATIONS*  Operations;
    PVOID                       PrivateData;
    ListHeader                  OpenedSegments;
    ListHeader                  OpenedBlocksList;
    XARRAY                      OpenedBlocksXa;
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

#ifndef _KERNEL_MODULE_ //i dont want externals using these
DRIVER_IMPORT LOUSTATUS BlkdevApiAcquireBlockDevices(ListHeader** BlockDevicesList);
DRIVER_IMPORT LOUSTATUS BlkdevApiReleaseBlockDevices();
#endif

DRIVER_IMPORT LOUSTATUS BlkdevApiFlushBlockDevice(PBLOCK_DEVICE_OBJECT Device);
DRIVER_IMPORT LOUSTATUS BlkdevApiSoftwareDefragment(PBLOCK_DEVICE_OBJECT Device);
DRIVER_IMPORT LOUSTATUS BlkdevApiHardwareDefragment(PBLOCK_DEVICE_OBJECT Device);

DRIVER_IMPORT LOUSTATUS BlkdevApiReadBlock(PBLOCK_DEVICE_OBJECT Device, PBLKDEV_OPENED_BLOCK Block);
DRIVER_IMPORT LOUSTATUS BlkdevApiWriteBlock(PBLOCK_DEVICE_OBJECT Device, PBLKDEV_OPENED_BLOCK Block);
DRIVER_IMPORT LOUSTATUS BlkdevApiCloseBlock(PBLOCK_DEVICE_OBJECT Device, PBLKDEV_OPENED_BLOCK Block);
DRIVER_IMPORT LOUSTATUS BlkdevApiOpenBlock(PBLOCK_DEVICE_OBJECT Device, SIZE BlockID, PBLKDEV_OPENED_BLOCK* BlockOut);

DRIVER_IMPORT LOUSTATUS BlkdevApiReadBlockSegment(PBLOCK_DEVICE_OBJECT Device, PBLKDEV_OPENED_BLOCK_SEGMENT Segment);
DRIVER_IMPORT LOUSTATUS BlkdevApiWriteBlockSegment(PBLOCK_DEVICE_OBJECT Device, PBLKDEV_OPENED_BLOCK_SEGMENT Segment);
DRIVER_IMPORT LOUSTATUS BlkdevApiCloseBlockSegment(PBLOCK_DEVICE_OBJECT Device, PBLKDEV_OPENED_BLOCK_SEGMENT Segment);
DRIVER_IMPORT LOUSTATUS BlkdevApiOpenBlockSegment(PBLOCK_DEVICE_OBJECT Device, PBLOCK_SEGMENT BlockSegment, PBLKDEV_OPENED_BLOCK_SEGMENT* SegmentOut);



#endif
#endif