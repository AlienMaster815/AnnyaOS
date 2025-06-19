#include "DrsdCore.h"

PDRSD_VBLANK_CRTC GetDrsdVBlankCrtcFromCrtc(
    PDRSD_DEVICE    Device,
    PDRSD_CRTC      Crtc
){
    size_t Index = GetDrsdCrtcIndex(Crtc);
    PDRSD_VBLANK_CRTC VBlank = Device->VBlanks;
    for(size_t i = 0 ; i < Index; i++){
        VBlank = (PDRSD_VBLANK_CRTC)VBlank->Peers.NextHeader;
    }
    return VBlank;
}

void AddVBlankToCrtc(PDRSD_DEVICE Device){
    Device->VBlankCount++;
    PDRSD_VBLANK_CRTC VBlank = Device->VBlanks;
    if(!VBlank){
        Device->VBlanks = LouKeMallocType(DRSD_VBLANK_CRTC, KERNEL_GENERIC_MEMORY);
        return;
    }
    while(VBlank){
        if(!VBlank->Peers.NextHeader){
            VBlank->Peers.NextHeader = (PListHeader)LouKeMallocType(DRSD_VBLANK_CRTC, KERNEL_GENERIC_MEMORY);
            return;          
        }
        VBlank = (PDRSD_VBLANK_CRTC)VBlank->Peers.NextHeader;
    }   
}

void DrsdResetCrtcVBlank(
    PDRSD_CRTC Crtc
){
    PDRSD_DEVICE Device = Crtc->Device;
    PDRSD_VBLANK_CRTC VBlank = GetDrsdVBlankCrtcFromCrtc(Device, Crtc);
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&Device->VBlankLock, &Irql);
    if(!VBlank->InModeset){
        LouKeSetAtomic(&VBlank->Count, LouKeGetAtomic(&VBlank->Count) + 1);
        VBlank->InModeset++;
    }
    LouKeReleaseSpinLock(&Device->VBlankLock, &Irql);
}