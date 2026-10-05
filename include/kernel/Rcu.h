#ifndef _RCU_H
#define _RCU_H

#include <kernel/threads.h>

#ifdef _RCU_INTERNALS

typedef struct _SRCU_OBJECT{
    atomic_t        Readers;
    mutex_t         ReadLock;
    mutex_t         WriteLock;
    PVOID           Items[2];
    SIZE            ItemSize;
}SRCU_OBJECT, * PSRCU_OBJECT, * PRCU_OBJECT;

#else
typedef PVOID PSRCU_OBJECT;
typedef PVOID PRCU_OBJECT;
#endif

KERNEL_EXPORT
LOUSTATUS 
LouKeCreateSrcuObject(
    PSRCU_OBJECT*   ObjectOut, 
    SIZE            ObjectSize, 
    SIZE            ObjectAlignment,
    UINT64          AllocationFlags
);

KERNEL_EXPORT
PVOID 
LouKeSrcuReadObjectAcquire(
    PSRCU_OBJECT SrcuObject
);

KERNEL_EXPORT
void 
LouKeSrcuReadObjectRelease(
    PSRCU_OBJECT SrcuObject
);

KERNEL_EXPORT
PVOID 
LouKeSrcuWriteObjectAcquire(
    PSRCU_OBJECT SrcuObject
);

#endif