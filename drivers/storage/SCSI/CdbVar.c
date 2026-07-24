#include "ScsiCore.h"

void 
ScsiCoreEncodeCdbVar(
    PSCSI_CDBVAR_COMMAND    Cdb,
    UINT8                   Control,
    UINT8                   Mci[5],
    UINT16                  ServiceAction,
    UINT8*                  Buffer,
    UINT8                   BufferLength
){
    UINT16 Tmp16;
    SCSI_CDBVAR_COMMAND_HEADER tCdb = {0};
    tCdb.OpCode = SCSI_CDBVAR_COMMAND_OPCODE;
    tCdb.Control = Control;
    memcpy(tCdb.Mci, Mci, 5);
    tCdb.CdbAdditionalLength = BufferLength;
    LouKeSwapEndianess(&ServiceAction, &Tmp16, sizeof(UINT16));
    tCdb.ServiceAction = Tmp16;
    memcpy(Cdb, &tCdb, sizeof(SCSI_CDBVAR_COMMAND_HEADER));
    memcpy(&Cdb->ServiceActionData[0], Buffer, BufferLength);
}

void 
ScsiCoreEncodeLongLbaCdbVar(
    PSCSI_LONG_LBA_CDBVAR_COMMAND   Cdb,
    UINT8                           Control,
    UINT8                           Mci[5],
    UINT8                           CdbAdditionalLength,
    UINT16                          ServiceAction,
    UINT8                           MciFuaDpoMci,
    UINT8                           Mci2,
    UINT64                          Lba,
    UINT64                          Mci3,
    UINT32                          TpaLength
){
    UINT64 Tmp64;
    UINT32 Tmp32;
    UINT16 Tmp16;
    SCSI_LONG_LBA_CDBVAR_COMMAND tCdb = {0};
    tCdb.OpCode = SCSI_CDBVAR_COMMAND_OPCODE;
    tCdb.Control = Control;
    memcpy(tCdb.Mci, Mci, 5);
    tCdb.CdbAdditionalLength = CdbAdditionalLength;
    LouKeSwapEndianess(&ServiceAction, &Tmp16, sizeof(UINT16));
    tCdb.ServiceAction = Tmp16;
    tCdb.MciFuaDpoMci = MciFuaDpoMci;
    tCdb.Mci2 = Mci2;
    LouKeSwapEndianess(&Lba, &Tmp64, sizeof(UINT64));
    tCdb.Lba = Tmp64;
    LouKeSwapEndianess(&Mci3, &Tmp64, sizeof(UINT64));
    tCdb.Mci3 = Tmp64;
    LouKeSwapEndianess(&TpaLength, &Tmp32, sizeof(UINT32));
    tCdb.TpaLength = Tmp32;
    memcpy(Cdb, &tCdb, sizeof(SCSI_LONG_LBA_CDBVAR_COMMAND));
}

