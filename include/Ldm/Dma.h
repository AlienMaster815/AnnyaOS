#ifndef _LDM_DMA_H
#define _LDM_DMA_H
#ifdef __cplusplus
extern "C" {
#endif

#include <Ldm/miniport.h>
#include <Ldm.h>

struct _DMA_ADAPTER;
struct _IOMMU_DMA_DEVICE;
struct _IOMMU_DMA_PASID_DEVICE;
struct _IOMMU_DMA_DOMAIN;
struct _IOMMU_DMA_DEVICE_INFORMATION;
struct _DMA_TRANSFER_INFO;
struct _DMA_ADAPTER_INFO;
struct _DOMAIN_CONFIGURATION;

typedef ULONGLONG IOMMU_DMA_LOGICAL_ADDRESS;

typedef enum _DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_TYPE{
    CommonBufferConfigTypeLogicalAddressLimits = 0,
    CommonBufferConfigTypeSubSection,
    CommonBufferConfigTypeHardwareAccessPermissions,
    CommonBufferConfigTypeMax
}DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_TYPE, * PDMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_TYPE;

typedef enum _DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_ACCESS_TYPE{
    CommonBufferHardwareAccessReadOnly = 0,
    CommonBufferHardwareAccessWriteOnly,
    CommonBufferHardwareAccessReadWrite,
    CommonBufferHardwareAccessMax
}DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_ACCESS_TYPE, * PDMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_ACCESS_TYPE;

typedef struct _DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION{
    DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_TYPE               ConfigType;
    union {
        struct {
            PHYSICAL_ADDRESS                                    MinimumAddress;
            PHYSICAL_ADDRESS                                    MaximumAddress;
        }                                                       LogicalAddressLimits;
        struct {
            ULONGLONG                                           Offset;
            ULONG                                               Length;
        }                                                       SubSection;
        DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION_ACCESS_TYPE    HardwareAccessType;
        ULONGLONG                                               Reserved[4];
    };
}DMA_COMMON_BUFFER_EXTENDED_CONFIGURATION, * PDMA_COMMON_BUFFER_EXTENDED_CONFIGURATION;

typedef enum _DMA_WIDTH{
    Width8Bits = 0,
    Width16Bits,
    Width32Bits,
    Width64Bits,
    MaximumDmaWidth,
}DMA_WIDTH, * PDMA_WIDTH;

typedef enum _DMA_SPEED{
    Compatible = 0,
    TypeA,
    TypeB,
    TypeC,
    TypeF,
    MaximumDmaSpeed,
}DMA_SPEED, * PDMA_SPEED;

typedef enum{
    DmaComplete = 0,
    DmaAborted,
    DmaError,
    DmaCancelled
}DMA_COMPLETION_STATUS;

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

typedef struct _SCATTER_GATHER_ELEMENT {
  PHYSICAL_ADDRESS Address;
  ULONG            Length;
  ULONG_PTR        Reserved;
} SCATTER_GATHER_ELEMENT, *PSCATTER_GATHER_ELEMENT;

typedef struct _SCATTER_GATHER_LIST {
    ULONG                  NumberOfElements;
    ULONG_PTR              Reserved;
    SCATTER_GATHER_ELEMENT Elements[];
} SCATTER_GATHER_LIST, * PSCATTER_GATHER_LIST;




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

typedef void FREE_COMMON_BUFFER_FROM_VECTOR(
    struct _DMA_ADAPTER*        DmaAdapter,
    PDMA_COMMON_BUFFER_VECTOR   Vector,
    ULONG                       Index
);
typedef FREE_COMMON_BUFFER_FROM_VECTOR* PFREE_COMMON_BUFFER_FROM_VECTOR;

typedef void FREE_COMMON_BUFFER_VECTOR(
    struct _DMA_ADAPTER*        DmaAdapter,
    PDMA_COMMON_BUFFER_VECTOR   Vector
);
typedef FREE_COMMON_BUFFER_VECTOR* PFREE_COMMON_BUFFER_VECTOR;

typedef void FREE_COMMON_BUFFER(
    struct _DMA_ADAPTER*        DmaAdapter,
    ULONG                       Length,
    PVOID                       LogicalAddress,
    PVOID                       VirtualAddress,
    BOOLEAN                     CacheEnabled
);
typedef FREE_COMMON_BUFFER* PFREE_COMMON_BUFFER;

typedef LOUSTATUS FLUSH_ADAPTER_BUFFERS_EX(
    struct _DMA_ADAPTER*    DmaAdapter,
    PMDL                    Mdl,
    PVOID                   Offset,
    ULONG                   Length,
    BOOLEAN                 WriteToDevice
);
typedef FLUSH_ADAPTER_BUFFERS_EX* PFLUSH_ADAPTER_BUFFERS_EX;

typedef BOOLEAN FLUSH_ADAPTER_BUFFERS(
    struct _DMA_ADAPTER*    DmaAdapter,
    PMDL                    Mdl,
    PVOID                   MapRegisterBase,
    PVOID                   CurrentVa,
    ULONG                   Length,
    BOOLEAN                 WriteToDevice
);
typedef FLUSH_ADAPTER_BUFFERS* PFLUSH_ADAPTER_BUFFERS;

typedef LOUSTATUS ALLOCATE_ADAPTER_CHANNEL_EX(
    struct _DMA_ADAPTER*    DmaAdapter,
    PDEVICE_OBJECT          DeviceObject,
    PVOID                   DmaTransferContext,
    ULONG                   MapRegisterCount,
    ULONG                   Flags,
    PDRIVER_CONTROL         DriverControl,
    PVOID                   Contex,
    PVOID                   MapRegisterBase
);
typedef ALLOCATE_ADAPTER_CHANNEL_EX* PALLOCATE_ADAPTER_CHANNEL_EX;

typedef 
LOUSTATUS IOMMU_PASID_DEVICE_CREATE(
    struct _IOMMU_DMA_DEVICE*           DmaDevice,
    struct _IOMMU_DMA_PASID_DEVICE*     PasidDeviceOut,
    PULONG                              AsidOut
);
typedef IOMMU_PASID_DEVICE_CREATE* PIOMMU_PASID_DEVICE_CREATE;

typedef 
LOUSTATUS IOMMU_PASID_DEVICE_DELETE(
    struct _IOMMU_DMA_PASID_DEVICE* PasidDeviceOut
);
typedef IOMMU_PASID_DEVICE_DELETE* PIOMMU_PASID_DEVICE_DELETE;

typedef 
LOUSTATUS IOMMU_DOMAIN_ATTACH_PASID_DEVICE(
    struct _IOMMU_DMA_DOMAIN*       Domain,
    struct _IOMMU_DMA_PASID_DEVICE* PasidDevice
);
typedef IOMMU_DOMAIN_ATTACH_PASID_DEVICE* PIOMMU_DOMAIN_ATTACH_PASID_DEVICE;

typedef 
LOUSTATUS 
IOMMU_DOMAIN_DETACH_PASID_DEVICE(
    struct _IOMMU_DMA_PASID_DEVICE  PasidDevice
);
typedef IOMMU_DOMAIN_DETACH_PASID_DEVICE* PIOMMU_DOMAIN_DETACH_PASID_DEVICE;

typedef 
LOUSTATUS
IOMMU_DEVICE_QUERY_INFORMATION(
    struct _IOMMU_DMA_DEVICE*               DmaDevice,
    ULONG                                   Size,
    PULONG                                  BytesWriten,
    struct _IOMMU_DMA_DEVICE_INFORMATION*   Buffer
);
typedef IOMMU_DEVICE_QUERY_INFORMATION* PIOMMU_DEVICE_QUERY_INFORMATION;

//new stuff starts here
typedef 
LOUSTATUS 
ALLOCATE_ADAPTER_CHANNEL(
    struct _DMA_ADAPTER*    DmaAdapter,
    PDEVICE_OBJECT          DeviceObject,
    ULONG                   MapRegisterCount,
    PDRIVER_CONTROL         DriverControl,
    PVOID                   Context
);
typedef ALLOCATE_ADAPTER_CHANNEL* PALLOCATE_ADAPTER_CHANNEL;

typedef 
void 
FREE_MAP_REGISTERS(
    struct _DMA_ADAPTER*    DmaAdapter,
    PVOID                   MapRegisterBase,
    ULONG                   MapRegisterCount
);
typedef FREE_MAP_REGISTERS* PFREE_MAP_REGISTERS;

typedef 
void 
FREE_ADAPTER_CHANNEL(
    struct _DMA_ADAPTER DmaAdapter
);
typedef FREE_ADAPTER_CHANNEL* PFREE_ADAPTER_CHANNEL;

typedef 
void 
DMA_COMPLETION_ROUTINE(
    struct _DMA_ADAPTER*    DmaAdapter,
    PDEVICE_OBJECT          DeviceObject,
    PVOID                   CompletionContext,
    DMA_COMPLETION_STATUS   Status
);
typedef DMA_COMPLETION_ROUTINE* PDMA_COMPLETION_ROUTINE;

typedef 
LOUSTATUS 
MAP_TRANSFER_EX(
    struct _DMA_ADAPTER*    DmaAdapter,
    PMDL                    Mdl,
    PVOID                   MapRegisterBase,
    ULONGLONG               Offset,
    ULONG                   DeviceOffset,
    PULONG                  Length,
    BOOLEAN                 WriteToDevice,
    PSCATTER_GATHER_LIST    Sgb,
    ULONG                   SgbLength,
    PDMA_COMPLETION_ROUTINE DmaCompletionRoutine,
    PVOID                   CompletionContext
);
typedef MAP_TRANSFER_EX* PMAP_TRANSFER_EX;

typedef 
PHYSICAL_ADDRESS
MAP_TRANSFER(
    struct _DMA_ADAPTER*    DmaAdapter,
    PMDL                    Pmdl,
    PVOID                   MapRegisterBase,
    PVOID                   CurrentVa,
    PULONG                  Length,
    BOOLEAN                 WriteToDevice
);
typedef MAP_TRANSFER* PMAP_TRANSFER;

typedef 
ULONG
GET_DMA_ALIGNMENT(
    struct _DMA_ADAPTER DmaAdapter
);
typedef GET_DMA_ALIGNMENT* PGET_DMA_ALIGNMENT;

typedef 
LOUSTATUS
CREATE_COMMON_BUFFER_FROM_MDL(
    struct _DMA_ADAPTER*                            DmaAdapter,
    PMDL                                            Mdl,
    PDMA_COMMON_BUFFER_EXTENDED_CONFIGURATION       ExtendedConfigs,
    ULONG                                           ExtendedConfigsCount,
    PPHYSICAL_ADDRESS                               LogicalAddress
);
typedef CREATE_COMMON_BUFFER_FROM_MDL* PCREATE_COMMON_BUFFER_FROM_MDL;

typedef 
PVOID
ALLOCATE_COMMON_BUFFER_WITH_BOUNDS(
    struct _DMA_ADAPTER*    DmaAdapter,
    PPHYSICAL_ADDRESS       MinimumAddress,
    PPHYSICAL_ADDRESS       MaximumAddress,
    ULONG                   Length,
    ULONG                   Flags,
    PMEMORY_CACHING_TYPE    CacheType,
    NODE_REQUIREMENT        PerferredNode,
    PPHYSICAL_ADDRESS       LogicalAddress
);
typedef ALLOCATE_COMMON_BUFFER_WITH_BOUNDS* PALLOCATE_COMMON_BUFFER_WITH_BOUNDS;

typedef 
HANDLE 
GET_DMA_DOMAIN(
    struct _DMA_ADAPTER* DmaAdapter
);
typedef GET_DMA_DOMAIN* PGET_DMA_DOMAIN;

typedef 
LOUSTATUS 
LEAVE_DMA_DOMAIN(
    struct _DMA_ADAPTER* DmaAdapter
);
typedef LEAVE_DMA_DOMAIN* PLEAVE_DMA_DOMAIN;

typedef 
LOUSTATUS 
JOIN_DMA_DOMAIN(
    struct _DMA_ADAPTER*    DmaAdapter,
    HANDLE                  DomainHandle
);
typedef JOIN_DMA_DOMAIN* PJOIN_DMA_DOMAIN;

typedef 
LOUSTATUS 
FLUSH_DMA_BUFFER(
    struct _DMA_ADAPTER*    DmaAdapter,
    PMDL                    Mdl,
    BOOLEAN                 ReadOperation
);
typedef FLUSH_DMA_BUFFER* PFLUSH_DMA_BUFFER;

typedef 
LOUSTATUS 
ALLOCATE_DOMAIN_COMMON_BUFFER(
    struct _DMA_ADAPTER     DmaAdapter,
    HANDLE                  DomainHandle,
    PPHYSICAL_ADDRESS       MaximumAddress,
    ULONG                   Length,
    ULONG                   Flags,
    PMEMORY_CACHING_TYPE    CacheType,
    NODE_REQUIREMENT        PreferredNode,
    PPHYSICAL_ADDRESS       LogicalAddress,
    PVOID*                  VirtualAddress
);
typedef ALLOCATE_DOMAIN_COMMON_BUFFER* PALLOCATE_DOMAIN_COMMON_BUFFER;

typedef 
LOUSTATUS 
CANCEL_MAPPED_TRANSFER(
    struct _DMA_ADAPTER*    DmaAdapter,
    PVOID                   DmaTransferContext
);
typedef CANCEL_MAPPED_TRANSFER* PCANCEL_MAPPED_TRANSFER;

typedef 
void
FREE_ADAPTER_OBJECT(
    struct _DMA_ADAPTER     DmaAdapter,
    IO_ALLOCATION_ACTION    AllocationAction
);
typedef FREE_ADAPTER_OBJECT* PFREE_ADAPTER_OBJECT;

typedef 
void
DRIVER_LIST_CONTROL(
    PDEVICE_OBJECT          DeviceObject,
    struct _IRP*            Irp,
    PSCATTER_GATHER_LIST    ScatterGather,
    PVOID                   Context
);
typedef DRIVER_LIST_CONTROL* PDRIVER_LIST_CONTROL;

typedef 
LOUSTATUS
BUILD_SCATTER_GATHER_LIST_EX(
    struct _DMA_ADAPTER*    DmaAdapter,
    PDEVICE_OBJECT          DeviceObject,
    PVOID                   DmaTransferContext,
    PMDL                    Mdl,
    ULONGLONG               Offset,
    ULONG                   Length,
    ULONG                   Flags,
    PDRIVER_LIST_CONTROL    ExeRoutine,
    PVOID                   Context,
    BOOLEAN                 WriteToDevice,
    PVOID                   Sgb,
    ULONG                   SgbLength,
    PDMA_COMPLETION_ROUTINE DmaCompletionRoutine,
    PVOID                   CompletionContext,
    PVOID                   ScatterGatherList
);
typedef BUILD_SCATTER_GATHER_LIST_EX* PBUILD_SCATTER_GATHER_LIST_EX;

typedef 
LOUSTATUS 
GET_SCATTER_GATHER_LIST_EX(
    struct _DMA_ADAPTER*    DmaAdapter,
    PDEVICE_OBJECT          DeviceObject,
    PVOID                   DmaTransferContext,
    PMDL                    Mdl,
    ULONGLONG               Offset,
    ULONG                   Length,
    ULONG                   Flags,
    PDRIVER_LIST_CONTROL    ExeRoutine,
    PVOID                   Context,
    BOOLEAN                 WriteToDevice,
    PDMA_COMPLETION_ROUTINE DmaCompletionRoutine,
    PVOID                   CompletionContext,
    PSCATTER_GATHER_LIST*   ScatterGatherList
);
typedef GET_SCATTER_GATHER_LIST_EX* PGET_SCATTER_GATHER_LIST_EX;

typedef 
BOOLEAN 
CANCEL_ADAPTER_CHANNEL(
    struct _DMA_ADAPTER*    DmaAdapter,
    PDEVICE_OBJECT          DeviceObject,
    PVOID                   DmaTransferContext
);
typedef CANCEL_ADAPTER_CHANNEL* PCANCEL_ADAPTER_CHANNEL;

typedef 
LOUSTATUS 
CONFIGURE_ADAPTER_CHANNEL(
    struct _DMA_ADAPTER DmaAdapter,
    ULONG               FunctionNumbr,
    PVOID               Context
);
typedef CONFIGURE_ADAPTER_CHANNEL* PCONFIGURE_ADAPTER_CHANNEL;

typedef 
PVOID
ALLOCATE_COMMON_BUFFER_EX(
    struct _DMA_ADAPTER*    DmaAdapter,
    PPHYSICAL_ADDRESS       MaximumAddress,
    ULONG                   Length,
    PPHYSICAL_ADDRESS       LogicalAddress,
    BOOLEAN                 CacheEnabled,
    NODE_REQUIREMENT        PreferredNode
);
typedef ALLOCATE_COMMON_BUFFER_EX* PALLOCATE_COMMON_BUFFER_EX;

typedef 
LOUSTATUS 
INITIALIZE_DMA_TRANSFER_CONTEXT(
    struct _DMA_ADAPTER     DmaAdapter,
    PVOID                   DmaTransferContext
);
typedef INITIALIZE_DMA_TRANSFER_CONTEXT* PINITIALIZE_DMA_TRANSFER_CONTEXT;

typedef 
LOUSTATUS 
GET_DMA_TRANSFER_INFO(
    struct _DMA_ADAPTER*        DmaAdapter,
    PMDL                        Mdl,
    ULONGLONG                   Length,
    ULONG                       WriteOnly,
    struct _DMA_TRANSFER_INFO*  TransferInfo
);
typedef GET_DMA_TRANSFER_INFO* PGET_DMA_TRANSFER_INFO;

typedef 
LOUSTATUS 
GET_DMA_ADAPTER_INFO(
    struct _DMA_ADAPTER*        DmaAdapter,
    struct _DMA_ADAPTER_INFO*    AdapterInfo
);
typedef GET_DMA_ADAPTER_INFO* PGET_DMA_ADAPTER_INFO;

typedef 
LOUSTATUS
BUILD_MDL_FROM_SCATTER_GATHER_LIST(
    struct _DMA_ADAPTER*    DmaAdapter,
    PSCATTER_GATHER_LIST    ScatterGather,
    PMDL                    OriginalMdl,
    PMDL*                   TargetMdl
);
typedef BUILD_MDL_FROM_SCATTER_GATHER_LIST* PBUILD_MDL_FROM_SCATTER_GATHER_LIST;

typedef 
LOUSTATUS 
BUILD_SCATTER_GATHER_LIST(
    struct _DMA_ADAPTER*    DmaAdapter,
    PDEVICE_OBJECT          DeviceObject,
    PMDL                    Mdl,
    PVOID                   CurrentVa,
    ULONG                   Length,
    PDRIVER_LIST_CONTROL    ExeRoutine,
    PVOID                   Context,
    BOOLEAN                 WriteToDevice,
    PVOID                   Sgb,
    ULONG                   SgbLength
);
typedef BUILD_SCATTER_GATHER_LIST* PBUILD_SCATTER_GATHER_LIST;

typedef 
LOUSTATUS 
CALCULATE_SCATTER_GATHER_LIST_SIZE(
    struct _DMA_ADAPTER*    DmaAdapter,
    PMDL                    Mdl,
    PVOID                   CurrentVa,
    ULONG                   Length,
    PULONG                  SglSize,
    PULONG                  pMappedRegisrers
);
typedef CALCULATE_SCATTER_GATHER_LIST_SIZE* PCALCULATE_SCATTER_GATHER_LIST_SIZE;

typedef 
void
PUT_SCATTER_GATHER_LIST(
    struct _DMA_ADAPTER*    DmaAdapter,
    PSCATTER_GATHER_LIST    ScatterGather,
    BOOLEAN                 WriteToDevice
);
typedef PUT_SCATTER_GATHER_LIST* PPUT_SCATTER_GATHER_LIST;

typedef 
LOUSTATUS
GET_SCATTER_GATHER_LIST(
    struct _DMA_ADAPTER DmaAdapter,
    PDEVICE_OBJECT      DeviceObject,
    PMDL                Mdl

);
typedef GET_SCATTER_GATHER_LIST* PGET_SCATTER_GATHER_LIST;

typedef 
ULONG
READ_DMA_COUNTER(
    struct _DMA_ADAPTER* DmaAdapter
);
typedef READ_DMA_COUNTER* PREAD_DMA_COUNTER;

typedef 
LOUSTATUS 
IOMMU_DOMAIN_CONFIGURE(
    struct _IOMMU_DMA_DOMAIN*       Domain,
    struct _DOMAIN_CONFIGURATION*   DomainConfiguration
);
typedef IOMMU_DOMAIN_CONFIGURE* PIOMMU_DOMAIN_CONFIGURE;


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

typedef struct _DEVICE_DESCRIPTION{
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
}DEVICE_DESCRIPTION, * PDEVICE_DESCRIPTION;

typedef struct _DMA_ADAPTER_INFO_CRASHDUMP{
    DEVICE_DESCRIPTION DeviceDescription;
    SIZE_T             DeviceIdSize;
    PVOID              DeviceId;
}DMA_ADAPTER_INFO_CRASHDUMP, * PDMA_ADAPTER_INFO_CRASHDUMP;

typedef struct _DMA_ADAPTER_INFO_V1{
    ULONG ReadDmaCounterAvailable;
    ULONG ScatterGatherLimit;
    ULONG DmaAddressWidth;
    ULONG Flags;
    ULONG MinimumTransferUnit;
}DMA_ADAPTER_INFO_V1, * PDMA_ADAPTER_INFO_V1;

typedef struct _DMA_IOMMU_INTERFACE_V1{
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
}DMA_IOMMU_INTERFACE_V1, * PDMA_IOMMU_INTERFACE_V1;

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

typedef struct _DMA_IOMMU_INTERFACE_V3{
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
    PIOMMU_PASID_DEVICE_CREATE                        CreatePasidDevice;
    PIOMMU_PASID_DEVICE_DELETE                        DeletePasidDevice;
    PIOMMU_DOMAIN_ATTACH_PASID_DEVICE                 AttachPasidDevice;
    PIOMMU_DOMAIN_DETACH_PASID_DEVICE                 DetachPasidDevice;
    PIOMMU_DEVICE_QUERY_INFORMATION                   QueryDeviceInfo;
}DMA_IOMMU_INTERFACE_V3, * PDMA_IOMMU_INTERFACE_V3;

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

typedef struct _IOMMU_DMA_DEVICE{
    PVOID Todo;
}IOMMU_DMA_DEVICE, * PIOMMU_DMA_DEVICE;

typedef struct _IOMMU_DMA_PASID_DEVICE{
    PVOID Todo;
}IOMMU_DMA_PASID_DEVICE, * PIOMMU_DMA_PASID_DEVICE;

typedef struct _IOMMU_DMA_DOMAIN{
    PVOID Todo;
}IOMMU_DMA_DOMAIN, * PIOMMU_DMA_DOMAIN;

typedef struct _IOMMU_DMA_DEVICE_INFORMATION{
    BOOLEAN DefaultPasidEnabled;
    BOOLEAN PasidTaggedDmaEnabled;
    BOOLEAN PasidFaultsSuppressed;
}IOMMU_DMA_DEVICE_INFORMATION, * PIOMMU_DMA_DEVICE_INFORMATION;



#ifndef _USER_MODE_CODE_
KERNEL_EXPORT void LouKePutDmaAdapter(PDMA_ADAPTER DmaAdapter);
KERNEL_EXPORT LOUSTATUS LouKeAllocateCommonBufferVector(PDMA_ADAPTER DmaAdapter, PHYSICAL_ADDRESS LowAdderss, PHYSICAL_ADDRESS HighAddress, MEMORY_CACHING_TYPE CachingType, NODE_REQUIREMENT IdealNode, ULONG Flags, ULONG ElementCount, ULONGLONG ElementSize, PDMA_COMMON_BUFFER_VECTOR VectorOut);
KERNEL_EXPORT PVOID LouKeAllocateCommonBuffer(PDMA_ADAPTER DmaAdapter, ULONG Length, PPHYSICAL_ADDRESS LogicalAddress, BOOLEAN CacheEnabled);
KERNEL_EXPORT void LouKeGetCommonBufferFromVectorByIndex(PDMA_COMMON_BUFFER_VECTOR Vector, ULONG Index, PVOID* VAddress, PPHYSICAL_ADDRESS LogicalAddress);
KERNEL_EXPORT void LouKeFreeCommonBufferFromVector(PDMA_ADAPTER DmaAdapter, PDMA_COMMON_BUFFER_VECTOR Vector, ULONG Index);
KERNEL_EXPORT void LouKeFreeCommonBufferVector(PDMA_ADAPTER DmaAdapter, PDMA_COMMON_BUFFER_VECTOR Vector);
KERNEL_EXPORT void LouKeFreeCommonBuffer(PDMA_ADAPTER DmaAdapter, ULONG Length, PHYSICAL_ADDRESS LogicalAddress, PVOID VirtualAddress, BOOLEAN CacheEnabled);
KERNEL_EXPORT LOUSTATUS LouKeFlushAdapterBuffersEx(PDMA_ADAPTER DmaAdapter, PMDL Mdl, PVOID Offset, ULONG Length, BOOLEAN WriteToDevice);
KERNEL_EXPORT BOOLEAN LouKeFlushAdapterBuffers(PDMA_ADAPTER DmaAdapter, PMDL Mdl, PVOID MapRegisterBase, PVOID CurrentVa, ULONG Length, BOOLEAN WriteToDevice);
KERNEL_EXPORT LOUSTATUS LouKeAllocateAdapterChannelEx(PDMA_ADAPTER DmaAdapter, PDEVICE_OBJECT DeviceObject, PVOID DmaTransferContext, ULONG MapRegisterCount, ULONG Flags, PDRIVER_CONTROL DriverControl, PVOID Contex, PVOID MapRegisterBase);
KERNEL_EXPORT LOUSTATUS LouKeIommuPasidDeviceCreate(PIOMMU_DMA_DEVICE DmaDevice, PIOMMU_DMA_PASID_DEVICE PasidDeviceOut, PULONG AsidOut);
KERNEL_EXPORT LOUSTATUS LouKeIommuPasidDeviceDelete(PIOMMU_DMA_PASID_DEVICE PasidDeviceOut);
KERNEL_EXPORT LOUSTATUS LouKeIommuDomainAttatchPasidDevice(PIOMMU_DMA_DOMAIN Domain, PIOMMU_DMA_PASID_DEVICE PasidDevice);
KERNEL_EXPORT LOUSTATUS LouKeIommuDomainDetatchPasidDevice(PIOMMU_DMA_PASID_DEVICE PasidDevice);
KERNEL_EXPORT LOUSTATUS LouKeIommuDeviceQueryInformation(PIOMMU_DMA_DEVICE DmaDevice, ULONG Size, PULONG BytesWriten, PIOMMU_DMA_DEVICE_INFORMATION Buffer);

#endif
#ifdef __cplusplus
}
#endif
#endif