#define _KERNEL_MODULE_
/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */
/* Port Copyright (C) 2025-2026 Tyler Grenier */


#include <LouDDK.h>
#include "VirtualboxDriver.h"
#include <Hal.h>
#include <drivers/VBoxError.h>


static void VboxDoModeSet(
    PDRSD_CRTC          Crtc
){
    PVIRTUALBOX_PRIVATE_DATA VBox = (PVIRTUALBOX_PRIVATE_DATA)Crtc->Device;
    PVIRTUALBOX_CRTC VBoxCrtc = (PVIRTUALBOX_CRTC)Crtc;
    PDRSD_FRAME_BUFFER Fb = Crtc->PrimaryPlane->FrameBuffer;
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


static LOUSTATUS VBoxSetView(PDRSD_CRTC DrsdCrtc){
    PVIRTUALBOX_CRTC VBoxCrtc = (PVIRTUALBOX_CRTC)DrsdCrtc;
    PVIRTUALBOX_PRIVATE_DATA VBox = (PVIRTUALBOX_PRIVATE_DATA)DrsdCrtc->Device;
    PVBVA_INFORMATION_VIEW View = (PVBVA_INFORMATION_VIEW)HgsmiBufferAllocate(VBox->GuestPool, sizeof(VBVA_INFORMATION_VIEW), HGSMI_CH_VBVA, VBVA_INFORMATION_VIEW_COMMAND);
    if(!View){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    View->ViewIndex = VBoxCrtc->CrtcId;
    View->ViewOffset = VBoxCrtc->FramebufferOffset;
    View->ViewSize = VBox->AvailableVramSize - VBoxCrtc->FramebufferOffset + VBoxCrtc->CrtcId * VBVA_MINIMUM_BUFFER_SIZE;
    View->MaximumScreenSize = VBox->AvailableVramSize - VBoxCrtc->FramebufferOffset;
    HgsmiBufferSubmit(VBox->GuestPool, View);
    HgsmiBufferFree(VBox->GuestPool, View);
    //LouPrint("VBoxSetView() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}


static bool VBoxSetUpInputMapping(PVIRTUALBOX_PRIVATE_DATA VBox){
    PDRSD_CRTC Crtc;
    PDRSD_CONNECTOR Connector;
    BOOL SingleFrameBuffer = true;
    BOOL OldSingleFrameBuffer = VBox->SingleFramebuffer;
    PDRSD_FRAME_BUFFER FrameBuffer = Crtc->PrimaryPlane->FrameBuffer;
    PDRSD_FRAME_BUFFER FrameBuffer1 = 0x00;
    UINT16 Width = 0;
    UINT16 Height = 0;

    ForEachListEntry(Crtc, &VBox->DrsdDevice.ModeConfig.CrtcList, Head){
        FrameBuffer = Crtc->Primary->State->FrameBuffer;
        if(!FrameBuffer){
            continue;
        }
        if(!FrameBuffer1){
            FrameBuffer1 = FrameBuffer;
            if(FrameBuffer1 == VBox->DrsdDevice.FbHelper.FrameBuffer){
                break;
            }
        }else if(FrameBuffer != FrameBuffer1){
            SingleFrameBuffer = false;
        }
    }
    if(!FrameBuffer1){
        return false;
    }

    if(SingleFrameBuffer){
        VBox->SingleFramebuffer = true;
        VBox->InputMappingWidth = FrameBuffer1->Width; 
        VBox->InputMappingHeight = FrameBuffer1->Height; 
        return (VBox->SingleFramebuffer != OldSingleFrameBuffer);
    }    

    ForEachListEntry(Connector, &VBox->DrsdDevice.ModeConfig.ConnectorList, Head){
        PVIRTUALBOX_CONNECTOR VBoxConnector = (PVIRTUALBOX_CONNECTOR)Connector;
        PVIRTUALBOX_CRTC VBoxCrtc = (PVIRTUALBOX_CRTC)VBoxConnector->VBOXCrtc;
        Width = MIN(UINT16_MAX, MAX(Width, VBoxCrtc->XHint + VBoxConnector->ModeHint.Width));
        Width = MIN(UINT16_MAX, MAX(Height, VBoxCrtc->YHint + VBoxConnector->ModeHint.Height));
    }

    VBox->SingleFramebuffer = false;
    VBox->InputMappingWidth = Width;
    VBox->InputMappingHeight = Height;
    return (VBox->SingleFramebuffer != OldSingleFrameBuffer);
}


static void VirtualCrtcSetBaseAndMode(
    PDRSD_CRTC          Crtc,
    PDRSD_FRAME_BUFFER  FrameBuffer,
    int32_t             X,
    int32_t             Y
){
    PDRSD_GXE_VRAM_OBJECT       Gbo = DrsdGxeVramOfGem(FrameBuffer->Objects[0]); 
    PVIRTUALBOX_PRIVATE_DATA    VBox = (PVIRTUALBOX_PRIVATE_DATA)FrameBuffer->Device;
    PVIRTUALBOX_CRTC            VBoxCrtc = (PVIRTUALBOX_CRTC)Crtc;
    BOOLEAN                     NeedsModeSet = DrsdAtomicCrtcNeedsModeset(Crtc->State); 

    MutexLock(&VBox->HardwareMutex);

    if(Crtc->State->Enable){
        VBoxCrtc->Width = Crtc->State->Mode.HorizontalDisplay;
        VBoxCrtc->Height = Crtc->State->Mode.VerticalDisplay;
    }

    VBoxCrtc->X = X;
    VBoxCrtc->Y = Y;
    VBoxCrtc->FramebufferOffset = DrsdGxeVramOffset(Gbo);

    if(NeedsModeSet && (VBoxSetUpInputMapping(VBox))){
        PDRSD_CRTC CrtcIndex;
        ForEachListEntry(CrtcIndex, &VBox->DrsdDevice.ModeConfig.CrtcList, Head){
            if(CrtcIndex == Crtc){
                continue;
            }
            VboxDoModeSet(CrtcIndex);
        }

    }

    VBoxSetView(Crtc);
    VboxDoModeSet(Crtc);

    if(NeedsModeSet){
        HgsmiUpdateInputMappings(VBox->GuestPool, 0, 0, VBox->InputMappingWidth, VBox->InputMappingHeight);
    }

    MutexUnlock(&VBox->HardwareMutex);
    //LouPrint("VirtualCrtcSetBaseAndMode() STATUS_SUCCESS\n");
}

static void VirtualboxCrtcAtomicEnable(
    PDRSD_CRTC          Crtc,
    PDRSD_ATOMIC_STATE  AtomicData
){
}

static void VirtualboxCrtcAtomicDisable(
    PDRSD_CRTC          Crtc,
    PDRSD_ATOMIC_STATE  AtomicData
){
}

static void VirtualboxCrtcAtomicFlush(
    PDRSD_CRTC          Crtc,
    PDRSD_ATOMIC_STATE  AtomicData
){
}

static  DRSD_CRTC_ASSIST_FUNCTIONS VBoxCrtcAssistFunctions = {
    .FlushAtomic = VirtualboxCrtcAtomicFlush,
    .EnableAtomic = VirtualboxCrtcAtomicEnable,
    .DisableAtomic = VirtualboxCrtcAtomicDisable,
};

static void VirtualboxCrtcDestroy(PDRSD_CRTC Crtc){
    DrsdCrtcCleanup(Crtc);
    LouKeFree(Crtc);
}

static DRSD_CRTC_FUNCTIONS VBoxCrtcCallbacks = {
    .Reset = DrsdAtomicHelperCrtcReset,
    .Destroy = VirtualboxCrtcDestroy,
    .SetConfiguration = DrsdAtomicHelperCrtcSetConfiguration,
    .PageFlip = DrsdAtomicHelperPageFlip,
    .AtomicDuplicateState = DrsdAtomicHelperCrtcDuplicateState,
    .AtomicDestroyState = DrsdAtomicHelperCrtcDestroyState,
};

static 
LOUSTATUS 
VirtualboxPrimaryAtomicCheck(
    PDRSD_PLANE         Plane,
    PDRSD_ATOMIC_STATE  State
){
    PDRSD_PLANE_STATE   NewState = DrsdAtomicGetNewPlaneState(State, Plane);
    PDRSD_CRTC_STATE    CrtcState = 0x00;
    if(NewState->Crtc){
        CrtcState = DrsdAtomicGetNewCrtcState(State, NewState->Crtc);
        if(!CrtcState){
            return STATUS_INVALID_PARAMETER;
        }
    }
    return DrsdAtomicHelperCheckPlaneState(
        NewState, CrtcState,
        DRSD_PLANE_NO_SCALING,
        DRSD_PLANE_NO_SCALING,
        false, true
    );
}


static void VirtualboxPrimaryAtomicUpdate(
    PDRSD_PLANE         Plane,
    PDRSD_ATOMIC_STATE  State
){

    PDRSD_PLANE_STATE NewState = DrsdAtomicGetNewPlaneState(State, Plane);
    PDRSD_CRTC Crtc = NewState->Crtc;
    PDRSD_FRAME_BUFFER FrameBuffer = NewState->FrameBuffer;
    PVIRTUALBOX_PRIVATE_DATA Vbox = (PVIRTUALBOX_PRIVATE_DATA)FrameBuffer->Device;
    PDRSD_MODE_RECT Clips;
    UINT32 ClipCount, i;

    VirtualCrtcSetBaseAndMode(
        Crtc, 
        FrameBuffer, 
        NewState->SourceX >> 16,
        NewState->SourceX >> 16
    );

    Clips = DrsdPlaneGetDamageClips(NewState);
    ClipCount = DrsdPlaneGetDamageClipsCount(NewState);

    MutexLock(&Vbox->HardwareMutex);

    for(i = 0 ; i < ClipCount; ++i, ++Clips){
        VBVA_COMMAND_HEADER CommandHeader;
        UINT CrtcID = ((PVIRTUALBOX_CRTC)Crtc)->CrtcId;
        CommandHeader.X = (INT16)Clips->X1;
        CommandHeader.Y = (INT16)Clips->Y1;
        CommandHeader.W = (INT16)(Clips->X2 - Clips->X1);
        CommandHeader.H = (INT16)(Clips->Y2 - Clips->Y1);

        if(!VbvaBufferBeginUpdate(&Vbox->VbvaInformation[CrtcID], Vbox->GuestPool)){
            continue;
        }

        VbvaWrite(&Vbox->VbvaInformation[CrtcID], Vbox->GuestPool, &CommandHeader, sizeof(VBVA_COMMAND_HEADER));
        VbvaBufferEndUpdate(&Vbox->VbvaInformation[CrtcID]);
    }

    MutexUnlock(&Vbox->HardwareMutex);
}

static 
void 
VirtualboxPrimaryAtomicDisable(
    PDRSD_PLANE         Plane,
    PDRSD_ATOMIC_STATE  State
){
    PDRSD_PLANE_STATE OldState = DrsdAtomicGetOldPlaneState(State, Plane);
    PDRSD_CRTC Crtc = OldState->Crtc;
    VirtualCrtcSetBaseAndMode(
        Crtc, OldState->FrameBuffer,
        OldState->SourceX >> 16,
        OldState->SourceY >> 16
    );
}

static LOUSTATUS VirtualboxCursorAtomicCheck(
    PDRSD_PLANE         Plane,
    PDRSD_ATOMIC_STATE  State
){
    PDRSD_PLANE_STATE NewState = DrsdAtomicGetNewPlaneState(State, Plane);
    PDRSD_CRTC_STATE CrtcState = 0x00;
    UINT32 Width = NewState->CrtcWidth;
    UINT32 Height = NewState->CrtcHeight;
    LOUSTATUS Status;

    if(NewState->Crtc){
        CrtcState = DrsdAtomicGetNewCrtcState(State, NewState->Crtc);
        if(!CrtcState){
            return STATUS_INVALID_PARAMETER;
        }
    }

    Status = DrsdAtomicHelperCheckPlaneState(
        NewState, CrtcState,
        DRSD_PLANE_NO_SCALING,
        DRSD_PLANE_NO_SCALING,
        true, true
    );

    if(Status != STATUS_SUCCESS){
        return Status;
    }

    if(!NewState->FrameBuffer){
        return STATUS_SUCCESS;
    }

    if(
        (Width > VIRTUALBOX_MAXIMUM_CURSOR_WIDTH) ||
        (Height > VIRTUALBOX_MAXIMUM_CURSOR_HEIGHT) ||
        (Width == 0) ||
        (Height == 0) 
    ){
        return STATUS_INVALID_PARAMETER;
    }

    return STATUS_SUCCESS;
}

static 
void 
CopyCursorImage(
    UINT8*  Source,
    UINT8*  Destination,
    UINT32  Width,
    UINT32  Height,
    SIZE    MaskSize
){
    SIZE LineSize = (Width + 7) / 8;
    UINT32 i, j;
    
    memcpy(Destination + MaskSize, Source, Width * Height * 4);
    for(i = 0 ; i < Height; ++i){
        for(j = 0;j <Width; ++j){
            if(((UINT32*)Source)[i * Width + j] > 0xF0000000){
                Destination[i * LineSize + j / 8] |= (0x80 >> (j % 8));
            }
        }
    }
}

static 
void 
VirtualboxCursorAtomicUpdate(
    PDRSD_PLANE         Plane,
    PDRSD_ATOMIC_STATE  State
){
    PDRSD_PLANE_STATE NewState = DrsdAtomicGetNewPlaneState(State, Plane);
    PDRSD_PLANE_STATE OldState = DrsdAtomicGetOldPlaneState(State, Plane);
    PVIRTUALBOX_PRIVATE_DATA Vbox = CONTAINER_OF(Plane->Device, VIRTUALBOX_PRIVATE_DATA, DrsdDevice);
    PVIRTUALBOX_CRTC VboxCrtc = (PVIRTUALBOX_CRTC)NewState->Crtc;
    PDRSD_FRAME_BUFFER FrameBuffer = NewState->FrameBuffer;
    UINT32 Width = NewState->CrtcWidth;
    UINT32 Height = NewState->CrtcHeight;
    PDRSD_SHADOW_PLANE_STATE ShadowPlaneState = ToDrsdShadowPlaneState(NewState);
    IO_MAP_OBJECT Map = ShadowPlaneState->Data[0];
    UINT8* Source = (UINT8*)Map.MmIoAddress;
    SIZE DataSize, MaskSize;
    UINT32 Flags;

    if(FrameBuffer == OldState->FrameBuffer){
        return;
    }

    MutexLock(&Vbox->HardwareMutex);

    VboxCrtc->CursorEnabled = true;

    MaskSize = ((Width + 7) / 8 * Height + 3) & ~3;
    DataSize = Width * Height * 4 + MaskSize;

    CopyCursorImage(Source, Vbox->CursorData, Width, Height, MaskSize);

    Flags = VBOX_MOUSE_POINTER_VISABLE | VBOX_MOUSE_POINTER_SHAPE | VBOX_MOUSE_POINTER_ALPHA;
    HgsmiUpdatePointerShape(
        Vbox->GuestPool,
        Flags,
        MIN(MIN(MAX(NewState->HotSpotX, 0), Width), 0xFFFFFFFF),
        MIN(MIN(MAX(NewState->HotSpotY, 0), Height), 0xFFFFFFFF),
        Width,
        Height,
        Vbox->CursorData,
        DataSize
    );
    MutexUnlock(&Vbox->HardwareMutex);
}

static 
void
VirtualboxCursorAtomicDisable(
    PDRSD_PLANE         Plane,
    PDRSD_ATOMIC_STATE  State
){

    PDRSD_PLANE_STATE OldState = DrsdAtomicGetOldPlaneState(State, Plane);
    PVIRTUALBOX_PRIVATE_DATA Vbox = CONTAINER_OF(Plane->Device, VIRTUALBOX_PRIVATE_DATA, DrsdDevice);
    PVIRTUALBOX_CRTC VboxCrtc = (PVIRTUALBOX_CRTC)OldState->Crtc;
    BOOLEAN CursorEnabled = false;
    PDRSD_CRTC Crtci;

    MutexLock(&Vbox->HardwareMutex);

    VboxCrtc->CursorEnabled = false;

    ForEachListEntry(Crtci, &Vbox->DrsdDevice.ModeConfig.CrtcList, Head){
        if(((PVIRTUALBOX_CRTC)Crtci)->CursorEnabled){
            CursorEnabled = true;
        }
    }

    if(!CursorEnabled){
        HgsmiUpdatePointerShape(
            Vbox->GuestPool,
            0,0,0,0,0,0,0
        );
    }

    MutexUnlock(&Vbox->HardwareMutex);
} 

static void* VBoxEdid = 0x00;
static uint32_t PlaneFormats[] = {DRSD_COLOR_FORMAT_XRGB8888, DRSD_COLOR_FORMAT_ARGB8888};
static uint32_t CursorPlaneFormats[] = {DRSD_COLOR_FORMAT_ARGB8888};

static  DRSD_PLANE_ASSIST_FUNCTIONS CursorPlaneAssistFunctions = {
    DRSD_GXE_SHADOW_PLANE_ASSIST_FUNCTIONS,
    .AtomicCheck = VirtualboxCursorAtomicCheck,
    .AtomicUpdate = VirtualboxCursorAtomicUpdate,
    .AtomicDisable = VirtualboxCursorAtomicDisable,
};

static  DRSD_PLANE_FUNCTIONS CursorPlaneFunctions = {
    //.UpdatePlane = DrsdInternalPlaneUpdateAtomic,
    //.DisablePlane = DrsdInternalPlaneDisableAtomic,
    //.Destroy = DrsdInternalDestroyPlaneAtomic,
    //.ResetPlane = DrsdGxeResetShadowPlane,
    //.AtomicDuplicateState = DrsdGxeDuplicateShadowPlaneState,
    //.AtomicDestroyState = DrsdGxeDestroyShadowPlane,
};




static  DRSD_PLANE_ASSIST_FUNCTIONS PlaneAssistedCallbacks = {
    //.PrepareFrameBuffer = DrsdGxeInternalPrepareFrameBuffer,
    //.CleanupFrameBuffer = DrsdGxeInternalCleanupFrameBuffer,
    //.AtomicCheck = VirtualboxPrimaryAtomicCheck,
    //.AtomicUpdate = VirtualboxPrimaryAtomicUpdate,
    //.AtomicSetState = VirtualboxPrimaryAtomicSetState,
};

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

    PDRSD_DISPLAY_MODE NewGenuineMode = 0x00; //DrsdCvtMode(Connector->Device, PreferedWidth, PreferedHeight, 60, false, false, false);
    if(NewGenuineMode){
        NewGenuineMode->Type |= DRSD_MODE_TYPE_PREFERED;
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

static  DRSD_CONNECTOR_ASSIST_FUNCTIONS VirtualboxConnectorAssistFunctions = {
    .GetModes = VirtualboxGetModes,
};

static  DRSD_CONNECTOR_CALLBACKS VirtualboxConnectorCalbacks = {
    .Detect = VirtualboxConnectorDetect,
    .FillModes = VirtualboxFillModes,
    .Destroy = VirtualboxConnectorDestroy,
    .AtomicDuplicateState = DrsdInternalAtomicConnectorDuplicateState,
    .AtomicDestroyState = DrsdInternalAtomicConnectorDestroyState,
};

static void VirtualboxEncoderDestroy(
    PDRSD_ENCODER Encoder
){
    LouPrint("VirtualboxEncoderDestroy()\n");
    while(1);
}

static  DRSD_ENCODER_FUNCTIONS VirtualboxEncoderCallbacks = {
    .Destroy = VirtualboxEncoderDestroy,
};


static void VirtualboxCursorAtomicUpdate(
    PDRSD_PLANE Plane,
    void*       Handle
){
    LouPrint("VirtualboxCursorAtomicUpdate()\n");
    while(1);
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





//disable and enable
static void VirtualboxAtomicSetState(
    PDRSD_PLANE     Plane, 
    void*           State,
    bool            Enable
){
    LouPrint("VirtualboxAtomicSetState()\n");
    while(1);
}





static  DRSD_PLANE_FUNCTIONS PlaneCallbacks = {
    .UpdatePlane = DrsdInternalPlaneUpdateAtomic,
    .DisablePlane = DrsdInternalPlaneDisableAtomic,
    .Destroy = DrsdInternalDestroyPlaneAtomic,
    .ResetPlane = DrsdInternalResetPlane,
    .AtomicDuplicateState = DrsdInternalDuplicateAtomicState,
    .AtomicDestroyState = DrsdInternalDestroyPlaneAtomic,
};

static  DRSD_MODE_CONFIGURATION_CALLBACKS VirtualboxModeCallbacks = {
    /*.FbCreate = DrsdGxeCreateAsyncFramebuffer,
    .ModeValid = DrsdGxeVramInternalModeValid,
    .AtomicCheck = DrsdInternalAtomicCheck,
    .AtomicCommit = DrsdInternalAtomicCommit,*/
};

static PDRSD_PLANE VirtualboxCreatePlane(
    PVIRTUALBOX_PRIVATE_DATA    VBox,
    uint64_t                    CrtcLimit,
    DRSD_PLANE_TYPE             Type
){
    PDRSD_PLANE_ASSIST_FUNCTIONS AssistFunctions = 0x00;
    PDRSD_PLANE_FUNCTIONS Functions = 0x00;
    PDRSD_PLANE NewPlane;
    uint32_t*   Formats;
    size_t      FormatCount;
    LOUSTATUS   Status;

    switch(Type){
        case PRIMARY_PLANE:
            Functions = (PDRSD_PLANE_FUNCTIONS)&PlaneCallbacks;
            AssistFunctions = (PDRSD_PLANE_ASSIST_FUNCTIONS)&PlaneAssistedCallbacks;
            Formats = PlaneFormats;
            FormatCount = ARRAY_SIZE(PlaneFormats);
            break;
        case CURSOR_PLANE:
            Functions = (PDRSD_PLANE_FUNCTIONS)&CursorPlaneFunctions;
            AssistFunctions = (PDRSD_PLANE_ASSIST_FUNCTIONS)&CursorPlaneAssistFunctions;
            Formats = CursorPlaneFormats;
            FormatCount = ARRAY_SIZE(CursorPlaneFormats); 
            break;
        default:
            return 0x00;
    }
    NewPlane = LouKeMallocType(DRSD_PLANE, KERNEL_GENERIC_MEMORY);
    if(!NewPlane){
        return 0x00;
    }

    /*Status = DrsdInitializeGenericPlane(
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
    }*/

    NewPlane->AssistFunctions = AssistFunctions;

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

    /*Status = DrsdInitializeCrtcWithPlanes(
        Device, 
        &VBoxCrtc->Base,
        Primary,
        Cursor,
        (PDRSD_CRTC_FUNCTIONS)&VBoxCrtcCallbacks
    );
    if(Status != STATUS_SUCCESS){
        return 0x00;
    }*/

    //DrsdInitializeCrtcGammaSize(&VBoxCrtc->Base, 256);

    VBoxCrtc->Base.AssistFunctions = (PDRSD_CRTC_ASSIST_FUNCTIONS)&VBoxCrtcAssistFunctions;

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
    /*DrsdInitializeEncoder(
        Device,
        &VBoxEncoder->Base,
        (PDRSD_ENCODER_FUNCTIONS)&VirtualboxEncoderCallbacks,
        DRSD_ENCODER_MODE_DAC, 
        0x00
    );*/
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

    /*DrsdConnectorInitialize(
        Device, 
        &Crtc->Base,
        Connector, 
        (PDRSD_CONNECTOR_CALLBACKS)&VirtualboxConnectorCalbacks, 
        DRSD_CONNECTOR_MODE_VGA
    );*/

    Connector->AssistFunctions = (PDRSD_CONNECTOR_ASSIST_FUNCTIONS)&VirtualboxConnectorAssistFunctions;

    Connector->InterlaceAble = false;
    Connector->DoubleScanAble = false;

    Device->ModeConfig.SuggestedX = 0;
    Device->ModeConfig.SuggestedY = 0;
        
    ((PVIRTUALBOX_CONNECTOR)Connector)->VBOXCrtc = Crtc;

    LouPrint("VirtualboxConnectorInitialize() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS VirtualboxModeInitialization(PVIRTUALBOX_PRIVATE_DATA VBox){
    LouPrint("VirtualboxModeInitialization()\n");
   
    PDRSD_DEVICE Device = &VBox->DrsdDevice;
    PVIRTUALBOX_CRTC VBoxCrtc;
    PDRSD_ENCODER VBoxEncoder;
    LOUSTATUS Result;
   

    DrsdModeConfigInit(Device);

    LouPrint("VirtualboxModeInitialization():STATUS_SUCCESS\n");
    while(1);

    VBox->SingleFramebuffer = true;

    Device->ModeConfig.Callbacks = (PDRSD_MODE_CONFIGURATION_CALLBACKS)&VirtualboxModeCallbacks; 
    Device->ModeConfig.MinimalWidth = 0;
    Device->ModeConfig.MinimalHeight = 0;
    Device->ModeConfig.MaximumWidth = VIRTUALBOX_VBE_DISPI_MAX_XRESOLUTION; 
    Device->ModeConfig.MaximumHeight = VIRTUALBOX_VBE_DISPI_MAX_YRESOLUTION;
    Device->ModeConfig.PreferedDepth = 24;

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

    //DrsdModeConfigReset(Device);

    VBoxEdid = LouKeMalloc(STANDARD_INTEL_CHIPSET_EDID_SIZE, KERNEL_GENERIC_MEMORY);

    return STATUS_SUCCESS;
}

void VirtualBoxModeFaildInitialization(PVIRTUALBOX_PRIVATE_DATA VBox){
    //DrsdModeConfigCleanup(&VBox->DrsdDevice);
}