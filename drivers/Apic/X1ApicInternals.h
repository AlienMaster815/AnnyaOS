#ifndef _X1APIC_INTERNALS_H
#define _X1APIC_INTERNALS_H

#include "ApicInternals.h"

#define X1APIC_ID_REGISTER_OFFSET                                               0x20
#define X1APIC_VERSION_REGISTER_OFFSET                                          0x30
#define X1APIC_TASK_PRIORITY_REGISTER_OFFSET                                    0x80
#define X1APIC_ARBITRATION_PRIOIRITY_REGISTER_OFFSET                            0x90
#define X1APIC_PROCESSOR_PRIORITY_REGISTER_OFFSET                               0xA0
#define X1APIC_END_OF_INTERRUPT_REGISTER_OFFSET                                 0xB0
#define X1APIC_REMOTE_READ_REGISTER_OFFSET                                      0xC0
#define X1APIC_LOGICAL_DESTINATION_REGISTER_OFFSET                              0xD0
#define X1APIC_DESTINATION_FORMAT_REGISTER_OFFSET                               0xE0
#define X1APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER_OFFSET                        0xF0
#define X1APIC_IN_SERVICE_REGISTER_BITS_0_31_OFFSET                             0x100
#define X1APIC_IN_SERVICE_REGISTER_BITS_32_63_OFFSET                            0x110
#define X1APIC_IN_SERVICE_REGISTER_BITS_64_95_OFFSET                            0x120
#define X1APIC_IN_SERVICE_REGISTER_BITS_96_127_OFFSET                           0x130
#define X1APIC_IN_SERVICE_REGISTER_BITS_128_159_OFFSET                          0x140
#define X1APIC_IN_SERVICE_REGISTER_BITS_160_191_OFFSET                          0x150
#define X1APIC_IN_SERVICE_REGISTER_BITS_192_223_OFFSET                          0x160
#define X1APIC_IN_SERVICE_REGISTER_BITS_224_255_OFFSET                          0x170
#define X1APIC_TRIGGER_MODE_REGISTER_BITS_0_31_OFFSET                           0x180
#define X1APIC_TRIGGER_MODE_REGISTER_BITS_32_63_OFFSET                          0x190
#define X1APIC_TRIGGER_MODE_REGISTER_BITS_64_95_OFFSET                          0x1A0
#define X1APIC_TRIGGER_MODE_REGISTER_BITS_96_127_OFFSET                         0x1B0
#define X1APIC_TRIGGER_MODE_REGISTER_BITS_128_159_OFFSET                        0x1C0
#define X1APIC_TRIGGER_MODE_REGISTER_BITS_160_191_OFFSET                        0x1D0
#define X1APIC_TRIGGER_MODE_REGISTER_BITS_192_223_OFFSET                        0x1E0
#define X1APIC_TRIGGER_MODE_REGISTER_BITS_224_255_OFFSET                        0x1F0
#define X1APIC_INTERRUPT_REQUEST_REGISTER_BITS_0_31_OFFSET                      0x200
#define X1APIC_INTERRUPT_REQUEST_REGISTER_BITS_32_63_OFFSET                     0x210
#define X1APIC_INTERRUPT_REQUEST_REGISTER_BITS_64_95_OFFSET                     0x220
#define X1APIC_INTERRUPT_REQUEST_REGISTER_BITS_96_127_OFFSET                    0x230
#define X1APIC_INTERRUPT_REQUEST_REGISTER_BITS_128_159_OFFSET                   0x240
#define X1APIC_INTERRUPT_REQUEST_REGISTER_BITS_160_191_OFFSET                   0x250
#define X1APIC_INTERRUPT_REQUEST_REGISTER_BITS_192_223_OFFSET                   0x260
#define X1APIC_INTERRUPT_REQUEST_REGISTER_BITS_224_255_OFFSET                   0x270
#define X1APIC_ERROR_STATUS_REGISTER_OFFSET                                     0x280
#define X1APIC_LVT_CMCI_REGISTER_OFFSET                                         0x2F0
#define X1APIC_INTERRUPT_COMMAND_REGISTER_LOW_OFFSET                            0x300
#define X1APIC_INTERRUPT_COMMAND_REGISTER_HIGH_OFFSET                           0x310
#define X1APIC_LVT_TIMER_REGISTER_OFFSET                                        0x320
#define X1APIC_LVT_THERMAL_SENSOR_REGISTER_OFFSET                               0x330
#define X1APIC_LVT_PERFORMANCE_MONITORING_COUNTERS_REGISTER_OFFSET              0x340
#define X1APIC_LVT_LINT0_REGISTER_OFFSET                                        0x350
#define X1APIC_LVT_LINT1_REGISTER_OFFSET                                        0x360
#define X1APIC_ERROR_REGISTER_OFFSET                                            0x370
#define X1APIC_INITIAL_COUNT_REGISTER_OFFSET                                    0x380
#define X1APIC_CURRENT_COUNT_REGISTER_OFFSET                                    0x390
#define X1APIC_DIVIDE_CONFIGURATION_REGISTER                                    0x3E0

