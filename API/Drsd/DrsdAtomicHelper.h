#ifndef _DRSD_ATOMIC_HELPER_H
#define _DRSD_ATOMIC_HELPER_H

#include "DrsdCore.h"

DRIVER_EXPORT
LOUSTATUS 
DrsdAtomicHelperResetCrtc(
    PDRSD_CRTC                      Crtc,
    PDRSD_MODESET_ACQURE_CONTEXT    Context
);



#endif