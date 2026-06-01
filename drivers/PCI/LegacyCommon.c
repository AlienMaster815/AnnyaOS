//Tyler Grenier - LegacyCommon.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

UINT16 LegacyPciGetVendorIdEx(
    UINT8   Bus, 
    UINT8   Slot, 
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus,
        Slot,
        Function,
        PCI_CONFIG_VENDOR_ID
    );
}

UINT16 LegacyPciGetDeviceIdEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus,
        Slot, 
        Function,
        PCI_CONFIG_DEVICE_ID
    );
}

UINT16 LegacyPciGetCommandEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus,
        Slot,
        Function,
        PCI_CONFIG_COMMAND
    );
}

void LegacyPciSetCommandEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT16  Value
){
    LegacyPciWriteUint16Ex(
        Bus,
        Slot,
        Function,
        PCI_CONFIG_COMMAND,
        Value
    );

}

UINT16 LegacyPciGetStatusEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint16Ex(
        Bus,
        Slot,
        Function,
        PCI_CONFIG_STATUS
    );
}

void LegacyPciSetStatusEx(
    UINT8   Bus, 
    UINT8   Slot, 
    UINT8   Function, 
    UINT16  Value
){
    LegacyPciWriteUint16Ex(
        Bus, 
        Slot,
        Function,
        PCI_CONFIG_STATUS,
        Value
    );
}

UINT8 LegacyPciGetRevisionIdEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot, 
        Function,
        PCI_CONFIG_REVISION_ID
    );
}

UINT8 LegacyPciGetProgIfEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot, 
        Function,
        PCI_CONFIG_PROGIF
    );
}

UINT8 LegacyPciGetSubClassEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_CONFIG_SUBCLASS
    );
}

UINT8 LegacyPciGetClassCodeEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_CONFIG_CLASS_CODE
    );
}

UINT8 LegacyPciGetCacheLineSizeEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_CONFIG_CACHE_LINE_SIZE
    );
}

void LegacyPciSetCacheLineSizeEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   Value
){
    LegacyPciWriteUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_CONFIG_CACHE_LINE_SIZE,
        Value
    );
}


UINT8 LegacyPciGetLatencyTimerEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_CONFIG_LATENCY_TIMER
    );
}

void LegacyPciSetLatencyTimerEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   Value
){
    LegacyPciWriteUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_CONFIG_LATENCY_TIMER,
        Value
    );
}

UINT8 LegacyPciGetHeaderTypeEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_CONFIG_HEADER_TYPE
    );
}

UINT8 LegacyPciGetBistEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    return LegacyPciReadUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_CONFIG_BIST
    );
}

void LegacyPciSetBistEx(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT8   Value
){
    LegacyPciWriteUint8Ex(
        Bus, 
        Slot,
        Function,
        PCI_CONFIG_BIST,
        Value
    );
}

UINT16 LegacyPciGetVendorId(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetVendorIdEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciGetDeviceId(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetDeviceIdEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT16 LegacyPciGetCommand(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetCommandEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

void LegacyPciSetCommand(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT16              Value
){
    LegacyPciSetCommandEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Value
    );
}

UINT16 LegacyPciGetStatus(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetStatusEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

void LegacyPciSetStatus(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT16              Value
){
    LegacyPciSetStatusEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Value
    );
}

UINT8 LegacyPciGetRevisionId(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetRevisionIdEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciGetProgIf(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetProgIfEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciGetSubClass(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetSubClassEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciGetClassCode(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetClassCodeEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}


UINT8 LegacyPciGetCacheLineSize(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetCacheLineSizeEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

void LegacyPciSetCacheLineSize(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT8               Value
){
    LegacyPciSetCacheLineSizeEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Value
    );
}

UINT8 LegacyPciGetLatencyTimer(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetLatencyTimerEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

void LegacyPciSetLatencyTimer(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT8               Value
){
    LegacyPciSetLatencyTimerEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Value
    );
}

UINT8 LegacyPciGetHeaderType(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetHeaderTypeEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

UINT8 LegacyPciGetBist(
    PPCI_DEVICE_OBJECT PDEV
){
    return LegacyPciGetBistEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function
    );
}

void LegacyPciSetBist(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT8               Value
){
    LegacyPciSetBistEx(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Value
    );
}


