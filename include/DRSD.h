#ifndef _DRSD_H
#define _DRSD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdlib.h>
#include <Modulation.h>
#include <WinAPI/Win32/winnt.h>
#include <Ldm.h>

typedef struct _DRSD_DEVICE_INFO_FLAGS{
    union{
        struct{
            UINT    GuarenteedDmaBufferContract     :   1;
            UINT    Reserved                        :   31;
        };
        UINT        Value;
    };  
}DRSD_DEVICE_INFO_FLAGS, * PDRSD_DEVICE_INFO_FLAGS;

typedef struct _DRSD_DEVICE_INFO{
    UINT                    DmaBufferSize;
    UINT                    DmaBufferSegmentSet;
    UINT                    DmaBufferPRivateDataSize;
    UINT                    AllocationListSize;
    UINT                    PatchLocationListSize;
    DRSD_DEVICE_INFO_FLAGS  Flags;
}DRSD_DEVICE_INFO, * PDRSD_DEVICE_INFO;

typedef struct _DRSD_CREATE_DEVICE_FLAGS{
    union{
        struct{
            UINT    SystemDevice    :   1;
            UINT    GdiDevice       :   1;
            UINT    Reserved        :   29;
            UINT    DevReserve      :   1;
        };
        UINT        Value;
    };
}DRSD_CREATE_DEVICE_FLAGS, * PDRSD_CREATE_DEVICE_FLAGS;

typedef struct _DRSD_ARG_CREATE_DEVICE{
    HANDLE                          Device;
    union{
        DRSD_CREATE_DEVICE_FLAGS    Flags;
        PDRSD_DEVICE_INFO           DeviceInfo;
    };
    ULONG                           Pasid;
    HANDLE                          KmdProcess;
}DRSD_ARG_CREATE_DEVICE, * PDRSD_ARG_CREATE_DEVICE;

typedef struct _DRSD_START_INFO{
    ULONG   RequiredDmaQueueEntry;
    GUID    AdapterGuid;
    LUID    AdapterLuid;
}DRSD_START_INFO, * PDRSD_START_INFO;

typedef struct _DRSD_KERNEL_INTERFACE{
    //TODO 
    ULONG   Size;
}DRSD_KERNEL_INTERFACE, * PDRSD_KERNEL_INTERFACE;

typedef LOUSTATUS DRSD_DDI_ADD_DEVICE(PDEVICE_OBJECT, PVOID*);
typedef DRSD_DDI_ADD_DEVICE* PDRSD_DDI_ADD_DEVICE;

typedef LOUSTATUS DRSD_DDI_START_DEVICE(PVOID, PDRSD_START_INFO, PDRSD_KERNEL_INTERFACE, PULONG, PULONG);
typedef DRSD_DDI_START_DEVICE* PDRSD_DDI_START_DEVICE;

typedef LOUSTATUS DRSD_DDI_STOP_DEVICE(PVOID);
typedef DRSD_DDI_STOP_DEVICE* PDRSD_DDI_STOP_DEVICE;

typedef LOUSTATUS DRSD_DDI_REMOVE_DEVICE(PVOID);
typedef DRSD_DDI_REMOVE_DEVICE* PDRSD_DDI_REMOVE_DEVICE;

typedef struct _VIDEO_REQUEST_PACKET{
    ULONG           IoControlCode;
    PSTATUS_BLOCK   StatusBlock;
    PVOID           InputBuffer;
    ULONG           InputBufferLength;
    PVOID           OutputBuffer;
    ULONG           OutputBufferLength;
}VIDEO_REQUEST_PACKET, * PVIDEO_REQUEST_PACKET;

typedef LOUSTATUS DRSD_DDI_DISPATCH_IO_REQUEST(PVOID, ULONG, PVIDEO_REQUEST_PACKET);
typedef DRSD_DDI_DISPATCH_IO_REQUEST* PDRSD_DDI_DISPATCH_IO_REQUEST;

typedef BOOLEAN DRSD_DDI_INTERRUPT_ROUTINE(PVOID, ULONG);
typedef DRSD_DDI_INTERRUPT_ROUTINE* PDRSD_DDI_INTERRUPT_ROUTINE;

typedef void DRSD_DDI_DPC_ROUTINE(PVOID);
typedef DRSD_DDI_DPC_ROUTINE* PDRSD_DDI_DPC_ROUTINE;

typedef enum {
    TypeUninitialized = 0,
    TypeVideoOutput,
    TypeOther,
    TypeIntegratedDisplay,
    TypeLogicalGpu,
}DRSD_CHILD_DEVICE_TYPE;
typedef DRSD_CHILD_DEVICE_TYPE* PDRSD_CHILD_DEVICE_TYPE;

typedef enum {
    DRSD3D_KMDT_VOT_UNINITIALIZED = -1,
    DRSD3D_KMDT_VOT_OTHER = -1,
    DRSD3D_KMDT_VOT_HD15 = 0,
    DRSD3D_KMDT_VOT_SVIDEO = 1,
    DRSD3D_KMDT_VOT_COMPOSITE_VIDEO = 2,
    DRSD3D_KMDT_VOT_COMPONENT_VIDEO = 3,
    DRSD3D_KMDT_VOT_DVI = 4,
    DRSD3D_KMDT_VOT_HDMI = 5,
    DRSD3D_KMDT_VOT_LVDS = 6,
    DRSD3D_KMDT_VOT_D_JPN = 8,
    DRSD3D_KMDT_VOT_DISPLAYPORT_EXTERNAL = 10,
    DRSD3D_KMDT_VOT_DISPLAYPORT_EMBEDDED = 11,
    DRSD3D_KMDT_VOT_UDI_EXTERNAL = 12,
    DRSD3D_KMDT_VOT_UDI_EMBEDDED = 13,
    DRSD3D_KMDT_VOT_SDTDONGLE = 14,
    DRSD3D_KMDT_VOT_MIRACAST = 15,
    DRSD3D_KMDT_INDIRECT_WIRED = 16,
    DRSD3D_KMDT_VOT_INTERNAL = 0x80000000,
    DRSD3D_KMDT_VOT_SVIDEO_4PIN = DRSD3D_KMDT_VOT_SVIDEO,
    DRSD3D_KMDT_VOT_SVIDEO_7PIN = DRSD3D_KMDT_VOT_SVIDEO,
    DRSD3D_KMDT_VOT_RF = DRSD3D_KMDT_VOT_COMPOSITE_VIDEO,
    DRSD3D_KMDT_VOT_RCA_3COMPONENT = DRSD3D_KMDT_VOT_COMPOSITE_VIDEO,
    DRSD3D_KMDT_VOT_BNC = DRSD3D_KMDT_VOT_COMPOSITE_VIDEO,
}DRSD3D_KMDT_VIDEO_OUTPUT_TECHNOLOGY;
typedef DRSD3D_KMDT_VIDEO_OUTPUT_TECHNOLOGY* PDRSD3D_KMDT_VIDEO_OUTPUT_TECHNOLOGY;

