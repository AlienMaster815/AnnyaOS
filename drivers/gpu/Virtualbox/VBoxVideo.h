#ifndef _VBOX_VIDEO_H
#define _VBOX_VIDEO_H

/*
 * This is a clean-room reimplementation of the VirtualBox VBE/VMSVGA driver,
 * originally developed by Oracle Corporation and released under the MIT license.
 *
 * This implementation is based on independent research and observation of the
 * Linux kernel's `vboxvideo` driver and related specifications. No code was
 * directly copied or translated.
 *
 * All identifiers, register names, and behavior are derived from public
 * documentation or reverse-engineered from hardware behavior.
 *
 * Copyright (C) 2025 Tyler Grenier
 * Licensed under the GNU GPLv2
 */

#define VIRTUALBOX_VIDEO_MAX_SCREENS                                64
#define VBVA_RING_BUFFER_SIZE                                       (4194304 - 1024)
#define VBVA_RING_BUFFER_THRESHOLD                                  (4096)
#define VBVA_MAXIMUM_RECORDS                                        (64)
#define VBVA_F_MODE_ENABLED                                         0x00000001u
#define VBVA_F_MODE_VRDP                                            0x00000002u
#define VBVA_F_MODE_VRDP_RESET                                      0x00000004u
#define VBVA_F_MODE_VRDP_ORDER_BITS                                 0x00000008u
#define VBVA_F_STATE_PROCESSING                                     0x00010000u
#define VBVA_F_RECORD_PARTIAL                                       0x80000000u
#define VBVA_ADAPTER_INFORMATION_SIZE                               (65536)
#define VBVA_MINIMUM_BUFFER_SIZE                                    (65536)
#define VIRTUALBOX_VIDEO_DISABLE_ADAPTER_MEMORY                     0xFFFFFFFF
#define VIRTUALBOX_VIDEO_INTERPRIT_ADAPTER_MEMORY                   0x00000000
#define VIRTUALBOX_VIDEOP_INTERPRIT_DISPLAY_MEMORY_BASE             0x00010000
#define VBVA_MAXIMUM_RECORD_SIZE                                    (128 * MEGABYTE) //128 MB
//Guest To Host Command
#define VBVA_QUERY_CONFIGURATION32_COMMAND                          1
#define VBVA_SET_CONFIGURATION32_COMMAND                            2
#define VBVA_INFORMATION_VIEW_COMMAND                               3
#define VBVA_INFORMATION_HEAP_COMAND                                4
#define VBVA_FLUSH_COMMAND                                          5
#define VBVA_INFORMATION_SCREEN_COMMAND                             6
#define VBVA_ENABLE_COMMAND                                         7
#define VBVA_MOUSE_POINTER_SHAPE_COMMAND                            8
#define VBVA_INFORMATION_CAPS                                       12
#define VBVA_SCANLINE_CONFIGURATION_COMMAND                         13
#define VBVA_SCANLINE_INFORMATION_COMMAND                           14
#define VBVA_COMMAND_VBVA_SUBMISSION_COMMAND                        16
#define VBVA_COMMAND_VBVA_FLUSH_COMMAND                             17
#define VBVA_COMMAND_VBVA_CONTROL_COMMAND                           18
#define VBVA_QUERY_MODE_HINTS_COMMAND                               19
#define VBVA_REPORT_INPUT_MAPPING_COMMAND                           20
#define VBVA_CURSOR_POSITION_COMMAND                                21
//Host to guest command
#define VBVA_HOSTGUEST_EVENT                                        1
#define VBVA_HODTGUEST_DISPLAY_CUSTOM                               2
//configuration32 Indexing
#define VIRTUALBOX_VBVA_CONFIGURATION32_MONITOR_CCOUNT              0
#define VIRTUALBOX_VBVA_CONFIGURATION32_HOST_HEAP_SIZE              1
#define VIRTUALBOX_VBVA_CONFIGURATION32_MODE_HINT_REPORTING         2
#define VIRTUALBOX_VBVA_CONFIGURATION32_GUEST_CURSOR_REPORTING      3
#define VIRTUALBOX_VBVA_CONFIGURATION32_CURSOR_CAPABILITIES         4
#define VIRTUALBOX_VBVA_CONFIGURATION32_SCREEN_FLAGS                5
#define VIRTUALBOX_VBVA_CONFIGURATION32_MAXIMUM_RECORD_SIZE         6
#define VIRTUALBOX_VBVA_CURSOR_CAPABILITY_RESERVED0                 1
#define VIRTUALBOX_VBVA_CURSOR_CAPABILITY_HARDWARE                  1 << 1
#define VIRTUALBOX_VBVA_CURSOR_CAPABILITY_RESERVED2                 1 << 2
#define VIRTUALBOX_VBVA_CURSOR_CAPABILITY_RESERVED3                 1 << 3
#define VIRTUALBOX_VBVA_CURSOR_CAPABILITY_RESERVED4                 1 << 4
#define VIRTUALBOX_VBVA_CURSOR_CAPABILITY_RESERVED5                 1 << 5
#define VBVA_SCREEN_F_NONE                                          0x0000
#define VBVA_SCREEN_F_ACTIVE                                        0x0001
#define VBVA_SCREEN_F_DISABLED                                      0x0002
#define VBVA_SCREEN_F_BLANK                                         0x0004
#define VBVA_SCREEN_F_BLANK2                                        0x0005
#define VBVA_F_NONE                                                 0x00000000
#define VBVA_F_ENABLE                                               0x00000001
#define VBVA_F_DISABLE                                              0x00000002
#define VBVA_F_EXTENDED                                             0x00000004
#define VBVA_F_ABSOFFSET                                            0x00000008
#define VBOX_MOUSE_POINTER_VISABLE                                  0x0001
#define VBOX_MOUSE_POINTER_ALPHA                                    0x0002
#define VBOX_MOUSE_POINTER_SHAPE                                    0x0004
#define VBVACAPS_COMPLETEGCMD_BY_IOREAD		                        0x00000001
#define VBVACAPS_IRQ				                                0x00000002
#define VBVACAPS_VIDEO_MODE_HINTS		                            0x00000004
#define VBVACAPS_DISABLE_CURSOR_INTEGRATION	                        0x00000008
#define VBVACAPS_USE_VBVA_ONLY			                            0x00000010

