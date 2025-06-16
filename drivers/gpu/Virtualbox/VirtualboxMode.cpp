#define _KERNEL_MODULE_
#include <LouDDK.h>
#include "VirtualboxDriver.h"
#include <Hal.h>
#include <drivers/VBoxError.h>

static size_t VirtualboxGetModes(PDRSD_CONNECTOR Connector){
    LouPrint("VirtualboxGetModes()\n");
    while(1);
}

static LOUSTATUS VirtualboxFillModes(
    PDRSD_CONNECTOR Connector, 
    uint32_t MaxX, 
    uint32_t MaxY
){
    LouPrint("VirtualboxFillModes()\n");
    while(1);
    return STATUS_SUCCESS;
}

static DRSD_CONNECTOR_STATUS VirtualboxConnectorDetect(
    PDRSD_CONNECTOR Connector,
    bool            Force
){
    LouPrint("VirtualboxConnectorDetect()\n");
    while(1);
    return (DRSD_CONNECTOR_STATUS)0x00;
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

static void VirtualboxAtomicUpdate(
    PDRSD_PLANE Plane,
    void*       Handle
){
    LouPrint("VirtualboxAtomicUpdate()\n");
    while(1);
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
        Connector, 
        (PDRSD_CONNECTOR_CALLBACKS)&VirtualboxConnectorCalbacks, 
        DRSD_CONNECTOR_MODE_VGA
    );

    Connector->AssistCallbacks = (PDRSD_CONNECTOR_ASSIST_CALLBACKS)&VirtualboxConnectorAssistCallbacks;

    Connector->InterlaceAble = false;
    Connector->DoubleScanAble = false;



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

    return STATUS_SUCCESS;
}