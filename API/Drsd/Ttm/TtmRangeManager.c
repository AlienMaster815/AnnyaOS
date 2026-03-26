#include "../DrsdCore.h"

LOUSTATUS 
TtmRangeManagerInitializeNoCheck(
    PDRSD_TTM_DEVICE    TtmDevice,
    UINT                Type,
    BOOLEAN             UseTt,
    UINT64              Size
){
    /*PTTM_RESOURCE_MANAGER   Manager;
    PTTM_RANGE_MANAGER      RManager;

    RManager = LouKeMallocType(TTM_RANGE_MANAGER, KERNEL_GENERIC_MEMORY);
    if(!RManager){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Manager = &RManager;
    Manager->UseTt = UseTt;*/

    LouPrint("TtmRangeManagerInitializeNoCheck()\n");
    while(1);
    return STATUS_SUCCESS;
}