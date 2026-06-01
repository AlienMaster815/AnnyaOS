//Tyler Grenier - Legacy.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

//OFFSET NOTE:
//Offsets of the pci legacy specification 0 - 3.0
//are defined as a scope of 0 - 0xFF or UINT8 Type
//but im using UINT32 so i dont need to cast upstream
//in the abstraction - Tyler Grenier

//IO NOTE:
//IO is done through the IO PIN controller introduced
//with the Intel 8086 using 32 bit or LONG ports so for
//IO shorter than 4 bytes i am using the offsets lower 
//3 bits to shift the 32 bit results and masking according
//to the size of the required type for example
//0b00 = 0, 0b01 = 8, 0b10 = 16, 0b11 = 24 
//and then masking either 0x02 OR 0b10 or 0x03 0b11

#include "Pci.h"

static spinlock_t GlobalPciConfigLock = {0};

static UINT32 LegacyPciConfigLongAddress(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT32  Offset
){
    return ((UINT32)Bus << 16) | ((UINT32)Slot << 11) | ((UINT32)Function << 8) | ((UINT32)Offset & 0xFC) | ((UINT32)0x80000000);
}

static UINT32 LegacyPciReadUint32ExNs(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT32  Offset
){
    UINT32 Address = LegacyPciConfigLongAddress(
        Bus, 
        Slot,
        Function,
        Offset
    );
    outl(PCI_CONFIG_ADDRESS_PORT, Address);
    return inl(PCI_CONFIG_DATA_PORT);
}

static void LegacyPciWriteUint32ExNs(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT32  Offset,
    UINT32  Data
){
    UINT32 Address = LegacyPciConfigLongAddress(
        Bus, 
        Slot,
        Function,
        Offset
    );
    outl(PCI_CONFIG_ADDRESS_PORT, Address);
    outl(PCI_CONFIG_DATA_PORT, Data);
}

UINT32 LegacyPciReadUint32Ex(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT32  Offset
){
    UINT32 Result;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&GlobalPciConfigLock, &Irql);
    Result = LegacyPciReadUint32ExNs(
        Bus,
        Slot,
        Function,
        Offset
    );
    LouKeReleaseSpinLock(&GlobalPciConfigLock, &Irql);
    return Result;
}


void LegacyPciWriteUint32Ex(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT32  Offset,
    UINT32  Data
){
    UINT32 Result;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&GlobalPciConfigLock, &Irql);
    LegacyPciWriteUint32ExNs(
        Bus,
        Slot,
        Function,
        Offset,
        Data
    );
    LouKeReleaseSpinLock(&GlobalPciConfigLock, &Irql);
}

UINT16 LegacyPciReadUint16Ex(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT32  Offset
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&GlobalPciConfigLock, &Irql);
    UINT32 Tmp = LegacyPciReadUint32ExNs(
        Bus, 
        Slot, 
        Function, 
        Offset
    );
    LouKeReleaseSpinLock(&GlobalPciConfigLock, &Irql);
    return (UINT16)((Tmp >> ((Offset & 0x02) * 8)) & UINT16_MAX);
}

void LegacyPciWriteUint16Ex(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT32  Offset,
    UINT16  Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&GlobalPciConfigLock, &Irql);
    UINT32 Tmp = LegacyPciReadUint32ExNs(
        Bus,
        Slot, 
        Function,
        Offset
    );
    UINT8 Shift = ((Offset & 0x02) * 8);
    Tmp &= ~((UINT32)UINT16_MAX << Shift);
    Tmp |= ((UINT32)Value << Shift);
    LegacyPciWriteUint32ExNs(
        Bus,
        Slot,
        Function,
        Offset,
        Tmp
    );
    LouKeReleaseSpinLock(&GlobalPciConfigLock, &Irql);
}

UINT8
LegacyPciReadUint8Ex(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT32  Offset
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&GlobalPciConfigLock, &Irql);
    UINT32 Tmp = LegacyPciReadUint32ExNs(
        Bus,
        Slot,
        Function,
        Offset
    );
    LouKeReleaseSpinLock(&GlobalPciConfigLock, &Irql);
    return (UINT8)((Tmp >> ((Offset & 0x03) * 8)) & UINT8_MAX);
}

void
LegacyPciWriteUint8Ex(
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT32  Offset,
    UINT8   Value
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&GlobalPciConfigLock, &Irql);
    UINT32 Tmp = LegacyPciReadUint32ExNs(
        Bus,
        Slot, 
        Function,
        Offset
    );
    UINT8 Shift = ((Offset & 0x03) * 8);
    Tmp &= ~((UINT32)UINT8_MAX << Shift);
    Tmp |= ((UINT32)Value << Shift);
    LegacyPciWriteUint32ExNs(
        Bus,
        Slot,
        Function,
        Offset,
        Tmp
    );
    LouKeReleaseSpinLock(&GlobalPciConfigLock, &Irql);
}

UINT32 LegacyPciReadUint32(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset
){
    return LegacyPciReadUint32Ex(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Offset
    );
}

void LegacyPciWriteUint32(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset,
    UINT32              Value
){
    LegacyPciWriteUint32Ex(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Offset,
        Value
    );
}

UINT16 LegacyPciReadUint16(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset
){
    return LegacyPciReadUint16Ex(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Offset
    );
}

void LegacyPciWriteUint16(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset,
    UINT16              Value
){
    LegacyPciWriteUint16Ex(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Offset,
        Value
    );
}

UINT8 LegacyPciReadUint8(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset
){
    return LegacyPciReadUint8Ex(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Offset
    );
}

void LegacyPciWriteUint8(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT32              Offset,
    UINT8               Value
){
    LegacyPciWriteUint8Ex(
        PDEV->Bus,
        PDEV->Slot,
        PDEV->Function,
        Offset,
        Value
    );
}