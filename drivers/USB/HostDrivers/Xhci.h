#define _KERNEL_MODULE_
#ifndef _XHCI_H
#define _XHCI_H
#include <LouDDK.h>
#include <usb.h>
#include "XhciExtCap.h"
#include "XhciPorts.h"
#include "XhciCap.h"

#define XHCI_MAX_DISPATCHES         500
#define XHCI_SBRN_OFFSET            0x60
#define XHCI_MAX_HC_SLOTS           256
#define XHCI_MAX_HC_PORTS           127

#define XHCI_REGISTER_PER_PORT      4
#define XHCI_SC_PORT                0
#define XHCI_PMSC_PORT              1
#define XHCI_LI_PORT                2
#define XHCI_HLPMC_PORT             3

#define XHCI_COMMAND_RESET          (1 << 1)
#define XHCI_COMMAND_LRESET         (1 << 7)
#define XHCI_COMMAND_CSS            (1 << 8)
#define XHCI_COMMAND_CRS            (1 << 9)
#define XHCI_COMMAND_PM_INDEX       (1 << 11)
#define XHCI_COMMAND_ETE            (1 << 14)

#define XHCI_RESET_LONG_TIMEOUT     (10 * 1000)
#define XHCI_RESET_SHORT_TIMEOUT    (250)

#define XHCI_STATUS_FATAL           (1 << 2)
#define XHCI_STATUS_EINT            (1 << 3)
#define XHCI_STATUS_PORT_CHANGE     (1 << 4)
#define XHCI_STATUS_SAVE            (1 << 8)
#define XHCI_STATUS_RESTORE         (1 << 9)
#define XHCI_STATUS_SRE             (1 << 10)
#define XHCI_STATUS_HCE             (1 << 12)

#define XHCI_DEVICE_NOTE_MASK       (0xFFFF)
#define XHCI_DEVICE_NOTE_WAKE       (1 << 1)

#define XHCI_DEVRNG_CYCLE           (1)
#define XHCI_DEVRNG_PAUSE           (1 << 1)
#define XHCI_DEVRNG_ABORT           (1 << 2)
#define XHCI_DEVRNG_RUNNING         (1 << 3)
#define XHCI_DEVRNG_POINTER_MASK    (0xFFFFFFFFFFFFFFD0)

#define XHCI_MAX_DEVICES(Port)      ((Port) & 0xFF)
#define XHCI_CONFIG_U3E             (1 << 8)
#define XHCI_CONFIG_CIE             (1 << 9)
#define XHCI_PAGE_SIZE_MASK         (0xFFFF)

#define XHCI_IMAN_IP                (1)
#define XHCI_IMAN_IE                (1 << 1)
#define XHCI_IMODI_MASK             (0xFFFF)
#define XHCI_IMODC_MASK             (0xFFFF << 16)

#define XHCI_ERST_SIZE_MASK         (0xFFFF)

#define XHCI_ERST_BASE_ADDRESS_MASK XHCI_DEVRNG_POINTER_MASK

#define XHCI_DESI_MASK              (0x07)
#define XHCI_ERST_EHB               (1 << 3)
#define XHCI_ERST_POINTER_MASK      (0xFFFFFFFFFFFFFFF0)

#define XHCI_DOORBELL_VALUE(Ep, Stream) ((((Ep) + 1) & 0xFF) | ((Stream) << 16))          
#define XHCI_DOORBELL_VALUE_HOST    (0)

#define XHCI_PLT_MASK               (0x03 << 6)
#define XHCI_PLT_SYM                (0)
#define XHCI_PLT_ASYM_RX            (0x02 << 6)
#define XCHI_PLT_ASYM_TX            (0x03 << 6)

#define XHCI_CONTEXT_TYPE_DEVICE    0x01
#define XHCI_CONTEXT_TYPE_INPUT     0x02

