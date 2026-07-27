#include "ScsiCore.h"

void ScsiCoreEncodeCdb6Command(
    PSCSI_CDB6_COMMAND  Cdb,
    UINT8               OpCode,
    UINT8               MsbMci,
    UINT16              Lba,
    UINT8               TpaLength,
    UINT8               Control 
){
    UINT16 Tmp16;
    SCSI_CDB6_COMMAND tCdb = {0};
    tCdb.OpCode = OpCode;
    tCdb.MsbMci = MsbMci;
    tCdb.Lba = Lba;
    LouKeSwapEndianess(&TpaLength, &Tmp16, sizeof(UINT16));
    tCdb.TpaLength = Tmp16;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_CDB6_COMMAND));
}


void 
ScsiCoreEncodeFormatUnitCommand(
    PSCSI_FORMAT_UNIT_COMMAND_STRUCTURE Cdb,
    UINT8                               DefectListFormat,
    UINT8                               CmpList,
    UINT8                               FmtData,
    UINT8                               LongList,
    UINT8                               FmtpInfo,
    UINT8                               VendorSpecific,
    UINT8                               Ffmt,
    UINT8                               Control
){
    SCSI_FORMAT_UNIT_COMMAND_STRUCTURE tCdb;
    tCdb.OpCode = SCSI_COMMAND_FORMAT_UNIT;
    tCdb.FmtInfoLlFmtDataClDfl = (DefectListFormat) | (CmpList << 3) | (FmtData << 4) | (LongList << 5) | (FmtpInfo << 6);
    tCdb.VendorSpecific = VendorSpecific;
    tCdb.Ffmt = Ffmt;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_FORMAT_UNIT_COMMAND_STRUCTURE));
}