typedef enum {
    DRSD3D_KMDT_MOA_UNINITIALIZED = 0,
    DRSD3D_KMDT_MOA_NONE,
    DRSD3D_KMDT_MOA_POLLED,
    DRSD3D_KMDT_MOA_INTERRUPTABLE,
}DRSD3D_KMDT_MONITOR_ORIENTATION_AWARENESS;
typedef DRSD3D_KMDT_MONITOR_ORIENTATION_AWARENESS* PDRSD3D_KMDT_MONITOR_ORIENTATION_AWARENESS;

typedef struct _DRSD_VIDEO_OUTPUT_CAPABILITIES{
    DRSD3D_KMDT_VIDEO_OUTPUT_TECHNOLOGY         InterfaceTechology;
    DRSD3D_KMDT_MONITOR_ORIENTATION_AWARENESS   MonitorOrientationAwareness;
    BOOLEAN                                     SupportsSdtvModes;
}DRSD_VIDEO_OUTPUT_CAPABILITIES, * PDRSD_VIDEO_OUTPUT_CAPABILITIES;

typedef struct _DRSD_INTEGRATED_DISPLAY_CHILD{
    DRSD3D_KMDT_VIDEO_OUTPUT_TECHNOLOGY InterfaceTechology;
    USHORT                              DescriptorLength;
}DRSD_INTEGRATED_DISPLAY_CHILD, * PDRSD_INTEGRATED_DISPLAY_CHILD;

typedef enum {
    HdpAwarenessUninitialize = 0,
    HpdAwarenessAlwaysConnected,
    HpdAwarenessNone,
    HpdAwarenessPolled,
    HpdAwarenessInterruptible,
}DRSD_CHILD_DEVICE_HPD_AWARENESS;
typedef DRSD_CHILD_DEVICE_HPD_AWARENESS* PDRSD_CHILD_DEVICE_HPD_AWARENESS;

typedef struct _DRSD_CHILD_CAPABILITIES{
    union{
        DRSD_VIDEO_OUTPUT_CAPABILITIES  VideoOuput;
        struct{
            UINT                        Mbz;
        }                               Other;
        DRSD_INTEGRATED_DISPLAY_CHILD   IntegratedDisplayChild;
    }Type;
    DRSD_CHILD_DEVICE_HPD_AWARENESS     HpdAwareness; 
}DRSD_CHILD_CAPABILITIES, * PDRSD_CHILD_CAPABILITIES;

typedef struct _DRSD_CHILD_DESCRIPTOR{
    DRSD_CHILD_DEVICE_TYPE  ChildDeviceType;
    DRSD_CHILD_CAPABILITIES ChildCapabilities;
    ULONG                   AcpiUid;
    ULONG                   ChildUid;
}DRSD_CHILD_DESCRIPTOR, * PDRSD_CHILD_DESCRIPTOR;

typedef LOUSTATUS DRSD_DDI_QUERY_CHILD_RELATIONS(PVOID, PDRSD_CHILD_DESCRIPTOR, ULONG);
typedef DRSD_DDI_QUERY_CHILD_RELATIONS* PDRSD_DDI_QUERY_CHILD_RELATIONS;

typedef enum {
    StatusUninitialized = 0,
    StatusConnection,
    StatusRotation,
    StatusMiracastConnection,
}DRSD_CHILD_STATUS_TYPE;
typedef DRSD_CHILD_STATUS_TYPE* PDRSD_CHILD_STATUS_TYPE;


typedef struct _DRSD_CHILD_STATUS{
    DRSD_CHILD_STATUS_TYPE                          Type;
    ULONG                                           ChildUid;
    union{
        struct{
            BOOLEAN                                 Connected;
        }                                           HotPlug;
        struct{
            UCHAR                                   Angle;
        }                                           Rotation;
        struct{
            BOOLEAN                                 Connected;
            DRSD3D_KMDT_VIDEO_OUTPUT_TECHNOLOGY     MiracastMonitorType;
        }                                           Miracast;
    };
}DRSD_CHILD_STATUS, * PDRSD_CHILD_STATUS;

typedef LOUSTATUS DRSD_DDI_QUERY_CHILD_STATUS(PVOID, PDRSD_CHILD_STATUS, BOOLEAN);
typedef DRSD_DDI_QUERY_CHILD_STATUS* PDRSD_DDI_QUERY_CHILD_STATUS;

typedef struct _DRSD_DEVICE_DESCRIPTOR{
    ULONG   DescriptorOffset;
    ULONG   DescriptorLength;
    PVOID   DescriptorBuffer;
}DRSD_DEVICE_DESCRIPTOR, * PDRSD_DEVICE_DESCRIPTOR;

typedef LOUSTATUS DRSD_DDI_QUERY_DEVICE_DESCRIPTOR(PVOID, ULONG, PDRSD_DEVICE_DESCRIPTOR);
typedef DRSD_DDI_QUERY_DEVICE_DESCRIPTOR* PDRSD_DDI_QUERY_DEVICE_DESCRIPTOR;

typedef LOUSTATUS DRSD_DDI_SET_POWER_STATE(PVOID, ULONG, DEVICE_POWER_STATE, POWER_ACTION);
typedef DRSD_DDI_SET_POWER_STATE* PDRSD_DDI_SET_POWER_STATE;

