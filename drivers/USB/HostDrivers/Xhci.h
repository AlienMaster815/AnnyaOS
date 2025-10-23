/* SPDX-License-Identifier: GPL-2.0 */

/*
 * xHCI host controller driver
 *
 * Copyright (C) 2008 Intel Corp.
 *
 * Author: Sarah Sharp
 * Some code borrowed from the Linux EHCI driver.
 */

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
#define XHCI_COMPLETION_MAX_EXIT_LATENCY_TOO_LARGE_ERROR   29
#define XHCI_COMPLETION_ISOCH_BUFFER_OVERRUN                31
#define XHCI_COMPLETION_EVENT_LOST_ERROR                    32
#define XHCI_COMPLETION_UNDEFINED_ERROR                     33
#define XHCI_COMPLETION_INVALID_STREAM_ID_ERROR             34
#define XHCI_COMPLETION_SECONDARY_BANDWIDTH_ERROR           35
#define XHCI_COMPLETION_SPLIT_TRANSACTION_ERROR             36

#define XHCI_COMPLETION_PARAMETER(Port)     ((Port) & 0xFFFFFF)

#define XHCI_TRB_BSR        (1 << 9)
#define XHCI_TRB_DC         (1 << 9)
#define XHCI_TRB_TSP        (1 << 9)

#define XHCI_TRB_TO_VF_INTR_TARGET(Port)        (((Port) & (0x03FF << 22)) >> 22)
#define XHCI_TRB_TO_VF_ID(Port)                 (((Port) & (0xFF << 16)) >> 16)
#define XHCI_TRB_TO_BELT(Port)                  (((Port) & (0x0FFF << 16)) >> 16)
#define XHCI_TRB_TO_DEVICE_SPEED(Port)          (((Port) & (0x0F << 16)) >> 16)
#define XHCI_TRB_TO_PACKET_TYPE(Port)           ((Port) & 0x1F)
#define XHCI_TRB_TO_ROOTHUB_PORT(Port)          (((Port) & (0xFF << 24)) >> 24)

#define XHCI_DEV_SPEED_FOR_TRB(Port)            ((Port) << 16)

#define XHCI_SUSPEND_PORT_TO_TRB(Port)          (((Port) & 0x01) << 23)
#define XHCI_TRB_TO_SUSPEND_PORT(Port)          (((Port) & (1 << 23)) >> 23)

#define XHCI_LAST_EP_INDEX                      30

#define XHCI_TRB_TO_STREAM_ID(Port)             ((((Port) & (0xFFFF << 16)) >> 16))
#define XHCI_STREAM_ID_TO_TRB(Port)             ((((Port)) & 0xFFFF) << 16)
#define XHCI_ST_FOR_TRB(Port)                   (((Port) & 0x07) << 1)

#define XHCI_TRB_TC                             (1 << 1)
#define XHCI_GET_PORT_ID(Port)                  (((Port) & (0xFF << 24)) >> 24)
#define XHCI_EVENT_DATA                         (1 << 2)

#define XHCI_TRB_LENGTH(Port)                   ((Port) & 0x1FFFF)
#define XHCI_TRB_TD_SIZE(Port)                  (min((Port), (UINT32)31) << 17)
#define XHCI_GET_TD_SIZE(Port)                  (((Port) & 0x3E0000) >> 17)
#define XHCI_TRB_TD_SIZE_TBC(Port)              (min((Port), (UINT32)31) << 17)
#define XHCI_TRB_INTR_TARGET(Port)              (((Port) & 0x03FF) << 22)
#define XHCI_GET_INTR_TARGET(Port)              (((Port) >> 22) & 0x03FF)

#define XHCI_TRB_CYCLE          (1 << 0)
#define XHCI_TRB_ENT            (1 << 1)
#define XHCI_TRB_ISP            (1 << 2)
#define XHCI_TRB_NO_SNOOP       (1 << 3)
#define XHCI_TRB_CHAIN          (1 << 4)
#define XHCI_TRB_IOC            (1 << 5)
#define XHCI_TRB_IDT            (1 << 6)
#define XHCI_TRB_IDT_MAX_SIZE   8
#define XHCI_TRB_BEI            (1 << 9)
#define XHCI_TRB_DIR_IN         (1 << 16)
#define XHCI_TRB_TX_TYPE(Port)  ((Port) << 16)
#define XHCI_TRB_DATA_OUT       2
#define XHCI_TRB_DATA_IN        3

