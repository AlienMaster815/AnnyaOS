//Tyler Grenier - LegacyPciBridge.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

UINT32 LegacyPciBridgeDeviceGetBarEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   Bar
){
    return LegacyPciReadUint32Ex(
        Bus,
        Slot,
        Function,
        (UINT32)(Bar * 0x04 + PCI_BRIDGE_DEVICE_CONFIG_BAR_STACK)
    );
}

void LegacyPciBridgeDeviceSetBarEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   Bar,
    UINT32  Value
){
    LegacyPciWriteUint32Ex(
        Bus,
        Slot,
        Function,
        (UINT32)(Bar * 0x04 + PCI_BRIDGE_DEVICE_CONFIG_BAR_STACK),
        Value
    );
}

UINT8 LegacyPciBridgeDeviceGetPrimaryBusNumberEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_PRIMARY_BUS_NUMBER
    );
}

UINT8 LegacyPciBridgeDeviceGetSecondaryBusNumberEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_SECONDARY_BUS_NUMBER
    );
}

UINT8 LegacyPciBridgeDeviceGetSubordinateBusNumberEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_SUBORDINATE_BUS_NUMBER
    );
}

UINT8 LegacyPciBridgeDeviceGetSecondaryLatencyTimerEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_SECONDARY_LATENCY_TIMER
    );
}

UINT8 LegacyPciBridgeDeviceGetIoBaseEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_IO_BASE
    );
}

UINT8 LegacyPciBridgeDeviceGetIoLimitEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_IO_LIMIT
    );
}

UINT16 LegacyPciBridgeDeviceGetSecondaryStatusEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_SECONDARY_STATUS
    );
}

void LegacyPciBridgeDeviceSetSecondaryStatusEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT16  Value
){
    LegacyPciWriteUint16Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_SECONDARY_STATUS,
        Value
    );
}

UINT16 LegacyPciBridgeDeviceGetMemoryBaseEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_MEMORY_BASE
    );
}

UINT16 LegacyPciBridgeDeviceGetMemoryLimitEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_MEMORY_LIMIT
    );
}

UINT16 LegacyPciBridgeDeviceGetPrefetchableMemoryBaseEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_MEMORY_BASE
    );
}

UINT16 LegacyPciBridgeDeviceGetPrefetchableMemoryLimitEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_MEMORY_LIMIT
    );
}

UINT32 LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32BaseEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint32Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_UPPER32_BASE
    );
}

UINT32 LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32LimitEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint32Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_UPPER32_LIMIT
    );
}

UINT16 LegacyPciBridgeDeviceGetIoUpper16BaseEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_IO_BASE_UPPER16
    );
}

UINT16 LegacyPciBridgeDeviceGetIoUpper16LimitEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_IO_LIMIT_UPPER16
    );
}

UINT8 LegacyPciBridgeDeviceGetCapabilitiesPointerEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_CAPABILITIES_POINTER
    );  
}

UINT32 LegacyPciBridgeDeviceGetExpansionRomBaseEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint32Ex(
        Bus,
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_EXPANSION_ROM_BASE  
    );
}

UINT8 LegacyPciBridgeDeviceGetInterruptLineEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_INTERRUPT_LINE  
    );
}

void LegacyPciBridgeDeviceSetInterruptLineEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   Value
){
    LegacyPciWriteUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_INTERRUPT_LINE,
        Value
    );
}

UINT8 LegacyPciBridgeDeviceGetInterruptPinEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_INTERRUPT_PIN
    );
}

UINT16 LegacyPciBridgeDeviceGetBridgeControlEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus, 
        Slot,
        Function,
        PCI_BRIDGE_DEVICE_CONFIG_BRIDGE_CONTROL
    );
}



UINT32 LegacyPciBridgeDeviceGetBar(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               Bar
){
    return LegacyPciBridgeDeviceGetBarEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Bar
    );
}

void LegacyPciBridgeDeviceSetBar(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               Bar, 
    UINT32              Value
){
    LegacyPciBridgeDeviceSetBarEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Bar,
        Value
    );
}

UINT8 LegacyPciBridgeDeviceGetPrimaryBusNumber(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetPrimaryBusNumberEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciBridgeDeviceGetSecondaryBusNumber(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetSecondaryBusNumberEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciBridgeDeviceGetSubordinateBusNumber(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetSubordinateBusNumberEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciBridgeDeviceGetSecondaryLatencyTimer(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetSecondaryLatencyTimerEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciBridgeDeviceGetIoBase(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetIoBaseEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciBridgeDeviceGetIoLimit(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetIoLimitEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciBridgeDeviceGetSecondaryStatus(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetSecondaryStatusEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

void LegacyPciBridgeDeviceSetSecondaryStatus(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT16              Value
){
    LegacyPciBridgeDeviceSetSecondaryStatusEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Value
    );
}

UINT16 LegacyPciBridgeDeviceGetMemoryBase(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetMemoryBaseEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciBridgeDeviceGetMemoryLimit(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetMemoryLimitEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciBridgeDeviceGetPrefetchableMemoryBase(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetPrefetchableMemoryBaseEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciBridgeDeviceGetPrefetchableMemoryLimit(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetPrefetchableMemoryLimitEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT32 LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32Base(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32BaseEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT32 LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32Limit(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32LimitEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciBridgeDeviceGetIoUpper16Base(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetIoUpper16BaseEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciBridgeDeviceGetIoUpper16Limit(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetIoUpper16LimitEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciBridgeDeviceGetCapabilitiesPointer(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetCapabilitiesPointerEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT32 LegacyPciBridgeDeviceGetExpansionRomBase(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetExpansionRomBaseEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciBridgeDeviceGetInterruptLine(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetInterruptLineEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

void LegacyPciBridgeDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    LegacyPciBridgeDeviceSetInterruptLineEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Value
    );
}

UINT16 LegacyPciBridgeDeviceGetBridgeControl(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciBridgeDeviceGetBridgeControlEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function 
    );
}
