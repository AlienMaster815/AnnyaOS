#include <LouAPI.h>


LOUSTATUS 
LouKeWaitForUlongRegisterCondition(
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