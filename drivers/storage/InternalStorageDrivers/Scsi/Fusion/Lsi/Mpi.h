//SPDX-Licence-IdentifierL AGPL 3.0/Proprietary
//Copyright (C) 2024-2025 Tyler Grenier
//Time Started  : 12/28/2024 11:35 PM
//Time Finished : 12/29/2024  9:07 PM
//Last Modified : 12/29/2024  9:07 PM

#ifndef _MPI_H
#define _MPI_H
#pragma pack(push,1)

#include "MpiTypes.h"

//Mpi version 1.5
#define MPI_MAJOR_VERSION               1
#define MPI_MINOR_VERSION               5
#define MPI_MAJOR_VERSION_BITS          0xFF00
#define MPI_MAJOR_VERSION_SHIFT         8
#define MPI_MINOR_VERSION_BITS          0xFF
#define MPI_MINOR_VERSION_SHIFT         8

//Define Current Relsease Version
#define MPI_CURRENT_VERSION_MACRO ((MPI_MAJOR_VERSION << MPI_MAJOR_VERSION_SHIFT) | MPI_MINOR_VERSION)

//Define Valid Release Versions
#define MPI_RELEASE_1_0 0x0100
#define MPI_RELEASE_1_1 0x0101
#define MPI_RELEASE_1_2 0x0102
#define MPI_RELEASE_1_3 0x0103
#define MPI_RELEASE_1_5 0x0105

//Header Set Versions
#define MPI_HEADER_RELEASE_UNIT             0x13
#define MPI_HEADER_RELEASE_DEVICE           0x00
#define MPI_HEADER_RELEASE_UNIT_BITS        0xFF << 8
#define MPI_HEADER_RELEASE_UNIT_SHIFT       8
#define MPI_HEADER_RELEASE_DEVICE_BITS      0xFF
#define MPI_HEADER_RELEASE_DEVICE_SHIFT     0

#define MPI_HEADER_RELEASE_MACRO ((MPI_HEADER_RELEASE_UNIT << MPI_HEADER_RELEASE_UNIT_SHIFT) | (MPI_HEADER_RELEASE_DEVICE))

//Declare Ioc States
#define MPI_IOC_STATE_RESET             0x00
#define MPI_IOC_STATE_READY             0x10000000
#define MPI_IOC_STATE_OPERATIONAL       0x20000000
#define MPI_IOC_STATE_FAULT             0x40000000

#define MPI_IOC_STATE_BITS              0xF0000000
#define MPI_IOC_STATE_SHIFT             28

//Declare Fault Variables
#define MPI_FAULT_REQUEST_MESSAGE_PCI_PARITY        0x8111
#define MPI_FAULT_REQUEST_MESSAGE_PCI_BUS           0x8112
#define MPI_FAULT_REPLY_MESSAGE_PCI_PARITY          0x8113
#define MPI_FAULT_REPLY_MESSAGE_PCI_BUS             0x8114
#define MPI_FAULT_DATA_SEND_PCI_PARITY              0x8115
#define MPI_FAULT_DATA_SEND_PCI_BUS                 0x8116
#define MPI_FAULT_DATA_RECIEVE_PCI_PARRITY          0x8117
#define MPI_FAULT_DATA_RECIEV_PCI_BUS               0x8118

//Define Doorbell Variables
#define MPI_DOORBELL_REGISTER_OFFSET                0
#define MPI_DOORBELL_REGISTER_ACTIVE                0x08000000
#define MPI_DOORBELL_REGISTER_USED                  MPI_DOORBELL_REGISTER_ACTIVE
#define MPI_DOORBELL_REGISTER_ACTIVE_SHIFT          27
#define MPI_DOORBELL_REGISTER_WHO_INIT_BITS         0x07000000
#define MPI_DOORBELL_REGISTER_WHO_INIT_SHIFT        24
#define MPI_DOORBELL_REGISTER_FUNCTION_BITS         0xFF000000
#define MPI_DOORBELL_REGISTER_FUNCTION_SHIFT        24
#define MPI_DOORBELL_REGISTER_ADD_DWORD_BITS        0x00FF0000
#define MPI_DOORBELL_REGISTER_ADD_DWORD_SHIFT       16
#define MPI_DOORBELL_REGISTER_DATA_BITS             0x0000FFFF
#define MPI_DOORBELL_REGISTER_SPECIFIC_FUNC_BITS    0x0000FFFF

