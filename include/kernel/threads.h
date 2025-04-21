#ifndef _THREADS_H
#define _THREADS_H

typedef void* PTHREAD;
typedef void* PTHREAD_DATA;


#ifdef __cplusplus
#include <LouDDK.h>
#ifndef _KERNEL_MODULE_
LOUDDK_API_ENTRY LOUSTATUS LouKeCreateThread(void (*Function)(), PVOID FunctionParameters, uint32_t StackSize);
LOUDDK_API_ENTRY uintptr_t LouKeCreateUserStackThread(void (*Function)(), PVOID FunctionParameters, size_t StackSize);
KERNEL_IMPORT uint32_t LouKeCreateUserProcess(void (*Function)(), PVOID FunctionParameters, uint32_t StackSize);
#else
KERNEL_EXPORT LOUSTATUS LouKeCreateThread(void (*Function)(), PVOID FunctionParameters, size_t StackSize);

#endif
extern "C" {
#else
#include <LouAPI.h>
typedef void* PVOID; 
LOUSTATUS LouKeCreateThread(void (*Function)(), PVOID FunctionParameters, size_t StackSize);
uint32_t LouKeCreateUserProcess(void (*Function)(), PVOID FunctionParameters, size_t StackSize);
uintptr_t LouKeCreateUserStackThread(void (*Function)(), PVOID FunctionParameters, size_t StackSize);
#endif

#define MUTEX_FREE 0
#define MUTEX_LOCKED 1

#define ACTIVE_THREAD 0
#define INACTIVE_THREAD 1

#include "atomic.h"

typedef struct {
    atomic_t  locked;
    uintptr_t Handle;
    uint64_t  PrivaledgeLevel;
} mutex_t;



static inline void MutexLock(mutex_t* m){
    SetAtomic(&m->locked);
}

static inline void MutexSyncronize(mutex_t* m){
    while(TestAtomic(&m->locked)){
        //spinlock
    }
}

static inline bool MutexIsLocked(mutex_t* m){
    if(TestAtomic(&m->locked))return true;
    return false;
}



static inline void MutexUnlock(mutex_t* m){
    UnsetAtomic(&m->locked);
}

typedef struct _spinlock_t{
    mutex_t     Lock;
    LouKIRQL    Irql;
}spinlock_t;

static inline void SpinlockSyncronize(spinlock_t* s){
    while(TestAtomic(&s->Lock.locked)){

    }
}

static inline bool SpinlockIsLocked(spinlock_t* s){
    if(TestAtomic(&s->Lock.locked))return true;
    return false;
}

typedef struct {
    atomic_t    Count;
    atomic_t    Limit; 
    mutex_t     Lock;
}semaphore_t;

static inline void SemaphoreLock(semaphore_t* S){
    atomic_t old = AtomicFetchAdd(&S->Count, 1);
    if (old >= S->Limit) {
        MutexLock(&S->Lock);
    }    
}

static inline void SemaphoreUnlock(semaphore_t* S){
    atomic_t old = AtomicFetchSub(&S->Count, 1);
    if (old > S->Limit) {
        MutexUnlock(&S->Lock);
    }    
}

static inline void SemaphoreInitialize(semaphore_t* S, atomic_t Limit){
    SetAtomicValue(&S->Limit, Limit);
    SetAtomicValue(&S->Count, 0);
}

#ifndef _KERNEL_MODULE_
void LouKeAcquireSpinLock(spinlock_t* LockValue, LouKIRQL* Irql);
void LouKeReleaseSpinLock(spinlock_t* LockValue, LouKIRQL* Irql);
#else 
KERNEL_EXPORT void LouKeAcquireSpinLock(spinlock_t* LockValue, LouKIRQL* Irql);
KERNEL_EXPORT void LouKeReleaseSpinLock(spinlock_t* LockValue, LouKIRQL* Irql);
#endif
#ifdef __cplusplus
}
#endif


typedef enum{
    KERNEL_THREAD = 1,
    USER_THREAD = 2,
}THREAD_TYPE;


#endif