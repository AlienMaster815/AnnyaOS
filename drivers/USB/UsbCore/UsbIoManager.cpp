#include "UsbCore.h"

void UsbCoreHcdIoQueueManager(PVOID Params){
    PUSB_HCD_OBJECT HcdObject = (PUSB_HCD_OBJECT)(UINT8*)Params;
    PTHREAD Thread = LouKeGetCurrentThreadHandle();
    BOOLEAN CommandPolled;
    
    while(1){
        //MutexLock(&HcdObject->IoQueueLock);
        //
        //if(){
        //  MutexUnlock(&HcdObject->IoQueueLock);
        //  LouKeBlockThread(Thread);
        //}
        

        LouKeYieldExecution();
    }
}


void UsbCoreHcdIoDeQueueManager(PVOID Params){
    PUSB_HCD_OBJECT HcdObject = (PUSB_HCD_OBJECT)(UINT8*)Params;
    PTHREAD Thread = LouKeGetCurrentThreadHandle();
    BOOLEAN CommandPolled;
    while(1){



        LouKeYieldExecution();
    }
}