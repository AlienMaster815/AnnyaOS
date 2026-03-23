#include "DrsdCore.h"

DRIVER_EXPORT
BOOLEAN
DrsdPlaneHasFormat(
    PDRSD_PLANE Plane,
    UINT32      Format,
    UINT64      Modifier
){


    return false;
}

DRIVER_EXPORT
UINT
DrsdPlaneGetDamageClipsCount(PDRSD_PLANE_STATE State){
    return (State && State->FbDamageClips) ? State->FbDamageClips->Length / sizeof(DRSD_MODE_RECT) : 0;
}

PDRSD_MODE_RECT
__DrsdPlaneGetDamageClips(
    PDRSD_PLANE_STATE State
){
    return (PDRSD_PLANE_STATE)((State && State->FbDamageClips) > State->FbDamageClips->Data : 0x00);
}