#ifndef WDM_H
#define WDM_H

#include "irp.h"
#include "ntoapi.h"
#include <NtAPI.h>

#define CONNECT_FULLY_SPECIFIED 1
#define CONNECT_LINE_BASED 2
#define CONNECT_MESSAGE_BASED 3


typedef enum _IO_NOTIFICATION_EVENT_CATEGORY {
    EventCategoryReserved,
    EventCategoryHardwareProfileChange,
    EventCategoryDeviceInterfaceChange,
    EventCategoryTargetDeviceChange,
    EventCategoryKernelSoftRestart
} IO_NOTIFICATION_EVENT_CATEGORY;

typedef enum _POOL_TYPE {
    NonPagedPool,
    NonPagedPoolExecute = NonPagedPool,
    PagedPool,
    NonPagedPoolMustSucceed = NonPagedPool + 2,
    DontUseThisType,
    NonPagedPoolCacheAligned = NonPagedPool + 4,
    PagedPoolCacheAligned,
    NonPagedPoolCacheAlignedMustS = NonPagedPool + 6,
    MaxPoolType,
    NonPagedPoolBase = 0,
    NonPagedPoolBaseMustSucceed = NonPagedPoolBase + 2,
    NonPagedPoolBaseCacheAligned = NonPagedPoolBase + 4,
    NonPagedPoolBaseCacheAlignedMustS = NonPagedPoolBase + 6,
    NonPagedPoolSession = 32,
    PagedPoolSession = NonPagedPoolSession + 1,
    NonPagedPoolMustSucceedSession = PagedPoolSession + 1,
    DontUseThisTypeSession = NonPagedPoolMustSucceedSession + 1,
    NonPagedPoolCacheAlignedSession = DontUseThisTypeSession + 1,
    PagedPoolCacheAlignedSession = NonPagedPoolCacheAlignedSession + 1,
    NonPagedPoolCacheAlignedMustSSession = PagedPoolCacheAlignedSession + 1,
    NonPagedPoolNx = 512,
    NonPagedPoolNxCacheAligned = NonPagedPoolNx + 4,
    NonPagedPoolSessionNx = NonPagedPoolNx + 32,

} POOL_TYPE;


typedef enum _IOMMU_MAP_PHYSICAL_ADDRESS_TYPE {
  MapPhysicalAddressTypeMdl,
  MapPhysicalAddressTypeContiguousRange,
  MapPhysicalAddressTypePfn,
  MapPhysicalAddressTypeMax
} IOMMU_MAP_PHYSICAL_ADDRESS_TYPE, *PIOMMU_MAP_PHYSICAL_ADDRESS_TYPE;

typedef struct _IOMMU_DMA_LOGICAL_ADDRESS_TOKEN {
    IOMMU_DMA_LOGICAL_ADDRESS LogicalAddressBase;
    SIZE_T                    Size;
} IOMMU_DMA_LOGICAL_ADDRESS_TOKEN, * PIOMMU_DMA_LOGICAL_ADDRESS_TOKEN;

typedef enum _KEY_SET_INFORMATION_CLASS {
    KeyWriteTimeInformation,
    KeyWow64FlagsInformation,
    KeyControlFlagsInformation,
    KeySetVirtualizationInformation,
    KeySetDebugInformation,
    KeySetHandleTagsInformation,
    KeySetLayerInformation,
    MaxKeySetInfoClass
} KEY_SET_INFORMATION_CLASS;

//bitflag enum
typedef enum _EX_POOL_PRIORITY {
    LowPoolPriority,
    LowPoolPrioritySpecialPoolOverrun = 8,
    LowPoolPrioritySpecialPoolUnderrun = 9,
    NormalPoolPriority = 16,
    NormalPoolPrioritySpecialPoolOverrun = 24,
    NormalPoolPrioritySpecialPoolUnderrun = 25,
    HighPoolPriority = 32,
    HighPoolPrioritySpecialPoolOverrun = 40,
    HighPoolPrioritySpecialPoolUnderrun = 41
} EX_POOL_PRIORITY;

typedef enum _KEY_VALUE_INFORMATION_CLASS {
    KeyValueBasicInformation,
    KeyValueFullInformation,
    KeyValuePartialInformation,
    KeyValueFullInformationAlign64,
    KeyValuePartialInformationAlign64,
    KeyValueLayerInformation,
    MaxKeyValueInfoClass
} KEY_VALUE_INFORMATION_CLASS;


typedef enum _IO_PAGING_PRIORITY {
    IoPagingPriorityInvalid,
    IoPagingPriorityNormal,
    IoPagingPriorityHigh,
    IoPagingPriorityReserved1,
    IoPagingPriorityReserved2
} IO_PAGING_PRIORITY;

typedef enum _IO_PRIORITY_HINT {
    IoPriorityVeryLow,
    IoPriorityLow,
    IoPriorityNormal,
    IoPriorityHigh,
    IoPriorityCritical,
    MaxIoPriorityTypes
} IO_PRIORITY_HINT;
typedef struct _XSAVE_CET_U_FORMAT {
    ULONG64 Ia32CetUMsr;
    ULONG64 Ia32Pl3SspMsr;
} XSAVE_CET_U_FORMAT, * PXSAVE_CET_U_FORMAT;

typedef enum _KEY_INFORMATION_CLASS {
    KeyBasicInformation,
    KeyNodeInformation,
    KeyFullInformation,
    KeyNameInformation,
    KeyCachedInformation,
    KeyFlagsInformation,
    KeyVirtualizationInformation,
    KeyHandleTagsInformation,
    KeyTrustInformation,
    KeyLayerInformation,
    MaxKeyInfoClass
} KEY_INFORMATION_CLASS;


typedef enum _WORK_QUEUE_TYPE {
    CriticalWorkQueue,
    DelayedWorkQueue,
    HyperCriticalWorkQueue,
    NormalWorkQueue,
    BackgroundWorkQueue,
    RealTimeWorkQueue,
    SuperCriticalWorkQueue,
    MaximumWorkQueue,
    CustomPriorityWorkQueue
} WORK_QUEUE_TYPE;
typedef enum _TRACE_INFORMATION_CLASS {
    TraceIdClass,
    TraceHandleClass,
    TraceEnableFlagsClass,
    TraceEnableLevelClass,
    GlobalLoggerHandleClass,
    EventLoggerHandleClass,
    AllLoggerHandlesClass,
    TraceHandleByNameClass,
    LoggerEventsLostClass,
    TraceSessionSettingsClass,
    LoggerEventsLoggedClass,
    DiskIoNotifyRoutinesClass,
    TraceInformationClassReserved1,
    FltIoNotifyRoutinesClass,
    TraceInformationClassReserved2,
    WdfNotifyRoutinesClass,
    MaxTraceInformationClass
} TRACE_INFORMATION_CLASS;

typedef enum _IOMMU_DMA_LOGICAL_ALLOCATOR_TYPE {
    IommuDmaLogicalAllocatorNone,
    IommuDmaLogicalAllocatorBuddy,
    IommuDmaLogicalAllocatorMax
} IOMMU_DMA_LOGICAL_ALLOCATOR_TYPE, * PIOMMU_DMA_LOGICAL_ALLOCATOR_TYPE;


typedef struct _TRANSACTION_BASIC_INFORMATION {
    GUID  TransactionId;
    ULONG State;
    ULONG Outcome;
} TRANSACTION_BASIC_INFORMATION, * PTRANSACTION_BASIC_INFORMATION;

typedef struct _TRANSACTION_ENLISTMENT_PAIR {
    GUID EnlistmentId;
    GUID ResourceManagerId;
} TRANSACTION_ENLISTMENT_PAIR, * PTRANSACTION_ENLISTMENT_PAIR;

typedef struct _TRANSACTION_ENLISTMENTS_INFORMATION {
    ULONG                       NumberOfEnlistments;
    TRANSACTION_ENLISTMENT_PAIR EnlistmentPair[1];
} TRANSACTION_ENLISTMENTS_INFORMATION, * PTRANSACTION_ENLISTMENTS_INFORMATION;

typedef enum _TRANSACTION_INFORMATION_CLASS {
    TransactionBasicInformation,
    TransactionPropertiesInformation,
    TransactionEnlistmentInformation,
    TransactionSuperiorEnlistmentInformation
} TRANSACTION_INFORMATION_CLASS;

typedef enum _TRANSACTION_OUTCOME {
    TransactionOutcomeUndetermined,
    TransactionOutcomeCommitted,
    TransactionOutcomeAborted
} TRANSACTION_OUTCOME;

typedef struct _TRANSACTION_PROPERTIES_INFORMATION {
    ULONG         IsolationLevel;
    ULONG         IsolationFlags;
    LARGE_INTEGER Timeout;
    ULONG         Outcome;
    ULONG         DescriptionLength;
    WCHAR         Description[1];
} TRANSACTION_PROPERTIES_INFORMATION, * PTRANSACTION_PROPERTIES_INFORMATION;

typedef struct _KEY_VALUE_ENTRY {
    PUNICODE_STRING ValueName;
    ULONG           DataLength;
    ULONG           DataOffset;
    ULONG           Type;
} KEY_VALUE_ENTRY, * PKEY_VALUE_ENTRY;

typedef struct _RESOURCEMANAGER_BASIC_INFORMATION {
    GUID  ResourceManagerId;
    ULONG DescriptionLength;
    WCHAR Description[1];
} RESOURCEMANAGER_BASIC_INFORMATION, * PRESOURCEMANAGER_BASIC_INFORMATION;

typedef struct _RESOURCEMANAGER_COMPLETION_INFORMATION {
    HANDLE    IoCompletionPortHandle;
    ULONG_PTR CompletionKey;
} RESOURCEMANAGER_COMPLETION_INFORMATION, * PRESOURCEMANAGER_COMPLETION_INFORMATION;

typedef enum _RESOURCEMANAGER_INFORMATION_CLASS {
    ResourceManagerBasicInformation,
    ResourceManagerCompletionInformation
} RESOURCEMANAGER_INFORMATION_CLASS;

typedef struct _SLIST_ENTRY {
    struct _SLIST_ENTRY* Next;
} SLIST_ENTRY, * PSLIST_ENTRY;


typedef struct _SYSTEM_POOL_ZEROING_INFORMATION {
    BOOLEAN PoolZeroingSupportPresent;
} SYSTEM_POOL_ZEROING_INFORMATION, * PSYSTEM_POOL_ZEROING_INFORMATION;


typedef enum {
    PoAc,
    PoDc,
    PoHot,
    PoConditionMaximum
} SYSTEM_POWER_CONDITION;


typedef struct _FILE_OBJECT {
    CSHORT                            Type;
    CSHORT                            Size;
    PDEVICE_OBJECT                    DeviceObject;
    PVPB                              Vpb;
    PVOID                             FsContext;
    PVOID                             FsContext2;
    PSECTION_OBJECT_POINTERS          SectionObjectPointer;
    PVOID                             PrivateCacheMap;
    NTSTATUS                          FinalStatus;
    struct _FILE_OBJECT* RelatedFileObject;
    BOOLEAN                           LockOperation;
    BOOLEAN                           DeletePending;
    BOOLEAN                           ReadAccess;
    BOOLEAN                           WriteAccess;
    BOOLEAN                           DeleteAccess;
    BOOLEAN                           SharedRead;
    BOOLEAN                           SharedWrite;
    BOOLEAN                           SharedDelete;
    ULONG                             Flags;
    UNICODE_STRING                    FileName;
    LARGE_INTEGER                     CurrentByteOffset;
    ULONG                  Waiters;
    ULONG                  Busy;
    PVOID                             LastLock;
    KEVENT                            Lock;
    KEVENT                            Event;
    PIO_COMPLETION_CONTEXT CompletionContext;
    KSPIN_LOCK                        IrpListLock;
    LIST_ENTRY                        IrpList;
    PVOID                  FileObjectExtension;
} FILE_OBJECT, * PFILE_OBJECT;

typedef struct _TARGET_DEVICE_CUSTOM_NOTIFICATION {
    USHORT       Version;
    USHORT       Size;
    GUID         Event;
    PFILE_OBJECT FileObject;
    LONG         NameBufferOffset;
    UCHAR        CustomDataBuffer[1];
} TARGET_DEVICE_CUSTOM_NOTIFICATION, * PTARGET_DEVICE_CUSTOM_NOTIFICATION;

typedef struct _TARGET_DEVICE_REMOVAL_NOTIFICATION {
    USHORT       Version;
    USHORT       Size;
    GUID         Event;
    PFILE_OBJECT FileObject;
} TARGET_DEVICE_REMOVAL_NOTIFICATION, * PTARGET_DEVICE_REMOVAL_NOTIFICATION;


typedef struct _TIME_FIELDS {
    CSHORT Year;
    CSHORT Month;
    CSHORT Day;
    CSHORT Hour;
    CSHORT Minute;
    CSHORT Second;
    CSHORT Milliseconds;
    CSHORT Weekday;
} TIME_FIELDS;

typedef struct {
    ULONG                  Version;
    GUID                   Guid;
    SYSTEM_POWER_CONDITION PowerCondition;
    ULONG                  DataLength;
    UCHAR*                  Data;
} SET_POWER_SETTING_VALUE, * PSET_POWER_SETTING_VALUE;

typedef struct _POOL_CREATE_EXTENDED_PARAMS {
    ULONG Version;
} POOL_CREATE_EXTENDED_PARAMS, * PPOOL_CREATE_EXTENDED_PARAMS;



typedef struct _POOL_EXTENDED_PARAMETER {
    struct {
        ULONG64 Type : POOL_EXTENDED_PARAMETER_TYPE_BITS;
        ULONG64 Optional : POOL_EXTENDED_PARAMETER_REQUIRED_FIELD_BITS;
        ULONG64 Reserved : POOL_EXTENDED_PARAMETER_RESERVED_BITS;
    } DUMMYSTRUCTNAME;
    union {
        ULONG64                          Reserved2;
        PVOID                            Reserved3;
        EX_POOL_PRIORITY                 Priority;
        POOL_EXTENDED_PARAMS_SECURE_POOL* SecurePoolParams;
        POOL_NODE_REQUIREMENT            PreferredNode;
    } DUMMYUNIONNAME;
} POOL_EXTENDED_PARAMETER, * PPOOL_EXTENDED_PARAMETER;

typedef enum POOL_EXTENDED_PARAMETER_TYPE {
    PoolExtendedParameterInvalidType = 0,
    PoolExtendedParameterPriority,
    PoolExtendedParameterSecurePool,
    PoolExtendedParameterNumaNode,
    PoolExtendedParameterMax
}  *PPOOL_EXTENDED_PARAMETER_TYPE;




typedef struct _SCATTER_GATHER_LIST {
    ULONG                  NumberOfElements;
    ULONG_PTR              Reserved;
    SCATTER_GATHER_ELEMENT Elements[];
} SCATTER_GATHER_LIST, * PSCATTER_GATHER_LIST;

typedef struct _SDEV_IDENTIFIER_INTERFACE {
    INTERFACE            InterfaceHeader;
    PGET_SDEV_IDENTIFIER GetIdentifier;
} SDEV_IDENTIFIER_INTERFACE, * PSDEV_IDENTIFIER_INTERFACE;

typedef enum _SE_IMAGE_TYPE {
    SeImageTypeElamDriver,
    SeImageTypeDriver,
    SeImageTypePlatformSecureFile,
    SeImageTypeDynamicCodeFile,
    SeImageTypeMax,
} SE_IMAGE_TYPE, * PSE_IMAGE_TYPE;


typedef struct _SECTION_OBJECT_POINTERS {
    PVOID DataSectionObject;
    PVOID SharedCacheMap;
    PVOID ImageSectionObject;
} SECTION_OBJECT_POINTERS;

typedef struct _REENUMERATE_SELF_INTERFACE_STANDARD {
    USHORT                 Size;
    USHORT                 Version;
    PVOID                  Context;
    PINTERFACE_REFERENCE   InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PREENUMERATE_SELF      SurpriseRemoveAndReenumerateSelf;
} REENUMERATE_SELF_INTERFACE_STANDARD, * PREENUMERATE_SELF_INTERFACE_STANDARD;

typedef struct _REG_CALLBACK_CONTEXT_CLEANUP_INFORMATION {
    PVOID Object;
    PVOID ObjectContext;
    PVOID Reserved;
} REG_CALLBACK_CONTEXT_CLEANUP_INFORMATION, * PREG_CALLBACK_CONTEXT_CLEANUP_INFORMATION;

typedef struct _REG_CREATE_KEY_INFORMATION {
    PUNICODE_STRING CompleteName;
    PVOID           RootObject;
    PVOID           ObjectType;
    ULONG           CreateOptions;
    PUNICODE_STRING Class;
    PVOID           SecurityDescriptor;
    PVOID           SecurityQualityOfService;
    ACCESS_MASK     DesiredAccess;
    ACCESS_MASK     GrantedAccess;
    PULONG          Disposition;
    PVOID* ResultObject;
    PVOID           CallContext;
    PVOID           RootObjectContext;
    PVOID           Transaction;
    PVOID           Reserved;
} REG_CREATE_KEY_INFORMATION, REG_OPEN_KEY_INFORMATION, * PREG_CREATE_KEY_INFORMATION, * PREG_OPEN_KEY_INFORMATION;

typedef struct _REG_CREATE_KEY_INFORMATION_V1 {
    PUNICODE_STRING CompleteName;
    PVOID           RootObject;
    PVOID           ObjectType;
    ULONG           Options;
    PUNICODE_STRING Class;
    PVOID           SecurityDescriptor;
    PVOID           SecurityQualityOfService;
    ACCESS_MASK     DesiredAccess;
    ACCESS_MASK     GrantedAccess;
    PULONG          Disposition;
    PVOID* ResultObject;
    PVOID           CallContext;
    PVOID           RootObjectContext;
    PVOID           Transaction;
    ULONG_PTR       Version;
    PUNICODE_STRING RemainingName;
    ULONG           Wow64Flags;
    ULONG           Attributes;
    KPROCESSOR_MODE CheckAccessMode;
} REG_CREATE_KEY_INFORMATION_V1, REG_OPEN_KEY_INFORMATION_V1, * PREG_CREATE_KEY_INFORMATION_V1, * PREG_OPEN_KEY_INFORMATION_V1;

typedef struct _REG_DELETE_KEY_INFORMATION {
    PVOID Object;
    PVOID CallContext;
    PVOID ObjectContext;
    PVOID Reserved;
} REG_DELETE_KEY_INFORMATION, * PREG_DELETE_KEY_INFORMATION, REG_FLUSH_KEY_INFORMATION, * PREG_FLUSH_KEY_INFORMATION;

typedef struct _REG_DELETE_VALUE_KEY_INFORMATION {
    PVOID           Object;
    PUNICODE_STRING ValueName;
    PVOID           CallContext;
    PVOID           ObjectContext;
    PVOID           Reserved;
} REG_DELETE_VALUE_KEY_INFORMATION, * PREG_DELETE_VALUE_KEY_INFORMATION;

typedef struct _REG_ENUMERATE_KEY_INFORMATION {
    PVOID                 Object;
    ULONG                 Index;
    KEY_INFORMATION_CLASS KeyInformationClass;
    PVOID                 KeyInformation;
    ULONG                 Length;
    PULONG                ResultLength;
    PVOID                 CallContext;
    PVOID                 ObjectContext;
    PVOID                 Reserved;
} REG_ENUMERATE_KEY_INFORMATION, * PREG_ENUMERATE_KEY_INFORMATION;

typedef struct _REG_ENUMERATE_VALUE_KEY_INFORMATION {
    PVOID                       Object;
    ULONG                       Index;
    KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass;
    PVOID                       KeyValueInformation;
    ULONG                       Length;
    PULONG                      ResultLength;
    PVOID                       CallContext;
    PVOID                       ObjectContext;
    PVOID                       Reserved;
} REG_ENUMERATE_VALUE_KEY_INFORMATION, * PREG_ENUMERATE_VALUE_KEY_INFORMATION;

typedef struct _REG_KEY_HANDLE_CLOSE_INFORMATION {
    PVOID Object;
    PVOID CallContext;
    PVOID ObjectContext;
    PVOID Reserved;
} REG_KEY_HANDLE_CLOSE_INFORMATION, * PREG_KEY_HANDLE_CLOSE_INFORMATION;

typedef struct _REG_LOAD_KEY_INFORMATION {
    PVOID           Object;
    PUNICODE_STRING KeyName;
    PUNICODE_STRING SourceFile;
    ULONG           Flags;
    PVOID           TrustClassObject;
    PVOID           UserEvent;
    ACCESS_MASK     DesiredAccess;
    PHANDLE         RootHandle;
    PVOID           CallContext;
    PVOID           ObjectContext;
    PVOID           Reserved;
} REG_LOAD_KEY_INFORMATION, * PREG_LOAD_KEY_INFORMATION;

typedef struct _REG_LOAD_KEY_INFORMATION_V2 {
    PVOID           Object;
    PUNICODE_STRING KeyName;
    PUNICODE_STRING SourceFile;
    ULONG           Flags;
    PVOID           TrustClassObject;
    PVOID           UserEvent;
    ACCESS_MASK     DesiredAccess;
    PHANDLE         RootHandle;
    PVOID           CallContext;
    PVOID           ObjectContext;
    ULONG_PTR       Version;
    PVOID           FileAccessToken;
} REG_LOAD_KEY_INFORMATION_V2, * PREG_LOAD_KEY_INFORMATION_V2;

typedef enum _REG_NOTIFY_CLASS {
    RegNtDeleteKey,
    RegNtPreDeleteKey,
    RegNtSetValueKey,
    RegNtPreSetValueKey,
    RegNtDeleteValueKey,
    RegNtPreDeleteValueKey,
    RegNtSetInformationKey,
    RegNtPreSetInformationKey,
    RegNtRenameKey,
    RegNtPreRenameKey,
    RegNtEnumerateKey,
    RegNtPreEnumerateKey,
    RegNtEnumerateValueKey,
    RegNtPreEnumerateValueKey,
    RegNtQueryKey,
    RegNtPreQueryKey,
    RegNtQueryValueKey,
    RegNtPreQueryValueKey,
    RegNtQueryMultipleValueKey,
    RegNtPreQueryMultipleValueKey,
    RegNtPreCreateKey,
    RegNtPostCreateKey,
    RegNtPreOpenKey,
    RegNtPostOpenKey,
    RegNtKeyHandleClose,
    RegNtPreKeyHandleClose,
    RegNtPostDeleteKey,
    RegNtPostSetValueKey,
    RegNtPostDeleteValueKey,
    RegNtPostSetInformationKey,
    RegNtPostRenameKey,
    RegNtPostEnumerateKey,
    RegNtPostEnumerateValueKey,
    RegNtPostQueryKey,
    RegNtPostQueryValueKey,
    RegNtPostQueryMultipleValueKey,
    RegNtPostKeyHandleClose,
    RegNtPreCreateKeyEx,
    RegNtPostCreateKeyEx,
    RegNtPreOpenKeyEx,
    RegNtPostOpenKeyEx,
    RegNtPreFlushKey,
    RegNtPostFlushKey,
    RegNtPreLoadKey,
    RegNtPostLoadKey,
    RegNtPreUnLoadKey,
    RegNtPostUnLoadKey,
    RegNtPreQueryKeySecurity,
    RegNtPostQueryKeySecurity,
    RegNtPreSetKeySecurity,
    RegNtPostSetKeySecurity,
    RegNtCallbackObjectContextCleanup,
    RegNtPreRestoreKey,
    RegNtPostRestoreKey,
    RegNtPreSaveKey,
    RegNtPostSaveKey,
    RegNtPreReplaceKey,
    RegNtPostReplaceKey,
    RegNtPreQueryKeyName,
    RegNtPostQueryKeyName,
    RegNtPreSaveMergedKey,
    RegNtPostSaveMergedKey,
    MaxRegNtNotifyClass
} REG_NOTIFY_CLASS;

typedef struct _REG_POST_CREATE_KEY_INFORMATION {
    PUNICODE_STRING CompleteName;
    PVOID           Object;
    NTSTATUS        Status;
} REG_POST_CREATE_KEY_INFORMATION, REG_POST_OPEN_KEY_INFORMATION, * PREG_POST_CREATE_KEY_INFORMATION, * PREG_POST_OPEN_KEY_INFORMATION;

typedef struct _REG_POST_OPERATION_INFORMATION {
    PVOID    Object;
    NTSTATUS Status;
    PVOID    PreInformation;
    NTSTATUS ReturnStatus;
    PVOID    CallContext;
    PVOID    ObjectContext;
    PVOID    Reserved;
} REG_POST_OPERATION_INFORMATION, * PREG_POST_OPERATION_INFORMATION;

typedef struct _REG_PRE_CREATE_KEY_INFORMATION {
    PUNICODE_STRING CompleteName;
} REG_PRE_CREATE_KEY_INFORMATION, REG_PRE_OPEN_KEY_INFORMATION, * PREG_PRE_CREATE_KEY_INFORMATION, * PREG_PRE_OPEN_KEY_INFORMATION;

typedef enum {
    LT_DONT_CARE,
    LT_LOWEST_LATENCY
} LATENCY_TIME;

typedef struct _LINK_SHARE_ACCESS {
    ULONG OpenCount;
    ULONG Deleters;
    ULONG SharedDelete;
} LINK_SHARE_ACCESS, * PLINK_SHARE_ACCESS;

typedef struct _MAILSLOT_CREATE_PARAMETERS {
    ULONG         MailslotQuota;
    ULONG         MaximumMessageSize;
    LARGE_INTEGER ReadTimeout;
    BOOLEAN       TimeoutSpecified;
} MAILSLOT_CREATE_PARAMETERS, * PMAILSLOT_CREATE_PARAMETERS;


typedef struct MEM_EXTENDED_PARAMETER {
    struct {
        ULONG64 Type : MEM_EXTENDED_PARAMETER_TYPE_BITS;
        ULONG64 Reserved : 64 - MEM_EXTENDED_PARAMETER_TYPE_BITS;
    } DUMMYSTRUCTNAME;
    union {
        ULONG64 ULong64;
        PVOID   Pointer;
        SIZE_T  Size;
        HANDLE  Handle;
        ULONG   ULong;
    } DUMMYUNIONNAME;
} MEM_EXTENDED_PARAMETER, * PMEM_EXTENDED_PARAMETER;

typedef enum MEM_EXTENDED_PARAMETER_TYPE {
    MemExtendedParameterInvalidType = 0,
    MemExtendedParameterAddressRequirements = 1,
    MemExtendedParameterNumaNode = 2,
    MemExtendedParameterPartitionHandle = 3,
    MemExtendedParameterUserPhysicalHandle = 4,
    MemExtendedParameterAttributeFlags = 5,
    MemExtendedParameterImageMachine = 6,
    MemExtendedParameterMax
}  *PMEM_EXTENDED_PARAMETER_TYPE;


typedef struct _MEMORY_PARTITION_DEDICATED_MEMORY_OPEN_INFORMATION {
    ULONG64     DedicatedMemoryTypeId;
    ULONG       HandleAttributes;
    ACCESS_MASK DesiredAccess;
    HANDLE      DedicatedMemoryPartitionHandle;
} MEMORY_PARTITION_DEDICATED_MEMORY_OPEN_INFORMATION, * PMEMORY_PARTITION_DEDICATED_MEMORY_OPEN_INFORMATION;

typedef struct _MM_PHYSICAL_ADDRESS_LIST {
    PHYSICAL_ADDRESS PhysicalAddress;
    SIZE_T           NumberOfBytes;
} MM_PHYSICAL_ADDRESS_LIST, * PMM_PHYSICAL_ADDRESS_LIST;


typedef struct _REG_QUERY_KEY_INFORMATION {
    PVOID                 Object;
    KEY_INFORMATION_CLASS KeyInformationClass;
    PVOID                 KeyInformation;
    ULONG                 Length;
    PULONG                ResultLength;
    PVOID                 CallContext;
    PVOID                 ObjectContext;
    PVOID                 Reserved;
} REG_QUERY_KEY_INFORMATION, * PREG_QUERY_KEY_INFORMATION;


typedef struct _REG_QUERY_KEY_NAME {
    PVOID                    Object;
    POBJECT_NAME_INFORMATION ObjectNameInfo;
    ULONG                    Length;
    PULONG                   ReturnLength;
    PVOID                    CallContext;
    PVOID                    ObjectContext;
    PVOID                    Reserved;
} REG_QUERY_KEY_NAME, * PREG_QUERY_KEY_NAME;

typedef struct _REG_QUERY_KEY_SECURITY_INFORMATION {
    PVOID                 Object;
    PSECURITY_INFORMATION SecurityInformation;
    PSECURITY_DESCRIPTOR  SecurityDescriptor;
    PULONG                Length;
    PVOID                 CallContext;
    PVOID                 ObjectContext;
    PVOID                 Reserved;
} REG_QUERY_KEY_SECURITY_INFORMATION, * PREG_QUERY_KEY_SECURITY_INFORMATION;

typedef struct _REG_QUERY_MULTIPLE_VALUE_KEY_INFORMATION {
    PVOID            Object;
    PKEY_VALUE_ENTRY ValueEntries;
    ULONG            EntryCount;
    PVOID            ValueBuffer;
    PULONG           BufferLength;
    PULONG           RequiredBufferLength;
    PVOID            CallContext;
    PVOID            ObjectContext;
    PVOID            Reserved;
} REG_QUERY_MULTIPLE_VALUE_KEY_INFORMATION, * PREG_QUERY_MULTIPLE_VALUE_KEY_INFORMATION;

typedef struct _REG_QUERY_VALUE_KEY_INFORMATION {
    PVOID                       Object;
    PUNICODE_STRING             ValueName;
    KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass;
    PVOID                       KeyValueInformation;
    ULONG                       Length;
    PULONG                      ResultLength;
    PVOID                       CallContext;
    PVOID                       ObjectContext;
    PVOID                       Reserved;
} REG_QUERY_VALUE_KEY_INFORMATION, * PREG_QUERY_VALUE_KEY_INFORMATION;

typedef struct _REG_RENAME_KEY_INFORMATION {
    PVOID           Object;
    PUNICODE_STRING NewName;
    PVOID           CallContext;
    PVOID           ObjectContext;
    PVOID           Reserved;
} REG_RENAME_KEY_INFORMATION, * PREG_RENAME_KEY_INFORMATION;

typedef struct _REG_REPLACE_KEY_INFORMATION {
    PVOID           Object;
    PUNICODE_STRING OldFileName;
    PUNICODE_STRING NewFileName;
    PVOID           CallContext;
    PVOID           ObjectContext;
    PVOID           Reserved;
} REG_REPLACE_KEY_INFORMATION, * PREG_REPLACE_KEY_INFORMATION;

typedef struct _REG_RESTORE_KEY_INFORMATION {
    PVOID  Object;
    HANDLE FileHandle;
    ULONG  Flags;
    PVOID  CallContext;
    PVOID  ObjectContext;
    PVOID  Reserved;
} REG_RESTORE_KEY_INFORMATION, * PREG_RESTORE_KEY_INFORMATION;

typedef struct _REG_SAVE_KEY_INFORMATION {
    PVOID  Object;
    HANDLE FileHandle;
    ULONG  Format;
    PVOID  CallContext;
    PVOID  ObjectContext;
    PVOID  Reserved;
} REG_SAVE_KEY_INFORMATION, * PREG_SAVE_KEY_INFORMATION;

typedef struct _REG_SAVE_MERGED_KEY_INFORMATION {
    PVOID  Object;
    HANDLE FileHandle;
    PVOID  HighKeyObject;
    PVOID  LowKeyObject;
    PVOID  CallContext;
    PVOID  ObjectContext;
    PVOID  Reserved;
} REG_SAVE_MERGED_KEY_INFORMATION, * PREG_SAVE_MERGED_KEY_INFORMATION;


typedef struct _REG_SET_INFORMATION_KEY_INFORMATION {
    PVOID                     Object;
    KEY_SET_INFORMATION_CLASS KeySetInformationClass;
    PVOID                     KeySetInformation;
    ULONG                     KeySetInformationLength;
    PVOID                     CallContext;
    PVOID                     ObjectContext;
    PVOID                     Reserved;
} REG_SET_INFORMATION_KEY_INFORMATION, * PREG_SET_INFORMATION_KEY_INFORMATION;

