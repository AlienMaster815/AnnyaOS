//SPDX-Licence-IdentifierL AGPL 3.0/Proprietary
//Copyright (C) 2024-2025 Tyler Grenier
//Time Started  : 1/1/2024  9:04 PM
//Time Finished : 1/1/2024 11:24 PM
//Last Modified : 1/1/2024 11:24 PM

#ifndef _MPI_FUSION_CONTROL_H
#define _MPI_FUSION_CONTROL_H
#pragma pack(push,1)

#include "MpiTypes.h"
#include "Mpi.h"

#define LINK_SERVICE_BUFFER_POST_FLAGS_PORT_BITS 0x01

#define MPI_LINK_SERVICE_BUFFER_PSOT_REPLY_FLAGS_NO_RSP_NEEDED  0x80

#define MPI_FIBRE_CHANNEL_DID_BITS                              0x00FFFFFF
#define MPI_FIBRE_CHANNEL_DID_SHIFT                             0
#define MPI_FIBRE_CHANNEL_RCTL_BITS                             0xFF000000
#define MPI_FIBRE_CHANNEL_RCTL_SHIFT                            24
#define MPI_FIBRE_CHANNEL_SID_BITS                              0x00FFFFFF
#define MPI_FIBRE_CHANNEL_SID_SHIFT                             24
#define MPI_FIBRE_CHANNEL_CSCTL_BITS                            0x00FFFFFF
#define MPI_FIBRE_CHANNEL_CSCTL_SHIFT                           0
#define MPI_FIBRE_CHANNEL_FCTL_BITS                             0xFF000000
#define MPI_FIBRE_CHANNEL_FCTL_SHIFT                            24

//Obsolete But Still Important
#define FCP_TARGET_DID_BITS                                     0x00FFFFFF
#define FCP_TARGET_DID_SHIFT                                    0
#define FCP_TARGET_RCTL_BITS                                    0xFF000000
#define FCP_TARGET_RCTL_SHIFT                                   24
#define FCP_TARGET_SID_BITS                                     0x00FFFFFF
#define FCP_TARGET_SID_SHIFT                                    0
#define FCP_TARGET_CSCTL_BITS                                   0xFF000000
#define FCP_TARGET_CSCTL_SHIFT                                  24
#define FCP_TARGET_FCTL_BITS                                    0x00FFFFFF
#define FCP_TARGET_FCTL_SHIFT                                   0
#define FCP_TARGET_TYPE_BITS                                    0xFF000000
#define FCP_TARGET_TYPE_SHIFT                                   24

#define LINK_SERVICE_RSP_FLAGS_IMEDIATE                         0x80
#define LINK_SERVICE_RSP_FLAGS_PORT_BITS                        0x01

#define FIBRE_CHANNEL_ABORT_FLAG_PORT_BITS                      0x01

#define FIBRE_CHANNEL_ABORT_TYPE_ALL_FIBRE_CHANNEL_BUFFERS      0x00
#define FIBRE_CHANNEL_ABORT_TYPE_EXACT_FIBRE_CHANNEL_BUFFER     0x01
#define FIBRE_CHANNEL_ABORT_TYPE_CT_SEND_REQUEST                0x02
#define FIBRE_CHANNEL_ABORT_TYPE_EXLINK_SEND_REQUEST            0x03

#define FIBRE_CHANNEL_CT_SEND_DID_PORTS                         0x00FFFFFF
#define FIBRE_CHANNEL_CT_SEND_DID_SHIFT                         0
#define FIBRE_CHANNEL_CT_SEND_MESSAGE_FLAGS_BITS                0xFF000000
#define FIBRE_CHANNEL_CT_SEND_MESSAGE_FLAGS_SHIFT               24

#define FIBRE_CHANNEL_PRIMATIVE_FLAGS_PORT_MASK                 0x01
#define FIBRE_CHANNEL_PRIMATIVE_FLAGS_ML_RESET_LINK             0x02
#define FIBRE_CHANNEL_PRIMATIVE_FLAGS_RESET_LINK                0x04
#define FIBRE_CHANNEL_PRIMATIVE_FLAGS_STOP_SEND                 0x08
#define FIBRE_CHANNEL_PRIMATIVE_FLAGS_SEND_ONCE                 0x10
#define FIBRE_CHANNEL_PRIMATIVE_FLAGS_SEND_AROUND               0x20
#define FIBRE_CHANNEL_PRIMATIVE_FLAGS_UNTIL_FULL                0x40
#define FIBRE_CHANNEL_PRIMATIVE_FLAGS_FOREVER                   0x80



