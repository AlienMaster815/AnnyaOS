#include <LouAPI.h>

static LOUQ_WORK_QUEUE MainWorkQueue = {
    .QueueName = "Losine Kernel Main System Queue",
    .QueuePriority = 31,
};

DWORD LouKeWorkStackDemon(PVOID Data){
    UNUSED PLOUQ_WORK_QUEUE WorkQueueData = (PLOUQ_WORK_QUEUE)Data;
    LouPrint("Work Queue Started:%s\n", WorkQueueData->QueueName);
    LouKIRQL Irql;
    while(1){
        if(!LouKeListIsEmpty(&WorkQueueData->QueuedWork)){
            LouKeAcquireSpinLock(&WorkQueueData->AddLock, &Irql);
            ListHeader TmpList = WorkQueueData->QueuedWork;
            LouKeListDeleteAll(&WorkQueueData->QueuedWork);
            LouKeReleaseSpinLock(&WorkQueueData->AddLock, &Irql);

            PLOUQ_WORK TmpWork;
            PLOUQ_WORK ForwardWork;
            ForEachListEntrySafe(TmpWork, ForwardWork, &TmpList, QueueObject.Peers){
                TmpWork->Work.DelayedFunction(TmpWork->Work.WorkData);
                LouKeListDeleteItem(&TmpWork->QueueObject.Peers);
            }
        }
        LouKeYeildExecution();
    }
    return STATUS_SUCCESS;
}


KERNEL_EXPORT
LOUSTATUS 
LouKeWqQueueWork(
    PLOUQ_WORK_QUEUE    WorkQueue,
    PLOUQ_WORK          WorkItem
){
    SpinlockSyncronize(&WorkQueue->AddLock);
    LouKeListAddTail(&WorkItem->QueueObject.Peers, &WorkQueue->QueuedWork);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeQueueWork(
    PLOUQ_WORK WorkItem
){
    return LouKeWqQueueWork(
        &MainWorkQueue,
        WorkItem
    );
}


KERNEL_EXPORT 
LOUSTATUS 
LouKeQueueDelayedWork(
    string QueueName, 
    PLOUQ_WORK WorkItem, 
    PTIME_T Delay
){
    LouPrint("QUEUE:%s Requesting Delayed Work\n", QueueName);
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeQueueTimedWork(
    string QueueName, 
    PLOUQ_WORK WorkItem, 
    PTIME_T Delay
){



    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS LouKeCreateWorkQueue(
    PLOUQ_WORK_QUEUE*   OutQueue,
    UINT8               QueuePriority,
    string              QueueName
){
    
    PLOUQ_WORK_QUEUE NewQueue = LouKeMallocType(LOUQ_WORK_QUEUE, KERNEL_GENERIC_MEMORY);
    NewQueue->QueueName = LouKeMallocArray(CHAR, strlen(QueueName) + 1, KERNEL_GENERIC_MEMORY);
    strcpy(NewQueue->QueueName, QueueName);
    NewQueue->QueuePriority = QueuePriority;
    NewQueue->QueueThread = LouKeCreateDemon(LouKeWorkStackDemon, (PVOID)NewQueue, 16 * KILOBYTE, QueuePriority);

    LouKeListAddTail(&NewQueue->Peers, &MainWorkQueue.Peers);

    if(OutQueue){
        *OutQueue = NewQueue;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS LouKeCreateSystemWorkQeueue(){

    if(MainWorkQueue.QueueThread){
        return STATUS_UNSUCCESSFUL;
    }

    MainWorkQueue.QueueThread = LouKeCreateDemon(LouKeWorkStackDemon, (PVOID)&MainWorkQueue, 16 * KILOBYTE, 31);

    return STATUS_SUCCESS;
}
