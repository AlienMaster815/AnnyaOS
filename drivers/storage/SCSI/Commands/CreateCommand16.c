#include "../ScsiCore.h"

LOUSTATUS 
ScsiCoreCreateBackgroundControlCommandForDevice(
    PSCSI_DEVICE_OBJECT         ScsiDevice,
    PSCSI_COMMAND_PACKET        ControlCommand,
    UINT8                       BoControl,
    UINT8                       BoTime
){
    if(!(ScsiDevice->ScsiFeatures & SCSI_BACKGROUND_CONTROL_FEATURE)){
        return STATUS_NOT_SUPPORTED;
    }
    ControlCommand->CommandID = SCSI_COMMAND_BACKGROUND_CONTROL_ID;
    ControlCommand->Shdd = ScsiDevice->Shdd;
    ControlCommand->ScsiPortDeviceObject = ScsiDevice->PortDevice;
    ScsiCoreEncodeBackgroundControlCommand(&ControlCommand->Command.BackgroundControl, BoControl, BoTime, 0x00);
    return ScsiDevice->Shdd->DriverObject->Callbacks->ScsiDevicePrepScsiCommand(ScsiDevice->PortDevice, ControlCommand);
}