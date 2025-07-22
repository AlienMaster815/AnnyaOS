#include <LouAPI.h>

void LouKeAcquireSpinLock(spinlock_t* LockValue, LouKIRQL* Irql){
    MutexLock(&LockValue->Lock);
    LouKeSetIrql(HIGH_LEVEL, Irql);
}

void LouKeReleaseSpinLock(spinlock_t* LockValue, LouKIRQL* Irql){
    LouKeSetIrql(*Irql, 0x00);
    MutexUnlock(&LockValue->Lock);
}


uint8_t LouKeAcquireSpinLockRaiseToDpc(uint64_t* LockData){

    
    return 0;
}