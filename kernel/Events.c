#include <LouAPI.h>

void LouKeUnblockThread(UINT64 ThreadID);

LOUSTATUS LouKeWaitForEvent(PKERNEL_EVENT_OBJECT Event){
    MutexLock(&Event->Lock);
    Event->ThreadID = LouKeGetThreadIdentification();
    LouKeThreadSleep(Event->TimeOut);
    BOOL Completed = Event->Completed;
    Event->Completed = false;
    MutexUnlock(&Event->Lock);
    return Completed ? STATUS_SUCCESS : STATUS_TIMEOUT;
}


void LouKeSignalEvent(PKERNEL_EVENT_OBJECT Event){
    Event->Completed = true;
    LouKeUnblockThread(Event->ThreadID);
}