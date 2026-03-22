#include "DrsdCore.h"


void 
DrsdColorOpAtomicDestroyState(
    PDRSD_COLOR_OP          ColorOp,
    PDRSD_COLOR_OP_STATE    State
){
    LouKeFree(State);
}

PDRSD_COLOR_OP_STATE
DrsdAtomicHelperColorOpDuplicateState(
    PDRSD_COLOR_OP ColorOp
){
    return 0x00;
}
