#ifndef _ATA_IDE_GENERIC_H
#define _ATA_IDE_GENERIC_H

#define _KERNEL_MODULE_

#include <LouDDK.h>

#define ATA_PRDT_ALIGNMENT  4
#define ATA_PRDT_BOUNDRY    64
#define ATA_PRDT_EDT_VALUE  (1 << 8)

#define ATA_BM_PRI_IDE_CMD_REG_OFFSET   0x00
#define ATA_BM_PRI_IDE_STS_REG_OFFSET   0x02
#define ATA_BM_PRI_IDE_PRD_REG_OFFSET   0x04

#define ATA_BM_SEC_IDE_CMD_REG_OFFSET   0x08
#define ATA_BM_SEC_IDE_STS_REG_OFFSET   0x0A
#define ATA_BM_SEC_IDE_PRD_REG_OFFSET   0x0C

#define ATA_BM_CMD_RW_CONTROL           (1 << 3)

#define ATA_BM_STS_SIMPLEX_ONLY         (1 << 7)
#define ATA_BM_STS_DRIVE1_DMA_CAP       (1 << 6)
#define ATA_BM_STS_DRIVE0_DMA_CAP       (1 << 5)
#define ATA_BM_STS_INTERRUPT            (1 << 2)
#define ATA_BM_STS_ERROR                (1 << 1)
#define ATA_BM_STS_IDE_ACTIVE           (1 << 0)

typedef struct PACKED _ATA_PRDT_ENTRY{
    UINT32  DmaAddress;
    UINT16  DmaSize;
    UINT8   Reserved;
    UINT8   Edt;
}ATA_PRDT_ENTRY, * PATA_PRDT_ENTRY;



#endif