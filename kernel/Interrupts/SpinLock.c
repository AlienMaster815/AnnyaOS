#include <LouAPI.h>

KERNEL_EXPORT void LouKeAcquireSpinLock(spinlock_t* LockValue, LouKIRQL* Irql){
    LouKeRaiseIrql(DISPATCH_LEVEL, Irql);
    AtomicLock(&LockValue->Lock);
}

KERNEL_EXPORT void LouKeReleaseSpinLock(spinlock_t* LockValue, LouKIRQL* Irql){
    MutexUnlock(&LockValue->Lock);
    LouKeLowerIrql(*Irql);
}

KERNEL_EXPORT void LouKeAcquireInterruptLock(spinlock_t* LockValue, LouKIRQL* Irql){
    LouKeRaiseIrql(DISPATCH_LEVEL, Irql);
    AtomicLock(&LockValue->Lock);
}

KERNEL_EXPORT void LouKeReleaseInterruptLock(spinlock_t* LockValue, LouKIRQL* Irql){
    MutexUnlock(&LockValue->Lock);
    LouKeLowerIrql(*Irql);
}




uint8_t LouKeAcquireSpinLockRaiseToDpc(uint64_t* LockData){

    
    return 0;
}