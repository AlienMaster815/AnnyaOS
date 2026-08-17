#ifndef _SCSI_CORE_H
#define _SCSI_CORE_H

#include <LouDDK.h>

typedef struct _SCSI_INTERNAL_HOST_DEVICE_OBJECT{
    struct _SCSI_HOST_DEVICE_DRIVER_OBJECT*     DriverObject;
    ListHeader                                  HostDeviceList;
    UINT64                                      HostXaID;
    mutex_t                                     DeviceListLock;
    XARRAY                                      DeviceArray;
    ListHeader                                  DeviceList;
    PDEVICE_OBJECT                              LdmDevice;
    SCSI_HOST_DEVICE_OBJECT                     ScsiHostDevice;
}SCSI_INTERNAL_HOST_DEVICE_OBJECT, * PSCSI_INTERNAL_HOST_DEVICE_OBJECT;


typedef struct _SCSI_INTERNAL_HOST_DEVICE_DRIVER_OBJECT{
    ListHeader                      DriverList;
    UINT64                          DriverXaID;
    mutex_t                         HostDeviceListLock;
    XARRAY                          HostDeviceArray;
    ListHeader                      HostDeviceList;
    SIZE                            PrivateDataSize;
    SIZE                            PrivateDataAlignment;
    PSCSI_HOST_DEVICE_DRIVER_OBJECT DriverObject;
}SCSI_INTERNAL_HOST_DEVICE_DRIVER_OBJECT, * PSCSI_INTERNAL_HOST_DEVICE_DRIVER_OBJECT;

