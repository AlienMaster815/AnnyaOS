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
    spinlock_t                  LOUQLock;
    mutex_t                     LouQtex;
    struct _LOUQ_COMPLETION*    Completion;
}LOUQ, * PLOUQ;

typedef struct _LOUQ_WAIT{
    LOUQ    LouQHeader;
}LOUQ_WAIT, * PLOUQ_WAIT;

typedef struct _LOUQ_WORK{
    ListHeader          CurrentWorkList;
    LOUQ                LouQHeader;
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
    UINT64          MsTime;
    BOOL            Completed;
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

static inline void LouKeLouQInitializeWork(PLOUQ_WORK Work, DELAYED_CALLBACK Callback){
    Work->Work.DelayedFunction = Callback;
}

#ifndef _KERNEL_MODULE_

LOUSTATUS LouKeStartWork(PLOUQ_WORK Work);

#else

KERNEL_EXPORT LOUSTATUS LouKeStartWork(PLOUQ_WORK Work);
 
#endif
#ifdef __cplusplus
}
#endif
#endif 