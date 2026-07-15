#include "X1ApicInternals.h"
#include "X2ApicInternals.h"
#include "ApicInternals.h"

LOUSTATUS ApicHalGetApicIdRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* IdOut){
    return ApicHalGetApicIdRegisterEx(ApicDeviceObject, IdOut);
}

LOUSTATUS 
ApicHalGetApicVersionRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             VersionOut,
    UINT32*             MaxLvtOut,
    BOOLEAN*            SupportsEoiSuppresionOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicVersionRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(VersionOut){
        *VersionOut = GET_X1APIC_VERSION_VALUE(Register);
    }
    if(MaxLvtOut){
        *MaxLvtOut = GET_X1APIC_MAX_LVT_ENTRY_VALUE(Register);
    }
    if(SupportsEoiSuppresionOut){
        *SupportsEoiSuppresionOut = GET_X1APIC_SUPPORT_EOI_SUPRESS_VALUE(Register) ? true : false;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicLvtTimerRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    APIC_TIMER_MODE*    TimerModeOut,
    BOOLEAN*            MaskedOut,
    BOOLEAN*            InterruptPendingOut,
    UINT8*              VectorOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtTimerRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(TimerModeOut){
        *TimerModeOut = (APIC_TIMER_MODE)GET_X1APIC_LVT_TIMER_MODE(Register);
    }
    if(MaskedOut){
        *MaskedOut = GET_X1APIC_LVT_TIMER_MASK(Register) ? true : false;
    }
    if(InterruptPendingOut){
        *InterruptPendingOut = GET_X1APIC_LVT_TIMER_DELIVERY_STATUS(Register) ? true : false;
    }
    if(VectorOut){
        *VectorOut = (UINT8)GET_X1APIC_LVT_TIMER_VECTOR(Register);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicLvtCmciRegister(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedOut,
    BOOLEAN*                    InterruptPendingOut,
    APIC_LVT_DELIVERY_MODE*     DeliveryModeOut,
    UINT8*                      VectorOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtCmciRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedOut){
        *MaskedOut = GET_X1APIC_LVT_CMCI_MASK(Register) ? true : false;
    }
    if(InterruptPendingOut){
        *InterruptPendingOut = GET_X1APIC_LVT_CMCI_DELIVERY_STATUS(Register) ? true : false;
    }
    if(DeliveryModeOut){
        *DeliveryModeOut = (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LVT_CMCI_DELIVERY_MODE(Register);
    }
    if(VectorOut){
        *VectorOut = (UINT8)GET_X1APIC_LVT_CMCI_VECTOR(Register);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicLvtLint0Register(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedOut,
    APIC_TRIGGER_MODE*          TriggerModeOut,
    BOOLEAN*                    IrrSetOut,
    APIC_IN_PIN_POLARITY*       InPinPolarityOut,
    BOOLEAN*                    InterruptPendingOut,
    APIC_LVT_DELIVERY_MODE*     DeliveryModeOut,
    UINT8*                      VectorOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtLint0RegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedOut){
        *MaskedOut = GET_X1APIC_LINT0_MASK(Register) ? true : false;
    }
    if(TriggerModeOut){
        *TriggerModeOut = (APIC_TRIGGER_MODE)GET_X1APIC_LINT0_TRIGGER_MODE(Register);
    }
    if(IrrSetOut){
        *IrrSetOut = GET_X1APIC_LINT0_REMOTE_IRR(Register) ? true : false;
    }
    if(InPinPolarityOut){
        *InPinPolarityOut = (APIC_IN_PIN_POLARITY)GET_X1APIC_LINT0_INT_PIN_POLARITY(Register);
    }
    if(InterruptPendingOut){
        *InterruptPendingOut = GET_X1APIC_LINT0_DELIVERY_STATUS(Register) ? true : false;
    }
    if(DeliveryModeOut){
        *DeliveryModeOut = (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LINT0_DELIVERY_MODE(Register);
    }
    if(VectorOut){
        *VectorOut = (UINT8)GET_X1APIC_LINT0_VECTOR(Register);
    }
    return STATUS_SUCCESS;
}


LOUSTATUS 
ApicHalGetApicLvtLint1Register(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedOut,
    APIC_TRIGGER_MODE*          TriggerModeOut,
    BOOLEAN*                    IrrSetOut,
    APIC_IN_PIN_POLARITY*       InPinPolarityOut,
    BOOLEAN*                    InterruptPendingOut,
    APIC_LVT_DELIVERY_MODE*     DeliveryModeOut,
    UINT8*                      VectorOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtLint1RegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedOut){
        *MaskedOut = GET_X1APIC_LINT1_MASK(Register) ? true : false;
    }
    if(TriggerModeOut){
        *TriggerModeOut = (APIC_TRIGGER_MODE)GET_X1APIC_LINT1_TRIGGER_MODE(Register);
    }
    if(IrrSetOut){
        *IrrSetOut = GET_X1APIC_LINT1_REMOTE_IRR(Register) ? true : false;
    }
    if(InPinPolarityOut){
        *InPinPolarityOut = (APIC_IN_PIN_POLARITY)GET_X1APIC_LINT1_INT_PIN_POLARITY(Register);
    }
    if(InterruptPendingOut){
        *InterruptPendingOut = GET_X1APIC_LINT1_DELIVERY_STATUS(Register) ? true : false;
    }
    if(DeliveryModeOut){
        *DeliveryModeOut = (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LINT1_DELIVERY_MODE(Register);
    }
    if(VectorOut){
        *VectorOut = (UINT8)GET_X1APIC_LINT1_VECTOR(Register);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicLvtErrorRegister(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedOut,
    BOOLEAN*                    InterruptPendingOut,
    APIC_LVT_DELIVERY_MODE*     DeliveryModeOut,
    UINT8*                      VectorOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtErrorRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedOut){
        *MaskedOut = GET_X1APIC_ERROR_MASK(Register) ? true : false;
    }
    if(InterruptPendingOut){
        *InterruptPendingOut = GET_X1APIC_ERROR_DELIVERY_STATUS(Register) ? true : false;
    }
    if(DeliveryModeOut){
        *DeliveryModeOut = (APIC_LVT_DELIVERY_MODE)GET_X1APIC_ERROR_DELIVERY_MODE(Register);
    }
    if(VectorOut){
        *VectorOut = (UINT8)GET_X1APIC_ERROR_VECTOR(Register);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicLvtPerformanceMonitoringCountersRegister(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedOut,
    BOOLEAN*                    InterruptPendingOut,
    APIC_LVT_DELIVERY_MODE*     DeliveryModeOut,
    UINT8*                      VectorOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtPerformanceMonitoringCountersRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedOut){
        *MaskedOut = GET_X1APIC_PMC_MASK(Register) ? true : false;
    }
    if(InterruptPendingOut){
        *InterruptPendingOut = GET_X1APIC_PMC_DELIVERY_STATUS(Register) ? true : false;
    }
    if(DeliveryModeOut){
        *DeliveryModeOut = (APIC_LVT_DELIVERY_MODE)GET_X1APIC_PMC_DELIVERY_MODE(Register);
    }
    if(VectorOut){
        *VectorOut = (UINT8)GET_X1APIC_PMC_VECTOR(Register);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicLvtThermalSensorRegister(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedOut,
    BOOLEAN*                    InterruptPendingOut,
    APIC_LVT_DELIVERY_MODE*     DeliveryModeOut,
    UINT8*                      VectorOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtThermalSensorRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedOut){
        *MaskedOut = GET_X1APIC_TS_MASK(Register) ? true : false;
    }
    if(InterruptPendingOut){
        *InterruptPendingOut = GET_X1APIC_TS_DELIVERY_STATUS(Register) ? true : false;
    }
    if(DeliveryModeOut){
        *DeliveryModeOut = (APIC_LVT_DELIVERY_MODE)GET_X1APIC_TS_DELIVERY_MODE(Register);
    }
    if(VectorOut){
        *VectorOut = (UINT8)GET_X1APIC_TS_VECTOR(Register);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicLogicalDestinationRegister(
    PAPIC_DEVICE_OBJECT     ApicDeviceObject,
    UINT32*                 IdOut
){
    return ApicHalGetApicLogicalDestinationRegisterEx(ApicDeviceObject, IdOut);
}

LOUSTATUS 
ApicHalGetApicDestinationFormatRegister(
    PAPIC_DEVICE_OBJECT     ApicDeviceObject,
    UINT32*                 DfrModelOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicDestinationFormatRegister(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(DfrModelOut){
        *DfrModelOut = GET_X1APIC_DFR_MODEL(Register);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicArbitrationPriorityRegister(
    PAPIC_DEVICE_OBJECT     ApicDeviceObject,
    UINT32*                 ClassOut,
    UINT32*                 SubClassOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicArbitrationPriorityRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    if(ClassOut){
        *ClassOut = GET_X1APIC_APR_CLASS(Register);
    }
    if(SubClassOut){
        *SubClassOut = GET_X1APIC_APR_SUB_CLASS(Register);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicTaskPriorityRegister(
    PAPIC_DEVICE_OBJECT     ApicDeviceObject,
    UINT32*                 ClassOut,
    UINT32*                 SubClassOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicTaskPriorityRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    if(ClassOut){
        *ClassOut = GET_X1APIC_TPR_CLASS(Register);
    }
    if(SubClassOut){
        *SubClassOut = GET_X1APIC_TPR_SUB_CLASS(Register);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicProcessorPriorityRegister(
    PAPIC_DEVICE_OBJECT     ApicDeviceObject,
    UINT32*                 ClassOut,
    UINT32*                 SubClassOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicProcessorPriorityRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    if(ClassOut){
        *ClassOut = GET_X1APIC_PPR_CLASS(Register);
    }
    if(SubClassOut){
        *SubClassOut = GET_X1APIC_PPR_SUB_CLASS(Register);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
ApicHalGetApicSpuriousInterruptVectorRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    BOOLEAN*            EoiBroadcastSuppresedOut,
    BOOLEAN*            FocusProcessorCheckingEnabledOut,
    BOOLEAN*            ApicSoftwareEnabledOut,
    UINT8*              SpuriousInterruptVectorOut
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicSpuriousInterruptVectorRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(EoiBroadcastSuppresedOut){
        *EoiBroadcastSuppresedOut = GET_X1APIC_SVR_EOI_BROADCAST_SUPPRESS(Register) ? true : false;
    }
    if(FocusProcessorCheckingEnabledOut){
        *FocusProcessorCheckingEnabledOut = GET_X1APIC_SVR_FOCUS_PROCESSOR_CHECKING(Register) ? true : false;
    }
    if(ApicSoftwareEnabledOut){
        *ApicSoftwareEnabledOut = GET_X1APIC_SVR_APIC_SOFTWARE_ENABLE(Register) ? true : false;
    }
    if(SpuriousInterruptVectorOut){
        *SpuriousInterruptVectorOut = (UINT8)GET_X1APIC_SVR_VECTOR(Register);
    }
    return STATUS_SUCCESS;
}