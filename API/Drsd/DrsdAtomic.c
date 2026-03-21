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

DRIVER_EXPORT
void 
__DrsdCrtcCommitFree(PKERNEL_REFERENCE Kref){
    PDRSD_CRTC_COMMIT Commit = CONTAINER_OF(Kref, DRSD_CRTC_COMMIT, Reference);
    LouKeFree(Commit);
}

DRIVER_EXPORT
LOUSTATUS
DrsdCrtcCommitWait(
    PDRSD_CRTC_COMMIT Commit
){
    LOUSTATUS Status;
    if(!Commit){
        return STATUS_SUCCESS;
    }

    Status = LouKeWaitForCompletionTimeout(&Commit->HwDone, 10);
    if(Status != STATUS_SUCCESS){
        LouPrint("DRSD.SYS:Crtc:%h HwDone Timed Out\n", Commit->Crtc->Device);
        return STATUS_TIMEOUT;
    }

    Status = LouKeWaitForCompletionTimeout(&Commit->FlipDone, 10);
    if(Status != STATUS_SUCCESS){
        LouPrint("DRSD.SYS:Crtc:%h FlipDone Timed Out\n", Commit->Crtc->Device);
        return STATUS_TIMEOUT;
    }

    return STATUS_SUCCESS;
}

DRIVER_EXPORT 
void 
DrsdAtomicStateDefaultRelease(
    PDRSD_ATOMIC_STATE State
){
    LouKeFree(State->Connectors);
    LouKeFree(State->Crtcs);
    LouKeFree(State->Planes);
    LouKeFree(State->ColorOps);
    LouKeFree(State->PrivateObjects);
}

DRIVER_EXPORT
LOUSTATUS 
DrsdAtomicStateInitalize(
    PDRSD_DEVICE        Device,
    PDRSD_ATOMIC_STATE  State
){
    LouKeInitializeKernelRefence(&State->Reference);
    State->AllowModeSet = true;
    State->Crtcs = LouKeMallocArray(DRSD_CRTCS_STATE, Device->ModeConfig.CrtcCount, KERNEL_GENERIC_MEMORY);
    if(!State->Crtcs){
        goto _INIT_FAILED;
    }
    State->Planes = LouKeMallocArray(DRSD_PLANES_STATE, Device->ModeConfig.TotalPlaneCount, KERNEL_GENERIC_MEMORY);
    if(State->Planes){
        goto _INIT_FAILED;
    }
    State->ColorOps = LouKeMallocArray(DRSD_COLOR_OPS, Device->ModeConfig.ColorOpCount, KERNEL_GENERIC_MEMORY);
    if(State->ColorOps){
        goto _INIT_FAILED;
    }

    DrsdAcquireDevice(Device);
    State->Device = Device;

    LouPrint("DRSD.SYS:Allocated Device State:%h\n", State);

    return STATUS_SUCCESS;

    _INIT_FAILED:
        DrsdAtomicStateDefaultRelease(State);
        return STATUS_INSUFFICIENT_RESOURCES;

}

DRIVER_EXPORT
PDRSD_ATOMIC_STATE 
DrsdAtomicStateAllocate(
    PDRSD_DEVICE    Device
){
    PDRSD_MODE_CONFIGURATION Config = &Device->ModeConfig;
    if(!Config->Functions->AtomicStateAllocate){
        PDRSD_ATOMIC_STATE State = LouKeMallocType(DRSD_ATOMIC_STATE, KERNEL_GENERIC_MEMORY);   
        if(!State){
            return  0x00;
        }
        if(DrsdAtomicStateInitalize(Device, State) != STATUS_SUCCESS){
            LouKeFree(State);
            return 0x00;
        }
        return State;
    }
    return Config->Functions->AtomicStateAllocate(Device);
}

