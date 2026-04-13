#include "DrsdCore.h"


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



    return STATUS_SUCCESS;
}