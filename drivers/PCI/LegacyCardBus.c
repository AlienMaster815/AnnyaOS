//Tyler Grenier - LegacyCardBus.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

UINT32 LegacyPciCardBusGetCardBusSocketExCaBaseAddressEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint32Ex(
        Bus, 
        Slot, 
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_CARDBUS_SOCKET_EXCA_BASE
    );
}

UINT8 LegacyPciCardBusGetOffsetCapabilitiesEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_OFFSET_CAPABILITIES_LIST
    );
}

UINT16 LegacyPciCardBusGetSecondaryStatusEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_SECONDARY_STATUS
    );
}

void LegacyPciCardBusSetSecondaryStatusEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT16  Value
){
    LegacyPciWriteUint16Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_SECONDARY_STATUS,
        Value
    );
}

UINT8 LegacyPciCardBusGetPciBusNumberEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_PCI_BUS_NUMBER
    );
}

UINT8 LegacyPciCardBusGetCardBusNumberEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_CARDBUS_NUMBER
    );
}

UINT8 LegacyPciCardBusGetSubordinateBusNumberEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_SUBORDINATE_BUS_NUMBER
    );
}

UINT8 LegacyPciCardBusGetCardBusLatencyTimerEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_CARDBUS_LATENCY_TIMER
    );
}

UINT32 LegacyPciCardBusGetMemoryBaseAddressEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   x
){
    return LegacyPciReadUint32Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_MEMORY_BASE_ADDRESS_0 + ((x & 1) * 8) 
    );
}

UINT32 LegacyPciCardBusGetMemoryLimitEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   x
){
    return LegacyPciReadUint32Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_MEMORY_LIMIT_0 + ((x & 1) * 8) 
    );
}

UINT32 LegacyPciCardBusGetIoBaseAddressEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   x
){
    return LegacyPciReadUint32Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_IO_BASE_ADDRESS_0 + ((x & 1) * 8) 
    );
}

UINT32 LegacyPciCardBusGetIoLimitEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   x
){
    return LegacyPciReadUint32Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_IO_LIMIT_0 + ((x & 1) * 8) 
    );
}

UINT8 LegacyPciCardBusGetInterruptLineEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_INTERRUPT_LINE
    );
}

void LegacyPciCardBusSetInterruptLineEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   Value
){
    LegacyPciWriteUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_INTERRUPT_LINE,
        Value
    );
}

UINT8 LegacyPciCardBusGetInterruptPinEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_INTERRUPT_PIN
    );
}

UINT16 LegacyPciCardBusGetBridgeControlEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_BRIDGE_CONTROL
    );
}

UINT16 LegacyPciCardBusGetSubsystemDeviceIdEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_SUBSYSTEM_DEVICE_ID
    );
}

UINT16 LegacyPciCardBusGetSubsystemVendorIdEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_SUBSYSTEM_VENDOR_ID
    );
}

UINT32 LegacyPciCardBusGet16BitPcCardLegacyModeBaseAddressEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint32Ex(
        Bus,
        Slot,
        Function,
        PCI_CARDBUS_DEVICE_CONFIG_16BIT_PC_CARD_LEGACY_BASE
    );
}


UINT32 LegacyPciCardBusGetCardBusSocketExCaBaseAddress(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetCardBusSocketExCaBaseAddressEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciCardBusGetOffsetCapabilities(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetOffsetCapabilitiesEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciCardBusGetSecondaryStatus(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetSecondaryStatusEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

void LegacyPciCardBusSetSecondaryStatus(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT16              Value
){
    LegacyPciCardBusSetSecondaryStatusEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Value
    );
}

UINT8 LegacyPciCardBusGetPciBusNumber(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetPciBusNumberEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciCardBusGetCardBusNumber(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetCardBusNumberEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciCardBusGetSubordinateBusNumber(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetSubordinateBusNumberEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciCardBusGetCardBusLatencyTimer(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetCardBusLatencyTimerEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT32 LegacyPciCardBusGetMemoryBaseAddress(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               x
){
    return LegacyPciCardBusGetMemoryBaseAddressEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        x
    );
}

UINT32 LegacyPciCardBusGetMemoryLimit(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               x
){
    return LegacyPciCardBusGetMemoryLimitEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        x
    );
}

UINT32 LegacyPciCardBusGetIoBaseAddress(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               x
){
    return LegacyPciCardBusGetIoBaseAddressEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        x
    );
}

UINT32 LegacyPciCardBusGetIoLimit(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               x
){
    return LegacyPciCardBusGetIoLimitEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        x
    );
}

UINT8 LegacyPciCardBusGetInterruptLine(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetInterruptLineEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

void LegacyPciCardBusSetInterruptLine(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               Value
){
    LegacyPciCardBusSetInterruptLineEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Value
    );
}

UINT8 LegacyPciCardBusGetInterruptPin(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetInterruptPinEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciCardBusGetBridgeControl(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetBridgeControlEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciCardBusGetSubsystemDeviceId(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetSubsystemDeviceIdEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciCardBusGetSubsystemVendorId(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGetSubsystemVendorIdEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT32 LegacyPciCardBusGet16BitPcCardLegacyModeBaseAddress(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciCardBusGet16BitPcCardLegacyModeBaseAddressEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}
