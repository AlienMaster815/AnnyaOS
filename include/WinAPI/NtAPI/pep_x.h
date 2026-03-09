
#ifndef PEPX_HEADER
#define PEPX_HEADER
#pragma once

#include <NtAPI.h>









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
  LOUSTATUS              MethodStatus;
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

LOUSTATUS PoFxRegisterCoreDevice(
    PCUNICODE_STRING   Id,
    PPO_FX_CORE_DEVICE Device,
   POHANDLE           *Handle
);

LOUSTATUS PoFxRegisterPlugin(
        PPEP_INFORMATION        PepInformation,
    PPEP_KERNEL_INFORMATION KernelInformation
);

LOUSTATUS PoFxRegisterPluginEx(
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