#include <LouAPI.h>

static LOUQ_WORK MainWorkQueue = {0};

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
}

