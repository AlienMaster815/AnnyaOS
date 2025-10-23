#define _KERNEL_MODULE_
/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */


#include <LouDDK.h>
#include "VirtualboxDriver.h"
#include <Hal.h>
#include <drivers/VBoxError.h>

static void* VBoxEdid = 0x00;

static const uint8_t VBoxMasterEdid[] ={
//directly coppied from Linux https://github.com/torvalds/linux/blob/master/drivers/gpu/drm/vboxvideo/vbox_mode.c
// SPDX-License-Identifier: MIT
/*
 * Copyright (C) 2013-2017 Oracle Corporation
 * This file is based on ast_mode.c
 * Copyright 2012 Red Hat Inc.
 * Parts based on xf86-video-ast
 * Copyright (c) 2005 ASPEED Technology Inc.
 * Authors: Dave Airlie <airlied@redhat.com>
 *          Michael Thayer <michael.thayer@oracle.com,
 *          Hans de Goede <hdegoede@redhat.com>
 */
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,	/* header */
	0x58, 0x58,	/* manufacturer (VBX) */
	0x00, 0x00,	/* product code */
	0x00, 0x00, 0x00, 0x00,	/* serial number goes here */
	0x01,		/* week of manufacture */
	0x00,		/* year of manufacture */
	0x01, 0x03,	/* EDID version */
	0x80,		/* capabilities - digital */
	0x00,		/* horiz. res in cm, zero for projectors */
	0x00,		/* vert. res in cm */
	0x78,		/* display gamma (120 == 2.2). */
	0xEE,		/* features (standby, suspend, off, RGB, std */
	/* colour space, preferred timing mode) */
	0xEE, 0x91, 0xA3, 0x54, 0x4C, 0x99, 0x26, 0x0F, 0x50, 0x54,
	/* chromaticity for standard colour space. */
	0x00, 0x00, 0x00,	/* no default timings */
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01,
	0x01, 0x01, 0x01, 0x01,	/* no standard timings */
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x02, 0x02,
	0x02, 0x02,
	/* descriptor block 1 goes below */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* descriptor block 2, monitor ranges */
	0x00, 0x00, 0x00, 0xFD, 0x00,
	0x00, 0xC8, 0x00, 0xC8, 0x64, 0x00, 0x0A, 0x20, 0x20, 0x20,
	0x20, 0x20,
	/* 0-200Hz vertical, 0-200KHz horizontal, 1000MHz pixel clock */
	0x20,
	/* descriptor block 3, monitor name */
	0x00, 0x00, 0x00, 0xFC, 0x00,
	'V', 'B', 'O', 'X', ' ', 'm', 'o', 'n', 'i', 't', 'o', 'r',
	'\n',
	/* descriptor block 4: dummy data */
	0x00, 0x00, 0x00, 0x10, 0x00,
	0x0A, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20,
	0x00,		/* number of extensions */
	0x00		/* checksum goes here */
//Endof Direct Copy
};

static void VirtualboxSetEDID(
    PDRSD_CONNECTOR Connector, 
    uint32_t Width, 
    uint32_t Height
){
    uint8_t* VbEdidTmp = (uint8_t*)VBoxEdid;

    memcpy(VbEdidTmp, VBoxMasterEdid, STANDARD_INTEL_CHIPSET_EDID_SIZE);

    size_t KhzClock = (Width + 6) * (Height + 6) * 60 / 10000;
    size_t Sum = 0;
    
    VbEdidTmp[12] = Width & 0xFF;
    VbEdidTmp[13] = (Width >> 8) & 0xFF;
    VbEdidTmp[14] = Height & 0xFF;
    VbEdidTmp[15] = (Height >> 8) & 0xFF;

    VbEdidTmp[54] = KhzClock & 0xFF;
    VbEdidTmp[55] = (KhzClock >> 8) & 0xFF;
   
    VbEdidTmp[56] = Width & 0xFF;
    VbEdidTmp[58] = (Width >> 4) & 0xF0;
    VbEdidTmp[59] = Height & 0xFF;
    VbEdidTmp[61] = (Height >> 4) & 0xF0;

    for(size_t i = 0 ; i < STANDARD_INTEL_CHIPSET_EDID_SIZE - 1; ++i){
        Sum += VbEdidTmp[i];
    }
    VbEdidTmp[STANDARD_INTEL_CHIPSET_EDID_SIZE - 1] = (0x100 - (Sum & 0xFF)) & 0xFF;
    DrsdUpdateEdidConnectorProperties(Connector, (PINTEL_STANDARD_EDID)VbEdidTmp);
}

