#ifndef _APIC_INTERNALS_H
#define _APIC_INTERNALS_H
#define _KERNEL_MODULE_
#include <LouAPI.h>

#define APIC_TIMER_VECTOR           0x20
#define APIC_IPI_DISPATCH_VECTOR    0x21
#define APIC_SPV_HANDLER_VECTOR     0x22

#define IA32_APIC_BASE_MSR_OFFSET               0x1B
#define IA32_APIC_BASE_MSR_X2APIC_ENABLE_BIT    (1 << 10)
#define IA32_APIC_BASE_MSR_XAPIC_ENABLE_BIT     (1 << 11)

#define IA32_THERMAL_STATUS_REGISTER                    0x01B0
#define IA32_THERMAL_STATUS_REGISTER_PMU_RESTRICTION    (1 << 11)


typedef enum{
    APIC_TIMER_MODE_ONE_SHOT = 0,
    APIC_TIMER_MODE_PERIODIC,
    APIC_TIMER_MODE_TSC_DEADLINE,
}APIC_TIMER_MODE;

typedef enum{
    APIC_LVT_DELIVERY_MODE_FIXED    = 0b0000,
    APIC_LVT_DELIVERY_MODE_SMI      = 0b0010,
    APIC_LVT_DELIVERY_MODE_NMI      = 0b0100,
    APIC_LVT_DELIVERY_MODE_EXT_INT  = 0b0111,
    APIC_LVT_DELIVERY_MODE_INIT     = 0b1000,
}APIC_LVT_DELIVERY_MODE;

typedef enum {
    APIC_TRIGGER_MODE_EDGE = 0,
    APIC_TRIGGER_MODE_LEVEL,
}APIC_TRIGGER_MODE;

typedef enum{
    APIC_IN_PIN_POLARITY_ACTIVE_HIGH = 0,
    APIC_IN_PIN_POLARITY_ACTIVE_LOW,
}APIC_IN_PIN_POLARITY;

typedef enum{
    APIC_ERROR_STATUS_SEND_CHECKSUM_ERROR =     (1),
    APIC_ERROR_STATUS_RECEIVE_CHECKSUM_ERROR =  (1 << 1),
    APIC_ERROR_STATUS_SEND_ACCEPT_ERROR =       (1 << 2),
    APIC_ERROR_STATUS_RECEIVE_ACCEPT_ERROR =    (1 << 3),
    APIC_ERROR_STATUS_REDIRECT_IPI =            (1 << 4),
    APIC_ERROR_STATUS_SEND_ILLEGAL_VECTOR =     (1 << 5),
    APIC_ERROR_STATUS_RECEIVE_ILLEGAL_VECTOR =  (1 << 6),
    APIC_ERROR_STATUS_ILLEGAL_VECTOR_ADDRESS =  (1 << 7),
}APIC_ERROR_STATUS;

typedef enum{
    APIC_TIMER_DIVIDE_BY2   = 0b0000,
    APIC_TIMER_DIVIDE_BY4   = 0b0001,
    APIC_TIMER_DIVIDE_BY8   = 0b0010,
    APIC_TIMER_DIVIDE_BY16  = 0b0011,
    APIC_TIMER_DIVIDE_BY32  = 0b1000,
    APIC_TIMER_DIVIDE_BY64  = 0b1001,
    APIC_TIMER_DIVIDE_BY128 = 0b1010,
    APIC_TIMER_DIVIDE_BY1   = 0b1011, 
}APIC_TIMER_DIVIDE_CONFIG;

typedef enum {
    APIC_ICR_DELIVERY_MODE_FIXED = 0,
    APIC_ICR_DELIVERY_MODE_LOWEST_PRIORITY,
    APIC_ICR_DELIVERY_MODE_SMI,
    APIC_ICR_DELIVERY_MODE_RSVD0,
    APIC_ICR_DELIVERY_MODE_NMI,
    APIC_ICR_DELIVERY_MODE_INIT,
    APIC_ICR_DELIVERY_MODE_STARTUP,
}APIC_ICR_DELIVERY_MODE;

typedef enum{
    APIC_DESTINATION_MODE_PHYSICAL = 0,
    APIC_DESTINATION_MODE_LOGICAL,
}APIC_DESTINATION_MODE;

