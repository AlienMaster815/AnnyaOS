

#ifndef _NTDDK_H
#define _NTDDK_H

#include <NtAPI.h>
#include "irp.h"
#include "ntoapi.h"
#include "wdm.h"

typedef struct _SIGNAL_REG_VALUE {
	UINT8* RegName;
	UINT32 MsrAddr;
	UINT64 Value;
} SIGNAL_REG_VALUE, * PSIGNAL_REG_VALUE;


typedef struct _WHEA_ACPI_HEADER {
	UINT32 Signature;
	UINT32 Length;
	UINT8  Revision;
	UINT8  Checksum;
	UINT8  OemId[6];
	UINT64 OemTableId;
	UINT32 OemRevision;
	UINT32 CreatorId;
	UINT32 CreatorRevision;
} WHEA_ACPI_HEADER, * PWHEA_ACPI_HEADER;

typedef enum _STATE_LOCATION_TYPE {
	LocationTypeRegistry,
	LocationTypeFileSystem,
	LocationTypeMaximum
} STATE_LOCATION_TYPE;


typedef enum _BDCB_CALLBACK_TYPE {
	BdCbStatusUpdate,
	BdCbInitializeImage
} BDCB_CALLBACK_TYPE, * PBDCB_CALLBACK_TYPE;

typedef enum _BDCB_CLASSIFICATION {
	BdCbClassificationUnknownImage,
	BdCbClassificationKnownGoodImage,
	BdCbClassificationKnownBadImage,
	BdCbClassificationKnownBadImageBootCritical,
	BdCbClassificationEnd
} BDCB_CLASSIFICATION, * PBDCB_CLASSIFICATION;

typedef enum _BDCB_STATUS_UPDATE_TYPE {
	BdCbStatusPrepareForDependencyLoad,
	BdCbStatusPrepareForDriverLoad,
	BdCbStatusPrepareForUnload
} BDCB_STATUS_UPDATE_TYPE, * PBDCB_STATUS_UPDATE_TYPE;

typedef enum _HAL_QUERY_INFORMATION_CLASS {
	HalInstalledBusInformation,
	HalProfileSourceInformation,
	HalInformationClassUnused1,
	HalPowerInformation,
	HalProcessorSpeedInformation,
	HalCallbackInformation,
	HalMapRegisterInformation,
	HalMcaLogInformation,
	HalFrameBufferCachingInformation,
	HalDisplayBiosInformation,
	HalProcessorFeatureInformation,
	HalNumaTopologyInterface,
	HalErrorInformation,
	HalCmcLogInformation,
	HalCpeLogInformation,
	HalQueryMcaInterface,
	HalQueryAMLIIllegalIOPortAddresses,
	HalQueryMaxHotPlugMemoryAddress,
	HalPartitionIpiInterface,
	HalPlatformInformation,
	HalQueryProfileSourceList,
	HalInitLogInformation,
	HalFrequencyInformation,
	HalProcessorBrandString,
	HalHypervisorInformation,
	HalPlatformTimerInformation,
	HalAcpiAuditInformation,
	HalIrtInformation,
	HalSecondaryInterruptInformation,
	HalParkingPageInformation,
	HalNumaRangeTableInformation,
	HalChannelTopologyInformation,
	HalExternalCacheInformation,
	HalQueryDebuggerInformation,
	HalFwBootPerformanceInformation,
	HalFwS3PerformanceInformation,
	HalGetChannelPowerInformation,
	HalQueryStateElementInformation,
	HalPsciInformation,
	HalInterruptControllerInformation,
	HalQueryIommuReservedRegionInformation,
	HalQueryArmErrataInformation,
	HalQueryProcessorEfficiencyInformation,
	HalQueryAcpiWakeAlarmSystemPowerStateInformation,
	HalQueryProfileNumberOfCounters,
	HalQueryHyperlaunchEntrypoint,
	HalHardwareWatchdogInformation,
	HalDmaRemappingInformation,
	HalQueryUnused0001,
	HalHeterogeneousMemoryAttributesInterface,
	HalQueryPerDeviceMsiLimitInformation,
	HalQueryProfileCorruptionStatus,
	HalQueryProfileCounterOwnership
} HAL_QUERY_INFORMATION_CLASS, * PHAL_QUERY_INFORMATION_CLASS;

typedef enum _HAL_SET_INFORMATION_CLASS {
	HalProfileSourceInterval,
	HalProfileSourceInterruptHandler,
	HalMcaRegisterDriver,
	HalKernelErrorHandler,
	HalCmcRegisterDriver,
	HalCpeRegisterDriver,
	HalMcaLog,
	HalCmcLog,
	HalCpeLog,
	HalGenerateCmcInterrupt,
	HalProfileSourceTimerHandler,
	HalEnlightenment,
	HalProfileDpgoSourceInterruptHandler,
	HalRegisterSecondaryInterruptInterface,
	HalSetChannelPowerInformation,
	HalI386ExceptionChainTerminatorInformation,
	HalSetResetParkDisposition,
	HalSetPsciSuspendMode,
	HalSetHvciEnabled,
	HalSetProcessorTraceInterruptHandler,
	HalProfileSourceAdd,
	HalProfileSourceRemove,
	HalSetSwInterruptHandler,
	HalSetClockTimerMinimumInterval
} HAL_SET_INFORMATION_CLASS, * PHAL_SET_INFORMATION_CLASS;

typedef enum {
	ApicDestinationModePhysical,
	ApicDestinationModeLogicalFlat,
	ApicDestinationModeLogicalClustered,
	ApicDestinationModeUnknown
} HAL_APIC_DESTINATION_MODE, * PHAL_APIC_DESTINATION_MODE;

typedef enum {
	KdConfigureDeviceAndContinue,
	KdSkipDeviceAndContinue,
	KdConfigureDeviceAndStop,
	KdSkipDeviceAndStop
} KD_CALLBACK_ACTION, * PKD_CALLBACK_ACTION;

typedef enum {
	KdNameSpacePCI,
	KdNameSpaceACPI,
	KdNameSpaceAny,
	KdNameSpaceNone,
	KdNameSpaceMax
} KD_NAMESPACE_ENUM, * PKD_NAMESPACE_ENUM;

typedef struct _BDCB_IMAGE_INFORMATION {
	BDCB_CLASSIFICATION Classification;
	ULONG               ImageFlags;
	UNICODE_STRING      ImageName;
	UNICODE_STRING      RegistryPath;
	UNICODE_STRING      CertificatePublisher;
	UNICODE_STRING      CertificateIssuer;
	PVOID               ImageHash;
	PVOID               CertificateThumbprint;
	ULONG               ImageHashAlgorithm;
	ULONG               ThumbprintHashAlgorithm;
	ULONG               ImageHashLength;
	ULONG               CertificateThumbprintLength;
} BDCB_IMAGE_INFORMATION, * PBDCB_IMAGE_INFORMATION;

