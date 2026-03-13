#ifndef _LDM_H
#define _LDM_H

#include <Ldm/CommonTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OPAQUE_ARRAY_SIZE 1

typedef PVOID OPAQUE_PTR;

typedef struct _OFFSETINSTANCEDATAANDLENGTH {
    ULONG OffsetInstanceData;
    ULONG LengthInstanceData;
} OFFSETINSTANCEDATAANDLENGTH, * POFFSETINSTANCEDATAANDLENGTH;

typedef enum {
    KernelMode = 0,
    UserMode,
}KPROCESSOR_MODE;

typedef UCHAR KIRQL;

typedef struct _FILE_INTERNAL_INFORMATION{
    LARGE_INTEGER   IndexNumber;
}FILE_INTERNAL_INFORMATION, * PFILE_INTERNAL_INFORMATION;

typedef struct _PREPARSE_DATA_BUFFER{
    ULONG           ReparseTag;
    USHORT          ReparseDataLength;
    USHORT          Reserved;
    union{
        struct {
            USHORT  SubstituteNameOffset;
            USHORT  SubstituteNameLength;
            USHORT  PrintNameOffset;
            USHORT  PrintNameLength;
            ULONG   Flags;
            WCHAR   PathBuffer[1];
        }SymbolicLinkReparseBuffer;
        struct {
            USHORT  SubstituteNameOffset;
            USHORT  SubstituteNameLength;
            USHORT  PrintNameOffset;
            USHORT  PrintNameLength;
            WCHAR   PathBuffer[1];
        }MountPointReparseBuffer;
        struct{
            UCHAR DataBuffer;
        }GenericReparseBuffer;
    };
}PREPARSE_DATA_BUFFER, * PPREPARSE_DATA_BUFFER;

typedef struct _FILE_TIMESTAMPS{
    LARGE_INTEGER   CreationTime;
    LARGE_INTEGER   LastAccessTime;
    LARGE_INTEGER   LastWriteTime;
    LARGE_INTEGER   ChangeTime;
}FILE_TIMESTAMPS, * PFILE_TIMESTAMPS;

typedef BOOLEAN* PBOOLEAN;

typedef enum _OBJECT_INFORMATION_CLASS{
    ObjectBasicInformation = 0,
    ObjectTypeInformation = 2,
}OBJECT_INFORMATION_CLASS;

typedef enum _MEMORY_INFORMATION_CLASS{
    MemoryBasicInformation = 0,
}MEMORY_INFORMATION_CLASS;

typedef const WCHAR* PCWCH;
typedef const CHAR* PCCH;

typedef enum _VIRTUAL_MEMORY_INFORMATION_CLASS{ 
    VmPrefetchInformation = 0,
    VmPagePriorityInformation,
    VmConfigCallTargetInformation,
}VIRTUAL_MEMORY_INFORMATION_CLASS;

typedef struct _MEMORY_RANGE_ENTRY{
    PVOID   VirtualAddrress;
    SIZE    NumberOfBytes;   
}MEMORY_RANGE_ENTRY, * PMEMORY_RANGE_ENTRY;

typedef const char* PCSZ;

typedef const PGUID PCGUID, LPCGUID;

typedef enum _EMULATOR_PORT_ACCESS_TYPE{
    Uchar = 0,
    Ushort,
    Ulong,
}EMULATOR_PORT_ACCESS_TYPE, * PEMULATOR_PORT_ACCESS_TYPE;

typedef PSTR LOUSTRSAFE_PSTR;
typedef PCSTR LOUSTRSAFE_PCSTR;
typedef PWSTR LOUSTRSAFE_PWSTR;
typedef PCWSTR LOUSTRSAFE_PCWSTR;
typedef const char* PCNZCH;
typedef const wchar_t* PCNZWCH;
typedef PCNZCH STRSAFE_PCNZCH;
typedef PCNZWCH STRSAFE_PCNZWCH;
typedef PCUNZWCH STRSAFE_PCUNZWCH;
typedef HANDLE PEPHANDLE;

typedef struct _ACPI_METHOD_ARGUMENT{
    UINT16      Type;
    UINT16      Length;
    union{
        ULONG   Argument;
        UINT8   Data[OPAQUE_ARRAY_SIZE];
    };
}ACPI_METHOD_ARGUMENT, * PACPI_METHOD_ARGUMENT; 

typedef HANDLE* POHANDLE;

typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

typedef VOID(*PINTERFACE_REFERENCE)(PVOID Context);
typedef VOID(*PINTERFACE_DEREFERENCE)(PVOID Context);

typedef ULONG NODE_REQUIREMENT;

typedef enum _LOU_PRODUCT_TYPE{
    LouProductAnnyaLou  = 1,
    LouProductLanManLou = 2,
    LouProductServer    = 3,
}LOU_PRODUCT_TYPE, * PLOU_PRODUCT_TYPE;

typedef enum _ALTERNATIVE_ARCHITECTURE_TYPE{
    StandardDesign  = 0,
    NEC98x86        = 1,
    EndAlternitives = 2,
}ALTERNATIVE_ARCHITECTURE_TYPE, * PALTERNATIVE_ARCHITECTURE_TYPE;