#define GET_X1APIC_ID_REGISTER(ApicBase)                                        ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_ID_REGISTER_OFFSET)))
#define GET_X1APIC_VERSION_REGISTER(ApicBase)                                   ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_VERSION_REGISTER_OFFSET)))
#define GET_X1APIC_TASK_PRIORITY_REGISTER(ApicBase)                             ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_TASK_PRIORITY_REGISTER_OFFSET)))
#define GET_X1APIC_ARBITRATION_PRIOIRTY_REGISTER(ApicBase)                      ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_ARBITRATION_PRIOIRITY_REGISTER_OFFSET)))
#define GET_X1APIC_PROCESSOR_PRIORITY_REGISTER(ApicBase)                        ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_PROCESSOR_PRIORITY_REGISTER_OFFSET)))
#define GET_X1APIC_REMOTE_READ_REGISTER(ApicBase)                               ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_REMOTE_READ_REGISTER_OFFSET)))
#define GET_X1APIC_LOGICAL_DESTINATION_REGISTER(ApicBase)                       ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LOGICAL_DESTINATION_REGISTER_OFFSET)))
#define GET_X1APIC_DESTINATION_FORMAT_REGISTER(ApicBase)                        ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_DESTINATION_FORMAT_REGISTER_OFFSET)))
#define GET_X1APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER(ApicBase)                 ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER_OFFSET)))
#define GET_X1APIC_IN_SERVICE_REGISTER_X32(ApicBase, x)                         ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_IN_SERVICE_REGISTER_BITS_0_31_OFFSET + (x * 0x10))))
#define GET_X1APIC_TRIGGER_MODE_REGISTER_X32(ApicBase, x)                       ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_TRIGGER_MODE_REGISTER_BITS_0_31_OFFSET + (x * 0x10))))
#define GET_X1APIC_INTERRUPT_REQUEST_REGISTER_X32(ApicBase, x)                  ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_INTERRUPT_REQUEST_REGISTER_BITS_0_31_OFFSET + (x * 0x10))))
#define GET_X1APIC_ERROR_STATUS_REGISTER(ApicBase)                              ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_ERROR_STATUS_REGISTER_OFFSET)))
#define GET_X1APIC_LVT_CMCI_REGISTER(ApicBase)                                  ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_CMCI_REGISTER_OFFSET)))
#define GET_X1APIC_INTERRUPT_COMMAND_REGISTER_LOW(ApicBase)                     ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_INTERRUPT_COMMAND_REGISTER_LOW_OFFSET)))
#define GET_X1APIC_INTERRUPT_COMMAND_REGISTER_HIGH(ApicBase)                    ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_INTERRUPT_COMMAND_REGISTER_HIGH_OFFSET)))
#define GET_X1APIC_LVT_TIMER_REGISTER(ApicBase)                                 ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_TIMER_REGISTER_OFFSET)))
#define GET_X1APIC_LVT_THERMAL_SENSOR_REGISTER(ApicBase)                        ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_THERMAL_SENSOR_REGISTER_OFFSET)))
#define GET_X1APIC_LVT_PERFORMANCE_MONITORING_COUNTERS_REGISTER(ApicBase)       ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_PERFORMANCE_MONITORING_COUNTERS_REGISTER_OFFSET)))
#define GET_X1APIC_LVT_LINT0_REGISTER(ApicBase)                                 ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_LINT0_REGISTER_OFFSET)))
#define GET_X1APIC_LVT_LINT1_REGISTER(ApicBase)                                 ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_LINT1_REGISTER_OFFSET)))
#define GET_X1APIC_LVT_ERROR_REGISTER(ApicBase)                                 ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_ERROR_REGISTER_OFFSET)))
#define GET_X1APIC_INITIAL_COUNT_REGISTER(ApicBase)                             ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_INITIAL_COUNT_REGISTER_OFFSET)))
#define GET_X1APIC_CURRENT_COUNT_REGISTER(ApicBase)                             ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_CURRENT_COUNT_REGISTER_OFFSET)))
#define GET_X1APIC_DIVIDE_CONFIGURATION_REGISTER(ApicBase)                      ((UINT32)READ_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_DIVIDE_CONFIGURATION_REGISTER)))



#define SET_X1APIC_ID_REGISTER(ApicBase, x)                                     WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_ID_REGISTER_OFFSET), x)
#define SET_X1APIC_TASK_PRIORITY_REGISTER(ApicBase, x)                          WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_TASK_PRIORITY_REGISTER_OFFSET), x)
#define SET_X1APIC_END_OF_INTERRUPT_REGISTER(ApicBase, x)                       WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_END_OF_INTERRUPT_REGISTER_OFFSET), x)
#define SET_X1APIC_LOGICAL_DESTINATION_REGISTER(ApicBase, x)                    WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LOGICAL_DESTINATION_REGISTER_OFFSET), x)
#define SET_X1APIC_DESTINATION_FORMAT_REGISTER(ApicBase, x)                     WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_DESTINATION_FORMAT_REGISTER_OFFSET), x)
#define SET_X1APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER(ApicBase, x)              WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER_OFFSET), x)
#define SET_X1APIC_ERROR_STATUS_REGISTER(ApicBase, x)                           WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_ERROR_STATUS_REGISTER_OFFSET), x)
#define SET_X1APIC_LVT_CMCI_REGISTER(ApicBase, x)                               WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_CMCI_REGISTER_OFFSET), x)
#define SET_X1APIC_INTERRUPT_COMMAND_REGISTER_LOW(ApicBase, x)                  WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_INTERRUPT_COMMAND_REGISTER_LOW_OFFSET), x)
#define SET_X1APIC_INTERRUPT_COMMAND_REGISTER_HIGH(ApicBase, x)                 WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_INTERRUPT_COMMAND_REGISTER_HIGH_OFFSET), x)
#define SET_X1APIC_LVT_TIMER_REGISTER(ApicBase, x)                              WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_TIMER_REGISTER_OFFSET), x)
#define SET_X1APIC_LVT_THERMAL_SENSOR_REGISTER(ApicBase, x)                     WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_THERMAL_SENSOR_REGISTER_OFFSET), x)
#define SET_X1APIC_LVT_PERFORMANCE_MONITORING_COUNTERS_REGISTER(ApicBase, x)    WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_PERFORMANCE_MONITORING_COUNTERS_REGISTER_OFFSET), x)
#define SET_X1APIC_LVT_LINT0_REGISTER(ApicBase, x)                              WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_LINT0_REGISTER_OFFSET), x)
#define SET_X1APIC_LVT_LINT1_REGISTER(ApicBase, x)                              WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_LVT_LINT1_REGISTER_OFFSET), x)
#define SET_X1APIC_LVT_ERROR_REGISTER(ApicBase, x)                              WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_ERROR_REGISTER_OFFSET), x)
#define SET_X1APIC_INITIAL_COUNT_REGISTER(ApicBase, x)                          WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_INITIAL_COUNT_REGISTER_OFFSET), x)
#define SET_X1APIC_DIVIDE_CONFIGURATION_REGISTER(ApicBase, x)                   WRITE_REGISTER_ULONG((PULONG)(PVOID)((UINTPTR)ApicBase + X1APIC_DIVIDE_CONFIGURATION_REGISTER), x)