#define XHCI_TRB_SIA            (1 << 31)
#define XHCI_TRB_FRAME_ID(Port) (((Port) & 0x07FF) << 20)
#define XHCI_GET_FRAME_ID(Port) (((Port) >> 20) & 0x07FF)

#define XHCI_TRB_TBC(Port)      (((Port) & 0x03) << 7)
#define XHCI_GET_TBC(Port)      (((Port) >> 7) & 0x03)
#define XHCI_TRB_TLBPC(Port)    (((Port) & 0x0F) << 16)
#define XHCI_GET_TLBPC(Port)    (((Port) >> 16) & 0x0F)

#define XHCI_TRB_CACHE_SIZE_HS      8
#define XHCI_TRB_CACHE_SIZE_SS      16

#define XHCI_TRB_TYPE_MASK          (0xFC00)
#define XHCI_TRB_TYPE(Port)         ((Port) << 10)
#define XHCI_TRB_FIELD_TO_TYPE      (((Port) & XHCI_TRB_TYPE_MASK) >> 10)

#define XHCI_TRB_NORMAL                     1
#define XHCI_TRB_SETUP                      2
#define XHCI_TRB_DATA                       3
#define XHCI_TRB_STATUS                     4
#define XHCI_TRB_ISOC                       5
#define XHCI_TRB_LINK                       6
#define XHCI_TRB_EVENT_DATA                 7
#define XHCI_TRB_TR_NOOP                    8
#define XHCI_TRB_ENABLE_SLOT                9
#define XHCI_TRB_DISABLE_SLOT               10
#define XHCI_TRB_ADDR_DEV                   11
#define XHCI_TRB_CONFIG_EP                  12
#define XHCI_TRB_EVAL_CONTEXT               13
#define XHCI_TRB_RESET_EP                   14
#define XHCI_TRB_STOP_RING                  15
#define XHCI_TRB_SET_DEQ                    16
#define XHCI_TRB_RESET_DEV                  17
#define XHCI_TRB_FORCE_EVENT                18
#define XHCI_TRB_NEG_BANDWIDTH              19
#define XHCI_TRB_SET_LT                     20
#define XHCI_TRB_GET_BW                     21
#define XHCI_TRB_FORCE_HEADER               22
#define XHCI_TRB_COMMAND_NOOP               23
#define XHCI_TRB_TRANSFER                   32
#define XHCI_TRB_COMPLETION                 33
#define XHCI_TRB_PORT_STATUS                34
#define XHCI_TRB_BANDWIDTH_EVENT            35
#define XHCI_TRB_DOORBELL                   36
#define XHCI_TRB_HC_EVENT                   37
#define XHCI_TRB_DEV_NOTE                   38
#define XHCI_TRB_MF_INDEX_WRAP              39
#define XHCI_TRB_VENDOR_DEFINED_LOW         48
#define XHCI_TRB_NEC_COMMAND_COMPLETION     48
#define XHCI_TRB_NEC_GET_FW_REVISION        49

#define XHCI_TRB_TYPE_LINK(Port)            (((Port) & XHCI_TRB_TYPE_MASK) == XHCI_TRB_TYPE(XHCI_TRB_LINK))

#define XHCI_NEC_FW_MINOR(Port)             ((Port) & 0xFF)
#define XHCI_NEC_FW_MAJOR(Port)             (((Port) >> 8) & 0xFF)

#define XHCI_TRBS_PER_SEGMENT               256
#define XHCI_MAX_RESERVED_COMMAND_TRBS      (XHCI_TRBS_PER_SEGMENT - 3)
#define XHCI_TRB_SEGMENT_SIZE               (XHCI_TRBS_PER_SEGMENT * 16)
#define XHCI_TRB_SEGMENT_SHIFT              (ILog2(XHCI_TRB_SEGMENT_SIZE))
#define XHCI_TRB_MAX_BUFFER_SHIFT           16
#define XHCI_TRB_MAX_BUFFER_SIZE            (1 << XHCI_TRB_MAX_BUFFER_SHIFT)
#define XHCI_TRB_BUFFER_LENGTH_TO_BOUNDRY(Address)   (XHCI_TRB_MAX_BUFFER_SIZE - (Address & (XHCI_TRB_MAX_BUFFER_SIZE -1)))
#define XHCI_MAX_SOFT_RETRY                 3

