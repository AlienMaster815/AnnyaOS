#ifndef _USER_THREAD_H
#define _USER_THREAD_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdatomic.h>

typedef struct {
	uint64_t counter;
}atomic_t;

typedef atomic_t* p_atomic_t;

typedef struct _mutex_t{
    atomic_t locked;
    atomic_t Handle;
    atomic_t PrivaledgeLevel;
} mutex_t;

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

#ifdef __cplusplus
}
#endif
#endif