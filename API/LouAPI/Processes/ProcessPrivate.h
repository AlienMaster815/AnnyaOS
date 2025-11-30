#ifndef _PROCESS_PRIVATE_H
#define _PROCESS_PRIVATE_H
#include <LouDDK.h>
#include <KulaAPI.h>

typedef enum {
    THREAD_READY = 0,
    THREAD_RUNNING = 1,
    THREAD_TERMINATED = 2,
    THREAD_BLOCKED = 3,
} thread_state_t;

typedef struct  PACKED _CPUContext{
    // General-Purpose Registers    
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;

    uint64_t rbp;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r8;

    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;

    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;

    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} CPUContext;

KERNEL_IMPORT void SaveEverything(uint64_t* ContextHandle);
KERNEL_IMPORT void RestoreEverything(uint64_t* ContextHandle);

#define CTXMGR_DEFAULT_SAVE_EVERYTHING      SaveEverything
#define CTXMGR_DEFAULT_RESTORE_EVERYTHING   RestoreEverything

#define IS_PROCESSOR_AFFILIATED(Bitmap, Processor) ((Bitmap)[(Processor) / 8] &  (1u << ((Processor) % 8)))
#define MARK_PROCESSOR_AFFILIATED(Bitmap, Processor) ((Bitmap)[(Processor) / 8] |=  (1u << ((Processor) % 8)))
#define UNMARK_PROCESSOR_AFFILIATED(Bitmap, Processor) ((Bitmap)[(Processor) / 8] &=  (1u << ((Processor) % 8)))

typedef enum {
    LONG_MODE       = 0,
    PROTECTED_MODE  = 1,
    REAL_MODE       = 2,
}INSTRUCTION_MODE;

typedef struct _GENERIC_THREAD_DATA{
    ListHeader          Peers; //thread manager chain
    mutex_t             LockOutTagOut;
    thread_state_t      State;
    INTEGER             Cpu;
    PPEB                Peb;
    CPUContext          SavedState;
    CPUContext*         CurrentState;
    TEB                 Teb;
    INTEGER             ThreadID;
    UINT64              StackBase;
    UINT64              StackTop;
    UINT64              InterruptStorage;
    UINT64              ContextStorage;
    UINT64              TotalMsSlice;
    UINT64              CurrentMsSlice;
    TIME_T              ThreadStart;
    TIME_T              BlockTimeout;
    BOOL                NewThread;
    UINT8               Cs;
    UINT8               Ss;
    INSTRUCTION_MODE    InstructionMode;
    UINT8*              AfinityBitmap;
}GENERIC_THREAD_DATA, * PGENERIC_THREAD_DATA;

typedef struct THREAD_RING{
    ListHeader              Peers; //schedualer chain
    GENERIC_THREAD_DATA     ThreadData;
}THREAD_RING, * PTHREAD_RING;

#define USER_THREAD_RING_ID     1
#define DEMON_THREAD_RING_ID    2

#define THREAD_PRIORITY_RINGS 32

#define PROCESS_PRIORITY_HIGH       0
#define PROCESS_PRIORITY_ABOVE      1
#define PROCESS_PRIORITY_NORMAL     2
#define PROCESS_PRIORITY_BELOW      3
#define PROCESS_PRIORITY_LOW        4
#define PROCESS_PRIORITY_RINGS      5

#define THREAD_PRIORITY_HIGH        PROCESS_PRIORITY_HIGH
#define THREAD_PRIORITY_ABOVE       PROCESS_PRIORITY_ABOVE
#define THREAD_PRIORITY_NORMAL      PROCESS_PRIORITY_NORMAL
#define THREAD_PRIORITY_BELOW       PROCESS_PRIORITY_BELOW
#define THREAD_PRIORITY_LOW         PROCESS_PRIORITY_LOW

typedef struct _SCHEDUALER_DISTRIBUTION_OBJECT{
    UINT64              TotalLimiters;
    UINT64              LimitIncrementor;
    UINT64              CurrentLimiter; //prioirty dips in goaround
    UINT64              CurrentIndexor;
}SCHEDUALER_DISTRIBUTION_OBJECT, * PSCHEDUALER_DISTRIBUTION_OBJECT;

static inline UINT8 EulerCurveIndexor(PSCHEDUALER_DISTRIBUTION_OBJECT Sched){
    Sched->CurrentIndexor++;
    Sched->CurrentIndexor %= Sched->CurrentLimiter; 
    if(!Sched->CurrentIndexor){
        Sched->CurrentLimiter += Sched->LimitIncrementor;
        if(Sched->CurrentLimiter > Sched->TotalLimiters){// over 32 set to 1
            Sched->CurrentLimiter = 1;
        }
    }
    return Sched->CurrentIndexor;
}

static inline LOUSTATUS CreateShecdualerObject(
    PSCHEDUALER_DISTRIBUTION_OBJECT ObjectIn,
    UINT64                          TotalLimiters,
    UINT64                          LimitIncrementor
){
    if((!TotalLimiters) || (!LimitIncrementor) || (!ObjectIn)){
        return STATUS_INVALID_PARAMETER;
    }
    ObjectIn->TotalLimiters = TotalLimiters;
    ObjectIn->LimitIncrementor = LimitIncrementor;
    ObjectIn->CurrentLimiter = 1;
    return STATUS_SUCCESS;
}

typedef class _SCHEDUAL_MANAGER{

}SCHEDUAL_MANAGER, * PSCHEDUAL_MANAGER;

typedef struct _PROCESSOR_STATE_BLOCK{
    mutex_t                         LockOutTagOut;
    UINT64                          CurrentThreadID;
    UINT64                          CurrentInterruptStorage;
    UINT64                          CurrentContextStorage;
    
}PROCESSOR_STATE_BLOCK, * PPROCESSOR_STATE_BLOCK;

typedef struct _LOUSINE_PROCESS_MANAGER_BLOCK{
    mutex_t                         LockOutTagOut;
    INTEGER                         ProcessorCount;
    PPROCESSOR_STATE_BLOCK          ProcStateBlock;

}LOUSINE_PROCESS_MANAGER_BLOCK, * PLOUSINE_PROCESS_MANAGER_BLOCK;

KERNEL_IMPORT uint16_t GetNPROC();

KERNEL_IMPORT LouKIRQL LouKeGetIrql();
KERNEL_IMPORT void LouKeSendIcEOI();
void LouKeSwitchToTask(
    UINT64                  StackContex,
    PGENERIC_THREAD_DATA    ThreadFrom,
    PGENERIC_THREAD_DATA    ThreadTo,
    BOOL                    StoreData
);

KERNEL_IMPORT 
void SetPEB(uint64_t PEB);
KERNEL_IMPORT
void SetTEB(uint64_t Teb);

#endif