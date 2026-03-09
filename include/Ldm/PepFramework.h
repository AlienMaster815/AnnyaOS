#ifndef _PEP_FRAMEWORK_H
#define _PEP_FRAMEWORK_H

#include <Ldm.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef 
LOUSTATUS 
PEPCALLBACKNOTIFYDPM(
    PEPHANDLE   DeviceHandle,
    ULONG       Notification,
    PVOID       Data
);

typedef PEPCALLBACKNOTIFYDPM* PPEPCALLBACKNOTIFYDPM;

typedef 
BOOLEAN
PEPCALLBACKNOTIFYPPM(
    ULONG   Notification,
    PVOID   Data
);

typedef PEPCALLBACKNOTIFYPPM* PPEPCALLBACKNOTIFYPPM;

typedef 
BOOLEAN
PEPCALLBACKNOTIFYACPI(
    ULONG   Notification,
    PVOID   Data
);

typedef PEPCALLBACKNOTIFYACPI* PPEPCALLBACKNOTIFYACPI;

typedef 
LOUSTATUS 
POFXCALLBACKREQUESTWORKER(
    POHANDLE    DeviceHandle,
    ULONG       Flags
);

typedef POFXCALLBACKREQUESTWORKER* PPOFXCALLBACKREQUESTWORKER;

typedef 
LOUSTATUS
POFXCALLBACKENUMERATEUNMASKEDINTERRUPTS(
    PVOID   PluginHandle,
    ULONG   Flags
);

typedef POFXCALLBACKENUMERATEUNMASKEDINTERRUPTS* PPOFXCALLBACKENUMERATEUNMASKEDINTERRUPTS;

typedef 
LOUSTATUS 
PROCESSOR_HALT_ROUTINE(
    PVOID   Context
);

typedef PROCESSOR_HALT_ROUTINE * PPROCESSOR_HALT_ROUTINE;

typedef 
LOUSTATUS
POFXCALLBACKPROCESSORHALT(
    ULONG                       Flags,
    PVOID                       Context,
    PPROCESSOR_HALT_ROUTINE     HaltRoutine
);

typedef POFXCALLBACKPROCESSORHALT* PPOFXCALLBACKPROCESSORHALT;


typedef 
LOUSTATUS
POFXCALLBACKREQUESTINTERRUPT(
    ULONG   Gsiv
);

typedef POFXCALLBACKREQUESTINTERRUPT* PPOFXCALLBACKREQUESTINTERRUPT;

typedef 
void
POFXCALLBACKCRITICALRESOURCE(
    POHANDLE    DeviceHandle,
    ULONG       Component,
    BOOLEAN     Active
);

typedef POFXCALLBACKCRITICALRESOURCE* PPOFXCALLBACKCRITICALRESOURCE;


typedef 
LOUSTATUS
POFXCALLBACKPROCESSORIDLEVETO(
    POHANDLE    ProcessorHandle,
    ULONG       ProcessorState,
    ULONG       VetoReason,
    BOOLEAN     Increment
);

typedef POFXCALLBACKPROCESSORIDLEVETO* PPOFXCALLBACKPROCESSORIDLEVETO;

typedef 
LOUSTATUS 
POFXCALLBACKPLATFORMIDLEVETO(
    POHANDLE    ProcessorHandle,
    ULONG       PlatformState,
    ULONG       VetoReason,
    BOOLEAN     Increment
);

typedef POFXCALLBACKPLATFORMIDLEVETO* PPOFXCALLBACKPLATFORMIDLEVETO;

typedef struct _PEP_IDLE_STATE_UPDATE {
    ULONG Version;
    ULONG Latency;
    ULONG BreakEvenDuration;
} PEP_PROCESSOR_IDLE_STATE_UPDATE, * PPEP_PROCESSOR_IDLE_STATE_UPDATE, 
    PEP_PLATFORM_IDLE_STATE_UPDATE, * PPEP_PLATFORM_IDLE_STATE_UPDATE;

typedef 
LOUSTATUS
POFXCALLBACKUPDATEPROCESSORIDLESTATE(
    POHANDLE                            ProcessorHandle,
    ULONG                               ProcessorState,
    PPEP_PROCESSOR_IDLE_STATE_UPDATE    IdleStateUpdate
);

typedef POFXCALLBACKUPDATEPROCESSORIDLESTATE* PPOFXCALLBACKUPDATEPROCESSORIDLESTATE;

typedef 
LOUSTATUS
POFXCALLBACKUPDATEPLATFORMIDLESTATE(
    POHANDLE                            ProcessorHandle,
    ULONG                               PlatformState,
    PPEP_PLATFORM_IDLE_STATE_UPDATE     IdleUpdateState 
);

typedef POFXCALLBACKUPDATEPLATFORMIDLESTATE* PPOFXCALLBACKUPDATEPLATFORMIDLESTATE;

typedef 
LOUSTATUS 
POFXCALLBACKREQUESTCOMMON(
    ULONG   RequestId,
    PVOID   Data
);

typedef POFXCALLBACKREQUESTCOMMON* PPOFXCALLBACKREQUESTCOMMON;

typedef struct _PEP_CRASHDUMP_INFORMATION{
   PEPHANDLE DeviceHandle;
   PVOID     DeviceContext;
}PEP_CRASHDUMP_INFORMATION, * PPEP_CRASHDUMP_INFORMATION;

