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


static UINT8 SpvVector = APIC_SPV_HANDLER_VECTOR;
static BOOLEAN ApicEnable = true;

UINT64 ApicHalSpurriousInterruptHandler(UINT64 CpuData){

    return CpuData;
}

LOUSTATUS ApicHalConfigureSpriousVector(ULONG Cpu){
    PPER_PROCESSOR_APIC_DATA ApicData = &PerProcessorApicData[Cpu];
    
    LouKeIpicCreateVectorObjectEx(
        &ApicData->SpurriousVectorObject,
        Cpu,
        APIC_SPV_HANDLER_VECTOR,
        false,
        IsrRoutine,
        (OPAQUE_PTR)ApicHalSpurriousInterruptHandler,
        0,
        1,
        true
    );

    LouKeIpicSoftwareMaskVectorObject(ApicData->SpurriousVectorObject, 0, false);

    return ApicHalSetLocalApicSpuriousInterruptVectorRegister(0, 0, &ApicEnable, &SpvVector);

}