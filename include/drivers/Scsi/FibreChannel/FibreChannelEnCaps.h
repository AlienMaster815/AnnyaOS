#ifndef _FIBRE_CHANNEL_ENCAPS_H
#define _FIBRE_CHANNEL_ENCAPS_H

#pragma pack(push, 1)

#define FIBRE_CHANNEL_ENCAPS_MIN_FRAME_LENGTH  64
#define FIBRE_CHANNEL_ENCAPS_MAX_FRAME_LENGTH (FIBRE_CHANNEL_ENCAPS_MIN_FRAME_LENGTH + FIBRE_CHANNEL_MAX_PAYLOADS)

#define FIBRE_CHANNEL_ENCAPS_VERSION    1

#define FIBRE_CHANNEL_IP_ENCAPS_HEADER_LENGTH 0x20

#define FIBRE_CHANNEL_XY(X,Y) ((((X) & 0xFF) << 8) | ((Y) & 0xFF))
#define FIBRE_CHANNEL_XYXY(X,Y) ((FIBRE_CHANNEL_IP_XY(X, Y) << 16) | FIBRE_CHANNEL_XY(X, Y))
#define FIBRE_CHANNEL_XYNN(X,Y) (FIBRE_CHANNEL_IP_XYXY(X,Y) ^ 0xFFFF)

#define FIBRE_CHANNEL_SOF_ENCODE(n) FIBRE_CHANNEL_XYNN(n,n)
#define FIBRE_CHANNEL_EOF_ENCODE(n) FIBRE_CHANNEL_XYNN(n,n)

#define FIBRE_CHANNEL_SOF_CLASS_BITS 0x06


typedef struct _FIBRE_CHANNEL_ENCAPS_HEADER{
    uint8_t     FibreChannelProtocol;
    uint8_t     FibreChannelVersion;
    uint8_t     FibreChannelProtocolN;
    uint8_t     FibreChannelVersionN;
    uint8_t     FibreChannelProtocolData[8];
    uint16_t    FibreChannelLengthAndFlags; //Big Endian
    uint16_t    FibreChannelLengthAndFlagsN;//Big Endian
    uint32_t    FibreChannelTime[2];        //Big Endian
    uint32_t    FibreChannelCrc;            //Big Endian
    uint32_t    FibreChannelSof;            //Big Endian
}FIBRE_CHANNEL_ENCAPS_HEADER, * PFIBRE_CHANNEL_ENCAPS_HEADER;

enum FIBRE_CHANNEL_SOF{
    FIBRE_CHANNEL_SOF_F     = 0x28,
    FIBRE_CHANNEL_SOF_I4    = 0x29,
    FIBRE_CHANNEL_SOF_I2    = 0x2D,
    FIBRE_CHANNEL_SOF_I3    = 0x2E,
    FIBRE_CHANNEL_SOF_N4    = 0x31,
    FIBRE_CHANNEL_SOF_N2    = 0x35,
    FIBRE_CHANNEL_SOF_N3    = 0x36,
    FIBRE_CHANNEL_SOF_C4    = 0x39,
}PACKED;//sanity pack

enum FIBRE_CHANNEL_EOF{
    FIBRE_CHANNEL_EOF_N     = 0x41,
    FIBRE_CHANNEL_EOF_T     = 0x42,
    FIBRE_CHANNEL_EOF_RT    = 0x44,
    FIBRE_CHANNEL_EOF_DT    = 0x46,
    FIBRE_CHANNEL_EOF_NI    = 0x49,
    FIBRE_CHANNEL_EOF_DTI   = 0x4E,
    FIBRE_CHANNEL_EOF_RTI   = 0x4F,
    FIBRE_CHANNEL_EOF_A     = 0x50,
}PACKED;//sanity pack

typedef enum {
    FIBRE_CHANNEL_CLASS_NONE    = 0,
    FIBRE_CHANNEL_CLASS2        = FIBRE_CHANNEL_SOF_I2,
    FIBRE_CHANNEL_CLASS3        = FIBRE_CHANNEL_SOF_I3,
    FIBRE_CHANNEL_CLASS4        = FIBRE_CHANNEL_SOF_I4,
    FIBRE_CHANNEL_CLASSF        = FIBRE_CHANNEL_SOF_F,
}FIBRE_CHANNEL_CLASS;

static inline int FibreChannelSofNeedsAcknowledgement(enum FIBRE_CHANNEL_SOF Sof){
    return (int)(~(Sof) & 0x02);
}

static inline enum FIBRE_CHANNEL_SOF FcSofNormal(FIBRE_CHANNEL_CLASS Class){
    return (enum FIBRE_CHANNEL_SOF)(Class + FIBRE_CHANNEL_SOF_N3 - FIBRE_CHANNEL_SOF_I3); 
}

static inline FIBRE_CHANNEL_CLASS FibreChannelSofClass(enum FIBRE_CHANNEL_SOF Sof){
    return (FIBRE_CHANNEL_CLASS)((Sof & 0x07) | FIBRE_CHANNEL_SOF_F);
}

static inline int FibreChannelSofIsInit(enum FIBRE_CHANNEL_SOF Sof){
    return (int)(Sof < 30);
}

#pragma pack(pop)
#endif //_FIBRE_CHANNEL_ENCAPS_H