#ifndef _BUS_DATA_TYPE
#define _BUS_DATA_TYPE
typedef enum _BUS_DATA_TYPE {
	Cmos = 0,
	EisaConfiguration = 1,
	Pos = 2,
	CbusConfiguration = 3,
	PCIConfiguration = 4,
	VMEConfiguration = 5,
	NuBusConfiguration = 6,
	PCMCIAConfiguration = 7,
	MPIConfiguration = 8,
	MPSAConfiguration = 9,
	PNPISAConfiguration = 10,
	SgiInternalConfiguration = 11,
	MaximumBusDataType = 12,
} BUS_DATA_TYPE, * PBUS_DATA_TYPE;
#endif

typedef struct _CONFIGURATION_INFORMATION {
	ULONG   DiskCount;
	ULONG   FloppyCount;
	ULONG   CdRomCount;
	ULONG   TapeCount;
	ULONG   ScsiPortCount;
	ULONG   SerialCount;
	ULONG   ParallelCount;
	BOOLEAN AtDiskPrimaryAddressClaimed;
	BOOLEAN AtDiskSecondaryAddressClaimed;
	ULONG   Version;
	ULONG   MediumChangerCount;
} CONFIGURATION_INFORMATION, * PCONFIGURATION_INFORMATION;


typedef struct _BDCB_STATUS_UPDATE_CONTEXT {
	BDCB_STATUS_UPDATE_TYPE StatusType;
} BDCB_STATUS_UPDATE_CONTEXT, * PBDCB_STATUS_UPDATE_CONTEXT;


typedef struct _CONTEXT {
	ULONG              ContextFlags;
	ULONG              Dr0;
	ULONG              Dr1;
	ULONG              Dr2;
	ULONG              Dr3;
	ULONG              Dr6;
	ULONG              Dr7;
	FLOATING_SAVE_AREA FloatSave;
	ULONG              SegGs;
	ULONG              SegFs;
	ULONG              SegEs;
	ULONG              SegDs;
	ULONG              Edi;
	ULONG              Esi;
	ULONG              Ebx;
	ULONG              Edx;
	ULONG              Ecx;
	ULONG              Eax;
	ULONG              Ebp;
	ULONG              Eip;
	ULONG              SegCs;
	ULONG              EFlags;
	ULONG              Esp;
	ULONG              SegSs;
	UCHAR*              ExtendedRegisters;
} CONTEXT;



typedef struct _CONTROLLER_OBJECT {
	SHORT        Type;
	SHORT        Size;
	PVOID         ControllerExtension;
	KDEVICE_QUEUE DeviceWaitQueue;
	ULONG         Spare1;
	LARGE_INTEGER Spare2;
} CONTROLLER_OBJECT, * PCONTROLLER_OBJECT;

typedef struct CORRELATION_VECTOR {
	CHAR Version;
	CHAR* Vector;
} CORRELATION_VECTOR;


typedef struct _CUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG {
	ULONG  Size;
	PCWSTR TriggerId;
} CUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG, * PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG;

typedef struct {
	UCHAR   Type;
	BOOLEAN Valid;
	union {
		UCHAR Reserved[2];
		struct {
			UCHAR BitWidth;
			UCHAR AccessSize;
		};
	};
	PUCHAR  TranslatedAddress;
	ULONG   Length;
} DEBUG_DEVICE_ADDRESS, * PDEBUG_DEVICE_ADDRESS;

typedef struct {
	PHYSICAL_ADDRESS Start;
	PHYSICAL_ADDRESS MaxEnd;
	PVOID            VirtualAddress;
	ULONG            Length;
	BOOLEAN          Cached;
	BOOLEAN          Aligned;
} DEBUG_MEMORY_REQUIREMENTS, * PDEBUG_MEMORY_REQUIREMENTS;

typedef struct _EFI_ACPI_RAS_SIGNAL_TABLE {
	WHEA_ACPI_HEADER Header;
	UINT32           NumberRecord;
	SIGNAL_REG_VALUE* Entries;
} EFI_ACPI_RAS_SIGNAL_TABLE, * PEFI_ACPI_RAS_SIGNAL_TABLE;


typedef struct _FILE_ALIGNMENT_INFORMATION {
	ULONG AlignmentRequirement;
} FILE_ALIGNMENT_INFORMATION, * PFILE_ALIGNMENT_INFORMATION;

typedef struct _FILE_ATTRIBUTE_TAG_INFORMATION {
	ULONG FileAttributes;
	ULONG ReparseTag;
} FILE_ATTRIBUTE_TAG_INFORMATION, * PFILE_ATTRIBUTE_TAG_INFORMATION;

typedef struct _FILE_DISPOSITION_INFORMATION {
	BOOLEAN DeleteFile;
} FILE_DISPOSITION_INFORMATION, * PFILE_DISPOSITION_INFORMATION;

typedef struct _FILE_END_OF_FILE_INFORMATION {
	LARGE_INTEGER EndOfFile;
} FILE_END_OF_FILE_INFORMATION, * PFILE_END_OF_FILE_INFORMATION;

typedef struct _FILE_NAME_INFORMATION {
	ULONG FileNameLength;
	WCHAR FileName[1];
} FILE_NAME_INFORMATION, * PFILE_NAME_INFORMATION;

typedef struct _FILE_VALID_DATA_LENGTH_INFORMATION {
	LARGE_INTEGER ValidDataLength;
} FILE_VALID_DATA_LENGTH_INFORMATION, * PFILE_VALID_DATA_LENGTH_INFORMATION;


void HalExamineMBR(
	  PDEVICE_OBJECT DeviceObject,
	  ULONG          SectorSize,
	  ULONG          MBRTypeIdentifier,
	 PVOID* Buffer
);


typedef HalQuerySystemInformation* pHalQuerySystemInformation;
typedef HalSetSystemInformation* pHalSetSystemInformation;
typedef HalQueryBusSlots* pHalQueryBusSlots;
typedef void (*pHalExamineMBR)( PDEVICE_OBJECT, ULONG,  ULONG,  PVOID*);
typedef HalIoReadPartitionTable* pHalIoReadPartitionTable;
typedef HalIoSetPartitionInformation* pHalIoSetPartitionInformation;
typedef HalIoWritePartitionTable* pHalIoWritePartitionTable;
typedef HalHandlerForBus* pHalHandlerForBus;
typedef HalReferenceBusHandler* pHalReferenceBusHandler;
typedef HalInitPnpDriver* pHalInitPnpDriver;
typedef HalInitPowerManagement* pHalInitPowerManagement;
typedef HalGetDmaAdapter* pHalGetDmaAdapter;
typedef HalGetInterruptTranslator* pHalGetInterruptTranslator;
typedef HalStartMirroring* pHalStartMirroring;
typedef HalEndMirroring* pHalEndMirroring;
typedef HalMirrorPhysicalMemory* pHalMirrorPhysicalMemory;
typedef HalEndOfBoot* pHalEndOfBoot;
typedef HalMirrorVerify* pHalMirrorVerify;
typedef HalGetAcpiTable* pHalGetAcpiTable;
typedef HalSetPciErrorHandlerCallback* pHalSetPciErrorHandlerCallback;
typedef HalGetPrmCache* pHalGetPrmCache;

