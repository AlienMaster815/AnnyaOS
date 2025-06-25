#include "DrsdCore.h"


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

    //LouPrint("Callbacks->ResetPlane:%h\n", PlaneCallbacks->ResetPlane);

    PDRSD_PLANE Tmp = Device->Planes;
    if(!Tmp){
        Device->Planes = Plane;
    }else{
        while(Tmp->Peers.NextHeader){
            Tmp = (PDRSD_PLANE)Tmp->Peers.NextHeader;
        }
        Tmp->Peers.NextHeader = (PListHeader)Plane;
    }

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
    uint32_t* Base = (uint32_t*)Fb->SecondaryFrameBufferBase;
    uint32_t  YAnchor = (uint32_t)Fb->Width;
    Base[X + (YAnchor * Y)] = Color;
}

#define DRSD_XRGB32 0

KERNEL_IMPORT void LouKeSetScreenSurface(int64_t X, int64_t Y);

LOUDDK_API_ENTRY
void* GetFrameBufferAddress(
    int64_t x, int64_t y
){
    return 0x00;
}


LOUDDK_API_ENTRY
void LouKeDrsdCorePutPixel(int64_t X, int64_t Y, uint8_t R, uint8_t G, uint8_t B, uint8_t A){

}
