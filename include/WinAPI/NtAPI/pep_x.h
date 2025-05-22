
#ifndef PEPX_HEADER
#define PEPX_HEADER
#pragma once

#include <NtAPI.h>

typedef struct _PO_FX_CORE_DEVICE {
    ULONG                                         Version;
    ULONG                                         ComponentCount;
    PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK    ComponentActiveConditionCallback;
    PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK      ComponentIdleConditionCallback;
    PPO_FX_COMPONENT_CRITICAL_TRANSITION_CALLBACK ComponentCriticalTransitionCallback;
    PPO_FX_COMPONENT_IDLE_STATE_CALLBACK          ComponentIdleStateCallback;
    PVOID                                         DeviceContext;
    PO_FX_COMPONENT* Components;
} PO_FX_CORE_DEVICE, * PPO_FX_CORE_DEVICE;

typedef enum _GPIO_PIN_CONFIG_TYPE {
  PullDefault,
  PullUp,
  PullDown,
  PullNone
} GPIO_PIN_CONFIG_TYPE;

typedef enum _GPIO_PIN_IORESTRICTION_TYPE {
  IoRestrictionNone,
  IoRestrictionInputOnly,
  IoRestrictionOutputOnly,
  IoRestrictionNoneAndPreserve
} GPIO_PIN_IORESTRICTION_TYPE;

typedef enum {
    PepIdleCancelWorkPending,
    PepIdleCancelDependencyCheckFailed,
    PepIdleCancelNoCState,
    PepIdleCancelMax
} PEP_PROCESSOR_IDLE_CANCEL_CODE, * PPEP_PROCESSOR_IDLE_CANCEL_CODE;

typedef enum _PEP_DEVICE_ACCEPTANCE_TYPE {
    PepDeviceNotAccepted,
    PepDeviceAccepted,
    PepDeviceAceptedMax
} PEP_DEVICE_ACCEPTANCE_TYPE, * PPEP_DEVICE_ACCEPTANCE_TYPE;

typedef enum _PEP_WORK_TYPE {
    PepWorkRequestPowerControl,
    PepWorkCompleteIdleState,
    PepWorkCompletePerfState,
    PepWorkAcpiNotify,
    PepWorkAcpiBUILD_CHILDRENControlMethodComplete,
    PepWorkMax
} PEP_WORK_TYPE, * PPEP_WORK_TYPE;

typedef enum {
    PepIdleTypeProcessor,
    PepIdleTypePlatform,
    PepIdleTypeMax
} PEP_PROCESSOR_IDLE_TYPE, * PPEP_PROCESSOR_IDLE_TYPE;


typedef union _PEP_ACPI_OBJECT_NAME {
    UCHAR Name[4];
    ULONG NameAsUlong;
} PEP_ACPI_OBJECT_NAME, * PPEP_ACPI_OBJECT_NAME;

typedef enum _PEP_ACPI_OBJECT_TYPE {
    PepAcpiObjectTypeMethod,
    PepAcpiObjectTypeDevice,
    PepAcpiObjectTypeMaximum
} PEP_ACPI_OBJECT_TYPE, * PPEP_ACPI_OBJECT_TYPE;

typedef struct _PEP_ACPI_OBJECT_NAME_WITH_TYPE {
    PEP_ACPI_OBJECT_NAME Name;
    PEP_ACPI_OBJECT_TYPE Type;
} PEP_ACPI_OBJECT_NAME_WITH_TYPE, * PPEP_ACPI_OBJECT_NAME_WITH_TYPE;

typedef union _PEP_ACPI_RESOURCE_FLAGS {
    ULONG  AsULong;
    struct {
        ULONG Shared : 1;
        ULONG Wake : 1;
        ULONG ResourceUsage : 1;
        ULONG SlaveMode : 1;
        ULONG AddressingMode : 1;
        ULONG SharedMode : 1;
        ULONG Reserved : 26;
    } DUMMYSTRUCTNAME;
} PEP_ACPI_RESOURCE_FLAGS, * PPEP_ACPI_RESOURCE_FLAGS;

typedef enum _PEP_PERF_STATE_TYPE {
    PepPerfStateTypeDiscrete,
    PepPerfStateTypeRange,
    PepPerfStateTypeMax
} PEP_PERF_STATE_TYPE, * PPEP_PERF_STATE_TYPE;

typedef enum _PEP_PERF_STATE_UNIT {
    PepPerfStateUnitOther,
    PepPerfStateUnitFrequency,
    PepPerfStateUnitBandwidth,
    PepPerfStateUnitMax
} PEP_PERF_STATE_UNIT, * PPEP_PERF_STATE_UNIT;

typedef enum _PEP_ACPI_RESOURCE_TYPE {
    PepAcpiMemory,
    PepAcpiIoPort,
    PepAcpiInterrupt,
    PepAcpiGpioIo,
    PepAcpiGpioInt,
    PepAcpiSpbI2c,
    PepAcpiSpbSpi,
    PepAcpiSpbUart,
    PepAcpiExtendedMemory,
    PepAcpiExtendedIo
} PEP_ACPI_RESOURCE_TYPE;

typedef struct _PEP_ABANDON_DEVICE {
    PCUNICODE_STRING DeviceId;
   BOOLEAN          DeviceAccepted;
} PEP_ABANDON_DEVICE, *PPEP_ABANDON_DEVICE;

typedef struct _PEP_ACPI_ABANDON_DEVICE {
    PCUNICODE_STRING AcpiDeviceName;
   BOOLEAN          DeviceAccepted;
} PEP_ACPI_ABANDON_DEVICE, *PPEP_ACPI_ABANDON_DEVICE;

typedef struct _PEP_ACPI_ENUMERATE_DEVICE_NAMESPACE {
  PEPHANDLE                      DeviceHandle;
  ULONG                          RequestFlags;
  NTSTATUS                       Status;
  ULONG                          ObjectCount;
  SIZE_T                         ObjectBufferSize;
  PEP_ACPI_OBJECT_NAME_WITH_TYPE* Objects;
} PEP_ACPI_ENUMERATE_DEVICE_NAMESPACE, *PPEP_ACPI_ENUMERATE_DEVICE_NAMESPACE;


typedef struct _PEP_ACPI_BUILD_CHILDREN_CONTROL_METHOD {
  PEPHANDLE             DeviceHandle;
  ULONG                 RequestFlags;
  union {
    ULONG       MethodName;
    ANSI_STRING MethodNameString;
  };
  NTSTATUS              MethodStatus;
  PVOID                 CompletionContext;
  ULONG                 InputArgumentCount;
  SIZE_T                InputArgumentSize;
  PACPI_METHOD_ARGUMENT InputArguments;
  ULONG                 OutputArgumentCount;
  SIZE_T                OutputArgumentSize;
  PACPI_METHOD_ARGUMENT OutputArguments;
} PEP_ACPI_BUILD_CHILDREN_CONTROL_METHOD, *PPEP_ACPI_BUILD_CHILDREN_CONTROL_METHOD;


typedef struct _PEP_ACPI_EXTENDED_ADDRESS {
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
} PEP_ACPI_EXTENDED_ADDRESS, *PPEP_ACPI_EXTENDED_ADDRESS;

