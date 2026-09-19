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
    //next PDXGKDDI_RESET_DEVICE
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