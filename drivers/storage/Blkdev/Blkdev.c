#include "Blkdev.h"

BOOLEAN DbgPrintEn = false;

static mutex_t      DeviceLock = {0};
static ListHeader   DeviceList = {0};

void BlkDevDbgPrint(char* format, ...){
    if(DbgPrintEn){
        va_list args;
        va_start(args, format);
        LouPrintEx(format, args);
        va_end(args);
    }
}


LOUSTATUS BlkDevEntry(){
    HANDLE BlkDebugKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\DEBUG\\BLKDEV_DEBUG", 0x00);
    BYTE DbgValue = 0;
    LouKeReadRegistryByteValue(BlkDebugKey, &DbgValue);
    DbgPrintEn = DbgValue ? true : false;
    return STATUS_SUCCESS;
}


DRIVER_EXPORT 
LOUSTATUS 
BlkdevApiCreateDeviceObject(
    ULONG               DeviceFlags, 
    PLOUSINE_DMA_DEVICE DmaDevice, 
    SIZE                BlockSize, 
    SIZE                BlockCount, 
    PBLKDEV_OPERATIONS  Operations, 
    PVOID               PrivateData
){
    BlkDevDbgPrint("BLKDEV.SYS:Creating New Block Device\n");
    PBLOCK_DEVICE_OBJECT NewBlockDevice = LouKeMallocType(BLOCK_DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
    if(!NewBlockDevice){
        BlkDevDbgPrint("BLKDEV.SYS:Unable To Create New Block Device\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    
    NewBlockDevice->DeviceFlags = DeviceFlags;
    NewBlockDevice->DmaDevice = DmaDevice;
    NewBlockDevice->BlockSize = BlockSize;
    NewBlockDevice->BlockCount = BlockCount;
    NewBlockDevice->Operations = Operations;
    NewBlockDevice->PrivateData = PrivateData;

    MutexLock(&DeviceLock);
    LouKeListAddTail(&NewBlockDevice->Peers, &DeviceList);
    MutexUnlock(&DeviceLock);

    BlkDevDbgPrint("BLKDEV.SYS:Block Device Created Successfully\n");

    return STATUS_SUCCESS;
}