typedef 
BOOLEAN
PEPCALLBACKPOWERONCRASHDUMPDEVICE(
    PPEP_CRASHDUMP_INFORMATION  Information
);  

typedef PEPCALLBACKPOWERONCRASHDUMPDEVICE* PPEPCALLBACKPOWERONCRASHDUMPDEVICE;

typedef struct _PEP_KERNEL_INFORMATION_STRUCT_V1{
    USHORT                                   Version;
    USHORT                                   Size;
    POHANDLE                                 Plugin;
    PPOFXCALLBACKREQUESTWORKER               RequestWorker;
    PPOFXCALLBACKENUMERATEUNMASKEDINTERRUPTS EnumerateUnmaskedInterrupts;
    PPOFXCALLBACKPROCESSORHALT               ProcessorHalt;
    PPOFXCALLBACKREQUESTINTERRUPT            RequestInterrupt;
    PPOFXCALLBACKCRITICALRESOURCE            TransitionCriticalResource;
}PEP_KERNEL_INFORMATION_STRUCT_V1, * PPEP_KERNEL_INFORMATION_STRUCT_V1;

typedef struct _PEP_KERNEL_INFORMATION_STRUCT_V2{
    USHORT                                   Version;
    USHORT                                   Size;
    POHANDLE                                 Plugin;
    PPOFXCALLBACKREQUESTWORKER               RequestWorker;
    PPOFXCALLBACKENUMERATEUNMASKEDINTERRUPTS EnumerateUnmaskedInterrupts;
    PPOFXCALLBACKPROCESSORHALT               ProcessorHalt;
    PPOFXCALLBACKREQUESTINTERRUPT            RequestInterrupt;
    PPOFXCALLBACKCRITICALRESOURCE            TransitionCriticalResource;
    PPOFXCALLBACKPROCESSORIDLEVETO           ProcessorIdleVeto;
    PPOFXCALLBACKPLATFORMIDLEVETO            PlatformIdleVeto;
    PPOFXCALLBACKUPDATEPROCESSORIDLESTATE    UpdateProcessorIdleState;
    PPOFXCALLBACKUPDATEPLATFORMIDLESTATE     UpdatePlatformIdleState;
}PEP_KERNEL_INFORMATION_STRUCT_V2, *PPEP_KERNEL_INFORMATION_STRUCT_V2;

typedef struct _PEP_KERNEL_INFORMATION_STRUCT_V3{
    USHORT                                   Version;
    USHORT                                   Size;
    POHANDLE                                 Plugin;
    PPOFXCALLBACKREQUESTWORKER               RequestWorker;
    PPOFXCALLBACKENUMERATEUNMASKEDINTERRUPTS EnumerateUnmaskedInterrupts;
    PPOFXCALLBACKPROCESSORHALT               ProcessorHalt;
    PPOFXCALLBACKREQUESTINTERRUPT            RequestInterrupt;
    PPOFXCALLBACKCRITICALRESOURCE            TransitionCriticalResource;
    PPOFXCALLBACKPROCESSORIDLEVETO           ProcessorIdleVeto;
    PPOFXCALLBACKPLATFORMIDLEVETO            PlatformIdleVeto;
    PPOFXCALLBACKUPDATEPROCESSORIDLESTATE    UpdateProcessorIdleState;
    PPOFXCALLBACKUPDATEPLATFORMIDLESTATE     UpdatePlatformIdleState;
    PPOFXCALLBACKREQUESTCOMMON               RequestCommon;
}PEP_KERNEL_INFORMATION_STRUCT_V3, * PPEP_KERNEL_INFORMATION_STRUCT_V3;

typedef union _PEP_KERNEL_INFORMATION{
    PEP_KERNEL_INFORMATION_STRUCT_V1    V1;
    PEP_KERNEL_INFORMATION_STRUCT_V2    V2;
    PEP_KERNEL_INFORMATION_STRUCT_V3    V3;
}PEP_KERNEL_INFORMATION, * PPEP_KERNEL_INFORMATION;

typedef struct _PO_FX_COMPONENT_IDLE_STATE {
    ULONGLONG TransitionLatency;
    ULONGLONG ResidencyRequirement;
    ULONG     NominalPower;
} PO_FX_COMPONENT_IDLE_STATE, * PPO_FX_COMPONENT_IDLE_STATE;

typedef struct _PO_FX_COMPONENT_V1{
    GUID                        Id;
    ULONG                       IdleStateCount;
    ULONG                       DeepestWakeableIdleState;
    PPO_FX_COMPONENT_IDLE_STATE IdleStates;
}PO_FX_COMPONENT_V1, * PPO_FX_COMPONENT_V1;

typedef struct _PO_FX_COMPONENT_V2{
   GUID                        Id;
   ULONGLONG                   Flags;
   ULONG                       DeepestWakeableIdleState;
   ULONG                       IdleStateCount;
   PPO_FX_COMPONENT_IDLE_STATE IdleStates;
   ULONG                       ProviderCount;
   PULONG                      Providers;
}PO_FX_COMPONENT_V2, * PPO_FX_COMPONENT_V2;

typedef union _PO_FX_COMPONENT{
    PO_FX_COMPONENT_V1     V1;
    PO_FX_COMPONENT_V2     V2;
}PO_FX_COMPONENT, * PPO_FX_COMPONENT;

