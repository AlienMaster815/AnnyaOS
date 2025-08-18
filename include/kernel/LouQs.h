#ifndef _LOUQS_H
#define _LOUQS_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else 
#include <LouAPI.h>
#endif
 
typedef struct  _LOUQ{
    ListHeader                  Peers;
    string                      Identifer;
    void*                       QueueData;
    uint64_t                    QueueDataSize;
    uint64_t                    LOUQFlags;
    uint64_t                    QueueTimeout;
    uint64_t                    QueueDepth;
    uint64_t                    QueueLimit;
    uint64_t                    QueuesInFront;
    uint64_t                    Priority;
    spinlock_t                  LOUQLock;
    mutex_t                     LouQtex;
    struct _LOUQ_COMPLETION*    Completion;
}LOUQ, * PLOUQ;

typedef struct _LOUQ_WAIT{
    LOUQ    LouQHeader;
}LOUQ_WAIT, * PLOUQ_WAIT;

typedef struct _LOUQ_WORK{
    LOUQ                LouQHeader;
    bool                WorkRequired;
    DELAYED_FUNCTION    Work;
}LOUQ_WORK, * PLOUQ_WORK;

typedef struct _LOUQ_WORK_STRUCTURE{
    string          Identifier;
    size_t          ActiveQCount; 
    mutex_t         StructureLock;
    uint64_t        StructureFlags;
    PLOUQ_WORK      NonActiveMembers;
    //the Non active mebers are pushed to the ActiveMembers
    //stack and removed from non ActiveMembers so that the
    //next worker can just grab from the ActiveMembers through
    //an array access rather than using the Listings
    PLOUQ_WORK       ActiveMembers;
}LOUQ_WORK_STRUCTURE, * PLOUQ_WORK_STRUCTURE;

typedef struct  _LOUQ_INTEFACE{
    PLOUQ NextInLine;
    PLOUQ InFront;
}LOUQ_INTEFACE, *PLOUQ_INTEFACE;

typedef struct _LOUQ_COMPLETION{
    ListHeader      Neighbors;

}LOUQ_COMPLETION, * PLOUQ_COMPLETION;

typedef struct _LOUQ_REQUEST{
    LOUQ    LouQHeader;
    void*   RequestData;
}LOUQ_REQUEST, * PLOUQ_REQUEST;

typedef struct _LOUQ_LIMITS{
    PLOUQ    LouQReference;
    uint64_t NumberOfQues;
    uint64_t OperationLimitFlags;
}LOUQ_LIMITS, * PLOUQ_LIMITS;

#define KERNEL_WORK_QUEUE 0
#define USER_WORK_QUEUE   1

#define IMEDIATE_PRIORITY            UINT64_MAX
#define KERNEL_PRIORITY             (UINT64_MAX - 1)
#define KERNEL_DEMON_PRIORITY       (UINT64_MAX - 2)
#define SUBSYSTEM_PRIORITY          (UINT64_MAX - 3)
#define SUBSYSTEM_DEMON_PRIORITY    (UINT64_MAX - 4)
#define DEVICE_PRIORITY             (UINT64_MAX - 5)
#define USER_SUBSYSTEM              (UINT64_MAX - 6)
#define USER_SUBSYSTEM_THREAD       (UINT64_MAX - 7)

#ifndef _KERNEL_MODULE_

PLOUQ_WORK_STRUCTURE LouKeMallocLouQWorkManagement(string Identifer, uint64_t StructureFlags, size_t MaxActive);
#define LouKeMallocLouQWorkStream(Identifer, StructureFlags) LouKeMallocLouQWorkManagement(Identifer, StructureFlags, 1)
LOUSTATUS LouKeInitializeWorkQueue(
    PLOUQ_WORK          WorkQueue,
    string              Identifier,
    UINT64              QueueFlags,
    UINT64              Timeout,
    UINT64              QueueLimit,
    UINT64              Priority,
    PLOUQ_COMPLETION    Completion,
    PVOID               WorkHandler,
    PVOID               WorkHandlerData
);

#else

KERNEL_EXPORT
LOUSTATUS LouKeInitializeWorkQueue(
    PLOUQ_WORK          WorkQueue,
    string              Identifier,
    UINT64              QueueFlags,
    UINT64              Timeout,
    UINT64              QueueLimit,
    UINT64              Priority,
    PLOUQ_COMPLETION    Completion,
    PVOID               WorkHandler,
    PVOID               WorkHandlerData
);



#endif
#ifdef __cplusplus
}
#endif
#endif 