typedef struct _PEP_ACPI_GPIO_RESOURCE {
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
} PEP_ACPI_GPIO_RESOURCE, *PPEP_ACPI_GPIO_RESOURCE;


typedef struct _PEP_ACPI_INTERRUPT_RESOURCE {
  PEP_ACPI_RESOURCE_TYPE  Type;
  KINTERRUPT_MODE         InterruptType;
  KINTERRUPT_POLARITY     InterruptPolarity;
  PEP_ACPI_RESOURCE_FLAGS Flags;
  UCHAR                   Count;
  PULONG                  Pins;
} PEP_ACPI_INTERRUPT_RESOURCE, *PPEP_ACPI_INTERRUPT_RESOURCE;

typedef struct _PEP_ACPI_IO_MEMORY_RESOURCE {
  PEP_ACPI_RESOURCE_TYPE Type;
  UCHAR                  Information;
  PHYSICAL_ADDRESS       MinimumAddress;
  PHYSICAL_ADDRESS       MaximumAddress;
  ULONG                  Alignment;
  ULONG                  Length;
} PEP_ACPI_IO_MEMORY_RESOURCE, *PPEP_ACPI_IO_MEMORY_RESOURCE;



typedef struct _PEP_ACPI_PREPARE_DEVICE {
    PCUNICODE_STRING AcpiDeviceName;
    ULONG            InputFlags;
   BOOLEAN          DeviceAccepted;
   ULONG            OutputFlags;
} PEP_ACPI_PREPARE_DEVICE, *PPEP_ACPI_PREPARE_DEVICE;


typedef struct _PEP_ACPI_QUERY_DEVICE_CONTROL_RESOURCES {
        PEPHANDLE            DeviceHandle;
        ULONG                RequestFlags;
       NTSTATUS             Status;
    SIZE_T               BiosResourcesSize;
            ACPI_METHOD_ARGUMENT* BiosResources;
} PEP_ACPI_QUERY_DEVICE_CONTROL_RESOURCES, *PPEP_ACPI_QUERY_DEVICE_CONTROL_RESOURCES;


typedef struct _PEP_ACPI_QUERY_OBJECT_INFORMATION {
    PEPHANDLE            DeviceHandle;
    PEP_ACPI_OBJECT_NAME Name;
    PEP_ACPI_OBJECT_TYPE Type;
    ULONG                ObjectFlags;
  union {
    struct {
      ULONG InputArgumentCount;
      ULONG OutputArgumentCount;
    } MethodObject;
  } DUMMYUNIONNAME;
} PEP_ACPI_QUERY_OBJECT_INFORMATION, *PPEP_ACPI_QUERY_OBJECT_INFORMATION;

typedef struct _PEP_ACPI_REGISTER_DEVICE {
    PCUNICODE_STRING AcpiDeviceName;
    ULONG            InputFlags;
    POHANDLE         KernelHandle;
   PEPHANDLE        DeviceHandle;
   ULONG            OutputFlags;
} PEP_ACPI_REGISTER_DEVICE, *PPEP_ACPI_REGISTER_DEVICE;


typedef struct _PEP_ACPI_SPB_RESOURCE {
    PEP_ACPI_RESOURCE_TYPE  Type;
    PEP_ACPI_RESOURCE_FLAGS Flags;
    USHORT                  TypeSpecificFlags;
    UCHAR                   ResourceSourceIndex;
    PUNICODE_STRING         ResourceSourceName;
    PCHAR                   VendorData;
    USHORT                  VendorDataLength;
} PEP_ACPI_SPB_RESOURCE, * PPEP_ACPI_SPB_RESOURCE;

typedef struct _PEP_ACPI_SPB_I2C_RESOURCE {
    PEP_ACPI_SPB_RESOURCE SpbCommon;
    ULONG                 ConnectionSpeed;
    USHORT                SlaveAddress;
} PEP_ACPI_SPB_I2C_RESOURCE, * PPEP_ACPI_SPB_I2C_RESOURCE;


typedef struct _PEP_ACPI_SPB_SPI_RESOURCE {
    PEP_ACPI_SPB_RESOURCE SpbCommon;
    ULONG                 ConnectionSpeed;
    UCHAR                 DataBitLength;
    UCHAR                 Phase;
    UCHAR                 Polarity;
    USHORT                DeviceSelection;
} PEP_ACPI_SPB_SPI_RESOURCE, * PPEP_ACPI_SPB_SPI_RESOURCE;

typedef struct _PEP_ACPI_SPB_UART_RESOURCE {
    PEP_ACPI_SPB_RESOURCE SpbCommon;
    ULONG                 BaudRate;
    USHORT                RxBufferSize;
    USHORT                TxBufferSize;
    UCHAR                 Parity;
    UCHAR                 LinesInUse;
} PEP_ACPI_SPB_UART_RESOURCE, * PPEP_ACPI_SPB_UART_RESOURCE;


typedef union _PEP_ACPI_RESOURCE {
  PEP_ACPI_RESOURCE_TYPE      Type;
  PEP_ACPI_IO_MEMORY_RESOURCE IoMemory;
  PEP_ACPI_INTERRUPT_RESOURCE Interrupt;
  PEP_ACPI_GPIO_RESOURCE      Gpio;
  PEP_ACPI_SPB_I2C_RESOURCE   SpbI2c;
  PEP_ACPI_SPB_SPI_RESOURCE   SpbSpi;
  PEP_ACPI_SPB_UART_RESOURCE  SpbUart;
  PEP_ACPI_EXTENDED_ADDRESS   ExtendedAddress;
} PEP_ACPI_RESOURCE, *PPEP_ACPI_RESOURCE;

/// <summary>
/// /
/// </summary>
typedef struct _PEP_PROCESSOR_IDLE_DEPENDENCY {
    POHANDLE TargetProcessor;
    UCHAR    ExpectedState;
    BOOLEAN  AllowDeeperStates;
    BOOLEAN  LooseDependency;
} PEP_PROCESSOR_IDLE_DEPENDENCY, * PPEP_PROCESSOR_IDLE_DEPENDENCY;


typedef struct _PEP_ACPI_REQUEST_CONVERT_TO_BIOS_RESOURCES {
    NTSTATUS           TranslationStatus;
    PPEP_ACPI_RESOURCE InputBuffer;
    SIZE_T             InputBufferSize;
    PVOID              OutputBuffer;
    SIZE_T             OutputBufferSize;
    ULONG              Flags;
} PEP_ACPI_REQUEST_CONVERT_TO_BIOS_RESOURCES, * PPEP_ACPI_REQUEST_CONVERT_TO_BIOS_RESOURCES;

typedef struct _PEP_PERF_STATE {
    ULONGLONG Value;
    PVOID     Context;
} PEP_PERF_STATE, * PPEP_PERF_STATE;





typedef struct _PEP_ACPI_TRANSLATED_DEVICE_CONTROL_RESOURCES {
  PEPHANDLE         DeviceHandle;
  ULONG             RequestFlags;
  NTSTATUS          Status;
  SIZE_T            TranslatedResourcesSize;
  PCM_RESOURCE_LIST TranslatedResources;
} PEP_ACPI_TRANSLATED_DEVICE_CONTROL_RESOURCES, *PPEP_ACPI_TRANSLATED_DEVICE_CONTROL_RESOURCES;

