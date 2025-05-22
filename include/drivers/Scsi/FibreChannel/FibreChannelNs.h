#ifndef _FIBRE_CHANNEL_NS_H
#define _FIBRE_CHANNEL_NS_H

#pragma pack(push,1)

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else 
#include <LouAPI.h>
#endif

#define FIBRE_CHANNEL_NS_SUB_TYPE   2

#define FIBRE_CHANNEL_NS_GET_ALL_NEXT                   0x0100
#define FIBRE_CHANNEL_NS_GET_IDENTIFIER_A               0x0101
#define FIBRE_CHANNEL_NS_GET_PORT_NAME_ID               0x0112
#define FIBRE_CHANNEL_NS_GET_NODE_NAME_ID               0x0113
#define FIBRE_CHANNEL_NS_GET_SYMBOLIC_PORT_NAME         0x0118
#define FIBRE_CHANNEL_NS_GET_ID_PORT_NAME               0x0121
#define FIBRE_CHANNEL_NS_GET_ID_NODE_NAME               0x0131
#define FIBRE_CHANNEL_NS_GET_ID_FC4                     0x0171
#define FIBRE_CHANNEL_NS_GET_PORT_NAMES_FC4             0x0172
#define FIBRE_CHANNEL_NS_GET_PORT_ID_BY_TYPE            0x01A1
#define FIBRE_CHANNEL_NS_REGISTER_PORT_NAME             0x0212
#define FIBRE_CHANNEL_NS_REGISTER_NODE_NAME             0x0213
#define FIBRE_CHANNEL_NS_REGISTER_FC4_TYPE              0x0217
#define FIBRE_CHANNEL_NS_REGISTER_SYMBOLIC_PORT_NAME    0x0218
#define FIBRE_CHANNEL_NS_REGISTER_FC4_ID                0x021F
#define FIBRE_CHANNEL_NS_REGISTER_SYMBOLIC_NODE_NAME    0x0239

#define FIBRE_CHANNEL_NS_UNIDENTIFIED_PORT              0x00
#define FIBRE_CHANNEL_NS_N_PORT                         0x01
#define FIBRE_CHANNEL_NS_NL_PORT                        0x02
#define FIBRE_CHANNEL_NS_FNL_PORT                       0x03
#define FIBRE_CHANNEL_NS_NX_PORT                        0x7F
#define FIBRE_CHANNEL_NS_F_PORT                         0x81
#define FIBRE_CHANNEL_NS_FL_PORT                        0x82
#define FIBRE_CHANNEL_NS_E_PORT                         0x84
#define FIBRE_CHANNEL_NS_B_PORT                         0x85

typedef struct _FIBRE_CHANNEL_NS_PORT_TYPE_OBJECT{
    uint8_t Type;
}FIBRE_CHANNEL_NS_PORT_TYPE_OBJECT, * PFIBRE_CHANNEL_NS_PORT_TYPE_OBJECT;

typedef struct _FIBRE_CHANNEL_NS_FID{
    uint8_t     Flags;
    uint8_t     FID[3];
}FIBRE_CHANNEL_NS_FID, * PFIBRE_CHANNEL_NS_FID;

#define FIBRE_CHANNEL_NS_FID_LAST                       0x80

#define FIBRE_CHANNEL_NS_TYPES                          256
#define FIBRE_CHANNEL_NS_BITS_PER_WORD                  32

//Bif Endian Struct
typedef struct _FIBRE_CHANNEL_NS_FTS{
    uint32_t    TypeMap[FIBRE_CHANNEL_NS_TYPES / FIBRE_CHANNEL_NS_BITS_PER_WORD];
}FIBRE_CHANNEL_NS_FTS, * PFIBRE_CHANNEL_NS_FTS;

//big endian struct
typedef struct _FIBRE_CHANNEL_NS_FF{
    uint32_t Features[(FIBRE_CHANNEL_NS_TYPES * 4) / FIBRE_CHANNEL_NS_BITS_PER_WORD];
}FIBRE_CHANNEL_NS_FF, * PFIBRE_CHANNEL_NS_FF;

typedef struct _FIBRE_CHANNEL_NS_GID_PT_REQUEST{
    uint8_t     PT_Type;
    uint8_t     DomainIDScope;
    uint8_t     AreaIDScope;
    uint8_t     Reserved;
}FIBRE_CHANNEL_NS_GID_PT_REQUEST, * PFIBRE_CHANNEL_NS_GID_PT_REQUEST;

typedef struct _FIBRE_CHANNEL_NS_GIF_FT_REQUEST{
    uint8_t     Reserved;
    uint8_t     DomainIDScope;
    uint8_t     AreaIDScope;
    uint8_t     Fc4Type;
}FIBRE_CHANNEL_NS_GIF_FT_REQUEST, * PFIBRE_CHANNEL_NS_GIF_FT_REQUEST;

//Big Endian Struct
typedef struct _FIBRE_CHANNEL_NS_GPN_FT_RESPONCE{
    uint8_t     Flags;
    uint8_t     FID[3];
    uint32_t    Reserved;
    uint64_t    Wwpn;
}FIBRE_CHANNEL_NS_GPN_FT_RESPONCE, * PFIBRE_CHANNEL_NS_GPN_FT_RESPONCE;

//big endian struct
typedef struct _FIBRE_CHANNEL_NS_GID_PN_REQUEST{
    uint64_t Wwpn;
}FIBRE_CHANNEL_NS_GID_PN_REQUEST, * PFIBRE_CHANNEL_NS_GID_PN_REQUEST;

typedef struct _FIBRE_CHANNEL_NS_GID_PN_RESPONCE{
    uint8_t     Reserved;
    uint8_t     Fid[3];
}FIBRE_CHANNEL_NS_GID_PN_RESPONCE, * PFIBRE_CHANNEL_NS_GID_PN_RESPONCE;

typedef struct _FIBRE_CHANNEL_GSPN_ID_RESPONCE{
    uint8_t     NameLength;
    char        Name;
}FIBRE_CHANNEL_GSPN_ID_RESPONCE, * PFIBRE_CHANNEL_GSPN_ID_RESPONCE;

typedef struct _FIBRE_CHANNEL_NS_RFT_ID_REQUEST{
    FIBRE_CHANNEL_NS_FID    Fid;
    FIBRE_CHANNEL_NS_FTS    Fts;
}FIBRE_CHANNEL_NS_RFT_ID_REQUEST, * PFIBRE_CHANNEL_NS_RFT_ID_REQUEST;

typedef struct _FIBRE_CHANNEL_NS_RN_ID_REQUEST{
    FIBRE_CHANNEL_NS_FID    Fid;
    uint64_t                wwn;
}FIBRE_CHANNEL_NS_RN_ID_REQUEST,  * PFIBRE_CHANNEL_NS_RN_ID_REQUEST;

typedef struct _FIBRE_CHANNEL_NS_RSNN_REQUEST{
    uint64_t    Wwn;
    uint8_t     NameLength;
    char        Name[];
}FIBRE_CHANNEL_NS_RSNN_REQUEST, * PFIBRE_CHANNEL_NS_RSNN_REQUEST;

typedef struct _FIBRE_CHANNEL_NS_RFF_ID_REQUEST{
    FIBRE_CHANNEL_NS_FID    Fid;
    uint8_t                 Reserved[2];
    uint8_t                 Features;
    uint8_t                 Types;
}FIBRE_CHANNEL_NS_RFF_ID_REQUEST, * PFIBRE_CHANNEL_NS_RFF_ID_REQUEST;

#ifdef __cplusplus
}
#endif
#pragma pack(pop)
#endif //_FIBRE_CHANNEL_NS_H