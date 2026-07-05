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

UINT32 ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegistrEx(PVOID ApicBase){
    return GET_X1APIC_LVT_PERFORMANCE_MONITORING_COUNTERS_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtInt0RegisterEx(PVOID ApicBase){
    return GET_X1APIC_LVT_LINT0_REGISTER(ApicBase);
}

UINT32 ApicHalGetX1ApicLvtInt1RegisterEx(PVOID ApicBase){
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

void ApicHalSetX1ApicLvtPerformanceMonitoringCounterRegisterEx(PVOID ApicBase, UINT32 Value){
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
