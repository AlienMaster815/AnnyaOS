#ifndef _USER_THREAD_H
#define _USER_THREAD_H

#ifdef __cplusplus
extern "C"{
#endif

#include <kernel/atomic.h>

#define LouKeMemoryBarrier() asm volatile("mfence" : : : "memory")
#define LouKePauseMemoryBarrier() asm volatile("pause" : : : "memory")

static inline void LouKeSetAtomic(atomic_t* A, int Value){
    atomic_set(A, Value);
    LouKeMemoryBarrier();
}

typedef atomic_t* p_atomic_t;

#ifndef _MUTEX_STRUCTURE_DEFINITION
#define _MUTEX_STRUCTURE_DEFINITION
typedef struct _mutex_t{
    atomic_t locked;
    atomic_t Handle;
    atomic_t PrivaledgeLevel;
    atomic_t ThreadOwnerLow;
    atomic_t ThreadOwnerHigh;
} mutex_t;
#endif

typedef struct {
    mutex_t Lock;
    atomic_t ThreadOwner;
}spinlock_t;

typedef struct {
    atomic_t Lock;
    atomic_t Counter;
    atomic_t Limit;
    atomic_t ThreadOwner;
}semaphore_t;



static inline void LouSetAtomic(atomic_t* A, int Value){
    atomic_set(A, Value);
    LouKeMemoryBarrier();
}

static inline int LouGetAtomic(atomic_t* A){
    LouKeMemoryBarrier();
    return atomic_read(A);
}


static void MutexLockEx(mutex_t* m, bool LockOutTagOut){
    if(LockOutTagOut){
        while (__atomic_test_and_set(&m->locked.counter, 1)) {
            LouKeMemoryBarrier();
            // spin
        }
    }else{
        uint64_t Thread = (uint64_t)LouGetAtomic(&m->ThreadOwnerLow);
        Thread |= (((uint64_t)LouGetAtomic(&m->ThreadOwnerHigh)) << 32);
        #ifndef _USER_MODE_CODE_
        if((Thread == LouKeGetThreadIdentification()) && (LouGetAtomic(&m->locked) == 0x01)){
            //access Granted
            LouKeMemoryBarrier();
            return;
        }
        #else
            //TODO: Use User Mode Thread Request
        #endif
        while (__atomic_test_and_set(&m->locked.counter, 1)) {
            // spin
            LouKeMemoryBarrier();
        }
        #ifndef _USER_MODE_CODE_
        Thread = LouKeGetThreadIdentification();
        #else
            //TODO: Use User Mode Thread Request
        #endif
        LouSetAtomic(&m->ThreadOwnerLow, Thread & 0xFFFFFFFF);
        LouSetAtomic(&m->ThreadOwnerHigh, Thread >> 32);
    }
    LouKeMemoryBarrier();
}

static inline void MutexLock(mutex_t* m){
    MutexLockEx(m, true);
}

static inline void MutexSynchronize(mutex_t* m){
    while (m->locked.counter) {
        // spin until it's unlocked
        LouKeMemoryBarrier();
    }
}

static inline bool MutexIsLocked(mutex_t* m){
    LouKeMemoryBarrier();
    return m->locked.counter;
}

static inline void MutexUnlock(mutex_t* m){
    LouKeSetAtomic(&m->locked, 0);
    LouKeMemoryBarrier();
}

#ifdef __cplusplus
}
#endif
#endif