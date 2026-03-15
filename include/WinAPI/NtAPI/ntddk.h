

#ifndef _NTDDK_H
#define _NTDDK_H

#include <NtAPI.h>
#include "irp.h"
#include "ntoapi.h"
#include "wdm.h"



void ExpandStackCallout(
	PVOID Parameter
);

void ExRaiseDatatypeMisalignment();

void ExRaiseAccessViolation();

LOUSTATUS ExUuidCreate(
	 UUID* Uuid
);

LOUSTATUS HalAllocateHardwareCounters(
	PGROUP_AFFINITY                 GroupAffinty,
	  ULONG                           GroupCount,
	  PPHYSICAL_COUNTER_RESOURCE_LIST ResourceList,
	 PHANDLE                         CounterSetHandle
);


LOUSTATUS HalFreeHardwareCounters(
	 HANDLE CounterSetHandle
);


//WARNING BACKPATIBLE FUNCTIONS STABILITY THREAT
ULONG HalGetBusDataByOffset(
	 BUS_DATA_TYPE BusDataType,
	 ULONG         BusNumber,
	 ULONG         SlotNumber,
	 PVOID         Buffer,
	 ULONG         Offset,
	 ULONG         Length
);

ULONG HalSetBusDataByOffset(
	 BUS_DATA_TYPE BusDataType,
	 ULONG         BusNumber,
	 ULONG         SlotNumber,
	 PVOID         Buffer,
	 ULONG         Offset,
	 ULONG         Length
);

void IoAllocateController(
	           PCONTROLLER_OBJECT ControllerObject,
	           struct _DEVICE_OBJECT*     DeviceObject,
	           PDRIVER_CONTROL    ExecutionRoutine,
	 PVOID              Context
);

//void IoAssignArcName(
//	  ArcName,
//	  DeviceName
//);

void IoClearActivityIdThread(
	 LPCGUID OriginalId
);

PCONTROLLER_OBJECT IoCreateController(
	 ULONG Size
);

//void IoDeassignArcName(
//	  ArcName
//);

//void IoDeassignArcName(
//	  ArcName
//);

LOUSTATUS IoDecrementKeepAliveCount(
	  PFILE_OBJECT FileObject,
	  PEPROCESS    Process
);


void IoDeleteController(
	 PCONTROLLER_OBJECT ControllerObject
);

void IoFreeController(
	 PCONTROLLER_OBJECT ControllerObject
);

LOUSTATUS IoGetActivityIdIrp(
	  PIRP   Irp,
	 LPGUID Guid
);

LPCGUID IoGetActivityIdThread();

PCONFIGURATION_INFORMATION IoGetConfigurationInformation();

PGENERIC_MAPPING IoGetFileObjectGenericMapping();

PEPROCESS IoGetInitiatorProcess(
	 PFILE_OBJECT FileObject
);

IO_PAGING_PRIORITY IoGetPagingIoPriority(
	 PIRP Irp
);

PIO_FOEXT_SHADOW_FILE IoGetShadowFileInformation(
	 PFILE_OBJECT FileObject
);

LOUSTATUS IoIncrementKeepAliveCount(
	  PFILE_OBJECT FileObject,
	  PEPROCESS    Process
);

LOGICAL IoIsValidIrpStatus(
	 LOUSTATUS Status
);

PIRP IoMakeAssociatedIrp(
	 PIRP  Irp,
	 CCHAR StackSize
);

LOUSTATUS IoPropagateActivityIdToThread(
	  PIRP    Irp,
	 LPGUID  PropagatedId,
	LPCGUID* OriginalId
);

LOUSTATUS IoQueryFullDriverPath(
	  PDRIVER_OBJECT  DriverObject,
	 PUNICODE_STRING FullPath
);

void IoRaiseHardError(
	           PIRP           Irp,
	 PVPB           Vpb,
	           struct _DEVICE_OBJECT* RealDeviceObject
);