typedef struct _MESSAGE_LINK_SERVICE_BUFFER_POST_REQUEST{
    MPIU8                                       BufferFlags;
    MPIU8                                       BufferCount;
    MPIU8                                       ChainOffset;
    MPIU8                                       MpiFunction;
    MPIU16                                      Rsv1;
    MPIU8                                       Rsv2;
    MPIU8                                       MessageFlags;
    MPIU32                                      MessageContext;
    SCATTER_GATHER_TCE_SIMPLE_UNION             ScatterGatherList;
}MESSAGE_LINK_SERVICE_BUFFER_POST_REQUEST, * PMESSAGE_LINK_SERVICE_BUFFER_POST_REQUEST;

typedef struct _WWN_FORMAT{
    MPIU32  PortNameHighDWORD;
    MPIU32  PortNameLowDWROD;
    MPIU32  NodeNameHighDWORD;
    MPIU32  NodeNameLowDWORD;
}WWN_FORMAT, * PWWN_FORMAT;

typedef struct _MESSAGE_LINK_SERVICE_BUFFER_POST_REPLY{
    MPIU8       Flags;
    MPIU8       Rsv1;
    MPIU8       MessageLength;
    MPIU8       MpiFunction;
    MPIU16      Rsv2;
    MPIU8       PortNumber;
    MPIU8       MessageFlags;
    MPIU32      MessageContext;
    MPIU16      Rsv3;
    MPIU16      IocStatus;
    MPIU32      IocLogInfo;
    MPIU32      TransferLength;
    MPIU32      TransactionContext;
    MPIU32      RctlDid;
    MPIU32      CsctlSid;
    MPIU32      TypeFctl;
    MPIU16      SequenceCount;
    MPIU8       DFctl;
    MPIU8       SequenceID;
    MPIU16      OxID;
    MPIU32      Parameter;
    WWN_FORMAT  WwnFormat;
}MESSAGE_LINK_SERVICE_BUFFER_POST_REPLY, * PMESSAGE_LINK_SERVICE_BUFFER_POST_REPLY;

typedef struct _MESSAGE_LINK_SERVICE_RSP_REQUEST{
    MPIU8                               RspFlags;
    MPIU8                               RspLength;
    MPIU8                               ChainOffset;
    MPIU8                               MpiFunction;
    MPIU16                              Rsv1;
    MPIU8                               Rsv2;
    MPIU8                               MessageFlags;
    MPIU32                              MessageContext;
    MPIU32                              RctlDid;
    MPIU32                              CsctlSid;
    MPIU32                              TypeFctl;
    MPIU16                              SequnceCount;
    MPIU8                               Dfctl;
    MPIU8                               SeqquenceID;
    MPIU16                              RxID;
    MPIU16                              OxID;
    MPIU32                              Parameter;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   ScatterGatherList;
}MESSAGE_LINK_SERVICE_RSP_REQUEST, * PMESSAGE_LINK_SERVICE_RSP_REQUEST;

typedef struct _MESSAGE_LINK_SERVICE_RSP_REPLY{
    MPIU16      Rsv1;
    MPIU8       MessageLength;
    MPIU8       MpiFunction;
    MPIU16      Rsv2;
    MPIU8       OldInitiatorIndex;
    MPIU8       MessageFlags;
    MPIU32      MessageContext;
    MPIU16      Rsv3;
    MPIU16      IocStatus;
    MPIU32      IocLogInfo;
    MPIU32      InitiatorIndex;      
}MESSAGE_LINK_SERVICE_RSP_REPLY, * PMESSAGE_LINK_SERVICE_RSP_REPLY;

