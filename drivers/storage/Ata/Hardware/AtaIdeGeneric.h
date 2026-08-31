#ifndef _ATA_IDE_GENERIC_H
#define _ATA_IDE_GENERIC_H

#define _KERNEL_MODULE_

#include <LouDDK.h>

#define ATA_PRDT_ALIGNMENT  4
#define ATA_PRDT_BOUNDRY    64
#define ATA_PRDT_EDT_VALUE  (1 << 7)

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

#define ATA_GENCMD_DATA_OFFSET(Base)        (((UINT16)(UINTPTR)Base) + 0)
#define ATA_GENCMD_ERRFEAT_OFFSET(Base)     (((UINT16)(UINTPTR)Base) + 1)
#define ATA_GENCMD_SECTORCOUNT_OFFSET(Base) (((UINT16)(UINTPTR)Base) + 2)
#define ATA_GENCMD_LBALOW_OFFSET(Base)      (((UINT16)(UINTPTR)Base) + 3)
#define ATA_GENCMD_LBAMID_OFFSET(Base)      (((UINT16)(UINTPTR)Base) + 4)
#define ATA_GENCMD_LBAHIGH_OFFSET(Base)     (((UINT16)(UINTPTR)Base) + 5)
#define ATA_GENCMD_DEVICE_OFFSET(Base)      (((UINT16)(UINTPTR)Base) + 6)
#define ATA_GENCMD_CMDSTS_OFFSET(Base)      (((UINT16)(UINTPTR)Base) + 7)

#define ATA_ISACTL_ALTDEVSTS_OFFSET(Base)   ((UINT16)(UINTPTR)Base)
#define ATA_PCICTL_ALTDEVSTS_OFFSET(Base)   (((UINT16)(UINTPTR)Base) + 2)   

typedef struct _ATA_GENERIC_PRIVATE_DATA{
    struct {
        UINT16  Data;
        UINT16  ErrFeat;
        UINT16  SectorCount;
        UINT16  LbaLow;
        UINT16  LbaMid;
        UINT16  LbaHigh;
        UINT16  Device;
        UINT16  CmdSts;
        UINT16  AltDevSts;
        UINT16  BusMasterCmd;
        UINT16  BusMasterSts;
        UINT16  BusMasterPrd;
    }           Ports;
}ATA_GENERIC_PRIVATE_DATA, * PATA_GENERIC_PRIVATE_DATA;

#endif