BOOLEAN IoRaiseInformationalHardError(
	           LOUSTATUS        ErrorStatus,
	 PUNICODE_STRING String,
	 PKTHREAD        Thread
);

PVOID IoRegisterBootDriverCallback(
	           PBOOT_DRIVER_CALLBACK_FUNCTION CallbackFunction,
	 PVOID                          CallbackContext
);

void IoRegisterBootDriverReinitialization(
	           PDRIVER_OBJECT       DriverObject,
	           PDRIVER_REINITIALIZE DriverReinitializationRoutine,
	 PVOID                Context
);

void IoRegisterDriverReinitialization(
	           PDRIVER_OBJECT       DriverObject,
	           PDRIVER_REINITIALIZE DriverReinitializationRoutine,
	 PVOID                Context
);

LOUSTATUS IoReportDetectedDevice(
	           PDRIVER_OBJECT                 DriverObject,
	           INTERFACE_TYPE                 LegacyBusType,
	           ULONG                          BusNumber,
	           ULONG                          SlotNumber,
	 PCM_RESOURCE_LIST              ResourceList,
	 PIO_RESOURCE_REQUIREMENTS_LIST ResourceRequirements,
	           BOOLEAN                        ResourceAssigned,
	       struct _DEVICE_OBJECT** DeviceObject
);

LOUSTATUS IoReportResourceForDetection(
	           PDRIVER_OBJECT    DriverObject,
	 PCM_RESOURCE_LIST DriverList,
	 ULONG             DriverListSize,
	 struct _DEVICE_OBJECT*    DeviceObject,
	 PCM_RESOURCE_LIST DeviceList,
	 ULONG             DeviceListSize,
	          PBOOLEAN          ConflictDetected
);

LOUSTATUS IoReportRootDevice(
	 PDRIVER_OBJECT DriverObject
);
LOUSTATUS IoSetActivityIdIrp(
	           PIRP    Irp,
	 LPCGUID Guid
);

LPCGUID IoSetActivityIdThread(
	LPCGUID ActivityId
);
void IoSetHardErrorOrVerifyDevice(
	 PIRP           Irp,
	 struct _DEVICE_OBJECT* DeviceObject
);
void IoSetMasterIrpStatus(
	  PIRP     MasterIrp,
	      LOUSTATUS Status
);
LOUSTATUS IoSetShadowFileInformation(
	 PFILE_OBJECT FileObject,
	 PFILE_OBJECT BackingFileObject,
	 PVOID        BackingFltInstance
);
LOUSTATUS IoSetSystemPartition(
	 PUNICODE_STRING VolumeNameString
);
BOOLEAN IoSetThreadHardErrorMode(
	 BOOLEAN EnableHardErrors
);
void IoTransferActivityId(
	 LPCGUID ActivityId,
	 LPCGUID RelatedActivityId
);

void IoUnregisterBootDriverCallback(
	 PVOID CallbackHandle
);
LOUSTATUS IoVerifyPartitionTable(
	 struct _DEVICE_OBJECT* DeviceObject,
	 BOOLEAN        FixErrors
);
LOUSTATUS IoVolumeDeviceToDosName(
	  PVOID           VolumeDeviceObject,
	 PUNICODE_STRING DosName
);

BOOLEAN KeAreApcsDisabled();

void KeBugCheck(
	 ULONG BugCheckCode
);
void KeEnterCriticalRegion();

void KeEnterGuardedRegion();

LOUSTATUS
KeExpandKernelStackAndCallout(
	 PEXPAND_STACK_CALLOUT Callout,
	 PVOID Parameter,
	 SIZE_T Size
);

LOUSTATUS KeExpandKernelStackAndCalloutEx(
	PEXPAND_STACK_CALLOUT Callout,
	PVOID                 Parameter,
	SIZE_T                Size,
	BOOLEAN               Wait,
	PVOID                 Context
);

USHORT KeGetCurrentNodeNumber();
ULONG KeGetCurrentProcessorNumber();