typedef enum{
    DrsdUndefinedEvent = 0,
    DrsdAcpiEvent,
    DrsdPowerStateEvent,
    DrsdDockingEvent,
    DrsdChainedAcpiEvent,
}DRSD_EVENT_TYPE;
typedef DRSD_EVENT_TYPE* PDRSD_EVENT_TYPE;

typedef LOUSTATUS DRSD_DDI_NOTIFY_ACPI_EVENT(PVOID, DRSD_EVENT_TYPE, ULONG, PVOID, PULONG);
typedef DRSD_DDI_NOTIFY_ACPI_EVENT* PDRSD_DDI_NOTIFY_ACPI_EVENT;

typedef void DRSD_DDI_RESET_DEVICE(PVOID);
typedef DRSD_DDI_RESET_DEVICE* PDRSD_DDI_RESET_DEVICE;

typedef void DRSD_DDI_UNLOAD();
typedef DRSD_DDI_UNLOAD* PDRSD_DDI_UNLOAD;

typedef struct _QUERY_INTERFACE{
    PGUID       InterfaceType;
    USHORT      Size;
    USHORT      Version;
    PINTERFACE  Interface;
    PVOID       InterfaceSpecificData;
    ULONG       DeviceUid;
}QUERY_INTERFACE, * PQUERY_INTERFACE;

typedef LOUSTATUS DRSD_DDI_QUERY_INTERFACE(PVOID, PQUERY_INTERFACE);
typedef DRSD_DDI_QUERY_INTERFACE* PDRSD_DDI_QUERY_INTERFACE;

typedef void DRSD_DDI_CONTROL_ETW_LOGGING(BOOLEAN, LONG, UCHAR);
typedef DRSD_DDI_CONTROL_ETW_LOGGING* PDRSD_DDI_CONTROL_ETW_LOGGING;

typedef enum{
    DRSD_QAI_TYPE_UMDRIVER_PRIVATE = 0,
    DRSD_QAI_TYPE_DRIVER_CAPS = 1,
    DRSD_QAI_TYPE_QUERY_SEGMENT = 2,
    DRSD_QAI_TYPE_RESERVED = 3, 
    DRSD_QAI_TYPE_QUERY_SEGMENT2 = 4,
    DRSD_QAI_TYPE_QUERY_SEGMENT3 = 5,
    DRSD_QAI_TYPE_NUM_POWER_COMPONENTS = 6,
    DRSD_QAI_TYPE_POWER_COMPONENT_INFO = 7,
    DRSD_QAI_TYPE_PREFERED_GPU_NODE = 8,
    DRSD_QAI_TYPE_POWER_COMPONENT_PSTATE_INFO = 9,
    DRSD_QAI_TYPE_HISTORY_BUFFER_PRECISION = 10,
    DRSD_QAI_TYPE_QUERY_SEGMENT4 = 11,
    DRSD_QAI_TYPE_SEGMENT_MEMORY_STATE = 12,
    DRSD_QAI_TYPE_GPU_MMU_CAPS = 13,
    DRSD_QAI_TYPE_PAGE_TABLE_LEVEL_DESC = 14,
    DRSD_QAI_TYPE_PHYSICAL_ADAPTER_CAPS = 15,
    DRSD_QAI_TYPE_DISPLAY_DRIVER_CAPS_EXTENTION = 16,
    DRSD_QAI_TYPE_INTEGRATED_DISPLAY_DESCRIPTOR = 17,
    DRSD_QAI_TYPE_UEFI_FRAMEBUFFER_RANGES = 18,
    DRSD_QAI_TYPE_QUERY_COLORIMETRY_OVERIDES = 19,
    DRSD_QAI_TYPE_DISPLAY_ID_DESCRIPTOR = 20,
    DRSD_QAI_TYPE_FRAMEBUFFER_SAVE_SIZE = 21,
    DRSD_QAI_TYPE_HARDWARE_RESERVED_RANGES = 22,
    DRSD_QAI_TYPE_INTEGRATED_DISPLAY_DESCRIPTOR2 = 23,
    DRSD_QAI_TYPE_NODE_PREF_DATA = 24,
    DRSD_QAI_TYPE_ADAPTER_PREF_DATA = 25,
    DRSD_QAI_TYPE_ADAPTER_PREF_DATA_CAPS = 26,
    DRSD_QAI_TYPE_GPU_VERSION = 27,
    DRSD_QAI_TYPE_DEVICE_TYPE_CAPS = 28,
    DRSD_QAI_TYPE_DRSD_DEVICE_CAPS = 29,
    DRSD_QAI_TYPE_GPU_CAPS = 30,
    DRSD_QAI_TYPE_QUERY_TARGET_GAMMA_CAPS = 31,
    DRSD_QAI_TYPE_SCANOUT_CAPS = 33,
    DRSD_QAI_TYPE_PHYSICAL_MEMORY_CAPS = 34,
    DRSD_QAI_TYPE_IOMMU_CAPS = 35,
    DRSD_QAI_TYPE_HARDWARE_RESERVED_RANGES2 = 36,
    DRSD_QAI_TYPE_NATIVE_FENCE_CAPS = 37,
    DRSD_QAI_TYPE_USERMODE_SUBMISSION_CAPS = 38,
    DRSD_QAI_TYPE_DIRTY_BIT_TRACKING_CAPS = 39,
    DRSD_QAI_TYPE_DIRTY_BIT_TRACKING_SEGMENT_CAPS = 40,
    DRSD_QAI_TYPE_SCATTER_RESERVE = 41,
    DRSD_QAI_TYPE_QUERY_PAGING_BUFFER_INFO = 42,
    DRSD_QAI_TYPE_QUERY_SEGMENT_COUNT = 43,
    DRSD_QAI_TYPE_QUERY_SEGMENT5 = 44,
    DRSD_QAI_TYPE_QUERY_MMU_COUNT = 45,
    DRSD_QAI_TYPE_QUERY_MMUS = 46,
    DRSD_QAI_TYPE_64BIT_ONLY_CAPS = 47,
    DRSD_QAI_TYPE_PAGING_PROCESS_GPU_VA_SIZE = 48,
}DRSD_QUERY_ADAPTER_INFO_TYPE;
typedef DRSD_QUERY_ADAPTER_INFO_TYPE* PDRSD_QUERY_ADAPTER_INFO_TYPE;

