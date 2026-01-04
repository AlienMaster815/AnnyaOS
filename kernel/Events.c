#include <LouAPI.h>

LOUSTATUS LouKeWaitForEvent(PKERNEL_EVENT_OBJECT Event){
    MutexLock(&Event->Lock);
    Event->ThreadID = LouKeGetThreadIdentification();
    LouKeThreadSleep(Event->TimeOut);
    BOOL Completed = Event->Completed;
    Event->Completed = false;
    MutexUnlock(&Event->Lock);
    return Completed ? STATUS_SUCCESS : STATUS_TIMEOUT;
}


LOUSTATUS LouKeSignalEvent(PKERNEL_EVENT_OBJECT Event){
    Event->Completed = true;
    return STATUS_SUCCESS;
}