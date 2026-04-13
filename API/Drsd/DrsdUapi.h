#ifndef _DRSD_UAPI_INTERNAL_H
#define _DRSD_UAPI_INTERNAL_H

#include "DrsdCore.h"

DRIVER_EXPORT
LOUSTATUS 
DrsdAtomicSetModeForCrtc(
    PDRSD_CRTC_STATE    State,
    PDRSD_DISPLAY_MODE  Mode
);

DRIVER_EXPORT
LOUSTATUS
DrsdAtomicSetCrtcForPlane(
    PDRSD_PLANE_STATE   PlaneState,
    PDRSD_CRTC          Crtc
);

#endif 