static size_t VirtualboxGetModes(PDRSD_CONNECTOR Connector){
    PVIRTUALBOX_CONNECTOR VBoxConnector = (PVIRTUALBOX_CONNECTOR)Connector;
    PDRSD_DISPLAY_MODE DispMode;
    size_t ModeCount = 0;
    int32_t PreferedWidth, PreferedHeight;
    PVIRTUALBOX_PRIVATE_DATA VBox = (PVIRTUALBOX_PRIVATE_DATA)Connector->Device;

    HgsmiReportFlagsLocation(VBox->GuestPool, VIRTUALBOX_GUEST_HEAP_OFFSET(VBox) + VIRTUALBOX_HOST_FLAGS_OFFSET);    

    if(VBoxConnector->VBOXCrtc->CrtcId == 0){
        VirtualboxReportCapabilities(VBox);
    }

    ModeCount = DrsdAddModesNoEDID(Connector, 2560, 1600);

    PreferedWidth = VBoxConnector->ModeHint.Width;
    PreferedWidth = PreferedWidth ? PreferedWidth : 1024; 
    PreferedHeight = VBoxConnector->ModeHint.Height;
    PreferedHeight = PreferedHeight ? PreferedHeight : 768;

    LouPrint("Prefered Width :%d\n", PreferedWidth);
    LouPrint("Prefered Height:%d\n", PreferedHeight);

    PDRSD_DISPLAY_MODE NewGenuineMode = DrsdCvtMode(Connector->Device, PreferedWidth, PreferedHeight, 60, false, false, false);
    if(NewGenuineMode){
        NewGenuineMode->ModeType |= DRSD_MODE_TYPE_PREFERED;
        DrsdAddProbedDisplayModeToConnector(Connector, NewGenuineMode);
        ++ModeCount;
    }
    VirtualboxSetEDID(Connector, PreferedWidth, PreferedHeight);

    LouPrint("VirtualboxGetModes() STATUS_SUCCESS\n");
    return ModeCount;
}