ULONG KeGetCurrentProcessorNumberEx(
	 PPROCESSOR_NUMBER ProcNumber
);

LOUSTATUS KeInitializeCrashDumpHeader(
	            ULONG  DumpType,
	            ULONG  Flags,
	           PVOID  Buffer,
	            ULONG  BufferSize,
	 PULONG BufferNeeded
);

BOOLEAN KeInvalidateAllCaches();

void KeInvalidateRangeAllCaches(
	PVOID BaseAddress,
	ULONG Length
);

void KeLeaveCriticalRegion();

void KeLeaveGuardedRegion();

LONG KePulseEvent(
	  PRKEVENT  Event,
	      KPRIORITY Increment,
	      BOOLEAN   Wait
);

USHORT KeQueryActiveGroupCount();

ULONG KeQueryActiveProcessorCount(
	 PKAFFINITY ActiveProcessors
);

ULONG KeQueryActiveProcessorCountEx(
	 USHORT GroupNumber
);
KAFFINITY KeQueryActiveProcessors();

KAFFINITY KeQueryGroupAffinity(
	 USHORT GroupNumber
);

KAFFINITY KeQueryGroupAffinity(
	 USHORT GroupNumber
);
USHORT KeQueryHighestNodeNumber();

USHORT KeQueryMaximumGroupCount();

ULONG KeQueryMaximumProcessorCount();

ULONG KeQueryMaximumProcessorCountEx(
	 USHORT GroupNumber
);

USHORT KeQueryNodeMaximumProcessorCount(
	 USHORT NodeNumber
);
VOID
KeQueryTickCount(
	 PLARGE_INTEGER CurrentCount
);

KERNEL_EXPORT KIRQL KeRaiseIrqlToDpcLevel();

LONG KeSetBasePriorityThread(
	  PKTHREAD Thread,
	      LONG     Increment
);

LOUSTATUS KeSetHardwareCounterConfiguration(
	 PHARDWARE_COUNTER CounterArray,
	 ULONG             Count
);

void KeSetImportanceDpc(
	  PRKDPC          Dpc,
	      KDPC_IMPORTANCE Importance
);

void KeSetTargetProcessorDpc(
	  PRKDPC Dpc,
	      CCHAR  Number
);


LOUSTATUS MmAddPhysicalMemory(
	 PPHYSICAL_ADDRESS StartAddress,
	 PLARGE_INTEGER    NumberOfBytes
);

PVOID MmAllocateContiguousMemory(
	 SIZE_T           NumberOfBytes,
	 PHYSICAL_ADDRESS HighestAcceptableAddress
);

PVOID MmAllocateContiguousMemorySpecifyCache(
	           SIZE_T              NumberOfBytes,
	           PHYSICAL_ADDRESS    LowestAcceptableAddress,
	           PHYSICAL_ADDRESS    HighestAcceptableAddress,
	 PHYSICAL_ADDRESS    BoundaryAddressMultiple,
	           MEMORY_CACHING_TYPE CacheType
);

PVOID MmAllocateContiguousMemorySpecifyCacheNode(
	           SIZE_T              NumberOfBytes,
	           PHYSICAL_ADDRESS    LowestAcceptableAddress,
	           PHYSICAL_ADDRESS    HighestAcceptableAddress,
	 PHYSICAL_ADDRESS    BoundaryAddressMultiple,
	           MEMORY_CACHING_TYPE CacheType,
	           NODE_REQUIREMENT    PreferredNode
);

PVOID MmAllocateContiguousNodeMemory(
	           SIZE_T           NumberOfBytes,
	           PHYSICAL_ADDRESS LowestAcceptableAddress,
	           PHYSICAL_ADDRESS HighestAcceptableAddress,
	 PHYSICAL_ADDRESS BoundaryAddressMultiple,
	           ULONG            Protect,
	           NODE_REQUIREMENT PreferredNode
);

PVOID MmAllocateNonCachedMemory(
	 SIZE_T NumberOfBytes
);

