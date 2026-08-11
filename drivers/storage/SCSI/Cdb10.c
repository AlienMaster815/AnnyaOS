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

