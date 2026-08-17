#include "../ScsiCore.h"

void ScsiCoreEncodeCdb16Command(
    PSCSI_CDB16_COMMAND Cdb,
    UINT8               OpCode,
    UINT64              Lba,
    UINT32              TpaLength,
    UINT8               Mci,
    UINT8               Control
){
    SCSI_CDB16_COMMAND tCdb = {0};
    tCdb.OpCode = OpCode;
    tCdb.Lba = ScsiCoreEncodeUint64(Lba);
    tCdb.TpaLength = ScsiCoreEncodeUint32(TpaLength); 
    tCdb.Mci = Mci;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_CDB16_COMMAND));
}

void 
ScsiCoreEncodeBackgroundControlCommand(
    PSCSI_BACKGROUND_CONTROL_COMMAND_STRUCTURE  Cdb,
    UINT8                                       BoControl,
    UINT8                                       BoTime,
    UINT8                                       Control 
){
    SCSI_BACKGROUND_CONTROL_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_BACKGROUND_CONTROL;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_BACKGROUND_CONTROL;
    tCdb.BoControl = BoControl;
    tCdb.BoTime = BoTime;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_SERVICE_ACTION_BACKGROUND_CONTROL));
}

void ScsiCoreEncodeGetLbaStatusCommand(
    PSCSI_GET_LBA_STATUS_COMMAND_STRUCTURE  Cdb,
    UINT64                                  StartingLba,
    UINT32                                  AllocationLength,
    UINT8                                   Reserved,
    UINT8                                   Control
){
    SCSI_GET_LBA_STATUS_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_GET_LBA_STATUS;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_GET_LBA_STATUS;
    tCdb.StartingLba = ScsiCoreEncodeUint64(StartingLba);
    tCdb.AllocationLength = ScsiCoreEncodeUint32(AllocationLength);
    tCdb.Reserved = Reserved;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_GET_LBA_STATUS_COMMAND_STRUCTURE));
}

void ScsiCoreEncodeGetStreamStatusCommand(
    PSCSI_GET_STREAM_STATUS_COMMAND_STRUCTURE   Cdb,
    UINT16                                      StartingStreamID,
    UINT32                                      AllocationLength,
    UINT8                                       Control
){
    SCSI_GET_STREAM_STATUS_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_GET_STREAM_STATUS;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_GET_STREAM_STATUS;
    tCdb.StartingStreamID = ScsiCoreEncodeUint16(StartingStreamID);
    tCdb.AllocationLength = ScsiCoreEncodeUint32(AllocationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_GET_STREAM_STATUS_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeRead16Command(
    PSCSI_READ16_COMMAND_STRUCTURE  Cdb,
    UINT8                           Dld2,
    UINT8                           Rarc,
    UINT8                           Fua,
    UINT8                           Dpo,
    UINT8                           RdProtect,
    UINT64                          Lba,
    UINT32                          TransferLength,
    UINT8                           GroupNumber,
    UINT8                           Dld0,
    UINT8                           Dld1,
    UINT8                           Control
){
    SCSI_READ16_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_READ_CDB16;
    tCdb.Dld2RarcFuaDpoRdprotect = ((Dld2) | (Rarc << 2) | (Fua << 3) | (Dpo << 4) | (RdProtect << 5));
    tCdb.Lba = ScsiCoreEncodeUint64(Lba);
    tCdb.TransferLength = ScsiCoreEncodeUint32(TransferLength);
    tCdb.GroupNumberDld0Dld1 = (GroupNumber | (Dld0 << 6) | (Dld1 << 7));
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ16_COMMAND_STRUCTURE));
}   