typedef struct _DRSD_QUERY_ADAPTER_INFO_FLAGS{
    union{
        struct {
            UINT    VmData   : 1;
            UINT    Svm      : 1;
            UINT    Reserved : 30; 
        };
        UINT        Value;
    };
}DRSD_QUERY_ADAPTER_INFO_FLAGS, * PDRSD_QUERY_ADAPTER_INFO_FLAGS;

typedef struct _DRSD_ARG_QUERY_ADAPTER_INFO{
    DRSD_QUERY_ADAPTER_INFO_TYPE    Type;
    PVOID                           InputData;
    UINT                            InputDataSize;
    PVOID                           OutputData;
    UINT                            OutputDataSize;
    DRSD_QUERY_ADAPTER_INFO_FLAGS   Flags;
    HANDLE                          KernelProcessHandle;
}DRSD_ARG_QUERY_ADAPTER_INFO, * PDRSD_ARG_QUERY_ADAPTER_INFO;

typedef LOUSTATUS DRSD_DDI_QUERY_ADAPTER_INFO(HANDLE, PDRSD_ARG_QUERY_ADAPTER_INFO);
typedef DRSD_DDI_QUERY_ADAPTER_INFO* PDRSD_DDI_QUERY_ADAPTER_INFO;

typedef LOUSTATUS DRSD_DDI_CREATE_DEVICE(HANDLE, PDRSD_ARG_CREATE_DEVICE);
typedef DRSD_DDI_CREATE_DEVICE* PDRSD_DDI_CREATE_DEVICE;

typedef struct _DRSD_SEGMENT_BANK_PREFERENCE{
    union{
        struct{
            UINT    Bank0       :   7;
            UINT    Direction0  :   1;
            UINT    Bank1       :   7;
            UINT    Direction1  :   1;
            UINT    Bank2       :   7;
            UINT    Direction2  :   1;
            UINT    Bank3       :   7;
            UINT    Direction3  :   1;
        };
        UINT        Value;
    };
}DRSD_SEGMENT_BANK_PREFERENCE, * PDRSD_SEGMENT_BANK_PREFERENCE;

typedef struct _DRSD_SEGMENT_PREFERENCE{
    union{
        struct{
            UINT    SegmentId0  :   5;
            UINT    Direction0  :   1;
            UINT    SegmentId1  :   5;
            UINT    Direction1  :   1;
            UINT    SegmentId2  :   5;
            UINT    Direction2  :   1;
            UINT    SegmentId3  :   5;
            UINT    Direction3  :   1;
            UINT    SegmentId4  :   5;
            UINT    Direction4  :   1;
            UINT    Reserved    :   2;
        };
        UINT        Value;
    };
}DRSD_SEGMENT_PREFERENCE, * PDRSD_SEGMENT_PREFERENCE;

typedef struct _DRSD_ALLOCATION_INFO_FLAGS{
    union{
        struct{
            UINT    CpuVisable                      :   1;
            UINT    PermanentSysMem                 :   1;
            UINT    Cached                          :   1;
            UINT    Protected                       :   1;
            UINT    ExistingSysMem                  :   1;
            UINT    ExistingKernelSysMem            :   1;
            UINT    FromEndOfSegment                :   1;
            UINT    Swizzled                        :   1;
            UINT    Overlay                         :   1;
            UINT    Capture                         :   1;
            UINT    UseAlternateVa                  :   1;
            UINT    SynchronusPaging                :   1;
            UINT    LinkMirrored                    :   1;
            UINT    LingInstanced                   :   1;
            UINT    HistoryBuffer                   :   1;
            UINT    AccessedPhysically              :   1;
            UINT    ExplicitResidencyNotification   :   1;
            UINT    HardwareProtected               :   1;
            UINT    CpuVisableOnDemand              :   1;
            UINT    Reserved                        :   4;
            UINT    DRSD_ALLOC_RESERVED16           :   1;
            UINT    DRSD_ALLOC_RESERVED15           :   1;
            UINT    DRSD_ALLOC_RESERVED14           :   1;
            UINT    DRSD_ALLOC_RESERVED13           :   1;
            UINT    DRSD_ALLOC_RESERVED12           :   1;
            UINT    DRSD_ALLOC_RESERVED11           :   1;
            UINT    DRSD_ALLOC_RESERVED10           :   1;
            UINT    DRSD_ALLOC_RESERVED9            :   1;
            UINT    DRSD_ALLOC_RESERVED4            :   1;
            UINT    DRSD_ALLOC_RESERVED3            :   1;
            UINT    DRSD_ALLOC_RESERVED2            :   1;
            UINT    DRSD_ALLOC_RESERVED1            :   1;
            UINT    DRSD_ALLOC_RESERVED0            :   1;
        };
        UINT        Value;
    };
}DRSD_ALLOCATION_INFO_FLAGS, * PDRSD_ALLOCATION_INFO_FLAGS;

