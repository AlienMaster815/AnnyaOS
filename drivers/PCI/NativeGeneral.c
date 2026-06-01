//Tyler Grenier - NativeGeneral.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

UINT32 NativePciGeneralDeviceGetBarEx(UINT32* DeviceBase, UINT8 Bar){
    return NativePciReadUint32Ex(
        DeviceBase, 
        (UINT32)(Bar * 0x04 + PCI_GENERAL_DEVICE_CONFIG_BAR_STACK)
    );
}

void NativePciGeneralDeviceSetBarEx(UINT32* DeviceBase, UINT8 Bar, UINT32 Value){
    NativePciWriteUint32Ex(
        DeviceBase, 
        (UINT32)(Bar * 0x04 + PCI_GENERAL_DEVICE_CONFIG_BAR_STACK),
        Value
    );
}

UINT32 NativePciGeneralDeviceGetCardBusCisPointerEx(UINT32* DeviceBase){
    return NativePciReadUint32Ex(
        DeviceBase,
        PCI_GENERAL_DEVICE_CONFIG_CARDBUS_CIS_POINTER
    );
}

UINT16 NativePciGeneralDeviceGetSubsystemVendorIdEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(
        DeviceBase,
        PCI_GENERAL_DEVICE_CONFIG_SUBSYSTEM_VENDOR_ID
    );
}

UINT16 NativePciGeneralDeviceGetSubsystemIdEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(
        DeviceBase,
        PCI_GENERAL_DEVICE_CONFIG_SUBSYSTEM_ID
    );
}

UINT32 NativePciGeneralDeviceGetExpansionRomBaseEx(UINT32* DeviceBase){
    return NativePciReadUint32Ex(
        DeviceBase,
        PCI_GENERAL_DEVICE_CONFIG_EXPANSION_ROM_BASE
    );
}

UINT8 NativePciGeneralDeviceGetCapabilitiesPointerEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(
        DeviceBase,
        PCI_GENERAL_DEVICE_CONFIG_CAPABILITIES_POINTER
    );
}

UINT8 NativePciGeneralDeviceGetInterruptLineEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(
        DeviceBase,
        PCI_GENERAL_DEVICE_CONFIG_INTERRUPT_LINE
    );
}

void NativePciGeneralDeviceSetInterruptLineEx(UINT32* DeviceBase, UINT8 Value){
    NativePciWriteUint8Ex(
        DeviceBase,
        PCI_GENERAL_DEVICE_CONFIG_INTERRUPT_LINE,
        Value
    );
}

UINT8 NativePciGeneralDeviceGetInterruptPinEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(
        DeviceBase,
        PCI_GENERAL_DEVICE_CONFIG_INTERRUPT_PIN
    );
}

UINT8 NativePciGeneralDeviceGetMinGrantEx(UINT32* DeviceBase){
    //weak
    return 0;
}

UINT8 NativePciGeneralDeviceGetMaxLatencyEx(UINT32* DeviceBase){
    //weak
    return 0;
}



UINT32 NativePciGeneralDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar){
    return NativePciGeneralDeviceGetBarEx(PDEV->EcamDeviceBase, Bar);
}

void NativePciGeneralDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciGeneralDeviceSetBarEx(PDEV->EcamDeviceBase, Bar, Value);
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}

UINT32 NativePciGeneralDeviceGetCardBusCisPointer(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGeneralDeviceGetCardBusCisPointerEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciGeneralDeviceGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGeneralDeviceGetSubsystemVendorIdEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciGeneralDeviceGetSubsystemId(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGeneralDeviceGetSubsystemIdEx(PDEV->EcamDeviceBase);
}

UINT32 NativePciGeneralDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGeneralDeviceGetExpansionRomBaseEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciGeneralDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGeneralDeviceGetCapabilitiesPointerEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciGeneralDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGeneralDeviceGetInterruptLineEx(PDEV->EcamDeviceBase);
}

void NativePciGeneralDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciGeneralDeviceSetInterruptLineEx(PDEV->EcamDeviceBase, Value);
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}

UINT8 NativePciGeneralDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGeneralDeviceGetInterruptPinEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciGeneralDeviceGetMinGrant(PPCI_DEVICE_OBJECT PDEV){
    //weak
    return 0;
}
UINT8 NativePciGeneralDeviceGetMaxLatency(PPCI_DEVICE_OBJECT PDEV){
    //weak
    return 0;
}
