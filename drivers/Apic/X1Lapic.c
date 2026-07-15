#include "X1ApicInternals.h"

UINT32 ApicHalGetX1ApicIdRegister(PVOID ApicBase){
    return GET_X1APIC_ID_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicVersionRegister(PVOID ApicBase){
    return GET_X1APIC_VERSION_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicTaskPriorityRegister(PVOID ApicBase){
    return GET_X1APIC_TASK_PRIORITY_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicArbitrationPriorityRegister(PVOID ApicBase){
    return GET_X1APIC_ARBITRATION_PRIOIRTY_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicProcessorPriorityRegister(PVOID ApicBase){
    return GET_X1APIC_PROCESSOR_PRIORITY_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicRemoteReadRegister(PVOID ApicBase){
    return GET_X1APIC_REMOTE_READ_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLogicalDestinationRegister(PVOID ApicBase){
    return GET_X1APIC_LOGICAL_DESTINATION_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicDestinationFormatRegister(PVOID ApicBase){
    return GET_X1APIC_DESTINATION_FORMAT_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicSpuriousInterruptVectorRegister(PVOID ApicBase){
    return GET_X1APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicInServiceRegisterX32(PVOID ApicBase, SIZE Offset){
    return GET_X1APIC_IN_SERVICE_REGISTER_X32(ApicBase, Offset);
}

UINT32 ApicHalGetX1ApicTriggerModeRegisterX32(PVOID ApicBase, SIZE Offset){
    return GET_X1APIC_TRIGGER_MODE_REGISTER_X32(ApicBase, Offset);
}

UINT32 ApicHalGetX1ApicInterruptRequestRegisterX32(PVOID ApicBase, SIZE Offset){
    return GET_X1APIC_INTERRUPT_REQUEST_REGISTER_X32(ApicBase, Offset);
}

UINT32 ApicHalGetX1ApicErrorStatusRegister(PVOID ApicBase){
    return GET_X1APIC_ERROR_STATUS_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtCmciRegister(PVOID ApicBase){
    return GET_X1APIC_LVT_CMCI_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicInterruptCommandRegisterLow(PVOID ApicBase){
    return GET_X1APIC_INTERRUPT_COMMAND_REGISTER_LOW(ApicBase);
}

UINT32 ApicHalGetX1ApicInterruptCommandRegisterHigh(PVOID ApicBase){
    return GET_X1APIC_INTERRUPT_COMMAND_REGISTER_HIGH(ApicBase);
}

UINT64 ApicHalGetX1ApicInterruptCommandRegister(PVOID ApicBase){
    UINT64 Register = ApicHalGetX1ApicInterruptCommandRegisterLow(ApicBase);
    Register |= (UINT64)ApicHalGetX1ApicInterruptCommandRegisterHigh(ApicBase) << 32;
    return Register;
}

UINT32 ApicHalGetX1ApicLvtTimerRegister(PVOID ApicBase){
    return GET_X1APIC_LVT_TIMER_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtThermalSensorRegister(PVOID ApicBase){
    return GET_X1APIC_LVT_THERMAL_SENSOR_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegister(PVOID ApicBase){
    return GET_X1APIC_LVT_PERFORMANCE_MONITORING_COUNTERS_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtLint0Register(PVOID ApicBase){
    return GET_X1APIC_LVT_LINT0_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtLint1Register(PVOID ApicBase){
    return GET_X1APIC_LVT_LINT1_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtErrorRegister(PVOID ApicBase){
    return GET_X1APIC_LVT_ERROR_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicInitialCountRegister(PVOID ApicBase){
    return GET_X1APIC_INITIAL_COUNT_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicCurrentCountRegister(PVOID ApicBase){
    return GET_X1APIC_CURRENT_COUNT_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicDivideConfigurationRegister(PVOID ApicBase){
    return GET_X1APIC_DIVIDE_CONFIGURATION_REGISTER(ApicBase);
}

void ApicHalSetX1ApicIdRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_ID_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicTaskPriorityRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_TASK_PRIORITY_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicEndOfInterruptRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_END_OF_INTERRUPT_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLogicalDestinationRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LOGICAL_DESTINATION_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicDestinationFormatRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_DESTINATION_FORMAT_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicSpuriousInterruptVectorRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtCmciRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_CMCI_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicInterruptCommandRegisterLow(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_INTERRUPT_COMMAND_REGISTER_LOW(ApicBase, Value);
}

void ApicHalSetX1ApicInterruptCommandRegisterHigh(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_INTERRUPT_COMMAND_REGISTER_HIGH(ApicBase, Value);
}

void ApicHalSetX1ApicInterruptCommandRegister(PVOID ApicBase, UINT64 Value){
    ApicHalSetX1ApicInterruptCommandRegisterHigh(ApicBase, (Value >> 32) & UINT32_MAX);
    ApicHalSetX1ApicInterruptCommandRegisterLow(ApicBase, Value & UINT32_MAX);
}

void ApicHalSetX1ApicLvtTimerRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_TIMER_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtThermalSensorRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_THERMAL_SENSOR_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtPerformanceMonitoringCountersRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_PERFORMANCE_MONITORING_COUNTERS_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtLint0Register(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_LINT0_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtLint1Register(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_LINT1_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicLvtErrorRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_LVT_ERROR_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicInitialCountRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_INITIAL_COUNT_REGISTER(ApicBase, Value);
}

void ApicHalSetX1ApicDivideConfigurationRegister(PVOID ApicBase, UINT32 Value){
    SET_X1APIC_DIVIDE_CONFIGURATION_REGISTER(ApicBase, Value);
}