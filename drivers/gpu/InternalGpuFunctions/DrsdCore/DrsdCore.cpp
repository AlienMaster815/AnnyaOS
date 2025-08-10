#include "DrsdCore.h"

static PDRSD_DEVICE BootDevice = 0x00;
static DRSD_PLANE_CHAIN MasterPlaneChain = {0};
static mutex_t PlaneLock = {0};
static size_t PlaneCount = 0;

UNUSED static void CalculateNextUpdate(PDRSD_PLANE Plane, size_t X, size_t Y, size_t Width, size_t Height){
    size_t Right = X + Width;
    size_t Bottom = Y + Height;
    if(!Plane->IsDirty){
        Plane->DirtyX = X;
        Plane->DirtyY = Y;
        Plane->DirtyWidth = Width;
        Plane->DirtyHeight = Height;
        Plane->IsDirty = true;
    }else{
        size_t DirtyRight = Plane->DirtyX + Plane->DirtyWidth;
        size_t DirtyBottom = Plane->DirtyY + Plane->DirtyHeight;
        if(X < Plane->DirtyX){
            Plane->DirtyX = X;
        }
        if(Y < Plane->DirtyY){
            Plane->DirtyY = Y;
        }
        if(Right > DirtyRight){
            DirtyRight = Right;
        }
        if(Bottom > DirtyBottom){
            DirtyBottom = Bottom;
        }
        Plane->DirtyWidth = DirtyRight - Plane->DirtyX;
        Plane->DirtyHeight = DirtyBottom - Plane->DirtyY;
    }
}


UNUSED static void DrsdFbDoUpdate(
    PDRSD_PLANE Plane
){
    uint32_t* Fb1 = (uint32_t*)Plane->FrameBuffer->FramebufferBase;
    uint32_t* Fb2 = (uint32_t*)Plane->FrameBuffer->SecondaryFrameBufferBase;
    size_t FbWidth = Plane->FrameBuffer->Width; 
    size_t X = Plane->DirtyX, Y = Plane->DirtyY, Width = Plane->DirtyWidth, Height = Plane->DirtyHeight;
    for(size_t y = 0 ; y < Height; y++){
       for(size_t x = 0 ; x < Width; x++){
            Fb1[(x + X) + ((y + Y) * FbWidth)] = Fb2[(x + X)  + ((y + Y) * FbWidth)];
       }
    }
}

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
    State->FrameBuffer = LouKeMallocType(DRSD_FRAME_BUFFER, USER_GENERIC_MEMORY);
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

PDRSD_PLANE_CHAIN LouKeDrsdAcquireClipChainMember(PDRSD_PLANE Plane) {
    MutexLock(&PlaneLock);
    PDRSD_PLANE_CHAIN TmpChain = &MasterPlaneChain;
    while(TmpChain->Peers.NextHeader){
        TmpChain = (PDRSD_PLANE_CHAIN)TmpChain->Peers.NextHeader;
        if(Plane == TmpChain->PlaneID){
            TmpChain->PlaneReady = true; 
            MutexUnlock(&PlaneLock);
            return TmpChain;
        }
    }
    TmpChain->Peers.NextHeader = (PListHeader)LouKeMallocType(DRSD_PLANE_CHAIN, USER_GENERIC_MEMORY); 
    TmpChain = (PDRSD_PLANE_CHAIN)TmpChain->Peers.NextHeader;
    TmpChain->PlaneID = Plane;
    TmpChain->PlaneReady = true; 
    PlaneCount++;
    MutexUnlock(&PlaneLock);
    return TmpChain;
}

void LouKeDrsdRemovePlaneChainMember(PDRSD_PLANE Plane) {
    MutexLock(&PlaneLock);
    PDRSD_PLANE_CHAIN TmpChain = &MasterPlaneChain;
    PDRSD_PLANE_CHAIN LastChain = &MasterPlaneChain;
    while(TmpChain->Peers.NextHeader){
        LastChain = TmpChain;
        TmpChain = (PDRSD_PLANE_CHAIN)TmpChain->Peers.NextHeader;
        if(Plane == TmpChain->PlaneID){
            TmpChain->PlaneReady = false;
            LastChain->Peers.NextHeader = TmpChain->Peers.NextHeader;
            PlaneCount--;
            LouKeFree(TmpChain);
            MutexUnlock(&PlaneLock);
            return;
        }
    }
    MutexUnlock(&PlaneLock);
}


