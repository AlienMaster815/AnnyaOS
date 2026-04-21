#include "DrsdCore.h"

DRIVER_EXPORT
PDRSD_GXE_OBJECT
DrsdGxeFbGetObject(
    PDRSD_FRAME_BUFFER  Fb,
    UINT                Plane
){
    PDRSD_DEVICE Device = Fb->Device;

    if(Plane >= ARRAY_SIZE(Fb->Objects)){
        return 0x00;
    }
    if(!Fb->Objects[Plane]){
        LouPrint("DRSDCORE.SYS:Object:%h Dosent Have Data For Plane:%d\n", Fb->Objects, Plane);
    }
    return Fb->Objects[Plane];
}

DRIVER_EXPORT
void
DrsdGxeVUnMap(
    PDRSD_GXE_OBJECT    Object,
    PIO_MAP_OBJECT      IoMap
){



}

DRIVER_EXPORT
LOUSTATUS
DrsdGxeVMap(
    PDRSD_GXE_OBJECT    Object,
    PIO_MAP_OBJECT      IoMap
){
    LOUSTATUS Status = STATUS_SUCCESS
    LouKeDmaReserveLock(Object->DmaReserve, 0x00);
    //TODO:Status = DrsdGxeVMapLocked(Object, IoMap);
    LouKeDmaReserveUnlock(Object->DmaReserve);

    return Status;
}

DRIVER_EXPORT 
LOUSTATUS
DrsdGxeFbVMap(
    PDRSD_FRAME_BUFFER  Fb,
    PIO_MAP_OBJECT      Map,
    PIO_MAP_OBJECT      Data
){
    PDRSD_GXE_OBJECT Object;
    UINT32 i;
    LOUSTATUS Status;
    
    for(i = 0 ; i < Fb->Format->PlaneCount; i++){
        Object = DrsdGxeFbGetObject(Fb, i);
        if(!Object){
            Status = STATUS_INVALID_PARAMETER;
            goto _ERROR_GXE_UNMAP;
        }
        Status = DrsdGxeVMap(Object, &Map[i]);
        if(Status != STATUS_SUCCESS){
            goto _ERROR_GXE_UNMAP;
        }
    }

    if(Data){
        for(i = 0; i < Fb->Format->PlaneCount; ++i){
            memcpy(&Data[i], &Map[i], sizeof(Data[i]));
            if(LouKeIoMapObjIsNull(&Data[i])){
                continue;
            }
            LouKeIoMapObjIncrement(&Data[i], Fb->Offsets[i]);
        }
    }

    return STATUS_SUCCESS;

_ERROR_GXE_UNMAP:
    while(i){
        --i;
        Object = DrsdGxeFbGetObject(Fb, i);
        if(!Object){
            continue;
        }
        DrsdGxeVUnMap(Object, &Map[i]);
    }

    return Status;
}