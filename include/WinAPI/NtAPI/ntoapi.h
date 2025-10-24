#ifndef NTOAPI_H
#define NTOAPI_H

#include <NtAPI.h>
#include "ntoapi.h"


typedef enum _POWER_STATE_TYPE {
    SystemPowerState,
    DevicePowerState
} POWER_STATE_TYPE, * PPOWER_STATE_TYPE;



typedef enum {
    InternalWakeSourceDozeToHibernate,
    InternalWakeSourcePredictedUserPresence,
    InternalWakeSourceTimerOverride
} PO_INTERNAL_WAKE_SOURCE_TYPE, * PPO_INTERNAL_WAKE_SOURCE_TYPE;

typedef enum {
    MonitorRequestReasonUnknown,
    MonitorRequestReasonPowerButton,
    MonitorRequestReasonRemoteConnection,
    MonitorRequestReasonScMonitorpower,
    MonitorRequestReasonUserInput,
    MonitorRequestReasonAcDcDisplayBurst,
    MonitorRequestReasonUserDisplayBurst,
    MonitorRequestReasonPoSetSystemState,
    MonitorRequestReasonSetThreadExecutionState,
    MonitorRequestReasonFullWake,
    MonitorRequestReasonSessionUnlock,
    MonitorRequestReasonScreenOffRequest,
    MonitorRequestReasonIdleTimeout,
    MonitorRequestReasonPolicyChange,
    MonitorRequestReasonSleepButton,
    MonitorRequestReasonLid,
    MonitorRequestReasonBatteryCountChange,
    MonitorRequestReasonGracePeriod,
    MonitorRequestReasonPnP,
    MonitorRequestReasonDP,
    MonitorRequestReasonSxTransition,
    MonitorRequestReasonSystemIdle,
    MonitorRequestReasonNearProximity,
    MonitorRequestReasonThermalStandby,
    MonitorRequestReasonResumePdc,
    MonitorRequestReasonResumeS4,
    MonitorRequestReasonTerminal,
    MonitorRequestReasonPdcSignal,
    MonitorRequestReasonAcDcDisplayBurstSuppressed,
    MonitorRequestReasonSystemStateEntered,
    MonitorRequestReasonWinrt,
    MonitorRequestReasonUserInputKeyboard,
    MonitorRequestReasonUserInputMouse,
    MonitorRequestReasonUserInputTouchpad,
    MonitorRequestReasonUserInputPen,
    MonitorRequestReasonUserInputAccelerometer,
    MonitorRequestReasonUserInputHid,
    MonitorRequestReasonUserInputPoUserPresent,
    MonitorRequestReasonUserInputSessionSwitch,
    MonitorRequestReasonUserInputInitialization,
    MonitorRequestReasonPdcSignalWindowsMobilePwrNotif,
    MonitorRequestReasonPdcSignalWindowsMobileShell,
    MonitorRequestReasonPdcSignalHeyCortana,
    MonitorRequestReasonPdcSignalHolographicShell,
    MonitorRequestReasonPdcSignalFingerprint,
    MonitorRequestReasonDirectedDrips,
    MonitorRequestReasonDim,
    MonitorRequestReasonBuiltinPanel,
    MonitorRequestReasonDisplayRequiredUnDim,
    MonitorRequestReasonBatteryCountChangeSuppressed,
    MonitorRequestReasonResumeModernStandby,
    MonitorRequestReasonTerminalInit,
    MonitorRequestReasonPdcSignalSensorsHumanPresence,
    MonitorRequestReasonBatteryPreCritical,
    MonitorRequestReasonUserInputTouch,
    MonitorRequestReasonMax
} POWER_MONITOR_REQUEST_REASON;

typedef enum _MONITOR_DISPLAY_STATE {
    PowerMonitorOff,
    PowerMonitorOn,
    PowerMonitorDim
} MONITOR_DISPLAY_STATE, * PMONITOR_DISPLAY_STATE;

typedef struct CM_Power_Data_s {
  ULONG              PD_Size;
  DEVICE_POWER_STATE PD_MostRecentPowerState;
  ULONG              PD_Capabilities;
  ULONG              PD_D1Latency;
  ULONG              PD_D2Latency;
  ULONG              PD_D3Latency;
  DEVICE_POWER_STATE* PD_PowerStateMapping;
  SYSTEM_POWER_STATE PD_DeepestSystemWake;
} CM_POWER_DATA, *PCM_POWER_DATA;

typedef struct _COUNTED_REASON_CONTEXT {
  ULONG Version;
  ULONG Flags;
  union {
    struct {
      UNICODE_STRING  ResourceFileName;
      USHORT          ResourceReasonId;
      ULONG           StringCount;
      PUNICODE_STRING ReasonStrings;
    } DUMMYSTRUCTNAME;
    UNICODE_STRING SimpleString;
  } DUMMYUNIONNAME;
} COUNTED_REASON_CONTEXT, *PCOUNTED_REASON_CONTEXT;




KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtPowerInformation(
              POWER_INFORMATION_LEVEL InformationLevel,
    PVOID                   InputBuffer,
              ULONG                   InputBufferLength,
   PVOID                   OutputBuffer,
              ULONG                   OutputBufferLength
);



typedef struct _PO_SPR_ACTIVE_SESSION_DATA {
  BOOLEAN Start;
  GUID    ActiveSessionGuid;
} PO_SPR_ACTIVE_SESSION_DATA, *PPO_SPR_ACTIVE_SESSION_DATA;



typedef struct _POWER_PLATFORM_INFORMATION {
  BOOLEAN AoAc;
} POWER_PLATFORM_INFORMATION, *PPOWER_PLATFORM_INFORMATION;


typedef struct _POWER_SESSION_ALLOW_EXTERNAL_DMA_DEVICES {
  BOOLEAN IsAllowed;
} POWER_SESSION_ALLOW_EXTERNAL_DMA_DEVICES, *PPOWER_SESSION_ALLOW_EXTERNAL_DMA_DEVICES;

typedef union _POWER_STATE {
  SYSTEM_POWER_STATE SystemState;
  DEVICE_POWER_STATE DeviceState;
} POWER_STATE, *PPOWER_STATE;



typedef struct _SYSTEM_POWER_STATE_CONTEXT {
  union {
    struct {
      ULONG Reserved1 : 8;
      ULONG TargetSystemState : 4;
      ULONG EffectiveSystemState : 4;
      ULONG CurrentSystemState : 4;
      ULONG IgnoreHibernationPath : 1;
      ULONG PseudoTransition : 1;
      ULONG KernelSoftReboot : 1;
      ULONG DirectedDripsTransition : 1;
      ULONG Reserved2 : 8;
    } DUMMYSTRUCTNAME;
    ULONG ContextAsUlong;
  } DUMMYUNIONNAME;
} SYSTEM_POWER_STATE_CONTEXT, *PSYSTEM_POWER_STATE_CONTEXT;



#endif