#define XHCI_ROUTE_STRING_MASK      (0xFFFFF)
#define XHCI_DEVICE_SPEED           (0x0F << 20)
#define XHCI_GET_DEVICE_SPEED(Port) (((Port) & XHCI_DEVICE_SPEED) >> 20)
#define XHCI_DEVICE_MTT             (0x01 << 25)
#define XHCI_DEVICE_HUB             (0x01 << 26)
#define XHCI_LAST_CONTEXT_MASK      (0x1F << 27)
#define XHCI_LAST_CONTEXT(Port)     ((Port) << 27)
#define XHCI_LAST_CONTEXT_TO_EP_NUMBER(Port)    (((Port) >> 27) - 1)
#define XCHI_SLOT_FLAG              (1)
#define XHCI_EP0_FLAG               (1 << 1)

#define XCHI_MAX_EXIT_LATENCY       (0xFFFF)

#define XHCI_ROOT_HUB_PORT(Port)    (((Port) & 0xFF) << 16)
#define XHCI_DEVICE_INFO_TO_ROOT_HUB_PORT(Port) (((Port) >> 16) & 0xFF)
#define XHCI_MAX_PORTS(Port)        (((Port) & 0xFF) << 24)
#define XHCI_DEVICE_INFO_TO_MAX_PORTS(Port) (XHCI_MAX_PORTS(Port) >> 24)

#define XHCI_TT_SLOT                (0xFF)
#define XHCI_TT_PORT                (0xFF << 8)
#define XHCI_TT_THINK_TIME(Port)    (((Port) & 0x03) << 16)
#define XHCI_GET_TT_THINK_TIME(Port) (XHCI_TT_THINK_TIME(Port) >> 16)

#define XHCI_DEVICE_ADDRESS_MASK    (0xFF)

#define XHCI_SLOT_STATE             (0x1f << 27)
#define XHCI_GET_SLOT_STATE(Port)   ((Port & XHCI_SLOT_STATE) >> 27)

#define XHCI_SLOT_STATE_DISABLED    0
#define XHCI_SLOT_STATE_ENABLED     0
#define XHCI_SLOT_STATE_DEFAULT     1
#define XHCI_SLOT_STATE_ADDRESSED   2
#define XHCI_SLOT_STATE_CONFIGURED  3

#define XHCI_EP_STATE_MASK          (0x07)
#define XHCI_EP_STATE_DISABLED      0
#define XHCI_EP_STATE_RUNNING       1
#define XHCI_EP_STATE_HALTED        2
#define XHCI_EP_STATE_STOPPED       3
#define XHCI_EP_STATE_ERROR         4

#define XHCI_GET_EP_CONTEXT_STATE(Context)  ((Context->EpInfo) & (XHCI_EP_STATE_MASK))

#define XHCI_EP_MULT(Port)          (((Port) & 0x03) << 8)
#define XHCI_CONTEXT_EP_MULT(Port)  (((Port) >> 8) & 0x03)
#define XHCI_EP_INTERVAL(Port)      (((Port) & 0xFF) << 16)
#define XHCI_EP_INTERNAL_TO_UFRAMES(Port) (1 << (((Port) >> 16) & 0xFF))
#define XHCI_CONTEXT_TO_EP_INTERVAL(Port) (((Port) >> 16) & 0xFF)
#define XHCI_MAX_EP_STREAMS_MASK    (0x1F << 10)
#define XHCI_MAX_EP_STREAMS(Port)   (((Port) << 10) & XHCI_MAX_EP_STREAMS_MASK)
#define XHCI_CONTEX_TO_MAX_EP_STREAM(Port)  (((Port) & XHCI_MAX_EP_STREAMS_MASK) >> 10)

#define XHCI_EP_HAS_LSA             (1 << 15)

#define XHCI_CONTEXT_TO_MAX_ESIT_PAYLOAD_HI(Port)       (((Port) >> 24) & 0xFF)

