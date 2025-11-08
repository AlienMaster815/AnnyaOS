#ifndef _LOUQS_H
#define _LOUQS_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else 
#include <LouAPI.h>
#endif
 
#include <Time.h>

typedef struct  _LOUQ{
    ListHeader                  Peers;
    spinlock_t                  LOUQLock;
    mutex_t                     LouQtex;
    struct _LOUQ_COMPLETION*    Completion;
}LOUQ, * PLOUQ;

typedef enum{
    IMEDIATE_WORK = 0,
    KERNEL_QUEUE = 1,
    SUBSYSTEM_WORK = 2,
    DRIVER_WORK = 3,
}WORK_QUEUE_PRIORITY;

typedef struct _LOUQ_WORK{
    ListHeader          CurrentWorkList;
    LOUQ                LouQHeader;
    DELAYED_FUNCTION    Work;
    BOOL                TimedQueue;
    BOOL                DelayedQueue;
    TIME_T              TimeCondition;
}LOUQ_WORK, * PLOUQ_WORK;

typedef struct _LOUQ_WORK_QUEUE{
    ListHeader          Peers;
    string              QueueName;
    LOUQ_WORK           WorkEntries;
    PLOUQ_WORK          LastWorkEntry;
    WORK_QUEUE_PRIORITY QueuePriority;
    PTHREAD             QueueThread;
}LOUQ_WORK_QUEUE, * PLOUQ_WORK_QUEUE;

static inline void LouKeLouQInitializeWork(PLOUQ_WORK Work, DELAYED_CALLBACK Callback){
    Work->Work.DelayedFunction = Callback;
}

#ifndef _KERNEL_MODULE_


LOUSTATUS LouKeQueueWork(string QueueName, PLOUQ_WORK WorkItem);
LOUSTATUS LouKeQueueDelayedWork(string QueueName, PLOUQ_WORK WorkItem, PTIME_T Delay);
LOUSTATUS LouKeQueueTimedWork(string QueueName, PLOUQ_WORK WorkItem, PTIME_T Delay);

LOUSTATUS LouKeCreateWorkQueue(
    PLOUQ_WORK_QUEUE*   OutQueue,
    WORK_QUEUE_PRIORITY QueuePriority,
    string              QueueName
);


#else

KERNEL_EXPORT LOUSTATUS LouKeQueueWork(string QueueName, PLOUQ_WORK WorkItem);

#endif
#ifdef __cplusplus
}
#endif
#endif 