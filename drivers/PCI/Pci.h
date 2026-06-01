#ifndef _PCI_INTERNALS_H
#define _PCI_INTERNALS_H
#define _KERNEL_MODULE_
#include <LouDDK.h>

LOUAPI void PciHalPciDbgPrint(char* format, ...);

UINT32 LegacyPciReadUint32Ex(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT32 Offset);
void LegacyPciWriteUint32Ex(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT32 Offset, UINT32 Data);
UINT16 LegacyPciReadUint16Ex(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT32 Offset);
void LegacyPciWriteUint16Ex(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT32 Offset, UINT16 Value);
UINT8 LegacyPciReadUint8Ex(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT32 Offset);
void LegacyPciWriteUint8Ex(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT32 Offset, UINT8 Value);

UINT32 LegacyPciReadUint32(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
void LegacyPciWriteUint32(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT32 Value);
UINT16 LegacyPciReadUint16(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
void LegacyPciWriteUint16(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT16 Value);
UINT8 LegacyPciReadUint8(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
void LegacyPciWriteUint8(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT8 Value);

UINT16 LegacyPciGetVendorIdEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciGetDeviceIdEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciGetCommandEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
void LegacyPciSetCommandEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT16 Value);
UINT16 LegacyPciGetStatusEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
void LegacyPciSetStatusEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT16 Value);
UINT8 LegacyPciGetRevisionIdEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciGetProgIfEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciGetSubClassEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciGetClassCodeEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciGetCacheLineSizeEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
void LegacyPciSetCacheLineSizeEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 Value);
UINT8 LegacyPciGetLatencyTimerEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
void LegacyPciSetLatencyTimerEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 Value);
UINT8 LegacyPciGetHeaderTypeEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciGetBistEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
void LegacyPciSetBistEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 Value);

