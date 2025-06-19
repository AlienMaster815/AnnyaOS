#include <LouDDK.h>

void DrsdAtomicDestroyPlaneState(PDRSD_PLANE_STATE PlaneState);
void DrsdModeObjectObjectFree(PDRSD_MODE_OBJECT Object);
void DrsdModeSetDestroyModeContext(PDRSD_DEVICE Device, PDRSD_MODE_SET_CONTEXT Setex);
void DrsdGxeDestroyShadowPlane(PDRSD_PLANE Plane);
void DrsdModeSetLockContext(PDRSD_MODE_SET_CONTEXT Context);
void DrsdResetCrtcVBlank(PDRSD_CRTC Crtc);
PDRSD_MODE_SET_CONTEXT DrsdInitializeModeContext(PDRSD_DEVICE Device);
void AddVBlankToCrtc(PDRSD_DEVICE Device);
void DrsdModeSetWarnIfLocked(PDRSD_DEVICE Device);
size_t GetDrsdCrtcIndex(PDRSD_CRTC Crtc);
DRSD_CONNECTOR_STATUS DrsdInternalProbeDetection(
    PDRSD_CONNECTOR Connector, 
    PDRSD_MODE_SET_CONTEXT Setex, 
    bool Force
);
DRSD_CONNECTOR_STATUS DrsdDetectConnectorStatus(
    PDRSD_CONNECTOR         Connector, 
    PDRSD_MODE_SET_CONTEXT  Setex,
    bool                    Force
);
int DrsdInternalProbeModes(PDRSD_CONNECTOR Connector);