typedef struct {
	ULONG                          Version;
	pHalQuerySystemInformation     HalQuerySystemInformation;
	pHalSetSystemInformation       HalSetSystemInformation;
	pHalQueryBusSlots              HalQueryBusSlots;
	ULONG                          Spare1;
	pHalExamineMBR                 HalExamineMBR;
	pHalIoReadPartitionTable       HalIoReadPartitionTable;
	pHalIoSetPartitionInformation  HalIoSetPartitionInformation;
	pHalIoWritePartitionTable      HalIoWritePartitionTable;
	pHalHandlerForBus              HalReferenceHandlerForBus;
	pHalReferenceBusHandler        HalReferenceBusHandler;
	pHalReferenceBusHandler        HalDereferenceBusHandler;
	pHalInitPnpDriver              HalInitPnpDriver;
	pHalInitPowerManagement        HalInitPowerManagement;
	pHalGetDmaAdapter              HalGetDmaAdapter;
	pHalGetInterruptTranslator     HalGetInterruptTranslator;
	pHalStartMirroring             HalStartMirroring;
	pHalEndMirroring               HalEndMirroring;
	pHalMirrorPhysicalMemory       HalMirrorPhysicalMemory;
	pHalEndOfBoot                  HalEndOfBoot;
	pHalMirrorVerify               HalMirrorVerify;
	pHalGetAcpiTable               HalGetCachedAcpiTable;
	pHalSetPciErrorHandlerCallback HalSetPciErrorHandlerCallback;
	pHalGetPrmCache                HalGetPrmCache;
} HAL_DISPATCH, * PHAL_DISPATCH;


typedef enum _HARDWARE_COUNTER_TYPE {
	PMCCounter,
	MaxHardwareCounterType
} HARDWARE_COUNTER_TYPE, * PHARDWARE_COUNTER_TYPE;

typedef struct _HARDWARE_COUNTER {
	HARDWARE_COUNTER_TYPE Type;
	ULONG                 Reserved;
	ULONG64               Index;
} HARDWARE_COUNTER, * PHARDWARE_COUNTER;

typedef struct _IMAGE_INFO {
	union {
		ULONG Properties;
		struct {
			ULONG ImageAddressingMode : 8;
			ULONG SystemModeImage : 1;
			ULONG ImageMappedToAllPids : 1;
			ULONG ExtendedInfoPresent : 1;
			ULONG MachineTypeMismatch : 1;
			ULONG ImageSignatureLevel : 4;
			ULONG ImageSignatureType : 3;
			ULONG ImagePartialMap : 1;
			ULONG Reserved : 12;
		};
	};
	PVOID  ImageBase;
	ULONG  ImageSelector;
	SIZE_T ImageSize;
	ULONG  ImageSectionNumber;
} IMAGE_INFO, * PIMAGE_INFO;

typedef struct _IMAGE_INFO_EX {
	SIZE_T              Size;
	IMAGE_INFO          ImageInfo;
	struct _FILE_OBJECT* FileObject;
} IMAGE_INFO_EX, * PIMAGE_INFO_EX;

typedef struct _IO_FOEXT_SHADOW_FILE {
	struct _FILE_OBJECT* BackingFileObject;
	PVOID        BackingFltInstance;
} IO_FOEXT_SHADOW_FILE, * PIO_FOEXT_SHADOW_FILE;

typedef struct _KEY_CACHED_INFORMATION {
	LARGE_INTEGER LastWriteTime;
	ULONG         TitleIndex;
	ULONG         SubKeys;
	ULONG         MaxNameLen;
	ULONG         Values;
	ULONG         MaxValueNameLen;
	ULONG         MaxValueDataLen;
	ULONG         NameLength;
} KEY_CACHED_INFORMATION, * PKEY_CACHED_INFORMATION;

typedef struct _KEY_NAME_INFORMATION {
	ULONG NameLength;
	WCHAR Name[1];
} KEY_NAME_INFORMATION, * PKEY_NAME_INFORMATION;

typedef struct _KEY_VIRTUALIZATION_INFORMATION {
	ULONG VirtualizationCandidate : 1;
	ULONG VirtualizationEnabled : 1;
	ULONG VirtualTarget : 1;
	ULONG VirtualStore : 1;
	ULONG VirtualSource : 1;
	ULONG Reserved : 27;
} KEY_VIRTUALIZATION_INFORMATION, * PKEY_VIRTUALIZATION_INFORMATION;

typedef struct _KUSER_SHARED_DATA {
	ULONG                         TickCountLowDeprecated;
	ULONG                         TickCountMultiplier;
	KSYSTEM_TIME                  InterruptTime;
	KSYSTEM_TIME                  SystemTime;
	KSYSTEM_TIME                  TimeZoneBias;
	USHORT                        ImageNumberLow;
	USHORT                        ImageNumberHigh;
	WCHAR                         NtSystemRoot[260];
	ULONG                         MaxStackTraceDepth;
	ULONG                         CryptoExponent;
	ULONG                         TimeZoneId;
	ULONG                         LargePageMinimum;
	ULONG                         AitSamplingValue;
	ULONG                         AppCompatFlag;
	ULONGLONG                     RNGSeedVersion;
	ULONG                         GlobalValidationRunlevel;
	LONG                          TimeZoneBiasStamp;
	ULONG                         NtBuildNumber;
	NT_PRODUCT_TYPE               NtProductType;
	BOOLEAN                       ProductTypeIsValid;
	BOOLEAN                       Reserved0[1];
	USHORT                        NativeProcessorArchitecture;
	ULONG                         NtMajorVersion;
	ULONG                         NtMinorVersion;
	BOOLEAN*                       ProcessorFeatures;
	ULONG                         Reserved1;
	ULONG                         Reserved3;
	ULONG                         TimeSlip;
	ALTERNATIVE_ARCHITECTURE_TYPE AlternativeArchitecture;
	ULONG                         BootId;
	LARGE_INTEGER                 SystemExpirationDate;
	ULONG                         SuiteMask;
	BOOLEAN                       KdDebuggerEnabled;
	union {
		UCHAR MitigationPolicies;
		struct {
			UCHAR NXSupportPolicy : 2;
			UCHAR SEHValidationPolicy : 2;
			UCHAR CurDirDevicesSkippedForDlls : 2;
			UCHAR Reserved : 2;
		};
	};
	USHORT                        CyclesPerYield;
	ULONG                         ActiveConsoleId;
	ULONG                         DismountCount;
	ULONG                         ComPlusPackage;
	ULONG                         LastSystemRITEventTickCount;
	ULONG                         NumberOfPhysicalPages;
	BOOLEAN                       SafeBootMode;
	union {
		UCHAR VirtualizationFlags;
		struct {
			UCHAR ArchStartedInEl2 : 1;
			UCHAR QcSlIsSupported : 1;
		};
	};
	UCHAR                         Reserved12[2];
	union {
		ULONG SharedDataFlags;
		struct {
			ULONG DbgErrorPortPresent : 1;
			ULONG DbgElevationEnabled : 1;
			ULONG DbgVirtEnabled : 1;
			ULONG DbgInstallerDetectEnabled : 1;
			ULONG DbgLkgEnabled : 1;
			ULONG DbgDynProcessorEnabled : 1;
			ULONG DbgConsoleBrokerEnabled : 1;
			ULONG DbgSecureBootEnabled : 1;
			ULONG DbgMultiSessionSku : 1;
			ULONG DbgMultiUsersInSessionSku : 1;
			ULONG DbgStateSeparationEnabled : 1;
			ULONG SpareBits : 21;
		} DUMMYSTRUCTNAME2;
	} DUMMYUNIONNAME2;
	ULONG                         DataFlagsPad[1];
	ULONGLONG                     TestRetInstruction;
	LONGLONG                      QpcFrequency;
	ULONG                         SystemCall;
	ULONG                         Reserved2;
	ULONGLONG                     SystemCallPad[2];
	union {
		KSYSTEM_TIME TickCount;
		ULONG64      TickCountQuad;
		struct {
			ULONG ReservedTickCountOverlay[3];
			ULONG TickCountPad[1];
		} DUMMYSTRUCTNAME;
	} DUMMYUNIONNAME3;
	ULONG                         Cookie;
	ULONG                         CookiePad[1];
	LONGLONG                      ConsoleSessionForegroundProcessId;
	ULONGLONG                     TimeUpdateLock;
	ULONGLONG                     BaselineSystemTimeQpc;
	ULONGLONG                     BaselineInterruptTimeQpc;
	ULONGLONG                     QpcSystemTimeIncrement;
	ULONGLONG                     QpcInterruptTimeIncrement;
	UCHAR                         QpcSystemTimeIncrementShift;
	UCHAR                         QpcInterruptTimeIncrementShift;
	USHORT                        UnparkedProcessorCount;
	ULONG                         EnclaveFeatureMask[4];
	ULONG                         TelemetryCoverageRound;
	USHORT                        UserModeGlobalLogger[16];
	ULONG                         ImageFileExecutionOptions;
	ULONG                         LangGenerationCount;
	ULONGLONG                     Reserved4;
	ULONGLONG                     InterruptTimeBias;
	ULONGLONG                     QpcBias;
	ULONG                         ActiveProcessorCount;
	UCHAR                         ActiveGroupCount;
	UCHAR                         Reserved9;
	union {
		USHORT QpcData;
		struct {
			UCHAR QpcBypassEnabled;
			UCHAR QpcShift;
		};
	};
	LARGE_INTEGER                 TimeZoneBiasEffectiveStart;
	LARGE_INTEGER                 TimeZoneBiasEffectiveEnd;
	XSTATE_CONFIGURATION          XState;
	KSYSTEM_TIME                  FeatureConfigurationChangeStamp;
	ULONG                         Spare;
	ULONG64                       UserPointerAuthMask;
} KUSER_SHARED_DATA, * PKUSER_SHARED_DATA;