LOUSTATUS ScsiCoreGetInfoSenceDataInformation(PSSDD_INFO_STRUCTURE SenceData, UINT64* Out);
LOUSTATUS ScsiCoreGetCommandSpecificInfoSenceDataInformation(PSSDD_COMMAND_SPECIFIC_INFO_STRUCTURE SenceData, UINT64* Out);
LOUSTATUS ScsiCoreEncodeOpCode(UINT8* Out, UINT8 CommandCode, UINT8 GroupCode);
LOUSTATUS ScsiCoreEncodeControl(UINT8* Out, UINT8 VendorSpecific, UINT8 Reserved, UINT8 Naca, UINT8 Obsolete1, UINT8 Obsolete0);
void ScsiCoreEncodeCdb6Command(PSCSI_CDB6_COMMAND Cdb, UINT8 OpCode, UINT8 MsbMci, UINT16 Lba, UINT8 TpaLength, UINT8 Control);
void ScsiCoreEncodeCdb10Command(PSCSI_CDB10_COMMAND Cdb, UINT8 OpCode, UINT8 ServiceActionMci, UINT32 Lba, UINT8 Mci, UINT16 TpaLength, UINT8 Control);
void ScsiCoreEncodeCdb12Command(PSCSI_CDB12_COMMAND Cdb, UINT8 OpCode, UINT8 ServiceActionMci, UINT32 Lba, UINT32 TpaLength, UINT8 Mci, UINT8 Control);
void ScsiCoreEncodeCdb16Command(PSCSI_CDB16_COMMAND Cdb, UINT8 OpCode, UINT64 Lba, UINT32 TpaLength, UINT8 Mci, UINT8 Control);
void ScsiCoreEncodeLongLbaCdbVar(PSCSI_LONG_LBA_CDBVAR_COMMAND Cdb, UINT8 Control, UINT8 Mci[5], UINT8 CdbAdditionalLength, UINT16 ServiceAction, UINT8 MciFuaDpoMci, UINT8 Mci2, UINT64 Lba, UINT64 Mci3, UINT32 TpaLength);
void ScsiCoreEncodeBackgroundControlCommand(PSCSI_BACKGROUND_CONTROL_COMMAND_STRUCTURE Cdb, UINT8 BoControl, UINT8 BoTime, UINT8 Control);
void ScsiCoreEncodeChangeDefinitionCommand(PSCSI_CHANGE_DEFINITION_COMMAND_STRUCTURE Cdb, UINT8 Save, UINT8 DefParam, UINT8 ParamLength, UINT8 Control);
void ScsiCoreEncodeFormatUnitCommand(PSCSI_FORMAT_UNIT_COMMAND_STRUCTURE Cdb, UINT8 DefectListFormat, UINT8 CmpList, UINT8 FmtData, UINT8 LongList, UINT8 FmtpInfo, UINT8 VendorSpecific, UINT8 Ffmt, UINT8 Control);
void ScsiCoreEncodeGetLbaStatusCommand(PSCSI_GET_LBA_STATUS_COMMAND_STRUCTURE Cdb, UINT64 StartingLba, UINT32 AllocationLength, UINT8 Reserved, UINT8 Control);
void ScsiCoreEncodeGetStreamStatusCommand(PSCSI_GET_STREAM_STATUS_COMMAND_STRUCTURE Cdb, UINT16 StartingStreamID, UINT32 AllocationLength, UINT8 Control);
void ScsiCoreEncodeLogSelectCommand(PSCSI_LOG_SELECT_COMMAND_STRUCTURE Cdb, UINT8 Sp, UINT8 Pcr, UINT8 PageCode, UINT8 Pc, UINT8 SubPageCode, UINT16 ParameterListLength, UINT8 Control);
void ScsiCoreEncodeRead32Command(PSCSI_READ32_COMMAND_STRUCTURE Cdb, UINT8 Control, UINT8 GroupNumber, UINT16 ServiceAction, UINT8 Rarc, UINT8 Fua, UINT8 Dpo, UINT8 RdProtect, UINT64 Lba, UINT32 EilbrTag, UINT16 ElbaTag, UINT16 LbaTagMask, UINT32 TransferLength);
void ScsiCoreEncodeRead16Command(PSCSI_READ16_COMMAND_STRUCTURE Cdb, UINT8 Dld2, UINT8 Rarc, UINT8 Fua, UINT8 Dpo, UINT8 RdProtect, UINT64 Lba, UINT32 TransferLength, UINT8 GroupNumber, UINT8 Dld0, UINT8 Dld1, UINT8 Control);
void ScsiCoreEncodeRead12Command(PSCSI_READ12_COMMAND_STRUCTURE Cdb, UINT8 Rarc, UINT8 Fua, UINT16 Dpo, UINT8 RdProtect, UINT32 Lba, UINT32 TransferLength, UINT8 GroupNumber, UINT8 Control);
void ScsiCoreEncodeModeSense10Command(PSCSI_MODE_SENSE10_COMMAND_STRUCTURE Cdb, UINT8 Dbd, UINT8 Llbaa, UINT8 PageCode, UINT8 Pc, UINT8 SubPageCode, UINT16 AllocationLength, UINT8 Control);
void ScsiCoreEncodePersistentReserveInCommand(PSCSI_PERSISTENT_RESERVE_IN_COMMAND_STRUCTURE Cdb, UINT8 ServiceAction, UINT16 AllocationLength, UINT8 Control);
void ScsiCoreEncodePersistentReserveOutCommand(PSCSI_PERSISTENT_RESERVE_OUT_COMMAND_STRUCTURE Cdb, UINT8 ServiceAction, UINT8 Type, UINT8 Scope, UINT32 ParameterListLength, UINT8 Control);
void ScsiCoreEncodeRead10Command(PSCSI_READ10_COMMAND_STRUCTURE Cdb, UINT8 Rarc, UINT8 Fua, UINT8 Dpo, UINT8 RdProtect, UINT32 Lba, UINT8 GroupNumber, UINT16 TransferLength, UINT8 Control);
void ScsiCoreEncodeModeSense6Command(PSCSI_MODE_SENSE6_COMMAND_STRUCTURE Cdb, UINT8 Dbd, UINT8 PageCode, UINT8 Pc, UINT8 SubPageCode, UINT8 AllocationLength, UINT8 Control);
void ScsiCoreEncodeRead6Command(PSCSI_READ6_COMMAND_STRUCTURE Cdb, UINT32 Lba, UINT8 TransferLength, UINT8 Control);
void ScsiCoreEncodeReassignBlocksCommand(PSCSI_REASSIGN_BLOCKS_COMMAND_STRUCTURE Cdb, UINT8 LongList, UINT8 LongLba, UINT8 Control);
void ScsiCoreEncodeRecieveDiagnosticResultsCommand(PSCSI_RECIEVE_DIAGNOSTIC_RESULTS_COMMAND_STRUCTURE Cdb, UINT8 Pcv, UINT8 PageCode, UINT16 AllocationLength, UINT8 Control);
void ScsiCoreEncodeRequestSenseCommand(PSCSI_REQUEST_SENSE_COMMAND_STRUCTURE Cdb, UINT8 Desc, UINT8 AllocationLength, UINT8 Control);
void ScsiCoreEncodeReserve6Command(PSCSI_RESERVE6_COMMAND_STRUCTURE Cdb, UINT8 Control);
void ScsiCoreEncodeRezeroUnitCommand(PSCSI_REZERO_UNIT_COMMAND_STRUCTURE Cdb, UINT8 Lun, UINT8 Control);
void ScsiCoreEncodeSeekCommand(PSCSI_SEEK_COMMAND_STRUCTURE Cdb, UINT8 Lun, UINT32 Lba, UINT8 Control);
void ScsiCoreEncodeTestUnitReadyCommand(PSCSI_TEST_UNIT_READY_COMMAND_STRUCTURE Cdb, UINT8 Control);
void ScsiCoreEncodeReadBuffer10Command(PSCSI_READ_BUFFER10_COMMAND_STRUCTURE Cdb, UINT8 Mode, UINT8 ModeSpecific, UINT8 BufferId, UINT32 BufferOffset, UINT32 AllocationLength, UINT8 Control);
void ScsiCoreEncodeReadCapacity10Command(PSCSI_READ_CAPACITY10_COMMAND_STRUCTURE Cdb, UINT32 Lba, UINT8 Pmi, UINT8 Control);
void ScsiCoreEncodeReadDefectData10Command(PSCSI_READ_DEFECT_DATA10_COMMAND_STRUCTURE Cdb, UINT8 DefectListFormat, UINT8 ReqGlist, UINT8 ReqPlist, UINT16 AllocationLength, UINT8 Control);
void ScsiCoreEncodeReadLong10Command(PSCSI_READ_LONG10_COMMAND_STRUCTURE Cdb, UINT8 Corrct, UINT8 Pblock, UINT32 Lba, UINT8 Btl, UINT8 Control);
void ScsiCoreEncodeRelease10Command(PSCSI_RELEASE10_COMMAND_STRUCTURE Cdb, UINT8 LongId, UINT8 ThirdParty, UINT8 ThirdPartyDevID, UINT16 ParameterListLength, UINT8 Control);
void ScsiCoreEncodeReportLunsCommandStructure(PSCSI_REPORT_LUNS_COMMAND_STRUCTURE Cdb, UINT8 SelectReport, UINT32 AllocationLength, UINT8 Control);
void ScsiCoreEncodeReportSupportedTaskManagementFunctionsCommand(PSCSI_REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS_COMMAND_STRUCTURE Cdb, UINT8 Repd, UINT32 AllocationLength, UINT8 Control);
void ScsiCoreEncodeReserve10Command(PSCSI_RESERVE10_COMMAND_STRUCTURE Cdb, UINT8 LongId, UINT8 ThirdParty, UINT8 ThirdPartyDevID, UINT16 ParameterListLength, UINT8 Control);
void ScsiCoreEncodeSanatizeCommand(PSCSI_SANITIZE_COMMAND_STRUCTURE Cdb, UINT8 ServiceAction, UINT8 Ause, UINT8 Znr, UINT8 Immed, UINT16 ParameterListLength, UINT8 Control);
void ScsiCoreEncodeSeekExtendedCommand(PSCSI_SEEK_EX_COMMAND_STRUCTURE Cdb, UINT8 Lun, UINT32 Lba, UINT8 Control);
void ScsiCoreEncodeSynchronizeCache10Command(PSCSI_SYNCHRONIZE_CACHE10_COMMAND_STRUCTURE Cdb, UINT8 Immed, UINT32 Lba, UINT8 GroupNumber, UINT16 NumberOfBlocks, UINT8 Control);
void ScsiCoreEncodeUnmapCommand(PSCSI_UNMAP_COMMAND_STRUCTURE Cdb, UINT8 Anchor, UINT8 GroupNumber, UINT16 ParameterListLength, UINT8 Control);
void ScsiCoreEncodeVerify10Command(PSCSI_VERIFY10_COMMAND_STRUCTURE Cdb, UINT8 ByteCheck, UINT8 Dpo, UINT8 VrProctect, UINT32 Lba, UINT8 GroupNumber, UINT16 VerificationLength, UINT8 Control);
void ScsiCoreEncodeReadDefectData12Command(PSCSI_READ_DEFECT_DATA12_COMMAND_STRUCTURE Cdb, UINT8 DefectListFormat, UINT8 ReqGList, UINT8 ReqPList, UINT32 Adi, UINT32 AllocationLength, UINT8 Control);
void ScsiCoreEncodeReportIdentifyingInformationCommand(PSCSI_REPORT_IDENTIFYING_INFORMATION_COMMAND_STRUCTURE Cdb, UINT16 Restricted, UINT32 AllocationLength, UINT8 InformationType, UINT8 Control);
void ScsiCoreEncodeReportSupportedOperationCodesCommand(PSCSI_REPORT_SUPPORTED_OPERATION_CODES Cdb, UINT8 ReportingOptions, UINT8 Rctd, UINT8 RequestedOperationCode, UINT16 RequestedServiceAction, UINT32 AllocationLength, UINT8 Control);
void ScsiCoreEncodeReportTimeStampCommand(PSCSI_REPORT_TIMESTAMP_COMMAND_STRUCTURE Cdb, UINT32 AllocationLength, UINT8 Control);
void ScsiCoreEncodeSecurityProtocolInCommand(PSCSI_SECURITY_PROTOCOL_IN_COMMAND_STRUCTURE Cdb, UINT8 SecurityProtocol, UINT16 SecurityProtocolSpecific, UINT8 Inc512, UINT32 AllocationLength, UINT8 Control);
void ScsiCoreEncodeSecurityProtocolOutCommand(PSCSI_SECURITY_PROTOCOL_OUT_COMMAND_STRUCTURE Cdb, UINT8 SecurityProtocol, UINT16 SecurityProtocolSpecific, UINT8 Inc512, UINT32 TransferLength, UINT8 Control);
void ScsiCoreEncodeSetIdentifyingInformationCommand(PSCSI_SET_IDENTIFYING_INFORMATION_COMMAND_STRUCTURE Cdb, UINT32 ParameterListLength, UINT8 InformationType, UINT8 Control);
void ScsiCoreEncodeSetTimeStampCommand(PSCSI_SET_TIMESTAMP_COMMAND_STRUCTURE Cdb, UINT32 ParameterListLength, UINT8 Control);
void ScsiCoreEncodeStartStopUnitCommand(PSCSI_START_STOP_UNIT_COMMAND_STRUCTURE Cdb, UINT8 Immed, UINT8 Pcm, UINT8 Start, UINT8 Loej, UINT8 NoFlush, UINT8 PowerCondition, UINT8 Control);
void ScsiCoreEncodeVerify12Command(PSCSI_VERIFY12_COMMAND_STRUCTURE Cdb, UINT8 ByteCheck, UINT8 Dpo, UINT8 VrProctect, UINT32 Lba, UINT32 VerificationLength, UINT8 GroupNumber, UINT8 Control);
void ScsiCoreEncodeReadBuffer16Command(PSCSI_READ_BUFFER16_COMMAND_STRUCTURE Cdb, UINT8 Mode, UINT8 ModeSpecific, UINT64 BufferOffset, UINT32 AllocationLength, UINT8 BufferId, UINT8 Control);
void ScsiCoreEncodeReadCapacity16Command(PSCSI_READ_CAPACITY16_COMMAND_STRUCTURE Cdb, UINT64 Lba, UINT32 AllocationLength, UINT8 Pmi, UINT8 Control);
void ScsiCoreEncodeReadLong16Command(PSCSI_READ_LONG16_COMMAND_STRUCTURE Cdb, UINT64 Lba, UINT16 Btl, UINT8 Corrct, UINT8 Pblock, UINT8 Control);
void ScsiCoreEncodeStreamControlCommand(PSCSI_STREAM_CONTROL_COMMAND_STRUCTURE Cdb, UINT8 StreamControl, UINT16 StreamID, UINT8 Control);
void ScsiCoreEncodeSynchronizeCache16Command(PSCSI_SYNCHRONIZE_CACHE16_COMMAND_STRUCTURE Cdb, UINT8 Immed, UINT64 Lba, UINT32 NumberOfBlocks, UINT8 GroupNumber, UINT8 Control);
void ScsiCoreEncodeVerify16Command(PSCSI_VERIFY16_COMMAND_STRUCTURE Cdb, UINT8 ByteCheck, UINT8 Dpo, UINT8 VrProctect, UINT64 Lba, UINT32 VerificationLength, UINT8 GroupNumber, UINT8 Control);
void ScsiCoreEncodeVerify32Command(PSCSI_VERIFY32_COMMAND_STRUCTURE Cdb, UINT8 Control, UINT8 GroupNumber, UINT8 ByteCheck, UINT8 Dpo, UINT8 VrProctect, UINT64 Lba, UINT32 EilbrTag, UINT16 ElbaTag, UINT16 LbaTagMask, UINT32 VerificationLength);
void ScsiCoreEncodeWrite6Command(PSCSI_WRITE6_COMMAND_STRUCTURE Cdb, UINT32 Lba, UINT8 TransferLength, UINT8 Control);
void ScsiCoreEncodeWrite10Command(PSCSI_WRITE10_COMMAND_STRUCTURE Cdb, UINT8 Fua, UINT8 Dpo, UINT8 WrProtect, UINT32 Lba, UINT8 GroupNumber, UINT16 TransferLength, UINT8 Control);
void ScsiCoreEncodeWriteAndVerify10Command(PSCSI_WRITE_AND_VERIFY10_COMMAND_STRUCTURE Cdb, UINT8 ByteCheck, UINT8 Dpo, UINT8 WrProtect, UINT32 Lba, UINT8 GroupNumber, UINT16 TransferLength, UINT8 Control);
void ScsiCoreEncodeWriteBufferCommand(PSCSI_WRITE_BUFFER_COMMAND_STRUCTURE Cdb, UINT8 Mode, UINT8 ModeSpecific, UINT8 BufferId, UINT32 BufferOffset, UINT32 ParameterListLength, UINT8 Control);
void ScsiCoreEncodeWriteLong10Command(PSCSI_WRITE_LONG10_COMMAND_STRUCTURE Cdb, UINT8 WrUncor, UINT32 Lba, UINT16 TransferLength, UINT8 Control);
void ScsiCoreEncodeWriteSame10Command(PSCSI_WRITE_SAME10_COMMAND_STRUCTURE Cdb, UINT8 UnMap, UINT8 Anchor, UINT8 WrProtect, UINT32 Lba, UINT8 GroupNumber, UINT16 NumberOfBlocks, UINT8 Control);
void ScsiCoreEncodeWrite12Command(PSCSI_WRITE12_COMMAND_STRUCTURE Cdb, UINT8 Fua, UINT8 Dpo, UINT8 WrProtect, UINT32 Lba, UINT32 TransferLength, UINT8 GroupNumber, UINT8 Control);
void ScsiCoreEncodeWriteAndVerify12Command(PSCSI_WRITE_AND_VERIFY12_COMMAND_STRUCTURE Cdb, UINT8 ByteCheck, UINT8 Dpo, UINT8 WrProtect, UINT32 Lba, UINT32 TransferLength, UINT8 GroupNumber, UINT8 Control);
void ScsiCoreEncodeWrite16Command(PSCSI_WRITE16_COMMAND_STRUCTURE Cdb, UINT8 Fua, UINT8 Dpo, UINT8 WrProtect, UINT64 Lba, UINT32 TransferLength, UINT8 GroupNumber, UINT8 Dld0, UINT8 Dld1, UINT8 Dld2, UINT8 Control);
void ScsiCoreEncodeWriteAndVerify16Command(PSCSI_WRITE_AND_VERIFY16_COMMAND_STRUCTURE Cdb, UINT8 ByteCheck, UINT8 Dpo, UINT8 WrProtect, UINT64 Lba, UINT32 TransferLength, UINT8 GroupNumber, UINT8 Control);
void ScsiCoreEncodeWriteAtomic16Command(PSCSI_WRITE_ATOMIC16_COMMAND_STRUCTURE Cdb, UINT8 Fua, UINT8 Dpo, UINT8 WrProtect, UINT64 Lba, UINT16 AtomicBoundry, UINT16 TransferLength, UINT8 GroupNumber, UINT8 Control);
void ScsiCoreEncodeWriteStream16Command(PSCSI_WRITE_STREAM16_COMMAND_STRUCTURE Cdb, UINT8 Fua, UINT8 Dpo, UINT8 WrProtect, UINT64 Lba, UINT16 StreamID, UINT16 TransferLength, UINT8 GroupNumber, UINT8 Control);
void ScsiCoreEncodeWriteLong16Command(PSCSI_WRITE_LONG16_COMMAND_STRUCTURE Cdb, UINT8 WrUncor, UINT64 Lba, UINT16 TransferLength, UINT8 Control);
void ScsiCoreEncodeWriteSame16Command(PSCSI_WRITE_SAME16_COMMAND_STRUCTURE Cdb, UINT8 Ndob, UINT8 Unmap, UINT8 Anchor, UINT8 WrProtect, UINT64 Lba, UINT32 NumberOfBlocks, UINT8 GroupNumber, UINT8 Control);
void ScsiCoreEncodeWrite32Command(PSCSI_WRITE32_COMMAND_STRUCTURE Cdb, UINT8 Control, UINT8 GroupNumber, UINT8 Fua, UINT8 Dp0, UINT8 WrProtect, UINT64 Lba, UINT32 EilbrTag, UINT16 ElbaTag, UINT16 LbaTagMask, UINT32 TransferLength);
void ScsiCoreEncodeWriteAndVerify32Command(PSCSI_WRITE_AND_VERIFY32_COMMAND_STRUCTURE Cdb, UINT8 Control, UINT8 GroupNumber, UINT8 ByteCheck, UINT8 Dpo, UINT8 WrProtect, UINT64 Lba, UINT32 EilbrTag, UINT16 ElbaTag, UINT16 LbaTagMask, UINT32 TransferLength);
void ScsiCoreEncodeWriteAtomic32Command(PSCSI_WRITE_ATOMIC32_COMMAND_STRUCTURE Cdb, UINT8 Control, UINT16 AtomicBoundry, UINT8 GroupNumber, UINT8 Fua, UINT8 Dp0, UINT8 WrProtect, UINT64 Lba, UINT32 EilbrTag, UINT16 ElbaTag, UINT16 LbaTagMask, UINT32 TransferLength);
void ScsiCoreEncodeWriteSame32Command(PSCSI_WRITE_SAME32_COMMAND_STRUCTURE Cdb, UINT8 Control, UINT8 GroupNumber, UINT8 Ndob, UINT8 UnMap, UINT8 Anchor, UINT8 WrProtect, UINT64 Lba, UINT32 EilbrTag, UINT16 ElbaTag, UINT16 LbaTagMask, UINT32 NumberOfBlocks);
void ScsiCoreEncodeWriteStream32Command(PSCSI_WRITE_STREAM32_COMMAND_STRUCTURE Cdb, UINT8 Control, UINT16 StreamID, UINT8 GroupNumber, UINT8 Fua, UINT8 Dpo, UINT8 WrProtect, UINT64 Lba, UINT32 EilbrTag, UINT16 ElbaTag, UINT16 LbaTagMask, UINT32 TransferLength);

UINT16 ScsiCoreEncodeUint16(UINT16 Input);
UINT32 ScsiCoreEncodeUint32(UINT32 Input);
UINT64 ScsiCoreEncodeUint64(UINT64 Input);
void ScsiCoreDbgPrint(char* format, ...);

DRIVER_EXPORT LOUSTATUS ScsiCoreRegisterScsiHostDeviceDriver(
    PSCSI_HOST_DEVICE_DRIVER_OBJECT NewScsiDriverObject,
    SIZE                            DriverPrivateDataSize,
    SIZE                            DriverPrivateDataAlignment
);

DRIVER_EXPORT LOUSTATUS ScsiCoreCreateScsiHostDeviceObject(
    PSCSI_HOST_DEVICE_DRIVER_OBJECT ScsiDriverObject,
    PDEVICE_OBJECT                  LdmDevice,
    PSCSI_HOST_DEVICE_OBJECT*       NewDeviceObjectOut
);


#endif