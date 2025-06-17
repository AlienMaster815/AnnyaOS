#include "DrsdCore.h"


void DrsdGxeDestroyShadowPlane(
    PDRSD_PLANE Plane
){

    DrsdAtomicDestroyPlaneState(Plane->PlaneState);

    LouPrint("DrsdGxeDestroyShadowPlane() STATUS_SUCCESS\n");
}