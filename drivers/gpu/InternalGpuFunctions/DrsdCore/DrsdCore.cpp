#include "DrsdCore.h"

static PDRSD_DEVICE BootDevice = 0x00;
static DRSD_CLIP_CHAIN MasterClipChain = {0};
static mutex_t ClipLock = {0};
static size_t PlaneCount = 0;

static void FillOutInitializationMode(PDRSD_CONNECTOR Connector, PDRSD_PLANE_STATE State, PDRSD_CRTC Crtc){
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

    memset((void*)State->FrameBuffer->FramebufferBase, 0, State->FrameBuffer->FramebufferSize * 3);

    Crtc->CrtcState->NeedsModeset = true;
    Crtc->CrtcState->Enable = true;
    Crtc->CrtcState->DisplayMode = *DisplayMode;

}

PDRSD_CLIP_CHAIN LouKeDrsdAcquireClipChainMember(PDRSD_PLANE Plane) {
    MutexLock(&ClipLock);
    PDRSD_CLIP_CHAIN TmpChain = &MasterClipChain;
    while(TmpChain->Peers.NextHeader){
        TmpChain = (PDRSD_CLIP_CHAIN)TmpChain->Peers.NextHeader;
        if(Plane == TmpChain->Owner){
            TmpChain->PlaneReady = true; 
            MutexUnlock(&ClipLock);
            return TmpChain;
        }
    }
    TmpChain->Peers.NextHeader = (PListHeader)LouKeMallocType(DRSD_CLIP_CHAIN, USER_GENERIC_MEMORY); 
    TmpChain = (PDRSD_CLIP_CHAIN)TmpChain->Peers.NextHeader;
    TmpChain->Owner = Plane;
    TmpChain->PlaneReady = true; 
    PlaneCount++;
    MutexUnlock(&ClipLock);
    return TmpChain;
}

void LouKeDrsdRemoveClipChainMember(PDRSD_PLANE Plane) {
    MutexLock(&ClipLock);
    PDRSD_CLIP_CHAIN TmpChain = &MasterClipChain;
    PDRSD_CLIP_CHAIN TrailChain;
    while(TmpChain->Peers.NextHeader){
        TrailChain = TmpChain; 
        TmpChain = (PDRSD_CLIP_CHAIN)TmpChain->Peers.NextHeader;
        if(Plane == TmpChain->Owner){
            TmpChain->PlaneReady = false;
            TrailChain->Peers.NextHeader = TmpChain->Peers.NextHeader;
            PDRSD_CLIP Clips = TmpChain->Clips; 
            while(Clips){
                if(Clips->SignalClipChange){
                    Clips->SignalClipChange(Clips, CLIP_DESTROYED, 0x00);
                }
                Clips = (PDRSD_CLIP)Clips->Peers.NextHeader;
            }
            Clips = TmpChain->Clips; 
            PDRSD_CLIP TrailClip;
            while(Clips){
                TrailClip = Clips;
                Clips = (PDRSD_CLIP)Clips->Peers.NextHeader; 
                LouKeFree(TrailClip);
            }
            LouKeFree(TmpChain);
            PlaneCount--;
            MutexUnlock(&ClipLock);
            return;
        }
    }
    MutexUnlock(&ClipLock);
}


LOUDDK_API_ENTRY
PDRSD_CLIP LouKeDrsdCreateClip(
    PDRSD_PLANE Plane, 
    size_t X, size_t Y, 
    size_t Width, size_t Height, 
    uint8_t R, uint8_t G, uint8_t B, uint8_t A
) {
    PDRSD_CLIP_CHAIN PlaneChain = LouKeDrsdAcquireClipChainMember(Plane);
    PDRSD_CLIP ClipQueue;
    if(!PlaneChain->Clips){
        PlaneChain->Clips = LouKeMallocType(DRSD_CLIP, USER_GENERIC_MEMORY);
        ClipQueue = PlaneChain->Clips;
    }else {
        ClipQueue = PlaneChain->Clips;
        while(ClipQueue->Peers.NextHeader){
            ClipQueue = (PDRSD_CLIP)ClipQueue->Peers.NextHeader;
        }
        ClipQueue->Peers.NextHeader = (PListHeader)LouKeMallocType(DRSD_CLIP, USER_GENERIC_MEMORY);
        ClipQueue = (PDRSD_CLIP)ClipQueue->Peers.NextHeader;
    }
    //add next queue member
    //fill the new clip information out

    LouPrint("Chain:%h\n", PlaneChain);
    LouPrint("Plane:%h\n", Plane);
    LouPrint("Clip:%h\n", ClipQueue);
    LouPrint("X:%d\n", X);
    LouPrint("Y:%d\n", Y);
    LouPrint("Width:%d\n", Width);
    LouPrint("Height:%d\n", Height);

    ClipQueue->WindowBuffer = LouKeMallocArray(uint32_t, Width * Height, USER_GENERIC_MEMORY);
    ClipQueue->X = X;
    ClipQueue->Y = Y;
    ClipQueue->Width = Width;
    ClipQueue->Height = Height;
    ClipQueue->Owner = Plane;
    ClipQueue->ChainOwner = PlaneChain;
    uint32_t Color = DRSD_CORE_TRANSLATE_COLOR(R,G,B,A);
    for(size_t Ty = 0; Ty < Height; Ty++){
        for(size_t Tx = 0; Tx < Width; Tx++){
            ClipQueue->WindowBuffer[Tx + (Ty * Width)] = Color;
        }
    }
    return ClipQueue;
}