#define X1APIC_ID_SHIFT                                                         24
#define X1APIC_ID_MASK                                                          0xFF
#define GET_X1APIC_ID_VALUE(IdRegister)                                         ((IdRegister >> X1APIC_ID_SHIFT) & X1APIC_ID_MASK)
#define SET_X1APIC_ID_VALUE(IdRegister, Value)                                  ((IdRegister & ~(X1APIC_ID_MASK << X1APIC_ID_SHIFT)) | ((Value & X1APIC_ID_MASK) << X1APIC_ID_SHIFT))


#define X1APIC_VERSION_SHIFT                                                    0
#define X1APIC_VERSION_MASK                                                     0xFF
#define GET_X1APIC_VERSION_VALUE(VersionRegister)                               ((VersionRegister >> X1APIC_VERSION_SHIFT) & X1APIC_VERSION_MASK)
#define X1APIC_MAX_LVT_ENTRY_SHIFT                                              16
#define X1APIC_MAX_LVT_ENTRY_MASK                                               0xFF
#define GET_X1APIC_MAX_LVT_ENTRY_VALUE(VersionRegister)                         ((VersionRegister >> X1APIC_MAX_LVT_ENTRY_SHIFT) & X1APIC_MAX_LVT_ENTRY_MASK)
#define X1APIC_SUPPORT_EOI_SUPRESS_SHIFT                                        24
#define X1APIC_SUPPORT_EOI_SUPRESS_MASK                                         0x01
#define GET_X1APIC_SUPPORT_EOI_SUPRESS_VALUE(VersionRegister)                   ((VersionRegister >> X1APIC_SUPPORT_EOI_SUPRESS_SHIFT) & X1APIC_SUPPORT_EOI_SUPRESS_MASK)

#define X1APIC_LVT_TIMER_MODE_MASK                                              0x03
#define X1APIC_LVT_TIMER_MODE_SHIFT                                             17
#define GET_X1APIC_LVT_TIMER_MODE(TimerRegister)                                ((TimerRegister >> X1APIC_LVT_TIMER_MODE_SHIFT) & X1APIC_LVT_TIMER_MODE_MASK)
#define SET_X1APIC_LVT_TIMER_MODE(TimerRegister, x)                             ((TimerRegister & ~(X1APIC_LVT_TIMER_MODE_MASK << X1APIC_LVT_TIMER_MODE_SHIFT)) | ((x & X1APIC_LVT_TIMER_MODE_MASK) << X1APIC_LVT_TIMER_MODE_SHIFT))                    
#define X1APIC_LVT_TIMER_MASK_MASK                                              1
#define X1APIC_LVT_TIMER_MASK_SHIFT                                             16
#define GET_X1APIC_LVT_TIMER_MASK(TimerRegister)                                ((TimerRegister >> X1APIC_LVT_TIMER_MASK_SHIFT) & X1APIC_LVT_TIMER_MASK_MASK)
#define SET_X1APIC_LVT_TIMER_MASK(TimerRegister, x)                             (TimerRegister = ((TimerRegister & ~(X1APIC_LVT_TIMER_MASK_MASK << X1APIC_LVT_TIMER_MASK_SHIFT)) | ((x & X1APIC_LVT_TIMER_MASK_MASK) << X1APIC_LVT_TIMER_MASK_SHIFT)))
#define X1APIC_LVT_TIMER_DELIVERY_STATUS_MASK                                   1
#define X1APIC_LVT_TIMER_DELIVERY_STATUS_SHIFT                                  12
#define GET_X1APIC_LVT_TIMER_DELIVERY_STATUS(TimerRegister)                     ((TimerRegister >> X1APIC_LVT_TIMER_DELIVERY_STATUS_SHIFT) & X1APIC_LVT_TIMER_DELIVERY_STATUS_MASK)
#define X1APIC_LVT_TIMER_VECTOR_MASK                                            0xFF
#define X1APIC_LVT_TIMER_VECTOR_SHIFT                                           0
#define GET_X1APIC_LVT_TIMER_VECTOR(TimerRegister)                              ((TimerRegister >> X1APIC_LVT_TIMER_VECTOR_SHIFT) & X1APIC_LVT_TIMER_VECTOR_MASK)
#define SET_X1APIC_LVT_TIMER_VECTOR(TimerRegister, x)                           ((TimerRegister & ~(X1APIC_LVT_TIMER_VECTOR_MASK << X1APIC_LVT_TIMER_VECTOR_SHIFT)) | ((x & X1APIC_LVT_TIMER_VECTOR_MASK) << X1APIC_LVT_TIMER_VECTOR_SHIFT))