typedef struct _MM_COPY_ADDRESS {
	union {
		PVOID            VirtualAddress;
		PHYSICAL_ADDRESS PhysicalAddress;
	};
} MM_COPY_ADDRESS, * PMMCOPY_ADDRESS;

typedef enum {
  MaxPayload128Bytes,
  MaxPayload256Bytes,
  MaxPayload512Bytes,
  MaxPayload1024Bytes,
  MaxPayload2048Bytes,
  MaxPayload4096Bytes
} PCI_EXPRESS_MAX_PAYLOAD_SIZE;

typedef enum {
  BtiVbarNone,
  BtiVbarTrapHvc,
  BtiVbarTrapSmc,
  BtiVbarBhbDsbIsb,
  BtiVbarBhbSb,
  BtiVbarBhbClr
} PCR_BTI_VBAR_INDEX;

typedef enum _PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR_TYPE {
	ResourceTypeSingle,
	ResourceTypeRange,
	ResourceTypeExtendedCounterConfiguration,
	ResourceTypeOverflow,
	ResourceTypeEventBuffer,
	ResourceTypeIdenitificationTag,
	ResourceTypeMax
} PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR_TYPE;

typedef struct _PHYSICAL_COUNTER_EVENT_BUFFER_CONFIGURATION {
  PPHYSICAL_COUNTER_EVENT_BUFFER_OVERFLOW_HANDLER OverflowHandler;
  ULONG                                           CustomEventBufferEntrySize;
  ULONG                                           EventThreshold;
} PHYSICAL_COUNTER_EVENT_BUFFER_CONFIGURATION, *PPHYSICAL_COUNTER_EVENT_BUFFER_CONFIGURATION;

typedef struct _PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR {
  PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR_TYPE Type;
  ULONG                                     Flags;
  union {
	ULONG                                       CounterIndex;
	struct {
	  ULONG Begin;
	  ULONG End;
	} Range;
	PPHYSICAL_COUNTER_OVERFLOW_HANDLER          OverflowHandler;
	PHYSICAL_COUNTER_EVENT_BUFFER_CONFIGURATION EventBufferConfiguration;
	ULONG                                       IdentificationTag;
  } u;
} PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR, *PPHYSICAL_COUNTER_RESOURCE_DESCRIPTOR;


typedef struct _PHYSICAL_COUNTER_RESOURCE_LIST {
  ULONG                                Count;
  PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR* Descriptors;
} PHYSICAL_COUNTER_RESOURCE_LIST, *PPHYSICAL_COUNTER_RESOURCE_LIST;


NTSTATUS IoAllocateAdapterChannel(
	PADAPTER_OBJECT AdapterObject,
	PDEVICE_OBJECT  DeviceObject,
	ULONG           NumberOfMapRegisters,
	PDRIVER_CONTROL ExecutionRoutine,
	PVOID           Context
);

BOOLEAN WheaSignalHandlerOverrideCallback(
	  UINT_PTR Context
);

void BootDriverCallbackFunction(
	PVOID CallbackContext,
	BDCB_CALLBACK_TYPE Classification,
	PBDCB_IMAGE_INFORMATION ImageInformation
);


void CUSTOM_SYSTEM_EVENT_TRIGGER_INIT(
	PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG Config,
	PCWSTR                              TriggerId
);


void DriverReinitialize(
	          _DRIVER_OBJECT* DriverObject,
	 PVOID Context,
	           ULONG Count
);

//void ExFreePool(
//	uintptr_t a
//);

void ExpandStackCallout(
	 PVOID Parameter
);

void ExRaiseDatatypeMisalignment();

void ExRaiseAccessViolation();

NTSTATUS ExUuidCreate(
	 UUID* Uuid
);

NTSTATUS HalAllocateHardwareCounters(
	PGROUP_AFFINITY                 GroupAffinty,
	  ULONG                           GroupCount,
	  PPHYSICAL_COUNTER_RESOURCE_LIST ResourceList,
	 PHANDLE                         CounterSetHandle
);


