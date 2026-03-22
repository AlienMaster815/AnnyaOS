#ifndef _DRSD_COLOR_OP_INTERNAL_H
#define _DRSD_COLOR_OP_INTERNAL_H

#include "DrsdCore.h"

static inline UINT DrsdColorOpIndex(
    PDRSD_COLOR_OP ColorOp
){
    return ColorOp->Index;
}

void 
DrsdColorOpAtomicDestroyState(
    PDRSD_COLOR_OP          ColorOp,
    PDRSD_COLOR_OP_STATE    State
);

PDRSD_COLOR_OP_STATE
DrsdAtomicHelperColorOpDuplicateState(
    PDRSD_COLOR_OP ColorOp
);

#endif