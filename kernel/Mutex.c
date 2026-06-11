#include <LouAPI.h>

mutex_t* LouKeGetPrintMutex();

KERNEL_EXPORT
void LouKeReportMutexBlock(mutex_t* m, UINT64 Thread){
    if(m != LouKeGetPrintMutex()){
        //LouPrint("Thread:%d whants Mutex:%h From Thread:%d\n", LouKeGetThreadIdentification(), m, Thread);
    }
}


KERNEL_EXPORT void MutexDestroy(mutex_t* m){
    memset(m, 0, sizeof(mutex_t));
}

KERNEL_EXPORT void MutexInitialize(mutex_t* m){
    MutexDestroy(m);
}