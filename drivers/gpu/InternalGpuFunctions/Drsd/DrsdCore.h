#include <LouDDK.h>

void DrsdAtomicDestroyPlaneState(
    PDRSD_PLANE_STATE PlaneState
);

void DrsdModeObjectObjectFree(PDRSD_MODE_OBJECT Object);

void DrsdGxeDestroyShadowPlane(
    PDRSD_PLANE Plane
);

void DrsdResetCrtcVBlank(
    PDRSD_CRTC Crtc
);

void AddVBlankToCrtc(PDRSD_DEVICE Device);

size_t GetDrsdCrtcIndex(PDRSD_CRTC Crtc);