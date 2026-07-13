#include "X2ApicInternals.h"

//reusing x1 code for sanity

UINT32 ApicHalGetX2ApicId(){
    return ApicHalGetX2ApicIdRegister();
}

UINT32 ApicHalGetX2ApicVersion(){
    UINT32 Register = ApicHalGetX2ApicVersionRegister();
    return GET_X1APIC_VERSION_VALUE(Register);
}

UINT32 ApicHalGetX2ApicMaxLvtEntry(){
    UINT32 Register = ApicHalGetX2ApicVersionRegister();
    return GET_X1APIC_MAX_LVT_ENTRY_VALUE(Register);
}

BOOLEAN ApicHalX2ApicSupportsEoiSuppression(){
    UINT32 Register = ApicHalGetX2ApicVersionRegister();
    return GET_X1APIC_SUPPORT_EOI_SUPRESS_VALUE(Register) ? true : false;
}

APIC_TIMER_MODE ApicHalGetX2ApicLvtTimerMode(){
    UINT32 Register = ApicHalGetX2ApicLvtTimerRegister();
    return (APIC_TIMER_MODE)GET_X1APIC_LVT_TIMER_MODE(Register);
}

BOOLEAN ApicHalIsX2ApicLvtTimerMasked(){
    UINT32 Register = ApicHalGetX2ApicLvtTimerRegister();
    return GET_X1APIC_LVT_TIMER_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX2ApicLvtTimerInterruptPending(){
    UINT32 Register = ApicHalGetX2ApicLvtTimerRegister();
    return GET_X1APIC_LVT_TIMER_DELIVERY_STATUS(Register) ? true : false;
}

UINT8 ApicHalGetX2ApicLvtTimerVector(){
    UINT32 Register = ApicHalGetX2ApicLvtTimerRegister();
    return (UINT8)GET_X1APIC_LVT_TIMER_VECTOR(Register); 
}

BOOLEAN ApicHalIsX2ApicLvtCmciMasked(){
    UINT32 Register = ApicHalGetX2ApicLvtCmciRegister();
    return GET_X1APIC_LVT_CMCI_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX2ApicLvtCmciInterruptPending(){
    UINT32 Register = ApicHalGetX2ApicLvtCmciRegister();
    return GET_X1APIC_LVT_CMCI_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtCmciDeliveryMode(){
    UINT32 Register = ApicHalGetX2ApicLvtCmciRegister();
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LVT_CMCI_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX2ApicLvtCmciVector(){
    UINT32 Register = ApicHalGetX2ApicLvtCmciRegister();
    return (UINT8)GET_X1APIC_LVT_CMCI_VECTOR(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint0Masked(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return GET_X1APIC_LINT0_MASK(Register) ? true : false;
}

APIC_TRIGGER_MODE ApicHalGetX2ApicLvtLint0TriggerMode(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return (APIC_TRIGGER_MODE)GET_X1APIC_LINT0_TRIGGER_MODE(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint0IrrSet(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return GET_X1APIC_LINT0_REMOTE_IRR(Register) ? true : false;
}

APIC_IN_PIN_POLARITY ApicHalGetX2ApicLvtLint0InPinPolarity(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return (APIC_IN_PIN_POLARITY)GET_X1APIC_LINT0_INT_PIN_POLARITY(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint0InterruptPending(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return GET_X1APIC_LINT0_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtLint0DeliveryMode(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LINT0_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX2ApicLvtLint0Vector(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return (UINT8)GET_X1APIC_LINT0_VECTOR(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint1Masked(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return GET_X1APIC_LINT1_MASK(Register) ? true : false;
}

APIC_TRIGGER_MODE ApicHalGetX2ApicLvtLint1TriggerMode(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return (APIC_TRIGGER_MODE)GET_X1APIC_LINT1_TRIGGER_MODE(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint1IrrSet(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return GET_X1APIC_LINT1_REMOTE_IRR(Register) ? true : false;
}

APIC_IN_PIN_POLARITY ApicHalGetX2ApicLvtLint1InPinPolarity(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return (APIC_IN_PIN_POLARITY)GET_X1APIC_LINT1_INT_PIN_POLARITY(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint1InterruptPending(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return GET_X1APIC_LINT1_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtLint1DeliveryMode(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LINT1_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX2ApicLvtLint1Vector(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return (UINT8)GET_X1APIC_LINT1_VECTOR(Register);
}

BOOLEAN ApicHalIsX2ApicLvtErrorMasked(){
    UINT32 Register = ApicHalGetX2ApicLvtErrorRegister();
    return GET_X1APIC_ERROR_MASK(Register) ? true : false;
}

BOOLEAN ApicHalGetX2ApicLvtErrorInterruptPending(){
    UINT32 Register = ApicHalGetX2ApicLvtErrorRegister();
    return GET_X1APIC_ERROR_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtErrorDeliveryMode(){
    UINT32 Register = ApicHalGetX2ApicLvtErrorRegister();
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_ERROR_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX2ApicLvtErrorVector(){
    UINT32 Register = ApicHalGetX2ApicLvtErrorRegister();
    return (UINT8)GET_X1APIC_ERROR_VECTOR(Register);
}

BOOLEAN ApicHalIsX2ApicLvtPerformanceMonitoringCountersMasked(){
    UINT32 Register = ApicHalGetX2ApicLvtPerformanceMonitoringCountersRegister();
    return GET_X1APIC_PMC_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX2ApicLvtPerformanceMonitoringCountersInterruptPending(){
    UINT32 Register = ApicHalGetX2ApicLvtPerformanceMonitoringCountersRegister();
    return GET_X1APIC_PMC_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtPerformanceMonitoringCountersDeliveryMode(){
    UINT32 Register = ApicHalGetX2ApicLvtPerformanceMonitoringCountersRegister();
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_PMC_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX2ApicLvtPerformanceMonitoringCountersVector(){
    UINT32 Register = ApicHalGetX2ApicLvtPerformanceMonitoringCountersRegister();
    return (UINT8)GET_X1APIC_PMC_VECTOR(Register);
}

BOOLEAN ApicHalIsX2ApicLvtThermalSensorMasked(){
    UINT32 Register = ApicHalGetX2ApicLvtThermalSensorRegister();
    return GET_X1APIC_TS_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX2ApicLvtThermalSensorInterruptPending(){
    UINT32 Register = ApicHalGetX2ApicLvtThermalSensorRegister();
    return GET_X1APIC_TS_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtThermalSensorDeliveryMode(){
    UINT32 Register = ApicHalGetX2ApicLvtThermalSensorRegister();
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_TS_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX2ApicLvtThermalSensorVector(){
    UINT32 Register = ApicHalGetX2ApicLvtThermalSensorRegister();
    return (UINT8)GET_X1APIC_TS_VECTOR(Register);
}

UINT32 ApicHalGetX2ApicLogicalDestinationRegisterLogicalApicId(){
    return ApicHalGetX2ApicLogicalDestinationRegister();
}

UINT32 ApicHalGetX2ApicTaskPriorityRegisterClass(){
    UINT32 Register = ApicHalGetX2ApicTaskPriorityRegister();
    return GET_X1APIC_TPR_CLASS(Register);
}

UINT32 ApicHalGetX2ApicTaskPriorityRegisterSubClass(){
    UINT32 Register = ApicHalGetX2ApicTaskPriorityRegister();
    return GET_X1APIC_TPR_SUB_CLASS(Register);
}

UINT32 ApicHalGetX2ApicProcessorPriorityRegisterClass(){
    UINT32 Register = ApicHalGetX2ApicProcessorPriorityRegister();
    return GET_X1APIC_PPR_CLASS(Register);
}

UINT32 ApicHalGetX2ApicProcessorPriorityRegisterSubClass(){
    UINT32 Register = ApicHalGetX2ApicProcessorPriorityRegister();
    return GET_X1APIC_PPR_SUB_CLASS(Register);
}

BOOLEAN ApicHalIsX2ApicEoiBroadcastSuppressed(){
    UINT32 Register = ApicHalGetX2ApicSpuriousInterruptVectorRegister();
    return GET_X1APIC_SVR_EOI_BROADCAST_SUPPRESS(Register) ? true : false;
}

BOOLEAN ApicHalIsX2ApicFocusProcessorCheckingEnabled(){
    UINT32 Register = ApicHalGetX2ApicSpuriousInterruptVectorRegister();
    return GET_X1APIC_SVR_FOCUS_PROCESSOR_CHECKING(Register) ? true : false;
}

BOOLEAN ApicHalIsX2ApicSoftwareEnabled(){
    UINT32 Register = ApicHalGetX2ApicSpuriousInterruptVectorRegister();
    return GET_X1APIC_SVR_APIC_SOFTWARE_ENABLE(Register) ? true : false;
}

UINT8 ApicHalGetX2ApicSpuriousInterruptVector(){
    UINT32 Register = ApicHalGetX2ApicSpuriousInterruptVectorRegister();
    return (UINT8)GET_X1APIC_SVR_VECTOR(Register);
}



void ApicHalSetX2ApicLvtTimerMode(APIC_TIMER_MODE TimerMode){
    UINT32 Register = ApicHalGetX2ApicLvtTimerRegister();
    Register = SET_X1APIC_LVT_TIMER_MODE(Register, (UINT32)TimerMode);
    ApicHalSetX2ApicLvtTimerRegister(Register);
}

void ApicHalSetX2ApicLvtTimerMask(BOOLEAN Masked){
    UINT32 Register = ApicHalGetX2ApicLvtTimerRegister();
    Register = SET_X1APIC_LVT_TIMER_MASK(Register, (Masked ? 1 : 0));
    ApicHalSetX2ApicLvtTimerRegister(Register);
}

void ApicHalSetX2ApicLvtTimerVector(UINT8 Vector){
    UINT32 Register = ApicHalGetX2ApicLvtTimerRegister();
    Register = SET_X1APIC_LVT_TIMER_VECTOR(Register, Vector);
    ApicHalSetX2ApicLvtTimerRegister(Register);
}

void ApicHalMaskX2ApicLvtCmci(BOOLEAN Masked){
    UINT32 Register = ApicHalGetX2ApicLvtCmciRegister();
    Register = SET_X1APIC_LVT_CMCI_MASK(Register, (Masked ? 1 : 0));
    ApicHalSetX2ApicLvtCmciRegister(Register);
}
void ApicHalSetX2ApicLvtCmciDeliveryMode(APIC_LVT_DELIVERY_MODE DeliveryMode){
    UINT32 Register = ApicHalGetX2ApicLvtCmciRegister();
    Register = SET_X1APIC_LVT_CMCI_DELIVERY_MODE(Register, (UINT32)DeliveryMode);
    ApicHalSetX2ApicLvtCmciRegister(Register);
}

void ApicHalSetX2ApicLvtCmciVector(UINT8 Vector){
    UINT32 Register = ApicHalGetX2ApicLvtCmciRegister();
    Register = SET_X1APIC_LVT_CMCI_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX2ApicLvtCmciRegister(Register);
}

void ApicHalMaskX2ApicLvtLint0(BOOLEAN Masked){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    Register = SET_X1APIC_LINT0_MASK(Register, (UINT32)(Masked ? 1 : 0));
    ApicHalSetX2ApicLvtLint0Register(Register);
}

void ApicHalSetX2ApicLvtLint0TriggerMode(APIC_TRIGGER_MODE TriggerMode){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    Register = SET_X1APIC_LINT0_TRIGGER_MODE(Register, (UINT32)TriggerMode);
    ApicHalSetX2ApicLvtLint0Register(Register);
}

void ApicHalSetX2ApicLvtLint0InPinPolarity(PVOID ApicBase, APIC_IN_PIN_POLARITY Polarity){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    Register = SET_X1APIC_LINT0_INT_PIN_POLARITY(Register, (UINT32)Polarity);
    ApicHalSetX2ApicLvtLint0Register(Register);
}

void ApicHalSetX2ApicLvtLint0Vector(UINT8 Vector){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    Register = SET_X1APIC_LINT0_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX2ApicLvtLint0Register(Register);
}



void ApicHalMaskX2ApicLvtLint1(BOOLEAN Masked){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    Register = SET_X1APIC_LINT1_MASK(Register, (UINT32)(Masked ? 1 : 0));
    ApicHalSetX2ApicLvtLint1Register(Register);
}

void ApicHalSetX2ApicLvtLint1TriggerMode(APIC_TRIGGER_MODE TriggerMode){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    Register = SET_X1APIC_LINT1_TRIGGER_MODE(Register, (UINT32)TriggerMode);
    ApicHalSetX2ApicLvtLint1Register(Register);
}

void ApicHalSetX2ApicLvtLint1InPinPolarity(PVOID ApicBase, APIC_IN_PIN_POLARITY Polarity){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    Register = SET_X1APIC_LINT1_INT_PIN_POLARITY(Register, (UINT32)Polarity);
    ApicHalSetX2ApicLvtLint1Register(Register);
}

void ApicHalSetX2ApicLvtLint1Vector(UINT8 Vector){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    Register = SET_X1APIC_LINT1_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX2ApicLvtLint1Register(Register);
}


void ApicHalMaskX2ApicLvtError(BOOLEAN Masked){
    UINT32 Register = ApicHalGetX2ApicLvtErrorRegister();
    Register = SET_X1APIC_ERROR_MASK(Register, (UINT32)(Masked ? 1 : 0));
    ApicHalSetX2ApicLvtErrorRegister(Register);
}

void ApicHalSetX2ApicLvtErrorDeliveryMode(APIC_LVT_DELIVERY_MODE DeliveryMode){
    UINT32 Register = ApicHalGetX2ApicLvtErrorRegister();
    Register = SET_X1APIC_ERROR_DELIVERY_MODE(Register, (UINT32)DeliveryMode);
    ApicHalSetX2ApicLvtErrorRegister(Register);
}

void ApicHalSetX2ApicLvtErrorVector(UINT8 Vector){
    UINT32 Register = ApicHalGetX2ApicLvtErrorRegister();
    Register = SET_X1APIC_ERROR_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX2ApicLvtErrorRegister(Register);
}

void ApicHalSetX2ApicLvtPerformanceMonitoringCountersMask(BOOLEAN Masked){
    UINT32 Register = ApicHalGetX2ApicLvtPerformanceMonitoringCountersRegister();
    Register = SET_X1APIC_PMC_MASK(Register, (UINT32)(Masked ? 1 : 0));
    ApicHalSetX2ApicLvtPerformanceMonitoringCountersRegister(Register);
}

void ApicHalSetX2ApicLvtPerformanceMonitoringCountersDeliveryMode(APIC_LVT_DELIVERY_MODE DeliveryMode){
    UINT32 Register = ApicHalGetX2ApicLvtPerformanceMonitoringCountersRegister();
    Register = SET_X1APIC_PMC_DELIVERY_MODE(Register, (UINT32)DeliveryMode);
    ApicHalSetX2ApicLvtPerformanceMonitoringCountersRegister(Register);
}

void ApicHalSetX2ApicLvtPerformanceMonitoringCountersVector(UINT8 Vector){
    UINT32 Register = ApicHalGetX2ApicLvtPerformanceMonitoringCountersRegister();
    Register = SET_X1APIC_PMC_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX2ApicLvtPerformanceMonitoringCountersRegister(Register);
}

void ApicHalMaskX2ApicLvtThermalSensor(PVOID ApicBase, BOOLEAN Masked){
    UINT32 Register = ApicHalGetX2ApicLvtThermalSensorRegister();
    Register = SET_X1APIC_TS_MASK(Register, (UINT32)(Masked ? 1 : 0));
    ApicHalSetX2ApicLvtThermalSensorRegister(Register);
}

void ApicHalSetX2ApicLvtThermalSensorDeliveryMode(APIC_LVT_DELIVERY_MODE DeliveryMode){
    UINT32 Register = ApicHalGetX2ApicLvtThermalSensorRegister();
    Register = SET_X1APIC_TS_DELIVERY_MODE(Register, (UINT32)DeliveryMode);
    ApicHalSetX2ApicLvtThermalSensorRegister(Register);
}

void ApicHalSetX2ApicLvtThermalSensorVector(UINT8 Vector){
    UINT32 Register = ApicHalGetX2ApicLvtThermalSensorRegister();
    Register = SET_X1APIC_TS_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX2ApicLvtThermalSensorRegister(Register);
}

void ApicHalSetX2ApicSendInterruptCommand( 
    UINT32                          DestinationField, 
    APIC_DESTINATION_SHORTHAND      Shorthand,
    APIC_TRIGGER_MODE               TriggerMode,
    APIC_LEVEL                      Level,
    APIC_DESTINATION_MODE           DestinationMode,
    APIC_ICR_DELIVERY_MODE          DeliveryMode,
    UINT8                           Vector
){
    UINT64 Register = ((UINT64)DestinationField << 32) | ((UINT64)Shorthand << 18) | ((UINT64)TriggerMode << 15) | ((UINT64)Level << 14) | ((UINT64)DestinationMode << 11) | ((UINT64)DeliveryMode << 8) | (UINT64)Vector;  
    ApicHalSetX2ApicInterruptCommandRegister(Register);
}

void ApicHalSetX2ApicTaskPriorityRegisterClass(UINT32 Value){
    UINT32 Register = ApicHalGetX2ApicTaskPriorityRegister();
    Register = SET_X1APIC_TPR_CLASS(Register, Value);
    ApicHalSetX2ApicTaskPriorityRegister(Register);
}

void ApicHalSetX2ApicTaskPriorityRegisterSubClass(UINT32 Value){
    UINT32 Register = ApicHalGetX2ApicTaskPriorityRegister();
    Register = SET_X1APIC_TPR_SUB_CLASS(Register, Value);
    ApicHalSetX2ApicTaskPriorityRegister(Register);
}


void ApicHalEnableX2ApicEoiBroadcastSuppression(BOOLEAN Enabled){
    UINT32 Register = ApicHalGetX2ApicSpuriousInterruptVectorRegister();
    Register = SET_X1APIC_SVR_EOI_BROADCAST_SUPPRESS(Register, (Enabled ? 1 : 0));
    ApicHalSetX2ApicSpuriousInterruptVectorRegister(Register);
}

void ApicHalEnableX2ApicFocusProcessorChecking(BOOLEAN Enabled){
    UINT32 Register = ApicHalGetX2ApicSpuriousInterruptVectorRegister();
    Register = SET_X1APIC_SVR_FOCUS_PROCESSOR_CHECKING(Register, (Enabled ? 1 : 0));
    ApicHalSetX2ApicSpuriousInterruptVectorRegister(Register);   
}

void ApicHalEnableX2ApicSoftware(BOOLEAN Enabled){
    UINT32 Register = ApicHalGetX2ApicSpuriousInterruptVectorRegister();
    Register = SET_X1APIC_SVR_APIC_SOFTWARE_ENABLE(Register, (Enabled ? 1 : 0));
    ApicHalSetX2ApicSpuriousInterruptVectorRegister(Register);   
}

void ApicHalSetX2ApicSpuriousInterruptVector(UINT8 Vector){
    UINT32 Register = ApicHalGetX2ApicSpuriousInterruptVectorRegister();
    Register = SET_X1APIC_SVR_VECTOR(Register, (UINT32)Vector);
    ApicHalSetX2ApicSpuriousInterruptVectorRegister(Register);   
}