LOUSTATUS MmCopyMemory(
	  PVOID           TargetAddress,
	  MM_COPY_ADDRESS SourceAddress,
	  SIZE_T          NumberOfBytes,
	  ULONG           Flags,
	 PSIZE_T         NumberOfBytesTransferred
);

void MmFreeContiguousMemory(
	 PVOID BaseAddress
);

void MmFreeContiguousMemorySpecifyCache(
	 PVOID               BaseAddress,
	 SIZE_T              NumberOfBytes,
	 MEMORY_CACHING_TYPE CacheType
);

void MmFreeNonCachedMemory(
	 PVOID  BaseAddress,
	 SIZE_T NumberOfBytes
);

PHYSICAL_ADDRESS MmGetPhysicalAddress(
	 PVOID BaseAddress
);

PPHYSICAL_MEMORY_RANGE MmGetPhysicalMemoryRangesEx2(
	PVOID PartitionObject,
	ULONG Flags
);

//Not A Recomended Function
BOOLEAN MmIsAddressValid(
	 PVOID VirtualAddress
);

BOOLEAN MmIsThisAnNtAsSystem();

void MmLockPagableSectionByHandle(
	 PVOID ImageSectionHandle
);

LOUSTATUS MmMapViewInSystemSpace(
	PVOID   Section,
	PVOID* MappedBase,
	PSIZE_T ViewSize
);


HANDLE MmSecureVirtualMemory(
	 PVOID  Address,
	 SIZE_T Size,
	 ULONG  ProbeMode
);

HANDLE MmSecureVirtualMemoryEx(
  PVOID  Address,
  SIZE_T Size,
  ULONG  ProbeMode,
  ULONG  Flags
);


LOUSTATUS MmUnmapViewInSystemSpace(
  PVOID MappedBase
);

void MmUnsecureVirtualMemory(
   HANDLE SecureHandle
);



KERNEL_ENTRY KERNEL_EXPORT LOUSTATUS NtOpenProcess(
            PHANDLE            ProcessHandle,
             ACCESS_MASK        DesiredAccess,
             POBJECT_ATTRIBUTES ObjectAttributes,
   PCLIENT_ID         ClientId
);


void PcreateProcessNotifyRoutine(
   HANDLE ParentId,
   HANDLE ProcessId,
   BOOLEAN Create
);

void PcreateThreadNotifyRoutine(
   HANDLE ProcessId,
   HANDLE ThreadId,
   BOOLEAN Create
);

LOUSTATUS PgetLocationString(
    PVOID Context,
       PZZWSTR *LocationStrings
);

void Phalexaminembr(
    struct _DEVICE_OBJECT* DeviceObject,
    ULONG SectorSize,
    ULONG MBRTypeIdentifier,
   PVOID *Buffer
);

void PcreateProcessNotifyRoutineEx(
	           PEPROCESS Process,
	                HANDLE ProcessId,
	  PPS_CREATE_NOTIFY_INFO CreateInfo
);


LOUSTATUS PsAllocSiloContextSlot(
    ULONG_PTR Reserved,
   ULONG     *ReturnedContextSlot
);

PESILO PsAttachSiloToCurrentThread(
   PESILO Silo
);



LOUSTATUS PsCreateSiloContext(
             PESILO                        Silo,
             ULONG                         Size,
             POOL_TYPE                     PoolType,
   SILO_CONTEXT_CLEANUP_CALLBACK ContextCleanupCallback,
				 PVOID                         *ReturnedSiloContext
);

void PsDereferenceSiloContext(
   PVOID SiloContext
);

void PsDetachSiloFromCurrentThread(
   PESILO PreviousSilo
);

LOUSTATUS PsFreeSiloContextSlot(
   ULONG ContextSlot
);

HANDLE PsGetCurrentProcessId();

PESILO PsGetCurrentServerSilo();

PESILO PsGetCurrentSilo();

PETHREAD PsGetCurrentThread();

HANDLE PsGetCurrentThreadId();

