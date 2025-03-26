#ifndef _VIRTUALBOX_DRIVER_H
#define _VIRTUALBOX_DRIVER_H

/* SPDX-License-Identifier: MIT */
/*
 * Copyright (C) 2013-2017 Oracle Corporation
 * This file is based on ast_drv.h
 * Copyright 2012 Red Hat Inc.
 * Authors: Dave Airlie <airlied@redhat.com>
 *          Michael Thayer <michael.thayer@oracle.com,
 *          Hans de Goede <hdegoede@redhat.com>
 */
/* Copyright (C) 2025 Tyler Grenier */
/* Rewritten keystroke-by-keystroke by Tyler Grenier for AnnyaOS */


#define VIRTUALBOX_MAXIMUM_CURSOR_WIDTH     64
#define VIRTUALBOX_MAXIMUM_CURSOR_HEIGHT    64
#define VIRTUALBOX_CURSOR_PIXEL_COUNT       (VIRTUALBOX_MAXIMUM_CURSOR_WIDTH * VIRTUALBOX_MAXIMUM_CURSOR_HEIGHT)
#define VIRTUALBOX_CURSOR_DATA_SIZE         (VIRTUALBOX_CURSOR_PIXEL_COUNT * 4 + VIRTUALBOX_CURSOR_PIXEL_COUNT / 8)
#define MAXIMUM_VIRTUALBOX_MONITORS         32
#define VIRTUALBOX_GUEST_HEAP_OFFSET(VBox)  ((VBox)->FullVRamSize - VBVA_ADAPTER_INFORMATION_SIZE)
#define VIRTUALBOX_GUEST_HEAP_SIZE          VBVA_ADAPTER_INFORMATION_SIZE
#define VIRTUALBOX_GUEST_HEAP_USABLE_SIZE   VBVA_ADAPTER_INFORMATION_SIZE - sizeof(HGSMI_HOST_FLAGS)
#define VIRTUALBOX_HOST_FLAGS_OFFSET        VIRTUALBOX_GUEST_HEAP_USABLE_SIZE

typedef struct _VIRTUALBOX_PRIVATE_DATA{
    PDrsdVRamObject             VirtualboxDrsdSystem;
    PFrameBufferModeDefinition  ModeDefinitions;
    uint8_t*                    GuestHeap;
    uint8_t*                    VbvaBuffers;
    POOL                        GuestPool;
    void*                       VbvaBufferContext;
    bool                        AnyPitch;
    uint32_t                    CrtcCount;
    uint32_t                    FullVRamSize;
    uint32_t                    AvailableVramSize;
    void*                       LastModeHints;
    int                         FrameBufferMtrr;
    mutex_t                     HardwareMutex;
    LOUQ_WORK                   HotplugWork;
    uint32_t                    InputMappingWidth;
    uint32_t                    InputMappingHeight;
    bool                        SingleFramebuffer;
    uint8_t             CursorData[VIRTUALBOX_CURSOR_DATA_SIZE];
}VIRTUALBOX_PRIVATE_DATA, * PVIRTUALBOX_PRIVATE_DATA;

#undef VIRTUALBOX_CURSOR_PIXEL_COUNT
#undef VIRTUALBOX_CURSOR_DATA_SIZE

typedef struct _VIRTUALBOX_CONNECTOR{
    PDrsdConnector  Base;
    char            Name[32];
    void*           VBOXCrtc;
    struct{
        uint32_t    Width;
        uint32_t    Height;
        bool        Disconnected;
    }ModeHint;
}VIRTUALBOX_CONNECTOR, * PVIRTUALBOX_CONNECTOR;

typedef struct _VIRTUALBOX_CRTC{
    PDrsdCrtc   Base;
    bool        Disconnected;
    uint32_t    CrtcId;
    uint32_t    FramebufferOffset;
    bool        CursorEnabled;
    uint32_t    XHint;
    uint32_t    YHint;
    uint32_t    Width;
    uint32_t    Height;
    uint32_t    X;
    uint32_t    Y;
}VIRTUALBOX_CRTC, * PVIRTUALBOX_CRTC;

typedef struct _VIRTUALBOX_ENCODER{
    DrsdEncoder Base;
}VIRTUALBOX_ENCODER, * PVIRTUALBOX_ENCODER;

#define GET_VIRTUALBOX_CRTC(x)      container_of(x, VIRTUALBOX_CRTC, Base)
#define GET_VIRTUALBOX_CONNECTOR(x) container_of(x, VIRTUALBOX_CONNECTOR, Base)
#define GET_VIRTUALBOX_ENCODER(x)   container_of(x, VIRTUALBOX_ENCODER, Base)
#define GET_VIRTUALBOX_DEVICE(x)    container_of(x, VIRTUALBOX_PRIVATE_DATA, Device)

bool VirtualboxCheckSupported(uint16_t Identification);
int VirtualboxHardwareInitialization(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void VirtualboxHardwareDeinitialization(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
int VirtualboxModeInitialization(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void VirtualboxModeDeinitialization(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void VirtualboxReportCaps(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
int VirtualboxMmInit(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
int VirtualboxIrqInitializeation(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void VirtualboxIrqDeinitialization(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void VirtualboxIrqReportHotplug(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void* HgsmiBufferAllocate(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void  HgsmiBufferFree(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void  HgsmiBufferSubmit(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);

#define VBE_DISPI_IOPORT_INDEX 0x01CE  // I/O port for setting the index register
#define VBE_DISPI_DISABLED 0x00  // Common value used to disable the adapter
#define VBE_DISPI_IOPORT_DATA 0x01CF  // I/O port for reading/writing data
#define VBE_DISPI_ENABLED 0x01  // Common value used to enable the adapter
#define VBE_DISPI_LFB_ENABLED 0x40  // Value to enable linear framebuffer mode

static inline void VBOX_IO_WRITE(uint16_t Index, uint16_t Data){
    outw(Index, VBE_DISPI_IOPORT_INDEX);
    outw(Index, VBE_DISPI_IOPORT_DATA);
}

#endif//_VIRTUALBOX_DRIVER_H