#define X1APIC_LVT_CMCI_MASK_MASK                                               1
#define X1APIC_LVT_CMCI_MASK_SHIFT                                              16
#define GET_X1APIC_LVT_CMCI_MASK(CmciRegister)                                  ((CmciRegister >> X1APIC_LVT_CMCI_MASK_SHIFT) & X1APIC_LVT_CMCI_MASK_MASK)
#define SET_X1APIC_LVT_CMCI_MASK(CmciRegister, x)                               ((CmciRegister & ~(X1APIC_LVT_CMCI_MASK_MASK << X1APIC_LVT_CMCI_MASK_SHIFT)) | ((x & X1APIC_LVT_CMCI_MASK_MASK) << X1APIC_LVT_CMCI_MASK_SHIFT))
#define X1APIC_LVT_CMCI_DELIVERY_STATUS_MASK                                    1
#define X1APIC_LVT_CMCI_DELIVERY_STATUS_SHIFT                                   12
#define GET_X1APIC_LVT_CMCI_DELIVERY_STATUS(CmciRegister)                       ((CmciRegister >> X1APIC_LVT_CMCI_DELIVERY_STATUS_SHIFT) & X1APIC_LVT_CMCI_DELIVERY_STATUS_MASK)
#define X1APIC_LVT_CMCI_DELIVERY_MODE_MASK                                      0x07
#define X1APIC_LVT_CMCI_DELIVERY_MODE_SHIFT                                     8
#define GET_X1APIC_LVT_CMCI_DELIVERY_MODE(CmciRegister)                         ((CmciRegister >> X1APIC_LVT_CMCI_DELIVERY_MODE_SHIFT) & X1APIC_LVT_CMCI_DELIVERY_MODE_MASK)
#define SET_X1APIC_LVT_CMCI_DELIVERY_MODE(CmciRegister, x)                      ((CmciRegister & ~(X1APIC_LVT_CMCI_DELIVERY_MODE_MASK << X1APIC_LVT_CMCI_DELIVERY_MODE_SHIFT)) | ((x & X1APIC_LVT_CMCI_DELIVERY_MODE_MASK) << X1APIC_LVT_CMCI_DELIVERY_MODE_SHIFT))
#define X1APIC_LVT_CMCI_VECTOR_MASK                                             0xFF
#define X1APIC_LVT_CMCI_VECTOR_SHIFT                                            0
#define GET_X1APIC_LVT_CMCI_VECTOR(CmciRegister)                                ((CmciRegister >> X1APIC_LVT_CMCI_VECTOR_SHIFT) & X1APIC_LVT_CMCI_VECTOR_MASK)
#define SET_X1APIC_LVT_CMCI_VECTOR(CmciRegister, x)                             ((CmciRegister & ~(X1APIC_LVT_CMCI_VECTOR_MASK << X1APIC_LVT_CMCI_VECTOR_SHIFT)) | ((x & X1APIC_LVT_CMCI_VECTOR_MASK) << X1APIC_LVT_CMCI_VECTOR_SHIFT))

#define X1APIC_LINT0_MASK_MASK                                                  1
#define X1APIC_LINT0_MASK_SHIFT                                                 16
#define GET_X1APIC_LINT0_MASK(LintRegister)                                     ((LintRegister >> X1APIC_LINT0_MASK_SHIFT) & X1APIC_LINT0_MASK_MASK)
#define SET_X1APIC_LINT0_MASK(LintRegister, x)                                  ((LintRegister & ~(X1APIC_LINT0_MASK_MASK << X1APIC_LINT0_MASK_SHIFT)) | ((x & X1APIC_LINT0_MASK_MASK) << X1APIC_LINT0_MASK_SHIFT))
#define X1APIC_LINT0_TRIGGER_MODE_MASK                                          1
#define X1APIC_LINT0_TRIGGER_MODE_SHIFT                                         15
#define GET_X1APIC_LINT0_TRIGGER_MODE(LintRegister)                             ((LintRegister >> X1APIC_LINT0_TRIGGER_MODE_SHIFT) & X1APIC_LINT0_TRIGGER_MODE_MASK)
#define SET_X1APIC_LINT0_TRIGGER_MODE(LintRegister, x)                          ((LintRegister & ~(X1APIC_LINT0_TRIGGER_MODE_MASK << X1APIC_LINT0_TRIGGER_MODE_SHIFT)) | ((x & X1APIC_LINT0_TRIGGER_MODE_MASK) << X1APIC_LINT0_TRIGGER_MODE_SHIFT))
#define X1APIC_LINT0_REMOTE_IRR_MASK                                            1
#define X1APIC_LINT0_REMOTE_IRR_SHIFT                                           14
#define GET_X1APIC_LINT0_REMOTE_IRR(LintRegister)                               ((LintRegister >> X1APIC_LINT0_REMOTE_IRR_SHIFT) & X1APIC_LINT0_REMOTE_IRR_MASK)
#define X1APIC_LINT0_INT_PIN_POLARITY_MASK                                      1
#define X1APIC_LINT0_INT_PIN_POLARITY_SHIFT                                     13
#define GET_X1APIC_LINT0_INT_PIN_POLARITY(LintRegister)                         ((LintRegister >> X1APIC_LINT0_INT_PIN_POLARITY_SHIFT) & X1APIC_LINT0_INT_PIN_POLARITY_MASK)
#define SET_X1APIC_LINT0_INT_PIN_POLARITY(LintRegister, x)                      ((LintRegister & ~(X1APIC_LINT0_INT_PIN_POLARITY_MASK << X1APIC_LINT0_INT_PIN_POLARITY_SHIFT)) | ((x & X1APIC_LINT0_INT_PIN_POLARITY_MASK) << X1APIC_LINT0_INT_PIN_POLARITY_SHIFT))
#define X1APIC_LINT0_DELIVERY_STATUS_MASK                                       1
#define X1APIC_LINT0_DELIVERY_STATUS_SHIFT                                      12
#define GET_X1APIC_LINT0_DELIVERY_STATUS(LintRegister)                          ((LintRegister >> X1APIC_LINT0_DELIVERY_STATUS_SHIFT) & X1APIC_LINT0_DELIVERY_STATUS_MASK)
#define X1APIC_LINT0_DELIVERY_MODE_MASK                                         0x07
#define X1APIC_LINT0_DELIVERY_MODE_SHIFT                                        8
#define GET_X1APIC_LINT0_DELIVERY_MODE(LintRegister)                            ((LintRegister >> X1APIC_LINT0_DELIVERY_MODE_SHIFT) & X1APIC_LINT0_DELIVERY_MODE_MASK)
#define SET_X1APIC_LINT0_DELIVERY_MODE(LintRegister, x)                         ((LintRegister & ~(X1APIC_LINT0_DELIVERY_MODE_MASK << X1APIC_LINT0_DELIVERY_MODE_SHIFT)) | ((x & X1APIC_LINT0_DELIVERY_MODE_MASK) << X1APIC_LINT0_DELIVERY_MODE_SHIFT))
#define X1APIC_LINT0_VECTOR_MASK                                                0xFF
#define X1APIC_LINT0_VECTOR_SHIFT                                               0
#define GET_X1APIC_LINT0_VECTOR(LintRegister)                                   ((LintRegister >> X1APIC_LINT0_VECTOR_SHIFT) & X1APIC_LINT0_VECTOR_MASK)
#define SET_X1APIC_LINT0_VECTOR(LintRegister, x)                                ((LintRegister & ~(X1APIC_LINT0_VECTOR_MASK << X1APIC_LINT0_VECTOR_SHIFT)) | ((x & X1APIC_LINT0_VECTOR_MASK) << X1APIC_LINT0_VECTOR_SHIFT))