typedef 
void 
PHYSICAL_COUNTER_EVENT_BUFFER_OVERFLOW_HANDLER(
    PVOID   EventBuffer,
    SIZE    EntrySize,
    SIZE    EntryCount,
    HANDLE  Owner
);
typedef PHYSICAL_COUNTER_EVENT_BUFFER_OVERFLOW_HANDLER* PPHYSICAL_COUNTER_EVENT_BUFFER_OVERFLOW_HANDLER;

typedef 
void 
PHYSICAL_COUNTER_OVERFLOW_HANDLER(
    ULONGLONG   OverflowBits,
    HANDLE      Owner
);
typedef PHYSICAL_COUNTER_OVERFLOW_HANDLER* PPHYSICAL_COUNTER_OVERFLOW_HANDLER;

typedef PVOID PKTHREAD;

#include <Ldm/Bdcb.h>

typedef 
void
BOOT_DRIVER_CALLBACK_FUNCTION(
    PVOID                   CallbackContext,
    BDCB_CALLBACK_TYPE      CallType,
    PBDCB_IMAGE_INFORMATION ImageInformation
);
typedef BOOT_DRIVER_CALLBACK_FUNCTION* PBOOT_DRIVER_CALLBACK_FUNCTION;

typedef 
void 
DRIVER_REINITIALIZE(
    PDRIVER_OBJECT  DriverObject,
    PVOID           Context,
    ULONG           Count
);
typedef DRIVER_REINITIALIZE* PDRIVER_REINITIALIZE;

typedef ULONGLONG LOGICAL;

typedef 
void
EXPAND_STACK_CALLOUT(
    PVOID   Parameter
);
typedef EXPAND_STACK_CALLOUT* PEXPAND_STACK_CALLOUT;

typedef ULONG KPRIORITY;

typedef UCHAR KDPC_IMPORTANCE;

typedef struct  _PHYSICAL_MEMORY_RANGE{
    PHYSICAL_ADDRESS    BaseAddress;
    LARGE_INTEGER       NumberOfBytes;
}PHYSICAL_MEMORY_RANGE, * PPHYSICAL_MEMORY_RANGE;

typedef 
LOUSTATUS
GET_LOCATION_STRING(
    PVOID           Context,
    PUNICODE_STRING LocationString
);
typedef GET_LOCATION_STRING* PGET_LOCATION_STRING;

typedef PVOID ESILO;
typedef ESILO* PESILO;

typedef 
void
SILO_CONTEXT_CLEANUP_CALLBACK(
    PVOID   SiloContext
);
typedef SILO_CONTEXT_CLEANUP_CALLBACK* PSILO_CONTEXT_CLEANUP_CALLBACK;

typedef PVOID EJOB;
typedef EJOB* PEJOB;

typedef PVOID           SILO_MONITOR;
typedef SILO_MONITOR    PSILO_MONITOR;

typedef 
void
CREATE_THREAD_NOTIFY_ROUTINE(
    HANDLE  ProcessID,
    HANDLE  ThreadID,
    BOOLEAN Create
);
typedef CREATE_THREAD_NOTIFY_ROUTINE* PCREATE_THREAD_NOTIFY_ROUTINE;

typedef struct _IMAGE_INFO{
	union{
		ULONG       Properties;
		struct {
			ULONG   ImageAddressingMode     : 8;
			ULONG   SystemModeImage         : 1;
			ULONG   ImageMappedToAllPids    : 1;
			ULONG   ExtendedInfoPresent     : 1;
			ULONG   MachineTypeMismatch     : 1;
			ULONG   ImageSignatureLevel     : 4;
			ULONG   ImageSignatureType      : 3;
			ULONG   ImagePartialMap         : 1;
			ULONG   Reserved                : 12;
		};
	};
	PVOID           ImageBase;
	ULONG           ImageSelector;
	SIZE_T          ImageSize;
	ULONG           ImageSectionNumber;
} IMAGE_INFO, * PIMAGE_INFO;

typedef 
void 
LOAD_IMAGE_NOTIFY_ROUTINE(
    PUNICODE_STRING FullImageName,
    HANDLE          ProcessID,
    PIMAGE_INFO     ImageInfo
);
typedef void* PLOAD_IMAGE_NOTIFY_ROUTINE;

typedef struct _PS_CREATE_NOTIFY_INFO{
    SIZE                    Size;
    union{      
    ULONG                   Flags;
        struct {        
            ULONG           FileOpenNamAvailable    : 1;
            ULONG           IsSubsystemProcess      : 1;
            ULONG           Reserved                : 30;
        };      
    };      
    HANDLE                  ParrentProcessId;
    CLIENT_ID               CreatingThreadId;
    struct _FILE_OBJECT*    FileObjet;
    PCUNICODE_STRING        ImageFileName;
    PCUNICODE_STRING        CommandLine;
}PS_CREATE_NOTIFY_INFO, * PPS_CREATE_NOTIFY_INFO;

typedef 
void 
CREATE_PROCESS_NOTIFY_ROUTINE(
    HANDLE                      ParrentId,
    HANDLE                      ProcessId,
    PPS_CREATE_NOTIFY_INFO      CreateInfo
);
typedef CREATE_PROCESS_NOTIFY_ROUTINE* PCREATE_PROCESS_NOTIFY_ROUTINE;

