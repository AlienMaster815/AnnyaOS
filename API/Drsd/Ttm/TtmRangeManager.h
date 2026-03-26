#ifndef _TTM_RANGE_MANAGER_INTERNAL_H
#define _TTM_RANGE_MANAGER_INTERNAL_H

#include "../DrsdCore.h"

LOUSTATUS 
TtmRangeManagerInitializeNoCheck(
    PDRSD_TTM_DEVICE    TtmDevice,
    UINT                Type,
    BOOLEAN             UseTt,
    UINT64              Size
);

FORCE_INLINE
LOUSTATUS 
TtmRangeManagerInitialize(
    PDRSD_TTM_DEVICE    TtmDevice,
    UINT                Type,
    BOOLEAN             UseTt,
    UINT64              Size
){
    if(Type >= TTM_MEM_TYPES_COUNT){
        return STATUS_INVALID_PARAMETER;
    }
    return TtmRangeManagerInitializeNoCheck(TtmDevice, Type, UseTt, Size);
}

#endif