typedef struct _PEP_ACPI_UNREGISTER_DEVICE {
   PEPHANDLE DeviceHandle;
   ULONG     InputFlags;
} PEP_ACPI_UNREGISTER_DEVICE, *PPEP_ACPI_UNREGISTER_DEVICE;




typedef struct _PEP_COMPONENT_PERF_SET {
  UNICODE_STRING      Name;
  ULONGLONG           Flags;
  PEP_PERF_STATE_UNIT Unit;
  PEP_PERF_STATE_TYPE Type;
  union {
    struct {
      ULONG           Count;
      PPEP_PERF_STATE States;
    } Discrete;
    struct {
      ULONGLONG Minimum;
      ULONGLONG Maximum;
    } Range;
  };
} PEP_COMPONENT_PERF_SET, *PPEP_COMPONENT_PERF_SET;


typedef struct _PEP_COMPONENT_PERF_INFO {
    ULONG                  SetCount;
    PEP_COMPONENT_PERF_SET* PerfStateSets;
} PEP_COMPONENT_PERF_INFO, * PPEP_COMPONENT_PERF_INFO;


typedef struct _PEP_COMPONENT_PERF_STATE_REQUEST {
  ULONG Set;
  union {
    ULONG     StateIndex;
    ULONGLONG StateValue;
  };
} PEP_COMPONENT_PERF_STATE_REQUEST, *PPEP_COMPONENT_PERF_STATE_REQUEST;

typedef struct _PEP_COMPONENT_PLATFORM_CONSTRAINTS {
   PEPHANDLE DeviceHandle;
   ULONG     Component;
   PULONG    MinimumFStates;
   ULONG     PlatformStateCount;
} PEP_COMPONENT_PLATFORM_CONSTRAINTS, *PPEP_COMPONENT_PLATFORM_CONSTRAINTS;

typedef struct _PEP_COMPONENT_V2 {
  GUID                        Id;
  ULONGLONG                   Flags;
  ULONG                       DeepestWakeableIdleState;
  ULONG                       IdleStateCount;
  PPO_FX_COMPONENT_IDLE_STATE IdleStates;
} PEP_COMPONENT_V2, *PPEP_COMPONENT_V2;

typedef struct _PEP_COORDINATED_DEPENDENCY_OPTION {
  UCHAR   ExpectedStateIndex;
  BOOLEAN LooseDependency;
  BOOLEAN InitiatingState;
  BOOLEAN DependentState;
} PEP_COORDINATED_DEPENDENCY_OPTION, *PPEP_COORDINATED_DEPENDENCY_OPTION;

typedef struct _PEP_COORDINATED_IDLE_STATE {
  ULONG Latency;
  ULONG BreakEvenDuration;
  ULONG DependencyCount;
  ULONG MaximumDependencySize;
} PEP_COORDINATED_IDLE_STATE, *PPEP_COORDINATED_IDLE_STATE;

typedef struct _PEP_CRASHDUMP_INFORMATION {
   PEPHANDLE DeviceHandle;
   PVOID     DeviceContext;
} PEP_CRASHDUMP_INFORMATION, *PPEP_CRASHDUMP_INFORMATION;



typedef struct _PEP_DEVICE_PLATFORM_CONSTRAINTS {
   PEPHANDLE           DeviceHandle;
   PDEVICE_POWER_STATE MinimumDStates;
   ULONG               PlatformStateCount;
} PEP_DEVICE_PLATFORM_CONSTRAINTS, *PPEP_DEVICE_PLATFORM_CONSTRAINTS;

typedef struct _PEP_DEVICE_POWER_STATE {
   PEPHANDLE          DeviceHandle;
   DEVICE_POWER_STATE PowerState;
   BOOLEAN            Complete;
   BOOLEAN            SystemTransition;
} PEP_DEVICE_POWER_STATE, *PPEP_DEVICE_POWER_STATE;

typedef struct _PEP_DEVICE_REGISTER_V2 {
  ULONGLONG         Flags;
  ULONG             ComponentCount;
  PPEP_COMPONENT_V2* Components;
} PEP_DEVICE_REGISTER_V2, *PPEP_DEVICE_REGISTER_V2;

typedef struct _PEP_DEVICE_STARTED {
   PEPHANDLE DeviceHandle;
} PEP_DEVICE_STARTED, *PPEP_DEVICE_STARTED;

typedef struct _PEP_INFORMATION {
  USHORT                 Version;
  USHORT                 Size;
  PPEPCALLBACKNOTIFYDPM  AcceptDeviceNotification;
  PPEPCALLBACKNOTIFYPPM  AcceptProcessorNotification;
  PPEPCALLBACKNOTIFYACPI AcceptAcpiNotification;
} PEP_INFORMATION, *PPEP_INFORMATION;

typedef struct _PEP_KERNEL_INFORMATION_STRUCT_V1 {
  USHORT                                   Version;
  USHORT                                   Size;
  POHANDLE                                 Plugin;
  PPOFXCALLBACKREQUESTWORKER               RequestWorker;
  PPOFXCALLBACKENUMERATEUNMASKEDINTERRUPTS EnumerateUnmaskedInterrupts;
  PPOFXCALLBACKPROCESSORHALT               ProcessorHalt;
  PPOFXCALLBACKREQUESTINTERRUPT            RequestInterrupt;
  PPOFXCALLBACKCRITICALRESOURCE            TransitionCriticalResource;
} PEP_KERNEL_INFORMATION_STRUCT_V1, *PPEP_KERNEL_INFORMATION_STRUCT_V1;

typedef struct _PEP_KERNEL_INFORMATION_STRUCT_V2 {
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
} PEP_KERNEL_INFORMATION_STRUCT_V2, *PPEP_KERNEL_INFORMATION_STRUCT_V2;

typedef struct _PEP_KERNEL_INFORMATION_STRUCT_V3 {
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
} PEP_KERNEL_INFORMATION_STRUCT_V3, *PPEP_KERNEL_INFORMATION_STRUCT_V3;

typedef struct _PEP_LOW_POWER_EPOCH {
  BOOLEAN LowPowerEpoch;
} PEP_LOW_POWER_EPOCH, *PPEP_LOW_POWER_EPOCH;

typedef struct _PEP_NOTIFY_COMPONENT_IDLE_STATE {
    PEPHANDLE DeviceHandle;
    ULONG     Component;
    ULONG     IdleState;
    BOOLEAN   DriverNotified;
   BOOLEAN   Completed;
} PEP_NOTIFY_COMPONENT_IDLE_STATE, *PPEP_NOTIFY_COMPONENT_IDLE_STATE;


typedef struct _PEP_PLATFORM_IDLE_STATE {
  POHANDLE                      InitiatingProcessor;
  UCHAR                         InitiatingState;
  ULONG                         Latency;
  ULONG                         BreakEvenDuration;
  ULONG                         DependencyArrayUsed;
  ULONG                         DependencyArrayCount;
  PEP_PROCESSOR_IDLE_DEPENDENCY* DependencyArray;
} PEP_PLATFORM_IDLE_STATE, *PPEP_PLATFORM_IDLE_STATE;

