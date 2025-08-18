#include <LouAPI.h>



void LouQWorkDemon(PVOID Data);

LOUSTATUS LouKeInitializeLouQ(
    PLOUQ               Queue,
    string              Identifier,
    UINT64              QueueFlags,
    UINT64              Timeout,
    UINT64              QueueLimit,
    UINT64              Priority,
    PLOUQ_COMPLETION    Completion,
    PVOID               QueueHandler,
    PVOID               QueueHandlerData
);

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
){
    WorkQueue->Work.WorkData = WorkHandlerData;
    WorkQueue->Work.DelayedFunction = (void(*)(void *))WorkHandler;
    return LouKeInitializeLouQ(
        &WorkQueue->LouQHeader,
        Identifier,
        QueueFlags,
        Timeout,
        QueueLimit,
        Priority,
        Completion,
        LouQWorkDemon,
        WorkQueue
    );
}
