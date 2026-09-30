#include "Blkdev.h"

static 
LOUSTATUS
_BlkDevApiAllocateNewSegmentObject(
    PBLKDEV_OPENED_BLOCK_SEGMENT*   NewSegment,
    SIZE                            Count
){
    if(!Count || !NewSegment){
        return STATUS_INVALID_PARAMETER;
    }
    *NewSegment = LouKeMallocEx(GetStructureSize(BLKDEV_OPENED_BLOCK_SEGMENT, Blocks, Count), GET_ALIGNMENT(BLKDEV_OPENED_BLOCK_SEGMENT), KERNEL_GENERIC_MEMORY);
    return *NewSegment ? STATUS_SUCCESS : STATUS_INSUFFICIENT_RESOURCES;
}

static void _BlkDevApiFreeSegmentObject(
    PBLKDEV_OPENED_BLOCK_SEGMENT Segment
){
    if(Segment){
        LouKeFree(Segment);
    }
}


DRIVER_EXPORT 
LOUSTATUS
BlkDevApiOpenBlockSegment(
    PBLOCK_DEVICE_OBJECT            BlockDevice,
    PBLOCK_SEGMENT                  BlockSegment,
    PBLKDEV_OPENED_BLOCK_SEGMENT*   SegmentOut
){
    if(!BlockDevice || !SegmentOut || !BlockSegment){
        return STATUS_INVALID_PARAMETER;
    }
    SIZE i;
    PBLKDEV_OPENED_BLOCK_SEGMENT TmpSegment;
    MutexLock(&BlockDevice->Loto);
    ForEachListEntry(TmpSegment, &BlockDevice->OpenedSegments, Peers){
        MutexLock(&TmpSegment->Loto);
        if(!memcmp(&TmpSegment->BlockSegment, BlockSegment, sizeof(BLOCK_SEGMENT))){
            LouKeAcquireReference(&TmpSegment->References);
            *SegmentOut = TmpSegment;
            MutexUnlock(&TmpSegment->Loto);
            MutexUnlock(&BlockDevice->Loto);
            return STATUS_SUCCESS;
        }
        MutexUnlock(&TmpSegment->Loto);
    }

    PBLKDEV_OPENED_BLOCK_SEGMENT NewSegment = 0x00;
    LOUSTATUS Status = STATUS_SUCCESS;
    SIZE BlockNumber = BlockSegment->BlockNumber;
    SIZE BlockCount = BlockSegment->BlockCount;
    SIZE BlockSize = BlkdevApiGetBlockSize(BlockDevice);
    PXARRAY OpenedBlocks = &BlockDevice->OpenedBlocksXa;
    if(!BlockSize){
        BlkDevDbgPrint("BLKDEV.SYS:Block Device(%h) Has An Invalid Block Size\n", BlockDevice);
        MutexUnlock(&BlockDevice->Loto);
        return STATUS_IO_DEVICE_ERROR;
    }
    for(UINT64 i = BlockNumber; i < (BlockNumber + BlockCount); i++){
        if(LouKeXaIsIndexUsed(OpenedBlocks, i)){
            Status = STATUS_REQUEST_NOT_ACCEPTED;
            BlkDevDbgPrint("BLKDEV.SYS:Block Device(%h) Block:%d Is Already Being Used Elseware\n", BlockDevice, i);
            goto _ERROR_OUT;
        }
    }  
    Status = _BlkDevApiAllocateNewSegmentObject(SegmentOut, BlockCount);
    if(Status != STATUS_SUCCESS){
        BlkDevDbgPrint("BLKDEV.SYS:Block Device(%h) Unable To Allocate New Segment Object\n", BlockDevice);
        goto _ERROR_OUT;
    }
    NewSegment = *SegmentOut;
    NewSegment->BlockSize = BlockSize;
    NewSegment->TotalSize = BlockSize * BlockCount;
    NewSegment->DmaTransfer = LouKeCreateDmaTransfer(BlockDevice->DmaDevice, NewSegment->TotalSize, BlockSize);
    if(!NewSegment->DmaTransfer){
        BlkDevDbgPrint("BLKDEV.SYS:Block Device(%h) Unable To Create Dma Transfer:TransferSize:%h:BlockSize:%h\n", BlockDevice, NewSegment->TotalSize, BlockSize);
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto _ERROR_OUT;
    }

    LouKeAcquireReference(&NewSegment->References);
    NewSegment->BlockSegment = *BlockSegment;
    NewSegment->Device = BlockDevice;
    Status = BlkDevReadDeviceSegment(BlockDevice, NewSegment);
    if(Status != STATUS_SUCCESS){   
        BlkDevDbgPrint("BLKDEV.SYS:Block Device(%h) Unable To Read Device Segment\n", BlockDevice);
        goto _ERROR_OUT;
    }
    for(i = 0 ; i < BlockCount; i++){
        PBLKDEV_OPENED_BLOCK NewBlock = &NewSegment->Blocks[i];
        NewBlock->BlockNumber = BlockNumber + i; 
        NewBlock->BlockSize = BlockSize;
        NewBlock->BlockInSegment = true; 
        NewBlock->OwnerSegment = NewSegment;       
        NewBlock->Device = BlockDevice;
        Status = LouKeXaStore(OpenedBlocks, NewBlock->BlockNumber, NewBlock, 0x00, KERNEL_GENERIC_MEMORY);
        if(Status != STATUS_SUCCESS){
            goto _ERROR_ON_XA_STORE;
        }
        LouKeAcquireReference(&NewBlock->References);
        LouKeListAddTail(&NewBlock->Peers, &BlockDevice->OpenedBlocksList);
    }
    LouKeListAddTail(&NewSegment->Peers, &BlockDevice->OpenedSegments);
    MutexUnlock(&BlockDevice->Loto);
    return STATUS_SUCCESS;
_ERROR_ON_XA_STORE:
    for(SIZE j = 0; j < i; j++){
        PBLKDEV_OPENED_BLOCK NewBlock = &NewSegment->Blocks[j];
        LouKeXaFreeUint64(OpenedBlocks, NewBlock->BlockNumber);
        LouKeListDeleteItem(&NewBlock->Peers);
        LouKeReleaseReference(&NewBlock->References);
    }    

_ERROR_OUT:
    if(NewSegment && NewSegment->DmaTransfer){
        LouKeDestroyDmaTransfer(NewSegment->DmaTransfer);
    }
    _BlkDevApiFreeSegmentObject(NewSegment);
    MutexUnlock(&BlockDevice->Loto);
    return Status;
}