typedef 
void 
CREATE_PROCESS_NOTIFY_ROUTINE_EX(
    PEPROCESS               Process,
    HANDLE                  ProcessId,
    PPS_CREATE_NOTIFY_INFO  CreateInfo
);
typedef CREATE_PROCESS_NOTIFY_ROUTINE_EX* PCREATE_PROCESS_NOTIFY_ROUTINE_EX;

typedef struct _CORRELATION_VECTOR{
    CHAR    Version;
    CHAR    Vector[1];
}CORRELATION_VECTOR, * PCORRELATION_VECTOR;

typedef 
LOUSTATUS 
SILO_MONITOR_CREATE_CALLBACK(
    PESILO Silo
);
typedef SILO_MONITOR_CREATE_CALLBACK* PSILO_MONITOR_CREATE_CALLBACK;

typedef 
void 
SILO_MONITOR_TERMINATE_CALLBACK(
    PESILO Silo
);
typedef SILO_MONITOR_TERMINATE_CALLBACK* PSILO_MONITOR_TERMINATE_CALLBACK;

#include <Ldm/Lhea.h>

typedef void* PFN_NUMBER;

typedef 
LOUSTATUS
GPE_SERVICE_ROUTINE(
    PVOID,
    PVOID
);
typedef GPE_SERVICE_ROUTINE* PGPE_SERVICE_ROUTINE;

typedef 
void 
GPE_DISCONNECT_VECTOR2(
    PVOID   Context,
    PVOID   ObjectContext
);
typedef GPE_DISCONNECT_VECTOR2* PGPE_DISCONNECT_VECTOR2;

typedef 
LOUSTATUS
GPE_ENABLE_EVENT2(
    PVOID   Context,
    PVOID   ObjectContext
);
typedef GPE_ENABLE_EVENT2* PGPE_ENABLE_EVENT2;

typedef 
LOUSTATUS
GPE_DISABLE_EVENT2(
    PVOID   Context,
    PVOID   ObjectContext
);
typedef GPE_DISABLE_EVENT2* PGPE_DISABLE_EVENT2;

typedef 
LOUSTATUS
GPE_CLEAR_STATUS2(
    PVOID   Context,
    PVOID   ObjectContext
);
typedef GPE_CLEAR_STATUS2* PGPE_CLEAR_STATUS2;

typedef 
ULONG 
DEVICE_NOTIFTY_CALLBACK(
    PVOID   Context,
    ULONG   Type,
    PVOID   Settings
);
typedef DEVICE_NOTIFTY_CALLBACK* PDEVICE_NOTIFTY_CALLBACK;

typedef
LOUSTATUS 
REGISTER_FOR_DEVICE_NOTIFICATIONS2(
    PVOID                       Context,
    PDEVICE_NOTIFTY_CALLBACK    Notify,
    PVOID                       NotificationContext
);
typedef REGISTER_FOR_DEVICE_NOTIFICATIONS2* PREGISTER_FOR_DEVICE_NOTIFICATIONS2;

#include <Ldm/Drives.h>

#include <Ldm/Dma.h>

#include <Ldm/miniport.h>

typedef 
LOUSTATUS 
GPE_CONNECT_VECTOR2(
    PVOID                   Context,
    ULONG                   GpeNumber,
    KINTERRUPT_MODE         Mode,
    BOOLEAN                 Shareable,
    PGPE_SERVICE_ROUTINE    ServiceRoutine,
    PVOID                   ServiceContext,
    PVOID*                  ObjectContext
);
typedef GPE_CONNECT_VECTOR2* PGPE_CONNECT_VECTOR2;

typedef 
void
UNREGISTER_FOR_DEVICE_NOTIFICATIONS2(
    PVOID   Conteext
);
typedef UNREGISTER_FOR_DEVICE_NOTIFICATIONS2* PUNREGISTER_FOR_DEVICE_NOTIFICATIONS2;

typedef
BOOLEAN TRANSLATE_BUS_ADDRESS(
    PVOID               Context,
    PHYSICAL_ADDRESS    BusAddress,
    ULONG               Length,
    PULONG              AddressSpace,
    PPHYSICAL_ADDRESS   TranslatedAddress
);
typedef TRANSLATE_BUS_ADDRESS *PTRANSLATE_BUS_ADDRESS;

typedef 
ULONG 
GET_SET_DEVICE_DATA(
    PVOID Context,
    ULONG DataType,
    PVOID Buffer,
    ULONG Offset,
    ULONG Length
);
typedef GET_SET_DEVICE_DATA* PGET_SET_DEVICE_DATA;


typedef 
LOUSTATUS
GET_UPDATED_BUS_RESOURCE(
    PVOID               Context,
    PCM_RESOURCE_LIST*  UpdatedResourceList,
    PCM_RESOURCE_LIST*  UpdatedTranslatedResourceList
);
typedef GET_UPDATED_BUS_RESOURCE* PGET_UPDATED_BUS_RESOURCE;

typedef void* PLOG_FILE_OBJECT;
typedef PLOG_FILE_OBJECT* PPLOG_FILE_OBJECT;

