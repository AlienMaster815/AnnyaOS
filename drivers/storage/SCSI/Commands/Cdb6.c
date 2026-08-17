#include "../ScsiCore.h"

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
    SCSI_FORMAT_UNIT_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_FORMAT_UNIT;
    tCdb.FmtInfoLlFmtDataClDfl = (DefectListFormat) | (CmpList << 3) | (FmtData << 4) | (LongList << 5) | (FmtpInfo << 6);
    tCdb.VendorSpecific = VendorSpecific;
    tCdb.Ffmt = Ffmt;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_FORMAT_UNIT_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeInquiryCommand(
    PSCSI_INQUIRY_COMMAND_STRUCTURE     Cdb,
    UINT8                               Evpd,
    UINT8                               Cmddt, 
    UINT8                               PageCode,
    UINT16                              AllocationLength,
    UINT8                               Control
){
    SCSI_INQUIRY_COMMAND_STRUCTURE  tCdb = {0};
    UINT16 Tmp16;
    tCdb.OpCode = SCSI_COMMAND_INQUIRY;
    tCdb.EvdpCmddt = Evpd | (Cmddt << 1);
    tCdb.PageCode = PageCode;
    LouKeSwapEndianess(&AllocationLength, &Tmp16, sizeof(UINT16));
    tCdb.AllocationLength = AllocationLength;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_INQUIRY_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeModeSelect6Command(
    PSCSI_MODE_SELECT6_COMMAND_STRUCTURE    Cdb,
    UINT8                                   Sp,
    UINT8                                   Rtd,
    UINT8                                   Pf,
    UINT8                                   ParameterListLength,
    UINT8                                   Control
){
    SCSI_MODE_SELECT6_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_MODE_SELECT_CDB6;
    tCdb.SpRtdPf = Sp | (Rtd << 1) | (Pf << 4);
    tCdb.ParameterListLength = ParameterListLength;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_MODE_SELECT6_COMMAND_STRUCTURE));
}

void
ScsiCoreEncodeModeSense6Command(
    PSCSI_MODE_SENSE6_COMMAND_STRUCTURE Cdb,
    UINT8                               Dbd,
    UINT8                               PageCode,
    UINT8                               Pc,
    UINT8                               SubPageCode,
    UINT8                               AllocationLength,
    UINT8                               Control  
){
    SCSI_MODE_SENSE6_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_MODE_SENCE_CDB6;
    tCdb.Dbd = (Dbd << 3);
    tCdb.PageCodePc = PageCode | (Pc << 6);
    tCdb.SubPageCode = SubPageCode;
    tCdb.AllocationLength = AllocationLength;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_MODE_SENSE6_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeRead6Command(
    PSCSI_READ6_COMMAND_STRUCTURE   Cdb,
    UINT32                          Lba,
    UINT8                           TransferLength,
    UINT8                           Control  
){
    SCSI_READ6_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_READ_CDB6;
    tCdb.Lba[0] = (Lba >> 16) & 0x1F;
    tCdb.Lba[1] = (Lba >> 8) & 0xFF;
    tCdb.Lba[2] =  Lba & 0xFF;
    tCdb.TransferLength = TransferLength;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ6_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeReassignBlocksCommand(
    PSCSI_REASSIGN_BLOCKS_COMMAND_STRUCTURE Cdb,
    UINT8                                   LongList,
    UINT8                                   LongLba,
    UINT8                                   Control
){
    SCSI_REASSIGN_BLOCKS_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_REASIGN_BLOCKS;
    tCdb.LongGListLba = (LongList | (LongLba << 1));
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_REASSIGN_BLOCKS_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeRecieveDiagnosticResultsCommand(
    PSCSI_RECIEVE_DIAGNOSTIC_RESULTS_COMMAND_STRUCTURE  Cdb,
    UINT8                                               Pcv,
    UINT8                                               PageCode,
    UINT16                                              AllocationLength,
    UINT8                                               Control
){
    SCSI_RECIEVE_DIAGNOSTIC_RESULTS_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_RECIEVE_DIAGNOSTIC_RESULTS;
    tCdb.Pcv = Pcv;
    tCdb.PageCode = PageCode;
    tCdb.AllocationLength = ScsiCoreEncodeUint16(AllocationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_RECIEVE_DIAGNOSTIC_RESULTS_COMMAND_STRUCTURE));
}

void
ScsiCoreEncodeRequestSenseCommand(
    PSCSI_REQUEST_SENSE_COMMAND_STRUCTURE   Cdb,
    UINT8                                   Desc,
    UINT8                                   AllocationLength,
    UINT8                                   Control
){
    SCSI_REQUEST_SENSE_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_REQUEST_SENSE;
    tCdb.Desc = Desc;
    tCdb.AllocationLength = AllocationLength;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_REQUEST_SENSE_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeReserve6Command(
    PSCSI_RESERVE6_COMMAND_STRUCTURE    Cdb,
    UINT8                               Control
){
    memset(Cdb, 0, sizeof(SCSI_RESERVE6_COMMAND_STRUCTURE));
    Cdb->OpCode = SCSI_COMMAND_RESERVE_CDB6;
    Cdb->Control = Control;
}

void 
ScsiCoreEncodeRezeroUnitCommand(
    PSCSI_REZERO_UNIT_COMMAND_STRUCTURE Cdb,
    UINT8                               Lun,
    UINT8                               Control
){
    memset(Cdb, 0, sizeof(SCSI_REZERO_UNIT_COMMAND_STRUCTURE));
    Cdb->OpCode = SCSI_COMMAND_REZERO_UNIT;
    Cdb->LunLbaMSB = (Lun << 5);
    Cdb->Control = Control;
}

void 
ScsiCoreEncodeSeekCommand(
    PSCSI_SEEK_COMMAND_STRUCTURE    Cdb,
    UINT8                           Lun,
    UINT32                          Lba,
    UINT8                           Control
){
    SCSI_SEEK_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_SEEK_CDB6;
    tCdb.LunLbaMsb = ((Lun << 6) | ((Lba >> 16) & 0x1F));
    tCdb.Lba = ScsiCoreEncodeUint16((UINT16)(Lba & UINT16_MAX));
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_SEEK_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeTestUnitReadyCommand(
    PSCSI_TEST_UNIT_READY_COMMAND_STRUCTURE Cdb,
    UINT8                                   Control
){
    memset(Cdb, 0, sizeof(SCSI_TEST_UNIT_READY_COMMAND_STRUCTURE));
    Cdb->OpCode = SCSI_COMMAND_TEST_UNIT_READY;
    Cdb->Control = Control;
}