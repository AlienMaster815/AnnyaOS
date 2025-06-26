#include "DrsdCore.h"

void FillOutInitializationMode(PDRSD_CONNECTOR Connector, PDRSD_PLANE_STATE State, PDRSD_CRTC Crtc){
    //DRSD_MODE_TYPE_PREFERED
    PDRSD_DISPLAY_MODE DisplayMode = (PDRSD_DISPLAY_MODE)Connector->ProbedModes.NextHeader;
    PDRSD_DEVICE Device = Connector->Device;

    while(DisplayMode->Peers.NextHeader){
        if(DisplayMode->ModeType & DRSD_MODE_TYPE_PREFERED){
            break;
        }
        DisplayMode = (PDRSD_DISPLAY_MODE)DisplayMode->Peers.NextHeader;
    }
    //TODO: check for the actuall wandted mode from the registry

    LouPrint("DisplayMode Width : %d\n", DisplayMode->HorizontalDisplay);
    LouPrint("DisplayMode Height: %d\n", DisplayMode->VirticalDisplay);

    State->SourceX = State->SourceX ? State->SourceX : 0; 
    State->SourceY = State->SourceY ? State->SourceY : 0;
    State->Width = DisplayMode->HorizontalDisplay;
    State->Height = DisplayMode->VirticalDisplay;
    State->FrameBuffer = LouKeMallocType(DRSD_FRAME_BUFFER, KERNEL_GENERIC_MEMORY);
    State->FrameBuffer->Device = Device;
    State->FrameBuffer->Width = State->Width;
    State->FrameBuffer->Height = State->Height;
    size_t i;
    for(i = 0; i < State->FormatCount; i++){
        if(strncmp(DRSD_COLOR_FORMAT_XRGB8888, (string)&State->Formats[i] ,4) == 0){
            State->FrameBuffer->Bpp = 32;
            State->FrameBuffer->Pitch = 4 * State->Width;
            State->FrameBuffer->FramebufferSize = State->FrameBuffer->Pitch * State->FrameBuffer->Height;
            State->FormatUsed = DRSD_COLOR_FORMAT_XRGB8888;
            break;
        }
    }
    if(i == State->FormatCount){
        return;// no available mode
    }
    //State->FrameBuffer->

    //use double buffering for now
    uint64_t TmpDmaOffset = 0;
    State->FrameBuffer->FramebufferBase = (uint64_t)LouKeGenricAllocateDmaPool(Device->VramPool, State->FrameBuffer->FramebufferSize * 3, &TmpDmaOffset); 
    State->FrameBuffer->SecondaryFrameBufferBase = State->FrameBuffer->FramebufferBase + State->FrameBuffer->FramebufferSize;
    State->FrameBuffer->TrimaryFrameBufferBase = State->FrameBuffer->FramebufferBase + (State->FrameBuffer->FramebufferSize * 2);
    State->FrameBuffer->Offset = TmpDmaOffset;
    State->Crtc = Crtc;

    memset((void*)State->FrameBuffer->FramebufferBase, 0, State->FrameBuffer->FramebufferSize);

    Crtc->CrtcState->NeedsModeset = true;
    Crtc->CrtcState->Enable = true;
    Crtc->CrtcState->DisplayMode = *DisplayMode;

}

