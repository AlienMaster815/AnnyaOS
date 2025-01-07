#ifndef _SCSI_BSG_USF_H
#define _SCSI_BSG_USF_H

#pragma pack(push, 1)

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif

#define UFS_CCOMMADN_DATA_BUFFER_SIZE    16
#define UIC_COMMAND_SIZE                 sizeof(uint32_t) * 4

#define UFS_TRANSACTION_UIC_COMMAND     0x1F
#define UFS_TRANSACTION_ARMB_COMMADN    0x20

#define UFS_RPMB_OPERATION_TYPE_WRITE_KEY           0x01
#define UFS_RPMB_OPERATION_TYPE_READ_CNT            0x02
#define UFS_RPMB_OPERATION_TYPE_WRITE               0x03
#define UFS_RPMB_OPERATION_TYPE_READ                0x04
#define UFS_RPMB_OPERATION_TYPE_READ_RESPONCE       0x05
#define UFS_RPMB_OPERATION_TYPE_SEC_CONF_WRITE      0x06
#define UFS_RPMB_OPERATION_TYPE_SEC_CONF_READ       0x07
#define UFS_RPMB_OPERATION_TYPE_PURGE_ENABELE       0x08
#define UFS_RPMB_OPERATION_TYPE_STATUS_READ         0x09


typedef struct _UTP_UPIU_HEADER{
    union{
        struct {
            uint32_t    DWORD0;//big endian
            uint32_t    DWORD1;//big endian
            uint32_t    DWORD2;//Big Endian
        };
        struct{
            uint8_t TransactionCode;
            uint8_t Flags;
            uint8_t Lun;
            uint8_t TaskTag;
        #if defined(__BIG_ENDIAN)
            uint8_t Iif : 4;
            uint8_t CommandSetType : 4;
        #elif defined(_LITTLE_ENDIAN)
            uint8_t CommandSetType : 4;
            uint8_t Iif : 4;
        #else
        #endif
        union{
            uint8_t TmFunction;
            uint8_t QueryFunction;
        }__attribute__((packed));
            uint8_t Responce;
            uint8_t Status;
            uint8_t EhsLength;
            uint8_t DeviceInfol;
            uint16_t DataSegment;   //Big Endian
        };
    };
}UTP_UPIU_HEADER, * PUTP_UPIU_HEADER;

//Big Endian structure
typedef struct _UTP_UPIU_QUERY{
    uint8_t     Opcode;
    uint8_t     Idn;
    uint8_t     Index;
    uint8_t     Selector;
    uint16_t    ReservedOsf;    
    uint16_t    Length;
    uint32_t    Value;
    uint32_t    Reserved[2];
}UTP_UPIU_QUERY, * PUTP_UPIU_QUERY;

//big endian structure
typedef struct _UTP_UPIU_QUERY_V4_0{
    uint8_t     Opcode;
    uint8_t     Idn;
    uint8_t     Index;
    uint8_t     Selector;
    uint8_t     Osf3;
    uint8_t     Osf4;
    uint16_t    Osf5;
    uint32_t    Osf6;
    uint32_t    Osf7;
    uint32_t    Reserved;
}UTP_UPIU_QUERY_V4_0, * PUTP_UPIU_QUERY_V4_0;

//big endian
typedef struct _UTP_UPIU_COMMAND{
    uint32_t    ExpDataTransferLength;
    uint8_t     Cdb[UFS_CCOMMADN_DATA_BUFFER_SIZE];
}UTP_UPIU_COMMAND, * PUTP_UPIU_COMMAND;

typedef struct _UTP_UPIU_REQUEST{
    UTP_UPIU_HEADER     Header;
    union{
        UTP_UPIU_COMMAND    Sc;
        UTP_UPIU_QUERY      Qr;
        UTP_UPIU_QUERY      Uc;
    };
}UTP_UPIU_REQUEST, * PUTP_UPIU_REQUEST;

//Big Endian Structure
typedef struct _UFS_ARPMB_META{
    uint16_t    RequestResponceType;
    uint8_t     Nonce[16];
    uint32_t    WriteCounter;
    uint16_t    LunAddress;
    uint16_t    BlockCount;
    uint16_t    Result;
}UFS_ARPMB_META, * PUFS_ARPMB_META;

typedef struct _UFS_EHS{
    uint8_t             Length;
    uint8_t             EhsType;
    uint16_t            EhsSubType;
    UFS_ARPMB_META      MetaData;
    uint8_t             MacKey[32];
}UFS_EHS, * PUFS_EHS;

typedef struct _UFS_BSG_REQUEST{
    uint32_t            MessageCode;
    UTP_UPIU_REQUEST    UpiuRequest;
}UFS_BSG_REQUEST, * PUFS_BSG_REQUEST;

typedef struct _UFS_BSG_REPLY{
    int         Result;
    uint32_t    ReplyPayloadLength;
}UFS_BSG_REPLY, * PUFS_BSG_REPLY;

typedef struct _UFS_RPMB_REQUEST{
    UFS_BSG_REQUEST     BsgRequest;
    UFS_EHS             EhsRequest;
}UFS_RPMB_REQUEST, * PUFS_RPMB_REQUEST;

typedef struct _UFS_RPMB_REPLY{
    UFS_BSG_REPLY       BsgReply;
    UFS_EHS             EhsResponce;
}UFS_RPMB_REPLY, * PUFS_RPMB_REPLY;

#ifdef __cplusplus
}
#endif
#pragma pack(pop)
#endif //_SCSI_BSG_USF_H