#include "X1ApicInternals.h"

UINT32 ApicHalGetX1ApicIdEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicIdRegisterEx(ApicBase);
    return GET_X1APIC_ID_VALUE(Register);
}

UINT32 ApicHalGetX1ApicId(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicIdEx(ApicDeviceObject->ApicBase);
}





void ApicHalSetX1ApicIdEx(PVOID ApicBase, UINT32 Value){
    UINT32 Tmp = ApicHalGetX1ApicIdRegisterEx(ApicBase);
    SET_X1APIC_ID_REGISTER(Tmp, Value);
    ApicHalSetX1ApicIdRegisterEx(ApicBase, Value);
}

void ApicHalSetX1ApicId(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicIdEx(ApicDeviceObject->ApicBase, Value);
}