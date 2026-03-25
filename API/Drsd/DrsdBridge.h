#ifndef _DRSD_BRIDGE_INTERNAL_H
#define _DRSD_BRIDGE_INTERNAL_H

#include "DrsdCore.h"

DRIVER_EXPORT
void
DrsdBridgePut(
    PDRSD_BRIDGE Bridge
);

DEFINE_FREE(DrsdBridgePut, PDRSD_BRIDGE, if (_T) DrsdBridgePut(_T))

static inline 
PDRSD_BRIDGE DrsdBridgeGetNextBridgeAndPut(PDRSD_BRIDGE Bridge){
//    PDRSD_BRIDGE Next = DrsdBridgeGetNextBridge(Bridge);
    return 0x00;
}

static inline 
PDRSD_BRIDGE DrsdBridgeChainGetFirstBridge(PDRSD_ENCODER Encoder){
    return 0x00;
}

#define DrsdForEachBridgeInChainScoped(Encoder, Bridge) \
    for(PDRSD_BRIDGE Bridge __free(DrsdBridgePut) = DrsdBridgeChainGetFirstBridge(Encoder); Bridge; Bridge = DrsdBridgeGetNextBridgeAndPut(Bridge))

#endif