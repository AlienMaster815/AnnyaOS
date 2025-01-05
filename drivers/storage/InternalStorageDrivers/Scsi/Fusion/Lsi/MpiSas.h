//SPDX-Licence-IdentifierL AGPL 3.0/Proprietary
//Copyright (C) 2024-2025 Tyler Grenier
//Time Started  : 12/31/2024 12:49 AM
//Time Finished : 12/31/2024  2:13 AM
//Last Modified : 12/31/2024  2:13 AM


#ifndef _MPI_SAS_H
#define _MPI_SAS_H
#pragma pack(push,1)

//sas status Values
#define MPI_SAS_STATUS_SUCCESS                                  0x00
#define MPI_SAS_STATUS_UNKOWN_ERROR                             0x01
#define MPI_SAS_STATUS_INVALID_FRAME                            0x02
#define MPI_SAS_STATUS_UTC_BAD_DESTINATION                      0x03
#define MPI_SAS_STATUS_UTC_BREAK_RECIEVED                       0x04
#define MPI_SAS_STATUS_UTC_CONNECTION_RATE_NOT_SUPPORTED        0x05
#define MPI_SAS_STATUS_UTC_PORT_LAYER_REQUEST                   0x06
#define MPI_SAS_STATUS_UTC_PROTOCOL_NOT_SUPPORTED               0x07
#define MPI_SAS_STATUS_UTC_STP_RESOURCE_BUSY                    0x08
#define MPI_SAS_STATUS_UTC_WRONG_DESTINATION                    0x09
#define MPI_SAS_STATUS_SHORT_INFORMATION_LIMIT                  0x0A
#define MPI_SAS_STATUS_LONG_INFORMATION_UNIT                    0x0B
#define MPI_SAS_STATUS_XFER_READY_INCORRECT_WRITE_DATA          0x0C
#define MPI_SAS_STATUS_XFER_READY_REQUEST_OFFSET_ERROR          0x0D
#define MPI_SAS_STATUS_XFER_READY_NOT_EXPECTED                  0x0E
#define MPI_SAS_STATUS_DATA_INCORRECT_DATA_LENGTH               0x0F
#define MPI_SAS_STATUS_DATA_TOO_MUCH_READ_DATA                  0x10
#define MPI_SAS_STATUS_DATA_OFFSET_ERROR                        0x11
#define MPI_SAS_STATUS_SDSF_NAKED_RECIEVED                      0x12
#define MPI_SAS_STATUS_SDSF_CONNECTION_FAILED                   0x13
#define MPI_SAS_STATUS_INITIATOR_RESPONCE_TIMEOUT               0x14

//Sas Device Info
#define MPI_SAS_DEVICE_PRODUCT_INFORMATION                      0xF0000000

#define MPI_SAS_DEVICE_INFORMATION_SEP                          0x00004000
#define MPI_SAS_DEVICE_INFORMATION_ATAPI_DEVICE                 0x00002000
#define MPI_SAS_DEVICE_INFORMATION_LSI_DEVICE                   0x00001000
#define MPI_SAS_DEVICE_INFORMATION_DIRECT_ATTATCH               0x00000800
#define MPI_SAS_DEVICE_INFORMATION_SSP_TARGET                   0x00000400
#define MPI_SAS_DEVICE_INFORMATION_STP_TARGET                   0x00000200
#define MPI_SAS_DEVICE_INFORMATION_SMP_TARGET                   0x00000100
#define MPI_SAS_DEVICE_INFORMATION_SATA_DEVICE                  0x00000080
#define MPI_SAS_DEVICE_INFORMATION_SSP_INITIATOR                0x00000040
#define MPI_SAS_DEVICE_INFORMATION_STP_INITIATOR                0x00000020
#define MPI_SAS_DEVICE_INFORMATION_SMP_INITIATOR                0x00000010
#define MPI_SAS_DEVICE_INFORMATION_SATA_HOST                    0x00000008

#define MPI_SAS_DEVICE_INFORMATION_DEVICE_TYPE_BITS             7
#define MPI_SAS_DEVICE_INFORMATION_NO_DEVICE                    0
#define MPI_SAS_DEVICE_INFORMATION_END_DEVICE                   1
#define MPI_SAS_DEVICE_INFORMATION_EDGE_EXPANDER                2
#define MPI_SAS_DEVICE_INFORMATION_FANOUT_EXPANDER              3