typedef struct _MESSAGE_EXLINK_SERVICE_SEND_REQUEST{
    MPIU16      Rsv1;
    MPIU8       MessageLength;
    MPIU8       MpiFunction;
    MPIU16      Rsv2;
    MPIU8       Rsv3;
    MPIU8       MessageFlags;
    MPIU32      MessageContext;
    MPIU16      Rsv4;
    MPIU16      IocStatus;
    MPIU32      IocLogInfo;
}MESSAGE_EXLINK_SERVICE_SEND_REQUEST, * PMESSAGE_EXLINK_SERVICE_SEND_REQUEST;

typedef struct _MESSAGE_FIBRE_CHANNEL_ABORT_REQUEST{
    MPIU8   AbortFlags;
    MPIU8   AbortType;
    MPIU8   ChainOffset;
    MPIU8   MpiFunction;
    MPIU16  Rsv1;
    MPIU8   Rsv2;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU32  TransactionContextToAbort;
}MESSAGE_FIBRE_CHANNEL_ABORT_REQUEST, * PMESSAGE_FIBRE_CHANNEL_ABORT_REQUEST;

typedef struct _MESSAGE_FIBRE_CHANNEL_ABORT_REPLY{
    MPIU16  Rsv1;
    MPIU8   MessageLength;
    MPIU8   MpiFunction;
    MPIU16  Rsv2;
    MPIU8   Rsv3;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU16  Rsv4;
    MPIU16  IocStatus;
    MPIU32  IocLogInfo;
}MESSAGE_FIBRE_CHANNEL_ABORT_REPLY, * PMESSAGE_FIBRE_CHANNEL_ABORT_REPLY;

typedef struct _MESSAGE_FIBRE_CHANNEL_COMMON_TRANSPORT_SEND_REQUEST{
    MPIU8                               SendFlags;
    MPIU8                               AliasIndes;
    MPIU8                               ChainOffset;
    MPIU8                               MpiFunction;
    MPIU32                              MessageFlagsAndDid;
    MPIU32                              MessageContext;
    MPIU16                              CtCommandCode;
    MPIU8                               FsType;
    MPIU8                               Rsv1;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   ScatterGatherList;
}MESSAGE_FIBRE_CHANNEL_COMMON_TRANSPORT_SEND_REQUEST, * PMESSAGE_FIBRE_CHANNEL_COMMON_TRANSPORT_SEND_REQUEST;

typedef struct _MESSAGE_FIBRE_CHANNEL_COMMON_TRANSPORT_SEND_REPLY{
    MPIU8   Rsv1;
    MPIU8   AliasIndes;
    MPIU8   MessageLength;
    MPIU8   MpiFunction;
    MPIU16  Rsv2;
    MPIU8   Rsv3;
    MPIU8   MessageFlags;
    MPIU8   MessageContext;
    MPIU8   Rsv4;
    MPIU16  IocStatus;
    MPIU32  IocLogInfo;
    MPIU32  RepsonceLength;                       
}MESSAGE_FIBRE_CHANNEL_COMMON_TRANSPORT_SEND_REPLY, * PMESSAGE_FIBRE_CHANNEL_COMMON_TRANSPORT_SEND_REPLY;

typedef struct _MESSAGE_FIBRE_CHANNEL_PRIMATIVE_SEND_REQUEST{
    MPIU8   SendFlags;
    MPIU8   Rsv1;
    MPIU8   ChainOffset;
    MPIU8   MpiFunction;
    MPIU16  Rsv2;
    MPIU8   Rsv3;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU8   FcPrimative[4];
}MESSAGE_FIBRE_CHANNEL_PRIMATIVE_SEND_REQUEST, * PMESSAGE_FIBRE_CHANNEL_PRIMATIVE_SEND_REQUEST;

typedef struct _MESSAGE_FIBRE_CHANNEL_PRIMATIVE_SEND_REPLY{
    MPIU8   SendFlags;
    MPIU8   Rsv1;
    MPIU8   MessageLength;
    MPIU8   MpiFunction;
    MPIU16  Rsv2;
    MPIU8   Rsv3;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU16  Rsv4;
    MPIU16  IocStatus;
    MPIU32  IocLogInfo;
}MESSAGE_FIBRE_CHANNEL_PRIMATIVE_SEND_REPLY, * PMESSAGE_FIBRE_CHANNEL_PRIMATIVE_SEND_REPLY;

#pragma pack(pop)
#endif //_MPI_FUSION_CONTROL_H