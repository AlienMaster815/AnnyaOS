#include <LouAPI.h>

/*static LOUQ_WORK MainWorkQueue = {0};

LOUSTATUS LouKeStartWork(PLOUQ_WORK Work){
    MutexLock(&MainWorkQueue.LouQHeader.LouQtex);

    if(!MainWorkQueue.CurrentWorkList.NextHeader){
        MainWorkQueue.CurrentWorkList.NextHeader = (PListHeader)Work;
        goto _DONE_ASSIGNING_WORK;
    }

    PLOUQ_WORK NextQueue = (PLOUQ_WORK)MainWorkQueue.CurrentWorkList.NextHeader;
    if(NextQueue == Work){
        goto _DONE_ASSIGNING_WORK;
    }

    while(NextQueue->CurrentWorkList.NextHeader){
        NextQueue = (PLOUQ_WORK)NextQueue->CurrentWorkList.NextHeader;
        if(NextQueue == Work){
            goto _DONE_ASSIGNING_WORK;
        }
    }

    NextQueue->CurrentWorkList.NextHeader = (PListHeader)Work;

    _DONE_ASSIGNING_WORK:
    MutexUnlock(&MainWorkQueue.LouQHeader.LouQtex);
    return STATUS_SUCCESS;
}

static PLOUQ_WORK LouKeGetFreeWork(PLOUQ_WORK HeadWork){
    PLOUQ_WORK NextQueue = (PLOUQ_WORK)MainWorkQueue.CurrentWorkList.NextHeader;
    while(NextQueue){
        NextQueue = (PLOUQ_WORK)NextQueue->CurrentWorkList.NextHeader;
        if(!MutexIsLocked(&NextQueue->LouQHeader.LouQtex)){
            break;
        }
    }
    return NextQueue;
}

int LouKeMainWorkDemon(){
    PLOUQ_WORK NextQueue = 0x00;
    while(1){
        NextQueue = (PLOUQ_WORK)MainWorkQueue.CurrentWorkList.NextHeader;
        if((!NextQueue) || (MutexIsLocked(&MainWorkQueue.LouQHeader.LouQtex))){
            asm("INT $200");//yeild
            continue;
        }

        if(MutexIsLocked(&NextQueue->LouQHeader.LouQtex)){
            NextQueue = LouKeGetFreeWork(&MainWorkQueue);
        }else{
            MainWorkQueue.CurrentWorkList.NextHeader = NextQueue->CurrentWorkList.NextHeader;
        }

        if(NextQueue){
            MutexLock(&NextQueue->LouQHeader.LouQtex);
            NextQueue->Work.DelayedFunction(NextQueue);
            if(NextQueue->LouQHeader.Completion){
                //TODO:handle completion
            }
            MutexUnlock(&NextQueue->LouQHeader.LouQtex);
            NextQueue = 0x00;
        }else{
            asm("INT $200");//yeild
        }
    }
}*/

UNUSED static LOUQ_WORK_QUEUE MainWorkQueue = {0};

DWORD LouKeWorkStackDemon(PVOID Data){
    UNUSED PLOUQ_WORK_QUEUE WorkQueueData = (PLOUQ_WORK_QUEUE)Data;
    LouPrint("Work Queue Started:%s\n", WorkQueueData->QueueName);
    while(1){
        
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeQueueWork(
    string QueueName,
    PLOUQ_WORK WorkItem
){


    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeQueueDelayedWork(
    string QueueName, 
    PLOUQ_WORK WorkItem, 
    PTIME_T Delay
){


    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeQueueTimedWork(
    string QueueName, 
    PLOUQ_WORK WorkItem, 
    PTIME_T Delay
){



    return STATUS_SUCCESS;
}

LOUSTATUS LouKeCreateWorkQueue(
    PLOUQ_WORK_QUEUE*   OutQueue,
    WORK_QUEUE_PRIORITY QueuePriority,
    string              QueueName
){
    PLOUQ_WORK_QUEUE TmpQueue = &MainWorkQueue;
    while(TmpQueue->Peers.NextHeader){
        TmpQueue = (PLOUQ_WORK_QUEUE)TmpQueue->Peers.NextHeader;
        if(strcmp(TmpQueue->QueueName, QueueName)){
            if(OutQueue){
                *OutQueue = TmpQueue;
            }
            return STATUS_SUCCESS;
        }
    }
    
    TmpQueue->Peers.NextHeader = (PListHeader)LouKeMallocType(LOUQ_WORK_QUEUE, KERNEL_GENERIC_MEMORY);
    TmpQueue = (PLOUQ_WORK_QUEUE)TmpQueue->Peers.NextHeader;

    TmpQueue->QueueName = LouKeMallocArray(CHAR, strlen(QueueName) + 1, KERNEL_GENERIC_MEMORY);
    strcpy(TmpQueue->QueueName, QueueName);
    TmpQueue->QueuePriority = QueuePriority;

    TmpQueue->QueueThread = LouKeCreateDemon(LouKeWorkStackDemon, (PVOID)TmpQueue, 16 * KILOBYTE);

    if(OutQueue){
        *OutQueue = TmpQueue;
    }
    return STATUS_SUCCESS;
}
