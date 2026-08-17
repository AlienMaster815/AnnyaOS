#ifndef _BLKDEV_INTERNALS_H
#define _BLKDEV_INTERNALS_H

#define _KERNEL_MODULE_

#include <LouDDK.h>

struct _BLOCK_DEVICE_OBJECT;

typedef enum {
    SCATTER_BLOCK_TABLE_ID_READ = 0,
    SCATTER_BLOCK_TABLE_ID_WRITE,
    SCATTER_BLOCK_TABLE_ID_COPY,
}SCATTER_BLOCK_TABLE_ID;

typedef struct _BLOCK_SCATTER_TABLE{
    struct _BLOCK_DEVICE_OBJECT*    Device;
    union{
        struct{
            SIZE                    BlockBase;
            SIZE                    BlockCount;
            PVOID                   DataOut[];
        }Read;
        struct{
            SIZE                    BlockBase;
            SIZE                    BlockCount;
            PVOID                   DataIn[];
        }Write;
        struct{
            SIZE                    BlockBase;
            SIZE                    BlockCount;
            PVOID                   Data[];
        }Copy;
        struct{
            SIZE                    BlockBase;
            SIZE                    BlockCount;
            PVOID                   Data[];
        }Verify;
    };
}BLOCK_SCATTER_TABLE, * PBLOCK_SCATTER_TABLE;

typedef struct _BLOCK_DEVICE_DRIVER_OPERATIONS{
    LOUSTATUS   (*BlockDeviceReadBlocks)(PBLOCK_SCATTER_TABLE ScatterTable);
    LOUSTATUS   (*BlockDeviceWriteBlocks)(PBLOCK_SCATTER_TABLE ScatterTable);
    LOUSTATUS   (*BlockDeviceCopyBlocks)(PBLOCK_SCATTER_TABLE ScatterTable);
    LOUSTATUS   (*BlockDeviceVerifyBlocks)(PBLOCK_SCATTER_TABLE ScatterTable);
    LOUSTATUS   (*BlockDeviceInitDevInfo)(struct _BLOCK_DEVICE_OBJECT* Device);
}BLOCK_DEVICE_DRIVER_OPERATIONS, * PBLOCK_DEVICE_DRIVER_OPERATIONS;

typedef struct _BLOCK_DEVICE_DRIVER_OBJECT{
    LOUSTR                              DriverName;
    BLOCK_DEVICE_DRIVER_OPERATIONS      Operations;
    PVOID                               DriverPrivateData;
}BLOCK_DEVICE_DRIVER_OBJECT, * PBLOCK_DEVICE_DRIVER_OBJECT;

typedef struct _BLOCK_DEVICE_OBJECT{
    LOUSTR                          DeviceName;
    PBLOCK_DEVICE_DRIVER_OBJECT     DriverObject;
    DMA_FENCE                       DmaFence;
    BOOLEAN                         RemovableMedia;
    SIZE                            BlockSize;
    SIZE                            TotalBlocks;
    PVOID                           DevicePrivateData;
}BLOCK_DEVICE_OBJECT, * PBLOCK_DEVICE_OBJECT;

typedef struct _INTERNAL_BLOCK_SCATTER_TABLE{
    ListHeader             Peers;
    BLOCK_SCATTER_TABLE    Table;
}INTERNAL_BLOCK_SCATTER_TABLE, * PINTERNAL_BLOCK_SCATTER_TABLE;

typedef struct _INTERNAL_BLOCK_DEVICE_OBJECT{
    ListHeader              Peers;
    PBLOCK_DEVICE_OBJECT    DeviceObject;
}INTERNAL_BLOCK_DEVICE_OBJECT, * PINTERNAL_BLOCK_DEVICE_OBJECT;

typedef struct _INTERNAL_BLOCK_DEVICE_DRIVER_OBJECT{
    ListHeader                     Peers;
    ListHeader                     Devices;
    PBLOCK_DEVICE_DRIVER_OBJECT    DriverObject;
}INTERNAL_BLOCK_DEVICE_DRIVER_OBJECT, * PINTERNAL_BLOCK_DEVICE_DRIVER_OBJECT;



#endif