typedef enum{
    APIC_LEVEL_DE_ASSERT = 0,
    APIC_LEVEL_ASSERT,
}APIC_LEVEL;

typedef enum{
    APIC_DESTINATION_SHORTHAND_NONE = 0,
    APIC_DESTINATION_SHORTHAND_SELF,
    APIC_DESTINATION_SHORTHAND_ALL,
    APIC_DESTINATION_SHORTHAND_ALL_ES, //excluding self
}APIC_DESTINATION_SHORTHAND;

typedef enum{
    X1_LOCAL_APIC_OBJECT_TYPE = 0,
    X2_LOCAL_APIC_OBJECT_TYPE,
    IO_APIC_OBJECT_TYPE,
    TOTAL_APIC_OBJECT_TYPES,
}APIC_OBJECT_TYPE;

typedef enum{
    IO_APIC_DELIVERY_MODE_FIXED = 0,
    IO_APIC_DELIVERY_MODE_LOWEST,
    IO_APIC_DELIVERY_MODE_SMI,
    IO_APIC_DELIVERY_MODE_NMI,
    IO_APIC_DELIVERY_MODE_INIT,
    IO_APIC_DELIVERY_MODE_EXT_INT,
}IO_APIC_DELIVERY_MODE;

typedef enum{
    IO_APIC_DESTINATION_MODE_PHYSICAL = 0,
    IO_APIC_DESTINATION_MODE_LOGICAL = 1,
}IO_APIC_DESTINATION_MODE;

typedef enum{
    IO_APIC_PIN_POLARITY_ACTIVE_HIGH = 0,
    IO_APIC_PIN_POLARITY_ISA_DEFAULT = 0,
    IO_APIC_PIN_POLARITY_ACTIVE_LOW,
}IO_APIC_PIN_POLARITY;

typedef enum{
    IO_APIC_TRIGGER_MODE_EDGE = 0,
    IO_APIC_TRIGGER_MODE_ISA_DEFAULT = 0,
    IO_APIC_TRIGGER_MODE_LEVEL,
}IO_APIC_TRIGGER_MODE;

typedef struct _X1LOCAL_APIC_DEVICE_OBJECT{
    PVOID                           ApicBase;
}X1LOCAL_APIC_DEVICE_OBJECT, * PX1LOCAL_APIC_DEVICE_OBJECT;

typedef struct _IO_APIC_DEVICE_OBJECT{
    PVOID                           ApicBase;
}IO_APIC_DEVICE_OBJECT, * PIO_APIC_DEVICE_OBJECT;

typedef struct _APIC_DEVICE_OBJECT{
    APIC_OBJECT_TYPE                ApicObjectType;
    UINT8                           TimerConfigTick;
    UINT8                           TimerConfigSelector;
    UINT32                          MsTimerCount;
    union{
        X1LOCAL_APIC_DEVICE_OBJECT  X1ApicObject;
        IO_APIC_DEVICE_OBJECT       IoApicObject;
    };
}APIC_DEVICE_OBJECT, * PAPIC_DEVICE_OBJECT;

typedef enum {
    REGISTER_COMMUNICATION_INTERRUPT = 0,
    ROUTE_INSTALLATION_INTERRUPT,
    DEMON_INSTALLATION_INTERRUPT,
    TOTAL_IPI_INTERRUPT_PACKET_TYPES,
}IPI_INTERRUPT_PACKET_TYPE;

typedef void (*IPI_HANDLER)(ULONG Processor, PVOID Data);

typedef struct _IPI_INTERRUPT_PACKET{
    IPI_HANDLER                 IpiHandler;
    PVOID                       IpiData;
}IPI_INTERRUPT_PACKET, * PIPI_INTERRUPT_PACKET;

typedef struct _PER_PROCESSOR_IPI_DATA{
    OPAQUE_PTR                      IpiVectorObject;
    spinlock_t                      ProcessorLock;
    IPI_INTERRUPT_PACKET            InterruptPacket;
}PER_PROCESSOR_IPI_DATA, * PPER_PROCESSOR_IPI_DATA;

typedef struct _PER_PROCESSOR_APIC_DATA{
    UINT32                          ApicID;
    UINT32                          ProcessorID;
    APIC_DEVICE_OBJECT              ApicDeviceObject;
    PER_PROCESSOR_IPI_DATA          IpiData;
    OPAQUE_PTR                      SpurriousVectorObject;
}PER_PROCESSOR_APIC_DATA, * PPER_PROCESSOR_APIC_DATA;