typedef 
void 
PO_FX_COMPONENT_IDLE_STATE_CALLBACK(
    PVOID   Context,
    ULONG   Component,
    ULONG State
);

typedef PO_FX_COMPONENT_IDLE_STATE_CALLBACK* PPO_FX_COMPONENT_IDLE_STATE_CALLBACK;

typedef 
void 
PO_FX_COMPONENT_CRITICAL_TRANSITION_CALLBACK(
    PVOID   Context,
    ULONG   Component,
    ULONG   Fx
);

typedef PO_FX_COMPONENT_CRITICAL_TRANSITION_CALLBACK* PPO_FX_COMPONENT_CRITICAL_TRANSITION_CALLBACK;

typedef 
void
PO_FX_COMPONENT_IDLE_CONDITION_CALLBACK(
    PVOID   Context,
    ULONG   Component
);

typedef PO_FX_COMPONENT_IDLE_CONDITION_CALLBACK* PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK;

typedef 
void 
PO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK(
    PVOID   Context,
    ULONG   Component
);

typedef PO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK* PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK;

typedef 
void
PO_FX_DEVICE_POWER_REQUIRED_CALLBACK(
    PVOID Context
);

typedef PO_FX_DEVICE_POWER_REQUIRED_CALLBACK* PPO_FX_DEVICE_POWER_REQUIRED_CALLBACK;

typedef 
void 
PO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK(
    PVOID   Context
);

typedef PO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK* PPO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK;

typedef 
LOUSTATUS 
PO_FX_POWER_CONTROL_CALLBACK(
    PVOID   DeviceContext,
    LPCGUID PowerControlCode,
    PVOID   InBuffer,
    SIZE    InBufferSize,
    PVOID   OutBuffer,
    SIZE    OutBufferSize,
    PSIZE   BytesReturned
);

typedef PO_FX_POWER_CONTROL_CALLBACK* PPO_FX_POWER_CONTROL_CALLBACK;

typedef 
void
PO_FX_DIRECTED_POWER_UP_CALLBACK(
    PVOID Context,
    ULONG Flags
);

typedef PO_FX_DIRECTED_POWER_UP_CALLBACK* PPO_FX_DIRECTED_POWER_UP_CALLBACK;

typedef 
void 
PO_FX_DIRECTED_POWER_DOWN_CALLBACK(
    PVOID   Context,
    ULONG   Flags
);

typedef PO_FX_DIRECTED_POWER_DOWN_CALLBACK* PPO_FX_DIRECTED_POWER_DOWN_CALLBACK;

typedef 
void
PO_FX_COMPONENT_PERF_STATE_CALLBACK(
    PVOID   Context,
    ULONG   Component,
    BOOLEAN Succeeded,
    PVOID   RequestContext
);

typedef PO_FX_COMPONENT_PERF_STATE_CALLBACK* PPO_FX_COMPONENT_PERF_STATE_CALLBACK;

typedef struct _PO_FX_DEVICE_V1{
    ULONG                                      Version;
    ULONG                                      ComponentCount;
    PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK ComponentActiveConditionCallback;
    PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK   ComponentIdleConditionCallback;
    PPO_FX_COMPONENT_IDLE_STATE_CALLBACK       ComponentIdleStateCallback;
    PPO_FX_DEVICE_POWER_REQUIRED_CALLBACK      DevicePowerRequiredCallback;
    PPO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK  DevicePowerNotRequiredCallback;
    PPO_FX_POWER_CONTROL_CALLBACK              PowerControlCallback;
    PVOID                                      DeviceContext;
    PO_FX_COMPONENT_V1*                         Components;
}PO_FX_DEVICE_V1, * PPO_FX_DEVICE_V1;

typedef struct _PO_FX_DEVICE_V2{
    ULONG                                      Version;
    ULONGLONG                                  Flags;
    PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK ComponentActiveConditionCallback;
    PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK   ComponentIdleConditionCallback;
    PPO_FX_COMPONENT_IDLE_STATE_CALLBACK       ComponentIdleStateCallback;
    PPO_FX_DEVICE_POWER_REQUIRED_CALLBACK      DevicePowerRequiredCallback;
    PPO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK  DevicePowerNotRequiredCallback;
    PPO_FX_POWER_CONTROL_CALLBACK              PowerControlCallback;
    PVOID                                      DeviceContext;
    ULONG                                      ComponentCount;
    PO_FX_COMPONENT_V2*                         Components;
}PO_FX_DEVICE_V2, * PPO_FX_DEVICE_V2;

typedef struct _PO_FX_DEVICE_V3{
    ULONG                                      Version;
    ULONGLONG                                  Flags;
    PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK ComponentActiveConditionCallback;
    PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK   ComponentIdleConditionCallback;
    PPO_FX_COMPONENT_IDLE_STATE_CALLBACK       ComponentIdleStateCallback;
    PPO_FX_DEVICE_POWER_REQUIRED_CALLBACK      DevicePowerRequiredCallback;
    PPO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK  DevicePowerNotRequiredCallback;
    PPO_FX_POWER_CONTROL_CALLBACK              PowerControlCallback;
    PPO_FX_DIRECTED_POWER_UP_CALLBACK          DirectedPowerUpCallback;
    PPO_FX_DIRECTED_POWER_DOWN_CALLBACK        DirectedPowerDownCallback;
    ULONG                                      DirectedFxTimeoutInSeconds;
    PVOID                                      DeviceContext;
    ULONG                                      ComponentCount;
    PO_FX_COMPONENT_V2*                        Components;
}PO_FX_DEVICE_V3, * PPO_FX_DEVICE_V3;

