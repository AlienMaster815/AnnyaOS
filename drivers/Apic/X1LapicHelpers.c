#include "X1ApicInternals.h"

UINT32 ApicHalGetX1ApicIdEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicIdRegisterEx(ApicBase);
    return GET_X1APIC_ID_VALUE(Register);
}

UINT32 ApicHalGetX1ApicId(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicIdEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicVersionEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicVersionRegisterEx(ApicBase);
    return GET_X1APIC_VERSION_VALUE(Register);
}

UINT32 ApicHalGetX1ApicVersion(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicVersionEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicMaxLvtEntryEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicVersionRegisterEx(ApicBase);
    return GET_X1APIC_MAX_LVT_ENTRY_VALUE(Register);   
}

UINT32 ApicHalGetX1ApicMaxLvtEntry(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicMaxLvtEntryEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalX1ApicSupportsEoiSuppresionEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicVersionRegisterEx(ApicBase);
    return GET_X1APIC_SUPPORT_EOI_SUPRESS_VALUE(Register) ? true : false;
}

APIC_TIMER_MODE ApicHalGetX1ApicLvtTimerModeEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    return (APIC_TIMER_MODE)GET_X1APIC_LVT_TIMER_MODE(Register);
}

APIC_TIMER_MODE ApicHalGetX1ApicLvtTimerMode(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtTimerModeEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtTimerMaskedEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    return GET_X1APIC_LVT_TIMER_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtTimerMasked(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtTimerMaskedEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtTimerInterruptPendingEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    return GET_X1APIC_LVT_TIMER_DELIVERY_STATUS(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtTimerInterruptPending(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtTimerInterruptPendingEx(ApicDeviceObject->ApicBase);
}

UINT8 ApicHalGetX1ApicLvtTimerVectorEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    return (UINT8)GET_X1APIC_LVT_TIMER_VECTOR(Register);
}

BOOLEAN ApicHalIsX1ApicLvtCmciMaskedEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtCmciRegisterEx(ApicBase);
    return GET_X1APIC_LVT_CMCI_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtCmciMasked(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtCmciMaskedEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtCmciInterruptPendingEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtCmciRegisterEx(ApicBase);
    return GET_X1APIC_LVT_CMCI_DELIVERY_STATUS(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtCmciInterruptPending(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtCmciInterruptPendingEx(ApicDeviceObject->ApicBase);
}

APIC_DELIVERY_MODE ApicHalGetX1ApicLvtCmciDeliveryModeEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtCmciRegisterEx(ApicBase);
    return (APIC_DELIVERY_MODE)GET_X1APIC_LVT_CMCI_DELIVERY_MODE(Register);
}

APIC_DELIVERY_MODE ApicHalGetX1ApicLvtCmciDeliveryMode(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtCmciDeliveryModeEx(ApicDeviceObject->ApicBase);
}

UINT8 ApicHalGetX1ApicLvtCmciVectorEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtCmciRegisterEx(ApicBase);
    return (UINT8)GET_X1APIC_LVT_CMCI_VECTOR(Register);
}

UINT8 ApicHalGetX1ApicLvtCmciVector(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtCmciVectorEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtLint0MaskedEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0RegisterEx(ApicBase);
    return GET_X1APIC_LINT0_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtLint0Masked(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtLint0MaskedEx(ApicDeviceObject->ApicBase);
}

APIC_TRIGGER_MODE ApicHalGetX1ApicLvtLint0TriggerModeEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0RegisterEx(ApicBase);
    return (APIC_TRIGGER_MODE)GET_X1APIC_LINT0_TRIGGER_MODE(Register);
}

APIC_TRIGGER_MODE ApicHalGetX1ApicLvtLint0TriggerMode(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtLint0TriggerModeEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtLint0IrrSetEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0RegisterEx(ApicBase);
    return GET_X1APIC_LINT0_REMOTE_IRR(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtLint0IrrSet(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtLint0IrrSetEx(ApicDeviceObject->ApicBase);
}

APIC_IN_PIN_POLARITY ApicHalGetX1ApicLvtLint0InPinPolarityEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0RegisterEx(ApicBase);
    return (APIC_IN_PIN_POLARITY)GET_X1APIC_LINT0_INT_PIN_POLARITY(Register);
}

APIC_IN_PIN_POLARITY ApicHalGetX1ApicLvtLint0InPinPolarity(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtLint0InPinPolarityEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtLint0InterruptPendingEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0RegisterEx(ApicBase);
    return GET_X1APIC_LINT0_DELIVERY_STATUS(Register) ? true : false;
}

APIC_DELIVERY_MODE ApicHalGetX1ApicLvtLint0DeliveryModeEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0RegisterEx(ApicBase);
    return (APIC_DELIVERY_MODE)GET_X1APIC_LINT0_DELIVERY_MODE(Register);
}

APIC_DELIVERY_MODE ApicHalGetX1ApicLvtLint0DeliveryMode(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtLint0DeliveryModeEx(ApicDeviceObject->ApicBase);
}

UINT8 ApicHalGetX1ApicLvtLint0VectorEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint0RegisterEx(ApicBase);
    return (UINT8)GET_X1APIC_LINT0_VECTOR(Register);
}

UINT8 ApicHalGetX1ApicLvtLint0Vector(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtLint0VectorEx(ApicDeviceObject->ApicBase);
}


BOOLEAN ApicHalIsX1ApicLvtLint1MaskedEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1RegisterEx(ApicBase);
    return GET_X1APIC_LINT1_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtLint1Masked(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtLint1MaskedEx(ApicDeviceObject->ApicBase);
}

APIC_TRIGGER_MODE ApicHalGetX1ApicLvtLint1TriggerModeEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1RegisterEx(ApicBase);
    return (APIC_TRIGGER_MODE)GET_X1APIC_LINT1_TRIGGER_MODE(Register);
}

