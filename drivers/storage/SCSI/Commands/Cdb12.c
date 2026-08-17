#include "../ScsiCore.h"

void ScsiCoreEncodeCdb12Command(
    PSCSI_CDB12_COMMAND Cdb,
    UINT8               OpCode,
    UINT8               ServiceActionMci,
    UINT32              Lba,
    UINT32              TpaLength,
    UINT8               Mci,
    UINT8               Control
){
    SCSI_CDB12_COMMAND tCdb = {0};
    tCdb.OpCode = OpCode;
    tCdb.ServiceActionMci = ServiceActionMci;
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.TpaLength = ScsiCoreEncodeUint32(TpaLength);
    tCdb.Mci = Mci;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_CDB12_COMMAND));
}

void ScsiCoreEncodeRead12Command(
    PSCSI_READ12_COMMAND_STRUCTURE  Cdb,
    UINT8                           Rarc,
    UINT8                           Fua,
    UINT16                          Dpo,
    UINT8                           RdProtect,
    UINT32                          Lba,
    UINT32                          TransferLength,
    UINT8                           GroupNumber,
    UINT8                           Control
){
    SCSI_READ12_COMMAND_STRUCTURE tCdb = {0};
    tCdb.RarcFuaDpoRdprotect = ((Rarc << 2) | (Fua << 3) | (Dpo << 4) | (RdProtect << 5));
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.TransferLength = ScsiCoreEncodeUint32(TransferLength); 
    tCdb.GroupNumberMmc6 = GroupNumber;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ12_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeReadDefectData12Command(
    PSCSI_READ_DEFECT_DATA12_COMMAND_STRUCTURE  Cdb,
    UINT8                                       DefectListFormat,
    UINT8                                       ReqGList,
    UINT8                                       ReqPList,
    UINT32                                      Adi,
    UINT32                                      AllocationLength,
    UINT8                                       Control
){
    SCSI_READ_DEFECT_DATA12_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_READ_DEFECT_DATA_CDB12;
    tCdb.DlfReqGListPList = (DefectListFormat | (ReqGList << 3) | (ReqPList << 4));
    tCdb.Adi = ScsiCoreEncodeUint32(Adi);
    tCdb.AllocationLength = ScsiCoreEncodeUint32(AllocationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_READ_DEFECT_DATA12_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeReportIdentifyingInformationCommand(
    PSCSI_REPORT_IDENTIFYING_INFORMATION_COMMAND_STRUCTURE  Cdb,
    UINT16                                                  Restricted,
    UINT32                                                  AllocationLength,
    UINT8                                                   InformationType,
    UINT8                                                   Control
){
    SCSI_REPORT_IDENTIFYING_INFORMATION_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_REPORT_IDENTIFYING_INFO;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_IDENTIFYING_INFORMATION;
    tCdb.Restricted = ScsiCoreEncodeUint16(Restricted);
    tCdb.AllocationLength = ScsiCoreEncodeUint32(AllocationLength);
    tCdb.InformationType = InformationType;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_REPORT_IDENTIFYING_INFORMATION_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeReportSupportedOperationCodesCommand(
    PSCSI_REPORT_SUPPORTED_OPERATION_CODES  Cdb,
    UINT8                                   ReportingOptions,
    UINT8                                   Rctd,
    UINT8                                   RequestedOperationCode,
    UINT16                                  RequestedServiceAction,
    UINT32                                  AllocationLength,
    UINT8                                   Control
){
    SCSI_REPORT_SUPPORTED_OPERATION_CODES tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_REPORT_SUPPORTED_OPCODES;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_REPORT_SUPPORTED_OPCODES;
    tCdb.ReportingOptionsRctd = (ReportingOptions | (Rctd << 7));
    tCdb.RequestedOperationCode = RequestedOperationCode; 
    tCdb.RequestedServiceAction = ScsiCoreEncodeUint16(RequestedServiceAction);
    tCdb.AllocationLength = ScsiCoreEncodeUint32(AllocationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_REPORT_SUPPORTED_OPERATION_CODES));
}

void
ScsiCoreEncodeReportTimeStampCommand(
    PSCSI_REPORT_TIMESTAMP_COMMAND_STRUCTURE    Cdb,
    UINT32                                      AllocationLength,
    UINT8                                       Control
){
    SCSI_REPORT_TIMESTAMP_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_REPORT_TIMESTAMP;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_REPORT_TIMESTAMP;
    tCdb.AllocationLength = ScsiCoreEncodeUint32(AllocationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_REPORT_TIMESTAMP_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeSecurityProtocolInCommand(
    PSCSI_SECURITY_PROTOCOL_IN_COMMAND_STRUCTURE    Cdb,
    UINT8                                           SecurityProtocol,
    UINT16                                          SecurityProtocolSpecific,
    UINT8                                           Inc512,
    UINT32                                          AllocationLength,
    UINT8                                           Control
){
    SCSI_SECURITY_PROTOCOL_IN_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_SECURITY_PROTOCOL_IN;
    tCdb.SecurityProtocol = SecurityProtocol;
    tCdb.SecurityProtocolSpecific = ScsiCoreEncodeUint16(SecurityProtocolSpecific);
    tCdb.Inc512 = (Inc512 << 7);
    tCdb.AllocationLength = ScsiCoreEncodeUint32(AllocationLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_SECURITY_PROTOCOL_IN_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeSecurityProtocolOutCommand(
    PSCSI_SECURITY_PROTOCOL_OUT_COMMAND_STRUCTURE   Cdb,
    UINT8                                           SecurityProtocol,
    UINT16                                          SecurityProtocolSpecific,
    UINT8                                           Inc512,
    UINT32                                          TransferLength,
    UINT8                                           Control
){
    SCSI_SECURITY_PROTOCOL_OUT_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_SECURITY_PROTOCOL_IN;
    tCdb.SecurityProtocol = SecurityProtocol;
    tCdb.SecurityProtocolSpecific = ScsiCoreEncodeUint16(SecurityProtocolSpecific);
    tCdb.Inc512 = (Inc512 << 7);
    tCdb.TransferLength = ScsiCoreEncodeUint32(TransferLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_SECURITY_PROTOCOL_OUT_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeSetIdentifyingInformationCommand(
    PSCSI_SET_IDENTIFYING_INFORMATION_COMMAND_STRUCTURE Cdb,
    UINT32                                              ParameterListLength,
    UINT8                                               InformationType,
    UINT8                                               Control
){
    SCSI_SET_IDENTIFYING_INFORMATION_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_SET_IDENTIFYING_INFO;    
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_SET_IDENTIFYING_INFORMATION;
    tCdb.ParameterListLength = ScsiCoreEncodeUint32(ParameterListLength);
    tCdb.InformationType = InformationType;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_SET_IDENTIFYING_INFORMATION_COMMAND_STRUCTURE)); 
}

void 
ScsiCoreEncodeSetTimeStampCommand(
    PSCSI_SET_TIMESTAMP_COMMAND_STRUCTURE   Cdb,
    UINT32                                  ParameterListLength,
    UINT8                                   Control
){  
    SCSI_SET_TIMESTAMP_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_SET_TIMESTAMP;
    tCdb.ServiceAction = SCSI_SERVICE_ACTION_SET_TIMESTAMP;
    tCdb.ParameterListLength = ScsiCoreEncodeUint32(ParameterListLength);
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_SET_TIMESTAMP_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeStartStopUnitCommand(
    PSCSI_START_STOP_UNIT_COMMAND_STRUCTURE Cdb,
    UINT8                                   Immed,
    UINT8                                   Pcm,
    UINT8                                   Start,
    UINT8                                   Loej,
    UINT8                                   NoFlush,
    UINT8                                   PowerCondition,
    UINT8                                   Control
){
    SCSI_START_STOP_UNIT_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_START_STOP_UNIT;
    tCdb.Immed = Immed;
    tCdb.Pcm = Pcm;
    tCdb.StartLoejNoFlushPc = (Start | (Loej << 1) | (NoFlush << 2) | (PowerCondition << 4));
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_START_STOP_UNIT_COMMAND_STRUCTURE));
}

void 
ScsiCoreEncodeVerify12Command(
    PSCSI_VERIFY12_COMMAND_STRUCTURE    Cdb,
    UINT8                               ByteCheck,
    UINT8                               Dpo,
    UINT8                               VrProctect,
    UINT32                              Lba,
    UINT32                              VerificationLength,
    UINT8                               GroupNumber,
    UINT8                               Control
){
    SCSI_VERIFY12_COMMAND_STRUCTURE tCdb = {0};
    tCdb.OpCode = SCSI_COMMAND_VERIFY_CDB12;
    tCdb.BytChkDpoVrProtect = ((ByteCheck << 1) | (Dpo << 4) | (VrProctect << 5));
    tCdb.Lba = ScsiCoreEncodeUint32(Lba);
    tCdb.VerificationLength = ScsiCoreEncodeUint32(VerificationLength);
    tCdb.GroupNumber = GroupNumber;
    tCdb.Control = Control;
    memcpy(Cdb, &tCdb, sizeof(SCSI_VERIFY12_COMMAND_STRUCTURE));
}