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
    Config->Header.VendorID = PciHalGetVendorId(PDEV);
    Config->Header.DeviceID = PciHalGetDeviceId(PDEV);
    Config->Header.Command = PciHalGetCommand(PDEV);
    Config->Header.Status = PciHalGetStatus(PDEV);
    Config->Header.RevisionID = PciHalGetRevisionId(PDEV);
    Config->Header.ProgIf = PciHalGetProgIf(PDEV);
    Config->Header.SubClass = PciHalGetProgIf(PDEV);
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
    LouPrint("PCI.SYS:PciHalGetIoRegionSize()\n");
    while(1);
    return 0;
}