typedef union _PO_FX_DEVICE{
    PO_FX_DEVICE_V1     V1;
    PO_FX_DEVICE_V2     V2;
    PO_FX_DEVICE_V3     V3;
}PO_FX_DEVICE, * PPO_FX_DEVICE;

typedef struct _PO_FX_CORE_DEVICE{
    ULONG                                           Version;
    ULONG                                           ComponentCount;
    PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK      ComponentActiveConditionCallback;
    PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK        ComponentIdleConditionCallback;
    PPO_FX_COMPONENT_CRITICAL_TRANSITION_CALLBACK   ComponentCriticalTransitionCallback;
    PPO_FX_COMPONENT_IDLE_STATE_CALLBACK            ComponentIdleStateCallback;
    PVOID                                           DeviceContext;
    PO_FX_COMPONENT*                                Components;
}PO_FX_CORE_DEVICE, * PPO_FX_CORE_DEVICE;

typedef enum _GPIO_PIN_CONFIG_TYPE{
    PullDefault = 0,
    PullUp,
    PullDown,
    PullNone
} GPIO_PIN_CONFIG_TYPE;

typedef enum _GPIO_PIN_IORESTRICTION_TYPE{
    IoRestrictionNone = 0,
    IoRestrictionInputOnly,
    IoRestrictionOutputOnly,
    IoRestrictionNoneAndPreserve
}GPIO_PIN_IORESTRICTION_TYPE;

typedef enum{
    PepIdleCancelWorkPending = 0,
    PepIdleCancelDependencyCheckFailed,
    PepIdleCancelNoCState,
    PepIdleCancelMax
}PEP_PROCESSOR_IDLE_CANCEL_CODE, * PPEP_PROCESSOR_IDLE_CANCEL_CODE;

typedef enum _PEP_DEVICE_ACCEPTANCE_TYPE{
    PepDeviceNotAccepted = 0,
    PepDeviceAccepted,
    PepDeviceAceptedMax
}PEP_DEVICE_ACCEPTANCE_TYPE, * PPEP_DEVICE_ACCEPTANCE_TYPE;

typedef enum _PEP_WORK_TYPE{
    PepWorkRequestPowerControl = 0,
    PepWorkCompleteIdleState,
    PepWorkCompletePerfState,
    PepWorkAcpiNotify,
    PepWorkAcpiBUILD_CHILDRENControlMethodComplete,
    PepWorkMax
}PEP_WORK_TYPE, * PPEP_WORK_TYPE;

typedef enum{
    PepIdleTypeProcessor = 0,
    PepIdleTypePlatform,
    PepIdleTypeMax
} PEP_PROCESSOR_IDLE_TYPE, * PPEP_PROCESSOR_IDLE_TYPE;

typedef union _PEP_ACPI_OBJECT_NAME{
    UCHAR   Name[4];
    ULONG   NameAsUlong;
}PEP_ACPI_OBJECT_NAME, * PPEP_ACPI_OBJECT_NAME;

typedef enum _PEP_ACPI_OBJECT_TYPE{
    PepAcpiObjectTypeMethod = 0,
    PepAcpiObjectTypeDevice,
    PepAcpiObjectTypeMaximum
}PEP_ACPI_OBJECT_TYPE, * PPEP_ACPI_OBJECT_TYPE;

typedef struct _PEP_ACPI_OBJECT_NAME_WITH_TYPE{
    PEP_ACPI_OBJECT_NAME    Name;
    PEP_ACPI_OBJECT_TYPE    Type;
}PEP_ACPI_OBJECT_NAME_WITH_TYPE, * PPEP_ACPI_OBJECT_NAME_WITH_TYPE;

typedef union _PEP_ACPI_RESOURCE_FLAGS{
    ULONG       AsULong;
    struct {
        ULONG   Shared          : 1;
        ULONG   Wake            : 1;
        ULONG   ResourceUsage   : 1;
        ULONG   SlaveMode       : 1;
        ULONG   AddressingMode  : 1;
        ULONG   SharedMode      : 1;
        ULONG   Reserved        : 26;
    };
}PEP_ACPI_RESOURCE_FLAGS, * PPEP_ACPI_RESOURCE_FLAGS;

typedef enum _PEP_PERF_STATE_TYPE{
    PepPerfStateTypeDiscrete = 0,
    PepPerfStateTypeRange,
    PepPerfStateTypeMax
}PEP_PERF_STATE_TYPE, * PPEP_PERF_STATE_TYPE;

typedef enum _PEP_PERF_STATE_UNIT{
    PepPerfStateUnitOther = 0,
    PepPerfStateUnitFrequency,
    PepPerfStateUnitBandwidth,
    PepPerfStateUnitMax
}PEP_PERF_STATE_UNIT, * PPEP_PERF_STATE_UNIT;

typedef enum _PEP_ACPI_RESOURCE_TYPE{
    PepAcpiMemory = 0,
    PepAcpiIoPort,
    PepAcpiInterrupt,
    PepAcpiGpioIo,
    PepAcpiGpioInt,
    PepAcpiSpbI2c,
    PepAcpiSpbSpi,
    PepAcpiSpbUart,
    PepAcpiExtendedMemory,
    PepAcpiExtendedIo
}PEP_ACPI_RESOURCE_TYPE, * PPEP_ACPI_RESOURCE_TYPE;

