#include "DrsdCore.h"

size_t GetDrsdCrtcIndex(PDRSD_CRTC Crtc){

    PDRSD_DEVICE Device = Crtc->Device;
    size_t Count = Device->CrtcCount;
    PDRSD_CRTC Check = Device->Crtcs;
    for(size_t i = 0 ; i < Count; i++){
        if(Check == Crtc){
            return i;
        }
        Check = (PDRSD_CRTC)Check->Peers.NextHeader;
    }
    return 0x00;
}