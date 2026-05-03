#ifndef _THREADS_H
#define _THREADS_H

#ifdef __cplusplus
extern "C" {
#endif 

#include <cstdint.h>
#include <kernel/atomic.h>
#include <kernel/LKPCB.h>
#include <Modulation.h>

#include <WinAPI/Win32/winnt.h>

//TODO: Add 64 bit atomic values to lock out tag out 
//mechanism now that the kernel supports them

typedef struct _NT_CONTEXT{ //recreation of CONTEXT in WINAPI
    union{
        struct {
            DWORD           ContextFlags;
            DWORD           Cpsr;
            union{
                struct {
                    DWORD64     X0;
                    DWORD64     X1;
                    DWORD64     X2;
                    DWORD64     X3;
                    DWORD64     X4;
                    DWORD64     X5;
                    DWORD64     X6;
                    DWORD64     X7;
                    DWORD64     X8;
                    DWORD64     X9;
                    DWORD64     X10;
                    DWORD64     X11;
                    DWORD64     X12;
                    DWORD64     X13;
                    DWORD64     X14;
                    DWORD64     X15;
                    DWORD64     X16;
                    DWORD64     X17;
                    DWORD64     X18;
                    DWORD64     X19;
                    DWORD64     X20;
                    DWORD64     X21;
                    DWORD64     X22;
                    DWORD64     X23;
                    DWORD64     X24;
                    DWORD64     X25;
                    DWORD64     X26;
                    DWORD64     X27;
                    DWORD64     X28;
                    DWORD64     Fp;
                    DWORD64     Lr;
                };
                DWORD64         X[31];
            };
            DWORD64             Sp;
            DWORD64             Pc;
            ARM64_NT_NEON128    V[32];
            DWORD               Fpcr;
            DWORD               Fpsr;
            DWORD               Bcr[ARM64_MAX_BREAKPOINTS];
            DWORD64             Bvr[ARM64_MAX_BREAKPOINTS];
            DWORD               Wcr[ARM64_MAX_WATCHPOINTS];
            DWORD64             Wvr[ARM64_MAX_WATCHPOINTS];
        }Arm64;
        struct {    
            DWORD64             P1Home;
            DWORD64             P2Home;
            DWORD64             P3Home;
            DWORD64             P4Home;
            DWORD64             P5Home;
            DWORD64             P6Home;
            DWORD               ContextFlags;
            DWORD               McCsr;
            WORD                SegCs;
            WORD                SegDs;
            WORD                SegEs;
            WORD                SegFs;
            WORD                SegGs;
            WORD                SegSs;
            DWORD               EFlags;
            DWORD64             Dr0;
            DWORD64             Dr1;
            DWORD64             Dr2;
            DWORD64             Dr3;
            DWORD64             Dr6;
            DWORD64             Dr7;
            DWORD64             Rax;
            DWORD64             Rcx;
            DWORD64             Rdx;
            DWORD64             Rbx;
            DWORD64             Rsp;
            DWORD64             Rsi;
            DWORD64             Rdi;
            DWORD64             R8;
            DWORD64             R9;
            DWORD64             R10;
            DWORD64             R11;
            DWORD64             R12;
            DWORD64             R13;
            DWORD64             R14;
            DWORD64             R15;
            DWORD64             Rip;
            union{
                XMM_SAVE_AREA32 FltSave;
                NEON128         Q[16];
                ULONGLONG       D[32];
                struct{
                    M128A       Header[2];
                    M128A       Legacy[8];
                    M128A       Xmm0;
                    M128A       Xmm1;
                    M128A       Xmm2;
                    M128A       Xmm3;
                    M128A       Xmm4;
                    M128A       Xmm5;
                    M128A       Xmm6;
                    M128A       Xmm7;
                    M128A       Xmm8;
                    M128A       Xmm9;
                    M128A       Xmm10;
                    M128A       Xmm11;
                    M128A       Xmm12;
                    M128A       Xmm13;
                    M128A       Xmm14;
                    M128A       Xmm15;
                };
                DWORD           S[32];
            };
            M128A               VectorRegister;
            DWORD64             VectorControl;
            DWORD64             DebugControl;
            DWORD64             LastBranchToRip;
            DWORD64             LastBranchFromRip;
            DWORD64             LastExceptionToRip;
            DWORD64             LastExceptionFromRip;
        }Amd64;
    };
}NT_CONTEXT, * PNT_CONTEXT;

typedef struct _mutex_t{
    atomic_t locked;
    atomic_t Handle;
    atomic_t PrivaledgeLevel;
    atomic_t ThreadOwnerLow;
    atomic_t ThreadOwnerHigh;
} mutex_t;

typedef void* PTHREAD;
typedef void* PTHREAD_DATA;

#define MUTEX_FREE 0
#define MUTEX_LOCKED 1

#define ACTIVE_THREAD 0
#define INACTIVE_THREAD 1

#define LouKeMemoryBarrier() asm volatile("mfence" : : : "memory")
#define LouKePauseMemoryBarrier() asm volatile("pause" : : : "memory")

static inline void LouKeSetAtomic(atomic_t* A, int Value){
    atomic_set(A, Value);
}

static inline int LouKeGetAtomic(atomic_t* A){
    return atomic_read(A);
}

static inline void LouKeSetAtomic64(atomic_int64_t* A, int64_t Value){
    atomic64_set(A, Value);
}

static inline int64_t LouKeGetAtomic64(atomic_int64_t* A){
    return atomic64_read(A);
}

static inline void LouKeSetAtomic64FromUint64(UINT64* A, int64_t Value){
    atomic64_set((atomic_int64_t*)A, Value);
}

static inline int64_t LouKeGetAtomic64FromUint64(UINT64* A){
    return atomic64_read((atomic_int64_t*)A);
}

static inline void LouKeSetAtomicBoolean(PATOMIC_BOOLEAN b, int Boolean){
    LouKeSetAtomic(b, Boolean);
}

static inline bool LouKeGetAtomicBoolean(PATOMIC_BOOLEAN b){
    return (bool)LouKeGetAtomic(b);
}

static inline void MutexSynchronize(mutex_t* m){
    while (LouKeGetAtomic(&m->locked)) {
        // spin until it's unlocked
    }
}

static inline bool MutexIsLocked(mutex_t* m){
    return LouKeGetAtomic(&m->locked);
}

static inline void MutexUnlock(mutex_t* m){
    LouKeSetAtomic(&m->locked, 0);
}


static inline void MutexPriorityUnlock(mutex_t* m){
    m->Handle.counter = 0x00;
    m->PrivaledgeLevel.counter = 0x00;
    MutexUnlock(m);
}


typedef struct {
    mutex_t Lock;
    atomic_t ThreadOwner;
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
    atomic_t ThreadOwner;
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
#define LouKeDestroySemaphore(s) LouKeFree(s)

typedef enum{
    KERNEL_THREAD = 1,
    USER_THREAD = 2,
}THREAD_TYPE;

#ifndef _USER_MODE_CODE_

KERNEL_EXPORT
uint64_t
LouKeGetProcessIdentification();
KERNEL_EXPORT
uint64_t LouKeGetThreadIdentification();

uint32_t LouKeCreateUserProcess(void (*Function)(), PVOID FunctionParameters, size_t StackSize);
void LouKeInitializeDelayedWork(
    void (*DelayedFunction)(uint64_t PrivateData),
    uint64_t PrivateData,
    uint64_t MsDelay
);
void LouKeInitializeIntervalWork(
    void (*DelayedFunction)(uint64_t PrivateData),
    uint64_t PrivateData,
    uint64_t MsInterval
);

KERNEL_EXPORT void LouKeReportMutexBlock(mutex_t* m, UINT64 Thread);

KERNEL_EXPORT void LouKeAcquireSpinLock(spinlock_t* LockValue, LouKIRQL* Irql);
KERNEL_EXPORT void LouKeReleaseSpinLock(spinlock_t* LockValue, LouKIRQL* Irql);

void LouKeDestroyThread(PVOID ThreadHandle);

PTHREAD 
LouKeCreateDemon(
    PVOID   Function,
    PVOID   Params,
    size_t  StackSize,
    UINT8   Priority
);

PTHREAD
LouKeCreateDemonEx(
    PVOID   Function,
    PVOID   Params,
    size_t  StackSize,
    UINT8   Prioirty,
    BOOL    ProcessorSpecific,
    INTEGER Processor
);

PTHREAD
LouKeCreateDeferedDemonEx(
    PVOID   Function,
    PVOID   Params,
    size_t  StackSize,
    UINT8   Prioirty,
    BOOL    ProcessorSpecific,
    INTEGER Processor,
    PVOID   UnblockTimeHandle
);


PTHREAD 
LouKeCreateImp(
    PVOID   Function,
    PVOID   Params,
    size_t  StackSize,
    UINT8   Priority
);

PTHREAD
LouKeCreateImpEx(
    PVOID   Function,
    PVOID   Params,
    size_t  StackSize,
    UINT8   Prioirty,
    BOOL    ProcessorSpecific,
    INTEGER Processor
);

PTHREAD
LouKeCreateDeferedImpEx(
    PVOID   Function,
    PVOID   Params,
    size_t  StackSize,
    UINT8   Prioirty,
    BOOL    ProcessorSpecific,
    INTEGER Processor,
    PVOID   UnblockTimeHandle
);

void LouKeYeildExecution();

#endif


static void MutexLockEx(mutex_t* m, bool LockOutTagOut){
    #ifndef _USER_MODE_CODE_
    uint64_t Thread = (uint64_t)LouKeGetAtomic(&m->ThreadOwnerLow);
    Thread |= (((uint64_t)LouKeGetAtomic(&m->ThreadOwnerHigh)) << 32);
    if(LockOutTagOut){
        if(LouKeGetAtomic(&m->locked)){
            uint64_t Thread = (uint64_t)LouKeGetAtomic(&m->ThreadOwnerLow);
            Thread |= (((uint64_t)LouKeGetAtomic(&m->ThreadOwnerHigh)) << 32);
            LouKeReportMutexBlock(m, Thread);
        }
        while (__atomic_test_and_set(&m->locked.counter, 1)) {
            // spin
        }
    }else{
        if((Thread == LouKeGetThreadIdentification()) && (LouKeGetAtomic(&m->locked) == 0x01)){
            //access Granted
            return;
        }
        while (__atomic_test_and_set(&m->locked.counter, 1)) {
            // spin
        }
    }
    Thread = LouKeGetThreadIdentification();
    LouKeSetAtomic(&m->ThreadOwnerLow, Thread & 0xFFFFFFFF);
    LouKeSetAtomic(&m->ThreadOwnerHigh, Thread >> 32);
    #else

    

    #endif
}


static inline void MutexLock(mutex_t* m){
    MutexLockEx(m, true);
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

#ifdef __cplusplus
}
#endif
#endif