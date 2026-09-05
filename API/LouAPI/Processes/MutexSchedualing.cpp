#include "ProcessPrivate.h"


LOUAPI void LouKeMxBlockThread(mutex_t* m){
    PGENERIC_THREAD_DATA Thread = (PGENERIC_THREAD_DATA)LouKeGetCurrentThreadHandle();
    while(LouKeAtomicTestAndSet(&m->WaitQueueLock, 1));
    LouKeListAddTail(&Thread->WaitQueue, &m->WaitQueue);
    LouKeSetAtomic(&m->WaitQueueLock, 0);
    LouKeBlockThread(Thread);
    LouKeListDeleteItem(&Thread->WaitQueue);
}


LOUAPI void LouKeMxUnblockThread(mutex_t* m){
    PGENERIC_THREAD_DATA Thread = ListItemToTypeOrNull(m->WaitQueue.NextHeader, GENERIC_THREAD_DATA, WaitQueue);
    if(Thread){
        LouKeUnblockThread(Thread);
        LouKeYieldExecution();
    }
}