typedef struct _DRSD_ALLOCATION_INFO_FLAGS_LDDM2_0{
    union{
        struct{
            UINT    CpuVisable                      :   1;
            UINT    PermanentSysMem                 :   1;
            UINT    Cached                          :   1;
            UINT    Protected                       :   1;
            UINT    ExistingSysMem                  :   1;
            UINT    ExistingKernelSysMem            :   1;
            UINT    FromEndOfSegment                :   1;
            UINT    DisableLargePageMapping         :   1;
            UINT    Overlay                         :   1;
            UINT    Capture                         :   1;
            UINT    CreateInVpr                     :   1;
            UINT    Reserved00                      :   1;
            UINT    DRSD_ALLOC_RESERVED17           :   1;
            UINT    Reserved02                      :   1;
            UINT    MapApertureCpuVisable           :   1;
            UINT    Reserved03                      :   1;
            UINT    HistoryBuffer                   :   1;
            UINT    AccessedPhysically              :   1;
            UINT    ExplicitResidencyNotification   :   1;
            UINT    HardwareProtected               :   1;
            UINT    CpuVisableOnDemand              :   1;
            UINT    DRSD_ALLOC_RESERVED16           :   1;
            UINT    DRSD_ALLOC_RESERVED15           :   1;
            UINT    DRSD_ALLOC_RESERVED14           :   1;
            UINT    DRSD_ALLOC_RESERVED13           :   1;
            UINT    DRSD_ALLOC_RESERVED12           :   1;
            UINT    DRSD_ALLOC_RESERVED11           :   1;
            UINT    DRSD_ALLOC_RESERVED10           :   1;
            UINT    DRSD_ALLOC_RESERVED9            :   1;
            UINT    DRSD_ALLOC_RESERVED4            :   1;
            UINT    DRSD_ALLOC_RESERVED3            :   1;
            UINT    DRSD_ALLOC_RESERVED2            :   1;
            UINT    DRSD_ALLOC_RESERVED1            :   1;
            UINT    DRSD_ALLOC_RESERVED0            :   1;
        };
        UINT        Value;
    };
}DRSD_ALLOCATION_INFO_FLAGS_LDDM2_0, * PDRSD_ALLOCATION_INFO_FLAGS_LDDM2_0;

typedef enum{
    D3DDDIFMT_UNKNOWN = 0,
    D3DDDIFMT_R8G8B8,
    D3DDDIFMT_A8R8G8B8,
    D3DDDIFMT_X8R8G8B8,
    D3DDDIFMT_R5G6B5,
    D3DDDIFMT_X1R5G5B5,
    D3DDDIFMT_A1R5G5B5,
    D3DDDIFMT_A4R4G4B4,
    D3DDDIFMT_R3G3B2,
    D3DDDIFMT_A8,
    D3DDDIFMT_A8R3G3B2,
    D3DDDIFMT_X4R4G4B4,
    D3DDDIFMT_A2B10G10R10,
    D3DDDIFMT_A8B8G8R8,
    D3DDDIFMT_X8B8G8R8,
    D3DDDIFMT_G16R16,
    D3DDDIFMT_A2R10G10B10,
    D3DDDIFMT_A16B16G16R16,
    D3DDDIFMT_A8P8,
    D3DDDIFMT_P8,
    D3DDDIFMT_L8,
    D3DDDIFMT_A8L8,
    D3DDDIFMT_A4L4,
    D3DDDIFMT_V8U8,
    D3DDDIFMT_L6V5U5,
    D3DDDIFMT_X8L8V8U8,
    D3DDDIFMT_Q8W8V8U8,
    D3DDDIFMT_V16U16,
    D3DDDIFMT_W11V11U10,
    D3DDDIFMT_A2W10V10U10,
    D3DDDIFMT_UYVY,
    D3DDDIFMT_R8G8_B8G8,
    D3DDDIFMT_YUY2,
    D3DDDIFMT_G8R8_G8B8,
    D3DDDIFMT_DXT1,
    D3DDDIFMT_DXT2,
    D3DDDIFMT_DXT3,
    D3DDDIFMT_DXT4,
    D3DDDIFMT_DXT5,
    D3DDDIFMT_D16_LOCKABLE,
    D3DDDIFMT_D32,
    D3DDDIFMT_D15S1,
    D3DDDIFMT_D24S8,
    D3DDDIFMT_D24X8,
    D3DDDIFMT_D24X4S4,
    D3DDDIFMT_D16,
    D3DDDIFMT_D32F_LOCKABLE,
    D3DDDIFMT_D24FS8,
    D3DDDIFMT_D32_LOCKABLE,
    D3DDDIFMT_S8_LOCKABLE,
    D3DDDIFMT_S1D15,
    D3DDDIFMT_S8D24,
    D3DDDIFMT_X8D24,
    D3DDDIFMT_X4S4D24,
    D3DDDIFMT_L16,
    D3DDDIFMT_G8R8,
    D3DDDIFMT_R8,
    D3DDDIFMT_VERTEXDATA,
    D3DDDIFMT_INDEX16,
    D3DDDIFMT_INDEX32,
    D3DDDIFMT_Q16W16V16U16,
    D3DDDIFMT_MULTI2_ARGB8,
    D3DDDIFMT_R16F,
    D3DDDIFMT_G16R16F,
    D3DDDIFMT_A16B16G16R16F,
    D3DDDIFMT_R32F,
    D3DDDIFMT_G32R32F,
    D3DDDIFMT_A32B32G32R32F,
    D3DDDIFMT_CxV8U8,
    D3DDDIFMT_A1,
    D3DDDIFMT_A2B10G10R10_XR_BIAS,
    D3DDDIFMT_DXVACOMPBUFFER_BASE,
    D3DDDIFMT_PICTUREPARAMSDATA,
    D3DDDIFMT_MACROBLOCKDATA,
    D3DDDIFMT_RESIDUALDIFFERENCEDATA,
    D3DDDIFMT_DEBLOCKINGDATA,
    D3DDDIFMT_INVERSEQUANTIZATIONDATA,
    D3DDDIFMT_SLICECONTROLDATA,
    D3DDDIFMT_BITSTREAMDATA,
    D3DDDIFMT_MOTIONVECTORBUFFER,
    D3DDDIFMT_FILMGRAINBUFFER,
    D3DDDIFMT_DXVA_RESERVED9,
    D3DDDIFMT_DXVA_RESERVED10,
    D3DDDIFMT_DXVA_RESERVED11,
    D3DDDIFMT_DXVA_RESERVED12,
    D3DDDIFMT_DXVA_RESERVED13,
    D3DDDIFMT_DXVA_RESERVED14,
    D3DDDIFMT_DXVA_RESERVED15,
    D3DDDIFMT_DXVA_RESERVED16,
    D3DDDIFMT_DXVA_RESERVED17,
    D3DDDIFMT_DXVA_RESERVED18,
    D3DDDIFMT_DXVA_RESERVED19,
    D3DDDIFMT_DXVA_RESERVED20,
    D3DDDIFMT_DXVA_RESERVED21,
    D3DDDIFMT_DXVA_RESERVED22,
    D3DDDIFMT_DXVA_RESERVED23,
    D3DDDIFMT_DXVA_RESERVED24,
    D3DDDIFMT_DXVA_RESERVED25,
    D3DDDIFMT_DXVA_RESERVED26,
    D3DDDIFMT_DXVA_RESERVED27,
    D3DDDIFMT_DXVA_RESERVED28,
    D3DDDIFMT_DXVA_RESERVED29,
    D3DDDIFMT_DXVA_RESERVED30,
    D3DDDIFMT_DXVA_RESERVED31,
    D3DDDIFMT_DXVACOMPBUFFER_MAX,
    D3DDDIFMT_BINARYBUFFER,
    D3DDDIFMT_FORCE_UINT
}D3DDDIFORMAT;

