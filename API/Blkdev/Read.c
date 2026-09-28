#include "Blkdev.h"

DRIVER_EXPORT 
LOUSTATUS 
BlkDevApiReadBlockSegment(
    PBLKDEV_OPENED_BLOCK_SEGMENT    Segment, 
    PVOID                           Buffer, 
    SIZE                            ByteOffset, 
    SIZE                            ByteCount
){
    SIZE Count = 0;
    SIZE BytesRemaining;
    SIZE TransferSize;
    while(Count < ByteCount){
        PVOID Mem = LouKeDmaTransferGetOffsetVa(Segment->DmaTransfer, ByteOffset + Count, &BytesRemaining);
        if(!Mem){
            return STATUS_UNSUCCESSFUL;
        }
        TransferSize = MIN(BytesRemaining, ByteCount);
        memcpy((UINT8*)Buffer + Count, Mem, TransferSize);
        Count += TransferSize;
    }
    return STATUS_SUCCESS;
}
