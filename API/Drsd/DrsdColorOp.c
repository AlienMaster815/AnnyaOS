#include "DrsdCore.h"


void 
DrsdColorOpAtomicDestroyState(
    PDRSD_COLOR_OP          ColorOp,
    PDRSD_COLOR_OP_STATE    State
){
    LouKeFree(State);
}