DRIVER_EXPORT 
LOUSTATUS
BlkDevApiCloseBlockSegment(
    PBLKDEV_OPENED_BLOCK_SEGMENT    Segment
){
    if(!Segment){
        return STATUS_INVALID_PARAMETER;
    }
    PBLOCK_DEVICE_OBJECT BlockDevice = Segment->Device;
    SIZE CurrentReferences;
    MutexLock(&BlockDevice->Loto);
    LouKeReleaseReference(&Segment->References);
    CurrentReferences = LouKeGetReferenceCount(&Segment->References);
    if(CurrentReferences){
        MutexUnlock(&BlockDevice->Loto);
        return STATUS_SUCCESS;
    }
    LouKeListDeleteItem(&Segment->Peers);
    PXARRAY OpenedBlocks = &BlockDevice->OpenedBlocksXa;
    SIZE BlockNumber = Segment->BlockSegment.BlockNumber;
    SIZE BlockCount = Segment->BlockSegment.BlockCount;

    for(SIZE i = 0 ; i < BlockCount; i++){
        PBLKDEV_OPENED_BLOCK TmpBlock = &Segment->Blocks[i];
        LouKeXaFreeUint64(OpenedBlocks, TmpBlock->BlockNumber);
        LouKeListDeleteItem(&TmpBlock->Peers);
        LouKeReleaseReference(&TmpBlock->References);
    }
    
    LouKeDestroyDmaTransfer(Segment->DmaTransfer);
    
    MutexUnlock(&Segment->Loto);
    MutexUnlock(&BlockDevice->Loto);
    _BlkDevApiFreeSegmentObject(Segment);
    return STATUS_SUCCESS;
}