#define XHCI_AVOID_BEI_INTERVAL_MIN         8
#define XHCI_AVOID_BEI_INTERVAL_MAX         32

#define XhciForEachRingSegment(Head, Segment) for(Segment = Head; Segment != 0x00; Segment = (Segment->NextSegment != Head ? Segment->NextSegment : 0x00))

#define XHCI_COMMAND_DEFAULT_TIMEOUT        5000

#define XHCI_ERST_DEFAULT_SEGMENTS          2
#define XHCI_POLL_TIMEOUT                   60

#define XHCI_STOP_EP_COMMAND_TIMEOUT        5

#define XHCI_MAX_REXIT_TIMEOUT              20

#define COMMAND_RING_STATE_RUNNING          (1)
#define COMMAND_RING_STATE_ABORTED          (1 << 1)
#define COMMAND_RING_STATE_STOPPED          (1 << 2)

#define XHCI_STATE_DYING                    (1 << 0)
#define XHCI_STATE_HALTED                   (1 << 1)
#define XHCI_STATE_REMOVING                 (1 << 2)

#define XHCI_QUIRK_LINK_TRB                         (1 << 0)
#define XHCI_QUIRK_RESET_EP                         (1 << 1)
#define XHCI_QUIRK_NEC_HOST                         (1 << 2)
#define XHCI_QUIRK_AMD_PLL_FIX                      (1 << 3)
#define XHCI_QUIRK_SPURRIOUS_SUCCESS                (1 << 4)
#define XHCI_QUIRK_EP_LIMIT                         (1 << 5)
#define XHCI_QUIRK_BROKEN_MSI                       (1 << 6)
#define XHCI_QUIRK_RESET_ON_RESUME                  (1 << 7)
#define XHCI_QUIRK_SW_BW_CHECKING                   (1 << 8)
#define XHCI_QUIRK_AMD_0x96_HOST                    (1 << 9)
#define XHCI_QUIRK_TRUST_TX_LENGTH                  (1 << 10)
#define XHCI_QUIRK_LPM_SUPPORT                      (1 << 11)
#define XHCI_QUIRK_INTEL_HOST                       (1 << 12)
#define XHCI_QUIRK_SPURRIOUS_REBOOT                 (1 << 13)
#define XHCI_QUIRK_COMP_MODE_QUIRK                  (1 << 14)
#define XHCI_QUIRK_AVOID_BEI                        (1 << 15)
#define XHCI_QUIRK_PLAT                             (1 << 16)
#define XHCI_QUIRK_SLOW_SUSPEND                     (1 << 17)
#define XHCI_QUIRK_SPURRIOUS_WAKEUP                 (1 << 18)
#define XHCI_QUIRK_BROKEN_STREAMS                   (1 << 19)
#define XHCI_QUIRK_PME_STUCK                        (1 << 20)
#define XHCI_QUIRK_MTK_HOST                         (1 << 21)
#define XHCI_QUIRK_SSIC_PORT_UNUSED                 (1 << 22)
#define XHCI_QUIRK_NO_64BIT_SUPPORT                 (1 << 23)
#define XHCI_QUIRK_MISSING_CAS                      (1 << 24)
#define XHCI_QUIRK_BROKEN_PORT_PED                  (1 << 25)
#define XHCI_QUIRK_LIMIT_ENDPOINT_INTERVAL_7        (1 << 26)
#define XHCI_QUIRK_U2_DISABLE_WAKE                  (1 << 27)
#define XHCI_QUIRK_ASMEDIA_MODIFY_FLOW_CONTROL      (1 << 28)
#define XHCI_QUIRK_HW_LPM_DISABLED                  (1 << 29)
#define XHCI_QUIRK_SUSPEND_DELAY                    (1 << 30)
#define XHCI_QUIRK_INTEL_USB_ROLE_SW                (1 << 31)
#define XHCI_QUIRK_ZERO_64_BIT_REGISTERS            (1 << 32)
#define XHCI_QUIRK_DEFAULT_PM_RUNTIME_ALLOW         (1 << 33)
#define XHCI_QUIRK_RESET_PLL_ON_DISCONNECT          (1 << 34)
#define XHCI_QUIRK_SNPS_BROKEN_SUSPEND              (1 << 35)
#define XHCI_QUIRK_SKIP_PHY_INIT                    (1 << 37)
#define XHCI_QUIRK_DISABLE_SPARCE                   (1 << 38)
#define XHCI_QUIRK_SG_TRB_CACHE_SIZE_QUIRK          (1 << 39)
#define XHCI_QUIRK_NO_SOFT_RETRY                    (1 << 40)
#define XHCI_QUIRK_BROKEN_D3_COLD_S2I               (1 << 41)
#define XHCI_QUIRK_EP_CONTEXT_BROKER_DCS            (1 << 42)
#define XHCI_QUIRK_SUSPEND_RESUME_CLOCKS            (1 << 43)
#define XHCI_QUIRK_RESET_TO_DEFAULT                 (1 << 44)
#define XHCI_QUIRK_TRB_OVERFETCH                    (1 << 45)
#define XHCI_QUIRK_ZHAOXIN_HOST                     (1 << 46)
#define XHCI_QUIRK_WRITE_64_HI_LO                   (1 << 47)
#define XHCI_QUIRK_CDNS_SCTX                        (1 << 48)
#define XHCI_QUIRK_ETRON_HOST                       (1 << 49)
#define XHCI_QUIRK_LIMIT_ENDPOINT_INTERVAL_9        (1 << 50)

