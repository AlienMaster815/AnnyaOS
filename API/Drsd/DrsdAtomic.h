#ifndef _DRSD_ATOMIC_H
#define _DRSD_ATOMIC_H
#include "DrsdCore.h"

DRIVER_EXPORT
PDRSD_CONNECTOR 
DrsdAtomicGetConnectorForEncoder(
    PDRSD_ENCODER                   Encoder,
    PDRSD_MODESET_ACQURE_CONTEXT    Context
);

DRIVER_EXPORT 
BOOLEAN 
IsDrsdAtomicGetConnectorForEncoderError(
    PDRSD_CONNECTOR Connector
);

#endif