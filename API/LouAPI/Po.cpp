#include <LouDDK.h>


KERNEL_EXPORT 
LOUSTATUS 
LouKePoCallDriver(
    PDEVICE_OBJECT DeviceObject, 
    PIRP Irp
){
    LouPrint("LouKePoCallDriver()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePoClearPowerRequest(
    PVOID PowerRequest, 
    POWER_REQUEST_TYPE Type
){
    LouPrint("LouKePoClearPowerRequest()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePoCreatePowerRequest(
    PVOID* PowerRequest, 
    PDEVICE_OBJECT DeviceObject, 
    PCOUNTED_REASON_CONTEXT Context
){
    LouPrint("LouKePoCreatePowerRequest()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
void 
LouKePoDeletePowerRequest(PVOID PowerRequest){
    LouPrint("LouKePoDeletePowerRequest()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKePoEndDeviceBusy(PULONG IdlePointer){
    LouPrint("LouKePoEndDeviceBusy()\n");
    while(1);
}

KERNEL_EXPORT 
BOOLEAN 
LouKePoQueryWatchdogTime(PDEVICE_OBJECT Pdo, PULONG SecondsRemaining){
    LouPrint("LouKePoQueryWatchdogTime()\n");
    while(1);
    return false;
}

KERNEL_EXPORT 
PULONG 
LouKePoRegisterDeviceForIdleDetection(
    PDEVICE_OBJECT DeviceObject, 
    ULONG ConservationIdleTime, 
    ULONG PerformanceIdleTime, 
    DEVICE_POWER_STATE State
){
    LouPrint("LouKePoRegisterDeviceForIdleDetection()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePoRegisterPowerSettingCallback(
    PDEVICE_OBJECT DeviceObject, 
    LPCGUID SettingGuid, 
    PPOWER_SETTING_CALLBACK Callback, 
    PVOID Context, 
    PVOID* Handle
){
    LouPrint("LouKePoRegisterPowerSettingCallback()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
PVOID 
LouKePoRegisterSystemState(
    PVOID StateHandle, 
    EXECUTION_STATE Flags
){
    LouPrint("LouKePoRegisterSystemState()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
void 
LouKePoSetDeviceBusyEx(
    PULONG IdlePointer
){
    LouPrint("LouKePoSetDeviceBusyEx()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePoSetPowerRequest(
    PVOID PowerRequest, 
    POWER_REQUEST_TYPE Type
){
    LouPrint("LouKePoSetPowerRequest()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
POWER_STATE 
LouKePoSetPowerState(
    PDEVICE_OBJECT DeviceObject, 
    POWER_STATE_TYPE Type, 
    POWER_STATE State
){
    POWER_STATE Foo;
    LouPrint("LouKePoSetPowerState()\n");
    while(1);
    return Foo;
}

KERNEL_EXPORT 
void 
LouKePoStartDeviceBusy(
    PULONG IdlePointer
){
    LouPrint("LouKePoStartDeviceBusy()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKePoStartNextPowerIrp(
    PIRP Irp
){
    LouPrint("LouKePoStartNextPowerIrp()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKePoUnregisterPowerSettingCallback(
    PVOID Handle
){
    LouPrint("LouKePoUnregisterPowerSettingCallback()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
void 
LouKePoUnregisterSystemState(
    PVOID StateHandle
){
    LouPrint("LouKePoUnregisterSystemState()\n");
    while(1);
}