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

//#define C0_PAGE_ADDRESS_REGISTER    0x87
#define C1_PAGE_ADDRESS_REGISTER    0x83
#define C2_PAGE_ADDRESS_REGISTER    0x81
#define C3_PAGE_ADDRESS_REGISTER    0x82
//#define C4_PAGE_ADDRESS_REGISTER    0x8F
#define C5_PAGE_ADDRESS_REGISTER    0x8B
#define C6_PAGE_ADDRESS_REGISTER    0x89
#define C7_PAGE_ADDRESS_REGISTER    0x8A


#define DMA_CLEAR_FF_REG(ctrl) ((ctrl) ? DMA16_FLIP_FLOP_4_7 : DMA16_FLIP_FLOP_0_3)

#define TRANSFER_DIRECTION_READ 0
#define TRANSFER_DIRECTION_WRITE 1

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

#define DMA16_SET_CHANNEL(x)                    (((x) > 3) ? (x - 4) : (x))
#define TRANSFER_SELF_TEST                      0b00
#define TRANSFER_DEVICE_WRAM                    0b01
#define TRANSFER_DEVICE_RRAM                    0b10

#define AUTO_RELOAD_START_ON_COMPLETION         1
#define AUTO_STANDBY_ON_COMPLETION              0

#define DOWN_REVERSE_TRANSFER_ORDER             1
#define DOWN_REGULAR_TRANSFER_ORDER             0

#define MODE_TRANSFER_ON_DEMAND                 0b00
#define MODE_SINGLE_DMA_TRANSFER                0b01
#define MODE_BLOCK_DMA_TRANSFER                 0b10
#define MODE_CASCADE_SLAVE_CHIP                 0b11

#ifndef _INTERNAL_

DRIVER_EXPORT
LOUSTATUS Initialize8237ADmaTransfer(
    PDMA16_TRANSFER_PACKET Packet
);

#endif

#endif