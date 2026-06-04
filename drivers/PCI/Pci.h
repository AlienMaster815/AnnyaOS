//Tyler Grenier - Pci.h :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#ifndef _PCI_INTERNALS_H
#define _PCI_INTERNALS_H
#define _KERNEL_MODULE_
#include <LouDDK.h>

#define ACPI_SIG_MCFG           "MCFG"      /* PCI Memory Mapped Configuration table */

KERNEL_EXPORT void* LouKeAcquireAcpiTable(string TableName);
KERNEL_EXPORT LOUSTATUS LouKeCreateFastObjectClass(LOUSTR ClassName, SIZE ObjectCount, SIZE ObjectSize, SIZE ObjectAlignment, SIZE Flags, SIZE PageFlags);

typedef struct _MCFG_TABLE_ENTRY{
    UINT64      ConfigurationBaseAddress;
    UINT16      Group;
    UINT8       StartBus;
    UINT8       EndBus;
    UINT32      Reserved;
}MCFG_TABLE_ENTRY, * PMCFG_TABLE_ENTRY;

typedef struct PACKED _MCFG_TABLE{
    UINT32              TableHeader;
    UINT32              TableLength;
    UINT8               Revision;
    UINT8               Checksum;
    UINT8               OemID[6];
    UINT8               OemTableID[8];
    UINT32              OemRevision;
    UINT32              CreatorID;
    UINT32              CreatorRevision;
    UINT64              Reserved;
    MCFG_TABLE_ENTRY    TableEntries[];
}MCFG_TABLE, * PMCFG_TABLE;

typedef struct _PCI_DEVICE_GROUP{
    ListHeader              Peers;
    UNICODE_STRING          DeviceName;
    PPCI_DEVICE_OBJECT      PciDeviceobject;
    DEVICE_OBJECT           LdmDeviceObject;
}PCI_DEVICE_GROUP, * PPCI_DEVICE_GROUP;

typedef struct _LOADED_PCI_MODULE{
    ListHeader                  Peers;
    UNICODE_STRING              RegistryEntry;
    HANDLE                      RegistryHandle;
    DRIVER_MODULE_ENTRY         DriverEntry;
    FILE*                       DriverFile;
    PDRIVER_OBJECT              DriverObject;
    mutex_t                     UninitializedDeviceGroupLock;
    ListHeader                  UninitializedDeviceGroup;
    mutex_t                     InitializedDeviceGroupLock;
    ListHeader                  InitializedDeviceGroup;
    BOOLEAN                     BootModule;
    UINT16                      LoadOrder;
    PLOUSINE_PCI_DEVICE_TABLE   DeviceTable;
}LOADED_PCI_MODULE, * PLOADED_PCI_MODULE;


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
UINT8 LegacyPciBridgeDeviceGetInterruptPinEx(UINT8 Bus, UINT8 Slot, UINT8 Function);
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
UINT8 LegacyPciBridgeDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
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

UINT32 NativePciReadUint32Ex(UINT32* DeviceBase, UINT32 Offset);
void NativePciWriteUint32Ex(UINT32* DeviceBase, UINT32 Offset, UINT32 Value);
UINT16 NativePciReadUint16Ex(UINT32* DeviceBase, UINT32 Offset);
void NativePciWriteUint16Ex(UINT32* DeviceBase, UINT32 Offset, UINT16 Value);
UINT8 NativePciReadUint8Ex(UINT32* DeviceBase, UINT32 Offset);
void NativePciWriteUint8Ex(UINT32* DeviceBase, UINT32 Offset, UINT8 Value);

