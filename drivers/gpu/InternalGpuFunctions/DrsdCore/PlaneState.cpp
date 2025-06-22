#include "DrsdCore.h"


typedef struct _DRSD_PLANE_TRACK{
    ListHeader  Peers;
    PDRSD_PLANE Plane;
}DRSD_PLANE_TRACK, * PDRSD_PLANE_TRACK;

static PDRSD_PLANE_TRACK GlobalPlanes = 0x00;
static size_t PriPlaneCount = 0;
static bool Mirrored = true;

KERNEL_IMPORT
LOUSTATUS DrsdInitializeGenericPlane(
    PDRSD_DEVICE            Device, 
    PDRSD_PLANE             Plane,
    size_t                  CrtcLimit,
    PDRSD_PLANE_CALLBACKS   PlaneCallbacks,
    uint32_t*               PlaneFormats,
    size_t                  FormatCount,
    uint64_t*               FormatModifiers,
    DRSD_PLANE_TYPE         PlaneType,
    string                  Name,
    ...
){
    Plane->PlaneName = Name;
    Plane->Callbacks = PlaneCallbacks;
    Plane->FormatCount = FormatCount;
    Plane->FormatDefault = PlaneFormats ? false : true;
    Plane->Modifiers = FormatModifiers;
    Plane->ModifierDefault = FormatModifiers ? false : true;
    Plane->PlaneType = PlaneType;
    Plane->Device = Device;
    Plane->Formats = PlaneFormats; 
    
    LouPrint("Callbacks->ResetPlane:%h\n", PlaneCallbacks->ResetPlane);

    PDRSD_PLANE Tmp = Device->Planes;
    PDRSD_PLANE_TRACK Tmp2 = GlobalPlanes;
    if(!Tmp){
        Device->Planes = Plane;
    }else{
        while(Tmp->Peers.NextHeader){
            Tmp = (PDRSD_PLANE)Tmp->Peers.NextHeader;
        }
        Tmp->Peers.NextHeader = (PListHeader)Plane;
    }
    Tmp2 = GlobalPlanes;
    if(!Tmp2){
        GlobalPlanes = LouKeMallocType(DRSD_PLANE_TRACK, KERNEL_GENERIC_MEMORY);
        GlobalPlanes->Plane = Plane;
    }else{
        while(Tmp2->Peers.NextHeader){
            Tmp2 = (PDRSD_PLANE_TRACK)Tmp->Peers.NextHeader;
        }
        Tmp2->Peers.NextHeader = (PListHeader)LouKeMallocType(DRSD_PLANE_TRACK, KERNEL_GENERIC_MEMORY);
        Tmp2 = (PDRSD_PLANE_TRACK)Tmp2->Peers.NextHeader;
        Tmp2->Plane = Plane;
    }

    PlaneType & PRIMARY_PLANE ? PriPlaneCount++ : 0; 

    //TODO: later add support for Extra Data

    LouPrint("DrsdInitializeGenericPlane() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

void DrsdGxeDestroyShadowPlane(
    PDRSD_PLANE Plane
){

    DrsdAtomicDestroyPlaneState(Plane->PlaneState);

    LouPrint("DrsdGxeDestroyShadowPlane() STATUS_SUCCESS\n");
}


void LouKeDrsdCorePutPixelExXRGB8888(
    PDRSD_PLANE Plane,
    uint32_t X, uint32_t Y, 
    uint8_t R, uint8_t G, 
    uint8_t B, uint8_t A
){
    uint32_t Color = 0;
    Color = (A << 24) | (R << 16) | (G << 8) | B;
    PDRSD_FRAME_BUFFER Fb = Plane->FrameBuffer;
    uint32_t* Base = (uint32_t*)Fb->FramebufferBase;
    uint32_t  YAnchor = (uint32_t)Fb->Width;
    Base[X + (YAnchor * Y)] = Color;
}

#define DRSD_XRGB32 0

KERNEL_IMPORT void LouKeSetScreenSurface(int64_t X, int64_t Y);

void LouKeDrsdCorePutPixel(int64_t X, int64_t Y, uint8_t R, uint8_t G, uint8_t B, uint8_t A){
    PDRSD_PLANE Plane = GlobalPlanes->Plane;
    if(!Plane){
        return;
    }
    if((PriPlaneCount > 1) && (!Mirrored)){          
        LouPrint("LouKeDrsdCorePutPixel()\n");
        while(1);
    }

    if(!Plane->PlaneInUse){
        return;
    }

    switch(Plane->DrsdPutPixelCase){
        case DRSD_XRGB32:{
            LouKeDrsdCorePutPixelExXRGB8888(Plane, X, Y, R, G, B, A);
            return;
        }
        default:
            return;
    }

}

void LouKeSetScreenSurface(int64_t X, int64_t Y);


void LouKeDrsdClearScreen(PDRSD_PLANE Plane){

    LouPrint("X     :%d\n", Plane->PlaneState->SourceX);
    LouPrint("Y     :%d\n", Plane->PlaneState->SourceY);
    LouPrint("Width :%d\n", Plane->PlaneState->Width);
    LouPrint("Height:%d\n", Plane->PlaneState->Height); 
    
    if(strncmp(Plane->PlaneState->FormatUsed, DRSD_COLOR_FORMAT_XRGB8888, 4) == 0){
        Plane->DrsdPutPixelCase = DRSD_XRGB32;
    }
    else return;

    Plane->PlaneInUse = true;

    const int64_t Width = Plane->PlaneState->Width, Height = Plane->PlaneState->Height;

    if(PriPlaneCount == 1){
        //LouKeSetScreenSurface(Width, Height);
    }

    for(int64_t y = 0; y < (int64_t)Height; y++){
        for(int64_t x = 0; x < (int64_t)Width; x++){
            LouKeDrsdCorePutPixel(x, y, 0, 128, 128, 0);
        }
    }


    LouPrint("LouKeDrsdClearScreen() STATUS_SUCCESS\n");
}