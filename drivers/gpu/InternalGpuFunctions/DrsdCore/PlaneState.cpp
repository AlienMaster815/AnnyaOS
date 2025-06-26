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
