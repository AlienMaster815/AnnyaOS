#ifndef _X2APIC_INTERNALS_H
#define _X2APIC_INTERNALS_H

#include "X1ApicInternals.h"

#define X2APIC_ID_REGISTER_OFFSET                                           0x0802
#define X2APIC_VERSION_REGISTER_OFFSET                                      0x0803
#define X2APIC_TASK_PRIORITY_REGISTER_OFFSET                                0x0808
#define X2APIC_PROCESSOR_PRIORITY_REGISTER_OFFSET                           0x080A
#define X2APIC_END_OF_INTERRUPT_REGISTER_OFFSET                             0x080B
#define X2APIC_LOGICAL_DESTINATION_REGISTER_OFFSET                          0x080D
#define X2APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER_OFFSET                    0x080F
#define X2APIC_IN_SERVICE_REGISTER_BITS_0_31_OFFSET                         0x0810
#define X2APIC_IN_SERVICE_REGISTER_BITS_32_63_OFFSET                        0x0811
#define X2APIC_IN_SERVICE_REGISTER_BITS_64_95_OFFSET                        0x0812
#define X2APIC_IN_SERVICE_REGISTER_BITS_96_127_OFFSET                       0x0813
#define X2APIC_IN_SERVICE_REGISTER_BITS_128_159_OFFSET                      0x0814
#define X2APIC_IN_SERVICE_REGISTER_BITS_160_191_OFFSET                      0x0815
#define X2APIC_IN_SERVICE_REGISTER_BITS_192_223_OFFSET                      0x0816
#define X2APIC_IN_SERVICE_REGISTER_BITS_224_255_OFFSET                      0x0817
#define X2APIC_TRIGGER_MODE_REGISTER_BITS_0_31_OFFSET                       0x0818
#define X2APIC_TRIGGER_MODE_REGISTER_BITS_32_63_OFFSET                      0x0819
#define X2APIC_TRIGGER_MODE_REGISTER_BITS_64_95_OFFSET                      0x081A
#define X2APIC_TRIGGER_MODE_REGISTER_BITS_96_127_OFFSET                     0x081B
#define X2APIC_TRIGGER_MODE_REGISTER_BITS_128_159_OFFSET                    0x081C
#define X2APIC_TRIGGER_MODE_REGISTER_BITS_160_191_OFFSET                    0x081D
#define X2APIC_TRIGGER_MODE_REGISTER_BITS_192_223_OFFSET                    0x081E
#define X2APIC_TRIGGER_MODE_REGISTER_BITS_224_255_OFFSET                    0x081F
#define X2APIC_INTERRUPT_REQUEST_REGISTER_BITS_0_31_OFFSET                  0x0820
#define X2APIC_INTERRUPT_REQUEST_REGISTER_BITS_32_63_OFFSET                 0x0821
#define X2APIC_INTERRUPT_REQUEST_REGISTER_BITS_64_95_OFFSET                 0x0822
#define X2APIC_INTERRUPT_REQUEST_REGISTER_BITS_96_127_OFFSET                0x0823
#define X2APIC_INTERRUPT_REQUEST_REGISTER_BITS_128_159_OFFSET               0x0824
#define X2APIC_INTERRUPT_REQUEST_REGISTER_BITS_160_191_OFFSET               0x0825
#define X2APIC_INTERRUPT_REQUEST_REGISTER_BITS_192_223_OFFSET               0x0826
#define X2APIC_INTERRUPT_REQUEST_REGISTER_BITS_224_255_OFFSET               0x0827
#define X2APIC_ERROR_STATUS_REGISTER_OFFSET                                 0x0828
#define X2APIC_LVT_CMCI_REGISTER_OFFSET                                     0x082F
#define X2APIC_INTERRUPT_COMMAND_REGISTER_OFFSET                            0x0830
#define X2APIC_LVT_TIMER_REGISTER_OFFSET                                    0x0832
#define X2APIC_LVT_THERMAL_SENSOR_REGISTER_OFFSET                           0x0833
#define X2APIC_LVT_PERFORMANCE_MONITORING_REGISTER_OFFSET                   0x0834
#define X2APIC_LINT0_REGISTER_OFFSET                                        0x0835
#define X2APIC_LINT1_REGISTER_OFFSET                                        0x0836
#define X2APIC_LVT_ERROR_REGISTER_OFFSET                                    0x0837
#define X2APIC_INITIAL_COUNT_REGISTER_OFFSET                                0x0838 
#define X2APIC_CURRENT_COUNT_REGISTER_OFFSET                                0x0839
#define X2APIC_DIVIDE_CONFIGURATION_REGISTER_OFFSET                         0x083E
#define X2APIC_SELF_IPI_REGISTER_OFFSET                                     0x083F



