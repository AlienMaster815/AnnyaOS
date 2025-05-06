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

typedef struct _mutex_t{
    atomic_t locked;
    atomic_t Handle;
    atomic_t PrivaledgeLevel;
} mutex_t;

static inline void MutexLock(mutex_t* m){
    while (__atomic_test_and_set(&m->locked.counter, __ATOMIC_ACQUIRE)) {
        // spin
    }
}

static inline void MutexSynchronize(mutex_t* m){
    while (m->locked.counter) {
        // spin until it's unlocked
    }
}

static inline bool MutexIsLocked(mutex_t* m){
    return m->locked.counter;
}

static inline void MutexUnlock(mutex_t* m){
    __atomic_clear(&m->locked.counter, __ATOMIC_RELEASE);
}

static inline uintptr_t MutexPriorityLock(
    mutex_t* m, 
    uintptr_t Handle, 
    int Privaledge
){
    if((m->locked.counter) && (m->PrivaledgeLevel.counter < Privaledge)){
        uintptr_t OldHandle = m->Handle.counter;
        m->Handle.counter = Handle;
        m->PrivaledgeLevel.counter = Privaledge;
        return OldHandle;
    }
    MutexLock(m);
    return 0;
}

static inline void MutexPriorityUnlock(mutex_t* m){
    m->Handle.counter = 0x00;
    m->PrivaledgeLevel.counter = 0x00;
    MutexUnlock(m);
}


typedef struct {
    mutex_t Lock;
}spinlock_t;

static inline void SpinlockSyncronize(spinlock_t* s){
    while (s->Lock.locked.counter){
        // spin until unlocked
    }
}

static inline bool SpinlockIsLocked(spinlock_t* s){
    return s->Lock.locked.counter;
}

typedef struct {
    atomic_t Lock;
    atomic_t Counter;
    atomic_t Limit;
}semaphore_t;

static inline void SemaphoreLock(semaphore_t* sem) {
    while (1) {
        int val = atomic_read(&sem->Counter);
        if (val <= 0)
            continue;
        if (atomic_cmpxchg(&sem->Counter, val, val - 1))
            break;
    }
}


static inline void SemaphoreUnlock(semaphore_t* sem) {
    while (1) {
        int val = atomic_read(&sem->Counter);
        int lim = atomic_read(&sem->Limit);
        if (val >= lim)
            break;
        if (atomic_cmpxchg(&sem->Counter, val, val + 1))
            break;
    }
}

static inline void SemaphoreInitialize(semaphore_t* sem, int initial, int limit) {
    if (!sem) return;
    atomic_set(&sem->Lock, 0);
    atomic_set(&sem->Counter, initial);
    atomic_set(&sem->Limit, limit);
}
semaphore_t* LouKeCreateSemaphore(int initial, int limit);

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