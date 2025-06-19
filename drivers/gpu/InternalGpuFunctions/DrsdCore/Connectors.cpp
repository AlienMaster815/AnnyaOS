#include "DrsdCore.h"

DRSD_CONNECTOR_STATUS DrsdDetectConnectorStatus(
    PDRSD_CONNECTOR         Connector, 
    PDRSD_MODE_SET_CONTEXT  Setex,
    bool                    Force
){
    if(Connector->AssistCallbacks->ConnectorDetectContext){
        return Connector->AssistCallbacks->ConnectorDetectContext(Connector, Setex, Force);
    }else if(Connector->AssistCallbacks->ConnectorDetect){
        return Connector->AssistCallbacks->ConnectorDetect(Connector, Force);
    }else if(Connector->Callbacks->DetectConnector){
        Connector->Callbacks->DetectConnector(Connector, Force);
    }
    return DRSD_CONNECTOR_CONNECTED;
}

LOUSTATUS DrsdInternalProbeSingleConnectorModes(
    PDRSD_CONNECTOR Connector,
    uint32_t        MaxX,
    uint32_t        MaxY
){
    LouPrint("DrsdInternalProbeSingleConnectorModes()\n");
    PDRSD_DEVICE Device = Connector->Device;
    PDRSD_DISPLAY_MODE DispMode;
    DRSD_CONNECTOR_STATUS OldConnectorStatus;
    DRSD_CONNECTOR_STATUS Status;
    UNUSED int ModeCount;

    DrsdModeSetWarnIfLocked(Device);

    PDRSD_MODE_SET_CONTEXT Setex = DrsdInitializeModeContext(Device);

    DrsdModeSetLockContext(Setex);

    DispMode = (PDRSD_DISPLAY_MODE)Connector->SupportedModes.NextHeader;

    while(DispMode){
        DispMode->ModeStatus = DRSD_MODE_STALE;
        DispMode = (PDRSD_DISPLAY_MODE)DispMode->Peers.NextHeader;
    }

    OldConnectorStatus = Connector->ConnectorStatus;

    if(Connector->Force){
        if(
            (Connector->Force == DRSD_FORCE_ON) ||
            (Connector->Force == DRSD_FORCE_DIGITAL)
        ){
            Connector->ConnectorStatus = DRSD_CONNECTOR_CONNECTED;   
        }else {
            Connector->ConnectorStatus = DRSD_CONNECTOR_DISCONNECTED;
        }
        if(Connector->Callbacks->ForceConnector){
            Connector->Callbacks->ForceConnector(Connector);
        }
    }else{
        Status = DrsdInternalProbeDetection(Connector, Setex, true);
        Connector->ConnectorStatus = Status;   
    }

    if(Connector->ConnectorStatus != OldConnectorStatus){
        //TODO: Notify and register change
        LouPrint("NOTICE:Device Status Changed From:%d to %d\n", OldConnectorStatus, Connector->ConnectorStatus);

    }    

    if(!Device->ModeConfiguration.UsingPolling){
        Device->ModeConfiguration.UsingPolling = true;
    }

    //TODO Get Connection Enabled if not so

    ModeCount = DrsdInternalProbeModes(Connector);

    DrsdModeSetDestroyModeContext(Device, Setex);
    LouPrint("DrsdInternalProbeSingleConnectorModes() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}