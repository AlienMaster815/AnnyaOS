#ifndef _ATA_DMA_H
#define _ATA_DMA_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else
#include <LouAPI.h>
#endif

#define ATA_PRIMARY_DMA_COMMAND_BYTE_OFFSET             0x00
#define ATA_PRIMARY_DMA_STATUS_BYTE_OFFSET              0x02
#define ATA_PRIMARY_DMA_PRDT_OFFSET                     0x04
#define ATA_SECONDARY_DMA_COMMAND_BYTE_OFFSET           0x08
#define ATA_SECONDARY_DMA_SATIS_BYTE_OFFSET             0x0A
#define ATA_SECONDARY_DMA_PRDT_OFFSET                   0x0C

typedef struct __attribute__((aligned(4))) _ATA_PRDT_ENTRY{
    uint32_t PhysicalAddress;
    uint16_t TrasferSize;
    uint16_t ControllerReserved;
}ATA_PRDT_ENTRY, * PATA_PRDT_ENTRY;

#define ATA_READ_PRIMARY_DMA_COMMAND_PORT       inb(DmaPort + ATA_PRIMARY_DMA_COMMAND_BYTE_OFFSET)
#define ATA_WRITE_PRIMARY_DMA_COMMAND_PORT(x)   outb(DmaPort + ATA_PRIMARY_DMA_COMMAND_BYTE_OFFSET, (x))
#define ATA_READ_PRIMARY_DMA_STATUS_PORT        inb(DmaPort + ATA_PRIMARY_DMA_STATUS_BYTE_OFFSET)
#define ATA_WRITE_PRIMARY_DMA_STATUS_PORT(x)    outb(DmaPort + ATA_PRIMARY_DMA_STATUS_BYTE_OFFSET, (x))
#define ATA_READ_PRIMARY_DMA_PRDT_PORT          inl(DmaPort + ATA_PRIMARY_DMA_PRDT_OFFSET)
#define ATA_WRITE_PRIMARY_DMA_PRDT_PORT(x)      outl(DmaPort + ATA_PRIMARY_DMA_PRDT_OFFSET, (uint32_t)(uintptr_t)(x))

#define ATA_READ_SECONDARY_DMA_COMMAND_PORT       inb(DmaPort + ATA_SECONDARY_DMA_COMMAND_BYTE_OFFSET)
#define ATA_WRITE_SECONDARY_DMA_COMMAND_PORT(x)   outb(DmaPort + ATA_SECONDARY_DMA_COMMAND_BYTE_OFFSET, (x))
#define ATA_READ_SECONDARY_DMA_STATUS_PORT        inb(DmaPort + ATA_SECONDARY_DMA_STATUS_BYTE_OFFSET)
#define ATA_WRITE_SECONDARY_DMA_STATUS_PORT(x)    outb(DmaPort + ATA_SECONDARY_DMA_STATUS_BYTE_OFFSET, (x))
#define ATA_READ_SECONDARY_DMA_PRDT_PORT          inl(DmaPort + ATA_SECONDARY_DMA_PRDT_OFFSET)
#define ATA_WRITE_SECONDARY_DMA_PRDT_PORT(x)      outl(DmaPort + ATA_SECONDARY_DMA_PRDT_OFFSET, (uint32_t)(uintptr_t)(x))

#define ATA_DMA_ACKNOLEDGE_PRIMARY_INTERRUPT        ATA_WRITE_PRIMARY_DMA_STATUS_PORT(ATA_READ_PRIMARY_DMA_STATUS_PORT & ~(1 << 2))
#define ATA_DMA_ACKNOLEDGE_SECONDARY_INTERRUPT      ATA_WRITE_SECONDARY_DMA_STATUS_PORT(ATA_READ_SECONDARY_DMA_STATUS_PORT & ~(1 << 2))

#ifdef __cplusplus
}
#endif
#endif //_ATA_DMA_H