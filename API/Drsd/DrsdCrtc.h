#ifndef _DRSD_CRTC_INTERNAL_H
#define _DRSD_CRTC_INTERNAL_H

#include "DrsdCore.h"

static inline UINT DrsdCrtcIndex(PDRSD_CRTC Crtc){
    return Crtc->Index;
} 

static inline UINT32 DrsdCrtcMask(PDRSD_CRTC Crtc){
    return (1 << DrsdCrtcIndex(Crtc));
}



#endif