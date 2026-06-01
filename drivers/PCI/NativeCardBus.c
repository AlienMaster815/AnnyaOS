//Tyler Grenier - NativePciBridge.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"


UINT32 NativePciCardBusGetCardBusSocketExCaBaseAddressEx(UINT32* DeviceBase){
    return 0;
}

UINT8 NativePciCardBusGetOffsetCapabilitiesEx(UINT32* DeviceBase){
    return 0;
}

UINT16 NativePciCardBusGetSecondaryStatusEx(UINT32* DeviceBase){
    return 0;
}

void NativePciCardBusSetSecondaryStatusEx(UINT32* DeviceBase, UINT16 Value){

}

UINT8 NativePciCardBusGetPciBusNumberEx(UINT32* DeviceBase){
    return 0;
}

UINT8 NativePciCardBusGetCardBusNumberEx(UINT32* DeviceBase){
    return 0;
}

UINT8 NativePciCardBusGetSubordinateBusNumberEx(UINT32* DeviceBase){
    return 0;
}

UINT8 NativePciCardBusGetCardBusLatencyTimerEx(UINT32* DeviceBase){
    return 0;
}

UINT32 NativePciCardBusGetMemoryBaseAddressEx(UINT32* DeviceBase, UINT8 x){
    return 0;
}

UINT32 NativePciCardBusGetMemoryLimitEx(UINT32* DeviceBase, UINT8 x){
    return 0;
}

UINT32 NativePciCardBusGetIoBaseAddressEx(UINT32* DeviceBase, UINT8 x){
    return 0;
}

UINT32 NativePciCardBusGetIoLimitEx(UINT32* DeviceBase, UINT8 x){
    return 0;
}

UINT8 NativePciCardBusGetInterruptLineEx(UINT32* DeviceBase){
    return 0;
}

void NativePciCardBusSetInterruptLineEx(UINT32* DeviceBase, UINT8 Value){

}

UINT8 NativePciCardBusGetInterruptPinEx(UINT32* DeviceBase){
    return 0;
}

UINT16 NativePciCardBusGetBridgeControlEx(UINT32* DeviceBase){
    return 0;
}

UINT16 NativePciCardBusGetSubsystemVendorIdEx(UINT32* DeviceBase){
    return 0;
}

UINT16 NativePciCardBusGetSubsystemDeviceIdEx(UINT32* DeviceBase){
    return 0;
}

UINT32 NativePciCardBusGet16BitPcCardNativeModeBaseAddressEx(UINT32* DeviceBase){
    return 0;
}



UINT32 NativePciCardBusGetCardBusSocketExCaBaseAddress(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetCardBusSocketExCaBaseAddressEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciCardBusGetOffsetCapabilities(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetOffsetCapabilitiesEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciCardBusGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetSecondaryStatusEx(PDEV->EcamDeviceBase);
}

void NativePciCardBusSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciCardBusSetSecondaryStatusEx(PDEV->EcamDeviceBase, Value);
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}

UINT8 NativePciCardBusGetPciBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetPciBusNumberEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciCardBusGetCardBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetCardBusNumberEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciCardBusGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetSubordinateBusNumberEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciCardBusGetCardBusLatencyTimer(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetCardBusLatencyTimerEx(PDEV->EcamDeviceBase);
}

UINT32 NativePciCardBusGetMemoryBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x){
    return NativePciCardBusGetMemoryBaseAddressEx(PDEV->EcamDeviceBase, x);
}

UINT32 NativePciCardBusGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x){
    return NativePciCardBusGetMemoryLimitEx(PDEV->EcamDeviceBase, x);
}

UINT32 NativePciCardBusGetIoBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x){
    return NativePciCardBusGetIoBaseAddressEx(PDEV->EcamDeviceBase, x);
}

UINT32 NativePciCardBusGetIoLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x){
    return NativePciCardBusGetIoLimitEx(PDEV->EcamDeviceBase, x);
}

UINT8 NativePciCardBusGetInterruptLine(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetInterruptLineEx(PDEV->EcamDeviceBase);
}

void NativePciCardBusSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciCardBusSetInterruptLineEx(PDEV->EcamDeviceBase, Value);
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}

UINT8 NativePciCardBusGetInterruptPin(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetInterruptPinEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciCardBusGetBridgeControl(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetBridgeControlEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciCardBusGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetSubsystemVendorIdEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciCardBusGetSubsystemDeviceId(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGetSubsystemDeviceIdEx(PDEV->EcamDeviceBase);
}

UINT32 NativePciCardBusGet16BitPcCardNativeModeBaseAddress(PPCI_DEVICE_OBJECT PDEV){
    return NativePciCardBusGet16BitPcCardNativeModeBaseAddressEx(PDEV->EcamDeviceBase);
}
