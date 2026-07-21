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

KERNEL_EXPORT 
void 
LouKeIpicSendNewInterruptRoutingData(
    ULONG Processor,
    PVOID Data
);

LOUSTATUS ApicHalInterProcessorInterruptHandler(UINT64 Data){
    PIPI_INTERRUPT_PACKET InterruptPacket = (PIPI_INTERRUPT_PACKET)Data;
    ULONG Processor = LouKeGetCurrentProcessorNumber();
    switch(InterruptPacket->PacketType){
        case ROUTE_INSTALLATION_INTERRUPT:
            LouKeIpicSendNewInterruptRoutingData(Processor, InterruptPacket->RouteInstallationPacket.InstallData);
            break;
        default:
            LouPrint("APIC.SYS:ApicHalInterProcessorInterruptHandler():Unhandled IPI\n");
            break;
    }
    return STATUS_SUCCESS;
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
    LouKIRQL Irql;
    LOUSTATUS Status;
    PPER_PROCESSOR_IPI_DATA IpiData  = &PerProcessorApicData[Cpu].IpiData;
    
    LouKeAcquireSpinLock(&IpiData->ProcessorLock, &Irql);
    ULONG Processor = LouKeGetCurrentProcessorNumber(Cpu); 
    if(Cpu == Processor){
        LouKeIpicSendNewInterruptRoutingData(Processor, RouteData);
        LouKeReleaseSpinLock(&IpiData->ProcessorLock, &Irql);
        return STATUS_SUCCESS;
    }
    

    ApicHalSetLocalApicErrorStatus(0);

    BOOLEAN InterruptPending = true;
    while(InterruptPending){
        Status = ApicHalGetLocalApicInterruptCommandRegister(0x00, 0x00, 0x00, 0x00, &InterruptPending, 0x00, 0x00, 0x00);
        if(Status != STATUS_SUCCESS){
            LouKeReleaseSpinLock(&IpiData->ProcessorLock, &Irql);
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
    LouKeReleaseSpinLock(&IpiData->ProcessorLock, &Irql);
    return Status;
}


//ApicIpiHalSendNewProcessData