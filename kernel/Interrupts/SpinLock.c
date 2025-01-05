#include <LouAPI.h>

void LouKeAcquireSpinLock(spinlock_t* LockValue, LouKIRQL* Irql){
    LouKeSetIrql(HIGH_LEVEL, Irql);
    MutexLock(&LockValue->Lock);
}

void LouKeReleaseSpinLock(spinlock_t* LockValue, LouKIRQL* Irql){
    MutexUnlock(&LockValue->Lock);
    LouKeSetIrql(*Irql, 0x00);
}


uint8_t LouKeAcquireSpinLockRaiseToDpc(uint64_t* LockData){

    
    return 0;
}