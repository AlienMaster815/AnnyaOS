#define _KERNEL_MODULE_
#ifndef _8237A_H
#define _8237A_H
#include <drivers/Dma8237A.h>

#define DMA16_ST_ADDR_REG_C1        0x02  
#define DMA16_ST_ADDR_REG_C5        0xC4
#define DMA16_COUNT_REG_C1          0x03
#define DMA16_COUNT_REG_C5          0xC6
#define DMA16_ST_ADDR_REG_C2        0x04
#define DMA16_ST_ADDR_REG_C6        0xC8
#define DMA16_COUNT_REG_C2          0x05
#define DMA16_COUNT_REG_C6          0xCA
#define DMA16_ST_ADDR_REG_C3        0x06
#define DMA16_ST_ADDR_REG_C7        0xCC
#define DMA16_COUNT_REG_C3          0x07
#define DMA16_COUNT_REG_C7          0xCE
#define DMA16_STATUS_REG_0_3        0x08
#define DMA16_STATUS_REG_4_7        0xD0
#define DMA16_COMMAND_REG_0_3       0x08
#define DMA16_COMMAND_REG_4_7       0xD0
#define DMA16_REQUEST_REG_0_3       0x09
#define DMA16_REQUEST_REG_4_7       0xD2
#define DMA16_SCM_REG_0_3           0x0A
#define DMA16_SCM_REG_4_7           0xD4
#define DMA16_MODE_REG_0_3          0x0B
#define DMA16_MODE_REG_4_7          0xD6
#define DMA16_FLIP_FLOP_0_3         0x0C
#define DMA16_FLIP_FLOP_4_7         0xD8
#define DMA16_INTERMEDIATE_0_3      0x0D
#define DMA16_INTERMEDIATE_4_7      0xDA
#define DMA16_MASTER_RESET_0_3      0x0D
#define DMA16_MASTER_RESET_4_7      0xDA
#define DMA16_MASK_RESET_0_3        0x0E
#define DMA16_MASK_RESET_4_7        0xDC
#define DMA16_MULTI_CHANNEL_MASK_0_3 0x0F
#define DMA16_MULTI_CHANNEL_MASK_4_7 0xDE



#endif