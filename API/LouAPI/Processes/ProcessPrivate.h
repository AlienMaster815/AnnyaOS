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

typedef enum {
    PROCESS_READY = 0,
    PROCESS_RUNNING = 1,
    PROCESS_TERMINATED = 2,
    PROCESS_BLOCKED = 3,
} process_state_t;

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

KERNEL_IMPORT void SaveEverythingWithInterruptBuffer(uint64_t* ContextHandle);
KERNEL_IMPORT void RestoreEverything(uint64_t ContextHandle);
KERNEL_IMPORT void SaveEverything(uint64_t ContextHandle);

#define CTXMGR_DEFAULT_SAVE_EVERYTHING      SaveEverything
#define CTXMGR_DEFAULT_RESTORE_EVERYTHING   RestoreEverything

#define PROCESSOR_BITMAP_LENGTH (ROUND_UP64(GetNPROC(), 8) / 8)
#define IS_PROCESSOR_AFFILIATED(Bitmap, Processor) ((Bitmap)[(Processor) / 8] &  (1u << ((Processor) % 8)))
#define MARK_PROCESSOR_AFFILIATED(Bitmap, Processor) ((Bitmap)[(Processor) / 8] |=  (1u << ((Processor) % 8)))
#define UNMARK_PROCESSOR_AFFILIATED(Bitmap, Processor) ((Bitmap)[(Processor) / 8] &=  (1u << ((Processor) % 8)))

typedef enum {
    LONG_MODE       = 0,
    PROTECTED_MODE  = 1,
    REAL_MODE       = 2,
}INSTRUCTION_MODE;

typedef struct _GENERIC_THREAD_DATA{
    ListHeader                      Peers; //thread manager chain
    mutex_t                         LockOutTagOut;
    thread_state_t                  State;
    struct _GENERIC_PROCESS_DATA*   Process;
    TEB                             Teb;
    UINT64                          ThreadID;
    UINT8                           ThreadPriority;
    UINT64                          StackBase;
    UINT64                          StackTop;
    UINT64                          InterruptStorage;
    UINT64                          ContextStorage;
    UINT64                          TotalMsSlice;
    UINT64                          CurrentMsSlice;
    TIME_T                          ThreadStart;
    TIME_T                          BlockTimeout;
    UINT8                           Cs;
    UINT8                           Ss;
    INSTRUCTION_MODE                InstructionMode;
    UINT8*                          AfinityBitmap;
    BOOL                            Resting;
    CPUContext                      SavedState;
}GENERIC_THREAD_DATA, * PGENERIC_THREAD_DATA;

typedef struct THREAD_RING{
    ListHeader              Peers; //schedualer chain
    PGENERIC_THREAD_DATA    ThreadData;
}THREAD_RING, * PTHREAD_RING;

#define USER_THREAD_RING_ID     1
#define DEMON_THREAD_RING_ID    2

#define THREAD_PRIORITY_RINGS 32

typedef struct _SCHEDUALER_DISTRIBUTION_OBJECT{
    UINT64              TotalLimiters;
    UINT64              LimitIncrementor;
    UINT64              CurrentLimiter; //prioirty dips in goaround
    UINT64              CurrentIndexor;
}SCHEDUALER_DISTRIBUTION_OBJECT, * PSCHEDUALER_DISTRIBUTION_OBJECT;

