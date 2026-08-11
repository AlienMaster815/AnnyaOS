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
    SCSI_CDBVAR_COMMAND_HEADER tCdb = {0};
    tCdb.OpCode = SCSI_CDBVAR_COMMAND_OPCODE;
    tCdb.Control = Control;
    memcpy(tCdb.Mci, Mci, 5);
    tCdb.CdbAdditionalLength = BufferLength;
    tCdb.ServiceAction = ScsiCoreEncodeUint16(ServiceAction);
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
    SCSI_LONG_LBA_CDBVAR_COMMAND tCdb = {0};
    tCdb.OpCode = SCSI_CDBVAR_COMMAND_OPCODE;
    tCdb.Control = Control;
    memcpy(tCdb.Mci, Mci, 5);
    tCdb.CdbAdditionalLength = CdbAdditionalLength;
    tCdb.ServiceAction = ScsiCoreEncodeUint16(ServiceAction);
    tCdb.MciFuaDpoMci = MciFuaDpoMci;
    tCdb.Mci2 = Mci2;
    tCdb.Lba = ScsiCoreEncodeUint64(Lba);
    tCdb.Mci3 = ScsiCoreEncodeUint64(Mci3);
    tCdb.TpaLength = ScsiCoreEncodeUint32(TpaLength);
    memcpy(Cdb, &tCdb, sizeof(SCSI_LONG_LBA_CDBVAR_COMMAND));
}

void 
ScsiCoreEncodeRead32Command(
    PSCSI_READ32_COMMAND_STRUCTURE  Cdb,
    UINT8                           Control,
    UINT8                           GroupNumber,
    UINT16                          ServiceAction,
    UINT8                           Rarc,
    UINT8                           Fua,
    UINT8                           Dpo,
    UINT8                           RdProtect,
    UINT64                          Lba,
    UINT32                          EilbrTag,
    UINT16                          ElbaTag,
    UINT16                          LbaTagMask,
    UINT32                          TransferLength
){
    SCSI_READ32_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_READ_CDB32;
    tCdb.Control = Control;
    tCdb.GroupNumber = GroupNumber;
    tCdb.AdditionalLength = 0x18;
    tCdb.ServiceAction = ScsiCoreEncodeUint16(ServiceAction);
    tCdb.RarcFuaDp0Rdprotect = ((Rarc << 2) | (Fua << 3) | (Dpo << 4) | (RdProtect << 5));
    tCdb.Lba = ScsiCoreEncodeUint64(Lba);
    tCdb.EilbrTag = ScsiCoreEncodeUint32(EilbrTag);
    tCdb.ElbaTag = ScsiCoreEncodeUint16(ElbaTag);
    tCdb.LbaTagMask = ScsiCoreEncodeUint16(LbaTagMask);
    tCdb.TransferLength = ScsiCoreEncodeUint32(TransferLength);
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ32_COMMAND_STRUCTURE));
}