LOUDDK_API_ENTRY
PDRSD_CLIP LouKeDrsdCreateClip(
    size_t X, size_t Y, 
    size_t Width, size_t Height, 
    uint8_t R, uint8_t G, uint8_t B, uint8_t A
) {
    PDRSD_CLIP ClipQueue = LouKeMallocType(DRSD_CLIP, USER_GENERIC_MEMORY);
    
    ClipQueue->PlaneGroup = &MasterPlaneChain;
    ClipQueue->WindowBuffer = LouKeMallocArray(uint32_t, Width * Height, USER_GENERIC_MEMORY);
    ClipQueue->X = X;
    ClipQueue->Y = Y;
    ClipQueue->Width = Width;
    ClipQueue->Height = Height;
    uint32_t Color = DRSD_CORE_TRANSLATE_COLOR(R,G,B,A);
    for(size_t Ty = 0; Ty < Height; Ty++){
        for(size_t Tx = 0; Tx < Width; Tx++){
            ClipQueue->WindowBuffer[Tx + (Ty * Width)] = Color;
        }
    }
    return ClipQueue;
}

LOUDDK_API_ENTRY void LouKeDestroyClip(PDRSD_CLIP Clip){
    MutexLock(&PlaneLock);

    MutexUnlock(&PlaneLock);
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
    INT64 X = Clip->X;
    INT64 Y = Clip->Y;
    INT64 Width = (INT64)Clip->Width;
    INT64 Height = (INT64)Clip->Height;

    PDRSD_PLANE_CHAIN TmpChain = &MasterPlaneChain;
    while (TmpChain->Peers.NextHeader) {
        TmpChain = (PDRSD_PLANE_CHAIN)TmpChain->Peers.NextHeader;
        PDRSD_PLANE Plane = TmpChain->PlaneID;

        INT64 x = MAX(X, Plane->PlaneState->SourceX);
        INT64 y = MAX(Y, Plane->PlaneState->SourceY);
        INT64 x2 = MIN(X + Width, Plane->PlaneState->SourceX + (INT64)Plane->PlaneState->Width);
        INT64 y2 = MIN(Y + Height, Plane->PlaneState->SourceY + (INT64)Plane->PlaneState->Height);

        if (x2 <= x || y2 <= y) {
            continue;
        }

        INT64 w = x2 - x;
        INT64 h = y2 - y;

        size_t FbWidth = Plane->FrameBuffer->Width;
        uint32_t* Fb2 = (uint32_t*)Plane->FrameBuffer->SecondaryFrameBufferBase;
        uint32_t* Cb = Clip->WindowBuffer;

        for (size_t Ty = 0; Ty < (size_t)h; Ty++) {
            size_t dstY = (size_t)(y + Ty);
            size_t srcY = (size_t)(Ty + (y - Clip->Y));
            size_t dstOffset = (dstY * FbWidth) + (size_t)x;
            size_t srcOffset = (srcY * Clip->Width) + (size_t)(x - Clip->X);
            for (size_t Tx = 0; Tx < (size_t)w; Tx++) {
                Fb2[dstOffset + Tx] = Cb[srcOffset + Tx];
            }
        }
        CalculateNextUpdate(Plane, x, y, w, h);

    }
}

LOUDDK_API_ENTRY void LouKeDrsdSyncScreen(){
    PDRSD_PLANE_CHAIN TmpChain = &MasterPlaneChain;
    while(TmpChain->Peers.NextHeader){
        TmpChain = (PDRSD_PLANE_CHAIN)TmpChain->Peers.NextHeader;
        PDRSD_PLANE Plane = TmpChain->PlaneID;
        DrsdFbDoUpdate(Plane);
        if(TmpChain->PrimaryAtomicUpdate){
            TmpChain->PrimaryAtomicUpdate(Plane, Plane->PlaneState);
        }
    }
}

void LouKeCreateScrollTerminal(PDRSD_CLIP Clip);

