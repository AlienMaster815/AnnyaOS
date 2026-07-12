#include "X1ApicInternals.h"

UINT32 ApicHalGetX1ApicId(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicIdRegister(ApicBase);
    return GET_X1APIC_ID_VALUE(Register);
}

UINT32 ApicHalGetX1ApicVersion(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicVersionRegister(ApicBase);
    return GET_X1APIC_VERSION_VALUE(Register);
}

UINT32 ApicHalGetX1ApicMaxLvtEntry(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicVersionRegister(ApicBase);
    return GET_X1APIC_MAX_LVT_ENTRY_VALUE(Register);   
}

BOOLEAN ApicHalX1ApicSupportsEoiSuppresion(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicVersionRegister(ApicBase);
    return GET_X1APIC_SUPPORT_EOI_SUPRESS_VALUE(Register) ? true : false;
}

APIC_TIMER_MODE ApicHalGetX1ApicLvtTimerMode(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegister(ApicBase);
    return (APIC_TIMER_MODE)GET_X1APIC_LVT_TIMER_MODE(Register);
}

BOOLEAN ApicHalIsX1ApicLvtTimerMasked(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegister(ApicBase);
    return GET_X1APIC_LVT_TIMER_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtTimerInterruptPending(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegister(ApicBase);
    return GET_X1APIC_LVT_TIMER_DELIVERY_STATUS(Register) ? true : false;
}

UINT8 ApicHalGetX1ApicLvtTimerVector(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegister(ApicBase);
    return (UINT8)GET_X1APIC_LVT_TIMER_VECTOR(Register);
}

BOOLEAN ApicHalIsX1ApicLvtCmciMasked(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtCmciRegister(ApicBase);
    return GET_X1APIC_LVT_CMCI_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtCmciInterruptPending(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtCmciRegister(ApicBase);
    return GET_X1APIC_LVT_CMCI_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX1ApicLvtCmciDeliveryMode(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtCmciRegister(ApicBase);
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LVT_CMCI_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX1ApicLvtCmciVector(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtCmciRegister(ApicBase);
    return (UINT8)GET_X1APIC_LVT_CMCI_VECTOR(Register);
}

BOOLEAN ApicHalIsX1ApicLvtLint0Masked(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0Register(ApicBase);
    return GET_X1APIC_LINT0_MASK(Register) ? true : false;
}

APIC_TRIGGER_MODE ApicHalGetX1ApicLvtLint0TriggerMode(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0Register(ApicBase);
    return (APIC_TRIGGER_MODE)GET_X1APIC_LINT0_TRIGGER_MODE(Register);
}

BOOLEAN ApicHalIsX1ApicLvtLint0IrrSet(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0Register(ApicBase);
    return GET_X1APIC_LINT0_REMOTE_IRR(Register) ? true : false;
}

APIC_IN_PIN_POLARITY ApicHalGetX1ApicLvtLint0InPinPolarity(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0Register(ApicBase);
    return (APIC_IN_PIN_POLARITY)GET_X1APIC_LINT0_INT_PIN_POLARITY(Register);
}


BOOLEAN ApicHalIsX1ApicLvtLint0InterruptPending(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0Register(ApicBase);
    return GET_X1APIC_LINT0_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX1ApicLvtLint0DeliveryMode(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0Register(ApicBase);
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LINT0_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX1ApicLvtLint0Vector(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0Register(ApicBase);
    return (UINT8)GET_X1APIC_LINT0_VECTOR(Register);
}

BOOLEAN ApicHalIsX1ApicLvtLint1Masked(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1Register(ApicBase);
    return GET_X1APIC_LINT1_MASK(Register) ? true : false;
}

APIC_TRIGGER_MODE ApicHalGetX1ApicLvtLint1TriggerMode(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1Register(ApicBase);
    return (APIC_TRIGGER_MODE)GET_X1APIC_LINT1_TRIGGER_MODE(Register);
}

BOOLEAN ApicHalIsX1ApicLvtLint1IrrSet(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1Register(ApicBase);
    return GET_X1APIC_LINT1_REMOTE_IRR(Register) ? true : false;
}

APIC_IN_PIN_POLARITY ApicHalGetX1ApicLvtLint1InPinPolarity(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1Register(ApicBase);
    return (APIC_IN_PIN_POLARITY)GET_X1APIC_LINT1_INT_PIN_POLARITY(Register);
}

BOOLEAN ApicHalIsX1ApicLvtLint1InterruptPending(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1Register(ApicBase);
    return GET_X1APIC_LINT0_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX1ApicLvtLint1DeliveryMode(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1Register(ApicBase);
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LINT1_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX1ApicLvtLint1Vector(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1Register(ApicBase);
    return (UINT8)GET_X1APIC_LINT1_VECTOR(Register);
}

BOOLEAN ApicHalIsX1ApicLvtErrorMasked(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtErrorRegister(ApicBase);
    return GET_X1APIC_ERROR_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtErrorInterruptPending(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtErrorRegister(ApicBase);
    return GET_X1APIC_ERROR_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX1ApicLvtErrorDeliveryMode(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtErrorRegister(ApicBase);
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_ERROR_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX1ApicLvtErrorVector(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtErrorRegister(ApicBase);
    return (UINT8)GET_X1APIC_ERROR_MASK(Register);
}

BOOLEAN ApicHalIsX1ApicLvtPerformanceMonitoringCountersMasked(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegister(ApicBase);
    return GET_X1APIC_PMC_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtPerformanceMonitoringCountersInterruptPending(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegister(ApicBase);
    return GET_X1APIC_PMC_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX1ApicLvtPerformanceMonitoringCountersDeliveryMode(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegister(ApicBase);
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_PMC_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX1ApicLvtPerformanceMonitoringCountersVector(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegister(ApicBase);
    return (UINT8)GET_X1APIC_PMC_VECTOR(Register);
}

BOOLEAN ApicHalIsX1ApicThermalSensorMasked(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtThermalSensorRegister(ApicBase);
    return GET_X1APIC_TS_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicThermalSensorInterruptPending(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtThermalSensorRegister(ApicBase);
    return GET_X1APIC_TS_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX1ApicThermalSensorDeliveryMode(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtThermalSensorRegister(ApicBase);
    return GET_X1APIC_TS_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX1ApicThermalSensorVector(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtThermalSensorRegister(ApicBase);
    return (UINT8)GET_X1APIC_TS_VECTOR(Register);
}

UINT32 ApicHalGetX1ApicLogicalDestinationLogicalApicId(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLogicalDestinationRegister(ApicBase);
    return GET_X1APIC_LDR_LOGICAL_APIC_ID(Register);
}

UINT32 ApicHalGetX1ApicDestinationFormatRegisterModel(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicDestinationFormatRegister(ApicBase);
    return GET_X1APIC_DFR_MODEL(Register);
}

UINT32 ApicHalGetX1ApicArbitrationPriorityRegisterClass(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicArbitrationPriorityRegister(ApicBase);
    return GET_X1APIC_APR_CLASS(Register);
}

UINT32 ApicHalGetX1ApicArbitrationPriorityRegisterSubClass(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicArbitrationPriorityRegister(ApicBase);
    return GET_X1APIC_APR_SUB_CLASS(Register);
}

UINT32 ApicHalGetX1ApicTaskPriorityRegisterClass(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicTaskPriorityRegister(ApicBase);
    return GET_X1APIC_TPR_CLASS(Register);
}

UINT32 ApicHalGetX1ApicTaskPriorityRegisterSubClass(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicTaskPriorityRegister(ApicBase);
    return GET_X1APIC_TPR_SUB_CLASS(Register);
}

UINT32 ApicHalGetX1ApicProcessorPriorityRegisterClass(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicProcessorPriorityRegister(ApicBase);
    return GET_X1APIC_PPR_CLASS(Register);
}

UINT32 ApicHalGetX1ApicProcessorPriorityRegisterSubClass(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicProcessorPriorityRegister(ApicBase);
    return GET_X1APIC_PPR_SUB_CLASS(Register);
}

BOOLEAN ApicHalIsX1ApicEoiBroadcastSuppressed(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicSpuriousInterruptVectorRegister(ApicBase);
    return GET_X1APIC_SVR_EOI_BROADCAST_SUPPRESS(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicFocusProcessorCheckingEnabled(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicSpuriousInterruptVectorRegister(ApicBase);
    return GET_X1APIC_SVR_FOCUS_PROCESSOR_CHECKING(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicSoftwareEnabled(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicSpuriousInterruptVectorRegister(ApicBase);
    return GET_X1APIC_SVR_APIC_SOFTWARE_ENABLE(Register) ? true : false;
}

UINT8 ApicHalGetX1ApicSpurriousInterruptVector(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicSpuriousInterruptVectorRegister(ApicBase);
    return (UINT8)GET_X1APIC_SVR_VECTOR(Register);
}   



void ApicHalSetX1ApicId(PVOID ApicBase, UINT32 Value){
    UINT32 Tmp = ApicHalGetX1ApicIdRegister(ApicBase);
    Tmp = SET_X1APIC_ID_VALUE(Tmp, Value);
    ApicHalSetX1ApicIdRegister(ApicBase, Value);
}

void ApicHalSetX1ApicLvtTimerMode(PVOID ApicBase, APIC_TIMER_MODE TimerMode){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegister(ApicBase);
    Register = SET_X1APIC_LVT_TIMER_MODE(Register, (UINT32)TimerMode);
    ApicHalSetX1ApicLvtTimerRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLvtTimerMask(PVOID ApicBase, BOOLEAN Masked){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegister(ApicBase);
    Register = SET_X1APIC_LVT_TIMER_MASK(Register, (Masked ? 1 : 0));
    ApicHalSetX1ApicLvtTimerRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLvtTimerVector(PVOID ApicBase, UINT8 Vector){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegister(ApicBase);
    Register = SET_X1APIC_LVT_TIMER_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX1ApicLvtTimerRegister(ApicBase, Register);
}

void ApicHalMaskX1ApicLvtCmci(PVOID ApicBase, BOOLEAN Masked){
    UINT32 Register = ApicHalGetX1ApicLvtCmciRegister(ApicBase);
    Register = SET_X1APIC_LVT_CMCI_MASK(Register, (UINT32)(Masked ? 1 : 0));
    ApicHalSetX1ApicLvtCmciRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLvtCmciDeliveryMode(PVOID ApicBase, APIC_LVT_DELIVERY_MODE DeliveryMode){
    UINT32 Register = ApicHalGetX1ApicLvtCmciRegister(ApicBase);
    Register = SET_X1APIC_LVT_CMCI_DELIVERY_MODE(Register, (UINT32)DeliveryMode);
    ApicHalSetX1ApicLvtCmciRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLvtCmciVector(PVOID ApicBase, UINT8 Vector){
    UINT32 Register = ApicHalGetX1ApicLvtCmciRegister(ApicBase);
    Register = SET_X1APIC_LVT_CMCI_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX1ApicLvtCmciRegister(ApicBase, Register);
}

void ApicHalMaskX1ApicLvtLint0(PVOID ApicBase, BOOLEAN Masked){
    UINT32 Register = ApicHalGetX1ApicLvtLint0Register(ApicBase);
    Register = SET_X1APIC_LINT0_MASK(Register, (UINT32)(Masked ? 1 : 0));
    ApicHalSetX1ApicLvtLint0Register(ApicBase, Register);
}

void ApicHalSetX1ApicLvtLint0TriggerMode(PVOID ApicBase, APIC_TRIGGER_MODE TriggerMode){
    UINT32 Register = ApicHalGetX1ApicLvtLint0Register(ApicBase);
    Register = SET_X1APIC_LINT0_TRIGGER_MODE(Register, (UINT32)TriggerMode);
    ApicHalSetX1ApicLvtLint0Register(ApicBase, Register);
}

void ApicHalSetX1ApicLvtLint0InPinPolarity(PVOID ApicBase, APIC_IN_PIN_POLARITY Polarity){
    UINT32 Register = ApicHalGetX1ApicLvtLint0Register(ApicBase);
    Register = SET_X1APIC_LINT0_INT_PIN_POLARITY(Register,(UINT32)Polarity);
    ApicHalSetX1ApicLvtLint0Register(ApicBase, Register);
}

void ApicHalSetX1ApicLvtLint0Vector(PVOID ApicBase, UINT8 Vector){
    UINT32 Register = ApicHalGetX1ApicLvtLint0Register(ApicBase);
    Register = SET_X1APIC_LINT0_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX1ApicLvtLint0Register(ApicBase, Register);
}

void ApicHalMaskX1ApicLvtLint1(PVOID ApicBase, BOOLEAN Masked){
    UINT32 Register = ApicHalGetX1ApicLvtLint1Register(ApicBase);
    Register = SET_X1APIC_LINT1_MASK(Register, (UINT32)(Masked ? 1 : 0));
    ApicHalSetX1ApicLvtLint1Register(ApicBase, Register);
}

void ApicHalSetX1ApicLvtLint1TriggerMode(PVOID ApicBase, APIC_TRIGGER_MODE TriggerMode){
    UINT32 Register = ApicHalGetX1ApicLvtLint1Register(ApicBase);
    Register = SET_X1APIC_LINT1_TRIGGER_MODE(Register, (UINT32)TriggerMode);
    ApicHalSetX1ApicLvtLint1Register(ApicBase, Register);
}

void ApicHalSetX1ApicLvtLint1InPinPolarity(PVOID ApicBase, APIC_IN_PIN_POLARITY Polarity){
    UINT32 Register = ApicHalGetX1ApicLvtLint1Register(ApicBase);
    Register = SET_X1APIC_LINT1_INT_PIN_POLARITY(Register,(UINT32)Polarity);
    ApicHalSetX1ApicLvtLint1Register(ApicBase, Register);
}

void ApicHalSetX1ApicLvtLint1Vector(PVOID ApicBase, UINT8 Vector){
    UINT32 Register = ApicHalGetX1ApicLvtLint1Register(ApicBase);
    Register = SET_X1APIC_LINT1_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX1ApicLvtLint1Register(ApicBase, Register);
}

void ApicHalMaskX1ApicLvtError(PVOID ApicBase, BOOLEAN Masked){
    UINT32 Register = ApicHalGetX1ApicLvtErrorRegister(ApicBase);
    Register = SET_X1APIC_ERROR_MASK(Register, (UINT32)(Masked ? 1 : 0));
    ApicHalSetX1ApicLvtErrorRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLvtErrorDeliveryMode(PVOID ApicBase, APIC_LVT_DELIVERY_MODE DeliveryMode){
    UINT32 Register = ApicHalGetX1ApicLvtErrorRegister(ApicBase);
    Register = SET_X1APIC_ERROR_DELIVERY_MODE(Register, (UINT32)DeliveryMode);
    ApicHalSetX1ApicLvtErrorRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLvtErrorVector(PVOID ApicBase, UINT8 Vector){
    UINT32 Register = ApicHalGetX1ApicLvtErrorRegister(ApicBase);
    Register = SET_X1APIC_ERROR_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX1ApicLvtErrorRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLvtPerformanceMonitoringCountersMask(PVOID ApicBase, BOOLEAN Masked){
    UINT32 Register = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegister(ApicBase);
    Register = SET_X1APIC_PMC_MASK(Register, (UINT32)(Masked ? 1 : 0));
    ApicHalSetX1ApicLvtPerformanceMonitoringCountersRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLvtPerformanceMonitoringCountersDeliveryMode(PVOID ApicBase, APIC_LVT_DELIVERY_MODE DeliveryMode){
    UINT32 Register = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegister(ApicBase);
    Register = SET_X1APIC_PMC_DELIVERY_MODE(Register, (UINT32)DeliveryMode);
    ApicHalSetX1ApicLvtPerformanceMonitoringCountersRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLvtPerformanceMonitoringCountersVector(PVOID ApicBase, UINT8 Vector){
    UINT32 Register = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegister(ApicBase);
    Register = SET_X1APIC_PMC_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX1ApicLvtPerformanceMonitoringCountersRegister(ApicBase, Register);
}

void ApicHalMaskX1ApicLvtThermalSensor(PVOID ApicBase, BOOLEAN Masked){
    UINT32 Register = ApicHalGetX1ApicLvtThermalSensorRegister(ApicBase);
    Register = SET_X1APIC_TS_MASK(Register, (UINT32)(Masked ? 1 : 0));
    ApicHalSetX1ApicLvtThermalSensorRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLvtThermalSensorDeliveryMode(PVOID ApicBase, APIC_LVT_DELIVERY_MODE DeliveryMode){
    UINT32 Register = ApicHalGetX1ApicLvtThermalSensorRegister(ApicBase);
    Register = SET_X1APIC_TS_DELIVERY_MODE(Register, (UINT32)DeliveryMode);
    ApicHalSetX1ApicLvtThermalSensorRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLvtThermalSensorVector(PVOID ApicBase, UINT8 Vector){
    UINT32 Register = ApicHalGetX1ApicLvtThermalSensorRegister(ApicBase);
    Register = SET_X1APIC_TS_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX1ApicLvtThermalSensorRegister(ApicBase, Register);
}

void ApicHalSetX1ApicSendInterruptCommand(
    PVOID                           ApicBase, 
    UINT8                           DestinationField, 
    APIC_DESTINATION_SHORTHAND      Shorthand,
    APIC_TRIGGER_MODE               TriggerMode,
    APIC_LEVEL                      Level,
    APIC_DESTINATION_MODE           DestinationMode,
    APIC_ICR_DELIVERY_MODE          DeliveryMode,
    UINT8                           Vector
){
    UINT64 Register = ((UINT64)DestinationField << 56) | ((UINT64)Shorthand << 18) | ((UINT64)TriggerMode << 15) | ((UINT64)Level << 14) | ((UINT64)DestinationMode << 11) | ((UINT64)DeliveryMode << 8) | (UINT64)Vector;  
    ApicHalSetX1ApicInterruptCommandRegister(ApicBase, Register);
}

void ApicHalSetX1ApicLogicalDestinationLogicalApicId(PVOID ApicBase, UINT32 Value){
    UINT32 Register = ApicHalGetX1ApicLogicalDestinationRegister(ApicBase);
    Register = SET_X1APIC_LDR_LOGICAL_APIC_ID(Register, Value);
    ApicHalSetX1ApicLogicalDestinationRegister(ApicBase, Register);
}

void ApicHalSetX1ApicDestinationFormatRegisterModel(PVOID ApicBase, UINT32 Value){
    UINT32 Register = ApicHalGetX1ApicDestinationFormatRegister(ApicBase);
    Register = SET_X1APIC_DFR_MODEL(Register, Value);
    ApicHalSetX1ApicDestinationFormatRegister(ApicBase, Register);
}

void ApicHalSetX1ApicTaskPriorityRegisterClass(PVOID ApicBase, UINT32 Value){
    UINT32 Register = ApicHalGetX1ApicTaskPriorityRegister(ApicBase);
    Register = SET_X1APIC_TPR_CLASS(Register, Value);
    ApicHalSetX1ApicTaskPriorityRegister(ApicBase, Register);
}

void ApicHalSetX1ApicTaskPriorityRegisterSubClass(PVOID ApicBase, UINT32 Value){
    UINT32 Register = ApicHalGetX1ApicTaskPriorityRegister(ApicBase);
    Register = SET_X1APIC_TPR_SUB_CLASS(Register, Value);
    ApicHalSetX1ApicTaskPriorityRegister(ApicBase, Register);
}

void ApicHalEnableX1ApicEoiBroadcastSuppression(PVOID ApicBase, BOOLEAN Enabled){
    UINT32 Register = ApicHalGetX1ApicSpuriousInterruptVectorRegister(ApicBase);
    Register = SET_X1APIC_SVR_EOI_BROADCAST_SUPPRESS(Register, (Enabled ? 1 : 0));
    ApicHalSetX1ApicSpuriousInterruptVectorRegister(ApicBase, Register);
}

void ApicHalEnableX1ApicFocusProcessorChecking(PVOID ApicBase, BOOLEAN Enabled){
    UINT32 Register = ApicHalGetX1ApicSpuriousInterruptVectorRegister(ApicBase);
    Register = SET_X1APIC_SVR_FOCUS_PROCESSOR_CHECKING(Register, (Enabled ? 1 : 0));
    ApicHalSetX1ApicSpuriousInterruptVectorRegister(ApicBase, Register);   
}

void ApicHalEnableX1ApicSoftware(PVOID ApicBase, BOOLEAN Enabled){
    UINT32 Register = ApicHalGetX1ApicSpuriousInterruptVectorRegister(ApicBase);
    Register = SET_X1APIC_SVR_APIC_SOFTWARE_ENABLE(Register, (Enabled ? 1 : 0));
    ApicHalSetX1ApicSpuriousInterruptVectorRegister(ApicBase, Register);   
}

void ApicHalSetX1ApicSpuriousInterruptVector(PVOID ApicBase, UINT8 Vector){
    UINT32 Register = ApicHalGetX1ApicSpuriousInterruptVectorRegister(ApicBase);
    Register = SET_X1APIC_SVR_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX1ApicSpuriousInterruptVectorRegister(ApicBase, Register);   
}