UINT32 ApicHalGetX2ApicIdRegister();
UINT32 ApicHalGetX2ApicVersionRegister();
UINT32 ApicHalGetX2ApicTaskPriorityRegister();
UINT32 ApicHalGetX2ApicProcessorPriorityRegister();
UINT32 ApicHalGetX2ApicLogicalDestinationRegister();
UINT32 ApicHalGetX2ApicSpuriousInterruptVectorRegister();
UINT32 ApicHalGetX2ApicInServiceRegisterX32(UINT8 Offset);
UINT32 ApicHalGetX2ApicTriggerModeRegisterX32(UINT8 Offset);
UINT32 ApicHalGetX2ApicInterruptRequestRegisterX32(UINT8 Offset);
UINT32 ApicHalGetX2ApicErrorStatusRegister();
UINT32 ApicHalGetX2ApicLvtCmciRegister();
UINT64 ApicHalGetX2ApicInterruptCommandRegister();
UINT32 ApicHalGetX2ApicLvtTimerRegister();
UINT32 ApicHalGetX2ApicLvtThermalSensorRegister();
UINT32 ApicHalGetX2ApicLvtPerformanceMonitoringCountersRegister();
UINT32 ApicHalGetX2ApicLvtLint0Register();
UINT32 ApicHalGetX2ApicLvtLint1Register();
UINT32 ApicHalGetX2ApicLvtErrorRegister();
UINT32 ApicHalGetX2ApicInitialCountRegister();
UINT32 ApicHalGetX2ApicCurrentCountRegister();
UINT32 ApicHalGetX2ApicDivideConfigurationRegister();
void ApicHalSetX2ApicTaskPriorityRegister(UINT32 Value);
void ApicHalSetX2ApicEndOfInterruptRegister(UINT32 Value);
void ApicHalSetX2ApicSpuriousInterruptVectorRegister(UINT32 Value);
void ApicHalSetX2ApicErrorStatusRegister(UINT32 Value);
void ApicHalSetX2ApicLvtCmciRegister(UINT32 Value);
void ApicHalSetX2ApicInterruptCommandRegister(UINT64 Value);
void ApicHalSetX2ApicLvtTimerRegister(UINT32 Value);
void ApicHalSetX2ApicLvtThermalSensorRegister(UINT32 Value);
void ApicHalSetX2ApicLvtPerformanceMonitoringCountersRegister(UINT32 Value);
void ApicHalSetX2ApicLvtLint0Register(UINT32 Value);
void ApicHalSetX2ApicLvtLint1Register(UINT32 Value);
void ApicHalSetX2ApicLvtErrorRegister(UINT32 Value);
void ApicHalSetX2ApicInitialCountRegister(UINT32 Value);
void ApicHalSetX2ApicDivideConfigurationRegister(UINT32 Value);
void ApicHalSetX2ApicSelfIpiRegister(UINT32 Value);



