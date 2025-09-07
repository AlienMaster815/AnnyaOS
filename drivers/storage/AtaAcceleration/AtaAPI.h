#ifndef _ATA_API_H
#define _ATA_API_H

#include <LouDDK.h>

#define ATA_READ_ID_POST_RESET      (1)
#define ATA_DOWN_XFER_PIO           0
#define ATA_DOWN_XFER_DMA           1
#define ATA_DOWN_XFER_40C           2
#define ATA_DOWN_XFER_FORCE_PIO     3
#define ATA_DOWN_XFER_FORCE_PIO0    4
#define ATA_DOWN_XFER_QUIET         (1 << 31)



#endif