typedef enum _POOL_TYPE{
    NonPagedPool                            = 0,
    NonPagedPoolExecute                     = NonPagedPool,
    PagedPool,
    NonPagedPoolMustSucceed                 = NonPagedPool + 2,
    DontUseThisType,
    NonPagedPoolCacheAligned                = NonPagedPool + 4,
    PagedPoolCacheAligned,
    NonPagedPoolCacheAlignedMustS           = NonPagedPool + 6,
    MaxPoolType,
    NonPagedPoolBase                        = 0,
    NonPagedPoolBaseMustSucceed             = NonPagedPoolBase + 2,
    NonPagedPoolBaseCacheAligned            = NonPagedPoolBase + 4,
    NonPagedPoolBaseCacheAlignedMustS       = NonPagedPoolBase + 6,
    NonPagedPoolSession                     = 32,
    PagedPoolSession                        = NonPagedPoolSession + 1,
    NonPagedPoolMustSucceedSession          = PagedPoolSession + 1,
    DontUseThisTypeSession                  = NonPagedPoolMustSucceedSession + 1,
    NonPagedPoolCacheAlignedSession         = DontUseThisTypeSession + 1,
    PagedPoolCacheAlignedSession            = NonPagedPoolCacheAlignedSession + 1,
    NonPagedPoolCacheAlignedMustSSession    = PagedPoolCacheAlignedSession + 1,
    NonPagedPoolNx                          = 512,
    NonPagedPoolNxCacheAligned              = NonPagedPoolNx + 4,
    NonPagedPoolSessionNx                   = NonPagedPoolNx + 32,
}POOL_TYPE, * PPOOL_TYPE;

typedef 
PVOID 
ALLOCATE_FUNCTION(
    POOL_TYPE   PoolType,
    SIZE        NumberOfBytes,
    ULONG       Tag
);
typedef ALLOCATE_FUNCTION* PALLOCATE_FUNCTION;

typedef 
void 
FREE_FUNCTION(
    PVOID Buffer
);
typedef FREE_FUNCTION* PFREE_FUNCTION;

typedef 
LOUSTATUS
EX_CALLBACK_FUNCTION(
    PVOID   CallbackContext,
    PVOID   Argument1,
    PVOID   Argument2
);
typedef EX_CALLBACK_FUNCTION* PEX_CALLBACK_FUNCTION;

typedef 
void
SET_D3COLD_SUPPORT(
    PVOID   Context,
    BOOLEAN D3ColdSupport
);
typedef SET_D3COLD_SUPPORT* PSET_D3COLD_SUPPORT;

typedef 
void 
D3COLD_REQUEST_CORE_POWER_RAIL(
    PVOID Context,
    BOOLEAN CorePowerRailNeeded
);
typedef D3COLD_REQUEST_CORE_POWER_RAIL* PD3COLD_REQUEST_CORE_POWER_RAIL;

typedef 
LOUSTATUS 
D3COLD_REQUEST_AUX_POWER(
    PVOID   Context,
    ULONG   AuxPortInMilliWats,
    PULONG  RetryInSeconds
);
typedef D3COLD_REQUEST_AUX_POWER* PD3COLD_REQUEST_AUX_POWER;

typedef 
LOUSTATUS 
D3COLD_REQUEST_PERST_DELAY(
    PVOID   Context,
    ULONG   DelayInMicroSeconds
);
typedef D3COLD_REQUEST_PERST_DELAY* PD3COLD_REQUEST_PERST_DELAY;

typedef enum _DEVICE_WAKE_DEPTH{
    DeviceWakeDepthNotWakeable = 0,
    DeviceWakeDepthD0,
    DeviceWakeDepthD1,
    DeviceWakeDepthD2,
    DeviceWakeDepthD3hot,
    DeviceWakeDepthD3cold,
    DeviceWakeDepthMaximum
}DEVICE_WAKE_DEPTH, * PDEVICE_WAKE_DEPTH;

typedef 
LOUSTATUS 
GET_IDLE_WAKE_INFO(
    PVOID               Context,
    SYSTEM_POWER_STATE  SystemPowerState,
    PDEVICE_WAKE_DEPTH  DeepestWakeDepth
);
typedef GET_IDLE_WAKE_INFO* PGET_IDLE_WAKE_INFO;

typedef 
LOUSTATUS 
GET_D3COLD_CAPABILITY(
    PVOID       Context,
    PBOOLEAN    D3ColdSupported
);
typedef GET_D3COLD_CAPABILITY* PGET_D3COLD_CAPABILITY;

typedef enum _D3COLD_LAST_TRANSITION_STATUS{
    LastDStateTransitionStatusUnknown = 0,
    LastDStateTransitionD3hot,
    LastDStateTransitionD3cold
}D3COLD_LAST_TRANSITION_STATUS, * PD3COLD_LAST_TRANSITION_STATUS;

typedef 
void 
GET_D3COLD_LAST_TRANSITION_STATUS(
    PVOID                           Context,
    PD3COLD_LAST_TRANSITION_STATUS  LastTransitionStatus
);
typedef GET_D3COLD_LAST_TRANSITION_STATUS* PGET_D3COLD_LAST_TRANSITION_STATUS;