#define X1APIC_LINT1_MASK_MASK                                                  1
#define X1APIC_LINT1_MASK_SHIFT                                                 16
#define GET_X1APIC_LINT1_MASK(LintRegister)                                     ((LintRegister >> X1APIC_LINT1_MASK_SHIFT) & X1APIC_LINT1_MASK_MASK)
#define SET_X1APIC_LINT1_MASK(LintRegister, x)                                  ((LintRegister & ~(X1APIC_LINT1_MASK_MASK << X1APIC_LINT1_MASK_SHIFT)) | ((x & X1APIC_LINT1_MASK_MASK) << X1APIC_LINT1_MASK_SHIFT))
#define X1APIC_LINT1_TRIGGER_MODE_MASK                                          1
#define X1APIC_LINT1_TRIGGER_MODE_SHIFT                                         15
#define GET_X1APIC_LINT1_TRIGGER_MODE(LintRegister)                             ((LintRegister >> X1APIC_LINT1_TRIGGER_MODE_SHIFT) & X1APIC_LINT1_TRIGGER_MODE_MASK)
#define SET_X1APIC_LINT1_TRIGGER_MODE(LintRegister, x)                          ((LintRegister & ~(X1APIC_LINT1_TRIGGER_MODE_MASK << X1APIC_LINT1_TRIGGER_MODE_SHIFT)) | ((x & X1APIC_LINT1_TRIGGER_MODE_MASK) << X1APIC_LINT1_TRIGGER_MODE_SHIFT))
#define X1APIC_LINT1_REMOTE_IRR_MASK                                            1
#define X1APIC_LINT1_REMOTE_IRR_SHIFT                                           14
#define GET_X1APIC_LINT1_REMOTE_IRR(LintRegister)                               ((LintRegister >> X1APIC_LINT1_REMOTE_IRR_SHIFT) & X1APIC_LINT1_REMOTE_IRR_MASK)
#define X1APIC_LINT1_INT_PIN_POLARITY_MASK                                      1
#define X1APIC_LINT1_INT_PIN_POLARITY_SHIFT                                     13
#define GET_X1APIC_LINT1_INT_PIN_POLARITY(LintRegister)                         ((LintRegister >> X1APIC_LINT1_INT_PIN_POLARITY_SHIFT) & X1APIC_LINT1_INT_PIN_POLARITY_MASK)
#define SET_X1APIC_LINT1_INT_PIN_POLARITY(LintRegister, x)                      ((LintRegister & ~(X1APIC_LINT1_INT_PIN_POLARITY_MASK << X1APIC_LINT1_INT_PIN_POLARITY_SHIFT)) | ((x & X1APIC_LINT1_INT_PIN_POLARITY_MASK) << X1APIC_LINT1_INT_PIN_POLARITY_SHIFT))
#define X1APIC_LINT1_DELIVERY_STATUS_MASK                                       1
#define X1APIC_LINT1_DELIVERY_STATUS_SHIFT                                      12
#define GET_X1APIC_LINT1_DELIVERY_STATUS(LintRegister)                          ((LintRegister >> X1APIC_LINT1_DELIVERY_STATUS_SHIFT) & X1APIC_LINT1_DELIVERY_STATUS_MASK)
#define X1APIC_LINT1_DELIVERY_MODE_MASK                                         0x07
#define X1APIC_LINT1_DELIVERY_MODE_SHIFT                                        8
#define GET_X1APIC_LINT1_DELIVERY_MODE(LintRegister)                            ((LintRegister >> X1APIC_LINT1_DELIVERY_MODE_SHIFT) & X1APIC_LINT1_DELIVERY_MODE_MASK)
#define X1APIC_LINT1_VECTOR_MASK                                                0xFF
#define X1APIC_LINT1_VECTOR_SHIFT                                               0
#define GET_X1APIC_LINT1_VECTOR(LintRegister)                                   ((LintRegister >> X1APIC_LINT1_VECTOR_SHIFT) & X1APIC_LINT1_VECTOR_MASK)
#define SET_X1APIC_LINT1_VECTOR(LintRegister, x)                                ((LintRegister & ~(X1APIC_LINT1_VECTOR_MASK << X1APIC_LINT1_VECTOR_SHIFT)) | ((x & X1APIC_LINT1_VECTOR_MASK) << X1APIC_LINT1_VECTOR_SHIFT))

