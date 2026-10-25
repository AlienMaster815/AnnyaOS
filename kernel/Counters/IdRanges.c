#include <LouAPI.h>

KERNEL_EXPORT
INTEGER 
LouKeAcquireIdFromRange(
    PIDENTIFICATION_RANGE   IdRange,
    PVOID                   Object
){
    if(!IdRange){
        return (INTEGER)-1;
    }
    UINT64 Start = (UINT64)IdRange->IdRangeStart; 
    LOUSTATUS Status = LouKeXaAllocateUint64(&IdRange->IdRangeData, &Start, Object, (UINT64)IdRange->IdRangeEnd, KERNEL_GENERIC_MEMORY);
    if(Status != STATUS_SUCCESS){
        return (INTEGER)-1;
    }
    return (INTEGER)Start;
}

KERNEL_EXPORT
void LouKeReleaseIdFromRange(
    PIDENTIFICATION_RANGE   IdRange,
    INTEGER                 Id
){
    if(!IdRange){
        return;
    }
    LouKeXaFreeUint64(&IdRange->IdRangeData, (UINT64)Id);
}

KERNEL_EXPORT
PIDENTIFICATION_RANGE
LouKeCreateIdentificationRange(
    INTEGER RangeStart,
    INTEGER RangeEnd
){
    PIDENTIFICATION_RANGE NewRange = LouKeMallocType(IDENTIFICATION_RANGE, KERNEL_GENERIC_MEMORY);
    if(!NewRange){
        return NewRange;
    }
    NewRange->IdRangeStart = RangeStart;
    NewRange->IdRangeEnd = RangeEnd;
    return NewRange;
}