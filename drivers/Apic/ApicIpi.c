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

    LouPrint("HERE\n");

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

DRIVER_EXPORT 
LOUSTATUS 
ApicIpiHalSendNewInterruptRouteData(
    ULONG   Cpu,
    PVOID   RouteData
){
    LOUSTATUS Status;
    PPER_PROCESSOR_IPI_DATA IpiData  = &PerProcessorApicData[Cpu].IpiData;

    MutexLock(&IpiData->ProcessorLock);

    ApicHalSetLocalApicErrorStatus(0);

    BOOLEAN InterruptPending = true;
    while(InterruptPending){
        Status = ApicHalGetLocalApicInterruptCommandRegister(0x00, 0x00, 0x00, 0x00, &InterruptPending, 0x00, 0x00, 0x00);
        if(Status != STATUS_SUCCESS){
            MutexUnlock(&IpiData->ProcessorLock);
            return Status;
        }
    }

    IpiData->InterruptPacket.PacketType = ROUTE_INSTALLATION_INTERRUPT; 
    IpiData->InterruptPacket.RouteInstallationPacket.InstallData = RouteData;


    Status = ApicHalSetLocalApicInterruptCommandRegister(
        PerProcessorApicData[Cpu].ApicID,
        APIC_DESTINATION_SHORTHAND_NONE,
        APIC_TRIGGER_MODE_EDGE,
        APIC_LEVEL_ASSERT,
        APIC_DESTINATION_MODE_PHYSICAL,
        APIC_ICR_DELIVERY_MODE_FIXED,
        APIC_IPI_DISPATCH_VECTOR
    );
    MutexUnlock(&IpiData->ProcessorLock);
    return Status;
}

DRIVER_EXPORT 
LOUSTATUS 
ApicIpiHalSendNewDemonData(
    ULONG   Cpu,
    PVOID   DemonData
){
    LOUSTATUS Status;
    PPER_PROCESSOR_IPI_DATA IpiData  = &PerProcessorApicData[Cpu].IpiData;

    MutexLock(&IpiData->ProcessorLock);

    ApicHalSetLocalApicErrorStatus(0);

    BOOLEAN InterruptPending = true;
    while(InterruptPending){
        Status = ApicHalGetLocalApicInterruptCommandRegister(0x00, 0x00, 0x00, 0x00, &InterruptPending, 0x00, 0x00, 0x00);
        if(Status != STATUS_SUCCESS){
            MutexUnlock(&IpiData->ProcessorLock);
            return Status;
        }
    }

    IpiData->InterruptPacket.PacketType = DEMON_INSTALLATION_INTERRUPT; 
    IpiData->InterruptPacket.RouteInstallationPacket.InstallData = DemonData;


    Status = ApicHalSetLocalApicInterruptCommandRegister(
        PerProcessorApicData[Cpu].ApicID,
        APIC_DESTINATION_SHORTHAND_NONE,
        APIC_TRIGGER_MODE_EDGE,
        APIC_LEVEL_ASSERT,
        APIC_DESTINATION_MODE_PHYSICAL,
        APIC_ICR_DELIVERY_MODE_FIXED,
        APIC_IPI_DISPATCH_VECTOR
    );
    MutexUnlock(&IpiData->ProcessorLock);
    return Status;
}

//ApicIpiHalSendNewProcessData