#define X1APIC_ERROR_MASK_MASK                                                  1
#define X1APIC_ERROR_MASK_SHIFT                                                 16
#define GET_X1APIC_ERROR_MASK(ErrorRegister)                                    ((ErrorRegister >> X1APIC_ERROR_MASK_SHIFT) & X1APIC_ERROR_MASK_MASK)
#define SET_X1APIC_ERROR_MASK(ErrorRegister, x)                                 ((ErrorRegister & ~(X1APIC_ERROR_MASK_MASK << X1APIC_ERROR_MASK_SHIFT)) | ((x & X1APIC_ERROR_MASK_MASK) << X1APIC_ERROR_MASK_SHIFT))
#define X1APIC_ERROR_DELIVERY_STATUS_MASK                                       1
#define X1APIC_ERROR_DELIVERY_STATUS_SHIFT                                      12
#define GET_X1APIC_ERROR_DELIVERY_STATUS(ErrorRegister)                         ((ErrorRegister >> X1APIC_ERROR_DELIVERY_STATUS_SHIFT) & X1APIC_ERROR_DELIVERY_STATUS_MASK)
#define X1APIC_ERROR_DELIVERY_MODE_MASK                                         0x07
#define X1APIC_ERROR_DELIVERY_MODE_SHIFT                                        8
#define GET_X1APIC_ERROR_DELIVERY_MODE(ErrorRegister)                           ((ErrorRegister >> X1APIC_ERROR_DELIVERY_MODE_SHIFT) & X1APIC_ERROR_DELIVERY_MODE_MASK)
#define SET_X1APIC_ERROR_DELIVERY_MODE(ErrorRegister, x)                        ((ErrorRegister & ~(X1APIC_ERROR_DELIVERY_MODE_MASK << X1APIC_ERROR_DELIVERY_MODE_SHIFT)) | ((x & X1APIC_ERROR_DELIVERY_MODE_MASK) << X1APIC_ERROR_DELIVERY_MODE_SHIFT))
#define X1APIC_ERROR_VECTOR_MASK                                                0xFF
#define X1APIC_ERROR_VECTOR_SHIFT                                               0
#define GET_X1APIC_ERROR_VECTOR(ErrorRegister)                                  ((ErrorRegister >> X1APIC_ERROR_VECTOR_SHIFT) & X1APIC_ERROR_VECTOR_MASK)
#define SET_X1APIC_ERROR_VECTOR(ErrorRegister, x)                               ((ErrorRegister & ~(X1APIC_ERROR_VECTOR_MASK << X1APIC_ERROR_VECTOR_SHIFT)) | ((x & X1APIC_ERROR_VECTOR_MASK) << X1APIC_ERROR_VECTOR_SHIFT))

#define X1APIC_PMC_MASK_MASK                                                    1
#define X1APIC_PMC_MASK_SHIFT                                                   16
#define GET_X1APIC_PMC_MASK(PmcRegister)                                        ((PmcRegister >> X1APIC_PMC_MASK_SHIFT) & X1APIC_PMC_MASK_MASK)
#define SET_X1APIC_PMC_MASK(PmcRegister, x)                                     ((PmcRegister & ~(X1APIC_PMC_MASK_MASK << X1APIC_PMC_MASK_SHIFT)) | ((x & X1APIC_PMC_MASK_MASK) << X1APIC_PMC_MASK_SHIFT))
#define X1APIC_PMC_DELIVERY_STATUS_MASK                                         1
#define X1APIC_PMC_DELIVERY_STATUS_SHIFT                                        12
#define GET_X1APIC_PMC_DELIVERY_STATUS(PmcRegister)                             ((PmcRegister >> X1APIC_PMC_DELIVERY_STATUS_SHIFT) & X1APIC_PMC_DELIVERY_STATUS_MASK)
#define X1APIC_PMC_DELIVERY_MODE_MASK                                           0x07
#define X1APIC_PMC_DELIVERY_MODE_SHIFT                                          8
#define GET_X1APIC_PMC_DELIVERY_MODE(PmcRegister)                               ((PmcRegister >> X1APIC_PMC_DELIVERY_MODE_SHIFT) & X1APIC_PMC_DELIVERY_MODE_MASK)
#define SET_X1APIC_PMC_DELIVERY_MODE(PmcRegister, x)                            ((PmcRegister & ~(X1APIC_PMC_DELIVERY_MODE_MASK << X1APIC_PMC_DELIVERY_MODE_SHIFT)) | ((x & X1APIC_PMC_DELIVERY_MODE_MASK) << X1APIC_PMC_DELIVERY_MODE_SHIFT))
#define X1APIC_PMC_VECTOR_MASK                                                  0xFF
#define X1APIC_PMC_VECTOR_SHIFT                                                 0
#define GET_X1APIC_PMC_VECTOR(PmcRegister)                                      ((PmcRegister >> X1APIC_PMC_VECTOR_SHIFT) & X1APIC_PMC_VECTOR_MASK)
#define SET_X1APIC_PMC_VECTOR(PmcRegister, x)                                   ((PmcRegister & ~(X1APIC_PMC_VECTOR_MASK << X1APIC_PMC_VECTOR_SHIFT)) | ((x & X1APIC_PMC_VECTOR_MASK) << X1APIC_PMC_VECTOR_SHIFT))

