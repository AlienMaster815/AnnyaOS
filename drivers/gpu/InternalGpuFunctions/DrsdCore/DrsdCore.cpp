#include "DrsdCore.h"

/*
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

    State->SourceX = State->SourceX ? State->SourceX : DrsdPlaneInitBase; 
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

    while(1);
    Crtc->CrtcState->NeedsModeset = true;
    Crtc->CrtcState->Enable = true;
    Crtc->CrtcState->DisplayMode = *DisplayMode;

    DrsdPlaneInitBase += DisplayMode->HorizontalDisplay;
}

static void InitializeModernGraphicsDevice(void* Device){

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
*/

static PDRSD_DEVICE BootDevice = 0x00;


typedef struct _DRSD_CLIP{
    ListHeader  Peers;
    ListHeader  Children;
    PDRSD_PLANE Owner;
    size_t      X;
    size_t      Y;
    size_t      Width;
    size_t      Height;
    uint32_t*   WindowBuffer;
    bool        ClipDirty;
}DRSD_CLIP, * PDRSD_CLIP;

typedef struct _DRSD_CLIP_CHAIN{
    ListHeader  Peers;
    PDRSD_PLANE Owner;    
    DRSD_CLIP   Clips;
    bool        PlaneReady;
}DRSD_CLIP_CHAIN, * PDRSD_CLIP_CHAIN;

static DRSD_CLIP_CHAIN MasterClipChain = {0};

static PDRSD_CLIP_CHAIN LouKeDrsdAllocateClipChainMember(PDRSD_PLANE Plane){
    PDRSD_CLIP_CHAIN TmpClip = &MasterClipChain;
    while (TmpClip->Peers.NextHeader){
        TmpClip = (PDRSD_CLIP_CHAIN)TmpClip->Peers.NextHeader;
        if ((!TmpClip->Owner) || (TmpClip->Owner == Plane)){
            TmpClip->Owner = Plane;
            return TmpClip;
        }
    }
    TmpClip->Peers.NextHeader = (PListHeader)LouKeMallocType(DRSD_CLIP_CHAIN, KERNEL_GENERIC_MEMORY);
    PDRSD_CLIP_CHAIN NewChain = (PDRSD_CLIP_CHAIN)TmpClip->Peers.NextHeader;
    NewChain->Peers.LastHeader = (PListHeader)TmpClip;
    NewChain->Owner = Plane;
    NewChain->PlaneReady = false;
    return NewChain;
}
static PDRSD_CLIP LouKeDrsdCreateClip(
    PDRSD_PLANE Plane,
    size_t X, size_t Y, 
    size_t Width, size_t Height,
    uint8_t R, uint8_t G, uint8_t B, uint8_t A
){
    PDRSD_CLIP NewClip = LouKeMallocType(DRSD_CLIP, USER_GENERIC_MEMORY);
    NewClip->WindowBuffer = (uint32_t*)LouKeMallocEx(sizeof(uint32_t) * (Width * Height), GET_ALIGNMENT(uint32_t), USER_GENERIC_MEMORY);
    NewClip->X = X;
    NewClip->Y = Y;
    NewClip->Width = Width;
    NewClip->Height = Height;
    NewClip->Owner = Plane;
    PDRSD_CLIP_CHAIN TmpChain = &MasterClipChain;
    bool ChainFound = false;
    while (TmpChain){
        if (TmpChain->Owner == Plane){
            ChainFound = true;
            break;
        }
        TmpChain = (PDRSD_CLIP_CHAIN)TmpChain->Peers.NextHeader;
    }
    if (!ChainFound){
        TmpChain = LouKeDrsdAllocateClipChainMember(Plane);
    }
    uint32_t Color = (A << 24) | (R << 16) | (G << 8) | B;
    for (size_t y = 0; y < Height; y++){
        for (size_t x = 0; x < Width; x++){
            NewClip->WindowBuffer[x + (y * Width)] = Color;
        }
    }
    return NewClip;
}

LOUDDK_API_ENTRY
void LouKeUpdateClipState(PDRSD_CLIP Clip){
    uint32_t* Fb = (uint32_t*)Clip->Owner->FrameBuffer->SecondaryFrameBufferBase;
    uint32_t* Cb = Clip->WindowBuffer;
    size_t X = Clip->X;
    size_t Y = Clip->Y;
    size_t Width = Clip->Width;
    size_t Height = Clip->Height;

    for(size_t y = 0; y < Height; y++){
        for(size_t x = 0 ; x < Width; x++){
            Fb[(x + X) + ((y + Y) * Width)] = Cb[x + (y * Width)];
        }
    }   
}

LOUDDK_API_ENTRY
void LouKeDrsdSyncScreens(){
    PDRSD_CLIP_CHAIN TmpChain = &MasterClipChain;

    while (TmpChain){
        if (TmpChain->PlaneReady){
            uint32_t* Fb1 = (uint32_t*)TmpChain->Owner->FrameBuffer->FramebufferBase;
            uint32_t* Fb2 = (uint32_t*)TmpChain->Owner->FrameBuffer->SecondaryFrameBufferBase;
            size_t FbSize = TmpChain->Owner->FrameBuffer->FramebufferSize;
            FbSize /= sizeof(uint32_t);
            
            for (size_t i = 0; i < FbSize; i++){
                Fb1[i] = Fb2[i];
            }
        }
        TmpChain = (PDRSD_CLIP_CHAIN)TmpChain->Peers.NextHeader;
    }
}

LOUDDK_API_ENTRY 
LOUSTATUS
LouKeDrsdInitializeBootDevice(
    PDRSD_DEVICE Device
){

    BootDevice = Device;
    PDRSD_PLANE Plane = Device->Planes;
    
    PDRSD_CLIP_CHAIN NewChain = LouKeDrsdAllocateClipChainMember(Plane);

    UNUSED PDRSD_CLIP Background = LouKeDrsdCreateClip(
        Plane,
        Plane->PlaneState->SourceX, Plane->PlaneState->SourceY,
        Plane->PlaneState->Width, Plane->PlaneState->Height,
        0, 128, 128, 0
    );

    LouKeUpdateClipState(Background);

    NewChain->PlaneReady = true;

    LouKeDrsdSyncScreens();

    LouPrint("LouKeDrsdInitializeBootDevice() STATUS_SUCCESS\n", Plane);
    return STATUS_SUCCESS;
}


LOUDDK_API_ENTRY
LOUSTATUS
LouKeDrsdInitializeDevice(
    PDRSD_DEVICE Device
){
    BootDevice = 0x00;


    LouPrint("LouKeDrsdInitializeDevice()\n");

    while(1);
    return STATUS_SUCCESS;
}