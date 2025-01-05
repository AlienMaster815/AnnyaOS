//SPDX-Licence-IdentifierL AGPL 3.0/Proprietary
//Copyright (C) 2024-2025 Tyler Grenier
//Time Started  : 12/30/2024  3:05 AM
//Time Finished : 12/30/2024  8:07 PM
//Last Modified : 12/30/2024  8:07 PM

#ifndef _MPI_TOOLS_H
#define _MPI_TOOLS_H

#include "MpiTypes.h"
#include "Mpi.h"

#pragma pack(push,1)

#define MPI_TOOLBOX_CLEAN               0
#define MPI_TOOLBOX_MEMMOV              1
#define MPI_DIAGNOSTIC_DATA_UPLOAD      2
#define MPI_ISTWI_READ_WRITE            3
#define MPI_FIBRE_CLABE_MANAGEMENT      4
#define MPI_TOOLBOX_BEACON              5

//Toolbox Clean Requests
#define MPI_TOOLBOX_CLEAN_REQUEST_NVSRAM                            0x00000001
#define MPI_TOOLBOX_CLEAN_REQUEST_SEEPROM                           0x00000002
#define MPI_TOOLBOX_CLEAN_REQUEST_FLASH                             0x00000004
#define MPI_TOOLBOX_CLEAN_REQUEST_BOOTLOADER                        0x04000000
#define MPI_TOOLBOX_CLEAN_REQUEST_FIRMWARE_BACKUP                   0x08000000
#define MPI_TOOLBOX_CLEAN_REQUEST_FIRMWARE_CURRENT                  0x10000000
#define MPI_TOOLBOX_CLEAN_REQUEST_OTHER_PERSIST_PAGES               0x20000000
#define MPI_TOOLBOX_CLEAN_REQUEST_PERSIST_MANUFACTURE_PAGES         0x40000000
#define MPI_TOOLBOX_CLEAN_REQUEST_BOOT_SERVICES                     0x80000000 

//diagnostic Formats
#define MPI_TOOLBOX_DIAGNOSTIC_FORMAT_SCSI_PRINTF_TYPE1             0x01
#define MPI_TOOLBOX_DIAGNOSTIC_FORMAT_SCSI_TYPE2                    0x02
#define MPI_TOOLBOX_DIAGNOSTIC_FORMAT_SCSI_TPYE3                    0x03
#define MPI_TOOLBOX_DIAGNOSTIC_FORMAT_FIBRE_CHANNEL_TRACE_TYPE1       0x04

#define MPI_TOOLBOX_ISTWI_FLAGS_WRITE             0x00
#define MPI_TOOLBOX_ISTWI_FLAGS_READ              0x01

#define MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_ACTION_DISC_ALL                   0x00
#define MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_ACTION_DISC_PID                   0x01
#define MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_ACTION_DISC_BUS_TID               0x02
#define MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_ACTION_SET_MASK_FRAME_SIZE        0x03

#define MPI_TOOLBOX_FLAGS_BEACON_OFF    0
#define MPI_TOOLBOX_FLAGS_BEACON_ON     1

#define MPI_DIAGNOSTIC_BUFFER_TYPE_TRACE        0
#define MPI_DIAGNOSTIC_BUFFER_TYPE_SNAPSHOT     1
#define MPI_DIAGNOSTIC_BUFFER_TYPE_EXTENDED     2
#define MPI_DIAGNOSTIC_BUFFER_TYPE_COUNT        3

#define MPI_DIAGNOSTIC_EXTENDED_QTAG            1

//Toolbox Reply Structure
typedef struct _TOOLBOX_MESSAGE_REPLY{
    MPIU8       ToolID;
    MPIU8       Rsv1;
    MPIU8       MessageLength;
    MPIU8       MpiFunction;
    MPIU16      Rsv2;
    MPIU8       Rsv3;
    MPIU8       MessageFlags;
    MPIU32      MessageContext;
    MPIU16      Rsv4;
    MPIU16      IocStatus;
    MPIU32      IocLogInfo;
}TOOLBOX_MESSAGE_REPLY, * PTOOLBOX_MESSAGE_REPLY;

