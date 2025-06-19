#include "DrsdCore.h"

int DrsdInternalProbeModes(PDRSD_CONNECTOR Connector){

    int Count = Connector->AssistCallbacks->ConnectorGetModes(Connector);


    LouPrint("Mode Count:%d\n", Count);

    LouPrint("DrsdInternalProbeModes() STATUS_SUCCESS\n");
    while(1);
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