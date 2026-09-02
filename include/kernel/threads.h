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

typedef struct _NT_ARM64_CONTEXT{
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
}NT_ARM64_CONTEXT, * PNT_ARM64_CONTEXT;

typedef struct _NT_AMD64_CONTEXT {
    DWORD64             P1Home;                 // 0x0000
    DWORD64             P2Home;                 // 0x0008
    DWORD64             P3Home;                 // 0x0010
    DWORD64             P4Home;                 // 0x0018
    DWORD64             P5Home;                 // 0x0020
    DWORD64             P6Home;                 // 0x0028
    DWORD               ContextFlags;           // 0x0030
    DWORD               MxCsr;                  // 0x0034
    WORD                SegCs;                  // 0x0038
    WORD                SegDs;                  // 0x003A
    WORD                SegEs;                  // 0x003C
    WORD                SegFs;                  // 0x003E
    WORD                SegGs;                  // 0x0040
    WORD                SegSs;                  // 0x0042
    DWORD               EFlags;                 // 0x0044
    DWORD64             Dr0;                    // 0x0048
    DWORD64             Dr1;                    // 0x0050
    DWORD64             Dr2;                    // 0x0058
    DWORD64             Dr3;                    // 0x0060
    DWORD64             Dr6;                    // 0x0068
    DWORD64             Dr7;                    // 0x0070
    DWORD64             Rax;                    // 0x0078
    DWORD64             Rcx;                    // 0x0080
    DWORD64             Rdx;                    // 0x0088
    DWORD64             Rbx;                    // 0x0090
    DWORD64             Rsp;                    // 0x0098
    DWORD64             Rbp;                    // 0x00A0
    DWORD64             Rsi;                    // 0x00A8
    DWORD64             Rdi;                    // 0x00B0
    DWORD64             R8;                     // 0x00B8
    DWORD64             R9;                     // 0x00C0
    DWORD64             R10;                    // 0x00C8
    DWORD64             R11;                    // 0x00D0
    DWORD64             R12;                    // 0x00D8
    DWORD64             R13;                    // 0x00E0
    DWORD64             R14;                    // 0x00E8
    DWORD64             R15;                    // 0x00F0
    DWORD64             Rip;                    // 0x00F8
    union{
        XMM_SAVE_AREA32 FltSave;                // 0x0100
        struct {
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
    };                                          // 0x0100
    M128A               VectorRegister[26];     // 0x0300
    DWORD64             VectorControl;          // 0x04A0
    DWORD64             DebugControl;           // 0x04A8
    DWORD64             LastBranchToRip;        // 0x04B0
    DWORD64             LastBranchFromRip;      // 0x04B8
    DWORD64             LastExceptionToRip;     // 0x04C0
    DWORD64             LastExceptionFromRip;   // 0x04C8
} NT_AMD64_CONTEXT, *PNT_AMD64_CONTEXT;


typedef struct _NT_CONTEXT{ //recreation of CONTEXT in WINAPI
    union{
        NT_ARM64_CONTEXT Arm64;
        NT_AMD64_CONTEXT Amd64;
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

static inline void LouKeSetAtomic64(atomic64_t* A, int64_t Value){
    atomic64_set(A, Value);
}

static inline int64_t LouKeGetAtomic64(atomic64_t* A){
    return atomic64_read(A);
}



static inline void LouKeSetAtomic64FromUint64(atomic64_t* A, uint64_t Value) {
    union { uint64_t u; int64_t i; } converter;
    converter.u = Value;
    A->counter = converter.i;
}

static inline uint64_t LouKeGetAtomic64FromUint64(atomic64_t* A) {
    union { uint64_t u; int64_t i; } converter;
    converter.i = A->counter;
    return converter.u;
}


static inline void LouKeSetAtomicBoolean(PATOMIC_BOOLEAN b, int Boolean){
    LouKeSetAtomic(b, Boolean);
}

static inline bool LouKeGetAtomicBoolean(PATOMIC_BOOLEAN b){
    return (bool)LouKeGetAtomic(b);
}

#ifndef _USER_MODE_CODE_
KERNEL_EXPORT void LouKeYieldExecution();
static inline void MutexSynchronize(mutex_t* m){
    while (LouKeGetAtomic(&m->locked)) {
        LouKeYieldExecution();
    }
}
#endif

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
    mutex_t     Check;
    mutex_t     Lock;
    atomic_t    ThreadOwner;
}spinlock_t;

typedef struct {
    mutex_t     Check;
    mutex_t     Unlock;
    atomic_t    Counter;
    atomic_t    Limit;
}semaphore_t;


static inline void SpinlockSyncronize(spinlock_t* s){
    while (LouKeGetAtomic(&s->Lock.locked)){
        // spin until unlocked
    }
}

static inline bool SpinlockIsLocked(spinlock_t* s){
    return (bool)LouKeGetAtomic(&s->Lock.locked);
}

typedef enum{
    KERNEL_THREAD = 1,
    USER_THREAD = 2,
}THREAD_TYPE;

typedef struct _EXLO_MUTEX{
    mutex_t         ExloLock;
    semaphore_t     Counter;
    atomic64_t  ExloThread;
    atomic_t        GracePeriod;
}EXLO_MUTEX, * PEXLO_MUTEX;

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


KERNEL_EXPORT void LouKeUnblockThread(UINT64 ThreadID);
KERNEL_EXPORT void LouKeBlockThread(UINT64 ThreadID);
KERNEL_EXPORT UINT64 LouKeGetThreadIdentificationFromThreadHandle(PTHREAD ThreadHandle);

LOUSTATUS 
LouKeInitializeExloMutexEx(
    PEXLO_MUTEX     ExloMutex,
    UINT64          ExloThread,
    int             GracePeriod
);

KERNEL_EXPORT
LOUSTATUS 
LouKeInitializeExloMutex(
    PEXLO_MUTEX     ExloMutex,
    UINT64          ExloThread
);

#endif

KERNEL_EXPORT void MutexDestroy(mutex_t* m);
KERNEL_EXPORT void MutexInitialize(mutex_t* m);

static void AtomicLockEx(mutex_t* m, bool LockOutTagOut){
    #ifndef _USER_MODE_CODE_
    uint64_t Thread = (uint64_t)LouKeGetAtomic(&m->ThreadOwnerLow);
    Thread |= (((uint64_t)LouKeGetAtomic(&m->ThreadOwnerHigh)) << 32);
    BOOLEAN Reported = false;
    if(LockOutTagOut){
        while (__atomic_test_and_set(&m->locked, 1)) {
            if(!Reported){
                LouKeReportMutexBlock(m, Thread);
                Reported = true;
            }
            // spin
        }
    }else{
        if((Thread == LouKeGetThreadIdentification()) && (LouKeGetAtomic(&m->locked) == 0x01)){
            //access Granted
            return;
        }
        while (__atomic_test_and_set(&m->locked, 1)) {
            // spin
        }
    }
    Thread = LouKeGetThreadIdentification();
    LouKeSetAtomic(&m->ThreadOwnerLow, Thread & 0xFFFFFFFF);
    LouKeSetAtomic(&m->ThreadOwnerHigh, Thread >> 32);
    #else

    

    #endif
}

static BOOLEAN AtomicLockOrFalseEx(mutex_t* m, bool LockOutTagOut){
    #ifndef _USER_MODE_CODE_
    uint64_t Thread = (uint64_t)LouKeGetAtomic(&m->ThreadOwnerLow);
    Thread |= (((uint64_t)LouKeGetAtomic(&m->ThreadOwnerHigh)) << 32);
    if(LockOutTagOut){
        if(__atomic_test_and_set(&m->locked, 1)) {
            LouKeReportMutexBlock(m, Thread);
            return false;
        }
    }else{
        if((Thread == LouKeGetThreadIdentification()) && (LouKeGetAtomic(&m->locked) == 0x01)){
            //access Granted
            return true;
        }
        if(__atomic_test_and_set(&m->locked, 1)) {
            LouKeReportMutexBlock(m, Thread);
            return false;
        }
    }
    Thread = LouKeGetThreadIdentification();
    LouKeSetAtomic(&m->ThreadOwnerLow, Thread & 0xFFFFFFFF);
    LouKeSetAtomic(&m->ThreadOwnerHigh, Thread >> 32);
    #else

    

    #endif
    return true;
}


static void MutexLockEx(mutex_t* m, bool LockOutTagOut){
    #ifndef _USER_MODE_CODE_
    uint64_t Thread = (uint64_t)LouKeGetAtomic(&m->ThreadOwnerLow);
    Thread |= (((uint64_t)LouKeGetAtomic(&m->ThreadOwnerHigh)) << 32);
    BOOLEAN Reported = false;
    if(LockOutTagOut){
        while(__atomic_test_and_set(&m->locked, 1)){
            if(!Reported){
                LouKeReportMutexBlock(m, Thread);
                Reported = true;
            }
            LouKeYieldExecution();
        }
    }else{
        if((Thread == LouKeGetThreadIdentification()) && (LouKeGetAtomic(&m->locked) == 0x01)){
            //access Granted
            return;
        }
        while (__atomic_test_and_set(&m->locked, 1)) {
            LouKeYieldExecution();
        }
    }
    Thread = LouKeGetThreadIdentification();
    LouKeSetAtomic(&m->ThreadOwnerLow, Thread & 0xFFFFFFFF);
    LouKeSetAtomic(&m->ThreadOwnerHigh, Thread >> 32);
    #else

    

    #endif
}


static inline void AtomicLock(mutex_t* m){
    AtomicLockEx(m, true);
}

static inline BOOLEAN AtomicLockOrFalse(mutex_t* m){
    return AtomicLockOrFalseEx(m, true);
}

static inline void MutexLock(mutex_t* m){
    MutexLockEx(m, true);
}

int LouPrint(char*, ...);

static inline void SemaphoreLock(semaphore_t* sem) {
    MutexLock(&sem->Check);
    while(!LouKeGetAtomic(&sem->Counter)){
        // spin until semaphore goes below limit
    }
    LouKeSetAtomic(&sem->Counter, LouKeGetAtomic(&sem->Counter) - 1);
    MutexUnlock(&sem->Check);
}

static inline BOOLEAN SemaphoreLockOrFalse(semaphore_t* sem) {
    BOOLEAN Result = true;
    MutexLock(&sem->Check);
    if(!LouKeGetAtomic(&sem->Counter)){
        Result = false;
    }else{
        LouKeSetAtomic(&sem->Counter, LouKeGetAtomic(&sem->Counter) - 1);
    }
    MutexUnlock(&sem->Check);
    return Result;
}

static inline void SemaphoreUnlock(semaphore_t* sem) {
    MutexLock(&sem->Unlock);
    LouKeSetAtomic(&sem->Counter, LouKeGetAtomic(&sem->Counter) - 1);
    MutexUnlock(&sem->Unlock);
}

static inline void SemaphoreInitialize(semaphore_t* sem, int initial, int limit) {
    if (!sem) return;
    MutexUnlock(&sem->Check);
    atomic_set(&sem->Counter, initial);
    atomic_set(&sem->Limit, limit);
}

static inline BOOLEAN SemaphoreBeingUsed(semaphore_t* sem) {
    return (LouKeGetAtomic(&sem->Counter) == LouKeGetAtomic(&sem->Limit));
}

semaphore_t* LouKeCreateSemaphore(int initial, int limit);
#define LouKeDestroySemaphore(s) LouKeFree(s)

#ifdef __cplusplus
}
#endif
#endif