void InitializeModernGraphicsDevice(void* Device){

    PDRSD_DEVICE DrsdDevice = (PDRSD_DEVICE)Device;
    PDRSD_CONNECTOR DrsdConnector = DrsdDevice->Connectors;
    PDRSD_CRTC DrsdCrtc = DrsdDevice->Crtcs;
    PDRSD_PLANE DrsdPlane = DrsdDevice->Planes;
    while(DrsdConnector){
        LouPrint("Initializing Connector:%h\n", DrsdConnector);

        while(DrsdPlane->Peers.NextHeader){
            if(DrsdPlane->PlaneType == PRIMARY_PLANE){
                break;
            }
            DrsdPlane = (PDRSD_PLANE)DrsdPlane->Peers.NextHeader;
        }

        DrsdConnector->ProbeModeCount = DrsdConnector->Callbacks->ConnectorFillModes(
            DrsdConnector, 
            DrsdDevice->ModeConfiguration.MaximumWidth, 
            DrsdDevice->ModeConfiguration.MaximumHeight
        );

        DrsdPlane->PlaneState->Formats = DrsdPlane->Formats;
        DrsdPlane->PlaneState->FormatCount = DrsdPlane->FormatCount;
        
        FillOutInitializationMode(DrsdConnector, DrsdPlane->PlaneState, DrsdCrtc);

        DrsdPlane->FrameBuffer = DrsdPlane->PlaneState->FrameBuffer;


        if(DrsdPlane->AssistCallbacks->AtomicUpdate){
            DrsdPlane->AssistCallbacks->AtomicUpdate(DrsdPlane, DrsdPlane->PlaneState);
        }

        
        DrsdConnector = (PDRSD_CONNECTOR)DrsdConnector->Peers.NextHeader;
        DrsdCrtc = (PDRSD_CRTC)DrsdCrtc->Peers.NextHeader;
        DrsdPlane = (PDRSD_PLANE)DrsdPlane->Peers.NextHeader;
    }

    LouPrint("InitializeModernGraphicsDevice() STATUS_SUCCESS\n");
    
}

UNUSED static PDRSD_DEVICE BootDevice = 0x00;
UNUSED static DRSD_CLIP_CHAIN MasterClipChain = {0};

void LouKeCreateScrollTerminal(PDRSD_CLIP Clip);

PDRSD_CLIP_CHAIN LouKeDrsdAllocateClipChainMember(PDRSD_PLANE Plane) {

    return 0x00;
}

void LouKeDrsdRemoveClipChainMember(PDRSD_PLANE Plane) {

}

PDRSD_CLIP LouKeDrsdCreateClip(PDRSD_PLANE Plane, size_t X, size_t Y, size_t Width, size_t Height, uint8_t R, uint8_t G, uint8_t B, uint8_t A) {

    return 0x00;
}

LOUDDK_API_ENTRY void LouKeDrsdUpdateClipColor(PDRSD_CLIP Clip, uint32_t Color) {

}

LOUDDK_API_ENTRY void LouKeUpdateClipState(PDRSD_CLIP Clip) {

}

LOUDDK_API_ENTRY void LouKeDrsdSyncScreens() {

}


LOUDDK_API_ENTRY 
LOUSTATUS
LouKeDrsdInitializeBootDevice(
    PDRSD_DEVICE Device
){

    BootDevice = Device;
    PDRSD_PLANE Plane = Device->Planes;
        
    PDRSD_CLIP_CHAIN NewChain = LouKeDrsdAllocateClipChainMember(Plane);

    while(1);

    UNUSED PDRSD_CLIP Background = LouKeDrsdCreateClip(
        Plane,
        Plane->PlaneState->SourceX, Plane->PlaneState->SourceY,
        Plane->PlaneState->Width, Plane->PlaneState->Height,
        0, 128, 128, 0
    );

    LouKeUpdateClipState(Background);

    NewChain->PlaneReady = true;

    LouKeDrsdSyncScreens();

    LouKeCreateScrollTerminal(Background);

    LouPrint("LouKeDrsdInitializeBootDevice() STATUS_SUCCESS\n", Plane);
    return STATUS_SUCCESS;
}


LOUDDK_API_ENTRY 
void LouKeDrsdHandleConflictingDevices(P_PCI_DEVICE_OBJECT PDEV){

    LouPrint("LouKeDrsdHandleConflictingDevices()\n");
    while(1);
}

LOUDDK_API_ENTRY
void LouKeOsDosUpdateMapping();

LOUDDK_API_ENTRY
LOUSTATUS
LouKeDrsdInitializeDevice(
    PDRSD_DEVICE Device
){

    
    LouPrint("LouKeDrsdInitializeDevice() STATUS_SUCCESS\n");

    while(1);
    return STATUS_SUCCESS;
}