typedef enum _FAULT_INFORMATION_ARCH{
    FaultInformationInvalid,
    FaultInformationArm64,
    FaultInformationX64
}FAULT_INFORMATION_ARCH, * PFAULT_INFORMATION_ARCH;

typedef enum _FAULT_INFORMATION_ARM64_TYPE{
    UnsupportedUpstreamTransaction = 0,
    AddressSizeFault,
    TlbMatchConflict,
    ExternalFault,
    PermissionFault,
    AccessFlagFault,
    TranslationFault,
    MaxFaultType
}FAULT_INFORMATION_ARM64_TYPE, * PFAULT_INFORMATION_ARM64_TYPE, 
    FAULT_INFORMATION_X64_TYPE, * PFAULT_INFORMATION_X64_TYPE;

typedef struct _FAULT_INFORMATION_ARM64_FLAGS{
    ULONG   WriteNotRead        :   1;
    ULONG   InstructionNotData  :   1;
    ULONG   Privaledged         :   1;
    ULONG   FaultAddressValid   :   1;
    ULONG   Reserved            :   28;
}FAULT_INFORMATION_ARM64_FLAGS, * PFAULT_INFORMATION_ARM64_FLAGS,
    FAULT_INFORMATION_X64_FLAGS, * PFAULT_INFORMATION_X64_FLAGS;

typedef struct _FAULT_INFORMATION_ARM64{
    PVOID                           DomainHandle;
    PVOID                           FaultAddress;
    PDEVICE_OBJECT                  DeviceObject;
    FAULT_INFORMATION_ARM64_FLAGS   Flags;
    FAULT_INFORMATION_ARM64_TYPE    Type;
    ULONG64                         IommuBaseAddress;
}FAULT_INFORMATION_ARM64, * PFAULT_INFORMATION_ARM64;

typedef struct _FAULT_INFORMATION_X64{
    PVOID                           DomainHandle;
    PVOID                           FaultAddress;
    PDEVICE_OBJECT                  DeviceObject;
    FAULT_INFORMATION_X64_FLAGS     Flags;
    FAULT_INFORMATION_X64_TYPE      Type;
    ULONG64                         IommuBaseAddress;
}FAULT_INFORMATION_X64, * PFAULT_INFORMATION_X64;

typedef struct _FAULT_INFORMATION{
    FAULT_INFORMATION_ARCH          Type;
    BOOLEAN                         Stage1;
    union{
        FAULT_INFORMATION_ARM64     Arm64;
        FAULT_INFORMATION_X64       X64;
    };
}FAULT_INFORMATION, * PFAULT_INFORMATION;

typedef 
void 
IOMMU_DEVICE_FAULT_HANDLER(
    PVOID               Context,
    PFAULT_INFORMATION  FaultInfo
);
typedef IOMMU_DEVICE_FAULT_HANDLER* PIOMMU_DEVICE_FAULT_HANDLER;

typedef enum _DEVICE_RESET_TYPE{
    FunctionLevelDeviceReset = 0,
    PlatformLevelDeviceReset,
}DEVICE_RESET_TYPE, * PDEVICE_RESET_TYPE;

typedef 
LOUSTATUS 
DEVICE_RESET_HANDLER(
    PVOID               InterfaceContext,
    DEVICE_RESET_TYPE   ResetType,
    ULONG               Flags,
    PVOID               ResetParameters
);
typedef DEVICE_RESET_HANDLER* PDEVICE_RESET_HANDLER;

typedef union _BUS_SPECIFIC_RESET_FLAGS{
    struct {
        ULONGLONG KeepStackReset    : 1;
        ULONGLONG Reserved          : 63;
    };
    ULONGLONG AsULONGLONG;
}BUS_SPECIFIC_RESET_FLAGS, * PBUS_SPECIFIC_RESET_FLAGS;

typedef union _DEVICE_BUS_SPECIFIC_RESET_TYPE{
    struct {
        ULONGLONG FunctionLevelDeviceReset : 1;
        ULONGLONG PlatformLevelDeviceReset : 1;
        ULONGLONG SecondaryBusReset : 1;
        ULONGLONG Reserved : 61;
    } Pci;
    struct {
        ULONGLONG FunctionLevelDeviceReset : 1;
        ULONGLONG PlatformLevelDeviceReset : 1;
        ULONGLONG Reserved : 62;
    } Acpi;
    ULONGLONG AsULONGLONG;
}DEVICE_BUS_SPECIFIC_RESET_TYPE, * PDEVICE_BUS_SPECIFIC_RESET_TYPE;

typedef struct _DEVICE_BUS_SPECIFIC_RESET_INFO{
    GUID                           BusTypeGuid;
    DEVICE_BUS_SPECIFIC_RESET_TYPE ResetTypeSupported;
}DEVICE_BUS_SPECIFIC_RESET_INFO, * PDEVICE_BUS_SPECIFIC_RESET_INFO;

typedef 
LOUSTATUS 
DEVICE_QUERY_BUS_SPECIFIC_RESET_HANDLER(
    PVOID                               InterfaceContext,
    PULONG                              ResetInfoCount,
    PDEVICE_BUS_SPECIFIC_RESET_INFO     ResetInfoSupported
);
typedef DEVICE_QUERY_BUS_SPECIFIC_RESET_HANDLER* PDEVICE_QUERY_BUS_SPECIFIC_RESET_HANDLER;