#define XHCI_FORCE_EVENT            (0x01)
#define XHCI_ERROR_COUNT(Port)      (((Port) & 0x03) << 1)
#define XHCI_CONTEXT_TO_EP_TYPE(Port)   (((Port) >> 3) & 0x07)
#define XHCI_EP_TYPE(Port)          (((Port) << 3))
#define XHCI_ISOC_OUT_EP            1
#define XHCI_BULK_OUT_EP            2
#define XHCI_INT_OUT_EP             3
#define XHCI_CONTROL_EP             4
#define XHCI_ISOC_IN_EP             5
#define XHCI_BULE_IN_EP             6
#define XHCI_INT_IN_EP              7

#define XHCI_MAX_BURST(Port)                (((Port) & 0xFF) << 8)
#define XHCI_CONTEXT_MAX_BURST(Port)        (((Port) >> 8) & 0xFF)
#define XHCI_MAX_PACKET(Port)               (((Port) & 0xFFFF) << 16)
#define XHCI_MAX_PACKET_MASK                (0xFFFF << 16)
#define XHCI_MAX_PAXKET_DECODED(Port)       (((Port) >> 16) & 0xFFFF)

#define XHCI_EP_AVERAGE_TRB_LENGTH(Port)    ((Port) & 0xFFFF)
#define XHCI_EP_MAX_ESIT_PAYLOAD_LO(Port)   (((Port) & 0xFFFF) << 16)
#define XHCI_EP_MAX_ESIT_PAYLOAD_HIGH(Port) ((((Port) >> 16) & 0xFF) << 24)
#define XHCI_TO_MAX_ESIT_PAYLOAD(Port)      (((Port) >> 16) & 0xFFFF)

#define XHCI_EP_CONTEXT_CYCLE_MASK          (1)
#define XHCI_SCONTEXT_DEQ_MASK64            (0xFFFFFFFFFFFFFFF0)
#define XHCI_SCONTEXT_DEQ_MASK32            (0xFFFFFFF0)

#define XHCI_EP_IS_ADDED(ControlContect, i)  (ControlContect-AddFlags & (1 << (i + 1)))
#define XHCI_EP_IS_DROPED(ControlContect, i)  (ControlContect-DropFlags & (1 << (i + 1)))

#define XHCI_DROP_EP(x)                     (0x01 << x)

#define XHCI_ADD_EP(x)                      (0x01 << x)

#define XHCI_SCT_FROM_CONTEXT(Port)         (((Port) & 0x07) << 1)
#define XHCI_CONTEXT_TO_CONTEXT(Port)       (((Port) >> 1) & 0x07)

#define XHCI_SCT_SECONDARY_TR               0
#define XHCI_SCT_PRIMARY_TR                 1
#define XHCI_SCT_SSA_8                      2
#define XHCI_SCT_SSA_16                     3
#define XHCI_SCT_SSA_32                     4
#define XHCI_SCT_SSA_64                     5
#define XHCI_SCT_SSA_128                    6
#define XHCI_SCT_SSA_256                    7

#define XHCI_SMALL_STREAM_ARRAY_SIZE        256
#define XHCI_MEDIUM_STREAM_ARRAY_SIZE       1024
#define GET_PORT_BW_ARRAY_SIZE              256

#define XHCI_FS_BLOCK       1
#define XHCI_HS_BLOCK       4
#define XHCI_SS_BLOCK       16
#define XHCI_DMI_BLOCK      32

#define XHCI_DMI_OVERHEAD           8
#define XHCI_DMI_OVERHEAD_BURST     4
#define XHCI_SS_OVERHEAD            8
#define XHCI_SS_OVERHEAD_BURST      32
#define XHCI_HS_OVERHEAD            26
#define XHCI_FS_OVERHEAD            20
#define XHCI_LS_OVERHEAD            128

#define XHCI_TT_HS_OVERHEAD         (31 + 94)
#define XHCI_TT_DMI_OVERHEAD        (25 + 12)

#define XHCI_FS_BW_LIMIT            1285
#define XHCI_TT_BW_LIMIT            1320
#define XHCI_HS_BW_LIMIT            1607
#define XHCI_SS_BW_LIMIT_IN         3906
#define XHCI_DMI_BW_LIMIT_IN        3906
#define XHCI_SS_BW_LIMIT_OUT        3906
#define XHCI_DMI_BW_LIMIT_OUT       3906