DRIVER_EXPORT
void 
DrsdAtomicStateDefaultClear(
    PDRSD_ATOMIC_STATE State
){
    PDRSD_DEVICE                Device = State->Device;
    PDRSD_MODE_CONFIGURATION    Config = &Device->ModeConfig;
    SIZE                        i;

    LouPrint("DRSD.SYS:Clearing Atomic State:%h\n", State);

    State->Checked = false;

    for(i = 0 ; i < State->ConnectorCount; i++){
        PDRSD_CONNECTOR Connector = State->Connectors[i].Connector;
        if(!Connector){
            continue;
        }

        Connector->Functions->AtomicDestroyState(Connector, State->Connectors[i].StateToDestroy);

        State->Connectors[i].Connector = 0x00;
        State->Connectors[i].StateToDestroy = 0x00;
        State->Connectors[i].OldState = 0x00;
        State->Connectors[i].NewState = 0x00;
        DrsdConnectorPut(Connector);
    }

    for(i = 0 ; i < Config->CrtcCount; i++){
        PDRSD_CRTC Crtc = State->Crtcs[i].Crtc;
        if(!Crtc){
            continue;
        }

        Crtc->Functions->AtomicDestroyState(Crtc, State->Crtcs[i].StateToDestroy);

        State->Crtcs[i].Crtc = 0x00;
        State->Crtcs[i].StateToDestroy = 0x00;
        State->Crtcs[i].OldState = 0x00;
        State->Crtcs[i].NewState = 0x00;

        if(State->Crtcs[i].Commit){
            DrsdCrtcCommitPut(State->Crtcs[i].Commit);
            State->Crtcs[i].Commit = 0x00;
        }
    }

    for(i = 0 ; i < Config->TotalPlaneCount; i++){
        PDRSD_PLANE Plane = State->Planes[i].Plane;

        if(!Plane){
            continue;
        }

        Plane->Functions->AtomicDestroyState(Plane, State->Planes[i].StateToDestroy);
        State->Planes[i].Plane = 0x00;
        State->Planes[i].StateToDestroy = 0x00;
        State->Planes[i].OldState = 0x00;
        State->Planes[i].NewState = 0x00;
    }

    for(i = 0 ; i < Config->ColorOpCount; i++){
        PDRSD_COLOR_OP ColorOp = State->ColorOps[i].ColorOp;
        if(!ColorOp){
            continue;
        }

        DrsdColorOpAtomicDestroyState(ColorOp, State->ColorOps[i].State);
        State->ColorOps[i].ColorOp = 0x00;
        State->ColorOps[i].State = 0x00;
        State->ColorOps[i].OldState = 0x00;
        State->ColorOps[i].NewState = 0x00;
    }

    for(i = 0 ; i < State->PrivateObjectsCount; i++){
        PDRSD_PRIVATE_OBJECT Object = State->PrivateObjects[i].Object;
        
        Object->Functions->AtomicDestroyState(Object, State->PrivateObjects[i].StateToDestroy);
        State->PrivateObjects[i].Object = 0x00;
        State->PrivateObjects[i].StateToDestroy = 0x00;
        State->PrivateObjects[i].OldState = 0x00;
        State->PrivateObjects[i].NewState = 0x00;
    }
    State->PrivateObjectsCount = 0;

    if(State->FakeCommit){
        DrsdCrtcCommitPut(State->FakeCommit);
        State->FakeCommit = 0x00;
    }
}

void DrsdAtomicStateClear(PDRSD_ATOMIC_STATE State){
    PDRSD_DEVICE Device = State->Device;
    PDRSD_MODE_CONFIGURATION Config = &Device->ModeConfig;

    if(Config->Functions->AtomicStateClear){
        Config->Functions->AtomicStateClear(State);
    }else{
        DrsdAtomicStateDefaultClear(State);
    }
}

void __DrsdAtomicStateFree(PKERNEL_REFERENCE Reference){
    PDRSD_ATOMIC_STATE          State = CONTAINER_OF(Reference, DRSD_ATOMIC_STATE, Reference);
    PDRSD_DEVICE                Device = State->Device;
    PDRSD_MODE_CONFIGURATION    Config = &Device->ModeConfig;

    DrsdAtomicStateClear(State);

    LouPrint("DRSD.SYS:Freeing Atomic State:%h\n", State);

    if(Config->Functions->AtomicStateFree){
        Config->Functions->AtomicStateFree(State);
    }else {
        DrsdAtomicStateDefaultRelease(State);
        LouKeFree(State);
    }
    DrsdReleaseDevice(Device);
}

