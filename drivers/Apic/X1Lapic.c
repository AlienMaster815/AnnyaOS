#include "X1ApicInternals.h"

UINT32 ApicHalGetX1ApicIdRegisterEx(PVOID ApicBase){
    return GET_X1APIC_ID_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicVersionRegisterEx(PVOID ApicBase){
    return GET_X1APIC_VERSION_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicTaskPriorityRegisterEx(PVOID ApicBase){
    return GET_X1APIC_TASK_PRIORITY_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicArbitrationPriorityRegisterEx(PVOID ApicBase){
    return GET_X1APIC_ARBITRATION_PRIOIRTY_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicProcessorPriorityRegisterEx(PVOID ApicBase){
    return GET_X1APIC_PROCESSOR_PRIORITY_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicRemoteReadRegisterEx(PVOID ApicBase){
    return GET_X1APIC_REMOTE_READ_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLogicalDestinationRegisterEx(PVOID ApicBase){
    return GET_X1APIC_LOGICAL_DESTINATION_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicDestinationFormatRegisterEx(PVOID ApicBase){
    return GET_X1APIC_DESTINATION_FORMAT_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicSpuriousInterruptVectorRegisterEx(PVOID ApicBase){
    return GET_X1APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicInServiceRegisterX32Ex(PVOID ApicBase, SIZE Offset){
    return GET_X1APIC_IN_SERVICE_REGISTER_X32(ApicBase, Offset);
}

UINT32 ApicHalGetX1ApicTriggerModeRegisterX32Ex(PVOID ApicBase, SIZE Offset){
    return GET_X1APIC_TRIGGER_MODE_REGISTER_X32(ApicBase, Offset);
}

UINT32 ApicHalGetX1ApicInterruptRequestRegisterX32Ex(PVOID ApicBase, SIZE Offset){
    return GET_X1APIC_INTERRUPT_REQUEST_REGISTER_X32(ApicBase, Offset);
}

UINT32 ApicHalGetX1ApicErrorStatusRegisterEx(PVOID ApicBase){
    return GET_X1APIC_ERROR_STATUS_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtCmciRegisterEx(PVOID ApicBase){
    return GET_X1APIC_LVT_CMCI_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicInterruptControlRegisterLowEx(PVOID ApicBase){
    return GET_X1APIC_INTERRUPT_CONTROL_REGISTER_LOW(ApicBase);
}

UINT32 ApicHalGetX1ApicInterruptControlRegisterHighEx(PVOID ApicBase){
    return GET_X1APIC_INTERRUPT_CONTROL_REGISTER_HIGH(ApicBase);
}

UINT64 ApicHalGetX1ApicInterruptControlRegisterEx(PVOID ApicBase){
    UINT64 Register = ApicHalGetX1ApicInterruptControlRegisterLowEx(ApicBase);
    Register |= (UINT64)ApicHalGetX1ApicInterruptControlRegisterHighEx(ApicBase) << 32;
    return Register;
}

UINT32 ApicHalGetX1ApicLvtTimerRegisterEx(PVOID ApicBase){
    return GET_X1APIC_LVT_TIMER_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtThermalSensorRegisterEx(PVOID ApicBase){
    return GET_X1APIC_LVT_THERMAL_SENSOR_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegisterEx(PVOID ApicBase){
    return GET_X1APIC_LVT_PERFORMANCE_MONITORING_COUNTERS_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtLint0RegisterEx(PVOID ApicBase){
    return GET_X1APIC_LVT_LINT0_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtLint1RegisterEx(PVOID ApicBase){
    return GET_X1APIC_LVT_LINT1_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtErrorRegisterEx(PVOID ApicBase){
    return GET_X1APIC_LVT_ERROR_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicInitialCountRegisterEx(PVOID ApicBase){
    return GET_X1APIC_INITIAL_COUNT_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicCurrentCountRegisterEx(PVOID ApicBase){
    return GET_X1APIC_CURRENT_COUNT_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicDivideConfigurationRegisterEx(PVOID ApicBase){
    return GET_X1APIC_DIVIDE_CONFIGURATION_REGISTER(ApicBase);
}

void ApicHalSetX1ApicIdRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_ID_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicTaskPriorityRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_TASK_PRIORITY_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicEndOfInterruptRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_END_OF_INTERRUPT_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLogicalDestinationRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LOGICAL_DESTINATION_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicDestinationFormatRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_DESTINATION_FORMAT_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicSpuriousInterruptVectorRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtCmciRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_CMCI_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicInterruptControlRegisterLowEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_INTERRUPT_CONTROL_REGISTER_LOW(ApicBase, Value);
}

void ApicHalSetX1ApicInterruptControlRegisterHighEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_INTERRUPT_CONTROL_REGISTER_HIGH(ApicBase, Value);
}

void ApicHalSetX1ApicInterruptControlRegisterEx(PVOID ApicBase, UINT64 Value){
    ApicHalSetX1ApicInterruptControlRegisterLowEx(ApicBase, Value & UINT32_MAX);
    ApicHalSetX1ApicInterruptControlRegisterHighEx(ApicBase, (Value >> 32) & UINT32_MAX);
}

void ApicHalSetX1ApicLvtTimerRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_TIMER_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtThermalSensorRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_THERMAL_SENSOR_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtPerformanceMonitoringCountersRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_PERFORMANCE_MONITORING_COUNTERS_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtLint0RegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_LINT0_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtLint1RegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_LINT1_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtErrorRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_ERROR_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicInitialCountRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_INITIAL_COUNT_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicDivisionConfigurationRegisterEx(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_DIVIDE_CONFIGURATION_REGISTER(ApicBase, Value);
}

UINT32 ApicHalGetX1ApicIdRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicIdRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicVersionRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicVersionRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicTaskPriorityRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicTaskPriorityRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicArbitrationPriorityRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicArbitrationPriorityRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicProcessorPriorityRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicProcessorPriorityRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicRemoteReadRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicRemoteReadRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicLogicalDestinationRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLogicalDestinationRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicDestinationFormatRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicDestinationFormatRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicSpuriousInterruptVectorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicSpuriousInterruptVectorRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicInServiceRegisterX32(PAPIC_DEVICE_OBJECT ApicDeviceObject, SIZE Offset){
    return ApicHalGetX1ApicInServiceRegisterX32Ex(ApicDeviceObject->ApicBase, Offset);
}

UINT32 ApicHalGetX1ApicTriggerModeRegisterX32(PAPIC_DEVICE_OBJECT ApicDeviceObject, SIZE Offset){
    return ApicHalGetX1ApicTriggerModeRegisterX32Ex(ApicDeviceObject->ApicBase, Offset);
}

UINT32 ApicHalGetX1ApicInterruptRequestRegisterX32(PAPIC_DEVICE_OBJECT ApicDeviceObject, SIZE Offset){
    return ApicHalGetX1ApicInterruptRequestRegisterX32Ex(ApicDeviceObject->ApicBase, Offset);
}

UINT32 ApicHalGetX1ApicErrorStatusRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicErrorStatusRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicLvtCmciRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtCmciRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicInterruptControlRegisterLow(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicInterruptControlRegisterLowEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicInterruptControlRegisterHigh(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicInterruptControlRegisterHighEx(ApicDeviceObject->ApicBase);
}

UINT64 ApicHalGetX1ApicInterruptControlRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicInterruptControlRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicLvtTimerRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtTimerRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicLvtThermalSensorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtThermalSensorRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicLvtLint0Register(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtLint0RegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicLvtLint1Register(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtLint1RegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicLvtErrorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtErrorRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicInitialCountRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicInitialCountRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicCurrentCountRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicCurrentCountRegisterEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicDivideConfigurationRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicDivideConfigurationRegisterEx(ApicDeviceObject->ApicBase);
}

void ApicHalSetX1ApicIdRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicIdRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicTaskPriorityRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicTaskPriorityRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicEndOfInterruptRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicEndOfInterruptRegister(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicLogicalDestinationRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicLogicalDestinationRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicDestinationFormatRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicDestinationFormatRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicSpuriousInterruptVectorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicSpuriousInterruptVectorRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicLvtCmciRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicLvtCmciRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicInterruptControlRegisterLow(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicInterruptControlRegisterLowEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicInterruptControlRegisterHigh(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicInterruptControlRegisterHighEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicInterruptControlRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT64 Value){
    ApicHalSetX1ApicInterruptControlRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicLvtTimerRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicLvtTimerRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicLvtThermalSensorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicLvtThermalSensorRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicLvtPerformanceMonitoringCountersRegisterister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicLvtPerformanceMonitoringCountersRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicLvtLint0Register(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicLvtLint0RegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicLvtLint1Register(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicLvtLint1RegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicLvtErrorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicLvtErrorRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicInitialCountRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicInitialCountRegisterEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicDivisionConfigurationRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicDivisionConfigurationRegister(ApicDeviceObject->ApicBase, Value);
}
