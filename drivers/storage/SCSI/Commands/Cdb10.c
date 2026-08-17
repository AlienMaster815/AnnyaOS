#include "../ScsiCore.h"

void ScsiCoreEncodeCdb10Command(
    PSCSI_CDB10_COMMAND Cdb,
    UINT8               OpCode,
    UINT8               ServiceActionMci,
    UINT32              Lba,
    UINT8               Mci,
    UINT16              TpaLength,
    UINT8               Control
){
    SCSI_CDB10_COMMAND tCdb = {0};
    tCdb.OpCode = OpCode;
    tCdb.ServiceActionMci = ServiceActionMci;
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.Mci = Mci;
    tCdb.TpaLength = ScsiCoreEncodeUint16(TpaLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_CDB10_COMMAND));
}

void 
ScsiCoreEncodeChangeDefinitionCommand(
    PSCSI_CHANGE_DEFINITION_COMMAND_STRUCTURE   Cdb,
    UINT8                                       Save,
    UINT8                                       DefParam,
    UINT8                                       ParamLength,
    UINT8                                       Control
){
    SCSI_CHANGE_DEFINITION_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_CHANGE_DEFINITION;
    tCdb.Save = Save;
    tCdb.DefParam = DefParam;
    tCdb.ParamLength = ParamLength;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_CHANGE_DEFINITION_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeLogSelectCommand(
    PSCSI_LOG_SELECT_COMMAND_STRUCTURE  Cdb,
    UINT8                               Sp,
    UINT8                               Pcr,
    UINT8                               PageCode,
    UINT8                               Pc,
    UINT8                               SubPageCode,
    UINT16                              ParameterListLength,
    UINT8                               Control
){
    SCSI_LOG_SELECT_COMMAND_STRUCTURE tCdb = {0}; 
    tCdb.OpCode = SCSI_COMMAND_LOG_SELECT;
    tCdb.SpPcr = Sp | (Pcr << 1);
    tCdb.PageCodePc = PageCode | (Pc << 6); 
    tCdb.SubPageCode = SubPageCode;
    tCdb.ParameterListLength = ScsiCoreEncodeUint16(ParameterListLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_LOG_SELECT_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeLogSenseCommand(
    PSCSI_LOG_SENSE_COMMAND_STRUCTURE   Cdb,
    UINT8                               Sp,
    UINT8                               PageCode,
    UINT8                               Pc,
    UINT8                               SubPageCode,
    UINT16                              ParameterPointer,
    UINT16                              AllocationLength,
    UINT8                               Control
){
    SCSI_LOG_SENSE_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_LOG_SENSE;
    tCdb.Sp = Sp;
    tCdb.PageCodePc = PageCode | (Pc << 6);
    tCdb.SubPageCode = SubPageCode;
    tCdb.ParameterPointer = ScsiCoreEncodeUint16(ParameterPointer);
    tCdb.AllocationLength = ScsiCoreEncodeUint16(AllocationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_LOG_SENSE_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeModeSelect10Command(
    PSCSI_MODE_SELECT10_COMMAND_STRUCTURE   Cdb,
    UINT8                                   Sp,
    UINT8                                   Pf,
    UINT16                                  ParameterListLength,
    UINT8                                   Control
){
    SCSI_MODE_SELECT10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_MODE_SELECT_CDB10;
    tCdb.SpPf = Sp | (Pf << 4);
    tCdb.ParameterListLength = ScsiCoreEncodeUint16(ParameterListLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_MODE_SELECT10_COMMAND_STRUCTURE));
}

void ScsiCoreEncodeModeSense10Command(
    PSCSI_MODE_SENSE10_COMMAND_STRUCTURE    Cdb,
    UINT8                                   Dbd,
    UINT8                                   Llbaa,
    UINT8                                   PageCode,
    UINT8                                   Pc,
    UINT8                                   SubPageCode,
    UINT16                                  AllocationLength,
    UINT8                                   Control
){
    SCSI_MODE_SENSE10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_MODE_SENCE_CDB10;
    tCdb.DbdLlbaa = ((Dbd << 3) | (Llbaa << 4));
    tCdb.PageCodePc = PageCode | (Pc << 6);
    tCdb.SubPageCode = SubPageCode;
    tCdb.AllocationLength = ScsiCoreEncodeUint16(AllocationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_MODE_SENSE10_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodePersistentReserveInCommand(
    PSCSI_PERSISTENT_RESERVE_IN_COMMAND_STRUCTURE   Cdb,
    UINT8                                           ServiceAction,
    UINT16                                          AllocationLength,
    UINT8                                           Control
){
    SCSI_PERSISTENT_RESERVE_IN_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_PERSISTENT_RESERVE_IN;
    tCdb.ServiceAction = ServiceAction;
    tCdb.AllocationLength = ScsiCoreEncodeUint16(AllocationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_PERSISTENT_RESERVE_IN_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodePersistentReserveOutCommand(
    PSCSI_PERSISTENT_RESERVE_OUT_COMMAND_STRUCTURE  Cdb,
    UINT8                                           ServiceAction,
    UINT8                                           Type,
    UINT8                                           Scope,
    UINT32                                          ParameterListLength,
    UINT8                                           Control
){
    SCSI_PERSISTENT_RESERVE_OUT_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_PERSISTENT_RESERVE_OUT;
    tCdb.ServiceAction = ServiceAction;
    tCdb.TypeScope = Type | (Scope << 4);
    tCdb.ParameterListLength = ScsiCoreEncodeUint32(ParameterListLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_PERSISTENT_RESERVE_OUT_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeRead10Command(
    PSCSI_READ10_COMMAND_STRUCTURE  Cdb,
    UINT8                           Rarc,
    UINT8                           Fua,
    UINT8                           Dpo,
    UINT8                           RdProtect,
    UINT32                          Lba,
    UINT8                           GroupNumber,
    UINT16                          TransferLength,
    UINT8                           Control
){
    SCSI_READ10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_READ_CDB10;
    tCdb.RarcFuaDpoRdprotect = ((Rarc << 2) | (Fua << 3) | (Dpo << 4) | (RdProtect << 5));
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.GroupNumber = GroupNumber;
    tCdb.TransferLength = ScsiCoreEncodeUint16(TransferLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ10_COMMAND_STRUCTURE));
}

void
ScsiCoreEncodeReadBuffer10Command(
    PSCSI_READ_BUFFER10_COMMAND_STRUCTURE   Cdb,
    UINT8                                   Mode,
    UINT8                                   ModeSpecific,
    UINT8                                   BufferId,
    UINT32                                  BufferOffset,
    UINT32                                  AllocationLength,
    UINT8                                   Control
){
    SCSI_READ_BUFFER10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_READ_BUFFER_CDB10;
    tCdb.ModeModeSpecific = (Mode | (ModeSpecific << 5));
    tCdb.BufferId = BufferId;
    tCdb.BufferOffset[0] = (BufferOffset >> 16) & 0xFF;
    tCdb.BufferOffset[1] = (BufferOffset >> 8) & 0xFF;
    tCdb.BufferOffset[2] =  BufferOffset & 0xFF;
    tCdb.AllocationLength[0] = (AllocationLength >> 16) & 0xFF;
    tCdb.AllocationLength[1] = (AllocationLength >> 8) & 0xFF;
    tCdb.AllocationLength[2] =  AllocationLength & 0xFF;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ_BUFFER10_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeReadCapacity10Command(
    PSCSI_READ_CAPACITY10_COMMAND_STRUCTURE Cdb,
    UINT32                                  Lba,
    UINT8                                   Pmi,
    UINT8                                   Control
){
    SCSI_READ_CAPACITY10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.Pmi = Pmi;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ_CAPACITY10_COMMAND_STRUCTURE));
}


void 
ScsiCoreEncodeReadDefectData10Command(
    PSCSI_READ_DEFECT_DATA10_COMMAND_STRUCTURE  Cdb,
    UINT8                                       DefectListFormat,
    UINT8                                       ReqGlist,
    UINT8                                       ReqPlist,
    UINT16                                      AllocationLength,
    UINT8                                       Control
){
    SCSI_READ_DEFECT_DATA10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_READ_DEFECT_DATA_CDB10;
    tCdb.DlfReqGListPList = (DefectListFormat | (ReqGlist << 3) | (ReqPlist));
    tCdb.AllocationLength = ScsiCoreEncodeUint16(AllocationLength);
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ_DEFECT_DATA10_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeReadLong10Command(
    PSCSI_READ_LONG10_COMMAND_STRUCTURE Cdb,
    UINT8                               Corrct,
    UINT8                               Pblock,
    UINT32                              Lba,
    UINT8                               Btl,
    UINT8                               Control
){
    SCSI_READ_LONG10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_READ_LONG_CDB10;
    tCdb.CorrctPblock = ((Corrct << 1) | (Pblock << 2));
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.Btl = ScsiCoreEncodeUint16(Btl);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ_LONG10_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeRelease10Command(
    PSCSI_RELEASE10_COMMAND_STRUCTURE   Cdb,
    UINT8                               LongId,
    UINT8                               ThirdParty,
    UINT8                               ThirdPartyDevID,
    UINT16                              ParameterListLength,
    UINT8                               Control
){
    SCSI_RELEASE10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_RELEASE_CDB10;
    tCdb.LongID3rdParty = (LongId | (ThirdParty << 4));
    tCdb.ThirdPartyDevID = ThirdPartyDevID;
    tCdb.ParameterListLength = ScsiCoreEncodeUint16(ParameterListLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_RELEASE10_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeReportLunsCommandStructure(
    PSCSI_REPORT_LUNS_COMMAND_STRUCTURE Cdb,
    UINT8                               SelectReport,
    UINT32                              AllocationLength,
    UINT8                               Control
){
    SCSI_REPORT_LUNS_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_REPORT_LUNS;
    tCdb.SelectReport = SelectReport;
    tCdb.AllocationLength = ScsiCoreEncodeUint32(AllocationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_REPORT_LUNS_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeReportSupportedTaskManagementFunctionsCommand(
    PSCSI_REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS_COMMAND_STRUCTURE  Cdb,
    UINT8                                                               Repd,
    UINT32                                                              AllocationLength,
    UINT8                                                               Control
){
    SCSI_REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_REPORT_SUPPORTED_TASKMNG;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_REPORT_SUPPORTED_TASKMNG;
    tCdb.Repd = Repd << 7;
    tCdb.AllocationLength = ScsiCoreEncodeUint32(AllocationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeReserve10Command(
    PSCSI_RESERVE10_COMMAND_STRUCTURE   Cdb,
    UINT8                               LongId,
    UINT8                               ThirdParty,
    UINT8                               ThirdPartyDevID,
    UINT16                              ParameterListLength,
    UINT8                               Control
){
    SCSI_RESERVE10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_RESERVE_CDB10;
    tCdb.LongId3rdParty = ((LongId << 1) | (ThirdParty << 4));
    tCdb.ThirdPartyDevID = ThirdPartyDevID;
    tCdb.ParameterListLength = ScsiCoreEncodeUint16(ParameterListLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_RESERVE10_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeSanatizeCommand(
    PSCSI_SANITIZE_COMMAND_STRUCTURE    Cdb,
    UINT8                               ServiceAction,
    UINT8                               Ause,
    UINT8                               Znr,
    UINT8                               Immed,
    UINT16                              ParameterListLength,
    UINT8                               Control
){
    SCSI_SANITIZE_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_SANITIZE;
    tCdb.ServiceActionAuseZnrImmed = (ServiceAction | (Ause << 5) | (Znr << 6) | (Immed << 7));
    tCdb.ParameterListLength = ScsiCoreEncodeUint16(ParameterListLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_SANITIZE_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeSeekExtendedCommand(
    PSCSI_SEEK_EX_COMMAND_STRUCTURE   Cdb,
    UINT8                             Lun,
    UINT32                            Lba,
    UINT8                             Control
){
    SCSI_SEEK_EX_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_SEEK_EXTENDED_CDB10;
    tCdb.Lun = Lun;
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_SEEK_EX_COMMAND_STRUCTURE));
}

void ScsiCoreEncodeSynchronizeCache10Command(
    PSCSI_SYNCHRONIZE_CACHE10_COMMAND_STRUCTURE Cdb,
    UINT8                                       Immed,
    UINT32                                      Lba,
    UINT8                                       GroupNumber,
    UINT16                                      NumberOfBlocks,
    UINT8                                       Control
){
    SCSI_SYNCHRONIZE_CACHE10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_SYNCHRONIZE_CACHE_CDB10;
    tCdb.Immed = Immed;
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.GroupNumber = GroupNumber;
    tCdb.NumberOfBlocks = ScsiCoreEncodeUint16(NumberOfBlocks);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_SYNCHRONIZE_CACHE10_COMMAND_STRUCTURE));
}

void
ScsiCoreEncodeUnmapCommand(
    PSCSI_UNMAP_COMMAND_STRUCTURE   Cdb,
    UINT8                           Anchor,
    UINT8                           GroupNumber,
    UINT16                          ParameterListLength,
    UINT8                           Control
){
    SCSI_UNMAP_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_UNMAP;
    tCdb.Anchor = Anchor;
    tCdb.GroupNumber = GroupNumber;
    tCdb.ParameterListLength = ScsiCoreEncodeUint16(ParameterListLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_UNMAP_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeVerify10Command(
    PSCSI_VERIFY10_COMMAND_STRUCTURE    Cdb,
    UINT8                               ByteCheck,
    UINT8                               Dpo,
    UINT8                               VrProctect,
    UINT32                              Lba,
    UINT8                               GroupNumber,
    UINT16                              VerificationLength,
    UINT8                               Control
){
    SCSI_VERIFY10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_VERIFY_CDB10;
    tCdb.BytChkDpoVrProtect = ((ByteCheck << 1) | (Dpo << 4) | (VrProctect << 5));
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.GroupNumber = GroupNumber;
    tCdb.VerificationLength = ScsiCoreEncodeUint16(VerificationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_VERIFY10_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeWrite10Command(
    PSCSI_WRITE10_COMMAND_STRUCTURE Cdb,
    UINT8                           Fua,
    UINT8                           Dpo,
    UINT8                           WrProtect,
    UINT32                          Lba,
    UINT8                           GroupNumber,
    UINT16                          TransferLength,
    UINT8                           Control
){
    SCSI_WRITE10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_WRITE_CDB10;
    tCdb.FuaDpoWrProtect = ((Fua << 3) | (Dpo << 4) | (WrProtect << 5));
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.GroupNumber = GroupNumber;
    tCdb.TransferLength = ScsiCoreEncodeUint16(TransferLength);
    tCdb.Control = Control; 
    memcpy(Cdb, &tCdb, sizeof(SCSI_WRITE10_COMMAND_STRUCTURE));
}

void ScsiCoreEncodeWriteAndVerify10Command(
    PSCSI_WRITE_AND_VERIFY10_COMMAND_STRUCTURE  Cdb,
    UINT8                                       ByteCheck,
    UINT8                                       Dpo,
    UINT8                                       WrProtect,
    UINT32                                      Lba,
    UINT8                                       GroupNumber,
    UINT16                                      TransferLength,
    UINT8                                       Control
){
    SCSI_WRITE_AND_VERIFY10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_WRITE_AND_VERIFY_CDB10;
    tCdb.BytChkDpoWrProtect = ((ByteCheck << 1) | (Dpo << 4) | (WrProtect << 5));
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.GroupNumber = GroupNumber;
    tCdb.TransferLength = ScsiCoreEncodeUint16(TransferLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_WRITE_AND_VERIFY10_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeWriteBufferCommand(
    PSCSI_WRITE_BUFFER_COMMAND_STRUCTURE    Cdb,
    UINT8                                   Mode,
    UINT8                                   ModeSpecific,
    UINT8                                   BufferId,
    UINT32                                  BufferOffset,
    UINT32                                  ParameterListLength,
    UINT8                                   Control 
){
    SCSI_WRITE_BUFFER_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_WRITE_BUFFER;
    tCdb.ModeModeSpecific = (Mode | (ModeSpecific << 5));
    tCdb.BufferId = BufferId;
    tCdb.BufferOffset[0] = (BufferOffset >> 16) & 0xFF;
    tCdb.BufferOffset[1] = (BufferOffset >> 8) & 0xFF;
    tCdb.BufferOffset[2] =  BufferOffset & 0xFF;
    tCdb.ParameterListLength[0] = (ParameterListLength >> 16) & 0xFF;
    tCdb.ParameterListLength[1] = (ParameterListLength >> 8) & 0xFF;
    tCdb.ParameterListLength[2] =  ParameterListLength & 0xFF;
    tCdb.Control = Control;
}

void 
ScsiCoreEncodeWriteLong10Command(
    PSCSI_WRITE_LONG10_COMMAND_STRUCTURE    Cdb,
    UINT8                                   WrUncor,
    UINT32                                  Lba,
    UINT16                                  TransferLength,
    UINT8                                   Control
){
    SCSI_WRITE_LONG10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_WRITE_LONG;
    tCdb.WrUncor = WrUncor << 6;
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.TransferLength = ScsiCoreEncodeUint16(TransferLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_WRITE_LONG10_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeWriteSame10Command(
    PSCSI_WRITE_SAME10_COMMAND_STRUCTURE    Cdb,
    UINT8                                   UnMap,
    UINT8                                   Anchor,
    UINT8                                   WrProtect,
    UINT32                                  Lba,
    UINT8                                   GroupNumber,
    UINT16                                  NumberOfBlocks,
    UINT8                                   Control
){
    SCSI_WRITE_SAME10_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_WRITE_SAME_CDB10;
    tCdb.UnMapAnchorWrProtect = ((UnMap << 3) | (Anchor << 4) | (WrProtect << 5));
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.GroupNumber = GroupNumber;
    tCdb.NumberOfBlocks = NumberOfBlocks;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_WRITE_SAME10_COMMAND_STRUCTURE));
}