typedef 
LOUSTATUS 
DEVICE_BUS_SPECIFIC_RESET_HANDLER(
    PVOID                               InterfaceContext,
    PCGUID                              ButType,
    DEVICE_BUS_SPECIFIC_RESET_TYPE      ResetTypeSelected,
    PBUS_SPECIFIC_RESET_FLAGS           Flags,
    PVOID                               ResetParameters
);
typedef DEVICE_BUS_SPECIFIC_RESET_HANDLER* PDEVICE_BUS_SPECIFIC_RESET_HANDLER;


typedef union _DEVICE_RESET_STATUS_FLAGS{
  struct{
    ULONGLONG   KeepStackReset          : 1;
    ULONGLONG   RecoveringFromBusError  : 1;
    ULONGLONG   Reserved                : 62;
  };
  ULONGLONG     AsUlonglong;
}DEVICE_RESET_STATUS_FLAGS, * PDEVICE_RESET_STATUS_FLAGS;

typedef
LOUSTATUS
GET_DEVICE_RESET_STATUS(
    PVOID                           InterfaceContext,
    PBOOLEAN                        Resetting,
    PDEVICE_BUS_SPECIFIC_RESET_TYPE ResetTypeSelected,
    PDEVICE_RESET_STATUS_FLAGS      Flags
); 
typedef GET_DEVICE_RESET_STATUS* PGET_DEVICE_RESET_STATUS;

typedef HANDLE REGHANDLE;

typedef enum _EVENT_INFO_CLASS{
    EventProviderBinaryTrackInfo = 0,
    EventProviderSetReserved1,
    EventProviderSetTraits,
    EventProviderUseDescriptorType,
    MaxEventInfo,
}EVENT_INFO_CLASS, * PEVENT_INFO_CLASS;

typedef PVOID PFAST_MUTEX;
typedef PVOID PERESOURCE;
typedef PVOID PEX_RUNDOWN_REF;
typedef PVOID PEX_SPIN_LOCK;
typedef PVOID PEX_RUNDOWN_REF_CACHE_AWARE;
typedef PVOID PLOOKASIDE_LIST_EX;
typedef PVOID PNPAGED_LOOKASIDE_LIST;
typedef PVOID PPAGED_LOOKASIDE_LIST;

typedef ULONG64 POOL_FLAGS;

#define POOL_FLAG_REQUIRED_START          0x0000000000000001ULL
#define POOL_FLAG_USE_QUOTA               0x0000000000000001ULL
#define POOL_FLAG_UNINITIALIZED           0x0000000000000002ULL
#define POOL_FLAG_SESSION                 0x0000000000000004ULL
#define POOL_FLAG_CACHE_ALIGNED           0x0000000000000008ULL
#define POOL_FLAG_RESERVED1               0x0000000000000010ULL
#define POOL_FLAG_RAISE_ON_FAILURE        0x0000000000000020ULL
#define POOL_FLAG_NON_PAGED               0x0000000000000040ULL
#define POOL_FLAG_NON_PAGED_EXECUTE       0x0000000000000080ULL
#define POOL_FLAG_PAGED                   0x0000000000000100ULL
#define POOL_FLAG_RESERVED2               0x0000000000000200ULL
#define POOL_FLAG_RESERVED3               0x0000000000000400ULL
#define POOL_FLAG_REQUIRED_END            0x0000000080000000ULL
#define POOL_FLAG_OPTIONAL_START          0x0000000100000000ULL
#define POOL_FLAG_SPECIAL_POOL            0x0000000100000000ULL
#define POOL_FLAG_OPTIONAL_END            0x8000000000000000ULL

typedef enum _EX_POOL_PRIORITY{
    LowPoolPriority = 0,
    LowPoolPrioritySpecialPoolOverrun = 8,
    LowPoolPrioritySpecialPoolUnderrun = 9,
    NormalPoolPriority = 16,
    NormalPoolPrioritySpecialPoolOverrun = 24,
    NormalPoolPrioritySpecialPoolUnderrun = 25,
    HighPoolPriority = 32,
    HighPoolPrioritySpecialPoolOverrun = 40,
    HighPoolPrioritySpecialPoolUnderrun = 41
}EX_POOL_PRIORITY, * PEX_POOL_PRIORITY;

#define POOL_EXTENDED_PARAMETER_TYPE_BITS           3
#define POOL_EXTENDED_PARAMETER_REQUIRED_FIELD_BITS 1
#define POOL_EXTENDED_PARAMETER_RESERVED_BITS       60

typedef struct _POOL_EXTENDED_PARAMS_SECURE_POOL{
  HANDLE    SecurePoolHandle;
  PVOID     Buffer;
  ULONG_PTR Cookie;
  ULONG     SecurePoolFlags;
}POOL_EXTENDED_PARAMS_SECURE_POOL, * PPOOL_EXTENDED_PARAMS_SECURE_POOL;

typedef ULONG POOL_NODE_REQUIREMENT;

