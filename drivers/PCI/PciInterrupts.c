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
    UINT32 Grouped = ROUND_UP64(RequestedVectors, HardwareLimitation) / HardwareLimitation;
    *RequestedVectorsp = ROUND_UP64(RequestedVectors, HardwareLimitation) / Grouped; 
    *Groupedp = Grouped;   
}

LOUSTATUS PciHalDumbyInterruptHandler(UINT64 Foo){



}

DRIVER_EXPORT LOUSTATUS PciHalAllocatePciIrqVectors(PPCI_DEVICE_OBJECT PDEV, UINT32 RequestedVectors, UINT64 Flags){
    OPAQUE_PTR* NewVectors;   
    LOUSTATUS Status; 
    UINT8 Vector;
    if(PDEV->InterruptVectors){
        return STATUS_UNSUCCESSFUL;
    }

    //if(PciHalPciSupportsMsix(PDEV)){
    //    LouPrint("PCI.SYS:Allocating MSI-X Vectors\n");
    //    while(1);
    //}else 
    if(PciHalPciSupportsMsi(PDEV)){
        UINT32 Grouped;
        UINT32 HardwareLimitation = MIN(32, PciMsiGetMultiMessageCount(PDEV));
        LouPrint("PCI Hardware Limitation:%h\n", HardwareLimitation);
        InitializeRequestsAndGroupsToHardwareLimitation(
            &RequestedVectors,
            &Grouped,
            HardwareLimitation
        );

        UINT32 MmeBits = 0;
        UINT32 TmpCount = Grouped;

        while(TmpCount > 1){
            TmpCount >>= 1;
            MmeBits++;
        }

        NewVectors = LouKeMallocArray(OPAQUE_PTR, 2, KERNEL_GENERIC_MEMORY);
        NewVectors[0] = (UINT8*)(UINTPTR)RequestedVectors;
        Status = LouKeIpicAllocateVectorObjectsExWithApicIdLimitation(
            &NewVectors[1],
            false,
            LirRoutine,
            &PciHalDumbyInterruptHandler,
            0x00,
            RequestedVectors,
            RequestedVectors,
            254
        );
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Status = LouKeIpicGetVectorObjectVector(
            NewVectors[1],
            &Vector
        );
        if(Status != STATUS_SUCCESS){
            LouPrint("PCI.SYS:LouKeIpicGetVectorObjectVector()\n");
            while(1);
            return Status;
        }
        ULONG Processor;
        Status = LouKeIpicGetVectorObjectProcessorNumber(NewVectors[1], &Processor);
        if(Status != STATUS_SUCCESS){
            LouPrint("PCI.SYS:LouKeIpicGetVectorObjectProcessorNumber()\n");
            return Status;
        }
        UINT64 Address = 0xFEE00000;
        Address |= ((UINT32)ApicHalCpuIdToApicId(Processor) << 12);

        if(!PciMsiSetMessageAddress(PDEV, Address)){
            LouPrint("PCI.SYS:PciMsiSetMessageAddress()\n");
            while(1);
            return STATUS_UNSUCCESSFUL;
        }
        if(!PciMsiSetMessageData(PDEV, (UINT16)Vector)){
            LouPrint("PCI.SYS:PciMsiSetMessageData()\n");
            while(1);
            return STATUS_UNSUCCESSFUL;
        }
        UINT16 Control;
        if(!PciMsiGetMessageControl(PDEV, &Control)){
            LouPrint("PCI.SYS:PciMsiGetMessageControl()\n");
            while(1);
            return STATUS_UNSUCCESSFUL;
        }
        Control &= ~(0x07 << 4);
        Control |= ((MmeBits & 0x07) << 4);
        Control |= 0x01;
        if(!PciMsiSetMessageControl(PDEV, Control)){
            LouPrint("PCI.SYS:PciMsiSetMessageControl()\n");
            while(1);
            return STATUS_UNSUCCESSFUL;
        }
        PciHalSetCommand(PDEV, PciHalGetCommand(PDEV) | (1 << 10));
    }else{ 
        PciHalDbgPrint("PCI.SYS:Allocating INT-X Vectors\n");
        NewVectors = LouKeMallocArray(OPAQUE_PTR, 2, KERNEL_GENERIC_MEMORY);
        NewVectors[0] = (UINT8*)(UINTPTR)1;
        Status = LouKeIpicAllocateVectorObjects(
            &NewVectors[1],
            false,
            LirRoutine,
            &PciHalDumbyInterruptHandler,
            0x00,
            1
        );

        if(Status != STATUS_SUCCESS){
            return Status;
        }
        UINT8 Line = LouKeGetPciInterruptLineFromPin(PDEV);
        if(!Line){
            LouPrint("PciHalAllocatePciIrqVectors():ERROR No Pin\n");
            while(1);
        }
        Status = ApicHalInitializeVectorToIoApicRedirection(
            NewVectors[1],
            Line,
            IO_APIC_TRIGGER_MODE_LEVEL,
            IO_APIC_PIN_POLARITY_ACTIVE_LOW
        );
        if(Status != STATUS_SUCCESS){
            LouPrint("PciHalAllocatePciIrqVectors():ERROR No Redirect\n");
            while(1);
            return Status;
        }
    }
    PDEV->InterruptVectors = NewVectors;
    return STATUS_SUCCESS;
}

DRIVER_EXPORT void PciHalFreeIrqVectors(PPCI_DEVICE_OBJECT PDEV){
    LouPrint("PCI.SYS:PciHalFreeIrqVectors()\n");
    while(1);
}

DRIVER_EXPORT UINT32 PciHalGetIrqVectorCount(PPCI_DEVICE_OBJECT PDEV){
    return (UINT32)(UINTPTR)(UINT8*)PDEV->InterruptVectors[0];
}

DRIVER_EXPORT UINT8 PciHalGetIrqVector(PPCI_DEVICE_OBJECT PDEV, UINT32 Member){
    if(Member >= PciHalGetIrqVectorCount(PDEV)){
        return 0x00;
    }
    LOUSTATUS Status;
    UINT8 Result;
    if(PciHalGetIrqVectorCount(PDEV) == 1){
        Status = LouKeIpicGetVectorObjectVector(
            PDEV->InterruptVectors[1],
            &Result
        );
        if(Status != STATUS_SUCCESS){
            return 0x00;
        }
        return Result;
    }

    LouPrint("PciHalGetIrqVector()\n");
    while(1);
    //return PDEV->InterruptVectors[Member + 1];
    return 0x00;
}

DRIVER_EXPORT LOUSTATUS PciHalConnectIrqHandler(
    PPCI_DEVICE_OBJECT  PDEV,
    OPAQUE_PTR          Routine, 
    IPIC_ROUTINE_TYPE   RoutineType, 
    UINT64              LirData,
    UINT32              Member       
){
    if(Member >= PciHalGetIrqVectorCount(PDEV)){
        return STATUS_INVALID_PARAMETER;
    }

    LOUSTATUS Status;
    if(PciHalGetIrqVectorCount(PDEV) == 1){
        Status = LouKeIpicChangeVectorObjectHandlerProperties(
            PDEV->InterruptVectors[1],
            Routine,
            RoutineType,
            LirData
        );
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        return LouKeIpicSoftwareMaskVectorObject(PDEV->InterruptVectors[1], 0, false);
    }

    LouPrint("PciHalConnectIrqHandler()\n");
    while(1);
    return STATUS_SUCCESS;
}