APIC_TRIGGER_MODE ApicHalGetX1ApicLvtLint1TriggerMode(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtLint1TriggerModeEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtLint1IrrSetEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1RegisterEx(ApicBase);
    return GET_X1APIC_LINT1_REMOTE_IRR(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtLint1IrrSet(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtLint1IrrSetEx(ApicDeviceObject->ApicBase);
}

APIC_IN_PIN_POLARITY ApicHalGetX1ApicLvtLint1InPinPolarityEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1RegisterEx(ApicBase);
    return (APIC_IN_PIN_POLARITY)GET_X1APIC_LINT1_INT_PIN_POLARITY(Register);
}

APIC_IN_PIN_POLARITY ApicHalGetX1ApicLvtLint1InPinPolarity(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtLint1InPinPolarityEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtLint1InterruptPendingEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1RegisterEx(ApicBase);
    return GET_X1APIC_LINT0_DELIVERY_STATUS(Register) ? true : false;
}

APIC_DELIVERY_MODE ApicHalGetX1ApicLvtLint1DeliveryModeEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1RegisterEx(ApicBase);
    return (APIC_DELIVERY_MODE)GET_X1APIC_LINT1_DELIVERY_MODE(Register);
}

APIC_DELIVERY_MODE ApicHalGetX1ApicLvtLint1DeliveryMode(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtLint1DeliveryModeEx(ApicDeviceObject->ApicBase);
}

UINT8 ApicHalGetX1ApicLvtLint1VectorEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtLint1RegisterEx(ApicBase);
    return (UINT8)GET_X1APIC_LINT1_VECTOR(Register);
}

UINT8 ApicHalGetX1ApicLvtLint1Vector(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtLint1VectorEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtErrorMaskedEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtErrorRegisterEx(ApicBase);
    return GET_X1APIC_ERROR_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtErrorMasked(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtErrorMaskedEx(ApicDeviceObject->ApicBase); 
}

BOOLEAN ApicHalIsX1ApicLvtErrorInterruptPendingEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtErrorRegisterEx(ApicBase);
    return GET_X1APIC_ERROR_DELIVERY_STATUS(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtErrorInterruptPending(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtErrorInterruptPendingEx(ApicDeviceObject->ApicBase);
}

APIC_DELIVERY_MODE ApicHalGetX1ApicLvtErrorDeliveryModeEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtErrorRegisterEx(ApicBase);
    return (APIC_DELIVERY_MODE)GET_X1APIC_ERROR_DELIVERY_MODE(Register);
}

APIC_DELIVERY_MODE ApicHalGetX1ApicLvtErrorDeliveryMode(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtErrorDeliveryModeEx(ApicDeviceObject->ApicBase);
}

UINT8 ApicHalGetX1ApicLvtErrorVectorEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtErrorRegisterEx(ApicBase);
    return (UINT8)GET_X1APIC_ERROR_MASK(Register);
}