#define XHCI_FS_BW_RESERVED         10
#define XHCI_HS_BW_RESERVED         20
#define XHCI_SS_BW_RESERVED         10

#define XHCI_SET_DEQ_PENDING        (1)
#define XHCI_EP_HALTER              (1 << 1)
#define XHCI_EP_STOP_CMD_PENDING    (1 << 2)
#define XHCI_EP_GETTING_STREAMS     (1 << 3)
#define XHCI_EP_HAS_STREAMS         (1 << 4)
#define XHCI_EP_GETTING_NO_STREAMS  (1 << 5)
#define XHCI_EP_HARD_CLEAR_TOGGLE   (1 << 6)
#define XHCI_EP_SOFT_CLEAR_TOGGLE   (1 << 7)
#define XHCI_EP_CLEARING_TT         (1 << 8)

#define XHCI_MAX_INTERVAL           16

#define XHCI_EP_CONTEXT_PER_DEVICE  31

#define XHCI_VIRTUAL_DEVICE_PORT_ERROR  (1)

#define XHCI_TRB_TO_SLOT_ID(Port)           (((Port) >> 24) & 0xFF)
#define XHCI_SLOT_ID_TO_TRB(Port)           (((Port) & 0xFF) << 24)

#define XHCI_TRB_TO_EP_ID(Port)             (((Port) >> 16) & 0x1F)
#define XHCI_EP_ID_TO_TRB(Port)             (((Port) & 0x1F) << 16)

#define XHCI_TRB_TO_EP_INDEX(Port)          (XHCI_TRB_TO_EP_ID(Port) - 1)
#define XHCI_EP_INDEX_TO_TRB(Port)          ((((Port) + 1) & 0x1F) << 16)

#define XHCI_EVENT_TRB_LENGTH(Port)         ((Port) & 0xFFFFFF)
#define XHCI_COMPLETION_CODE_MASK                   (0xFF << 24)
#define XHCI_COMPLETION_GET_CODE(Port)              (((Port) & XHCI_COMPLETION_CODE_MASK) >> 24)
#define XHCI_COMPLETION_IVALID                              0
#define XHCI_COMPLETION_SUCCESS                             1 
#define XHCI_COMPLETION_DATA_BUFFER_ERROR                   2
#define XHCI_COMPLETION_BABBLE_DETECT_ERROR                 3
#define XHCI_COMPLETION_USB_TRANSACTION_ERROR               4
#define XHCI_COMPLETION_TRB_ERROR                           5
#define XHCI_COMPLETION_STALL_ERROR                         6
#define XHCI_COMPLETION_RESOURCE_ERROR                      7
#define XHCI_COMPLETION_BANDWIDTH_ERROR                     8
#define XHCI_COMPLETION_NO_SLOTS_AVAILABLE_ERROR            9
#define XHCI_COMPLETION_INVALID_STREAM_TYPE_ERROR           10
#define XHCI_COMPLETION_SLOT_NOT_ENABLED_ERROR              11
#define XHCI_COMPLETION_ENDPOINT_NOT_ENABLED_ERROR          12
#define XHCI_COMPLETION_SHORT_PACKET                        13
#define XHCI_COMPLETION_RING_UNDERUN                        14
#define XHCI_COMPLETION_RING_OVERRUN                        15
#define XHCI_COMPLETION_VF_EVENT_RING_FULL_ERROR            16
#define XHCI_COMPLETION_PARAMETER_ERROR                     17
#define XHCI_COMPLETION_BANDWIDTH_OVERRUN_ERROR             18
#define XHCI_COMPLETION_CONTEXT_STATE_ERROR                 19
#define XHCI_COMPLETION_NO_PING_RESPONCE_ERROR              20
#define XHCI_COMPLETION_EVENT_RING_FULL_ERROR               21
#define XHCI_COMPLETION_INCOMPATIBLE_DEVICE_ERROR           22
#define XHCI_COMPLETION_MISSED_SERVICE_ERROR                23
#define XHCI_COMPLETION_COMMAND_RING_STOPED                 24
#define XHCI_COMPLETION_COMMAND_ABORTED                     25
#define XHCI_COMPLETION_STOPPED                             26
#define XHCI_COMPLETION_STOPPED_LENGTH_INVALID              27
#define XHCI_COMPLETION_STOPPED_SHORT_PACKET                28
#define XHCI_COMPLETION_MAX_EXITT_LATENCY_TOO_LARGE_ERROR   29
#define XHCI_COMPLETION_ISOCJ_BUFFER_OVERRUN                31
#define XHCI_COMPLETION_EVENT_LOST_ERROR                    32
#define XHCI_COMPLETION_UNDEFINED_ERROR                     33
#define XHCI_COMPLETION_INVALID_STREAM_ID_ERROR             34
#define XHCI_COMPLETION_SECONDARY_BANDWIDTH_ERROR           35
#define XHCI_COMPLETION_SPLIT_TRANSACTION_ERROR             36



