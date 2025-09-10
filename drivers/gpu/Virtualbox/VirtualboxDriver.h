#ifndef _VIRTUALBOX_DRIVER_H
#define _VIRTUALBOX_DRIVER_H

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

#define VIRTUALBOX_MAXIMUM_CURSOR_WIDTH     64
#define VIRTUALBOX_MAXIMUM_CURSOR_HEIGHT    64
#define VIRTUALBOX_CURSOR_PIXEL_COUNT       (VIRTUALBOX_MAXIMUM_CURSOR_WIDTH * VIRTUALBOX_MAXIMUM_CURSOR_HEIGHT)
#define VIRTUALBOX_CURSOR_DATA_SIZE         (VIRTUALBOX_CURSOR_PIXEL_COUNT * 4 + VIRTUALBOX_CURSOR_PIXEL_COUNT / 8)
#define MAXIMUM_VIRTUALBOX_MONITORS         32
#define VIRTUALBOX_GUEST_HEAP_OFFSET(VBox)  ((VBox)->FullVRamSize - VBVA_ADAPTER_INFORMATION_SIZE)
#define VIRTUALBOX_GUEST_HEAP_SIZE          VBVA_ADAPTER_INFORMATION_SIZE
#define VIRTUALBOX_GUEST_HEAP_USABLE_SIZE   VBVA_ADAPTER_INFORMATION_SIZE - sizeof(HGSMI_HOST_FLAGS)
#define VIRTUALBOX_HOST_FLAGS_OFFSET        VIRTUALBOX_GUEST_HEAP_USABLE_SIZE

#include "VirtualboxGuest.h"

typedef struct _VIRTUALBOX_PRIVATE_DATA{
    DRSD_DEVICE                         DrsdDevice;
    PPCI_DEVICE_OBJECT                  PDEV;
    struct _VBVA_BUFFER_CONTEXT*        VbvaInformation;
    POOL                                VramPool;
    uint8_t*                            VbvaBuffers;
    uint8_t*                            HgsmiHeap;
    POOL                                HgsmiPool;
    uint8_t*                            GuestHeap;
    POOL                                GuestPool;
    void*                               VbvaBufferContext;
    bool                                AnyPitch;
    bool                                VBoxVideo;
    uint32_t                            CrtcCount;
    uint32_t                            FullVRamSize;
    uint32_t                            AvailableVramSize;
    struct _VBVA_MODE_HINT*             LastModeHints;
    int                                 FrameBufferMtrr;
    mutex_t                             HardwareMutex;
    LOUQ_WORK                           HotplugWork;
    uint32_t                            InputMappingWidth;
    uint32_t                            InputMappingHeight;
    bool                                SingleFramebuffer;
    uint8_t                             CursorData[VIRTUALBOX_CURSOR_DATA_SIZE];
}VIRTUALBOX_PRIVATE_DATA, * PVIRTUALBOX_PRIVATE_DATA;

#undef VIRTUALBOX_CURSOR_PIXEL_COUNT
#undef VIRTUALBOX_CURSOR_DATA_SIZE

typedef struct _VIRTUALBOX_CRTC{
    DRSD_CRTC   Base;
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

typedef struct _VIRTUALBOX_CONNECTOR{
    DRSD_CONNECTOR      Base;
    char                Name[32];
    PVIRTUALBOX_CRTC    VBOXCrtc;
    struct{
        uint32_t        Width;
        uint32_t        Height;
        uint32_t        X;
        uint32_t        Y;
        bool            Disconnected;
    }ModeHint;
}VIRTUALBOX_CONNECTOR, * PVIRTUALBOX_CONNECTOR;

typedef struct _VIRTUALBOX_ENCODER{
    DRSD_ENCODER        Base;
}VIRTUALBOX_ENCODER, * PVIRTUALBOX_ENCODER;

#define GET_VIRTUALBOX_CRTC(x)          GET_CONTAINER(x, VIRTUALBOX_CRTC, Base)
#define GET_VIRTUALBOX_CONNECTOR(x)     GET_CONTAINER(x, VIRTUALBOX_CONNECTOR, Base)
#define GET_VIRTUALBOX_ENCODER(x)       GET_CONTAINER(x, VIRTUALBOX_ENCODER, Base)
#define GET_VIRTUALBOX_PRIVATE_DATA(x)  GET_CONTAINER(x, VIRTUALBOX_PRIVATE_DATA, Device)

bool VirtualboxCheckSupported(uint16_t Identification);
int VirtualboxHardwareInitialization(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void VirtualboxHardwareDeinitialization(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
LOUSTATUS VirtualboxModeInitialization(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void VirtualboxModeDeinitialization(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void VirtualboxReportCapabilities(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
int VirtualboxMmInit(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
LOUSTATUS InitializeVirtualboxInterrupts(PVIRTUALBOX_PRIVATE_DATA VBox);
void VirtualboxIrqDeinitialization(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);
void VirtualboxIrqReportHotplug(PVIRTUALBOX_PRIVATE_DATA VirtualboxPrivate);

void* HgsmiBufferAllocate(
    POOL GuestPool, 
    size_t size,
    uint8_t Channel,
    uint16_t ChannelInfo
);

int HgsmiBufferSubmit(
    POOL Context,
    void* Buffer
);

void HgsmiBufferFree(
    POOL Context,
    void* Buffer
);

#include "HgsmiDefinitions.h"
#include "VBoxVideo.h"
#include "HgsmiChSetup.h"
#include "HgsmiChannels.h"
#include "VirtualBoxVbe.h"


static inline void VBOX_IO_WRITE(uint16_t Index, uint16_t Data){
    outw(VIRTUALBOX_VBE_DISPI_IO_INDEX_PORT, Index);
    outw(VIRTUALBOX_VBE_DISPI_IO_DATA_PORT, Data);
}

#endif//_VIRTUALBOX_DRIVER_H