//Values For HBAC
#define MPI_DOORBELL_HBAC_VALUE_BITS            0x0000F000
#define MPI_DOORBELL_HBAC_ENABLE_ACCESS         0x01
#define MPI_DOORBELL_HBAC_DISABLE_ACCESS        0x02
#define MPI_DOORBELL_HBAC_FREE_BUFFER           0x03

//Declare WSEQ Values
#define MPI_WRITE_SEQUENCE_OFFSET               0x04
#define MPI_WRITE_SEQUENCE_KEY_VALUE_BITS       0x0F
#define MPI_WRITE_SEQUENCE_1ST_KEY_VALUE        0x04
#define MPI_WRITE_SEQUENCE_2ND_KEY_VALUE        0x0B
#define MPI_WRITE_SEQUENCE_3RD_KEY_VALUE        0x02
#define MPI_WRITE_SEQUENCE_4TH_KEY_VALUE        0x07
#define MPI_WRITE_SEQUENCE_5TH_KEY_VALUE        0x0D

//Declare Diagnostic REGISTER
#define MPI_DIAGNOSTICS_REGISTER_OFFSET                         0x00000008
#define MPI_DIAGNOSTICS_REGISTER_CLEAR_FLASH_BAD_SIGNATURE      0x00000400
#define MPI_DIAGNOSTICS_REGISTER_PREVENT_IOC_BOOT               0x00000200
#define MPI_DIAGNOSTICS_REGISTER_DRWE                           0x00000080
#define MPI_DIAGNOSTICS_REGISTER_FLASH_BAD_SIGNATURE            0x00000040
#define MPI_DIAGNOSTICS_REGISTER_RESET_HISTORY                  0x00000020
#define MPI_DIAGNOSTICS_REGISTER_RW_ENABLE                      0x00000010
#define MPI_DIAGNOSTICS_REGISTER_RESET_ADAPTER                  0x00000004
#define MPI_DIAGNOSTICS_REGISTER_DISABLE_ARM                    0x00000002
#define MPI_DIAGNOSTICS_REGISTER_MEMORY_ENABLE                  0x00000001

#define MPI_TEST_REGISTER_BASE_ADDRESS_OFFSET                   0x0000000C
#define MPI_DIAGNOSTIC_RW_DATA_OFFSET                           0x00000010
#define MPI_DIAGNOSTIC_RW_ADDRESS_OFFSET                        0x00000014

#define MPI_HOST_INTERRUPT_STATUS_REGISTER_OFFSET               0x00000030
#define MPI_HOST_INTERRUPT_STATUS_IOP_DOORBELL_STATUS           0x80000000
#define MPI_HOST_INTERRUPT_STATUS_REPLY_MESSAGE_INTERRUPT       0x00000008
#define MPI_HOST_INTERRUPT_STATUS_DOORBELL_INTERRUPT            0x00000001

#define MPI_HOST_INTERRUPT_BITS_OFFSET                          0x00000034
#define MPI_HOST_INTERRUPT_BITS_RIM                             0x00000008
#define MPI_HOST_INTERRUPT_BITS_DIM                             0x00000001

#define MPI_REQUEST_QUEUE_OFFSET                                0x00000040
#define MPI_REQUEST_POST_FIFO_OFFSET                            0x00000040 

#define MPI_REPLY_QUEUE_OFFSET                                  0x00000044
#define MPI_REPLY_POST_FIFO_OFFSET                              0x00000044
#define MPI_REPLY_FREE_FIFO_OFFSET                              0x00000044

#define MPI_HIGH_PRIORITY_REQUEST_QUEUE_OFFSET                  0x00000048

//Message Frame Descriptors
#define MPI_MESSAGE_FRAME_REQUEST_NB_BITS                       0x00000003
#define MPI_MESSAGE_FRAME_REQUEST_F_BIT                         0x00000001
#define MPI_MESSAGE_FRAME_REQUEST_ADDRESS_BITS                  0xFFFFFFF8

#define MPI_ADDRESS_REPLY_A_BIT                                 0x80000000
#define MPI_ADDRESS_REPLY_TYPE_BITS                             0x7FFFFFFF