typedef struct _XHCI_CAPABILITIES_REGISTER{
    UINT32      HcCapBase;
    UINT32      HcsParameter1;
    UINT32      HcsParameter2;
    UINT32      HcsParameter3;
    UINT32      HccParameter;
    UINT32      DoorbellOffset;
    UINT32      RuntimeRegisterOffset;
    UINT32      HccParameter2;   
}XHCI_CAPABILITIES_REGISTER, * PXHCI_CAPABILITIES_REGISTER;

typedef struct _XHCI_OPERATIONAL_PORT{
    UINT32      StatusBase;
    UINT32      PowerPortBase;
    UINT32      PortLinkBase;
    UINT32      Reserved;
}XHCI_OPERATIONAL_PORT, * PXHCI_OPERATIONAL_PORT;

typedef struct _XHCI_OPERATIONAL_REGISTER{
    UINT32                  Command;
    UINT32                  Status;
    UINT32                  PageSize;
    UINT32                  Reserved1;
    UINT32                  Reserved2;
    UINT32                  DeviceNotification;
    UINT64                  CommandRing;
    UINT32                  Reserved3[4];
    UINT64                  DCBAAPointer;
    UINT32                  CongiurationRegister;
    UINT32                  Reserved4[241];
    XHCI_OPERATIONAL_PORT   Ports[255]; 
}XHCI_OPERATIONAL_REGISTER, * PXHCI_OPERATIONAL_REGISTER;

typedef struct _XHCI_INTERRUPT_REGISTER{
    UINT32          Man;
    UINT32          Mod;
    UINT32          ERstSize;
    UINT32          Reserved;
    UINT64          ErstBase;
    UINT64          ErstDeQueue;
}XHCI_INTERRUPT_REGISTER, * PXHCI_INTERRUPT_REGISTER;

typedef struct _XHCI_RUNTIME_REGISTERS{
    UINT32                      MicroFrameIndex;
    UINT32                      Reserved[7];
    XHCI_INTERRUPT_REGISTER     IrSet[128];
}XHCI_RUNTIME_REGISTERS, * PXHCI_RUNTIME_REGISTERS;

typedef struct _XHCI_DORRBELL_ARRAY{
    UINT32      Doorbell[256];
}XHCI_DORRBELL_ARRAY, * PXHCI_DORRBELL_ARRAY;

typedef struct _XHCI_CONTAINER_CONTEXT{
    UINT64      Type;
    UINT32      Size;
    UINT8*      Bytes;
    UINT64      DmaAddress;
}XHCI_CONTAINER_CONTEXT, * PXHCI_CONTAINER_CONTEXT;

typedef struct _XHCI_SLOT_CONTEXT{
    UINT32      DeviceInfo;
    UINT32      DeviceInfo2;
    UINT32      TtInfo;
    UINT32      DeviceState;
    UINT32      Reserved[4];
}XHCI_SLOT_CONTEXT, * PXHCI_SLOT_CONTEXT;

