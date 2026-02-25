#include <LouAPI.h>

KERNEL_EXPORT void LouKeAcquireSpinLock(spinlock_t* LockValue, LouKIRQL* Irql){
    LouKeSetIrql(HIGH_LEVEL, Irql);
    MutexLock(&LockValue->Lock);
}

KERNEL_EXPORT void LouKeReleaseSpinLock(spinlock_t* LockValue, LouKIRQL* Irql){
    MutexUnlock(&LockValue->Lock);
    LouKeSetIrql(*Irql, 0x00);
}


uint8_t LouKeAcquireSpinLockRaiseToDpc(uint64_t* LockData){

    
    return 0;
}