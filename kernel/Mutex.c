#include <LouAPI.h>

mutex_t* LouKeGetPrintMutex();

KERNEL_EXPORT
void LouKeReportMutexBlock(mutex_t* m, UINT64 Thread){
    //if(m != LouKeGetPrintMutex()){
    //    LouPrint("Thread:%d whants Mutex:%h From Thread:%d\n", LouKeGetThreadIdentification(), m, Thread);
    //}
}


KERNEL_EXPORT void MutexDestroy(mutex_t* m){
    memset(m, 0, sizeof(mutex_t));
}

KERNEL_EXPORT void MutexInitialize(mutex_t* m){
    MutexDestroy(m);
}

LOUSTATUS 
LouKeInitializeExloMutexEx(
    PEXLO_MUTEX     ExloMutex,
    PTHREAD         ExloThread,
    int             GracePeriod
){  
    memset(ExloMutex, 0, sizeof(*ExloMutex));
    LouKeSetAtomic64FromUint64(&ExloMutex->ExloThread, (UINT64)ExloThread);
    SemaphoreInitialize(&ExloMutex->Counter, GracePeriod, GracePeriod);
    LouKeMemoryBarrier();
    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeInitializeExloMutex(
    PEXLO_MUTEX     ExloMutex,
    PTHREAD         ExloThread
){
    return LouKeInitializeExloMutexEx(
        ExloMutex,
        ExloThread,
        0
    );
}

void 
LouKeAcquireExloMutex(
    PEXLO_MUTEX ExloMutex
){
    /*PTHREAD CurrentThread = (PTHREAD)LouKeGetCurrentThreadHandle();
    PTHREAD ExloThread = (PTHREAD)LouKeGetAtomic64FromUint64(&ExloMutex->ExloThread);
    if(CurrentThread == ExloThread){
        MutexLock(&ExloMutex->ExloLock);
        while(SemaphoreBeingUsed(&ExloMutex->Counter)){
            LouKeYieldExecution();
        }
        return;
    }
    if(SemaphoreIsFull(&ExloMutex->Counter)){
        LouKeUnblockThread(ExloThread);
    }
    SemaphoreSynchronizeIfFullTillEvent(&ExloMutex->Counter, &ExloMutex->ReleaseEvent);
    MutexSynchronize(&ExloMutex->ExloLock);
    SemaphoreLock(&ExloMutex->Counter);*/
}

void 
LouKeReleaseExloLock(
    PEXLO_MUTEX ExloMutex
){
    /*PTHREAD CurrentThread = LouKeGetCurrentThreadHandle();
    PTHREAD ExloThread = (PTHREAD)LouKeGetAtomic64FromUint64(&ExloMutex->ExloThread);
    if(CurrentThread == ExloThread){
        LouKeSignalEvent(&ExloMutex->ReleaseEvent);
        MutexUnlock(&ExloMutex->ExloLock);
    }else{
        SemaphoreUnlock(&ExloMutex->Counter);
    }*/
}
