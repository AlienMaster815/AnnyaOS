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

DRIVER_EXPORT
void
DrsdAtomicSetFbForPlane(
    PDRSD_PLANE_STATE   State,
    PDRSD_FRAME_BUFFER  FrameBuffer
);

DRIVER_EXPORT 
LOUSTATUS
DrsdAtomicSetCrtcForConnector(
    PDRSD_CONNECTOR_STATE   State,
    PDRSD_CRTC              Crtc
);

DRIVER_EXPORT
LOUSTATUS
DrsdAtomicSetModePropForCrtc(
    PDRSD_CRTC_STATE    State,
    PDRSD_PROPERTY_BLOB Blob
);

#endif 