LOUDDK_API_ENTRY 
LOUSTATUS
LouKeDrsdInitializeBootDevice(
    PDRSD_DEVICE Device
){
    BootDevice = Device;
    PDRSD_PLANE Plane = Device->Planes;
    
    LouKeDrsdAcquireClipChainMember(Plane);

    PDRSD_CLIP Background = LouKeDrsdCreateClip(
        0, 0,
        Plane->PlaneState->Width, Plane->PlaneState->Height,
        0, 128, 128, 255
    );

    Plane->AlphaShift = 24;
    Plane->RedShift = 16;
    Plane->GreenShift = 8;
    Plane->BlueShift = 0;

    LouKeUpdateClipState(Background);

    LouKeDrsdSyncScreen();
    LouPrint("LouKeDrsdInitializeBootDevice() STATUS_SUCCESS\n");

    LouKeCreateScrollTerminal(Background);

    return STATUS_SUCCESS;
}


LOUDDK_API_ENTRY 
void LouKeDrsdHandleConflictingDevices(P_PCI_DEVICE_OBJECT PDEV){

    if(BootDevice){
        LouKeDrsdRemovePlaneChainMember(BootDevice->Planes);
        BootDevice = 0x00;
    }


    LouPrint("LouKeDrsdHandleConflictingDevices() STATUS_SUCCESS\n");
}

LOUDDK_API_ENTRY
void LouKeOsDosUpdateMapping();

void LouKeSetScrollTerminalResolution(SIZE Width, SIZE Height);

