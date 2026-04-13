#include "DrsdCore.h"

DRIVER_EXPORT
LOUSTATUS
DrsdAtomicSetModePropForCrtc(
    PDRSD_CRTC_STATE    State,
    PDRSD_PROPERTY_BLOB Blob
){

    PDRSD_CRTC Crtc = State->Crtc;
    LOUSTATUS Status;
    if(Blob == State->ModeBlob){
        return 0x00;
    }

    DrsdPutBlobProperty(State->ModeBlob);
    State->ModeBlob = 0x00;

    memset(&State->Mode, 0, sizeof(State->Mode));
    
    if(Blob){
        if(Blob->Length != sizeof(DRSD_MODE_MODEINFO)){
            LouPrint("Blob:%h Is Invalid Length For Set Mode\n", Blob);
            return STATUS_INVALID_PARAMETER;
        }
        Status = DrsdModeConvertUMode(Crtc->Device, &State->Mode, Blob->Data);
        if(Status != STATUS_SUCCESS){
            LouPrint("Unable To Convert Mode To UMODE\n");
            return STATUS_INVALID_PARAMETER;
        }
        State->ModeBlob = DrsdGetPropertBlob(Blob);
        State->Enable = true;
        //TODO: Print Debug Info
    }else{
        State->Enable = false;
        //TODO: Print Debug Info
    }

    return STATUS_SUCCESS;
}

DRIVER_EXPORT 
LOUSTATUS
DrsdAtomicSetCrtcForConnector(
    PDRSD_CONNECTOR_STATE   State,
    PDRSD_CRTC              Crtc
){
    PDRSD_CONNECTOR     Connector = State->Connector;
    PDRSD_CRTC_STATE    CrtcState;
    LOUSTATUS           Status;
    if(State->Crtc == Crtc){
        return STATUS_SUCCESS;
    }

    if(State->Crtc){
        CrtcState = DrsdAtomicGetNewCrtcState(State->State, State->Crtc);
        CrtcState->ConnectorMask &= ~DrsdConnectorMask(Connector);
        DrsdConnectorPut(State->Connector);
        State->Crtc = 0x00;
    }

    if(Crtc){
        CrtcState = DrsdAtomicGetNewCrtcState(State->State, Crtc);
        if(LOU_KE_PTR_ERROR(CrtcState)){
            return (LOUSTATUS)(UINTPTR)CrtcState;
        }

        CrtcState->ConnectorMask |= DrsdConnectorMask(State->Connector);
        CrtcState->Crtc = 0x00;
    }else{
        //TODO: Print Debug Info
    }

    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS 
DrsdAtomicSetModeForCrtc(
    PDRSD_CRTC_STATE    State,
    PDRSD_DISPLAY_MODE  Mode
){
    PDRSD_CRTC          Crtc = State->Crtc;
    DRSD_MODE_MODEINFO  UMode;

    if(Mode && (!memcmp(&State->Mode, Mode, sizeof(DRSD_DISPLAY_MODE)))){
        return STATUS_SUCCESS;
    }

    DrsdPutBlobProperty(State->ModeBlob);
    State->ModeBlob = 0x00;

    if(Mode){
        PDRSD_PROPERTY_BLOB Blob;

        DrsdModeConvertToUMode(&UMode, Mode);
        Blob = DrsdCreateBlobProperty(Crtc->Device, sizeof(DRSD_MODE_MODEINFO), &UMode);
        if(LOU_KE_PTR_ERROR(Blob)){
            return (LOUSTATUS)(UINTPTR)Blob;
        }

        DrsdModeCopy(&State->Mode, Mode);
        State->ModeBlob = Blob;
        State->Enable = true;
        LouPrint("Set MODE:%s for CRTC:%d:%s With State%h\n",Mode->Name, Crtc->Base.Identification, Crtc->Name, State);
    }else{
        memset(&State->Mode, 0, sizeof(DRSD_DISPLAY_MODE));
        State->Enable = false;
        LouPrint("Set NOMODE for CRTC:%d:%s With State%h\n", Crtc->Base.Identification, Crtc->Name, State);
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS
DrsdAtomicSetCrtcForPlane(
    PDRSD_PLANE_STATE   PlaneState,
    PDRSD_CRTC          Crtc
){
    PDRSD_PLANE         Plane = PlaneState->Plane;
    PDRSD_CRTC_STATE    CrtcState;

    if(PlaneState->Crtc == Crtc){
        return STATUS_SUCCESS;
    }
    if(PlaneState->Crtc){
        CrtcState = DrsdAtomicGetCrtcState(PlaneState->State, PlaneState->Crtc);
        if(LOU_KE_PTR_ERROR(CrtcState)){
            return (LOUSTATUS)(UINTPTR)CrtcState;
        }
        CrtcState->PlaneMask &= ~DrsdPlaneMask(Plane);
    }

    PlaneState->Crtc = Crtc;

    if(Crtc){
        CrtcState = DrsdAtomicGetCrtcState(PlaneState->State, Crtc);
        if(LOU_KE_PTR_ERROR(CrtcState)){
            return (LOUSTATUS)(UINTPTR)CrtcState;
        }
        CrtcState->PlaneMask |= DrsdPlaneMask(Plane);
    }

    //TODO: Print Debug Data

    return STATUS_SUCCESS;
}

DRIVER_EXPORT
void
DrsdAtomicSetFbForPlane(
    PDRSD_PLANE_STATE   State,
    PDRSD_FRAME_BUFFER  FrameBuffer
){
    PDRSD_PLANE Plane = State->Plane;
    if(FrameBuffer){
        //TODO: Print Debug Data
    }else{
        //TODO: Print Debug Data
    }

    DrsdFramebufferAssign(&State->FrameBuffer, FrameBuffer);

}