#include <LouAPI.h>

KERNEL_EXPORT
LOUSTATUS LouKeMmioWaitForCondition(
    volatile ULONG* Register,
    ULONG           And,
    ULONG           Condition,
    LONG            DebounceMs,
    LONG            Timeout
){
    ULONG Tmp;
    while(Timeout > 0){
        Tmp = READ_REGISTER_ULONG(Register);
        if((Tmp & And) == Condition){
            return STATUS_SUCCESS;
        }        
        sleep(DebounceMs);
        Timeout -= DebounceMs;
    }
    return STATUS_TIMEOUT;
}

KERNEL_EXPORT
LOUSTATUS LouKeMmioWaitTillClear(
    volatile ULONG* Register,
    ULONG           And,
    LONG            DebounceMs,
    LONG            Timeout
){
    ULONG Tmp;
    while(Timeout > 0){
        Tmp = READ_REGISTER_ULONG(Register);
        if(!(Tmp & And)){
            return STATUS_SUCCESS;
        }
        sleep(DebounceMs);
        Timeout -= DebounceMs;
    }
    return STATUS_TIMEOUT;
}

KERNEL_EXPORT
LOUSTATUS LouKeMmioWaitTillSet(
    volatile ULONG* Register,
    ULONG           And,
    LONG            DebounceMs,
    LONG            Timeout
){
    ULONG Tmp;
    while(Timeout > 0){
        Tmp = READ_REGISTER_ULONG(Register);
        if(Tmp & And){
            return STATUS_SUCCESS;
        }
        sleep(DebounceMs);
        Timeout -= DebounceMs;
    }
    return STATUS_TIMEOUT;
}