BOOLEAN ApicHalIsX1ApicLvtPerformanceMonitoringCountersMaskedEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegisterEx(ApicBase);
    return GET_X1APIC_PMC_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtPerformanceMonitoringCountersMasked(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtPerformanceMonitoringCountersMaskedEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtPerformanceMonitoringCountersInterruptPendingEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegisterEx(ApicBase);
    return GET_X1APIC_PMC_DELIVERY_STATUS(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtPerformanceMonitoringCountersInterruptPending(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtPerformanceMonitoringCountersInterruptPendingEx(ApicDeviceObject->ApicBase);
}


APIC_DELIVERY_MODE ApicHalGetX1ApicLvtPerformanceMonitoringCountersDeliveryModeEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegisterEx(ApicBase);
    return (APIC_DELIVERY_MODE)GET_X1APIC_PMC_DELIVERY_MODE(Register);
}

APIC_DELIVERY_MODE ApicHalGetX1ApicLvtPerformanceMonitoringCountersDeliveryMode(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtPerformanceMonitoringCountersDeliveryModeEx(ApicDeviceObject->ApicBase);
}

UINT8 ApicHalGetX1ApicLvtPerformanceMonitoringCountersVectorEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegisterEx(ApicBase);
    return (UINT8)GET_X1APIC_PMC_VECTOR(Register);
}

