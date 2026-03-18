#include "DrsdCore.h"

DRIVER_EXPORT
LOUSTATUS 
DrsdModesetLock(
    PDRSD_MODESET_LOCK Lock, 
    PDRSD_MODESET_ACQURE_CONTEXT Ctx
){
    
    if(Ctx){

    }
    
    MutexLock(&Lock->Mutex);

    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS 
DrsdModesetUnlock(
    PDRSD_MODESET_LOCK Lock
){

    MutexUnlock(&Lock->Mutex);

    return STATUS_SUCCESS;
}