typedef struct _PEP_PLATFORM_IDLE_STATE_UPDATE {
  ULONG Version;
  ULONG Latency;
  ULONG BreakEvenDuration;
} PEP_PLATFORM_IDLE_STATE_UPDATE, *PPEP_PLATFORM_IDLE_STATE_UPDATE;

typedef struct _PEP_POWER_CONTROL_COMPLETE {
   PEPHANDLE DeviceHandle;
   LPCGUID   PowerControlCode;
   PVOID     RequestContext;
   SIZE_T    BytesReturned;
   NTSTATUS  Status;
} PEP_POWER_CONTROL_COMPLETE, *PPEP_POWER_CONTROL_COMPLETE;

typedef struct _PEP_POWER_CONTROL_REQUEST {
    PEPHANDLE DeviceHandle;
    LPCGUID   PowerControlCode;
    PVOID     InBuffer;
    SIZE_T    InBufferSize;
    PVOID     OutBuffer;
    SIZE_T    OutBufferSize;
   SIZE_T    BytesReturned;
   NTSTATUS  Status;
} PEP_POWER_CONTROL_REQUEST, *PPEP_POWER_CONTROL_REQUEST;

typedef struct _PEP_PPM_CONTEXT_QUERY_PARKING_PAGE {
  PHYSICAL_ADDRESS PhysicalPageAddress;
  PVOID            VirtualPageAddress;
} PEP_PPM_CONTEXT_QUERY_PARKING_PAGE, *PPEP_PPM_CONTEXT_QUERY_PARKING_PAGE;

typedef struct _PEP_PPM_CST_STATE {
  UCHAR            Type;
  USHORT           Latency;
  ULONG            Power;
  UCHAR            AddressSpaceId;
  UCHAR            BitWidth;
  UCHAR            BitOffset;
  UCHAR            AccessSize;
  PHYSICAL_ADDRESS Address;
} PEP_PPM_CST_STATE, *PPEP_PPM_CST_STATE;

typedef struct _PEP_PPM_CST_STATES {
  ULONG              Count;
  PPEP_PPM_CST_STATE IdleStates;
} PEP_PPM_CST_STATES, *PPEP_PPM_CST_STATES;

typedef struct _PEP_PPM_ENTER_SYSTEM_STATE {
  SYSTEM_POWER_STATE TargetState;
} PEP_PPM_ENTER_SYSTEM_STATE, *PPEP_PPM_ENTER_SYSTEM_STATE;

typedef struct _PEP_PPM_FEEDBACK_READ {
  ULONG CounterIndex;
  union {
    ULONG64 InstantaneousValue;
    struct {
      ULONG64 NominalCount;
      ULONG64 ActualCount;
    };
  };
} PEP_PPM_FEEDBACK_READ, *PPEP_PPM_FEEDBACK_READ;

typedef struct _PEP_PPM_IDLE_CANCEL {
   PEP_PROCESSOR_IDLE_CANCEL_CODE CancelCode;
} PEP_PPM_IDLE_CANCEL, *PPEP_PPM_IDLE_CANCEL;

typedef struct _PEP_PPM_IDLE_COMPLETE {
   ULONG ProcessorState;
   ULONG PlatformState;
} PEP_PPM_IDLE_COMPLETE, *PPEP_PPM_IDLE_COMPLETE;

typedef struct _PEP_PPM_IDLE_COMPLETE_V2 {
   ULONG  ProcessorState;
   ULONG  PlatformState;
       ULONG  CoordinatedStateCount;
       PULONG CoordinatedStates;
} PEP_PPM_IDLE_COMPLETE_V2, *PPEP_PPM_IDLE_COMPLETE_V2;

typedef struct _PEP_PPM_IDLE_EXECUTE {
   NTSTATUS Status;
    ULONG    ProcessorState;
    ULONG    PlatformState;
} PEP_PPM_IDLE_EXECUTE, *PPEP_PPM_IDLE_EXECUTE;

typedef struct _PEP_PPM_IDLE_EXECUTE_V2 {
   NTSTATUS Status;
    ULONG    ProcessorState;
    ULONG    PlatformState;
        ULONG    CoordinatedStateCount;
        PULONG   CoordinatedStates;
} PEP_PPM_IDLE_EXECUTE_V2, *PPEP_PPM_IDLE_EXECUTE_V2;

/// <summary>
/// 
/// </summary>

typedef struct _PEP_PROCESSOR_FEEDBACK_COUNTER {
    struct {
        ULONG Affinitized : 1;
        ULONG Type : 2;
        ULONG Counter : 4;
        ULONG DiscountIdle : 1;
        ULONG Reserved : 24;
    };
    ULONG  NominalRate;
} PEP_PROCESSOR_FEEDBACK_COUNTER, * PPEP_PROCESSOR_FEEDBACK_COUNTER;

typedef struct _PEP_PROCESSOR_PERF_STATE {
    ULONG Performance;
    ULONG Frequency;
    ULONG Reserved[4];
} PEP_PROCESSOR_PERF_STATE, * PPEP_PROCESSOR_PERF_STATE;

typedef struct _PEP_PPM_PLATFORM_STATE_RESIDENCY {
    ULONG64 Residency;
    ULONG64 TransitionCount;
} PEP_PPM_PLATFORM_STATE_RESIDENCY, * PPEP_PPM_PLATFORM_STATE_RESIDENCY;


typedef struct _PEP_PROCESSOR_PARK_PREFERENCE {
    PEPHANDLE Processor;
    UCHAR     PoPreference;
    UCHAR     PepPreference;
} PEP_PROCESSOR_PARK_PREFERENCE, * PPEP_PROCESSOR_PARK_PREFERENCE;


typedef struct _PEP_PROCESSOR_PARK_STATE {
    PEPHANDLE Processor;
    BOOLEAN   Parked;
    UCHAR     Reserved[3];
} PEP_PROCESSOR_PARK_STATE, * PPEP_PROCESSOR_PARK_STATE;


typedef struct _PEP_PROCESSOR_IDLE_CONSTRAINTS {
    ULONGLONG               IdleDuration;
    BOOLEAN                 Interruptible;
    PEP_PROCESSOR_IDLE_TYPE Type;
} PEP_PROCESSOR_IDLE_CONSTRAINTS, * PPEP_PROCESSOR_IDLE_CONSTRAINTS;


typedef struct _PEP_PPM_IDLE_SELECT {
    PPEP_PROCESSOR_IDLE_CONSTRAINTS Constraints;
   BOOLEAN                         AbortTransition;
   ULONG                           IdleStateIndex;
   ULONG                           DependencyArrayUsed;
    ULONG                           DependencyArrayCount;
    PPEP_PROCESSOR_IDLE_DEPENDENCY  DependencyArray;
   ULONG                           PlatformIdleStateIndex;
} PEP_PPM_IDLE_SELECT, *PPEP_PPM_IDLE_SELECT;

typedef struct _PEP_PPM_INITIATE_WAKE {
   BOOLEAN NeedInterruptForCompletion;
} PEP_PPM_INITIATE_WAKE, *PPEP_PPM_INITIATE_WAKE;

typedef struct _PEP_PPM_IS_PROCESSOR_HALTED {
   BOOLEAN Halted;
} PEP_PPM_IS_PROCESSOR_HALTED, *PPEP_PPM_IS_PROCESSOR_HALTED;