//Toolbox Clean Tool Request
typedef struct _TOOLBOX_MESSAGE_CLEAN_REQUEST{
    MPIU8   ToolID;
    MPIU8   Rsv1;
    MPIU8   ChainOffset;
    MPIU8   MpiFunction;
    MPIU16  Rsv2;
    MPIU8   Rsv3;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU32  Flags;
}TOOLBOX_MESSAGE_CLEAN_REQUEST, * PTOOLBOX_MESSAGE_CLEAN_REQUEST;

//Toolbox Memmov Request
typedef struct _TOOLBOX_MESSAGE_MEMMOV_REQUEST{
    MPIU8                               ToolID;
    MPIU8                               Rsv1;
    MPIU8                               ChainOffset;
    MPIU8                               Function;
    MPIU16                              Rsv2;
    MPIU8                               Rsv3;
    MPIU8                               MessageFlags;
    MPIU32                              MessageContext;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   ScatterGatherList;
}TOOLBOX_MESSAGE_MEMMOV_REQUEST, * PTOOLBOX_MESSAGE_MEMMOV_REQUEST;

//Toolbox Diagnostic Data Upload Request
typedef struct _TOOLBOX_MESSAGE_DIAGNOSTIC_DATA_UPLOAD_REQUEST{
    MPIU8                               ToolID;
    MPIU8                               Rsv1;  
    MPIU8                               ChainOffset;
    MPIU8                               Function;
    MPIU16                              Rsv2;
    MPIU8                               Rsv3;
    MPIU8                               MessageFlags;
    MPIU32                              MessageContext;
    MPIU32                              Flags;
    MPIU32                              Rsv4;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   ScatterGatherList;
}TOOLBOX_MESSAGE_DIAGNOSTIC_DATA_UPLOAD_REQUEST, * PTOOLBOX_MESSAGE_DIAGNOSTIC_DATA_UPLOAD_REQUEST;

typedef struct _DIAGNOSTIC_DATA_UPLOAD_HEADER{
    MPIU32      DiagnosticDataLength;
    MPIU8       FormatCode;
    MPIU8       Rsv1;
    MPIU16      Rsv2;
}DIAGNOSTIC_DATA_UPLOAD_HEADER, * PDIAGNOSTIC_DATA_UPLOAD_HEADER;

//Istwi Read Write
typedef struct _TOOLBOX_MESSAGE_ISTWI_READ_WRITE_REQUEST{
    MPIU8                               Toolbox;
    MPIU8                               Rsv1;
    MPIU8                               ChainOffset;
    MPIU8                               Function;
    MPIU16                              Rsv2;
    MPIU8                               Rsv3;
    MPIU8                               MessageFlags;
    MPIU32                              MessageContext;
    MPIU8                               Flags;
    MPIU8                               BusNumber;
    MPIU16                              Rsv4;
    MPIU8                               NumberAddressBytes;
    MPIU8                               Rsv5;
    MPIU16                              DataLength;
    MPIU8                               DeviceAddress;
    MPIU8                               Address1;
    MPIU8                               Address2;
    MPIU8                               Address3;
    MPIU32                              Rsv6;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   ScatterGatherList;
}TOOLBOX_MESSAGE_ISTWI_READ_WRITE_REQUEST, * PTOOLBOX_MESSAGE_ISTWI_READ_WRITE_REQUEST;

typedef struct _MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_BUS_TARGET_ID_ACTION_INFO{
    MPIU16  Rsv1;
    MPIU8   Bus;
    MPIU8   TargetID;
}MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_BUS_TARGET_ID_ACTION_INFO, * PMPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_BUS_TARGET_ID_ACTION_INFO;

typedef struct _MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_PORT_IDENTIFIER_ACTION_INFO{
    MPIU32      PortIdentifier;
}MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_PORT_IDENTIFIER_ACTION_INFO, * PMPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_PORT_IDENTIFIER_ACTION_INFO;

typedef struct _MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_FRAME_SIZE_ACTION_INFO{
    MPIU16      FrameSize;
    MPIU8       PortNumber;
    MPIU8       Rsv1;
}MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_FRAME_SIZE_ACTION_INFO, * PMPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_FRAME_SIZE_ACTION_INFO;

