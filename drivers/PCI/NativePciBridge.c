//Tyler Grenier - NativePciBridge.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

UINT32 NativePciBridgeDeviceGetBarEx(UINT32* DeviceBase, UINT8 Bar){
    return NativePciReadUint32Ex(
        DeviceBase,
        (UINT32)(Bar * 0x04 + PCI_BRIDGE_DEVICE_CONFIG_BAR_STACK)
    );
}

void NativePciBridgeDeviceSetBarEx(UINT32* DeviceBase, UINT8 Bar, UINT32 Value){
    NativePciWriteUint32Ex(DeviceBase, Bar, Value);
}

UINT8 NativePciBridgeDeviceGetPrimaryBusNumberEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_PRIMARY_BUS_NUMBER);
}

UINT8 NativePciBridgeDeviceGetSecondaryBusNumberEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_SECONDARY_BUS_NUMBER);
}

UINT8 NativePciBridgeDeviceGetSubordinateBusNumberEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_SUBORDINATE_BUS_NUMBER);
}

UINT8 NativePciBridgeDeviceGetSecondaryLatencyTimerEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_SECONDARY_LATENCY_TIMER);
}

UINT8 NativePciBridgeDeviceGetIoBaseEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_IO_BASE);
}

UINT8 NativePciBridgeDeviceGetIoLimitEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_IO_LIMIT);
}

UINT16 NativePciBridgeDeviceGetSecondaryStatusEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_SECONDARY_STATUS);
}

void NativePciBridgeDeviceSetSecondaryStatusEx(UINT32* DeviceBase, UINT16 Value){
    NativePciWriteUint16Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_SECONDARY_STATUS, Value);
}

UINT16 NativePciBridgeDeviceGetMemoryBaseEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_MEMORY_BASE);
}

UINT16 NativePciBridgeDeviceGetMemoryLimitEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_MEMORY_LIMIT);
}

UINT16 NativePciBridgeDeviceGetPrefetchableMemoryBaseEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_MEMORY_BASE);
}

UINT16 NativePciBridgeDeviceGetPrefetchableMemoryLimitEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_MEMORY_LIMIT);
}

UINT32 NativePciBridgeDeviceGetPrefetchableMemoryUpper32BaseEx(UINT32* DeviceBase){
    return NativePciReadUint32Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_UPPER32_BASE);
}

UINT32 NativePciBridgeDeviceGetPrefetchableMemoryUpper32LimitEx(UINT32* DeviceBase){
    return NativePciReadUint32Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_UPPER32_BASE);
}

UINT16 NativePciBridgeDeviceGetIoUpper16BaseEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_IO_BASE_UPPER16);
}

UINT16 NativePciBridgeDeviceGetIoUpper16LimitEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_IO_LIMIT_UPPER16);
}

UINT8 NativePciBridgeDeviceGetCapabilitiesPointerEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_CAPABILITIES_POINTER);
}

UINT32 NativePciBridgeDeviceGetExpansionRomBaseEx(UINT32* DeviceBase){
    return NativePciReadUint32Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_EXPANSION_ROM_BASE);
}

UINT8 NativePciBridgeDeviceGetInterruptLineEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_INTERRUPT_LINE);
}

void NativePciBridgeDeviceSetInterruptLineEx(UINT32* DeviceBase, UINT8 Value){
    NativePciWriteUint8Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_INTERRUPT_LINE, Value);
}

UINT16 NativePciBridgeDeviceGetBridgeControlEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_BRIDGE_DEVICE_CONFIG_INTERRUPT_PIN);
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