#define XHCI_COMPLETION_MODE_RECOVERY_MSEC  2000

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
    UINT32          Iman;
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
}XHCI_DORRBELL_ARRAY, * PXHCI_DOORBELL_ARRAY;

typedef struct _XHCI_CONTAINER_CONTEXT{
    UINT64      Type;
    UINT32      Size;
    UINT8*      Bytes;
    UINT64      DmaVAddress;
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
    union _XHCI_TRB*            CommandTrb;
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
    union _XHCI_TRB*                    QueuedDeqPtr;
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

typedef struct _XHCI_LINK_TRB{
    UINT64      SegmentPointer;
    UINT32      InterTarget;
    UINT32      Control;
}XHCI_LINK_TRB, * PXHCI_LINK_TRB;

#define XHCI_LINK_TOGGLE    (1 << 1)

typedef struct _XHCI_EVENT_COMMAND{
    UINT64      CommandTRB;
    UINT32      Status;
    UINT32      Flags;
}XHCI_EVENT_COMMAND, * PXHCI_EVENT_COMMAND;

typedef enum{
    EP_HARD_RESET = 0,
    EP_SOFT_RESET = 1,
}XHCI_EP_RESET_TYPE;

typedef enum{
    SETUP_CONTEXT_ONLY = 0,
    SETUP_CONTEXT_ADDRESS = 1,
}XHCI_SETUP_DEVICE;

typedef struct _XHCI_GENERIC_TRB{
    UINT32  Field[4];
}XHCI_GENERIC_TRB, * PXHCI_GENERIC_TRB;

typedef union _XHCI_TRB{
    XHCI_LINK_TRB           Link;
    XHCI_TRANSFER_EVENT     TransferEvent;
    XHCI_EVENT_COMMAND      EventCommand;
    XHCI_GENERIC_TRB        Generic;
}XHCI_TRB, * PXHCI_TRB;

typedef struct _XHCI_SEGMENT{
    PXHCI_TRB               Trbs;
    struct _XHCI_SEGMENT*   NextSegment;
    UINT32                  Number;
    UINT64                  DmaAddress;
    UINT64                  BounceDma;
    PVOID                   BounceBuffer;
    UINT32                  BounceOffset;
    UINT32                  BounceLength;
}XHCI_SEGMENT, * PXHCI_SEGMENT;

typedef enum{
    TD_DIRTY = 0,
    TD_HALTED = 1,
    TD_CLEARING_CACHE = 2,
    TD_CLEARING_CACHE_DEFERED = 3,
    TD_CLEARED = 4,
}XHCI_CANCELLED_TD_STATUS;

typedef struct _XHCI_TD{
    ListHeader                  TdList;
    ListHeader                  CanceledTdList;
    INTEGER                     Status;
    XHCI_CANCELLED_TD_STATUS    CancelStatus;
    PURB                        Urb;
    PXHCI_SEGMENT               StartSegment;
    PXHCI_TRB                   StartTrb;
    PXHCI_SEGMENT               EndSegment;
    PXHCI_TRB                   EndTrb;
    PXHCI_SEGMENT               BounceSegment;
    BOOL                        UrbLengthSet;
    BOOL                        ErrorMidTd;
}XHCI_TD, * PXHCI_TD;

typedef struct _XHCI_CD{
    PXHCI_COMMAND   Command;
    PXHCI_TRB       CommandTrb; 
}XHCI_CD, * PXHCI_CD;

typedef enum{
    TYPE_CONTROL = 0,
    TYPE_ISOC = 1,
    TYPE_BULK = 2,
    TYPE_INTR = 3,
    TYPE_STREAM = 4,
    TYPE_COMMAND = 5,
    TYPE_EVENT = 6,
}XHCI_RING_TYPE;

typedef struct _XHCI_RING{
    PXHCI_SEGMENT       FirstSegment;
    PXHCI_SEGMENT       LastSegment;
    PXHCI_TRB           EnQueue;
    PXHCI_SEGMENT       EnqSegment;
    PXHCI_TRB           DeQueue;
    PXHCI_SEGMENT       DeqSegment;
    ListHeader          TdList;
    UINT32              CycleState;
    UINT32              StreamID;
    UINT32              SegmentCount;
    UINT32              FreeTrbs;
    UINT32              BounceBufferLength;
    XHCI_RING_TYPE      Type;
    UINT32              OldTrbCompletionCode;
    PRADIX_TREE_ROOT    TrbAddressMap;    
}XHCI_RING, * PXHCI_RING;

typedef struct _XHCI_ERST_ENTRY{
    UINT64      SegmentAddress;
    UINT32      SegmentSize;
    UINT32      Reserved;
}XHCI_ERST_ENTRY, * PXHCI_ERST_ENTRY;

typedef struct _XHCI_ERST{
    PXHCI_ERST_ENTRY    Entries;
    UINT32              EntryCount;
    UINT64              ErstDmaAddress;
}XHCI_ERST, * PXHCI_ERST;

typedef struct _XHCI_SCRATCHPAD{
    UINT64*     SpArray;
    UINT64      SpDmaAddress;
    PVOID*      SpBuffers;
}XHCI_SCRATCHPAD, * PXHCI_SCRATCHPAD;

typedef struct _XHCI_URB_PRIVATE{
    INTEGER     TdsCount;
    INTEGER     TdsDoneCount;
    XHCI_TD     Tds[];
}XHCI_URB_PRIVATE, * PXHCI_URB_PRIVATE;

typedef struct _XHCI_S3_SAVE{
    UINT32      Command;
    UINT32      DevNt;
    UINT64      DcbaaPointer;
    UINT32      ConfigRegister;
}XHCI_S3_SAVE, * PXHCI_S3_SAVE;

typedef struct _XHCI_DEVICE_INFO{
    UINT32      DeviceID;
    ListHeader  NextDevice;
}XHCI_DEVICE_INFO, * PXHCI_DEVICE_INFO;

typedef struct _XHCI_BUS_STATE{
    UINT64      BusSuspend;
    UINT64      NextStateChange;
    UINT32      PortCSuspend;
    UINT32      PortRemoteWakeup;
    UINT64      ResumingPorts;
}XHCI_BUS_STATE, * PXHCI_BUS_STATE;

typedef struct _XHCI_INTERRUPTER{
    PXHCI_RING                  EventRing;
    XHCI_ERST                   Erst;
    PXHCI_INTERRUPT_REGISTER    IrSet;
    UINT32                      IntrNumber;
    BOOL                        IpAutoClear;
    UINT32                      IsocBeiInterval;
    UINT32                      S3IMan;
    UINT32                      S3IMod;
    UINT32                      S3ErstSize;
    UINT64                      S3ErstBase;
    UINT64                      S3ErstDeQueue;
}XHCI_INTERRUPTER, * PXHCI_INTERRUPTER;

typedef struct _XHCI_PORT_CAPABILITES{
    UINT32*         Psi;
    UINT8           PsiCount;
    UINT8           PciUidCount;
    UINT8           MajorRevision;
    UINT8           MinorRevision;
    UINT32          ProtocolCapabilities;
}XHCI_PORT_CAPABILITES, * PXHCI_PORT_CAPABILITES;

typedef struct _XHCI_PORT{
    UINT32*                     Address;
    INTEGER                     HwPortNumber;
    INTEGER                     HcdPortNumber;
    struct _XHCI_HUB*           RootHub;
    PXHCI_PORT_CAPABILITES      PortCapabilities;
    BOOL                        LpmIncapable;
    UINT64                      ResumeTimestamp;
    BOOL                        RExitActive;
    INTEGER                     SlotID;
    BOOL                        RExitDone;
    BOOL                        U3ExitDone;
}XHCI_PORT, * PXHCI_PORT;

typedef struct _XHCI_HUB{
    PXHCI_PORT*                 Ports;
    UINT32                      PortCount;
    PUSB_HOST_CONTROLLER_DEVICE  HostControllerDevice;
    XHCI_BUS_STATE              BusState;
    UINT8                       MajorRevision;
    UINT8                       MinorRevision;
}XHCI_HUB, * PXHCI_HUB;

//1502

typedef struct _XHCI_HCD{
    PPCI_DEVICE_OBJECT              PDEV;
    PUSB_HOST_CONTROLLER_DEVICE     MainHcd;
    PUSB_HOST_CONTROLLER_DEVICE     SharedHcd;
    PXHCI_CAPABILITIES_REGISTER     CapabilitiesRegister;
    PXHCI_OPERATIONAL_REGISTER      OperationalRegister;
    PXHCI_RUNTIME_REGISTERS         RuntimeRegister;
    PXHCI_DOORBELL_ARRAY            Dba;
    UINT32                          HcsParameter1;
    UINT32                          HcsParameter2;
    UINT32                          HcsParameter3;
    UINT32                          HccParameter1;
    UINT32                          HccParameter2;
    spinlock_t                      DeviceHardLock;
    UINT16                          HciVersion;
    UINT16                          MaxInterrupts;
    UINT32                          IModInterval;
    UINT32                          PageSize;
    INTEGER                         nVectors;
    PXHCI_DEVICE_CONTEXT_ARRAY      ContextArray;
    PXHCI_INTERRUPTER*              Interrupters;
    PXHCI_RING                      CommandRing;
    UINT32                          CommandRingState;
    ListHeader                      CommandList;
    UINT32                          CommandRingReservedTrbs;
    PXHCI_COMMAND                   CurrentCommand;
    PXHCI_SCRATCHPAD                Scratchpad;
    mutex_t                         DeviceSoftLock;
    mutex_t                         RegisterPollLock;
    PXHCI_VIRTUAL_DEVICE            Devices[XHCI_MAX_HC_SLOTS];
    POOL                            DevicePool;
    POOL                            SegmentPool;
    POOL                            SmallStreamsPool;
    POOL                            PortBwPool;
    POOL                            MediumStreamsPool;
    UINT32                          XhcState;
    UINT64                          RunGracePeriod;
    XHCI_S3_SAVE                    S3;
    UINT64                          Quirks;
    UINT32                          ActiveEpCount;
    UINT32                          LimitActiveEpCount;
    PXHCI_PORT                      HwPorts;
    PXHCI_HUB                       Usb2RootHub;
    PXHCI_HUB                       Usb3RootHub;
    UINT8                           HwLpmSupport    : 1;
    UINT8                           BrokenSuspend   : 1;
    UINT8                           AllowSingleRoot : 1;
    PXHCI_PORT_CAPABILITES          PortCaps;
    UINT32                          PortCount;
    //TODO: add completion mode recovery timer
    UINT32                          PortStatusU0;
    UINT16                          TestMode;
    ListHeader                      RegisterSetList;
    UINT64                          PrivateData[] FORCE_ALIGNMENT(sizeof(UINT64));
}XHCI_HCD, * PXHCI_HCD;

static inline string XhciTrbCompletionCodeString(UINT8 Status){
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
        case XHCI_COMPLETION_VF_EVENT_RING_FULL_ERROR:{
            return "VF Event Ring Full Error";
        }   
        case XHCI_COMPLETION_PARAMETER_ERROR:{
            return "Parameter Error";
        }
        case XHCI_COMPLETION_BANDWIDTH_OVERRUN_ERROR:{
            return "Bandwidth Overrun Error";
        }
        case XHCI_COMPLETION_CONTEXT_STATE_ERROR:{
            return "Context State Error";
        }
        case XHCI_COMPLETION_NO_PING_RESPONCE_ERROR:{
            return "No Ping Responce Error";
        }
        case XHCI_COMPLETION_EVENT_RING_FULL_ERROR:{
            return "Event Ring Full Error";
        }
        case XHCI_COMPLETION_INCOMPATIBLE_DEVICE_ERROR:{
            return "Incompatible Device Error";
        }
        case XHCI_COMPLETION_MISSED_SERVICE_ERROR:{
            return "Missed Service Error";
        }
        case XHCI_COMPLETION_COMMAND_RING_STOPED:{
            return "Command Ring Stoped Error";
        }
        case XHCI_COMPLETION_COMMAND_ABORTED:{
            return "Command Aborted Error";
        }
        case XHCI_COMPLETION_STOPPED:{
            return "Stopped Error";
        }
        case XHCI_COMPLETION_STOPPED_LENGTH_INVALID:{
            return "Stopped Error Invalid Length";
        }
        case XHCI_COMPLETION_STOPPED_SHORT_PACKET:{
            return "Stopped Error Short Packet";
        }
        case XHCI_COMPLETION_MAX_EXIT_LATENCY_TOO_LARGE_ERROR:{
            return "Max Exit Latency Too Large";
        }
        case XHCI_COMPLETION_ISOCH_BUFFER_OVERRUN:{
            return "Isoch Buffer Overrun";
        }
        case XHCI_COMPLETION_EVENT_LOST_ERROR:{
            return "Max Exit Latency Too Large Error";
        }
        case XHCI_COMPLETION_UNDEFINED_ERROR:{
            return "Undefined Error";
        }
        case XHCI_COMPLETION_INVALID_STREAM_ID_ERROR:{
            return "Invalid Stream ID Error";
        }
        case XHCI_COMPLETION_SECONDARY_BANDWIDTH_ERROR:{
            return "Secondary Bandwidth Error";
        }
        case XHCI_COMPLETION_SPLIT_TRANSACTION_ERROR:{
            return "Split Transaction Error";
        }
    }
    return "Invalid Or Unkown";
}