#define MPI_CONTEXT_REPLY_A_BIT                                 0x80000000
#define MPI_CONTEXT_REPLY_TYPE_BITS                             0x60000000                                                        
#define MPI_CONTEXT_REPLY_TYPE_SCSI_INIT                        0x00
#define MPI_CONTEXT_REPLY_TYPE_SCSI_TARGET                      0x01
#define MPI_CONTEXT_REPLY_TYPE_LAN                              0x02
#define MPI_CONTEXT_REPLY_TYPE_SHIFT                            29
#define MPI_CONTEXT_REPLY_CONTEXT_BITS                          0x1FFFFFFF

//Reply Macros
#define MPI_GET_REPLY_TYPE_MACRO(X) (((X) & MPI_CONTEXT_REPLY_TYPE_BITS) >> MPI_CONTEXT_REPLY_TYPE_SHIFT)
#define MPI_SET_REPLY_TYPE_MACRO(X,Y) ((X) = ((X) & ~(MPI_CONTEXT_REPLY_TYPE_BITS)) | (((Y) << MPI_CONTEXT_REPLY_TYPE_SHIFT) & MPI_CONTEXT_REPLY_TYPE_BITS))

//Message Functions
#define MPI_FUNCTION_TYPE_SCSI_IO_REQUEST               0x00
#define MPI_FUNCTION_TYPE_SCSI_TASK_MANAGEMENT          0x01
#define MPI_FUNCTION_TYPE_IOC_INITIALIZATION            0x02
#define MPI_FUNCTION_TYPE_IOC_FACTS                     0x03
#define MPI_FUNCTION_TYPE_CONFIGURATION                 0x04
#define MPI_FUNCTION_TYPE_PORT_FACTS                    0x05
#define MPI_FUNCTION_TYPE_PORT_ENABLE                   0X06
#define MPI_FUNCTION_TYPE_EVENT_NOTIFICATION            0x07
#define MPI_FUNCTION_TYPE_EVENT_ACKNOLEDGE              0x08
#define MPI_FUNCTION_TYPE_EVENT_FIRMWARE_DOWNLOAD       0x09
#define MPI_FUNCTION_TYPE_TARGET_COMMAND_BUFFER_POST    0x0A
#define MPI_FUNCTION_TYPE_TARGET_ASSIST                 0x0B
#define MPI_FUNCTION_TYPE_TARGET_STATUS_SEND            0x0C
#define MPI_FUNCTION_TYPE_TARGET_MODE_ABORT             0x0D
#define MPI_FUNCTION_TYPE_FC_LINK_SERVICE_BUFFER_POST   0x0E
#define MPI_FUNCTION_TYPE_FC_LINK_SERVICE_RSP           0x0F
#define MPI_FUNCTION_TYPE_FC_EX_LINK_SERVICE_SEND       0x10
#define MPI_FUNCTION_TYPE_FC_ABORT                      0x11
#define MPI_FUNCTION_TYPE_FC_UPLOAD                     0x12
#define MPI_FUNCTION_TYPE_FC_COMMON_TRANSPORT_SEND      0x13
#define MPI_FUNCTION_TYPE_FC_PRIMATIVE_SEND             0x14

#define MPI_FUNCTION_TYPE_RAID_ACTION                   0x15
#define MPI_FUNCTION_TYPE_RAID_SCSI_IO_PASSTHROUGH      0x16

#define MPI_FUNCTION_TYPE_TOOLBOX                       0x17

#define MPI_FUNCTION_TYPE_SCSI_ENCLOSURE_PROCESSOR      0x18

#define MPI_FUNCTION_TYPE_MAILBOX                       0x19

#define MPI_FUNCTION_TYPE_SMP_PASSTHROUGH               0x1A
#define MPI_FUNCTION_TYPE_SAS_IO_UNIT_CONTROL           0x1B
#define MPI_FUNCTION_TYPE_SATA_PASSTHROUGH              0x1C

#define MPI_FUNCTION_TYPE_DIAGNOSTIC_BUFFER_POST        0x1D
#define MPI_FUNCTION_TYPE_DIAGNOSTIC_RELEASE            0x1E

#define MPI_FUNCTION_TYPE_SCSI_IO_32BIT                 0x1F

#define MPI_FUNCTION_TYPE_LAN_SEND                      0x20
#define MPI_FUNCTION_TYPE_LAN_RECIEVE                   0x21
#define MPI_FUNCTION_TYPE_LAN_RESET                     0x22

