#include "DrsdCore.h"

static void DrsdCrtcCrcDeInitialize(PDRSD_CRTC Crtc){

}

DRIVER_EXPORT
void
DrsdCrtcCleanup(
    PDRSD_CRTC  Crtc
){
    PDRSD_DEVICE Device = Crtc->Device;
    
    DrsdCrtcCrcDeInitialize(Crtc);
    
    LouKeFree(Crtc->GammaStore);
    Crtc->GammaStore = 0x00;

    DrsdModesetLockDeInitialize(&Crtc->Mutex);

    DrsdUnregisterModeObject(Device, &Crtc->Base);
    LouKeListDeleteItem(&Crtc->Head);
    Device->ModeConfig.CrtcCount--;

    if(Crtc->Functions->AtomicDestroyState){
        Crtc->Functions->AtomicDestroyState(Crtc, Crtc->State);
    }

    LouKeFree(Crtc->Name);

    memset(Crtc, 0, sizeof(DRSD_CRTC));
}