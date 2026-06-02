//Tyler Grenier - PciHal.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

typedef struct _PCI_DISPATCH_TEMPLATE{
    //Basic Read and Write
    UINT32      (*PciHalReadUint32)                                         (PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
    void        (*PciHalWriteUint32)                                        (PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT32 Value);
    UINT16      (*PciHalReadUint16)                                         (PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
    void        (*PciHalWriteUint16)                                        (PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT16 Value);
    UINT8       (*PciHalReadUint8)                                          (PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
    void        (*PciHalWriteUint8)                                         (PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT8 Value);
    //Common Headers Read and Write
    UINT16      (*PciHalGetVendorId)                                        (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalGetDeviceId)                                        (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalGetCommand)                                         (PPCI_DEVICE_OBJECT PDEV);
    void        (*PciHalSetCommand)                                         (PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
    UINT16      (*PciHalGetStatus)                                          (PPCI_DEVICE_OBJECT PDEV);
    void        (*PciHalSetStatus)                                          (PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
    UINT8       (*PciHalGetRevisionId)                                      (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalGetProgIf)                                          (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalGetSubClass)                                        (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalGetClassCode)                                       (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalGetCacheLineSize)                                   (PPCI_DEVICE_OBJECT PDEV);
    void        (*PciHalSetCacheLineSize)                                   (PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
    UINT8       (*PciHalGetLatencyTimer)                                    (PPCI_DEVICE_OBJECT PDEV);
    void        (*PciHalSetLatencyTimer)                                    (PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
    UINT8       (*PciHalGetHeaderType)                                      (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalGetBist)                                            (PPCI_DEVICE_OBJECT PDEV);
    void        (*PciHalSetBist)                                            (PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
    //General Device Helpers Read and Write
    UINT32      (*PciHalGeneralDeviceGetBar)                                (PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
    void        (*PciHalGeneralDeviceSetBar)                                (PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value);
    UINT32      (*PciHalGeneralDeviceGetCardBusCisPointer)                  (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalGeneralDeviceGetSubsystemVendorId)                  (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalGeneralDeviceGetSubsystemId)                        (PPCI_DEVICE_OBJECT PDEV);
    UINT32      (*PciHalGeneralDeviceGetExpansionRomBase)                   (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalGeneralDeviceGetCapabilitiesPointer)                (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalGeneralDeviceGetInterruptLine)                      (PPCI_DEVICE_OBJECT PDEV);
    void        (*PciHalGeneralDeviceSetInterruptLine)                      (PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
    UINT8       (*PciHalGeneralDeviceGetInterruptPin)                       (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalGeneralDeviceGetMinGrant)                           (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalGeneralDeviceGetMaxLatency)                         (PPCI_DEVICE_OBJECT PDEV);
    //Bridge Device Helpers Read and Write
    UINT32      (*PciHalBridgeDeviceGetBar)                                 (PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
    void        (*PciHalBridgeDeviceSetBar)                                 (PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value);
    UINT8       (*PciHalBridgeDeviceGetPrimaryBusNumber)                    (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalBridgeDeviceGetSecondaryBusNumber)                  (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalBridgeDeviceGetSubordinateBusNumber)                (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalBridgeDeviceGetSecondaryLatencyTimer)               (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalBridgeDeviceGetIoBase)                              (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalBridgeDeviceGetIoLimit)                             (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalBridgeDeviceGetSecondaryStatus)                     (PPCI_DEVICE_OBJECT PDEV);
    void        (*PciHalBridgeDeviceSetSecondaryStatus)                     (PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
    UINT16      (*PciHalBridgeDeviceGetMemoryBase)                          (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalBridgeDeviceGetMemoryLimit)                         (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalBridgeDeviceGetPrefetchableMemoryBase)              (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalBridgeDeviceGetPrefetchableMemoryLimit)             (PPCI_DEVICE_OBJECT PDEV); 
    UINT32      (*PciHalBridgeDeviceGetPrefetchableMemoryUpper32Base)       (PPCI_DEVICE_OBJECT PDEV);
    UINT32      (*PciHalBridgeDeviceGetPrefetchableMemoryUpper32Limit)      (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalBridgeDeviceGetIoUpper16Base)                       (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalBridgeDeviceGetIoUpper16Limit)                      (PPCI_DEVICE_OBJECT PDEV);    
    UINT8       (*PciHalBridgeDeviceGetCapabilitiesPointer)                 (PPCI_DEVICE_OBJECT PDEV);
    UINT32      (*PciHalBridgeDeviceGetExpansionRomBase)                    (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalBridgeDeviceGetInterruptLine)                       (PPCI_DEVICE_OBJECT PDEV);
    void        (*PciHalBridgeDeviceSetInterruptLine)                       (PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
    UINT8       (*PciHalBridgeDeviceGetInterruptPin)                        (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalBridgeDeviceGetBridgeControl)                       (PPCI_DEVICE_OBJECT PDEV);
    //CarBus Device Helpers Read and Write
    UINT32      (*PciHalCardBusDeviceGetCardBusSocketExCaBaseAddress)       (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalCardBusDeviceGetOffsetCapabilities)                 (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalCardBusDeviceGetSecondaryStatus)                    (PPCI_DEVICE_OBJECT PDEV);
    void        (*PciHalCardBusDeviceSetSecondaryStatus)                    (PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
    UINT8       (*PciHalCardBusDeviceGetPciBusNumber)                       (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalCardBusDeviceGetCardBusNumber)                      (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalCardBusDeviceGetSubordinateBusNumber)               (PPCI_DEVICE_OBJECT PDEV);
    UINT8       (*PciHalCardBusDeviceGetCardBusLatencyTimer)                (PPCI_DEVICE_OBJECT PDEV);
    UINT32      (*PciHalCardBusDeviceGetMemoryBaseAddress)                  (PPCI_DEVICE_OBJECT PDEV, UINT8 x);
    UINT32      (*PciHalCardBusDeviceGetMemoryLimit)                        (PPCI_DEVICE_OBJECT PDEV, UINT8 x);
    UINT32      (*PciHalCardBusDeviceGetIoBaseAddress)                      (PPCI_DEVICE_OBJECT PDEV, UINT8 x);
    UINT32      (*PciHalCardBusDeviceGetIoLimit)                            (PPCI_DEVICE_OBJECT PDEV, UINT8 x);
    UINT8       (*PciHalCardBusDeviceGetInterruptLine)                      (PPCI_DEVICE_OBJECT PDEV);
    void        (*PciHalCardBusDeviceSetInterruptLine)                      (PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
    UINT8       (*PciHalCardBusDeviceGetInterruptPin)                       (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalCardBusDeviceGetBridgeControl)                      (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalCardBusDeviceGetSubsystemVendorId)                  (PPCI_DEVICE_OBJECT PDEV);
    UINT16      (*PciHalCardBusDeviceGetSubsystemDeviceId)                  (PPCI_DEVICE_OBJECT PDEV);
    UINT32      (*PciHalCardBusDeviceGet16BitPcCardLegacyModeBaseAddress)   (PPCI_DEVICE_OBJECT PDEV);
}PCI_DISPATCH_TEMPLATE, * PPCI_DISPATCH_TEMPLATE;

static const PCI_DISPATCH_TEMPLATE Dispatch[PciTotalDispatch]= {
    {
        //Basic Legacy
        .PciHalReadUint32 = LegacyPciReadUint32,
        .PciHalWriteUint32 = LegacyPciWriteUint32,
        .PciHalReadUint16 = LegacyPciReadUint16,
        .PciHalWriteUint16 = LegacyPciWriteUint16,
        .PciHalReadUint8 = LegacyPciReadUint8,
        .PciHalWriteUint8 = LegacyPciWriteUint8,
        //Common Header Legacy
        .PciHalGetVendorId = LegacyPciGetVendorId,
        .PciHalGetDeviceId = LegacyPciGetDeviceId,
        .PciHalGetCommand = LegacyPciGetCommand,
        .PciHalSetCommand = LegacyPciSetCommand,
        .PciHalGetStatus = LegacyPciGetStatus,
        .PciHalSetStatus = LegacyPciSetStatus,
        .PciHalGetRevisionId = LegacyPciGetRevisionId,
        .PciHalGetProgIf = LegacyPciGetProgIf,
        .PciHalGetSubClass = LegacyPciGetSubClass,
        .PciHalGetClassCode = LegacyPciGetClassCode,
        .PciHalGetCacheLineSize = LegacyPciGetCacheLineSize,
        .PciHalSetCacheLineSize = LegacyPciSetCacheLineSize,
        .PciHalGetLatencyTimer = LegacyPciGetLatencyTimer,
        .PciHalSetLatencyTimer = LegacyPciSetLatencyTimer,
        .PciHalGetHeaderType = LegacyPciGetHeaderType,
        .PciHalGetBist = LegacyPciGetBist,
        .PciHalSetBist = LegacyPciSetBist,
        //General Legacy
        .PciHalGeneralDeviceGetBar = LegacyPciGeneralDeviceGetBar,
        .PciHalGeneralDeviceSetBar = LegacyPciGeneralDeviceSetBar,
        .PciHalGeneralDeviceGetCardBusCisPointer = LegacyPciGeneralDeviceGetCardBusCisPointer,
        .PciHalGeneralDeviceGetSubsystemVendorId = LegacyPciGeneralDeviceGetSubsystemVendorId,
        .PciHalGeneralDeviceGetSubsystemId = LegacyPciGeneralDeviceGetSubsystemId,
        .PciHalGeneralDeviceGetExpansionRomBase = LegacyPciGeneralDeviceGetExpansionRomBase,
        .PciHalGeneralDeviceGetCapabilitiesPointer = LegacyPciGeneralDeviceGetCapabilitiesPointer,
        .PciHalGeneralDeviceGetInterruptLine = LegacyPciGeneralDeviceGetInterruptLine,
        .PciHalGeneralDeviceGetInterruptPin = LegacyPciGeneralDeviceGetInterruptPin,
        .PciHalGeneralDeviceGetMinGrant = LegacyPciGeneralDeviceGetMinGrant,
        .PciHalGeneralDeviceGetMaxLatency = LegacyPciGeneralDeviceGetMaxLatency,
        //Pci Bridge Legacy
        .PciHalBridgeDeviceGetBar = LegacyPciBridgeDeviceGetBar,
        .PciHalBridgeDeviceSetBar = LegacyPciBridgeDeviceSetBar,
        .PciHalBridgeDeviceGetPrimaryBusNumber = LegacyPciBridgeDeviceGetPrimaryBusNumber,
        .PciHalBridgeDeviceGetSecondaryBusNumber = LegacyPciBridgeDeviceGetSecondaryBusNumber,
        .PciHalBridgeDeviceGetSubordinateBusNumber = LegacyPciBridgeDeviceGetSubordinateBusNumber,
        .PciHalBridgeDeviceGetSecondaryLatencyTimer = LegacyPciBridgeDeviceGetSecondaryLatencyTimer,
        .PciHalBridgeDeviceGetIoBase = LegacyPciBridgeDeviceGetIoBase,
        .PciHalBridgeDeviceGetIoLimit = LegacyPciBridgeDeviceGetIoLimit,
        .PciHalBridgeDeviceGetSecondaryStatus = LegacyPciBridgeDeviceGetSecondaryStatus,
        .PciHalBridgeDeviceSetSecondaryStatus = LegacyPciBridgeDeviceSetSecondaryStatus,
        .PciHalBridgeDeviceGetMemoryBase = LegacyPciBridgeDeviceGetMemoryBase,
        .PciHalBridgeDeviceGetMemoryLimit = LegacyPciBridgeDeviceGetMemoryLimit,
        .PciHalBridgeDeviceGetPrefetchableMemoryBase = LegacyPciBridgeDeviceGetPrefetchableMemoryBase,
        .PciHalBridgeDeviceGetPrefetchableMemoryLimit = LegacyPciBridgeDeviceGetPrefetchableMemoryLimit,
        .PciHalBridgeDeviceGetPrefetchableMemoryUpper32Base = LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32Base,
        .PciHalBridgeDeviceGetPrefetchableMemoryUpper32Limit = LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32Limit,
        .PciHalBridgeDeviceGetIoUpper16Base = LegacyPciBridgeDeviceGetIoUpper16Base,
        .PciHalBridgeDeviceGetIoUpper16Limit = LegacyPciBridgeDeviceGetIoUpper16Limit,   
        .PciHalBridgeDeviceGetCapabilitiesPointer = LegacyPciBridgeDeviceGetCapabilitiesPointer,
        .PciHalBridgeDeviceGetExpansionRomBase = LegacyPciBridgeDeviceGetExpansionRomBase,
        .PciHalBridgeDeviceGetInterruptLine = LegacyPciBridgeDeviceGetInterruptLine,
        .PciHalBridgeDeviceSetInterruptLine = LegacyPciBridgeDeviceSetInterruptLine,
        .PciHalBridgeDeviceGetInterruptPin = LegacyPciBridgeDeviceGetInterruptPin,
        .PciHalBridgeDeviceGetBridgeControl = LegacyPciBridgeDeviceGetBridgeControl,
        //Card Bus Legacy
        .PciHalCardBusDeviceGetCardBusSocketExCaBaseAddress = LegacyPciCardBusGetCardBusSocketExCaBaseAddress,
        .PciHalCardBusDeviceGetOffsetCapabilities = LegacyPciCardBusGetOffsetCapabilities,
        .PciHalCardBusDeviceGetSecondaryStatus = LegacyPciCardBusGetSecondaryStatus,
        .PciHalCardBusDeviceSetSecondaryStatus = LegacyPciCardBusSetSecondaryStatus,
        .PciHalCardBusDeviceGetPciBusNumber = LegacyPciCardBusGetPciBusNumber,
        .PciHalCardBusDeviceGetCardBusNumber = LegacyPciCardBusGetCardBusNumber,
        .PciHalCardBusDeviceGetSubordinateBusNumber = LegacyPciCardBusGetSubordinateBusNumber,
        .PciHalCardBusDeviceGetCardBusLatencyTimer = LegacyPciCardBusGetCardBusLatencyTimer,
        .PciHalCardBusDeviceGetMemoryBaseAddress = LegacyPciCardBusGetMemoryBaseAddress,
        .PciHalCardBusDeviceGetMemoryLimit = LegacyPciCardBusGetMemoryLimit,
        .PciHalCardBusDeviceGetIoBaseAddress = LegacyPciCardBusGetIoBaseAddress,
        .PciHalCardBusDeviceGetIoLimit = LegacyPciCardBusGetIoLimit,
        .PciHalCardBusDeviceGetInterruptLine = LegacyPciCardBusGetInterruptLine,
        .PciHalCardBusDeviceSetInterruptLine = LegacyPciCardBusSetInterruptLine,
        .PciHalCardBusDeviceGetInterruptPin = LegacyPciCardBusGetInterruptPin,
        .PciHalCardBusDeviceGetBridgeControl = LegacyPciCardBusGetBridgeControl,
        .PciHalCardBusDeviceGetSubsystemVendorId = LegacyPciCardBusGetSubsystemVendorId,
        .PciHalCardBusDeviceGetSubsystemDeviceId = LegacyPciCardBusGetSubsystemDeviceId,
        .PciHalCardBusDeviceGet16BitPcCardLegacyModeBaseAddress = LegacyPciCardBusGet16BitPcCardLegacyModeBaseAddress,
    }, 
    {
        //Basic Native
        .PciHalReadUint32 = NativePciReadUint32,
        .PciHalWriteUint32 = NativePciWriteUint32,
        .PciHalReadUint16 = NativePciReadUint16,
        .PciHalWriteUint16 = NativePciWriteUint16,
        .PciHalReadUint8 = NativePciReadUint8,
        .PciHalWriteUint8 = NativePciWriteUint8,
        //Common Header Native
        .PciHalGetVendorId = NativePciGetVendorId,
        .PciHalGetDeviceId = NativePciGetDeviceId,
        .PciHalGetCommand = NativePciGetCommand,
        .PciHalSetCommand = NativePciSetCommand,
        .PciHalGetStatus = NativePciGetStatus,
        .PciHalSetStatus = NativePciSetStatus,
        .PciHalGetRevisionId = NativePciGetRevisionId,
        .PciHalGetProgIf = NativePciGetProgIf,
        .PciHalGetSubClass = NativePciGetSubClass,
        .PciHalGetClassCode = NativePciGetClassCode,
        .PciHalGetCacheLineSize = NativePciGetCacheLineSize,
        .PciHalSetCacheLineSize = NativePciSetCacheLineSize,
        .PciHalGetLatencyTimer = NativePciGetLatencyTimer,
        .PciHalSetLatencyTimer = NativePciSetLatencyTimer,
        .PciHalGetHeaderType = NativePciGetHeaderType,
        .PciHalGetBist = NativePciGetBist,
        .PciHalSetBist = NativePciSetBist,
        //General Native
        .PciHalGeneralDeviceGetBar = NativePciGeneralDeviceGetBar,
        .PciHalGeneralDeviceSetBar = NativePciGeneralDeviceSetBar,
        .PciHalGeneralDeviceGetCardBusCisPointer = NativePciGeneralDeviceGetCardBusCisPointer,
        .PciHalGeneralDeviceGetSubsystemVendorId = NativePciGeneralDeviceGetSubsystemVendorId,
        .PciHalGeneralDeviceGetSubsystemId = NativePciGeneralDeviceGetSubsystemId,
        .PciHalGeneralDeviceGetExpansionRomBase = NativePciGeneralDeviceGetExpansionRomBase,
        .PciHalGeneralDeviceGetCapabilitiesPointer = NativePciGeneralDeviceGetCapabilitiesPointer,
        .PciHalGeneralDeviceGetInterruptLine = NativePciGeneralDeviceGetInterruptLine,
        .PciHalGeneralDeviceGetInterruptPin = NativePciGeneralDeviceGetInterruptPin,
        .PciHalGeneralDeviceGetMinGrant = NativePciGeneralDeviceGetMinGrant,
        .PciHalGeneralDeviceGetMaxLatency = NativePciGeneralDeviceGetMaxLatency,
        //Pci Bridge Native
        .PciHalBridgeDeviceGetBar = NativePciBridgeDeviceGetBar,
        .PciHalBridgeDeviceSetBar = NativePciBridgeDeviceSetBar,
        .PciHalBridgeDeviceGetPrimaryBusNumber = NativePciBridgeDeviceGetPrimaryBusNumber,
        .PciHalBridgeDeviceGetSecondaryBusNumber = NativePciBridgeDeviceGetSecondaryBusNumber,
        .PciHalBridgeDeviceGetSubordinateBusNumber = NativePciBridgeDeviceGetSubordinateBusNumber,
        .PciHalBridgeDeviceGetSecondaryLatencyTimer = NativePciBridgeDeviceGetSecondaryLatencyTimer,
        .PciHalBridgeDeviceGetIoBase = NativePciBridgeDeviceGetIoBase,
        .PciHalBridgeDeviceGetIoLimit = NativePciBridgeDeviceGetIoLimit,
        .PciHalBridgeDeviceGetSecondaryStatus = NativePciBridgeDeviceGetSecondaryStatus,
        .PciHalBridgeDeviceSetSecondaryStatus = NativePciBridgeDeviceSetSecondaryStatus,
        .PciHalBridgeDeviceGetMemoryBase = NativePciBridgeDeviceGetMemoryBase,
        .PciHalBridgeDeviceGetMemoryLimit = NativePciBridgeDeviceGetMemoryLimit,
        .PciHalBridgeDeviceGetPrefetchableMemoryBase = NativePciBridgeDeviceGetPrefetchableMemoryBase,
        .PciHalBridgeDeviceGetPrefetchableMemoryLimit = NativePciBridgeDeviceGetPrefetchableMemoryLimit,
        .PciHalBridgeDeviceGetPrefetchableMemoryUpper32Base = NativePciBridgeDeviceGetPrefetchableMemoryUpper32Base,
        .PciHalBridgeDeviceGetPrefetchableMemoryUpper32Limit = NativePciBridgeDeviceGetPrefetchableMemoryUpper32Limit,
        .PciHalBridgeDeviceGetIoUpper16Base = NativePciBridgeDeviceGetIoUpper16Base,
        .PciHalBridgeDeviceGetIoUpper16Limit = NativePciBridgeDeviceGetIoUpper16Limit,   
        .PciHalBridgeDeviceGetCapabilitiesPointer = NativePciBridgeDeviceGetCapabilitiesPointer,
        .PciHalBridgeDeviceGetExpansionRomBase = NativePciBridgeDeviceGetExpansionRomBase,
        .PciHalBridgeDeviceGetInterruptLine = NativePciBridgeDeviceGetInterruptLine,
        .PciHalBridgeDeviceSetInterruptLine = NativePciBridgeDeviceSetInterruptLine,
        .PciHalBridgeDeviceGetInterruptPin = NativePciBridgeDeviceGetInterruptPin,
        .PciHalBridgeDeviceGetBridgeControl = NativePciBridgeDeviceGetBridgeControl,
        //Card Bus Native
        .PciHalCardBusDeviceGetCardBusSocketExCaBaseAddress = NativePciCardBusGetCardBusSocketExCaBaseAddress,
        .PciHalCardBusDeviceGetOffsetCapabilities = NativePciCardBusGetOffsetCapabilities,
        .PciHalCardBusDeviceGetSecondaryStatus = NativePciCardBusGetSecondaryStatus,
        .PciHalCardBusDeviceSetSecondaryStatus = NativePciCardBusSetSecondaryStatus,
        .PciHalCardBusDeviceGetPciBusNumber = NativePciCardBusGetPciBusNumber,
        .PciHalCardBusDeviceGetCardBusNumber = NativePciCardBusGetCardBusNumber,
        .PciHalCardBusDeviceGetSubordinateBusNumber = NativePciCardBusGetSubordinateBusNumber,
        .PciHalCardBusDeviceGetCardBusLatencyTimer = NativePciCardBusGetCardBusLatencyTimer,
        .PciHalCardBusDeviceGetMemoryBaseAddress = NativePciCardBusGetMemoryBaseAddress,
        .PciHalCardBusDeviceGetMemoryLimit = NativePciCardBusGetMemoryLimit,
        .PciHalCardBusDeviceGetIoBaseAddress = NativePciCardBusGetIoBaseAddress,
        .PciHalCardBusDeviceGetIoLimit = NativePciCardBusGetIoLimit,
        .PciHalCardBusDeviceGetInterruptLine = NativePciCardBusGetInterruptLine,
        .PciHalCardBusDeviceSetInterruptLine = NativePciCardBusSetInterruptLine,
        .PciHalCardBusDeviceGetInterruptPin = NativePciCardBusGetInterruptPin,
        .PciHalCardBusDeviceGetBridgeControl = NativePciCardBusGetBridgeControl,
        .PciHalCardBusDeviceGetSubsystemVendorId = NativePciCardBusGetSubsystemVendorId,
        .PciHalCardBusDeviceGetSubsystemDeviceId = NativePciCardBusGetSubsystemDeviceId,
        .PciHalCardBusDeviceGet16BitPcCardLegacyModeBaseAddress = NativePciCardBusGet16BitPcCardLegacyModeBaseAddress,    
    }, 
};

//Basic Read and Write

DRIVER_EXPORT UINT32 PciHalReadUint32(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT32              Offset
){
    return Dispatch[PDEV->Dispatch].PciHalReadUint32(PDEV, Offset);
}

DRIVER_EXPORT void PciHalWriteUint32(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT32              Offset, 
    UINT32              Value
){
    Dispatch[PDEV->Dispatch].PciHalWriteUint32(PDEV, Offset, Value);
}
    
DRIVER_EXPORT UINT16 PciHalReadUint16(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT32              Offset
){
    return Dispatch[PDEV->Dispatch].PciHalReadUint16(PDEV, Offset);
}

DRIVER_EXPORT void PciHalWriteUint16(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT32              Offset, 
    UINT16              Value
){
    Dispatch[PDEV->Dispatch].PciHalWriteUint16(PDEV, Offset, Value);
}

DRIVER_EXPORT UINT8 PciHalReadUint8(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT32              Offset
){
    return Dispatch[PDEV->Dispatch].PciHalReadUint8(PDEV, Offset);
}

DRIVER_EXPORT void PciHalWriteUint8(
    PPCI_DEVICE_OBJECT  PDEV, 
    UINT32              Offset, 
    UINT8               Value
){
    Dispatch[PDEV->Dispatch].PciHalWriteUint8(PDEV, Offset, Value);
}

DRIVER_EXPORT UINT16 PciHalGetVendorId(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetVendorId(PDEV);
}

DRIVER_EXPORT UINT16 PciHalGetDeviceId(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetDeviceId(PDEV);
}

DRIVER_EXPORT UINT16 PciHalGetCommand(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetCommand(PDEV);
}

DRIVER_EXPORT void PciHalSetCommand(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    Dispatch[PDEV->Dispatch].PciHalSetCommand(PDEV, Value);
}

DRIVER_EXPORT UINT16 PciHalGetStatus(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetStatus(PDEV);
}
    
DRIVER_EXPORT void PciHalSetStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    Dispatch[PDEV->Dispatch].PciHalSetStatus(PDEV, Value);
}

DRIVER_EXPORT UINT8 PciHalGetRevisionId(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetRevisionId(PDEV);
}

DRIVER_EXPORT UINT8 PciHalGetProgIf(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetProgIf(PDEV);
}
    
DRIVER_EXPORT UINT8 PciHalGetSubClass(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetSubClass(PDEV);
}

DRIVER_EXPORT UINT8 PciHalGetClassCode(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetClassCode(PDEV);
}

DRIVER_EXPORT UINT8 PciHalGetCacheLineSize(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetCacheLineSize(PDEV);
}

DRIVER_EXPORT void PciHalSetCacheLineSize(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    Dispatch[PDEV->Dispatch].PciHalSetCacheLineSize(PDEV, Value);
}

DRIVER_EXPORT UINT8 PciHalGetLatencyTimer(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetLatencyTimer(PDEV);
}

DRIVER_EXPORT void PciHalSetLatencyTimer(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    Dispatch[PDEV->Dispatch].PciHalSetLatencyTimer(PDEV, Value);
}

DRIVER_EXPORT UINT8 PciHalGetHeaderType(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetHeaderType(PDEV);
}

DRIVER_EXPORT UINT8 PciHalGetBist(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGetBist(PDEV);
}

DRIVER_EXPORT void PciHalSetBist(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    return Dispatch[PDEV->Dispatch].PciHalSetBist(PDEV, Value);
}


DRIVER_EXPORT UINT32 PciHalGeneralDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar){
    return Dispatch[PDEV->Dispatch].PciHalGeneralDeviceGetBar(PDEV, Bar);
}

DRIVER_EXPORT void PciHalGeneralDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value){
    Dispatch[PDEV->Dispatch].PciHalGeneralDeviceSetBar(PDEV, Bar, Value);
}

DRIVER_EXPORT UINT32 PciHalGeneralDeviceGetCardBusCisPointer(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGeneralDeviceGetCardBusCisPointer(PDEV);
}

DRIVER_EXPORT UINT16 PciHalGeneralDeviceGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGeneralDeviceGetSubsystemVendorId(PDEV);
}

DRIVER_EXPORT UINT16 PciHalGeneralDeviceGetSubsystemId(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGeneralDeviceGetSubsystemId(PDEV);
}

DRIVER_EXPORT UINT32 PciHalGeneralDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGeneralDeviceGetExpansionRomBase(PDEV);
}

DRIVER_EXPORT UINT8 PciHalGeneralDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGeneralDeviceGetCapabilitiesPointer(PDEV);
}

DRIVER_EXPORT UINT8 PciHalGeneralDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGeneralDeviceGetInterruptLine(PDEV);
}

DRIVER_EXPORT void PciHalGeneralDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    Dispatch[PDEV->Dispatch].PciHalGeneralDeviceSetInterruptLine(PDEV, Value);
}

DRIVER_EXPORT UINT8 PciHalGeneralDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGeneralDeviceGetInterruptPin(PDEV);
}

DRIVER_EXPORT UINT8 PciHalGeneralDeviceGetMinGrant(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGeneralDeviceGetMinGrant(PDEV);
}

DRIVER_EXPORT UINT8 PciHalGeneralDeviceGetMaxLatency(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalGeneralDeviceGetMaxLatency(PDEV);
}


DRIVER_EXPORT UINT32 PciHalBridgeDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetBar(PDEV, Bar);
}

DRIVER_EXPORT void PciHalBridgeDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value){
    Dispatch[PDEV->Dispatch].PciHalBridgeDeviceSetBar(PDEV, Bar, Value);
}

DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetPrimaryBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetPrimaryBusNumber(PDEV);
}

DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetSecondaryBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetSecondaryBusNumber(PDEV);
}

DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetSubordinateBusNumber(PDEV);
}

DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetSecondaryLatencyTimer(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetSecondaryLatencyTimer(PDEV);
}

DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetIoBase(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetIoBase(PDEV);
}

DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetIoLimit(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetIoLimit(PDEV);
}

DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetSecondaryStatus(PDEV);
}