PVOID PsGetCurrentThreadTeb();

PESILO PsGetEffectiveServerSilo(
   PESILO Silo
);

PESILO PsGetHostSilo();

LOUSTATUS PsGetJobServerSilo(
   PEJOB  Job,
            PESILO *ServerSilo
);

LOUSTATUS PsGetJobSilo(
    PEJOB  Job,
   PESILO *Silo
);

PESILO PsGetParentSilo(
   PEJOB Job
);

LOUSTATUS PsGetPermanentSiloContext(
   PESILO Silo,
   ULONG  ContextSlot,
	   PVOID  *ReturnedSiloContext
);

LONGLONG PsGetProcessCreateTimeQuadPart(
   PEPROCESS Process
);

LOUSTATUS PsGetProcessExitStatus(
   PEPROCESS Process
);

HANDLE PsGetProcessId(
   PEPROCESS Process
);

ULONGLONG PsGetProcessStartKey(
   PEPROCESS Process
);

ULONG PsGetServerSiloActiveConsoleId(
  PESILO Silo
);

GUID * PsGetSiloContainerId(
   PESILO Silo
);

LOUSTATUS PsGetSiloContext(
   PESILO Silo,
   ULONG  ContextSlot,
	   PVOID  *ReturnedSiloContext
);

ULONG PsGetSiloMonitorContextSlot(
   PSILO_MONITOR Monitor
);

LONGLONG PsGetThreadCreateTime(
   PETHREAD Thread
);

LOUSTATUS PsGetThreadExitStatus(
   PETHREAD Thread
);

HANDLE PsGetThreadId(
   PETHREAD Thread
);

HANDLE PsGetThreadProcessId(
  PETHREAD Thread
);

PESILO PsGetThreadServerSilo(
   PETHREAD Thread
);

LOUSTATUS PsInsertPermanentSiloContext(
   PESILO Silo,
   ULONG  ContextSlot,
   PVOID  SiloContext
);

LOUSTATUS PsInsertSiloContext(
   PESILO Silo,
   ULONG  ContextSlot,
   PVOID  SiloContext
);

BOOLEAN PsIsHostSilo(
   PESILO Silo
);

LOUSTATUS PsMakeSiloContextPermanent(
   PESILO Silo,
   ULONG  ContextSlot
);

void PsReferenceSiloContext(
   PVOID SiloContext
);

LOUSTATUS PsRemoveCreateThreadNotifyRoutine(
   PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine
);

LOUSTATUS PsRemoveLoadImageNotifyRoutine(
   PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine
);

LOUSTATUS PsRemoveSiloContext(
   PESILO Silo,
   ULONG  ContextSlot,
	   PVOID  *RemovedSiloContext
);

LOUSTATUS PsReplaceSiloContext(
         PESILO Silo,
         ULONG  ContextSlot,
         PVOID  NewSiloContext,
  PVOID  *OldSiloContext
);

LOUSTATUS PsSetCreateProcessNotifyRoutine(
   PCREATE_PROCESS_NOTIFY_ROUTINE NotifyRoutine,
   BOOLEAN                        Remove
);

LOUSTATUS PsSetCreateProcessNotifyRoutineEx(
   PCREATE_PROCESS_NOTIFY_ROUTINE_EX NotifyRoutine,
   BOOLEAN                           Remove
);

LOUSTATUS PsSetCreateProcessNotifyRoutineEx2(
   PSCREATEPROCESSNOTIFYTYPE NotifyType,
   PVOID                     NotifyInformation,
   BOOLEAN                   Remove
);

LOUSTATUS PsSetCreateThreadNotifyRoutine(
   PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine
);

LOUSTATUS PsSetCreateThreadNotifyRoutineEx(
   PSCREATETHREADNOTIFYTYPE NotifyType,
   PVOID                    NotifyInformation
);

LOUSTATUS PsSetLoadImageNotifyRoutine(
   PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine
);

