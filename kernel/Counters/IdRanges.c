#include <LouAPI.h>


INTEGER 
LouKeAcquireIdFromRange(
    PIDENTIFICATION_RANGE   IdRange,
    PVOID                   Object
){
    if((!IdRange) || (!Object)){
        return (INTEGER)-1;
    }
    MutexLock(&IdRange->RangeLock);
    INTEGER MemberCount = IdRange->Entries;
    INTEGER Result = (INTEGER)-1;
    for(INTEGER i = 0; i < MemberCount; i++){
        if(!IdRange->Identities[i].RangeAllocated){
            Result = IdRange->Identities[i].RangeID;
            IdRange->Identities[i].Object = Object;
            IdRange->Identities[i].RangeAllocated = true;
            break;
        }
    }
    MutexUnlock(&IdRange->RangeLock);
    return Result;
}

void LouKeReleaseIdFromRange(
    PIDENTIFICATION_RANGE IdRange,
    INTEGER Id
){
    if((!IdRange) ||  (Id >= (IdRange->RangeStart + IdRange->Entries)) || (Id < IdRange->RangeStart)){
        return;
    }
    MutexLock(&IdRange->RangeLock);
    IdRange->Identities[Id - IdRange->RangeStart].RangeAllocated = false;
    IdRange->Identities[Id - IdRange->RangeStart].Object = 0x00;
    MutexUnlock(&IdRange->RangeLock);
}

PIDENTIFICATION_RANGE
LouKeCreateIdentificationRange(
    INTEGER RangeStart,
    INTEGER RangeEnd
){
    PIDENTIFICATION_RANGE Result = 0x00;
    INTEGER MemberCount; 
    if(RangeStart > RangeEnd){
        return 0x00;
    }
    MemberCount = (RangeEnd - RangeStart) + 1;
    Result = LouKeMallocEx(GetStructureSize(Result, Identities, MemberCount), GET_ALIGNMENT(IDENTIFICATION_RANGE), KERNEL_GENERIC_MEMORY);
    Result->RangeStart = RangeStart; 
    Result->Entries = MemberCount;

    for(INTEGER i = 0 ; i < MemberCount; i++){
        Result->Identities[i].RangeID = RangeStart + i;  
        Result->Identities[i].Object = 0x00;
        Result->Identities[i].RangeAllocated = false;
    }
    return Result;
}