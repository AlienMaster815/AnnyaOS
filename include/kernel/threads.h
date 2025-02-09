#ifndef _THREADS_H
#define _THREADS_H

typedef void* PTHREAD;
typedef void* PTHREAD_DATA;

#ifdef __cplusplus
#include <LouDDK.h>
#ifndef _KERNEL_MODULE_
LOUDDK_API_ENTRY LOUSTATUS LouKeCreateThread(void (*Function)(), PVOID FunctionParameters, uint32_t StackSize);
LOUDDK_API_ENTRY uintptr_t LouKeCreateUserStackThread(void (*Function)(), PVOID FunctionParameters, uint32_t StackSize);
KERNEL_IMPORT uint32_t LouKeCreateUserProcess(void (*Function)(), PVOID FunctionParameters, uint32_t StackSize);
#else
KERNEL_EXPORT LOUSTATUS LouKeCreateThread(void (*Function)(), PVOID FunctionParameters, uint32_t StackSize);

#endif
extern "C" {
#else
#include <LouAPI.h>
typedef void* PVOID; 
LOUSTATUS LouKeCreateThread(void (*Function)(), PVOID FunctionParameters, uint32_t StackSize);
uint32_t LouKeCreateUserProcess(void (*Function)(), PVOID FunctionParameters, uint32_t StackSize);
uintptr_t LouKeCreateUserStackThread(void (*Function)(), PVOID FunctionParameters, uint32_t StackSize);
#endif

#define MUTEX_FREE 0
#define MUTEX_LOCKED 1

#define ACTIVE_THREAD 0
#define INACTIVE_THREAD 1


#pragma pack(push,1)
typedef struct {
    bool locked;
    uintptr_t Handle;
    uint64_t  PrivaledgeLevel;
} mutex_t;
#pragma pack(pop)

static inline void MutexLock(mutex_t* m){
    while(m->locked == true){
        //spinlock
    }
    m->locked = true;
}

static inline void MutexSyncronize(mutex_t* m){
    while(m->locked){
        //spinlock
    }
}


static inline void MutexUnlock(mutex_t* m){
    m->locked = false;
}

static inline uintptr_t MutexPriorityLock(
    mutex_t* m, 
    uintptr_t Handle, 
    uint64_t Privaledge
){

    if((m->locked) && (m->PrivaledgeLevel < Privaledge)){
        uintptr_t OldHandle = m->Handle;
        m->Handle = Handle;
        m->PrivaledgeLevel = Privaledge;
        return OldHandle;
    }
    MutexLock(m);
    return 0;
}

static inline void MutexPriorityUnlock(mutex_t* m){
    m->Handle = 0x00;
    m->PrivaledgeLevel = 0x00;
    MutexUnlock(m);
}

typedef struct {
    mutex_t Lock;
}spinlock_t;

static inline void SpinlockSyncronize(spinlock_t* s){
    while(s->Lock.locked){

    }
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