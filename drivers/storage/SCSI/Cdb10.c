#include "ScsiCore.h"

void ScsiCoreEncodeCdb10Command(
    PSCSI_CDB10_COMMAND Cdb,
    UINT8               OpCode,
    UINT8               ServiceActionMci,
    UINT32              Lba,
    UINT8               Mci,
    UINT16              TpaLength,
    UINT8               Control
){
    UINT32 Tmp32;
    UINT16 Tmp16;
    SCSI_CDB10_COMMAND tCdb = {0};
    tCdb.OpCode = OpCode;
    tCdb.ServiceActionMci = ServiceActionMci;
    LouKeSwapEndianess(&Lba, &Tmp32, sizeof(UINT32));
    tCdb.Lba = Tmp32;
    tCdb.Mci = Mci;
    LouKeSwapEndianess(&TpaLength, &Tmp16, sizeof(UINT16));
    tCdb.TpaLength = Tmp16;
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
    UINT16 Tmp16;
    tCdb.OpCode = SCSI_COMMAND_LOG_SELECT;
    tCdb.SpPcr = Sp | (Pcr << 1);
    tCdb.PageCodePc = PageCode | (Pc << 6); 
    tCdb.SubPageCode = SubPageCode;
    LouKeSwapEndianess(&ParameterListLength, &Tmp16, sizeof(UINT16));
    tCdb.ParameterListLength = Tmp16;
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
    UINT16 Tmp16;
    tCdb.OpCode = SCSI_COMMAND_LOG_SENSE;
    tCdb.Sp = Sp;
    tCdb.PageCodePc = PageCode | (Pc << 6);
    tCdb.SubPageCode = SubPageCode;
    LouKeSwapEndianess(&ParameterPointer, &Tmp16, sizeof(UINT16));
    tCdb.ParameterPointer = Tmp16;
    LouKeSwapEndianess(&AllocationLength, &Tmp16, sizeof(UINT16));
    tCdb.AllocationLength = Tmp16;
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
    UINT16 Tmp16;
    tCdb.OpCode = SCSI_COMMAND_MODE_SELECT_CDB10;
    tCdb.SpPf = Sp | (Pf << 4);
    LouKeSwapEndianess(&ParameterListLength, &Tmp16, sizeof(UINT16));
    tCdb.ParameterListLength = Tmp16;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_MODE_SELECT10_COMMAND_STRUCTURE));
}

