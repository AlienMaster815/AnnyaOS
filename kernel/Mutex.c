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
    UINT64          ExloThread,
    int             GracePeriod
){  
    memset(ExloMutex, 0, sizeof(*ExloMutex));
    LouKeSetAtomic64FromUint64(&ExloMutex->ExloThread, ExloThread);
    SemaphoreInitialize(&ExloMutex->Counter, GracePeriod, GracePeriod);
    LouKeMemoryBarrier();
    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeInitializeExloMutex(
    PEXLO_MUTEX     ExloMutex,
    UINT64          ExloThread
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
    UINT64 CurrentThread = LouKeGetThreadIdentification();
    UINT64 ExloThread = LouKeGetAtomic64FromUint64(&ExloMutex->ExloThread);

    MutexLock(&ExloMutex->ExloLock);
    if(CurrentThread == ExloThread){
        while(SemaphoreBeingUsed(&ExloMutex->Counter));
        return;
    }
    SemaphoreLock(&ExloMutex->Counter);
    MutexUnlock(&ExloMutex->ExloLock);
}

void 
LouKeReleaseExloLock(
    PEXLO_MUTEX ExloMutex
){
    UINT64 CurrentThread = LouKeGetThreadIdentification();
    UINT64 ExloThread = LouKeGetAtomic64FromUint64(&ExloMutex->ExloThread);
    if(CurrentThread == ExloThread){
        MutexUnlock(&ExloMutex->ExloLock);
    }else{
        SemaphoreUnlock(&ExloMutex->Counter);
    }
}