typedef struct _REG_SET_KEY_SECURITY_INFORMATION {
    PVOID                 Object;
    PSECURITY_INFORMATION SecurityInformation;
    PSECURITY_DESCRIPTOR  SecurityDescriptor;
    PVOID                 CallContext;
    PVOID                 ObjectContext;
    PVOID                 Reserved;
} REG_SET_KEY_SECURITY_INFORMATION, * PREG_SET_KEY_SECURITY_INFORMATION;

typedef struct _REG_SET_VALUE_KEY_INFORMATION {
    PVOID           Object;
    PUNICODE_STRING ValueName;
    ULONG           TitleIndex;
    ULONG           Type;
    PVOID           Data;
    ULONG           DataSize;
    PVOID           CallContext;
    PVOID           ObjectContext;
    PVOID           Reserved;
} REG_SET_VALUE_KEY_INFORMATION, * PREG_SET_VALUE_KEY_INFORMATION;


typedef struct _REG_UNLOAD_KEY_INFORMATION {
    PVOID Object;
    PVOID UserEvent;
    PVOID CallContext;
    PVOID ObjectContext;
    PVOID Reserved;
} REG_UNLOAD_KEY_INFORMATION, * PREG_UNLOAD_KEY_INFORMATION;

typedef struct _KEY_BASIC_INFORMATION {
    LARGE_INTEGER LastWriteTime;
    ULONG         TitleIndex;
    ULONG         NameLength;
    WCHAR         Name[1];
} KEY_BASIC_INFORMATION, * PKEY_BASIC_INFORMATION;

typedef struct _KEY_FULL_INFORMATION {
    LARGE_INTEGER LastWriteTime;
    ULONG         TitleIndex;
    ULONG         ClassOffset;
    ULONG         ClassLength;
    ULONG         SubKeys;
    ULONG         MaxNameLen;
    ULONG         MaxClassLen;
    ULONG         Values;
    ULONG         MaxValueNameLen;
    ULONG         MaxValueDataLen;
    WCHAR         Class[1];
} KEY_FULL_INFORMATION, * PKEY_FULL_INFORMATION;


typedef struct _KEY_NODE_INFORMATION {
    LARGE_INTEGER LastWriteTime;
    ULONG         TitleIndex;
    ULONG         ClassOffset;
    ULONG         ClassLength;
    ULONG         NameLength;
    WCHAR         Name[1];
} KEY_NODE_INFORMATION, * PKEY_NODE_INFORMATION;


typedef struct _KEY_VALUE_BASIC_INFORMATION {
    ULONG TitleIndex;
    ULONG Type;
    ULONG NameLength;
    WCHAR Name[1];
} KEY_VALUE_BASIC_INFORMATION, * PKEY_VALUE_BASIC_INFORMATION;



typedef struct _KEY_VALUE_FULL_INFORMATION {
    ULONG TitleIndex;
    ULONG Type;
    ULONG DataOffset;
    ULONG DataLength;
    ULONG NameLength;
    WCHAR Name[1];
} KEY_VALUE_FULL_INFORMATION, * PKEY_VALUE_FULL_INFORMATION;



typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
    ULONG TitleIndex;
    ULONG Type;
    ULONG DataLength;
    UCHAR Data[1];
} KEY_VALUE_PARTIAL_INFORMATION, * PKEY_VALUE_PARTIAL_INFORMATION;

typedef struct _KEY_WRITE_TIME_INFORMATION {
    LARGE_INTEGER LastWriteTime;
} KEY_WRITE_TIME_INFORMATION, * PKEY_WRITE_TIME_INFORMATION;



