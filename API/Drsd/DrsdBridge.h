#ifndef _DRSD_BRIDGE_INTERNAL_H
#define _DRSD_BRIDGE_INTERNAL_H

#include "DrsdCore.h"

DRIVER_EXPORT
void
DrsdBridgePut(
    PDRSD_BRIDGE Bridge
);

//static inline 
//PDRSD_BRIDGE DrsdBridgeGetNextBridgeAndPut(PDRSD_BRIDGE Bridge){
//    PDRSD_BRIDGE Next = DrsdBridgeGetNextBridge(Bridge);
//}

#define DrsdForEachBridgeInChainScoped(Encoder, Bridge) for(PDRSD_BRIDGE Bridge) \
    for(PDRSD_BRIDGE Bridge __free(DrsdBridgePut) = DrsdBridgeChainGetFirstBridge(Encoder); Bridge; Bridge = DrsdBridgeGetNextBridgeAndPut(Bridge))

#endif