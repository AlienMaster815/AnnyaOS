#include "DrsdCore.h"


KERNEL_IMPORT
LOUSTATUS LouKePassVramToDrsdMemoryManager(PDRSD_DEVICE Device, void* VramBase, size_t size, void* PAddress){

    Device->VramPool = LouKeCreateGenericPool((uint64_t)VramBase, (uint64_t)PAddress, size , 0);

    return STATUS_SUCCESS;
}

KERNEL_IMPORT
PDRSD_FRAME_BUFFER DrsdGxeCreateAsyncFramebuffer(
    PDRSD_DEVICE    Device,
    void*           DrsdBuffer,
    void*           DrsdCommandBuffer
){

    LouPrint("DrsdGxeCreateAsyncFramebuffer()\n");
    while(1);
    return 0x00;
}

KERNEL_IMPORT
DRSD_MODE_STATUS DrsdGxeVramInternalModeValid(
    PDRSD_DEVICE        Device,
    PDRSD_DISPLAY_MODE  DisplayMode
){

    LouPrint("DrsdGxeVramInternalModeValid()\n");
    while(1);
    return DRSD_MODE_OK;
}

KERNEL_IMPORT
LOUSTATUS DrsdInternalAtomicCheck(
    PDRSD_DEVICE        Device,
    void*               AtomicHandle
){
    LouPrint("DrsdInternalAtomicCheck()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_IMPORT
LOUSTATUS DrsdInternalAtomicUpdate(
    PDRSD_DEVICE        Device,
    void*               AtomicHandle,
    bool                NonBlock
){

    LouPrint("DrsdInternalAtomicUpdate()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_IMPORT
LOUSTATUS DrsdInternalPlaneUpdateAtomic(
    PDRSD_PLANE                     Plane,
    PDRSD_CRTC                      Crtc,
    PDRSD_FRAME_BUFFER              FrameBuffer,
    int                             CrtcX, 
    int                             CrctY, 
    int                             CrtcWidth, 
    int                             CrtcHeight,
    uint32_t                        SourceX, 
    uint32_t                        SourceY, 
    uint32_t                        SourceWidth, 
    uint32_t                        SourceHeight,
    struct _DRSD_MODE_SET_CONTEXT*  ModeSetAquireContext
){
    LouPrint("DrsdInternalPlaneUpdateAtomic()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_IMPORT
LOUSTATUS DrsdInternalPlaneDisableAtomic(
    PDRSD_PLANE                     Plane,
    struct _DRSD_MODE_SET_CONTEXT*  ModeSetAquireContext            
){
    LouPrint("DrsdInternalPlaneDisableAtomic()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_IMPORT
void DrsdInternalDestroyPlane(
    PDRSD_PLANE Plane
){

    LouPrint("DrsdInternalDestroyPlane()\n");
    while(1);
}



KERNEL_IMPORT
void DrsdInternalResetPlane(
    PDRSD_PLANE Plane
){

    if(Plane->PlaneState){
        DrsdAtomicDestroyPlaneState(Plane->PlaneState);
        LouKeFree(Plane->PlaneState);
    }

    Plane->PlaneState = LouKeMallocType(DRSD_PLANE_STATE, KERNEL_GENERIC_MEMORY);
    if(!Plane->PlaneState){
        return;
    }

    Plane->PlaneState->Rotation = DRSD_ROTATION_MODE_0;
    Plane->PlaneState->PixelBlend = DRSD_PIXEL_BLEND_PRE_MULTI;

    if(Plane->ColorEncodingProperty){
        LouPrint("DrsdInternalResetPlane():ColorEncodingProperty\n");
    }
    if(Plane->ColorRangeProperty){
        LouPrint("DrsdInternalResetPlane():ColorRangeProperty\n");
        while(1);   
    }
    if(Plane->ZPositionProperty){
        LouPrint("DrsdInternalResetPlane():ZPositionProperty\n");
        while(1);   
    }
    if(Plane->HotSpotXProperty){
        LouPrint("DrsdInternalResetPlane():HotSpotXProperty\n");
        while(1);   
    }
    if(Plane->HotSpotYProperty){
        LouPrint("DrsdInternalResetPlane():HotSpotYProperty\n");
        while(1);   
    }
    LouPrint("DrsdInternalResetPlane() STATUS_SUCCESS\n");
}

KERNEL_IMPORT
PDRSD_PLANE_STATE DrsdInternalDuplicateAtomicState(
    PDRSD_PLANE         Plane
){

    LouPrint("DrsdInternalDuplicateAtomicState()\n");
    while(1);
    return 0x00;
}

KERNEL_IMPORT
void DrsdInternalDestroyPlaneAtomic(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
){

    LouPrint("DrsdInternalDestroyPlaneAtomic()\n");
    while(1);
}

KERNEL_IMPORT
LOUSTATUS DrsdGxeInternalPrepareFrameBuffer(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
){

    LouPrint("DrsdGxeInternalPrepareFrameBuffer()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_IMPORT
void DrsdGxeInternalCleanupFrameBuffer(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
){
    LouPrint("DrsdGxeInternalCleanupFrameBuffer()\n");
    while(1);
}

KERNEL_IMPORT
LOUSTATUS DrsdGxeInternalStartFrameBufferProcessing(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
){
    LouPrint("DrsdGxeInternalStartFrameBufferProcessing()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_IMPORT
void DrsdGxeInternalStopFrameBufferProcessing(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
){
    LouPrint("DrsdGxeInternalStopFrameBufferProcessing()\n");
    while(1);
}

KERNEL_IMPORT
void DrsdGxeResetShadowPlane(
    PDRSD_PLANE         Plane
){

    if(Plane->PlaneState){
        DrsdGxeDestroyShadowPlane(Plane);
    }    
    Plane->PlaneState = (PDRSD_PLANE_STATE)LouKeMallocType(SHADOW_PLANE_STATE, KERNEL_GENERIC_MEMORY);
    if(!Plane->PlaneState){
        return;
    }
    DrsdInternalResetPlane(Plane);
    LouPrint("DrsdGxeResetShadowPlane() STATUS_SUCCESS\n");
}

KERNEL_IMPORT
PDRSD_PLANE_STATE DrsdGxeDuplicateShadowPlaneState(
    PDRSD_PLANE Plane
){

    LouPrint("DrsdGxeDuplicateShadowPlaneState()\n");
    while(1);
    return 0x00;
}

KERNEL_IMPORT
void DrsdGxeDestroyShadowPlane(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
){
    LouPrint("DrsdGxeDestroyShadowPlane()\n");
    while(1);
}



KERNEL_EXPORT
LOUSTATUS DrsdInitializeCrtcWithPlanes(
    PDRSD_DEVICE            Device,
    PDRSD_CRTC              Crtc,
    PDRSD_PLANE             Primary,
    PDRSD_PLANE             Cursor,
    PDRSD_CRTC_CALLBACK     CrtcCallbacks
){
  
    Device->CrtcCount++;
    Crtc->CrtcCallbacks = CrtcCallbacks;
    Crtc->Device = Device;

    AddVBlankToCrtc(Device);

    Primary->Crtc = Crtc;
    Cursor->Crtc = Crtc;
    Crtc->PrimaryPlane = Primary;
    Crtc->CursorPlane = Cursor;

    PDRSD_CRTC Tmp = Device->Crtcs;
    if(!Tmp){
        Device->Crtcs = Crtc;
    }else{
        while(Tmp->Peers.NextHeader){
            Tmp = (PDRSD_CRTC)Tmp->Peers.NextHeader;
        }
        Tmp->Peers.NextHeader = (PListHeader)Crtc;
    }
    LouPrint("DrsdInitializeCrtcWithPlanes() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS DrsdInitializeCrtcGammaSize(
    PDRSD_CRTC  Crtc,
    size_t      GammaSize
){

    if(GammaSize > 256){
        LouPrint("DrsdInitializeCrtcGammaSize() STATUS_INVALID_PARAMETER");
        return STATUS_INVALID_PARAMETER;
    }

    uint16_t* Red;
    uint16_t* Green; 
    uint16_t* Blue;

    Crtc->GammaSize = GammaSize;
    Crtc->GammaStore = LouKeMallocArray(uint16_t, GammaSize * 3, KERNEL_GENERIC_MEMORY);

    Red     = Crtc->GammaStore;
    Green   = (uint16_t*)(uint8_t*)((uint64_t)Red + (uint64_t)GammaSize);
    Blue    = (uint16_t*)(uint8_t*)((uint64_t)Green + (uint64_t)GammaSize);
    for(size_t i = 0; i < GammaSize; i++){
        Red[i]      = (i << 8);
        Green[i]    = (i << 8);
        Blue[i]     = (i << 8);
    }
    LouPrint("DrsdInitializeCrtcGammaSize() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS DrsdInternalCrtcSetConfigurationAtomic(
    void*                            Mode,
    struct _DRSD_MODE_SET_CONTEXT*   ModeSetAquireContext
){
    LouPrint("DrsdInternalSetConfigurationAtomic()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS DrsdInternalCrtcPageFlipAtomic(
    PDRSD_CRTC                      Crtc,
    PDRSD_FRAME_BUFFER              FrameBuffer,
    void*                           VBlankEvent,
    uint32_t                        Flags,
    struct _DRSD_MODE_SET_CONTEXT*  ModeSetAquireContext
){
    LouPrint("DrsdinternalPageFlipAtomic()\n");
    while(1);
    return STATUS_SUCCESS;
}

void DrsdInternalCrtcResetAtomic(
    PDRSD_CRTC          Crtc 
){
    if(Crtc->CrtcState){
        Crtc->CrtcCallbacks->AtomicDestroyState(Crtc, Crtc->CrtcState);
    }
    Crtc->CrtcState = LouKeMallocType(DRSD_CRTC_STATE, KERNEL_GENERIC_MEMORY);
    Crtc->CrtcState->Crtc = Crtc;
    if(Crtc->Device->CrtcCount){
        DrsdResetCrtcVBlank(
            Crtc
        );
    }
    LouPrint("DrsdInternalCrtcResetAtomic() STATUS_SUCCESS\n");
}

void* DrsdInternalCrtcDuplicateStateAtomic(
    PDRSD_CRTC          Crtc
){
    LouPrint("DrsdInternalCrtcDuplicateStateAtomic()\n");
    while(1);
    return 0x00;
}

void DrsdInternalCrtcDestroyStateAtomic(
    PDRSD_CRTC  Crtc,
    void*       StateData
){
    LouPrint("DrsdInternalCrtcDestroyStateAtomic()\n");
    while(1);
}

LOUSTATUS DrsdInitializeEncoder(
    PDRSD_DEVICE                Device,
    PDRSD_ENCODER               Encoder,
    PDRSD_ENCODER_CALLBACKS     Callbacks,
    int                         EncoderType,
    string                      EncoderName,
    ...
){
    Encoder->Device = Device;
    Encoder->Callbacks = Callbacks;
    Encoder->EncoderType = EncoderType;
    Encoder->EncoderName = EncoderName;

    PDRSD_ENCODER Tmp = Device->Encoders;
    if(!Tmp){
        Device->Encoders = Encoder;
    }else{
        while(Tmp->Peers.NextHeader){
            Tmp = (PDRSD_ENCODER)Tmp->Peers.NextHeader;
        }
        Tmp->Peers.NextHeader = (PListHeader)Encoder;
    }

    LouPrint("DrsdInitializeEncoder() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

void DrsdInternalResetConnector(PDRSD_CONNECTOR Connector){

    LouPrint("DrsdInternalResetConnector()\n");
    while(1);
}

PDRSD_CONNECTOR_STATE DrsdInternalAtomicConnectorDuplicateState(PDRSD_CONNECTOR Connector){
    LouPrint("DrsdInternalAtomicConnectorDuplicateState()\n");
    while(1);
    return 0x00;
}

void DrsdInternalAtomicConnectorDestroyState(
    PDRSD_CONNECTOR         Connector,
    PDRSD_CONNECTOR_STATE   State
){
    LouPrint("DrsdInternalAtomicConnectorDestroyState()\n");
    while(1);
}

LOUSTATUS DrsdConnectorInitialize(
    PDRSD_DEVICE                Device,
    PDRSD_CRTC                  Crtc,
    PDRSD_CONNECTOR             Connector,
    PDRSD_CONNECTOR_CALLBACKS   Callbacks,
    int                         ConnectorType
){

    Connector->Device = Device;
    Connector->Callbacks = Callbacks;
    Connector->CType = ConnectorType;
    Connector->Crtc = Crtc; 

    PDRSD_CONNECTOR Tmp = Device->Connectors;
    if(!Tmp){
        Device->Connectors = Connector;
    }else{
        while(Tmp->Peers.NextHeader){
            Tmp = (PDRSD_CONNECTOR)Tmp->Peers.NextHeader;
        }
        Tmp->Peers.NextHeader = (PListHeader)Connector;
    }
    LouPrint("DrsdConnectorInitialize() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

void DrsdModeConfigurationReset(PDRSD_DEVICE Device){

    PDRSD_PLANE Plane = Device->Planes;
    PDRSD_CRTC  Crtc = Device->Crtcs;
    PDRSD_ENCODER Encoder = Device->Encoders;
    PDRSD_CONNECTOR Connector = Device->Connectors;

    while(Plane){
        if(Plane->Callbacks->ResetPlane){
            Plane->Callbacks->ResetPlane(Plane);
        }
        Plane = (PDRSD_PLANE)Plane->Peers.NextHeader;
    }

    while(Crtc){
        if(Crtc->CrtcCallbacks->ResetCrtc){
            Crtc->CrtcCallbacks->ResetCrtc(Crtc);
        }
        Crtc = (PDRSD_CRTC)Crtc->Peers.NextHeader;
    }   

    while(Encoder){
        if(Encoder->Callbacks->ResetEncoder){
            Encoder->Callbacks->ResetEncoder(Encoder);
        }
        Encoder = (PDRSD_ENCODER)Encoder->Peers.NextHeader;
    }

    while(Connector){
        if(Connector->Callbacks->ResetConnector){
            Connector->Callbacks->ResetConnector(Connector);
        }
        Connector = (PDRSD_CONNECTOR)Connector->Peers.NextHeader;
    }
    LouPrint("DrsdModeConfigurationReset() STATUS_SUCCESS\n");
}

PDRSD_PLANE_STATE DrsdGetNewPlaneState(PDRSD_PLANE_STATE OldState, PDRSD_PLANE Plane){



    LouPrint("DrsdGetNewPlaneState()\n");
    while(1);
    return 0x00;
}