typedef struct _KMUTANT {
    DISPATCHER_HEADER Header;
    LIST_ENTRY        MutantListEntry;
    struct _KTHREAD* OwnerThread;
    union {
        UCHAR MutantFlags;
        struct {
            UCHAR Abandoned : 1;
            UCHAR Spare1 : 7;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    UCHAR             ApcDisable;
} KMUTANT, * PKMUTANT, * PRKMUTANT, KMUTEX, * PKMUTEX, * PRKMUTEX;

typedef struct _KTMOBJECT_CURSOR {
    GUID  LastQuery;
    ULONG ObjectIdCount;
    GUID  ObjectIds[1];
} KTMOBJECT_CURSOR, * PKTMOBJECT_CURSOR;

typedef enum _KTMOBJECT_TYPE {
    KTMOBJECT_TRANSACTION,
    KTMOBJECT_TRANSACTION_MANAGER,
    KTMOBJECT_RESOURCE_MANAGER,
    KTMOBJECT_ENLISTMENT,
    KTMOBJECT_INVALID
} KTMOBJECT_TYPE, * PKTMOBJECT_TYPE;

typedef struct _OB_OPERATION_REGISTRATION {
    POBJECT_TYPE* ObjectType;
    OB_OPERATION                Operations;
    POB_PRE_OPERATION_CALLBACK  PreOperation;
    POB_POST_OPERATION_CALLBACK PostOperation;
} OB_OPERATION_REGISTRATION, * POB_OPERATION_REGISTRATION;

typedef struct _OB_CALLBACK_REGISTRATION {
    USHORT                    Version;
    USHORT                    OperationRegistrationCount;
    UNICODE_STRING            Altitude;
    PVOID                     RegistrationContext;
    OB_OPERATION_REGISTRATION* OperationRegistration;
} OB_CALLBACK_REGISTRATION, * POB_CALLBACK_REGISTRATION;


typedef struct _OB_POST_CREATE_HANDLE_INFORMATION {
    ACCESS_MASK GrantedAccess;
} OB_POST_CREATE_HANDLE_INFORMATION, * POB_POST_CREATE_HANDLE_INFORMATION;

typedef struct _OB_POST_DUPLICATE_HANDLE_INFORMATION {
    ACCESS_MASK GrantedAccess;
} OB_POST_DUPLICATE_HANDLE_INFORMATION, * POB_POST_DUPLICATE_HANDLE_INFORMATION;

typedef struct _OB_PRE_CREATE_HANDLE_INFORMATION {
    ACCESS_MASK DesiredAccess;
    ACCESS_MASK OriginalDesiredAccess;
} OB_PRE_CREATE_HANDLE_INFORMATION, * POB_PRE_CREATE_HANDLE_INFORMATION;

typedef struct _OB_PRE_DUPLICATE_HANDLE_INFORMATION {
    ACCESS_MASK DesiredAccess;
    ACCESS_MASK OriginalDesiredAccess;
    PVOID       SourceProcess;
    PVOID       TargetProcess;
} OB_PRE_DUPLICATE_HANDLE_INFORMATION, * POB_PRE_DUPLICATE_HANDLE_INFORMATION;

typedef union _OB_POST_OPERATION_PARAMETERS {
    OB_POST_CREATE_HANDLE_INFORMATION    CreateHandleInformation;
    OB_POST_DUPLICATE_HANDLE_INFORMATION DuplicateHandleInformation;
} OB_POST_OPERATION_PARAMETERS, * POB_POST_OPERATION_PARAMETERS;

typedef struct _OB_POST_OPERATION_INFORMATION {
    OB_OPERATION                  Operation;
    union {
        ULONG Flags;
        struct {
            ULONG KernelHandle : 1;
            ULONG Reserved : 31;
        };
    };
    PVOID                         Object;
    POBJECT_TYPE                  ObjectType;
    PVOID                         CallContext;
    NTSTATUS                      ReturnStatus;
    POB_POST_OPERATION_PARAMETERS Parameters;
} OB_POST_OPERATION_INFORMATION, * POB_POST_OPERATION_INFORMATION;


typedef union _OB_PRE_OPERATION_PARAMETERS {
    OB_PRE_CREATE_HANDLE_INFORMATION    CreateHandleInformation;
    OB_PRE_DUPLICATE_HANDLE_INFORMATION DuplicateHandleInformation;
} OB_PRE_OPERATION_PARAMETERS, * POB_PRE_OPERATION_PARAMETERS;



typedef struct _OB_PRE_OPERATION_INFORMATION {
    OB_OPERATION                 Operation;
    union {
        ULONG Flags;
        struct {
            ULONG KernelHandle : 1;
            ULONG Reserved : 31;
        };
    };
    PVOID                        Object;
    POBJECT_TYPE                 ObjectType;
    PVOID                        CallContext;
    POB_PRE_OPERATION_PARAMETERS Parameters;
} OB_PRE_OPERATION_INFORMATION, * POB_PRE_OPERATION_INFORMATION;





typedef struct {
    GUID Guid;
} NOTIFY_USER_POWER_SETTING, * PNOTIFY_USER_POWER_SETTING;

typedef struct _OSVERSIONINFOEXW {
    ULONG  dwOSVersionInfoSize;
    ULONG  dwMajorVersion;
    ULONG  dwMinorVersion;
    ULONG  dwBuildNumber;
    ULONG  dwPlatformId;
    WCHAR  szCSDVersion[128];
    USHORT wServicePackMajor;
    USHORT wServicePackMinor;
    USHORT wSuiteMask;
    UCHAR  wProductType;
    UCHAR  wReserved;
} OSVERSIONINFOEXW, * POSVERSIONINFOEXW, * LPOSVERSIONINFOEXW, RTL_OSVERSIONINFOEXW, * PRTL_OSVERSIONINFOEXW;



typedef struct _OSVERSIONINFOW {
    ULONG dwOSVersionInfoSize;
    ULONG dwMajorVersion;
    ULONG dwMinorVersion;
    ULONG dwBuildNumber;
    ULONG dwPlatformId;
    WCHAR szCSDVersion[128];
} OSVERSIONINFOW, * POSVERSIONINFOW, * LPOSVERSIONINFOW, RTL_OSVERSIONINFOW, * PRTL_OSVERSIONINFOW;

typedef struct _PCI_ATS_INTERFACE {
    USHORT                 Size;
    USHORT                 Version;
    PVOID                  Context;
    PINTERFACE_REFERENCE   InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PPCI_SET_ATS           SetAddressTranslationServices;
    UCHAR                  InvalidateQueueDepth;
} PCI_ATS_INTERFACE, * PPCI_ATS_INTERFACE;

typedef struct _PO_FX_PERF_STATE {
    ULONGLONG Value;
    PVOID     Context;
} PO_FX_PERF_STATE, * PPO_FX_PERF_STATE;

typedef struct _PCI_MSIX_TABLE_CONFIG_INTERFACE {
    USHORT                     Size;
    USHORT                     Version;
    PVOID                      Context;
    PINTERFACE_REFERENCE       InterfaceReference;
    PINTERFACE_DEREFERENCE     InterfaceDereference;
    PPCI_MSIX_SET_ENTRY        SetTableEntry;
    PPCI_MSIX_MASKUNMASK_ENTRY MaskTableEntry;
    PPCI_MSIX_MASKUNMASK_ENTRY UnmaskTableEntry;
    PPCI_MSIX_GET_ENTRY        GetTableEntry;
    PPCI_MSIX_GET_TABLE_SIZE   GetTableSize;
} PCI_MSIX_TABLE_CONFIG_INTERFACE, * PPCI_MSIX_TABLE_CONFIG_INTERFACE;

typedef struct _PCI_SECURITY_INTERFACE2 {
    USHORT                 Size;
    USHORT                 Version;
    PVOID                  Context;
    PINTERFACE_REFERENCE   InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    ULONG                  Flags;
    ULONG                  SupportedScenarios;
    PPCI_SET_ACS2          SetAccessControlServices;
} PCI_SECURITY_INTERFACE2, * PPCI_SECURITY_INTERFACE2;

typedef struct _PCI_SEGMENT_BUS_NUMBER {
    union {
        struct {
            ULONG BusNumber : 8;
            ULONG SegmentNumber : 16;
            ULONG Reserved : 8;
        } bits;
        ULONG AsULONG;
    } u;
} PCI_SEGMENT_BUS_NUMBER, * PPCI_SEGMENT_BUS_NUMBER;


typedef struct _PLUGPLAY_NOTIFICATION_HEADER {
    USHORT Version;
    USHORT Size;
    GUID   Event;
} PLUGPLAY_NOTIFICATION_HEADER, * PPLUGPLAY_NOTIFICATION_HEADER;


typedef enum _PO_FX_PERF_STATE_TYPE {
    PoFxPerfStateTypeDiscrete,
    PoFxPerfStateTypeRange,
    PoFxPerfStateTypeMaximum
} PO_FX_PERF_STATE_TYPE, * PPO_FX_PERF_STATE_TYPE;

typedef enum _PO_FX_PERF_STATE_UNIT {
    PoFxPerfStateUnitOther,
    PoFxPerfStateUnitFrequency,
    PoFxPerfStateUnitBandwidth,
    PoFxPerfStateUnitMaximum
} PO_FX_PERF_STATE_UNIT, * PPO_FX_PERF_STATE_UNIT;

typedef enum _TRANSACTION_STATE {
    TransactionStateNormal,
    TransactionStateIndoubt,
    TransactionStateCommittedNotify
} TRANSACTION_STATE;

typedef struct _PNP_BUS_INFORMATION {
    GUID           BusTypeGuid;
    INTERFACE_TYPE LegacyBusType;
    ULONG          BusNumber;
} PNP_BUS_INFORMATION, * PPNP_BUS_INFORMATION;

typedef struct _PO_FX_COMPONENT_IDLE_STATE {
    ULONGLONG TransitionLatency;
    ULONGLONG ResidencyRequirement;
    ULONG     NominalPower;
} PO_FX_COMPONENT_IDLE_STATE, * PPO_FX_COMPONENT_IDLE_STATE;

typedef struct _PO_FX_COMPONENT_PERF_SET {
    UNICODE_STRING        Name;
    ULONGLONG             Flags;
    PO_FX_PERF_STATE_UNIT Unit;
    PO_FX_PERF_STATE_TYPE Type;
    union {
        struct {
            ULONG             Count;
            PPO_FX_PERF_STATE States;
        } Discrete;
        struct {
            ULONGLONG Minimum;
            ULONGLONG Maximum;
        } Range;
    };
} PO_FX_COMPONENT_PERF_SET, * PPO_FX_COMPONENT_PERF_SET;

typedef struct _PO_FX_COMPONENT_PERF_INFO {
    ULONG                    PerfStateSetsCount;
    PO_FX_COMPONENT_PERF_SET* PerfStateSets;
} PO_FX_COMPONENT_PERF_INFO, * PPO_FX_COMPONENT_PERF_INFO;


typedef struct _PO_FX_COMPONENT_V1 {
    GUID                        Id;
    ULONG                       IdleStateCount;
    ULONG                       DeepestWakeableIdleState;
    PPO_FX_COMPONENT_IDLE_STATE IdleStates;
} PO_FX_COMPONENT_V1, * PPO_FX_COMPONENT_V1;

typedef struct _PO_FX_COMPONENT_V2 {
    GUID                        Id;
    ULONGLONG                   Flags;
    ULONG                       DeepestWakeableIdleState;
    ULONG                       IdleStateCount;
    PPO_FX_COMPONENT_IDLE_STATE IdleStates;
    ULONG                       ProviderCount;
    PULONG                      Providers;
} PO_FX_COMPONENT_V2, * PPO_FX_COMPONENT_V2;

typedef struct _PO_FX_DEVICE_V1 {
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
} PO_FX_DEVICE_V1, * PPO_FX_DEVICE_V1;

typedef struct _PO_FX_DEVICE_V2 {
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
} PO_FX_DEVICE_V2, * PPO_FX_DEVICE_V2;

typedef struct _PO_FX_DEVICE_V3 {
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
    PO_FX_COMPONENT_V2*                         Components;
} PO_FX_DEVICE_V3, * PPO_FX_DEVICE_V3;



typedef struct _PO_FX_PERF_STATE_CHANGE {
    ULONG Set;
    union {
        ULONG     StateIndex;
        ULONGLONG StateValue;
    };
} PO_FX_PERF_STATE_CHANGE, * PPO_FX_PERF_STATE_CHANGE;






typedef struct _TRANSACTIONMANAGER_BASIC_INFORMATION {
    GUID          TmIdentity;
    LARGE_INTEGER VirtualClock;
} TRANSACTIONMANAGER_BASIC_INFORMATION, * PTRANSACTIONMANAGER_BASIC_INFORMATION;

typedef struct _TRANSACTIONMANAGER_LOG_INFORMATION {
    GUID LogIdentity;
} TRANSACTIONMANAGER_LOG_INFORMATION, * PTRANSACTIONMANAGER_LOG_INFORMATION;

typedef struct _TRANSACTIONMANAGER_LOGPATH_INFORMATION {
    ULONG LogPathLength;
    WCHAR LogPath[1];
} TRANSACTIONMANAGER_LOGPATH_INFORMATION, * PTRANSACTIONMANAGER_LOGPATH_INFORMATION;

typedef struct _TRANSACTIONMANAGER_RECOVERY_INFORMATION {
    ULONGLONG LastRecoveredLsn;
} TRANSACTIONMANAGER_RECOVERY_INFORMATION, * PTRANSACTIONMANAGER_RECOVERY_INFORMATION;



typedef struct _CLS_LSN {
    ULONGLONG Internal;
} CLS_LSN, * PCLS_LSN, PPCLS_LSN;

typedef struct _DMA_OPERATIONS {
  ULONG                                   Size;
  PPUT_DMA_ADAPTER                        PutDmaAdapter;
  PALLOCATE_COMMON_BUFFER                 AllocateCommonBuffer;
  PFREE_COMMON_BUFFER                     FreeCommonBuffer;
  PALLOCATE_ADAPTER_CHANNEL               AllocateAdapterChannel;
  PFLUSH_ADAPTER_BUFFERS                  FlushAdapterBuffers;
  PFREE_ADAPTER_CHANNEL                   FreeAdapterChannel;
  PFREE_MAP_REGISTERS                     FreeMapRegisters;
  PMAP_TRANSFER                           MapTransfer;
  PGET_DMA_ALIGNMENT                      GetDmaAlignment;
  PREAD_DMA_COUNTER                       ReadDmaCounter;
  PGET_SCATTER_GATHER_LIST                GetScatterGatherList;
  PPUT_SCATTER_GATHER_LIST                PutScatterGatherList;
  PCALCULATE_SCATTER_GATHER_LIST_SIZE     CalculateScatterGatherList;
  PBUILD_SCATTER_GATHER_LIST              BuildScatterGatherList;
  PBUILD_MDL_FROM_SCATTER_GATHER_LIST     BuildMdlFromScatterGatherList;
  PGET_DMA_ADAPTER_INFO                   GetDmaAdapterInfo;
  PGET_DMA_TRANSFER_INFO                  GetDmaTransferInfo;
  PINITIALIZE_DMA_TRANSFER_CONTEXT        InitializeDmaTransferContext;
  PALLOCATE_COMMON_BUFFER_EX              AllocateCommonBufferEx;
  PALLOCATE_ADAPTER_CHANNEL_EX            AllocateAdapterChannelEx;
  PCONFIGURE_ADAPTER_CHANNEL              ConfigureAdapterChannel;
  PCANCEL_ADAPTER_CHANNEL                 CancelAdapterChannel;
  PMAP_TRANSFER_EX                        MapTransferEx;
  PGET_SCATTER_GATHER_LIST_EX             GetScatterGatherListEx;
  PBUILD_SCATTER_GATHER_LIST_EX           BuildScatterGatherListEx;
  PFLUSH_ADAPTER_BUFFERS_EX               FlushAdapterBuffersEx;
  PFREE_ADAPTER_OBJECT                    FreeAdapterObject;
  PCANCEL_MAPPED_TRANSFER                 CancelMappedTransfer;
  PALLOCATE_DOMAIN_COMMON_BUFFER          AllocateDomainCommonBuffer;
  PFLUSH_DMA_BUFFER                       FlushDmaBuffer;
  PJOIN_DMA_DOMAIN                        JoinDmaDomain;
  PLEAVE_DMA_DOMAIN                       LeaveDmaDomain;
  PGET_DMA_DOMAIN                         GetDmaDomain;
  PALLOCATE_COMMON_BUFFER_WITH_BOUNDS     AllocateCommonBufferWithBounds;
  PALLOCATE_COMMON_BUFFER_VECTOR          AllocateCommonBufferVector;
  PGET_COMMON_BUFFER_FROM_VECTOR_BY_INDEX GetCommonBufferFromVectorByIndex;
  PFREE_COMMON_BUFFER_FROM_VECTOR         FreeCommonBufferFromVector;
  PFREE_COMMON_BUFFER_VECTOR              FreeCommonBufferVector;
  PCREATE_COMMON_BUFFER_FROM_MDL          CreateCommonBufferFromMdl;
} *PDMA_OPERATIONS, DMA_OPERATIONS;


typedef struct _DMA_ADAPTER {
    USHORT          Version;
    USHORT          Size;
    PDMA_OPERATIONS DmaOperations;
} *PADAPTER_OBJECT, DMA_ADAPTER, * PDMA_ADAPTER;


 
unsigned char _BitTest64(
  __int64 const *Base,
  __int64       Index
);

unsigned char _BitTestAndComplement64(
  __int64 *Base,
  __int64 Index
);

unsigned char _BitTestAndReset64(
  __int64 *Base,
  __int64 Index
);

unsigned char _BitTestAndSet64(
  __int64 *Base,
  __int64 Index
);

void _ReadWriteBarrier();

typedef struct {
  USHORT                                Size;
  USHORT                                Version;
  PVOID                                 Context;
  PINTERFACE_REFERENCE                  InterfaceReference;
  PINTERFACE_DEREFERENCE                InterfaceDereference;
  PGPE_CONNECT_VECTOR2                  GpeConnectVector;
  PGPE_DISCONNECT_VECTOR2               GpeDisconnectVector;
  PGPE_ENABLE_EVENT2                    GpeEnableEvent;
  PGPE_DISABLE_EVENT2                   GpeDisableEvent;
  PGPE_CLEAR_STATUS2                    GpeClearStatus;
  PREGISTER_FOR_DEVICE_NOTIFICATIONS2   RegisterForDeviceNotifications;
  PUNREGISTER_FOR_DEVICE_NOTIFICATIONS2 UnregisterForDeviceNotifications;
} ACPI_INTERFACE_STANDARD2, *PACPI_INTERFACE_STANDARD2;



void AppendTailList(
    PLIST_ENTRY ListHead,
    PLIST_ENTRY ListToAppend
);

/*
void ARM64_SYSREG_CRM(
   _Reg_
);

void ARM64_SYSREG_CRN(
   _Reg_
);

void ARM64_SYSREG_OP1(
   _Reg_
);

void ARM64_SYSREG_OP2(
   _Reg_
);
*/


void BarrierAfterRead();

void BarrierAfterRead();

void BarrierAfterRead();

typedef struct _BOOTDISK_INFORMATION {
  LONGLONG BootPartitionOffset;
  LONGLONG SystemPartitionOffset;
  ULONG    BootDeviceSignature;
  ULONG    SystemDeviceSignature;
} BOOTDISK_INFORMATION, *PBOOTDISK_INFORMATION;

typedef struct _BOOTDISK_INFORMATION_EX {
  LONGLONG BootPartitionOffset;
  LONGLONG SystemPartitionOffset;
  ULONG    BootDeviceSignature;
  ULONG    SystemDeviceSignature;
  GUID     BootDeviceGuid;
  GUID     SystemDeviceGuid;
  BOOLEAN  BootDeviceIsGpt;
  BOOLEAN  SystemDeviceIsGpt;
} BOOTDISK_INFORMATION_EX, *PBOOTDISK_INFORMATION_EX;

typedef enum _BOUND_CALLBACK_STATUS {
  BoundExceptionContinueSearch,
  BoundExceptionHandled,
  BoundExceptionError,
  BoundExceptionMaximum
} BOUND_CALLBACK_STATUS, *PBOUND_CALLBACK_STATUS;


typedef struct _BUS_INTERFACE_STANDARD {
  USHORT                 Size;
  USHORT                 Version;
  PVOID                  Context;
  PINTERFACE_REFERENCE   InterfaceReference;
  PINTERFACE_DEREFERENCE InterfaceDereference;
  PTRANSLATE_BUS_ADDRESS TranslateBusAddress;
  PGET_DMA_ADAPTER       GetDmaAdapter;
  PGET_SET_DEVICE_DATA   SetBusData;
  PGET_SET_DEVICE_DATA   GetBusData;
} BUS_INTERFACE_STANDARD, *PBUS_INTERFACE_STANDARD;

typedef enum {
  BusQueryDeviceID,
  BusQueryHardwareIDs,
  BusQueryCompatibleIDs,
  BusQueryInstanceID,
  BusQueryDeviceSerialNumber,
  BusQueryContainerID
} BUS_QUERY_ID_TYPE, *PBUS_QUERY_ID_TYPE;

typedef struct _BUS_RESOURCE_UPDATE_INTERFACE {
  USHORT                    Size;
  USHORT                    Version;
  PVOID                     Context;
  PINTERFACE_REFERENCE      InterfaceReference;
  PINTERFACE_DEREFERENCE    InterfaceDereference;
  PGET_UPDATED_BUS_RESOURCE GetUpdatedBusResource;
} BUS_RESOURCE_UPDATE_INTERFACE, *PBUS_RESOURCE_UPDATE_INTERFACE;

typedef union _BUS_SPECIFIC_RESET_FLAGS {
  struct {
    ULONGLONG KeepStackReset : 1;
    ULONGLONG Reserved : 63;
  } u;
  ULONGLONG AsUlonglong;
} BUS_SPECIFIC_RESET_FLAGS, *PBUS_SPECIFIC_RESET_FLAGS;

typedef enum _CLFS_CONTEXT_MODE {
  ClfsContextNone,
  ClfsContextUndoNext,
  ClfsContextPrevious,
  ClfsContextForward
} CLFS_CONTEXT_MODE, *PCLFS_CONTEXT_MODE, PPCLFS_CONTEXT_MODE;

typedef struct _CLFS_LOG_NAME_INFORMATION {
  USHORT NameLengthInBytes;
  WCHAR  Name[1];
} CLFS_LOG_NAME_INFORMATION, *PCLFS_LOG_NAME_INFORMATION, PPCLFS_LOG_NAME_INFORMATION;

typedef struct _CLFS_MGMT_CLIENT_REGISTRATION {
  ULONG                                      Version;
  PCLFS_CLIENT_ADVANCE_TAIL_CALLBACK         AdvanceTailCallback;
  PVOID                                      AdvanceTailCallbackData;
  PCLFS_CLIENT_LFF_HANDLER_COMPLETE_CALLBACK LogGrowthCompleteCallback;
  PVOID                                      LogGrowthCompleteCallbackData;
  PCLFS_CLIENT_LOG_UNPINNED_CALLBACK         LogUnpinnedCallback;
  PVOID                                      LogUnpinnedCallbackData;
} CLFS_MGMT_CLIENT_REGISTRATION, *PCLFS_MGMT_CLIENT_REGISTRATION;


typedef enum _CLFS_MGMT_POLICY_TYPE {
    ClfsMgmtPolicyMaximumSize,
    ClfsMgmtPolicyMinimumSize,
    ClfsMgmtPolicyNewContainerSize,
    ClfsMgmtPolicyGrowthRate,
    ClfsMgmtPolicyLogTail,
    ClfsMgmtPolicyAutoShrink,
    ClfsMgmtPolicyAutoGrow,
    ClfsMgmtPolicyNewContainerPrefix,
    ClfsMgmtPolicyNewContainerSuffix,
    ClfsMgmtPolicyNewContainerExtension,
    ClfsMgmtPolicyInvalid
} CLFS_MGMT_POLICY_TYPE, * PCLFS_MGMT_POLICY_TYPE;

typedef struct _CLFS_MGMT_POLICY {
  ULONG                 Version;
  ULONG                 LengthInBytes;
  ULONG                 PolicyFlags;
  CLFS_MGMT_POLICY_TYPE PolicyType;
  union {
    struct {
      ULONG Containers;
    } MaximumSize;
    struct {
      ULONG Containers;
    } MinimumSize;
    struct {
      ULONG SizeInBytes;
    } NewContainerSize;
    struct {
      ULONG AbsoluteGrowthInContainers;
      ULONG RelativeGrowthPercentage;
    } GrowthRate;
    struct {
      ULONG MinimumAvailablePercentage;
      ULONG MinimumAvailableContainers;
    } LogTail;
    struct {
      ULONG Percentage;
    } AutoShrink;
    struct {
      ULONG Enabled;
    } AutoGrow;
    struct {
      USHORT PrefixLengthInBytes;
      WCHAR  PrefixString[1];
    } NewContainerPrefix;
    struct {
      ULONGLONG NextContainerSuffix;
    } NewContainerSuffix;
    struct {
      USHORT ExtensionLengthInBytes;
      WCHAR  ExtensionString[1];
    } NewContainerExtension;
  } PolicyParameters;
} CLFS_MGMT_POLICY, *PCLFS_MGMT_POLICY;

typedef struct _CLFS_STREAM_ID_INFORMATION {
  UCHAR StreamIdentifier;
} CLFS_STREAM_ID_INFORMATION, *PCLFS_STREAM_ID_INFORMATION, PPCLFS_STREAM_ID_INFORMATION;


typedef struct _CLS_CONTAINER_INFORMATION {
    ULONG                FileAttributes;
    ULONGLONG            CreationTime;
    ULONGLONG            LastAccessTime;
    ULONGLONG            LastWriteTime;
    LONGLONG             ContainerSize;
    ULONG                FileNameActualLength;
    ULONG                FileNameLength;
    WCHAR* FileName;
    CLFS_CONTAINER_STATE State;
    CLFS_CONTAINER_ID    PhysicalContainerId;
    CLFS_CONTAINER_ID    LogicalContainerId;
} CLS_CONTAINER_INFORMATION, * PCLS_CONTAINER_INFORMATION, PPCLS_CONTAINER_INFORMATION;

typedef struct _CLS_INFORMATION {
    LONGLONG  TotalAvailable;
    LONGLONG  CurrentAvailable;
    LONGLONG  TotalReservation;
    ULONGLONG BaseFileSize;
    ULONGLONG ContainerSize;
    ULONG     TotalContainers;
    ULONG     FreeContainers;
    ULONG     TotalClients;
    ULONG     Attributes;
    ULONG     FlushThreshold;
    ULONG     SectorSize;
    CLS_LSN   MinArchiveTailLsn;
    CLS_LSN   BaseLsn;
    CLS_LSN   LastFlushedLsn;
    CLS_LSN   LastLsn;
    CLS_LSN   RestartLsn;
    GUID      Identity;
} CLS_INFORMATION, * PCLS_INFORMATION, * PPCLS_INFORMATION;



typedef struct _CLS_IO_STATISTICS_HEADER {
    UCHAR              ubMajorVersion;
    UCHAR              ubMinorVersion;
    CLFS_IOSTATS_CLASS eStatsClass;
    USHORT             cbLength;
    ULONG              coffData;
} CLS_IO_STATISTICS_HEADER, * PCLS_IO_STATISTICS_HEADER, PPCLS_IO_STATISTICS_HEADER;

typedef enum _CLS_LOG_INFORMATION_CLASS {
    ClfsLogBasicInformation,
    ClfsLogBasicInformationPhysical,
    ClfsLogPhysicalNameInformation,
    ClfsLogStreamIdentifierInformation,
    ClfsLogSystemMarkingInformation,
    ClfsLogPhysicalLsnInformation
} CLS_LOG_INFORMATION_CLASS, * PCLS_LOG_INFORMATION_CLASS, PPCLS_LOG_INFORMATION_CLASS;

typedef struct _CLS_SCAN_CONTEXT {
    CLFS_NODE_ID               cidNode;
    PLOG_FILE_OBJECT           plfoLog;
    ULONG                      cIndex;
    ULONG                      cContainers;
    ULONG                      cContainersReturned;
    CLFS_SCAN_MODE             eScanMode;
    PCLS_CONTAINER_INFORMATION pinfoContainer;
} CLS_SCAN_CONTEXT, * PCLS_SCAN_CONTEXT, PPCLS_SCAN_CONTEXT;

typedef struct _CLS_WRITE_ENTRY {
    PVOID Buffer;
    ULONG ByteLength;
} CLS_WRITE_ENTRY, * PCLS_WRITE_ENTRY, PPCLS_WRITE_ENTRY;

typedef struct _CM_FLOPPY_DEVICE_DATA {
    USHORT Version;
    USHORT Revision;
    CHAR   Size[8];
    ULONG  MaxDensity;
    ULONG  MountDensity;
    UCHAR  StepRateHeadUnloadTime;
    UCHAR  HeadLoadTime;
    UCHAR  MotorOffTime;
    UCHAR  SectorLengthCode;
    UCHAR  SectorPerTrack;
    UCHAR  ReadWriteGapLength;
    UCHAR  DataTransferLength;
    UCHAR  FormatGapLength;
    UCHAR  FormatFillCharacter;
    UCHAR  HeadSettleTime;
    UCHAR  MotorSettleTime;
    UCHAR  MaximumTrackValue;
    UCHAR  DataTransferRate;
} CM_FLOPPY_DEVICE_DATA, * PCM_FLOPPY_DEVICE_DATA;

typedef struct _CM_FULL_RESOURCE_DESCRIPTOR {
    INTERFACE_TYPE           InterfaceType;
    ULONG                    BusNumber;
    CM_PARTIAL_RESOURCE_LIST PartialResourceList;
} CM_FULL_RESOURCE_DESCRIPTOR, * PCM_FULL_RESOURCE_DESCRIPTOR;

typedef struct _CM_INT13_DRIVE_PARAMETER {
    USHORT DriveSelect;
    ULONG  MaxCylinders;
    USHORT SectorsPerTrack;
    USHORT MaxHeads;
    USHORT NumberDrives;
} CM_INT13_DRIVE_PARAMETER, * PCM_INT13_DRIVE_PARAMETER;

typedef struct _CM_KEYBOARD_DEVICE_DATA {
    USHORT Version;
    USHORT Revision;
    UCHAR  Type;
    UCHAR  Subtype;
    USHORT KeyboardFlags;
} CM_KEYBOARD_DEVICE_DATA, * PCM_KEYBOARD_DEVICE_DATA;

typedef struct _CM_PARTIAL_RESOURCE_DESCRIPTOR {
    UCHAR  Type;
    UCHAR  ShareDisposition;
    USHORT Flags;
    union {
        struct {
            PHYSICAL_ADDRESS Start;
            ULONG            Length;
        } Generic;
        struct {
            PHYSICAL_ADDRESS Start;
            ULONG            Length;
        } Port;
        struct {
            USHORT    Level;
            USHORT    Group;

            //ULONG     Level;

            ULONG     Vector;
            KAFFINITY Affinity;
        } Interrupt;
        struct {
            union {
                struct {
                    USHORT    Group;
                    USHORT    Reserved;
                    USHORT    MessageCount;
                    ULONG     Vector;
                    KAFFINITY Affinity;
                } Raw;
                struct {
//#if ...
                    USHORT    Level;
                    USHORT    Group;
//#else
//                    ULONG     Level;
//#endif
                    ULONG     Vector;
                    KAFFINITY Affinity;
                } Translated;
            } DUMMYUNIONNAME;
        } MessageInterrupt;
        struct {
            PHYSICAL_ADDRESS Start;
            ULONG            Length;
        } Memory;
        struct {
            ULONG Channel;
            ULONG Port;
            ULONG Reserved1;
        } Dma;
        struct {
            ULONG Channel;
            ULONG RequestLine;
            UCHAR TransferWidth;
            UCHAR Reserved1;
            UCHAR Reserved2;
            UCHAR Reserved3;
        } DmaV3;
        struct {
            ULONG Data[3];
        } DevicePrivate;
        struct {
            ULONG Start;
            ULONG Length;
            ULONG Reserved;
        } BusNumber;
        struct {
            ULONG DataSize;
            ULONG Reserved1;
            ULONG Reserved2;
        } DeviceSpecificData;
        struct {
            PHYSICAL_ADDRESS Start;
            ULONG            Length40;
        } Memory40;
        struct {
            PHYSICAL_ADDRESS Start;
            ULONG            Length48;
        } Memory48;
        struct {
            PHYSICAL_ADDRESS Start;
            ULONG            Length64;
        } Memory64;
        struct {
            UCHAR Class;
            UCHAR Type;
            UCHAR Reserved1;
            UCHAR Reserved2;
            ULONG IdLowPart;
            ULONG IdHighPart;
        } Connection;
    } u;
} CM_PARTIAL_RESOURCE_DESCRIPTOR, * PCM_PARTIAL_RESOURCE_DESCRIPTOR;


typedef struct _CM_RESOURCE_LIST {
    ULONG                       Count;
    CM_FULL_RESOURCE_DESCRIPTOR List[1];
} CM_RESOURCE_LIST, * PCM_RESOURCE_LIST;


typedef struct _CM_SCSI_DEVICE_DATA {
    USHORT Version;
    USHORT Revision;
    UCHAR  HostIdentifier;
} CM_SCSI_DEVICE_DATA, * PCM_SCSI_DEVICE_DATA;

typedef struct _CM_SERIAL_DEVICE_DATA {
    USHORT Version;
    USHORT Revision;
    ULONG  BaudClock;
} CM_SERIAL_DEVICE_DATA, * PCM_SERIAL_DEVICE_DATA;

typedef struct _CLS_IO_STATISTICS {
    CLS_IO_STATISTICS_HEADER hdrIoStats;
    ULONGLONG                cFlush;
    ULONGLONG                cbFlush;
    ULONGLONG                cMetaFlush;
    ULONGLONG                cbMetaFlush;
} CLS_IO_STATISTICS, * PCLS_IO_STATISTICS, PPCLS_IO_STATISTICS;

CLFSUSER_API NTSTATUS ClfsAddLogContainer(
   PLOG_FILE_OBJECT plfoLog,
   PULONGLONG       pcbContainer,
   PUNICODE_STRING  puszContainerPath
);


CLFSUSER_API NTSTATUS ClfsAddLogContainerSet(
             PLOG_FILE_OBJECT plfoLog,
             USHORT           cContainers,
         PULONGLONG       pcbContainer,
             PUNICODE_STRING  rguszContainerPath
);


CLFSUSER_API NTSTATUS ClfsAdvanceLogBase(
   PVOID     pvMarshalContext,
        PCLFS_LSN plsnBase,
        ULONG     fFlags
);

CLFSUSER_API NTSTATUS ClfsAlignReservedLog(
    PVOID       pvMarshalContext,
    ULONG       cRecords,
    LONGLONG*   rgcbReservation,
   PLONGLONG   pcbAlignReservation
);

CLFSUSER_API NTSTATUS ClfsAllocReservedLog(
   PVOID     pvMarshalContext,
   ULONG     cRecords,
   PLONGLONG pcbAdjustment
);

CLFSUSER_API NTSTATUS ClfsCloseAndResetLogFile(
   PLOG_FILE_OBJECT plfoLog
);

CLFSUSER_API NTSTATUS ClfsCloseLogFileObject(
   PLOG_FILE_OBJECT plfoLog
);

CLFSUSER_API NTSTATUS ClfsCreateLogFile(
            PPLOG_FILE_OBJECT    pplfoLog,
             PUNICODE_STRING      puszLogFileName,
             ACCESS_MASK          fDesiredAccess,
             ULONG                dwShareMode,
   PSECURITY_DESCRIPTOR psdLogFile,
             ULONG                fCreateDisposition,
             ULONG                fCreateOptions,
             ULONG                fFlagsAndAttributes,
             ULONG                fLogOptionFlag,
   PVOID                pvContext,
             ULONG                cbContext
);

CLFSUSER_API NTSTATUS ClfsCreateMarshallingArea(
             PLOG_FILE_OBJECT   plfoLog,
             POOL_TYPE          ePoolType,
   PALLOCATE_FUNCTION pfnAllocBuffer,
   PFREE_FUNCTION     pfnFreeBuffer,
             ULONG              cbMarshallingBuffer,
             ULONG              cMaxWriteBuffers,
             ULONG              cMaxReadBuffers,
            PVOID              *ppvMarshalContext
);

CLFSUSER_API NTSTATUS ClfsCreateScanContext(
        PLOG_FILE_OBJECT   plfoLog,
        ULONG              cFromContainer,
        ULONG              cContainers,
        CLFS_SCAN_MODE     eScanMode,
   PCLFS_SCAN_CONTEXT pcxScan
);

CLFSUSER_API NTSTATUS ClfsDeleteLogByPointer(
   PLOG_FILE_OBJECT plfoLog
);

CLFSUSER_API NTSTATUS ClfsDeleteLogFile(
             PUNICODE_STRING puszLogFileName,
                 PVOID           pvReserved,
             ULONG           fLogOptionFlag,
   PVOID           pvContext,
             ULONG           cbContext
);

CLFSUSER_API NTSTATUS ClfsDeleteMarshallingArea(
   PVOID pvMarshalContext
);

CLFSUSER_API NTSTATUS ClfsFlushBuffers(
   PVOID pvMarshalContext
);

CLFSUSER_API NTSTATUS ClfsFlushToLsn(
              PVOID     pvMarshalContext,
              PCLFS_LSN plsnFlush,
   PCLFS_LSN plsnLastFlushed
);

CLFSUSER_API NTSTATUS ClfsGetContainerName(
              PLOG_FILE_OBJECT  plfoLog,
              CLFS_CONTAINER_ID cidLogicalContainer,
             PUNICODE_STRING   puszContainerName,
   PULONG            pcActualLenContainerName
);

CLFSUSER_API NTSTATUS ClfsGetIoStatistics(
              PLOG_FILE_OBJECT   plfoLog,
         PVOID              pvStatsBuffer,
              ULONG              cbStatsBuffer,
              CLFS_IOSTATS_CLASS eStatsClass,
   PULONG             pcbStatsWritten
);

CLFSUSER_API ULONG ClfsLsnBlockOffset(
   const CLFS_LSN *plsn
);

CLFSUSER_API CLFS_CONTAINER_ID ClfsLsnContainer(
   const CLFS_LSN *plsn
);

CLFSUSER_API CLFS_LSN ClfsLsnCreate(
   CLFS_CONTAINER_ID cidContainer,
   ULONG             offBlock,
   ULONG             cRecord
);

CLFSUSER_API BOOLEAN ClfsLsnEqual(
   const CLFS_LSN *plsn1,
   const CLFS_LSN *plsn2
);

CLFSUSER_API BOOLEAN ClfsLsnGreater(
   const CLFS_LSN *plsn1,
   const CLFS_LSN *plsn2
);

CLFSUSER_API BOOLEAN ClfsLsnLess(
   const CLFS_LSN *plsn1,
   const CLFS_LSN *plsn2
);

CLFSUSER_API BOOLEAN ClfsLsnNull(
   const CLFS_LSN *plsn
);

CLFSUSER_API ULONG ClfsLsnRecordSequence(
   const CLFS_LSN *plsn
);

CLFSUSER_API NTSTATUS ClfsMgmtDeregisterManagedClient(
  CLFS_MGMT_CLIENT ClientCookie
);

CLFSUSER_API NTSTATUS ClfsMgmtHandleLogFileFull(
   CLFS_MGMT_CLIENT Client
);

CLFSUSER_API NTSTATUS ClfsMgmtInstallPolicy(
   PLOG_FILE_OBJECT  LogFile,
   PCLFS_MGMT_POLICY Policy,
   ULONG             PolicyLength
);

CLFSUSER_API NTSTATUS ClfsMgmtQueryPolicy(
    PLOG_FILE_OBJECT      LogFile,
    CLFS_MGMT_POLICY_TYPE PolicyType,
   PCLFS_MGMT_POLICY     Policy,
   PULONG                PolicyLength
);

CLFSUSER_API NTSTATUS ClfsMgmtRegisterManagedClient(
   PLOG_FILE_OBJECT               LogFile,
   PCLFS_MGMT_CLIENT_REGISTRATION RegistrationData,
       PCLFS_MGMT_CLIENT              ClientCookie
);

CLFSUSER_API NTSTATUS ClfsMgmtRemovePolicy(
   PLOG_FILE_OBJECT      LogFile,
   CLFS_MGMT_POLICY_TYPE PolicyType
);

CLFSUSER_API NTSTATUS ClfsMgmtSetLogFileSize(
             PLOG_FILE_OBJECT                     LogFile,
             PULONGLONG                           NewSizeInContainers,
            PULONGLONG                           ResultingSizeInContainers,
   PCLFS_SET_LOG_SIZE_COMPLETE_CALLBACK CompletionRoutine,
   PVOID                                CompletionRoutineData
);

CLFSUSER_API NTSTATUS ClfsMgmtSetLogFileSizeAsClient(
              PLOG_FILE_OBJECT                     LogFile,
    PCLFS_MGMT_CLIENT                    ClientCookie,
              PULONGLONG                           NewSizeInContainers,
   PULONGLONG                           ResultingSizeInContainers,
    PCLFS_SET_LOG_SIZE_COMPLETE_CALLBACK CompletionRoutine,
    PVOID                                CompletionRoutineData
);

CLFSUSER_API NTSTATUS ClfsMgmtTailAdvanceFailure(
   CLFS_MGMT_CLIENT Client,
   NTSTATUS         Reason
);

CLFSUSER_API NTSTATUS ClfsQueryLogFileInformation(
    PLOG_FILE_OBJECT           plfoLog,
    CLFS_LOG_INFORMATION_CLASS eInformationClass,
        PVOID                      pinfoInputBuffer,
        ULONG                      cbinfoInputBuffer,
   PVOID                      pinfoBuffer,
        PULONG                     pcbInfoBuffer
);

CLFSUSER_API NTSTATUS ClfsReadLogRecord(
        PVOID             pvMarshalContext,
   PCLFS_LSN         plsnFirst,
        CLFS_CONTEXT_MODE peContextMode,
       PVOID             *ppvReadBuffer,
       PULONG            pcbReadBuffer,
       PCLFS_RECORD_TYPE peRecordType,
       PCLFS_LSN         plsnUndoNext,
       PCLFS_LSN         plsnPrevious,
       PVOID             *ppvReadContext
);

CLFSUSER_API NTSTATUS ClfsReadNextLogRecord(
        PVOID             pvReadContext,
            PVOID             *ppvBuffer,
            PULONG            pcbBuffer,
        PCLFS_RECORD_TYPE peRecordType,
   PCLFS_LSN         plsnUser,
            PCLFS_LSN         plsnUndoNext,
            PCLFS_LSN         plsnPrevious,
            PCLFS_LSN         plsnRecord
);

CLFSUSER_API NTSTATUS ClfsReadPreviousRestartArea(
    PVOID     pvReadContext,
   PVOID     *ppvRestartBuffer,
   PULONG    pcbRestartBuffer,
   PCLFS_LSN plsnRestart
);

CLFSUSER_API NTSTATUS ClfsReadRestartArea(
   PVOID     pvMarshalContext,
       PVOID     *ppvRestartBuffer,
       PULONG    pcbRestartBuffer,
       PCLFS_LSN plsn,
       PVOID     *ppvReadContext
);


CLFSUSER_API NTSTATUS ClfsRemoveLogContainer(
   PLOG_FILE_OBJECT plfoLog,
   PUNICODE_STRING  puszContainerPath,
   BOOLEAN          fForce
);

CLFSUSER_API NTSTATUS ClfsRemoveLogContainerSet(
   PLOG_FILE_OBJECT plfoLog,
   USHORT           cContainers,
   PUNICODE_STRING  rgwszContainerPath,
   BOOLEAN          fForce
);

CLFSUSER_API NTSTATUS ClfsReserveAndAppendLog(
              PVOID             pvMarshalContext,
    PCLFS_WRITE_ENTRY rgWriteEntries,
              ULONG             cWriteEntries,
    PCLFS_LSN         plsnUndoNext,
    PCLFS_LSN         plsnPrevious,
              ULONG             cReserveRecords,
         PLONGLONG         rgcbReservation,
              ULONG             fFlags,
   PCLFS_LSN         plsn
);

CLFSUSER_API NTSTATUS ClfsReserveAndAppendLogAligned(
              PVOID             pvMarshalContext,
    PCLFS_WRITE_ENTRY rgWriteEntries,
              ULONG             cWriteEntries,
              ULONG             cbEntryAlignment,
    PCLFS_LSN         plsnUndoNext,
    PCLFS_LSN         plsnPrevious,
              ULONG             cReserveRecords,
         PLONGLONG         rgcbReservation,
              ULONG             fFlags,
   PCLFS_LSN         plsn
);

CLFSUSER_API NTSTATUS ClfsScanLogContainers(
   PCLFS_SCAN_CONTEXT pcxScan,
        CLFS_SCAN_MODE     eScanMode
);

CLFSUSER_API NTSTATUS ClfsSetArchiveTail(
   PLOG_FILE_OBJECT plfoLog,
   PCLFS_LSN        plsnArchiveTail
);

CLFSUSER_API NTSTATUS ClfsSetEndOfLog(
   PLOG_FILE_OBJECT plfoLog,
   PCLFS_LSN        plsnEnd
);

CLFSUSER_API NTSTATUS ClfsSetLogFileInformation(
   PLOG_FILE_OBJECT           plfoLog,
   CLFS_LOG_INFORMATION_CLASS eInformationClass,
   PVOID                      pinfoBuffer,
   ULONG                      cbBuffer
);

CLFSUSER_API NTSTATUS ClfsTerminateReadLog(
   PVOID pvCursorContext
);

CLFSUSER_API NTSTATUS ClfsWriteRestartArea(
         PVOID     pvMarshalContext,
              PVOID     pvRestartBuffer,
              ULONG     cbRestartBuffer,
    PCLFS_LSN plsnBase,
              ULONG     fFlags,
   PULONG    pcbWritten,
   PCLFS_LSN plsnNext
);


NTSTATUS CmCallbackGetKeyObjectID(
              PLARGE_INTEGER   Cookie,
              PVOID            Object,
   PULONG_PTR       ObjectID,
   PCUNICODE_STRING *ObjectName
);

NTSTATUS CmCallbackGetKeyObjectIDEx(
              PLARGE_INTEGER   Cookie,
              PVOID            Object,
   PULONG_PTR       ObjectID,
   PCUNICODE_STRING *ObjectName,
              ULONG            Flags
);

void CmCallbackReleaseKeyObjectIDEx(
  PCUNICODE_STRING ObjectName
);

PVOID CmGetBoundTransaction(
   PLARGE_INTEGER Cookie,
   PVOID          Object
);

void CmGetCallbackVersion(
   PULONG Major,
   PULONG Minor
);

NTSTATUS CmRegisterCallback(
             PEX_CALLBACK_FUNCTION Function,
   PVOID                 Context,
            PLARGE_INTEGER        Cookie
);

NTSTATUS CmRegisterCallbackEx(
             PEX_CALLBACK_FUNCTION Function,
             PCUNICODE_STRING      Altitude,
             PVOID                 Driver,
   PVOID                 Context,
            PLARGE_INTEGER        Cookie,
                 PVOID                 Reserved
);

NTSTATUS CmSetCallbackObjectContext(
         PVOID          Object,
              PLARGE_INTEGER Cookie,
              PVOID          NewContext,
   PVOID          *OldContext
);

NTSTATUS CmUnRegisterCallback(
   LARGE_INTEGER Cookie
);

typedef struct _FILE_FS_DEVICE_INFORMATION {
    DEVICE_TYPE DeviceType;
    ULONG       Characteristics;
} FILE_FS_DEVICE_INFORMATION, * PFILE_FS_DEVICE_INFORMATION;

typedef struct _FILE_FULL_EA_INFORMATION {
    ULONG  NextEntryOffset;
    UCHAR  Flags;
    UCHAR  EaNameLength;
    USHORT EaValueLength;
    CHAR   EaName[1];
} FILE_FULL_EA_INFORMATION, * PFILE_FULL_EA_INFORMATION;

typedef struct _FILE_IO_PRIORITY_HINT_INFORMATION {
    IO_PRIORITY_HINT PriorityHint;
} FILE_IO_PRIORITY_HINT_INFORMATION, * PFILE_IO_PRIORITY_HINT_INFORMATION;

typedef struct _FILE_IS_REMOTE_DEVICE_INFORMATION {
    BOOLEAN IsRemote;
} FILE_IS_REMOTE_DEVICE_INFORMATION, * PFILE_IS_REMOTE_DEVICE_INFORMATION;




typedef struct _FILE_POSITION_INFORMATION {
    LARGE_INTEGER CurrentByteOffset;
} FILE_POSITION_INFORMATION, * PFILE_POSITION_INFORMATION;


typedef struct _FILE_STANDARD_INFORMATION_EX {
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG         NumberOfLinks;
    BOOLEAN       DeletePending;
    BOOLEAN       Directory;
    BOOLEAN       AlternateStream;
    BOOLEAN       MetadataAttribute;
} FILE_STANDARD_INFORMATION_EX, * PFILE_STANDARD_INFORMATION_EX;


PSLIST_ENTRY FirstEntrySList(
     PSLIST_HEADER SListHead
);

typedef struct _FPGA_CONTROL_INTERFACE {
    USHORT                        Size;
    USHORT                        Version;
    PVOID                         Context;
    PINTERFACE_REFERENCE          InterfaceReference;
    PINTERFACE_DEREFERENCE        InterfaceDereference;
    PFPGA_BUS_SCAN                BusScan;
    PFPGA_CONTROL_LINK            ControlLink;
    PFPGA_CONTROL_CONFIG_SPACE    ControlConfigSpace;
    PFPGA_CONTROL_ERROR_REPORTING ControlErrorReporting;
} FPGA_CONTROL_INTERFACE, * PFPGA_CONTROL_INTERFACE;


typedef
VOID
(*PDEVICE_RESET_COMPLETION)(
     NTSTATUS Status,
     PVOID Context
    );


typedef enum _IMAGE_POLICY_ENTRY_TYPE {
    ImagePolicyEntryTypeNone,
    ImagePolicyEntryTypeBool,
    ImagePolicyEntryTypeInt8,
    ImagePolicyEntryTypeUInt8,
    ImagePolicyEntryTypeInt16,
    ImagePolicyEntryTypeUInt16,
    ImagePolicyEntryTypeInt32,
    ImagePolicyEntryTypeUInt32,
    ImagePolicyEntryTypeInt64,
    ImagePolicyEntryTypeUInt64,
    ImagePolicyEntryTypeAnsiString,
    ImagePolicyEntryTypeUnicodeString,
    ImagePolicyEntryTypeOverride,
    ImagePolicyEntryTypeMaximum
} IMAGE_POLICY_ENTRY_TYPE;

typedef enum _IMAGE_POLICY_ID {
    ImagePolicyIdNone,
    ImagePolicyIdEtw,
    ImagePolicyIdDebug,
    ImagePolicyIdCrashDump,
    ImagePolicyIdCrashDumpKey,
    ImagePolicyIdCrashDumpKeyGuid,
    ImagePolicyIdParentSd,
    ImagePolicyIdParentSdRev,
    ImagePolicyIdSvn,
    ImagePolicyIdDeviceId,
    ImagePolicyIdCapability,
    ImagePolicyIdScenarioId,
    ImagePolicyIdMaximum
} IMAGE_POLICY_ID;

typedef struct _FUNCTION_LEVEL_DEVICE_RESET_PARAMETERS {
    ULONG                    Size;
    PDEVICE_RESET_COMPLETION DeviceResetCompletion;
    PVOID                    CompletionContext;
} FUNCTION_LEVEL_DEVICE_RESET_PARAMETERS, * PFUNCTION_LEVEL_DEVICE_RESET_PARAMETERS;


typedef struct _GENERIC_MAPPING {
    ACCESS_MASK GenericRead;
    ACCESS_MASK GenericWrite;
    ACCESS_MASK GenericExecute;
    ACCESS_MASK GenericAll;
} GENERIC_MAPPING;

typedef struct _HWPROFILE_CHANGE_NOTIFICATION {
    USHORT Version;
    USHORT Size;
    GUID   Event;
} HWPROFILE_CHANGE_NOTIFICATION, * PHWPROFILE_CHANGE_NOTIFICATION;

typedef struct _IMAGE_POLICY_ENTRY {
    IMAGE_POLICY_ENTRY_TYPE Type;
    IMAGE_POLICY_ID         PolicyId;
    union {
        const VOID* None;
        BOOLEAN    BoolValue;
        INT8       Int8Value;
        UINT8      UInt8Value;
        INT16      Int16Value;
        UINT16     UInt16Value;
        INT32      Int32Value;
        UINT32     UInt32Value;
        INT64      Int64Value;
        UINT64     UInt64Value;
        PCSTR      AnsiStringValue;
        PCWSTR     UnicodeStringValue;
    } u;
} IMAGE_POLICY_ENTRY;


typedef struct _IMAGE_POLICY_METADATA {
    UCHAR              Version;
    UCHAR              Reserved0[7];
    ULONGLONG          ApplicationId;
    IMAGE_POLICY_ENTRY* Policies;
} IMAGE_POLICY_METADATA;


typedef struct _D3COLD_AUX_POWER_AND_TIMING_INTERFACE {
  USHORT                          Size;
  USHORT                          Version;
  PVOID                           Context;
  PINTERFACE_REFERENCE            InterfaceReference;
  PINTERFACE_DEREFERENCE          InterfaceDereference;
  PD3COLD_REQUEST_CORE_POWER_RAIL RequestCorePowerRail;
  PD3COLD_REQUEST_AUX_POWER       RequestAuxPower;
  PD3COLD_REQUEST_PERST_DELAY     RequestPerstDelay;
} D3COLD_AUX_POWER_AND_TIMING_INTERFACE, *PD3COLD_AUX_POWER_AND_TIMING_INTERFACE;



typedef struct _D3COLD_SUPPORT_INTERFACE {
  USHORT                             Size;
  USHORT                             Version;
  PVOID                              Context;
  PINTERFACE_REFERENCE               InterfaceReference;
  PINTERFACE_DEREFERENCE             InterfaceDereference;
  PSET_D3COLD_SUPPORT                SetD3ColdSupport;
  PGET_IDLE_WAKE_INFO                GetIdleWakeInfo;
  PGET_D3COLD_CAPABILITY             GetD3ColdCapability;
  PGET_D3COLD_CAPABILITY             GetBusDriverD3ColdSupport;
  PGET_D3COLD_LAST_TRANSITION_STATUS GetLastTransitionStatus;
} D3COLD_SUPPORT_INTERFACE, *PD3COLD_SUPPORT_INTERFACE;

typedef union _DEVICE_BUS_SPECIFIC_RESET_TYPE {
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
} DEVICE_BUS_SPECIFIC_RESET_TYPE, * PDEVICE_BUS_SPECIFIC_RESET_TYPE;

typedef struct _DEVICE_BUS_SPECIFIC_RESET_INFO {
  GUID                           BusTypeGuid;
  DEVICE_BUS_SPECIFIC_RESET_TYPE ResetTypeSupported;
} DEVICE_BUS_SPECIFIC_RESET_INFO, *PDEVICE_BUS_SPECIFIC_RESET_INFO;

typedef struct _DEVICE_CAPABILITIES {
  USHORT             Size;
  USHORT             Version;
  ULONG              DeviceD1 : 1;
  ULONG              DeviceD2 : 1;
  ULONG              LockSupported : 1;
  ULONG              EjectSupported : 1;
  ULONG              Removable : 1;
  ULONG              DockDevice : 1;
  ULONG              UniqueID : 1;
  ULONG              SilentInstall : 1;
  ULONG              RawDeviceOK : 1;
  ULONG              SurpriseRemovalOK : 1;
  ULONG              WakeFromD0 : 1;
  ULONG              WakeFromD1 : 1;
  ULONG              WakeFromD2 : 1;
  ULONG              WakeFromD3 : 1;
  ULONG              HardwareDisabled : 1;
  ULONG              NonDynamic : 1;
  ULONG              WarmEjectSupported : 1;
  ULONG              NoDisplayInUI : 1;
  ULONG              Reserved1 : 1;
  ULONG              WakeFromInterrupt : 1;
  ULONG              SecureDevice : 1;
  ULONG              ChildOfVgaEnabledBridge : 1;
  ULONG              DecodeIoOnBoot : 1;
  ULONG              Reserved : 9;
  ULONG              Address;
  ULONG              UINumber;
  DEVICE_POWER_STATE* DeviceState;
  SYSTEM_POWER_STATE SystemWake;
  DEVICE_POWER_STATE DeviceWake;
  ULONG              D1Latency;
  ULONG              D2Latency;
  ULONG              D3Latency;
} DEVICE_CAPABILITIES, *PDEVICE_CAPABILITIES;

typedef struct _DEVICE_DESCRIPTION {
  ULONG            Version;
  BOOLEAN          Master;
  BOOLEAN          ScatterGather;
  BOOLEAN          DemandMode;
  BOOLEAN          AutoInitialize;
  BOOLEAN          Dma32BitAddresses;
  BOOLEAN          IgnoreCount;
  BOOLEAN          Reserved1;
  BOOLEAN          Dma64BitAddresses;
  ULONG            BusNumber;
  ULONG            DmaChannel;
  INTERFACE_TYPE   InterfaceType;
  DMA_WIDTH        DmaWidth;
  DMA_SPEED        DmaSpeed;
  ULONG            MaximumLength;
  ULONG            DmaPort;
  ULONG            DmaAddressWidth;
  ULONG            DmaControllerInstance;
  ULONG            DmaRequestLine;
  PHYSICAL_ADDRESS DeviceAddress;
} DEVICE_DESCRIPTION, *PDEVICE_DESCRIPTION;

typedef enum _DEVICE_DIRECTORY_TYPE {
  DeviceDirectoryData
} DEVICE_DIRECTORY_TYPE, *PDEVICE_DIRECTORY_TYPE;

typedef struct _DEVICE_FAULT_CONFIGURATION {
  PIOMMU_DEVICE_FAULT_HANDLER FaultHandler;
  PVOID                       FaultContext;
} DEVICE_FAULT_CONFIGURATION, *PDEVICE_FAULT_CONFIGURATION;

typedef enum _DEVICE_INSTALL_STATE {
  InstallStateInstalled,
  InstallStateNeedsReinstall,
  InstallStateFailedInstall,
  InstallStateFinishInstall
} DEVICE_INSTALL_STATE, *PDEVICE_INSTALL_STATE;

typedef struct _DEVICE_INTERFACE_CHANGE_NOTIFICATION {
  USHORT          Version;
  USHORT          Size;
  GUID            Event;
  GUID            InterfaceClassGuid;
  PUNICODE_STRING SymbolicLinkName;
} DEVICE_INTERFACE_CHANGE_NOTIFICATION, *PDEVICE_INTERFACE_CHANGE_NOTIFICATION;

typedef enum _DEVICE_REMOVAL_POLICY {
  RemovalPolicyExpectNoRemoval,
  RemovalPolicyExpectOrderlyRemoval,
  RemovalPolicyExpectSurpriseRemoval
} DEVICE_REMOVAL_POLICY, *PDEVICE_REMOVAL_POLICY;

typedef struct _DEVICE_RESET_INTERFACE_STANDARD {
  USHORT                                   Size;
  USHORT                                   Version;
  PVOID                                    Context;
  PINTERFACE_REFERENCE                     InterfaceReference;
  PINTERFACE_DEREFERENCE                   InterfaceDereference;
  PDEVICE_RESET_HANDLER                    DeviceReset;
  ULONG                                    SupportedResetTypes;
  PVOID                                    Reserved;
  PDEVICE_QUERY_BUS_SPECIFIC_RESET_HANDLER QueryBusSpecificResetInfo;
  PDEVICE_BUS_SPECIFIC_RESET_HANDLER       DeviceBusSpecificReset;
  PGET_DEVICE_RESET_STATUS                 GetDeviceResetStatus;
} DEVICE_RESET_INTERFACE_STANDARD, *PDEVICE_RESET_INTERFACE_STANDARD;

typedef union _DEVICE_RESET_STATUS_FLAGS {
  struct {
    ULONGLONG KeepStackReset : 1;
    ULONGLONG RecoveringFromBusError : 1;
    ULONGLONG Reserved : 62;
  } u;
  ULONGLONG AsUlonglong;
} DEVICE_RESET_STATUS_FLAGS, *PDEVICE_RESET_STATUS_FLAGS;

typedef enum _DEVICE_RESET_TYPE {
  FunctionLevelDeviceReset,
  PlatformLevelDeviceReset
} DEVICE_RESET_TYPE;

typedef enum {
  DeviceTextDescription,
  DeviceTextLocationInformation
} DEVICE_TEXT_TYPE, *PDEVICE_TEXT_TYPE;

typedef enum _DEVICE_USAGE_NOTIFICATION_TYPE {
  DeviceUsageTypeUndefined,
  DeviceUsageTypePaging,
  DeviceUsageTypeHibernation,
  DeviceUsageTypeDumpFile,
  DeviceUsageTypeBoot,
  DeviceUsageTypePostDisplay,
  DeviceUsageTypeGuestAssigned
} DEVICE_USAGE_NOTIFICATION_TYPE;

typedef enum _DEVICE_WAKE_DEPTH {
  DeviceWakeDepthNotWakeable,
  DeviceWakeDepthD0,
  DeviceWakeDepthD1,
  DeviceWakeDepthD2,
  DeviceWakeDepthD3hot,
  DeviceWakeDepthD3cold,
  DeviceWakeDepthMaximum
} DEVICE_WAKE_DEPTH, *PDEVICE_WAKE_DEPTH;

typedef struct _DMA_ADAPTER_INFO_CRASHDUMP {
  DEVICE_DESCRIPTION DeviceDescription;
  SIZE_T             DeviceIdSize;
  PVOID              DeviceId;
} DMA_ADAPTER_INFO_CRASHDUMP, *PDMA_ADAPTER_INFO_CRASHDUMP;

typedef struct _DMA_ADAPTER_INFO_V1 {
  ULONG ReadDmaCounterAvailable;
  ULONG ScatterGatherLimit;
  ULONG DmaAddressWidth;
  ULONG Flags;
  ULONG MinimumTransferUnit;
} DMA_ADAPTER_INFO_V1, *PDMA_ADAPTER_INFO_V1;

typedef struct _DMA_IOMMU_INTERFACE_V1 {
    PIOMMU_DOMAIN_CREATE              CreateDomain;
    PIOMMU_DOMAIN_DELETE              DeleteDomain;
    PIOMMU_DOMAIN_ATTACH_DEVICE       AttachDevice;
    PIOMMU_DOMAIN_DETACH_DEVICE       DetachDevice;
    PIOMMU_FLUSH_DOMAIN               FlushDomain;
    PIOMMU_FLUSH_DOMAIN_VA_LIST       FlushDomainByVaList;
    PIOMMU_QUERY_INPUT_MAPPINGS       QueryInputMappings;
    PIOMMU_MAP_LOGICAL_RANGE          MapLogicalRange;
    PIOMMU_UNMAP_LOGICAL_RANGE        UnmapLogicalRange;
    PIOMMU_MAP_IDENTITY_RANGE         MapIdentityRange;
    PIOMMU_UNMAP_IDENTITY_RANGE       UnmapIdentityRange;
    PIOMMU_SET_DEVICE_FAULT_REPORTING SetDeviceFaultReporting;
    PIOMMU_DOMAIN_CONFIGURE           ConfigureDomain;
} DMA_IOMMU_INTERFACE_V1, * PDMA_IOMMU_INTERFACE_V1;

typedef enum _DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_TYPE {
    CommonBufferConfigTypeLogicalAddressLimits,
    CommonBufferConfigTypeSubSection,
    CommonBufferConfigTypeHardwareAccessPermissions,
    CommonBufferConfigTypeMax
} DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_TYPE, * PDMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_TYPE;

typedef enum {
    DmaComplete,
    DmaAborted,
    DmaError,
    DmaCancelled
} DMA_COMPLETION_STATUS;


typedef enum _DOMAIN_CONFIGURATION_ARCH {
    DomainConfigurationArm64,
    DomainConfigurationX64,
    DomainConfigurationInvalid
} DOMAIN_CONFIGURATION_ARCH, * PDOMAIN_CONFIGURATION_ARCH;



typedef enum _DRIVER_REGKEY_TYPE {
    DriverRegKeyParameters,
    DriverRegKeyPersistentState,
    DriverRegKeySharedPersistentState
} DRIVER_REGKEY_TYPE, * PDRIVER_REGKEY_TYPE;



typedef enum _ENLISTMENT_INFORMATION_CLASS {
    EnlistmentBasicInformation,
    EnlistmentRecoveryInformation,
    EnlistmentCrmInformation
} ENLISTMENT_INFORMATION_CLASS;






typedef struct _DMA_IOMMU_INTERFACE_V2 {
    PIOMMU_DOMAIN_CREATE_EX                           CreateDomainEx;
    PIOMMU_DOMAIN_DELETE                              DeleteDomain;
    PIOMMU_DOMAIN_ATTACH_DEVICE_EX                    AttachDeviceEx;
    PIOMMU_DOMAIN_DETACH_DEVICE_EX                    DetachDeviceEx;
    PIOMMU_FLUSH_DOMAIN                               FlushDomain;
    PIOMMU_FLUSH_DOMAIN_VA_LIST                       FlushDomainByVaList;
    PIOMMU_QUERY_INPUT_MAPPINGS                       QueryInputMappings;
    PIOMMU_MAP_LOGICAL_RANGE_EX                       MapLogicalRangeEx;
    PIOMMU_UNMAP_LOGICAL_RANGE                        UnmapLogicalRange;
    PIOMMU_MAP_IDENTITY_RANGE_EX                      MapIdentityRangeEx;
    PIOMMU_UNMAP_IDENTITY_RANGE_EX                    UnmapIdentityRangeEx;
    PIOMMU_SET_DEVICE_FAULT_REPORTING_EX              SetDeviceFaultReportingEx;
    PIOMMU_DOMAIN_CONFIGURE                           ConfigureDomain;
    PIOMMU_DEVICE_QUERY_DOMAIN_TYPES                  QueryAvailableDomainTypes;
    PIOMMU_REGISTER_INTERFACE_STATE_CHANGE_CALLBACK   RegisterInterfaceStateChangeCallback;
    PIOMMU_UNREGISTER_INTERFACE_STATE_CHANGE_CALLBACK UnregisterInterfaceStateChangeCallback;
    PIOMMU_RESERVE_LOGICAL_ADDRESS_RANGE              ReserveLogicalAddressRange;
    PIOMMU_FREE_RESERVED_LOGICAL_ADDRESS_RANGE        FreeReservedLogicalAddressRange;
    PIOMMU_MAP_RESERVED_LOGICAL_RANGE                 MapReservedLogicalRange;
    PIOMMU_UNMAP_RESERVED_LOGICAL_RANGE               UnmapReservedLogicalRange;
    PIOMMU_DEVICE_CREATE                              CreateDevice;
    PIOMMU_DEVICE_DELETE                              DeleteDevice;
} DMA_IOMMU_INTERFACE_V2, * PDMA_IOMMU_INTERFACE_V2;


typedef struct _DMA_ADAPTER_INFO {
    ULONG Version;
    union {
        DMA_ADAPTER_INFO_V1        V1;
        DMA_ADAPTER_INFO_CRASHDUMP Crashdump;
    };
} DMA_ADAPTER_INFO, * PDMA_ADAPTER_INFO;




typedef struct _DMA_IOMMU_INTERFACE {
  ULONG                             Version;
  PIOMMU_DOMAIN_CREATE              CreateDomain;
  PIOMMU_DOMAIN_DELETE              DeleteDomain;
  PIOMMU_DOMAIN_ATTACH_DEVICE       AttachDevice;
  PIOMMU_DOMAIN_DETACH_DEVICE       DetachDevice;
  PIOMMU_FLUSH_DOMAIN               FlushDomain;
  PIOMMU_FLUSH_DOMAIN_VA_LIST       FlushDomainByVaList;
  PIOMMU_QUERY_INPUT_MAPPINGS       QueryInputMappings;
  PIOMMU_MAP_LOGICAL_RANGE          MapLogicalRange;
  PIOMMU_UNMAP_LOGICAL_RANGE        UnmapLogicalRange;
  PIOMMU_MAP_IDENTITY_RANGE         MapIdentityRange;
  PIOMMU_UNMAP_IDENTITY_RANGE       UnmapIdentityRange;
  PIOMMU_SET_DEVICE_FAULT_REPORTING SetDeviceFaultReporting;
  PIOMMU_DOMAIN_CONFIGURE           ConfigureDomain;
} DMA_IOMMU_INTERFACE, *PDMA_IOMMU_INTERFACE;

typedef struct _DMA_TRANSFER_INFO_V1 {
    ULONG MapRegisterCount;
    ULONG ScatterGatherElementCount;
    ULONG ScatterGatherListSize;
} DMA_TRANSFER_INFO_V1, * PDMA_TRANSFER_INFO_V1;

typedef struct _DMA_TRANSFER_INFO_V2 {
    ULONG MapRegisterCount;
    ULONG ScatterGatherElementCount;
    ULONG ScatterGatherListSize;
    ULONG LogicalPageCount;
} DMA_TRANSFER_INFO_V2, * PDMA_TRANSFER_INFO_V2;


typedef struct _DMA_IOMMU_INTERFACE_EX {
  SIZE_T Size;
  ULONG  Version;
  union {
    DMA_IOMMU_INTERFACE_V1 V1;
    DMA_IOMMU_INTERFACE_V2 V2;
    DMA_IOMMU_INTERFACE_V3 V3;
  };
} DMA_IOMMU_INTERFACE_EX, *PDMA_IOMMU_INTERFACE_EX;

typedef struct _DMA_TRANSFER_INFO {
  ULONG Version;
  union {
    DMA_TRANSFER_INFO_V1 V1;
    DMA_TRANSFER_INFO_V2 V2;
  };
} DMA_TRANSFER_INFO, *PDMA_TRANSFER_INFO;

typedef struct _DOMAIN_CONFIGURATION_ARM64 {
  PHYSICAL_ADDRESS Ttbr0;
  PHYSICAL_ADDRESS Ttbr1;
  ULONG            Mair0;
  ULONG            Mair1;
  UCHAR            InputSize0;
  UCHAR            InputSize1;
  BOOLEAN          CoherentTableWalks;
  BOOLEAN          TranslationEnabled;
} DOMAIN_CONFIGURATION_ARM64, *PDOMAIN_CONFIGURATION_ARM64;

typedef struct _DOMAIN_CONFIGURATION_X64 {
  PHYSICAL_ADDRESS FirstLevelPageTableRoot;
  BOOLEAN          TranslationEnabled;
} DOMAIN_CONFIGURATION_X64, *PDOMAIN_CONFIGURATION_X64;

typedef struct _ENLISTMENT_BASIC_INFORMATION {
  GUID EnlistmentId;
  GUID TransactionId;
  GUID ResourceManagerId;
} ENLISTMENT_BASIC_INFORMATION, *PENLISTMENT_BASIC_INFORMATION;



typedef struct _DOMAIN_CONFIGURATION {
    DOMAIN_CONFIGURATION_ARCH Type;
    union {
        DOMAIN_CONFIGURATION_ARM64 Arm64;
        DOMAIN_CONFIGURATION_X64   X64;
    };
} DOMAIN_CONFIGURATION, * PDOMAIN_CONFIGURATION;


typedef struct _EXT_DELETE_PARAMETERS {
    ULONG                Version;
    ULONG                Reserved;
    PEXT_DELETE_CALLBACK DeleteCallback;
    PVOID                DeleteContext;
} EXT_DELETE_PARAMETERS, * PEXT_DELETE_PARAMETERS;

typedef struct _EXT_SET_PARAMETERS_V0 {
    ULONG    Version;
    ULONG    Reserved;
    LONGLONG NoWakeTolerance;
} EXT_SET_PARAMETERS, * PEXT_SET_PARAMETERS;

typedef struct _EXTENDED_CREATE_INFORMATION {
    LONGLONG ExtendedCreateFlags;
    PVOID    EaBuffer;
    ULONG    EaLength;
} EXTENDED_CREATE_INFORMATION, * PEXTENDED_CREATE_INFORMATION;

typedef struct _EXTENDED_CREATE_INFORMATION_32 {
    LONGLONG ExtendedCreateFlags;
    POINTER_32* EaBuffer;
    ULONG    EaLength;
} EXTENDED_CREATE_INFORMATION_32, * PEXTENDED_CREATE_INFORMATION_32;


NTSTATUS* EtwSetInformation(
             REGHANDLE        RegHandle,
             EVENT_INFO_CLASS InformationClass,
   PVOID            EventInformation,
             ULONG            InformationLength
);

void ExAcquireFastMutex(
  PFAST_MUTEX FastMutex
);

void ExAcquireFastMutexUnsafe(
  PFAST_MUTEX FastMutex
);

//void ExAcquirePushLockExclusive(
//   Lock
//);

//void ExAcquirePushLockShared(
//   Lock
//);

BOOLEAN ExAcquireResourceExclusiveLite(
   PERESOURCE Resource,
        BOOLEAN    Wait
);

BOOLEAN ExAcquireResourceSharedLite(
   PERESOURCE Resource,
        BOOLEAN    Wait
);

BOOLEAN ExAcquireRundownProtection(
   PEX_RUNDOWN_REF RunRef
);

BOOLEAN ExAcquireRundownProtection(
   PEX_RUNDOWN_REF RunRef
);

BOOLEAN ExAcquireRundownProtection(
   PEX_RUNDOWN_REF RunRef
);

BOOLEAN ExAcquireRundownProtectionEx(
   PEX_RUNDOWN_REF RunRef,
        ULONG           Count
);

BOOLEAN ExAcquireSharedStarveExclusive(
   PERESOURCE Resource,
        BOOLEAN    Wait
);

BOOLEAN ExAcquireSharedWaitForExclusive(
   PERESOURCE Resource,
        BOOLEAN    Wait
);

KIRQL ExAcquireSpinLockExclusive(
  PEX_SPIN_LOCK SpinLock
);

void ExAcquireSpinLockExclusiveAtDpcLevel(
   PEX_SPIN_LOCK SpinLock
);

KIRQL ExAcquireSpinLockShared(
   PEX_SPIN_LOCK SpinLock
);

void ExAcquireSpinLockSharedAtDpcLevel(
  PEX_SPIN_LOCK SpinLock
);

PEX_RUNDOWN_REF_CACHE_AWARE ExAllocateCacheAwareRundownProtection(
   POOL_TYPE PoolType,
   ULONG PoolTag
);

PVOID ExAllocateFromLookasideListEx(
   PLOOKASIDE_LIST_EX Lookaside
);

PVOID ExAllocateFromNPagedLookasideList(
   PNPAGED_LOOKASIDE_LIST Lookaside
);

PVOID ExAllocateFromPagedLookasideList(
   PPAGED_LOOKASIDE_LIST Lookaside
);

PVOID ExAllocateFromPagedLookasideList(
   PPAGED_LOOKASIDE_LIST Lookaside
);

PVOID ExAllocatePool2(
  POOL_FLAGS Flags,
  SIZE_T     NumberOfBytes,
  ULONG      Tag
);

PVOID ExAllocatePool3(
  POOL_FLAGS                Flags,
  SIZE_T                    NumberOfBytes,
  ULONG                     Tag,
  PCPOOL_EXTENDED_PARAMETER ExtendedParameters,
  ULONG                     ExtendedParametersCount
);

PVOID ExAllocatePoolPriorityUninitialized(
  POOL_TYPE PoolType,
  SIZE_T                                         NumberOfBytes,
  ULONG                                          Tag,
  EX_POOL_PRIORITY                               Priority
);

PVOID ExAllocatePoolPriorityZero(
  POOL_TYPE PoolType,
  SIZE_T                                         NumberOfBytes,
  ULONG                                          Tag,
  EX_POOL_PRIORITY                               Priority
);

PVOID ExAllocatePoolQuotaUninitialized(
  POOL_TYPE PoolType,
  SIZE_T                                         NumberOfBytes,
  ULONG                                          Tag
);

PVOID ExAllocatePoolQuotaZero(
  POOL_TYPE PoolType,
  SIZE_T                                         NumberOfBytes,
  ULONG                                          Tag
);

PVOID ExAllocatePoolUninitialized(
  POOL_TYPE PoolType,
  SIZE_T                                         NumberOfBytes,
  ULONG                                          Tag
);

PVOID ExAllocatePoolWithQuota(
   POOL_TYPE PoolType,
   SIZE_T                                         NumberOfBytes
);

PVOID ExAllocatePoolWithQuotaTag(
   POOL_TYPE PoolType,
   SIZE_T                                         NumberOfBytes,
   ULONG                                          Tag
);

PVOID ExAllocatePoolWithTag(
   POOL_TYPE PoolType,
   SIZE_T                                         NumberOfBytes,
   ULONG                                          Tag
);

PVOID ExAllocatePoolWithTagPriority(
   POOL_TYPE        PoolType,
   SIZE_T                                                NumberOfBytes,
   ULONG                                                 Tag,
   EX_POOL_PRIORITY Priority
);

PVOID ExAllocatePoolZero(
  POOL_TYPE PoolType,
  SIZE_T                                         NumberOfBytes,
  ULONG                                          Tag
);

PEX_TIMER ExAllocateTimer(
   PEXT_CALLBACK Callback,
   PVOID         CallbackContext,
             ULONG         Attributes
);

BOOLEAN ExCancelTimer(
        PEX_TIMER              Timer,
   PEXT_CANCEL_PARAMETERS Parameters
);

void ExConvertExclusiveToSharedLite(
   PERESOURCE Resource
);

NTSTATUS ExCreateCallback(
   PCALLBACK_OBJECT   *CallbackObject,
    POBJECT_ATTRIBUTES ObjectAttributes,
    BOOLEAN            Create,
    BOOLEAN            AllowMultipleCallbacks
);

NTSTATUS ExCreatePool(
  ULONG                       Flags,
  ULONG_PTR                   Tag,
  POOL_CREATE_EXTENDED_PARAMS *Params,
  HANDLE                      *PoolHandle
);

void ExDeleteLookasideListEx(
   PLOOKASIDE_LIST_EX Lookaside
);

void ExDeleteNPagedLookasideList(
   PNPAGED_LOOKASIDE_LIST Lookaside
);

void ExDeletePagedLookasideList(
   PPAGED_LOOKASIDE_LIST Lookaside
);

NTSTATUS ExDeleteResourceLite(
   PERESOURCE Resource
);

BOOLEAN ExDeleteTimer(
   PEX_TIMER              Timer,
   BOOLEAN                Cancel,
   BOOLEAN                Wait,
   PEXT_DELETE_PARAMETERS Parameters
);

void ExDestroyPool(
  HANDLE PoolHandle
);

PVOID ExEnterCriticalRegionAndAcquireResourceExclusive(
  PERESOURCE Resource
);

void ExFlushLookasideListEx(
   PLOOKASIDE_LIST_EX Lookaside
);

void ExFreeCacheAwareRundownProtection(
   PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware
);

void ExFreePool(
   PVOID P
);


void ExFreePool2(
  PVOID                     P,
  ULONG                     Tag,
  PCPOOL_EXTENDED_PARAMETER ExtendedParameters,
  ULONG                     ExtendedParametersCount
);

void ExFreePoolWithTag(
   PVOID P,
   ULONG Tag
);

void ExFreeToLookasideListEx(
   PLOOKASIDE_LIST_EX Lookaside,
        PVOID              Entry
);

void ExFreeToNPagedLookasideList(
   PNPAGED_LOOKASIDE_LIST Lookaside,
        PVOID                  Entry
);

void ExFreeToPagedLookasideList(
   PPAGED_LOOKASIDE_LIST Lookaside,
        PVOID                 Entry
);

ULONG ExGetExclusiveWaiterCount(
   PERESOURCE Resource
);

NTSTATUS ExGetFirmwareEnvironmentVariable(
              PUNICODE_STRING VariableName,
              LPGUID          VendorGuid,
   PVOID           Value,
         PULONG          ValueLength,
   PULONG          Attributes
);

FIRMWARE_TYPE ExGetFirmwareType();

KPROCESSOR_MODE ExGetPreviousMode();

ULONG ExGetSharedWaiterCount(
   PERESOURCE Resource
);

void ExInitializeDeleteTimerParameters(
  PEXT_DELETE_PARAMETERS Parameters
);

NTSTATUS ExInitializeDeviceAts(
  _DEVICE_OBJECT *PhysicalDeviceObject,
  ULONG          Flags
);

void ExInitializeDriverRuntime(
  ULONG RuntimeFlags
);

void ExInitializeFastMutex(
   PFAST_MUTEX FastMutex
);

NTSTATUS ExInitializeLookasideListEx(
            PLOOKASIDE_LIST_EX    Lookaside,
   PALLOCATE_FUNCTION_EX Allocate,
   PFREE_FUNCTION_EX     Free,
             POOL_TYPE             PoolType,
             ULONG                 Flags,
             SIZE_T                Size,
             ULONG                 Tag,
             USHORT                Depth
);

void ExInitializeNPagedLookasideList(
            PNPAGED_LOOKASIDE_LIST Lookaside,
   PALLOCATE_FUNCTION     Allocate,
   PFREE_FUNCTION         Free,
             ULONG                  Flags,
             SIZE_T                 Size,
             ULONG                  Tag,
             USHORT                 Depth
);

void ExInitializePagedLookasideList(
            PPAGED_LOOKASIDE_LIST Lookaside,
   PALLOCATE_FUNCTION    Allocate,
   PFREE_FUNCTION        Free,
             ULONG                 Flags,
             SIZE_T                Size,
             ULONG                 Tag,
             USHORT                Depth
);

void ExInitializePushLock(
   PEX_PUSH_LOCK PushLock
);

NTSTATUS ExInitializeResourceLite(
   PERESOURCE Resource
);

void ExInitializeRundownProtection(
   PEX_RUNDOWN_REF RunRef
);

void ExInitializeRundownProtectionCacheAware(
   PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware,
    SIZE_T                      RunRefSize
);

void ExInitializeSetTimerParameters(
   PEXT_SET_PARAMETERS Parameters
);

LARGE_INTEGER ExInterlockedAddLargeInteger(
   PLARGE_INTEGER Addend,
        LARGE_INTEGER  Increment,
   PKSPIN_LOCK    Lock
);

//void ExInterlockedAddLargeStatistic(
  //  Addend,
  //  Increment
//);

ULONG ExInterlockedAddUlong(
   PULONG      Addend,
        ULONG       Increment,
   PKSPIN_LOCK Lock
);

//void ExInterlockedCompareExchange64(
//    Destination,
//         Exchange,
//             Comperand,
//         Lock
//);

NTKERNELAPI
PSLIST_ENTRY
ExInterlockedFlushSList (
     PSLIST_HEADER ListHead
    );

PLIST_ENTRY ExInterlockedInsertHeadList(
   PLIST_ENTRY                  ListHead,
   PLIST_ENTRY ListEntry,
   PKSPIN_LOCK                  Lock
);

PLIST_ENTRY ExInterlockedInsertTailList(
   PLIST_ENTRY                  ListHead,
   PLIST_ENTRY ListEntry,
   PKSPIN_LOCK                  Lock
);

PSINGLE_LIST_ENTRY ExInterlockedPopEntryList(
   PSINGLE_LIST_ENTRY ListHead,
   PKSPIN_LOCK        Lock
);

NTKERNELAPI
PSLIST_ENTRY
ExInterlockedPopEntrySList (
     PSLIST_HEADER ListHead,
     PKSPIN_LOCK Lock
    );

PSINGLE_LIST_ENTRY ExInterlockedPushEntryList(
   PSINGLE_LIST_ENTRY                  ListHead,
   PSINGLE_LIST_ENTRY ListEntry,
   PKSPIN_LOCK                         Lock
);

NTKERNELAPI
PSLIST_ENTRY
ExInterlockedPushEntrySList (
     PSLIST_HEADER ListHead,
     PSLIST_ENTRY ListEntry,
     PKSPIN_LOCK Lock
    );

PLIST_ENTRY ExInterlockedRemoveHeadList(
   PLIST_ENTRY ListHead,
   PKSPIN_LOCK Lock
);

BOOLEAN ExIsProcessorFeaturePresent(
   ULONG ProcessorFeature
);

BOOLEAN ExIsResourceAcquiredExclusiveLite(
   PERESOURCE Resource
);

ULONG ExIsResourceAcquiredSharedLite(
   PERESOURCE Resource
);

BOOLEAN ExIsSoftBoot();

void ExLocalTimeToSystemTime(
    PLARGE_INTEGER LocalTime,
   PLARGE_INTEGER SystemTime
);

void ExNotifyCallback(
             PVOID CallbackObject,
   PVOID Argument1,
   PVOID Argument2
);

PSLIST_ENTRY ExpInterlockedPopEntrySList(
  PSLIST_HEADER ListHead
);

PSLIST_ENTRY ExpInterlockedPushEntrySList(
  PSLIST_HEADER                 ListHead,
  PSLIST_ENTRY ListEntry
);

USHORT ExQueryDepthSList(
   PSLIST_HEADER SListHead
);

void ExQueryTimerResolution(
   PULONG MaximumTime,
   PULONG MinimumTime,
   PULONG CurrentTime
);

void ExRaiseStatus(
   NTSTATUS Status
);

PVOID ExRegisterCallback(
        PCALLBACK_OBJECT   CallbackObject,
             PCALLBACK_FUNCTION CallbackFunction,
   PVOID              CallbackContext
);

NTSTATUS ExReinitializeResourceLite(
   PERESOURCE Resource
);

void ExReInitializeRundownProtection(
   PEX_RUNDOWN_REF RunRef
);

void ExReInitializeRundownProtectionCacheAware(
   PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware
);

void ExReleaseFastMutex(
  PFAST_MUTEX FastMutex
);

void ExReleaseFastMutexUnsafe(
  PFAST_MUTEX FastMutex
);

//void ExReleasePushLockExclusive(
//   Lock
//);

//void ExReleasePushLockShared(
//   Lock
//);

void ExReleaseResourceAndLeaveCriticalRegion(
  PERESOURCE Resource
);

void ExReleaseResourceForThreadLite(
   PERESOURCE       Resource,
        ERESOURCE_THREAD ResourceThreadId
);

void ExReleaseResourceLite(
   PERESOURCE Resource
);

void ExReleaseRundownProtection(
   PEX_RUNDOWN_REF RunRef
);

void ExReleaseRundownProtectionCacheAware(
   PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware
);

void ExReleaseRundownProtectionCacheAwareEx(
   PEX_RUNDOWN_REF_CACHE_AWARE RunRef,
        ULONG                       Count
);

void ExReleaseRundownProtectionEx(
   PEX_RUNDOWN_REF RunRef,
        ULONG           Count
);

void ExReleaseSpinLockExclusive(
   PEX_SPIN_LOCK SpinLock,
        KIRQL         OldIrql
);

void ExReleaseSpinLockExclusiveFromDpcLevel(
  PEX_SPIN_LOCK SpinLock
);

void ExReleaseSpinLockShared(
   PEX_SPIN_LOCK SpinLock,
        KIRQL         OldIrql
);

void ExReleaseSpinLockSharedFromDpcLevel(
  PEX_SPIN_LOCK SpinLock
);

void ExRundownCompleted(
   PEX_RUNDOWN_REF RunRef
);

void ExRundownCompletedCacheAware(
   PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware
);

NTSTATUS ExSecurePoolUpdate(
   HANDLE    SecurePoolHandle,
   ULONG     Tag,
   PVOID     Allocation,
   ULONG_PTR Cookie,
   SIZE_T    Offset,
   SIZE_T    Size,
   PVOID     Buffer
);

LOGICAL ExSecurePoolValidate(
   HANDLE    SecurePoolHandle,
   ULONG     Tag,
   PVOID     Allocation,
   ULONG_PTR Cookie
);

NTSTATUS ExSetFirmwareEnvironmentVariable(
   PUNICODE_STRING VariableName,
   LPGUID          VendorGuid,
   PVOID           Value,
   ULONG           ValueLength,
   ULONG           Attributes
);

void ExSetResourceOwnerPointer(
   PERESOURCE Resource,
        PVOID      OwnerPointer
);

void ExSetResourceOwnerPointerEx(
   PERESOURCE Resource,
        PVOID      OwnerPointer,
        ULONG      Flags
);

BOOLEAN ExSetTimer(
             PEX_TIMER           Timer,
             LONGLONG            DueTime,
             LONGLONG            Period,
   PEXT_SET_PARAMETERS Parameters
);


ULONG ExSetTimerResolution(
   ULONG   DesiredTime,
   BOOLEAN SetResolution
);

SIZE_T ExSizeOfRundownProtectionCacheAware();

void ExSystemTimeToLocalTime(
    PLARGE_INTEGER SystemTime,
   PLARGE_INTEGER LocalTime
);

LOGICAL ExTryConvertSharedSpinLockExclusive(
   PEX_SPIN_LOCK SpinLock
);

BOOLEAN ExTryToAcquireFastMutex(
  PFAST_MUTEX FastMutex
);

void ExUnregisterCallback(
   PVOID CallbackRegistration
);

void ExWaitForRundownProtectionRelease(
   PEX_RUNDOWN_REF RunRef
);

void ExWaitForRundownProtectionReleaseCacheAware(
   PEX_RUNDOWN_REF_CACHE_AWARE RunRef
);

//void FIELD_OFFSET(
//    type,
//    field
//);


//void IMAGE_POLICY_OVERRIDE(
//   _PolicyId_
//);

void InitializeListHead(
   PLIST_ENTRY ListHead
);


//void InitializeSListHead(
//   PSLIST_HEADER SListHead
//);

typedef struct _INPUT_MAPPING_ELEMENT {
  ULONG InputMappingId;
} INPUT_MAPPING_ELEMENT, *PINPUT_MAPPING_ELEMENT;

void InsertHeadList(
   PLIST_ENTRY                  ListHead,
   PLIST_ENTRY Entry
);

void InsertTailList(
   PLIST_ENTRY                  ListHead,
   PLIST_ENTRY Entry
);


LONG InterlockedAnd(
   LONG volatile *Destination,
        LONG          Value
);

LONG InterlockedCompareExchange(
   LONG volatile *Destination,
        LONG          ExChange,
        LONG          Comperand
);

PVOID InterlockedCompareExchangePointer(
   PVOID volatile *Destination,
        PVOID          Exchange,
        PVOID          Comperand
);

LONG  InterlockedDecrement(
   LONG volatile *Addend
);

LONG InterlockedExchange(
   LONG volatile *Target,
        LONG          Value
);

LONG InterlockedExchangeAdd(
   LONG volatile *Addend,
        LONG          Value
);

PVOID InterlockedExchangePointer(
        PVOID volatile *Target,
   PVOID          Value
);

LONG  InterlockedIncrement(
   LONG volatile *Addend
);

LONG InterlockedOr(
   LONG volatile *Destination,
        LONG          Value
);

LONG InterlockedXor(
   LONG volatile *Destination,
        LONG          Value
);


typedef enum _IO_CONTAINER_INFORMATION_CLASS {
  IoSessionStateInformation,
  IoMaxContainerInformationClass
} IO_CONTAINER_INFORMATION_CLASS;

typedef enum _IO_CONTAINER_NOTIFICATION_CLASS {
  IoSessionStateNotification,
  IoMaxContainerNotificationClass
} IO_CONTAINER_NOTIFICATION_CLASS;


typedef struct _IO_ERROR_LOG_PACKET {
  UCHAR         MajorFunctionCode;
  UCHAR         RetryCount;
  USHORT        DumpDataSize;
  USHORT        NumberOfStrings;
  USHORT        StringOffset;
  USHORT        EventCategory;
  NTSTATUS      ErrorCode;
  ULONG         UniqueErrorValue;
  NTSTATUS      FinalStatus;
  ULONG         SequenceNumber;
  ULONG         IoControlCode;
  LARGE_INTEGER DeviceOffset;
  ULONG         DumpData[1];
} IO_ERROR_LOG_PACKET, *PIO_ERROR_LOG_PACKET;

#define DISPATCH_LENGTH 106

typedef struct _KINTERRUPT {
    CSHORT Type;
    CSHORT Size;
    LIST_ENTRY InterruptListEntry;
    KSPIN_LOCK SpinLock;
    PKSERVICE_ROUTINE ServiceRoutine;
    PVOID ServiceContext;
    KIRQL Irql;
    KIRQL SynchronizeIrql;
    BOOLEAN FloatingSave;
    BOOLEAN Connected;
    KINTERRUPT_MODE Mode;
    ULONG Vector;
    KAFFINITY ProcessorEnableMask;
    BOOLEAN ShareVector;
    BOOLEAN IrqlFlags;
    BOOLEAN IrqlRequested;
    BOOLEAN Reserved;
    PKINTERRUPT_ROUTINE DispatchAddress;
    ULONG DispatchCode[DISPATCH_LENGTH];
} KINTERRUPT, *PKINTERRUPT;



typedef struct _IO_INTERRUPT_MESSAGE_INFO_ENTRY {
  PHYSICAL_ADDRESS    MessageAddress;
  KAFFINITY           TargetProcessorSet;
  PKINTERRUPT         InterruptObject;
  ULONG               MessageData;
  ULONG               Vector;
  KIRQL               Irql;
  KINTERRUPT_MODE     Mode;
  KINTERRUPT_POLARITY Polarity;
} IO_INTERRUPT_MESSAGE_INFO_ENTRY, *PIO_INTERRUPT_MESSAGE_INFO_ENTRY;

typedef struct _IO_INTERRUPT_MESSAGE_INFO {
    KIRQL                           UnifiedIrql;
    ULONG                           MessageCount;
    IO_INTERRUPT_MESSAGE_INFO_ENTRY MessageInfo[1];
} IO_INTERRUPT_MESSAGE_INFO, * PIO_INTERRUPT_MESSAGE_INFO;

typedef struct _IO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS {
  ULONG Version;
  union {
    PVOID                      Generic;
    PKINTERRUPT                InterruptObject;
    PIO_INTERRUPT_MESSAGE_INFO InterruptMessageTable;
  } ConnectionContext;
} IO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS, *PIO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS;

typedef struct _IO_DISCONNECT_INTERRUPT_PARAMETERS {
    ULONG Version;
    union {
        PVOID                      Generic;
        PKINTERRUPT                InterruptObject;
        PIO_INTERRUPT_MESSAGE_INFO InterruptMessageTable;
    } ConnectionContext;
} IO_DISCONNECT_INTERRUPT_PARAMETERS, * PIO_DISCONNECT_INTERRUPT_PARAMETERS;

typedef struct _IO_SECURITY_CONTEXT {
  PSECURITY_QUALITY_OF_SERVICE SecurityQos;
  PACCESS_STATE                AccessState;
  ACCESS_MASK                  DesiredAccess;
  ULONG                        FullCreateOptions;
} IO_SECURITY_CONTEXT, *PIO_SECURITY_CONTEXT;

typedef struct _IO_SESSION_CONNECT_INFO {
  ULONG   SessionId;
  BOOLEAN LocalSession;
} IO_SESSION_CONNECT_INFO, *PIO_SESSION_CONNECT_INFO;

typedef enum _IO_SESSION_EVENT {
  IoSessionEventIgnore,
  IoSessionEventCreated,
  IoSessionEventTerminated,
  IoSessionEventConnected,
  IoSessionEventDisconnected,
  IoSessionEventLogon,
  IoSessionEventLogoff,
  IoSessionEventMax
} IO_SESSION_EVENT, *PIO_SESSION_EVENT;


typedef enum _IO_SESSION_STATE {
  IoSessionStateCreated,
  IoSessionStateInitialized,
  IoSessionStateConnected,
  IoSessionStateDisconnected,
  IoSessionStateDisconnectedLoggedOn,
  IoSessionStateLoggedOn,
  IoSessionStateLoggedOff,
  IoSessionStateTerminated,
  IoSessionStateMax
} IO_SESSION_STATE, *PIO_SESSION_STATE;

typedef struct _IO_SESSION_STATE_INFORMATION {
  ULONG            SessionId;
  IO_SESSION_STATE SessionState;
  BOOLEAN          LocalSession;
} IO_SESSION_STATE_INFORMATION, *PIO_SESSION_STATE_INFORMATION;

typedef struct _IO_SESSION_STATE_NOTIFICATION {
  ULONG Size;
  ULONG Flags;
  PVOID IoObject;
  ULONG EventMask;
  PVOID Context;
} IO_SESSION_STATE_NOTIFICATION, *PIO_SESSION_STATE_NOTIFICATION;

typedef struct _IO_STACK_LOCATION {
  UCHAR                  MajorFunction;
  UCHAR                  MinorFunction;
  UCHAR                  Flags;
  UCHAR                  Control;
  union {
    struct {
      PIO_SECURITY_CONTEXT     SecurityContext;
      ULONG                    Options;
      USHORT FileAttributes;
      USHORT                   ShareAccess;
      ULONG EaLength;
    } Create;
    struct {
      PIO_SECURITY_CONTEXT          SecurityContext;
      ULONG                         Options;
      USHORT Reserved;
      USHORT                        ShareAccess;
      PNAMED_PIPE_CREATE_PARAMETERS Parameters;
    } CreatePipe;
    struct {
      PIO_SECURITY_CONTEXT        SecurityContext;
      ULONG                       Options;
      USHORT Reserved;
      USHORT                      ShareAccess;
      PMAILSLOT_CREATE_PARAMETERS Parameters;
    } CreateMailslot;
    struct {
      ULONG                   Length;
      ULONG  Key;
      ULONG                   Flags;
      LARGE_INTEGER           ByteOffset;
    } Read;
    struct {
      ULONG                   Length;
      ULONG  Key;
      ULONG                   Flags;
      LARGE_INTEGER           ByteOffset;
    } Write;
    struct {
      ULONG                   Length;
      PUNICODE_STRING         FileName;
      FILE_INFORMATION_CLASS  FileInformationClass;
      ULONG FileIndex;
    } QueryDirectory;
    struct {
      ULONG                   Length;
      ULONG  CompletionFilter;
    } NotifyDirectory;
    struct {
      ULONG                                                Length;
      ULONG                               CompletionFilter;
      DIRECTORY_NOTIFY_INFORMATION_CLASS  DirectoryNotifyInformationClass;
    } NotifyDirectoryEx;
    struct {
      ULONG                                    Length;
      FILE_INFORMATION_CLASS  FileInformationClass;
    } QueryFile;
    struct {
      ULONG                                    Length;
      FILE_INFORMATION_CLASS  FileInformationClass;
      PFILE_OBJECT                             FileObject;
      union {
        struct {
          BOOLEAN ReplaceIfExists;
          BOOLEAN AdvanceOnly;
        };
        ULONG  ClusterCount;
        HANDLE DeleteHandle;
      };
    } SetFile;
    struct {
      ULONG                   Length;
      PVOID                   EaList;
      ULONG                   EaListLength;
      ULONG  EaIndex;
    } QueryEa;
    struct {
      ULONG Length;
    } SetEa;
    struct {
      ULONG                                  Length;
      FS_INFORMATION_CLASS  FsInformationClass;
    } QueryVolume;
    struct {
      ULONG                                  Length;
      FS_INFORMATION_CLASS  FsInformationClass;
    } SetVolume;
    struct {
      ULONG                   OutputBufferLength;
      ULONG  InputBufferLength;
      ULONG  FsControlCode;
      PVOID                   Type3InputBuffer;
    } FileSystemControl;
    struct {
      PLARGE_INTEGER          Length;
      ULONG  Key;
      LARGE_INTEGER           ByteOffset;
    } LockControl;
    struct {
      ULONG                   OutputBufferLength;
      ULONG  InputBufferLength;
      ULONG  IoControlCode;
      PVOID                   Type3InputBuffer;
    } DeviceIoControl;
    struct {
      SECURITY_INFORMATION    SecurityInformation;
      ULONG  Length;
    } QuerySecurity;
    struct {
      SECURITY_INFORMATION SecurityInformation;
      PSECURITY_DESCRIPTOR SecurityDescriptor;
    } SetSecurity;
    struct {
      PVPB           Vpb;
      PDEVICE_OBJECT DeviceObject;
      ULONG          OutputBufferLength;
    } MountVolume;
    struct {
      PVPB           Vpb;
      PDEVICE_OBJECT DeviceObject;
    } VerifyVolume;
    struct {
      struct _SCSI_REQUEST_BLOCK *Srb;
    } Scsi;
    struct {
      ULONG                       Length;
      PSID                        StartSid;
      PFILE_GET_QUOTA_INFORMATION SidList;
      ULONG                       SidListLength;
    } QueryQuota;
    struct {
      ULONG Length;
    } SetQuota;
    struct {
      DEVICE_RELATION_TYPE Type;
    } QueryDeviceRelations;
    struct {
      const GUID *InterfaceType;
      USHORT     Size;
      USHORT     Version;
      PINTERFACE Interface;
      PVOID      InterfaceSpecificData;
    } QueryInterface;
    struct {
      PDEVICE_CAPABILITIES Capabilities;
    } DeviceCapabilities;
    struct {
      PIO_RESOURCE_REQUIREMENTS_LIST IoResourceRequirementList;
    } FilterResourceRequirements;
    struct {
      ULONG                   WhichSpace;
      PVOID                   Buffer;
      ULONG                   Offset;
      ULONG  Length;
    } ReadWriteConfig;
    struct {
      BOOLEAN Lock;
    } SetLock;
    struct {
      BUS_QUERY_ID_TYPE IdType;
    } QueryId;
    struct {
      DEVICE_TEXT_TYPE       DeviceTextType;
      LCID  LocaleId;
    } QueryDeviceText;
    struct {
      BOOLEAN                                          InPath;
      BOOLEAN                                          Reserved[3];
      DEVICE_USAGE_NOTIFICATION_TYPE  Type;
    } UsageNotification;
    struct {
      SYSTEM_POWER_STATE PowerState;
    } WaitWake;
    struct {
      PPOWER_SEQUENCE PowerSequence;
    } PowerSequence;
//#if ...
    struct {
      union {
        ULONG                      SystemContext;
        SYSTEM_POWER_STATE_CONTEXT SystemPowerStateContext;
      };
      POWER_STATE_TYPE  Type;
      POWER_STATE       State;
      POWER_ACTION      ShutdownType;
    } Power;
//#else
//    struct {
//      ULONG                              SystemContext;
//      POWER_STATE_TYPE  Type;
//      POWER_STATE       State;
//      POWER_ACTION      ShutdownType;
//    } Power;
//#endif
    struct {
      PCM_RESOURCE_LIST AllocatedResources;
      PCM_RESOURCE_LIST AllocatedResourcesTranslated;
    } StartDevice;
    struct {
      ULONG_PTR ProviderId;
      PVOID     DataPath;
      ULONG     BufferSize;
      PVOID     Buffer;
    } WMI;
    struct {
      PVOID Argument1;
      PVOID Argument2;
      PVOID Argument3;
      PVOID Argument4;
    } Others;
  } Parameters;
  PDEVICE_OBJECT         DeviceObject;
  PFILE_OBJECT           FileObject;
  PIO_COMPLETION_ROUTINE CompletionRoutine;
  PVOID                  Context;
} IO_STACK_LOCATION, *PIO_STACK_LOCATION;

typedef struct _IO_STATUS_BLOCK64 {
  union {
    NTSTATUS Status;
    PVOID64  Pointer;
  } DUMMYUNIONNAME;
  ULONG64 Information;
} IO_STATUS_BLOCK64;

#ifndef _IRP_
#define _IRP_
typedef
VOID
(*PDRIVER_CANCEL) (
     struct _DEVICE_OBJECT* DeviceObject,
     struct _IRP* Irp
    );


typedef struct _IRP {
    CSHORT                    Type;
    USHORT                    Size;
    PMDL                      MdlAddress;
    ULONG                     Flags;
    union {
        struct _IRP* MasterIrp;
        LONG IrpCount;
        PVOID           SystemBuffer;
    } AssociatedIrp;
    LIST_ENTRY                ThreadListEntry;
    IO_STATUS_BLOCK           IoStatus;
    KPROCESSOR_MODE           RequestorMode;
    BOOLEAN                   PendingReturned;
    CHAR                      StackCount;
    CHAR                      CurrentLocation;
    BOOLEAN                   Cancel;
    KIRQL                     CancelIrql;
    CCHAR                     ApcEnvironment;
    UCHAR                     AllocationFlags;
    union {
        PIO_STATUS_BLOCK UserIosb;
        PVOID            IoRingContext;
    };
    PKEVENT                   UserEvent;
    union {
        struct {
            union {
                PIO_APC_ROUTINE UserApcRoutine;
                PVOID           IssuingProcess;
            };
            union {
                PVOID                 UserApcContext;
                //#if ...
                _IORING_OBJECT* IoRing;
                //#else
                //        struct _IORING_OBJECT *IoRing;
                //#endif
            };
        } AsynchronousParameters;
        LARGE_INTEGER AllocationSize;
    } Overlay;
    PDRIVER_CANCEL CancelRoutine;
    PVOID                     UserBuffer;
    union {
        struct {
            union {
                KDEVICE_QUEUE_ENTRY DeviceQueueEntry;
                struct {
                    PVOID DriverContext[4];
                };
            };
            PETHREAD     Thread;
            PCHAR        AuxiliaryBuffer;
            struct {
                LIST_ENTRY ListEntry;
                union {
                    struct _IO_STACK_LOCATION* CurrentStackLocation;
                    ULONG                     PacketType;
                };
            };
            PFILE_OBJECT OriginalFileObject;
        } Overlay;
        KAPC  Apc;
        PVOID CompletionKey;
    } Tail;
} IRP, * PIRP;
#endif


void IoAcquireCancelSpinLock(
  PKIRQL Irql
);

NTSTATUS IoAcquireKsrPersistentMemory(
  PDRIVER_OBJECT DriverObject,
  PDEVICE_OBJECT PhysicalDeviceObject,
  PVOID          Buffer,
  PSIZE_T        Size
);

NTSTATUS IoAcquireKsrPersistentMemoryEx(
  PDRIVER_OBJECT  DriverObject,
  PDEVICE_OBJECT  PhysicalDeviceObject,
  PUNICODE_STRING PhysicalDeviceId,
  PUSHORT         DataTag,
  PULONG          DataVersion,
  PVOID           Buffer,
  PSIZE_T         Size
);



NTSTATUS
IoAcquireRemoveLock (
     PIO_REMOVE_LOCK RemoveLock,
     PVOID          Tag
    );

//void IoAdjustPagingPathCount(
//    _count_,
//    _paging_
//);

NTSTATUS IoAllocateDriverObjectExtension(
    PDRIVER_OBJECT DriverObject,
    PVOID          ClientIdentificationAddress,
    ULONG          DriverObjectExtensionSize,
   PVOID          *DriverObjectExtension
);

PVOID IoAllocateErrorLogEntry(
   PVOID IoObject,
   UCHAR EntrySize
);

PIRP IoAllocateIrp(
   CCHAR   StackSize,
   BOOLEAN ChargeQuota
);

PIRP IoAllocateIrpEx(
  PDEVICE_OBJECT DeviceObject,
  CCHAR          StackSize,
  BOOLEAN        ChargeQuota
);

PMDL IoAllocateMdl(
              PVOID VirtualAddress,
                  ULONG                  Length,
                  BOOLEAN                SecondaryBuffer,
                  BOOLEAN                ChargeQuota,
    PIRP                   Irp
);

PIO_WORKITEM IoAllocateWorkItem(
   PDEVICE_OBJECT DeviceObject
);

NTSTATUS IoAttachDevice(
    PDEVICE_OBJECT  SourceDevice,
    PUNICODE_STRING TargetDevice,
   PDEVICE_OBJECT  *AttachedDevice
);

PDEVICE_OBJECT IoAttachDeviceToDeviceStack(
   PDEVICE_OBJECT SourceDevice,
   PDEVICE_OBJECT TargetDevice
);


PIRP IoBuildAsynchronousFsdRequest(
             ULONG            MajorFunction,
             PDEVICE_OBJECT   DeviceObject,
        PVOID            Buffer,
   ULONG            Length,
   PLARGE_INTEGER   StartingOffset,
   PIO_STATUS_BLOCK IoStatusBlock
);

PIRP IoBuildDeviceIoControlRequest(
              ULONG            IoControlCode,
              PDEVICE_OBJECT   DeviceObject,
    PVOID            InputBuffer,
              ULONG            InputBufferLength,
   PVOID            OutputBuffer,
              ULONG            OutputBufferLength,
              BOOLEAN          InternalDeviceIoControl,
    PKEVENT          Event,
             PIO_STATUS_BLOCK IoStatusBlock
);

void IoBuildPartialMdl(
        PMDL  SourceMdl,
   PMDL  TargetMdl,
        PVOID VirtualAddress,
        ULONG Length
);

 PIRP IoBuildSynchronousFsdRequest(
             ULONG            MajorFunction,
             PDEVICE_OBJECT   DeviceObject,
        PVOID            Buffer,
   ULONG            Length,
   PLARGE_INTEGER   StartingOffset,
             PKEVENT          Event,
            PIO_STATUS_BLOCK IoStatusBlock
);

#define IoCallDriver(a,b)   \
        IofCallDriver(a,b)  \
)


BOOLEAN IoCancelIrp(
   PIRP Irp
);

NTSTATUS IoCheckLinkShareAccess(
                  ACCESS_MASK        DesiredAccess,
                  ULONG              DesiredShareAccess,
    PFILE_OBJECT       FileObject,
    PSHARE_ACCESS      ShareAccess,
    PLINK_SHARE_ACCESS LinkShareAccess,
                  ULONG              IoShareAccessFlags
);

NTSTATUS IoCheckShareAccess(
        ACCESS_MASK   DesiredAccess,
        ULONG         DesiredShareAccess,
   PFILE_OBJECT  FileObject,
   PSHARE_ACCESS ShareAccess,
        BOOLEAN       Update
);

NTSTATUS IoCheckShareAccessEx(
        ACCESS_MASK   DesiredAccess,
        ULONG         DesiredShareAccess,
   PFILE_OBJECT  FileObject,
   PSHARE_ACCESS ShareAccess,
        BOOLEAN       Update,
        PBOOLEAN      WritePermission
);

NTSTATUS IoConnectInterrupt(
            PKINTERRUPT       *InterruptObject,
             PKSERVICE_ROUTINE ServiceRoutine,
   PVOID                   ServiceContext,
   PKSPIN_LOCK             SpinLock,
             ULONG             Vector,
             KIRQL             Irql,
             KIRQL             SynchronizeIrql,
             KINTERRUPT_MODE   InterruptMode,
             BOOLEAN           ShareVector,
             KAFFINITY         ProcessorEnableMask,
             BOOLEAN           FloatingSave
);


void IoCopyCurrentIrpStackLocationToNext(
   PIRP Irp
);

NTSTATUS IoCreateDevice(
             PDRIVER_OBJECT  DriverObject,
             ULONG           DeviceExtensionSize,
   PUNICODE_STRING DeviceName,
             DEVICE_TYPE     DeviceType,
             ULONG           DeviceCharacteristics,
             BOOLEAN         Exclusive,
            PDEVICE_OBJECT  *DeviceObject
);

NTSTATUS IoCreateFile(
            PHANDLE            FileHandle,
             ACCESS_MASK        DesiredAccess,
             POBJECT_ATTRIBUTES ObjectAttributes,
            PIO_STATUS_BLOCK   IoStatusBlock,
   PLARGE_INTEGER     AllocationSize,
             ULONG              FileAttributes,
             ULONG              ShareAccess,
             ULONG              Disposition,
             ULONG              CreateOptions,
   PVOID              EaBuffer,
             ULONG              EaLength,
             CREATE_FILE_TYPE   CreateFileType,
   PVOID              InternalParameters,
             ULONG              Options
);

PKEVENT IoCreateNotificationEvent(
    PUNICODE_STRING EventName,
   PHANDLE         EventHandle
);

NTSTATUS IoCreateSymbolicLink(
   PUNICODE_STRING SymbolicLinkName,
   PUNICODE_STRING DeviceName
);

PKEVENT IoCreateSynchronizationEvent(
    PUNICODE_STRING EventName,
   PHANDLE         EventHandle
);

NTSTATUS IoCreateSystemThread(
         PVOID              IoObject,
             PHANDLE            ThreadHandle,
              ULONG              DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    HANDLE             ProcessHandle,
   PCLIENT_ID         ClientId,
              PKSTART_ROUTINE    StartRoutine,
    PVOID              StartContext
);

NTSTATUS IoCreateUnprotectedSymbolicLink(
   PUNICODE_STRING SymbolicLinkName,
   PUNICODE_STRING DeviceName
);

NTSTATUS IoCsqInitialize(
   PIO_CSQ                       Csq,
    PIO_CSQ_INSERT_IRP            CsqInsertIrp,
    PIO_CSQ_REMOVE_IRP            CsqRemoveIrp,
    PIO_CSQ_PEEK_NEXT_IRP         CsqPeekNextIrp,
    PIO_CSQ_ACQUIRE_LOCK          CsqAcquireLock,
    PIO_CSQ_RELEASE_LOCK          CsqReleaseLock,
    PIO_CSQ_COMPLETE_CANCELED_IRP CsqCompleteCanceledIrp
);

NTSTATUS IoCsqInitializeEx(
   PIO_CSQ                       Csq,
    PIO_CSQ_INSERT_IRP_EX         CsqInsertIrp,
    PIO_CSQ_REMOVE_IRP            CsqRemoveIrp,
    PIO_CSQ_PEEK_NEXT_IRP         CsqPeekNextIrp,
    PIO_CSQ_ACQUIRE_LOCK          CsqAcquireLock,
    PIO_CSQ_RELEASE_LOCK          CsqReleaseLock,
    PIO_CSQ_COMPLETE_CANCELED_IRP CsqCompleteCanceledIrp
);

void IoCsqInsertIrp(
         PIO_CSQ             Csq,
         PIRP                Irp,
   PIO_CSQ_IRP_CONTEXT Context
);

NTSTATUS IoCsqInsertIrpEx(
         PIO_CSQ             Csq,
         PIRP                Irp,
   PIO_CSQ_IRP_CONTEXT Context,
    PVOID               InsertContext
);

PIRP IoCsqRemoveIrp(
   PIO_CSQ             Csq,
   PIO_CSQ_IRP_CONTEXT Context
);

PIRP IoCsqRemoveNextIrp(
        PIO_CSQ Csq,
   PVOID   PeekContext
);

void IoDeleteDevice(
   PDEVICE_OBJECT DeviceObject
);

NTSTATUS IoDeleteSymbolicLink(
   PUNICODE_STRING SymbolicLinkName
);

void IoDetachDevice(
   PDEVICE_OBJECT TargetDevice
);

void IoDisconnectInterrupt(
   PKINTERRUPT InterruptObject
);

void IoDisconnectInterruptEx(
   PIO_DISCONNECT_INTERRUPT_PARAMETERS Parameters
);

NTSTATUS IoEnumerateKsrPersistentMemoryEx(
  PDRIVER_OBJECT                            DriverObject,
  PDEVICE_OBJECT                            PhysicalDeviceObject,
  PUNICODE_STRING                           PhysicalDeviceId,
  PIO_PERSISTED_MEMORY_ENUMERATION_CALLBACK Callback,
  PVOID                                     CallbackContext
);

NTSTATUS IofCallDriver(
  PDEVICE_OBJECT        DeviceObject,
   PIRP Irp
);

void IofCompleteRequest(
  PIRP  Irp,
  CCHAR PriorityBoost
);

BOOLEAN IoForwardIrpSynchronously(
   PDEVICE_OBJECT DeviceObject,
   PIRP           Irp
);

void IoFreeErrorLogEntry(
   PVOID ElEntry
);

void IoFreeIrp(
   PIRP Irp
);

NTSTATUS IoFreeKsrPersistentMemory(
  PVOID DataHandle
);

void IoFreeMdl(
   PMDL Mdl
);

void IoFreeWorkItem(
   PIO_WORKITEM IoWorkItem
);

NTSTATUS IoGetAffinityInterrupt(
    PKINTERRUPT     InterruptObject,
   PGROUP_AFFINITY GroupAffinity
);

PDEVICE_OBJECT IoGetAttachedDeviceReference(
   PDEVICE_OBJECT DeviceObject
);

NTSTATUS IoGetBootDiskInformation(
   PBOOTDISK_INFORMATION BootDiskInformation,
        ULONG                 Size
);

NTSTATUS IoGetContainerInformation(
             IO_CONTAINER_INFORMATION_CLASS InformationClass,
   PVOID                          ContainerObject,
        PVOID                          Buffer,
             ULONG                          BufferLength
);

 PIO_STACK_LOCATION IoGetCurrentIrpStackLocation(
   PIRP Irp
);

PEPROCESS IoGetCurrentProcess();

NTSTATUS IoGetDeviceInterfaceAlias(
    PUNICODE_STRING SymbolicLinkName,
    const GUID      *AliasInterfaceClassGuid,
   PUNICODE_STRING AliasSymbolicLinkName
);

NTSTATUS IoGetDeviceInterfacePropertyData(
    PUNICODE_STRING  SymbolicLinkName,
    const DEVPROPKEY *PropertyKey,
    LCID             Lcid,
        ULONG            Flags,
    ULONG            Size,
   PVOID            Data,
   PULONG           RequiredSize,
   PDEVPROPTYPE     Type
);

NTSTATUS IoGetDeviceInterfaces(
             const GUID     *InterfaceClassGuid,
   PDEVICE_OBJECT PhysicalDeviceObject,
             ULONG          Flags,
            PZZWSTR        *SymbolicLinkList
);

NTSTATUS IoGetDeviceNumaNode(
    PDEVICE_OBJECT Pdo,
   PUSHORT        NodeNumber
);

NTSTATUS IoGetDeviceObjectPointer(
    PUNICODE_STRING ObjectName,
    ACCESS_MASK     DesiredAccess,
   PFILE_OBJECT    *FileObject,
   PDEVICE_OBJECT  *DeviceObject
);

NTSTATUS IoGetDeviceProperty(
              PDEVICE_OBJECT           DeviceObject,
              DEVICE_REGISTRY_PROPERTY DeviceProperty,
              ULONG                    BufferLength,
   PVOID                    PropertyBuffer,
             PULONG                   ResultLength
);

NTSTATUS IoGetDevicePropertyData(
    PDEVICE_OBJECT   Pdo,
    const DEVPROPKEY *PropertyKey,
    LCID             Lcid,
        ULONG            Flags,
    ULONG            Size,
   PVOID            Data,
   PULONG           RequiredSize,
   PDEVPROPTYPE     Type
);

_DMA_ADAPTER * IoGetDmaAdapter(
   PDEVICE_OBJECT      PhysicalDeviceObject,
             _DEVICE_DESCRIPTION *DeviceDescription,
            PULONG              NumberOfMapRegisters
);

NTSTATUS IoGetDriverDirectory(
    PDRIVER_OBJECT        DriverObject,
    DRIVER_DIRECTORY_TYPE DirectoryType,
    ULONG                 Flags,
   PHANDLE               DriverDirectoryHandle
);

 PVOID IoGetDriverObjectExtension(
   PDRIVER_OBJECT DriverObject,
   PVOID          ClientIdentificationAddress
);

//void IoGetFunctionCodeFromCtlCode(
//    ControlCode
//);

PVOID IoGetInitialStack();

NTSTATUS IoGetIommuInterface(
  ULONG                Version,
  PDMA_IOMMU_INTERFACE InterfaceOut
);

NTSTATUS IoGetIommuInterfaceEx(
  ULONG                   Version,
  ULONGLONG               Flags,
  PDMA_IOMMU_INTERFACE_EX InterfaceOut
);

IO_PRIORITY_HINT IoGetIoPriorityHint(
   PIRP Irp
);

 PIO_STACK_LOCATION IoGetNextIrpStackLocation(
   PIRP Irp
);


PDEVICE_OBJECT IoGetRelatedDeviceObject(
   PFILE_OBJECT FileObject
);

ULONG_PTR IoGetRemainingStackSize();

void IoGetStackLimits(
   PULONG_PTR LowLimit,
   PULONG_PTR HighLimit
);


void IoInitializeDpcRequest(
   PDEVICE_OBJECT  DeviceObject,
   PIO_DPC_ROUTINE DpcRoutine
);

void IoInitializeIrp(
   PIRP   Irp,
        USHORT PacketSize,
        CCHAR  StackSize
);

//void IoInitializeRemoveLock(
//    Lock,
//    Tag,
//    Maxmin,
//    HighWater
//);

NTSTATUS IoInitializeTimer(
             PDEVICE_OBJECT         DeviceObject,
             PIO_TIMER_ROUTINE      TimerRoutine,
    PVOID Context
);

void IoInitializeWorkItem(
   PVOID        IoObject,
   PIO_WORKITEM IoWorkItem
);

void IoInvalidateDeviceRelations(
   PDEVICE_OBJECT       DeviceObject,
   DEVICE_RELATION_TYPE Type
);

void IoInvalidateDeviceState(
   PDEVICE_OBJECT PhysicalDeviceObject
);

BOOLEAN IoIs32bitProcess(
   PIRP Irp
);

//BOOLEAN IoIsErrorUserInduced(
//   Status
//);

BOOLEAN IoIsWdmVersionAvailable(
   UCHAR MajorVersion,
   UCHAR MinorVersion
);

void IoMarkIrpPending(
   PIRP Irp
);

typedef struct _KBUGCHECK_ADD_PAGES {
    PVOID     Context;
    ULONG     Flags;
    ULONG     BugCheckCode;
    ULONG_PTR Address;
    ULONG_PTR Count;
} KBUGCHECK_ADD_PAGES, * PKBUGCHECK_ADD_PAGES;

typedef enum _KBUGCHECK_CALLBACK_REASON {
    KbCallbackInvalid,
    KbCallbackReserved1,
    KbCallbackSecondaryDumpData,
    KbCallbackDumpIo,
    KbCallbackAddPages,
    KbCallbackSecondaryMultiPartDumpData,
    KbCallbackRemovePages,
    KbCallbackTriageDumpData,
    KbCallbackReserved2
} KBUGCHECK_CALLBACK_REASON;

typedef enum _KBUGCHECK_DUMP_IO_TYPE {
    KbDumpIoInvalid,
    KbDumpIoHeader,
    KbDumpIoBody,
    KbDumpIoSecondaryData,
    KbDumpIoComplete
} KBUGCHECK_DUMP_IO_TYPE;

typedef struct _KBUGCHECK_DUMP_IO {
     ULONG64                Offset;
     PVOID                  Buffer;
     ULONG                  BufferLength;
     KBUGCHECK_DUMP_IO_TYPE Type;
} KBUGCHECK_DUMP_IO, * PKBUGCHECK_DUMP_IO;



typedef struct _KBUGCHECK_SECONDARY_DUMP_DATA {
     PVOID  InBuffer;
     ULONG  InBufferLength;
     ULONG  MaximumAllowed;
     GUID  Guid;
     PVOID OutBuffer;
     ULONG OutBufferLength;
} KBUGCHECK_SECONDARY_DUMP_DATA, * PKBUGCHECK_SECONDARY_DUMP_DATA;

typedef struct _KDPC_WATCHDOG_INFORMATION {
    ULONG DpcTimeLimit;
    ULONG DpcTimeCount;
    ULONG DpcWatchdogLimit;
    ULONG DpcWatchdogCount;
    ULONG Reserved;
} KDPC_WATCHDOG_INFORMATION, * PKDPC_WATCHDOG_INFORMATION;

typedef enum {
    KeProcessorAddStartNotify,
    KeProcessorAddCompleteNotify,
    KeProcessorAddFailureNotify
} KE_PROCESSOR_CHANGE_NOTIFY_STATE;

typedef struct _KE_PROCESSOR_CHANGE_NOTIFY_CONTEXT {
    KE_PROCESSOR_CHANGE_NOTIFY_STATE State;
    ULONG                            NtNumber;
    NTSTATUS                         Status;
    PROCESSOR_NUMBER                 ProcNumber;
} KE_PROCESSOR_CHANGE_NOTIFY_CONTEXT, * PKE_PROCESSOR_CHANGE_NOTIFY_CONTEXT;

typedef struct _IOMMU_DEVICE_CREATION_CONFIGURATION_ACPI {
    UINT32 InputMappingBase;
    UINT32 MappingsCount;
} IOMMU_DEVICE_CREATION_CONFIGURATION_ACPI, * PIOMMU_DEVICE_CREATION_CONFIGURATION_ACPI;

typedef enum _IOMMU_DEVICE_CREATION_CONFIGURATION_TYPE {
    IommuDeviceCreationConfigTypeNone,
    IommuDeviceCreationConfigTypeAcpi,
    IommuDeviceCreationConfigTypeDeviceId,
    IommuDeviceCreationConfigTypePasid,
    IommuDeviceCreationConfigTypeMax
} IOMMU_DEVICE_CREATION_CONFIGURATION_TYPE, * PIOMMU_DEVICE_CREATION_CONFIGURATION_TYPE;

typedef struct _IOMMU_DEVICE_CREATION_CONFIGURATION {
  LIST_ENTRY                               NextConfiguration;
  IOMMU_DEVICE_CREATION_CONFIGURATION_TYPE ConfigType;
  union {
    IOMMU_DEVICE_CREATION_CONFIGURATION_ACPI  Acpi;
    PVOID                                     DeviceId;
    IOMMU_DEVICE_CREATION_CONFIGURATION_PASID Pasid;
  };
} IOMMU_DEVICE_CREATION_CONFIGURATION, *PIOMMU_DEVICE_CREATION_CONFIGURATION;



typedef union _IOMMU_DMA_DOMAIN_CREATION_FLAGS {
  struct {
    ULONGLONG Reserved : 64;
  };
  ULONGLONG AsUlonglong;
} IOMMU_DMA_DOMAIN_CREATION_FLAGS, *PIOMMU_DMA_DOMAIN_CREATION_FLAGS;

typedef enum _IOMMU_DMA_DOMAIN_TYPE {
  DomainTypeTranslate,
  DomainTypePassThrough,
  DomainTypeUnmanaged,
  DomainTypeTranslateS1,
  DomainTypeMax
} IOMMU_DMA_DOMAIN_TYPE, *PIOMMU_DMA_DOMAIN_TYPE;

typedef struct _IOMMU_DMA_LOGICAL_ADDRESS_TOKEN_MAPPED_SEGMENT {
  PIOMMU_DMA_LOGICAL_ADDRESS_TOKEN OwningToken;
  SIZE_T                           Offset;
  SIZE_T                           Size;
} IOMMU_DMA_LOGICAL_ADDRESS_TOKEN_MAPPED_SEGMENT, *PIOMMU_DMA_LOGICAL_ADDRESS_TOKEN_MAPPED_SEGMENT;

typedef struct _IOMMU_DMA_LOGICAL_ALLOCATOR_CONFIG {
  IOMMU_DMA_LOGICAL_ALLOCATOR_TYPE LogicalAllocatorType;
  union {
    struct {
      ULONG AddressWidth;
    } BuddyAllocatorConfig;
  };
} IOMMU_DMA_LOGICAL_ALLOCATOR_CONFIG, *PIOMMU_DMA_LOGICAL_ALLOCATOR_CONFIG;

typedef union _IOMMU_INTERFACE_STATE_CHANGE_FIELDS {
    struct {
        ULONG AvailableDomainTypes : 1;
        ULONG Reserved : 31;
    } DUMMYSTRUCTNAME;
    ULONG  AsULONG;
} IOMMU_INTERFACE_STATE_CHANGE_FIELDS, * PIOMMU_INTERFACE_STATE_CHANGE_FIELDS;

typedef struct _IOMMU_DMA_RESERVED_REGION {
  struct _IOMMU_DMA_RESERVED_REGION *RegionNext;
  IOMMU_DMA_LOGICAL_ADDRESS         Base;
  SIZE_T                            NumberOfPages;
  BOOLEAN                           ShouldMap;
} IOMMU_DMA_RESERVED_REGION, *PIOMMU_DMA_RESERVED_REGION;

typedef struct _IOMMU_INTERFACE_STATE_CHANGE {
  IOMMU_INTERFACE_STATE_CHANGE_FIELDS PresentFields;
  ULONG                               AvailableDomainTypes;
} IOMMU_INTERFACE_STATE_CHANGE, *PIOMMU_INTERFACE_STATE_CHANGE;



typedef struct _IOMMU_MAP_PHYSICAL_ADDRESS {
  IOMMU_MAP_PHYSICAL_ADDRESS_TYPE MapType;
  union {
    struct {
      PMDL Mdl;
    } Mdl;
    struct {
      PHYSICAL_ADDRESS Base;
      SIZE_T           Size;
    } ContiguousRange;
    struct {
      PPFN_NUMBER PageFrame;
      SIZE_T      NumberOfPages;
    } PfnArray;
  };
} IOMMU_MAP_PHYSICAL_ADDRESS, *PIOMMU_MAP_PHYSICAL_ADDRESS;

NTSTATUS IoOpenDeviceInterfaceRegistryKey(
    PUNICODE_STRING SymbolicLinkName,
    ACCESS_MASK     DesiredAccess,
   PHANDLE         DeviceInterfaceRegKey
);

NTSTATUS IoOpenDeviceRegistryKey(
    PDEVICE_OBJECT DeviceObject,
    ULONG          DevInstKeyType,
    ACCESS_MASK    DesiredAccess,
   PHANDLE        DeviceRegKey
);

NTSTATUS IoOpenDriverRegistryKey(
    PDRIVER_OBJECT     DriverObject,
    DRIVER_REGKEY_TYPE RegKeyType,
    ACCESS_MASK        DesiredAccess,
    ULONG              Flags,
   PHANDLE            DriverRegKey
);

NTSTATUS IoQueryKsrPersistentMemorySize(
  PDRIVER_OBJECT DriverObject,
  PDEVICE_OBJECT PhysicalDeviceObject,
  PSIZE_T        BufferSize
);

NTSTATUS IoQueryKsrPersistentMemorySizeEx(
  PDRIVER_OBJECT  DriverObject,
  PDEVICE_OBJECT  PhysicalDeviceObject,
  PUNICODE_STRING PhysicalDeviceId,
  PUSHORT         DataTag,
  PULONG          DataVersion,
  PSIZE_T         BufferSize
);

void IoQueueWorkItem(
              PIO_WORKITEM IoWorkItem,
             PIO_WORKITEM_ROUTINE          WorkerRoutine,
             WORK_QUEUE_TYPE               QueueType,
    PVOID        Context
);

void IoQueueWorkItemEx(
              PIO_WORKITEM IoWorkItem,
             PIO_WORKITEM_ROUTINE_EX       WorkerRoutine,
             WORK_QUEUE_TYPE               QueueType,
    PVOID        Context
);

NTSTATUS
IoRegisterContainerNotification(
     IO_CONTAINER_NOTIFICATION_CLASS NotificationClass,
     PIO_CONTAINER_NOTIFICATION_FUNCTION CallbackFunction,
     PVOID NotificationInformation,
     ULONG NotificationInformationLength,
     PVOID * CallbackRegistration
    );

    NTSTATUS IoRegisterDeviceInterface(
             PDEVICE_OBJECT  PhysicalDeviceObject,
             const GUID      *InterfaceClassGuid,
   PUNICODE_STRING ReferenceString,
            PUNICODE_STRING SymbolicLinkName
);

NTSTATUS IoRegisterLastChanceShutdownNotification(
   PDEVICE_OBJECT DeviceObject
);

NTSTATUS IoRegisterPlugPlayNotification(
             IO_NOTIFICATION_EVENT_CATEGORY        EventCategory,
             ULONG                                 EventCategoryFlags,
   PVOID                                 EventCategoryData,
             PDRIVER_OBJECT                        DriverObject,
             PDRIVER_NOTIFICATION_CALLBACK_ROUTINE CallbackRoutine,
    PVOID                Context,
            PVOID                                 *NotificationEntry
);

NTSTATUS IoRegisterShutdownNotification(
   PDEVICE_OBJECT DeviceObject
);

void IoReleaseCancelSpinLock(
  KIRQL Irql
);

//void IoReleaseRemoveLock(
//    RemoveLock,
//    Tag
//);

//void IoReleaseRemoveLockAndWait(
//    RemoveLock,
//    Tag
//);

void IoRemoveLinkShareAccess(
                  PFILE_OBJECT       FileObject,
             PSHARE_ACCESS      ShareAccess,
    PLINK_SHARE_ACCESS LinkShareAccess
);

void IoRemoveShareAccess(
        PFILE_OBJECT  FileObject,
   PSHARE_ACCESS ShareAccess
);

void IoReportInterruptActive(
   PIO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS Parameters
);

void IoReportInterruptInactive(
   PIO_REPORT_INTERRUPT_ACTIVE_STATE_PARAMETERS Parameters
);

NTSTATUS IoReportTargetDeviceChange(
   PDEVICE_OBJECT PhysicalDeviceObject,
   PVOID          NotificationStructure
);

NTSTATUS IoReportTargetDeviceChangeAsynchronous(
             PDEVICE_OBJECT                   PhysicalDeviceObject,
             PVOID                            NotificationStructure,
   PDEVICE_CHANGE_COMPLETE_CALLBACK Callback,
        PVOID                            Context
);

void IoRequestDeviceEject(
   PDEVICE_OBJECT PhysicalDeviceObject
);

void IoRequestDpc(
   PDEVICE_OBJECT         DeviceObject,
   PIRP                   Irp,
    PVOID Context
);

NTSTATUS IoReserveKsrPersistentMemory(
  PDRIVER_OBJECT DriverObject,
  PDEVICE_OBJECT PhysicalDeviceObject,
  SIZE_T         Size,
  ULONG          Flags,
  PVOID          *DataHandle
);

NTSTATUS IoReserveKsrPersistentMemoryEx(
  PDRIVER_OBJECT  DriverObject,
  PDEVICE_OBJECT  PhysicalDeviceObject,
  PUNICODE_STRING PhysicalDeviceId,
  PUSHORT         DataTag,
  ULONG           DataVersion,
  SIZE_T          Size,
  ULONG           Flags,
  PVOID           *DataHandle
);

void IoReuseIrp(
   PIRP     Irp,
        NTSTATUS Iostatus
);

//void Iosb64ToIosb(
//   _iosb,
//   _iosb64
//);

//void IosbToIosb64(
//   _iosb64,
//   _iosb
//);

PDRIVER_CANCEL IoSetCancelRoutine(
   PIRP           Irp,
   PDRIVER_CANCEL CancelRoutine
);

void IoSetCompletionRoutine(
             PIRP                   Irp,
   PIO_COMPLETION_ROUTINE CompletionRoutine,
    PVOID Context,
             BOOLEAN                InvokeOnSuccess,
             BOOLEAN                InvokeOnError,
             BOOLEAN                InvokeOnCancel
);

NTSTATUS IoSetCompletionRoutineEx(
             PDEVICE_OBJECT         DeviceObject,
             PIRP                   Irp,
             PIO_COMPLETION_ROUTINE CompletionRoutine,
   PVOID                  Context,
             BOOLEAN                InvokeOnSuccess,
             BOOLEAN                InvokeOnError,
             BOOLEAN                InvokeOnCancel
);

NTSTATUS IoSetDeviceInterfacePropertyData(
             PUNICODE_STRING  SymbolicLinkName,
             const DEVPROPKEY *PropertyKey,
             LCID             Lcid,
             ULONG            Flags,
             DEVPROPTYPE      Type,
             ULONG            Size,
   PVOID            Data
);

NTSTATUS IoSetDeviceInterfaceState(
   PUNICODE_STRING SymbolicLinkName,
   BOOLEAN         Enable
);

NTSTATUS IoSetDevicePropertyData(
             PDEVICE_OBJECT   Pdo,
             const DEVPROPKEY *PropertyKey,
             LCID             Lcid,
             ULONG            Flags,
             DEVPROPTYPE      Type,
             ULONG            Size,
   PVOID            Data
);

NTSTATUS IoSetIoPriorityHint(
   PIRP             Irp,
   IO_PRIORITY_HINT PriorityHint
);

void IoSetLinkShareAccess(
                  ACCESS_MASK        DesiredAccess,
                  ULONG              DesiredShareAccess,
             PFILE_OBJECT       FileObject,
             PSHARE_ACCESS      ShareAccess,
    PLINK_SHARE_ACCESS LinkShareAccess,
                  ULONG              IoShareAccessFlags
);

void IoSetNextIrpStackLocation(
   PIRP Irp
);


void IoSetShareAccess(
        ACCESS_MASK   DesiredAccess,
        ULONG         DesiredShareAccess,
   PFILE_OBJECT  FileObject,
       PSHARE_ACCESS ShareAccess
);

void IoSetShareAccessEx(
             ACCESS_MASK   DesiredAccess,
             ULONG         DesiredShareAccess,
        PFILE_OBJECT  FileObject,
            PSHARE_ACCESS ShareAccess,
   PBOOLEAN      WritePermission
);

void IoSetStartIoAttributes(
   PDEVICE_OBJECT DeviceObject,
   BOOLEAN        DeferredStartIo,
   BOOLEAN        NonCancelable
);

//void IoSizeOfIrp(
//    StackSize
//);

ULONG IoSizeofWorkItem();

void IoStartNextPacket(
   PDEVICE_OBJECT DeviceObject,
   BOOLEAN        Cancelable
);

void IoStartNextPacketByKey(
   PDEVICE_OBJECT DeviceObject,
   BOOLEAN        Cancelable,
   ULONG          Key
);

void IoStartPacket(
             PDEVICE_OBJECT DeviceObject,
             PIRP           Irp,
   PULONG         Key,
   PDRIVER_CANCEL CancelFunction
);

void IoStartTimer(
   PDEVICE_OBJECT DeviceObject
);

void IoStopTimer(
   PDEVICE_OBJECT DeviceObject
);

void IoUninitializeWorkItem(
   PIO_WORKITEM IoWorkItem
);

void IoUnregisterContainerNotification(
   PVOID CallbackRegistration
);

NTSTATUS IoUnregisterPlugPlayNotification(
   PVOID NotificationEntry
);

NTSTATUS IoUnregisterPlugPlayNotificationEx(
   PVOID NotificationEntry
);

void IoUnregisterShutdownNotification(
   PDEVICE_OBJECT DeviceObject
);

void IoUpdateLinkShareAccess(
                  PFILE_OBJECT       FileObject,
             PSHARE_ACCESS      ShareAccess,
    PLINK_SHARE_ACCESS LinkShareAccess
);

void IoUpdateLinkShareAccessEx(
  PFILE_OBJECT       FileObject,
  PSHARE_ACCESS      ShareAccess,
  PLINK_SHARE_ACCESS LinkShareAccess,
  ULONG              IoShareAccessFlags
);

void IoUpdateShareAccess(
        PFILE_OBJECT  FileObject,
   PSHARE_ACCESS ShareAccess
);

NTSTATUS IoValidateDeviceIoControlAccess(
   PIRP  Irp,
   ULONG RequiredAccess
);

LOGICAL IoWithinStackLimits(
   ULONG_PTR RegionStart,
   SIZE_T    RegionSize
);

NTSTATUS IoWMIAllocateInstanceIds(
    LPCGUID Guid,
    ULONG   InstanceCount,
   ULONG   *FirstInstanceId
);

NTSTATUS IoWMIDeviceObjectToInstanceName(
    PVOID           DataBlockObject,
    PDEVICE_OBJECT  DeviceObject,
   PUNICODE_STRING InstanceName
);

ULONG IoWMIDeviceObjectToProviderId(
   PDEVICE_OBJECT DeviceObject
);

NTSTATUS IoWMIExecuteMethod(
        PVOID           DataBlockObject,
        PUNICODE_STRING InstanceName,
        ULONG           MethodId,
        ULONG           InBufferSize,
   PULONG          OutBufferSize,
   PUCHAR          InOutBuffer
);

NTSTATUS IoWMIHandleToInstanceName(
    PVOID           DataBlockObject,
    HANDLE          FileHandle,
   PUNICODE_STRING InstanceName
);

NTSTATUS IoWMIOpenBlock(
    LPCGUID Guid,
    ULONG   DesiredAccess,
   PVOID   *DataBlockObject
);

NTSTATUS IoWMIQueryAllData(
              PVOID  DataBlockObject,
         PULONG InOutBufferSize,
   PVOID  OutBuffer
);

NTSTATUS IoWMIQueryAllDataMultiple(
              PVOID  *DataBlockObjectList,
              ULONG  ObjectCount,
         PULONG InOutBufferSize,
   PVOID  OutBuffer
);

NTSTATUS IoWMIQuerySingleInstance(
              PVOID           DataBlockObject,
              PUNICODE_STRING InstanceName,
         PULONG          InOutBufferSize,
   PVOID           OutBuffer
);

NTSTATUS IoWMIQuerySingleInstanceMultiple(
              PVOID           *DataBlockObjectList,
              PUNICODE_STRING InstanceNames,
              ULONG           ObjectCount,
         PULONG          InOutBufferSize,
   PVOID           OutBuffer
);

NTSTATUS IoWMIRegistrationControl(
   PDEVICE_OBJECT DeviceObject,
   ULONG          Action
);

NTSTATUS IoWMISetNotificationCallback(
        PVOID                     Object,
             WMI_NOTIFICATION_CALLBACK Callback,
   PVOID                     Context
);

NTSTATUS IoWMISetSingleInstance(
   PVOID           DataBlockObject,
   PUNICODE_STRING InstanceName,
   ULONG           Version,
   ULONG           ValueBufferSize,
   PVOID           ValueBuffer
);

NTSTATUS IoWMISetSingleItem(
   PVOID           DataBlockObject,
   PUNICODE_STRING InstanceName,
   ULONG           DataItemId,
   ULONG           Version,
   ULONG           ValueBufferSize,
   PVOID           ValueBuffer
);

NTSTATUS IoWMISuggestInstanceName(
   PDEVICE_OBJECT  PhysicalDeviceObject,
   PUNICODE_STRING SymbolicLinkName,
             BOOLEAN         CombineNames,
            PUNICODE_STRING SuggestedInstanceName
);

NTSTATUS IoWMIWriteEvent(
   PVOID WnodeEventItem
);

void IoWriteErrorLogEntry(
   PVOID ElEntry
);

NTSTATUS IoWriteKsrPersistentMemory(
  PVOID  DataHandle,
  PVOID  Buffer,
  SIZE_T Size
);



BOOLEAN IsListEmpty(
   const LIST_ENTRY *ListHead
);



void KeAcquireGuardedMutex(
  PKGUARDED_MUTEX Mutex
);

void KeAcquireGuardedMutexUnsafe(
  PKGUARDED_MUTEX FastMutex
);

void KeAcquireInStackQueuedSpinLock(
  PKSPIN_LOCK         SpinLock,
  PKLOCK_QUEUE_HANDLE LockHandle
);

void KeAcquireInStackQueuedSpinLockAtDpcLevel(
  PKSPIN_LOCK         SpinLock,
  PKLOCK_QUEUE_HANDLE LockHandle
);

void KeAcquireInStackQueuedSpinLockForDpc(
  PKSPIN_LOCK         SpinLock,
  PKLOCK_QUEUE_HANDLE LockHandle
);

KIRQL KeAcquireInterruptSpinLock(
  PKINTERRUPT Interrupt
);

void KeAcquireSpinLock(
   SpinLock,
   OldIrql
);

void KeAcquireSpinLockAtDpcLevel(
   PKSPIN_LOCK SpinLock
);

KIRQL KeAcquireSpinLockForDpc(
  PKSPIN_LOCK SpinLock
);

KIRQL KeAcquireSpinLockRaiseToDpc(
  PKSPIN_LOCK SpinLock
);

NTSTATUS KeAddTriageDumpDataBlock(
   PKTRIAGE_DUMP_DATA_ARRAY KtriageDumpDataArray,
            PVOID                    Address,
      SIZE_T                   Size
);

BOOLEAN KeAreAllApcsDisabled();

BOOLEAN KeAreApcsDisabled();

void KeBugCheckEx(
   ULONG     BugCheckCode,
   ULONG_PTR BugCheckParameter1,
   ULONG_PTR BugCheckParameter2,
   ULONG_PTR BugCheckParameter3,
   ULONG_PTR BugCheckParameter4
);

BOOLEAN KeCancelTimer(
   PKTIMER unnamedParam1
);

void KeClearEvent(
   PRKEVENT Event
);

NTSTATUS KeConvertAuxiliaryCounterToPerformanceCounter(
              ULONG64  AuxiliaryCounterValue,
             PULONG64 PerformanceCounterValue,
   PULONG64 ConversionError
);

NTSTATUS KeConvertPerformanceCounterToAuxiliaryCounter(
              ULONG64  PerformanceCounterValue,
             PULONG64 AuxiliaryCounterValue,
   PULONG64 ConversionError
);

NTSTATUS KeDelayExecutionThread(
   KPROCESSOR_MODE WaitMode,
   BOOLEAN         Alertable,
   PLARGE_INTEGER  Interval
);

NTSTATUS KeDeregisterBoundCallback(
   PVOID Handle
);

BOOLEAN KeDeregisterBugCheckCallback(
   PKBUGCHECK_CALLBACK_RECORD CallbackRecord
);

BOOLEAN KeDeregisterBugCheckReasonCallback(
   PKBUGCHECK_REASON_CALLBACK_RECORD CallbackRecord
);

NTSTATUS KeDeregisterNmiCallback(
   PVOID Handle
);

void KeDeregisterProcessorChangeCallback(
     PVOID CallbackHandle
);


void KeEnterCriticalRegion();
void KeEnterGuardedRegion();

void KeFlushIoBuffers(
   PMDL    Mdl,
   BOOLEAN ReadOperation,
   BOOLEAN DmaOperation
);

void KeFlushQueuedDpcs();

void KefReleaseSpinLockFromDpcLevel(
   PKSPIN_LOCK SpinLock
);

NTHALAPI KIRQL KeGetCurrentIrql();

USHORT KeGetCurrentNodeNumber();

ULONG KeGetCurrentProcessorNumberEx(
   PPROCESSOR_NUMBER ProcNumber
);

PKTHREAD KeGetCurrentThread();

ULONG KeGetProcessorIndexFromNumber(
   PPROCESSOR_NUMBER ProcNumber
);

NTSTATUS KeGetProcessorNumberFromIndex(
    ULONG             ProcIndex,
   PPROCESSOR_NUMBER ProcNumber
);

ULONG KeGetRecommendedSharedDataAlignment();

NTSTATUS KeInitializeCrashDumpHeader(
              ULONG  DumpType,
              ULONG  Flags,
             PVOID  Buffer,
              ULONG  BufferSize,
   PULONG BufferNeeded
);

void KeInitializeDeviceQueue(
   PKDEVICE_QUEUE DeviceQueue
);

void KeInitializeDpc(
             PRKDPC Dpc,
             PKDEFERRED_ROUTINE      DeferredRoutine,
    PVOID  DeferredContext
);


void KeInitializeEvent(
   PRKEVENT   Event,
    EVENT_TYPE Type,
    BOOLEAN    State
);

void KeInitializeGuardedMutex(
   PKGUARDED_MUTEX Mutex
);

void KeInitializeMutex(
   PRKMUTEX Mutex,
    ULONG    Level
);

void KeInitializeSemaphore(
   PRKSEMAPHORE Semaphore,
    LONG         Count,
    LONG         Limit
);

void KeInitializeSpinLock(
   PKSPIN_LOCK SpinLock
);

void KeInitializeThreadedDpc(
            PRKDPC             Dpc,
             PKDEFERRED_ROUTINE DeferredRoutine,
   PVOID              DeferredContext
);

void KeInitializeTimer(
   PKTIMER Timer
);

void KeInitializeTimerEx(
   PKTIMER    Timer,
    TIMER_TYPE Type
);

BOOLEAN KeInsertByKeyDeviceQueue(
   PKDEVICE_QUEUE       DeviceQueue,
   PKDEVICE_QUEUE_ENTRY DeviceQueueEntry,
        ULONG                SortKey
);

BOOLEAN KeInsertDeviceQueue(
   PKDEVICE_QUEUE       DeviceQueue,
   PKDEVICE_QUEUE_ENTRY DeviceQueueEntry
);


BOOLEAN KeInsertQueueDpc(
        PRKDPC                 Dpc,
   PVOID                  SystemArgument1,
    PVOID SystemArgument2
);

ULONG_PTR KeIpiGenericCall(
   PKIPI_BROADCAST_WORKER BroadcastFunction,
   ULONG_PTR              Context
);

LOGICAL KeIsExecutingDpc();

void KeLeaveCriticalRegion();

void KeLeaveGuardedRegion();

void KeLowerIrql(
   KIRQL NewIrql
);

void KeMemoryBarrier();

USHORT KeQueryActiveGroupCount();

ULONG KeQueryActiveProcessorCount(
   PKAFFINITY ActiveProcessors
);

ULONG KeQueryActiveProcessorCountEx(
   USHORT GroupNumber
);


KAFFINITY KeQueryActiveProcessors();


NTSTATUS KeQueryAuxiliaryCounterFrequency(
   PULONG64 AuxiliaryCounterFrequency
);


NTSTATUS KeQueryDpcWatchdogInformation(
   PKDPC_WATCHDOG_INFORMATION WatchdogInformation
);

KAFFINITY KeQueryGroupAffinity(
   USHORT GroupNumber
);

USHORT KeQueryHighestNodeNumber();

ULONGLONG KeQueryInterruptTime();

ULONG64 KeQueryInterruptTimePrecise(
   PULONG64 QpcTimeStamp
);

NTSTATUS KeQueryLogicalProcessorRelationship(
    PPROCESSOR_NUMBER                        ProcessorNumber,
              LOGICAL_PROCESSOR_RELATIONSHIP           RelationshipType,
   PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Information,
         PULONG                                   Length
);

USHORT KeQueryMaximumGroupCount();


ULONG KeQueryMaximumProcessorCount();

ULONG KeQueryMaximumProcessorCountEx(
   USHORT GroupNumber
);

void KeQueryNodeActiveAffinity(
              USHORT          NodeNumber,
   PGROUP_AFFINITY Affinity,
   PUSHORT         Count
);

NTSTATUS KeQueryNodeActiveAffinity2(
    USHORT          NodeNumber,
   PGROUP_AFFINITY GroupAffinities,
    USHORT          GroupAffinitiesCount,
   PUSHORT         GroupAffinitiesRequired
);

ULONG KeQueryNodeActiveProcessorCount(
   USHORT NodeNumber
);

USHORT KeQueryNodeMaximumProcessorCount(
   USHORT NodeNumber
);


NTHALAPI LARGE_INTEGER KeQueryPerformanceCounter(
   PLARGE_INTEGER PerformanceFrequency
);

KPRIORITY KeQueryPriorityThread(
   PKTHREAD Thread
);

ULONG KeQueryRuntimeThread(
    PKTHREAD Thread,
   PULONG   UserTime
);

void KeQuerySystemTime(
   PLARGE_INTEGER CurrentTime
);

void KeQuerySystemTimePrecise(
   PLARGE_INTEGER CurrentTime
);

//void KeQueryTickCount(
  //  CurrentCount
//);

ULONG KeQueryTimeIncrement();

ULONG64 KeQueryTotalCycleTimeThread(
   PKTHREAD Thread,
       PULONG64 CycleTimeStamp
);

ULONGLONG KeQueryUnbiasedInterruptTime();

VOID KeRaiseIrql(
    KIRQL  NewIrql,
   PKIRQL OldIrql
);

_DECL_HAL_KE_IMPORT KIRQL KeRaiseIrqlToDpcLevel();

LONG KeReadStateEvent(
   PRKEVENT Event
);

LONG KeReadStateMutex(
   PRKMUTEX Mutex
);

LONG KeReadStateSemaphore(
   PRKSEMAPHORE Semaphore
);

BOOLEAN KeReadStateTimer(
   PKTIMER Timer
);

PVOID KeRegisterBoundCallback(
   PBOUND_CALLBACK CallbackRoutine
);

BOOLEAN KeRegisterBugCheckCallback(
            PKBUGCHECK_CALLBACK_RECORD  CallbackRecord,
             PKBUGCHECK_CALLBACK_ROUTINE CallbackRoutine,
   PVOID                       Buffer,
             ULONG                       Length,
             PUCHAR                      Component
);

BOOLEAN KeRegisterBugCheckReasonCallback(
   PKBUGCHECK_REASON_CALLBACK_RECORD  CallbackRecord,
    PKBUGCHECK_REASON_CALLBACK_ROUTINE CallbackRoutine,
    KBUGCHECK_CALLBACK_REASON          Reason,
    PUCHAR                             Component
);

PVOID KeRegisterNmiCallback(
             PNMI_CALLBACK CallbackRoutine,
   PVOID         Context
);

PVOID KeRegisterProcessorChangeCallback(
             PPROCESSOR_CALLBACK_FUNCTION CallbackFunction,
   PVOID                        CallbackContext,
             ULONG                        Flags
);

void KeReleaseGuardedMutex(
   PKGUARDED_MUTEX Mutex
);

void KeReleaseGuardedMutexUnsafe(
   PKGUARDED_MUTEX FastMutex
);

void KeReleaseInStackQueuedSpinLock(
   PKLOCK_QUEUE_HANDLE LockHandle
);

void KeReleaseInStackQueuedSpinLockForDpc(
   PKLOCK_QUEUE_HANDLE LockHandle
);

void KeReleaseInStackQueuedSpinLockFromDpcLevel(
   PKLOCK_QUEUE_HANDLE LockHandle
);

void KeReleaseInterruptSpinLock(
   PKINTERRUPT Interrupt,
        KIRQL       OldIrql
);

LONG KeReleaseMutex(
   PRKMUTEX Mutex,
        BOOLEAN  Wait
);

LONG KeReleaseSemaphore(
   PRKSEMAPHORE Semaphore,
        KPRIORITY    Increment,
        LONG         Adjustment,
        BOOLEAN      Wait
);

VOID
KeReleaseSpinLock (
     PKSPIN_LOCK SpinLock,
     KIRQL NewIrql
);

void KeReleaseSpinLockForDpc(
   PKSPIN_LOCK SpinLock,
        KIRQL       OldIrql
);

void KeReleaseSpinLockFromDpcLevel(
   PKSPIN_LOCK SpinLock
);

PKDEVICE_QUEUE_ENTRY KeRemoveByKeyDeviceQueue(
   PKDEVICE_QUEUE DeviceQueue,
        ULONG          SortKey
);


PKDEVICE_QUEUE_ENTRY KeRemoveDeviceQueue(
   PKDEVICE_QUEUE DeviceQueue
);

BOOLEAN KeRemoveEntryDeviceQueue(
   PKDEVICE_QUEUE       DeviceQueue,
   PKDEVICE_QUEUE_ENTRY DeviceQueueEntry
);

BOOLEAN KeRemoveQueueDpc(
   PRKDPC Dpc
);

LONG KeResetEvent(
   PRKEVENT Event
);

void KeRestoreExtendedProcessorState(
   PXSTATE_SAVE XStateSave
);

NTSTATUS KeRestoreFloatingPointState(
   PKFLOATING_SAVE FloatSave
);

void KeRevertToUserAffinityThreadEx(
   KAFFINITY Affinity
);

void KeRevertToUserAffinityThreadEx(
   KAFFINITY Affinity
);

void KeRevertToUserGroupAffinityThread(
   PGROUP_AFFINITY PreviousAffinity
);

typedef struct _KERNEL_CET_CONTEXT {
  ULONG64 Ssp;
  ULONG64 Rip;
  USHORT  SegCs;
  union {
    USHORT AllFlags;
    struct {
      USHORT UseWrss : 1;
      USHORT PopShadowStackOne : 1;
      USHORT Unused : 14;
    } DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
  USHORT  Fill[2];
} KERNEL_CET_CONTEXT, *PKERNEL_CET_CONTEXT;

typedef struct _KERNEL_SOFT_RESTART_NOTIFICATION {
  USHORT Version;
  USHORT Size;
  GUID   Event;
} KERNEL_SOFT_RESTART_NOTIFICATION, *PKERNEL_SOFT_RESTART_NOTIFICATION;

NTSTATUS KeSaveExtendedProcessorState(
    ULONG64      Mask,
   PXSTATE_SAVE XStateSave
);

NTSTATUS KeSaveFloatingPointState(
   PKFLOATING_SAVE FloatSave
);

BOOLEAN KeSetCoalescableTimer(
        PKTIMER       Timer,
             LARGE_INTEGER DueTime,
             ULONG         Period,
             ULONG         TolerableDelay,
   PKDPC         Dpc
);

LONG KeSetEvent(
   PRKEVENT  Event,
        KPRIORITY Increment,
        BOOLEAN   Wait
);

void KeSetImportanceDpc(
   PRKDPC          Dpc,
        KDPC_IMPORTANCE Importance
);

KPRIORITY KeSetPriorityThread(
   PKTHREAD  Thread,
        KPRIORITY Priority
);

void KeSetSystemAffinityThread(
   KAFFINITY Affinity
);

KAFFINITY KeSetSystemAffinityThreadEx(
   KAFFINITY Affinity
);

void KeSetSystemGroupAffinityThread(
              PGROUP_AFFINITY Affinity,
   PGROUP_AFFINITY PreviousAffinity
);

void KeSetTargetProcessorDpc(
   PRKDPC Dpc,
        CCHAR  Number
);

NTSTATUS KeSetTargetProcessorDpcEx(
   PKDPC             Dpc,
        PPROCESSOR_NUMBER ProcNumber
);

BOOLEAN KeSetTimer(
        PKTIMER       Timer,
             LARGE_INTEGER DueTime,
   PKDPC         Dpc
);

BOOLEAN KeSetTimerEx(
        PKTIMER       Timer,
             LARGE_INTEGER DueTime,
             LONG          Period,
   PKDPC         Dpc
);

LOGICAL KeShouldYieldProcessor();

NTHALAPI VOID KeStallExecutionProcessor(
   ULONG MicroSeconds
);

NTHALAPI VOID KeStallExecutionProcessor(
   ULONG MicroSeconds
);


BOOLEAN KeSynchronizeExecution(
        PKINTERRUPT            Interrupt,
             PKSYNCHRONIZE_ROUTINE  SynchronizeRoutine,
    PVOID SynchronizeContext
);

BOOLEAN KeTestSpinLock(
   PKSPIN_LOCK SpinLock
);

BOOLEAN KeTryToAcquireGuardedMutex(
   PKGUARDED_MUTEX Mutex
);

BOOLEAN KeTryToAcquireSpinLockAtDpcLevel(
   PKSPIN_LOCK SpinLock
);

NTSTATUS
KeWaitForMultipleObjects (
    ULONG Count,
    PVOID Object[],
    WAIT_TYPE WaitType,
    KWAIT_REASON WaitReason,
    KPROCESSOR_MODE WaitMode,
    BOOLEAN Alertable,
    PLARGE_INTEGER Timeout,
    PKWAIT_BLOCK WaitBlockArray
    );

NTSTATUS
KeWaitForSingleObject (
    PVOID Object,
    KWAIT_REASON WaitReason,
    KPROCESSOR_MODE WaitMode,
    BOOLEAN Alertable,
    PLARGE_INTEGER Timeout
    );


void KzLowerIrql(
   KIRQL NewIrql
);

KIRQL KzRaiseIrql(
   KIRQL NewIrql
);



NTSTATUS MmAdvanceMdl(
   PMDL  Mdl,
        ULONG NumberOfBytes
);

PVOID MmAllocateContiguousMemory(
   SIZE_T           NumberOfBytes,
   PHYSICAL_ADDRESS HighestAcceptableAddress
);

NTSTATUS MmAllocateContiguousMemoryEx(
             PSIZE_T          NumberOfBytes,
             PHYSICAL_ADDRESS LowestAcceptableAddress,
             PHYSICAL_ADDRESS HighestAcceptableAddress,
             PHYSICAL_ADDRESS BoundaryAddressMultiple,
             NODE_REQUIREMENT PreferredNode,
             ULONG            Protect,
   PVOID            PartitionObject,
             ULONG            Tag,
             ULONG            Flags,
            PVOID            *BaseAddress
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

PVOID MmAllocateMappingAddress(
   SIZE_T NumberOfBytes,
   ULONG  PoolTag
);


PVOID MmAllocateMappingAddressEx(
  SIZE_T NumberOfBytes,
  ULONG  PoolTag,
  ULONG  Flags
);

NTSTATUS MmAllocateMdlForIoSpace(
    PMM_PHYSICAL_ADDRESS_LIST PhysicalAddressList,
    SIZE_T                    NumberOfEntries,
   PMDL                      *NewMdl
);

PMDL MmAllocateNodePagesForMdlEx(
   PHYSICAL_ADDRESS    LowAddress,
   PHYSICAL_ADDRESS    HighAddress,
   PHYSICAL_ADDRESS    SkipBytes,
   SIZE_T              TotalBytes,
   MEMORY_CACHING_TYPE CacheType,
   ULONG               IdealNode,
   ULONG               Flags
);

PMDL MmAllocatePagesForMdl(
   PHYSICAL_ADDRESS LowAddress,
   PHYSICAL_ADDRESS HighAddress,
   PHYSICAL_ADDRESS SkipBytes,
   SIZE_T           TotalBytes
);

PMDL MmAllocatePagesForMdlEx(
   PHYSICAL_ADDRESS    LowAddress,
   PHYSICAL_ADDRESS    HighAddress,
   PHYSICAL_ADDRESS    SkipBytes,
   SIZE_T              TotalBytes,
   MEMORY_CACHING_TYPE CacheType,
   ULONG               Flags
);

void MmBuildMdlForNonPagedPool(
   PMDL MemoryDescriptorList
);

void MmFreeContiguousMemory(
   PVOID BaseAddress
);

void MmFreeContiguousMemorySpecifyCache(
   PVOID               BaseAddress,
   SIZE_T              NumberOfBytes,
   MEMORY_CACHING_TYPE CacheType
);

void MmFreeMappingAddress(
   PVOID BaseAddress,
   ULONG PoolTag
);

void MmFreePagesFromMdl(
   PMDL MemoryDescriptorList
);

ULONG MmGetMdlByteCount(
   PMDL Mdl
);

PPFN_NUMBER MmGetMdlPfnArray(
   PMDL Mdl
);

PVOID MmGetSystemAddressForMdl(
   MDL
);

PVOID MmGetSystemRoutineAddress(
   PUNICODE_STRING SystemRoutineName
);

PVOID MmGetSystemRoutineAddressEx(
  PUNICODE_STRING ModuleName,
  PSTR            FunctionName
);

LOGICAL MmIsDriverSuspectForVerifier(
   _DRIVER_OBJECT *DriverObject
);

LOGICAL MmIsDriverVerifying(
   _DRIVER_OBJECT *DriverObject
);


LOGICAL MmIsDriverVerifyingByAddress(
   PVOID AddressWithinSection
);

//void MmLockPagableCodeSection(
//    Address
//);

PVOID MmLockPagableDataSection(
   PVOID AddressWithinSection
);

PVOID MmMapIoSpace(
   PHYSICAL_ADDRESS    PhysicalAddress,
   SIZE_T              NumberOfBytes,
   MEMORY_CACHING_TYPE CacheType
);

PVOID MmMapIoSpaceEx(
   PHYSICAL_ADDRESS PhysicalAddress,
   SIZE_T           NumberOfBytes,
   ULONG            Protect
);

PVOID MmMapLockedPages(
   PMDL MemoryDescriptorList,
   KPROCESSOR_MODE ,
   uint64_t _MODE,
    KPROCESSOR_MODE AccessMode
);

PVOID MmMapLockedPagesSpecifyCache(
             PMDL                                                                          MemoryDescriptorList,
             KPROCESSOR_MODE Mode,
   uint64_t MODE,
  KPROCESSOR_MODE AccessMode,
             MEMORY_CACHING_TYPE                      CacheType,
   PVOID                                                                         RequestedAddress,
             ULONG                                                                         BugCheckOnFailure,
             ULONG                                                                         Priority
);

PVOID MmMapLockedPagesWithReservedMapping(
   PVOID                                                    MappingAddress,
   ULONG                                                    PoolTag,
   PMDL                                                     MemoryDescriptorList,
   MEMORY_CACHING_TYPE CacheType
);

NTSTATUS MmMapMdl(
   PMDL            MemoryDescriptorList,
   ULONG           Protection,
   PMM_MDL_ROUTINE DriverRoutine,
   PVOID           DriverContext
);

NTSTATUS MmMapMemoryDumpMdlEx(
  PVOID      Va,
  PFN_NUMBER PageTotal,
  PMDL       MemoryDumpMdl,
  ULONG      Flags
);

PVOID MmPageEntireDriver(
   PVOID AddressWithinSection
);

void MmProbeAndLockPages(
   PMDL            MemoryDescriptorList,
        KPROCESSOR_MODE AccessMode,
        LOCK_OPERATION  Operation
);

void MmProbeAndLockSelectedPages(
   PMDL                  MemoryDescriptorList,
        PFILE_SEGMENT_ELEMENT SegmentArray,
        KPROCESSOR_MODE       AccessMode,
        LOCK_OPERATION        Operation
);

NTSTATUS MmProtectDriverSection(
   PVOID  AddressWithinSection,
   SIZE_T Size,
   ULONG  Flags
);

NTSTATUS MmProtectMdlSystemAddress(
   PMDL  MemoryDescriptorList,
   ULONG NewProtect
);

MM_SYSTEMSIZE MmQuerySystemSize();

void MmResetDriverPaging(
   PVOID AddressWithinSection
);

SIZE_T MmSizeOfMdl(
   PVOID  Base,
   SIZE_T Length
);


void MmUnlockPagableImageSection(
   PVOID ImageSectionHandle
);

void MmUnlockPages(
   PMDL MemoryDescriptorList
);

void MmUnmapIoSpace(
   PVOID  BaseAddress,
   SIZE_T NumberOfBytes
);

void MmUnmapLockedPages(
   PVOID BaseAddress,
   PMDL  MemoryDescriptorList
);

void MmUnmapReservedMapping(
   PVOID BaseAddress,
   ULONG PoolTag,
   PMDL  MemoryDescriptorList
);


LOUDDK_API_ENTRY
NTSTATUS 
NtCommitComplete(
  HANDLE         EnlistmentHandle,
  PLARGE_INTEGER TmVirtualClock
);

LOUDDK_API_ENTRY
NTSTATUS 
NtCommitEnlistment(
  HANDLE         EnlistmentHandle,
  PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NtCommitTransaction(
   HANDLE  TransactionHandle,
   BOOLEAN Wait
);

NTSYSCALLAPI NTSTATUS NtCreateEnlistment(
            PHANDLE            EnlistmentHandle,
             ACCESS_MASK        DesiredAccess,
             HANDLE             ResourceManagerHandle,
             HANDLE             TransactionHandle,
   POBJECT_ATTRIBUTES ObjectAttributes,
   ULONG              CreateOptions,
             NOTIFICATION_MASK  NotificationMask,
   PVOID              EnlistmentKey
);

NTSYSCALLAPI NTSTATUS NtCreateResourceManager(
            PHANDLE            ResourceManagerHandle,
             ACCESS_MASK        DesiredAccess,
             HANDLE             TmHandle,
             LPGUID             RmGuid,
   POBJECT_ATTRIBUTES ObjectAttributes,
   ULONG              CreateOptions,
   PUNICODE_STRING    Description
);

NTSYSCALLAPI NTSTATUS NtCreateTransaction(
            PHANDLE            TransactionHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
   LPGUID             Uow,
   HANDLE             TmHandle,
   ULONG              CreateOptions,
   ULONG              IsolationLevel,
   ULONG              IsolationFlags,
   PLARGE_INTEGER     Timeout,
   PUNICODE_STRING    Description
);

NTSYSCALLAPI NTSTATUS NtCreateTransactionManager(
            PHANDLE            TmHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
   PUNICODE_STRING    LogFileName,
   ULONG              CreateOptions,
   ULONG              CommitStrength
);

NTSYSCALLAPI NTSTATUS NtEnumerateTransactionObject(
   HANDLE            RootObjectHandle,
             KTMOBJECT_TYPE    QueryType,
        PKTMOBJECT_CURSOR ObjectCursor,
             ULONG             ObjectCursorLength,
            PULONG            ReturnLength
);

NTSYSCALLAPI NTSTATUS NtGetNotificationResourceManager(
              HANDLE                    ResourceManagerHandle,
             PTRANSACTION_NOTIFICATION TransactionNotification,
              ULONG                     NotificationLength,
              PLARGE_INTEGER            Timeout,
   PULONG                    ReturnLength,
              ULONG                     Asynchronous,
    ULONG_PTR                 AsynchronousContext
);

NTSYSCALLAPI NTSTATUS NtManagePartition(
             HANDLE                      TargetHandle,
   HANDLE                      SourceHandle,
             PARTITION_INFORMATION_CLASS PartitionInformationClass,
        PVOID                       PartitionInformation,
             ULONG                       PartitionInformationLength
);

NTSYSCALLAPI NTSTATUS NtOpenEnlistment(
            PHANDLE            EnlistmentHandle,
             ACCESS_MASK        DesiredAccess,
             HANDLE             ResourceManagerHandle,
             LPGUID             EnlistmentGuid,
   POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NtOpenResourceManager(
            PHANDLE            ResourceManagerHandle,
             ACCESS_MASK        DesiredAccess,
             HANDLE             TmHandle,
             LPGUID             ResourceManagerGuid,
   POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NtOpenTransaction(
            PHANDLE            TransactionHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
             LPGUID             Uow,
   HANDLE             TmHandle
);

NTSYSCALLAPI NTSTATUS NtOpenTransactionManager(
            PHANDLE            TmHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
   PUNICODE_STRING    LogFileName,
   LPGUID             TmIdentity,
   ULONG              OpenOptions
);

NTSYSCALLAPI NTSTATUS NtPowerInformation(
              POWER_INFORMATION_LEVEL InformationLevel,
    PVOID                   InputBuffer,
              ULONG                   InputBufferLength,
   PVOID                   OutputBuffer,
              ULONG                   OutputBufferLength
);

NTSYSCALLAPI NTSTATUS NtPrepareComplete(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NtPrepareEnlistment(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NtPrePrepareComplete(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NtPrePrepareEnlistment(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NtQueryInformationEnlistment(
              HANDLE                       EnlistmentHandle,
              ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
             PVOID                        EnlistmentInformation,
              ULONG                        EnlistmentInformationLength,
   PULONG                       ReturnLength
);

NTSYSCALLAPI NTSTATUS NtQueryInformationResourceManager(
              HANDLE                            ResourceManagerHandle,
              RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
             PVOID                             ResourceManagerInformation,
              ULONG                             ResourceManagerInformationLength,
   PULONG                            ReturnLength
);

NTSYSCALLAPI NTSTATUS NtQueryInformationTransaction(
              HANDLE                        TransactionHandle,
              TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
             PVOID                         TransactionInformation,
              ULONG                         TransactionInformationLength,
   PULONG                        ReturnLength
);

NTSYSCALLAPI NTSTATUS NtQueryInformationTransactionManager(
              HANDLE                               TransactionManagerHandle,
              TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
             PVOID                                TransactionManagerInformation,
              ULONG                                TransactionManagerInformationLength,
   PULONG                               ReturnLength
);

NTSYSCALLAPI NTSTATUS NtReadOnlyEnlistment(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NtRecoverEnlistment(
             HANDLE EnlistmentHandle,
   PVOID  EnlistmentKey
);

NTSYSCALLAPI NTSTATUS NtRecoverResourceManager(
   HANDLE ResourceManagerHandle
);

NTSYSCALLAPI NTSTATUS NtRecoverTransactionManager(
   HANDLE TransactionManagerHandle
);

NTSYSCALLAPI NTSTATUS NtRenameTransactionManager(
   PUNICODE_STRING LogFileName,
   LPGUID          ExistingTransactionManagerGuid
);

NTSYSCALLAPI NTSTATUS NtRollbackComplete(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NtRollbackEnlistment(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NtRollbackTransaction(
   HANDLE  TransactionHandle,
   BOOLEAN Wait
);

NTSYSCALLAPI NTSTATUS NtRollforwardTransactionManager(
             HANDLE         TransactionManagerHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NtSetInformationEnlistment(
   HANDLE                       EnlistmentHandle,
   ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
   PVOID                        EnlistmentInformation,
   ULONG                        EnlistmentInformationLength
);

NTSYSCALLAPI NTSTATUS NtSetInformationResourceManager(
  HANDLE                            ResourceManagerHandle,
  RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
  PVOID                             ResourceManagerInformation,
  ULONG                             ResourceManagerInformationLength
);

NTSYSCALLAPI NTSTATUS NtSetInformationTransaction(
   HANDLE                        TransactionHandle,
   TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
   PVOID                         TransactionInformation,
   ULONG                         TransactionInformationLength
);

NTSYSCALLAPI NTSTATUS NtSetInformationTransactionManager(
   HANDLE                               TmHandle,
             TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
             PVOID                                TransactionManagerInformation,
             ULONG                                TransactionManagerInformationLength
);

NTSYSCALLAPI NTSTATUS NtSinglePhaseReject(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);



NTSTATUS ObCloseHandle(
   HANDLE          Handle,
   KPROCESSOR_MODE PreviousMode
);

//void ObDereferenceObject(
//    a
//);

void ObDereferenceObjectDeferDelete(
   PVOID Object
);

void ObDereferenceObjectDeferDeleteWithTag(
   PVOID Object,
   ULONG Tag
);

//void ObDereferenceObjectWithTag(
//    a,
//    t
//);

LONG_PTR ObfReferenceObject(
   PVOID Object
);

NTSTATUS ObGetObjectSecurity(
    PVOID                Object,
   PSECURITY_DESCRIPTOR *SecurityDescriptor,
   PBOOLEAN             MemoryAllocated
);

//void ObReferenceObject(
//    Object
//);

NTSTATUS ObReferenceObjectByHandle(
              HANDLE                     Handle,
              ACCESS_MASK                DesiredAccess,
    POBJECT_TYPE               ObjectType,
              KPROCESSOR_MODE            AccessMode,
             PVOID                      *Object,
   POBJECT_HANDLE_INFORMATION HandleInformation
);

NTSTATUS ObReferenceObjectByHandleWithTag(
              HANDLE                     Handle,
              ACCESS_MASK                DesiredAccess,
    POBJECT_TYPE               ObjectType,
              KPROCESSOR_MODE            AccessMode,
              ULONG                      Tag,
             PVOID                      *Object,
   POBJECT_HANDLE_INFORMATION HandleInformation
);

NTSTATUS ObReferenceObjectByPointer(
             PVOID           Object,
             ACCESS_MASK     DesiredAccess,
   POBJECT_TYPE    ObjectType,
             KPROCESSOR_MODE AccessMode
);

NTSTATUS ObReferenceObjectByPointerWithTag(
             PVOID           Object,
             ACCESS_MASK     DesiredAccess,
   POBJECT_TYPE    ObjectType,
             KPROCESSOR_MODE AccessMode,
             ULONG           Tag
);

BOOLEAN ObReferenceObjectSafe(
  PVOID Object
);

//void ObReferenceObjectWithTag(
//    Object,
//    Tag
//);

NTSTATUS ObRegisterCallbacks(
    POB_CALLBACK_REGISTRATION CallbackRegistration,
   PVOID                     *RegistrationHandle
);

void ObReleaseObjectSecurity(
   PSECURITY_DESCRIPTOR SecurityDescriptor,
   BOOLEAN              MemoryAllocated
);

void ObUnRegisterCallbacks(
   PVOID RegistrationHandle
);



NTSTATUS PoCallDriver(
        PDEVICE_OBJECT        DeviceObject,
    PIRP Irp
);

NTSTATUS PoClearPowerRequest(
   PVOID              PowerRequest,
        POWER_REQUEST_TYPE Type
);

NTSTATUS PoCreatePowerRequest(
   PVOID                   *PowerRequest,
    PDEVICE_OBJECT          DeviceObject,
    PCOUNTED_REASON_CONTEXT Context
);

void PoDeletePowerRequest(
   PVOID PowerRequest
);

void PoEndDeviceBusy(
   PULONG IdlePointer
);

void PoFxActivateComponent(
   POHANDLE Handle,
   ULONG    Component,
   ULONG    Flags
);

void PoFxCompleteDevicePowerNotRequired(
   POHANDLE Handle
);

void PoFxCompleteDirectedPowerDown(
  POHANDLE Handle
);

void PoFxCompleteIdleCondition(
   POHANDLE Handle,
   ULONG    Component
);

void PoFxCompleteIdleState(
   POHANDLE Handle,
   ULONG    Component
);

void PoFxIdleComponent(
   POHANDLE Handle,
   ULONG    Component,
   ULONG    Flags
);

void PoFxIssueComponentPerfStateChange(
   POHANDLE                 Handle,
   ULONG                    Flags,
   ULONG                    Component,
   PPO_FX_PERF_STATE_CHANGE PerfChange,
   PVOID                    Context
);

void PoFxIssueComponentPerfStateChangeMultiple(
   POHANDLE                   Handle,
   ULONG                      Flags,
   ULONG                      Component,
   ULONG                      PerfChangesCount,
   PO_FX_PERF_STATE_CHANGE*  PerfChanges,
   PVOID                      Context
);

void PoFxNotifySurprisePowerOn(
   PDEVICE_OBJECT Pdo
);

NTSTATUS PoFxPowerControl(
              POHANDLE Handle,
              LPCGUID  PowerControlCode,
    PVOID    InBuffer,
              SIZE_T   InBufferSize,
   PVOID    OutBuffer,
              SIZE_T   OutBufferSize,
   PSIZE_T  BytesReturned
);

NTSTATUS PoFxPowerOnCrashdumpDevice(
             POHANDLE Handle,
   PVOID    Context
);

NTSTATUS PoFxQueryCurrentComponentPerfState(
   POHANDLE   Handle,
   ULONG      Flags,
   ULONG      Component,
   ULONG      SetIndex,
   PULONGLONG CurrentPerf
);

NTSTATUS PoFxRegisterComponentPerfStates(
    POHANDLE                             Handle,
    ULONG                                Component,
    ULONGLONG                            Flags,
    PPO_FX_COMPONENT_PERF_STATE_CALLBACK ComponentPerfStateCallback,
    PPO_FX_COMPONENT_PERF_INFO           InputStateInfo,
   PPO_FX_COMPONENT_PERF_INFO           *OutputStateInfo
);

NTSTATUS PoFxRegisterCrashdumpDevice(
  POHANDLE Handle
);

NTSTATUS PoFxRegisterDevice(
    PDEVICE_OBJECT Pdo,
    PPO_FX_DEVICE  Device,
   POHANDLE       *Handle
);

void PoFxReportDevicePoweredOn(
   POHANDLE Handle
);

void PoFxSetComponentLatency(
   POHANDLE  Handle,
   ULONG     Component,
   ULONGLONG Latency
);

void PoFxSetComponentResidency(
   POHANDLE  Handle,
   ULONG     Component,
   ULONGLONG Residency
);

void PoFxSetComponentWake(
   POHANDLE Handle,
   ULONG    Component,
   BOOLEAN  WakeHint
);

void PoFxSetDeviceIdleTimeout(
   POHANDLE  Handle,
   ULONGLONG IdleTimeout
);

NTSTATUS PoFxSetTargetDripsDevicePowerState(
   POHANDLE           Handle,
   DEVICE_POWER_STATE TargetState
);

void PoFxStartDevicePowerManagement(
   POHANDLE Handle
);

void PoFxUnregisterDevice(
   POHANDLE Handle
);

BOOLEAN PoGetSystemWake(
   PIRP Irp
);



PSINGLE_LIST_ENTRY PopEntryList(
   PSINGLE_LIST_ENTRY ListHead
);

BOOLEAN PoQueryWatchdogTime(
    PDEVICE_OBJECT Pdo,
   PULONG         SecondsRemaining
);

PULONG PoRegisterDeviceForIdleDetection(
   PDEVICE_OBJECT     DeviceObject,
   ULONG              ConservationIdleTime,
   ULONG              PerformanceIdleTime,
   DEVICE_POWER_STATE State
);


NTSTATUS PoRegisterPowerSettingCallback(
   PDEVICE_OBJECT          DeviceObject,
             LPCGUID                 SettingGuid,
             PPOWER_SETTING_CALLBACK Callback,
   PVOID                   Context,
            PVOID                   *Handle
);

PVOID PoRegisterSystemState(
   PVOID           StateHandle,
        EXECUTION_STATE Flags
);

NTSTATUS PoRequestPowerIrp(
             PDEVICE_OBJECT          DeviceObject,
             UCHAR                   MinorFunction,
             POWER_STATE             PowerState,
   PREQUEST_POWER_COMPLETE CompletionFunction,
    PVOID  Context,
            PIRP                    *Irp
);

//void PoSetDeviceBusy(
//    IdlePointer
//);

void PoSetDeviceBusyEx(
   PULONG IdlePointer
);

NTSTATUS PoSetPowerRequest(
   PVOID              PowerRequest,
        POWER_REQUEST_TYPE Type
);

POWER_STATE PoSetPowerState(
   PDEVICE_OBJECT   DeviceObject,
   POWER_STATE_TYPE Type,
   POWER_STATE      State
);

void PoSetSystemState(
   EXECUTION_STATE Flags
);

void PoSetSystemWake(
   PIRP Irp
);

void PoSetSystemWakeDevice(
   PDEVICE_OBJECT DeviceObject
);

void PoStartDeviceBusy(
   PULONG IdlePointer
);

void PoStartNextPowerIrp(
   PIRP Irp
);

NTSTATUS PoUnregisterPowerSettingCallback(
   PVOID Handle
);

void PoUnregisterSystemState(
   PVOID StateHandle
);

typedef enum _POWER_MONITOR_REQUEST_TYPE {
  MonitorRequestTypeOff,
  MonitorRequestTypeOnAndPresent,
  MonitorRequestTypeToggleOn
} POWER_MONITOR_REQUEST_TYPE;




typedef enum {
  UserNotPresent,
  UserPresent,
  UserUnknown
} POWER_USER_PRESENCE_TYPE, *PPOWER_USER_PRESENCE_TYPE;

void ProbeForRead(
   const volatile VOID *Address,
   SIZE_T              Length,
   ULONG               Alignment
);

void ProbeForWrite(
   volatile VOID *Address,
        SIZE_T        Length,
        ULONG         Alignment
);

NTSTATUS PsAllocateAffinityToken(
   PAFFINITY_TOKEN *AffinityToken
);

NTSTATUS PsCreateSystemThread(
             PHANDLE            ThreadHandle,
              ULONG              DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    HANDLE             ProcessHandle,
   PCLIENT_ID         ClientId,
              PKSTART_ROUTINE    StartRoutine,
    PVOID              StartContext
);

void PsFreeAffinityToken(
  PAFFINITY_TOKEN AffinityToken
);

PETHREAD PsGetCurrentThread();

LOUDDK_API_ENTRY
bool
PsGetVersion(
    PULONG              MajorVersion, 
    PULONG              MinorVersion, 
    PULONG              BuildNumber,
    PUNICODE_STRING     CsdVersion
);

ULONG64 PsQueryTotalCycleTimeProcess(
   PEPROCESS Process,
       PULONG64  CycleTimeStamp
);

void PsRevertToUserMultipleGroupAffinityThread(
   PAFFINITY_TOKEN AffinityToken
);

NTSTATUS PsSetSystemMultipleGroupAffinityThread(
        PGROUP_AFFINITY GroupAffinities,
        USHORT          GroupCount,
   PAFFINITY_TOKEN AffinityToken
);

NTSTATUS PsTerminateSystemThread(
   NTSTATUS ExitStatus
);

typedef struct _PTM_CONTROL_INTERFACE {
  USHORT                        Size;
  USHORT                        Version;
  PVOID                         Context;
  PINTERFACE_REFERENCE          InterfaceReference;
  PINTERFACE_DEREFERENCE        InterfaceDereference;
  PPTM_DEVICE_QUERY_GRANULARITY QueryGranularity;
  PPTM_DEVICE_QUERY_TIME_SOURCE QueryTimeSource;
  PPTM_DEVICE_ENABLE            Enable;
  PPTM_DEVICE_DISABLE           Disable;
} PTM_CONTROL_INTERFACE, *PPTM_CONTROL_INTERFACE;

void PushEntryList(
   PSINGLE_LIST_ENTRY                  ListHead,
    PSINGLE_LIST_ENTRY Entry
);


UCHAR ReadBooleanRaw(
  BOOLEAN const volatile *Source
);

INT32 ReadInt32Acquire(
  INT32 const volatile *Source
);

INT32 ReadInt32NoFence(
  INT32 const volatile *Source
);

INT32 ReadInt32Raw(
  INT32 const volatile *Source
);

UINT32 ReadUInt32Acquire(
  UINT32 const volatile *Source
);

UINT32 ReadUInt32NoFence(
  UINT32 const volatile *Source
);

UINT32 ReadUInt32Raw(
  UINT32 const volatile *Source
);

BOOLEAN RemoveEntryList(
   PLIST_ENTRY Entry
);

PLIST_ENTRY RemoveHeadList(
   PLIST_ENTRY ListHead
);

PLIST_ENTRY RemoveTailList(
   PLIST_ENTRY ListHead
);



  
  ULONG
  RtlAnsiStringToUnicodeSize(
  PANSI_STRING AnsiString
  );


#define RtlAnsiStringToUnicodeSize(STRING) (                 \
    RtlxAnsiStringToUnicodeSize(STRING)                      \
)



 NTSTATUS RtlAnsiStringToUnicodeString(
   PUNICODE_STRING DestinationString,
        PCANSI_STRING   SourceString,
        BOOLEAN         AllocateDestinationString
);


 NTSTATUS RtlAppendUnicodeStringToString(
   PUNICODE_STRING  Destination,
        PCUNICODE_STRING Source
);

 NTSTATUS RtlAppendUnicodeToString(
        PUNICODE_STRING Destination,
   PCWSTR          Source
);


BOOLEAN RtlAreBitsClear(
   PRTL_BITMAP BitMapHeader,
   ULONG       StartingIndex,
   ULONG       Length
);

BOOLEAN RtlAreBitsSet(
   PRTL_BITMAP BitMapHeader,
   ULONG       StartingIndex,
   ULONG       Length
);


BOOLEAN RtlCheckBit(
   PRTL_BITMAP BitMapHeader,
   ULONG       BitPosition
);

 NTSTATUS RtlCheckRegistryKey(
   ULONG RelativeTo,
   PWSTR Path
);

 VOID RtlClearAllBits(
   PRTL_BITMAP BitMapHeader
);

 VOID RtlClearBit(
   PRTL_BITMAP BitMapHeader,
   ULONG       BitNumber
);

 VOID RtlClearBits(
   PRTL_BITMAP BitMapHeader,
   ULONG       StartingIndex,
   ULONG       NumberToClear
);

 ULONGLONG RtlCmDecodeMemIoResource(
              PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor,
   PULONGLONG                      Start
);

 NTSTATUS RtlCmEncodeMemIoResource(
   PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor,
   UCHAR                           Type,
   ULONGLONG                       Length,
   ULONGLONG                       Start
);

 SIZE_T RtlCompareMemory(
   const VOID *Source1,
   const VOID *Source2,
   SIZE_T     Length
);

 LONG RtlCompareUnicodeString(
   PCUNICODE_STRING String1,
   PCUNICODE_STRING String2,
   BOOLEAN          CaseInSensitive
);

int RtlConstantTimeEqualMemory(
  const void    *v1,
  const void    *v2,
  unsigned long len
);

LARGE_INTEGER NTAPI_INLINE RtlConvertLongToLargeInteger(
   LONG SignedInteger
);

LARGE_INTEGER NTAPI_INLINE RtlConvertUlongToLargeInteger(
   ULONG UnsignedInteger
);

void RtlCopyMemory(
   void*       Destination,
   const void* Source,
   size_t      Length
);

 VOID RtlCopyMemoryNonTemporal(
  VOID       *Destination,
  const VOID *Source,
  SIZE_T     Length
);

 VOID RtlCopyUnicodeString(
        PUNICODE_STRING  DestinationString,
   PCUNICODE_STRING SourceString
);

 NTSTATUS RtlCreateRegistryKey(
   ULONG RelativeTo,
   PWSTR Path
);

 NTSTATUS RtlCreateSecurityDescriptor(
   PSECURITY_DESCRIPTOR SecurityDescriptor,
    ULONG                Revision
);

 NTSTATUS RtlDeleteRegistryValue(
   ULONG  RelativeTo,
   PCWSTR Path,
   PCWSTR ValueName
);

 WCHAR RtlDowncaseUnicodeChar(
   WCHAR SourceCharacter
);

BOOLEAN
RtlEqualMemory(
    void*  Destination,
    void*  Source,
    size_t Length
);

 BOOLEAN RtlEqualUnicodeString(
   PCUNICODE_STRING String1,
   PCUNICODE_STRING String2,
   BOOLEAN          CaseInSensitive
);

void RtlFillMemory(
   void*  Destination,
   size_t Length,
   int    Fill
);


 VOID RtlFillMemoryNonTemporal(
  VOID        *Destination,
  SIZE_T      Length,
  const UCHAR Value
);

 ULONG RtlFindClearBits(
   PRTL_BITMAP BitMapHeader,
   ULONG       NumberToFind,
   ULONG       HintIndex
);

 ULONG RtlFindClearBitsAndSet(
   PRTL_BITMAP BitMapHeader,
   ULONG       NumberToFind,
   ULONG       HintIndex
);

 ULONG RtlFindClearRuns(
    PRTL_BITMAP     BitMapHeader,
   PRTL_BITMAP_RUN RunArray,
    ULONG           SizeOfRunArray,
    BOOLEAN         LocateLongestRuns
);

 ULONG RtlFindFirstRunClear(
    PRTL_BITMAP BitMapHeader,
   PULONG      StartingIndex
);

 ULONG RtlFindLastBackwardRunClear(
    PRTL_BITMAP BitMapHeader,
    ULONG       FromIndex,
   PULONG      StartingRunIndex
);

 CCHAR RtlFindLeastSignificantBit(
   ULONGLONG Set
);

 ULONG RtlFindLongestRunClear(
    PRTL_BITMAP BitMapHeader,
   PULONG      StartingIndex
);

 CCHAR RtlFindMostSignificantBit(
   ULONGLONG Set
);

 ULONG RtlFindNextForwardRunClear(
    PRTL_BITMAP BitMapHeader,
    ULONG       FromIndex,
   PULONG      StartingRunIndex
);

 ULONG RtlFindSetBits(
   PRTL_BITMAP BitMapHeader,
   ULONG       NumberToFind,
   ULONG       HintIndex
);




 ULONG RtlFindSetBitsAndClear(
   PRTL_BITMAP BitMapHeader,
   ULONG       NumberToFind,
   ULONG       HintIndex
);


 VOID RtlFreeAnsiString(
   PANSI_STRING AnsiString
);


 VOID RtlFreeUnicodeString(
   PUNICODE_STRING UnicodeString
);

 VOID RtlFreeUTF8String(
  PUTF8_STRING utf8String
);

 NTSTATUS RtlGetVersion(
   PRTL_OSVERSIONINFOW lpVersionInformation
);

 NTSTATUS RtlGUIDFromString(
    PCUNICODE_STRING GuidString,
   GUID             *Guid
);

 NTSTATUS RtlHashUnicodeString(
    PCUNICODE_STRING String,
    BOOLEAN          CaseInSensitive,
    ULONG            HashAlgorithm,
   PULONG           HashValue
);

 VOID RtlInitAnsiString(
            PANSI_STRING          DestinationString,
    PCSZ SourceString
);

 VOID RtlInitializeBitMap(
   PRTL_BITMAP             BitMapHeader,
     PULONG BitMapBuffer,
    ULONG                   SizeOfBitMap
);

 VOID RtlInitString(
            PSTRING               DestinationString,
    PCSZ SourceString
);



 VOID RtlInitUnicodeString(
            PUNICODE_STRING         DestinationString,
    PCWSTR SourceString
);


 VOID RtlInitUTF8String(
  PUTF8_STRING          DestinationString,
   PCSZ SourceString
);

 NTSTATUS RtlInitUTF8StringEx(
  PUTF8_STRING          DestinationString,
   PCSZ SourceString
);

 NTSTATUS RtlInt64ToUnicodeString(
             ULONGLONG       Value,
   ULONG           Base,
        PUNICODE_STRING String
);

 NTSTATUS RtlIntegerToUnicodeString(
             ULONG           Value,
   ULONG           Base,
        PUNICODE_STRING String
);

//void RtlIntPtrToUnicodeString(
//              Value,
//    Base,
//         String
//);

 ULONGLONG RtlIoDecodeMemIoResource(
              PIO_RESOURCE_DESCRIPTOR Descriptor,
   PULONGLONG              Alignment,
   PULONGLONG              MinimumAddress,
   PULONGLONG              MaximumAddress
);

 NTSTATUS RtlIoEncodeMemIoResource(
   PIO_RESOURCE_DESCRIPTOR Descriptor,
   UCHAR                   Type,
   ULONGLONG               Length,
   ULONGLONG               Alignment,
   ULONGLONG               MinimumAddress,
   ULONGLONG               MaximumAddress
);

BOOLEAN RtlIsNtDdiVersionAvailable(
   ULONG Version
);

BOOLEAN RtlIsServicePackVersionInstalled(
   ULONG Version
);

 ULONG RtlLengthSecurityDescriptor(
   PSECURITY_DESCRIPTOR SecurityDescriptor
);

void RtlMoveMemory(
   void*       Destination,
   const void* Source,
   size_t      Length
);


 ULONG RtlNumberOfClearBits(
   PRTL_BITMAP BitMapHeader
);

 ULONG RtlNumberOfSetBits(
   PRTL_BITMAP BitMapHeader
);

 ULONG RtlNumberOfSetBitsUlongPtr(
   ULONG_PTR Target
);

 VOID RtlPrefetchMemoryNonTemporal(
   PVOID  Source,
   SIZE_T Length
);

 NTSTATUS RtlQueryRegistryValues(
             ULONG                     RelativeTo,
             PCWSTR                    Path,
        PRTL_QUERY_REGISTRY_TABLE QueryTable,
   PVOID                     Context,
   PVOID                     Environment
);

void RtlSanitizeUnicodeStringPadding(
  PUNICODE_STRING String
);

PVOID RtlSecureZeroMemory(
   PVOID  ptr,
    SIZE_T cnt
);

 VOID RtlSetAllBits(
   PRTL_BITMAP BitMapHeader
);

 VOID RtlSetBit(
   PRTL_BITMAP BitMapHeader,
   ULONG       BitNumber
);

 VOID RtlSetBits(
   PRTL_BITMAP BitMapHeader,
   ULONG       StartingIndex,
   ULONG       NumberToSet
);

 NTSTATUS RtlSetDaclSecurityDescriptor(
        PSECURITY_DESCRIPTOR SecurityDescriptor,
             BOOLEAN              DaclPresent,
   PACL                 Dacl,
   BOOLEAN              DaclDefaulted
);

 NTSTATUS RtlStringFromGUID(
    REFGUID         Guid,
   PUNICODE_STRING GuidString
);

 BOOLEAN RtlTestBit(
   PRTL_BITMAP BitMapHeader,
   ULONG       BitNumber
);

 BOOLEAN RtlTimeFieldsToTime(
    PTIME_FIELDS   TimeFields,
   PLARGE_INTEGER Time
);


 VOID RtlTimeToTimeFields(
    PLARGE_INTEGER Time,
   PTIME_FIELDS   TimeFields
);

 ULONG RtlUlongByteSwap(
   ULONG Source
);

 ULONGLONG RtlUlonglongByteSwap(
  ULONGLONG Source
);

void RtlUnicodeStringToAnsiSize(
    STRING
);

 NTSTATUS RtlUnicodeStringToAnsiString(
   PANSI_STRING     DestinationString,
        PCUNICODE_STRING SourceString,
        BOOLEAN          AllocateDestinationString
);

 NTSTATUS RtlUnicodeStringToInteger(
             PCUNICODE_STRING String,
   ULONG            Base,
            PULONG           Value
);

 NTSTATUS RtlUnicodeStringToUTF8String(
  PUTF8_STRING     DestinationString,
  PCUNICODE_STRING SourceString,
  BOOLEAN          AllocateDestinationString
);


LOUDDK_API_ENTRY
WCHAR RtlUpcaseUnicodeChar(
   WCHAR SourceCharacter
);

 USHORT RtlUshortByteSwap(
   USHORT Source
);


 NTSTATUS RtlUTF8StringToUnicodeString(
  PUNICODE_STRING DestinationString,
  PUTF8_STRING    SourceString,
  BOOLEAN         AllocateDestinationString
);


 BOOLEAN RtlValidRelativeSecurityDescriptor(
   PSECURITY_DESCRIPTOR SecurityDescriptorInput,
   ULONG                SecurityDescriptorLength,
   SECURITY_INFORMATION RequiredInformation
);

 BOOLEAN RtlValidSecurityDescriptor(
   PSECURITY_DESCRIPTOR SecurityDescriptor
);

 NTSTATUS RtlVerifyVersionInfo(
   PRTL_OSVERSIONINFOEXW VersionInfo,
   ULONG                 TypeMask,
   ULONGLONG             ConditionMask
);

 NTSTATUS RtlWriteRegistryValue(
             ULONG  RelativeTo,
             PCWSTR Path,
             PCWSTR ValueName,
             ULONG  ValueType,
   PVOID  ValueData,
             ULONG  ValueLength
);

 ULONG RtlxAnsiStringToUnicodeSize(
   PCANSI_STRING AnsiString
);

 ULONG RtlxUnicodeStringToAnsiSize(
   PCUNICODE_STRING UnicodeString
);

void RtlZeroMemory(
   void*  Destination,
   size_t Length
);



BOOLEAN SeAccessCheck(
    PSECURITY_DESCRIPTOR      SecurityDescriptor,
    PSECURITY_SUBJECT_CONTEXT SubjectSecurityContext,
    BOOLEAN                   SubjectContextLocked,
    ACCESS_MASK               DesiredAccess,
    ACCESS_MASK               PreviouslyGrantedAccess,
   PPRIVILEGE_SET            *Privileges,
    PGENERIC_MAPPING          GenericMapping,
    KPROCESSOR_MODE           AccessMode,
   PACCESS_MASK              GrantedAccess,
   PNTSTATUS                 AccessStatus
);


NTSTATUS SeAssignSecurity(
   PSECURITY_DESCRIPTOR      ParentDescriptor,
   PSECURITY_DESCRIPTOR      ExplicitDescriptor,
            PSECURITY_DESCRIPTOR      *NewDescriptor,
             BOOLEAN                   IsDirectoryObject,
             PSECURITY_SUBJECT_CONTEXT SubjectContext,
             PGENERIC_MAPPING          GenericMapping,
             POOL_TYPE                 PoolType
);



NTSTATUS SeAssignSecurityEx(
   PSECURITY_DESCRIPTOR      ParentDescriptor,
   PSECURITY_DESCRIPTOR      ExplicitDescriptor,
            PSECURITY_DESCRIPTOR      *NewDescriptor,
   GUID                      *ObjectType,
             BOOLEAN                   IsDirectoryObject,
             ULONG                     AutoInheritFlags,
             PSECURITY_SUBJECT_CONTEXT SubjectContext,
             PGENERIC_MAPPING          GenericMapping,
             POOL_TYPE                 PoolType
);


NTSTATUS SeDeassignSecurity(
   PSECURITY_DESCRIPTOR *SecurityDescriptor
);


BOOLEAN SeValidSecurityDescriptor(
   ULONG                Length,
   PSECURITY_DESCRIPTOR SecurityDescriptor
);



NTSTATUS TmCommitComplete(
   PKENLISTMENT   Enlistment,
   PLARGE_INTEGER TmVirtualClock
);

NTSTATUS TmCommitEnlistment(
   PKENLISTMENT   Enlistment,
   PLARGE_INTEGER TmVirtualClock
);

NTSTATUS TmCommitTransaction(
   PKTRANSACTION Transaction,
   BOOLEAN       Wait
);

NTSTATUS TmCreateEnlistment(
            PHANDLE            EnlistmentHandle,
             KPROCESSOR_MODE    PreviousMode,
             ACCESS_MASK        DesiredAccess,
             POBJECT_ATTRIBUTES ObjectAttributes,
             PRKRESOURCEMANAGER ResourceManager,
             PKTRANSACTION      Transaction,
   ULONG              CreateOptions,
             NOTIFICATION_MASK  NotificationMask,
   PVOID              EnlistmentKey
);

NTSTATUS TmDereferenceEnlistmentKey(
              PKENLISTMENT Enlistment,
   PBOOLEAN     LastReference
);

NTSTATUS TmEnableCallbacks(
             PKRESOURCEMANAGER   ResourceManager,
             PTM_RM_NOTIFICATION CallbackRoutine,
   PVOID               RMKey
);

void TmGetTransactionId(
    PKTRANSACTION Transaction,
   PUOW          TransactionId
);

NTSTATUS TmInitializeTransactionManager(
             PRKTM            TransactionManager,
   PCUNICODE_STRING LogFileName,
             PGUID            TmId,
   ULONG            CreateOptions
);

BOOLEAN TmIsTransactionActive(
   PKTRANSACTION Transaction
);

NTSTATUS TmPrepareComplete(
   PKENLISTMENT   Enlistment,
   PLARGE_INTEGER TmVirtualClock
);

NTSTATUS TmPrepareEnlistment(
   PKENLISTMENT   Enlistment,
   PLARGE_INTEGER TmVirtualClock
);

NTSTATUS TmPrePrepareComplete(
   PKENLISTMENT   Enlistment,
   PLARGE_INTEGER TmVirtualClock
);

NTSTATUS TmPrePrepareEnlistment(
   PKENLISTMENT   Enlistment,
   PLARGE_INTEGER TmVirtualClock
);

NTSTATUS TmReadOnlyEnlistment(
   PKENLISTMENT   Enlistment,
   PLARGE_INTEGER TmVirtualClock
);

NTSTATUS TmRecoverEnlistment(
   PKENLISTMENT Enlistment,
   PVOID        EnlistmentKey
);

NTSTATUS TmRecoverResourceManager(
   PKRESOURCEMANAGER ResourceManager
);

NTSTATUS TmRecoverTransactionManager(
   PKTM           Tm,
   PLARGE_INTEGER TargetVirtualClock
);

NTSTATUS TmReferenceEnlistmentKey(
    PKENLISTMENT Enlistment,
   PVOID        *Key
);



NTSTATUS TmRenameTransactionManager(
   PUNICODE_STRING LogFileName,
   LPGUID          ExistingTransactionManagerGuid
);

NTSTATUS TmRequestOutcomeEnlistment(
   PKENLISTMENT   Enlistment,
   PLARGE_INTEGER TmVirtualClock
);

NTSTATUS TmRollbackComplete(
   PKENLISTMENT   Enlistment,
   PLARGE_INTEGER TmVirtualClock
);

NTSTATUS TmRollbackEnlistment(
   PKENLISTMENT   Enlistment,
   PLARGE_INTEGER TmVirtualClock
);

NTSTATUS TmRollbackTransaction(
   PKTRANSACTION Transaction,
   BOOLEAN       Wait
);

NTSTATUS TmSinglePhaseReject(
   PKENLISTMENT   Enlistment,
   PLARGE_INTEGER TmVirtualClock
);


NTSTATUS VslCreateSecureSection(
  PHANDLE   Handle,
  PEPROCESS TargetProcess,
  PMDL      Mdl,
  ULONG     DevicePageProtection,
  ULONG     Attributes
);

NTSTATUS VslDeleteSecureSection(
  HANDLE GlobalHandle
);


LOUDDK_API_ENTRY
NTSTATUS 
WmiQueryTraceInformation(
   TRACE_INFORMATION_CLASS TraceInformationClass,
   PVOID                   TraceInformation,
   ULONG                   TraceInformationLength,
   PULONG                  RequiredLength,
   PVOID                   Buffer
);

LOUDDK_API_ENTRY
NTSTATUS 
WmiTraceMessage(
   TRACEHANDLE LoggerHandle,
   ULONG       MessageFlags,
   LPCGUID     MessageGuid,
   USHORT      MessageNumber,
       ...
);

LOUDDK_API_ENTRY
NTSTATUS 
WmiTraceMessageVa(
   TRACEHANDLE LoggerHandle,
   ULONG       MessageFlags,
   LPCGUID     MessageGuid,
   USHORT      MessageNumber,
   va_list     MessageArgList
);

////



void WriteInt32NoFence(
  INT32 volatile *Destination,
  INT32          Value
);

void WriteInt32Raw(
  INT32 volatile *Destination,
  INT32          Value
);

void WriteInt32Release(
  INT32 volatile *Destination,
  INT32          Value
);


void WriteUInt32NoFence(
  UINT32 volatile *Destination,
  UINT32          Value
);

void WriteUInt32Raw(
  UINT32 volatile *Destination,
  UINT32          Value
);

void WriteUInt32Release(
  UINT32 volatile *Destination,
  UINT32          Value
);



 NTSTATUS ZwClose(
   HANDLE Handle
);

NTSYSCALLAPI NTSTATUS ZwCommitComplete(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS ZwCommitEnlistment(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS ZwCommitTransaction(
   HANDLE  TransactionHandle,
   BOOLEAN Wait
);

 NTSTATUS ZwCreateDirectoryObject(
   PHANDLE            DirectoryHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS ZwCreateEnlistment(
            PHANDLE            EnlistmentHandle,
             ACCESS_MASK        DesiredAccess,
             HANDLE             ResourceManagerHandle,
             HANDLE             TransactionHandle,
   POBJECT_ATTRIBUTES ObjectAttributes,
   ULONG              CreateOptions,
             NOTIFICATION_MASK  NotificationMask,
   PVOID              EnlistmentKey
);

 NTSTATUS ZwCreateFile(
            PHANDLE            FileHandle,
             ACCESS_MASK        DesiredAccess,
             POBJECT_ATTRIBUTES ObjectAttributes,
            PIO_STATUS_BLOCK   IoStatusBlock,
   PLARGE_INTEGER     AllocationSize,
             ULONG              FileAttributes,
             ULONG              ShareAccess,
             ULONG              CreateDisposition,
             ULONG              CreateOptions,
   PVOID              EaBuffer,
             ULONG              EaLength
);

 NTSTATUS ZwCreateKey(
             PHANDLE            KeyHandle,
              ACCESS_MASK        DesiredAccess,
              POBJECT_ATTRIBUTES ObjectAttributes,
                  ULONG              TitleIndex,
    PUNICODE_STRING    Class,
              ULONG              CreateOptions,
   PULONG             Disposition
);

 NTSTATUS ZwCreateKeyTransacted(
             PHANDLE            KeyHandle,
              ACCESS_MASK        DesiredAccess,
              POBJECT_ATTRIBUTES ObjectAttributes,
                  ULONG              TitleIndex,
    PUNICODE_STRING    Class,
              ULONG              CreateOptions,
              HANDLE             TransactionHandle,
   PULONG             Disposition
);

NTSYSCALLAPI NTSTATUS ZwCreateResourceManager(
            PHANDLE            ResourceManagerHandle,
             ACCESS_MASK        DesiredAccess,
             HANDLE             TmHandle,
   LPGUID             ResourceManagerGuid,
   POBJECT_ATTRIBUTES ObjectAttributes,
   ULONG              CreateOptions,
   PUNICODE_STRING    Description
);

 NTSTATUS ZwCreateSection(
            PHANDLE            SectionHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
   PLARGE_INTEGER     MaximumSize,
             ULONG              SectionPageProtection,
             ULONG              AllocationAttributes,
   HANDLE             FileHandle
);

NTSYSCALLAPI NTSTATUS ZwCreateTransaction(
            PHANDLE            TransactionHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
   LPGUID             Uow,
   HANDLE             TmHandle,
   ULONG              CreateOptions,
   ULONG              IsolationLevel,
   ULONG              IsolationFlags,
   PLARGE_INTEGER     Timeout,
   PUNICODE_STRING    Description
);

NTSYSCALLAPI NTSTATUS ZwCreateTransactionManager(
            PHANDLE            TmHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
   PUNICODE_STRING    LogFileName,
   ULONG              CreateOptions,
   ULONG              CommitStrength
);

 NTSTATUS ZwDeleteKey(
   HANDLE KeyHandle
);

 NTSTATUS ZwDeleteValueKey(
   HANDLE          KeyHandle,
   PUNICODE_STRING ValueName
);

 NTSTATUS ZwEnumerateKey(
              HANDLE                KeyHandle,
              ULONG                 Index,
              KEY_INFORMATION_CLASS KeyInformationClass,
   PVOID                 KeyInformation,
              ULONG                 Length,
             PULONG                ResultLength
);

NTSYSCALLAPI NTSTATUS ZwEnumerateTransactionObject(
   HANDLE            RootObjectHandle,
             KTMOBJECT_TYPE    QueryType,
        PKTMOBJECT_CURSOR ObjectCursor,
             ULONG             ObjectCursorLength,
            PULONG            ReturnLength
);

 NTSTATUS ZwEnumerateValueKey(
              HANDLE                      KeyHandle,
              ULONG                       Index,
              KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
   PVOID                       KeyValueInformation,
              ULONG                       Length,
             PULONG                      ResultLength
);

 NTSTATUS ZwFlushKey(
   HANDLE KeyHandle
);


NTSYSCALLAPI NTSTATUS ZwGetNotificationResourceManager(
              HANDLE                    ResourceManagerHandle,
             PTRANSACTION_NOTIFICATION TransactionNotification,
              ULONG                     NotificationLength,
              PLARGE_INTEGER            Timeout,
   PULONG                    ReturnLength,
              ULONG                     Asynchronous,
    ULONG_PTR                 AsynchronousContext
);

 NTSTATUS ZwLoadDriver(
   PUNICODE_STRING DriverServiceName
);

 NTSTATUS ZwMakeTemporaryObject(
   HANDLE Handle
);

 NTSTATUS ZwMapViewOfSection(
                  HANDLE          SectionHandle,
                  HANDLE          ProcessHandle,
             PVOID           *BaseAddress,
                  ULONG_PTR       ZeroBits,
                  SIZE_T          CommitSize,
    PLARGE_INTEGER  SectionOffset,
             PSIZE_T         ViewSize,
                  SECTION_INHERIT InheritDisposition,
                  ULONG           AllocationType,
                  ULONG           Win32Protect
);

NTSYSCALLAPI NTSTATUS ZwOpenEnlistment(
            PHANDLE            EnlistmentHandle,
             ACCESS_MASK        DesiredAccess,
             HANDLE             RmHandle,
             LPGUID             EnlistmentGuid,
   POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS ZwOpenEvent(
   PHANDLE            EventHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes
);

 NTSTATUS ZwOpenFile(
   PHANDLE            FileHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
   PIO_STATUS_BLOCK   IoStatusBlock,
    ULONG              ShareAccess,
    ULONG              OpenOptions
);

 NTSTATUS ZwOpenKey(
   PHANDLE            KeyHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes
);

 NTSTATUS ZwOpenKeyEx(
   PHANDLE            KeyHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    ULONG              OpenOptions
);

 NTSTATUS ZwOpenKeyTransacted(
   PHANDLE            KeyHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    HANDLE             TransactionHandle
);

 NTSTATUS ZwOpenKeyTransactedEx(
   PHANDLE            KeyHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    ULONG              OpenOptions,
    HANDLE             TransactionHandle
);

NTSYSCALLAPI NTSTATUS ZwOpenResourceManager(
            PHANDLE            ResourceManagerHandle,
             ACCESS_MASK        DesiredAccess,
             HANDLE             TmHandle,
             LPGUID             ResourceManagerGuid,
   POBJECT_ATTRIBUTES ObjectAttributes
);

 NTSTATUS ZwOpenSection(
   PHANDLE            SectionHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes
);

 NTSTATUS ZwOpenSymbolicLinkObject(
   PHANDLE            LinkHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS ZwOpenTransaction(
            PHANDLE            TransactionHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
             LPGUID             Uow,
   HANDLE             TmHandle
);

NTSYSCALLAPI NTSTATUS ZwOpenTransactionManager(
            PHANDLE            TmHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
   PUNICODE_STRING    LogFileName,
   LPGUID             TmIdentity,
   ULONG              OpenOptions
);

NTSYSCALLAPI NTSTATUS ZwPrepareComplete(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS ZwPrepareEnlistment(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS ZwPrePrepareComplete(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS ZwPrePrepareEnlistment(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

 NTSTATUS ZwQueryFullAttributesFile(
    POBJECT_ATTRIBUTES             ObjectAttributes,
   PFILE_NETWORK_OPEN_INFORMATION FileInformation
);

 NTSTATUS ZwQueryInformationByName(
    POBJECT_ATTRIBUTES     ObjectAttributes,
   PIO_STATUS_BLOCK       IoStatusBlock,
   PVOID                  FileInformation,
    ULONG                  Length,
    FILE_INFORMATION_CLASS FileInformationClass
);

NTSYSCALLAPI NTSTATUS ZwQueryInformationEnlistment(
              HANDLE                       EnlistmentHandle,
              ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
             PVOID                        EnlistmentInformation,
              ULONG                        EnlistmentInformationLength,
   PULONG                       ReturnLength
);

 NTSTATUS ZwQueryInformationFile(
    HANDLE                 FileHandle,
   PIO_STATUS_BLOCK       IoStatusBlock,
   PVOID                  FileInformation,
    ULONG                  Length,
    FILE_INFORMATION_CLASS FileInformationClass
);

NTSYSCALLAPI NTSTATUS ZwQueryInformationResourceManager(
              HANDLE                            ResourceManagerHandle,
              RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
             PVOID                             ResourceManagerInformation,
              ULONG                             ResourceManagerInformationLength,
   PULONG                            ReturnLength
);

NTSYSCALLAPI NTSTATUS ZwQueryInformationTransaction(
              HANDLE                        TransactionHandle,
              TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
             PVOID                         TransactionInformation,
              ULONG                         TransactionInformationLength,
   PULONG                        ReturnLength
);

NTSYSCALLAPI NTSTATUS ZwQueryInformationTransactionManager(
              HANDLE                               TransactionManagerHandle,
              TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
             PVOID                                TransactionManagerInformation,
              ULONG                                TransactionManagerInformationLength,
   PULONG                               ReturnLength
);

 NTSTATUS ZwQueryKey(
              HANDLE                KeyHandle,
              KEY_INFORMATION_CLASS KeyInformationClass,
   PVOID                 KeyInformation,
              ULONG                 Length,
             PULONG                ResultLength
);

 NTSTATUS ZwQuerySymbolicLinkObject(
              HANDLE          LinkHandle,
         PUNICODE_STRING LinkTarget,
   PULONG          ReturnedLength
);

 NTSTATUS ZwQueryValueKey(
              HANDLE                      KeyHandle,
              PUNICODE_STRING             ValueName,
              KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
   PVOID                       KeyValueInformation,
              ULONG                       Length,
             PULONG                      ResultLength
);

 NTSTATUS ZwReadFile(
             HANDLE           FileHandle,
   HANDLE           Event,
   PIO_APC_ROUTINE  ApcRoutine,
   PVOID            ApcContext,
            PIO_STATUS_BLOCK IoStatusBlock,
            PVOID            Buffer,
             ULONG            Length,
   PLARGE_INTEGER   ByteOffset,
   PULONG           Key
);

NTSYSCALLAPI NTSTATUS ZwReadOnlyEnlistment(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS ZwRecoverEnlistment(
             HANDLE EnlistmentHandle,
   PVOID  EnlistmentKey
);


NTSYSCALLAPI NTSTATUS ZwRecoverResourceManager(
   HANDLE ResourceManagerHandle
);

NTSYSCALLAPI NTSTATUS ZwRecoverTransactionManager(
   HANDLE TransactionManagerHandle
);

NTSYSCALLAPI NTSTATUS ZwRollbackComplete(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS ZwRollbackEnlistment(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS ZwRollbackTransaction(
   HANDLE  TransactionHandle,
   BOOLEAN Wait
);

NTSYSCALLAPI NTSTATUS ZwRollforwardTransactionManager(
             HANDLE         TransactionManagerHandle,
   PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS ZwSetInformationEnlistment(
   HANDLE                       EnlistmentHandle,
   ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
   PVOID                        EnlistmentInformation,
   ULONG                        EnlistmentInformationLength
);

 NTSTATUS ZwSetInformationFile(
    HANDLE                 FileHandle,
   PIO_STATUS_BLOCK       IoStatusBlock,
    PVOID                  FileInformation,
    ULONG                  Length,
    FILE_INFORMATION_CLASS FileInformationClass
);

NTSYSCALLAPI NTSTATUS ZwSetInformationResourceManager(
  HANDLE                            ResourceManagerHandle,
  RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
  PVOID                             ResourceManagerInformation,
  ULONG                             ResourceManagerInformationLength
);

NTSYSCALLAPI NTSTATUS ZwSetInformationTransaction(
   HANDLE                        TransactionHandle,
   TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
   PVOID                         TransactionInformation,
   ULONG                         TransactionInformationLength
);

 NTSTATUS ZwSetValueKey(
             HANDLE          KeyHandle,
             PUNICODE_STRING ValueName,
   ULONG           TitleIndex,
             ULONG           Type,
   PVOID           Data,
             ULONG           DataSize
);

NTSYSCALLAPI NTSTATUS ZwSinglePhaseReject(
             HANDLE         EnlistmentHandle,
   PLARGE_INTEGER TmVirtualClock
);

 NTSTATUS ZwUnloadDriver(
   PUNICODE_STRING DriverServiceName
);

 NTSTATUS ZwUnmapViewOfSection(
             HANDLE ProcessHandle,
   PVOID  BaseAddress
);

 NTSTATUS ZwWriteFile(
             HANDLE           FileHandle,
   HANDLE           Event,
   PIO_APC_ROUTINE  ApcRoutine,
   PVOID            ApcContext,
            PIO_STATUS_BLOCK IoStatusBlock,
             PVOID            Buffer,
             ULONG            Length,
   PLARGE_INTEGER   ByteOffset,
   PULONG           Key
);


typedef struct _IO_CONNECT_INTERRUPT_PARAMETERS {
    ULONG Version;
    union {
        struct {
            ULONG InterfaceType;
            ULONG BusNumber;
            ULONG Vector;
            KIRQL Irql;
            KINTERRUPT_MODE InterruptMode;
            PKSERVICE_ROUTINE ServiceRoutine;
            PVOID ServiceContext;
            BOOLEAN FloatingSave;
            BOOLEAN ShareVector;
            KAFFINITY ProcessorEnableMask;
            PKSPIN_LOCK SpinLock;
            PKINTERRUPT *InterruptObject;
        } FullySpecified;

        struct {
            PKSERVICE_ROUTINE ServiceRoutine;
            PVOID ServiceContext;
            PKINTERRUPT *InterruptObject;
            ULONG Vector;
            KIRQL Irql;
            KINTERRUPT_MODE InterruptMode;
            BOOLEAN ShareVector;
        } LineBased;

        struct {
            PKSERVICE_ROUTINE ServiceRoutine;
            PVOID ServiceContext;
            PKINTERRUPT *InterruptObject;
            PIO_INTERRUPT_MESSAGE_INFO MessageInfo;
            ULONG MessageCount;
            KINTERRUPT_MODE InterruptMode;
        } MessageBased;
    };
} IO_CONNECT_INTERRUPT_PARAMETERS, *PIO_CONNECT_INTERRUPT_PARAMETERS;

NTSTATUS IoConnectInterruptEx(
   PIO_CONNECT_INTERRUPT_PARAMETERS Parameters
);

#endif