static inline UINT64 EulerCurveIndexor(PSCHEDUALER_DISTRIBUTION_OBJECT Sched){
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

static inline void ResetEulerCurveIndexor(PSCHEDUALER_DISTRIBUTION_OBJECT Sched){
    Sched->CurrentIndexor = 0;
    Sched->CurrentLimiter = 1;
}

static inline LOUSTATUS CreateShecdualerObject(
    PSCHEDUALER_DISTRIBUTION_OBJECT ObjectIn,
    UINT64                          TotalLimiters,
    UINT64                          LimitIncrementor
){
    if((TotalLimiters < 2) || (!LimitIncrementor) || (!ObjectIn)){
        return STATUS_INVALID_PARAMETER;
    }
    ObjectIn->TotalLimiters = TotalLimiters;
    ObjectIn->LimitIncrementor = LimitIncrementor;
    ObjectIn->CurrentLimiter = 1;
    return STATUS_SUCCESS;
}

typedef class TsmThreadSchedualManagerObject{
    private:
        spinlock_t                          LockOutTagOut;                     
        SCHEDUALER_DISTRIBUTION_OBJECT      LoadDistributer;
        UINT64                              ProcessorID;
        PTHREAD_RING                        Threads[THREAD_PRIORITY_RINGS];
        PGENERIC_THREAD_DATA                IdleTask;
        PGENERIC_THREAD_DATA                TsmGetNext(PGENERIC_THREAD_DATA CurrentThread);
    public:
        LOUSTATUS                           TsmInitializeSchedualerObject(
                                                UINT64                          ProcessorID, 
                                                struct _GENERIC_PROCESS_DATA*   ProcessData,
                                                UINT64                          DistibutionLimitor,
                                                UINT64                          DistributerIncrementation
                                            );
        PGENERIC_THREAD_DATA                TsmSchedual(PGENERIC_THREAD_DATA CurrentThread);
        PGENERIC_THREAD_DATA                TsmYeild(PGENERIC_THREAD_DATA CurrentThread);
        void                                TsmAsignThreadToSchedual(PGENERIC_THREAD_DATA Thread);
        void                                TsmDeasignThreadFromSchedual(PGENERIC_THREAD_DATA Thread);
}THREAD_SCHEDUAL_MANAGER, * PTHREAD_SCHEDUAL_MANAGER;

#define THREAD_DEFAULT_DISTRIBUTER_INCREMENTER 1
#define PROCESS_DEFAULT_DISTRIBUTER_INCREMENTER THREAD_DEFAULT_DISTRIBUTER_INCREMENTER

typedef struct _GENERIC_PROCESS_DATA{
    ListHeader                              Peers;
    struct _GENERIC_PROCESS_DATA*           ParentProcess;
    string                                  ProcessName;
    mutex_t                                 LockOutTagOut;
    UINT64                                  PMLTree;
    UINT16                                  ProcessID;
    UINT8                                   ProcessPriority;
    PTHREAD_SCHEDUAL_MANAGER                ThreadObjects;    
    PEB                                     Peb;
    UINT64                                  Subsystem;
    process_state_t                         ProcessState;
    TIME_T                                  ThreadStart;
    TIME_T                                  BlockTimeout;
    UINT64                                  TotalMsSlice;
    UINT64                                  CurrentMsSlice;
    INSTRUCTION_MODE                        InstructionMode;
    UINT8*                                  AfinityBitmap;
    HANDLE                                  ProcessSection;
}GENERIC_PROCESS_DATA, * PGENERIC_PROCESS_DATA;

typedef struct _PROCESS_RING{
    ListHeader              Peers;
    PGENERIC_PROCESS_DATA   ProcessData;
}PROCESS_RING, * PPROCESS_RING;

typedef class PsmProcessScedualManagerObject{
    private:
        spinlock_t                          LockOutTagOut;                     
        SCHEDUALER_DISTRIBUTION_OBJECT      LoadDistributer;
        UINT64                              ProcessorID;
        PPROCESS_RING                       Processes[PROCESS_PRIORITY_RINGS];
        PGENERIC_PROCESS_DATA               SystemProcess;
        void                                PsmSetProcessTransitionState();
    public:
        PGENERIC_THREAD_DATA                OwnerThread;
        PGENERIC_THREAD_DATA                CurrentThread;
        PGENERIC_PROCESS_DATA               CurrentProcess;
        LOUSTATUS                           PsmInitializeSchedualerObject(
                                                UINT64 ProcessorID, 
                                                UINT64 DistibutionLimitor,
                                                UINT64 DistributerIncrementation
                                            );
        void                                PsmSchedual(UINT64 IrqState);
        void                                PsmYeildThread(UINT64 IrqState);
        void                                PsmAsignProcessToSchedual(PGENERIC_PROCESS_DATA Process);
        void                                PsmDeasignProcessFromSchedual(PGENERIC_PROCESS_DATA Process, bool SelfIdentifiing);
        UINT64                              PsmGetCurrentProcessID();
        UINT64                              PsmGetCurrentSubsystem();
        void                                PsmSetSystemProcess(HANDLE ProcessData);
        void                                PsmSetCurrentThread(PGENERIC_THREAD_DATA Thread);
}PROCESS_SCHEDUAL_MANAGER, * PPROCESS_SCHEDUAL_MANAGER;

typedef PROCESS_SCHEDUAL_MANAGER SCHEDUAL_MANAGER, *PSCHEDUAL_MANAGER;

typedef struct _PROCESSOR_STATE_BLOCK{
    mutex_t                         LockOutTagOut;
    SCHEDUAL_MANAGER                Schedualer;
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
    PGENERIC_THREAD_DATA    ThreadTo
);

KERNEL_IMPORT 
void SetPEB(uint64_t PEB);
KERNEL_IMPORT
void SetTEB(uint64_t Teb);

UINT64 LouKeVmmCreatePmlTable();
void LouKeVmmCloneSectionToPml(UINT64* Pml4);
LOUSTATUS LouKePsmGetProcessHandle(
    string  ProcessName,
    PHANDLE OutHandle
);

LOUSTATUS LouKeTsmCreateThreadHandle(
    PGENERIC_THREAD_DATA*   OutHandle,    
    PGENERIC_PROCESS_DATA   Process,
    PVOID                   CtxEntry,
    PVOID                   CtxFunction,
    PVOID                   CtxParams,
    UINT8                   ThreadPriority,
    UINT64                  StackSize,
    UINT64                  TimeSliceMs,
    UINT8                   CodeSegment,
    UINT8                   StackSegment,
    INSTRUCTION_MODE        InstructionMode,
    PTIME_T                 StartTime,
    UINT8*                  AfinityBitmap
);

#endif