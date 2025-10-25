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

typedef struct _GENERIC_THREAD_DATA{
    mutex_t         LockOutTagOut;
    thread_state_t  state;
    PPEB            KPeb;
    CPUContext      SavedState;
    TEB             KTeb;
    UINT64          ThreadID;
    UINT64          StackBase;
    UINT64          StackTop;
    TIME_T          ThreadStart;
    TIME_T          BlockTimeout;
    BOOL            NewThread;
    UINT8           Cs;
    UINT8           Ss;
    UINT8           Fs;
    UINT8           Gs;
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

typedef struct _PROCESS_THREAD_RING{
    ListHeader                      Peers;
    ATOMIC_BOOLEAN                  RingSelector; //TRUE = DEMON, FALSE = USER
    PKULA_TRANSITION_LAYER_OBECT    KernelObject;
    PKULA_TRANSITION_LAYER_OBECT    UserObject;
    PUSER_THREAD_RING               CurrentThread;
    PDEMON_THREAD_RING              CurrentDemon;//demon Process service 
}PROCESS_THREAD_RING, * PPROCESS_THREAD_RING;


typedef struct _PROCESSOR_STATE_BLOCK{
    ATOMIC_BOOLEAN                  RingSelector; //Transition layer Ring; //TRUE = LOUOSKRNL.EXE // False = TRANSITION EMULATION STATE (KULA Determined)
    PDEMON_THREAD_RING              CurrentDemon;
    PPROCESS_THREAD_RING            CurrentProcess;
    PVOID                           ProcessorPrivateData;
}PROCESSOR_STATE_BLOCK, * PPROCESSOR_STATE_BLOCK;

typedef struct _LOUSINE_PROCESS_MANAGER_BLOCK{
    THREAD_CONTEXT_MANAGR_BLOCK     ThreadCtxMgrBlock;
    ATOMIC                          ProcessorCount;
    PPROCESSOR_STATE_BLOCK          ProcStateBlock;
    DEMON_THREAD_RING               DemonRing;
    PROCESS_THREAD_RING             ProcessRing;
}LOUSINE_PROCESS_MANAGER_BLOCK, * PLOUSINE_PROCESS_MANAGER_BLOCK;

#endif