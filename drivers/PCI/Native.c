//Tyler Grenier - Native.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

//IO NOTE:
//PCIe by spec allows ECAM access with 8 bit 16 bit and 32 bit
//unlike legacy implementations using the IO instructions from
//the intel 8086 however due to some real implementations of
//PCIe not respectiong multibyte access i am doing 32 bit 
//accesses like the traditional PCI legacy implementations

#include "Pci.h"

static volatile PULONG PcieGetMemoryAddress(
    UINT32* DeviceBase,
    UINT32  Offset
){
    return (volatile PULONG)((UINTPTR)DeviceBase + (Offset & 0x0FFC));
}

UINT32 NativePciReadUint32Ex(
    UINT32* DeviceBase,
    UINT32  Offset
){
    volatile PULONG Register = PcieGetMemoryAddress(
        DeviceBase,
        Offset
    );
    return (UINT32)READ_REGISTER_ULONG(Register);
}

void NativePciWriteUint32Ex(
    UINT32* DeviceBase,
    UINT32  Offset,
    UINT32  Value
){
    volatile PULONG Register = PcieGetMemoryAddress(
        DeviceBase,
        Offset
    );
    WRITE_REGISTER_ULONG(Register, Value);
}

UINT16 NativePciReadUint16Ex(
    UINT32* DeviceBase,
    UINT32  Offset
){
    UINT32 Tmp = NativePciReadUint32Ex(
        DeviceBase,
        Offset
    );
    return (UINT16)((Tmp >> ((Offset & 0x02) * 8)) & UINT16_MAX);
}

void NativePciWriteUint16Ex(
    UINT32* DeviceBase,
    UINT32  Offset,
    UINT16  Value
){
    UINT32 Tmp = NativePciReadUint32Ex(
        DeviceBase,
        Offset
    );
    UINT8 Shift = ((Offset & 0x02) * 8);
    Tmp &= ~((UINT32)UINT16_MAX << Shift);
    Tmp |= ((UINT32)Value << Shift);
    NativePciWriteUint32Ex(
        DeviceBase,
        Offset,
        Tmp
    );
}

UINT8 NativePciReadUint8Ex(
    UINT32* DeviceBase,
    UINT32  Offset
){
    UINT32 Tmp = NativePciReadUint32Ex(
        DeviceBase,
        Offset
    );
    return (UINT8)((Tmp >> ((Offset & 0x03) * 8)) & UINT8_MAX);
}

void NativePciWriteUint8Ex(
    UINT32* DeviceBase,
    UINT32  Offset,
    UINT8   Value
){
    UINT32 Tmp = NativePciReadUint32Ex(
        DeviceBase,
        Offset
    );
    UINT8 Shift = ((Offset & 0x03) * 8);
    Tmp &= ~((UINT32)UINT8_MAX << Shift);
    Tmp |= ((UINT32)Value << Shift);
    NativePciWriteUint32Ex(
        DeviceBase,
        Offset,
        Tmp
    );
}

UINT32 NativePciReadUint32(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset
){
    return NativePciReadUint32Ex(
        PDEV->EcamDeviceBase,
        Offset
    );
}

void NativePciWriteUint32(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset,
    UINT32              Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciWriteUint32Ex(
        PDEV->EcamDeviceBase,
        Offset,
        Value
    );
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}


UINT16 NativePciReadUint16(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset
){
    return NativePciReadUint16Ex(
        PDEV->EcamDeviceBase,
        Offset
    );
}

void NativePciWriteUint16(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset,
    UINT16              Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciWriteUint16Ex(
        PDEV->EcamDeviceBase,
        Offset,
        Value
    );
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}

UINT8 NativePciReadUint8(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset
){
    return NativePciReadUint8Ex(
        PDEV->EcamDeviceBase,
        Offset
    );
}

void NativePciWriteUint8(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset,
    UINT8               Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&PDEV->ConfigSpaceLock, &Irql);
    NativePciWriteUint8Ex(
        PDEV->EcamDeviceBase,
        Offset,
        Value
    );
    LouKeReleaseSpinLock(&PDEV->ConfigSpaceLock, &Irql);
}