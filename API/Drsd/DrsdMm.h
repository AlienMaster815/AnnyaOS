#ifndef _DRSD_MM_INTERNAL_H
#define _DRSD_MM_INTERNAL_H
    
#include "DrsdCore.h"

DRIVER_EXPORT
void 
DrsdMmInitialize(
    PDRSD_MM    Mm, 
    UINT64      Start, 
    UINT64      Size
);

#endif