typedef union _MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_ACTION_INFO_UNION{
    MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_BUS_TARGET_ID_ACTION_INFO         BusTargetID;
    MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_PORT_IDENTIFIER_ACTION_INFO       PortID;
    MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_FRAME_SIZE_ACTION_INFO            FrameSize;
}MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_ACTION_INFO_UNION, * PMPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_ACTION_INFO_UNION;

typedef struct _TOOLBOX_MESSAGE_FIBRE_CHANNEL_MANAGER_REQUEST{
    MPIU8                                                   ToolID;
    MPIU8                                                   Rsv1;
    MPIU8                                                   ChainOffset;
    MPIU8                                                   MpiFunction;
    MPIU16                                                  Rsv2;
    MPIU8                                                   Rsv3;
    MPIU8                                                   MessageFlags;
    MPIU32                                                  MessageContext;
    MPIU8                                                   Action;
    MPIU8                                                   Rsv4;
    MPIU16                                                  Rsv5;
    MPI_TOOLBOX_FIBRE_CHANNEL_MANAGER_ACTION_INFO_UNION     ActionInfo;
}TOOLBOX_MESSAGE_FIBRE_CHANNEL_MANAGER_REQUEST, * PTOOLBOX_MESSAGE_FIBRE_CHANNEL_MANAGER_REQUEST;

typedef struct _TOOLBOX_MESSAGE_BEACON_REQUEST{
    MPIU8           Tool;
    MPIU8           Rsv1;
    MPIU8           ChainOffset;
    MPIU8           MpiFunction;
    MPIU16          Rsv2;
    MPIU8           Rsv3;
    MPIU8           MessageFlags;
    MPIU32          MessageContext;
    MPIU8           ConnectionNumber;
    MPIU8           PortNumber;
    MPIU8           Rsv4;
    MPIU8           Flags;
}TOOLBOX_MESSAGE_BEACON_REQUEST, * PTOOLBOX_MESSAGE_BEACON_REQUEST;

typedef struct _MESSAGE_DIAGNOSTIC_BUFFER_POST_REQUEST{
    MPIU8           TraceLevel;
    MPIU8           BufferType;
    MPIU8           ChainOffset;
    MPIU8           MpiFunction;
    MPIU16          Rsv1;
    MPIU8           Rsv2;
    MPIU8           MessageFlags;
    MPIU32          MessageContext;
    MPIU32          ExtendedType;
    MPIU32          BufferLength;
    MPIU32          ProductSpecific[4];
    MPIU32          Rsv3;
    MPIU64          BufferAddress;
}MESSAGE_DIAGNOSTIC_BUFFER_POST_REQUEST, * PMESSAGE_DIAGNOSTIC_BUFFER_POST_REQUEST;

typedef struct _MESSAGE_DIAGNOSTIC_BUFFER_POST_REPLY{
    MPIU8   Rsv1;
    MPIU8   BufferType;
    MPIU8   MessageLength;
    MPIU8   MpiFunction;
    MPIU16  Rsv2;
    MPIU8   Rsv3;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU16  Rsv4;
    MPIU16  IocStatus;
    MPIU32  TransferLength;
}MESSAGE_DIAGNOSTIC_BUFFER_POST_REPLY, * PMESSAGE_DIAGNOSTIC_BUFFER_POST_REPLY;

typedef struct _MESSAGE_DIAGNOSTIC_RELEASE_REQUEST{
    MPIU8   Rsv1;
    MPIU8   BufferType;
    MPIU8   ChainOffset;
    MPIU8   MpiFunction;
    MPIU16  Rsv2;
    MPIU8   Rsv3;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
}MESSAGE_DIAGNOSTIC_RELEASE_REQUEST, * PMESSAGE_DIAGNOSTIC_RELEASE_REQUEST;

typedef struct _MESSAGE_DIAGNOSTIC_RELEASE_REPLY{
    MPIU8   Rsv1;
    MPIU8   BufferType;
    MPIU8   MessageLength;
    MPIU8   MpiFunction;
    MPIU16  Rsv2;
    MPIU8   Rsv3;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU16  Rsv4;
    MPIU16  IocStatus;
    MPIU32  IocLogInfo;
}MESSAGE_DIAGNOSTIC_RELEASE_REPLY, * PMESSAGE_DIAGNOSTIC_RELEASE_REPLY;

#pragma pack(pop)
#endif //_MPI_TOOLS_H