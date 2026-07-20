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


LOUSTATUS ApicHalSendSipiToAp(
    UINT32 Ap
){
    ApicHalDbgPrint("APIC.SYS:Waking AP:%h\n", Ap);

    LOUSTATUS Status;
    BOOLEAN PendingInterrupt = true;
   
    Status = ApicHalSetLocalApicErrorStatus(0);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    while(PendingInterrupt){
        Status = ApicHalGetLocalApicInterruptCommandRegister(0x00, 0x00, 0x00, 0x00, &PendingInterrupt, 0x00, 0x00, 0x00);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
    }

    UINT32 ApicID = PerProcessorApicData[Ap].ApicID;

    Status = ApicHalSetLocalApicErrorStatus(0);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    ApicHalSetLocalApicInterruptCommandRegister(
        ApicID,
        APIC_DESTINATION_SHORTHAND_NONE,
        APIC_TRIGGER_MODE_EDGE,
        APIC_LEVEL_ASSERT,
        APIC_DESTINATION_MODE_PHYSICAL,
        APIC_LVT_DELIVERY_MODE_INIT,
        0
    );  

    PendingInterrupt = true;
    while(PendingInterrupt){
        Status = ApicHalGetLocalApicInterruptCommandRegister(0x00, 0x00, 0x00, 0x00, &PendingInterrupt, 0x00, 0x00, 0x00);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
    }

    sleep(10);

    //for(SIZE i = 0; i < 2; i++){
        Status = ApicHalSetLocalApicErrorStatus(0);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        ApicHalSetLocalApicInterruptCommandRegister(
            ApicID,
            APIC_DESTINATION_SHORTHAND_NONE,
            APIC_TRIGGER_MODE_EDGE,
            APIC_LEVEL_ASSERT,
            APIC_DESTINATION_MODE_PHYSICAL,
            APIC_ICR_DELIVERY_MODE_STARTUP,
            0x08
        );  
        
        PendingInterrupt = true;
        while(PendingInterrupt){
            Status = ApicHalGetLocalApicInterruptCommandRegister(0x00, 0x00, 0x00, 0x00, &PendingInterrupt, 0x00, 0x00, 0x00);
            if(Status != STATUS_SUCCESS){
                return Status;
            }
        }
        sleep(1);
    //}

    return STATUS_SUCCESS;
}