LOUDDK_API_ENTRY void LouKeDestroyClip(PDRSD_CLIP Clip){
    MutexLock(&ClipLock);
    PDRSD_CLIP_CHAIN PlaneChain = Clip->ChainOwner;
    PDRSD_CLIP TmpClip = PlaneChain->Clips;
    PDRSD_CLIP TrailTmpClip = TmpClip;
    while(TmpClip){
        if(TmpClip == Clip){
            TrailTmpClip->Peers.NextHeader = Clip->Peers.NextHeader;
            MutexUnlock(&ClipLock);
            LouKeFree(Clip->WindowBuffer);
            LouKeFree(Clip);
            return;
        }
        TrailTmpClip = TmpClip;
        TmpClip = (PDRSD_CLIP)TmpClip->Peers.NextHeader;
    }
    MutexUnlock(&ClipLock);
}

LOUDDK_API_ENTRY void LouKeDrsdUpdateClipColor(PDRSD_CLIP Clip, uint32_t Color) {
    size_t Width = Clip->Width;
    size_t Height = Clip->Height;
    for(size_t Ty = 0; Ty < Height; Ty++){
        for(size_t Tx = 0; Tx < Width; Tx++){
            Clip->WindowBuffer[Tx + (Ty * Width)] = Color;   
        }
    }
}

LOUDDK_API_ENTRY void LouKeUpdateClipState(PDRSD_CLIP Clip) {
    size_t X = Clip->X;
    size_t Y = Clip->Y;
    size_t Width = Clip->Width;
    size_t Height = Clip->Height;
    size_t FbWidth = Clip->Owner->FrameBuffer->Width;
    uint32_t* Fb2 = (uint32_t*)Clip->Owner->FrameBuffer->SecondaryFrameBufferBase;
    uint32_t* Cb = Clip->WindowBuffer;
    for(size_t Ty = 0; Ty < Height; Ty++){
        for(size_t Tx = 0 ; Tx < Width; Tx++){
            Fb2[(Tx + X) + ((Ty + Y) * FbWidth)] = Cb[Tx + (Ty * Width)];
        }
    }
}

LOUDDK_API_ENTRY void LouKeDrsdSyncScreen(PDRSD_CLIP_CHAIN Chain){
    void* Fb1;
    void* Fb2;
    size_t Size;
    if(Chain->PlaneReady == true){
        Fb1 = (void*)Chain->Owner->FrameBuffer->FramebufferBase;
        Fb2 = (void*)Chain->Owner->FrameBuffer->SecondaryFrameBufferBase;
        Size = Chain->Owner->FrameBuffer->FramebufferSize;
        memcpy(Fb1, Fb2, Size);
        if(Chain->PrimaryAtomicUpdate){
            Chain->PrimaryAtomicUpdate(Chain->Owner, Chain->Owner->PlaneState);
        }
    }
    sleep(1);
}

void LouKeCreateScrollTerminal(PDRSD_CLIP Clip);

LOUDDK_API_ENTRY 
LOUSTATUS
LouKeDrsdInitializeBootDevice(
    PDRSD_DEVICE Device
){
    BootDevice = Device;
    PDRSD_PLANE Plane = Device->Planes;
        
    PDRSD_CLIP_CHAIN Chain = LouKeDrsdAcquireClipChainMember(Plane);

    PDRSD_CLIP Background = LouKeDrsdCreateClip(
        Plane,
        Plane->PlaneState->SourceX, Plane->PlaneState->SourceY,
        Plane->PlaneState->Width, Plane->PlaneState->Height,
        0, 128, 128, 255
    );


    LouKeUpdateClipState(Background);

    LouKeDrsdSyncScreen(Chain);
    LouPrint("LouKeDrsdInitializeBootDevice() STATUS_SUCCESS\n");

    LouKeCreateScrollTerminal(Background);

    return STATUS_SUCCESS;
}


