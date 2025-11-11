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

typedef struct _THREAD_CONTEXT_MANAGR_BLOCK{
    void    (*SaveEverything)(uint64_t* ContextHandle);
    void    (*RestoreEverything)(uint64_t* ContextHandle);
    PVOID   PrivateManagementData;
}THREAD_CONTEXT_MANAGR_BLOCK, * PTHREAD_CONTEXT_MANAGR_BLOCK;

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

typedef struct _PM_ID_RANGE_POOL{
    ListHeader              Peers;
    PIDENTIFICATION_RANGE   IdRange;
}PM_ID_RANGE_POOL, * PPM_ID_RANGE_POOL;

typedef struct _GENERIC_THREAD_DATA{
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

typedef struct _DEMON_THREAD_RING{
    ListHeader              Peers;
    GENERIC_THREAD_DATA     DemonData;
}DEMON_THREAD_RING, * PDEMON_THREAD_RING;

typedef struct _USER_THREAD_RING{
    ListHeader              Peers;
    GENERIC_THREAD_DATA     ThreadData;
    PVOID                   SubsystemPrivateData;
}USER_THREAD_RING, * PUSER_THREAD_RING;

typedef PTHREAD (*PROCESS_RING_DISPATCH_HANDLER)(struct _PROCESSOR_STATE_BLOCK* ProcessBlock);

#define PROCESS_DISPATCH_HANDLER_HIGH_Q1        0   //HIGH
#define PRDCESS_DISPATCH_HANDLER_ABOVE_Q1       1   //ABOVE
#define PROCESS_DISPATCH_HANDLER_HIGH_Q2        2   //HIGH
#define PRDCESS_DISPATCH_HANDLER_ABOVE_Q2       3   //ABOVE
#define PROCESS_DISPATCH_HANDLER_NORMAL_Q1      4   //NORMAL
#define PROCESS_DISPATCH_HANDLER_HIGH_Q3        5   //HIGH
#define PROCESS_DISPATCH_HANDLER_ABOVE_Q3       6   //ABOVE 
#define PROCESS_DISPATCH_HANDLER_NORMAL_Q2      7   //NORMAL
#define PROCESS_DISPATCH_HANDLER_BELOW_Q1       8   //BELOW
#define PROCESS_DISPATCH_HANDLER_HIGH_Q4        9   //HIGH
#define PROCESS_DISPATCH_HANDLER_ABOVE_Q4       10  //ABOVE
#define PROCESS_DISPATCH_HANDLER_NORMAL_Q3      11  //NORMAL
#define PROCESS_DISPATCH_HANDLER_BELOW_Q2       12  //BELOW
#define PROCESS_DISPATCH_HANDLER_LOW_Q1         13  //LOW 
#define PRIORITY_DISPATCH_HANDLER_RINGS         14

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
#define THREAD_PRIORITY_RINGS       PROCESS_PRIORITY_RINGS

typedef struct _PROCESS_DISPATCH_MANAGER{
    struct {
        struct _PROCESS_THREAD_RING*    Ring; //priority ring tied to dispatcher
        PROCESS_RING_DISPATCH_HANDLER   DispatchHandlers;
    }QuantumMember[PRIORITY_DISPATCH_HANDLER_RINGS];
}PROCESS_DISPATCH_MANAGER, * PPROCESS_DISPATCH_MANAGER, 
    THREAD_DISPATCH_MANAGER, * PTHREAD_DISPATCH_MANAGER;

typedef struct _PROCESS_THREAD_RING{
    ListHeader                      Peers;
    mutex_t                         LockOutTagOut;
    PKULA_TRANSITION_LAYER_OBECT    KulaObject;
    UINT8                           DispatchRobin;
    THREAD_DISPATCH_MANAGER         ThreadRobin;
    PUSER_THREAD_RING               ThreadRings[THREAD_PRIORITY_RINGS];
}PROCESS_THREAD_RING, * PPROCESS_THREAD_RING;

typedef struct _PROCESSOR_STATE_BLOCK{
    mutex_t                         LockOutTagOut;
    UINT64                          CurrentThreadID;
    UINT64                          CurrentInterruptStorage;
    UINT64                          CurrentContextStorage;
    UINT64                          TotalMsSlice;
    UINT64                          CurrentMsSlice;
    PM_ID_RANGE_POOL                ThreadIDPool;
    ATOMIC_BOOLEAN                  RingSelector;
    UINT8                           DispatchRobin;
    THREAD_DISPATCH_MANAGER         ProcessRobin;
    PDEMON_THREAD_RING              CurrentDemon;
    PUSER_THREAD_RING               ProcessRings[PROCESS_PRIORITY_RINGS];  
    PVOID                           ProcessorPrivateData;
}PROCESSOR_STATE_BLOCK, * PPROCESSOR_STATE_BLOCK;

typedef struct _LOUSINE_PROCESS_MANAGER_BLOCK{
    mutex_t                         LockOutTagOut;
    PM_ID_RANGE_POOL                DemonIDPool;
    PM_ID_RANGE_POOL                ProcessIDPool;
    THREAD_CONTEXT_MANAGR_BLOCK     ThreadCtxMgrBlock;
    INTEGER                         ProcessorCount;
    PPROCESSOR_STATE_BLOCK          ProcStateBlock;
    PROCESS_DISPATCH_MANAGER        DispatchManager;
    PDEMON_THREAD_RING              DemonRing;
    PPROCESS_THREAD_RING            ProcessRing;
}LOUSINE_PROCESS_MANAGER_BLOCK, * PLOUSINE_PROCESS_MANAGER_BLOCK;

KERNEL_IMPORT uint16_t GetNPROC();
PDEMON_THREAD_RING LouKeCreateDemonThreadHandle();
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