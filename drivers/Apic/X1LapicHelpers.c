#include "X1ApicInternals.h"

UINT32 ApicHalGetX1ApicIdEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicIdRegisterEx(ApicBase);
    return GET_X1APIC_ID_VALUE(Register);
}

UINT32 ApicHalGetX1ApicId(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicIdEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicVersionEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicVersionRegisterEx(ApicBase);
    return GET_X1APIC_VERSION_VALUE(Register);
}

UINT32 ApicHalGetX1ApicVersion(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicVersionEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicMaxLvtEntryEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicVersionRegisterEx(ApicBase);
    return GET_X1APIC_MAX_LVT_ENTRY_VALUE(Register);   
}

UINT32 ApicHalGetX1ApicMaxLvtEntry(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicMaxLvtEntryEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalX1ApicSupportsEoiSuppresionEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicVersionRegisterEx(ApicBase);
    return GET_X1APIC_SUPPORT_EOI_SUPRESS_VALUE(Register) ? true : false;
}

APIC_TIMER_MODE ApicHalGetX1ApicLvtTimerModeEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    return (APIC_TIMER_MODE)GET_X1APIC_LVT_TIMER_MODE(Register);
}

APIC_TIMER_MODE ApicHalGetX1ApicLvtTimerMode(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalGetX1ApicLvtTimerModeEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtTimerMaskedEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    return GET_X1APIC_LVT_TIMER_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtTimerMasked(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtTimerMaskedEx(ApicDeviceObject->ApicBase);
}

BOOLEAN ApicHalIsX1ApicLvtTimerInterruptPendingEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    return GET_X1APIC_LVT_TIMER_DELIVERY_STATUS(Register) ? true : false;
}

BOOLEAN ApicHalIsX1ApicLvtTimerInterruptPending(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    return ApicHalIsX1ApicLvtTimerInterruptPendingEx(ApicDeviceObject->ApicBase);
}

UINT32 ApicHalGetX1ApicLvtTimerVectorEx(PVOID ApicBase){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    return GET_X1APIC_LVT_TIMER_VECTOR(Register);
}





void ApicHalSetX1ApicIdEx(PVOID ApicBase, UINT32 Value){
    UINT32 Tmp = ApicHalGetX1ApicIdRegisterEx(ApicBase);
    SET_X1APIC_ID_REGISTER(Tmp, Value);
    ApicHalSetX1ApicIdRegisterEx(ApicBase, Value);
}

void ApicHalSetX1ApicId(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Value){
    ApicHalSetX1ApicIdEx(ApicDeviceObject->ApicBase, Value);
}

void ApicHalSetX1ApicLvtTimerModeEx(PVOID ApicBase, APIC_TIMER_MODE TimerMode){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    SET_X1APIC_LVT_TIMER_MODE(Register, (UINT32)TimerMode);
    ApicHalSetX1ApicLvtTimerRegisterEx(ApicBase, Register);
}

void ApicHalSetX1ApicLvtTimerMode(PAPIC_DEVICE_OBJECT ApicDeviceObject, APIC_TIMER_MODE TimerMode){
    ApicHalSetX1ApicLvtTimerModeEx(ApicDeviceObject->ApicBase, TimerMode);
}

void ApicHalSetX1ApicLvtTimerMaskEx(PVOID ApicBase, BOOLEAN Masked){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    SET_X1APIC_LVT_TIMER_MASK(Register, (Masked ? 1 : 0));
    ApicHalSetX1ApicLvtTimerRegisterEx(ApicBase, Register);
}

void ApicHalSetX1ApicLvtTimerMask(PAPIC_DEVICE_OBJECT ApicDeviceObject, BOOLEAN Masked){
    ApicHalSetX1ApicLvtTimerMaskEx(ApicDeviceObject->ApicBase, Masked);
}

void ApicHalSetX1ApicLvtTimerVectorEx(PVOID ApicBase, UINT32 Vector){
    UINT32 Register = ApicHalGetX1ApicLvtTimerRegisterEx(ApicBase);
    SET_X1APIC_LVT_TIMER_VECTOR(Register, Vector);
    ApicHalSetX1ApicLvtTimerRegisterEx(ApicBase, Register);
}

void ApicHalSetX1ApicLvtTimerVector(PAPIC_DEVICE_OBJECT ApicDeviceObject, UINT32 Vector){
    ApicHalSetX1ApicLvtTimerVectorEx(ApicDeviceObject->ApicBase, Vector);
}