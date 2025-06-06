#ifndef _LOUQS_H
#define _LOUQS_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else 
#include <LouAPI.h>
#endif
 
typedef struct  _LOUQ{
    void* QueueData;
    uint64_t QueueDataSize;
    bool LOUQNext;
    bool LOUQBeingHandled;
    bool LOUQCompleted;
    uint64_t LOUQFlags;

    uint64_t QueueTimeout;
    uint64_t QueueDepth;

    uint64_t QueuesInFront;
    uint64_t Priority;
    spinlock_t LOUQLock;
}LOUQ, * PLOUQ;

typedef struct _LOUQ_WAIT{
    LOUQ    LouQHeader;
}LOUQ_WAIT, * PLOUQ_WAIT;

typedef struct _LOUQ_WORK{
    LOUQ                LouQHeader;
    DELAYED_FUNCTION    Work;
}LOUQ_WORK, * PLOUQ_WORK;

typedef struct  _LOUQ_INTEFACE{
    PLOUQ NextInLine;
    PLOUQ InFront;
}LOUQ_INTEFACE, *PLOUQ_INTEFACE;

typedef struct _LOUQ_COMPLETION{
    ListHeader      Neighbors;
    void*           CompletedDataStructure;
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


#ifdef __cplusplus
}
#endif
#endif 