typedef struct _POOL_EXTENDED_PARAMETER{
    struct {
        ULONG64                             Type        :  POOL_EXTENDED_PARAMETER_TYPE_BITS;
        ULONG64                             Optional    :  POOL_EXTENDED_PARAMETER_REQUIRED_FIELD_BITS;
        ULONG64                             Reserved    :  POOL_EXTENDED_PARAMETER_RESERVED_BITS;
    };
    union{
        ULONG64                             Reserved2;
        PVOID                               Reserved3;
        EX_POOL_PRIORITY                    Priority;
        POOL_EXTENDED_PARAMS_SECURE_POOL*   SecurePoolParams;
        POOL_NODE_REQUIREMENT               PreferredNode;
    };
}POOL_EXTENDED_PARAMETER, * PPOOL_EXTENDED_PARAMETER;

typedef const POOL_EXTENDED_PARAMETER CPOOL_EXTENDED_PARAMETER, * PCPOOL_EXTENDED_PARAMETER;

typedef PVOID PEX_TIMER;

typedef struct _PCW_COUNTER_INFORMATION{
    ULONG64             CounterMask;
    PCUNICODE_STRING    InstanceMask;
}PCW_COUNTER_INFORMATION, * PPCW_COUNTER_INFORMATION;

typedef PVOID PCW_BUFFER, * PPCW_BUFFER;

typedef struct _PCW_MASK_INFORMATION{
    ULONG64           CounterMask;
    PCUNICODE_STRING  InstanceMask;
    ULONG             InstanceId;
    BOOLEAN           CollectMultiple;
    PPCW_BUFFER       Buffer;
    PKEVENT           CancelEvent;
}PCW_MASK_INFORMATION, * PPCW_MASK_INFORMATION;

typedef union _PCW_CALLBACK_INFORMATION{
    PCW_COUNTER_INFORMATION   AddCounter;
    PCW_COUNTER_INFORMATION   RemoveCounter;
    PCW_MASK_INFORMATION      EnumerateInstances;
    PCW_MASK_INFORMATION      CollectData;
}PCW_CALLBACK_INFORMATION, * PPCW_CALLBACK_INFORMATION;

typedef enum _PCW_CALLBACK_TYPE{
    PcwCallbackAddCounter = 0,
    PcwCallbackRemoveCounter,
    PcwCallbackEnumerateInstances,
    PcwCallbackCollectData
}PCW_CALLBACK_TYPE, * PPCW_CALLBACK_TYPE;

typedef 
LOUSTATUS 
EXT_CALLBACK(
    PCW_CALLBACK_TYPE           Type,
    PPCW_CALLBACK_INFORMATION   Info,
    PVOID                       Context
);
typedef EXT_CALLBACK* PEXT_CALLBACK;

typedef OPAQUE_PTR PEXT_CANCEL_PARAMETERS;
typedef OPAQUE_PTR PCALLBACK_OBJECT;
typedef HANDLE TRACEHANDLE;
typedef OPAQUE_PTR PAFFINITY_TOKEN;
typedef OPAQUE_PTR PRKSEMAPHORE;
typedef OPAQUE_PTR PKTIMER;
typedef OPAQUE_PTR PKTRIAGE_DUMP_DATA_ARRAY;
typedef OPAQUE_PTR PKGUARDED_MUTEX;
typedef OPAQUE_PTR PPFN_NUMBER;
typedef PVOID PVOID64;
typedef KIRQL* PKIRQL;
typedef HANDLE PKLOCK_QUEUE_HANDLE;
typedef OPAQUE_PTR PUOW;
typedef OPAQUE_PTR PRKTM;
typedef OPAQUE_PTR PKTM;
typedef OPAQUE_PTR DEVPROPTYPE, * PDEVPROPTYPE;
typedef OPAQUE_PTR ERESOURCE_THREAD;
typedef OPAQUE_PTR PXSTATE_SAVE;
typedef OPAQUE_PTR PKFLOATING_SAVE;
typedef OPAQUE_PTR PKRESOURCEMANAGER;
typedef OPAQUE_PTR PRKRESOURCEMANAGER;
typedef OPAQUE_PTR PKTRANSACTION;
typedef OPAQUE_PTR PKENLISTMENT;
typedef OPAQUE_PTR POBJECT_TYPE;
typedef OPAQUE_PTR _IORING_OBJECT;
typedef OPAQUE_PTR PIO_CSQ;
typedef OPAQUE_PTR PPOWER_SEQUENCE;
typedef OPAQUE_PTR PIO_CSQ_IRP_CONTEXT;
typedef OPAQUE_PTR PIO_WORKITEM;
typedef OPAQUE_PTR PSHARE_ACCESS;


typedef enum _OB_OPERATION{
    CreateHandle = 0,
    DuplicateHandle,
}OB_OPERATION, * POB_OPERATION;

typedef enum _DIRECTORY_NOTIFY_INFORMATION_CLASS{
    DirectoryNotifyInformation = 0,
    DirectoryNotifyExtendedInformation,
    DirectoryNotifyFullInformation,
    DirectoryNotifyMaximumInformation,
}DIRECTORY_NOTIFY_INFORMATION_CLASS, * PDIRECTORY_NOTIFY_INFORMATION_CLASS;

