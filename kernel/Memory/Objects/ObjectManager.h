#ifndef _OBJMNR_H_PRIV
#define _OBJMNR_H_PRIV

#include <LouAPI.h>

typedef enum{
    SESSION_CHAIN = 0,
    PROCESS_CHAIN = 1,
    THREAD_CHAIN  = 2,
}OBJECT_MANAGER_POOL_CLASS;

typedef struct _OBJECT_POOL_TRACKER{
    ListHeader                      Peers;
    mutex_t                         TrackerLock;
    OBJECT_MANAGER_POOL_CLASS       PoolClass;
    POOL                            Pool;
}OBJECT_POOL_TRACKER, * POBJECT_POOL_TRACKER;

typedef struct _HANDLE_TRACKER{
    UINT64                          HandleID;
    PVOID                           HandleTie;
}HANDLE_TRACKER, * PHANDLE_TRACKER;

struct _PROCESS_OBJECT_CHAIN;

typedef struct _SESSION_OBJECT_CHAIN{
    ListHeader                      Peers;
    struct _PROCESS_OBJECT_CHAIN*   ProcessChain;
    HANDLE_TRACKER                  SessionHandle;
    PHANDLE_TRACKER                 ProcessHandles;
    POBJECT_POOL_TRACKER            ObjectAllocationPool;
}SESSION_OBJECT_CHAIN, * PSESSION_OBJECT_CHAIN;

struct _THREAD_OBJECT_CHAIN;

typedef struct _PROCESS_OBJECT_CHAIN{
    ListHeader                      Peers;
    PSESSION_OBJECT_CHAIN           SessionChain;
    struct _THREAD_OBJECT_CHAIN*    ThreadChain;    
    HANDLE_TRACKER                  ProcessHandle;
    POBJECT_POOL_TRACKER            ObjectAllocationPool;
}PROCESS_OBJECT_CHAIN, * PPROCESS_OBJECT_CHAIN;

typedef struct _THREAD_OBJECT_CHAIN{
    ListHeader                      Peers;
    struct _PROCESS_OBJECT_CHAIN*   ProcessChain;
    HANDLE_TRACKER                  ThreadHandle;
    POBJECT_POOL_TRACKER            ObjectAllocationPool;
}THREAD_OBJECT_CHAIN, * PTHREAD_OBJECT_CHAIN;

LOUSTATUS 
LouKeAllocateObjectPoolTracker(
    OBJECT_MANAGER_POOL_CLASS   PoolClass,
    PVOID*                      Out
);

PVOID AllocateSessionTracker();

#endif