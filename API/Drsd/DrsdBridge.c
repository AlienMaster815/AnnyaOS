#include "DrsdCore.h"

static mutex_t BridgeLock = {0};

DRIVER_EXPORT
void
DrsdBridgeUnplug(
    PDRSD_BRIDGE    Bridge
){
    Bridge->Unplugged = true;

    

    //DrsdBridgeRemove(Bridge);
}

static
void 
DrsdBridgeFree(
    PKERNEL_REFERENCE Ref
){
    PDRSD_BRIDGE Bridge = CONTAINER_OF(Ref, DRSD_BRIDGE, ReferenceCount);
    MutexLock(&BridgeLock);
    LouKeListDeleteItem(&Bridge->List);
    MutexUnlock(&BridgeLock);

    if(Bridge->Functions->Destroy){
        Bridge->Functions->Destroy(Bridge);
    }
    
    DrsdBridgePut(Bridge->NextBridge);
    
    LouKeFree(Bridge->Container);
}

DRIVER_EXPORT
void
DrsdBridgePut(
    PDRSD_BRIDGE Bridge
){
    if(Bridge){
        LouKeReleaseReferenceAndCall(&Bridge->ReferenceCount, DrsdBridgeFree);
    }
}

DRIVER_EXPORT
PDRSD_BRIDGE
DrsdBridgeGet(PDRSD_BRIDGE Bridge){
    if(Bridge){
        LouKeAcquireReference(&Bridge->ReferenceCount);
    }
    return Bridge;
}
