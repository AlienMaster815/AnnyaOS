#include "ApicInternals.h"

static UINT8 SpvVector = APIC_SPV_HANDLER_VECTOR;
static BOOLEAN ApicEnable = true;

UINT64 ApicHalSpurriousInterruptHandler(UINT64 CpuData){

    return CpuData;
}

LOUSTATUS ApicHalConfigureSpriousVector(ULONG Cpu){
    PPER_PROCESSOR_APIC_DATA ApicData = &PerProcessorApicData[Cpu];
    
    LouKeIpicCreateVectorObject(
        &ApicData->SpurriousVectorObject,
        Cpu,
        APIC_SPV_HANDLER_VECTOR,
        false,
        IsrRoutine,
        (OPAQUE_PTR)ApicHalSpurriousInterruptHandler,
        0,
        1
    );

    LouKeIpicSoftwareMaskVectorObject(ApicData->SpurriousVectorObject, 0, false);

    return ApicHalSetLocalApicSpuriousInterruptVectorRegister(0, 0, &ApicEnable, &SpvVector);

}