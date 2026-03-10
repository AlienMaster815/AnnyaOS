#ifndef _LDM_DMA_H
#define _LDM_DMA_H
#ifdef __cplusplus
extern "C" {
#endif

#include <Ldm/miniport.h>
#include <Ldm.h>

struct _DMA_ADAPTER;

typedef ULONGLONG IOMMU_DMA_LOGICAL_ADDRESS;

typedef void PUT_DMA_ADAPTER(
    struct _DMA_ADAPTER* DmaAdapter
);
typedef PUT_DMA_ADAPTER* PPUT_DMA_ADAPTER;

typedef struct _DMA_COMMON_BUFFER_VECTOR{
    struct _DMA_ADAPTER*    Adapter;
    PHYSICAL_ADDRESS        LowAdderss;
    PHYSICAL_ADDRESS        HighAddress;
    MEMORY_CACHING_TYPE     CachingType;
    NODE_REQUIREMENT        IdealNode;
    ULONG                   Flags;
    ULONG                   ElementCount;
    ULONGLONG               ElementSize;
}DMA_COMMON_BUFFER_VECTOR, * PDMA_COMMON_BUFFER_VECTOR;

typedef LOUSTATUS ALLOCATE_COMMON_BUFFER_VECTOR(
    struct _DMA_ADAPTER*                DmaAdapter,
    PHYSICAL_ADDRESS                    LowAdderss,
    PHYSICAL_ADDRESS                    HighAddress,
    MEMORY_CACHING_TYPE                 CachingType,
    NODE_REQUIREMENT                    IdealNode,
    ULONG                               Flags,
    ULONG                               ElementCount,
    ULONGLONG                           ElementSize,
    PDMA_COMMON_BUFFER_VECTOR           VectorOut
);
typedef ALLOCATE_COMMON_BUFFER_VECTOR* PALLOCATE_COMMON_BUFFER_VECTOR;

typedef PVOID ALLOCATE_COMMON_BUFFER(
    struct _DMA_ADAPTER*    DmaAdapter,
    ULONG                   Length,
    PPHYSICAL_ADDRESS       LogicalAddress,
    BOOLEAN                 CacheEnabled
);
typedef ALLOCATE_COMMON_BUFFER* PALLOCATE_COMMON_BUFFER;

typedef void GET_COMMON_BUFFER_FROM_VECTOR_BY_INDEX(
    PDMA_COMMON_BUFFER_VECTOR   Vector,
    ULONG                       Index,
    PVOID*                      VAddress,
    PPHYSICAL_ADDRESS           LogicalAddress  
);
typedef GET_COMMON_BUFFER_FROM_VECTOR_BY_INDEX* PGET_COMMON_BUFFER_FROM_VECTOR_BY_INDEX;

typedef void* PFREE_COMMON_BUFFER_FROM_VECTOR;
typedef void* PFREE_COMMON_BUFFER_VECTOR;
typedef void* PFREE_COMMON_BUFFER;
typedef void* PFLUSH_ADAPTER_BUFFERS_EX;
typedef void* PFLUSH_ADAPTER_BUFFERS;
typedef void* PALLOCATE_ADAPTER_CHANNEL_EX;
typedef void* PALLOCATE_ADAPTER_CHANNEL;
typedef void* PFREE_MAP_REGISTERS;
typedef void* PFREE_ADAPTER_CHANNEL;
typedef void* PMAP_TRANSFER_EX;
typedef void* PMAP_TRANSFER;
typedef void* PGET_DMA_ALIGNMENT;
typedef void* PCREATE_COMMON_BUFFER_FROM_MDL;
typedef void* PALLOCATE_COMMON_BUFFER_WITH_BOUNDS;
typedef void* PGET_DMA_DOMAIN;
typedef void* PLEAVE_DMA_DOMAIN;
typedef void* PJOIN_DMA_DOMAIN;
typedef void* PFLUSH_DMA_BUFFER;
typedef void* PALLOCATE_DOMAIN_COMMON_BUFFER;
typedef void* PCANCEL_MAPPED_TRANSFER;
typedef void* PFREE_ADAPTER_OBJECT;
typedef void* PBUILD_SCATTER_GATHER_LIST_EX;
typedef void* PGET_SCATTER_GATHER_LIST_EX;
typedef void* PCANCEL_ADAPTER_CHANNEL;
typedef void* PCONFIGURE_ADAPTER_CHANNEL;
typedef void* PALLOCATE_COMMON_BUFFER_EX;
typedef void* PINITIALIZE_DMA_TRANSFER_CONTEXT;
typedef void* PGET_DMA_TRANSFER_INFO;
typedef void* PGET_DMA_ADAPTER_INFO;
typedef void* PBUILD_MDL_FROM_SCATTER_GATHER_LIST;
typedef void* PBUILD_SCATTER_GATHER_LIST;
typedef void* PCALCULATE_SCATTER_GATHER_LIST_SIZE;
typedef void* PPUT_SCATTER_GATHER_LIST;
typedef void* PGET_SCATTER_GATHER_LIST;
typedef void* PREAD_DMA_COUNTER;
typedef void* PIOMMU_DOMAIN_CONFIGURE;
typedef void* PIOMMU_SET_DEVICE_FAULT_REPORTING;
typedef void* PIOMMU_SET_DEVICE_FAULT_REPORTING_EX;
typedef void* PIOMMU_UNMAP_IDENTITY_RANGE;
typedef void* PIOMMU_UNMAP_IDENTITY_RANGE_EX;
typedef void* PIOMMU_MAP_IDENTITY_RANGE;
typedef void* PIOMMU_MAP_IDENTITY_RANGE_EX;
typedef void* PIOMMU_MAP_LOGICAL_RANGE;
typedef void* PIOMMU_MAP_LOGICAL_RANGE_EX;
typedef void* PIOMMU_DOMAIN_DELETE;
typedef void* PIOMMU_UNMAP_LOGICAL_RANGE;
typedef void* PIOMMU_QUERY_INPUT_MAPPINGS;
typedef void* DMA_WIDTH;
typedef void* DMA_SPEED;
typedef void* PIOMMU_DOMAIN_CREATE;
typedef void* PIOMMU_DOMAIN_CREATE_EX;
typedef void* PIOMMU_DOMAIN_ATTACH_DEVICE;
typedef void* PIOMMU_DOMAIN_ATTACH_DEVICE_EX;
typedef void* PIOMMU_DOMAIN_DETACH_DEVICE;
typedef void* PIOMMU_DOMAIN_DETACH_DEVICE_EX;
typedef void* PIOMMU_FLUSH_DOMAIN;
typedef void* PIOMMU_FLUSH_DOMAIN_VA_LIST;
typedef void* PIOMMU_DEVICE_QUERY_DOMAIN_TYPES;
typedef void* PIOMMU_REGISTER_INTERFACE_STATE_CHANGE_CALLBACK;
typedef void* PIOMMU_UNREGISTER_INTERFACE_STATE_CHANGE_CALLBACK;
typedef void* PIOMMU_RESERVE_LOGICAL_ADDRESS_RANGE;
typedef void* PIOMMU_DEVICE_DELETE;
typedef void* PIOMMU_FREE_RESERVED_LOGICAL_ADDRESS_RANGE;
typedef void* PIOMMU_MAP_RESERVED_LOGICAL_RANGE;
typedef void* PIOMMU_UNMAP_RESERVED_LOGICAL_RANGE;
typedef void* PIOMMU_DEVICE_CREATE;
typedef void* DMA_IOMMU_INTERFACE_V3;


typedef struct _IOMMU_DMA_LOGICAL_ADDRESS_TOKEN{
    IOMMU_DMA_LOGICAL_ADDRESS LogicalAddressBase;
    SIZE_T                    Size;
}IOMMU_DMA_LOGICAL_ADDRESS_TOKEN, * PIOMMU_DMA_LOGICAL_ADDRESS_TOKEN;

typedef enum _IOMMU_DMA_LOGICAL_ALLOCATOR_TYPE{
    IommuDmaLogicalAllocatorNone = 0,
    IommuDmaLogicalAllocatorBuddy,
    IommuDmaLogicalAllocatorMax
}IOMMU_DMA_LOGICAL_ALLOCATOR_TYPE, * PIOMMU_DMA_LOGICAL_ALLOCATOR_TYPE;

typedef struct _DMA_OPERATIONS{
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
}DMA_OPERATIONS, * PDMA_OPERATIONS;

typedef struct _DMA_ADAPTER{
    USHORT          Version;
    USHORT          Size;
    PDMA_OPERATIONS DmaOperations;
}DMA_ADAPTER, *PADAPTER_OBJECT, * PDMA_ADAPTER;

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

typedef enum _DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_TYPE{
    CommonBufferConfigTypeLogicalAddressLimits = 0,
    CommonBufferConfigTypeSubSection,
    CommonBufferConfigTypeHardwareAccessPermissions,
    CommonBufferConfigTypeMax
}DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_TYPE, * PDMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_TYPE;

typedef enum{
    DmaComplete = 0,
    DmaAborted,
    DmaError,
    DmaCancelled
}DMA_COMPLETION_STATUS;

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




typedef struct _DMA_IOMMU_INTERFACE{
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
}DMA_IOMMU_INTERFACE, * PDMA_IOMMU_INTERFACE;

typedef struct _DMA_TRANSFER_INFO_V1{
    ULONG MapRegisterCount;
    ULONG ScatterGatherElementCount;
    ULONG ScatterGatherListSize;
}DMA_TRANSFER_INFO_V1, * PDMA_TRANSFER_INFO_V1;


typedef struct _DMA_TRANSFER_INFO_V2 {
    ULONG MapRegisterCount;
    ULONG ScatterGatherElementCount;
    ULONG ScatterGatherListSize;
    ULONG LogicalPageCount;
} DMA_TRANSFER_INFO_V2, * PDMA_TRANSFER_INFO_V2;


typedef struct _DMA_IOMMU_INTERFACE_EX{
    SIZE_T                      Size;
    ULONG                       Version;
    union {
        DMA_IOMMU_INTERFACE_V1  V1;
        DMA_IOMMU_INTERFACE_V2  V2;
        DMA_IOMMU_INTERFACE_V3  V3;
    };
}DMA_IOMMU_INTERFACE_EX, * PDMA_IOMMU_INTERFACE_EX;

typedef struct _DMA_TRANSFER_INFO{
    ULONG                       Version;
    union {
        DMA_TRANSFER_INFO_V1    V1;
        DMA_TRANSFER_INFO_V2    V2;
    };
}DMA_TRANSFER_INFO, * PDMA_TRANSFER_INFO;

PDMA_ADAPTER IoGetDmaAdapter(
    PDEVICE_OBJECT      PhysicalDeviceObject,
    PDEVICE_DESCRIPTION DeviceDescription,
    PULONG              NumberOfMapRegisters
);

typedef union _IOMMU_DMA_DOMAIN_CREATION_FLAGS{
    struct{
        ULONGLONG   Reserved : 64;
    };
    ULONGLONG       AsUlonglong;
}IOMMU_DMA_DOMAIN_CREATION_FLAGS, * PIOMMU_DMA_DOMAIN_CREATION_FLAGS;

typedef enum _IOMMU_DMA_DOMAIN_TYPE{
    DomainTypeTranslate = 0,
    DomainTypePassThrough,
    DomainTypeUnmanaged,
    DomainTypeTranslateS1,
    DomainTypeMax
}IOMMU_DMA_DOMAIN_TYPE, * PIOMMU_DMA_DOMAIN_TYPE;

typedef struct _IOMMU_DMA_LOGICAL_ADDRESS_TOKEN_MAPPED_SEGMENT{
    PIOMMU_DMA_LOGICAL_ADDRESS_TOKEN OwningToken;
    SIZE_T                           Offset;
    SIZE_T                           Size;
}IOMMU_DMA_LOGICAL_ADDRESS_TOKEN_MAPPED_SEGMENT, * PIOMMU_DMA_LOGICAL_ADDRESS_TOKEN_MAPPED_SEGMENT;

typedef struct _IOMMU_DMA_LOGICAL_ALLOCATOR_CONFIG {
    IOMMU_DMA_LOGICAL_ALLOCATOR_TYPE    LogicalAllocatorType;
    union {
        struct {
            ULONG                       AddressWidth;
        }                               BuddyAllocatorConfig;
    };
}IOMMU_DMA_LOGICAL_ALLOCATOR_CONFIG, * PIOMMU_DMA_LOGICAL_ALLOCATOR_CONFIG;

typedef struct _IOMMU_DMA_RESERVED_REGION{
    struct _IOMMU_DMA_RESERVED_REGION*  RegionNext;
    IOMMU_DMA_LOGICAL_ADDRESS           Base;
    SIZE_T                              NumberOfPages;
    BOOLEAN                             ShouldMap;
} IOMMU_DMA_RESERVED_REGION, *PIOMMU_DMA_RESERVED_REGION;

#ifndef _USER_MODE_CODE_
KERNEL_EXPORT void LouKePutDmaAdapter(PDMA_ADAPTER DmaAdapter);
KERNEL_EXPORT LOUSTATUS LouKeAllocateCommonBufferVector(PDMA_ADAPTER DmaAdapter, PHYSICAL_ADDRESS LowAdderss, PHYSICAL_ADDRESS HighAddress, MEMORY_CACHING_TYPE CachingType, NODE_REQUIREMENT IdealNode, ULONG Flags, ULONG ElementCount, ULONGLONG ElementSize, PDMA_COMMON_BUFFER_VECTOR VectorOut);
KERNEL_EXPORT PVOID LouKeAllocateCommonBuffer(PDMA_ADAPTER DmaAdapter, ULONG Length, PPHYSICAL_ADDRESS LogicalAddress, BOOLEAN CacheEnabled);
KERNEL_EXPORT void LouKeGetCommonBufferFromVectorByIndex(PDMA_COMMON_BUFFER_VECTOR Vector, ULONG Index, PVOID* VAddress, PPHYSICAL_ADDRESS LogicalAddress);



#endif
#ifdef __cplusplus
}
#endif
#endif