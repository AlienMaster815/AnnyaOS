//Tyler Grenier - PciHal.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

/*
    BOOLEAN     (*PciHalPciSupportsSpecialCycles)           (PPCI_DEVICE_OBJECT PDEV);
    BOOLEAN     (*PciHalPciSupportsMemoryWriteInvalidate)   (PPCI_DEVICE_OBJECT PDEV);
    BOOLEAN     (*PciHalPciSupportsVgaPaletteSnooping)      (PPCI_DEVICE_OBJECT PDEV);
    LOUSTATUS   (*PciHalEnableParityErrorResponce)          (PPCI_DEVICE_OBJECT PDEV);
    LOUSTATUS   (*PciHalDisableParityErrorResponce)         (PPCI_DEVICE_OBJECT PDEV);
    BOOLEAN     (*PciHalIsParityErrorResponceEnabled)       (PPCI_DEVICE_OBJECT PDEV);
    LOUSTATUS   (*PciHalEnableSerr)                         (PPCI_DEVICE_OBJECT PDEV);
    LOUSTATUS   (*PciHalDisableSerr)                        (PPCI_DEVICE_OBJECT PDEV);
    BOOLEAN     (*PciHalIsSerrEnabled)                      (PPCI_DEVICE_OBJECT PDEV);
    BOOLEAN     (*PciHalIsFastBackToBackEnabled)            (PPCI_DEVICE_OBJECT PDEV);
    LOUSTATUS   (*PciHalEnableInterrupts)                   (PPCI_DEVICE_OBJECT PDEV);
    LOUSTATUS   (*PciHalDisableInterrupts)                  (PPCI_DEVICE_OBJECT PDEV);
    BOOLEAN     (*PciHalAreInterruptsEnabled)               (PPCI_DEVICE_OBJECT PDEV);
*/

DRIVER_EXPORT LOUSTATUS PciHalEnableIoSpace(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalEnableIoSpace()\n");
    while(1);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalDisableIoSpace(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalDisableIoSpace()\n");
    while(1);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalIsIoSpaceEnabled(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalIsIoSpaceEnabled()\n");
    while(1);
    return true;
}

DRIVER_EXPORT LOUSTATUS PciHalEnableMemorySpace(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalEnableMemorySpace()\n");
    while(1);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalDisableMemorySpace(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalDisableMemorySpace()\n");
    while(1);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalIsMemorySpaceEnabled(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalDisableMemorySpace()\n");
    while(1);
    return true;
}

DRIVER_EXPORT LOUSTATUS PciHalEnableBusMaster(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalEnableBusMaster()\n");
    while(1);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalDisableBusMaster(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalDisableBusMaster()");
    while(1);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalIsBusMasterEnabled(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalIsBusMasterEnabled()\n");
    while(1);
    return true;
}

DRIVER_EXPORT LOUSTATUS PciHalMapPciResource(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               Bar, 
    UINT64              PageFlags
){

    LouPrint("PciHalMapPciResource()\n");
    while(1);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT PVOID PciHalGetIoRegion(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT8               Bar,
    SIZE                Offset
){
    LouPrint("PCI.SYS:PciHalGetIoRegion()\n");
    while(1);
    return 0x00;
}

DRIVER_EXPORT LOUSTATUS PciHalAllocatePciIrqVectors(PPCI_DEVICE_OBJECT PDEV, UINT32 RequestedVectors, UINT64 Flags){
    LouPrint("PCI.SYS:PciHalAllocatePciIrqVectors()\n");
    while(1);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT UINT8 PciHalGetIrqVector(PPCI_DEVICE_OBJECT PDEV, UINT8 Member){
    LouPrint("PCI.SYS:PciHalGetIrqVector()\n");
    while(1);
    return 0;
}

DRIVER_EXPORT void PciHalFreeIrqVectors(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalFreeIrqVectors()\n");
    while(1);
}

DRIVER_EXPORT UINT8 PciHalGetIrqVectorCount(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalGetIrqVectorCount()\n");
    while(1);
    return 0;
}

DRIVER_EXPORT void PciHalGetConfigurationSnapshot(PPCI_DEVICE_OBJECT PDEV, PPCI_COMMON_CONFIG Config){
    LouPrint("PCI.SYS:PciHalGetConfigurationSnapshot()\n");
    while(1);
}

DRIVER_EXPORT SIZE PciHalGetBarSize(
    PPCI_DEVICE_OBJECT PDEV, 
    UINT8 Bar
){
    LouPrint("PCI.SYS:PciHalGetBarSize()\n");
    while(1);
    return 0;
}