void 
ScsiCoreEncodeReadBuffer16Command(
    PSCSI_READ_BUFFER16_COMMAND_STRUCTURE   Cdb,
    UINT8                                   Mode,
    UINT8                                   ModeSpecific,
    UINT64                                  BufferOffset,
    UINT32                                  AllocationLength,
    UINT8                                   BufferId,
    UINT8                                   Control
){
    SCSI_READ_BUFFER16_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_READ_BUFFER_CDB16;
    tCdb.ModeModeSpecific = (Mode | (ModeSpecific << 5)); 
    tCdb.BufferOffset = ScsiCoreEncodeUint64(BufferOffset);
    tCdb.AllocationLength = ScsiCoreEncodeUint32(AllocationLength);
    tCdb.BufferId = BufferId;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ_BUFFER16_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeReadCapacity16Command(
    PSCSI_READ_CAPACITY16_COMMAND_STRUCTURE Cdb,
    UINT64                                  Lba,
    UINT32                                  AllocationLength,
    UINT8                                   Pmi,
    UINT8                                   Control
){
    SCSI_READ_CAPACITY16_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_READ_CAPACITY_CDB16;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_READ_CAPACITY_CDB16;
    tCdb.Lba = ScsiCoreEncodeUint64(Lba);
    tCdb.AllocationLength = ScsiCoreEncodeUint32(AllocationLength);
    tCdb.Pmi = Pmi;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ_CAPACITY16_COMMAND_STRUCTURE));
}

void
ScsiCoreEncodeReadLong16Command(
    PSCSI_READ_LONG16_COMMAND_STRUCTURE Cdb,
    UINT64                              Lba,
    UINT16                              Btl,
    UINT8                               Corrct,
    UINT8                               Pblock,
    UINT8                               Control
){
    SCSI_READ_LONG16_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_READ_LONG_CDB16;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_READ_LONG16;
    tCdb.Lba = ScsiCoreEncodeUint64(Lba);
    tCdb.Btl = ScsiCoreEncodeUint16(Btl);
    tCdb.CorrctPblock = (Corrct | (Pblock << 1));
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ_LONG16_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeStreamControlCommand(
    PSCSI_STREAM_CONTROL_COMMAND_STRUCTURE  Cdb,
    UINT8                                   StreamControl,
    UINT16                                  StreamID,
    UINT8                                   Control
){
    SCSI_STREAM_CONTROL_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_STREAM_CONTROL;
    tCdb.ServiceActionStrCtl = (SCSI_SERVICE_ACTION_STREAM_CONTROL | (StreamControl << 5));
    tCdb.StrID = ScsiCoreEncodeUint16(StreamID);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_STREAM_CONTROL_COMMAND_STRUCTURE));
}

void ScsiCoreEncodeSynchronizeCache16Command(
    PSCSI_SYNCHRONIZE_CACHE16_COMMAND_STRUCTURE Cdb,
    UINT8                                       Immed,
    UINT64                                      Lba,
    UINT32                                      NumberOfBlocks,
    UINT8                                       GroupNumber,
    UINT8                                       Control
){
    SCSI_SYNCHRONIZE_CACHE16_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_SYNCHRONIZE_CACHE_CDB16;
    tCdb.Immed = Immed;
    tCdb.Lba = ScsiCoreEncodeUint64(Lba);
    tCdb.NumberOfBlocks = ScsiCoreEncodeUint32(NumberOfBlocks);
    tCdb.GroupNumber = GroupNumber;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_SYNCHRONIZE_CACHE16_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeVerify16Command(
    PSCSI_VERIFY16_COMMAND_STRUCTURE    Cdb,
    UINT8                               ByteCheck,
    UINT8                               Dpo,
    UINT8                               VrProctect,
    UINT64                              Lba,
    UINT32                              VerificationLength,
    UINT8                               GroupNumber,
    UINT8                               Control
){
    SCSI_VERIFY16_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_VERIFY_CDB16;
    tCdb.BytChkDpoVrProtect = ((ByteCheck << 1) | (Dpo << 4) | (VrProctect << 5));
    tCdb.Lba = ScsiCoreEncodeUint64(Lba);
    tCdb.VerificationLength = ScsiCoreEncodeUint32(VerificationLength);
    tCdb.GroupNumber = GroupNumber;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_VERIFY16_COMMAND_STRUCTURE));
}