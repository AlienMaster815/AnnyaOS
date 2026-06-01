//Tyler Grenier - NativeCommon.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"


UINT16 NativePciGetVendorIdEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_CONFIG_VENDOR_ID);
}

UINT16 NativePciGetDeviceIdEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_CONFIG_DEVICE_ID);
}

UINT16 NativePciGetCommandEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_CONFIG_COMMAND);
}

void NativePciSetCommandEx(UINT32* DeviceBase, UINT16 Value){
    NativePciWriteUint16Ex(DeviceBase, PCI_CONFIG_COMMAND, Value);
}

UINT16 NativePciGetStatusEx(UINT32* DeviceBase){
    return NativePciReadUint16Ex(DeviceBase, PCI_CONFIG_STATUS);
}

void NativePciSetStatusEx(UINT32* DeviceBase, UINT16 Value){
    NativePciWriteUint16Ex(DeviceBase, PCI_CONFIG_STATUS, Value);
}

UINT8 NativePciGetRevisionIdEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_CONFIG_REVISION_ID);
}

UINT8 NativePciGetProgIfEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_CONFIG_PROGIF);
}

UINT8 NativePciGetSubClassEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_CONFIG_SUBCLASS);
}

UINT8 NativePciGetClassCodeEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_CONFIG_CLASS_CODE);
}

UINT8 NativePciGetCacheLineSizeEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_CONFIG_CACHE_LINE_SIZE);
}

void NativePciSetCacheLineSizeEx(UINT32* DeviceBase, UINT8 Value){
    NativePciWriteUint8Ex(DeviceBase, PCI_CONFIG_CACHE_LINE_SIZE, Value);
}

UINT8 NativePciGetLatencyTimerEx(UINT32* DeviceBase){
    //weak
    return 0;
}

void NativePciSetLatencyTimerEx(UINT32* DeviceBase, UINT8 Value){
    //weak
}

UINT8 NativePciGetHeaderTypeEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_CONFIG_HEADER_TYPE);
}

UINT8 NativePciGetBistEx(UINT32* DeviceBase){
    return NativePciReadUint8Ex(DeviceBase, PCI_CONFIG_BIST);
}

void NativePciSetBistEx(UINT32* DeviceBase, UINT8 Value){
    NativePciWriteUint8Ex(DeviceBase, PCI_CONFIG_BIST, Value);
}

UINT16 NativePciGetVendorId(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGetVendorIdEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciGetDeviceId(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGetDeviceIdEx(PDEV->EcamDeviceBase);
}

UINT16 NativePciGetCommand(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGetCommandEx(PDEV->EcamDeviceBase);
}

void NativePciSetCommand(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciSetCommandEx(PDEV->EcamDeviceBase, Value);
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}

UINT16 NativePciGetStatus(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGetStatusEx(PDEV->EcamDeviceBase);
}

void NativePciSetStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciSetStatusEx(PDEV->EcamDeviceBase, Value);
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}

UINT8 NativePciGetRevisionId(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGetRevisionIdEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciGetProgIf(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGetProgIfEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciGetSubClass(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGetSubClassEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciGetClassCode(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGetClassCodeEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciGetCacheLineSize(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGetCacheLineSizeEx(PDEV->EcamDeviceBase);
}

void NativePciSetCacheLineSize(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciSetCacheLineSizeEx(PDEV->EcamDeviceBase, Value);
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}

UINT8 NativePciGetLatencyTimer(PPCI_DEVICE_OBJECT PDEV){
    //weak
    return 0;
}

void NativePciSetLatencyTimer(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    //weak
}

UINT8 NativePciGetHeaderType(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGetHeaderTypeEx(PDEV->EcamDeviceBase);
}

UINT8 NativePciGetBist(PPCI_DEVICE_OBJECT PDEV){
    return NativePciGetBistEx(PDEV->EcamDeviceBase);
}

void NativePciSetBist(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciSetBistEx(PDEV->EcamDeviceBase, Value);
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}