#define MPI_FUNCTION_TYPE_TARGET_ASSIST_EXTENDED            0x23
#define MPI_FUNCTION_TYPE_TARGET_COMMAND_BUFFER_BASE_POST   0x24
#define MPI_FUNCTION_TYPE_TARGET_COMMAND_BUFFER_LIST_POST   0x25

#define MPI_FUNCTION_TYPE_INBAND_BUFFER_POST            0x28
#define MPI_FUNCTION_TYPE_INBAND_SEND                   0x29
#define MPI_FUNCTION_TYPE_INBAND_RSP                    0x2A
#define MPI_FUNCTION_TYPE_INBAND_ABORT                  0x2B

#define MPI_FUNCTION_TYPE_IOC_MESSAGE_UNIT_RESET        0x40
#define MPI_FUNCTION_TYPE_IO_UNIT_RESET                 0x41
#define MPI_FUNCTION_TYPE_HANDSHAKE                     0x42
#define MPI_FUNCTION_TYPE_REPLY_FRAME_REMOVE            0x43
#define MPI_FUNCTION_TYPE_HOST_PAGEBUFFER_ACCESS_CONTROL 0x44

//SGE Field Declarations
#define MPI_SCATTER_GATHER_ENTRY_FLAGS_LAST_ELEMENT                 0x80
#define MPI_SCATTER_GATHER_ENTRY_FLAGS_END_OF_BUFFER                0x40
#define MPI_SCATTER_GATHER_ENTRY_FLAGS_ELEMENT_TYPE_BITS            0x30
#define MPI_SCATTER_GATHER_ENTRY_FLAGS_LOCAL_ADDRESS                0x08
#define MPI_SCATTER_GATHER_ENTRY_FLAGS_DIRECTION                    0x04
#define MPI_SCATTER_GATHER_ENTRY_FLAGS_ADDRESS_SIZE                 0x02
#define MPI_SCATTER_GATHER_ENTRY_FLAGS_ENDOF_LIST                   0x01

#define MPI_SCATTER_GATHER_ENTRY_FLAGS_SHIFT                        24

#define MPI_SCATTER_GATHER_ENTRY_LENGTH_BITS                        0x00FFFFFF
#define MPI_SCATTER_GATHER_ENTRY_CHAIN_LENGTH_BITS                  0x0000FFFF

#define MPI_SCATTER_GATHER_ENTRY_ELEMENT_TRANSACTION                0x00
#define MPI_SCATTER_GATHER_ENTRY_ELEMENT_SIMPLE                     0x10
#define MPI_SCATTER_GATHER_ENTRY_ELEMENT_CHAIN_ELEMENT              0x30
#define MPI_SCATTER_GATHER_ENTRY_ELEMENT_BITS                       0x30

#define MPI_SCATTER_GATHER_ADDRESS_LOCATION_FLAGS                   0x00

#define MPI_SCATTER_GATHER_ENTRY_DIRECTION_IOC_TO_HOST              0x00
#define MPI_SCATTER_GATHER_ENTRY_DIRECTION_HOST_TO_IOC              0x04

#define MPI_SCATTER_GATHER_ENTRY_32_BIT_ADDRESSING                  0x00
#define MPI_SCATTER_GATHER_ENTRY_64_BIT_ADDRESSING                  0x02

#define MPI_SCATTER_GATHER_ENTRY_CONTEXT_SIZE_32_BITS               0x00
#define MPI_SCATTER_GATHER_ENTRY_CONTEXT_SIZE_64_BITS               0x02
#define MPI_SCATTER_GATHER_ENTRY_CONTEXT_SIZE_96_BITS               0x04
#define MPI_SCATTER_GATHER_ENTRY_CONTEXT_SIZE_128_BITS              0x06

#define MPI_SCATTER_GATHER_CHAIN_ENTRY_OFFSET_BITS                  0x00FF0000
#define MPI_SCATTER_GATHER_CHAIN_ENTRY_OFFSET_SHIFT                 16

#define MPI_SCATTER_GATHER_ENTRY_SET_FLAGS(Flags) ((MPIU32)(Flags) << MPI_SCATTER_GATHER_ENTRY_FLAGS_SHIFT)
#define MPI_SCATTER_GATHER_ENTRY_GET_FLAGS(Flags)      ((Flags) & ~(MPI_SCATTER_GATHER_ENTRY_LENGTH_BITS) >> MPI_SCATTER_GATHER_ENTRY_FLAGS_SHIFT)
#define MPI_SCATTER_GATHER_ENTRY_LENGTH(Flags)          ((Flags) & MPI_SCATTER_GATHER_ENTRY_LENGTH_BITS)
#define MPI_SCATTER_GATHER_ENTRY_CHAIN_LENGTH(Flags)    ((Flags) & MPI_SCATTER_GATHER_ENTRY_CHAIN_LENGTH_BITS)

