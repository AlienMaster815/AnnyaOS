#include "DrsdCore.h"

DRIVER_EXPORT
void
__DrsdAtomicHelperCrtcDestroyState(
    PDRSD_CRTC_STATE State
){
    if(State->Commit){
        if((State->Event) && (State->Commit->AbortCompletion)){
            DrsdCrtcCommitPut(State->Commit);
        }
        LouKeFree(State->Commit->Event);
        State->Commit->Event = 0x00;
        DrsdCrtcCommitPut(State->Commit);
    }
    DrsdPutBlobProperty(State->ModeBlob);
    DrsdPutBlobProperty(State->DegammaLut);
    DrsdPutBlobProperty(State->Ctm);
    DrsdPutBlobProperty(State->GammaLut);
}

DRIVER_EXPORT 
void 
__DrsdAtomicHelperCrtcStateReset(
    PDRSD_CRTC_STATE    State,
    PDRSD_CRTC          Crtc
){
    State->Crtc = Crtc;
}

DRIVER_EXPORT
void 
__DrsdAtomicHelperCrtcReset(
    PDRSD_CRTC          Crtc,
    PDRSD_CRTC_STATE    CrtcState
){
    if(CrtcState){
        __DrsdAtomicHelperCrtcStateReset(CrtcState, Crtc);
    }
    if(DrsdDeviceHasVBlank(Crtc->Device)){
        DrsdCrtcVBlankReset(Crtc);
    }
    Crtc->State = CrtcState;
}

DRIVER_EXPORT
void 
DrsdAtomicHelperCrtcDestroyState(
    PDRSD_CRTC         Crtc,
    PDRSD_CRTC_STATE   State
){
    __DrsdAtomicHelperCrtcDestroyState(State);
    LouKeFree(State);
}

DRIVER_EXPORT
void DrsdAtomicHelperCrtcReset(
    PDRSD_CRTC          Crtc 
){
    PDRSD_CRTC_STATE State = LouKeMallocType(DRSD_CRTC_STATE, KERNEL_GENERIC_MEMORY);
    if(Crtc->State){
        Crtc->Functions->AtomicDestroyState(Crtc, Crtc->State);
    }
    __DrsdAtomicHelperCrtcReset(Crtc, State);
}

DRIVER_EXPORT
void
__DrsdAtomicHelperCrtcDuplicateState(
    PDRSD_CRTC          Crtc,
    PDRSD_CRTC_STATE    State
){
    memcpy(State, Crtc->State, sizeof(DRSD_CRTC_STATE));
    if(State->ModeBlob){
        DrsdGetPropertBlob(State->ModeBlob);
    }
    if(State->DegammaLut){
        DrsdGetPropertBlob(State->DegammaLut);
    }
    if(State->Ctm){
        DrsdGetPropertBlob(State->Ctm);
    }
    if(State->GammaLut){
        DrsdGetPropertBlob(State->GammaLut);
    }
    State->ModeChanged = false;
    State->ActiveChanged = false;
    State->PlanesChanged = false;
    State->ConnectorsChanged = false;
    State->ColorMgmtChanged = false;
    State->ZPosChanged = false;
    State->Commit = 0x00;
    State->Event = 0x00;
    State->AsyncFlip = false;

    State->Active = DrsdAtomicCrtcEffectivlyActive(State);
    State->SelfRefreshActive = false;
}

DRIVER_EXPORT
PDRSD_CRTC_STATE 
DrsdAtomicHelperCrtcDuplicateState(
    PDRSD_CRTC          Crtc
){
    PDRSD_CRTC_STATE    State;

    if(!Crtc->State){
        return 0x00;
    }

    State = LouKeMallocType(DRSD_CRTC_STATE, KERNEL_GENERIC_MEMORY);
    if(State){
        __DrsdAtomicHelperCrtcDuplicateState(Crtc, State);
    }
    return State;
}