#include <LouAPI.h>

KERNEL_EXPORT
LOUSTATUS 
LouKeWaitForUcharRegisterConditionMs(
    PUCHAR  Mmio, 
    size_t  MsWait,
    UCHAR   Mask, 
    UCHAR   Value
){
    if((!Mmio) || (!MsWait) || (!Mask)){
        return STATUS_INVALID_PARAMETER;
    }
    size_t Limit = (GetCurrentTimeInMilliseconds() + MsWait);
    UCHAR Tmp = *Mmio;
    do{
        Tmp = *Mmio;
    }while(((Tmp & Mask) != Value) && (GetCurrentTimeInMilliseconds() < Limit));

    if((Tmp & Mask) != Value){
        return STATUS_TIMEOUT;
    }
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeWaitForUcharRegisterConditionHz(
    PUCHAR  Mmio, 
    size_t  HzWait,
    UCHAR   Mask, 
    UCHAR   Value
){  
    return LouKeWaitForUcharRegisterConditionMs(
        Mmio,
        HzWait * 100,
        Mask,
        Value
    );
}

KERNEL_EXPORT
LOUSTATUS 
LouKeWaitForUshortRegisterConditionMs(
    PUSHORT Mmio, 
    size_t  MsWait,
    USHORT  Mask, 
    USHORT  Value
){
    if((!Mmio) || (!MsWait) || (!Mask)){
        return STATUS_INVALID_PARAMETER;
    }
    size_t Limit = (GetCurrentTimeInMilliseconds() + MsWait);
    UCHAR Tmp = *Mmio;
    do{
        Tmp = *Mmio;
    }while(((Tmp & Mask) != Value) && (GetCurrentTimeInMilliseconds() < Limit));

    if((Tmp & Mask) != Value){
        return STATUS_TIMEOUT;
    }
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeWaitForUshortRegisterConditionHz(
    PUSHORT Mmio, 
    size_t  HzWait,
    USHORT  Mask, 
    USHORT  Value
){  
    return LouKeWaitForUshortRegisterConditionMs(
        Mmio,
        HzWait * 100,
        Mask,
        Value
    );
}


KERNEL_EXPORT
LOUSTATUS 
LouKeWaitForUlongRegisterConditionMs(
    PULONG  Mmio, 
    size_t  MsWait,
    ULONG   Mask, 
    ULONG   Value
){
    if((!Mmio) || (!MsWait) || (!Mask)){
        return STATUS_INVALID_PARAMETER;
    }
    size_t Limit = (GetCurrentTimeInMilliseconds() + MsWait);
    ULONG Tmp = *Mmio;
    do{
        Tmp = *Mmio;
    }while(((Tmp & Mask) != Value) && (GetCurrentTimeInMilliseconds() < Limit));

    if((Tmp & Mask) != Value){
        return STATUS_TIMEOUT;
    }
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeWaitForUlongRegisterConditionHz(
    PULONG  Mmio, 
    size_t  HzWait,
    ULONG   Mask, 
    ULONG   Value
){
    return LouKeWaitForUlongRegisterConditionMs(
        Mmio,
        HzWait * 100,
        Mask,
        Value
    );
}


KERNEL_EXPORT
LOUSTATUS 
LouKeWaitForUlonglongRegisterConditionMs(
    PULONGLONG  Mmio, 
    size_t      MsWait,
    ULONGLONG   Mask, 
    ULONGLONG   Value
){
    if((!Mmio) || (!MsWait) || (!Mask)){
        return STATUS_INVALID_PARAMETER;
    }
    size_t Limit = (GetCurrentTimeInMilliseconds() + MsWait);
    ULONG Tmp = *Mmio;
    do{
        Tmp = *Mmio;
    }while(((Tmp & Mask) != Value) && (GetCurrentTimeInMilliseconds() < Limit));

    if((Tmp & Mask) != Value){
        return STATUS_TIMEOUT;
    }
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeWaitForUlonglongRegisterConditionHz(
    PULONGLONG  Mmio, 
    size_t      HzWait,
    ULONGLONG   Mask, 
    ULONGLONG   Value
){
    return LouKeWaitForUlonglongRegisterConditionMs(
        Mmio,
        HzWait * 100,
        Mask,
        Value
    );
}

KERNEL_EXPORT
LOUSTATUS 
LouKeWaitForAtomicBooleanRegisterConditionMs(
    PATOMIC_BOOLEAN     Mmio, 
    size_t              MsWait, 
    BOOLEAN             Test
){
    if((!Mmio) || (!MsWait)){
        return STATUS_INVALID_PARAMETER;
    }
    size_t Limit = (GetCurrentTimeInMilliseconds() + MsWait);
    BOOLEAN Tmp = LouKeGetAtomicBoolean(Mmio);
    do{
        Tmp = LouKeGetAtomicBoolean(Mmio);
    }while((Tmp != Test) && (GetCurrentTimeInMilliseconds() < Limit));

    if(Tmp != Test){
        return STATUS_TIMEOUT;
    }
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeWaitForAtomicBooleanRegisterConditionHz(
    PATOMIC_BOOLEAN     Mmio, 
    size_t              HzWait, 
    BOOLEAN             Test
){ 
    return LouKeWaitForAtomicBooleanRegisterConditionMs(
        Mmio, 
        HzWait * 100, 
        Test
    );
}