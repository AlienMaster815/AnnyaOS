#ifndef _DRSD_PLANE_INTERNAL_H
#define _DRSD_PLANE_INTERNAL_H

#include "DrsdCore.h"

static inline UINT DrsdPlaneIndex(PDRSD_PLANE Plane){
    return Plane->Index;
}

DRIVER_EXPORT
BOOLEAN
DrsdPlaneHasFormat(
    PDRSD_PLANE Plane,
    UINT32      Format,
    UINT64      Modifier
);

#endif