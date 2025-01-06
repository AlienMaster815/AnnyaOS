#ifndef _SCS_BSG_FIBRE_CHANNEL_H
#define _SCS_BSG_FIBRE_CHANNEL_H
#pragma pack(push,1)
#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else
#include <LouAPI.h>
#endif


#define FIBRE_CHANNEL_DEFAULT_BSG_TIMEOUT       100
#define FIBRE_CHANNEL_BSG_CLASS_BITS            0xF0000000
#define FIBRE_CHANNEL_BSG_HOST_BITS             0x80000000
#define FIBRE_CHANNEL_BSG_RPORT_BITS            0x40000000

#define FIBRE_CHANEL_HOST_ADD_PORT_MACRO          FIBRE_CHANNEL_BSG_HOST_BITS | 0x00000001
#define FIBRE_CHANEL_HOST_DELETE_PORT_MACRO       FIBRE_CHANNEL_BSG_HOST_BITS | 0x00000002
#define FIBRE_CHANEL_HOST_ELS_NO_LOGIN_MACRO      FIBRE_CHANNEL_BSG_HOST_BITS | 0x00000003
#define FIBRE_CHANEL_HOST_CT_MACRO                FIBRE_CHANNEL_BSG_HOST_BITS | 0x00000004
#define FIBRE_CHANEL_HOST_VENDOR_MACRO            FIBRE_CHANNEL_BSG_HOST_BITS | 0x000000FF

#define FIBRE_CHANNEL_BSG_RPORT_ELS_MACRO         FIBRE_CHANNEL_BSG_RPORT_BITS | 0x00000001
#define FIBRE_CHANNEL_BSG_RPORT_CT_MACRO          FIBRE_CHANNEL_BSG_RPORT_BITS | 0x00000002

typedef struct _FIBRE_CHANNEL_BSG_HOST_ADD_RPORT{
    uint8_t     Reserved;
    uint8_t     PortID[3];
}FIBRE_CHANNEL_BSG_HOST_ADD_RPORT, * PFIBRE_CHANNEL_BSG_HOST_ADD_RPORT;

typedef struct  _FIBRE_CHANNEL_BSG_HOST_DELETE_RPORT{
    uint8_t     Reserved;
    uint8_t     PortID[3];
}FIBRE_CHANNEL_BSG_HOST_DELETE_RPORT, * PFIBRE_CHANNEL_BSG_HOST_DELETE_RPORT;

typedef struct _FIBRE_CHANNEL_HOST_ELS{
    uint8_t     CommandCode;
    uint8_t     PortID[3];
}FIBRE_CHANNEL_HOST_ELS, * PFIBRE_CHANNEL_HOST_ELS;

#define FIBRE_CHANNEL_CTELS_STATUS_OK         0x00000000
#define FIBRE_CHANNEL_CTELS_STATUS_REJECT     0x00000001
#define FIBRE_CHANNEL_CTELS_STATUS_P_RJT      0x00000002
#define FIBRE_CHANNEL_CTELS_STATUS_F_RJT      0x00000003
#define FIBRE_CHANNEL_CTELS_STATUS_P_BSY      0x00000004
#define FIBRE_CHANNEL_CTELS_STATUS_F_BSY      0x00000006

typedef struct _FIBRE_CHANNEL_CTELS_REPLY{
    uint32_t Status;
    struct{
        uint8_t     Action;
        uint8_t     ReasonCode;
        uint8_t     ReasonExplanation;
        uint8_t     VendorUnique;
    }RjtData;
}FIBRE_CHANNEL_CTELS_REPLY, * PFIBRE_CHANNEL_CTELS_REPLY;

typedef struct _FIBRE_CHANNEL_BSG_HOST_CT{
    uint8_t     Reserved;
    uint8_t     PortID[3];
    uint32_t    PreAmbleDWORD0;
    uint32_t    PreAmbleDWORD1;
    uint32_t    PreAmbleDWORD2;
}FIBRE_CHANNEL_BSG_HOST_CT, * PFIBRE_CHANNEL_BSG_HOST_CT;

typedef struct _FIBRE_CHANNEL_BSG_HOST_VENDOR{
    uint64_t VendorId;
    uint32_t VendorCommand[];
}FIBRE_CHANNEL_BSG_HOST_VENDOR, * PFIBRE_CHANNEL_BSG_HOST_VENDOR;

typedef struct _FIBRE_CHANNEL_BSG_VNEDOR_REPLY{
    uint32_t    VendorResponceDWORD0;
    uint32_t    VendorResponce[];
}FIBRE_CHANNEL_BSG_VNEDOR_REPLY, * PFIBRE_CHANNEL_BSG_VNEDOR_REPLY;

typedef struct _FIBRE_CHANNEL_RPORT_ELS{
    uint8_t ElsCode;
}FIBRE_CHANNEL_RPORT_ELS, * PFIBRE_CHANNEL_RPORT_ELS;

typedef struct _FIBRE_CHANNEL_BSG_RPORT_CT{
    uint32_t PreAmbleDWORD0;
    uint32_t PreAmbleDWORD1;
    uint32_t PreAmbleDWORD2;
}FIBRE_CHANNEL_BSG_RPORT_CT, * PFIBRE_CHANNEL_BSG_RPORT_CT;

typedef struct _FIBRE_CHANNEL_BSG_REQUEST{
    uint32_t    MessageCode;
    union {
        FIBRE_CHANNEL_BSG_HOST_ADD_RPORT            hAddRPort;
        FIBRE_CHANNEL_BSG_HOST_DELETE_RPORT         hDeleteRPort;
        FIBRE_CHANNEL_CTELS_REPLY                   hEls;
        FIBRE_CHANNEL_BSG_HOST_CT                   hCtl;
        FIBRE_CHANNEL_BSG_VNEDOR_REPLY              Vendor;
        FIBRE_CHANNEL_RPORT_ELS                     rEls;
        FIBRE_CHANNEL_BSG_RPORT_CT                  rCt;
    }RequestData;
}FIBRE_CHANNEL_BSG_REQUEST, * PFIBRE_CHANNEL_BSG_REQUEST;

typedef struct _FIBRE_CHANNEL_BSG_REPLY{
    uint32_t Result;
    uint32_t ReplyPayloadLength;
    union{
        FIBRE_CHANNEL_BSG_VNEDOR_REPLY      VendorReply;
        FIBRE_CHANNEL_CTELS_REPLY           CtelsReply;
    }ReplyData;
}FIBRE_CHANNEL_BSG_REPLY, * PFIBRE_CHANNEL_BSG_REPLY;

#ifdef __cplusplus
}
#endif
#pragma pack(pop)
#endif