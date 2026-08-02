#ifndef _SCSI_CORE_H
#define _SCSI_CORE_H

#include <LouDDK.h>

typedef struct _SCSI_INTERNAL_HOST_DEVICE_OBJECT{
    struct _SCSI_HOST_DEVICE_DRIVER_OBJECT*     DriverObject;
    ListHeader                                  HostList;
    SIZE                                        HostXaID;
    XARRAY                                      DeviceArray;
    ListHeader                                  DeviceList;
    SCSI_HOST_DEVICE_OBJECT                     ScsiHostDevice;
}SCSI_INTERNAL_HOST_DEVICE_OBJECT, * PSCSI_INTERNAL_HOST_DEVICE_OBJECT;


typedef struct _SCSI_INTERNAL_HOST_DEVICE_DRIVER_OBJECT{
    ListHeader                      DriverList;
    SIZE                            DriverXaID;
    XARRAY                          ShddArray;
    ListHeader                      ShddList;
    SCSI_HOST_DEVICE_DRIVER_OBJECT  DriverObject;
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

void ScsiCoreDbgPrint(char* format, ...);

#endif