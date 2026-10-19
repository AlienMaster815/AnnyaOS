#include <LouAPI.h>

LOUAPI void LouKeTsmAddThreadToMutexWaitList(PTHREAD ThreadData, PListHeader List);
LOUAPI PTHREAD LouKeTsmGetNextThreadInMutexWaitList(PListHeader List);
mutex_t* LouKeGetPrintMutex();

KERNEL_EXPORT
void LouKeReportMutexBlock(mutex_t* m, UINT64 Thread){
    if(m != LouKeGetPrintMutex()){
        LouPrint("Thread:%d whants Mutex:%h From Thread:%d\n", LouKeGetThreadIdentification(), m, Thread);
    }
}

KERNEL_EXPORT void MutexDestroy(mutex_t* m){
    memset(m, 0, sizeof(mutex_t));
}

KERNEL_EXPORT void MutexInitialize(mutex_t* m){
    MutexDestroy(m);
}

KERNEL_EXPORT
void 
MutexBlock(
    PMUTEX Mutex
){
    AtomicLock(&Mutex->Locked);
    return;


    BOOLEAN LockAcquired;
    //enter an atomic lock at current irql but force
    //the lock to yeild the current thread if the lock
    //is being held by somebody else
    AtomicLockEx(&Mutex->LockOutTagOut, true);
    
    //get the current wait count if there are already
    //waitors att the thread to the list of waitors
    //increment the wait list and block
    if(LouKeGetAtomic(&Mutex->Waitors)){
        goto _ADD_THREAD_AND_YIELD;
    }

    //if nobody is wating grab the main lock but dont
    //wait till the lock is unlocked so we can block
    //the current
    LockAcquired = AtomicLockOrFalse(&Mutex->Locked);
    if(LockAcquired){
        AtomicUnlock(&Mutex->LockOutTagOut);
        return;
    }

    //if a lock is already held by someone else
    //increment the waitors and add to the wait 
    //queue and yield 
_ADD_THREAD_AND_YIELD:
    PTHREAD ThreadData = LouKeGetCurrentThreadHandle();
    LouKeAtomicIncrement(&Mutex->Waitors);
    LouKeTsmAddThreadToMutexWaitList(ThreadData, &Mutex->WaitorList);
    AtomicUnlock(&Mutex->LockOutTagOut);
    LouKeBlockThread((PTHREAD)ThreadData);
}

KERNEL_EXPORT
void 
MutexUnblock(
    PMUTEX Mutex
){
    AtomicUnlock(&Mutex->Locked);
    return;

    //enter an atomic lock at current irql but force
    //the lock to yeild the current thread if the lock
    //is being held by somebody else
    AtomicLockEx(&Mutex->LockOutTagOut, true);

    //if there are waitors for the mutex wake the first
    //thread to be put to sleep
    if(LouKeGetAtomic(&Mutex->Waitors)){
        PTHREAD ThreadData = LouKeTsmGetNextThreadInMutexWaitList(&Mutex->WaitorList);
        //TODO:this should never be null occording to 
        //how the code is writted so later if this is
        //null throw a blue screen : for now though
        //it is safe to ignore
        if(ThreadData){
            LouKeUnblockThread((PTHREAD)ThreadData);
        }
        //decrement the waitors
        LouKeAtomicDecrement(&Mutex->Waitors);
    }else{
        //if no waitors unlock the main Lock
        AtomicUnlock(&Mutex->Locked);
    }
    AtomicUnlock(&Mutex->LockOutTagOut);
}