#ifndef _KERNEL_OBJECTS_H
#define _KERNEL_OBJECTS_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C"{
#endif

typedef struct _IDENTIFICATION_RANGE{
    string      RangeName;
    INTEGER     RangeStart;
    INTEGER     Entries;
    mutex_t     RangeLock;
    struct{
        INTEGER RangeID;
        PVOID   Object;
        BOOL    RangeAllocated;
    }Identities[];
}IDENTIFICATION_RANGE, * PIDENTIFICATION_RANGE;

#define LouKeDestroyIdentificationRange(x) LouKeFree(x)

PIDENTIFICATION_RANGE
LouKeCreateIdentificationRange(
    INTEGER RangeStart,
    INTEGER RangeEnd
);

void LouKeReleaseIdFromRange(
    PIDENTIFICATION_RANGE IdRange,
    INTEGER Id
);

INTEGER 
LouKeAcquireIdFromRange(
    PIDENTIFICATION_RANGE   IdRange,
    PVOID                   Object
);



typedef struct _KERNEL_REFERENCE{
    mutex_t     IncrementLock;
    mutex_t     RaceLock;
    atomic_t    ReferenceCounter;
    //TODO: Add variables as needed
}KERNEL_REFERENCE, * PKERNEL_REFERENCE;

static inline bool LouKeAcquireReference(PKERNEL_REFERENCE KRef){
    if(MutexIsLocked(&KRef->IncrementLock)){
        return false;
    }
    MutexLock(&KRef->RaceLock);
    UINT32 Tmp = (UINT32)LouKeGetAtomic(&KRef->ReferenceCounter);
    Tmp++;
    LouKeSetAtomic(&KRef->ReferenceCounter,Tmp);
    MutexUnlock(&KRef->RaceLock);
    return true;
}

static inline void LouKeReleaseReferece(PKERNEL_REFERENCE KRef){
    MutexLock(&KRef->RaceLock);
    UINT32 Tmp = (UINT32)LouKeGetAtomic(&KRef->ReferenceCounter);
    Tmp--;
    LouKeSetAtomic(&KRef->ReferenceCounter,Tmp);
    MutexUnlock(&KRef->RaceLock);
}


#ifdef __cplusplus
}
#endif

#endif