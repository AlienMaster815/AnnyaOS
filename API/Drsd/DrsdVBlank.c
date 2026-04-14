#include "DrsdCore.h"

static 
PDRSD_VBLANK_CRTC 
DrsdVBlankCrtc(
    PDRSD_DEVICE Device, 
    UINT Pipe
){
    return &Device->VBlanks[Pipe];
}

DRIVER_EXPORT 
BOOLEAN
DrsdDeviceHasVBlank(
    PDRSD_DEVICE Device
){
    return (Device->CrtcCount != 0);
}

DRIVER_EXPORT 
PDRSD_VBLANK_CRTC 
DrsdCrtcVBlankCrtc(
    PDRSD_CRTC  Crtc
){
    return DrsdVBlankCrtc(Crtc->Device, DrsdCrtcIndex(Crtc));
}

DRIVER_EXPORT
void
DrsdCrtcVBlankReset(
    PDRSD_CRTC  Crtc
){
    PDRSD_DEVICE        Device = Crtc->Device;
    PDRSD_VBLANK_CRTC   VBlank = DrsdCrtcVBlankCrtc(Crtc);
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&Device->VBlankLock, &Irql);
    if(!VBlank->InModeset){
        LouKeAcquireReference(&VBlank->ReferenceCount);
        VBlank->InModeset = 1;
    }
    LouKeReleaseSpinLock(&Device->VBlankLock, &Irql);
}