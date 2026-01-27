#include <LouAPI.h>

mutex_t* LouKeGetPrintMutex();

void LouKeReportMutexBlock(mutex_t* m, UINT64 Thread){
    //if(m != LouKeGetPrintMutex()){
    //    LouPrint("Thread:%d whants Mutex:%h From Thread:%d\n", LouKeGetThreadIdentification(), m, Thread);
    //}
}