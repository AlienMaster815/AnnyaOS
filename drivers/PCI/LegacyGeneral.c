//Tyler Grenier - LegacyGeneral.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

UINT32 LegacyPciGeneralDeviceGetBarEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   Bar
){
    return LegacyPciReadUint32Ex(
        Bus,
        Slot,
        Function,
        (UINT32)(Bar * 0x04 + PCI_GENERAL_DEVICE_CONFIG_BAR_STACK)
    );
}

void LegacyPciGeneralDeviceSetBarEx(
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
        (UINT32)(Bar * 0x04 + PCI_GENERAL_DEVICE_CONFIG_BAR_STACK),
        Value
    );
}

UINT32 LegacyPciGeneralDeviceGetCardBusCisPointerEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint32Ex(
        Bus,
        Slot,
        Function,
        PCI_GENERAL_DEVICE_CONFIG_CARDBUS_CIS_POINTER
    );
}

UINT16 LegacyPciGeneralDeviceGetSubsystemVendorIdEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus,
        Slot,
        Function,
        PCI_GENERAL_DEVICE_CONFIG_SUBSYSTEM_VENDOR_ID
    );
}

UINT16 LegacyPciGeneralDeviceGetSubsystemIdEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus,
        Slot,
        Function,
        PCI_GENERAL_DEVICE_CONFIG_SUBSYSTEM_ID
    );
}

UINT32 LegacyPciGeneralDeviceGetExpansionRomBaseEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint32Ex(
        Bus,
        Slot,
        Function,
        PCI_GENERAL_DEVICE_CONFIG_EXPANSION_ROM_BASE
    );
}

UINT8 LegacyPciGeneralDeviceGetCapabilitiesPointerEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_GENERAL_DEVICE_CONFIG_CAPABILITIES_POINTER
    );
}

UINT8 LegacyPciGeneralDeviceGetInterruptLineEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_GENERAL_DEVICE_CONFIG_INTERRUPT_LINE
    );
}

void LegacyPciGeneralDeviceSetInterruptLineEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   Value
){
    LegacyPciWriteUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_GENERAL_DEVICE_CONFIG_INTERRUPT_LINE,
        Value
    );
}

UINT8 LegacyPciGeneralDeviceGetInterruptPinEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_GENERAL_DEVICE_CONFIG_INTERRUPT_PIN
    );
}

UINT8 LegacyPciGeneralDeviceGetMinGrantEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_GENERAL_DEVICE_CONFIG_MIN_GRANT
    );
}

UINT8 LegacyPciGeneralDeviceGetMaxLatencyEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus,
        Slot,
        Function,
        PCI_GENERAL_DEVICE_CONFIG_MAX_LATENCY
    );
}



UINT32 LegacyPciGeneralDeviceGetBar(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               Bar
){
    return LegacyPciGeneralDeviceGetBarEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Bar
    );
}

void LegacyPciGeneralDeviceSetBar(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               Bar, 
    UINT32              Value
){
    LegacyPciGeneralDeviceSetBarEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Bar,
        Value
    );
}

UINT32 LegacyPciGeneralDeviceGetCardBusCisPointer(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGeneralDeviceGetCardBusCisPointerEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciGeneralDeviceGetSubsystemVendorId(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGeneralDeviceGetSubsystemVendorIdEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciGeneralDeviceGetSubsystemId(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGeneralDeviceGetSubsystemIdEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT32 LegacyPciGeneralDeviceGetExpansionRomBase(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGeneralDeviceGetExpansionRomBaseEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciGeneralDeviceGetCapabilitiesPointer(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGeneralDeviceGetCapabilitiesPointerEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciGeneralDeviceGetInterruptLine(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGeneralDeviceGetInterruptLineEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

void LegacyPciGeneralDeviceSetInterruptLine(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               Value
){
    LegacyPciGeneralDeviceSetInterruptLineEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Value
    );
}

UINT8 LegacyPciGeneralDeviceGetInterruptPin(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGeneralDeviceGetInterruptPinEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciGeneralDeviceGetMinGrant(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGeneralDeviceGetMinGrantEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciGeneralDeviceGetMaxLatency(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGeneralDeviceGetMaxLatencyEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}
