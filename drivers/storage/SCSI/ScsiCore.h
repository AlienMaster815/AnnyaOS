#ifndef _SCSI_CORE_H
#define _SCSI_CORE_H

#include <LouDDK.h>

//Command data types are in Big Endian (32 : 24 : 16 : 8 : 0)

typedef struct PACKED _SCSI_CDB6_COMMAND{
    UINT8   OpCode;
    UINT8   MsbMci;
    UINT16  Lba;
    UINT8   TpaLength;
    UINT8   Control;
}SCSI_CDB6_COMMAND, * PSCSI_CDB6_COMMAND;

typedef struct PACKED _SCSI_CDB10_COMMAND{
    UINT8   OpCode;
    UINT8   ServiceActionMci;
    UINT32  Lba;
    UINT8   Mci;
    UINT16  TpaLength;
    UINT8   Control;
}SCSI_CDB10_COMMAND, * PSCSI_CDB10_COMMAND;

typedef struct PACKED _SCSI_CDB12_COMMAND{
    UINT8   OpCode;
    UINT8   ServiceActionMci;
    UINT32  Lba;
    UINT32  TpaLength;
    UINT8   Mci;
    UINT8   Control;
}SCSI_CDB12_COMMAND, * PSCSI_CDB12_COMMAND;

typedef struct PACKED _SCSI_CDB16_COMMAND{
    UINT8   OpCode;
    UINT64  Lba;
    UINT32  TpaLength;
    UINT8   Mci;
    UINT8   Control;
}SCSI_CDB16_COMMAND, * PSCSI_CDB16_COMMAND;


typedef struct PACKED _SCSI_CDBVAR_COMMAND_HEADER{
    UINT8   OpCode;
    UINT8   Control;
    UINT8   Mci[5];
    UINT8   CdbAdditionalLength;
    UINT16  ServiceAction;
}SCSI_CDBVAR_COMMAND_HEADER, * PSCSI_CDBVAR_COMMAND_HEADER;

typedef struct PACKED _SCSI_CDBVAR_COMMAND{
    SCSI_CDBVAR_COMMAND_HEADER  CommandHeader;
    UINT8                       ServiceActionData[];
}SCSI_CDBVAR_COMMAND, * PSCSI_CDBVAR_COMMAND;

typedef struct PACKED _SCSI_LONG_LBA_CDBVAR_COMMAND{
    UINT8   OpCode;
    UINT8   Control;
    UINT8   Mci[5];
    UINT8   CdbAdditionalLength;
    UINT16  ServiceAction;
    UINT8   MciFuaDpoMci;
    UINT8   Mci2;
    UINT64  Lba;
    UINT64  Mci3;
    UINT32  TpaLength;
}SCSI_LONG_LBA_CDBVAR_COMMAND, * PSCSI_LONG_LBA_CDBVAR_COMMAND;


#define SCSI_CDBVAR_COMMAND_OPCODE 0x7F

#define SCSI_OPCODE_GROUP_CODE_6BYTE_COMMAND        0b000
#define SCSI_OPCODE_GROUP_CODE_10_1BYTE_COMMAND     0b001
#define SCSI_OPCODE_GROUP_CODE_10_2BYTE_COMMAND     0b010
#define SCSI_OPCODE_GROUP_CODE_16_BYTE_COMMAND      0b100
#define SCSI_OPCODE_GROUP_CODE_12_BYTE_COMMAND      0b101

//Page 44

#define SCSI_LONG_LBA_COMMAND_SIZE 0x18

#endif