typedef struct _PEP_ABANDON_DEVICE{
    PCUNICODE_STRING DeviceId;
    BOOLEAN          DeviceAccepted;
}PEP_ABANDON_DEVICE, * PPEP_ABANDON_DEVICE;


typedef struct _PEP_ACPI_ABANDON_DEVICE{
    PCUNICODE_STRING AcpiDeviceName;
    BOOLEAN          DeviceAccepted;
}PEP_ACPI_ABANDON_DEVICE, * PPEP_ACPI_ABANDON_DEVICE;

typedef struct _PEP_ACPI_ENUMERATE_DEVICE_NAMESPACE{
    PEPHANDLE                       DeviceHandle;
    ULONG                           RequestFlags;
    LOUSTATUS                       Status;
    ULONG                           ObjectCount;
    SIZE_T                          ObjectBufferSize;
    PEP_ACPI_OBJECT_NAME_WITH_TYPE* Objects;
}PEP_ACPI_ENUMERATE_DEVICE_NAMESPACE, * PPEP_ACPI_ENUMERATE_DEVICE_NAMESPACE;

typedef struct _PEP_ACPI_BUILD_CHILDREN_CONTROL_METHOD{
    PEPHANDLE             DeviceHandle;
    ULONG                 RequestFlags;
    union {
        ULONG             MethodName;
        ANSI_STRING       MethodNameString;
    };
    LOUSTATUS             MethodStatus;
    PVOID                 CompletionContext;
    ULONG                 InputArgumentCount;
    SIZE_T                InputArgumentSize;
    PACPI_METHOD_ARGUMENT InputArguments;
    ULONG                 OutputArgumentCount;
    SIZE_T                OutputArgumentSize;
    PACPI_METHOD_ARGUMENT OutputArguments;
}PEP_ACPI_BUILD_CHILDREN_CONTROL_METHOD, * PPEP_ACPI_BUILD_CHILDREN_CONTROL_METHOD;

typedef struct _PEP_ACPI_EXTENDED_ADDRESS{
    PEP_ACPI_RESOURCE_TYPE  Type;
    PEP_ACPI_RESOURCE_FLAGS Flags;
    UCHAR                   ResourceFlags;
    UCHAR                   GeneralFlags;
    UCHAR                   TypeSpecificFlags;
    UCHAR                   RevisionId;
    UCHAR                   Reserved;
    ULONGLONG               Granularity;
    ULONGLONG               MinimumAddress;
    ULONGLONG               MaximumAddress;
    ULONGLONG               TranslationAddress;
    ULONGLONG               AddressLength;
    ULONGLONG               TypeAttribute;
    PUNICODE_STRING         DescriptorName;
} PEP_ACPI_EXTENDED_ADDRESS, * PPEP_ACPI_EXTENDED_ADDRESS;

typedef struct _PEP_ACPI_GPIO_RESOURCE{
    PEP_ACPI_RESOURCE_TYPE      Type;
    PEP_ACPI_RESOURCE_FLAGS     Flags;
    KINTERRUPT_MODE             InterruptType;
    KINTERRUPT_POLARITY         InterruptPolarity;
    GPIO_PIN_CONFIG_TYPE        PinConfig;
    GPIO_PIN_IORESTRICTION_TYPE IoRestrictionType;
    USHORT                      DriveStrength;
    USHORT                      DebounceTimeout;
    PUSHORT                     PinTable;
    USHORT                      PinCount;
    UCHAR                       ResourceSourceIndex;
    PUNICODE_STRING             ResourceSourceName;
    PUCHAR                      VendorData;
    USHORT                      VendorDataLength;
} PEP_ACPI_GPIO_RESOURCE, * PPEP_ACPI_GPIO_RESOURCE;

typedef struct _PEP_ACPI_INTERRUPT_RESOURCE{
    PEP_ACPI_RESOURCE_TYPE  Type;
    KINTERRUPT_MODE         InterruptType;
    KINTERRUPT_POLARITY     InterruptPolarity;
    PEP_ACPI_RESOURCE_FLAGS Flags;
    UCHAR                   Count;
    PULONG                  Pins;
} PEP_ACPI_INTERRUPT_RESOURCE, * PPEP_ACPI_INTERRUPT_RESOURCE;

typedef struct _PEP_ACPI_IO_MEMORY_RESOURCE{
    PEP_ACPI_RESOURCE_TYPE Type;
    UCHAR                  Information;
    PHYSICAL_ADDRESS       MinimumAddress;
    PHYSICAL_ADDRESS       MaximumAddress;
    ULONG                  Alignment;
    ULONG                  Length;
}PEP_ACPI_IO_MEMORY_RESOURCE, * PPEP_ACPI_IO_MEMORY_RESOURCE;

typedef struct _PEP_ACPI_PREPARE_DEVICE{
    PCUNICODE_STRING AcpiDeviceName;
    ULONG            InputFlags;
    BOOLEAN          DeviceAccepted;
    ULONG            OutputFlags;
}PEP_ACPI_PREPARE_DEVICE, * PPEP_ACPI_PREPARE_DEVICE;


