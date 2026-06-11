#include "DrsdCore.h"

static mutex_t BridgeLock = {0};
static ListHeader BridgeList = {0};
static ListHeader BridgeLingerList = {0};
DEFINE_STATIC_SRCU(DrsdBridgeUnplugSrcu);

DRIVER_EXPORT
BOOLEAN
DrsdBridgeEntry(
    PDRSD_BRIDGE    Bridge,
    int*            Index
){  
    *Index = LouKeSrcuAcquireReadLock(&DrsdBridgeUnplugSrcu);

    if(Bridge->Unplugged){
        LouKeSrcuReleaseReadLock(&DrsdBridgeUnplugSrcu, *Index);
        return false;
    }
    return false;   
}

DRIVER_EXPORT
void 
DrsdBridgeExit(int Index){
    LouKeSrcuReleaseReadLock(&DrsdBridgeUnplugSrcu, Index);
}

DRIVER_EXPORT
void
DrsdBridgeUnplug(
    PDRSD_BRIDGE    Bridge
){
    Bridge->Unplugged = true;

    LouKeRcuSynchronize(&DrsdBridgeUnplugSrcu);    

    DrsdBridgeRemove(Bridge);
}

static
void 
__DrsdBridgeFree(
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

static void DrsdBridgePutVoid(PVOID Data){
    DrsdBridgePut((PDRSD_BRIDGE)Data);
}

static void DrsdBridgeRemoveVoid(PVOID Data){
    DrsdBridgeRemove((PDRSD_BRIDGE)Data);
}

DRIVER_EXPORT
PDRSD_BRIDGE
DrsdBridgeGet(PDRSD_BRIDGE Bridge){
    if(Bridge){
        LouKeAcquireReference(&Bridge->ReferenceCount);
    }
    return Bridge;
}


DRIVER_EXPORT
void
DrsdBridgePut(
    PDRSD_BRIDGE Bridge
){
    if(Bridge){
        LouKeReleaseReferenceAndCall(&Bridge->ReferenceCount, __DrsdBridgeFree);
    }
}

DRIVER_EXPORT 
void
DrsdBridgeClearAndPut(
    PDRSD_BRIDGE*   pBridge
){
    PDRSD_BRIDGE Bridge = *pBridge;
    *pBridge = 0x00;
    DrsdBridgePut(Bridge);
} 

DRIVER_EXPORT
PVOID 
__DrsdDeviceManagerAllocateBridge(
    PPCI_DEVICE_OBJECT      PDEV,
    SIZE                    Size,
    SIZE                    Offset,
    PDRSD_BRIDGE_FUNCTIONS  Functions
){
    PVOID           Container;
    PDRSD_BRIDGE    Bridge;
    //LOUSTATUS       Status;

    if(!Functions){
        LouPrint("Device:%h:Is Missing Functions\n", PDEV);
        return LOU_KE_ERROR_PTR(STATUS_INVALID_PARAMETER);
    }

    Container = LouKeMalloc(Size, KERNEL_GENERIC_MEMORY);
    if(!Container){
        return LOU_KE_ERROR_PTR(STATUS_INSUFFICIENT_RESOURCES);
    }

    Bridge = Container + Offset;
    INITIALIZE_LIST_HEADER(&Bridge->List);
    Bridge->Container = Container;
    Bridge->Functions = Functions;
    LouKeInitializeKernelRefence(&Bridge->ReferenceCount);
    
    //TODO:Add Action or reset  

    return Container;
}

DRIVER_EXPORT 
void
DrsdBridgeAdd(
    PDRSD_BRIDGE Bridge
){
    
    if(!Bridge->Container){
        LouPrint("DRSD.SYS:Drsd Bridge Currupted Or Not Allocated Bt Device Manager\n");
    }

    DrsdBridgeGet(Bridge);

    if(!LouKeListIsEmpty(&Bridge->List)){
        LouKeListDeleteInitialize(&Bridge->List);
    }

    MutexInitialize(&Bridge->HpdMutex);

    if(Bridge->Ops & DRSD_BRIDGE_OP_HDMI){
        Bridge->Ycbcr420Allowed = (Bridge->SupportedFormats & (1 << DRSD_OUTPUT_COLOR_FORMAT_YCBCR420)) ? true : false; 
    }

    MutexLock(&BridgeLock);
    LouKeListAddTail(&Bridge->List, &BridgeList);
    MutexUnlock(&BridgeLock);
}

DRIVER_EXPORT
LOUSTATUS
__DrsdDeviceManagerBridgeAdd(
    PPCI_DEVICE_OBJECT  PDEV,
    PDRSD_BRIDGE        Bridge
){
    DrsdBridgeAdd(Bridge);
    //TODO: Add Action Or Reset
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
void 
DrsdBridgeRemove(
    PDRSD_BRIDGE Bridge
){

    MutexLock(&BridgeLock);
    LouKeListMoveToTail(&Bridge->List, &BridgeLingerList);
    MutexUnlock(&BridgeLock);

    MutexDestroy(&Bridge->HpdMutex);

    DrsdBridgePut(Bridge);
}

//477