NTSTATUS HalFreeHardwareCounters(
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
	           PDEVICE_OBJECT     DeviceObject,
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

NTSTATUS IoDecrementKeepAliveCount(
	  PFILE_OBJECT FileObject,
	  PEPROCESS    Process
);


void IoDeleteController(
	 PCONTROLLER_OBJECT ControllerObject
);

void IoFreeController(
	 PCONTROLLER_OBJECT ControllerObject
);

NTSTATUS IoGetActivityIdIrp(
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

NTSTATUS IoIncrementKeepAliveCount(
	  PFILE_OBJECT FileObject,
	  PEPROCESS    Process
);

LOGICAL IoIsValidIrpStatus(
	 NTSTATUS Status
);

PIRP IoMakeAssociatedIrp(
	 PIRP  Irp,
	 CCHAR StackSize
);

NTSTATUS IoPropagateActivityIdToThread(
	  PIRP    Irp,
	 LPGUID  PropagatedId,
	LPCGUID* OriginalId
);

NTSTATUS IoQueryFullDriverPath(
	  PDRIVER_OBJECT  DriverObject,
	 PUNICODE_STRING FullPath
);

void IoRaiseHardError(
	           PIRP           Irp,
	 PVPB           Vpb,
	           PDEVICE_OBJECT RealDeviceObject
);

BOOLEAN IoRaiseInformationalHardError(
	           NTSTATUS        ErrorStatus,
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

NTSTATUS IoReportDetectedDevice(
	           PDRIVER_OBJECT                 DriverObject,
	           INTERFACE_TYPE                 LegacyBusType,
	           ULONG                          BusNumber,
	           ULONG                          SlotNumber,
	 PCM_RESOURCE_LIST              ResourceList,
	 PIO_RESOURCE_REQUIREMENTS_LIST ResourceRequirements,
	           BOOLEAN                        ResourceAssigned,
	       PDEVICE_OBJECT* DeviceObject
);

NTSTATUS IoReportResourceForDetection(
	           PDRIVER_OBJECT    DriverObject,
	 PCM_RESOURCE_LIST DriverList,
	 ULONG             DriverListSize,
	 PDEVICE_OBJECT    DeviceObject,
	 PCM_RESOURCE_LIST DeviceList,
	 ULONG             DeviceListSize,
	          PBOOLEAN          ConflictDetected
);

NTSTATUS IoReportRootDevice(
	 PDRIVER_OBJECT DriverObject
);
NTSTATUS IoSetActivityIdIrp(
	           PIRP    Irp,
	 LPCGUID Guid
);

LPCGUID IoSetActivityIdThread(
	LPCGUID ActivityId
);
void IoSetHardErrorOrVerifyDevice(
	 PIRP           Irp,
	 PDEVICE_OBJECT DeviceObject
);
void IoSetMasterIrpStatus(
	  PIRP     MasterIrp,
	      NTSTATUS Status
);
NTSTATUS IoSetShadowFileInformation(
	 PFILE_OBJECT FileObject,
	 PFILE_OBJECT BackingFileObject,
	 PVOID        BackingFltInstance
);
NTSTATUS IoSetSystemPartition(
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
NTSTATUS IoVerifyPartitionTable(
	 PDEVICE_OBJECT DeviceObject,
	 BOOLEAN        FixErrors
);
NTSTATUS IoVolumeDeviceToDosName(
	  PVOID           VolumeDeviceObject,
	 PUNICODE_STRING DosName
);

BOOLEAN KeAreApcsDisabled();

void KeBugCheck(
	 ULONG BugCheckCode
);
void KeEnterCriticalRegion();

void KeEnterGuardedRegion();

NTSTATUS
KeExpandKernelStackAndCallout(
	 PEXPAND_STACK_CALLOUT Callout,
	 PVOID Parameter,
	 SIZE_T Size
);

NTSTATUS KeExpandKernelStackAndCalloutEx(
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

NTSTATUS KeInitializeCrashDumpHeader(
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

KERNEL_ENTRY KIRQL KeRaiseIrqlToDpcLevel();

LONG KeSetBasePriorityThread(
	  PKTHREAD Thread,
	      LONG     Increment
);

NTSTATUS KeSetHardwareCounterConfiguration(
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


NTSTATUS MmAddPhysicalMemory(
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

NTSTATUS MmCopyMemory(
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

NTSTATUS MmMapViewInSystemSpace(
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


NTSTATUS MmUnmapViewInSystemSpace(
  PVOID MappedBase
);

void MmUnsecureVirtualMemory(
   HANDLE SecureHandle
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtOpenProcess(
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

NTSTATUS PgetLocationString(
    PVOID Context,
       PZZWSTR *LocationStrings
);

void Phalexaminembr(
    PDEVICE_OBJECT DeviceObject,
    ULONG SectorSize,
    ULONG MBRTypeIdentifier,
   PVOID *Buffer
);


NTSTATUS Phalquerysysteminformation(
    HAL_QUERY_INFORMATION_CLASS InformationClass,
    ULONG BufferSize,
   PVOID Buffer,
   PULONG ReturnedLength
);

NTSTATUS Phalsetsysteminformation(
	  HAL_SET_INFORMATION_CLASS InformationClass,
	  ULONG BufferSize,
	 PVOID Buffer
);

typedef struct _PNP_LOCATION_INTERFACE {
  USHORT                 Size;
  USHORT                 Version;
  PVOID                  Context;
  PINTERFACE_REFERENCE   InterfaceReference;
  PINTERFACE_DEREFERENCE InterfaceDereference;
  PGET_LOCATION_STRING   GetLocationString;
} PNP_LOCATION_INTERFACE, *PPNP_LOCATION_INTERFACE;

typedef struct _POWER_THROTTLING_PROCESS_STATE {
  ULONG Version;
  ULONG ControlMask;
  ULONG StateMask;
} POWER_THROTTLING_PROCESS_STATE, *PPOWER_THROTTLING_PROCESS_STATE;

typedef struct _POWER_THROTTLING_THREAD_STATE {
  ULONG Version;
  ULONG ControlMask;
  ULONG StateMask;
} POWER_THROTTLING_THREAD_STATE, *PPOWER_THROTTLING_THREAD_STATE;

void PphysicalCounterEventBufferOverflowHandler(
  PVOID EventBuffer,
  SIZE_T EntrySize,
  SIZE_T NumberOfEntries,
  HANDLE OwningHandle
);

void PphysicalCounterOverflowHandler(
  ULONGLONG OverflowBits,
  HANDLE OwningHandle
);

typedef struct _PROCESS_MEMBERSHIP_INFORMATION {
  ULONG ServerSiloId;
} PROCESS_MEMBERSHIP_INFORMATION, *PPROCESS_MEMBERSHIP_INFORMATION;

typedef struct _PROCESS_MITIGATION_ACTIVATION_CONTEXT_TRUST_POLICY {
  union {
	ULONG Flags;
	struct {
	  ULONG AssemblyManifestRedirectionTrust : 1;
	  ULONG ReservedFlags : 31;
	} DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
} PROCESS_MITIGATION_ACTIVATION_CONTEXT_TRUST_POLICY, *PPROCESS_MITIGATION_ACTIVATION_CONTEXT_TRUST_POLICY;

typedef struct _PROCESS_MITIGATION_CHILD_PROCESS_POLICY {
  union {
	ULONG Flags;
	struct {
	  ULONG NoChildProcessCreation : 1;
	  ULONG AuditNoChildProcessCreation : 1;
	  ULONG AllowSecureProcessCreation : 1;
	  ULONG ReservedFlags : 29;
	} DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
} PROCESS_MITIGATION_CHILD_PROCESS_POLICY, *PPROCESS_MITIGATION_CHILD_PROCESS_POLICY;

typedef struct _PROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY {
  union {
	ULONG Flags;
	struct {
	  ULONG EnableExportAddressFilter : 1;
	  ULONG AuditExportAddressFilter : 1;
	  ULONG EnableExportAddressFilterPlus : 1;
	  ULONG AuditExportAddressFilterPlus : 1;
	  ULONG EnableImportAddressFilter : 1;
	  ULONG AuditImportAddressFilter : 1;
	  ULONG EnableRopStackPivot : 1;
	  ULONG AuditRopStackPivot : 1;
	  ULONG EnableRopCallerCheck : 1;
	  ULONG AuditRopCallerCheck : 1;
	  ULONG EnableRopSimExec : 1;
	  ULONG AuditRopSimExec : 1;
	  ULONG ReservedFlags : 20;
	} DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
} PROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY, *PPROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY;

typedef enum _PROCESS_MITIGATION_POLICY {
  ProcessDEPPolicy,
  ProcessASLRPolicy,
  ProcessDynamicCodePolicy,
  ProcessStrictHandleCheckPolicy,
  ProcessSystemCallDisablePolicy,
  ProcessMitigationOptionsMask,
  ProcessExtensionPointDisablePolicy,
  ProcessControlFlowGuardPolicy,
  ProcessSignaturePolicy,
  ProcessFontDisablePolicy,
  ProcessImageLoadPolicy,
  ProcessSystemCallFilterPolicy,
  ProcessPayloadRestrictionPolicy,
  ProcessChildProcessPolicy,
  ProcessSideChannelIsolationPolicy,
  ProcessUserShadowStackPolicy,
  ProcessRedirectionTrustPolicy,
  ProcessUserPointerAuthPolicy,
  ProcessSEHOPPolicy,
  ProcessActivationContextTrustPolicy,
  MaxProcessMitigationPolicy
} PROCESS_MITIGATION_POLICY, *PPROCESS_MITIGATION_POLICY;

typedef struct _PROCESS_MITIGATION_SEHOP_POLICY {
  union {
	ULONG Flags;
	struct {
	  ULONG EnableSehop : 1;
	  ULONG ReservedFlags : 31;
	} DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
} PROCESS_MITIGATION_SEHOP_POLICY, *PPROCESS_MITIGATION_SEHOP_POLICY;

typedef struct _PROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY {
  union {
	ULONG Flags;
	struct {
	  ULONG FilterId : 4;
	  ULONG ReservedFlags : 28;
	} DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
} PROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY, *PPROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY;

typedef struct _PROCESS_MITIGATION_USER_POINTER_AUTH_POLICY {
  union {
	ULONG Flags;
	struct {
	  ULONG EnablePointerAuthUserIp : 1;
	  ULONG ReservedFlags : 31;
	} DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
} PROCESS_MITIGATION_USER_POINTER_AUTH_POLICY, *PPROCESS_MITIGATION_USER_POINTER_AUTH_POLICY;


typedef struct _PROCESS_SYSCALL_PROVIDER_INFORMATION {
  GUID  ProviderId;
  UCHAR Level;
} PROCESS_SYSCALL_PROVIDER_INFORMATION, *PPROCESS_SYSCALL_PROVIDER_INFORMATION;


typedef struct _PS_CREATE_NOTIFY_INFO {
  SIZE_T              Size;
  union {
	ULONG Flags;
	struct {
	  ULONG FileOpenNameAvailable : 1;
	  ULONG IsSubsystemProcess : 1;
	  ULONG Reserved : 30;
	};
  };
  HANDLE              ParentProcessId;
  CLIENT_ID           CreatingThreadId;
  struct _FILE_OBJECT *FileObject;
  PCUNICODE_STRING    ImageFileName;
  PCUNICODE_STRING    CommandLine;
  NTSTATUS            CreationStatus;
} PS_CREATE_NOTIFY_INFO, *PPS_CREATE_NOTIFY_INFO;

void PcreateProcessNotifyRoutineEx(
	           PEPROCESS Process,
	                HANDLE ProcessId,
	  PPS_CREATE_NOTIFY_INFO CreateInfo
);


NTSTATUS PsAllocSiloContextSlot(
    ULONG_PTR Reserved,
   ULONG     *ReturnedContextSlot
);

PESILO PsAttachSiloToCurrentThread(
   PESILO Silo
);

typedef enum _PSCREATEPROCESSNOTIFYTYPE {
  PsCreateProcessNotifySubsystems
} PSCREATEPROCESSNOTIFYTYPE;

NTSTATUS PsCreateSiloContext(
             PESILO                        Silo,
             ULONG                         Size,
             POOL_TYPE                     PoolType,
   SILO_CONTEXT_CLEANUP_CALLBACK ContextCleanupCallback,
				 PVOID                         *ReturnedSiloContext
);

typedef enum _PSCREATETHREADNOTIFYTYPE {
  PsCreateThreadNotifyNonSystem,
  PsCreateThreadNotifySubsystems
} PSCREATETHREADNOTIFYTYPE;

void PsDereferenceSiloContext(
   PVOID SiloContext
);

void PsDetachSiloFromCurrentThread(
   PESILO PreviousSilo
);

NTSTATUS PsFreeSiloContextSlot(
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

NTSTATUS PsGetJobServerSilo(
   PEJOB  Job,
            PESILO *ServerSilo
);

NTSTATUS PsGetJobSilo(
    PEJOB  Job,
   PESILO *Silo
);

PESILO PsGetParentSilo(
   PEJOB Job
);

NTSTATUS PsGetPermanentSiloContext(
   PESILO Silo,
   ULONG  ContextSlot,
	   PVOID  *ReturnedSiloContext
);

LONGLONG PsGetProcessCreateTimeQuadPart(
   PEPROCESS Process
);

NTSTATUS PsGetProcessExitStatus(
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

NTSTATUS PsGetSiloContext(
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

NTSTATUS PsGetThreadExitStatus(
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

NTSTATUS PsInsertPermanentSiloContext(
   PESILO Silo,
   ULONG  ContextSlot,
   PVOID  SiloContext
);

NTSTATUS PsInsertSiloContext(
   PESILO Silo,
   ULONG  ContextSlot,
   PVOID  SiloContext
);

BOOLEAN PsIsHostSilo(
   PESILO Silo
);

NTSTATUS PsMakeSiloContextPermanent(
   PESILO Silo,
   ULONG  ContextSlot
);

void PsReferenceSiloContext(
   PVOID SiloContext
);

NTSTATUS PsRemoveCreateThreadNotifyRoutine(
   PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine
);

NTSTATUS PsRemoveLoadImageNotifyRoutine(
   PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine
);

NTSTATUS PsRemoveSiloContext(
   PESILO Silo,
   ULONG  ContextSlot,
	   PVOID  *RemovedSiloContext
);

NTSTATUS PsReplaceSiloContext(
         PESILO Silo,
         ULONG  ContextSlot,
         PVOID  NewSiloContext,
  PVOID  *OldSiloContext
);

NTSTATUS PsSetCreateProcessNotifyRoutine(
   PCREATE_PROCESS_NOTIFY_ROUTINE NotifyRoutine,
   BOOLEAN                        Remove
);

NTSTATUS PsSetCreateProcessNotifyRoutineEx(
   PCREATE_PROCESS_NOTIFY_ROUTINE_EX NotifyRoutine,
   BOOLEAN                           Remove
);

NTSTATUS PsSetCreateProcessNotifyRoutineEx2(
   PSCREATEPROCESSNOTIFYTYPE NotifyType,
   PVOID                     NotifyInformation,
   BOOLEAN                   Remove
);

NTSTATUS PsSetCreateThreadNotifyRoutine(
   PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine
);

NTSTATUS PsSetCreateThreadNotifyRoutineEx(
   PSCREATETHREADNOTIFYTYPE NotifyType,
   PVOID                    NotifyInformation
);

NTSTATUS PsSetLoadImageNotifyRoutine(
   PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine
);

NTSTATUS PsSetLoadImageNotifyRoutineEx(
   PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine,
   ULONG_PTR                  Flags
);

NTSTATUS PsStartSiloMonitor(
   PSILO_MONITOR Monitor
);

void PsTerminateServerSilo(
   PESILO   ServerSilo,
	   NTSTATUS ExitStatus
);

void PsUnregisterSiloMonitor(
   PSILO_MONITOR Monitor
);

//RTL_RUN_ONCE_INIT_FN (
//	 PRTL_RUN_ONCE RunOnce,
//	 PVOID Parameter,
//	 PVOID *Context
//);

NTSYSAPI NTSTATUS RtlCharToInteger(
             PCSZ   String,
   ULONG  Base,
            PULONG Value
);

LONG RtlCompareString(
   const STRING *String1,
   const STRING *String2,
   BOOLEAN      CaseInSensitive
);

//NTAPI_INLINE RtlConvertUlongToLuid(
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

NTSYSAPI NTSTATUS RtlGetPersistedStateLocation(
        PCWSTR              SourceID,
    PCWSTR              CustomValue,
    PCWSTR              DefaultPath,
        STATE_LOCATION_TYPE StateLocationType,
        PWCHAR              TargetPath,
        ULONG               BufferLengthIn,
   PULONG              BufferLengthOut
);


NTSYSAPI NTSTATUS RtlIncrementCorrelationVector(
    PCORRELATION_VECTOR CorrelationVector
);

NTSYSAPI NTSTATUS RtlInitializeCorrelationVector(
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

NTSYSAPI NTSTATUS RtlQueryRegistryValueWithFallback(
    HANDLE          PrimaryHandle,
    HANDLE          FallbackHandle,
    PUNICODE_STRING ValueName,
    ULONG           ValueLength,
   PULONG          ValueType,
   PVOID           ValueData,
   PULONG          ResultLength
);

NTSTATUS RtlRaiseCustomSystemEventTrigger(
   PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG TriggerConfig
);

NTSYSAPI NTSTATUS RtlRunOnceBeginInitialize(
    PRTL_RUN_ONCE RunOnce,
        ULONG         Flags,
       PVOID         *Context
);

NTSYSAPI NTSTATUS RtlRunOnceComplete(
         PRTL_RUN_ONCE RunOnce,
             ULONG         Flags,
   PVOID         Context
);

NTSYSAPI NTSTATUS RtlRunOnceExecuteOnce(
  PRTL_RUN_ONCE         RunOnce,
  PRTL_RUN_ONCE_INIT_FN InitFn,
  PVOID                 Parameter,
  PVOID                 *Context
);

NTSYSAPI VOID RtlRunOnceInitialize(
   PRTL_RUN_ONCE RunOnce
);

NTSYSAPI NTSTATUS RtlUpcaseUnicodeString(
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

NTSYSAPI NTSTATUS RtlValidateCorrelationVector(
  PCORRELATION_VECTOR Vector
);

NTSYSAPI NTSTATUS RtlVolumeDeviceToDosName(
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


typedef struct _SILO_MONITOR_REGISTRATION {
  UCHAR                           Version;
  BOOLEAN                         MonitorHost;
  BOOLEAN                         MonitorExistingSilos;
  UCHAR                           Reserved[5];
  union {
	PUNICODE_STRING DriverObjectName;
	PUNICODE_STRING ComponentName;
  };
  SILO_MONITOR_CREATE_CALLBACK    CreateCallback;
  SILO_MONITOR_TERMINATE_CALLBACK TerminateCallback;
} SILO_MONITOR_REGISTRATION, *PSILO_MONITOR_REGISTRATION;

void SiloMonitorTerminateCallback(
   PESILO Silo
);


typedef enum _SUBSYSTEM_INFORMATION_TYPE {
  SubsystemInformationTypeWin32,
  SubsystemInformationTypeWSL,
  MaxSubsystemInformationType
} SUBSYSTEM_INFORMATION_TYPE, *PSUBSYSTEM_INFORMATION_TYPE;



typedef struct _WHEA_ERROR_SOURCE_OVERRIDE_SETTINGS {
  WHEA_ERROR_SOURCE_TYPE Type;
  ULONG                  MaxRawDataLength;
  ULONG                  NumRecordsToPreallocate;
  ULONG                  MaxSectionsPerRecord;
} WHEA_ERROR_SOURCE_OVERRIDE_SETTINGS, *PWHEA_ERROR_SOURCE_OVERRIDE_SETTINGS;

typedef struct _WHEA_FAILED_ADD_DEFECT_LIST_EVENT {
  WHEA_EVENT_LOG_ENTRY WheaEventLogEntry;
} WHEA_FAILED_ADD_DEFECT_LIST_EVENT, *PWHEA_FAILED_ADD_DEFECT_LIST_EVENT;

typedef struct _WHEA_PCI_RECOVERY_SECTION {
  UINT8   SignalType;
  BOOLEAN RecoveryAttempted;
  UINT8   RecoveryStatus;
} WHEA_PCI_RECOVERY_SECTION, *PWHEA_PCI_RECOVERY_SECTION;

typedef enum _WHEA_PCI_RECOVERY_SIGNAL {
  WheaPciRecoverySignalUnknown,
  WheaPciRecoverySignalAer,
  WheaPciRecoverySignalDpc
} WHEA_PCI_RECOVERY_SIGNAL, *PWHEA_PCI_RECOVERY_SIGNAL;

typedef enum _WHEA_PCI_RECOVERY_STATUS {
  WheaPciREcoveryStatusUnknown,
  WheaPciRecoveryStatusNoError,
  WheaPciRecoveryStatusLinkDisableTimeout,
  WheaPciRecoveryStatusLinkEnableTimeout,
  WheaPciRecoveryStatusRpBusyTimeout,
  WheaPciRecoveryStatusComplexTree,
  WheaPciRecoveryStatusBusNotFound
} WHEA_PCI_RECOVERY_STATUS, *PWHEA_PCI_RECOVERY_STATUS;

typedef struct _WHEA_PSHED_PI_CPU_BUSES_INIT_FAILED_EVENT {
  WHEA_EVENT_LOG_ENTRY WheaEventLogEntry;
  NTSTATUS             Status;
} WHEA_PSHED_PI_CPU_BUSES_INIT_FAILED_EVENT, *PWHEA_PSHED_PI_CPU_BUSES_INIT_FAILED_EVENT;

typedef struct _WHEA_PSHED_PLUGIN_INIT_FAILED_EVENT {
  WHEA_EVENT_LOG_ENTRY WheaEventLogEntry;
  NTSTATUS             Status;
} WHEA_PSHED_PLUGIN_INIT_FAILED_EVENT, *PWHEA_PSHED_PLUGIN_INIT_FAILED_EVENT;

typedef struct _WHEA_SEA_SECTION {
  ULONG   Esr;
  ULONG64 Far;
  ULONG64 Par;
  BOOLEAN WasKernel;
} WHEA_SEA_SECTION, *PWHEA_SEA_SECTION;

typedef struct _WHEA_SEI_SECTION {
  ULONG   Esr;
  ULONG64 Far;
} WHEA_SEI_SECTION, *PWHEA_SEI_SECTION;

typedef struct _WHEA_SRAS_TABLE_ENTRIES_EVENT {
  WHEA_EVENT_LOG_ENTRY WheaEventLogEntry;
  UINT32               LogNumber;
  UINT32               NumberSignals;
  UINT8*               Data;
} WHEA_SRAS_TABLE_ENTRIES_EVENT, *PWHEA_SRAS_TABLE_ENTRIES_EVENT;

typedef struct _WHEA_SRAS_TABLE_ERROR {
  WHEA_EVENT_LOG_ENTRY WheaEventLogEntry;
} WHEA_SRAS_TABLE_ERROR, *PWHEA_SRAS_TABLE_ERROR;

typedef struct _WHEA_SRAS_TABLE_NOT_FOUND {
  WHEA_EVENT_LOG_ENTRY WheaEventLogEntry;
} WHEA_SRAS_TABLE_NOT_FOUND, *PWHEA_SRAS_TABLE_NOT_FOUND;

//void WheaAdd2Ptr(
//   P,
//   I
//);

PVOID WheaErrorRecordBuilderAddPacket(
    PWHEA_ERROR_RECORD    Record,
    PWHEA_ERROR_PACKET_V2 Packet,
        UINT32                MaxSectionCount
);

PVOID WheaErrorRecordBuilderAddSection(
              PWHEA_ERROR_RECORD                         Record,
                  UINT32                                     MaxSectionCount,
                  UINT32                                     SectionLength,
                  WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS Flags,
                  GUID                                       SectionType,
    PVOID                                      DescriptorOut
);

void WheaErrorRecordBuilderInit(
  PWHEA_ERROR_RECORD  Record,
  UINT32              RecordLength,
  WHEA_ERROR_SEVERITY Severity,
  GUID                Notify
);

typedef struct _WHEAP_BAD_HEST_NOTIFY_DATA_EVENT {
  WHEA_EVENT_LOG_ENTRY         WheaEventLogEntry;
  USHORT                       SourceId;
  USHORT                       Reserved;
  WHEA_NOTIFICATION_DESCRIPTOR NotifyDesc;
} WHEAP_BAD_HEST_NOTIFY_DATA_EVENT, *PWHEAP_BAD_HEST_NOTIFY_DATA_EVENT;

typedef struct _WHEAP_DPC_ERROR_EVENT {
  WHEA_EVENT_LOG_ENTRY       WheaEventLogEntry;
  WHEAP_DPC_ERROR_EVENT_TYPE ErrType;
  ULONG                      Bus;
  ULONG                      Device;
  ULONG                      Function;
  USHORT                     DeviceId;
  USHORT                     VendorId;
} WHEAP_DPC_ERROR_EVENT, *PWHEAP_DPC_ERROR_EVENT;

typedef struct _WHEAP_PLUGIN_DEFECT_LIST_CORRUPT {
  WHEA_EVENT_LOG_ENTRY WheaEventLogEntry;
} WHEAP_PLUGIN_DEFECT_LIST_CORRUPT, *PWHEAP_PLUGIN_DEFECT_LIST_CORRUPT;

typedef struct _WHEAP_PLUGIN_DEFECT_LIST_FULL_EVENT {
  WHEA_EVENT_LOG_ENTRY WheaEventLogEntry;
} WHEAP_PLUGIN_DEFECT_LIST_FULL_EVENT, *PWHEAP_PLUGIN_DEFECT_LIST_FULL_EVENT;

typedef struct _WHEAP_PLUGIN_DEFECT_LIST_UEFI_VAR_FAILED {
  WHEA_EVENT_LOG_ENTRY WheaEventLogEntry;
} WHEAP_PLUGIN_DEFECT_LIST_UEFI_VAR_FAILED, *PWHEAP_PLUGIN_DEFECT_LIST_UEFI_VAR_FAILED;

typedef struct _WHEAP_ROW_FAILURE_EVENT {
  WHEA_EVENT_LOG_ENTRY WheaEventLogEntry;
  PFN_NUMBER           LowOrderPage;
  PFN_NUMBER           HighOrderPage;
} WHEAP_ROW_FAILURE_EVENT, *PWHEAP_ROW_FAILURE_EVENT;

NTSTATUS WheaRegisterErrorSourceOverride(
   WHEA_ERROR_SOURCE_OVERRIDE_SETTINGS   OverrideSettings,
   PWHEA_ERROR_SOURCE_CONFIGURATION      OverrideConfig,
   WHEA_SIGNAL_HANDLER_OVERRIDE_CALLBACK OverrideCallback
);

BOOLEAN WheaSignalHandlerOverride(
                  WHEA_ERROR_SOURCE_TYPE SourceType,
    UINT_PTR               Context
);

void WheaUnregisterErrorSourceOverride(
   WHEA_ERROR_SOURCE_TYPE Type,
   ULONG32                OverrideErrorSourceId
);

NTSYSAPI NTSTATUS ZwAllocateLocallyUniqueId(
  PLUID Luid
);


NTSYSAPI NTSTATUS ZwDeviceIoControlFile(
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

NTSYSAPI NTSTATUS ZwOpenProcess(
            PHANDLE            ProcessHandle,
             ACCESS_MASK        DesiredAccess,
             POBJECT_ATTRIBUTES ObjectAttributes,
   PCLIENT_ID         ClientId
);

NTSYSAPI NTSTATUS ZwPowerInformation(
              POWER_INFORMATION_LEVEL InformationLevel,
    PVOID                   InputBuffer,
              ULONG                   InputBufferLength,
   PVOID                   OutputBuffer,
              ULONG                   OutputBufferLength
);

NTSYSAPI NTSTATUS ZwQueryVolumeInformationFile(
    HANDLE               FileHandle,
   PIO_STATUS_BLOCK     IoStatusBlock,
   PVOID                FsInformation,
    ULONG                Length,
    FS_INFORMATION_CLASS FsInformationClass
);

NTSYSAPI NTSTATUS ZwSetInformationThread(
   HANDLE          ThreadHandle,
   THREADINFOCLASS ThreadInformationClass,
   PVOID           ThreadInformation,
   ULONG           ThreadInformationLength
);


NTSYSAPI NTSTATUS ZwTerminateProcess(
   HANDLE   ProcessHandle,
             NTSTATUS ExitStatus
);

static inline
bool NT_SUCCESS(NTSTATUS Status){
	switch(Status){
		case 0:
			return true;
		default:
			return false;
	}
}

#endif