//Passthrough Values
#define MPI_SERIAL_MANAGEMENT_PASS_THROUGH_REQUEST_FLAGS_IMEDIATE                   0x80

//Conection Rate Flags
#define MPI_SERIAL_MANAGEMENT_PASS_THROUGH_REQUEST_CONNECTION_RATE_NEGOTIATED       0x00
#define MPI_SERIAL_MANAGEMENT_PASS_THROUGH_REQUEST_CONNECTION_RATE_1_5              0x08
#define MPI_SERIAL_MANAGEMENT_PASS_THROUGH_REQUEST_CONNECTION_RATE_3_0              0x09

#define MPI_SERIAL_MANAGEMENT_PASS_THROUGH_REPLY_FLAGS_IMEDIATE                     080

//Passthrough Values
#define MPI_SATA_PASSTHROUGH_REQUEST_FLAGS_RESET_DEVICE             0x0200
#define MPI_SATA_PASSTHROUGH_REQUEST_FLAGS_EXECUTE_DIAGNOSTIC       0x0100
#define MPI_SATA_PASSTHROUGH_REQUEST_FLAGS_DMA_QUEUED               0x0080
#define MPI_SATA_PASSTHROUGH_REQUEST_FLAGS_PACKET_COMMAND           0x0040
#define MPI_SATA_PASSTHROUGH_REQUEST_FLAGS_DMA                      0x0020
#define MPI_SATA_PASSTHROUGH_REQUEST_FLAGS_PIO                      0x0010
#define MPI_SATA_PASSTHROUGH_REQUEST_FLAGS_UNSPECIFIED              0x0004
#define MPI_SATA_PASSTHROUGH_REQUEST_FLAGS_WRITE                    0x0002
#define MPI_SATA_PASSTHROUGH_REQUEST_FLAGS_READ                     0x0001

#define MPI_SATA_PASSTHROUGH_REQUEST_CONNECTION_RATE_NEGOTIATED     0
#define MPI_SATA_PASSTHROUGH_REQUEST_CONNECTION_RATE_1_5            8
#define MPI_SATA_PASSTHROUGH_REQUEST_CONNECTION_RATE_3_0            9

//Operation Fields
#define MPI_SERIAL_ATTACHED_OPERATION_CLEAR_NOT_PRESENT                 0x01
#define MPI_SERIAL_ATTACHED_OPERATION_CLEAR_ALL_PERSISTENT              0x02
#define MPI_SERIAL_ATTACHED_OPERATION_PHY_LINK_RESET                    0x06
#define MPI_SERIAL_ATTACHED_OPERATION_PHY_HARD_RESET                    0x07
#define MPI_SERIAL_ATTACHED_OPERATION_PHY_CLEAR_ERROR_LOG               0x08
#define MPI_SERIAL_ATTACHED_OPERATION_MAP_CURRENT                       0x09
#define MPI_SERIAL_ATTACHED_OPERATION_SEND_PRIMATIVE                    0x0A
#define MPI_SERIAL_ATTACHED_OPERATION_FORCE_FULL_DISCOVERY              0x0B    
#define MPI_SERIAL_ATTACHED_OPERATION_TRANSMIT_PORT_SELECT_SIGNAL       0x0C
#define MPI_SERIAL_ATTACHED_OPERATION_TRANSMIT_REMOVE_DEVICE            0x0D
#define MPI_SERIAL_ATTACHED_OPERATION_REMOVE_DEVICE                     0x0D
#define MPI_SERIAL_ATTACHED_OPERATION_SET_IOC_PARAMETER                 0x0E
#define MPI_SERIAL_ATTACHED_OPERATION_PRODUCT_MINIMUM                   0x80

//Primitive Flags
#define MPI_SERIAL_ATTACHED_PRIMATIVE_FLAGS_SINGLE          8
#define MPI_SERIAL_ATTACHED_PRIMATIVE_FLAGS_TRIPPLE         2
#define MPI_SERIAL_ATTACHED_PRIMATIVE_FLAGS_REDUNDANT       1

