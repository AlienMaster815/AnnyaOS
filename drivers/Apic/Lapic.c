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
    LOUSTATUS Status = ApicHalGetApicDestinationFormatRegisterEx(ApicDeviceObject, &Register);
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

LOUSTATUS ApicHalSetApicIdRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    UINT32*             IdIn
){  
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicIdRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(IdIn){
        Register = SET_X1APIC_ID_VALUE(Register, (*IdIn));
    }
    return ApicHalSetApicIdRegisterEx(ApicDeviceObject, Register);
}

LOUSTATUS 
ApicHalSetApicLvtTimerRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    APIC_TIMER_MODE*    TimerModeIn,
    BOOLEAN*            MaskedIn,
    UINT8*              VectorIn
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtTimerRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(TimerModeIn){
        Register = SET_X1APIC_LVT_TIMER_MODE(Register, (UINT32)(*TimerModeIn));
    }
    if(MaskedIn){
        Register = SET_X1APIC_LVT_TIMER_MASK(Register, ((*MaskedIn) ? 1 : 0));
    }
    if(VectorIn){
        Register = SET_X1APIC_LVT_TIMER_VECTOR(Register, (UINT32)(*VectorIn));
    }
    ApicHalSetApicLvtTimerRegisterEx(ApicDeviceObject, Register);
}

LOUSTATUS 
ApicHalSetApicLvtCmciRegister(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedIn,
    APIC_LVT_DELIVERY_MODE*     DeliveryModeIn,
    UINT8*                      VectorIn
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtCmciRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedIn){
        Register = SET_X1APIC_LVT_CMCI_MASK(Register, ((*MaskedIn) ? 1 : 0));
    }
    if(DeliveryModeIn){
        Register = SET_X1APIC_LVT_CMCI_DELIVERY_MODE(Register, (UINT32)(*DeliveryModeIn));
    }
    if(VectorIn){
        Register = SET_X1APIC_LVT_CMCI_VECTOR(Register, (UINT32)(*VectorIn));
    }
    return ApicHalSetApicLvtCmciRegisterEx(ApicDeviceObject, Register);
}

LOUSTATUS 
ApicHalSetApicLvtLint0Register(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedIn,
    APIC_TRIGGER_MODE*          TriggerModeIn,
    APIC_IN_PIN_POLARITY*       InPinPolarityIn,
    UINT8*                      VectorIn
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtLint0RegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedIn){
        Register = SET_X1APIC_LINT0_MASK(Register, ((*MaskedIn) ? 1 : 0));
    }
    if(TriggerModeIn){
        Register = SET_X1APIC_LINT0_TRIGGER_MODE(Register, (UINT32)(*TriggerModeIn));
    }
    if(InPinPolarityIn){
        Register = SET_X1APIC_LINT0_INT_PIN_POLARITY(Register, (UINT32)(*InPinPolarityIn));
    }
    if(VectorIn){
        Register = SET_X1APIC_LINT0_VECTOR(Register, (UINT32)(*VectorIn));
    }
    return ApicHalSetApicLvtLint0RegisterEx(ApicDeviceObject, Register);
}

LOUSTATUS 
ApicHalSetApicLvtLint1Register(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedIn,
    APIC_TRIGGER_MODE*          TriggerModeIn,
    APIC_IN_PIN_POLARITY*       InPinPolarityIn,
    UINT8*                      VectorIn
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtLint1RegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedIn){
        Register = SET_X1APIC_LINT1_MASK(Register, ((*MaskedIn) ? 1 : 0));
    }
    if(TriggerModeIn){
        Register = SET_X1APIC_LINT1_TRIGGER_MODE(Register, (UINT32)(*TriggerModeIn));
    }
    if(InPinPolarityIn){
        Register = SET_X1APIC_LINT1_INT_PIN_POLARITY(Register, (UINT32)(*InPinPolarityIn));
    }
    if(VectorIn){
        Register = SET_X1APIC_LINT1_VECTOR(Register, (UINT32)(*VectorIn));
    }
    return ApicHalSetApicLvtLint1RegisterEx(ApicDeviceObject, Register);
}

LOUSTATUS 
ApicHalSetApicLvtErrorRegister(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedIn,
    APIC_LVT_DELIVERY_MODE*     DeliveryModeIn,
    UINT8*                      VectorIn
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtErrorRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedIn){
        Register = SET_X1APIC_ERROR_MASK(Register, ((*MaskedIn) ? 1 : 0));
    }
    if(DeliveryModeIn){
        Register = SET_X1APIC_ERROR_DELIVERY_MODE(Register, (UINT32)(*DeliveryModeIn));
    }
    if(VectorIn){
        Register = SET_X1APIC_ERROR_VECTOR(Register, (UINT32)(*VectorIn));
    }    
    return ApicHalSetApicLvtErrorRegisterEx(ApicDeviceObject, Register);
}

LOUSTATUS 
ApicHalSetApicLvtPerformanceMonitoringCountersRegister(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedIn,
    APIC_LVT_DELIVERY_MODE*     DeliveryModeIn,
    UINT8*                      VectorIn
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtPerformanceMonitoringCountersRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedIn){
        Register = SET_X1APIC_PMC_MASK(Register, ((*MaskedIn) ? 1 : 0));
    }
    if(DeliveryModeIn){
        Register = SET_X1APIC_PMC_DELIVERY_MODE(Register, (UINT32)(*DeliveryModeIn));
    }
    if(VectorIn){
        Register = SET_X1APIC_PMC_VECTOR(Register, (UINT32)(*VectorIn));
    }    
    return ApicHalSetApicLvtPerformanceMonitoringCountersRegisterEx(ApicDeviceObject, Register);
}