#define MPI_SCATTER_GATHER_ENTRY_SET_FLAGS_LENGTH(Flags,Length) \
    MPI_SCATTER_GATHER_ENTRY_SET_FLAGS(Flags) | \
    MPI_SCATTER_GATHER_ENTRY_LENGTH(Length)

#define MPI_pSCATTER_GATHER_ENTRY_GET_FLAGS(PScatterGather) \
    MPI_SCATTER_GATHER_ENTRY_GET_FLAGS((PScatterGather)->FlagsAndLength)

#define MPI_pSCATTER_GATHER_ENTRY_GET_LENGTH(PScatterGather) \
    MPI_SCATTER_GATHER_ENTRY_LENGTH(1)

#define MPI_pSCATTER_GATHER_ENTRY_SET_FLAGS_LENGTH(PScatterGather, Flags, Length) \
    ((PScatterGather)->FlagsAndLength = MPI_SCATTER_GATHER_ENTRY_SET_FLAGS_LENGTH(Flags,Length))

#define MPI_pSCATTER_GATHER_ENTRY_SET_FLAGS(PScaterGather,Flags) \
    ((PScaterGather)->FlagsAndLength |= MPI_SCATTER_GATHER_ENTRY_SET_FLAGS(Flags))

#define MPI_pSCATTER_GATHER_ENTRY_SET_LENGTH(PScaterGather,Length) \
    ((PScaterGather)->FlagsAndLength |= MPI_SCATTER_GATHER_ENTRY_LENGTH(Length))

#define MPI_GET_CHAIN_OFFSET(Base) \
    ((x & MPI_SCATTER_GATHER_CHAIN_ENTRY_OFFSET_BITS) >> MPI_SCATTER_GATHER_CHAIN_ENTRY_OFFSET_SHIFT)


#define MPI_MESSAGE_FLAGS_CONTINUATION_REPLY                    0x80

//Common
#define MPI_IOC_STATUS_COMMON_SUCCESS                           0x00
#define MPI_IOC_STATUS_COMMON_INVALID_FUNCTION                  0x01
#define MPI_IOC_STATUS_COMMON_BUSY                              0x02
#define MPI_IOC_STATUS_COMMON_INVALID_SCATTER_GATHER_LIST       0x03
#define MPI_IOC_STATUS_COMMON_INTERNAL_ERROR                    0x04
#define MPI_IOC_STATUS_COMMON_RESERVED                          0x05
#define MPI_IOC_STATUS_COMMON_INSUFFICENT_RESOURCES             0x06
#define MPI_IOC_STATUS_COMMON_INVALID_FIELD                     0x07
#define MPI_IOC_STATUS_COMMON_INVALID_STATE                     0x08
#define MPI_IOC_STATUS_COMMON_OP_STATE_NT_SUPPORTED             0x09

//Config Ioc Status Values
#define MPI_IOC_STATUS_CONFIGURATION_INVALID_ACTION             0x20
#define MPI_IOC_STATUS_CONFIGURATION_INVALID_TYPE               0x21
#define MPI_IOC_STATUS_CONFIGURATION_INVALID_PAGE               0x22
#define MPI_IOC_STATUS_CONFIGURATION_INVALID_DATA               0x23
#define MPI_IOC_STATUS_CONFIGURATION_NO_DEFAULTS                0x24
#define MPI_IOC_STATUS_CONFIGURATION_CAN_NOT_COMMIT             0x25

