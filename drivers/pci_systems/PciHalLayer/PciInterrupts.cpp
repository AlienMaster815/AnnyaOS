#include <LouDDK.h>
#include <Hal.h>

KERNEL_IMPORT uint16_t GetNPROC();
KERNEL_IMPORT uint8_t GetTotalHardwareInterrupts();


UINT8 LouKeHalPciGetCapabilityPointer(
    PPCI_DEVICE_OBJECT   PDEV,
    UINT8               CapID
);

KERNEL_IMPORT
UINT8 LouKeHalGetPciIrqVector(PPCI_DEVICE_OBJECT PDEV, UINT8 Irq){
    return PDEV->InterruptVectors[Irq + 1];
}

LOUDDK_API_ENTRY
LOUSTATUS LouKeHalMallocPciIrqVectors(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT32              RequestedVectors, 
    uint64_t            Flags
){

    if(Flags & PCI_IRQ_USE_MSI_X){
        UNUSED UINT8 MsixCap = LouKeHalPciGetCapabilityPointer(PDEV, PCI_CAP_MSI_X);
        if(MsixCap){
            LouPrint("LouKeHalMallocPciIrqVectors() MsixCap\n");
            while(1);
        }
    
    }

    if(Flags & PCI_IRQ_USE_MSI){
        UNUSED UINT8 MsiCap = LouKeHalPciGetCapabilityPointer(PDEV, PCI_CAP_MSI);
        if(MsiCap){
            LouPrint("LouKeHalMallocPciIrqVectors() MsiCap\n");
            while(1);
        }
    
    }

    if(Flags & PCI_IRQ_USE_LEGACY){
        if(PDEV->InterruptVectors){
            LouPrint("ERROR:Device Already Has Allocated Interrutps\n");
            return STATUS_UNSUCCESSFUL;
        }

        PDEV->InterruptVectors = LouKeMallocArray(UINT8, 2, KERNEL_GENERIC_MEMORY);
        PDEV->InterruptVectors[0] = 1;
        PDEV->InterruptVectors[1] = LouKePciGetInterruptLine(PDEV);

        return STATUS_SUCCESS;
    }

    return STATUS_UNSUCCESSFUL;
}

LOUDDK_API_ENTRY
UINT8 LouKeHalGetPciIrqVectorCount(
    PPCI_DEVICE_OBJECT PDEV
){
    if(!PDEV->InterruptVectors){
        return 0;
    }
    return PDEV->InterruptVectors[0];
}