typedef struct _PEP_PPM_LPI_COMPLETE {
  ULONG  CoordinatedStateCount;
  PULONG CoordinatedStates;
} PEP_PPM_LPI_COMPLETE, *PPEP_PPM_LPI_COMPLETE;

typedef struct _PEP_PPM_PARK_MASK {
       ULONG                     Count;
       ULONGLONG                 EvaluationTime;
   PPEP_PROCESSOR_PARK_STATE Processors;
} PEP_PPM_PARK_MASK, *PPEP_PPM_PARK_MASK;

typedef struct _PEP_PPM_PARK_SELECTION {
       ULONG                          AdditionalUnparkedProcessors;
       ULONG                          Count;
   PPEP_PROCESSOR_PARK_PREFERENCE Processors;
} PEP_PPM_PARK_SELECTION, *PPEP_PPM_PARK_SELECTION;

typedef struct _PEP_PPM_PARK_SELECTION_V2 {
       ULONG                          AdditionalUnparkedProcessors;
       ULONG                          Count;
   PPEP_PROCESSOR_PARK_PREFERENCE Processors;
           ULONGLONG                      EvaluationTime;
           UCHAR                          EvaluationType;
} PEP_PPM_PARK_SELECTION_V2, *PPEP_PPM_PARK_SELECTION_V2;

typedef struct _PEP_PPM_PERF_CHECK_COMPLETE {
   ULONGLONG EvaluationTime;
} PEP_PPM_PERF_CHECK_COMPLETE, *PPEP_PPM_PERF_CHECK_COMPLETE;

typedef struct _PEP_PPM_QUERY_PERF_CONSTRAINTS {
   ULONG GuaranteedPerformanceLimit;
   ULONG LimitReasons;
} PEP_PPM_PERF_CONSTRAINTS, *PPEP_PPM_PERF_CONSTRAINTS;

typedef struct _PEP_PPM_PERF_SET {
   ULONG MinimumPerformance;
   ULONG MaximumPerformance;
   ULONG DesiredPerformance;
   ULONG TimeWindow;
   ULONG PerformanceTolerance;
} PEP_PPM_PERF_SET, *PPEP_PPM_PERF_SET;

typedef struct _PEP_PPM_PERF_SET_STATE {
  UCHAR MinimumPerformanceState;
  UCHAR MaximumPerformanceState;
  UCHAR DesiredPerformanceState;
  UCHAR EnergyPerformancePreference;
} PEP_PPM_PERF_SET_STATE, *PPEP_PPM_PERF_SET_STATE;

typedef struct _PEP_PPM_PLATFORM_STATE_RESIDENCIES {
   ULONG                             Count;
   PPEP_PPM_PLATFORM_STATE_RESIDENCY States;
} PEP_PPM_PLATFORM_STATE_RESIDENCIES, *PPEP_PPM_PLATFORM_STATE_RESIDENCIES;



typedef struct _PEP_PPM_QUERY_CAPABILITIES {
  ULONG   FeedbackCounterCount;
  ULONG   IdleStateCount;
  BOOLEAN PerformanceStatesSupported;
  BOOLEAN ParkingSupported;
  UCHAR   DiscretePerformanceStateCount;
  UCHAR   Reserved;
} PEP_PPM_QUERY_CAPABILITIES, *PPEP_PPM_QUERY_CAPABILITIES;

typedef struct _PEP_PPM_QUERY_COORDINATED_DEPENDENCY {
    ULONG                             StateIndex;
    ULONG                             DependencyIndex;
    ULONG                             DependencySize;
   ULONG                             DependencySizeUsed;
   POHANDLE                          TargetProcessor;
        PEP_COORDINATED_DEPENDENCY_OPTION* Options;
} PEP_PPM_QUERY_COORDINATED_DEPENDENCY, *PPEP_PPM_QUERY_COORDINATED_DEPENDENCY;

typedef struct _PEP_PPM_QUERY_COORDINATED_STATES {
    ULONG                      Count;
        PEP_COORDINATED_IDLE_STATE* States;
} PEP_PPM_QUERY_COORDINATED_STATES, *PPEP_PPM_QUERY_COORDINATED_STATES;

typedef struct _PEP_PPM_QUERY_DISCRETE_PERF_STATES {
  ULONG                     Count;
  PPEP_PROCESSOR_PERF_STATE States;
} PEP_PPM_QUERY_DISCRETE_PERF_STATES, *PPEP_PPM_QUERY_DISCRETE_PERF_STATES;

typedef struct _PEP_PPM_QUERY_DOMAIN_INFO {
  ULONG   DomainId;
  UCHAR   CoordinationType;
  BOOLEAN IdleProcessorsDiscounted;
  BOOLEAN SchedulerDirectedTransitionsSupported;
  BOOLEAN AffinitizePerfSet;
  ULONG   WorstCaseTransitionLatency;
  ULONG   WorstCaseTransitionOverhead;
} PEP_PPM_QUERY_DOMAIN_INFO, *PPEP_PPM_QUERY_DOMAIN_INFO;


/// <summary>
/// 
/// </summary>

typedef struct _PEP_SOC_SUBSYSTEM_METADATA {
    UNICODE_STRING Key;
    UNICODE_STRING Value;
} PEP_SOC_SUBSYSTEM_METADATA, * PPEP_SOC_SUBSYSTEM_METADATA;


typedef struct _PEP_PROCESSOR_IDLE_STATE_V2 {
    union {
        ULONG Ulong;
        struct {
            ULONG Interruptible : 1;
            ULONG CacheCoherent : 1;
            ULONG ThreadContextRetained : 1;
            ULONG CStateType : 4;
            ULONG WakesSpuriously : 1;
            ULONG PlatformOnly : 1;
            ULONG Autonomous : 1;
            ULONG Reserved : 22;
        };
    };
    ULONG Latency;
    ULONG BreakEvenDuration;
} PEP_PROCESSOR_IDLE_STATE_V2, * PPEP_PROCESSOR_IDLE_STATE_V2;

typedef struct _PEP_PROCESSOR_IDLE_STATE {
    union {
        ULONG Ulong;
        struct {
            ULONG Interruptible : 1;
            ULONG CacheCoherent : 1;
            ULONG ThreadContextRetained : 1;
            ULONG CStateType : 4;
            ULONG Reserved : 25;
        };
    };
} PEP_PROCESSOR_IDLE_STATE, * PPEP_PROCESSOR_IDLE_STATE;

typedef struct _PEP_PPM_QUERY_FEEDBACK_COUNTERS {
    ULONG                          Count;
        PEP_PROCESSOR_FEEDBACK_COUNTER* Counters;
} PEP_PPM_QUERY_FEEDBACK_COUNTERS, *PPEP_PPM_QUERY_FEEDBACK_COUNTERS;

typedef struct _PEP_PPM_QUERY_IDLE_STATES {
    ULONG                    Count;
   ULONG                    MaximumCoordinatedProcessors;
        PEP_PROCESSOR_IDLE_STATE* IdleStates;
} PEP_PPM_QUERY_IDLE_STATES, *PPEP_PPM_QUERY_IDLE_STATES;

