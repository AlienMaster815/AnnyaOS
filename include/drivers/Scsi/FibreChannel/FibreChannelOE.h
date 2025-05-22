#ifndef _FIBRE_CHANNEL_OE_H
#define _FIBRE_CHANNEL_OE_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else 
#include <LouAPI.h>
#endif

#define FIBRE_CHANNEL_OE_OUI                0x0EFC00
#define FIBRE_CHANNEL_OE_FLOGIC_MAGIC       {0x0E, 0x0FC, 0x00, 0xFF, 0xFF, 0xFE}
#define FIBRE_CHANNEL_OE_VERSION            0

#define FIBRE_CHANNEL_OE_ENCAPSULATE_ID(x)     (((uint64_t)FIBRE_CHANNEL_OE_OUI << 24) | (x))
#define FIBRE_CHANNEL_OE_DECAPSULATE_ID(x)     ((x) >> 24)

typedef struct _FIBRE_CHANNEL_OE_HEADER{
    uint8_t     FcoeVersion;
    uint8_t     FcoeReserved[12];
    uint8_t     FcoeFrameStart;
}FIBRE_CHANNEL_OE_HEADER, * PFIBRE_CHANNEL_OE_HEADER;

#define FIBRE_CHANNEL_OE_ENCAPSULATE_VERSION(Header, Version) ((Header)->FcoeVersion = (Version) << 4)
#define FIBRE_CHANNEL_OE_DECAPSULATE_VERSION(Header) ((Header)->FcoeVersion >> 4)

#pragma pack(push,1)
typedef struct _FIBRE_CHANNEL_OE_CRC_ENDOF_FILE{
    uint32_t FcoeCrc32;
    uint8_t  FcoeEof;
    uint8_t  FcoeReserved[3];
}FIBRE_CHANNEL_OE_CRC_ENDOF_FILE, * PFIBRE_CHANNEL_OE_CRC_ENDOF_FILE;
#pragma pack(pop)

#define FIBRE_CHANNEL_OE_HEADER_LENGTH 38
#define FIBRE_CHANNEL_OE_MINIMUM_FRAME 46

//Big Endian Structure
typedef struct _FIBRE_CHANNEL_OE_ELS_LESB{
    uint32_t LesbLinkFail;
    uint32_t LesbVlinkFail;
    uint32_t LesbMissFka;
    uint32_t LesbSymbolError;
    uint32_t LesbErrorBlockCount;
    uint32_t LesbFcsError;
}FIBRE_CHANNEL_OE_ELS_LESB, * PFIBRE_CHANNEL_OE_ELS_LESB;

static inline void FibreChabnnelOeSetMac(
    uint8_t* MacBuffer,
    uint8_t* DeviceID
){

    MacBuffer[0] = (uint8_t)(FIBRE_CHANNEL_OE_OUI >> 16) & 0xFF;
    MacBuffer[1] = (uint8_t)(FIBRE_CHANNEL_OE_OUI >> 8) & 0xFF;
    MacBuffer[2] = (uint8_t)FIBRE_CHANNEL_OE_OUI & 0xFF;
    MacBuffer[3] = DeviceID[0];
    MacBuffer[4] = DeviceID[1];
    MacBuffer[5] = DeviceID[2];
}

#ifdef __cplusplus
}
#endif
#endif //_FIBRE_CHANNEL_OE_H