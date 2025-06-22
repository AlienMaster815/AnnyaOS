#include "DrsdCore.h"

int DrsdInternalProbeModes(PDRSD_CONNECTOR Connector){

    int Count = Connector->AssistCallbacks->ConnectorGetModes(Connector);

    if(Count < 1){
        LouPrint("ERROR No Modes Available\n");
    }

    //TODO Add Edid Overide

    LouPrint("DrsdInternalProbeModes() STATUS_SUCCESS\n");
    return Count;
}

DRSD_CONNECTOR_STATUS DrsdInternalProbeDetection(
    PDRSD_CONNECTOR Connector, 
    PDRSD_MODE_SET_CONTEXT Setex, 
    bool Force
){
    DRSD_CONNECTOR_STATUS ConnectorStatus;
    
    DrsdModeSetLockContext(Setex);

    ConnectorStatus = DrsdDetectConnectorStatus(Connector, Setex, Force);

    if(ConnectorStatus != Connector->ConnectorStatus){
        Setex->EpochCounter += 1;
    }
    
    return ConnectorStatus;
}