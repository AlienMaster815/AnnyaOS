#ifndef _FIBRE_CHANNEL_2_H
#define _FIBRE_CHANNEL_2_H

#pragma pack(push, 1)

#define FIBRE_CHANNEL_SSB_SIZE 17

#define SSB_ST_RESP         (1 << 15)
#define SSB_ST_ACTIVE       (1 << 14)
#define SSB_ST_ABNORMAL     (1 << 12)

#define SSB_ST_REQUEST_BITS     (3 << 10)
#define SSB_ST_REQUEST_COUNT    (0 << 10)
#define SSB_ST_REQUEST_ABORT    (1 << 10)
#define SSB_ST_REQUST_STOP      (2 << 10)
#define SSB_ST_REQUEST_RE_TRANS (3 << 10)

#define SSB_ST_ABTS     (1 << 9)
#define SSB_ST_RE_TRANS (1 << 8)
#define SSB_ST_TIMEOUT  (1 << 7)
#define SSB_ST_P_RJT    (1 << 6)

#define SSB_ST_CLASS_BIT    4
#define SSB_ST_CLASS_BITS   3
#define SSB_ST_ACKNOWLEDGE  (1 << 3)

#define FIBRE_CHANNEL_ESB_SIZE (1 + 5 * 4 + 112 + 8)

#define ESB_ST_RESP             (1 << 31)
#define ESB_ST_SEQUENCE_INIT    (1 << 30)
#define ESB_ST_COMPLETE         (1 << 29)
#define ESB_ST_ABNORMAL         (1 << 28)
#define ESB_ST_REC_QUAL         (1 << 26)

#define ESB_ST_ERRP_BIT         24
#define ESB_ST_ERRP_BITS        (3 << ESB_ST_ERRP_BIT)
#define ESB_ST_ERRP_MULTI       (0 << ESB_ST_ERRP_BIT)
#define ESB_ST_ERRP_SING        (1 << ESB_ST_ERRP_BIT)
#define ESB_ST_EERP_INFI        (2 << ESB_ST_ERRP_BIT)
#define ESB_ST_EERP_IMMI        (3 << ESB_ST_ERRP_BIT)

#define ESB_ST_OX_ID_INVALID    (1 << 23)
#define ESB_ST_RX_ID_INVALID    (1 << 22)
#define ESB_ST_PRIORITY_INSUE   (1 << 21)

typedef struct _FIBRE_CHANNEL_SSB{
    uint8_t     SsbSequenceID;
    uint8_t     SsbReserved;
    uint16_t    SsbLowSequenceCount; //BigEndian
    uint16_t    SsbHighSequnceCount; //BigEndian
    uint16_t    SsbSStat;            //BigEndian
    uint16_t    SsbErrorSequnceCount;//BigEndian
    uint8_t     SsbFhCtCtl;
    uint16_t    SsbFhOxID;           //BigEndian
    uint16_t    SsbRxID;             //BigEndian
    uint8_t     SsvReserved2;
}FIBRE_CHANNEL_SSB, * PFIBRE_CHANNEL_SSB;

typedef struct _FIBRE_CHANNEL_ESB{
    uint8_t     EsbCsCtl;
    uint16_t    EsbOxID;    //BigEndian
    uint16_t    EsbRxID;    //BigEndian
    uint32_t    EsbOrigFid; //BigEndian
    uint32_t    EsbRespFid; //BigEndian
    uint32_t    EsbEStat;   //BigEndian
    uint8_t     _EsbResv[4];
    uint8_t     EsbServiceParam[112];
    uint8_t     EsbSequenceStatus[8];
}FIBRE_CHANNEL_ESB, * PFIBRE_CHANNEL_ESB;

#pragma pack(pop)
#endif //_FIBRE_CHANNEL_2_H