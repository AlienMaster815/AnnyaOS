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

typedef enum _PEP_ACPI_RESOURCE_TYPE {
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
}PEP_ACPI_RESOURCE_TYPE;



#ifdef __cplusplus
}
#endif
#endif