UINT32 ApicHalGetX2ApicId();
UINT32 ApicHalGetX2ApicVersion();
UINT32 ApicHalGetX2ApicMaxLvtEntry();
BOOLEAN ApicHalX2ApicSupportsEoiSuppression();
APIC_TIMER_MODE ApicHalGetX2ApicLvtTimerMode();
BOOLEAN ApicHalIsX2ApicLvtTimerMasked();
BOOLEAN ApicHalIsX2ApicLvtTimerInterruptPending();
UINT8 ApicHalGetX2ApicLvtTimerVector();
BOOLEAN ApicHalIsX2ApicLvtCmciMasked();
BOOLEAN ApicHalIsX2ApicLvtCmciInterruptPending();
APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtCmciDeliveryMode();
UINT8 ApicHalGetX2ApicLvtCmciVector();
BOOLEAN ApicHalIsX2ApicLvtLint0Masked();
APIC_TRIGGER_MODE ApicHalGetX2ApicLvtLint0TriggerMode();
BOOLEAN ApicHalIsX2ApicLvtLint0IrrSet();
APIC_IN_PIN_POLARITY ApicHalGetX2ApicLvtLint0InPinPolarity();
BOOLEAN ApicHalIsX2ApicLvtLint0InterruptPending();
APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtLint0DeliveryMode();
UINT8 ApicHalGetX2ApicLvtLint0Vector();
BOOLEAN ApicHalIsX2ApicLvtLint1Masked();
APIC_TRIGGER_MODE ApicHalGetX2ApicLvtLint1TriggerMode();
BOOLEAN ApicHalIsX2ApicLvtLint1IrrSet();
APIC_IN_PIN_POLARITY ApicHalGetX2ApicLvtLint1InPinPolarity();
BOOLEAN ApicHalIsX2ApicLvtLint1InterruptPending();
APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtLint1DeliveryMode();
UINT8 ApicHalGetX2ApicLvtLint1Vector();
BOOLEAN ApicHalIsX2ApicLvtErrorMasked();
BOOLEAN ApicHalGetX2ApicLvtErrorInterruptPending();
APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtErrorDeliveryMode();
UINT8 ApicHalGetX2ApicLvtErrorVector();
BOOLEAN ApicHalIsX2ApicLvtPerformanceMonitoringCountersMasked();
BOOLEAN ApicHalIsX2ApicLvtPerformanceMonitoringCountersInterruptPending();
APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtPerformanceMonitoringCountersDeliveryMode();
UINT8 ApicHalGetX2ApicLvtPerformanceMonitoringCountersVector();
BOOLEAN ApicHalIsX2ApicLvtThermalSensorMasked();
BOOLEAN ApicHalIsX2ApicLvtThermalSensorInterruptPending();
APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtThermalSensorDeliveryMode();
UINT8 ApicHalGetX2ApicLvtThermalSensorVector();
UINT32 ApicHalGetX2ApicLogicalDestinationRegisterLogicalApicId();
UINT32 ApicHalGetX2ApicTaskPriorityRegisterClass();
UINT32 ApicHalGetX2ApicTaskPriorityRegisterSubClass();
UINT32 ApicHalGetX2ApicProcessorPriorityRegisterClass();
UINT32 ApicHalGetX2ApicProcessorPriorityRegisterSubClass();
BOOLEAN ApicHalIsX2ApicEoiBroadcastSuppressed();
BOOLEAN ApicHalIsX2ApicFocusProcessorCheckingEnabled();
BOOLEAN ApicHalIsX2ApicSoftwareEnabled();
UINT8 ApicHalGetX2ApicSpuriousInterruptVector();
void ApicHalSetX2ApicLvtTimerMode(APIC_TIMER_MODE TimerMode);
void ApicHalSetX2ApicLvtTimerMask(BOOLEAN Masked);
void ApicHalSetX2ApicLvtTimerVector(UINT8 Vector);
void ApicHalMaskX2ApicLvtCmci(BOOLEAN Masked);
void ApicHalSetX2ApicLvtCmciDeliveryMode(APIC_LVT_DELIVERY_MODE DeliveryMode);
void ApicHalSetX2ApicLvtCmciVector(UINT8 Vector);
void ApicHalMaskX2ApicLvtLint0(BOOLEAN Masked);
void ApicHalSetX2ApicLvtLint0TriggerMode(APIC_TRIGGER_MODE TriggerMode);
void ApicHalSetX2ApicLvtLint0InPinPolarity(PVOID ApicBase, APIC_IN_PIN_POLARITY Polarity);
void ApicHalSetX2ApicLvtLint0Vector(UINT8 Vector);
void ApicHalMaskX2ApicLvtLint1(BOOLEAN Masked);
void ApicHalSetX2ApicLvtLint1TriggerMode(APIC_TRIGGER_MODE TriggerMode);
void ApicHalSetX2ApicLvtLint1InPinPolarity(PVOID ApicBase, APIC_IN_PIN_POLARITY Polarity);
void ApicHalSetX2ApicLvtLint1Vector(UINT8 Vector);
void ApicHalMaskX2ApicLvtError(BOOLEAN Masked);
void ApicHalSetX2ApicLvtErrorDeliveryMode(APIC_LVT_DELIVERY_MODE DeliveryMode);
void ApicHalSetX2ApicLvtErrorVector(UINT8 Vector);
void ApicHalSetX2ApicLvtPerformanceMonitoringCountersMask(BOOLEAN Masked);
void ApicHalSetX2ApicLvtPerformanceMonitoringCountersDeliveryMode(APIC_LVT_DELIVERY_MODE DeliveryMode);
void ApicHalSetX2ApicLvtPerformanceMonitoringCountersVector(UINT8 Vector);
void ApicHalMaskX2ApicLvtThermalSensor(PVOID ApicBase, BOOLEAN Masked);
void ApicHalSetX2ApicLvtThermalSensorDeliveryMode(APIC_LVT_DELIVERY_MODE DeliveryMode);
void ApicHalSetX2ApicLvtThermalSensorVector(UINT8 Vector);
void ApicHalSetX2ApicSendInterruptCommand(UINT32 DestinationField, APIC_DESTINATION_SHORTHAND Shorthand, APIC_TRIGGER_MODE TriggerMode, APIC_LEVEL Level, APIC_DESTINATION_MODE DestinationMode, APIC_ICR_DELIVERY_MODE DeliveryMode, UINT8 Vector);
void ApicHalSetX2ApicTaskPriorityRegisterClass(UINT32 Value);
void ApicHalSetX2ApicTaskPriorityRegisterSubClass(UINT32 Value);
void ApicHalEnableX2ApicEoiBroadcastSuppression(BOOLEAN Enabled);
void ApicHalEnableX2ApicFocusProcessorChecking(BOOLEAN Enabled);
void ApicHalEnableX2ApicSoftware(BOOLEAN Enabled);
void ApicHalSetX2ApicSpuriousInterruptVector(UINT8 Vector);

#endif