typedef struct _DRSD_ALLOCATION_USAGE_INFO1{
    union{
        struct{
            UINT        PrivateFormat   :   1;
            UINT        Swizzled        :   1;
            UINT        MipMap          :   1;
            UINT        Cube            :   1;
            UINT        Volume          :   1;
            UINT        Vertex          :   1;
            UINT        Index           :   1;
            UINT        Reserved        :   25;
        };
        UINT            Value;
    }                   Flags;
    union{
        D3DDDIFORMAT    Format;
        UINT            PrivateFormat;
    };
    UINT                SwizzledFormat;
    UINT                ByteOffset;
    UINT                Width;
    UINT                Height;
    UINT                Pitch;
    UINT                Depth;
    UINT                SlicePitch;
}DRSD_ALLOCATION_USAGE_INFO1, * PDRSD_ALLOCATION_USAGE_INFO1;

typedef struct _DRSD_ALLOCATION_USAGE_HINT{
    UINT                        Version;
    DRSD_ALLOCATION_USAGE_INFO1 v1;
}DRSD_ALLOCATION_USAGE_HINT, * PDRSD_ALLOCATION_USAGE_HINT;

typedef struct _DRSD_ALLOCATION_INFO_FLAGS2{
    union{
        struct{
            UINT    SharedBackingStoreWithKmd               :   1;
            UINT    NoImplicitSynchronization               :   1;
            UINT    DisablePartialResidency                 :   1;
            UINT    RestrictedToSingleSegment               :   1;
            UINT    NeedPagingVaAtResidencyNotification     :   1;
            UINT    Reserved01                              :   1;
            UINT    FaultAndStall                           :   1;
            UINT    Reserved                                :   25;
        };
        UINT        Value;
    };
}DRSD_ALLOCATION_INFO_FLAGS2, * PDRSD_ALLOCATION_INFO_FLAGS2;

typedef struct _DRSD_ALLOCATION_INFO{
    PVOID                                   PrivateDriverData;
    UINT                                    PrivateDriverDataSize;
    union{
        UINT                                Alignment;
        struct{
            UINT16                          MinimumPageSize;
            UINT16                          RecomendedPageSize;
        };
    };
    SIZE                                    Size;
    SIZE                                    PitchAlignment;
    DRSD_SEGMENT_BANK_PREFERENCE            HintedBlank;
    DRSD_SEGMENT_PREFERENCE                 PreferedSegment;
    union{
        UINT                                SupportedReadSegmentSet;
        UINT                                MmuSet;
    };
    UINT                                    SupportedWriteSegmentSet;
    UINT                                    EvictionSegmentSet;
    union{
        UINT                                MaximumRenamingListLength;
        UINT                                PhyscialAdapterIndex;
    };
    HANDLE                                  Allocation;
    union{
        DRSD_ALLOCATION_INFO_FLAGS          Flags;
        DRSD_ALLOCATION_INFO_FLAGS_LDDM2_0  FlagsLddm2;
    };
    PDRSD_ALLOCATION_USAGE_HINT             AllocationUsageHint;
    UINT                                    AllocationPriority;
    DRSD_ALLOCATION_INFO_FLAGS2             Flags2;
}DRSD_ALLOCATION_INFO, * PDRSD_ALLOCATION_INFO;

typedef struct _DRSD_CREATE_ALLOCATION_FLAGS{
    union{
        struct{
            UINT    Resource : 1;
            UINT    Reserved : 31;
        };
        UINT        Flags;
    };
}DRSD_CREATE_ALLOCATION_FLAGS, * PDRSD_CREATE_ALLOCATION_FLAGS;

typedef struct _DRSD_ARG_CREATE_ALLOCATION{
    const PVOID                     PrivateDriverData;
    UINT                            PrivateDriverDataSize;
    UINT                            NumAllocations;
    PDRSD_ALLOCATION_INFO           AllocationInfo;
    HANDLE                          Resource;
    DRSD_CREATE_ALLOCATION_FLAGS    Flags;
}DRSD_ARG_CREATE_ALLOCATION, * PDRSD_ARG_CREATE_ALLOCATION;

typedef LOUSTATUS DRSD_DDI_CREATE_ALLOCATION(HANDLE, PDRSD_ARG_CREATE_ALLOCATION);
typedef DRSD_DDI_CREATE_ALLOCATION* PDRSD_DDI_CREATE_ALLOCATION;

typedef struct _DRSD_DESTROY_ALLOCATION_FLAGS{
    union{
        struct{
            UINT    DestroyResource :   1;
            UINT    Reserved        :   31;
        };
        UINT        Value;
    };
}DRSD_DESTROY_ALLOCATION_FLAGS, * PDRSD_DESTROY_ALLOCATION_FLAGS;

typedef struct _DRSD_ARG_DESTROY_ALLOCATION_FLAGS{
    UINT                            NumAllocations;
    const PHANDLE                   AllocationList;
    HANDLE                          Resource;
    DRSD_DESTROY_ALLOCATION_FLAGS   Flags;
}DRSD_ARG_DESTROY_ALLOCATION_FLAGS, * PDRSD_ARG_DESTROY_ALLOCATION_FLAGS;

typedef LOUSTATUS DRSD_DDI_DESTROY_ALLOCATION(HANDLE, PDRSD_ARG_DESTROY_ALLOCATION_FLAGS);
typedef DRSD_DDI_DESTROY_ALLOCATION* PDRSD_DDI_DESTROY_ALLOCATION;

