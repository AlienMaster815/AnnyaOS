//SPDX-Licence-IdentifierL AGPL 3.0/Proprietary
//Copyright (C) 2024-2025 Tyler Grenier
//Time Started  : 12/31/2024 10:50 AM
//Time Finished : 12/31/2024 11:36 AM
//Last Modified : 12/31/2024 11:36 AM

#ifndef _MPI_LAN_H
#define _MPI_LAN_H
#pragma pack(push,1)

#include "MpiTypes.h"
#include "Mpi.h"


#define LAN_REPLY_PACKET_LENGTH_BITS    0x0000FFFF
#define LAN_REPLY_PACKET_LENGTH_SHIFT   0
#define LAN_REPLY_BUCKET_CONTEXT_BITS   0x07FF0000
#define LAN_REPLY_BUCKET_CONTEXT_SHIFT  16
#define LAN_REPLY_BUFFER_CONTEXT_BITS   0x07FFFFFF
#define LAN_REPLY_BUFFER_CONTEXT_SHIFT  0
#define LAN_REPLY_FORM_BITS             0x18000000
#define LAN_REPLY_FORM_RECIEVE_SINGLE   0
#define LAN_REPLY_FORM_RECIEVE_MULTIPLE 1
#define LAN_REPLY_FORM_SEND_SINGLE      2
#define LAN_REPLY_FORM_MESSAGE_CONTEXT  3
#define LAN_REPLY_FORM_SHIFT            27

#define GET_LAN_PACKET_LENGTH_MACRO(Base) (((Base) & LAN_REPLY_PACKET_LENGTH_BITS) >> LAN_REPLY_PACKET_LENGTH_SHIFT)
#define SET_LAN_PACKET_LENGTH_MACRO(Base, Length) ((Base) = (Base) & ~(LAN_REPLY_PACKET_LENGTH_BITS)) |  (((Length) << LAN_REPLY_PACKET_LENGTH_SHIFT) & LAN_REPLY_PACKET_LENGTH_BITS)

#define GET_LAN_BUCKET_CONTEXT_MACRO(Base) (((Base) & LAN_REPLY_BUCKET_CONTEXT_BITS) >> LAN_REPLY_BUCKET_CONTEXT_SHIFT)
#define SET_LAN_BUCKET_CONTEXT_MACRO(Base, Context) (((Base) = (Base) & ~(LAN_REPLY_BUCKET_CONTEXT_BITS)) | (((Context) << LAN_REPLY_BUCKET_CONTEXT_SHIFT) & LAN_REPLY_BUCKET_CONTEXT_BITS))

#define GET_LAN_BUFFER_CONTEXT_MACRO(Base) (((Base) & LAN_REPLY_BUFFER_CONTEXT_BITS >> LAN_REPLY_BUFFER_CONTEXT_SHIFT))
#define SET_LAN_BUFFER_CONTEXT_MACRO(Base, Context) ((Base) = ((Base) & ~(LAN_REPLY_BUFFER_CONTEXT_BITS)) | (((Context) << LAN_REPLY_BUCKET_CONTEXT_SHIFT) & LAN_REPLY_BUFFER_CONTEXT_BITS))

#define GET_LAN_FORM_MACRO(Base)  (((Base) & LAN_REPLY_BUFFER_CONTEXT_BITS) >> LAN_REPLY_FORM_SHIFT)
#define SET_LAN_FORM_MACRO(Base, Form) ((Base) = (Base) & ~(LAN_REPLY_FORM_BITS) | (((Form) << LAN_REPLY_FORM_SHIFT) & LAN_REPLY_FORM_BITS))

#define MPI_LAN_DEVICE_STATE_RESET          0
#define MPI_LAN_DEVICE_STATE_OPERATIONAL    1

#define MPI_LAN_TX_MODE_ENABLE_LOOPBACK_SUPPRESSION 1

typedef struct _MESSAGE_LAN_SEND_REQUEST{
    MPIU16                              Rsv1;
    MPIU8                               ChainOffset;
    MPIU8                               MpiFunction;
    MPIU16                              Rsv2;
    MPIU8                               PortNumber;
    MPIU8                               MessageFlags;
    MPIU32                              MessageContext;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   ScatterGatherList[];
}MESSAGE_LAN_SEND_REQUEST, * PMESSAGE_LAN_SEND_REQUEST;

typedef struct _MESSAGE_LAN_SEND_REPLY{
    MPIU16  Rsv1;
    MPIU8   MessageLength;
    MPIU8   MpiFunction;
    MPIU8   Rsv2;
    MPIU8   NumberOfContexts;
    MPIU8   PortNumber;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU16  Rsv3;
    MPIU16  IocStatus;
    MPIU32  IocLogInfo;
    MPIU32  BufferContext;
}MESSAGE_LAN_SEND_REPLY, * PMESSAGE_LAN_SEND_REPLY;

typedef struct _MESSAGE_LAN_RECIEVE_POST_REQUEST{
    MPIU16                              Rsv1;
    MPIU8                               ChainOffset;
    MPIU8                               MpiFunction;
    MPIU16                              Rsv2;
    MPIU8                               PortNumber;
    MPIU8                               MessageFlags;
    MPIU32                              MessageContext;
    MPIU32                              BucketCount;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   ScatterGatheList[1];
}MESSAGE_LAN_RECIEVE_POST_REQUEST, * PMESSAGE_LAN_RECIEVE_POST_REQUEST;

typedef struct _MESSAGE_LAN_RECIEVE_POST_REPLY{
    MPIU16      Rsv1;
    MPIU8       MessageLength;
    MPIU8       MpiFunction;
    MPIU8       Rsv2;
    MPIU8       NumberOfContexts;
    MPIU8       PortNumber;
    MPIU8       MessageFlags;
    MPIU32      MessageContext;
    MPIU16      Rsv3;
    MPIU16      IocStatus;
    MPIU32      IocLogInfo;
    MPIU32      BucketsRemaining;
    MPIU32      PacketOffset;
    MPIU32      PacketLength;
    MPIU32      BucketVontext[1];
}MESSAGE_LAN_RECIEVE_POST_REPLY, * PMESSAGE_LAN_RECIEVE_POST_REPLY;

typedef struct _MESSAGE_LAN_RESET_REQUEST{
    MPIU16  Rsv1;
    MPIU8   ChainOffset;
    MPIU8   MpiFunction;
    MPIU16  Rsv2;   
    MPIU8   PortNumber;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
}MESSAGE_LAN_RESET_REQUEST, * PMESSAGE_LAN_RESET_REQUEST;

typedef struct _MESSAGE_LAN_RESET_REPLY{
    MPIU16      Rsv1;
    MPIU8       MessageLength;
    MPIU8       MpiFunction;
    MPIU16      Rsv2;
    MPIU8       PortNumber;
    MPIU8       MessageFlags;
    MPIU32      MessageContext;
    MPIU16      Rsv3;
    MPIU16      IocStatus;
    MPIU32      IocLogInfo;
}MESSAGE_LAN_RESET_REPLY, * PMESSAGE_LAN_RESET_REPLY;


#pragma pack(pop)
#endif //_MPI_LAN_H