static inline string XhciTrbTypeString(UINT8 Type){
    switch(Type){
        case XHCI_TRB_NORMAL:{
            return "Normal";
        }
        case XHCI_TRB_SETUP:{
            return "Setup Stage";
        }
        case XHCI_TRB_DATA:{
            return "Data Stage";
        }
        case XHCI_TRB_STATUS:{
            return "Status Stage";
        }
        case XHCI_TRB_ISOC:{
            return "Isoch";
        }
        case XHCI_TRB_LINK:{
            return "Link";
        }
        case XHCI_TRB_EVENT_DATA:{
            return "Event Data";
        }
        case XHCI_TRB_TR_NOOP:{
            return "No-Op";
        } 
        case XHCI_TRB_ENABLE_SLOT:{
            return "Enable Slot Command";
        }
        case XHCI_TRB_DISABLE_SLOT:{
            return "Disable Slot Command";
        }
        case XHCI_TRB_ADDR_DEV:{
            return "Address Device Command";
        }
        case XHCI_TRB_CONFIG_EP:{
            return "Configure Endpoint Command";
        }
        case XHCI_TRB_EVAL_CONTEXT:{
            return "Evaluate Context Command";
        }
        case XHCI_TRB_RESET_EP:{
            return "Endpoint Reset Command";
        }
        case XHCI_TRB_FORCE_EVENT:{
            return "Force Event Command";
        }
        case XHCI_TRB_NEG_BANDWIDTH:{
            return "Negotiate Bandwidth Command";
        }
        case XHCI_TRB_SET_LT:{
            return "Set Latency Tolerance Value Command";
        }
        case XHCI_TRB_GET_BW:{
            return "Get Port Bandwidth Command";
        }
        case XHCI_TRB_FORCE_HEADER:{
            return "Force Header Command";
        }
        case XHCI_TRB_COMMAND_NOOP:{
            return "No-Op Command";
        }
        case XHCI_TRB_TRANSFER:{
            return "Transfer Event";
        }
        case XHCI_TRB_COMPLETION:{
            return "Command Completion Event";
        }
        case XHCI_TRB_PORT_STATUS:{
            return "Port Status Change Event";
        }
        case XHCI_TRB_DOORBELL:{
            return "Doorbell Event";
        }
        case XHCI_TRB_HC_EVENT:{
            return "Host Controller Event";
        }
        case XHCI_TRB_DEV_NOTE:{
            return "Device Notification Event";
        }
        case XHCI_TRB_MF_INDEX_WRAP:{
            return "MFINDEX Wrap Event";
        }
        case XHCI_TRB_NEC_COMMAND_COMPLETION:{
            return "NEX Command Completion Event";
        }
        case XHCI_TRB_NEC_GET_FW_REVISION:{
            return "NEC Get Firmware Revision Command";
        }
    }
    return "Unkown Event";
}