LOUDDK_API_ENTRY 
void LouKeDrsdHandleConflictingDevices(P_PCI_DEVICE_OBJECT PDEV){

    if(BootDevice){
        LouKeDrsdRemoveClipChainMember(BootDevice->Planes);
        BootDevice = 0x00;
    }


    LouPrint("LouKeDrsdHandleConflictingDevices() STATUS_SUCCESS\n");
}

LOUDDK_API_ENTRY
void LouKeOsDosUpdateMapping();

LOUDDK_API_ENTRY
LOUSTATUS
LouKeDrsdInitializeDevice(
    PDRSD_DEVICE Device
){
    PDRSD_CONNECTOR Connector = Device->Connectors;
    PDRSD_CRTC Crtc = 0x00;
    PDRSD_PLANE PrimaryPlane = 0x00;
    while(Connector){
        LouPrint("Configuring Connector:%h\n", Connector);
        
        Connector->ProbeModeCount = Connector->Callbacks->ConnectorFillModes(
            Connector, 
            Device->ModeConfiguration.MaximumWidth, 
            Device->ModeConfiguration.MaximumHeight
        );

        Crtc = Connector->Crtc;
        PrimaryPlane = Crtc->PrimaryPlane;

        PrimaryPlane->PlaneState->Formats = PrimaryPlane->Formats;
        PrimaryPlane->PlaneState->FormatCount = PrimaryPlane->FormatCount;

        FillOutInitializationMode(Connector, PrimaryPlane->PlaneState, Crtc);

        PrimaryPlane->FrameBuffer = PrimaryPlane->PlaneState->FrameBuffer;

        if(PrimaryPlane->AssistCallbacks->AtomicUpdate){
            PrimaryPlane->AssistCallbacks->AtomicUpdate(PrimaryPlane, PrimaryPlane->PlaneState);
        }

        Crtc->CrtcState->NeedsModeset = false;

        
        PDRSD_CLIP_CHAIN Chain = LouKeDrsdAcquireClipChainMember(PrimaryPlane);
        Chain->PrimaryAtomicUpdate = PrimaryPlane->AssistCallbacks->AtomicUpdate;
        UNUSED PDRSD_CLIP Background = LouKeDrsdCreateClip(
            PrimaryPlane,
            PrimaryPlane->PlaneState->SourceX, PrimaryPlane->PlaneState->SourceY,
            PrimaryPlane->PlaneState->Width, PrimaryPlane->PlaneState->Height,
            0, 128, 128, 255
        );

        LouKeUpdateClipState(Background);
        
        LouKeDrsdSyncScreen(Chain);

        LouKeCreateScrollTerminal(Background);

        LouPrint("Connector:%h Successfully Configured\n", Connector);

        Connector = (PDRSD_CONNECTOR)Connector->Peers.NextHeader;
    }

    LouPrint("LouKeDrsdInitializeDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

typedef struct _DRSD_PLANE_QUERY_INFORMATION{
    uintptr_t           Plane;
    uintptr_t           Chain;
    size_t              X;
    size_t              Y;
    size_t              Width;
    size_t              Height;
}DRSD_PLANE_QUERY_INFORMATION, * PDRSD_PLANE_QUERY_INFORMATION;


LOUDDK_API_ENTRY
void* LouDrsdGetPlaneInformation(size_t* CountHandle){
    *CountHandle = PlaneCount;
    MutexLock(&ClipLock);
    PDRSD_PLANE_QUERY_INFORMATION Query = LouKeMallocArray(DRSD_PLANE_QUERY_INFORMATION, PlaneCount, USER_GENERIC_MEMORY);

    PDRSD_CLIP_CHAIN Tmp = &MasterClipChain;
    size_t i = 0;
    while(Tmp->Peers.NextHeader){
        Tmp = (PDRSD_CLIP_CHAIN)Tmp->Peers.NextHeader;

        Query[i].Plane = (uintptr_t)Tmp->Owner;
        Query[i].Chain = (uintptr_t)Tmp;
        Query[i].X = Tmp->Owner->PlaneState->SourceX;
        Query[i].Y = Tmp->Owner->PlaneState->SourceY;
        Query[i].Width = Tmp->Owner->PlaneState->Width;
        Query[i].Height = Tmp->Owner->PlaneState->Height;

        i++;
    }
    MutexUnlock(&ClipLock);
    return (void*)Query;
}