typedef struct _PEP_ACPI_QUERY_DEVICE_CONTROL_RESOURCES {
    PEPHANDLE               DeviceHandle;
    ULONG                   RequestFlags;
    LOUSTATUS               Status;
    SIZE_T                  BiosResourcesSize;
    ACPI_METHOD_ARGUMENT*   BiosResources;
}PEP_ACPI_QUERY_DEVICE_CONTROL_RESOURCES, * PPEP_ACPI_QUERY_DEVICE_CONTROL_RESOURCES;

typedef struct _PEP_ACPI_QUERY_OBJECT_INFORMATION{
    PEPHANDLE               DeviceHandle;
    PEP_ACPI_OBJECT_NAME    Name;
    PEP_ACPI_OBJECT_TYPE    Type;
    ULONG                   ObjectFlags;
    union {
        struct {
            ULONG           InputArgumentCount;
            ULONG           OutputArgumentCount;
        }                   MethodObject;
    };
}PEP_ACPI_QUERY_OBJECT_INFORMATION, * PPEP_ACPI_QUERY_OBJECT_INFORMATION;

typedef struct _PEP_ACPI_REGISTER_DEVICE{
    PCUNICODE_STRING AcpiDeviceName;
    ULONG            InputFlags;
    POHANDLE         KernelHandle;
    PEPHANDLE        DeviceHandle;
    ULONG            OutputFlags;
}PEP_ACPI_REGISTER_DEVICE, * PPEP_ACPI_REGISTER_DEVICE;

typedef struct _PEP_ACPI_SPB_RESOURCE{
    PEP_ACPI_RESOURCE_TYPE  Type;
    PEP_ACPI_RESOURCE_FLAGS Flags;
    USHORT                  TypeSpecificFlags;
    UCHAR                   ResourceSourceIndex;
    PUNICODE_STRING         ResourceSourceName;
    PCHAR                   VendorData;
    USHORT                  VendorDataLength;
}PEP_ACPI_SPB_RESOURCE, * PPEP_ACPI_SPB_RESOURCE;

typedef struct _PEP_ACPI_SPB_I2C_RESOURCE{
    PEP_ACPI_SPB_RESOURCE SpbCommon;
    ULONG                 ConnectionSpeed;
    USHORT                SlaveAddress;
}PEP_ACPI_SPB_I2C_RESOURCE, * PPEP_ACPI_SPB_I2C_RESOURCE;


typedef struct _PEP_ACPI_SPB_SPI_RESOURCE{
    PEP_ACPI_SPB_RESOURCE SpbCommon;
    ULONG                 ConnectionSpeed;
    UCHAR                 DataBitLength;
    UCHAR                 Phase;
    UCHAR                 Polarity;
    USHORT                DeviceSelection;
}PEP_ACPI_SPB_SPI_RESOURCE, * PPEP_ACPI_SPB_SPI_RESOURCE;

typedef struct _PEP_ACPI_SPB_UART_RESOURCE{
    PEP_ACPI_SPB_RESOURCE SpbCommon;
    ULONG                 BaudRate;
    USHORT                RxBufferSize;
    USHORT                TxBufferSize;
    UCHAR                 Parity;
    UCHAR                 LinesInUse;
}PEP_ACPI_SPB_UART_RESOURCE, * PPEP_ACPI_SPB_UART_RESOURCE;


typedef union _PEP_ACPI_RESOURCE{
    PEP_ACPI_RESOURCE_TYPE      Type;
    PEP_ACPI_IO_MEMORY_RESOURCE IoMemory;
    PEP_ACPI_INTERRUPT_RESOURCE Interrupt;
    PEP_ACPI_GPIO_RESOURCE      Gpio;
    PEP_ACPI_SPB_I2C_RESOURCE   SpbI2c;
    PEP_ACPI_SPB_SPI_RESOURCE   SpbSpi;
    PEP_ACPI_SPB_UART_RESOURCE  SpbUart;
    PEP_ACPI_EXTENDED_ADDRESS   ExtendedAddress;
}PEP_ACPI_RESOURCE, * PPEP_ACPI_RESOURCE;

typedef struct _PEP_PROCESSOR_IDLE_DEPENDENCY{
    POHANDLE TargetProcessor;
    UCHAR    ExpectedState;
    BOOLEAN  AllowDeeperStates;
    BOOLEAN  LooseDependency;
}PEP_PROCESSOR_IDLE_DEPENDENCY, * PPEP_PROCESSOR_IDLE_DEPENDENCY;


typedef struct _PEP_ACPI_REQUEST_CONVERT_TO_BIOS_RESOURCES{
    LOUSTATUS           TranslationStatus;
    PPEP_ACPI_RESOURCE  InputBuffer;
    SIZE_T              InputBufferSize;
    PVOID               OutputBuffer;
    SIZE_T              OutputBufferSize;
    ULONG               Flags;
}PEP_ACPI_REQUEST_CONVERT_TO_BIOS_RESOURCES, * PPEP_ACPI_REQUEST_CONVERT_TO_BIOS_RESOURCES;

typedef struct _PEP_PERF_STATE{
    ULONGLONG           Value;
    PVOID               Context;
}PEP_PERF_STATE, * PPEP_PERF_STATE;

typedef struct _PEP_ACPI_TRANSLATED_DEVICE_CONTROL_RESOURCES{
    PEPHANDLE           DeviceHandle;
    ULONG               RequestFlags;
    LOUSTATUS           Status;
    SIZE_T              TranslatedResourcesSize;
    PCM_RESOURCE_LIST   TranslatedResources;
}PEP_ACPI_TRANSLATED_DEVICE_CONTROL_RESOURCES, * PPEP_ACPI_TRANSLATED_DEVICE_CONTROL_RESOURCES;

