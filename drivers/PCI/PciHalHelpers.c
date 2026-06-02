//Tyler Grenier - PciHal.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

/*
    LOUSTATUS   (*PciHalEnableIoSpace)                      (PPCI_DEVICE_OBJECT PDEV);
    LOUSTATUS   (*PciHalDisableIoSpace)                     (PPCI_DEVICE_OBJECT PDEV);
    BOOLEAN     (*PciHalIsIoSpaceEnabled)                   (PPCI_DEVICE_OBJECT PDEV);
    LOUSTATUS   (*PciHalEnableMemorySpace)                  (PPCI_DEVICE_OBJECT PDEV);
    LOUSTATUS   (*PciHalDisableMemorySpace)                 (PPCI_DEVICE_OBJECT PDEV);
    BOOLEAN     (*PciHalIsMemorySpaceEnabled)               (PPCI_DEVICE_OBJECT PDEV);
    LOUSTATUS   (*PciHalEnableBusMaster)                    (PPCI_DEVICE_OBJECT PDEV);
    LOUSTATUS   (*PciHalDisableBusMaster)                   (PPCI_DEVICE_OBJECT PDEV);
    BOOLEAN     (*PciHalIsBusMasterEnabled)                 (PPCI_DEVICE_OBJECT PDEV);
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
