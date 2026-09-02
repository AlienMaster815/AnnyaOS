#include <LouAPI.h>


PTHREAD LouKeGetCurrentThreadHandle();

KERNEL_EXPORT
LOUSTATUS LouKeWaitForEvent(PKERNEL_EVENT_OBJECT Event){
    MutexLock(&Event->Lock);
    Event->Thread = (PTHREAD)LouKeGetCurrentThreadHandle();
    LouKeThreadSleep(Event->TimeOut);
    BOOL Completed = Event->Completed;
    Event->Completed = false;
    MutexUnlock(&Event->Lock);
    return Completed ? STATUS_SUCCESS : STATUS_TIMEOUT;
}

KERNEL_EXPORT
void LouKeSignalEvent(PKERNEL_EVENT_OBJECT Event){
    Event->Completed = true;
    LouKeUnblockThread(Event->Thread);
}