typedef struct _PEP_ACPI_UNREGISTER_DEVICE{
   PEPHANDLE DeviceHandle;
   ULONG     InputFlags;
}PEP_ACPI_UNREGISTER_DEVICE, * PPEP_ACPI_UNREGISTER_DEVICE;

typedef struct _PEP_COMPONENT_PERF_SET{
    UNICODE_STRING              Name;
    ULONGLONG                   Flags;
    PEP_PERF_STATE_UNIT         Unit;
    PEP_PERF_STATE_TYPE         Type;
    union{
        struct{
            ULONG               Count;
            PPEP_PERF_STATE     States;
        }Discrete;
        struct{
            ULONGLONG           Minimum;
            ULONGLONG           Maximum;
        }                       Range;
    };
}PEP_COMPONENT_PERF_SET, * PPEP_COMPONENT_PERF_SET;

typedef struct _PEP_COMPONENT_PERF_INFO{
    ULONG                   SetCount;
    PPEP_COMPONENT_PERF_SET PerfStateSets;
} PEP_COMPONENT_PERF_INFO, * PPEP_COMPONENT_PERF_INFO;

typedef struct _PEP_COMPONENT_PERF_STATE_REQUEST{
    ULONG           Set;
    union{
        ULONG       StateIndex;
        ULONGLONG   StateValue;
    };
}PEP_COMPONENT_PERF_STATE_REQUEST, * PPEP_COMPONENT_PERF_STATE_REQUEST;

typedef struct _PEP_COMPONENT_PLATFORM_CONSTRAINTS{
    PEPHANDLE DeviceHandle;
    ULONG     Component;
    PULONG    MinimumFStates;
    ULONG     PlatformStateCount;
}PEP_COMPONENT_PLATFORM_CONSTRAINTS, * PPEP_COMPONENT_PLATFORM_CONSTRAINTS;

typedef struct _PEP_COMPONENT_V2{
  GUID                        Id;
  ULONGLONG                   Flags;
  ULONG                       DeepestWakeableIdleState;
  ULONG                       IdleStateCount;
  PPO_FX_COMPONENT_IDLE_STATE IdleStates;
}PEP_COMPONENT_V2, * PPEP_COMPONENT_V2;

typedef struct _PEP_COORDINATED_DEPENDENCY_OPTION{
    UCHAR       ExpectedStateIndex;
    BOOLEAN     LooseDependency;
    BOOLEAN     InitiatingState;
    BOOLEAN     DependentState;
}PEP_COORDINATED_DEPENDENCY_OPTION, * PPEP_COORDINATED_DEPENDENCY_OPTION;

typedef struct _PEP_COORDINATED_IDLE_STATE {
    ULONG   Latency;
    ULONG   BreakEvenDuration;
    ULONG   DependencyCount;
    ULONG   MaximumDependencySize;
} PEP_COORDINATED_IDLE_STATE, *PPEP_COORDINATED_IDLE_STATE;

typedef struct _PEP_DEVICE_PLATFORM_CONSTRAINTS{
    PEPHANDLE               DeviceHandle;
    PDEVICE_POWER_STATE     MinimumDStates;
    ULONG                   PlatformStateCount;
} PEP_DEVICE_PLATFORM_CONSTRAINTS, *PPEP_DEVICE_PLATFORM_CONSTRAINTS;

typedef struct _PEP_DEVICE_POWER_STATE{
    PEPHANDLE               DeviceHandle;
    DEVICE_POWER_STATE      PowerState;
    BOOLEAN                 Complete;
    BOOLEAN                 SystemTransition;
}PEP_DEVICE_POWER_STATE, * PPEP_DEVICE_POWER_STATE;

typedef struct _PEP_DEVICE_REGISTER_V2{
    ULONGLONG             Flags;
    ULONG                 ComponentCount;
    PPEP_COMPONENT_V2*    Components;
}PEP_DEVICE_REGISTER_V2, * PPEP_DEVICE_REGISTER_V2;

typedef struct _PEP_DEVICE_STARTED{
    PEPHANDLE   DeviceHandle;
}PEP_DEVICE_STARTED, *PPEP_DEVICE_STARTED;

typedef struct _PEP_INFORMATION{
    USHORT                  Version;
    USHORT                  Size;
    PPEPCALLBACKNOTIFYDPM   AcceptDeviceNotification;
    PPEPCALLBACKNOTIFYPPM   AcceptProcessorNotification;
    PPEPCALLBACKNOTIFYACPI  AcceptAcpiNotification;
} PEP_INFORMATION, *PPEP_INFORMATION;


typedef struct _PEP_LOW_POWER_EPOCH{
    BOOLEAN   LowPowerEpoch;
}PEP_LOW_POWER_EPOCH, * PPEP_LOW_POWER_EPOCH;

typedef struct _PEP_NOTIFY_COMPONENT_IDLE_STATE{
    PEPHANDLE DeviceHandle;
    ULONG     Component;
    ULONG     IdleState;
    BOOLEAN   DriverNotified;
    BOOLEAN   Completed;
} PEP_NOTIFY_COMPONENT_IDLE_STATE, * PPEP_NOTIFY_COMPONENT_IDLE_STATE;


