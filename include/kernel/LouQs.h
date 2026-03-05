#ifndef _LOUQS_H
#define _LOUQS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint.h>
#include <cstdlib.h>
#include <kernel/loustatus.h>
#include <Time.h>
#include <kernel/threads.h>
#include <string.h>

struct _LOUQ_WORK;

typedef struct _DELAYED_FUNCTION{
    LOUSTATUS         (*DelayedFunction)(struct _LOUQ_WORK*);
    void*               WorkData;
}DELAYED_FUNCTION, * PDELAYED_FUNCTION;

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
    PVOID               Data;//TODO change to ATOMIC64
    DELAYED_FUNCTION    Work;
}LOUQ_WORK, * PLOUQ_WORK;


typedef struct _LOUQ_WORK_QUEUE{
    ListHeader          Peers;
    string              QueueName;
    LOUQ_WORK           WorkEntries;
    PLOUQ_WORK          LastWorkEntry;
    WORK_QUEUE_PRIORITY QueuePriority;
    PTHREAD             QueueThread;
}LOUQ_WORK_QUEUE, * PLOUQ_WORK_QUEUE;

static inline void LouKeLouQInitializeWork(PLOUQ_WORK Work, LOUSTATUS(*Function)(struct _LOUQ_WORK*)){
    Work->Work.DelayedFunction = Function;
}

#ifndef _USER_MODE_CODE_

KERNEL_EXPORT LOUSTATUS LouKeQueueWork(string QueueName, PLOUQ_WORK WorkItem);
KERNEL_EXPORT LOUSTATUS LouKeQueueDelayedWork(string QueueName, PLOUQ_WORK WorkItem, PTIME_T Delay);
KERNEL_EXPORT LOUSTATUS LouKeQueueTimedWork(string QueueName, PLOUQ_WORK WorkItem, PTIME_T Delay);

LOUSTATUS LouKeCreateWorkQueue(
    PLOUQ_WORK_QUEUE*   OutQueue,
    WORK_QUEUE_PRIORITY QueuePriority,
    string              QueueName
);


#endif
#ifdef __cplusplus
}
#endif
#endif 