//Tyler Grenier - PciHalHelpers.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

DRIVER_EXPORT LOUSTATUS PciHalEnableIoSpace(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(Command & 1){
        PciHalDbgPrint("PCI.SYS:IO Space Already Enabled\n");
        return STATUS_SUCCESS;
    }
    PciHalSetCommand(PDEV, Command | 1);
    Command = PciHalGetCommand(PDEV);
    if(!(Command & 1)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Enable IO Space\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalDisableIoSpace(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(!(Command & 1)){
        PciHalDbgPrint("PCI.SYS:IO Space Already Disabled\n");
        return STATUS_SUCCESS;
    }
    PciHalSetCommand(PDEV, Command & ~1);
    Command = PciHalGetCommand(PDEV);
    if(Command & 1){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Disabled IO Space\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalIsIoSpaceEnabled(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCommand(PDEV) & 1) ? true : false;
}

DRIVER_EXPORT LOUSTATUS PciHalEnableMemorySpace(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(Command & (1 << 1)){
        PciHalDbgPrint("PCI.SYS:Memory Space Already Enabled\n");
        return STATUS_SUCCESS;
    }
    PciHalSetCommand(PDEV, Command | (1 << 1));
    Command = PciHalGetCommand(PDEV);
    if(!(Command & (1 << 1))){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Enable Memory Space\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalDisableMemorySpace(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(!(Command & (1 << 1))){
        PciHalDbgPrint("PCI.SYS:Memory Space Already Disabled\n");
        return STATUS_SUCCESS;
    }
    PciHalSetCommand(PDEV, Command & ~(1 << 1));
    Command = PciHalGetCommand(PDEV);
    if(Command & (1 << 1)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Disabled Memory Space\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalIsMemorySpaceEnabled(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCommand(PDEV) & (1 << 1)) ? true : false;
}

DRIVER_EXPORT LOUSTATUS PciHalEnableBusMaster(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(Command & (1 << 2)){
        PciHalDbgPrint("PCI.SYS:Bus Master Already Enabled\n");
        return STATUS_SUCCESS;
    }
    PciHalSetCommand(PDEV, Command | (1 << 2));
    Command = PciHalGetCommand(PDEV);
    if(!(Command & (1 << 2))){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Enable Bus Master\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalDisableBusMaster(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(!(Command & (1 << 2))){
        PciHalDbgPrint("PCI.SYS:Bus Master Already Disabled\n");
        return STATUS_SUCCESS;
    } 
    PciHalSetCommand(PDEV, Command & ~(1 << 2));
    Command = PciHalGetCommand(PDEV);
    if(Command & (1 << 2)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Disable Bus Mastering\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalIsBusMasterEnabled(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCommand(PDEV) & (1 << 2)) ? true : false;
}

DRIVER_EXPORT BOOLEAN PciHalPciSupportsSpecialCycles(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCommand(PDEV) & (1 << 3)) ? true : false;
}

DRIVER_EXPORT BOOLEAN PciHalPciHasMemoryWriteInvalidateEnabled(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCommand(PDEV) & (1 << 4)) ? true : false;
}

DRIVER_EXPORT BOOLEAN PciHalPciSupportsVgaPaletteSnooping(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCommand(PDEV) & (1 << 5)) ? false : true;
}

DRIVER_EXPORT LOUSTATUS PciHalEnableParityErrorResponce(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(Command & (1 << 6)){
        PciHalDbgPrint("PCI.SYS:Parrity Error Responce Already Enabled\n");
        return STATUS_SUCCESS;
    }
    PciHalSetCommand(PDEV, Command | (1 << 6));
    Command = PciHalGetCommand(PDEV);
    if(!(Command & (1 << 6))){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Enable Parrity Error Responce\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalDisableParityErrorResponce(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(!(Command & (1 << 6))){
        PciHalDbgPrint("PCI.SYS:Parrity Error Responce Already Disabled\n");
        return STATUS_SUCCESS;
    }
    PciHalSetCommand(PDEV, Command & ~(1 << 6));
    Command = PciHalGetCommand(PDEV);
    if(Command & (1 << 6)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Disable Parrity Error Responce\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalIsParityErrorResponceEnabled(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCommand(PDEV) & (1 << 6)) ? true : false;
}

DRIVER_EXPORT LOUSTATUS PciHalEnableSerr(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(Command & (1 << 8)){
        PciHalDbgPrint("PCI.SYS:SERR Is Already Enabled\n");
        return STATUS_SUCCESS;   
    }
    PciHalSetCommand(PDEV, Command | (1 << 8));
    Command = PciHalGetCommand(PDEV);
    if(!(Command & (1 << 8))){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Enable SERR\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalDisableSerr(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(Command & (1 << 8)){
        PciHalDbgPrint("PCI.SYS:SERR Is Already Disabled\n");
        return STATUS_SUCCESS;   
    }
    PciHalSetCommand(PDEV, Command & ~(1 << 8));
    Command = PciHalGetCommand(PDEV);
    if(Command & (1 << 8)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Disable SERR\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalIsSerrEnabled(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCommand(PDEV) & (1 << 8)) ? true : false;
}

DRIVER_EXPORT BOOLEAN PciHalIsFastBackToBackEnabled(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCommand(PDEV) & (1 << 9)) ? true : false;
}

DRIVER_EXPORT LOUSTATUS PciHalEnableInterrupts(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(!(Command & (1 << 10))){
        PciHalDbgPrint("PCI.SYS:Interrupt Are Already Enabled\n");
        return STATUS_SUCCESS;
    } 
    PciHalSetCommand(PDEV, Command & ~(1 << 10));
    Command = PciHalGetCommand(PDEV);
    if(Command & (1 << 10)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Enable Interrupts\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalDisableInterrupts(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Command = PciHalGetCommand(PDEV);
    if(Command & (1 << 10)){
        PciHalDbgPrint("PCI.SYS:Interrupt Are Already Disabled\n");
        return STATUS_SUCCESS;
    } 
    PciHalSetCommand(PDEV, Command | (1 << 10));
    Command = PciHalGetCommand(PDEV);
    if(!(Command & (1 << 10))){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Disable Interrupts\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalAreInterruptsEnabled(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetCommand(PDEV) & (1 << 10)) ? false : true;
}

DRIVER_EXPORT BOOLEAN PciHalGetPciInterruptStatus(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetStatus(PDEV) & (1 << 3)) ? true : false;
}

DRIVER_EXPORT BOOLEAN PciHalPciHasCapabiltiesList(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetStatus(PDEV) & (1 << 4)) ? true : false;
}

DRIVER_EXPORT BOOLEAN PciHalPciSupports66Mhz(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetStatus(PDEV) & (1 << 5)) ? true : false; 
}

DRIVER_EXPORT BOOLEAN PciHalPciSupportsFastBackToBack(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetStatus(PDEV) & (1 << 7)) ? true : false;
}

DRIVER_EXPORT BOOLEAN PciHalPciIsAssertingMasterDataParrityError(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetStatus(PDEV) & (1 << 8)) ? true : false;
}

DRIVER_EXPORT LOUSTATUS PciHalClearMasterDataParrityError(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Status = PciHalGetStatus(PDEV);
    if(!(Status & (1 << 8))){
        PciHalDbgPrint("PCI.SYS:Master Data Parrity Error Is Already Cleard\n");
        return STATUS_SUCCESS;
    }
    PciHalSetStatus(PDEV, (1 << 8));
    Status = PciHalGetStatus(PDEV);
    if(Status & (1 << 8)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Clear Master Data Parrity Error\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT UINT8 PciHalGetDevselTiming(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Status = PciHalGetStatus(PDEV);
    return (UINT8)((Status >> 9) & 0x03);
}

DRIVER_EXPORT BOOLEAN PciHalPciIsAssertingSignaledTargetAbort(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetStatus(PDEV) & (1 << 11)) ? true : false;
}

DRIVER_EXPORT LOUSTATUS PciHalClearSignaledTargetAbort(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Status = PciHalGetStatus(PDEV);
    if(!(Status & (1 << 11))){
        PciHalDbgPrint("PCI.SYS:Signaled Target Abort Is Already Cleared\n");
        return STATUS_SUCCESS;
    }
    PciHalSetStatus(PDEV, (1 << 11));
    Status = PciHalGetStatus(PDEV);
    if(Status & (1 << 11)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Clear Signaled Target Abort\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalPciIsAssertingReceivedTargetAbort(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetStatus(PDEV) & (1 << 12)) ? true : false;
}


DRIVER_EXPORT LOUSTATUS PciHalClearReceivedTargetAbort(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Status = PciHalGetStatus(PDEV);
    if(!(Status & (1 << 12))){
        PciHalDbgPrint("PCI.SYS:Received Target Abort Is Already Cleared\n");
        return STATUS_SUCCESS;
    }
    PciHalSetStatus(PDEV, (1 << 12));
    Status = PciHalGetStatus(PDEV);
    if(Status & (1 << 12)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Clear Received Target Abort\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalPciIsAssertingReceivedMasterAbort(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetStatus(PDEV) & (1 << 13)) ? true : false;
}


DRIVER_EXPORT LOUSTATUS PciHalClearReceivedMasterAbort(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Status = PciHalGetStatus(PDEV);
    if(!(Status & (1 << 13))){
        PciHalDbgPrint("PCI.SYS:Received Master Abort Is Already Cleared\n");
        return STATUS_SUCCESS;
    }
    PciHalSetStatus(PDEV, (1 << 13));
    Status = PciHalGetStatus(PDEV);
    if(Status & (1 << 13)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Clear Received Master Abort\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalPciIsAssertingSignaledSystemError(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetStatus(PDEV) & (1 << 14)) ? true : false;
}


DRIVER_EXPORT LOUSTATUS PciHalClearSignaledSystemError(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Status = PciHalGetStatus(PDEV);
    if(!(Status & (1 << 14))){
        PciHalDbgPrint("PCI.SYS:Signaled System Error Is Already Cleared\n");
        return STATUS_SUCCESS;
    }
    PciHalSetStatus(PDEV, (1 << 14));
    Status = PciHalGetStatus(PDEV);
    if(Status & (1 << 14)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Clear Signaled System Error\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT BOOLEAN PciHalPciIsAssertingDetectedParrityError(PPCI_DEVICE_OBJECT PDEV){
    return (PciHalGetStatus(PDEV) & (1 << 15)) ? true : false;
}


DRIVER_EXPORT LOUSTATUS PciHalClearDetectedParrityError(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Status = PciHalGetStatus(PDEV);
    if(!(Status & (1 << 15))){
        PciHalDbgPrint("PCI.SYS:Detected Parrity Error Is Already Cleared\n");
        return STATUS_SUCCESS;
    }
    PciHalSetStatus(PDEV, (1 << 15));
    Status = PciHalGetStatus(PDEV);
    if(Status & (1 << 15)){
        PciHalDbgPrint("PCI.SYS:WARNING:Unable To Clear Detected Parrity Error\n");
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalMapPciResource(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT8               Bar, 
    UINT64              OverideFlags
){
    if(PDEV->BarMapping[Bar]){
        return STATUS_INVALID_PARAMETER;
    }

    BOOLEAN IoOn = PciHalIsIoSpaceEnabled(PDEV);
    BOOLEAN MemOn = PciHalIsMemorySpaceEnabled(PDEV);
    UINT8 HeaderType = PciHalGetHeaderType(PDEV) & 0x3; 
    LOUSTATUS Status = STATUS_SUCCESS;
    if(IoOn)PciHalDisableIoSpace(PDEV);
    if(MemOn)PciHalDisableMemorySpace(PDEV);
    
    UINT32 BarSize = 0;
    UINT32 TmpBarValue = 0;
    UINT32 TmpUpperBarValue = 0;
    UINT64 BarPhyAddress = 0;
    UINT64 BarVAddress = 0;
    BOOLEAN WriteThroght = false;
    BOOLEAN Using32BitAllocator = false;

    switch(HeaderType){
        case 0:{
            if(Bar > 5){
                LouPrint("PCI.SYS:Error Bar Parameter Exceedes PCI Bar Limit\n");
                Status = STATUS_INVALID_PARAMETER;
                break;
            }
            
            TmpBarValue = PciHalGeneralDeviceGetBar(PDEV, Bar);
            if(TmpBarValue & 1){
                break; //TODO:IO_BAR
            }
            PciHalGeneralDeviceSetBar(PDEV, Bar, UINT32_MAX);
            BarSize = PciHalGeneralDeviceGetBar(PDEV, Bar);
            if(!((TmpBarValue >> 1) & 0x03)){
                BarSize &= 0xFFFFFFF0;
                BarSize = ~(BarSize) + 1;
                BarPhyAddress = TmpBarValue & 0xFFFFFFF0;
                Using32BitAllocator = true;
            }else if(!((TmpBarValue >> 1) & 0x03) == 1){
                LouPrint("PCI.SYS:Pci HAL Cannot Allocate 16 Bit Memory At This Time\n");
                Status = STATUS_INVALID_PARAMETER;
                break;
            }else if(((TmpBarValue >> 1) & 0x03) == 2){
                BarSize &= 0xFFFFFFF0;
                TmpUpperBarValue = PciHalGeneralDeviceGetBar(PDEV, Bar + 1);
                PciHalGeneralDeviceSetBar(PDEV, Bar + 1, UINT32_MAX);
                BarSize |= ((UINT64)PciHalGeneralDeviceGetBar(PDEV, Bar + 1) << 32);
                BarSize = ~(BarSize) + 1;
                BarPhyAddress = TmpBarValue & 0xFFFFFFF0;
                BarPhyAddress |= ((UINT64)TmpUpperBarValue << 32);
            }else{
                LouPrint("PCI.SYS:Unkown PCI Bar Type\n");
                Status = STATUS_INVALID_PARAMETER;
                break;
            }
            BarVAddress = (UINT64)LouVMallocEx(BarSize, BarSize);
            if(!BarPhyAddress && Using32BitAllocator){
                BarPhyAddress = (UINT64)LouAllocatePhysical32UpEx(BarSize, BarSize);
            }else if(!BarPhyAddress){
                BarPhyAddress = (UINT64)LouAllocatePhysical64UpEx(BarSize, BarSize);
            }
            else{
                EnforceSystemMemoryMap(BarPhyAddress, BarSize);
            }
            
            if(Using32BitAllocator){
                PciHalGeneralDeviceSetBar(PDEV, Bar, BarPhyAddress);
            }else{
                PciHalGeneralDeviceSetBar(PDEV, Bar, BarPhyAddress & UINT32_MAX);
                PciHalGeneralDeviceSetBar(PDEV, Bar + 1, (BarPhyAddress >> 32) & UINT32_MAX);
            }

            if(PCI_IOMAP_FLAGS_NO_WRITE_THROUGH){
                LouKeMapContinuousMemoryBlockKB(BarPhyAddress, BarVAddress, BarSize, KERNEL_DMA_MEMORY);
            }else if(PCI_IOMAP_FLAGS_USE_WRITE_COMBINE){
                LouKeMapContinuousMemoryBlockKB(BarPhyAddress, BarVAddress, BarSize, KERNEL_WRITE_COMBINE_MEMORY);
            }else {
                LouKeMapContinuousMemoryBlockKB(BarPhyAddress, BarVAddress, BarSize, KERNEL_DMA_MEMORY);
            }

            PDEV->BarMapping[Bar] = BarVAddress;
            PDEV->BarSize[Bar] = BarSize;
            PDEV->BarFlags[Bar] = OverideFlags; 
            PciHalDbgPrint("PCI.SYS:BAR Physical Address:%h\n", BarPhyAddress);
            PciHalDbgPrint("PCI.SYS:BAR Virtual  Address:%h\n", BarVAddress);
            PciHalDbgPrint("PCI.SYS:BAR Size            :%h\n", BarSize);
            break;
        }
        default:{
            LouPrint("PCI.SYS:ERROR Unable To Map PCI Resources\n");
            Status = STATUS_INVALID_PARAMETER;
            break;
        } 
    }

    if(IoOn)PciHalEnableIoSpace(PDEV);
    if(MemOn)PciHalEnableMemorySpace(PDEV);
    return Status;
}

DRIVER_EXPORT PVOID PciHalGetIoRegion(
    PPCI_DEVICE_OBJECT  PDEV,
    UINT8               Bar,
    SIZE                Offset
){
    return (PVOID)(UINTPTR)(PDEV->BarMapping[Bar] + Offset);
}


DRIVER_EXPORT void PciHalGetConfigurationSnapshot(PPCI_DEVICE_OBJECT PDEV, PPCI_COMMON_CONFIG Config){
    Config->Header.VendorID = PciHalGetVendorId(PDEV);
    Config->Header.DeviceID = PciHalGetDeviceId(PDEV);
    Config->Header.Command = PciHalGetCommand(PDEV);
    Config->Header.Status = PciHalGetStatus(PDEV);
    Config->Header.RevisionID = PciHalGetRevisionId(PDEV);
    Config->Header.ProgIf = PciHalGetProgIf(PDEV);
    Config->Header.SubClass = PciHalGetSubClass(PDEV);
    Config->Header.BaseClass = PciHalGetClassCode(PDEV);
    Config->Header.CacheLineSize = PciHalGetCacheLineSize(PDEV);
    Config->Header.LatencyTimer = PciHalGetLatencyTimer(PDEV);
    Config->Header.HeaderType = PciHalGetHeaderType(PDEV);
    Config->Header.BIST = PciHalGetBist(PDEV);
    switch(Config->Header.HeaderType & 0x03){
        case 0x00:{
            for(SIZE i = 0 ; i < PCI_TYPE0_ADDRESSES; i++){
                Config->Header.Type0.BaseAddresses[i] = PciHalGeneralDeviceGetBar(PDEV, i);
            }            
            Config->Header.Type0.CIS = PciHalGeneralDeviceGetCardBusCisPointer(PDEV);
            Config->Header.Type0.SubVendorID = PciHalGeneralDeviceGetSubsystemVendorId(PDEV);
            Config->Header.Type0.SubSystemID = PciHalGeneralDeviceGetSubsystemId(PDEV);
            Config->Header.Type0.ROMBaseAddress = PciHalGeneralDeviceGetExpansionRomBase(PDEV);
            Config->Header.Type0.CapabilitiesPtr = PciHalGeneralDeviceGetCapabilitiesPointer(PDEV);
            Config->Header.Type0.InterruptLine = PciHalGeneralDeviceGetInterruptLine(PDEV);
            Config->Header.Type0.InterruptPin = PciHalGeneralDeviceGetInterruptPin(PDEV);
            Config->Header.Type0.MinimumGrant = PciHalGeneralDeviceGetMinGrant(PDEV);
            Config->Header.Type0.MaximumLatency = PciHalGeneralDeviceGetMaxLatency(PDEV);
            break;
        }
        case 0x01:{
            for(SIZE i = 0 ; i < PCI_TYPE1_ADDRESSES; i++){
                Config->Header.Type0.BaseAddresses[i] = PciHalBridgeDeviceGetBar(PDEV, i);
            }      
            Config->Header.Type1.PrimaryBus = PciHalBridgeDeviceGetPrimaryBusNumber(PDEV);
            Config->Header.Type1.SecondaryBus = PciHalBridgeDeviceGetSecondaryBusNumber(PDEV);
            Config->Header.Type1.SubordinateBus = PciHalBridgeDeviceGetSubordinateBusNumber(PDEV);
            Config->Header.Type1.SecondaryLatency = PciHalBridgeDeviceGetSecondaryLatencyTimer(PDEV);
            Config->Header.Type1.IOBase = PciHalBridgeDeviceGetIoBase(PDEV);
            Config->Header.Type1.IOLimit = PciHalBridgeDeviceGetIoLimit(PDEV);
            Config->Header.Type1.SecondaryStatus = PciHalBridgeDeviceGetSecondaryStatus(PDEV);
            Config->Header.Type1.MemoryBase = PciHalBridgeDeviceGetMemoryBase(PDEV);
            Config->Header.Type1.MemoryLimit = PciHalBridgeDeviceGetMemoryLimit(PDEV);
            Config->Header.Type1.PrefetchBase = PciHalBridgeDeviceGetPrefetchableMemoryBase(PDEV);
            Config->Header.Type1.PrefetchLimit = PciHalBridgeDeviceGetPrefetchableMemoryLimit(PDEV);
            Config->Header.Type1.PrefetchBaseUpper32 = PciHalBridgeDeviceGetPrefetchableMemoryUpper32Base(PDEV);
            Config->Header.Type1.PrefetchLimitUpper32 = PciHalBridgeDeviceGetPrefetchableMemoryUpper32Limit(PDEV);
            Config->Header.Type1.IOBaseUpper16 = PciHalBridgeDeviceGetIoUpper16Base(PDEV);
            Config->Header.Type1.IOLimitUpper16 = PciHalBridgeDeviceGetIoUpper16Limit(PDEV);
            Config->Header.Type1.CapabilitiesPtr = PciHalBridgeDeviceGetCapabilitiesPointer(PDEV);
            Config->Header.Type1.ROMBaseAddress = PciHalBridgeDeviceGetExpansionRomBase(PDEV);
            Config->Header.Type1.InterruptLine = PciHalBridgeDeviceGetInterruptLine(PDEV);
            Config->Header.Type1.InterruptPin = PciHalBridgeDeviceGetInterruptPin(PDEV);
            Config->Header.Type1.BridgeControl = PciHalBridgeDeviceGetBridgeControl(PDEV);
            break;
        }
        case 0x02:{
            for(SIZE i = 0 ; i < 2; i++){
                Config->Header.Type2.Range[i].Base = PciHalCardBusDeviceGetMemoryBaseAddress(PDEV, i);
                Config->Header.Type2.Range[i].Limit = PciHalCardBusDeviceGetMemoryLimit(PDEV, i);
            }
            for(SIZE i = 2 ; i < 4; i++){
                Config->Header.Type2.Range[i].Base = PciHalCardBusDeviceGetIoBaseAddress(PDEV, i);
                Config->Header.Type2.Range[i].Limit = PciHalCardBusDeviceGetIoLimit(PDEV, i);
            }
            Config->Header.Type2.SocketRegistersBaseAddress = PciHalCardBusDeviceGetCardBusSocketExCaBaseAddress(PDEV);
            Config->Header.Type2.CapabilitiesPtr = PciHalCardBusDeviceGetOffsetCapabilities(PDEV);
            Config->Header.Type2.SecondaryStatus = PciHalCardBusDeviceGetSecondaryStatus(PDEV);
            Config->Header.Type2.PrimaryBus = PciHalCardBusDeviceGetPciBusNumber(PDEV);
            Config->Header.Type2.SecondaryBus = PciHalCardBusDeviceGetCardBusNumber(PDEV);
            Config->Header.Type2.SubordinateBus = PciHalCardBusDeviceGetSubordinateBusNumber(PDEV);
            Config->Header.Type2.SecondaryLatency = PciHalCardBusDeviceGetCardBusLatencyTimer(PDEV);
            Config->Header.Type2.InterruptLine = PciHalCardBusDeviceGetInterruptLine(PDEV);
            Config->Header.Type2.InterruptPin = PciHalCardBusDeviceGetInterruptPin(PDEV);
            Config->Header.Type2.BridgeControl = PciHalCardBusDeviceGetBridgeControl(PDEV);
            break;
        }
        default:
            LouPrint("PCI.SYS:ERROR:PciHalGetConfigurationSnapshot():Unkown Pci Device\n");
    }

}

DRIVER_EXPORT SIZE PciHalGetIoRegionSize(
    PPCI_DEVICE_OBJECT PDEV, 
    UINT8 Bar
){
    return PDEV->BarSize[Bar];
}

UINT16 PciHalGetCapabilitiesPointerEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr, UINT16 Capability, BOOLEAN PcieCap){
    if(!PciHalPciHasCapabiltiesList(PDEV)){
        return 0x00;
    } 
    UINT16 TmpPtr = 0x00;
    UINT32 TmpCap = 0x00;
    if((PCI_DEIVICE_IS_PCIE(PDEV)) && (PcieCap)){
        return 0x00;
    }
    else if(PcieCap){
        TmpPtr = 0x100;
        TmpCap = PciHalReadUint32(PDEV, 0x0100);
        while(1){
            if((TmpCap & UINT16_MAX) == Capability){
                return TmpPtr;
            }
            if(!((TmpCap >> 20) & 0x0FFF)){
                break;
            }
            TmpPtr = (TmpCap >> 20) & 0x0FFF;
            TmpCap = PciHalReadUint32(PDEV, TmpPtr);
        }
        return 0x00;
    }

    TmpPtr = CapPtr;
    TmpCap = PciHalReadUint16(PDEV, TmpPtr);
    while(1){
        if((TmpCap & UINT8_MAX) == Capability){
            return TmpPtr;
        }
        if(!((TmpCap >> 8) & UINT8_MAX)){
            break;
        }
        TmpPtr = (TmpCap >> 8) & UINT8_MAX;
        TmpCap = PciHalReadUint16(PDEV, TmpPtr);
    }
    return 0x00;
}

DRIVER_EXPORT UINT8 PciHalGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV, UINT16 Capability, BOOLEAN PcieCap){
    if(!PciHalPciHasCapabiltiesList(PDEV)){
        return 0x00;
    } 
    UINT8 HeaderType = PciHalGetHeaderType(PDEV) & 0x03;
    UINT16 CapPtr = 0x00;
    switch(HeaderType){
        case 0x00:
            CapPtr = (UINT16)PciHalGeneralDeviceGetCapabilitiesPointer(PDEV);
            CapPtr = PciHalGetCapabilitiesPointerEx(PDEV, CapPtr, Capability, PcieCap);
            break;
        case 0x01:
            CapPtr = (UINT16)PciHalBridgeDeviceGetCapabilitiesPointer(PDEV);
            CapPtr = PciHalGetCapabilitiesPointerEx(PDEV, CapPtr, Capability, PcieCap);
            break;
        case 0x02:
            CapPtr = (UINT16)PciHalCardBusDeviceGetOffsetCapabilities(PDEV);
            CapPtr = PciHalGetCapabilitiesPointerEx(PDEV, CapPtr, Capability, PcieCap);
            break;
        default:{
            LouPrint("PCI.SYS:PciHalGetCapabilitiesPointer():ERROR Invalid Header Type:%h\n", HeaderType);
            break;
        }
    }
    return CapPtr;
}