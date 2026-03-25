#ifndef _DRSD_BRIDGE_INTERNAL_H
#define _DRSD_BRIDGE_INTERNAL_H

#include "DrsdCore.h"

DRIVER_EXPORT
PDRSD_BRIDGE
DrsdBridgeGet(
    PDRSD_BRIDGE Bridge
);

DRIVER_EXPORT
void
DrsdBridgePut(
    PDRSD_BRIDGE Bridge
);

DEFINE_FREE(DrsdBridgePut, PDRSD_BRIDGE, if (_T) DrsdBridgePut(_T))

static inline PDRSD_BRIDGE DrsdBridgeGetNextBridge(PDRSD_BRIDGE Bridge){
    Bridge = ListItemToTypeOrNull(&Bridge->ChainNode.NextHeader, DRSD_BRIDGE, ChainNode);
    if(!Bridge){
        return Bridge;
    }
    return DrsdBridgeGet(Bridge);
}

static inline 
PDRSD_BRIDGE DrsdBridgeGetNextBridgeAndPut(PDRSD_BRIDGE Bridge){
    PDRSD_BRIDGE Next = DrsdBridgeGetNextBridge(Bridge);
    DrsdBridgePut(Bridge);
    return Next;
}

static inline 
PDRSD_BRIDGE DrsdBridgeChainGetFirstBridge(PDRSD_ENCODER Encoder){
    return DrsdBridgeGet(ListItemToTypeOrNull(Encoder->BridgeChain.NextHeader, DRSD_BRIDGE, ChainNode));
}

#define DrsdForEachBridgeInChainScoped(Encoder, Bridge) \
    for(PDRSD_BRIDGE Bridge __free(DrsdBridgePut) = DrsdBridgeChainGetFirstBridge(Encoder); Bridge; Bridge = DrsdBridgeGetNextBridgeAndPut(Bridge))

#endif