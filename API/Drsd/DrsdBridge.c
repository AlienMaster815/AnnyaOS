 /*
 * Copyright (c) 2026 AnnyaOS
 *
 * This file is a derivative work based on Linux DRM,
 * Copyright (c) 1994 - current
 *   - Dave Airlie          <airlied@linux.ie>
 *   - Daniel Vetter        <daniel.vetter@ffwll.ch>
 *   - Thomas Hellstrom     <thomas@vmware.com>
 *   - Alex Deucher         <alexander.deucher@amd.com>
 *   - Michel Dänzer        <michel@daenzer.net>
 *   - The X.Org / Mesa / DRM community
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
 
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

static 
PDRSD_PRIVATE_STATE 
DrsdBridgeAtomicDuplicatePrivateState(
    PDRSD_PRIVATE_OBJECT    Object
){

    PDRSD_BRIDGE        Bridge = DrsdPrivateToBridge(Object);
    PDRSD_BRIDGE_STATE  State;

    State = Bridge->Functions->AtomicDuplicateState(Bridge);
    return State ? &State->Base : 0x00;
}

static 
void
DrsdBridgeAtomicDestroyPrivateState(
    PDRSD_PRIVATE_OBJECT    Object,
    PDRSD_PRIVATE_STATE     PrivateState
){
    PDRSD_BRIDGE_STATE  BridgeState = DrsdPrivateToBridgeState(PrivateState);
    PDRSD_BRIDGE        Bridge = DrsdPrivateToBridge(Object);

    Bridge->Functions->AtomicDestroyState(Bridge, BridgeState);
}

static 
PDRSD_PRIVATE_STATE
DrsdBridgeAtomicCreatePrivateState(
    PDRSD_PRIVATE_OBJECT    PrivateObject
){
    PDRSD_BRIDGE            Bridge = DrsdPrivateToBridge(PrivateObject);
    PDRSD_BRIDGE_STATE      State;

    State = Bridge->Functions->AtomicReset(Bridge);

    if(IS_LOU_KE_PTR_ERROR(State)){
        return LOU_KE_ERROR_PTR(State);
    }

    return &State->Base;
}

static DRSD_PRIVATE_STATE_FUNCTIONS DrsdBridgePrivateStateFunctions = {
    .AtomicCreateState = DrsdBridgeAtomicCreatePrivateState,
    .AtomicDuplicateState = DrsdBridgeAtomicDuplicatePrivateState,
    .AtomicDestroyState = DrsdBridgeAtomicDestroyPrivateState,
};

static BOOLEAN DrsdBridgeIsAtomic(PDRSD_BRIDGE Bridge){
    return Bridge->Functions->AtomicReset ? true : false;
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


DRIVER_EXPORT
LOUSTATUS
DrsdBridgeAttatch(
    PDRSD_ENCODER               Encoder,
    PDRSD_BRIDGE                Bridge,
    PDRSD_BRIDGE                Previous,
    DRSD_BRIDGE_ATTATCH_FLAGS   Flags
){
    LOUSTATUS Status;

    if(!Encoder || !Bridge){
        return STATUS_INVALID_PARAMETER;
    }

    if(!Bridge->Container){
        LouPrint("DRSD.SYS:Drsd Bridge Currupted Or Not Allocated Bt Device Manager\n");
    }

    if(LouKeListIsEmpty(&Bridge->List)){
        LouPrint("DRSD.SYS:Missing DrsdBridgeAdd() Before Attatch\n");
    }

    DrsdBridgeGet(Bridge);

    if(Previous && (!Previous->Device || Previous->Encoder != Encoder)){
        Status = STATUS_INVALID_PARAMETER;
        goto _ERROR_PUT_BRIDGE;
    }

    if(Previous){
        LouKeListAddTail(&Bridge->ChainNode, &Previous->ChainNode);
    }else{
        LouKeListAddTail(&Bridge->ChainNode, &Encoder->BridgeChain);
    }

    if(Bridge->Functions->Attatch){
        Status = Bridge->Functions->Attatch(Bridge, Encoder, Flags);
        if(Status != STATUS_SUCCESS){
            goto _ERROR_RESET_BRIDGE;
        }
    }

    if(DrsdBridgeIsAtomic(Bridge)){
        DrsdAtomicPrivateObjectInitialize(
            Bridge->Device,
            &Bridge->Base,
            &DrsdBridgePrivateStateFunctions
        );
    }

    return STATUS_SUCCESS;

_ERROR_RESET_BRIDGE:
    Bridge->Device = 0x00;
    Bridge->Encoder = 0x00;
    LouKeListDeleteAll(&Bridge->ChainNode);
_ERROR_PUT_BRIDGE:
    DrsdBridgePut(Bridge);
    return STATUS_SUCCESS;
}

void DrsdBridgeDetatch(PDRSD_BRIDGE Bridge){
    if(!Bridge){
        return;
    }
    if(!Bridge->Device){
        return;
    }
    if(DrsdBridgeIsAtomic(Bridge)){
        DrsdAtomicPrivateObjectDeInitialize(&Bridge->Base);
    }
    if(Bridge->Functions->Detatch){
        Bridge->Functions->Detatch(Bridge);
    }
    LouKeListDeleteAll(&Bridge->ChainNode);
    Bridge->Device = 0x00;
    DrsdBridgePut(Bridge);
}

DRIVER_EXPORT
DRSD_MODE_STATUS 
DrsdBridgeChainModeValid(
    PDRSD_BRIDGE                Bridge,
    PDRSD_DISPLAY_INFORMATION   Info,
    PDRSD_DISPLAY_MODE          Mode
){
    PDRSD_ENCODER   Encoder;
    if(!Bridge){
        return DRSD_MODE_OK;
    }

    Encoder = Bridge->Encoder;
    ForEachListEntryFrom(Bridge, &Encoder->BridgeChain, ChainNode){
        DRSD_MODE_STATUS Status;
        if(!Bridge->Functions->ModeValid){
            continue;
        }
        Status = Bridge->Functions->ModeValid(Bridge, Info, Mode);
        if(Status != DRSD_MODE_OK){
            return Status;
        }
    }

    return DRSD_MODE_OK;
}

DRIVER_EXPORT
void 
DrsdBridgeChainModeSet(
    PDRSD_BRIDGE        Bridge,
    PDRSD_DISPLAY_MODE  Mode,
    PDRSD_DISPLAY_MODE  AdjustedMode
){
    PDRSD_ENCODER Encoder;
    if(!Bridge){
        return;
    }
    Encoder = Bridge->Encoder;
    ForEachListEntryFrom(Bridge, &Encoder->BridgeChain, ChainNode){
        if(Bridge->Functions->ModeSet){
            Bridge->Functions->ModeSet(Bridge, Mode, AdjustedMode);
        }
    }
}

//804
/*DRIVER_EXPORT
void 
DrsdAtomicBridgeChainDisable(
    PDRSD_BRIDGE        Bridge,
    PDRSD_ATOMIC_STATE  State
){
    PDRSD_ENCODER   Encoder;
    PDRSD_BRIDGE    Iteration;
    if(!Bridge){
        return;
    }

    Encoder = Bridge->Encoder;
    

}*/