typedef struct _PEP_PLATFORM_IDLE_STATE{
    POHANDLE                        InitiatingProcessor;
    UCHAR                           InitiatingState;
    ULONG                           Latency;
    ULONG                           BreakEvenDuration;
    ULONG                           DependencyArrayUsed;
    ULONG                           DependencyArrayCount;
    PEP_PROCESSOR_IDLE_DEPENDENCY*  DependencyArray;
} PEP_PLATFORM_IDLE_STATE, *PPEP_PLATFORM_IDLE_STATE;

typedef struct _PEP_POWER_CONTROL_COMPLETE {
    PEPHANDLE   DeviceHandle;
    LPCGUID     PowerControlCode;
    PVOID       RequestContext;
    SIZE_T      BytesReturned;
    LOUSTATUS   Status;
} PEP_POWER_CONTROL_COMPLETE, *PPEP_POWER_CONTROL_COMPLETE;

typedef struct _PEP_POWER_CONTROL_REQUEST{
    PEPHANDLE   DeviceHandle;
    LPCGUID     PowerControlCode;
    PVOID       InBuffer;
    SIZE_T      InBufferSize;
    PVOID       OutBuffer;
    SIZE_T      OutBufferSize;
    SIZE_T      BytesReturned;
    LOUSTATUS   Status;
} PEP_POWER_CONTROL_REQUEST, * PPEP_POWER_CONTROL_REQUEST;

typedef struct _PEP_PPM_CONTEXT_QUERY_PARKING_PAGE{
    PHYSICAL_ADDRESS PhysicalPageAddress;
    PVOID            VirtualPageAddress;
} PEP_PPM_CONTEXT_QUERY_PARKING_PAGE, * PPEP_PPM_CONTEXT_QUERY_PARKING_PAGE;

typedef struct _PEP_PPM_CST_STATE{
    UCHAR               Type;
    USHORT              Latency;
    ULONG               Power;
    UCHAR               AddressSpaceId;
    UCHAR               BitWidth;
    UCHAR               BitOffset;
    UCHAR               AccessSize;
    PHYSICAL_ADDRESS    Address;
}PEP_PPM_CST_STATE, * PPEP_PPM_CST_STATE;

typedef struct _PEP_PPM_CST_STATES{
    ULONG               Count;
    PPEP_PPM_CST_STATE  IdleStates;
} PEP_PPM_CST_STATES, * PPEP_PPM_CST_STATES;

typedef struct _PEP_PPM_ENTER_SYSTEM_STATE{
    SYSTEM_POWER_STATE  TargetState;
}PEP_PPM_ENTER_SYSTEM_STATE, * PPEP_PPM_ENTER_SYSTEM_STATE;

typedef struct _PEP_PPM_FEEDBACK_READ{
  ULONG         CounterIndex;
  union {
    ULONG64     InstantaneousValue;
    struct {
      ULONG64   NominalCount;
      ULONG64   ActualCount;
    };
  };
}PEP_PPM_FEEDBACK_READ, * PPEP_PPM_FEEDBACK_READ;

typedef struct _PEP_PPM_IDLE_CANCEL{
   PEP_PROCESSOR_IDLE_CANCEL_CODE   CancelCode;
}PEP_PPM_IDLE_CANCEL, * PPEP_PPM_IDLE_CANCEL;

typedef struct _PEP_PPM_IDLE_COMPLETE{
   ULONG ProcessorState;
   ULONG PlatformState;
}PEP_PPM_IDLE_COMPLETE, * PPEP_PPM_IDLE_COMPLETE;

typedef struct _PEP_PPM_IDLE_COMPLETE_V2{
    ULONG   ProcessorState;
    ULONG   PlatformState;
    ULONG   CoordinatedStateCount;
    PULONG  CoordinatedStates;
}PEP_PPM_IDLE_COMPLETE_V2, * PPEP_PPM_IDLE_COMPLETE_V2;

typedef struct _PEP_PPM_IDLE_EXECUTE{
    LOUSTATUS   Status;
    ULONG       ProcessorState;
    ULONG       PlatformState;
}PEP_PPM_IDLE_EXECUTE, * PPEP_PPM_IDLE_EXECUTE;

typedef struct _PEP_PPM_IDLE_EXECUTE_V2{
    LOUSTATUS   Status;
    ULONG       ProcessorState;
    ULONG       PlatformState;
    ULONG       CoordinatedStateCount;
    PULONG      CoordinatedStates;
} PEP_PPM_IDLE_EXECUTE_V2, *PPEP_PPM_IDLE_EXECUTE_V2;

typedef struct _PEP_PROCESSOR_FEEDBACK_COUNTER{
    struct {
        ULONG   Affinitized     : 1;
        ULONG   Type            : 2;
        ULONG   Counter         : 4;
        ULONG   DiscountIdle    : 1;
        ULONG   Reserved        : 24;
    };
    ULONG       NominalRate;
}PEP_PROCESSOR_FEEDBACK_COUNTER, * PPEP_PROCESSOR_FEEDBACK_COUNTER;

typedef struct _PEP_PROCESSOR_PERF_STATE{
    ULONG   Performance;
    ULONG   Frequency;
    ULONG   Reserved[4];
}PEP_PROCESSOR_PERF_STATE, * PPEP_PROCESSOR_PERF_STATE;



#ifdef __cplusplus
}
#endif
#endif