#include "Drsd.h"

DRSD_API
HRESULT
Drsd3dCreateDevice(
    OPAQUE_PTR              Adapter,
    DRSD_3D_FEATURE_LEVEL   MinumumFeatureLevel,
    REFIID                  Riid,
    PVOID*                  DeviceOut
){
    LouPrint("DRSD.DLL:Drsd3dCreateDevice()");
    while(1);
    return 0;
}