#include "X2ApicInternals.h"

UINT32 ApicHalGetX2ApicIdRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_ID_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicVersionRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_VERSION_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicTaskPriorityRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_TASK_PRIORITY_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicProcessorPriorityRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_PROCESSOR_PRIORITY_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicLogicalDestinationRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_LOGICAL_DESTINATION_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicSpuriousInterruptVectorRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicInServiceRegisterX32(UINT8 Offset){
    return (UINT32)(LouKeReadMsr(X2APIC_IN_SERVICE_REGISTER_BITS_0_31_OFFSET + Offset) & UINT32_MAX);   
}

UINT32 ApicHalGetX2ApicTriggerModeRegisterX32(UINT8 Offset){
    return (UINT32)(LouKeReadMsr(X2APIC_TRIGGER_MODE_REGISTER_BITS_0_31_OFFSET + Offset) & UINT32_MAX);   
}

UINT32 ApicHalGetX2ApicInterruptRequestRegisterX32(UINT8 Offset){
    return (UINT32)(LouKeReadMsr(X2APIC_INTERRUPT_REQUEST_REGISTER_BITS_0_31_OFFSET + Offset) & UINT32_MAX);   
}

UINT32 ApicHalGetX2ApicErrorStatusRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_ERROR_STATUS_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicLvtCmciRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_LVT_CMCI_REGISTER_OFFSET) & UINT32_MAX);
}

UINT64 ApicHalGetX2ApicInterruptCommandRegister(){
    return LouKeReadMsr(X2APIC_INTERRUPT_COMMAND_REGISTER_OFFSET);
}

UINT32 ApicHalGetX2ApicLvtTimerRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_LVT_TIMER_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicLvtThermalSensorRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_LVT_THERMAL_SENSOR_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicLvtPerformanceMonitoringRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_LVT_PERFORMANCE_MONITORING_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicLvtLint0Register(){
    return (UINT32)(LouKeReadMsr(X2APIC_LINT0_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicLvtLint1Register(){
    return (UINT32)(LouKeReadMsr(X2APIC_LINT1_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicLvtErrorRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_LVT_ERROR_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicInitialCountRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_INITIAL_COUNT_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicCurrentCountRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_CURRENT_COUNT_REGISTER_OFFSET) & UINT32_MAX);
}

UINT32 ApicHalGetX2ApicDivideConfigurationRegister(){
    return (UINT32)(LouKeReadMsr(X2APIC_DIVIDE_CONFIGURATION_REGISTER_OFFSET) & UINT32_MAX);
}


void ApicHalSetX2ApicTaskPriorityRegister(UINT32 Value){
    LouKeWriteMsr(X2APIC_TASK_PRIORITY_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicEndOfInterruptRegister(UINT32 Value){
    LouKeWriteMsr(X2APIC_END_OF_INTERRUPT_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicSpuriousInterruptVector(UINT32 Value){
    LouKeWriteMsr(X2APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicErrorStatusRegister(UINT32 Value){
    LouKeWriteMsr(X2APIC_ERROR_STATUS_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicLvtCmciRegister(UINT32 Value){
    LouKeWriteMsr(X2APIC_LVT_CMCI_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicInterruptCommandRegister(UINT64 Value){
    LouKeWriteMsr(X2APIC_INTERRUPT_COMMAND_REGISTER_OFFSET, Value);
}

void ApicHalSetX2ApicLvtTimerRegister(UINT32 Value){
    LouKeWriteMsr(X2APIC_LVT_TIMER_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicThermalSensorRegister(UINT32 Value){
    LouKeWriteMsr(X2APIC_LVT_THERMAL_SENSOR_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicLvtPerformanceMonitoringRegister(UINT32 Value){
    LouKeWriteMsr(X2APIC_LVT_PERFORMANCE_MONITORING_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicLvtLint0Register(UINT32 Value){
    LouKeWriteMsr(X2APIC_LINT0_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicLvtLint1Register(UINT32 Value){
    LouKeWriteMsr(X2APIC_LINT1_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicLvtErrorRegister(UINT32 Value){
    LouKeWriteMsr(X2APIC_LVT_ERROR_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicInitialCountRegister(UINT32 Value){
    LouKeWriteMsr(X2APIC_INITIAL_COUNT_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicDivideConfigurationRegister(UINT32 Value){
    LouKeWriteMsr(X2APIC_DIVIDE_CONFIGURATION_REGISTER_OFFSET, (UINT64)Value);
}

void ApicHalSetX2ApicSelfIpiRegister(UINT32 Value){
    LouKeWriteMsr(X2APIC_SELF_IPI_REGISTER_OFFSET, (UINT64)Value);
}