UINT8 ApicHalGetX1ApicLvtPerformanceMonitoringCountersVector(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtPerformanceMonitoringCountersVector(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicThermalSensorMaskedEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtThermalSensorRegisterEx(ApicBase);
    return GET_X1APIC_TS_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicThermalSensorMasked(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicThermalSensorMaskedEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicThermalSensorInterruptPendingEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtThermalSensorRegisterEx(ApicBase);
    return GET_X1APIC_TS_DELIVERY_STATUS(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicThermalSensorInterruptPending(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicThermalSensorInterruptPendingEx(ApicDeviceObject->ApicBase);
}

APIC_DELIVERY_MODE ApicHalGetX1ApicThermalSensorDeliveryModeEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtThermalSensorRegisterEx(ApicBase);
    return GET_X1APIC_TS_DELIVERY_MODE(Register);
}

APIC_DELIVERY_MODE ApicHalGetX1ApicThermalSensorDeliveryMode(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return (APIC_DELIVERY_MODE)ApicHalGetX1ApicThermalSensorDeliveryModeEx(ApicDeviceObject->ApicBase); 
}

UINT8 ApicHalGetX1ApicThermalSensorVectorEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtThermalSensorRegisterEx(ApicBase);
    return (UINT8)GET_X1APIC_TS_VECTOR(Register);
}

UINT8 ApicHalGetX1ApicThermalSensorVector(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicThermalSensorVectorEx(ApicDeviceObject->ApicBase);
}






void ApicHalSetX1ApicIdEx(PVOID ApicBase, UINT32 Value){
    UINT32 Tmp = ApicHalGetX1ApicIdRegisterEx(ApicBase);
    Tmp = SET_X1APIC_ID_VALUE(Tmp, Value);
    ApicHalSetX1ApicIdRegisterEx(ApicBase, Value);
}

void ApicHalSetX1ApicId(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicIdEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicLvtTimerModeEx(PVOID ApicBase, APIC_TIMER_MODE TimerMode){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    Register = SET_X1APIC_LVT_TIMER_MODE(Register, (UINT32)TimerMode);
    ApicHalSetX1ApicLvtTimerRegisterEx(ApicBase, Register);
}

void ApicHalSetX1ApicLvtTimerMode(PAPIC_DEVICE_OBJECT ApicDeviceObject, APIC_TIMER_MODE TimerMode){
    ApicHalSetX1ApicLvtTimerModeEx(ApicDeviceObject->ApicBase, TimerMode);
}

void ApicHalSetX1ApicLvtTimerMaskEx(PVOID ApicBase, BOOLEAN Masked){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    Register = SET_X1APIC_LVT_TIMER_MASK(Register, (Masked ? 1 : 0));
    ApicHalSetX1ApicLvtTimerRegisterEx(ApicBase, Register);
}

void ApicHalSetX1ApicLvtTimerMask(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN Masked){
    ApicHalSetX1ApicLvtTimerMaskEx(ApicDeviceObject->ApicBase, Masked);
}

void ApicHalSetX1ApicLvtTimerVectorEx(PVOID ApicBase, UINT8 Vector){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    Register = SET_X1APIC_LVT_TIMER_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX1ApicLvtTimerRegisterEx(ApicBase, Register);
}

void ApicHalSetX1ApicLvtTimerVector(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT8 Vector){
    ApicHalSetX1ApicLvtTimerVectorEx(ApicDeviceObject->ApicBase, Vector);
}


/*
#define SET_X1APIC_LVT_CMCI_MASK(CmciRegister, x)                               ((CmciRegister & ~(X1APIC_LVT_CMCI_MASK_MASK << X1APIC_LVT_CMCI_MASK_SHIFT)) | ((x & X1APIC_LVT_CMCI_MASK_MASK) << X1APIC_LVT_CMCI_MASK_SHIFT))
#define SET_X1APIC_LVT_CMCI_DELIVERY_MODE(CmciRegister, x)                      ((CmciRegister & ~(X1APIC_LVT_CMCI_DELIVERY_MODE_MASK << X1APIC_LVT_CMCI_DELIVERY_MODE_SHIFT)) | ((x & X1APIC_LVT_CMCI_DELIVERY_MODE_MASK) << X1APIC_LVT_CMCI_DELIVERY_MODE_SHIFT))
#define SET_X1APIC_LVT_CMCI_VECTOR(CmciRegister, x)                             ((CmciRegister & ~(X1APIC_LVT_CMCI_VECTOR_MASK << X1APIC_LVT_CMCI_VECTOR_SHIFT)) | ((x & X1APIC_LVT_CMCI_VECTOR_MASK) << X1APIC_LVT_CMCI_VECTOR_SHIFT))
#define SET_X1APIC_LINT0_MASK(LintRegister, x)                                  ((LintRegister & ~(X1APIC_LINT0_MASK_MASK << X1APIC_LINT0_MASK_SHIFT)) | ((x & X1APIC_LINT0_MASK_MASK) << X1APIC_LINT0_MASK_SHIFT))
#define SET_X1APIC_LINT0_TRIGGER_MODE(LintRegister, x)                          ((LintRegister & ~(X1APIC_LINT0_TRIGGER_MODE_MASK << X1APIC_LINT0_TRIGGER_MODE_SHIFT)) | ((x & X1APIC_LINT0_TRIGGER_MODE_MASK) << X1APIC_LINT0_TRIGGER_MODE_SHIFT))
#define SET_X1APIC_LINT0_INT_PIN_POLARITY(LintRegister, x)                      ((LintRegister & ~(X1APIC_LINT0_INT_PIN_POLARITY_MASK << X1APIC_LINT0_INT_PIN_POLARITY_SHIFT)) | ((x & X1APIC_LINT0_INT_PIN_POLARITY_MASK) << X1APIC_LINT0_INT_PIN_POLARITY_SHIFT))
#define SET_X1APIC_LINT0_DELIVERY_MODE(LintRegister, x)                         ((LintRegister & ~(X1APIC_LINT0_DELIVERY_MODE_MASK << X1APIC_LINT0_DELIVERY_MODE_SHIFT)) | ((x & X1APIC_LINT0_DELIVERY_MODE_MASK) << X1APIC_LINT0_DELIVERY_MODE_SHIFT))
#define SET_X1APIC_LINT0_VECTOR(LintRegister, x)                                ((LintRegister & ~(X1APIC_LINT0_VECTOR_MASK << X1APIC_LINT0_VECTOR_SHIFT)) | ((x & X1APIC_LINT0_VECTOR_MASK) << X1APIC_LINT0_VECTOR_SHIFT))
#define SET_X1APIC_LINT1_MASK(LintRegister, x)                                  ((LintRegister & ~(X1APIC_LINT1_MASK_MASK << X1APIC_LINT1_MASK_SHIFT)) | ((x & X1APIC_LINT1_MASK_MASK) << X1APIC_LINT1_MASK_SHIFT))
#define SET_X1APIC_LINT1_TRIGGER_MODE(LintRegister, x)                          ((LintRegister & ~(X1APIC_LINT1_TRIGGER_MODE_MASK << X1APIC_LINT1_TRIGGER_MODE_SHIFT)) | ((x & X1APIC_LINT1_TRIGGER_MODE_MASK) << X1APIC_LINT1_TRIGGER_MODE_SHIFT))
#define SET_X1APIC_LINT1_INT_PIN_POLARITY(LintRegister, x)                      ((LintRegister & ~(X1APIC_LINT1_INT_PIN_POLARITY_MASK << X1APIC_LINT1_INT_PIN_POLARITY_SHIFT)) | ((x & X1APIC_LINT1_INT_PIN_POLARITY_MASK) << X1APIC_LINT1_INT_PIN_POLARITY_SHIFT))
#define SET_X1APIC_LINT1_VECTOR(LintRegister, x)                                ((LintRegister & ~(X1APIC_LINT1_VECTOR_MASK << X1APIC_LINT1_VECTOR_SHIFT)) | ((x & X1APIC_LINT1_VECTOR_MASK) << X1APIC_LINT1_VECTOR_SHIFT))
#define SET_X1APIC_ERROR_MASK(ErrorRegister, x)                                 ((ErrorRegister & ~(X1APIC_ERROR_MASK_MASK << X1APIC_ERROR_MASK_SHIFT)) | ((x & X1APIC_ERROR_MASK_MASK) << X1APIC_ERROR_MASK_SHIFT))
#define SET_X1APIC_ERROR_DELIVERY_MODE(ErrorRegister, x)                        ((ErrorRegister & ~(X1APIC_ERROR_DELIVERY_MODE_MASK << X1APIC_ERROR_DELIVERY_MODE_SHIFT)) | ((x & X1APIC_ERROR_DELIVERY_MODE_MASK) << X1APIC_ERROR_DELIVERY_MODE_SHIFT))
#define SET_X1APIC_ERROR_VECTOR(ErrorRegister, x)                               ((ErrorRegister & ~(X1APIC_ERROR_VECTOR_MASK << X1APIC_ERROR_VECTOR_SHIFT)) | ((x & X1APIC_ERROR_VECTOR_MASK) << X1APIC_ERROR_VECTOR_SHIFT))
#define SET_X1APIC_PMC_MASK(PmcRegister, x)                                     ((PmcRegister & ~(X1APIC_PMC_MASK_MASK << X1APIC_PMC_MASK_SHIFT)) | ((x & X1APIC_PMC_MASK_MASK) << X1APIC_PMC_MASK_SHIFT))
#define SET_X1APIC_PMC_DELIVERY_MODE(PmcRegister, x)                            ((PmcRegister & ~(X1APIC_PMC_DELIVERY_MODE_MASK << X1APIC_PMC_DELIVERY_MODE_SHIFT)) | ((x & X1APIC_PMC_DELIVERY_MODE_MASK) << X1APIC_PMC_DELIVERY_MODE_SHIFT))
#define SET_X1APIC_PMC_VECTOR(PmcRegister, x)                                   ((PmcRegister & ~(X1APIC_PMC_VECTOR_MASK << X1APIC_PMC_VECTOR_SHIFT)) | ((x & X1APIC_PMC_VECTOR_MASK) << X1APIC_PMC_VECTOR_SHIFT))
#define SET_X1APIC_TS_MASK(TsRegister, x)                                       ((TsRegister & ~(X1APIC_TS_MASK_MASK << X1APIC_TS_MASK_SHIFT)) | ((x & X1APIC_TS_MASK_MASK) << X1APIC_TS_MASK_SHIFT))
#define SET_X1APIC_TS_DELIVERY_MODE(TsRegister, x)                              ((TsRegister & ~(X1APIC_TS_DELIVERY_MODE_MASK << X1APIC_TS_DELIVERY_MODE_SHIFT)) | ((x & X1APIC_TS_DELIVERY_MODE_MASK) << X1APIC_TS_DELIVERY_MODE_SHIFT))
#define SET_X1APIC_TS_VECTOR(TsRegister, x)                                     ((TsRegister & ~(X1APIC_TS_VECTOR_MASK << X1APIC_TS_VECTOR_SHIFT)) | ((x & X1APIC_TS_VECTOR_MASK) << X1APIC_TS_VECTOR_SHIFT))
*/