LOUSTATUS 
ApicHalSetApicLvtThermalSensorRegister(
    PAPIC_DEVICE_OBJECT         ApicDeviceObject,
    BOOLEAN*                    MaskedIn,
    APIC_LVT_DELIVERY_MODE*     DeliveryModeIn,
    UINT8*                      VectorIn
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicLvtThermalSensorRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(MaskedIn){
        Register = SET_X1APIC_TS_MASK(Register, ((*MaskedIn) ? 1 : 0));
    }
    if(DeliveryModeIn){
        Register = SET_X1APIC_TS_DELIVERY_MODE(Register, (UINT32)(*DeliveryModeIn));
    }
    if(VectorIn){
        Register = SET_X1APIC_TS_VECTOR(Register, (UINT32)(*VectorIn));
    }    
    return ApicHalSetApicLvtThermalSensorRegisterEx(ApicDeviceObject, Register);
}

LOUSTATUS 
ApicHalSetApicInterruptCommandRegister(
    PAPIC_DEVICE_OBJECT             ApicDeviceObject,
    UINT32                          DestinationField,
    APIC_DESTINATION_SHORTHAND      Shorthand,
    APIC_TRIGGER_MODE               TriggerMode,
    APIC_LEVEL                      Level,
    APIC_DESTINATION_MODE           DestinationMode,
    APIC_ICR_DELIVERY_MODE          DeliveryMode,
    UINT8                           Vector
){
    UINT8 Shift = 0;
    APIC_OBJECT_TYPE ObjectType = ApicDeviceObject->ApicObjectType;
    switch(ObjectType){
        case X1_LOCAL_APIC_OBJECT_TYPE:
            Shift = 56;
            break;
        case X2_LOCAL_APIC_OBJECT_TYPE:
            Shift = 32;
            break;
        case IO_APIC_OBJECT_TYPE:
            ApicHalDbgPrint("APIC.SYS:WARNING:IO Apic Device:%h Input Into Local Apic Function:ApicHalGetApicDivideConfigurationRegisterEx()\n", ApicDeviceObject);
        default:
            return STATUS_INVALID_PARAMETER;
    }
    UINT64 Register = ((UINT64)DestinationField << Shift) | ((UINT64)Shorthand << 18) | ((UINT64)TriggerMode << 15) | ((UINT64)Level << 14) | ((UINT64)DestinationMode << 11) | ((UINT64)DeliveryMode << 8) | (UINT64)Vector;
    ApicHalSetApicInterruptCommandRegisterEx(ApicDeviceObject, Register);
}


LOUSTATUS 
ApicHalSetApicLogicalDestinationRegister(
    PAPIC_DEVICE_OBJECT     ApicDeviceObject,
    UINT32*                 IdIn
){
    if(!IdIn){
        return STATUS_INVALID_PARAMETER;
    }
    return ApicHalSetApicLogicalDestinationRegisterEx(ApicDeviceObject, (*IdIn));
}

LOUSTATUS 
ApicHalSetApicDestinationFormatRegister(
    PAPIC_DEVICE_OBJECT     ApicDeviceObject,
    UINT32*                 DfrModelIn
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicDestinationFormatRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(DfrModelIn){
        Register = SET_X1APIC_DFR_MODEL(Register, (*DfrModelIn));
    }
    return ApicHalSetApicDestinationFormatRegisterEx(ApicDeviceObject, Register);
}

LOUSTATUS 
ApicHalSetApicTaskPriorityRegister(
    PAPIC_DEVICE_OBJECT     ApicDeviceObject,
    UINT32*                 ClassIn,
    UINT32*                 SubClassIn
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicTaskPriorityRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(ClassIn){
        Register = SET_X1APIC_TPR_CLASS(Register, (*ClassIn));
    }
    if(SubClassIn){
        Register = SET_X1APIC_TPR_SUB_CLASS(Register, (*ClassIn));
    }
    return ApicHalSetApicTaskPriorityRegisterEx(ApicDeviceObject, Register);
}

LOUSTATUS 
ApicHalSetApicSpuriousInterruptVectorRegister(
    PAPIC_DEVICE_OBJECT ApicDeviceObject,
    BOOLEAN*            EoiBroadcastSuppresedIn,
    BOOLEAN*            FocusProcessorCheckingEnabledIn,
    BOOLEAN*            ApicSoftwareEnabledIn,
    UINT8*              SpuriousInterruptVectorIn
){
    UINT32 Register;
    LOUSTATUS Status = ApicHalGetApicSpuriousInterruptVectorRegisterEx(ApicDeviceObject, &Register);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(EoiBroadcastSuppresedIn){
        Register = SET_X1APIC_SVR_EOI_BROADCAST_SUPPRESS(Register, ((*EoiBroadcastSuppresedIn) ? 1 : 0));
    }
    if(FocusProcessorCheckingEnabledIn){
        Register = SET_X1APIC_SVR_FOCUS_PROCESSOR_CHECKING(Register, ((*FocusProcessorCheckingEnabledIn) ? 1 : 0));
    }
    if(ApicSoftwareEnabledIn){
        Register = SET_X1APIC_SVR_APIC_SOFTWARE_ENABLE(Register, ((*ApicSoftwareEnabledIn) ? 1 : 0));
    }
    if(SpuriousInterruptVectorIn){
        Register = SET_X1APIC_SVR_VECTOR(Register, (UINT32)(*SpuriousInterruptVectorIn));
    }
    return ApicHalSetApicSpuriousInterruptVectorRegisterEx(ApicDeviceObject, Register);
}