#define VBVA_MODE_HINT_MAGIC                                        0x0801ADD9

#define U32_MAX ((uint32_t)~0U)

typedef struct __attribute__((packed)) _VBVA_COMMAND_HEADER{
    int16_t     X;
    int16_t     Y;
    uint16_t    W;
    uint16_t    H;
}VBVA_COMMAND_HEADER, * PVBVA_COMMAND_HEADER;

typedef struct __attribute__((packed)) _VBVA_RECORD{
    uint32_t LengthAndFlags;
}VBVA_RECORD, * PVBVA_RECORD;

typedef struct __attribute__((packed)) _VBVA_HOST_FLAGS{
    uint32_t HostEvents;
    uint32_t SupportedOrders;
}VBVA_HOST_FLAGS, * PVBVA_HOST_FLAGS;

typedef struct __attribute__((packed)) _VBVA_BUFFER{
    VBVA_HOST_FLAGS     VbVaHostFlags;
    uint32_t            DataOffset;
    uint32_t            FreeOffset;
    VBVA_RECORD         VbVaRecords[VBVA_MAXIMUM_RECORDS];
    uint32_t            RecordFirstIndex;
    uint32_t            RecordFreeIndex;
    uint32_t            PartialWriteTresh;
    uint32_t            DataLength;
    uint8_t             DataBlock[];
}VBVA_BUFFER, * PVBVA_BUFFER;

typedef struct __attribute__((packed)) _VBVA_CONFIGURATION32{
    uint32_t    Index;
    uint32_t    Value;
}VBVA_CONFIGURATION32, * PVBVA_CONFIGURATION32;

typedef struct __attribute__((packed)) _VBVA_INFORMATION_VIEW{
    uint32_t    ViewIndex;
    uint32_t    ViewOffset;
    uint32_t    ViewSize;
    uint32_t    MaximumScreenSize;
}VBVA_INFORMATION_VIEW, * PVBVA_INFORMATION_VIEW;

typedef struct __attribute__((packed)) _VBVA_INFORMATION_SCREEN{
    uint32_t    ViewIndex;
    uint32_t    StartX;
    uint32_t    StartY;
    uint32_t    StartOffset;
    uint32_t    LineSize;
    uint32_t    Width;
    uint32_t    Height;
    uint16_t    Bpp;
    uint16_t    Flags;
}VBVA_INFORMATION_SCREEN, * PVBVA_INFORMATION_SCREEN;

typedef struct __attribute__((packed)) _VBVA_ENABLE{
    uint32_t    Flags;
    uint32_t    Offset;
    uint32_t    Result;
}VBVA_ENABLE, * PVBVA_ENABLE;

typedef struct __attribute__((packed)) _VBVA_ENABLE_EX{
    VBVA_ENABLE Base;
    uint32_t    ScreenID;
}VBVA_ENABLE_EX, * PVBVA_ENABLE_EX;

typedef struct __attribute__((packed)) _VBVA_MOUSE_POINTER_SHAPE{
    int32_t     Result;
    uint32_t    Flags;
    uint32_t    HotX;
    uint32_t    HotY;
    uint32_t    Width;
    uint32_t    Height;
    uint8_t     DataBlock[];
}VBVA_MOUSE_POINTER_SHAPE, * PVBVA_MOUSE_POINTER_SHAPE;

typedef struct __attribute__((packed)) _VBVA_CAPS{
    int32_t     Rc;
    uint32_t    Caps;
}VBVA_CAPS, * PVBVA_CAPS;

typedef struct __attribute__((packed)) _VBVA_QUERY_MODE_HINTS{
    uint16_t    HintsQueriedCount;
    uint16_t    HintStructureQuestSize;
    int32_t     Rc;
}VBVA_QUERY_MODE_HINTS, * PVBVA_QUERY_MODE_HINTS;

typedef struct __attribute__((packed)) _VBVA_MODE_HINT{
    uint32_t Magic;
    uint32_t Cx;
    uint32_t Cy;
    uint32_t Bpp;
    uint32_t Dispaly;
    uint32_t Dx;
    uint32_t Dy;
    uint32_t Enabled;
}VBVA_MODE_HINT, * PVBVA_MODE_HINT;

typedef struct __attribute__((packed)) _VBVA_REPORT_INPUT_MAPPING{
    int32_t     X;
    int32_t     Y;
    uint32_t    Cx;
    uint32_t    Cy;
}VBVA_REPORT_INPUT_MAPPING, * PVBVA_REPORT_INPUT_MAPPING;

typedef struct __attribute__((packed)) _VBVA_CURSOR_POSITION{
    uint32_t ReportPosition;
    uint32_t X;
    uint32_t Y;
}VBVA_CURSOR_POSITION, * PVBVA_CURSOR_POSITION;

#endif//_VBOX_VIDEO_H