#define X1APIC_TS_MASK_MASK                                                     1
#define X1APIC_TS_MASK_SHIFT                                                    16
#define GET_X1APIC_TS_MASK(TsRegister)                                          ((TsRegister >> X1APIC_TS_MASK_SHIFT) & X1APIC_TS_MASK_MASK)
#define SET_X1APIC_TS_MASK(TsRegister, x)                                       ((TsRegister & ~(X1APIC_TS_MASK_MASK << X1APIC_TS_MASK_SHIFT)) | ((x & X1APIC_TS_MASK_MASK) << X1APIC_TS_MASK_SHIFT))
#define X1APIC_TS_DELIVERY_STATUS_MASK                                          1
#define X1APIC_TS_DELIVERY_STATUS_SHIFT                                         12
#define GET_X1APIC_TS_DELIVERY_STATUS(TsRegister)                               ((TsRegister >> X1APIC_TS_DELIVERY_STATUS_SHIFT) & X1APIC_TS_DELIVERY_STATUS_MASK)
#define X1APIC_TS_DELIVERY_MODE_MASK                                            0x07
#define X1APIC_TS_DELIVERY_MODE_SHIFT                                           8
#define GET_X1APIC_TS_DELIVERY_MODE(TsRegister)                                 ((TsRegister >> X1APIC_TS_DELIVERY_MODE_SHIFT) & X1APIC_TS_DELIVERY_MODE_MASK)
#define SET_X1APIC_TS_DELIVERY_MODE(TsRegister, x)                              ((TsRegister & ~(X1APIC_TS_DELIVERY_MODE_MASK << X1APIC_TS_DELIVERY_MODE_SHIFT)) | ((x & X1APIC_TS_DELIVERY_MODE_MASK) << X1APIC_TS_DELIVERY_MODE_SHIFT))
#define X1APIC_TS_VECTOR_MASK                                                   0xFF
#define X1APIC_TS_VECTOR_SHIFT                                                  0
#define GET_X1APIC_TS_VECTOR(TsRegister)                                        ((TsRegister >> X1APIC_TS_VECTOR_SHIFT) & X1APIC_TS_VECTOR_MASK)
#define SET_X1APIC_TS_VECTOR(TsRegister, x)                                     ((TsRegister & ~(X1APIC_TS_VECTOR_MASK << X1APIC_TS_VECTOR_SHIFT)) | ((x & X1APIC_TS_VECTOR_MASK) << X1APIC_TS_VECTOR_SHIFT))

#define X1APIC_LDR_LOGICAL_APIC_ID_MASK                                         0xFF
#define X1APIC_LDR_LOGICAL_APIC_ID_SHIFT                                        24
#define GET_X1APIC_LDR_LOGICAL_APIC_ID(LdrRegister)                             ((LdrRegister >> X1APIC_LDR_LOGICAL_APIC_ID_SHIFT) & X1APIC_LDR_LOGICAL_APIC_ID_MASK)
#define SET_X1APIC_LDR_LOGICAL_APIC_ID(LdrRegister, x)                          ((LdrRegister & ~(X1APIC_LDR_LOGICAL_APIC_ID_MASK << X1APIC_LDR_LOGICAL_APIC_ID_SHIFT)) | ((x & X1APIC_LDR_LOGICAL_APIC_ID_MASK) << X1APIC_LDR_LOGICAL_APIC_ID_SHIFT))

#define X1APIC_DFR_MODEL_MASK                                                   0x0F
#define X1APIC_DFR_MODEL_SHIFT                                                  28
#define GET_X1APIC_DFR_MODEL(DfrRegister)                                       ((DfrRegister >> X1APIC_DFR_MODEL_SHIFT) & X1APIC_DFR_MODEL_MASK)
#define SET_X1APIC_DFR_MODEL(DfrRegister, x)                                    ((DfrRegister & ~(X1APIC_DFR_MODEL_MASK << X1APIC_DFR_MODEL_SHIFT)) | ((x & X1APIC_DFR_MODEL_MASK) << X1APIC_DFR_MODEL_SHIFT))

#define X1APIC_APR_CLASS_MASK                                                   0x0F
#define X1APIC_APR_CLASS_SHIFT                                                  4
#define GET_X1APIC_APR_CLASS(AprRegister)                                       ((AprRegister >> X1APIC_APR_CLASS_SHIFT) & X1APIC_APR_CLASS_MASK)

#define X1APIC_APR_SUB_CLASS_MASK                                               0x0F
#define X1APIC_APR_SUB_CLASS_SHIFT                                              0
#define GET_X1APIC_APR_SUB_CLASS(AprRegister)                                   ((AprRegister >> X1APIC_APR_SUB_CLASS_SHIFT) & X1APIC_APR_SUB_CLASS_MASK)

#define X1APIC_TPR_CLASS_MASK                                                   0x0F
#define X1APIC_TPR_CLASS_SHIFT                                                  4
#define GET_X1APIC_TPR_CLASS(TprRegister)                                       ((TprRegister >> X1APIC_TPR_CLASS_SHIFT) & X1APIC_TPR_CLASS_MASK)
#define SET_X1APIC_TPR_CLASS(TprRegister, x)                                    ((TprRegister & ~(X1APIC_TPR_CLASS_MASK << X1APIC_TPR_CLASS_SHIFT)) | ((x & X1APIC_TPR_CLASS_MASK) << X1APIC_TPR_CLASS_SHIFT))

#define X1APIC_TPR_SUB_CLASS_MASK                                               0x0F
#define X1APIC_TPR_SUB_CLASS_SHIFT                                              4
#define GET_X1APIC_TPR_SUB_CLASS(TprRegister)                                   ((TprRegister >> X1APIC_TPR_SUB_CLASS_SHIFT) & X1APIC_TPR_SUB_CLASS_MASK)
#define SET_X1APIC_TPR_SUB_CLASS(TprRegister, x)                                ((TprRegister & ~(X1APIC_TPR_SUB_CLASS_MASK << X1APIC_TPR_SUB_CLASS_SHIFT)) | ((x & X1APIC_TPR_SUB_CLASS_MASK) << X1APIC_TPR_SUB_CLASS_SHIFT))


#define X1APIC_PPR_CLASS_MASK                                                   0x0F
#define X1APIC_PPR_CLASS_SHIFT                                                  4
#define GET_X1APIC_PPR_CLASS(PPRRegister)                                       ((PPRRegister >> X1APIC_PPR_CLASS_SHIFT) & X1APIC_PPR_CLASS_MASK)

#define X1APIC_PPR_SUB_CLASS_MASK                                               0x0F
#define X1APIC_PPR_SUB_CLASS_SHIFT                                              4
#define GET_X1APIC_PPR_SUB_CLASS(PPRRegister)                                   ((PPRRegister >> X1APIC_PPR_SUB_CLASS_SHIFT) & X1APIC_PPR_SUB_CLASS_MASK)