typedef struct _OBJECT_HANDLE_INFORMATION{
    ULONG       HandleAttributes;
    ACCESS_MASK GrantedAccess;
}OBJECT_HANDLE_INFORMATION, * POBJECT_HANDLE_INFORMATION;

typedef 
LOUSTATUS
RTL_QUERY_REGISTRY_ROUTINE(
    PWSTR   ValueName,
    ULONG   ValueType,
    PVOID   ValueData,
    ULONG   ValueLength,
    PVOID   Context,
    PVOID   EntryContext
);
typedef RTL_QUERY_REGISTRY_ROUTINE* PRTL_QUERY_REGISTRY_ROUTINE;

typedef struct _RTL_QUERY_REGISTRY_TABLE{
    PRTL_QUERY_REGISTRY_ROUTINE QueryRoutine;
    ULONG                       Flags;
    PWSTR                       Name;
    PVOID                       EntryContext;
    ULONG                       DefaultType;
    PVOID                       DefaultData;
    ULONG                       DefaultLength;
}RTL_QUERY_REGISTRY_TABLE, * PRTL_QUERY_REGISTRY_TABLE;

typedef enum _MM_SYSTEMSIZE {
    MmSmallSystem = 0,
    MmMediumSystem,
    MmLargeSystem,
    MmMaximumSystemSize,
}MM_SYSTEMSIZE, * PMM_SYSTEMSIZE;

typedef PGUID REFGUID;

typedef 
LOUSTATUS 
TM_RM_NOTIFICATION(
    PVOID   EnlistmentObject,
    PVOID   RMContext,
    PVOID   TransactionContext,
    ULONG   TransactionNotification,
    PVOID   Argument,
    ULONG   ArgumentLength
);
typedef TM_RM_NOTIFICATION* PTM_RM_NOTIFICATION;

typedef struct _SECTION_OBJECT_POINTERS{
    PVOID     DataSectionObject;
    PVOID     SharedCacheMap;
    PVOID     ImageSectionObject;
}SECTION_OBJECT_POINTERS, * PSECTION_OBJECT_POINTERS;

typedef struct _DEVPROPKEY{
    GUID    Fmtid;
    ULONG   Pid;
}DEVPROPKEY, * PDEVPROPKEY;;

typedef STRING UTF8_STRING, * PUTF8_STRING;

typedef enum _TRANSACTIONMANAGER_INFORMATION_CLASS{
    TransactionManagerBasicInformation = 0,
    TransactionManagerLogInformation,
    TransactionManagerLogPathInformation,
    TransactionManagerRecoveryInformation,
    TransactionManagerOnlineProbeInformation
}TRANSACTIONMANAGER_INFORMATION_CLASS, * PTRANSACTIONMANAGER_INFORMATION_CLASS;

typedef struct _SECURITY_SUBJECT_CONTEXT{
    PACCESS_TOKEN                ClientToken;
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
    PACCESS_TOKEN                PrimaryToken;
    PVOID                        ProcessAuditId;
}SECURITY_SUBJECT_CONTEXT, * PSECURITY_SUBJECT_CONTEXT;

typedef PRIVILEGE_SET INITIAL_PRIVILEGE_SET;

typedef struct _ACCESS_STATE{
    LUID                        OperationID;
    BOOLEAN                     SecurityEvaluated;
    BOOLEAN                     GenerateAudit;
    BOOLEAN                     GenerateOnClose;
    BOOLEAN                     PrivilegesAllocated;
    ULONG                       Flags;
    ACCESS_MASK                 RemainingDesiredAccess;
    ACCESS_MASK                 PreviouslyGrantedAccess;
    ACCESS_MASK                 OriginalDesiredAccess;
    SECURITY_SUBJECT_CONTEXT    SubjectSecurityContext;
    PSECURITY_DESCRIPTOR        SecurityDescriptor;
    PVOID                       AuxData;
    union {
        INITIAL_PRIVILEGE_SET   InitialPrivilegeSet;
        PRIVILEGE_SET           PrivilegeSet;
    }                           Privileges;
    BOOLEAN                     AuditPrivileges;
    UNICODE_STRING              ObjectName;
    UNICODE_STRING              ObjectTypeName;
}ACCESS_STATE, * PACCESS_STATE;

typedef 
ULONG_PTR 
KIPI_BROADCAST_WORKER(
    ULONG_PTR   Arg
);
typedef KIPI_BROADCAST_WORKER* PKIPI_BROADCAST_WORKER;

typedef 
LOUSTATUS 
FPGA_CONTROL_LINK(
    PVOID       Context,
    BOOLEAN     Enable
);
typedef FPGA_CONTROL_LINK* PFPGA_CONTROL_LINK;

typedef USHORT RTL_ATOM;
typedef RTL_ATOM* PRTL_ATOM;

#include <Ldm/Clfs.h>

#include <Hal.h>

#include <Ldm/PepFramework.h>

#include <Ldm/Lmilib.h>

typedef struct _TOKEN_PRIVALEDGES{
    DWORD               PrivaledgeCount;
    LUID_AND_ATTRIBUTES Priviledges[];
}TOKEN_PRIVALEDGES, * PTOKEN_PRIVALEDGES;


#ifdef __cplusplus
}
#endif
#endif