UINT32 NativePciReadUint32(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
void NativePciWriteUint32(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT32 Value);
UINT16 NativePciReadUint16(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
void NativePciWriteUint16(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT16 Value);
UINT8 NativePciReadUint8(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
void NativePciWriteUint8(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT8 Value);

UINT16 NativePciGetVendorIdEx(UINT32* DeviceBase);
UINT16 NativePciGetDeviceIdEx(UINT32* DeviceBase);
UINT16 NativePciGetCommandEx(UINT32* DeviceBase);
void NativePciSetCommandEx(UINT32* DeviceBase, UINT16 Value);
UINT16 NativePciGetStatusEx(UINT32* DeviceBase);
void NativePciSetStatusEx(UINT32* DeviceBase, UINT16 Value);
UINT8 NativePciGetRevisionIdEx(UINT32* DeviceBase);
UINT8 NativePciGetProgIfEx(UINT32* DeviceBase);
UINT8 NativePciGetSubClassEx(UINT32* DeviceBase);
UINT8 NativePciGetClassCodeEx(UINT32* DeviceBase);
UINT8 NativePciGetCacheLineSizeEx(UINT32* DeviceBase);
void NativePciSetCacheLineSizeEx(UINT32* DeviceBase, UINT8 Value);
UINT8 NativePciGetLatencyTimerEx(UINT32* DeviceBase);
void NativePciSetLatencyTimerEx(UINT32* DeviceBase, UINT8 Value);
UINT8 NativePciGetHeaderTypeEx(UINT32* DeviceBase);
UINT8 NativePciGetBistEx(UINT32* DeviceBase);
void NativePciSetBistEx(UINT32* DeviceBase, UINT8 Value);

UINT16 NativePciGetVendorId(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciGetDeviceId(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciGetCommand(PPCI_DEVICE_OBJECT PDEV);
void NativePciSetCommand(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
UINT16 NativePciGetStatus(PPCI_DEVICE_OBJECT PDEV);
void NativePciSetStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
UINT8 NativePciGetRevisionId(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciGetProgIf(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciGetSubClass(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciGetClassCode(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciGetCacheLineSize(PPCI_DEVICE_OBJECT PDEV);
void NativePciSetCacheLineSize(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
UINT8 NativePciGetLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
void NativePciSetLatencyTimer(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
UINT8 NativePciGetHeaderType(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciGetBist(PPCI_DEVICE_OBJECT PDEV);
void NativePciSetBist(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);

UINT32 NativePciGeneralDeviceGetBarEx(UINT32* DeviceBase, UINT8 Bar);
void NativePciGeneralDeviceSetBarEx(UINT32* DeviceBase, UINT8 Bar, UINT32 Value);
UINT32 NativePciGeneralDeviceGetCardBusCisPointerEx(UINT32* DeviceBase);
UINT16 NativePciGeneralDeviceGetSubsystemVendorIdEx(UINT32* DeviceBase);
UINT16 NativePciGeneralDeviceGetSubsystemIdEx(UINT32* DeviceBase);
UINT32 NativePciGeneralDeviceGetExpansionRomBaseEx(UINT32* DeviceBase);
UINT8 NativePciGeneralDeviceGetCapabilitiesPointerEx(UINT32* DeviceBase);
UINT8 NativePciGeneralDeviceGetInterruptLineEx(UINT32* DeviceBase);
void NativePciGeneralDeviceSetInterruptLineEx(UINT32* DeviceBase, UINT8 Value);
UINT8 NativePciGeneralDeviceGetInterruptPinEx(UINT32* DeviceBase);
UINT8 NativePciGeneralDeviceGetMinGrantEx(UINT32* DeviceBase);
UINT8 NativePciGeneralDeviceGetMaxLatencyEx(UINT32* DeviceBase);

UINT32 NativePciGeneralDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
void NativePciGeneralDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value);
UINT32 NativePciGeneralDeviceGetCardBusCisPointer(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciGeneralDeviceGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciGeneralDeviceGetSubsystemId(PPCI_DEVICE_OBJECT PDEV);
UINT32 NativePciGeneralDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciGeneralDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciGeneralDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
void NativePciGeneralDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
UINT8 NativePciGeneralDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciGeneralDeviceGetMinGrant(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciGeneralDeviceGetMaxLatency(PPCI_DEVICE_OBJECT PDEV);

UINT32 NativePciBridgeDeviceGetBarEx(UINT32* DeviceBase, UINT8 Bar);
void NativePciBridgeDeviceSetBarEx(UINT32* DeviceBase, UINT8 Bar, UINT32 Value);
UINT8 NativePciBridgeDeviceGetPrimaryBusNumberEx(UINT32* DeviceBase);
UINT8 NativePciBridgeDeviceGetSecondaryBusNumberEx(UINT32* DeviceBase);
UINT8 NativePciBridgeDeviceGetSubordinateBusNumberEx(UINT32* DeviceBase);
UINT8 NativePciBridgeDeviceGetSecondaryLatencyTimerEx(UINT32* DeviceBase);
UINT8 NativePciBridgeDeviceGetIoBaseEx(UINT32* DeviceBase);
UINT8 NativePciBridgeDeviceGetIoLimitEx(UINT32* DeviceBase);
UINT16 NativePciBridgeDeviceGetSecondaryStatusEx(UINT32* DeviceBase);
void NativePciBridgeDeviceSetSecondaryStatusEx(UINT32* DeviceBase, UINT16 Value);
UINT16 NativePciBridgeDeviceGetMemoryBaseEx(UINT32* DeviceBase);
UINT16 NativePciBridgeDeviceGetMemoryLimitEx(UINT32* DeviceBase);
UINT16 NativePciBridgeDeviceGetPrefetchableMemoryBaseEx(UINT32* DeviceBase);
UINT16 NativePciBridgeDeviceGetPrefetchableMemoryLimitEx(UINT32* DeviceBase);
UINT32 NativePciBridgeDeviceGetPrefetchableMemoryUpper32BaseEx(UINT32* DeviceBase);
UINT32 NativePciBridgeDeviceGetPrefetchableMemoryUpper32LimitEx(UINT32* DeviceBase);
UINT16 NativePciBridgeDeviceGetIoUpper16BaseEx(UINT32* DeviceBase);
UINT16 NativePciBridgeDeviceGetIoUpper16LimitEx(UINT32* DeviceBase);
UINT8 NativePciBridgeDeviceGetCapabilitiesPointerEx(UINT32* DeviceBase);
UINT32 NativePciBridgeDeviceGetExpansionRomBaseEx(UINT32* DeviceBase);
UINT8 NativePciBridgeDeviceGetInterruptLineEx(UINT32* DeviceBase);
void NativePciBridgeDeviceSetInterruptLineEx(UINT32* DeviceBase, UINT8 Value);
UINT8 NativePciBridgeDeviceGetInterruptPinEx(UINT32* DeviceBase);
UINT16 NativePciBridgeDeviceGetBridgeControlEx(UINT32* DeviceBase);

UINT32 NativePciBridgeDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
void NativePciBridgeDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value);
UINT8 NativePciBridgeDeviceGetPrimaryBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciBridgeDeviceGetSecondaryBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciBridgeDeviceGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciBridgeDeviceGetSecondaryLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciBridgeDeviceGetIoBase(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciBridgeDeviceGetIoLimit(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciBridgeDeviceGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV);
void NativePciBridgeDeviceSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
UINT16 NativePciBridgeDeviceGetMemoryBase(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciBridgeDeviceGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciBridgeDeviceGetPrefetchableMemoryBase(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciBridgeDeviceGetPrefetchableMemoryLimit(PPCI_DEVICE_OBJECT PDEV);
UINT32 NativePciBridgeDeviceGetPrefetchableMemoryUpper32Base(PPCI_DEVICE_OBJECT PDEV);
UINT32 NativePciBridgeDeviceGetPrefetchableMemoryUpper32Limit(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciBridgeDeviceGetIoUpper16Base(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciBridgeDeviceGetIoUpper16Limit(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciBridgeDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV);
UINT32 NativePciBridgeDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciBridgeDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
void NativePciBridgeDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
UINT8 NativePciBridgeDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciBridgeDeviceGetBridgeControl(PPCI_DEVICE_OBJECT PDEV);

UINT32 NativePciCardBusGetCardBusSocketExCaBaseAddressEx(UINT32* DeviceBase);
UINT8 NativePciCardBusGetOffsetCapabilitiesEx(UINT32* DeviceBase);
UINT16 NativePciCardBusGetSecondaryStatusEx(UINT32* DeviceBase);
void NativePciCardBusSetSecondaryStatusEx(UINT32* DeviceBase, UINT16 Value);
UINT8 NativePciCardBusGetPciBusNumberEx(UINT32* DeviceBase);
UINT8 NativePciCardBusGetCardBusNumberEx(UINT32* DeviceBase);
UINT8 NativePciCardBusGetSubordinateBusNumberEx(UINT32* DeviceBase);
UINT8 NativePciCardBusGetCardBusLatencyTimerEx(UINT32* DeviceBase);
UINT32 NativePciCardBusGetMemoryBaseAddressEx(UINT32* DeviceBase, UINT8 x);
UINT32 NativePciCardBusGetMemoryLimitEx(UINT32* DeviceBase, UINT8 x);
UINT32 NativePciCardBusGetIoBaseAddressEx(UINT32* DeviceBase, UINT8 x);
UINT32 NativePciCardBusGetIoLimitEx(UINT32* DeviceBase, UINT8 x);
UINT8 NativePciCardBusGetInterruptLineEx(UINT32* DeviceBase);
void NativePciCardBusSetInterruptLineEx(UINT32* DeviceBase, UINT8 Value);
UINT8 NativePciCardBusGetInterruptPinEx(UINT32* DeviceBase);
UINT16 NativePciCardBusGetBridgeControlEx(UINT32* DeviceBase);
UINT16 NativePciCardBusGetSubsystemVendorIdEx(UINT32* DeviceBase);
UINT16 NativePciCardBusGetSubsystemDeviceIdEx(UINT32* DeviceBase);
UINT32 NativePciCardBusGet16BitPcCardLegacyModeBaseAddressEx(UINT32* DeviceBase);

UINT32 NativePciCardBusGetCardBusSocketExCaBaseAddress(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciCardBusGetOffsetCapabilities(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciCardBusGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV);
void NativePciCardBusSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
UINT8 NativePciCardBusGetPciBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciCardBusGetCardBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciCardBusGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV);
UINT8 NativePciCardBusGetCardBusLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
UINT32 NativePciCardBusGetMemoryBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
UINT32 NativePciCardBusGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
UINT32 NativePciCardBusGetIoBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
UINT32 NativePciCardBusGetIoLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
UINT8 NativePciCardBusGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
void NativePciCardBusSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
UINT8 NativePciCardBusGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciCardBusGetBridgeControl(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciCardBusGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV);
UINT16 NativePciCardBusGetSubsystemDeviceId(PPCI_DEVICE_OBJECT PDEV);
UINT32 NativePciCardBusGet16BitPcCardLegacyModeBaseAddress(PPCI_DEVICE_OBJECT PDEV);


DRIVER_EXPORT UINT32 PciHalReadUint32(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
DRIVER_EXPORT void PciHalWriteUint32(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT32 Value);
DRIVER_EXPORT UINT16 PciHalReadUint16(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
DRIVER_EXPORT void PciHalWriteUint16(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT16 Value);
DRIVER_EXPORT UINT8 PciHalReadUint8(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
DRIVER_EXPORT void PciHalWriteUint8(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT8 Value);
DRIVER_EXPORT UINT16 PciHalGetVendorId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalGetDeviceId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalGetCommand(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT void PciHalSetCommand(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
DRIVER_EXPORT UINT16 PciHalGetStatus(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT void PciHalSetStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
DRIVER_EXPORT UINT8 PciHalGetRevisionId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalGetProgIf(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalGetSubClass(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalGetClassCode(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalGetCacheLineSize(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT void PciHalSetCacheLineSize(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
DRIVER_EXPORT void PciHalSetLatencyTimer(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
DRIVER_EXPORT UINT8 PciHalGetLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalGetHeaderType(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalGetBist(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT void PciHalSetBist(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);

DRIVER_EXPORT UINT32 PciHalGeneralDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
DRIVER_EXPORT void PciHalGeneralDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value);
DRIVER_EXPORT UINT32 PciHalGeneralDeviceGetCardBusCisPointer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalGeneralDeviceGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalGeneralDeviceGetSubsystemId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT32 PciHalGeneralDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalGeneralDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalGeneralDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT void PciHalGeneralDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
DRIVER_EXPORT UINT8 PciHalGeneralDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalGeneralDeviceGetMinGrant(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalGeneralDeviceGetMaxLatency(PPCI_DEVICE_OBJECT PDEV);


DRIVER_EXPORT UINT32 PciHalBridgeDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
DRIVER_EXPORT void PciHalBridgeDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value);
DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetPrimaryBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetSecondaryBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetSecondaryLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetIoBase(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetIoLimit(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT void  PciHalBridgeDeviceSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetMemoryBase(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetPrefetchableMemoryBase(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetPrefetchableMemoryLimit(PPCI_DEVICE_OBJECT PDEV); 
DRIVER_EXPORT UINT32 PciHalBridgeDeviceGetPrefetchableMemoryUpper32Base(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT32 PciHalBridgeDeviceGetPrefetchableMemoryUpper32Limit(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetIoUpper16Base(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetIoUpper16Limit(PPCI_DEVICE_OBJECT PDEV);    
DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT32 PciHalBridgeDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT void PciHalBridgeDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
DRIVER_EXPORT UINT8 PciHalBridgeDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalBridgeDeviceGetBridgeControl(PPCI_DEVICE_OBJECT PDEV);

DRIVER_EXPORT UINT32 PciHalCardBusDeviceGetCardBusSocketExCaBaseAddress(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetOffsetCapabilities(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalCardBusDeviceGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT void PciHalCardBusDeviceSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetPciBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetCardBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetCardBusLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT32 PciHalCardBusDeviceGetMemoryBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
DRIVER_EXPORT UINT32 PciHalCardBusDeviceGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
DRIVER_EXPORT UINT32 PciHalCardBusDeviceGetIoBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
DRIVER_EXPORT UINT32 PciHalCardBusDeviceGetIoLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT void PciHalCardBusDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
DRIVER_EXPORT UINT8 PciHalCardBusDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalCardBusDeviceGetBridgeControl(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalCardBusDeviceGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT16 PciHalCardBusDeviceGetSubsystemDeviceId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT32 PciHalCardBusDeviceGet16BitPcCardLegacyModeBaseAddress(PPCI_DEVICE_OBJECT PDEV);



DRIVER_EXPORT LOUSTATUS PciHalEnableIoSpace(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT LOUSTATUS PciHalDisableIoSpace(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT BOOLEAN PciHalIsIoSpaceEnabled(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT LOUSTATUS PciHalEnableMemorySpace(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT LOUSTATUS PciHalDisableBusMaster(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT LOUSTATUS PciHalEnableBusMaster(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT BOOLEAN PciHalIsBusMasterEnabled(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT LOUSTATUS PciHalDisableMemorySpace(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT BOOLEAN PciHalIsMemorySpaceEnabled(PPCI_DEVICE_OBJECT PDEV);


DRIVER_EXPORT PVOID PciHalGetIoRegion(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, SIZE Offset);
DRIVER_EXPORT SIZE PciHalGetIoRegionSize(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
DRIVER_EXPORT LOUSTATUS PciHalAllocatePciIrqVectors(PPCI_DEVICE_OBJECT PDEV, UINT32 RequestedVectors, UINT64 Flags);
DRIVER_EXPORT UINT8 PciHalGetIrqVector(PPCI_DEVICE_OBJECT PDEV, UINT8 Member);
DRIVER_EXPORT void PciHalFreeIrqVectors(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT UINT8 PciHalGetIrqVectorCount(PPCI_DEVICE_OBJECT PDEV);
DRIVER_EXPORT PPCI_DEVICE_OBJECT PciHalGetDeviceFromBusAddress(UINT16 Group, UINT8 Bus, UINT8 Slot, UINT8 Function);
DRIVER_EXPORT void PciHalGetConfigurationSnapshot(PPCI_DEVICE_OBJECT PDEV, PPCI_COMMON_CONFIG Config);


DRIVER_EXPORT LOUSTATUS PciHalMapPciResource(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT64 OverideFlags);

DRIVER_EXPORT LOUSTATUS PciHalScanBootDevices();
DRIVER_EXPORT LOUSTATUS PciHalRegisterLousinePciDeviceTable(PDRIVER_OBJECT DriverObject, PLOUSINE_PCI_DEVICE_TABLE DeviceTable);
DRIVER_EXPORT PPCI_DEVICE_OBJECT PciHalGetPciDeviceObjectFromLdmDeviceObject(PDEVICE_OBJECT DeviceObject);



LOUSTATUS PciHalRegisterPciDevice(PPCI_DEVICE_OBJECT PDEV);
void PciHalInitializePciBridge(PPCI_DEVICE_OBJECT PDEV);

#endif