LOUSTATUS PsSetLoadImageNotifyRoutineEx(
   PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine,
   ULONG_PTR                  Flags
);

LOUSTATUS PsStartSiloMonitor(
   PSILO_MONITOR Monitor
);

void PsTerminateServerSilo(
   PESILO   ServerSilo,
	   LOUSTATUS ExitStatus
);

void PsUnregisterSiloMonitor(
   PSILO_MONITOR Monitor
);

//RTL_RUN_ONCE_INIT_FN (
//	 PRTL_RUN_ONCE RunOnce,
//	 PVOID Parameter,
//	 PVOID *Context
//);

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



//void WheaAdd2Ptr(
//   P,
//   I
//);

PVOID WheaErrorRecordBuilderAddPacket(
    PLHEA_ERROR_RECORD    Record,
    LHEA_ERROR_PACKET_V2 Packet,
        UINT32                MaxSectionCount
);

PVOID WheaErrorRecordBuilderAddSection(
              PLHEA_ERROR_RECORD                         Record,
                  UINT32                                     MaxSectionCount,
                  UINT32                                     SectionLength,
                  LHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS Flags,
                  GUID                                       SectionType,
    PVOID                                      DescriptorOut
);

void WheaErrorRecordBuilderInit(
  PLHEA_ERROR_RECORD  Record,
  UINT32              RecordLength,
  LHEA_ERROR_SEVERITY Severity,
  GUID                Notify
);


LOUSTATUS WheaRegisterErrorSourceOverride(
   LHEA_ERROR_SOURCE_OVERRIDE_SETTINGS   OverrideSettings,
   PLHEA_ERROR_SOURCE_CONFIGURATION      OverrideConfig,
   PLHEA_SIGNAL_HANDLER_OVERRIDE_CALLBACK OverrideCallback
);

BOOLEAN WheaSignalHandlerOverride(
                  LHEA_ERROR_SOURCE_TYPE SourceType,
    UINT_PTR               Context
);

void WheaUnregisterErrorSourceOverride(
   LHEA_ERROR_SOURCE_TYPE Type,
   ULONG32                OverrideErrorSourceId
);

NTSYSAPI LOUSTATUS ZwAllocateLocallyUniqueId(
  PLUID Luid
);


NTSYSAPI LOUSTATUS ZwDeviceIoControlFile(
              HANDLE           FileHandle,
    HANDLE           Event,
    PIO_APC_ROUTINE  ApcRoutine,
    PVOID            ApcContext,
             PIO_STATUS_BLOCK IoStatusBlock,
              ULONG            IoControlCode,
    PVOID            InputBuffer,
              ULONG            InputBufferLength,
   PVOID            OutputBuffer,
              ULONG            OutputBufferLength
);

NTSYSAPI LOUSTATUS ZwOpenProcess(
            PHANDLE            ProcessHandle,
             ACCESS_MASK        DesiredAccess,
             POBJECT_ATTRIBUTES ObjectAttributes,
   PCLIENT_ID         ClientId
);

NTSYSAPI LOUSTATUS ZwPowerInformation(
              POWER_INFORMATION_LEVEL InformationLevel,
    PVOID                   InputBuffer,
              ULONG                   InputBufferLength,
   PVOID                   OutputBuffer,
              ULONG                   OutputBufferLength
);

NTSYSAPI LOUSTATUS ZwQueryVolumeInformationFile(
    HANDLE               FileHandle,
   PIO_STATUS_BLOCK     IoStatusBlock,
   PVOID                FsInformation,
    ULONG                Length,
    FS_INFORMATION_CLASS FsInformationClass
);

NTSYSAPI LOUSTATUS ZwSetInformationThread(
   HANDLE          ThreadHandle,
   THREADINFOCLASS ThreadInformationClass,
   PVOID           ThreadInformation,
   ULONG           ThreadInformationLength
);


NTSYSAPI LOUSTATUS ZwTerminateProcess(
   HANDLE   ProcessHandle,
             LOUSTATUS ExitStatus
);



#endif