//SCSI Reply Values
#define MPI_IOC_STATUS_SCSI_RECOVERED_ERROR                     0x40
#define MPI_IOC_STATUS_SCSI_INVALID_BUS                         0x41
#define MPI_IOC_STATUS_SCSI_INVALID_TARGET                      0x42
#define MPI_IOC_STATUS_SCSI_DEVICE_NOT_THERE                    0x43
#define MPI_IOC_STATUS_SCSI_DATA_OVERRUN                        0x44
#define MPI_IOC_STATUS_SCSI_DATA_UNDERRUN                       0x45
#define MPI_IOC_STATUS_SCSI_IO_DATA_ERROR                       0x46
#define MPI_IOC_STATUS_SCSI_PROTOCOL_ERROR                      0x47
#define MPI_IOC_STATUS_SCSI_TASK_TERMINATED                     0x48
#define MPI_IOC_STATUS_SCSI_RESIDUAL_MISMATCH                   0x49
#define MPI_IOC_STATUS_SCSI_TASK_MANAGEMENT_FAILED              0x4A
#define MPI_IOC_STATUS_SCSI_IOC_TERMINATED                      0x4B
#define MPI_IOC_STATUS_SCSI_EXT_TERMINATED                      0x4C

//SCSI Protection
#define MPI_IOC_STATUS_EEDP_GUARD_ERROR                         0x4D
#define MPI_IOC_STATUS_EEDP_REFERENCE_TAG_ERROR                 0x4E
#define MPI_IOC_STATUS_EEDP_APPLICATION_TAG_ERROR               0x4F

//SCSI Targets
#define MPI_IOC_STATUS_TARGET_PRIORITY_IO                       0x60
#define MPI_IOC_STATUS_TARGET_INVALID_PORT                      0x61
#define MPI_IOC_STATUS_TARGET_INVLAID_IOC_INDEX                 0x62
#define MPI_IOC_STATUS_TARGET_INVLAID_IO_INDEX                  0x62
#define MPI_IOC_STATUS_TARGET_ABORTED                           0x63
#define MPI_IOC_STATUS_TARGET_NO_CONNECTION_RETRIEVABLE         0x64
#define MPI_IOC_STATUS_TARGET_NO_CONNECTION                     0x65
#define MPI_IOC_STATUS_TARGET_XFER_COUNT_MISMATCH               0x6A
#define MPI_IOC_STATUS_TARGET_STS_DATA_NOT_SENT                 0x6B
#define MPI_IOC_STATUS_TARGET_DATA_OFFSET_ERROR                 0x6D
#define MPI_IOC_STATUS_TARGET_TOO_MUCH_WRITE_DATA               0x6E
#define MPI_IOC_STATUS_TARGET_IU_TOO_SHORT                      0x6F
#define MPI_IOC_STATUS_TARGET_ACKNOLEDGE_NAK_TIMEOUT            0x70
#define MPI_IOC_STATUS_TARGET_NAK_RECIEVED                      0x71

// FIBRE CHANNEL PROTOLCOL Extended Targets
#define MPI_IOC_STATUS_TARGET_FIBRE_CHANEL_ABORTED              0x66
#define MPI_IOC_STATUS_TARGET_FIBRE_CHANEL_RX_ID_INVALID        0x67
#define MPI_IOC_STATUS_TARGET_FIBRE_CHANEL_ID_INVLAID           0x68
#define MPI_IOC_STATUS_TARGET_FIBRE_CHANEL_NODE_LOGGED_OUT      0x69

//Direct Access Fibre Channel Valuess
#define MPI_IOC_STATUS_FIBRE_CHANNEL_ABBORTED                   0x66
#define MPI_IOC_STATUS_FIBRE_CHANNEL_RX_ID_INVALID              0x67
#define MPI_IOC_STATUS_FIBRE_CHANNEL_ID_INVALID                 0x68
#define MPI_IOC_STATUS_FIBRE_CHANNEL_NODE_LOGGED_OUT            0x69
#define MPI_IOC_STATUS_FIBRE_CHANNEL_EXCHANGE_CANCELED          0x6C

//LAN Values
#define MPI_IOC_STATUS_LAN_DEVICE_NOT_FOUND                     0x80
#define MPI_IOC_STATUS_LAN_DEVICE_FAILURE                       0x81
#define MPI_IOC_STATUS_LAN_TRANSMIT_ERROR                       0X82
#define MPI_IOC_STATUS_LAN_TRANSMIT_ABORT                       0x83
#define MPI_IOC_STATUS_LAN_RECIEVE_ERROR                        0x84
#define MPI_IOC_STATUS_LAN_RECIEVE_ABORTED                      0x85
#define MPI_IOC_STATUS_LAN_PARTIAL_PACKET                       0x86
#define MPI_IOC_STATUS_LAN_CANCELED                             0x87