#define X1APIC_SVR_EOI_BROADCAST_SUPPRESS_MASK                                  1
#define X1APIC_SVR_EOI_BROADCAST_SUPPRESS_SHIFT                                 12
#define GET_X1APIC_SVR_EOI_BROADCAST_SUPPRESS(SvrRegister)                      ((SvrRegister >> X1APIC_SVR_EOI_BROADCAST_SUPPRESS_SHIFT) & X1APIC_SVR_EOI_BROADCAST_SUPPRESS_MASK)
#define SET_X1APIC_SVR_EOI_BROADCAST_SUPPRESS(SvrRegister, x)                   ((SvrRegister & ~(X1APIC_SVR_EOI_BROADCAST_SUPPRESS_MASK << X1APIC_SVR_EOI_BROADCAST_SUPPRESS_SHIFT)) | ((x & X1APIC_SVR_EOI_BROADCAST_SUPPRESS_MASK) << X1APIC_SVR_EOI_BROADCAST_SUPPRESS_SHIFT))

#define X1APIC_SVR_FOCUS_PROCESSOR_CHECKING_MASK                                1
#define X1APIC_SVR_FOCUS_PROCESSOR_CHECKING_SHIFT                               9
#define GET_X1APIC_SVR_FOCUS_PROCESSOR_CHECKING(SvrRegister)                    ((SvrRegister >> X1APIC_SVR_FOCUS_PROCESSOR_CHECKING_SHIFT) & X1APIC_SVR_FOCUS_PROCESSOR_CHECKING_MASK)
#define SET_X1APIC_SVR_FOCUS_PROCESSOR_CHECKING(SvrRegister, x)                 ((SvrRegister & ~(X1APIC_SVR_FOCUS_PROCESSOR_CHECKING_MASK << X1APIC_SVR_FOCUS_PROCESSOR_CHECKING_SHIFT)) | ((x & X1APIC_SVR_FOCUS_PROCESSOR_CHECKING_MASK) << X1APIC_SVR_FOCUS_PROCESSOR_CHECKING_SHIFT))

#define X1APIC_SVR_APIC_SOFTWARE_ENABLE_MASK                                    1
#define X1APIC_SVR_APIC_SOFTWARE_ENABLE_SHIFT                                   8
#define GET_X1APIC_SVR_APIC_SOFTWARE_ENABLE(SvrRegister)                        ((SvrRegister >> X1APIC_SVR_APIC_SOFTWARE_ENABLE_SHIFT) & X1APIC_SVR_APIC_SOFTWARE_ENABLE_MASK)
#define SET_X1APIC_SVR_APIC_SOFTWARE_ENABLE(SvrRegister, x)                     ((SvrRegister & ~(X1APIC_SVR_APIC_SOFTWARE_ENABLE_MASK << X1APIC_SVR_APIC_SOFTWARE_ENABLE_SHIFT)) | ((x & X1APIC_SVR_APIC_SOFTWARE_ENABLE_MASK) << X1APIC_SVR_APIC_SOFTWARE_ENABLE_SHIFT))

#define X1APIC_SVR_VECTOR_MASK                                                  0xFF
#define X1APIC_SVR_VECTOR_SHIFT                                                 0
#define GET_X1APIC_SVR_VECTOR(SvrRegister)                                      ((SvrRegister >> X1APIC_SVR_VECTOR_SHIFT) & X1APIC_SVR_VECTOR_MASK)
#define SET_X1APIC_SVR_VECTOR(SvrRegister, x)                                   ((SvrRegister & ~(X1APIC_SVR_VECTOR_MASK << X1APIC_SVR_VECTOR_SHIFT)) | ((x & X1APIC_SVR_VECTOR_MASK) << X1APIC_SVR_VECTOR_SHIFT))



UINT32 ApicHalGetX1ApicIdRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicVersionRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicTaskPriorityRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicArbitrationPriorityRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicProcessorPriorityRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicRemoteReadRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicLogicalDestinationRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicDestinationFormatRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicSpuriousInterruptVectorRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicInServiceRegisterX32(PVOID ApicBase, SIZE Offset);
UINT32 ApicHalGetX1ApicTriggerModeRegisterX32(PVOID ApicBase, SIZE Offset);
UINT32 ApicHalGetX1ApicInterruptRequestRegisterX32(PVOID ApicBase, SIZE Offset);
UINT32 ApicHalGetX1ApicErrorStatusRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicLvtCmciRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicInterruptCommandRegisterLow(PVOID ApicBase);
UINT32 ApicHalGetX1ApicInterruptCommandRegisterHigh(PVOID ApicBase);
UINT64 ApicHalGetX1ApicInterruptCommandRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicLvtTimerRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicLvtThermalSensorRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicLvtPerformanceMonitoringCountersRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicLvtLint0Register(PVOID ApicBase);
UINT32 ApicHalGetX1ApicLvtLint1Register(PVOID ApicBase);
UINT32 ApicHalGetX1ApicLvtErrorRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicInitialCountRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicCurrentCountRegister(PVOID ApicBase);
UINT32 ApicHalGetX1ApicDivideConfigurationRegister(PVOID ApicBase);
void ApicHalSetX1ApicIdRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicTaskPriorityRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicEndOfInterruptRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicLogicalDestinationRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicDestinationFormatRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicSpuriousInterruptVectorRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicLvtCmciRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicInterruptCommandRegisterLow(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicInterruptCommandRegisterHigh(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicInterruptCommandRegister(PVOID ApicBase, UINT64 Value);
void ApicHalSetX1ApicLvtTimerRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicLvtThermalSensorRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicLvtPerformanceMonitoringCountersRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicLvtLint0Register(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicLvtLint1Register(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicLvtErrorRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicInitialCountRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicDivideConfigurationRegister(PVOID ApicBase, UINT32 Value);
void ApicHalSetX1ApicErrorStatusRegister(PVOID ApicBase, UINT32 Value);

#endif