#include "ScsiCore.h"



LOUSTATUS 
ScsiCoreSendBackgroundControlCommandToDevice(
    PSCSI_DEVICE_OBJECT         ScsiDevice,
    UINT8                       BoControl,
    UINT8                       BoTime
){
    if(!(ScsiDevice->ScsiFeatures & SCSI_BACKGROUND_CONTROL_FEATURE)){
        return STATUS_NOT_SUPPORTED;
    }
    LOUSTATUS Status;
    SCSI_COMMAND_PACKET ControlCommand = {0};
    ControlCommand.CommandID = SCSI_COMMAND_BACKGROUND_CONTROL_ID;
    ControlCommand.Shdd = ScsiDevice->Shdd;
    ControlCommand.ScsiDeviceObject = ScsiDevice;
    ScsiCoreEncodeBackgroundControlCommand(&ControlCommand.Command.BackgroundControl, BoControl, BoTime, 0x00);
    Status = ScsiDevice->Shdd->DriverObject->Callbacks->ScsiDeviceSendScsiCommand(&ControlCommand);
    if(Status == STATUS_NOT_SUPPORTED){
        ScsiDevice->ScsiFeatures &= ~(SCSI_BACKGROUND_CONTROL_FEATURE);
    }else if(Status != STATUS_SUCCESS){
        switch(ControlCommand.SenseResult){
            case SENSE_RESULT_ILLEGAL_REQUEST_ID:{ //stop and unset feature flag
                ScsiCoreEncodeBackgroundControlCommand(&ControlCommand.Command.BackgroundControl, SCSI_BO_CONTROL_STOP_OP, SCSI_BO_TIME_NO_LIMIT, 0x00);
                ScsiDevice->Shdd->DriverObject->Callbacks->ScsiDeviceSendScsiCommand(&ControlCommand);
                ScsiDevice->ScsiFeatures &= ~(SCSI_BACKGROUND_CONTROL_FEATURE);
                break;
            }

        }
    }
    return Status;
}


LOUSTATUS
ScsiCoreSendChangeDefinitionCommandToDevice(
    PSCSI_DEVICE_OBJECT         ScsiDevice,
    UINT8                       Mode,
    UINT8                       Save
){
    if(!(ScsiDevice->ScsiFeatures & SCSI_CHANGE_DEFINITION_FEATURE)){
        return STATUS_NOT_SUPPORTED;
    }
    LOUSTATUS Status;
    SCSI_COMMAND_PACKET ControlCommand = {0};
    ControlCommand.CommandID = SCSI_COMMAND_CHANGE_DEFINITION_ID;
    ControlCommand.Shdd = ScsiDevice->Shdd;
    ControlCommand.ScsiDeviceObject = ScsiDevice;
    ScsiCoreEncodeChangeDefinitionCommand(&ControlCommand.Command.ChangeDefinition, Save, Mode, 0x00, 0x00);
    Status = ScsiDevice->Shdd->DriverObject->Callbacks->ScsiDeviceSendScsiCommand(&ControlCommand);
    if(Status != STATUS_SUCCESS){
        ScsiDevice->ScsiFeatures &= ~(SCSI_CHANGE_DEFINITION_FEATURE);
    }
    return Status;
}