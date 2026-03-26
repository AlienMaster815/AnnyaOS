#include "DrsdCore.h"

DRIVER_EXPORT
LOUSTATUS 
DrsdGxeVRamDriverDumbCreate(
    PDRSD_FILE Dile, 
    PDRSD_DEVICE Device, 
    PDRSE_MODE_CREATE_DUMB Args
){
    LouPrint("DrsdGxeVRamDriverDumbCreate()\n");
    while(1);   
    return STATUS_SUCCESS;
}