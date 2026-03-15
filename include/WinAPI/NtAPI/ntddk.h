

#ifndef _NTDDK_H
#define _NTDDK_H

#include <NtAPI.h>
#include "irp.h"
#include "ntoapi.h"
#include "wdm.h"





NTSYSAPI LOUSTATUS RtlCharToInteger(
             PCSZ   String,
   ULONG  Base,
            PULONG Value
);

LONG RtlCompareString(
   const STRING *String1,
   const STRING *String2,
   BOOLEAN      CaseInSensitive
);

//LOUAPI_INLINE RtlConvertUlongToLuid(
//   ULONG Ulong
//);

VOID RtlCopyString(
            PSTRING      DestinationString,
   const STRING *SourceString
);

BOOLEAN RtlEqualString(
   const STRING *String1,
   const STRING *String2,
   BOOLEAN      CaseInSensitive
);

NTSYSAPI ULONG64 RtlGetEnabledExtendedFeatures(
   ULONG64 FeatureMask
);

NTSYSAPI LOUSTATUS RtlGetPersistedStateLocation(
        PCWSTR              SourceID,
    PCWSTR              CustomValue,
    PCWSTR              DefaultPath,
        STATE_LOCATION_TYPE StateLocationType,
        PWCHAR              TargetPath,
        ULONG               BufferLengthIn,
   PULONG              BufferLengthOut
);


NTSYSAPI LOUSTATUS RtlIncrementCorrelationVector(
    PCORRELATION_VECTOR CorrelationVector
);

NTSYSAPI LOUSTATUS RtlInitializeCorrelationVector(
    PCORRELATION_VECTOR CorrelationVector,
        int                 Version,
        const GUID          *Guid
);

NTSYSAPI BOOLEAN RtlIsStateSeparationEnabled();

NTSYSAPI BOOLEAN RtlIsZeroMemory(
  PVOID  Buffer,
  SIZE_T Length
);

NTSYSAPI VOID RtlMapGenericMask(
    PACCESS_MASK          AccessMask,
        const GENERIC_MAPPING *GenericMapping
);

NTSYSAPI BOOLEAN RtlNormalizeSecurityDescriptor(
  PSECURITY_DESCRIPTOR *SecurityDescriptor,
  ULONG                SecurityDescriptorLength,
  PSECURITY_DESCRIPTOR *NewSecurityDescriptor,
  PULONG               NewSecurityDescriptorLength,
  BOOLEAN              CheckOnly
);

NTSYSAPI BOOLEAN RtlPrefixUnicodeString(
   PCUNICODE_STRING String1,
   PCUNICODE_STRING String2,
   BOOLEAN          CaseInSensitive
);

NTSYSAPI LOUSTATUS RtlQueryRegistryValueWithFallback(
    HANDLE          PrimaryHandle,
    HANDLE          FallbackHandle,
    PUNICODE_STRING ValueName,
    ULONG           ValueLength,
   	PULONG          ValueType,
   	PVOID           ValueData,
   	PULONG          ResultLength
);

LOUSTATUS RtlRaiseCustomSystemEventTrigger(
   PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG TriggerConfig
);

NTSYSAPI VOID RtlRunOnceInitialize(
   PRTL_RUN_ONCE RunOnce
);

NTSYSAPI LOUSTATUS RtlUpcaseUnicodeString(
    PUNICODE_STRING  DestinationString,
        PCUNICODE_STRING SourceString,
        BOOLEAN          AllocateDestinationString
);

NTSYSAPI CHAR RtlUpperChar(
   CHAR Character
);

NTSYSAPI VOID RtlUpperString(
    PSTRING      DestinationString,
        const STRING *SourceString
);

NTSYSAPI LOUSTATUS RtlValidateCorrelationVector(
  PCORRELATION_VECTOR Vector
);

NTSYSAPI LOUSTATUS RtlVolumeDeviceToDosName(
    PVOID           VolumeDeviceObject,
   PUNICODE_STRING DosName
);

BOOLEAN SeSinglePrivilegeCheck(
   LUID            PrivilegeValue,
   KPROCESSOR_MODE PreviousMode
);

void SiloContextCleanupCallback(
   PVOID SiloContext
);

void SiloMonitorTerminateCallback(
   PESILO Silo
);

#endif