static inline string XhciRingTypeString(XHCI_RING_TYPE Type){

    switch(Type){
        case TYPE_CONTROL:{
            return "CONTROL";
        }
        case TYPE_ISOC:{
            return "ISOC";
        }
        case TYPE_BULK:{
            return "BULK";
        }
        case TYPE_INTR:{
            return "INTR";
        }
        case TYPE_STREAM:{
            return "STREAM";
        }
        case TYPE_COMMAND:{
            return "COMMAND";
        }
        case TYPE_EVENT:{
            return "EVENT";
        }
    }
    return "UNKOWN";
}

static inline PXHCI_HCD HcdToXhci(PUSB_HOST_CONTROLLER_DEVICE Hcd){
    PUSB_HOST_CONTROLLER_DEVICE PrimaryDevice;
    if(Hcd->PrimaryHcd){
        PrimaryDevice = Hcd->PrimaryHcd;
    }else{
        PrimaryDevice = Hcd;
    }
    return (PXHCI_HCD)PrimaryDevice->PrivateData;
}

static inline PUSB_HOST_CONTROLLER_DEVICE XhciToHcd(PXHCI_HCD Xhci){
    return Xhci->MainHcd;
}

static inline UINT64 XhciRead64(PXHCI_HCD Xhci, PVOID Register) {
    UINT64 Result = READ_REGISTER_ULONG((PULONG)Register);
    Result |= ((UINT64)READ_REGISTER_ULONG(((PULONG)Register) + 1)) << 32;
    return Result;
}

