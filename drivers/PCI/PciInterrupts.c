//Tyler Grenier - PciInterrupts.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

KERNEL_EXPORT uint8_t LouKeGetPciInterruptLineFromPin(PPCI_DEVICE_OBJECT PDEV);


static BOOLEAN PciHalPciSupportsMsix(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCapabilitiesPointer(PDEV, PCI_CAPABILITY_MSI, false)) ? true : false; 
}

static BOOLEAN PciHalPciSupportsMsi(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCapabilitiesPointer(PDEV, PCI_CAPABILITY_MSI, false)) ? true : false; 
}

DRIVER_EXPORT LOUSTATUS PciHalAllocatePciIrqVectors(PPCI_DEVICE_OBJECT PDEV, UINT32 RequestedVectors, UINT64 Flags){
    BOOLEAN PciSupportsMsix = PciHalPciSupportsMsix(PDEV);
    BOOLEAN PciSupportsMsi = PciHalPciSupportsMsi(PDEV);
    UINT16* NewVectors;
    
    if(PDEV->InterruptVectors){
        return STATUS_UNSUCCESSFUL;
    }

    if(PciSupportsMsix){
        LouPrint("PCI.SYS:Allocating MSI-X Vectors\n");
        while(1);
    }else if(PciSupportsMsi){
        LouPrint("PCI.SYS:Allocating MSI Vectors\n");
        while(1);
    }else{ 
        PciHalDbgPrint("PCI.SYS:Allocating INT-X Vectors\n");
        NewVectors = LouKeMallocArray(UINT16, 2, KERNEL_GENERIC_MEMORY);
        NewVectors[0] = 1;
        NewVectors[1] = LouKeGetPciInterruptLineFromPin(PDEV);
        if(!NewVectors[1]){
            LouPrint("PCI.SYS:PciHalAllocatePciIrqVectors():ERROR:Unable To Get Interrupt Line From Pin\n");
            LouKeFree(NewVectors);
            return STATUS_UNSUCCESSFUL;
        }
        NewVectors[1] += 32;
        PciHalDbgPrint("PCI.SYS:Using Vector:%h\n", (UINT64)NewVectors[1]);
    }
    
    PDEV->InterruptVectors = NewVectors;
    return STATUS_SUCCESS;
}

DRIVER_EXPORT void PciHalFreeIrqVectors(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalFreeIrqVectors()\n");
    while(1);
}

DRIVER_EXPORT UINT16 PciHalGetIrqVectorCount(PPCI_DEVICE_OBJECT PDEV){
    return PDEV->InterruptVectors[0];
}

DRIVER_EXPORT UINT8 PciHalGetIrqVector(PPCI_DEVICE_OBJECT PDEV, UINT8 Member){
    if(Member >= PciHalGetIrqVectorCount(PDEV)){
        return 0x00;
    }
    return PDEV->InterruptVectors[Member + 1];
}