typedef struct _D3DDDI_MULTISAMPLING_METHOD{
    UINT    NumSamples;
    UINT    NumQualityLevels;
}D3DDDI_MULTISAMPLING_METHOD, * PD3DDDI_MULTISAMPLING_METHOD;

typedef struct _D3DDDI_RATIONAL{
    UINT    Numerator;
    UINT    Denomerator;
}D3DDDI_RATIONAL, * PD3DDDI_RATIONAL;

typedef struct _DRSD_DESCRIBE_ALLOCATION_FLAGS{
    union{
        struct{
            UINT    CheckDisplayMode    :   1;
            UINT    Reserved            :   31;
        };
        UINT        Value;
    };
}DRSD_DESCRIBE_ALLOCATION_FLAGS, * PDRSD_DESCRIBE_ALLOCATION_FLAGS;

typedef enum{
    D3DDDI_ROTATION_IDENTITY = 0,
    D3DDDI_ROTATION_90,
    D3DDDI_ROTATION_180,
    D3DDDI_ROTATION_270
}D3DDDI_ROTATION;

typedef struct _DRSD_ARG_DESCRIBE_ALLOCATION{
    HANDLE                          Allocation;
    UINT                            Width;
    UINT                            Height;
    D3DDDIFORMAT                    Format;
    D3DDDI_MULTISAMPLING_METHOD     MultisamplingMethod;
    D3DDDI_RATIONAL                 RefreshRate;
    UINT                            PrivateDriverFormatAttribute;
    DRSD_DESCRIBE_ALLOCATION_FLAGS  Flags;
    D3DDDI_ROTATION                 Rotation;
}DRSD_ARG_DESCRIBE_ALLOCATION, * PDRSD_ARG_DESCRIBE_ALLOCATION;

typedef LOUSTATUS DRSD_DDI_DESCRIBE_ALLOCATION(HANDLE, PDRSD_ARG_DESCRIBE_ALLOCATION);
typedef DRSD_DDI_DESCRIBE_ALLOCATION* PDRSD_DDI_DESCRIBE_ALLOCATION;

typedef enum{
    DRSD_D3D_STANDARD_ALLOCATION_SHARED_PRIMARY_SURFACE = 1,
    DRSD_D3D_STANDARD_ALLOCATION_SHADOW_SURFACE,
    DRSD_D3D_STANDARD_ALLOCATION_STAGING_SURFACE,
    DRSD_D3D_STANDARD_ALLOCATION_GDI_SURFACE,
    DRSD_D3D_STANDARD_ALLOCATION_VGPU,
    DRSD_D3D_STANDARD_ALLOCATION_FENCE_STORAGE,
}DRSD_D3D_STANDARD_ALLOCATION_TYPE;

typedef UINT D3DDDI_VIDEO_PRESENT_SOURCE_ID;


typedef struct _DRSD_D3D_SHARED_PRIMARY_SURFACE_DATA{
    UINT                            Width;
    UINT                            Height;
    D3DDDIFORMAT                    Format;
    D3DDDI_RATIONAL                 RefreshRate;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
}DRSD_D3D_SHARED_PRIMARY_SURFACE_DATA, * PDRSD_D3D_SHARED_PRIMARY_SURFACE_DATA;

typedef struct _DRSD_D3D_SHADOW_SURFACE_DATA{
    UINT            Width;
    UINT            Height;
    D3DDDIFORMAT    Format;
    UINT            Pitch;
}DRSD_D3D_SHADOW_SURFACE_DATA, * PDRSD_D3D_SHADOW_SURFACE_DATA;

typedef struct _DRSD_D3D_STAGING_SURFACE_DATA{
    UINT    Width;
    UINT    Height;
    UINT    Pitch;
}DRSD_D3D_STAGING_SURFACE_DATA, * PDRSD_D3D_STAGING_SURFACE_DATA;

typedef enum{
    DRSD_D3D_GDI_SURFACE_INVALID = 0,
    DRSD_D3D_GDI_SURFACE_TEXTURE,
    DRSD_D3D_GDI_SURFACE_STAGING_CPUVISIBLE,
    DRSD_D3D_GDI_SURFACE_STAGING,
    DRSD_D3D_GDI_SURFACE_LOOKUPTABLE,
    DRSD_D3D_GDI_SURFACE_EXISTINGSYSMEM,
    DRSD_D3D_GDI_SURFACE_TEXTURE_CPUVISIBLE,
    DRSD_D3D_GDI_SURFACE_TEXTURE_CROSSADAPTER,
    DRSD_D3D_GDI_SURFACE_TEXTURE_CPUVISIBLE_CROSSADAPTER,
}DRSD_D3D_GDI_SURFACE_TYPE;

typedef struct _DRSD_D3D_GDI_SURFACE_FLAGS{
    union{
        struct{
            UINT    Reserved : 32;
        };
        UINT        Value;
    };
}DRSD_D3D_GDI_SURFACE_FLAGS, * PDRSD_D3D_GDI_SURFACE_FLAGS;

typedef struct _DRSD_D3D_GDI_SURFACE_DATA{
    UINT                        Width;
    UINT                        Height;
    D3DDDIFORMAT                Format;
    DRSD_D3D_GDI_SURFACE_TYPE   Type;
    DRSD_D3D_GDI_SURFACE_FLAGS  Flags;
    UINT                        Pitch;
}DRSD_D3D_GDI_SURFACE_DATA, * PDRSD_D3D_GDI_SURFACE_DATA;

typedef struct _DRSD_D3D_VIRTUAL_GPU_SURFACE_DATA{
    UINT64  Size;
    UINT    Alignment;
    UINT    DriverSegmentId;
    UINT    PrivateDriverData;
}DRSD_D3D_VIRTUAL_GPU_SURFACE_DATA, * PDRSD_D3D_VIRTUAL_GPU_SURFACE_DATA;

typedef enum{
    DRSD_ARG_FENCE_STORAGE_VALUE_TYPE_CURRENT_VALUE = 0,   
    DRSD_ARG_FENCE_STORAGE_VALUE_TYPE_MONITORED_VALUE,   
}DRSD_ARG_FENCE_STORAGE_VALUE_TYPE;

