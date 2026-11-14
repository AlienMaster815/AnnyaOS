#include <LouAPI.h>

static BOOLEAN MainWorkQueueRunning = false;

static LOUQ_WORK_QUEUE MainWorkQueue = {
    .QueueName = "Lousine Kernel Main System Queue",
    .QueuePriority = 31,
};

DWORD LouKeWorkStackDemon(PVOID Data){
    UNUSED PLOUQ_WORK_QUEUE WorkQueueData = (PLOUQ_WORK_QUEUE)Data;
    UNUSED PTHREAD WorkerThread = LouKeGetCurrentThreadHandle();
    LouPrint("Work Queue Started:%s\n", WorkQueueData->QueueName);
    LouKIRQL    Irql;
    UNUSED PLOUQ_WORK  TmpWork;
    UNUSED PLOUQ_WORK  ForwardWork;
    ListHeader  TmpList;
    while(1){
        LouKeAcquireInterruptLock(&WorkQueueData->AddLock, &Irql);
        TmpList = WorkQueueData->QueuedWork;
        LouKeListDeleteAll(&WorkQueueData->QueuedWork);
        LouKeMemoryBarrier();
        LouKeReleaseInterruptLock(&WorkQueueData->AddLock, &Irql);
        if(TmpList.NextHeader){
            ForEachListEntrySafe(TmpWork, ForwardWork, &TmpList, QueueObject.Peers){
                TmpWork->QueueObject.Status = TmpWork->Work.DelayedFunction(TmpWork->Work.WorkData);
                LouKeListDeleteItem(&TmpWork->QueueObject.Peers);
                LouKeSetAtomicBoolean(&TmpWork->QueueObject.InQueue, 0);
                if(TmpWork->Free){
                    LouKeFreeFastObject("LOUQ_WORK", TmpWork);
                }
            }
        }else{
            LouKeBlockThread(WorkerThread);
        }
    }
    return STATUS_SUCCESS;
}

DWORD 
LouKeMainWorkStackDemon(
    PVOID Data
){
    MainWorkQueueRunning = true;
    LouKeMemoryBarrier();
    return LouKeWorkStackDemon(Data);
}

KERNEL_EXPORT
LOUSTATUS 
LouKeWqQueueWork(
    PLOUQ_WORK_QUEUE    WorkQueue,
    PLOUQ_WORK          WorkItem
){

    LouKIRQL Irql;
    LouKeAcquireInterruptLock(&WorkQueue->AddLock, &Irql);
    if(!LouKeGetAtomicBoolean(&WorkItem->QueueObject.InQueue)){
        LouKeSetAtomicBoolean(&WorkItem->QueueObject.InQueue, 1);
        LouKeListAddTail(&WorkItem->QueueObject.Peers, &WorkQueue->QueuedWork);
        LouKeMemoryBarrier();
    }
    LouKeReleaseInterruptLock(&WorkQueue->AddLock, &Irql);
    LouKeUnblockThread(WorkQueue->QueueThread);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
void 
LouKeFlushWork(
    PLOUQ_WORK  WorkItem
){
    while(
        LouKeGetAtomicBoolean(&WorkItem->QueueObject.InQueue)
    );
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeQueueWork(
    PLOUQ_WORK WorkItem
){
    LOUSTATUS Status = LouKeWqQueueWork(
        &MainWorkQueue,
        WorkItem
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    return STATUS_SUCCESS;
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

    LouKeCreateFastObjectClass(
        "LOUQ_WORK",
        512,
        sizeof(LOUQ_WORK),
        GET_ALIGNMENT(LOUQ_WORK),
        0,
        KERNEL_GENERIC_MEMORY
    );
    MainWorkQueue.QueueThread = LouKeCreateDemon(LouKeMainWorkStackDemon, (PVOID)&MainWorkQueue, 16 * KILOBYTE, 31);

    return STATUS_SUCCESS;
}

void LouKeWaitForSystemWorkQueue(){
    while(!MainWorkQueueRunning){
        LouKeYieldExecution();
    }    
}