typedef struct _PEP_PPM_QUERY_IDLE_STATES_V2 {
    ULONG                       Count;
        PEP_PROCESSOR_IDLE_STATE_V2* IdleStates;
} PEP_PPM_QUERY_IDLE_STATES_V2, *PPEP_PPM_QUERY_IDLE_STATES_V2;

typedef struct _PEP_PPM_QUERY_LP_SETTINGS {
   HANDLE RegistryRoot;
} PEP_PPM_QUERY_LP_SETTINGS, *PPEP_PPM_QUERY_LP_SETTINGS;

typedef struct _PEP_PPM_QUERY_PERF_CAPABILITIES {
   ULONG HighestPerformance;
   ULONG NominalPerformance;
   ULONG LowestNonlinearPerformance;
   ULONG LowestPerformance;
   ULONG DomainId;
   ULONG DomainMembers;
} PEP_PPM_QUERY_PERF_CAPABILITIES, *PPEP_PPM_QUERY_PERF_CAPABILITIES;


typedef struct _PEP_PPM_QUERY_PLATFORM_STATE {
    ULONG                   StateIndex;
   PEP_PLATFORM_IDLE_STATE State;
} PEP_PPM_QUERY_PLATFORM_STATE, *PPEP_PPM_QUERY_PLATFORM_STATE;

typedef struct _PEP_PPM_QUERY_PLATFORM_STATES {
  ULONG PlatformStateCount;
} PEP_PPM_QUERY_PLATFORM_STATES, *PPEP_PPM_QUERY_PLATFORM_STATES;

typedef struct _PEP_PPM_QUERY_STATE_NAME {
       ULONG  StateIndex;
   USHORT NameSize;
       PWSTR  Name;
} PEP_PPM_QUERY_STATE_NAME, *PPEP_PPM_QUERY_STATE_NAME;

typedef struct _PEP_PPM_QUERY_VETO_REASON {
    ULONG  VetoReason;
   USHORT NameSize;
    PWSTR  Name;
} PEP_PPM_QUERY_VETO_REASON, *PPEP_PPM_QUERY_VETO_REASON;

typedef struct _PEP_PPM_QUERY_VETO_REASONS {
   ULONG VetoReasonCount;
} PEP_PPM_QUERY_VETO_REASONS, *PPEP_PPM_QUERY_VETO_REASONS;

typedef struct _PEP_PPM_RESUME_FROM_SYSTEM_STATE {
  SYSTEM_POWER_STATE TargetState;
} PEP_PPM_RESUME_FROM_SYSTEM_STATE, *PPEP_PPM_RESUME_FROM_SYSTEM_STATE;

typedef struct _PEP_PPM_TEST_IDLE_STATE {
        ULONG ProcessorState;
    ULONG PlatformState;
   ULONG VetoReason;
} PEP_PPM_TEST_IDLE_STATE, *PPEP_PPM_TEST_IDLE_STATE;

typedef struct _PEP_PREPARE_DEVICE {
    PCUNICODE_STRING DeviceId;
   BOOLEAN          DeviceAccepted;
} PEP_PREPARE_DEVICE, *PPEP_PREPARE_DEVICE;


typedef struct _PEP_PROCESSOR_IDLE_STATE_UPDATE {
  ULONG Version;
  ULONG Latency;
  ULONG BreakEvenDuration;
} PEP_PROCESSOR_IDLE_STATE_UPDATE, *PPEP_PROCESSOR_IDLE_STATE_UPDATE;


typedef struct _PEP_QUERY_COMPONENT_PERF_CAPABILITIES {
    PEPHANDLE DeviceHandle;
    ULONG     Component;
   ULONG     SetCount;
} PEP_QUERY_COMPONENT_PERF_CAPABILITIES, *PPEP_QUERY_COMPONENT_PERF_CAPABILITIES;

typedef struct _PEP_QUERY_COMPONENT_PERF_SET {
  PEPHANDLE           DeviceHandle;
  ULONG               Component;
  ULONG               Set;
  ULONGLONG           Flags;
  PEP_PERF_STATE_UNIT Unit;
  PEP_PERF_STATE_TYPE Type;
  union {
    struct {
      ULONG Count;
    } Discrete;
    struct {
      ULONGLONG Minimum;
      ULONGLONG Maximum;
    } Range;
  };
} PEP_QUERY_COMPONENT_PERF_SET, *PPEP_QUERY_COMPONENT_PERF_SET;

typedef struct _PEP_QUERY_COMPONENT_PERF_SET_NAME {
        PEPHANDLE DeviceHandle;
        ULONG     Component;
        ULONG     Set;
    USHORT    NameSize;
        PWCHAR    Name;
} PEP_QUERY_COMPONENT_PERF_SET_NAME, *PPEP_QUERY_COMPONENT_PERF_SET_NAME;

typedef struct _PEP_QUERY_COMPONENT_PERF_STATES {
   PEPHANDLE       DeviceHandle;
   ULONG           Component;
   ULONG           Set;
   PPEP_PERF_STATE States;
} PEP_QUERY_COMPONENT_PERF_STATES, *PPEP_QUERY_COMPONENT_PERF_STATES;

typedef struct _PEP_QUERY_CURRENT_COMPONENT_PERF_STATE {
  PEPHANDLE DeviceHandle;
  ULONG     Component;
  ULONG     Set;
  union {
    ULONG     StateIndex;
    ULONGLONG StateValue;
  };
} PEP_QUERY_CURRENT_COMPONENT_PERF_STATE, *PPEP_QUERY_CURRENT_COMPONENT_PERF_STATE;

typedef struct _PEP_QUERY_SOC_SUBSYSTEM {
       ULONG          PlatformIdleStateIndex;
       ULONG          SubsystemIndex;
      PVOID          SubsystemHandle;
   UNICODE_STRING ParentName;
   UNICODE_STRING SubsystemName;
      ULONG          MetadataCount;
           ULONG          Flags;
} PEP_QUERY_SOC_SUBSYSTEM, *PPEP_QUERY_SOC_SUBSYSTEM;

typedef struct _PEP_QUERY_SOC_SUBSYSTEM_BLOCKING_TIME {
    ULONG            PlatformIdleStateIndex;
    PVOID            SubsystemHandle;
    PCUNICODE_STRING SubsystemName;
   ULONG64          BlockingTime;
        ULONG            Flags;
} PEP_QUERY_SOC_SUBSYSTEM_BLOCKING_TIME, *PPEP_QUERY_SOC_SUBSYSTEM_BLOCKING_TIME;

typedef struct _PEP_QUERY_SOC_SUBSYSTEM_COUNT {
    ULONG PlatformIdleStateIndex;
   ULONG SubsystemCount;
        ULONG Flags;
} PEP_QUERY_SOC_SUBSYSTEM_COUNT, *PPEP_QUERY_SOC_SUBSYSTEM_COUNT;

typedef struct _PEP_QUERY_SOC_SUBSYSTEM_METADATA {
       ULONG                       PlatformIdleStateIndex;
       PVOID                       SubsystemHandle;
       PCUNICODE_STRING            SubsystemName;
           ULONG                       Flags;
       ULONG                       MetadataCount;
           PPEP_SOC_SUBSYSTEM_METADATA* Metadata;
} PEP_QUERY_SOC_SUBSYSTEM_METADATA, *PPEP_QUERY_SOC_SUBSYSTEM_METADATA;

