#ifndef _DRSD_CRTC_INTERNAL_H
#define _DRSD_CRTC_INTERNAL_H

#include "DrsdCore.h"

PDRSD_ENCODER
DrsdConnectorGetSingleEncoder(
    PDRSD_CONNECTOR Connector
);




static inline UINT32 DrsdCrtcMask(PDRSD_CRTC Crtc){
    return (1 << DrsdCrtcIndex(Crtc));
}



#endif