#include "ScsiCore.h"

void ScsiCoreEncodeCdb16Command(
    PSCSI_CDB16_COMMAND Cdb,
    UINT8               OpCode,
    UINT64              Lba,
    UINT32              TpaLength,
    UINT8               Mci,
    UINT8               Control
){
    UINT64 Tmp64;
    UINT32 Tmp32;
    SCSI_CDB16_COMMAND tCdb = {0};
    tCdb.OpCode = OpCode;
    LouKeSwapEndianess(&Lba , &Tmp64, sizeof(UINT64));
    tCdb.Lba = Lba;
    LouKeSwapEndianess(&TpaLength , &Tmp32, sizeof(UINT32));
    tCdb.TpaLength = TpaLength;
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
    UINT64 Tmp64;
    UINT32 Tmp32;
    SCSI_GET_LBA_STATUS_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_GET_LBA_STATUS;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_GET_LBA_STATUS;
    LouKeSwapEndianess(&StartingLba, &Tmp64, sizeof(UINT64));
    tCdb.StartingLba = Tmp64;
    LouKeSwapEndianess(&AllocationLength, &Tmp32, sizeof(UINT32));
    tCdb.AllocationLength  = Tmp32;
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
    UINT16 Tmp16;
    UINT32 Tmp32;
    SCSI_GET_STREAM_STATUS_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_GET_STREAM_STATUS;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_GET_STREAM_STATUS;
    LouKeSwapEndianess(&StartingStreamID, &Tmp16, sizeof(UINT16));
    tCdb.StartingStreamID = Tmp16;
    LouKeSwapEndianess(&AllocationLength, &Tmp32, sizeof(UINT32));
    tCdb.AllocationLength = Tmp32;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_GET_STREAM_STATUS_COMMAND_STRUCTURE));
}