DRIVER_EXPORT 
PDRSD_CRTC_STATE
DrsdAtomicGetCrtcState(
    PDRSD_ATOMIC_STATE  State,  
    PDRSD_CRTC          Crtc
){
    LOUSTATUS           Status;
    UINT                Index = DrsdCrtcIndex(Crtc); 
    PDRSD_CRTC_STATE    CrtcState;

    if(!State->AcquireContext){
        LouPrint("DRSD.SYS:WARNING:DrsdAtomicGetCrtcState():Atomic State Acquire Context is NULL\n");
    }
    if((State->Device) && (State->Checked)){
        LouPrint("DRSD.SYS:WARNING:DrsdAtomicGetCrtcState():Device And Check are true\n");
    }

    CrtcState = DrsdAtomicGetNewCrtcState(State, Crtc);
    if(CrtcState){
        return CrtcState;
    }

    Status = DrsdModesetLock(&Crtc->Mutex, State->AcquireContext);
    if(Status != STATUS_SUCCESS){
        return (PDRSD_CRTC_STATE)(UINTPTR)Status;
    }

    CrtcState = Crtc->Functions->AtomicDuplicateState(Crtc);
    if(!CrtcState){
        return (PDRSD_CRTC_STATE)(UINTPTR)STATUS_INSUFFICIENT_RESOURCES;
    }

    State->Crtcs[Index].StateToDestroy = CrtcState; 
    State->Crtcs[Index].OldState = Crtc->State;
    State->Crtcs[Index].NewState = CrtcState;
    State->Crtcs[Index].Crtc = Crtc;
    CrtcState->State = State;

    LouPrint("DRSD.SYS:Device:%h:Added[CRTC:%d:%s]:%h State to %h\n", State->Device, Crtc->Base.Identification, Crtc->Name, CrtcState, State);

    return CrtcState;
}

UNUSED 
static 
LOUSTATUS
DrsdAtomicCrtcCheck(
    PDRSD_CRTC_STATE    OldCrtcState,
    PDRSD_CRTC_STATE    NewCrtcState
){
    PDRSD_CRTC Crtc = NewCrtcState->Crtc;
    BOOLEAN DriverSupportsAtomic = DrsdCoreCheckFeature(Crtc->Device, DRIVER_ATOMIC);

    if((NewCrtcState->Active) && (!NewCrtcState->Enable)){
        LouPrint("DRSD.SYS:Device:%h:Added[CRTC:%d:%s]:Active Withought Enable\n", Crtc->Device, Crtc->Base.Identification, Crtc->Name);
        return STATUS_INVALID_PARAMETER; 
    }

    if((DriverSupportsAtomic) && (NewCrtcState->Enable) && (!NewCrtcState->ModeBlob)){
        LouPrint("DRSD.SYS:Device:%h:Added[CRTC:%d:%s]:Enabled Withought Mode Blob\n", Crtc->Device, Crtc->Base.Identification, Crtc->Name);
        return STATUS_INVALID_PARAMETER;
    }

    if((DriverSupportsAtomic) && (!NewCrtcState->Enable) && (NewCrtcState->ModeBlob)){
        LouPrint("DRSD.SYS:Device:%h:Added[CRTC:%d:%s]:Disabled With Mode Blob\n", Crtc->Device, Crtc->Base.Identification, Crtc->Name);
        return STATUS_INVALID_PARAMETER;
    }
    
    if((NewCrtcState->Event) && (!NewCrtcState->Active)){
        LouPrint("DRSD.SYS:Device:%h:Added[CRTC:%d:%s]:Requesting Event But Is Off\n", Crtc->Device, Crtc->Base.Identification, Crtc->Name);
        return STATUS_INVALID_PARAMETER;
    }

    return STATUS_SUCCESS;
}

DRIVER_EXPORT
PDRSD_CONNECTOR 
DrsdAtomicGetConnectorForEncoder(
    PDRSD_ENCODER                   Encoder,
    PDRSD_MODESET_ACQURE_CONTEXT    Context
){


    return 0x00;
}