typedef struct _XHCI_EP_CONTEXT{
    UINT32      EpInfo;
    UINT32      EpInfo2;
    UINT32      Deq;
    UINT32      TxInfo;
    UINT32      Reserved[3];
}XHCI_EP_CONTEXT, * PXHCI_EP_CONTEXT;

typedef struct _XHCI_INPUT_CONTROL_CONTEXT{
    UINT32      DropFlags;
    UINT32      AddFlags;
    UINT32      Reserved2;
}XHCI_INPUT_CONTROL_CONTEXT, * PXHCI_INPUT_CONTROL_CONTEXT;

typedef struct _XHCI_COMMAND{
    PXHCI_CONTAINER_CONTEXT     InContext;
    UINT32                      Status;
    UINT32                      CompParam;
    INTEGER                     SlotID;
    bool                        CommandCompleted;
    union XHCI_TRB*             CommandTrb;
    ListHeader                  CommandList;
    UINT32                      MsTimeout;
}XHCI_COMMAND, * PXHCI_COMMAND;

typedef struct _XHCI_STREAM_CONTEXT{
    UINT64                      SteamRing;
    UINT32                      Reserved[2];
}XHCI_STREAM_CONTEXT, * PXHCI_STREAM_CONTEXT;

typedef struct _XHCI_STREAM_INFORMATION{
    struct _XHCI_RING**         StreamRings;
    UINT32                      StreamCount;
    PXHCI_STREAM_CONTEXT        StreamContext;
    UINT32                      StreamContexts;
    UINT64                      CtxArrayDmaAddress;
    RADIX_TREE_ROOT             TrbAddressMap;
    PXHCI_COMMAND               FreeStreamCommands;
}XHCI_STREAM_INFORMATION, * PXHCI_STREAM_INFORMATION;

typedef struct _XHCI_BW_INFORMATION{
    UINT32      EpInterval;
    UINT32      Mult;
    UINT32      PacketCount;
    UINT32      MaxPacketSize;
    UINT32      MaxEsitPayload;
    UINT32      Type;
}XHCI_BW_INFORMATION, * PXHCI_BW_INFORMATION;

typedef struct _XHCI_VIRTUAL_EP{
    struct _XHCI_VIRTUAL_DEVICE*        VirtualDevice;
    UINT32                              EpIndex;
    struct _XHCI_RING*                  Ring;
    PXHCI_STREAM_INFORMATION            StreamInformation;
    struct _XHCI_RING*                  NewRing;
    UINT32                              ErrorCount;
    UINT32                              EpState;
    ListHeader                          CancelledList;
    struct _XHCI_HCD*                   Xhci;
    struct _XHCI_SEGMENT*               QueuedDeqSegment;
    union XHCI_TRB*                     QueuedDeqPtr;
    BOOL                                Skip;
    XHCI_BW_INFORMATION                 BwInformation;
    ListHeader                          BandwithEpList;
    UINT64                              StopTime;
    INTEGER                             NextFrameID;
    BOOL                                UseExtTbc;
    PVOID                               SideBand;
}XHCI_VIRTUAL_EP, * PXHCI_VIRTUAL_EP;

typedef enum{
    LS_OVERHEAD_TYPE = 0,
    FS_OVERHEAD_TYPE = 1,
    HS_OVERHEAD_TYPE = 2,
}XHCI_OVERHEAD_TYPE;

typedef struct _XHCI_INTERVAL_BW{
    UINT32          PacketCount;
    ListHeader      Ep;
    UINT32          Overhead[3];
}XHCI_INTERVAL_BW, * PXHCI_INTERVAL_BW;

typedef struct _XHCI_INTERVAL_BW_TABLE{
    UINT32              EsitPayloadInterval;
    XHCI_INTERVAL_BW    BandwithIntervals[XHCI_MAX_INTERVAL];
    UINT32              BandwithUsed;
    UINT32              SsBwIn;
    UINT32              SsBwOut;
}XHCI_INTERVAL_BW_TABLE, * PXHCI_INTERVAL_BW_TABLE;