//Serial Management protocols
typedef struct _MESSAGE_SERIAL_MANAGEMENT_PASSTHROUGH_REQUEST{
    MPIU8                                   PassthroughFlags;
    MPIU8                                   PhysicalPort;
    MPIU8                                   ChainOffset;
    MPIU8                                   MpiFunction;
    MPIU16                                  Rsv1;
    MPIU8                                   ConnectionRate;
    MPIU8                                   MessageFlags;
    MPIU32                                  MessageContext;
    MPIU32                                  Rsv2;
    MPIU64                                  SasAddress;
    MPIU32                                  Rsv3;
    MPIU32                                  Rsv4;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION       ScatterGatherList;
}MESSAGE_SERIAL_MANAGEMENT_PASSTHROUGH_REQUEST, * PMESSAGE_SERIAL_MANAGEMENT_PASSTHROUGH_REQUEST;

typedef struct _MESSAGE_SERIAL_MANAGEMENT_PASSTHROUGH_REPLY{
    MPIU8       PassthroughFlags;
    MPIU8       PhysicalPort;
    MPIU8       MessageLength;
    MPIU8       MpiFunction;
    MPIU16      ResponceLength;
    MPIU8       Rsv1;
    MPIU8       MessageFlags;
    MPIU32      MessageContext;
    MPIU8       Rsv2;
    MPIU8       SasStatus;
    MPIU16      IocStatus;
    MPIU32      IocLogInformation;
    MPIU32      Rsv3;
    MPIU8       RespondData[4];
}MESSAGE_SERIAL_MANAGEMENT_PASSTHROUGH_REPLY, * PMESSAGE_SERIAL_MANAGEMENT_PASSTHROUGH_REPLY;

typedef struct _MESSAGE_SATA_PASSTHROUGH_REQUEST{
    MPIU8                                   Target;
    MPIU8                                   BusNumber;
    MPIU8                                   ChainOffset;
    MPIU8                                   MpiFunction;
    MPIU16                                  PassFlags;
    MPIU8                                   ConnectionRate;
    MPIU8                                   MessageFlags;
    MPIU32                                  MessageContext;
    MPIU32                                  Rsv1;
    MPIU32                                  Rsv2;
    MPIU32                                  Rsv3;
    MPIU32                                  DataLength;
    MPIU8                                   CommandFis[20];
    SCATTER_GATHER_ENTRY_SIMPLE_UNION       ScatterGatherList;
}MESSAGE_SATA_PASSTHROUGH_REQUEST, * PMESSAGE_SATA_PASSTHROUGH_REQUEST;

typedef struct _MESSAGE_SATA_PASSTHROUGH_REPLY{
    MPIU8   Target;
    MPIU8   BusNumber;
    MPIU8   MessageLength;
    MPIU8   MpiFunction;
    MPIU16  PassthroughFlags;
    MPIU8   Rsv1;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU8   Rsv2;
    MPIU8   SasStatus;
    MPIU16  IocStatus;
    MPIU32  IocLogInformation;
    MPIU8   SCR;
    MPIU32  TranferCount;
}MESSAGE_SATA_PASSTHROUGH_REPLY, * PMESSAGE_SATA_PASSTHROUGH_REPLY;

typedef struct _MESSAGE_SERIAL_ATTATCH_IO_UNIT_CONTROL_REQUEST{
    MPIU8   Operation;
    MPIU8   Rsv1;
    MPIU8   ChainOffset;
    MPIU8   MpiFunction;
    MPIU16  DeviceHandle;
    MPIU8   IocParameter;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU8   TargetID;
    MPIU8   BusNumber;
    MPIU8   PhyNumber;
    MPIU8   PrimitiveFlags;
    MPIU32  Primitive;
    MPIU64  SasAddress;
    MPIU32  IocParameterValue;
}MESSAGE_SERIAL_ATTATCH_IO_UNIT_CONTROL_REQUEST, * PMESSAGE_SERIAL_ATTATCH_IO_UNIT_CONTROL_REQUEST;

typedef struct _MESSAGE_SERIAL_ATTATCH_IO_UNIT_CONTROL_REPLY{
    MPIU8   Operation;
    MPIU8   Rsv1;
    MPIU8   MessageLength;
    MPIU8   MpiFunction;
    MPIU16  DeviceHandle;
    MPIU8   IocParameter;
    MPIU8   MessageFlags;
    MPIU32  MessageContext;
    MPIU16  Rsv2;
    MPIU16  IocStatus;
    MPIU32  IocLogInformation;
}MESSAGE_SERIAL_ATTATCH_IO_UNIT_CONTROL_REPLY, * PMESSAGE_SERIAL_ATTATCH_IO_UNIT_CONTROL_REPLY;

#pragma pack(pop)
#endif //_MPI_SAS_H