DRIVER_EXPORT void PciHalBridgeDeviceSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    Dispatch[PDEV->Dispatch].PciHalBridgeDeviceSetSecondaryStatus(PDEV, Value);
}

DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetMemoryBase(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetMemoryBase(PDEV);
}

DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetMemoryLimit(PDEV);
}

DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetPrefetchableMemoryBase(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetPrefetchableMemoryBase(PDEV);
}

DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetPrefetchableMemoryLimit(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetPrefetchableMemoryLimit(PDEV);
} 

DRIVER_EXPORT UINT32 PciHalBridgeDeviceGetPrefetchableMemoryUpper32Base(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetPrefetchableMemoryUpper32Base(PDEV);
}

DRIVER_EXPORT UINT32 PciHalBridgeDeviceGetPrefetchableMemoryUpper32Limit(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetPrefetchableMemoryUpper32Limit(PDEV);
}

DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetIoUpper16Base(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetIoUpper16Base(PDEV);
}

DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetIoUpper16Limit(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetIoUpper16Limit(PDEV);
}    

DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetCapabilitiesPointer(PDEV);
}

DRIVER_EXPORT UINT32 PciHalBridgeDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetExpansionRomBase(PDEV);
}

DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetInterruptLine(PDEV);
}

DRIVER_EXPORT void PciHalBridgeDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    Dispatch[PDEV->Dispatch].PciHalBridgeDeviceSetInterruptLine(PDEV, Value);
}

DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetInterruptPin(PDEV);
}

DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetBridgeControl(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalBridgeDeviceGetBridgeControl(PDEV);
}



DRIVER_EXPORT UINT32 PciHalCardBusDeviceGetCardBusSocketExCaBaseAddress(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetCardBusSocketExCaBaseAddress(PDEV);
}

DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetOffsetCapabilities(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetOffsetCapabilities(PDEV);
}

DRIVER_EXPORT UINT16 PciHalCardBusDeviceGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetSecondaryStatus(PDEV);
}

DRIVER_EXPORT void PciHalCardBusDeviceSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    Dispatch[PDEV->Dispatch].PciHalCardBusDeviceSetSecondaryStatus(PDEV, Value);
}

DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetPciBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetPciBusNumber(PDEV);
}

DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetCardBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetCardBusNumber(PDEV);
}

DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetSubordinateBusNumber(PDEV);
}

DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetCardBusLatencyTimer(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetCardBusLatencyTimer(PDEV);
}

DRIVER_EXPORT UINT32 PciHalCardBusDeviceGetMemoryBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetMemoryBaseAddress(PDEV, x);
}

DRIVER_EXPORT UINT32 PciHalCardBusDeviceGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetMemoryLimit(PDEV, x);
}

DRIVER_EXPORT UINT32 PciHalCardBusDeviceGetIoBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetIoBaseAddress(PDEV, x);
}

DRIVER_EXPORT UINT32 PciHalCardBusDeviceGetIoLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetIoLimit(PDEV, x);
}

DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetInterruptLine(PDEV);
}

DRIVER_EXPORT void PciHalCardBusDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value){
    Dispatch[PDEV->Dispatch].PciHalCardBusDeviceSetInterruptLine(PDEV, Value);
}

DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetInterruptPin(PDEV);
}

DRIVER_EXPORT UINT16 PciHalCardBusDeviceGetBridgeControl(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetBridgeControl(PDEV);
}

DRIVER_EXPORT UINT16 PciHalCardBusDeviceGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetSubsystemVendorId(PDEV);
}

DRIVER_EXPORT UINT16 PciHalCardBusDeviceGetSubsystemDeviceId(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGetSubsystemDeviceId(PDEV);
}

DRIVER_EXPORT UINT32 PciHalCardBusDeviceGet16BitPcCardLegacyModeBaseAddress(PPCI_DEVICE_OBJECT PDEV){
    return Dispatch[PDEV->Dispatch].PciHalCardBusDeviceGet16BitPcCardLegacyModeBaseAddress(PDEV);
}