typedef struct _PER_IO_APIC_PIN_DATA{
    OPAQUE_PTR*     VectorObject;
}PER_IO_APIC_PIN_DATA, * PPER_IO_APIC_PIN_DATA;

typedef struct _PER_IO_APIC_DATA{
    UINT8                   ApicID;
    UINT8                   ApicGsiBase;
    UINT8                   ApicGsiCount;
    APIC_DEVICE_OBJECT      ApicDeviceObject;
    PPER_IO_APIC_PIN_DATA   PinVectorData;
}PER_IO_APIC_DATA, * PPER_IO_APIC_DATA;

typedef struct _PER_IO_OVERIDE_DATA{
    UINT8                   InDirectionIrq;
    UINT8                   OutDirectionIrq;
    IO_APIC_PIN_POLARITY    PinPolarity;
    IO_APIC_TRIGGER_MODE    TriggerMode;
}PER_IO_OVERIDE_DATA, * PPER_IO_OVERIDE_DATA;

#ifndef APIC_MAIN
extern PPER_PROCESSOR_APIC_DATA PerProcessorApicData;
#endif

void ApicHalDbgPrint(char* format, ...);
LOUSTATUS ApicHalInitializeInterProcessorInterrupts(ULONG Cpu);


LOUSTATUS ApicHalGetApicIdRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicVersionRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicTaskPriorityRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicArbitrationPriorityRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicProcessorPriorityRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicRemoteReadRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicLogicalDestinationRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicDestinationFormatRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicSpuriousInterruptVectorRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicInServiceRegisterX32Ex(PAPIC_DEVICE_OBJECT ApicDeviceObject, SIZE Offset, UINT32* Out);
LOUSTATUS ApicHalGetApicTriggerModeRegisterX32Ex(PAPIC_DEVICE_OBJECT ApicDeviceObject, SIZE Offset, UINT32* Out);
LOUSTATUS ApicHalGetApicInterruptRequestRegisterX32Ex(PAPIC_DEVICE_OBJECT ApicDeviceObject, SIZE Offset, UINT32* Out);
LOUSTATUS ApicHalGetApicErrorStatusRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicLvtCmciRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicInterruptCommandRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT64* Out);
LOUSTATUS ApicHalGetApicLvtTimerRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicLvtThermalSensorRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicLvtPerformanceMonitoringCountersRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicLvtLint0RegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicLvtLint1RegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicLvtErrorRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicInitialCountRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicCurrentCountRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);
LOUSTATUS ApicHalGetApicDivideConfigurationRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Out);

LOUSTATUS ApicHalSetApicIdRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicTaskPriorityRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicEndOfInterruptRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicLogicalDestinationRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicDestinationFormatRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicSpuriousInterruptVectorRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicErrorStatusRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicLvtCmciRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicInterruptCommandRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT64 Value);
LOUSTATUS ApicHalSetApicLvtTimerRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicLvtThermalSensorRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicLvtPerformanceMonitoringCountersRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicLvtLint0RegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicLvtLint1RegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicLvtErrorRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicInitialCountRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);
LOUSTATUS ApicHalSetApicDivideConfigurationRegisterEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value);

LOUSTATUS ApicHalGetApicIdRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* IdOut);
LOUSTATUS ApicHalGetApicVersionRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* VersionOut, UINT32* MaxLvtOut, BOOLEAN* SupportsEoiSuppresionOut);
LOUSTATUS ApicHalGetApicLvtTimerRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, APIC_TIMER_MODE* TimerModeOut, BOOLEAN* MaskedOut, BOOLEAN* InterruptPendingOut, UINT8* VectorOut);
LOUSTATUS ApicHalGetApicLvtCmciRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
LOUSTATUS ApicHalGetApicLvtLint0Register(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedOut, APIC_TRIGGER_MODE* TriggerModeOut, BOOLEAN* IrrSetOut, APIC_IN_PIN_POLARITY* InPinPolarityOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
LOUSTATUS ApicHalGetApicLvtLint1Register(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedOut, APIC_TRIGGER_MODE* TriggerModeOut, BOOLEAN* IrrSetOut, APIC_IN_PIN_POLARITY* InPinPolarityOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
LOUSTATUS ApicHalGetApicLvtErrorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
LOUSTATUS ApicHalGetApicLvtPerformanceMonitoringCountersRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
LOUSTATUS ApicHalGetApicLvtThermalSensorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
LOUSTATUS ApicHalGetApicLogicalDestinationRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* IdOut);
LOUSTATUS ApicHalGetApicDestinationFormatRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* DfrModelOut);
LOUSTATUS ApicHalGetApicArbitrationPriorityRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* ClassOut, UINT32* SubClassOut);
LOUSTATUS ApicHalGetApicTaskPriorityRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* ClassOut, UINT32* SubClassOut);
LOUSTATUS ApicHalGetApicProcessorPriorityRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* ClassOut, UINT32* SubClassOut);
LOUSTATUS ApicHalGetApicSpuriousInterruptVectorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* EoiBroadcastSuppresedOut, BOOLEAN* FocusProcessorCheckingEnabledOut, BOOLEAN* ApicSoftwareEnabledOut, UINT8* SpuriousInterruptVectorOut);

