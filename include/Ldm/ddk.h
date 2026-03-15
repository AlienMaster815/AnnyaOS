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


#ifndef _USER_MODE_CODE_

KERNEL_EXPORT LOUSTATUS LouKeIoAllocateAdapterChannel(PADAPTER_OBJECT AdapterObject, PDEVICE_OBJECT DeviceObject, ULONG NumberOfMapRegisters, PDRIVER_CONTROL ExecutionRoutine, PVOID Context);
KERNEL_EXPORT BOOLEAN LouKeLheaSignalHandlerOverrideCallback(UINT_PTR Context);
KERNEL_EXPORT void LouKeCustomSystemEventTriggerInit(PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG Config, PCWSTR TriggerId);
KERNEL_EXPORT void LouKeDriverReinitialize(PDRIVER_OBJECT DriverObject, PVOID Context, ULONG Count);
KERNEL_EXPORT void LouKeExFreePool(PVOID P);

#else


#endif
#ifdef __cplusplus
}
#endif
#endif