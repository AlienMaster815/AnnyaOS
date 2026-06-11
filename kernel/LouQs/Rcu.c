#include <LouAPI.h>

LOUAPI uint16_t GetNPROC();

//RCU and SRCU objects are the same structure

KERNEL_EXPORT LOUSTATUS LouKeInitializeSrcuObject(PSRCU_OBJECT SrcuObject){
    if(!SrcuObject){
        return STATUS_INVALID_PARAMETER;
    }
    memset(SrcuObject, 0, sizeof(SRCU_OBJECT));
    SrcuObject->Sleepable = true;
    return STATUS_SUCCESS;
}

KERNEL_EXPORT LOUSTATUS LouKeInitializeRcuObject(PRCU_OBJECT RcuObject){
    if(!RcuObject){
        return STATUS_INVALID_PARAMETER;
    }
    memset(RcuObject, 0, sizeof(RCU_OBJECT));
    RcuObject->Sleepable = false;
    return STATUS_SUCCESS;
}

KERNEL_EXPORT void LouKeDeInitializeSrcuObject(PRCU_OBJECT SrcuObject){
    if(!SrcuObject){
        return;
    }
    memset(SrcuObject, 0, sizeof(RCU_OBJECT));
}

KERNEL_EXPORT void LouKeDeInitializeRcuObject(PRCU_OBJECT RcuObject){
    if(!RcuObject){
        return;
    }
    memset(RcuObject, 0, sizeof(RCU_OBJECT));
}

KERNEL_EXPORT int LouKeSrcuAcquireReadLock(PSRCU_OBJECT SrcuObject){
    int Processor = LouKeGetCurrentProcessorNumber();
    LouKeMemoryBarrier();    
    if(!SrcuObject->Sleepable){
        LouKeSetIrql(DISPATCH_LEVEL, &SrcuObject->PerCpuData[Processor].Irql);
    }
    LouKeAcquireReference(&SrcuObject->PerCpuData[Processor].Readers);
    return Processor;
}

KERNEL_EXPORT void LouKeSrcuReleaseReadLock(PSRCU_OBJECT SrcuObject, int Token){
    int Processor = Token;
    if(SrcuObject->MbAfterReadUnlock){
        LouKeMemoryBarrier();
    }
    LouKeReleaseReference(&SrcuObject->PerCpuData[Processor].Readers);
    if(!SrcuObject->Sleepable){
        LouKeSetIrql(SrcuObject->PerCpuData[Processor].Irql, 0x00);
    }
}

KERNEL_EXPORT void LouKeRcuAcquireReadLock(PRCU_OBJECT RcuObject){
    int ProcessorID = LouKeGetCurrentProcessorNumber();
    RcuObject->PerCpuData[ProcessorID].NonRcuSleepableProcessorIndex = LouKeSrcuAcquireReadLock(RcuObject);
}

KERNEL_EXPORT void LouKeRcuReleaseReadLock(PRCU_OBJECT RcuObject){
    int ProcessorID = LouKeGetCurrentProcessorNumber();
    LouKeSrcuReleaseReadLock(RcuObject, RcuObject->PerCpuData[ProcessorID].NonRcuSleepableProcessorIndex);
}

KERNEL_EXPORT void LouKeRcuAssignPointer(PRCU_OBJECT RcuObject, PVOID NewPointer){
    RcuObject->Writer = NewPointer;
    LouKeMemoryBarrier();
}

KERNEL_EXPORT void LouKeRcuSynchronize(PRCU_OBJECT RcuObject){
    int ProcCount = GetNPROC();

    for(int i = 0; i < ProcCount; i++){
        while(LouKeGetReferenceCount(&RcuObject->PerCpuData[i].Readers)){
            LouKeYeildExecution();
        }
        RcuObject->PerCpuData[i].CurrentReader = RcuObject->Writer;
        LouKeMemoryBarrier();
    }
}