// Serial Attatched Scsi Values 
#define MPI_IOC_STATUS_SAS_SMP_REQUEST_FAILED                   0x90
#define MPI_IOC_STATUS_SAS_SMP_DATA_OVERRUN                     0x91

//Inband Values
#define MPI_IOC_STATUS_IN_BAND_ABORTED                          0x98
#define MPI_IOC_STATUS_IN_BAND_NO_CONNECTION                    0x99

//Diagnostic Tools Values
#define MPI_IOC_STATUS_DIAGNOSTIC_RELEASED                      0xA0

//Ioc Status Log Info Available Status
#define MPI_IOC_STATUS_FLAG_LOG_INFO_AVAILABLE                  0x8000
#define MPI_IOC_STATUS_BITS                                     0x7FFF

//Log Info Types
#define MPI_IOC_LOG_INFO_TYPE_BITS                              0xF0000000
#define MPI_IOC_LOG_INFO_TYPE_SHIFT                             28
#define MPI_IOC_LOG_INFO_TYPE_NONE                              0x00
#define MPI_IOC_LOG_INFO_TYPE_SCSI                              0x01
#define MPI_IOC_LOG_INFO_TYPE_FIBRE_CHANNEL                     0x02
#define MPI_IOC_LOG_INFO_TYPE_SAS                               0x03
#define MPI_IOC_LOG_INFO_TYPE_ISCSI                             0x04
#define MPI_IOC_LOG_INFO_LOG_DATA_BITS                          0x0FFFFFFF


//Declare Version Tag
typedef struct _MPI_VERSION_STRUCTURE{
    MPIU8       Device;
    MPIU8       Unit;
    MPIU8       MinorVersion;
    MPIU8       MajorVersion;
}MPI_VERSION_STRUCTURE, * PMPI_VERSION_STRUCTURE;

typedef union _MPI_VERSION_FORMAT{
    MPI_VERSION_STRUCTURE   Structure;
    MPIU32                  dword;
}MPI_VERSION_FORMAT, * PMPI_VERSION_FORMAT;

//Declare Scatter Gather Elemenets
typedef struct _SCATTER_GATHER_ENTRY_SIMPLE_32_BIT{
    MPIU32          FlagsAndLength;
    MPIU32          Address;
}SCATTER_GATHER_ENTRY_SIMPLE_32_BIT, * PSCATTER_GATHER_ENTRY_SIMPLE_32_BIT;

typedef struct _SCATTER_GATHER_ENTRY_SIMPLE_64_BIT{
    MPIU32          FlagsAndLength;
    MPIU64          Address;
}SCATTER_GATHER_ENTRY_SIMPLE_64_BIT, * PSCATTER_GATHER_ENTRY_SIMPLE_64_BIT;

typedef struct _SCATTER_GATHER_ENTRY_SIMPLE_UNION{
    MPIU32      FlagsAndLength;
    union{
        MPIU32  Address32;
        MPIU64  Address64;
    }Address;
}SCATTER_GATHER_ENTRY_SIMPLE_UNION, * PSCATTER_GATHER_ENTRY_SIMPLE_UNION;

//Declare Scatter Chain
typedef struct _SCATTER_GATHER_CHAIN_ENTRY_32_BIT{
    MPIU16          Length;
    MPIU8           NextChainOffset;
    MPIU8           Flags;
    MPIU32          Address;
}SCATTER_GATHER_CHAIN_ENTRY_32_BIT, * PSCATTER_GATHER_CHAIN_ENTRY_32_BIT;

typedef struct _SCATTER_GATHER_CHAIN_ENTRY_64_BIT{
    MPIU16          Length;
    MPIU8           NextChainOffset;
    MPIU8           Flags;
    MPIU64          Address;
}SCATTER_GATHER_CHAIN_ENTRY_64_BIT, * PSCATTER_GATHER_CHAIN_ENTRY_64_BIT;

typedef struct _SCATTER_GATHER_CHAIN_ENTRY_UNION{
    MPIU16      Length;
    MPIU8       NextChainOffset;
    MPIU8       Flags;
    union{
        MPIU32  Address32;
        MPIU64  Address64;
    }Address;
}SCATTER_GATHER_CHAIN_ENTRY_UNION, * PSCATTER_GATHER_CHAIN_ENTRY_UNION;

