#include "DrsdCore.h"

DRIVER_EXPORT
LOUSTATUS 
DrsdGxeBeginShadowFbAccess(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
){
    PDRSD_SHADOW_PLANE_STATE ShadowPlaneState = ToDrsdShadowPlaneState(PlaneState);
    PDRSD_FRAME_BUFFER Fb = PlaneState->FrameBuffer;

    if(!Fb){
        return STATUS_SUCCESS;
    }

    return DrsdGxeFbVMap(Fb, ShadowPlaneState->Map, ShadowPlaneState->Data);
}

DRIVER_EXPORT
void 
DrsdGxeEndShadowFbAccess(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   State
){
    LouPrint("DRSDCORE.SYS:DrsdGxeEndShadowFbAccess()\n");
    while(1);
}