LOUSTATUS ApicHalSetApicIdRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* IdIn);
LOUSTATUS ApicHalSetApicLvtTimerRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, APIC_TIMER_MODE* TimerModeIn, BOOLEAN* MaskedIn, UINT8* VectorIn);
LOUSTATUS ApicHalSetApicLvtCmciRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedIn, APIC_LVT_DELIVERY_MODE* DeliveryModeIn, UINT8* VectorIn);
LOUSTATUS ApicHalSetApicLvtLint0Register(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedIn, APIC_TRIGGER_MODE* TriggerModeIn, APIC_IN_PIN_POLARITY* InPinPolarityIn, UINT8* VectorIn);
LOUSTATUS ApicHalSetApicLvtLint1Register(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedIn, APIC_TRIGGER_MODE* TriggerModeIn, APIC_IN_PIN_POLARITY* InPinPolarityIn, UINT8* VectorIn);
LOUSTATUS ApicHalSetApicLvtErrorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedIn, APIC_LVT_DELIVERY_MODE* DeliveryModeIn, UINT8* VectorIn);
LOUSTATUS ApicHalSetApicLvtPerformanceMonitoringCountersRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedIn, APIC_LVT_DELIVERY_MODE* DeliveryModeIn, UINT8* VectorIn);
LOUSTATUS ApicHalSetApicLvtThermalSensorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* MaskedIn, APIC_LVT_DELIVERY_MODE* DeliveryModeIn, UINT8* VectorIn);
LOUSTATUS ApicHalSetApicInterruptCommandRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 DestinationField, APIC_DESTINATION_SHORTHAND Shorthand, APIC_TRIGGER_MODE TriggerMode, APIC_LEVEL Level, APIC_DESTINATION_MODE DestinationMode, APIC_ICR_DELIVERY_MODE DeliveryMode, UINT8 Vector);
LOUSTATUS ApicHalSetApicLogicalDestinationRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* IdIn);
LOUSTATUS ApicHalSetApicDestinationFormatRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* DfrModelIn);
LOUSTATUS ApicHalSetApicTaskPriorityRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* ClassIn, UINT32* SubClassIn);
LOUSTATUS ApicHalSetApicSpuriousInterruptVectorRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN* EoiBroadcastSuppresedIn, BOOLEAN* FocusProcessorCheckingEnabledIn, BOOLEAN* ApicSoftwareEnabledIn, UINT8* SpuriousInterruptVectorIn);

LOUSTATUS ApicHalGetApicDivideConfigurationRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, APIC_TIMER_DIVIDE_CONFIG* DivideConfigOut);
LOUSTATUS ApicHalSetApicDivideConfigurationRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, APIC_TIMER_DIVIDE_CONFIG DivideConfig);
LOUSTATUS ApicHalGetApicTimerInitialCount(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* InitialCountOut);
LOUSTATUS ApicHalSetApicTimerInitialCount(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 InitialCount);
LOUSTATUS ApicHalGetApicTimerCurrentCount(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* CurrentCountOut);
LOUSTATUS ApicHalGetApicInterruptCommandRegister(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* DestinationField, APIC_DESTINATION_SHORTHAND* Shorthand, APIC_TRIGGER_MODE* TriggerMode, APIC_LEVEL* Level, BOOLEAN* InterruptPending, APIC_DESTINATION_MODE* DestinationMode, APIC_ICR_DELIVERY_MODE* DeliveryMode, UINT8* Vector);
LOUSTATUS ApicHalSendSipiToAp(UINT32 Ap);

DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicIdRegister(UINT32* IdOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicVersionRegister(UINT32* VersionOut, UINT32* MaxLvtOut, BOOLEAN* SupportsEoiSuppresionOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicLvtTimerRegister(APIC_TIMER_MODE* TimerModeOut, BOOLEAN* MaskedOut, BOOLEAN* InterruptPendingOut, UINT8* VectorOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicLvtCmciRegister(BOOLEAN* MaskedOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicLvtLint0Register(BOOLEAN* MaskedOut, APIC_TRIGGER_MODE* TriggerModeOut, BOOLEAN* IrrSetOut, APIC_IN_PIN_POLARITY* InPinPolarityOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicLvtLint1Register(BOOLEAN* MaskedOut, APIC_TRIGGER_MODE* TriggerModeOut, BOOLEAN* IrrSetOut, APIC_IN_PIN_POLARITY* InPinPolarityOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicLvtErrorRegister(BOOLEAN* MaskedOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicLvtPerformanceMonitoringCountersRegister(BOOLEAN* MaskedOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicLvtThermalSensorRegister(BOOLEAN* MaskedOut, BOOLEAN* InterruptPendingOut, APIC_LVT_DELIVERY_MODE* DeliveryModeOut, UINT8* VectorOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicLogicalDestinationRegister(UINT32* IdOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicDestinationFormatRegister(UINT32* DfrModelOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicArbitrationPriorityRegister(UINT32* ClassOut, UINT32* SubClassOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicTaskPriorityRegister(UINT32* ClassOut, UINT32* SubClassOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicProcessorPriorityRegister(UINT32* ClassOut, UINT32* SubClassOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicSpuriousInterruptVectorRegister(BOOLEAN* EoiBroadcastSuppresedOut, BOOLEAN* FocusProcessorCheckingEnabledOut, BOOLEAN* ApicSoftwareEnabledOut, UINT8* SpuriousInterruptVectorOut);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicIdRegister(UINT32* IdIn);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicLvtTimerRegister(APIC_TIMER_MODE* TimerModeIn, BOOLEAN* MaskedIn, UINT8* VectorIn);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicLvtCmciRegister(BOOLEAN* MaskedIn, APIC_LVT_DELIVERY_MODE* DeliveryModeIn, UINT8* VectorIn);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicLvtLint0Register(BOOLEAN* MaskedIn, APIC_TRIGGER_MODE* TriggerModeIn, APIC_IN_PIN_POLARITY* InPinPolarityIn, UINT8* VectorIn);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicLvtLint1Register(BOOLEAN* MaskedIn, APIC_TRIGGER_MODE* TriggerModeIn,  APIC_IN_PIN_POLARITY* InPinPolarityIn,  UINT8* VectorIn);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicLvtErrorRegister(BOOLEAN* MaskedIn,  APIC_LVT_DELIVERY_MODE* DeliveryModeIn, UINT8* VectorIn);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicLvtPerformanceMonitoringCountersRegister(BOOLEAN* MaskedIn, APIC_LVT_DELIVERY_MODE* DeliveryModeIn, UINT8* VectorIn);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicLvtThermalSensorRegister(BOOLEAN* MaskedIn, APIC_LVT_DELIVERY_MODE* DeliveryModeIn, UINT8* VectorIn);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicInterruptCommandRegister(UINT32 DestinationField, APIC_DESTINATION_SHORTHAND  Shorthand, APIC_TRIGGER_MODE TriggerMode, APIC_LEVEL Level, APIC_DESTINATION_MODE DestinationMode, APIC_ICR_DELIVERY_MODE DeliveryMode, UINT8 Vector);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicLogicalDestinationRegister(UINT32* IdIn);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicDestinationFormatRegister(UINT32* DfrModelIn);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicTaskPriorityRegister(UINT32* ClassIn, UINT32* SubClassIn);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicSpuriousInterruptVectorRegister(BOOLEAN* EoiBroadcastSuppresedIn, BOOLEAN* FocusProcessorCheckingEnabledIn, BOOLEAN* ApicSoftwareEnabledIn, UINT8* SpuriousInterruptVectorIn);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicDivideConfigurationRegister(APIC_TIMER_DIVIDE_CONFIG* DivideConfigOut);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicDivideConfigurationRegister(APIC_TIMER_DIVIDE_CONFIG DivideConfig);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicTimerInitialCount(UINT32* InitialCountOut);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicTimerInitialCount(UINT32 InitialCount);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicTimerCurrentCount(UINT32* CurrentCountOut);
DRIVER_EXPORT void ApicHalSignalLocalApicEoi();

DRIVER_EXPORT LOUSTATUS ApicHalGetIoApicIdRegisterFromObject(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* VersionOut);
DRIVER_EXPORT LOUSTATUS ApicHalGetIoApicVersionRegisterFromObject(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Version, UINT32* MaxRedirections);
DRIVER_EXPORT LOUSTATUS ApicHalGetIoApicArbitrationIdRegisterFromObject(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32* Id);
DRIVER_EXPORT LOUSTATUS ApicHalGetIoApicRedirectionEntryFromObjectEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT8 Entry, UINT64* Out);
DRIVER_EXPORT LOUSTATUS ApicHalGetIoApicRedirectionEntryFromObject(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT8 Entry, UINT32* Destination, BOOLEAN* Masked, IO_APIC_TRIGGER_MODE* TriggerMode, BOOLEAN* IrrSet, IO_APIC_PIN_POLARITY* PinPolarity, BOOLEAN* InterruptPending, IO_APIC_DESTINATION_MODE* DestinationMode, IO_APIC_DELIVERY_MODE* DeliveryMode, UINT8* Vector);
DRIVER_EXPORT LOUSTATUS ApicHalSetIoApicRedirectionEntryFromObjectEx(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT8 Entry, UINT64 In);
DRIVER_EXPORT LOUSTATUS ApicHalSetIoApicRedirectionEntryFromObject(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT8 Entry, UINT32* Destination, BOOLEAN* Masked, IO_APIC_TRIGGER_MODE* TriggerMode, IO_APIC_PIN_POLARITY* PinPolarity, IO_APIC_DESTINATION_MODE* DestinationMode, IO_APIC_DELIVERY_MODE* DeliveryMode, UINT8* Vector);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicInterruptCommandRegister(UINT32* DestinationField, APIC_DESTINATION_SHORTHAND* Shorthand, APIC_TRIGGER_MODE* TriggerMode, APIC_LEVEL* Level, BOOLEAN* InterruptPending, APIC_DESTINATION_MODE* DestinationMode, APIC_ICR_DELIVERY_MODE* DeliveryMode, UINT8* Vector);
DRIVER_EXPORT LOUSTATUS ApicHalGetLocalApicErrorStatus(UINT32* ErrorStatus);
DRIVER_EXPORT LOUSTATUS ApicHalSetLocalApicErrorStatus(UINT32 Value);
DRIVER_EXPORT void ApicHalApInitializationFunction(PLKSEB TrampolineLkseb);

DRIVER_EXPORT LOUSTATUS ApicIpiHalSendNewInterruptRouteData(ULONG Cpu, PVOID RouteData);
DRIVER_EXPORT LOUSTATUS ApicIpiHalSendNewDemonData(ULONG Cpu, PVOID DemonData);

DRIVER_EXPORT LOUSTATUS ApicHalInitializeIsaVectorToIoApicRedirection(OPAQUE_PTR VectorObject, UINT8 GsiVector);
DRIVER_EXPORT LOUSTATUS ApicHalInitializeVectorToIoApicRedirection(OPAQUE_PTR VectorObject, UINT8 GsiVector, IO_APIC_TRIGGER_MODE TriggerMode, IO_APIC_PIN_POLARITY PinPolarity);
DRIVER_EXPORT ULONG ApicHalCpuIdToApicId(ULONG Cpu);

//TODO: 

//if ESR bit 4 is set then a redirectable IPI with lowest prioirty 
//is not supported so an IPI sender must check this in an error to 
//verify if this caused and error

//if ESR bit 5 is set the handler must scan through all local 
//tables and if the vector is 0 through 15 and print

//if ESR bit 6 is set the handler must scan through all local 
//tables and if the vector is 0 through 15 and print

//if ESR bit 7 is set the handler must attatch to the GPF Handler
//and disable whatever kernel thread or user process accessed 
//created the GPF


#endif