typedef struct _XHCI_VIRTUAL_DEVICE{
    INTEGER                         SlotId;
    PUSB_DEVICE                     UsbDevice;
    PXHCI_CONTAINER_CONTEXT         OutContext;
    PXHCI_CONTAINER_CONTEXT         InContext;
    PXHCI_VIRTUAL_EP                Eps[XHCI_EP_CONTEXT_PER_DEVICE];
    struct _XHCI_PORT*              RootHubPorts;
    PXHCI_INTERVAL_BW_TABLE         BandwithTable;
    struct _XHCI_TT_BW_INFORMATION* TtInformation;
    UINT64                          Flags;
    UINT16                          CurrentMel;
    PVOID                           SideBand;
}XHCI_VIRTUAL_DEVICE, * PXHCI_VIRTUAL_DEVICE;

typedef struct _XHCI_ROOT_PORT_BW_INFORMATION{
    ListHeader              Tts;
    UINT64                  ActiveTtsCount;
    XHCI_INTERVAL_BW_TABLE  BandwidthTable;
}XHCI_ROOT_PORT_BW_INFORMATION, * PXHCI_ROOT_PORT_BW_INFORMATION;

typedef struct _XHCI_TT_BW_INFORMATION{
    ListHeader              TtList;
    INTEGER                 SlotID;
    INTEGER                 TtPort;
    XHCI_INTERVAL_BW_TABLE  BandwidthTable;
    INTEGER                 ActiveEps;
}XHCI_TT_BW_INFORMATION, * PXHCI_TT_BW_INFORMATION;

typedef struct _XHCI_DEVICE_CONTEXT_ARRAY{
    UINT64                  DeviceContextPointers[XHCI_MAX_HC_SLOTS];
    UINT64                  DmaAddress;
}XHCI_DEVICE_CONTEXT_ARRAY, * PXHCI_DEVICE_CONTEXT_ARRAY;

typedef struct _XHCI_TRANSFER_EVENT{
    UINT64                  Buffer;
    UINT32                  TransferLength;
    UINT32                  Flags;
}XHCI_TRANSFER_EVENT, * PXHCI_TRANSFER_EVENT;

static inline string XhciTrbCompletionCodeString(UINT8  Status){
    switch(Status){
        case XHCI_COMPLETION_SUCCESS:{
            return "Success";
        }
        case XHCI_COMPLETION_DATA_BUFFER_ERROR:{
            return "Data Buffer Error";
        }
        case XHCI_COMPLETION_BABBLE_DETECT_ERROR:{
            return "Babble Detect Error";
        }
        case XHCI_COMPLETION_USB_TRANSACTION_ERROR:{
            return "USB Transaction Error";
        }
        case XHCI_COMPLETION_TRB_ERROR:{
            return "TRB Error";
        }
        case XHCI_COMPLETION_STALL_ERROR:{
            return "Stall Error";
        }
        case XHCI_COMPLETION_RESOURCE_ERROR:{
            return "Resoure Error";
        }
        case XHCI_COMPLETION_BANDWIDTH_ERROR:{
            return "Bandwidth Error";
        }
        case XHCI_COMPLETION_NO_SLOTS_AVAILABLE_ERROR:{
            return "No Slots Available Error";
        }
        case XHCI_COMPLETION_INVALID_STREAM_TYPE_ERROR:{
            return "Invalid Stream Type Error";
        }
        case XHCI_COMPLETION_SLOT_NOT_ENABLED_ERROR:{
            return "Slot Not Enabled Error";
        }
        case XHCI_COMPLETION_ENDPOINT_NOT_ENABLED_ERROR:{
            return "Endpoint Not Enabled Error";
        }
        case XHCI_COMPLETION_SHORT_PACKET:{
            return "Short Packet Error";
        }
        case XHCI_COMPLETION_RING_UNDERUN:{
            return "Ring Underrun Error";
        }
        case XHCI_COMPLETION_RING_OVERRUN:{
            return "Ring Overrun Error";
        }
        //905   
    }
    return "Invalid Or Unkown";
}

#endif