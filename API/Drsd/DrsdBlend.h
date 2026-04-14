#ifndef _DRSD_BLEND_INTERNAL_H
#define _DRSD_BLEND_INTERNAL_H

#include "DrsdCore.h"

static inline BOOLEAN DrsdRotation90Or270(UINT Rotation){
    return Rotation & (DRSD_MODE_ROTATE_90 | DRSD_MODE_ROTATE_270);
}

#endif