typedef struct _PEP_REGISTER_COMPONENT_PERF_STATES {
   PEPHANDLE                DeviceHandle;
   ULONG                    Component;
   ULONGLONG                Flags;
   PPEP_COMPONENT_PERF_INFO PerfStateInfo;
} PEP_REGISTER_COMPONENT_PERF_STATES, *PPEP_REGISTER_COMPONENT_PERF_STATES;

typedef struct _PEP_REGISTER_CRASHDUMP_DEVICE {
   PPEPCALLBACKPOWERONCRASHDUMPDEVICE PowerOnDumpDeviceCallback;
    PEPHANDLE                          DeviceHandle;
} PEP_REGISTER_CRASHDUMP_DEVICE, *PPEP_REGISTER_CRASHDUMP_DEVICE;

typedef struct _PEP_REGISTER_DEBUGGER {
   PEPHANDLE DeviceHandle;
} PEP_REGISTER_DEBUGGER, *PPEP_REGISTER_DEBUGGER;

typedef struct _PEP_REGISTER_DEVICE_V2 {
    PCUNICODE_STRING           DeviceId;
    POHANDLE                   KernelHandle;
    PPEP_DEVICE_REGISTER_V2    Register;
   PEPHANDLE                  DeviceHandle;
   PEP_DEVICE_ACCEPTANCE_TYPE DeviceAccepted;
} PEP_REGISTER_DEVICE_V2, *PPEP_REGISTER_DEVICE_V2;

typedef struct _PEP_REQUEST_COMPONENT_PERF_STATE {
    PEPHANDLE                         DeviceHandle;
    ULONG                             Component;
   BOOLEAN                           Completed;
   BOOLEAN                           Succeeded;
    ULONG                             PerfRequestsCount;
    PPEP_COMPONENT_PERF_STATE_REQUEST PerfRequests;
} PEP_REQUEST_COMPONENT_PERF_STATE, *PPEP_REQUEST_COMPONENT_PERF_STATE;

typedef struct _PEP_RESET_SOC_SUBSYSTEM_ACCOUNTING {
   ULONG PlatformIdleStateIndex;
       ULONG Flags;
} PEP_RESET_SOC_SUBSYSTEM_ACCOUNTING, *PPEP_RESET_SOC_SUBSYSTEM_ACCOUNTING;



typedef struct _PEP_SYSTEM_LATENCY {
   ULONGLONG Latency;
} PEP_SYSTEM_LATENCY, *PPEP_SYSTEM_LATENCY;

typedef union _PEP_UNMASKED_INTERRUPT_FLAGS {
  struct {
    USHORT SecondaryInterrupt : 1;
    USHORT Reserved : 15;
  };
  USHORT AsUSHORT;
} PEP_UNMASKED_INTERRUPT_FLAGS, *PPEP_UNMASKED_INTERRUPT_FLAGS;

typedef struct _PEP_UNMASKED_INTERRUPT_INFORMATION {
  USHORT                       Version;
  USHORT                       Size;
  PEP_UNMASKED_INTERRUPT_FLAGS Flags;
  KINTERRUPT_MODE              Mode;
  KINTERRUPT_POLARITY          Polarity;
  ULONG                        Gsiv;
  USHORT                       PinNumber;
  PEPHANDLE                    DeviceHandle;
} PEP_UNMASKED_INTERRUPT_INFORMATION, *PPEP_UNMASKED_INTERRUPT_INFORMATION;

typedef struct _PEP_UNREGISTER_DEVICE {
   PEPHANDLE DeviceHandle;
} PEP_UNREGISTER_DEVICE, *PPEP_UNREGISTER_DEVICE;



typedef struct _PEP_WORK_ACPI_BUILD_CHILDREN_CONTROL_METHOD_COMPLETE {
  POHANDLE              DeviceHandle;
  ULONG                 CompletionFlags;
  NTSTATUS              MethodStatus;
  PVOID                 CompletionContext;
  SIZE_T                OutputArgumentSize;
  PACPI_METHOD_ARGUMENT OutputArguments;
} PEP_WORK_ACPI_BUILD_CHILDREN_CONTROL_METHOD_COMPLETE, *PPEP_WORK_ACPI_BUILD_CHILDREN_CONTROL_METHOD_COMPLETE;


typedef struct _PEP_WORK_ACPI_NOTIFY {
  POHANDLE DeviceHandle;
  ULONG    NotifyCode;
} PEP_WORK_ACPI_NOTIFY, *PPEP_WORK_ACPI_NOTIFY;

typedef struct _PEP_WORK_ACTIVE_COMPLETE {
       POHANDLE DeviceHandle;
   ULONG    Component;
} PEP_WORK_ACTIVE_COMPLETE, *PPEP_WORK_ACTIVE_COMPLETE;

typedef struct _PEP_WORK_COMPLETE_IDLE_STATE {
       POHANDLE DeviceHandle;
   ULONG    Component;
} PEP_WORK_COMPLETE_IDLE_STATE, *PPEP_WORK_COMPLETE_IDLE_STATE;


typedef struct _PEP_WORK_COMPLETE_PERF_STATE {
       POHANDLE DeviceHandle;
   ULONG    Component;
       BOOLEAN  Succeeded;
} PEP_WORK_COMPLETE_PERF_STATE, *PPEP_WORK_COMPLETE_PERF_STATE;

typedef struct _PEP_WORK_DEVICE_IDLE {
  POHANDLE DeviceHandle;
  BOOLEAN  IgnoreIdleTimeout;
} PEP_WORK_DEVICE_IDLE, *PPEP_WORK_DEVICE_IDLE;

typedef struct _PEP_WORK_DEVICE_POWER {
  POHANDLE DeviceHandle;
  BOOLEAN  PowerRequired;
} PEP_WORK_DEVICE_POWER, *PPEP_WORK_DEVICE_POWER;

typedef struct _PEP_WORK_IDLE_STATE {
       POHANDLE DeviceHandle;
   ULONG    Component;
       ULONG    State;
} PEP_WORK_IDLE_STATE, *PPEP_WORK_IDLE_STATE;


typedef struct _PEP_WORK_POWER_CONTROL {
       POHANDLE DeviceHandle;
   LPCGUID  PowerControlCode;
       PVOID    RequestContext;
   PVOID    InBuffer;
   SIZE_T   InBufferSize;
   PVOID    OutBuffer;
   SIZE_T   OutBufferSize;
} PEP_WORK_POWER_CONTROL, *PPEP_WORK_POWER_CONTROL;

typedef struct _PEP_WORK_INFORMATION {
    PEP_WORK_TYPE WorkType;
    union {
        PEP_WORK_POWER_CONTROL                         PowerControl;
        PEP_WORK_COMPLETE_IDLE_STATE                   CompleteIdleState;
        PEP_WORK_COMPLETE_PERF_STATE                   CompletePerfState;
        PEP_WORK_ACPI_NOTIFY                           AcpiNotify;
        PEP_WORK_ACPI_BUILD_CHILDREN_CONTROL_METHOD_COMPLETE ControlMethodComplete;
    };
} PEP_WORK_INFORMATION, * PPEP_WORK_INFORMATION;

