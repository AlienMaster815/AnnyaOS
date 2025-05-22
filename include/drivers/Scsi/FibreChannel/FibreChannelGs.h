#ifndef _FIBRE_CHANNEL_GS_H
#define _FIBRE_CHANNEL_GS_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else 
#include <LouAPI.h>
#endif

//BigEndian
typedef struct _FIBRE_CHANNEL_COMMON_TRANSPORT_HEADER{
    uint8_t     Revision;
    uint8_t     NPortID[3];
    uint8_t     Type;
    uint8_t     SubType;
    uint8_t     Options;
    uint8_t     Reserved1;
    uint16_t    Command;
    uint16_t    ResidualSize;
    uint8_t     Reserved2;
    uint8_t     Reason;
    uint8_t     Explained;
    uint8_t     VendorID;
}FIBRE_CHANNEL_COMMON_TRANSPORT_HEADER, * PFIBRE_CHANNEL_COMMON_TRANSPORT_HEADER;

#define FIBRE_CHANNEL_COMMON_TRANSPORT_HEADER_LENGTH    16

#define FIBRE_CHANNEL_COMMON_TRANSPORT_REVISION         1

#define FIBRE_CHANNEL_FS_TYPE_ALIAL         0xF8
#define FIBRE_CHANNEL_FS_TYPE_MANAGEMENT    0xFA
#define FIBRE_CHANNEL_FS_TYPE_TIME          0xFB
#define FIBRE_CHANNEL_FS_TYPE_DIR           0xFC

#define FIBRE_CHANNEL_FS_REJECT_REASON_COMMAND      0x01
#define FIBRE_CHANNEL_FS_REJECT_REASON_VERSION      0x02
#define FIBRE_CHANNEL_FS_REJECT_REASON_LOGICAL      0x03
#define FIBRE_CHANNEL_FS_REJECT_REASON_IU_SIZE      0x04
#define FIBRE_CHANNEL_FS_REJECT_REASON_BUSY         0x05
#define FIBRE_CHANNEL_FS_REJECT_REASON_PROTOCOL     0x07
#define FIBRE_CHANNEL_FS_REJECT_REASON_UNABLE       0x09
#define FIBRE_CHANNEL_FS_REJECT_REASON_USUPORTED    0x0B

#define FIBRE_CHANNEL_FS_EXPLANATION_NONE               0x00
#define FIBRE_CHANNEL_FS_EXPLANATION_PORT_ID            0x01
#define FIBRE_CHANNEL_FS_EXPLANATION_PORT_NAME          0x02
#define FIBRE_CHANNEL_FS_EXPLANATION_NODE_NAME          0x03
#define FIBRE_CHANNEL_FS_EXPLANATION_CLASS_OF_SERVICE   0x04
#define FIBRE_CHANNEL_FS_EXPLANATION_FC4_NOT_REGISTERED 0x07

#ifdef __cplusplus
}
#endif
#endif //_FIBRE_CHANNEL_GS_H