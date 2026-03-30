#ifndef _TTM_RESOURCE_INTERNAL_H
#define _TTM_RESOURCE_INTERNAL_H

#include "../DrsdCore.h"

static inline void TtmResourceManagerSetUsed(
    PTTM_RESOURCE_MANAGER   Manager, 
    BOOLEAN                 Used
){
    //TODO:check for empty list and warn
    Manager->UseType = Used;
}

DRIVER_EXPORT
void 
TtmResourceManagerInitialize(
    PTTM_RESOURCE_MANAGER   Manager,
    PDRSD_TTM_DEVICE        Device,
    SIZE                    Size
);

#endif