//Tyler Grenier - NativePciBridge.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

UINT32 NativePciBridgeDeviceGetBarEx(UINT32* DeviceBase, UINT8 Bar){
    return 0;
}

void NativePciBridgeDeviceSetBarEx(UINT32* DeviceBase, UINT8 Bar, UINT32 Value){
    
}

UINT8 NativePciBridgeDeviceGetPrimaryBusNumberEx(UINT32* DeviceBase){
    return 0;
}

UINT8 NativePciBridgeDeviceGetSecondaryBusNumberEx(UINT32* DeviceBase){
    return 0;
}

UINT8 NativePciBridgeDeviceGetSubordinateBusNumberEx(UINT32* DeviceBase){
    return 0;
}

UINT8 NativePciBridgeDeviceGetSecondaryLatencyTimerEx(UINT32* DeviceBase){
    return 0;
}

UINT8 NativePciBridgeDeviceGetIoBaseEx(UINT32* DeviceBase){
    return 0;
}

UINT8 NativePciBridgeDeviceGetIoLimitEx(UINT32* DeviceBase){
    return 0;
}

UINT16 NativePciBridgeDeviceGetSecondaryStatusEx(UINT32* DeviceBase){
    return 0;
}

void NativePciBridgeDeviceSetSecondaryStatusEx(UINT32* DeviceBase, UINT16 Value){

}

UINT16 NativePciBridgeDeviceGetMemoryBaseEx(UINT32* DeviceBase){
    return 0;
}

UINT16 NativePciBridgeDeviceGetMemoryLimitEx(UINT32* DeviceBase){
    return 0;
}

UINT16 NativePciBridgeDeviceGetPrefetchableMemoryBaseEx(UINT32* DeviceBase){
    return 0;
}

UINT16 NativePciBridgeDeviceGetPrefetchableMemoryLimitEx(UINT32* DeviceBase){
    return 0;
}

UINT32 NativePciBridgeDeviceGetPrefetchableMemoryUpper32BaseEx(UINT32* DeviceBase){
    return 0;
}

UINT32 NativePciBridgeDeviceGetPrefetchableMemoryUpper32LimitEx(UINT32* DeviceBase){
    return 0;
}

UINT16 NativePciBridgeDeviceGetIoUpper16BaseEx(UINT32* DeviceBase){
    return 0;
}

UINT16 NativePciBridgeDeviceGetIoUpper16LimitEx(UINT32* DeviceBase){
    return 0;
}

UINT8 NativePciBridgeDeviceGetCapabilitiesPointerEx(UINT32* DeviceBase){
    return 0;
}

UINT32 NativePciBridgeDeviceGetExpansionRomBaseEx(UINT32* DeviceBase){
    return 0;
}

UINT8 NativePciBridgeDeviceGetInterruptLineEx(UINT32* DeviceBase){
    return 0;
}

void NativePciBridgeDeviceSetInterruptLineEx(UINT32* DeviceBase, UINT8 Value){

}

UINT16 NativePciBridgeDeviceGetBridgeControlEx(UINT32* DeviceBase){
    return 0;
}



UINT32 NativePciBridgeDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar){
    return NativePciBridgeDeviceGetBarEx(PDEV->EcamDeviceBase, Bar);
}

void NativePciBridgeDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciBridgeDeviceSetBarEx(PDEV->EcamDeviceBase, Bar, Value);
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}

UINT8 NativePciBridgeDeviceGetPrimaryBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetPrimaryBusNumberEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciBridgeDeviceGetSecondaryBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetSecondaryBusNumberEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciBridgeDeviceGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetSubordinateBusNumberEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciBridgeDeviceGetSecondaryLatencyTimer(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetSecondaryLatencyTimerEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciBridgeDeviceGetIoBase(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetIoBaseEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciBridgeDeviceGetIoLimit(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetIoLimitEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciBridgeDeviceGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetSecondaryStatusEx(PDEV->EcamDeviceBase);
}

void NativePciBridgeDeviceSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciBridgeDeviceSetSecondaryStatusEx(PDEV->EcamDeviceBase, Value);
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}

UINT16 NativePciBridgeDeviceGetMemoryBase(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetMemoryBaseEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciBridgeDeviceGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetMemoryLimitEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciBridgeDeviceGetPrefetchableMemoryBase(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetPrefetchableMemoryBaseEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciBridgeDeviceGetPrefetchableMemoryLimit(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetPrefetchableMemoryLimitEx(PDEV->EcamDeviceBase);
}

UINT32 NativePciBridgeDeviceGetPrefetchableMemoryUpper32Base(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetPrefetchableMemoryUpper32BaseEx(PDEV->EcamDeviceBase);
}

UINT32 NativePciBridgeDeviceGetPrefetchableMemoryUpper32Limit(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetPrefetchableMemoryUpper32LimitEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciBridgeDeviceGetIoUpper16Base(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetIoUpper16BaseEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciBridgeDeviceGetIoUpper16Limit(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetIoUpper16LimitEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciBridgeDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetCapabilitiesPointerEx(PDEV->EcamDeviceBase);
}

UINT32 NativePciBridgeDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetExpansionRomBaseEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciBridgeDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetInterruptLineEx(PDEV->EcamDeviceBase);
}

void NativePciBridgeDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciBridgeDeviceSetInterruptLineEx(PDEV->EcamDeviceBase, Value);
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}

UINT16 NativePciBridgeDeviceGetBridgeControl(PPCI_DEVICE_OBJECT PDEV){
    return NativePciBridgeDeviceGetBridgeControlEx(PDEV->EcamDeviceBase);
}