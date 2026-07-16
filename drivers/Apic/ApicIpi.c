#include "ApicInternals.h"





LOUSTATUS ApicHalInterProcessorInterruptHandler(UINT64 Data){



}


LOUSTATUS ApicHalInitializeInterProcessorInterrupts(){
    UINT32 ProcessorNumber = LouKeGetCurrentProcessorNumber();
    PPER_PROCESSOR_IPI_DATA IpiData  = &PerProcessorApicData[ProcessorNumber].IpiData;
    
    LouKeIpicCreateVectorObject(
        &IpiData->IpiVectorObject,
        ProcessorNumber,
        APIC_IPI_DISPATCH_VECTOR,
        false,
        LirRoutine,
        (OPAQUE_PTR)ApicHalInterProcessorInterruptHandler,
        (UINT64)&IpiData->InterruptPacket,
        1
    );

    LouKeIpicSoftwareMaskVectorObject(IpiData->IpiVectorObject, 0, false);

    return STATUS_SUCCESS;
}