//Declare Transaction Context Elements
typedef struct _SCATTER_GATHER_TCE_32_BIT{
    MPIU8       Rsv1;
    MPIU8       ContextSize;
    MPIU8       LengthOfDetails;
    MPIU8       TransactionFlags;
    MPIU32      TCE;
    MPIU32      TCEDetails[];
}SCATTER_GATHER_TCE_32_BIT, * PSCATTER_GATHER_TCE_32_BIT;

typedef struct _SCATTER_GATHER_TCE_64_BIT{
    MPIU8       Rsv1;
    MPIU8       ContextSize;
    MPIU8       LengthOfDetails;
    MPIU8       TransactionFlags;
    MPIU32      TCE[2];
    MPIU32      TCEDetails[1];
}SCATTER_GATHER_TCE_64_BIT, * PSCATTER_GATHER_TCE_64_BIT;

typedef struct _SCATTER_GATHER_TCE_96_BIT{
    MPIU8       Rsv1;
    MPIU8       ContextSize;
    MPIU8       LengthOfDetails;
    MPIU8       TransactionFlags;
    MPIU32      TCE[3];
    MPIU32      TCEDetails[1];
}SCATTER_GATHER_TCE_96_BIT, * PSCATTER_GATHER_TCE_96_BIT;

typedef struct _SCATTER_GATHER_TCE_128_BIT{
    MPIU8       Rsv1;
    MPIU8       ContextSize;
    MPIU8       LengthOfDetails;
    MPIU8       TransactionFlags;
    MPIU32      TCE[4];
    MPIU32      TCEDetails[1];
}SCATTER_GATHER_TCE_128_BIT, * PSCATTER_GATHER_TCE_128_BIT;

typedef struct _SCATTER_GATHER_TCE_UNION{
    MPIU8       Rsv1;
    MPIU8       ContextSize;
    MPIU8       LengthOfDetials;
    MPIU8       TransactionFlags;
    union{
        MPIU32  TCE32[1];
        MPIU32  TCE64[2];
        MPIU32  TCE96[3];
        MPIU32  TCE128[4];
    }TCE;
    MPIU32      TransactionDetails[1];
}SCATTER_GATHER_TCE_UNION, * PSCATTER_GATHER_TCE_UNION;

typedef struct _SCATTER_GATHER_ENTRY_IO_UNION{
    union{
        SCATTER_GATHER_ENTRY_SIMPLE_UNION   SimpleEntry;
        SCATTER_GATHER_CHAIN_ENTRY_UNION    ChainEntry;
    }SGE;
}SCATTER_GATHER_ENTRY_IO_UNION, * PSCATTER_GATHER_ENTRY_IO_UNION;

typedef struct _SCATTER_GATHER_TCE_SIMPLE_UNION{
    union{
        SCATTER_GATHER_ENTRY_SIMPLE_UNION   SimpleEntry;
        SCATTER_GATHER_TCE_UNION            TransactionEntry;
    }SGE;
}SCATTER_GATHER_TCE_SIMPLE_UNION, * PSCATTER_GATHER_TCE_SIMPLE_UNION;

typedef struct _SCATTER_GATHER_ENTRY_MPI_UNION{
    union{
        SCATTER_GATHER_ENTRY_SIMPLE_UNION   SimpleEntry;
        SCATTER_GATHER_CHAIN_ENTRY_UNION    ChainEntry;
        SCATTER_GATHER_TCE_UNION            TransactionEntry;
    }SGE;
}SCATTER_GATHER_ENTRY_MPI_UNION, * PSCATTER_GATHER_ENTRY_MPI_UNION;

typedef struct _STANDARD_MESSAGE_REQUEST_HEADER{
    MPIU8       Rsv1[2];
    MPIU8       ChainOffset;
    MPIU8       DeviceFunction;
    MPIU8       Rsv2[3];
    MPIU8       MessageFlags;
    MPIU32      MessageContext;
}STANDARD_MESSAGE_REQUEST_HEADER, * PSTANDARD_MESSAGE_REQUEST_HEADER;

typedef struct _DEFAULT_REPLY_MESSAGE{
    MPIU8   Rsv1[2];
    MPIU8   MessageLength;
    MPIU8   DeviceFunction;
    MPIU8   Rsv2[3];
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU8   Rsv3[2];
    MPIU16  IocStatus;
    MPIU32  IocLogInfo;
}DEFAULT_REPLY_MESSAGE, *PDEFAULT_REPLY_MESSAGE;



#pragma pack(pop)
#endif //_MPI_H