static LOUSTATUS VirtualboxFillModes(
    PDRSD_CONNECTOR Connector, 
    uint32_t MaxX, 
    uint32_t MaxY
){
    PVIRTUALBOX_CONNECTOR VBoxConnector = (PVIRTUALBOX_CONNECTOR)Connector;
    PDRSD_DEVICE Device = VBoxConnector->Base.Device;

    //TODO: Delete Old Modes

    LOUSTATUS Status = DrsdInternalProbeSingleConnectorModes(
        Connector,
        MaxX,
        MaxY
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    LouPrint("VirtualboxFillModes() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

static DRSD_CONNECTOR_STATUS VirtualboxConnectorDetect(
    PDRSD_CONNECTOR Connector,
    bool            Force
){
    return ((PVIRTUALBOX_CONNECTOR)Connector)->ModeHint.Disconnected ? DRSD_CONNECTOR_DISCONNECTED : DRSD_CONNECTOR_CONNECTED;
}

static void VirtualboxConnectorDestroy(
    PDRSD_CONNECTOR Connector
){
    LouPrint("VirtualboxConnectorDestroy()\n");
    while(1);
}

static  DRSD_CONNECTOR_ASSIST_CALLBACKS VirtualboxConnectorAssistCallbacks = {
    .ConnectorGetModes = VirtualboxGetModes,
};

static  DRSD_CONNECTOR_CALLBACKS VirtualboxConnectorCalbacks = {
    .DetectConnector = VirtualboxConnectorDetect,
    .ConnectorFillModes = VirtualboxFillModes,
    .DestroyConnector = VirtualboxConnectorDestroy,
    .ConnectorAtomicDuplicateState = DrsdInternalAtomicConnectorDuplicateState,
    .ConnectorDestroyStateAtomic = DrsdInternalAtomicConnectorDestroyState,
};

static void VirtualboxEncoderDestroy(
    PDRSD_ENCODER Encoder
){
    LouPrint("VirtualboxEncoderDestroy()\n");
    while(1);
}

static  DRSD_ENCODER_CALLBACKS VirtualboxEncoderCallbacks = {
    .DestroyEnocder = VirtualboxEncoderDestroy,
};

static void VirtualboxCrtcAtomicEnable(
    PDRSD_CRTC  Crtc,
    void*       AtomicData
){
}

static void VirtualboxCrtcAtomicDisable(
    PDRSD_CRTC  Crtc,
    void*       AtomicData
){
}

static void VirtualboxCrtcAtomicFlush(
    PDRSD_CRTC  Crtc,
    void*       AtomicData
){
}

static void VirtualboxCrtcDestroy(PDRSD_CRTC Crtc){
}

static  DRSD_CRTC_CALLBACK VBoxCrtcCallbacks = {
    .ResetCrtc = DrsdInternalCrtcResetAtomic,
    .DestroyCrtc = VirtualboxCrtcDestroy,
    .SetConfiguration = DrsdInternalCrtcSetConfigurationAtomic,
    .PageFlip = DrsdInternalCrtcPageFlipAtomic,
    .AtomicDuplicateState = DrsdInternalCrtcDuplicateStateAtomic,
    .AtomicDestroyState = DrsdInternalCrtcDestroyStateAtomic,
};

static  DRSD_CRTC_ASSIST_CALLBACK VBoxCrtcAssistCallbacks = {
    .FlushAtomic = VirtualboxCrtcAtomicFlush,
    .EnableAtomic = VirtualboxCrtcAtomicEnable,
    .DisableAtomic = VirtualboxCrtcAtomicDisable,
};

static void VirtualboxCursorAtomicUpdate(
    PDRSD_PLANE Plane,
    void*       Handle
){
    LouPrint("VirtualboxCursorAtomicUpdate()\n");
    while(1);
}

static LOUSTATUS VirtualboxCursorAtomicCheck(
    PDRSD_PLANE Plane,
    void*       Handle
){
    LouPrint("VirtualboxCursorAtomicCheck()\n");
    while(1);
    return STATUS_SUCCESS;
}

//disable and enable
static void VirtualboxCursorAtomicSetState(
    PDRSD_PLANE     Plane, 
    void*           State,
    bool            Enable
){
    LouPrint("VirtualboxCursorAtomicSetState()\n");
    while(1);
}

static bool VBoxSetUpInputMapping(PVIRTUALBOX_PRIVATE_DATA VBox){
    //PDRSD_CRTC Crtc = VBox->DrsdDevice.Crtcs;
    if(VBox->DrsdDevice.CrtcCount == 1){
        return false;
    }

    //TODO: im going to do this later once i know everything is working
    LouPrint("VBoxSetUpInputMapping()\n");
    while(1);
    return true;
}

static LOUSTATUS VBoxSetView(PDRSD_CRTC DrsdCrtc, size_t FbSize){
    PVIRTUALBOX_CRTC VBoxCrtc = (PVIRTUALBOX_CRTC)DrsdCrtc;
    PVIRTUALBOX_PRIVATE_DATA VBox = (PVIRTUALBOX_PRIVATE_DATA)DrsdCrtc->Device;
    PVBVA_INFORMATION_VIEW View = (PVBVA_INFORMATION_VIEW)HgsmiBufferAllocate(VBox->GuestPool, sizeof(VBVA_INFORMATION_VIEW), HGSMI_CH_VBVA, VBVA_INFORMATION_VIEW_COMMAND);
    if(!View){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    View->ViewIndex = VBoxCrtc->CrtcId;
    View->ViewOffset = VBoxCrtc->FramebufferOffset;
    View->ViewSize = FbSize;
    View->MaximumScreenSize = FbSize;
    HgsmiBufferSubmit(VBox->GuestPool, View);
    HgsmiBufferFree(VBox->GuestPool, View);
    //LouPrint("VBoxSetView() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

static void VboxDoModeSet(
    PDRSD_CRTC          Crtc,
    PDRSD_FRAME_BUFFER  Fb
){
    PVIRTUALBOX_PRIVATE_DATA VBox = (PVIRTUALBOX_PRIVATE_DATA)Crtc->Device;
    PVIRTUALBOX_CRTC VBoxCrtc = (PVIRTUALBOX_CRTC)Crtc;
    int32_t Width = VBoxCrtc->Width, Height = VBoxCrtc->Height, Bpp = Fb->Bpp, Pitch = Fb->Pitch, 
        X = VBoxCrtc->X ? VBoxCrtc->X : VBoxCrtc->XHint, Y = VBoxCrtc->Y ? VBoxCrtc->Y : VBoxCrtc->YHint;
    UNUSED uint16_t Flags = 0;

    if((VBoxCrtc->CrtcId == 0) && (Fb) && 
        ((VBoxCrtc->FramebufferOffset / Pitch) < (0xFFFF - Y)) && 
        ((VBoxCrtc->FramebufferOffset % (Bpp / 8)) == 0x00)){
            VBOX_IO_WRITE(VIRTUALBOX_VBE_DISPI_INDEX_XRESOLUTION, Width);
            VBOX_IO_WRITE(VIRTUALBOX_VBE_DISPI_INDEX_YRESOLUTION, Height);
            VBOX_IO_WRITE(VIRTUALBOX_VBE_DISPI_INDEX_VIRTUAL_WIDTH, Pitch * 8 / Bpp);
            VBOX_IO_WRITE(VIRTUALBOX_VBE_DISPI_INDEX_BPP, Bpp);
            VBOX_IO_WRITE(VIRTUALBOX_VBE_DISPI_INDEX_ENABLE, VIRTUALBOX_VBE_DISPI_ENABLED);
            VBOX_IO_WRITE(VIRTUALBOX_VBE_DISPI_INDEX_X_OFFSET, VBoxCrtc->FramebufferOffset % Pitch / Bpp * 8 + VBoxCrtc->X);
            VBOX_IO_WRITE(VIRTUALBOX_VBE_DISPI_INDEX_Y_OFFSET, VBoxCrtc->FramebufferOffset / Pitch + VBoxCrtc->Y);
    }

    Flags = VBVA_SCREEN_F_ACTIVE;
    Flags |= (Fb && Crtc->CrtcState->Enable) ? 0 : VBVA_SCREEN_F_BLANK;
    Flags |= VBoxCrtc->Disconnected ? VBVA_SCREEN_F_DISABLED : 0;

    HgsmiProccessDisplayInformation(
        VBox->GuestPool, 
        VBoxCrtc->CrtcId, 
        X, Y, 
        VBoxCrtc->X * Bpp / 8 + VBoxCrtc->Y * Pitch, 
        Pitch, Width, Height, Bpp, Flags
    );

    //LouPrint("VboxDoModeSet() STATUS_SUCCESS\n");
}

static void VirtualCrtcSetBaseAndMode(
    PDRSD_CRTC          Crtc,
    PDRSD_FRAME_BUFFER  FrameBuffer,
    int32_t             X,
    int32_t             Y
){
    PVIRTUALBOX_PRIVATE_DATA VBox = (PVIRTUALBOX_PRIVATE_DATA)FrameBuffer->Device;
    uintptr_t           FrameVBase = FrameBuffer->FramebufferBase;
    uintptr_t           FramePBase = FrameBuffer->Offset;
    size_t              FrameSize = FrameBuffer->FramebufferSize;
    bool                ModeSet = Crtc->CrtcState->NeedsModeset; 
    PVIRTUALBOX_CRTC    VBoxCrtc = (PVIRTUALBOX_CRTC)Crtc;
    
    MutexLock(&VBox->HardwareMutex);

    if(Crtc->CrtcState->Enable){
        VBoxCrtc->Width = Crtc->CrtcState->DisplayMode.HorizontalDisplay;
        VBoxCrtc->Height = Crtc->CrtcState->DisplayMode.VirticalDisplay;
        //LouPrint("VBOXGPU:Setting Width:%d And Height:%d\n", VBoxCrtc->Width, VBoxCrtc->Height);
    }

    VBoxCrtc->X = X;
    VBoxCrtc->Y = X;
    VBoxCrtc->FramebufferOffset = FramePBase;

    if(ModeSet && VBoxSetUpInputMapping(VBox)){
        //LouPrint("YAY!!!\n");
    }
    
    VBoxSetView(Crtc, FrameSize);
    VboxDoModeSet(Crtc, FrameBuffer);

    if(ModeSet){
        HgsmiUpdateInputMappings(VBox->GuestPool, 0, 0, VBox->InputMappingWidth, VBox->InputMappingHeight);
    }

    MutexUnlock(&VBox->HardwareMutex);
    //LouPrint("VirtualCrtcSetBaseAndMode() STATUS_SUCCESS\n");
}

static void VirtualboxAtomicUpdate(
    PDRSD_PLANE Plane,
    void*       Handle
){

    PDRSD_PLANE_STATE NewState = Plane->PlaneState;
    PDRSD_FRAME_BUFFER FrameBuffer = NewState->FrameBuffer;
    PVIRTUALBOX_PRIVATE_DATA Vbox = (PVIRTUALBOX_PRIVATE_DATA)FrameBuffer->Device;
    PDRSD_CRTC Crtc = NewState->Crtc;

    VirtualCrtcSetBaseAndMode(
        Crtc, 
        FrameBuffer, 
        NewState->SourceX, 
        NewState->SourceX
    );


    //LouPrint("VirtualboxAtomicUpdate() STATUS_SUCCES\n");
}

static LOUSTATUS VirtualboxAtomicCheck(
    PDRSD_PLANE Plane,
    void*       Handle
){
    LouPrint("VirtualboxAtomicCheck()\n");
    while(1);
    return STATUS_SUCCESS;
}

//disable and enable
static void VirtualboxAtomicSetState(
    PDRSD_PLANE     Plane, 
    void*           State,
    bool            Enable
){
    LouPrint("VirtualboxAtomicSetState()\n");
    while(1);
}

static uint32_t CursorPlaneFormats[1] = {0};

static  DRSD_PLANE_ASSIST_CALLBACKS CursorPlaneAssistFunctions = {
    .StartFrameBufferProcessing = DrsdGxeInternalStartFrameBufferProcessing,
    .StopFrameBufferProcessing = DrsdGxeInternalStopFrameBufferProcessing,
    .AtomicCheck = VirtualboxCursorAtomicCheck,
    .AtomicUpdate = VirtualboxCursorAtomicUpdate,
    .AtomicSetState = VirtualboxCursorAtomicSetState,
};

static  DRSD_PLANE_CALLBACKS CursorPlaneFunctions = {
    .UpdatePlane = DrsdInternalPlaneUpdateAtomic,
    .DisablePlane = DrsdInternalPlaneDisableAtomic,
    .DestroyPlane = DrsdInternalDestroyPlaneAtomic,
    .ResetPlane = DrsdGxeResetShadowPlane,
    .DuplicatePlaneAtomicState = DrsdGxeDuplicateShadowPlaneState,
    .DestroyPlaneAtomic = DrsdGxeDestroyShadowPlane,
};

static uint32_t PlaneFormats[2] = {0};

static  DRSD_PLANE_ASSIST_CALLBACKS PlaneAssistedCallbacks = {
    .PrepareFrameBuffer = DrsdGxeInternalPrepareFrameBuffer,
    .CleanupFrameBuffer = DrsdGxeInternalCleanupFrameBuffer,
    .AtomicCheck = VirtualboxAtomicCheck,
    .AtomicUpdate = VirtualboxAtomicUpdate,
    .AtomicSetState = VirtualboxAtomicSetState,
};

static  DRSD_PLANE_CALLBACKS PlaneCallbacks = {
    .UpdatePlane = DrsdInternalPlaneUpdateAtomic,
    .DisablePlane = DrsdInternalPlaneDisableAtomic,
    .DestroyPlane = DrsdInternalDestroyPlaneAtomic,
    .ResetPlane = DrsdInternalResetPlane,
    .DuplicatePlaneAtomicState = DrsdInternalDuplicateAtomicState,
    .DestroyPlaneAtomic = DrsdInternalDestroyPlaneAtomic, 
};

static  DRSD_MODE_CONFIGURATION_CALLBACKS VirtualboxModeCallbacks = {
    .CreateFrameBuffer = DrsdGxeCreateAsyncFramebuffer,
    .ModeValid = DrsdGxeVramInternalModeValid,
    .AtomicCheck = DrsdInternalAtomicCheck,
    .AtomicSet = DrsdInternalAtomicUpdate,
};

static PDRSD_PLANE VirtualboxCreatePlane(
    PVIRTUALBOX_PRIVATE_DATA    VBox,
    uint64_t                    CrtcLimit,
    DRSD_PLANE_TYPE             Type
){
    PDRSD_PLANE_ASSIST_CALLBACKS AssistFunctions = 0x00;
    PDRSD_PLANE_CALLBACKS Functions = 0x00;
    PDRSD_PLANE NewPlane;
    uint32_t*   Formats;
    size_t      FormatCount;
    LOUSTATUS   Status;

    switch(Type){
        case PRIMARY_PLANE:
            Functions = (PDRSD_PLANE_CALLBACKS)&PlaneCallbacks;
            AssistFunctions = (PDRSD_PLANE_ASSIST_CALLBACKS)&PlaneAssistedCallbacks;
            Formats = PlaneFormats;
            FormatCount = 2;
            break;
        case CURSOR_PLANE:
            Functions = (PDRSD_PLANE_CALLBACKS)&CursorPlaneFunctions;
            AssistFunctions = (PDRSD_PLANE_ASSIST_CALLBACKS)&CursorPlaneAssistFunctions;
            Formats = CursorPlaneFormats;
            FormatCount = 1; 
            break;
        default:
            return 0x00;
    }
    NewPlane = LouKeMallocType(DRSD_PLANE, KERNEL_GENERIC_MEMORY);
    if(!NewPlane){
        return 0x00;
    }

    Status = DrsdInitializeGenericPlane(
        &VBox->DrsdDevice, 
        NewPlane,
        CrtcLimit,
        Functions,
        Formats,
        FormatCount,
        0x00,
        Type,
        0x00
    );
    if(Status != STATUS_SUCCESS){
        return 0x00;
    }

    NewPlane->AssistCallbacks = AssistFunctions;

    LouPrint("VirtualboxCreatePlane() STATUS_SUCCESS\n");
    return NewPlane;
}

static PVIRTUALBOX_CRTC VirtualboxCrtcInitialize(
    PDRSD_DEVICE Device, 
    size_t i
){
    PVIRTUALBOX_PRIVATE_DATA VBox = (PVIRTUALBOX_PRIVATE_DATA)(uintptr_t)Device;
    PVIRTUALBOX_CRTC VBoxCrtc = 0x00;
    PDRSD_PLANE Cursor = 0x00;
    PDRSD_PLANE Primary = 0x00;
    uint32_t Capabilities = 0x00;
    LOUSTATUS Status;

    Status = HgsmiQueryConfiguration(
        VBox->GuestPool,
        VIRTUALBOX_VBVA_CONFIGURATION32_CURSOR_CAPABILITIES,
        &Capabilities
    );
    if(Status != STATUS_SUCCESS){
        return 0x00;
    }

    VBoxCrtc = LouKeMallocType(VIRTUALBOX_CRTC, KERNEL_GENERIC_MEMORY);
    if(!VBoxCrtc){
        return 0x00;
    }

    Primary = VirtualboxCreatePlane(
        VBox, 
        1 << i, 
        PRIMARY_PLANE
    );
    if(!Primary){
        return 0x00;
    }

    if(Capabilities & VIRTUALBOX_VBVA_CURSOR_CAPABILITY_HARDWARE){
        Cursor = VirtualboxCreatePlane(
            VBox,
            1 << i,
            CURSOR_PLANE
        );
        if(!Cursor){
            return 0x00;
        }
    }else{
        LouPrint("Virtualbox Host Too Old For Hardware Accelerated Cursor\n");
    }

    VBoxCrtc->CrtcId = i;

    Status = DrsdInitializeCrtcWithPlanes(
        Device, 
        &VBoxCrtc->Base,
        Primary,
        Cursor,
        (PDRSD_CRTC_CALLBACK)&VBoxCrtcCallbacks
    );
    if(Status != STATUS_SUCCESS){
        return 0x00;
    }

    DrsdInitializeCrtcGammaSize(&VBoxCrtc->Base, 256);

    VBoxCrtc->Base.AssistCallbacks = (PDRSD_CRTC_ASSIST_CALLBACK)&VBoxCrtcAssistCallbacks;

    VBoxCrtc->CrtcId = i;

    LouPrint("VirtualboxCrtcInitialize() STATUS_SUCCESS\n");
    return VBoxCrtc;
}

static PDRSD_ENCODER VirtualboxEncoderInitialize(
    PDRSD_DEVICE Device, 
    size_t i
){
    PVIRTUALBOX_ENCODER VBoxEncoder = LouKeMallocType(VIRTUALBOX_ENCODER, KERNEL_GENERIC_MEMORY);
    if(!VBoxEncoder){
        return 0x00;
    }
    DrsdInitializeEncoder(
        Device,
        &VBoxEncoder->Base,
        (PDRSD_ENCODER_CALLBACKS)&VirtualboxEncoderCallbacks,
        DRSD_ENCODER_MODE_DAC, 
        0x00
    );
    LouPrint("VirtualboxEncoderInitialize() STATUS_SUCCESS\n");

    return &VBoxEncoder->Base;
}

static LOUSTATUS VirtualboxConnectorInitialize(
    PDRSD_DEVICE        Device,
    PVIRTUALBOX_CRTC    Crtc,
    PDRSD_ENCODER       Encoder
){
    PVIRTUALBOX_CONNECTOR   VBoxConnector;
    PDRSD_CONNECTOR         Connector;
    VBoxConnector = LouKeMallocType(VIRTUALBOX_CONNECTOR, KERNEL_GENERIC_MEMORY);

    Connector = &VBoxConnector->Base;


    DrsdConnectorInitialize(
        Device, 
        &Crtc->Base,
        Connector, 
        (PDRSD_CONNECTOR_CALLBACKS)&VirtualboxConnectorCalbacks, 
        DRSD_CONNECTOR_MODE_VGA
    );

    Connector->AssistCallbacks = (PDRSD_CONNECTOR_ASSIST_CALLBACKS)&VirtualboxConnectorAssistCallbacks;

    Connector->InterlaceAble = false;
    Connector->DoubleScanAble = false;

    Device->ModeConfiguration.SuggestedX = 0;
    Device->ModeConfiguration.SuggestedY = 0;
        
    ((PVIRTUALBOX_CONNECTOR)Connector)->VBOXCrtc = Crtc;

    LouPrint("VirtualboxConnectorInitialize() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS VirtualboxModeInitialization(PVIRTUALBOX_PRIVATE_DATA VBox){
    PDRSD_DEVICE Device = &VBox->DrsdDevice;
    PVIRTUALBOX_CRTC    VBoxCrtc;
    PDRSD_ENCODER VBoxEncoder;
    LOUSTATUS Result;
    Device->ModeConfiguration.Callbacks = (PDRSD_MODE_CONFIGURATION_CALLBACKS)&VirtualboxModeCallbacks; 
    Device->ModeConfiguration.MinimalWidth = 0;
    Device->ModeConfiguration.MinimalHeight = 0;
    Device->ModeConfiguration.MaximumWidth = VIRTUALBOX_VBE_DISPI_MAX_XRESOLUTION; 
    Device->ModeConfiguration.MaximumHeight = VIRTUALBOX_VBE_DISPI_MAX_YRESOLUTION;
    Device->ModeConfiguration.PreferedDepth = 24;

    memcpy(&PlaneFormats[0], DRSD_COLOR_FORMAT_XRGB8888, 4); 
    memcpy(&PlaneFormats[1], DRSD_COLOR_FORMAT_ARGB8888, 4); 
    memcpy(&CursorPlaneFormats[0], DRSD_COLOR_FORMAT_ARGB8888, 4);

    for(size_t  i = 0 ; i < VBox->CrtcCount; i++){
        VBoxCrtc = VirtualboxCrtcInitialize(Device, i);
        if(!VBoxCrtc){
            return STATUS_UNSUCCESSFUL;    
        }
        VBoxEncoder = VirtualboxEncoderInitialize(Device, i);
        if(!VBoxEncoder){
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        Result = VirtualboxConnectorInitialize(Device, VBoxCrtc, VBoxEncoder);
        if(Result != STATUS_SUCCESS){
            return Result;
        }

    }

    DrsdModeConfigurationReset(Device);

    VBoxEdid = LouKeMalloc(STANDARD_INTEL_CHIPSET_EDID_SIZE, KERNEL_GENERIC_MEMORY);

    return STATUS_SUCCESS;
}
