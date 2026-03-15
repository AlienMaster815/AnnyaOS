#ifndef _LDM_DDK_H
#define _LDM_DDK_H
#ifdef __cplusplus
extern "C" {
#endif

#include <Ldm.h>

typedef struct _SIGNAL_REG_VALUE {
	UINT8*  	RegName;
	UINT32  	MsrAddr;
	UINT64  	Value;
}SIGNAL_REG_VALUE, * PSIGNAL_REG_VALUE;

typedef enum _STATE_LOCATION_TYPE{
	LocationTypeRegistry = 0,
	LocationTypeFileSystem,
	LocationTypeMaximum,
}STATE_LOCATION_TYPE, * PSTATE_LOCATION_TYPE;

typedef enum _KD_CALLBACK_ACTION{
	KdConfigureDeviceAndContinue = 0,
	KdSkipDeviceAndContinue,
	KdConfigureDeviceAndStop,
	KdSkipDeviceAndStop,
}KD_CALLBACK_ACTION, * PKD_CALLBACK_ACTION;

typedef enum _KD_NAMESPACE_ENUM{
	KdNameSpacePCI = 0,
	KdNameSpaceACPI,
	KdNameSpaceAny,
	KdNameSpaceNone,
	KdNameSpaceMax,
}KD_NAMESPACE_ENUM, * PKD_NAMESPACE_ENUM;

typedef struct _CONFIGURATION_INFORMATION{
	ULONG   	DiskCount;
	ULONG   	FloppyCount;
	ULONG   	CdRomCount;
	ULONG   	TapeCount;
	ULONG   	ScsiPortCount;
	ULONG   	SerialCount;
	ULONG   	ParallelCount;
	BOOLEAN 	AtDiskPrimaryAddressClaimed;
	BOOLEAN 	AtDiskSecondaryAddressClaimed;
	ULONG   	Version;
	ULONG   	MediumChangerCount;
}CONFIGURATION_INFORMATION, * PCONFIGURATION_INFORMATION;

typedef struct _CONTROLLER_OBJECT{
	SHORT        	Type;
	SHORT        	Size;
	PVOID         	ControllerExtension;
	KDEVICE_QUEUE 	DeviceWaitQueue;
	ULONG         	Spare1;
	LARGE_INTEGER 	Spare2;
}CONTROLLER_OBJECT, * PCONTROLLER_OBJECT;

typedef struct _CUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG{
	ULONG  	Size;
	PCWSTR 	TriggerId;
}CUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG, * PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG;

typedef struct _DEBUG_DEVICE_ADDRESS{
	UCHAR   		Type;
	BOOLEAN 		Valid;
	union {
		UCHAR 		Reserved[2];
		struct {
			UCHAR 	BitWidth;
			UCHAR 	AccessSize;
		};
	};
	PUCHAR  		TranslatedAddress;
	ULONG   		Length;
}DEBUG_DEVICE_ADDRESS, * PDEBUG_DEVICE_ADDRESS;

typedef struct _DEBUG_MEMORY_REQUIREMENTS{
	PHYSICAL_ADDRESS 	Start;
	PHYSICAL_ADDRESS 	MaxEnd;
	PVOID            	VirtualAddress;
	ULONG            	Length;
	BOOLEAN          	Cached;
	BOOLEAN          	Aligned;
}DEBUG_MEMORY_REQUIREMENTS, * PDEBUG_MEMORY_REQUIREMENTS;

typedef struct _EFI_ACPI_RAS_SIGNAL_TABLE{
	LHEA_ACPI_HEADER 	Header;
	UINT32           	NumberRecord;
	SIGNAL_REG_VALUE* 	Entries;
}EFI_ACPI_RAS_SIGNAL_TABLE, * PEFI_ACPI_RAS_SIGNAL_TABLE;

typedef struct _FILE_ALIGNMENT_INFORMATION{
	ULONG 	AlignmentRequirement;
}FILE_ALIGNMENT_INFORMATION, * PFILE_ALIGNMENT_INFORMATION;

typedef struct _FILE_ATTRIBUTE_TAG_INFORMATION{
	ULONG 	FileAttributes;
	ULONG 	ReparseTag;
}FILE_ATTRIBUTE_TAG_INFORMATION, * PFILE_ATTRIBUTE_TAG_INFORMATION;

typedef struct _FILE_DISPOSITION_INFORMATION{
	BOOLEAN 	DeleteFile;
}FILE_DISPOSITION_INFORMATION, * PFILE_DISPOSITION_INFORMATION;

typedef struct _FILE_END_OF_FILE_INFORMATION{
	LARGE_INTEGER 	EndOfFile;
}FILE_END_OF_FILE_INFORMATION, * PFILE_END_OF_FILE_INFORMATION;

typedef struct _FILE_NAME_INFORMATION{
	ULONG 	FileNameLength;
	WCHAR 	FileName[1];
}FILE_NAME_INFORMATION, * PFILE_NAME_INFORMATION;

typedef struct _FILE_VALID_DATA_LENGTH_INFORMATION{
	LARGE_INTEGER 	ValidDataLength;
}FILE_VALID_DATA_LENGTH_INFORMATION, * PFILE_VALID_DATA_LENGTH_INFORMATION;

typedef enum _HARDWARE_COUNTER_TYPE{
	PMCCounter = 0,
	MaxHardwareCounterType,
}HARDWARE_COUNTER_TYPE, * PHARDWARE_COUNTER_TYPE;

typedef struct _HARDWARE_COUNTER{
	HARDWARE_COUNTER_TYPE 	Type;
	ULONG                 	Reserved;
	ULONG64               	Index;
}HARDWARE_COUNTER, * PHARDWARE_COUNTER;

typedef struct _IMAGE_INFO_EX{
	SIZE_T              	Size;
	IMAGE_INFO          	ImageInfo;
	struct _FILE_OBJECT* 	FileObject;
}IMAGE_INFO_EX, * PIMAGE_INFO_EX;

typedef struct _IO_FOEXT_SHADOW_FILE{
	struct _FILE_OBJECT* 	BackingFileObject;
	PVOID        			BackingFltInstance;
}IO_FOEXT_SHADOW_FILE, * PIO_FOEXT_SHADOW_FILE;

typedef struct _KEY_CACHED_INFORMATION{
	LARGE_INTEGER 	LastWriteTime;
	ULONG         	TitleIndex;
	ULONG         	SubKeys;
	ULONG         	MaxNameLen;
	ULONG         	Values;
	ULONG         	MaxValueNameLen;
	ULONG         	MaxValueDataLen;
	ULONG         	NameLength;
}KEY_CACHED_INFORMATION, * PKEY_CACHED_INFORMATION;

typedef struct _KEY_NAME_INFORMATION{
	ULONG 	NameLength;
	WCHAR 	Name[1];
}KEY_NAME_INFORMATION, * PKEY_NAME_INFORMATION;

typedef struct _KEY_VIRTUALIZATION_INFORMATION{
	ULONG 	VirtualizationCandidate 	: 	1;
	ULONG 	VirtualizationEnabled 		: 	1;
	ULONG 	VirtualTarget 				: 	1;
	ULONG 	VirtualStore 				: 	1;
	ULONG 	VirtualSource 				: 	1;
	ULONG 	Reserved 					: 	27;
}KEY_VIRTUALIZATION_INFORMATION, * PKEY_VIRTUALIZATION_INFORMATION;

typedef struct _KUSER_SHARED_DATA{
	ULONG                         	TickCountLowDeprecated;
	ULONG                         	TickCountMultiplier;
	KSYSTEM_TIME                  	InterruptTime;
	KSYSTEM_TIME                  	SystemTime;
	KSYSTEM_TIME                  	TimeZoneBias;
	USHORT                        	ImageNumberLow;
	USHORT                        	ImageNumberHigh;
	WCHAR                         	NtSystemRoot[260];
	ULONG                         	MaxStackTraceDepth;
	ULONG                         	CryptoExponent;
	ULONG                         	TimeZoneId;
	ULONG                         	LargePageMinimum;
	ULONG                         	AitSamplingValue;
	ULONG                         	AppCompatFlag;
	ULONGLONG                     	RNGSeedVersion;
	ULONG                         	GlobalValidationRunlevel;
	LONG                          	TimeZoneBiasStamp;
	ULONG                         	LouBuildNumber;
	LOU_PRODUCT_TYPE              	LouProductType;
	BOOLEAN                       	ProductTypeIsValid;
	BOOLEAN                       	Reserved0[1];
	USHORT                        	NativeProcessorArchitecture;
	ULONG                         	LouMajorVersion;
	ULONG                         	LouMinorVersion;
	BOOLEAN*                      	ProcessorFeatures;
	ULONG                         	Reserved1;
	ULONG                         	Reserved3;
	ULONG                         	TimeSlip;
	ALTERNATIVE_ARCHITECTURE_TYPE 	AlternativeArchitecture;
	ULONG                         	BootId;
	LARGE_INTEGER                 	SystemExpirationDate;
	ULONG                         	SuiteMask;
	BOOLEAN                       	KdDebuggerEnabled;
	union{
		UCHAR 						MitigationPolicies;
		struct{
			UCHAR 					NXSupportPolicy 				: 	2;
			UCHAR 					SEHValidationPolicy 			: 	2;
			UCHAR 					CurDirDevicesSkippedForDlls 	: 	2;
			UCHAR 					Reserved 						: 	2;
		};
	};
	USHORT                        	CyclesPerYield;
	ULONG                         	ActiveConsoleId;
	ULONG                         	DismountCount;
	ULONG                         	ComPlusPackage;
	ULONG                         	LastSystemRITEventTickCount;
	ULONG                         	NumberOfPhysicalPages;
	BOOLEAN                       	SafeBootMode;
	union {
		UCHAR 						VirtualizationFlags;
		struct {
			UCHAR 					ArchStartedInEl2 : 1;
			UCHAR 					QcSlIsSupported : 1;
		};
	};
	UCHAR                         	Reserved12[2];
	union {
		ULONG 						SharedDataFlags;
		struct {
			ULONG 					DbgErrorPortPresent : 1;
			ULONG 					DbgElevationEnabled : 1;
			ULONG 					DbgVirtEnabled : 1;
			ULONG 					DbgInstallerDetectEnabled : 1;
			ULONG 					DbgLkgEnabled : 1;
			ULONG 					DbgDynProcessorEnabled : 1;
			ULONG 					DbgConsoleBrokerEnabled : 1;
			ULONG 					DbgSecureBootEnabled : 1;
			ULONG 					DbgMultiSessionSku : 1;
			ULONG 					DbgMultiUsersInSessionSku : 1;
			ULONG 					DbgStateSeparationEnabled : 1;
			ULONG 					SpareBits : 21;
		};
	};
	ULONG                         	DataFlagsPad[1];
	ULONGLONG                     	TestRetInstruction;
	LONGLONG                      	QpcFrequency;
	ULONG                         	SystemCall;
	ULONG                         	Reserved2;
	ULONGLONG                     	SystemCallPad[2];
	union {
		KSYSTEM_TIME 				TickCount;
		ULONG64      				TickCountQuad;
		struct {
			ULONG 					ReservedTickCountOverlay[3];
			ULONG 					TickCountPad[1];
		};
	};
	ULONG                         	Cookie;
	ULONG                         	CookiePad[1];
	LONGLONG                      	ConsoleSessionForegroundProcessId;
	ULONGLONG                     	TimeUpdateLock;
	ULONGLONG                     	BaselineSystemTimeQpc;
	ULONGLONG                     	BaselineInterruptTimeQpc;
	ULONGLONG                     	QpcSystemTimeIncrement;
	ULONGLONG                     	QpcInterruptTimeIncrement;
	UCHAR                         	QpcSystemTimeIncrementShift;
	UCHAR                         	QpcInterruptTimeIncrementShift;
	USHORT                        	UnparkedProcessorCount;
	ULONG                         	EnclaveFeatureMask[4];
	ULONG                         	TelemetryCoverageRound;
	USHORT                        	UserModeGlobalLogger[16];
	ULONG                         	ImageFileExecutionOptions;
	ULONG                         	LangGenerationCount;
	ULONGLONG                     	Reserved4;
	ULONGLONG                     	InterruptTimeBias;
	ULONGLONG                     	QpcBias;
	ULONG                         	ActiveProcessorCount;
	UCHAR                         	ActiveGroupCount;
	UCHAR                         	Reserved9;
	union {
		USHORT 						QpcData;
		struct {
			UCHAR 					QpcBypassEnabled;
			UCHAR 					QpcShift;
		};
	};
	LARGE_INTEGER                 	TimeZoneBiasEffectiveStart;
	LARGE_INTEGER                 	TimeZoneBiasEffectiveEnd;
	XSTATE_CONFIGURATION          	XState;
	KSYSTEM_TIME                  	FeatureConfigurationChangeStamp;
	ULONG                         	Spare;
	ULONG64                       	UserPointerAuthMask;
}KUSER_SHARED_DATA, * PKUSER_SHARED_DATA;

typedef struct _MM_COPY_ADDRESS{
	union {
		PVOID            	VirtualAddress;
		PHYSICAL_ADDRESS 	PhysicalAddress;
	};
}MM_COPY_ADDRESS, * PMM_COPY_ADDRESS, 
	MMCOPYADDRESS, * PMMCOPYADDRESS;

typedef enum _PCI_EXPRESS_MAX_PAYLOAD_SIZE{
	MaxPayload128Bytes = 0,
	MaxPayload256Bytes,
	MaxPayload512Bytes,
	MaxPayload1024Bytes,
	MaxPayload2048Bytes,
	MaxPayload4096Bytes,
}PCI_EXPRESS_MAX_PAYLOAD_SIZE, * PPCI_EXPRESS_MAX_PAYLOAD_SIZE;

typedef enum{
  	BtiVbarNone = 0,
  	BtiVbarTrapHvc,
  	BtiVbarTrapSmc,
  	BtiVbarBhbDsbIsb,
  	BtiVbarBhbSb,
  	BtiVbarBhbClr,
}PCR_BTI_VBAR_INDEX, * PPCR_BTI_VBAR_INDEX;

typedef enum _PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR_TYPE{
	ResourceTypeSingle = 0,
	ResourceTypeRange,
	ResourceTypeExtendedCounterConfiguration,
	ResourceTypeOverflow,
	ResourceTypeEventBuffer,
	ResourceTypeIdenitificationTag,
	ResourceTypeMax,
}PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR_TYPE, * PPHYSICAL_COUNTER_RESOURCE_DESCRIPTOR_TYPE;

typedef struct _PHYSICAL_COUNTER_EVENT_BUFFER_CONFIGURATION{
  	PPHYSICAL_COUNTER_EVENT_BUFFER_OVERFLOW_HANDLER 	OverflowHandler;
  	ULONG                                           	CustomEventBufferEntrySize;
  	ULONG                                           	EventThreshold;
}PHYSICAL_COUNTER_EVENT_BUFFER_CONFIGURATION, * PPHYSICAL_COUNTER_EVENT_BUFFER_CONFIGURATION;

typedef struct _PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR{
  	PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR_TYPE 			Type;
  	ULONG                                     			Flags;
  	union {
		ULONG                                       	CounterIndex;
		struct {
		  	ULONG 										Begin;
		  	ULONG 										End;
		}Range;
		PPHYSICAL_COUNTER_OVERFLOW_HANDLER          	OverflowHandler;
		PHYSICAL_COUNTER_EVENT_BUFFER_CONFIGURATION 	EventBufferConfiguration;
		ULONG                                       	IdentificationTag;
  	}													u;
}PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR, * PPHYSICAL_COUNTER_RESOURCE_DESCRIPTOR;

typedef struct _PHYSICAL_COUNTER_RESOURCE_LIST{
  	ULONG                                		Count;
  	PHYSICAL_COUNTER_RESOURCE_DESCRIPTOR* 		Descriptors;
}PHYSICAL_COUNTER_RESOURCE_LIST, * PPHYSICAL_COUNTER_RESOURCE_LIST;

typedef struct _PNP_LOCATION_INTERFACE{
  	USHORT                 	Size;
  	USHORT                 	Version;
  	PVOID                  	Context;
  	PINTERFACE_REFERENCE   	InterfaceReference;
  	PINTERFACE_DEREFERENCE 	InterfaceDereference;
  	PGET_LOCATION_STRING   	GetLocationString;
}PNP_LOCATION_INTERFACE, * PPNP_LOCATION_INTERFACE;

typedef struct _POWER_THROTTLING_PROCESS_STATE{
  	ULONG 	Version;
	ULONG 	ControlMask;
  	ULONG 	StateMask;
}POWER_THROTTLING_PROCESS_STATE, * PPOWER_THROTTLING_PROCESS_STATE;

typedef struct _POWER_THROTTLING_THREAD_STATE{
  	ULONG 	Version;
  	ULONG 	ControlMask;
  	ULONG 	StateMask;
}POWER_THROTTLING_THREAD_STATE, * PPOWER_THROTTLING_THREAD_STATE;

typedef struct _PROCESS_MEMBERSHIP_INFORMATION{
  	ULONG 	ServerSiloId;
}PROCESS_MEMBERSHIP_INFORMATION, * PPROCESS_MEMBERSHIP_INFORMATION;

typedef struct _PROCESS_MITIGATION_ACTIVATION_CONTEXT_TRUST_POLICY{
  	union {
		ULONG 		Flags;
		struct {
	  		ULONG 	AssemblyManifestRedirectionTrust 	: 	1;
	  		ULONG 	ReservedFlags 						: 	31;
		};
  	};
} PROCESS_MITIGATION_ACTIVATION_CONTEXT_TRUST_POLICY, *PPROCESS_MITIGATION_ACTIVATION_CONTEXT_TRUST_POLICY;

typedef struct _PROCESS_MITIGATION_CHILD_PROCESS_POLICY{
  	union{
		ULONG 		Flags;
		struct {
	  		ULONG 	NoChildProcessCreation			: 	1;
	  		ULONG 	AuditNoChildProcessCreation 	: 	1;
	  		ULONG 	AllowSecureProcessCreation 		: 	1;
	  		ULONG 	ReservedFlags 					: 	29;
		};
  	};
}PROCESS_MITIGATION_CHILD_PROCESS_POLICY, * PPROCESS_MITIGATION_CHILD_PROCESS_POLICY;

typedef struct _PROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY{
  	union {
		ULONG Flags;
		struct {
		  	ULONG 	EnableExportAddressFilter 		: 	1;
		  	ULONG 	AuditExportAddressFilter 		: 	1;
		  	ULONG 	EnableExportAddressFilterPlus 	: 	1;
		  	ULONG 	AuditExportAddressFilterPlus 	: 	1;
		  	ULONG 	EnableImportAddressFilter 		: 	1;
		  	ULONG 	AuditImportAddressFilter 		: 	1;
		  	ULONG 	EnableRopStackPivot 			: 	1;
		  	ULONG 	AuditRopStackPivot 				: 	1;
		  	ULONG 	EnableRopCallerCheck 			: 	1;
		  	ULONG 	AuditRopCallerCheck 			: 	1;
		  	ULONG 	EnableRopSimExec 				: 	1;
		  	ULONG 	AuditRopSimExec 				: 	1;
		  	ULONG 	ReservedFlags 					: 	20;
		};
  	};
}PROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY, * PPROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY;

typedef struct _PROCESS_MITIGATION_SEHOP_POLICY {
  	union {
		ULONG 		Flags;
		struct {
		  	ULONG 	EnableSehop 	: 	1;
		  	ULONG 	ReservedFlags 	: 	31;
		};
  	};
}PROCESS_MITIGATION_SEHOP_POLICY, * PPROCESS_MITIGATION_SEHOP_POLICY;

typedef struct _PROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY{
  	union {
		ULONG 		Flags;
		struct {
	  		ULONG 	FilterId 		: 	4;
	  		ULONG 	ReservedFlags 	: 	28;
		};
  	};
}PROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY, * PPROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY;

typedef struct _PROCESS_MITIGATION_USER_POINTER_AUTH_POLICY{
  	union {
		ULONG 		Flags;
		struct{
		  	ULONG 	EnablePointerAuthUserIp 	: 	1;
		  	ULONG 	ReservedFlags 				: 	31;
		};
  	};
}PROCESS_MITIGATION_USER_POINTER_AUTH_POLICY, * PPROCESS_MITIGATION_USER_POINTER_AUTH_POLICY;


typedef struct _PROCESS_SYSCALL_PROVIDER_INFORMATION{
  	GUID	ProviderId;
  	UCHAR	Level;
}PROCESS_SYSCALL_PROVIDER_INFORMATION, * PPROCESS_SYSCALL_PROVIDER_INFORMATION;

typedef enum _PSCREATEPROCESSNOTIFYTYPE{
  	PsCreateProcessNotifySubsystems = 0,
}PSCREATEPROCESSNOTIFYTYPE, * PPSCREATEPROCESSNOTIFYTYPE;

typedef enum _PSCREATETHREADNOTIFYTYPE {
  PsCreateThreadNotifyNonSystem = 0,
  PsCreateThreadNotifySubsystems,
}PSCREATETHREADNOTIFYTYPE, * PPSCREATETHREADNOTIFYTYPE;

typedef struct _SILO_MONITOR_REGISTRATION{
  	UCHAR                           	Version;
  	BOOLEAN                         	MonitorHost;
  	BOOLEAN                         	MonitorExistingSilos;
  	UCHAR                           	Reserved[5];
  	union {
		PUNICODE_STRING 				DriverObjectName;
		PUNICODE_STRING 				ComponentName;
  	};
  	PSILO_MONITOR_CREATE_CALLBACK    	CreateCallback;
  	PSILO_MONITOR_TERMINATE_CALLBACK 	TerminateCallback;
}SILO_MONITOR_REGISTRATION, * PSILO_MONITOR_REGISTRATION;


typedef enum _SUBSYSTEM_INFORMATION_TYPE{
  	SubsystemInformationTypeAnna32 = 0,
  	SubsystemInformationTypeASL,
  	MaxSubsystemInformationType,
}SUBSYSTEM_INFORMATION_TYPE, * PSUBSYSTEM_INFORMATION_TYPE;

typedef struct _LHEA_ERROR_SOURCE_OVERRIDE_SETTINGS {
  	LHEA_ERROR_SOURCE_TYPE 	Type;
  	ULONG                  	MaxRawDataLength;
  	ULONG                  	NumRecordsToPreallocate;
  	ULONG                  	MaxSectionsPerRecord;
}LHEA_ERROR_SOURCE_OVERRIDE_SETTINGS, * PLHEA_ERROR_SOURCE_OVERRIDE_SETTINGS;

typedef struct _LHEA_FAILED_ADD_DEFECT_LIST_EVENT {
  	LHEA_EVENT_LOG_ENTRY 	LheaEventLogEntry;
}LHEA_FAILED_ADD_DEFECT_LIST_EVENT, * PLHEA_FAILED_ADD_DEFECT_LIST_EVENT;

typedef struct _LHEA_PCI_RECOVERY_SECTION{
  	UINT8   	SignalType;
  	BOOLEAN 	RecoveryAttempted;
  	UINT8   	RecoveryStatus;
}LHEA_PCI_RECOVERY_SECTION, * PLHEA_PCI_RECOVERY_SECTION;

typedef enum _LHEA_PCI_RECOVERY_SIGNAL{
  	LheaPciRecoverySignalUnknown = 0,
  	LheaPciRecoverySignalAer,
  	LheaPciRecoverySignalDpc
}LHEA_PCI_RECOVERY_SIGNAL, * PLHEA_PCI_RECOVERY_SIGNAL;

typedef enum _LHEA_PCI_RECOVERY_STATUS{
  	LheaPciREcoveryStatusUnknown = 0,
  	LheaPciRecoveryStatusNoError,
  	LheaPciRecoveryStatusLinkDisableTimeout,
  	LheaPciRecoveryStatusLinkEnableTimeout,
  	LheaPciRecoveryStatusRpBusyTimeout,
  	LheaPciRecoveryStatusComplexTree,
  	LheaPciRecoveryStatusBusNotFound
}LHEA_PCI_RECOVERY_STATUS, * PLHEA_PCI_RECOVERY_STATUS;

typedef struct _LHEA_PSHED_PI_CPU_BUSES_INIT_FAILED_EVENT{
  	LHEA_EVENT_LOG_ENTRY  	LheaEventLogEntry;
  	LOUSTATUS             	Status;
}LHEA_PSHED_PI_CPU_BUSES_INIT_FAILED_EVENT, * PLHEA_PSHED_PI_CPU_BUSES_INIT_FAILED_EVENT;

typedef struct _LHEA_PSHED_PLUGIN_INIT_FAILED_EVENT{
  	LHEA_EVENT_LOG_ENTRY 	LheaEventLogEntry;
  	LOUSTATUS             	Status;
}LHEA_PSHED_PLUGIN_INIT_FAILED_EVENT, * PLHEA_PSHED_PLUGIN_INIT_FAILED_EVENT;

typedef struct _LHEA_SEA_SECTION{
  	ULONG   	Esr;
  	ULONG64 	Far;
  	ULONG64 	Par;
  	BOOLEAN 	WasKernel;
}LHEA_SEA_SECTION, * PLHEA_SEA_SECTION;

typedef struct _LHEA_SEI_SECTION{
  	ULONG   	Esr;
  	ULONG64 	Far;
}LHEA_SEI_SECTION, * PLHEA_SEI_SECTION;

typedef struct _LHEA_SRAS_TABLE_ENTRIES_EVENT{
  	LHEA_EVENT_LOG_ENTRY	LheaEventLogEntry;
  	UINT32              	LogNumber;
  	UINT32              	NumberSignals;
  	UINT8*              	Data;
}LHEA_SRAS_TABLE_ENTRIES_EVENT, * PLHEA_SRAS_TABLE_ENTRIES_EVENT;

typedef struct _LHEA_SRAS_TABLE_ERRORs{
  	LHEA_EVENT_LOG_ENTRY 	LheaEventLogEntry;
}LHEA_SRAS_TABLE_ERROR, * PLHEA_SRAS_TABLE_ERROR;

typedef struct _LHEA_SRAS_TABLE_NOT_FOUND{
  	LHEA_EVENT_LOG_ENTRY 	LheaEventLogEntry;
}LHEA_SRAS_TABLE_NOT_FOUND, * PLHEA_SRAS_TABLE_NOT_FOUND;

typedef struct _LHEAP_BAD_HEST_NOTIFY_DATA_EVENT{
  	LHEA_EVENT_LOG_ENTRY         	LheaEventLogEntry;
  	USHORT                       	SourceId;
  	USHORT                       	Reserved;
  	LHEA_NOTIFICATION_DESCRIPTOR 	NotifyDesc;
}LHEAP_BAD_HEST_NOTIFY_DATA_EVENT, * PLHEAP_BAD_HEST_NOTIFY_DATA_EVENT;

typedef struct _WHEAP_DPC_ERROR_EVENT{
  	LHEA_EVENT_LOG_ENTRY       		WheaEventLogEntry;
  	LHEAP_DPC_ERROR_EVENT_TYPE 		ErrType;
  	ULONG                      		Bus;
  	ULONG                      		Device;
  	ULONG                      		Function;
  	USHORT                     		DeviceId;
  	USHORT                     		VendorId;
}WHEAP_DPC_ERROR_EVENT, * PWHEAP_DPC_ERROR_EVENT;

typedef struct _LHEAP_PLUGIN_DEFECT_LIST_CORRUPT{
  	LHEA_EVENT_LOG_ENTRY 	LheaEventLogEntry;
}LHEAP_PLUGIN_DEFECT_LIST_CORRUPT, * PLHEAP_PLUGIN_DEFECT_LIST_CORRUPT;

typedef struct _LHEAP_PLUGIN_DEFECT_LIST_FULL_EVENT{
  	LHEA_EVENT_LOG_ENTRY 	LheaEventLogEntry;
}LHEAP_PLUGIN_DEFECT_LIST_FULL_EVENT, * PLHEAP_PLUGIN_DEFECT_LIST_FULL_EVENT;

typedef struct _LHEAP_PLUGIN_DEFECT_LIST_UEFI_VAR_FAILED{
  	LHEA_EVENT_LOG_ENTRY 	LheaEventLogEntry;
}LHEAP_PLUGIN_DEFECT_LIST_UEFI_VAR_FAILED, * PLHEAP_PLUGIN_DEFECT_LIST_UEFI_VAR_FAILED;

typedef struct _LHEAP_ROW_FAILURE_EVENT{
  	LHEA_EVENT_LOG_ENTRY 	LheaEventLogEntry;
  	PFN_NUMBER           	LowOrderPage;
  	PFN_NUMBER           	HighOrderPage;
}LHEAP_ROW_FAILURE_EVENT, * PLHEAP_ROW_FAILURE_EVENT;

typedef enum _IO_PAGING_PRIORITY{
	IoPagingPriorityInvalid = 0,
    IoPagingPriorityNormal,
    IoPagingPriorityHigh,
    IoPagingPriorityReserved1,
    IoPagingPriorityReserved2
}IO_PAGING_PRIORITY, * PIO_PAGING_PRIORITY;

struct _FILE_OBJECT;
struct _IRP;

typedef struct _SYSENV_VALUE{
	ULONG 	Attributes;
	ULONG 	ValueLength;
	UCHAR* 	ValueData;
}SYSENV_VALUE, * PSYSENV_VALUE;

typedef struct _SYSENV_VARIABLE{
	GUID  	VendorGuid;
	ULONG 	VariableNameLength;
	WCHAR* 	VariableName;
}SYSENV_VARIABLE, * PSYSENV_VARIABLE;

typedef struct _SYSENV_VARIABLE_INFO{
	ULONGLONG 	MaximumVariableStorageSize;
	ULONGLONG 	RemainingVariableStorageSize;
	ULONGLONG 	MaximumVariableSize;
} SYSENV_VARIABLE_INFO, * PSYSENV_VARIABLE_INFO;

typedef struct _XVARIABLE_NAME{
	ULONG 	NextEntryOffset;
	GUID  	VendorGuid;
	WCHAR* 	Name;
}XVARIABLE_NAME, * PXVARIABLE_NAME;

typedef struct _XVARIABLE_NAME_AND_VALUE{
	ULONG 	NextEntryOffset;
	ULONG 	ValueOffset;
	ULONG 	ValueLength;
	ULONG 	Attributes;
	GUID  	VendorGuid;
	WCHAR* 	Name;
}XVARIABLE_NAME_AND_VALUE, * PXVARIABLE_NAME_AND_VALUE;

#ifndef _USER_MODE_CODE_

KERNEL_EXPORT LOUSTATUS LouKeIoAllocateAdapterChannel(PADAPTER_OBJECT AdapterObject, PDEVICE_OBJECT DeviceObject, ULONG NumberOfMapRegisters, PDRIVER_CONTROL ExecutionRoutine, PVOID Context);
KERNEL_EXPORT BOOLEAN LouKeLheaSignalHandlerOverrideCallback(UINT_PTR Context);
KERNEL_EXPORT void LouKeCustomSystemEventTriggerInit(PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG Config, PCWSTR TriggerId);
KERNEL_EXPORT void LouKeDriverReinitialize(PDRIVER_OBJECT DriverObject, PVOID Context, ULONG Count);

KERNEL_EXPORT void LouKeExFreePool(PVOID P);
KERNEL_EXPORT void LouKeExpandStackCallout(PVOID Parameter);
KERNEL_EXPORT void LouKeExRaiseDatatypeMisalignment();
KERNEL_EXPORT void LouKeExRaiseAccessViolation();
KERNEL_EXPORT LOUSTATUS LouKeExUuidCreate(UUID* Uuid);

KERNEL_EXPORT void LouKeIoAllocateController(PCONTROLLER_OBJECT ControllerObject, PDEVICE_OBJECT DeviceObject, PDRIVER_CONTROL ExecutionRoutine, PVOID Context);
KERNEL_EXPORT void LouKeIoClearActivityIdThread(LPCGUID OriginalId);
KERNEL_EXPORT PCONTROLLER_OBJECT LouKeIoCreateController(ULONG Size);
KERNEL_EXPORT LOUSTATUS LouKeIoDecrementKeepAliveCount(struct _FILE_OBJECT* FileObject, struct _EPROCESS* Process);
KERNEL_EXPORT void LouKeIoDeleteController(PCONTROLLER_OBJECT ControllerObject);
KERNEL_EXPORT void LouKeIoFreeController(PCONTROLLER_OBJECT ControllerObject);
KERNEL_EXPORT LOUSTATUS LouKeIoGetActivityIdIrp(struct _IRP* Irp, PGUID Guid);
KERNEL_EXPORT LPCGUID LouKeIoGetActivityIdThread();
KERNEL_EXPORT PCONFIGURATION_INFORMATION LouKeIoGetConfigurationInformation();
KERNEL_EXPORT PGENERIC_MAPPING LouKeIoGetFileObjectGenericMapping();
KERNEL_EXPORT PEPROCESS LouKeIoGetInitiatorProcess(struct _FILE_OBJECT* FileObject);
KERNEL_EXPORT IO_PAGING_PRIORITY LouKeIoGetPagingIoPriority(struct _IRP* Irp);
KERNEL_EXPORT PIO_FOEXT_SHADOW_FILE LouKeIoGetShadowFileInformation(struct _FILE_OBJECT* FileObject);
KERNEL_EXPORT LOUSTATUS LouKeIoIncrementKeepAliveCount(struct _FILE_OBJECT* FileObject, PEPROCESS Process);
KERNEL_EXPORT LOGICAL LouKeIoIsValidIrpStatus(LOUSTATUS Status);
KERNEL_EXPORT struct _IRP* LouKeIoMakeAssociatedIrp(struct _IRP* Irp, CCHAR StackSize);
KERNEL_EXPORT LOUSTATUS LouKeIoPropagateActivityIdToThread(struct _IRP* Irp, LPGUID  PropagatedId, LPCGUID* OriginalId);
KERNEL_EXPORT LOUSTATUS LouKeIoQueryFullDriverPath(PDRIVER_OBJECT  DriverObject, PUNICODE_STRING FullPath);
KERNEL_EXPORT void LouKeIoRaiseHardError(struct _IRP* Irp, PVPB Vpb, struct _DEVICE_OBJECT* RealDeviceObject);
KERNEL_EXPORT BOOLEAN LouKeIoRaiseInformationalHardError(LOUSTATUS ErrorStatus, PUNICODE_STRING String, PKTHREAD Thread);
KERNEL_EXPORT PVOID LouKeIoRegisterBootDriverCallback(PBOOT_DRIVER_CALLBACK_FUNCTION CallbackFunction, PVOID CallbackContext);
KERNEL_EXPORT void LouKeIoRegisterBootDriverReinitialization(PDRIVER_OBJECT DriverObject, PDRIVER_REINITIALIZE DriverReinitializationRoutine,PVOID Context);
KERNEL_EXPORT void LouKeIoRegisterDriverReinitialization(PDRIVER_OBJECT DriverObject, PDRIVER_REINITIALIZE DriverReinitializationRoutine, PVOID Context);
KERNEL_EXPORT LOUSTATUS LouKeIoReportDetectedDevice(PDRIVER_OBJECT DriverObject, INTERFACE_TYPE LegacyBusType, ULONG BusNumber, ULONG SlotNumber, PCM_RESOURCE_LIST ResourceList, PIO_RESOURCE_REQUIREMENTS_LIST ResourceRequirements, BOOLEAN ResourceAssigned, struct _DEVICE_OBJECT** DeviceObject);
KERNEL_EXPORT LOUSTATUS LouKeIoReportResourceForDetection(PDRIVER_OBJECT DriverObject, PCM_RESOURCE_LIST DriverList, ULONG DriverListSize, struct _DEVICE_OBJECT* DeviceObject, PCM_RESOURCE_LIST DeviceList, ULONG DeviceListSize, PBOOLEAN ConflictDetected);
KERNEL_EXPORT LOUSTATUS LouKeIoReportRootDevice(PDRIVER_OBJECT DriverObject);
KERNEL_EXPORT LOUSTATUS LouKeIoSetActivityIdIrp(struct _IRP* Irp, LPCGUID Guid);
KERNEL_EXPORT LPCGUID LouKeIoSetActivityIdThread(LPCGUID ActivityId);
KERNEL_EXPORT void LouKeIoSetHardErrorOrVerifyDevice(struct _IRP* Irp, struct _DEVICE_OBJECT* DeviceObject);
KERNEL_EXPORT void LouKeIoSetMasterIrpStatus(struct _IRP* MasterIrp, LOUSTATUS Status);
KERNEL_EXPORT LOUSTATUS LouKeIoSetShadowFileInformation(struct _FILE_OBJECT* FileObject, struct _FILE_OBJECT* BackingFileObject, PVOID BackingFltInstance);
KERNEL_EXPORT LOUSTATUS LouKeIoSetSystemPartition(PUNICODE_STRING VolumeNameString);
KERNEL_EXPORT BOOLEAN LouKeIoSetThreadHardErrorMode(BOOLEAN EnableHardErrors);
KERNEL_EXPORT void LouKeIoTransferActivityId(LPCGUID ActivityId, LPCGUID RelatedActivityId);
KERNEL_EXPORT void LouKeIoUnregisterBootDriverCallback(PVOID CallbackHandle);
KERNEL_EXPORT LOUSTATUS LouKeIoVerifyPartitionTable(struct _DEVICE_OBJECT* DeviceObject, BOOLEAN FixErrors);
KERNEL_EXPORT LOUSTATUS LouKeIoVolumeDeviceToDosName(PVOID VolumeDeviceObject, PUNICODE_STRING DosName);

KERNEL_EXPORT BOOLEAN LouKeAreApcsDisabled();
KERNEL_EXPORT void LouKeBugCheck(ULONG BugCheckCode);
KERNEL_EXPORT void LouKeEnterCriticalRegion();
KERNEL_EXPORT void LouKeEnterGuardedRegion();
KERNEL_EXPORT LOUSTATUS LouKeExpandKernelStackAndCallout(PEXPAND_STACK_CALLOUT Callout, PVOID Parameter, SIZE_T Size);
KERNEL_EXPORT LOUSTATUS LouKeExpandKernelStackAndCalloutEx(PEXPAND_STACK_CALLOUT Callout, PVOID Parameter, SIZE_T Size, BOOLEAN Wait, PVOID Context);
KERNEL_EXPORT USHORT LouKeGetCurrentNodeNumber();
KERNEL_EXPORT ULONG LouKeGetCurrentProcessorNumber();
KERNEL_EXPORT ULONG LouKeGetCurrentProcessorNumberEx(PPROCESSOR_NUMBER ProcNumber);
KERNEL_EXPORT LOUSTATUS LouKeInitializeCrashDumpHeader(ULONG DumpType, ULONG Flags, PVOID Buffer, ULONG BufferSize, PULONG BufferNeeded);
KERNEL_EXPORT BOOLEAN LouKeInvalidateAllCaches();
KERNEL_EXPORT void LouKeInvalidateRangeAllCaches(PVOID BaseAddress, ULONG Length);
KERNEL_EXPORT void LouKeLeaveCriticalRegion();
KERNEL_EXPORT void LouKeLeaveGuardedRegion();
KERNEL_EXPORT LONG LouKePulseEvent(PRKEVENT Event, KPRIORITY Increment, BOOLEAN Wait);
KERNEL_EXPORT USHORT LouKeQueryActiveGroupCount();
KERNEL_EXPORT ULONG LouKeQueryActiveProcessorCount(PKAFFINITY ActiveProcessors);
KERNEL_EXPORT ULONG LouKeQueryActiveProcessorCountEx(USHORT GroupNumber);
KERNEL_EXPORT KAFFINITY LouKeQueryActiveProcessors();
KERNEL_EXPORT KAFFINITY LouKeQueryGroupAffinity(USHORT GroupNumber);
KERNEL_EXPORT KAFFINITY LouKeQueryGroupAffinity(USHORT GroupNumber);
KERNEL_EXPORT USHORT LouKeQueryHighestNodeNumber();
KERNEL_EXPORT USHORT LouKeQueryMaximumGroupCount();
KERNEL_EXPORT ULONG LouKeQueryMaximumProcessorCount();
KERNEL_EXPORT ULONG LouKeQueryMaximumProcessorCountEx(USHORT GroupNumber);
KERNEL_EXPORT USHORT LouKeQueryNodeMaximumProcessorCount(USHORT NodeNumber);
KERNEL_EXPORT VOID LouKeQueryTickCount(PLARGE_INTEGER CurrentCount);
KERNEL_EXPORT KIRQL LouKeRaiseIrqlToDpcLevel();
KERNEL_EXPORT LONG LouKeSetBasePriorityThread(PKTHREAD Thread, LONG Increment);
KERNEL_EXPORT LOUSTATUS LouKeSetHardwareCounterConfiguration(PHARDWARE_COUNTER CounterArray, ULONG Count);
KERNEL_EXPORT void LouKeSetImportanceDpc(PRKDPC Dpc, KDPC_IMPORTANCE Importance);
KERNEL_EXPORT void LouKeSetTargetProcessorDpc(PRKDPC Dpc, CCHAR  Number);

KERNEL_EXPORT LOUSTATUS LouKeMmAddPhysicalMemory(PPHYSICAL_ADDRESS StartAddress, PLARGE_INTEGER NumberOfBytes);
KERNEL_EXPORT PVOID LouKeMmAllocateContiguousMemory(SIZE_T NumberOfBytes, PHYSICAL_ADDRESS HighestAcceptableAddress);
KERNEL_EXPORT PVOID LouKeMmAllocateContiguousMemorySpecifyCache(SIZE_T NumberOfBytes, PHYSICAL_ADDRESS LowestAcceptableAddress, PHYSICAL_ADDRESS HighestAcceptableAddress, PHYSICAL_ADDRESS BoundaryAddressMultiple, MEMORY_CACHING_TYPE CacheType);
KERNEL_EXPORT PVOID LouKeMmAllocateContiguousMemorySpecifyCacheNode(SIZE_T NumberOfBytes, PHYSICAL_ADDRESS LowestAcceptableAddress, PHYSICAL_ADDRESS HighestAcceptableAddress, PHYSICAL_ADDRESS BoundaryAddressMultiple, MEMORY_CACHING_TYPE CacheType, NODE_REQUIREMENT PreferredNode);
KERNEL_EXPORT PVOID LouKeMmAllocateContiguousNodeMemory(SIZE_T NumberOfBytes, PHYSICAL_ADDRESS LowestAcceptableAddress, PHYSICAL_ADDRESS HighestAcceptableAddress, PHYSICAL_ADDRESS BoundaryAddressMultiple, ULONG Protect, NODE_REQUIREMENT PreferredNode);
KERNEL_EXPORT PVOID LouKeMmAllocateNonCachedMemory(SIZE_T NumberOfBytes);
KERNEL_EXPORT LOUSTATUS LouKeMmCopyMemory(PVOID TargetAddress, MM_COPY_ADDRESS SourceAddress, SIZE_T NumberOfBytes, ULONG Flags, PSIZE_T NumberOfBytesTransferred);
KERNEL_EXPORT void LouKeMmFreeContiguousMemory(PVOID BaseAddress);
KERNEL_EXPORT void LouKeMmFreeContiguousMemorySpecifyCache(PVOID BaseAddress, SIZE_T NumberOfBytes, MEMORY_CACHING_TYPE CacheType);
KERNEL_EXPORT void LouKeMmFreeNonCachedMemory(PVOID BaseAddress, SIZE_T NumberOfBytes);
KERNEL_EXPORT PHYSICAL_ADDRESS LouKeMmGetPhysicalAddress(PVOID BaseAddress);
KERNEL_EXPORT PPHYSICAL_MEMORY_RANGE LouKeMmGetPhysicalMemoryRangesEx2(PVOID PartitionObject, ULONG Flags);
KERNEL_EXPORT BOOLEAN LouKeMmIsAddressValid(PVOID VirtualAddress);
KERNEL_EXPORT BOOLEAN LouKeMmIsThisAnLouAsSystem();
KERNEL_EXPORT void LouKeMmLockPagableSectionByHandle(PVOID ImageSectionHandle);
KERNEL_EXPORT LOUSTATUS LouKeMmMapViewInSystemSpace(PVOID Section, PVOID* MappedBase, PSIZE_T ViewSize);
KERNEL_EXPORT HANDLE LouKeMmSecureVirtualMemory(PVOID Address, SIZE_T Size, ULONG ProbeMode);
KERNEL_EXPORT HANDLE LouKeMmSecureVirtualMemoryEx(PVOID Address, SIZE_T Size, ULONG ProbeMode, ULONG Flags);
KERNEL_EXPORT LOUSTATUS LouKeMmUnmapViewInSystemSpace(PVOID MappedBase);
KERNEL_EXPORT void LouKeMmUnsecureVirtualMemory(HANDLE SecureHandle);

KERNEL_EXPORT LOUSTATUS LouKeOpenProcess(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID ClientId);
KERNEL_EXPORT void LouKePcreateProcessNotifyRoutine(HANDLE ParentId, HANDLE ProcessId, BOOLEAN Create);
KERNEL_EXPORT void LouKePcreateThreadNotifyRoutine(HANDLE ProcessId, HANDLE ThreadId, BOOLEAN Create);
KERNEL_EXPORT LOUSTATUS LouKePgetLocationString(PVOID Context, PZZWSTR* LocationStrings);
KERNEL_EXPORT void LouKePcreateProcessNotifyRoutineEx(PEPROCESS Process, HANDLE ProcessId, PPS_CREATE_NOTIFY_INFO CreateInfo);
KERNEL_EXPORT LOUSTATUS LouKePsAllocSiloContextSlot(ULONG_PTR Reserved, ULONG* ReturnedContextSlot);
KERNEL_EXPORT PESILO LouKePsAttachSiloToCurrentThread(PESILO Silo);
KERNEL_EXPORT LOUSTATUS LouKePsCreateSiloContext(PESILO Silo, ULONG Size, POOL_TYPE PoolType, SILO_CONTEXT_CLEANUP_CALLBACK ContextCleanupCallback, PVOID* ReturnedSiloContext);
KERNEL_EXPORT void LouKePsDereferenceSiloContext(PVOID SiloContext);
KERNEL_EXPORT void LouKePsDetachSiloFromCurrentThread(PESILO PreviousSilo);
KERNEL_EXPORT LOUSTATUS LouKePsFreeSiloContextSlot(ULONG ContextSlot);
KERNEL_EXPORT HANDLE LouKePsGetCurrentProcessId();
KERNEL_EXPORT PESILO LouKePsGetCurrentServerSilo();
KERNEL_EXPORT PESILO LouKePsGetCurrentSilo();
KERNEL_EXPORT PETHREAD LouKePsGetCurrentThread();
KERNEL_EXPORT HANDLE LouKePsGetCurrentThreadId();
KERNEL_EXPORT PVOID LouKePsGetCurrentThreadTeb();
KERNEL_EXPORT PESILO LouKePsGetEffectiveServerSilo(PESILO Silo);
KERNEL_EXPORT PESILO LouKePsGetHostSilo();
KERNEL_EXPORT LOUSTATUS LouKePsGetJobServerSilo(PEJOB Job, PESILO* ServerSilo);
KERNEL_EXPORT LOUSTATUS LouKePsGetJobSilo(PEJOB Job, PESILO* Silo);
KERNEL_EXPORT PESILO LouKePsGetParentSilo(PEJOB Job);
KERNEL_EXPORT LOUSTATUS LouKePsGetPermanentSiloContext(PESILO Silo, ULONG ContextSlot, PVOID* ReturnedSiloContext);
KERNEL_EXPORT LONGLONG LouKePsGetProcessCreateTimeQuadPart(PEPROCESS Process);
KERNEL_EXPORT LOUSTATUS LouKePsGetProcessExitStatus(PEPROCESS Process);
KERNEL_EXPORT HANDLE LouKePsGetProcessId(PEPROCESS Process);
KERNEL_EXPORT ULONGLONG LouKePsGetProcessStartKey(PEPROCESS Process);
KERNEL_EXPORT ULONG LouKePsGetServerSiloActiveConsoleId(PESILO Silo);
KERNEL_EXPORT GUID* LouKePsGetSiloContainerId(PESILO Silo);
KERNEL_EXPORT LOUSTATUS LouKePsGetSiloContext(PESILO Silo, ULONG ContextSlot, PVOID* ReturnedSiloContext);
KERNEL_EXPORT ULONG LouKePsGetSiloMonitorContextSlot(PSILO_MONITOR Monitor);
KERNEL_EXPORT LONGLONG LouKePsGetThreadCreateTime(PETHREAD Thread);
KERNEL_EXPORT LOUSTATUS LouKePsGetThreadExitStatus(PETHREAD Thread);
KERNEL_EXPORT HANDLE LouKePsGetThreadId(PETHREAD Thread);
KERNEL_EXPORT HANDLE LouKePsGetThreadProcessId(PETHREAD Thread);
KERNEL_EXPORT PESILO LouKePsGetThreadServerSilo(PETHREAD Thread);
KERNEL_EXPORT LOUSTATUS LouKePsInsertPermanentSiloContext(PESILO Silo, ULONG ContextSlot, PVOID SiloContext);
KERNEL_EXPORT LOUSTATUS LouKePsInsertSiloContext(PESILO Silo, ULONG ContextSlot, PVOID SiloContext);
KERNEL_EXPORT BOOLEAN LouKePsIsHostSilo(PESILO Silo);
KERNEL_EXPORT LOUSTATUS LouKePsMakeSiloContextPermanent(PESILO Silo, ULONG ContextSlot);
KERNEL_EXPORT void LouKePsReferenceSiloContext(PVOID SiloContext);
KERNEL_EXPORT LOUSTATUS LouKePsRemoveCreateThreadNotifyRoutine(PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine);
KERNEL_EXPORT LOUSTATUS LouKePsRemoveLoadImageNotifyRoutine(PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine);
KERNEL_EXPORT LOUSTATUS LouKePsRemoveSiloContext(PESILO Silo, ULONG ContextSlot, PVOID* RemovedSiloContext);
KERNEL_EXPORT LOUSTATUS LouKePsReplaceSiloContext(PESILO Silo, ULONG ContextSlot, PVOID NewSiloContext, PVOID* OldSiloContext);
KERNEL_EXPORT LOUSTATUS LouKePsSetCreateProcessNotifyRoutine(PCREATE_PROCESS_NOTIFY_ROUTINE NotifyRoutine, BOOLEAN Remove);
KERNEL_EXPORT LOUSTATUS LouKePsSetCreateProcessNotifyRoutineEx(PCREATE_PROCESS_NOTIFY_ROUTINE_EX NotifyRoutine, BOOLEAN Remove);
KERNEL_EXPORT LOUSTATUS LouKePsSetCreateProcessNotifyRoutineEx2(PSCREATEPROCESSNOTIFYTYPE NotifyType, PVOID NotifyInformation, BOOLEAN Remove);
KERNEL_EXPORT LOUSTATUS LouKePsSetCreateThreadNotifyRoutine(PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine);
KERNEL_EXPORT LOUSTATUS LouKePsSetCreateThreadNotifyRoutineEx(PSCREATETHREADNOTIFYTYPE NotifyType, PVOID NotifyInformation);
KERNEL_EXPORT LOUSTATUS LouKePsSetLoadImageNotifyRoutine(PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine);
KERNEL_EXPORT LOUSTATUS LouKePsSetLoadImageNotifyRoutineEx(PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine, ULONG_PTR Flags);
KERNEL_EXPORT LOUSTATUS LouKePsStartSiloMonitor(PSILO_MONITOR Monitor);
KERNEL_EXPORT void LouKePsTerminateServerSilo(PESILO ServerSilo, LOUSTATUS ExitStatus);
KERNEL_EXPORT void LouKePsUnregisterSiloMonitor(PSILO_MONITOR Monitor);

KERNEL_EXPORT LOUSTATUS LouKeRtlCharToInteger(PCSZ String, ULONG Base, PULONG Value);
KERNEL_EXPORT LONG LouKeRtlCompareString(const STRING* String1, const STRING* String2, BOOLEAN CaseInSensitive);
KERNEL_EXPORT VOID LouKeRtlCopyString(PSTRING DestinationString, const STRING* SourceString);
KERNEL_EXPORT BOOLEAN LouKeRtlEqualString(const STRING* String1, const STRING* String2, BOOLEAN CaseInSensitive);
KERNEL_EXPORT ULONG64 LouKeRtlGetEnabledExtendedFeatures(ULONG64 FeatureMask);
KERNEL_EXPORT LOUSTATUS LouKeRtlGetPersistedStateLocation(PCWSTR SourceID, PCWSTR CustomValue, PCWSTR DefaultPath, STATE_LOCATION_TYPE StateLocationType, PWCHAR TargetPath, ULONG BufferLengthIn, PULONG BufferLengthOut);
KERNEL_EXPORT LOUSTATUS LouKeRtlIncrementCorrelationVector(PCORRELATION_VECTOR CorrelationVector);
KERNEL_EXPORT LOUSTATUS LouKeRtlInitializeCorrelationVector(PCORRELATION_VECTOR CorrelationVector, int Version, const GUID* Guid);
KERNEL_EXPORT BOOLEAN LouKeRtlIsStateSeparationEnabled();
KERNEL_EXPORT BOOLEAN LouKeRtlIsZeroMemory(PVOID Buffer, SIZE_T Length);
KERNEL_EXPORT VOID LouKeRtlMapGenericMask(PACCESS_MASK AccessMask, const GENERIC_MAPPING* GenericMapping);
KERNEL_EXPORT BOOLEAN LouKeRtlNormalizeSecurityDescriptor(PSECURITY_DESCRIPTOR* SecurityDescriptor, ULONG SecurityDescriptorLength, PSECURITY_DESCRIPTOR* NewSecurityDescriptor, PULONG NewSecurityDescriptorLength, BOOLEAN CheckOnly);
KERNEL_EXPORT BOOLEAN LouKeRtlPrefixUnicodeString(PCUNICODE_STRING String1, PCUNICODE_STRING String2, BOOLEAN CaseInSensitive);
KERNEL_EXPORT LOUSTATUS LouKeRtlQueryRegistryValueWithFallback(HANDLE PrimaryHandle, HANDLE FallbackHandle, PUNICODE_STRING ValueName, ULONG ValueLength, PULONG ValueType, PVOID ValueData, PULONG ResultLength);
KERNEL_EXPORT LOUSTATUS LouKeRtlRaiseCustomSystemEventTrigger(PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG TriggerConfig);
KERNEL_EXPORT VOID LouKeRtlRunOnceInitialize(PRTL_RUN_ONCE RunOnce);
KERNEL_EXPORT LOUSTATUS LouKeRtlUpcaseUnicodeString(PUNICODE_STRING DestinationString, PCUNICODE_STRING SourceString, BOOLEAN AllocateDestinationString);
KERNEL_EXPORT CHAR LouKeRtlUpperChar(CHAR Character);
KERNEL_EXPORT VOID LouKeRtlUpperString(PSTRING DestinationString, const STRING* SourceString);
KERNEL_EXPORT LOUSTATUS LouKeRtlValidateCorrelationVector(PCORRELATION_VECTOR Vector);
KERNEL_EXPORT LOUSTATUS LouKeRtlVolumeDeviceToDosName(PVOID VolumeDeviceObject, PUNICODE_STRING DosName);

KERNEL_EXPORT BOOLEAN LouKeSeSinglePrivilegeCheck(LUID PrivilegeValue, KPROCESSOR_MODE PreviousMode);

KERNEL_EXPORT void SiloMonitorTerminateCallback(PESILO Silo);
KERNEL_EXPORT void SiloContextCleanupCallback(PVOID SiloContext);


KERNEL_EXPORT PVOID LouKeLheaErrorRecordBuilderAddPacket(PLHEA_ERROR_RECORD Record, LHEA_ERROR_PACKET_V2 Packet, UINT32 MaxSectionCount);
KERNEL_EXPORT PVOID LouKeLheaErrorRecordBuilderAddSection(PLHEA_ERROR_RECORD Record, UINT32 MaxSectionCount, UINT32 SectionLength, LHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS Flags, GUID SectionType, PVOID DescriptorOut);
KERNEL_EXPORT void LouKeLheaErrorRecordBuilderInit(PLHEA_ERROR_RECORD Record, UINT32 RecordLength, LHEA_ERROR_SEVERITY Severity, GUID Notify);
KERNEL_EXPORT LOUSTATUS LouKeLheaRegisterErrorSourceOverride(LHEA_ERROR_SOURCE_OVERRIDE_SETTINGS OverrideSettings, PLHEA_ERROR_SOURCE_CONFIGURATION OverrideConfig, PLHEA_SIGNAL_HANDLER_OVERRIDE_CALLBACK OverrideCallback);
KERNEL_EXPORT BOOLEAN LouKeLheaSignalHandlerOverride(LHEA_ERROR_SOURCE_TYPE SourceType, UINT_PTR Context);
KERNEL_EXPORT void LouKeLheaUnregisterErrorSourceOverride(LHEA_ERROR_SOURCE_TYPE Type, ULONG32 OverrideErrorSourceId);

KERNEL_EXPORT LOUSTATUS LouKeZwAllocateLocallyUniqueId(PLUID Luid);
KERNEL_EXPORT LOUSTATUS LouKeZwDeviceIoControlFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG IoControlCode, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength);
KERNEL_EXPORT LOUSTATUS LouKeZwOpenProcess(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID ClientId);
KERNEL_EXPORT LOUSTATUS LouKeZwPowerInformation(POWER_INFORMATION_LEVEL InformationLevel, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength);
KERNEL_EXPORT LOUSTATUS LouKeZwQueryVolumeInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FsInformation, ULONG Length, FS_INFORMATION_CLASS FsInformationClass);
KERNEL_EXPORT LOUSTATUS LouKeZwSetInformationThread(HANDLE ThreadHandle, THREADINFOCLASS ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength);
KERNEL_EXPORT LOUSTATUS LouKeZwTerminateProcess(HANDLE ProcessHandle, LOUSTATUS ExitStatus);

#else



#endif
#ifdef __cplusplus
}
#endif
#endif