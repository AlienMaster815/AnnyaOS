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
                Status = ScsiDevice->Shdd->DriverObject->Callbacks->ScsiDeviceSendScsiCommand(&ControlCommand);
                ScsiDevice->ScsiFeatures &= ~(SCSI_BACKGROUND_CONTROL_FEATURE);
                break;
            }
            case SENSE_RESULT_UNIT_ATTENTION:{ //error handled higher in the API
                ScsiDevice->DeviceStatus = SCSI_DEVICE_NEEDS_CLEAR_STATE_AND_RETRY;
                break;
            }
            case SENSE_RESULT_NOT_READY:{ //error handled higher in the API
                ScsiDevice->DeviceStatus = SCSI_DEVICE_NEEDS_TO_WAIT;
                break;
            }
            default: //error handled higher in the API
                ScsiCoreDbgPrint("SCSICORE.SYS:ScsiCoreSendBackgroundControlCommandToDevice():Unable To Handle Error\n");
                ScsiDevice->DeviceStatus = SCSI_DEVICE_HARDWARE_FAILURE;
                break;
        }
    }
    return Status;
}