UINT16 LegacyPciGetVendorId(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciGetDeviceId(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciGetCommand(PPCI_DEVICE_OBJECT PDEV);
void LegacyPciSetCommand(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
UINT16 LegacyPciGetStatus(PPCI_DEVICE_OBJECT PDEV);
void LegacyPciSetStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
UINT8 LegacyPciGetRevisionId(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciGetProgIf(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciGetSubClass(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciGetClassCode(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciGetCacheLineSize(PPCI_DEVICE_OBJECT PDEV);
void LegacyPciSetCacheLineSize(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
UINT8 LegacyPciGetLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
void LegacyPciSetLatencyTimer(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
UINT8 LegacyPciGetHeaderType(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciGetBist(PPCI_DEVICE_OBJECT PDEV);
void LegacyPciSetBist(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);

UINT32 LegacyPciGeneralDeviceGetBarEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 Bar);
void LegacyPciGeneralDeviceSetBarEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 Bar, UINT32 Value);
UINT32 LegacyPciGeneralDeviceGetCardBusCisPointerEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciGeneralDeviceGetSubsystemVendorIdEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciGeneralDeviceGetSubsystemIdEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT32 LegacyPciGeneralDeviceGetExpansionRomBaseEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciGeneralDeviceGetCapabilitiesPointerEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciGeneralDeviceGetInterruptLineEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
void LegacyPciGeneralDeviceSetInterruptLineEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 Value);
UINT8 LegacyPciGeneralDeviceGetInterruptPinEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciGeneralDeviceGetMinGrantEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciGeneralDeviceGetMaxLatencyEx(UINT8 Bus, UINT8 Slot, UINT8 Function);

UINT32 LegacyPciGeneralDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
void LegacyPciGeneralDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value);
UINT32 LegacyPciGeneralDeviceGetCardBusCisPointer(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciGeneralDeviceGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciGeneralDeviceGetSubsystemId(PPCI_DEVICE_OBJECT PDEV);
UINT32 LegacyPciGeneralDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciGeneralDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciGeneralDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
void LegacyPciGeneralDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
UINT8 LegacyPciGeneralDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciGeneralDeviceGetMinGrant(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciGeneralDeviceGetMaxLatency(PPCI_DEVICE_OBJECT PDEV);

UINT32 LegacyPciBridgeDeviceGetBarEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 Bar);
void LegacyPciBridgeDeviceSetBarEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 Bar, UINT32 Value);
UINT8 LegacyPciBridgeDeviceGetPrimaryBusNumberEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciBridgeDeviceGetSecondaryBusNumberEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciBridgeDeviceGetSubordinateBusNumberEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciBridgeDeviceGetSecondaryLatencyTimerEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciBridgeDeviceGetIoBaseEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciBridgeDeviceGetIoLimitEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciBridgeDeviceGetSecondaryStatusEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
void LegacyPciBridgeDeviceSetSecondaryStatusEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT16 Value);
UINT16 LegacyPciBridgeDeviceGetMemoryBaseEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciBridgeDeviceGetMemoryLimitEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciBridgeDeviceGetPrefetchableMemoryBaseEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciBridgeDeviceGetPrefetchableMemoryLimitEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT32 LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32BaseEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT32 LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32LimitEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciBridgeDeviceGetIoUpper16BaseEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciBridgeDeviceGetIoUpper16LimitEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciBridgeDeviceGetCapabilitiesPointerEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT32 LegacyPciBridgeDeviceGetExpansionRomBaseEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciBridgeDeviceGetInterruptLineEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
void LegacyPciBridgeDeviceSetInterruptLineEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 Value);
UINT16 LegacyPciBridgeDeviceGetBridgeControlEx(UINT8 Bus, UINT8 Slot, UINT8 Function);

UINT32 LegacyPciBridgeDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
void LegacyPciBridgeDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value);
UINT8 LegacyPciBridgeDeviceGetPrimaryBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciBridgeDeviceGetSecondaryBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciBridgeDeviceGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciBridgeDeviceGetSecondaryLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciBridgeDeviceGetIoBase(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciBridgeDeviceGetIoLimit(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciBridgeDeviceGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV);
void LegacyPciBridgeDeviceSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
UINT16 LegacyPciBridgeDeviceGetMemoryBase(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciBridgeDeviceGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciBridgeDeviceGetPrefetchableMemoryBase(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciBridgeDeviceGetPrefetchableMemoryLimit(PPCI_DEVICE_OBJECT PDEV);
UINT32 LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32Base(PPCI_DEVICE_OBJECT PDEV);
UINT32 LegacyPciBridgeDeviceGetPrefetchableMemoryUpper32Limit(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciBridgeDeviceGetIoUpper16Base(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciBridgeDeviceGetIoUpper16Limit(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciBridgeDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV);
UINT32 LegacyPciBridgeDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciBridgeDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
void LegacyPciBridgeDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
UINT16 LegacyPciBridgeDeviceGetBridgeControl(PPCI_DEVICE_OBJECT PDEV);

UINT32 LegacyPciCardBusGetCardBusSocketExCaBaseAddressEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciCardBusGetOffsetCapabilitiesEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciCardBusGetSecondaryStatusEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
void LegacyPciCardBusSetSecondaryStatusEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT16 Value);
UINT8 LegacyPciCardBusGetPciBusNumberEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciCardBusGetCardBusNumberEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciCardBusGetSubordinateBusNumberEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT8 LegacyPciCardBusGetCardBusLatencyTimerEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT32 LegacyPciCardBusGetMemoryBaseAddressEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 x);
UINT32 LegacyPciCardBusGetMemoryLimitEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 x);
UINT32 LegacyPciCardBusGetIoBaseAddressEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 x);
UINT32 LegacyPciCardBusGetIoLimitEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 x);
UINT8 LegacyPciCardBusGetInterruptLineEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
void LegacyPciCardBusSetInterruptLineEx(UINT8 Bus, UINT8 Slot, UINT8 Function, UINT8 Value);
UINT8 LegacyPciCardBusGetInterruptPinEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciCardBusGetBridgeControlEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciCardBusGetSubsystemVendorIdEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT16 LegacyPciCardBusGetSubsystemDeviceIdEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
UINT32 LegacyPciCardBusGet16BitPcCardLegacyModeBaseAddressEx(UINT8 Bus, UINT8 Slot, UINT8 Function);

UINT32 LegacyPciCardBusGetCardBusSocketExCaBaseAddress(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciCardBusGetOffsetCapabilities(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciCardBusGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV);
void LegacyPciCardBusSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
UINT8 LegacyPciCardBusGetPciBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciCardBusGetCardBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciCardBusGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 LegacyPciCardBusGetCardBusLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
UINT32 LegacyPciCardBusGetMemoryBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
UINT32 LegacyPciCardBusGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
UINT32 LegacyPciCardBusGetIoBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
UINT32 LegacyPciCardBusGetIoLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
UINT8 LegacyPciCardBusGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
void LegacyPciCardBusSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
UINT8 LegacyPciCardBusGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciCardBusGetBridgeControl(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciCardBusGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV);
UINT16 LegacyPciCardBusGetSubsystemDeviceId(PPCI_DEVICE_OBJECT PDEV);
UINT32 LegacyPciCardBusGet16BitPcCardLegacyModeBaseAddress(PPCI_DEVICE_OBJECT PDEV);


#endif