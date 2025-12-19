#define _KERNEL_MODULE_
#ifndef _SBMOD_H
#define _SBMOD_H

#include <LouDDK.h>

typedef struct _DMA16_TRANSFER_PACKET{
    UINT32  DmaAddress;
    UINT16  Transferlength;
    UINT16  TransferMode;
    UINT8   Channel;
    UINT8   Transfer    : 2;
    UINT8   Auto        : 1;
    UINT8   Down        : 1;
    UINT8   Mode        : 2;
}DMA16_TRANSFER_PACKET, * PDMA16_TRANSFER_PACKET;

KERNEL_EXPORT
PVOID LouKeMallocDma16Ex(
    SIZE AllocationSize, 
    UINT64 Alignment
);
KERNEL_EXPORT
PVOID LouKeMallocDma16(
    SIZE AllocationSize
);
KERNEL_EXPORT
void LouKeFreeDma16(
    PVOID Address
);

#endif //_SBMOD_H