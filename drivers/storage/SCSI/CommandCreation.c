#include "ScsiCore.h"

//TODO:Check parameter safety



LOUSTATUS
ScsiCoreCreateChangeDefinitionCommandToDevice(
    PSCSI_DEVICE_OBJECT         ScsiDevice,
    PSCSI_COMMAND_PACKET        ControlCommand,
    UINT8                       Mode,
    UINT8                       Save
){
    if(!(ScsiDevice->ScsiFeatures & SCSI_CHANGE_DEFINITION_FEATURE)){
        return STATUS_NOT_SUPPORTED;
    }
    ControlCommand->CommandID = SCSI_COMMAND_CHANGE_DEFINITION_ID;
    ControlCommand->Shdd = ScsiDevice->Shdd;
    ControlCommand->ScsiPortDeviceObject = ScsiDevice->PortDevice;
    ScsiCoreEncodeChangeDefinitionCommand(&ControlCommand->Command.ChangeDefinition, Save, Mode, 0x00, 0x00);
    return ScsiDevice->Shdd->DriverObject->Callbacks->ScsiDevicePrepScsiCommand(ScsiDevice->PortDevice, ControlCommand);
}

LOUSTATUS
ScsiCoreCreateFormatUnitCommand(
    PSCSI_DEVICE_OBJECT     ScsiDevice,
    PSCSI_COMMAND_PACKET    ControlCommand,
    UINT8                   DefectListFormat,
    UINT8                   CmpList,
    UINT8                   FmtData,
    UINT8                   LongList,
    UINT8                   FmtpInfo,
    UINT8                   Ffmt,
    PVOID                   ListData,
    SIZE                    ListSize
){
    if(!(ScsiDevice->ScsiFeatures & SCSI_CHANGE_FORMAT_UNIT_FEATURE)){
        return STATUS_NOT_SUPPORTED;
    }
    ControlCommand->CommandID = SCSI_COMMAND_FORMAT_UNIT_ID;
    ControlCommand->Shdd = ScsiDevice->Shdd;
    ControlCommand->ScsiPortDeviceObject = ScsiDevice->PortDevice;
    ControlCommand->Command.FormatUnit.ListData = ListData;
    ControlCommand->Command.FormatUnit.ListSize = ListSize;
    ScsiCoreEncodeFormatUnitCommand(&ControlCommand->Command.FormatUnit.Cdb, DefectListFormat, CmpList, FmtData, LongList, FmtpInfo, 0x00, Ffmt, 0x00);
    return ScsiDevice->Shdd->DriverObject->Callbacks->ScsiDevicePrepScsiCommand(ScsiDevice->PortDevice, ControlCommand);
}

LOUSTATUS
ScsiCoreCreateGetLbaStatusCommand(
    PSCSI_DEVICE_OBJECT     ScsiDevice,
    PSCSI_COMMAND_PACKET    ControlCommand,
    UINT64                  StartingLba,
    UINT32                  AllocationLength
){
    if(!(ScsiDevice->ScsiFeatures & SCSI_CHANGE_GET_LBA_STATUS_FEATURE)){
        return STATUS_NOT_SUPPORTED;
    }
    ControlCommand->CommandID = SCSI_COMMAND_GET_LBA_STATUS_ID;
    ControlCommand->Shdd = ScsiDevice->Shdd;
    ControlCommand->ScsiPortDeviceObject = ScsiDevice->PortDevice;
    ControlCommand->Command.GetLbaStatus.StatusData = 0x00;
    ControlCommand->Command.GetLbaStatus.StatusSize = 0x00;
    ScsiCoreEncodeGetLbaStatusCommand(&ControlCommand->Command.GetLbaStatus.Cdb, StartingLba, AllocationLength, 0x00, 0x00);
    return ScsiDevice->Shdd->DriverObject->Callbacks->ScsiDevicePrepScsiCommand(ScsiDevice->PortDevice, ControlCommand);
}