typedef enum{
    D3DDDI_NATIVE_FENCE_TYPE_DEFAULT = 0,
    D3DDDI_NATIVE_FENCE_TYPE_INTRA_GPU,
}D3DDDI_NATIVE_FENCE_TYPE;

typedef struct _DRSD_ARG_FENCE_STORAGE_FLAGS{
    UINT    Reserved;
}DRSD_ARG_FENCE_STORAGE_FLAGS, * PDRSD_ARG_FENCE_STORAGE_FLAGS;

typedef struct _DRSD_D3D_FENCE_STORAGE_SURFACE_DATA{
    UINT                                PhyscialAdapterIndex;
    DRSD_ARG_FENCE_STORAGE_VALUE_TYPE   FenceStorageValueType;
    D3DDDI_NATIVE_FENCE_TYPE            FenceStorageType;
    DRSD_ARG_FENCE_STORAGE_FLAGS        Flags;
    UINT                                Reserved;
    DRSD_ALLOCATION_INFO                AllocationInfo;
}DRSD_D3D_FENCE_STORAGE_SURFACE_DATA, * PDRSD_D3D_FENCE_STORAGE_SURFACE_DATA;

typedef struct _DRSD_ARG_GET_STANDARD_ALLOCATION_DRIVER_DATA{
    DRSD_D3D_STANDARD_ALLOCATION_TYPE           StandardAllocationType;
    union{
        PDRSD_D3D_SHARED_PRIMARY_SURFACE_DATA   CreateSharedPrimarySurfaceData;
        PDRSD_D3D_SHADOW_SURFACE_DATA           CreateShadowSurfaceData;
        PDRSD_D3D_STAGING_SURFACE_DATA          CreateStagingSurfaceData;
        PDRSD_D3D_GDI_SURFACE_DATA              CreateGdiSurfaceData;
        PDRSD_D3D_VIRTUAL_GPU_SURFACE_DATA      CreateVirtualGpuSurfaceData;
        PDRSD_D3D_FENCE_STORAGE_SURFACE_DATA    CreateFenceStorageData;
    };
    PVOID                                       AllocationPrivateDriverData;
    UINT                                        AllocationPrivateDriverDataSize;
    PVOID                                       ResourcePrivateDriverData;
    UINT                                        ResourcePrivateDriverDataSize;
    UINT                                        PhyscialAdapterIndex;
}DRSD_ARG_GET_STANDARD_ALLOCATION_DRIVER_DATA, * PDRSD_ARG_GET_STANDARD_ALLOCATION_DRIVER_DATA;

typedef LOUSTATUS DRSD_DDI_GET_STANDARD_ALLOCATION_DRIVER_DATA(HANDLE, PDRSD_ARG_GET_STANDARD_ALLOCATION_DRIVER_DATA);
typedef DRSD_DDI_GET_STANDARD_ALLOCATION_DRIVER_DATA* PDRSD_DDI_GET_STANDARD_ALLOCATION_DRIVER_DATA;

typedef struct _DRSD_DRIVER_INITIALIZATION_DATA{
    ULONG                                           Version;
    PDRSD_DDI_ADD_DEVICE                            DrsdDdiAddDevice;
    PDRSD_DDI_START_DEVICE                          DrsdDdiStartDevice;
    PDRSD_DDI_STOP_DEVICE                           DrsdDdiStopDevice;
    PDRSD_DDI_REMOVE_DEVICE                         DrsdDdiRemoveDevice;
    PDRSD_DDI_DISPATCH_IO_REQUEST                   DrsdDdiDispatchIoRequest;
    PDRSD_DDI_INTERRUPT_ROUTINE                     DrsdDdiInterruptRoutine;
    PDRSD_DDI_DPC_ROUTINE                           DrsdDdiDpcRoutine;
    PDRSD_DDI_QUERY_CHILD_RELATIONS                 DrsdDdiQueryChildRelations;
    PDRSD_DDI_QUERY_CHILD_STATUS                    DrsdDdiQueryChildStatus;
    PDRSD_DDI_QUERY_DEVICE_DESCRIPTOR               DrsdDdiQueryDeviceDescriptor;
    PDRSD_DDI_SET_POWER_STATE                       DrsdDdiSetPowerState;
    PDRSD_DDI_NOTIFY_ACPI_EVENT                     DrsdDdiNotifyAcpiEvent;
    PDRSD_DDI_RESET_DEVICE                          DrsdDdiResetDevice;
    PDRSD_DDI_UNLOAD                                DrsdDdiUnload;
    PDRSD_DDI_QUERY_INTERFACE                       DrsdDdiQueryInterface;
    PDRSD_DDI_CONTROL_ETW_LOGGING                   DrsdDdiControlEtwLogging;
    PDRSD_DDI_QUERY_ADAPTER_INFO                    DrsdDdiQueryAdapterInfo;
    PDRSD_DDI_CREATE_DEVICE                         DrsdDdiCreateDevice;
    PDRSD_DDI_CREATE_ALLOCATION                     DrsdDdiCreateAllocation;
    PDRSD_DDI_DESTROY_ALLOCATION                    DrsdDdiDestroyAllocation;
    PDRSD_DDI_DESCRIBE_ALLOCATION                   DrsdDdiDescribeAllocation;
    PDRSD_DDI_GET_STANDARD_ALLOCATION_DRIVER_DATA   DrsdDdiGetStandardAllocationDriverData;
    //PDXGKDDI_ACQUIRESWIZZLINGRANGE
}DRSD_DRIVER_INITIALIZATION_DATA, * PDRSD_DRIVER_INITIALIZATION_DATA;

#ifndef _USER_MODE_CODE_
#ifndef _DRSD_MAIN_INTERNALS
DRIVER_IMPORT LOUSTATUS DrsdCreateDevice(const HANDLE Adapter, PDRSD_ARG_CREATE_DEVICE CreateDevice);
#else
DRIVER_EXPORT LOUSTATUS DrsdCreateDevice(const HANDLE Adapter, PDRSD_ARG_CREATE_DEVICE CreateDevice);
#endif
#else //USER MODE CODE

#endif

#ifdef __cplusplus
}
#endif
#endif