typedef struct _PEP_COMPONENT_ACTIVE {
      PEPHANDLE             DeviceHandle;
      ULONG                 Component;
      BOOLEAN               Active;
     PPEP_WORK_INFORMATION WorkInformation;
     BOOLEAN               NeedWork;
} PEP_COMPONENT_ACTIVE, * PPEP_COMPONENT_ACTIVE;

typedef struct _PEP_WORK {
     PPEP_WORK_INFORMATION WorkInformation;
     BOOLEAN               NeedWork;
} PEP_WORK, * PPEP_WORK;


//static PEPCALLBACKNOTIFYACPI Pepcallbacknotifyacpi;

NTSTATUS PoFxRegisterCoreDevice(
    PCUNICODE_STRING   Id,
    PPO_FX_CORE_DEVICE Device,
   POHANDLE           *Handle
);

NTSTATUS PoFxRegisterPlugin(
        PPEP_INFORMATION        PepInformation,
    PPEP_KERNEL_INFORMATION KernelInformation
);

NTSTATUS PoFxRegisterPluginEx(
        PPEP_INFORMATION        PepInformation,
        ULONGLONG               Flags,
    PPEP_KERNEL_INFORMATION KernelInformation
);


void PEP_ACPI_INITIALIZE_EXTENDED_IO_RESOURCE(
      BOOLEAN            ResourceUsage,
      UCHAR              Decode,
      BOOLEAN            IsMinFixed,
      BOOLEAN            IsMaxFixed,
      UCHAR              ISARanges,
      ULONGLONG          AddressGranularity,
      ULONGLONG          AddressMinimum,
      ULONGLONG          AddressMaximum,
      ULONGLONG          AddressTranslation,
      ULONGLONG          RangeLength,
      ULONGLONG          TypeSpecificAttributes,
      PUNICODE_STRING    DescriptorName,
      BOOLEAN            TranslationTypeNonStatic,
      BOOLEAN            TanslationSparseDensity,
     PPEP_ACPI_RESOURCE Resource
);

void PEP_ACPI_INITIALIZE_EXTENDED_MEMORY_RESOURCE(
      BOOLEAN            ResourceUsage,
      UCHAR              Decode,
      BOOLEAN            IsMinFixed,
      BOOLEAN            IsMaxFixed,
      UCHAR              Cacheable,
      BOOLEAN            ReadWrite,
      ULONGLONG          AddressGranularity,
      ULONGLONG          AddressMinimum,
      ULONGLONG          AddressMaximum,
      ULONGLONG          AddressTranslation,
      ULONGLONG          RangeLength,
      ULONGLONG          TypeSpecificAttributes,
      PUNICODE_STRING    DescriptorName,
      UCHAR              MemoryRangeType,
    BOOLEAN            TranslationTypeNonStatic,
     PPEP_ACPI_RESOURCE Resource
);

void PEP_ACPI_INITIALIZE_GPIO_INT_RESOURCE(
      KINTERRUPT_MODE      InterruptType,
      KINTERRUPT_POLARITY  LevelType,
      BOOLEAN              Shareable,
      BOOLEAN              CanWake,
      GPIO_PIN_CONFIG_TYPE PinConfig,
      USHORT               DebounceTimeout,
      UCHAR                ResourceSourceIndex,
      PUNICODE_STRING      ResourceSourceName,
      BOOLEAN              ResourceUsage,
      PUCHAR               VendorData,
      USHORT               VendorDataLength,
      PUSHORT              PinTable,
      UCHAR                PinCount,
     PPEP_ACPI_RESOURCE   Resource
);


void PEP_ACPI_INITIALIZE_GPIO_IO_RESOURCE(
      BOOLEAN                     Shareable,
      BOOLEAN                     CanWake,
      GPIO_PIN_CONFIG_TYPE        PinConfig,
      USHORT                      DebounceTimeout,
      USHORT                      DriveStrength,
      GPIO_PIN_IORESTRICTION_TYPE IoRestriction,
      UCHAR                       ResourceSourceIndex,
      PUNICODE_STRING             ResourceSourceName,
      BOOLEAN                     ResourceUsage,
      PUCHAR                      VendorData,
      USHORT                      VendorDataLength,
      PUSHORT                     PinTable,
      USHORT                      PinCount,
     PPEP_ACPI_RESOURCE          Resource
);


void PEP_ACPI_INITIALIZE_INTERRUPT_RESOURCE(
      BOOLEAN             ResourceUsage,
      KINTERRUPT_MODE     EdgeLevel,
      KINTERRUPT_POLARITY InterruptLevel,
      BOOLEAN             ShareType,
      BOOLEAN             Wake,
      PULONG              PinTable,
      UCHAR               PinCount,
     PPEP_ACPI_RESOURCE  Resource
);

void PEP_ACPI_INITIALIZE_IOPORT_RESOURCE(
      UCHAR              Decode,
      USHORT             MinimumAddress,
      USHORT             MaximumAddress,
      UCHAR              Alignment,
      UCHAR              PortLength,
     PPEP_ACPI_RESOURCE Resource
);

void PEP_ACPI_INITIALIZE_SPB_UART_RESOURCE(
      ULONG              BaudRate,
      UCHAR              BitsPerByte,
      UCHAR              StopBits,
      UCHAR              LinesInUse,
      UCHAR              IsBigEndian,
      UCHAR              Parity,
      UCHAR              FlowControl,
      USHORT             RxSize,
      USHORT             TxSize,
      PUNICODE_STRING    ResourceSource,
      UCHAR              ResourceSourceIndex,
      BOOLEAN            ResourceUsage,
      BOOLEAN            SharedMode,
      PCHAR              VendorData,
      USHORT             VendorDataLength,
     PPEP_ACPI_RESOURCE Resource
);

void PEP_ACPI_INITIALIZE_MEMORY_RESOURCE(
      UCHAR              ReadWrite,
      ULONG              MinimumAddress,
      ULONG              MaximumAddress,
      ULONG              Alignment,
      ULONG              MemorySize,
     PPEP_ACPI_RESOURCE Resource
);


void PEP_ACPI_INITIALIZE_SPB_SPI_RESOURCE(
      USHORT             DeviceSelection,
      UCHAR              DeviceSelectionPolarity,
      UCHAR              WireMode,
      UCHAR              DataBitLength,
      BOOLEAN            SlaveMode,
      ULONG              ConnectionSpeed,
      UCHAR              ClockPolarity,
      UCHAR              ClockPhase,
      PUNICODE_STRING    ResourceSource,
      UCHAR              ResourceSourceIndex,
      BOOLEAN            ResourceUsage,
      BOOLEAN            SharedMode,
      PCHAR              VendorData,
      USHORT             VendorDataLength,
     PPEP_ACPI_RESOURCE Resource
);

void PEP_ACPI_INITIALIZE_SPB_I2C_RESOURCE(
      USHORT             SlaveAddress,
      BOOLEAN            DeviceInitiated,
      ULONG              ConnectionSpeed,
      BOOLEAN            AddressingMode,
      PUNICODE_STRING    ResourceSource,
      UCHAR              ResourceSourceIndex,
      BOOLEAN            ResourceUsage,
      BOOLEAN            SharedMode,
      PCHAR              VendorData,
      USHORT             VendorDataLength,
     PPEP_ACPI_RESOURCE Resource
);


#endif