static inline void XhciWrite64(PXHCI_HCD Xhci, PVOID Register, UINT64 Value) {
    UINT32 Low  = (UINT32)(Value & UINT32_MAX);
    UINT32 High = (UINT32)(Value >> 32);
    WRITE_REGISTER_ULONG(((PULONG)Register), Low);
    WRITE_REGISTER_ULONG(((PULONG)Register) + 1, High);
}


void XhciRingCommandDoorbell(
    PXHCI_HCD Xhci
);

PXHCI_COMMAND 
XhciAllocateCommand(
    PXHCI_HCD   Xhci,
    bool        AllocateCompletion,
    UINT64      MemoryFlags
);

void
XhciFreeCommand(
    PXHCI_HCD Xhci,
    PXHCI_COMMAND Command
);

LOUSTATUS 
XhciQueueVendorCommand(
    PXHCI_HCD Xhci,
    PXHCI_COMMAND Command,
    UINT32 Feild1,
    UINT32 Feild2,
    UINT32 Feild3,
    UINT32 Feild4
);

LOUSTATUS 
XhciRingExspansion(
    PXHCI_HCD Xhci,
    PXHCI_RING Ring,
    UINT32 NewSegments,
    UINT64 MemoryFlags
);

bool 
XhciLinkChainQuirk(
    PXHCI_HCD Xhci,
    XHCI_RING_TYPE Type
);

#endif