LOUDDK_API_ENTRY
LOUSTATUS
LouKeDrsdInitializeDevice(
    PDRSD_DEVICE Device
){
    PDRSD_CONNECTOR Connector = Device->Connectors;
    PDRSD_CRTC Crtc = 0x00;
    PDRSD_PLANE PrimaryPlane = 0x00;
    uint32_t* Formats; 
    size_t FormatCount; 
    while(Connector){
        LouPrint("Configuring Connector:%h\n", Connector);
        
        Connector->ProbeModeCount = Connector->Callbacks->ConnectorFillModes(
            Connector, 
            Device->ModeConfiguration.MaximumWidth, 
            Device->ModeConfiguration.MaximumHeight
        );

        Crtc = Connector->Crtc;
        PrimaryPlane = Crtc->PrimaryPlane;
        FormatCount = PrimaryPlane->FormatCount;
        Formats = PrimaryPlane->PlaneState->Formats;
        for(size_t foo = 0 ; foo < FormatCount; foo++){
            if(memcmp(&Formats[foo] , DRSD_COLOR_FORMAT_XRGB8888, 4) == 0){
                PrimaryPlane->AlphaShift = 24;
                PrimaryPlane->RedShift = 16;
                PrimaryPlane->GreenShift = 8;
                PrimaryPlane->BlueShift = 0;
            }
        }

        PrimaryPlane->PlaneState->Formats = PrimaryPlane->Formats;
        PrimaryPlane->PlaneState->FormatCount = PrimaryPlane->FormatCount;

        FillOutInitializationMode(Connector, PrimaryPlane->PlaneState, Crtc);

        PrimaryPlane->FrameBuffer = PrimaryPlane->PlaneState->FrameBuffer;

        if(PrimaryPlane->AssistCallbacks->AtomicUpdate){
            PrimaryPlane->AssistCallbacks->AtomicUpdate(PrimaryPlane, PrimaryPlane->PlaneState);
        }

        Crtc->CrtcState->NeedsModeset = false;

        
        PDRSD_PLANE_CHAIN Chain = LouKeDrsdAcquireClipChainMember(PrimaryPlane);
        Chain->PrimaryAtomicUpdate = PrimaryPlane->AssistCallbacks->AtomicUpdate;

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
void* LouKeDrsdGetPlaneInformation(size_t* CountHandle){
    *CountHandle = PlaneCount;
    MutexLock(&PlaneLock);
    PDRSD_PLANE_QUERY_INFORMATION Query = LouKeMallocArray(DRSD_PLANE_QUERY_INFORMATION, PlaneCount, USER_GENERIC_MEMORY);

    PDRSD_PLANE_CHAIN Tmp = &MasterPlaneChain;
    size_t i = 0;
    while(Tmp->Peers.NextHeader){
        Tmp = (PDRSD_PLANE_CHAIN)Tmp->Peers.NextHeader;

        Query[i].Plane = (uintptr_t)Tmp->PlaneID;
        Query[i].Chain = (uintptr_t)Tmp;
        Query[i].X = Tmp->PlaneID->PlaneState->SourceX;
        Query[i].Y = Tmp->PlaneID->PlaneState->SourceY;
        Query[i].Width = Tmp->PlaneID->PlaneState->Width;
        Query[i].Height = Tmp->PlaneID->PlaneState->Height;

        i++;
    }
    MutexUnlock(&PlaneLock);
    return (void*)Query;
}

LOUDDK_API_ENTRY
LOUSTATUS LouKeDrsdSetPlaneInformation(PVOID Context){

    MutexLock(&PlaneLock);
    PDRSD_PLANE_QUERY_INFORMATION Query = (PDRSD_PLANE_QUERY_INFORMATION)Context;

    PDRSD_PLANE_CHAIN Tmp = &MasterPlaneChain;
    size_t i = 0;
    while(Tmp->Peers.NextHeader){
        Tmp = (PDRSD_PLANE_CHAIN)Tmp->Peers.NextHeader;
        LouPrint("Seting Drsd Plane ID:%h Plane Values X:%d :: Y:%d :: Width:%d :: Height:%d\n", Tmp->PlaneID, Query[i].X, Query[i].Y, Query[i].Width, Query[i].Height);
        Tmp->PlaneID->PlaneState->SourceX = Query[i].X;
        Tmp->PlaneID->PlaneState->SourceY = Query[i].Y;
        Tmp->PlaneID->PlaneState->Width = Query[i].Width;
        Tmp->PlaneID->PlaneState->Height = Query[i].Height;
        LouPrint("Drsd Plane ID:%h Changed Dimentions: X:%d :: Y:%d :: Width:%d :: Height:%d\n", 
            Tmp->PlaneID, Tmp->PlaneID->PlaneState->SourceX, Tmp->PlaneID->PlaneState->SourceY, 
            Tmp->PlaneID->PlaneState->Width, Tmp->PlaneID->PlaneState->Height
        );
        i++;
    }
    MutexUnlock(&PlaneLock);
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
void LouKeUpdateClipSubState(PDRSD_CLIP Clip, size_t SubX, size_t SubY, size_t SubWidth, size_t SubHeight) {
    INT64 X = (INT64)Clip->X + (INT64)SubX;
    INT64 Y = (INT64)Clip->Y + (INT64)SubY;
    INT64 Width  = (INT64)SubWidth;
    INT64 Height = (INT64)SubHeight;

    PDRSD_PLANE_CHAIN TmpChain = &MasterPlaneChain;
    while (TmpChain->Peers.NextHeader) {
        TmpChain = (PDRSD_PLANE_CHAIN)TmpChain->Peers.NextHeader;
        PDRSD_PLANE Plane = TmpChain->PlaneID;

        INT64 x  = MAX(X, Plane->PlaneState->SourceX);
        INT64 y  = MAX(Y, Plane->PlaneState->SourceY);
        INT64 x2 = MIN(X + Width,  Plane->PlaneState->SourceX + (INT64)Plane->PlaneState->Width);
        INT64 y2 = MIN(Y + Height, Plane->PlaneState->SourceY + (INT64)Plane->PlaneState->Height);

        if (x2 <= x || y2 <= y) {
            continue; // No overlap
        }

        INT64 w = x2 - x;
        INT64 h = y2 - y;

        size_t FbWidth = Plane->FrameBuffer->Width;
        uint32_t* Fb2 = (uint32_t*)Plane->FrameBuffer->SecondaryFrameBufferBase;
        uint32_t* Cb = Clip->WindowBuffer;

        for (size_t Ty = 0; Ty < (size_t)h; Ty++) {
            size_t dstY = (size_t)(y + Ty);
            size_t srcY = (size_t)(Ty + (y - Clip->Y));
            size_t dstOffset = (dstY * FbWidth) + (size_t)x;
            size_t srcOffset = (srcY * Clip->Width) + (size_t)(x - Clip->X);
            for (size_t Tx = 0; Tx < (size_t)w; Tx++) {
                Fb2[dstOffset + Tx] = Cb[srcOffset + Tx];
            }
        }
        CalculateNextUpdate(Plane, x, y, w, h);

    }
}


LOUDDK_API_ENTRY
void LouKeUpdateShadowClipState(PDRSD_CLIP Clip) {
    INT64 X = Clip->X;
    INT64 Y = Clip->Y;
    INT64 Width = (INT64)Clip->Width;
    INT64 Height = (INT64)Clip->Height;

    PDRSD_PLANE_CHAIN TmpChain = &MasterPlaneChain;
    while (TmpChain->Peers.NextHeader) {
        TmpChain = (PDRSD_PLANE_CHAIN)TmpChain->Peers.NextHeader;
        PDRSD_PLANE Plane = TmpChain->PlaneID;

        INT64 x = MAX(X, Plane->PlaneState->SourceX);
        INT64 y = MAX(Y, Plane->PlaneState->SourceY);
        INT64 x2 = MIN(X + Width, Plane->PlaneState->SourceX + (INT64)Plane->PlaneState->Width);
        INT64 y2 = MIN(Y + Height, Plane->PlaneState->SourceY + (INT64)Plane->PlaneState->Height);

        if (x2 <= x || y2 <= y) {
            continue;
        }

        INT64 w = x2 - x;
        INT64 h = y2 - y;

        size_t FbWidth = Plane->FrameBuffer->Width;
        uint32_t* Fb2 = (uint32_t*)Plane->FrameBuffer->SecondaryFrameBufferBase;
        uint32_t* Cb = Clip->WindowBuffer;

        for (size_t Ty = 0; Ty < (size_t)h; Ty++) {
            size_t dstY = (size_t)(y + Ty);
            size_t srcY = (size_t)(Ty + (y - Clip->Y));
            size_t dstOffset = (dstY * FbWidth) + (size_t)x;
            size_t srcOffset = (srcY * Clip->Width) + (size_t)(x - Clip->X);
            for (size_t Tx = 0; Tx < (size_t)w; Tx++) {
                if(Cb[srcOffset + Tx] & (0xFF << 24)){
                    Fb2[dstOffset + Tx] = Cb[srcOffset + Tx];
                }
            }
        }
        CalculateNextUpdate(Plane, x, y, w, h);

    }
}

LOUDDK_API_ENTRY
void LouKeUpdateShadowClipSubState(
    PDRSD_CLIP Clip, 
    size_t SubX, size_t SubY, 
    size_t SubWidth, size_t SubHeight
){
    INT64 X = (INT64)Clip->X + (INT64)SubX;
    INT64 Y = (INT64)Clip->Y + (INT64)SubY;
    INT64 Width  = (INT64)SubWidth;
    INT64 Height = (INT64)SubHeight;

    PDRSD_PLANE_CHAIN TmpChain = &MasterPlaneChain;
    while (TmpChain->Peers.NextHeader) {
        TmpChain = (PDRSD_PLANE_CHAIN)TmpChain->Peers.NextHeader;
        PDRSD_PLANE Plane = TmpChain->PlaneID;

        INT64 x  = MAX(X, Plane->PlaneState->SourceX);
        INT64 y  = MAX(Y, Plane->PlaneState->SourceY);
        INT64 x2 = MIN(X + Width,  Plane->PlaneState->SourceX + (INT64)Plane->PlaneState->Width);
        INT64 y2 = MIN(Y + Height, Plane->PlaneState->SourceY + (INT64)Plane->PlaneState->Height);

        if (x2 <= x || y2 <= y) {
            continue; // No overlap
        }

        INT64 w = x2 - x;
        INT64 h = y2 - y;

        size_t FbWidth = Plane->FrameBuffer->Width;
        uint32_t* Fb2 = (uint32_t*)Plane->FrameBuffer->SecondaryFrameBufferBase;
        uint32_t* Cb = Clip->WindowBuffer;

        for (size_t Ty = 0; Ty < (size_t)h; Ty++) {
            size_t dstY = (size_t)(y + Ty);
            size_t srcY = (size_t)(Ty + (y - Clip->Y));
            size_t dstOffset = (dstY * FbWidth) + (size_t)x;
            size_t srcOffset = (srcY * Clip->Width) + (size_t)(x - Clip->X);
            for (size_t Tx = 0; Tx < (size_t)w; Tx++) {
                if(Cb[srcOffset + Tx] & (0xFF << 24)){
                    Fb2[dstOffset + Tx] = Cb[srcOffset + Tx];
                }
            }
        }
        CalculateNextUpdate(Plane, x, y, w, h);

    }
}
