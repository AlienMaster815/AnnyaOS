#include "ApicInternals.h"

KERNEL_EXPORT
LOUSTATUS LouKeIpicCreateVectorObjectEx(
    OPAQUE_PTR*         VectorObjectOut,
    SIZE                Processor,
    SIZE                Vector,
    BOOLEAN             NeedFlotationSave,
    IPIC_ROUTINE_TYPE   RoutineType,
    OPAQUE_PTR          Routine,
    UINT64              LirData,
    SIZE                Items,
    BOOLEAN             DisableIpcSafety
);


LOUSTATUS ApicHalInterProcessorInterruptHandler(UINT64 Data){



}


LOUSTATUS ApicHalInitializeInterProcessorInterrupts(ULONG Cpu){
    PPER_PROCESSOR_IPI_DATA IpiData  = &PerProcessorApicData[Cpu].IpiData;
    
    LouKeIpicCreateVectorObjectEx(
        &IpiData->IpiVectorObject,
        Cpu,
        APIC_IPI_DISPATCH_VECTOR,
        false,
        LirRoutine,
        (OPAQUE_PTR)ApicHalInterProcessorInterruptHandler,
        (UINT64)&IpiData->InterruptPacket,
        1,
        true
    );

    LouKeIpicSoftwareMaskVectorObject(IpiData->IpiVectorObject, 0, false);

    return STATUS_SUCCESS;
}