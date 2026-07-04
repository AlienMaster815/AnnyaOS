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

static void InitializeRequestsAndGroupsToHardwareLimitation(
    UINT32* RequestedVectorsp,
    UINT32* Groupedp,
    UINT32  HardwareLimitation
){
    UINT32 RequestedVectors = *RequestedVectorsp;
    UINT32 Grouped = 1;
    if(RequestedVectors > HardwareLimitation){
        Grouped++;
        RequestedVectors = ROUND_UP64(RequestedVectors, HardwareLimitation);
        RequestedVectors /= HardwareLimitation;
        while(RequestedVectors > HardwareLimitation){
            Grouped++;
            RequestedVectors =  ROUND_UP64(RequestedVectors, HardwareLimitation) / HardwareLimitation;
        }
    }
    *RequestedVectorsp = RequestedVectors; 
    *Groupedp = Grouped;   
}



DRIVER_EXPORT LOUSTATUS PciHalAllocatePciIrqVectors(PPCI_DEVICE_OBJECT PDEV, UINT32 RequestedVectors, UINT64 Flags){
    UINT16* NewVectors;    
    if(PDEV->InterruptVectors){
        return STATUS_UNSUCCESSFUL;
    }

    //if(PciHalPciSupportsMsix(PDEV)){
    //    LouPrint("PCI.SYS:Allocating MSI-X Vectors\n");
    //    while(1);
    //}else 
    if(PciHalPciSupportsMsi(PDEV)){
        UINT32 Grouped;
        InitializeRequestsAndGroupsToHardwareLimitation(
            &RequestedVectors,
            &Grouped,
            32
        );



        LouPrint("PCI.SYS:Allocating:%d MSI Vectors Handling:%d Items\n", (UINT64)RequestedVectors, (UINT64)Grouped);
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