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



typedef struct _DRSD_DRIVER_INITIALIZATION_DATA{
    ULONG                               Version;
    PDRSD_DDI_ADD_DEVICE                DrsdDdiAddDevice;
    PDRSD_DDI_START_DEVICE              DrsdDdiStartDevice;
    PDRSD_DDI_STOP_DEVICE               DrsdDdiStopDevice;
    PDRSD_DDI_REMOVE_DEVICE             DrsdDdiRemoveDevice;
    PDRSD_DDI_DISPATCH_IO_REQUEST       DrsdDdiDispatchIoRequest;
    PDRSD_DDI_INTERRUPT_ROUTINE         DrsdDdiInterruptRoutine;
    PDRSD_DDI_DPC_ROUTINE               DrsdDdiDpcRoutine;
    PDRSD_DDI_QUERY_CHILD_RELATIONS     DrsdDdiQueryChildRelations;
    PDRSD_DDI_QUERY_CHILD_STATUS        DrsdDdiQueryChildStatus;
    PDRSD_DDI_QUERY_DEVICE_DESCRIPTOR   DrsdDdiQueryDeviceDescriptor;
    PDRSD_DDI_SET_POWER_STATE           DrsdDdiSetPowerState;
    PDRSD_DDI_NOTIFY_ACPI_EVENT         DrsdDdiNotifyAcpiEvent;
    PDRSD_DDI_RESET_DEVICE              DrsdDdiResetDevice;
    PDRSD_DDI_UNLOAD                    DrsdDdiUnload;
    PDRSD_DDI_QUERY_INTERFACE           DrsdDdiQueryInterface;
    PDRSD_DDI_CONTROL_ETW_LOGGING       DrsdDdiControlEtwLogging;
    PDRSD_DDI_QUERY_ADAPTER_INFO        DrsdDdiQueryAdapterInfo;
    //next DXGKDDI_CREATEDEVICE
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