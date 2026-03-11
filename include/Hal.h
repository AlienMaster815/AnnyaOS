#ifndef _HAL_H
#define _HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel/memmory.h>
#include <drivers/pci.h>
#include <Firmware/Dmi.h>
#include <Devices.h>
#include <DRSD.h>
#include <Ldm.h>

typedef enum _HAL_QUERY_INFORMATION_CLASS{
    HalInstalledBusInformation = 0,
    HalProfileSourceInformation,
    HalInformationClassUnused1,
    HalPowerInformation,
    HalProcessorSpeedInformation,
    HalCallbackInformation,
    HalMapRegisterInformation,
    HalMcaLogInformation,
    HalFrameBufferCachingInformation,
    HalDisplayBiosInformation,
    HalProcessorFeatureInformation,
    HalNumaTopologyInterface,
    HalErrorInformation,
    HalCmcLogInformation,
    HalCpeLogInformation,
    HalQueryMcaInterface,
    HalQueryAMLIIllegalIOPortAddresses,
    HalQueryMaxHotPlugMemoryAddress,
    HalPartitionIpiInterface,
    HalPlatformInformation,
    HalQueryProfileSourceList,
    HalInitLogInformation,
    HalFrequencyInformation,
    HalProcessorBrandString,
    HalHypervisorInformation,
    HalPlatformTimerInformation,
    HalAcpiAuditInformation,
    HalIrtInformation,
    HalSecondaryInterruptInformation,
    HalParkingPageInformation,
    HalNumaRangeTableInformation,
    HalChannelTopologyInformation,
    HalExternalCacheInformation,
    HalQueryDebuggerInformation,
    HalFwBootPerformanceInformation,
    HalFwS3PerformanceInformation,
    HalGetChannelPowerInformation,
    HalQueryStateElementInformation,
    HalPsciInformation,
    HalInterruptControllerInformation,
    HalQueryIommuReservedRegionInformation,
    HalQueryArmErrataInformation,
    HalQueryProcessorEfficiencyInformation,
    HalQueryAcpiWakeAlarmSystemPowerStateInformation,
    HalQueryProfileIsTimerBasedProfiling,
    HalQueryProfileNumberOfCounters,
    HalQueryHyperlaunchEntrypoint,
    HalHardwareWatchdogInformation,
    HalDmaRemappingInformation,
    HalQueryUnused0001,
    HalHeterogeneousMemoryAttributesInterface,
    HalQueryPerDeviceMsiLimitInformation,
    HalQueryProfileCorruptionStatus,
    HalQueryProfileCounterOwnership,
    HalQueryMpamInformation,
    HalAmuInformation,
    HalQueryApHibernateResumePc,
    HalQueryArm64PlatformInformation
}HAL_QUERY_INFORMATION_CLASS, * PHAL_QUERY_INFORMATION_CLASS;

typedef LOUSTATUS HalQuerySystemInformation(HAL_QUERY_INFORMATION_CLASS InfoClass, ULONG BufferSize, PVOID Buffer, PULONG ReturnedLength);

typedef HalQuerySystemInformation* pHalQuerySystemInformation;

typedef LOUSTATUS HalSetSystemInformation(HAL_QUERY_INFORMATION_CLASS InfoClass, ULONG BufferSize, PVOID Buffer);

typedef HalSetSystemInformation* pHalSetSystemInformation;

typedef LOUSTATUS HalQueryBusSlots(PBUS_HANDLER BusHandler, ULONG Index, PULONG Data, PULONG Remaining);

typedef HalQueryBusSlots* pHalQueryBusSlots;

typedef LOUSTATUS HalIoReadPartitionTable(
    PDEVICE_OBJECT              DeviceObject,
    ULONG                       SectorSize,
    BOOLEAN                     ReturnRecognizedPartitions,
    PDRIVE_LAYOUT_INFORMATION*  PartitionBuffer
);

typedef HalIoReadPartitionTable* pHalIoReadPartitionTable;

typedef LOUSTATUS HalIoSetPartitionInformation(
    PDEVICE_OBJECT  DeviceObject, 
    ULONG           SectorSize,
    ULONG           PartitionNumber,
    ULONG           PartitionType
);

typedef HalIoSetPartitionInformation* pHalIoSetPartitionInformation;

typedef LOUSTATUS HalIoWritePartitionTable(
    PDEVICE_OBJECT  DeviceObject,
    ULONG           SectorSize,
    ULONG           SectorsPerTrack,
    ULONG           NumberOfHeads
);

typedef HalIoWritePartitionTable* pHalIoWritePartitionTable;

typedef PBUS_HANDLER HalHandlerForBus(
    INTERFACE_TYPE InterfaceType, 
    ULONG BusNumber
);

typedef HalHandlerForBus* pHalHandlerForBus;

typedef void HalReferenceBusHandler(PBUS_HANDLER BusHandler);

typedef HalReferenceBusHandler* pHalReferenceBusHandler;

typedef LOUSTATUS HalInitPnpDriver();

typedef HalInitPnpDriver* pHalInitPnpDriver;

typedef LOUSTATUS HalInitPowerManagement(PVOID Info);

typedef HalInitPowerManagement* pHalInitPowerManagement;

typedef PDMA_ADAPTER HalGetDmaAdapter(
    PVOID                   Context,
    PDEVICE_DESCRIPTION     DeviceDescription,
    PULONG                  MapRegisterCount
);
typedef HalGetDmaAdapter* pHalGetDmaAdapter;

typedef enum _RESOURCE_TRANSLATION_DIRECTION{
    DevicePropertyDeviceDescription = 0,
    DevicePropertyHardwareID,
    DevicePropertyCompatibleIDs,
    DevicePropertyBootConfiguration,
    DevicePropertyBootConfigurationTranslated,
    DevicePropertyClassName,
    DevicePropertyClassGuid,
    DevicePropertyDriverKeyName,
    DevicePropertyManufacturer,
    DevicePropertyFreindlyName,
    DevicePropertyLocationInformation,
    DevicePropertyPhysicalDeviceObjectName,
    DevicePropertyButTypeGuid,
    DevicePropertyLegacyBusType,
    DevicePropertyBusNumber,
    DevicePropertyEnumeratorName,
    DevicePropertyAddress,
    DevicePropertyUINumber,
    DevicePropertyInstallState,
    DevicePropertyRemovalPolicy,
    DevicePropertyResourceRequirements,
    DevicePropertyAllocatedResources,
    DevicePropertyContainorID,
}RESOURCE_TRANSLATION_DIRECTION, * PRESOURCE_TRANSLATION_DIRECTION;

typedef 
LOUSTATUS 
TRANSLATE_RESOURCE_HANDLER(
    PVOID                               Context,
    PCM_PARTIAL_RESOURCE_LIST           Source,
    RESOURCE_TRANSLATION_DIRECTION      Direction,
    ULONG                               AltCount
);
typedef TRANSLATE_RESOURCE_HANDLER* PTRANSLATE_RESOURCE_HANDLER;

typedef 
LOUSTATUS
TRANSLATE_RESOURCE_REQUIREMENTS_HANDLER(
    PVOID                   Context,
    PIO_RESOURCE_DESCRIPTOR Source,
    PDEVICE_OBJECT          PhyDeviceObject,
    PULONG                  TargetCount,
    PIO_RESOURCE_DESCRIPTOR Target
);
typedef TRANSLATE_RESOURCE_REQUIREMENTS_HANDLER* PTRANSLATE_RESOURCE_REQUIREMENTS_HANDLER;

typedef struct _TRANSLATOR_INTERFACE{
    USHORT                                      Size;
    USHORT                                      Version;
    PVOID                                       Context;
    PINTERFACE_REFERENCE                        InterfaceReference;
    PINTERFACE_DEREFERENCE                      InterfaceDereference;
    PTRANSLATE_RESOURCE_HANDLER                 TranslateResource;
    PTRANSLATE_RESOURCE_REQUIREMENTS_HANDLER    TranslateResourceReq;
}TRANSLATOR_INTERFACE, * PTRANSLATOR_INTERFACE;

typedef LOUSTATUS HalGetInterruptTranslator(
    INTERFACE_TYPE          ParrentInterfaceType,
    ULONG                   ParrentBussNumber,
    INTERFACE_TYPE          BridgeInterfaceType,
    USHORT                  Size,
    USHORT                  VendorsDictionary,
    PTRANSLATOR_INTERFACE   Translator,
    PULONG                  BridgeBusNumber
);


#ifndef _USER_MODE_CODE_

#define LouKeHalClosePciCompanions(x) LouKeFree((PVOID)x)
#define LouKeClosePciDeviceGroup(x) LouKeFree((uint8_t*)x)
KERNEL_EXPORT void* LouKeHalGetPciVirtualBaseAddress(PPCI_COMMON_CONFIG Config, uint8_t BarNumber);
KERNEL_EXPORT void LouKeHalPciSetMaster(PPCI_DEVICE_OBJECT PDEV);
KERNEL_EXPORT LOUSTATUS LouKeHalEnablePciDevice(PPCI_DEVICE_OBJECT PDEV);
KERNEL_EXPORT LOUSTATUS LouKeHalMallocPciIrqVectors(PPCI_DEVICE_OBJECT PDEV, UINT32 RequestedVectors, uint64_t Flags);
KERNEL_EXPORT void LouKeHalFreePciIrqVectors(PPCI_DEVICE_OBJECT PDEV);
KERNEL_EXPORT UINT8 LouKeHalGetPciIrqVectorCount(PPCI_DEVICE_OBJECT PDEV);
KERNEL_EXPORT LOUSTATUS LouKeRegisterDevice(PPCI_DEVICE_OBJECT PDEV, SYSTEM_DEVICE_IDENTIFIER Sdi, string LRE, void* KeyData, void* DevicePrivateData);
KERNEL_EXPORT void LouKeHalGetPciConfiguration(PPCI_DEVICE_OBJECT PDEV, PPCI_COMMON_CONFIG Config);
KERNEL_EXPORT void LouKeHalPciEnableInterrupts(PPCI_DEVICE_OBJECT PDEV);
KERNEL_EXPORT void LouKeHalPciDisableInterrupts(PPCI_DEVICE_OBJECT PDEV);
KERNEL_EXPORT void LouKeHalAcpiShutdown();
KERNEL_EXPORT size_t LouKeHalGetPciBaseAddressSize(PPCI_DEVICE_OBJECT PciConfig, uint8_t BarNum);
KERNEL_EXPORT void* LouKePciGetIoRegion(PPCI_DEVICE_OBJECT PDEV, uint8_t BarNumber, size_t BarOffset);
KERNEL_EXPORT LOUSTATUS LouKePassVramToDrsdMemoryManager(PDRSD_DEVICE Device, void* VramBase, size_t size, void* PAddress);
KERNEL_EXPORT uint64_t LouKePciGetVirtualBarAddress(uint64_t PhyAddress);
KERNEL_EXPORT PPCI_DEVICE_OBJECT LouKeHalGetPDEV(uint16_t Group, uint8_t Bus, uint8_t Slot, uint8_t Function);
KERNEL_EXPORT UINT16 LouKeHalGetChipsetVendor();
KERNEL_EXPORT PDMI_SYSTEM_ID LouKeDmiGetFirstMatch(PDMI_SYSTEM_ID IdList);
KERNEL_EXPORT UINT8 LouKeHalGetPciIrqVector(PPCI_DEVICE_OBJECT PDEV, UINT8 Irq);
KERNEL_EXPORT LOUSTATUS LouKeHalQuerySystemInformation(HAL_QUERY_INFORMATION_CLASS InfoClass, ULONG BufferSize, PVOID Buffer, PULONG ReturnedLength); //export as HalQuerySystemInformation as NTOSKRNL.EXE 
KERNEL_EXPORT LOUSTATUS LouKeHalSetSystemInformation(HAL_QUERY_INFORMATION_CLASS InfoClass, ULONG BufferSize, PVOID Buffer);                          //export as HalSetSystemInformation as NTOSKRNL.EXE
KERNEL_EXPORT LOUSTATUS LouKeHalQueryBusSlots(PBUS_HANDLER BusHandler, ULONG Index, PULONG Data, PULONG Remaining);
KERNEL_EXPORT LOUSTATUS LouKeHalIoReadPartitionTable(PDEVICE_OBJECT DeviceObject, ULONG SectorSize, BOOLEAN ReturnRecognizedPartitions, PDRIVE_LAYOUT_INFORMATION* PartitionBuffer);
KERNEL_EXPORT LOUSTATUS LouKeHalIoSetPartitionInformation(PDEVICE_OBJECT DeviceObject, ULONG SectorSize, ULONG PartitionNumber, ULONG PartitionType);
KERNEL_EXPORT LOUSTATUS LouKeHalIoWritePartitionTable(PDEVICE_OBJECT DeviceObject, ULONG SectorSize, ULONG SectorsPerTrack, ULONG NumberOfHeads);
KERNEL_EXPORT PBUS_HANDLER LouKeHalHandlerForBus(INTERFACE_TYPE InterfaceType,ULONG BusNumber);
KERNEL_EXPORT void LouKeHalReferenceBusHandler(PBUS_HANDLER BusHandler);
KERNEL_EXPORT LOUSTATUS LouKeHalInitPnpDriver();
KERNEL_EXPORT LOUSTATUS LouKeHalInitPowerManagement(PVOID Info);
KERNEL_EXPORT PDMA_ADAPTER LouKeHalGetDmaAdapter(PVOID Context, PDEVICE_DESCRIPTION DeviceDescription, PULONG MapRegisterCount);
KERNEL_EXPORT LOUSTATUS LouKeHalGetInterruptTranslator(INTERFACE_TYPE ParrentInterfaceType, ULONG ParrentBussNumber, INTERFACE_TYPE BridgeInterfaceType, USHORT Size, USHORT VendorsDictionary, PTRANSLATOR_INTERFACE Translator, PULONG BridgeBusNumber);
#ifndef _KERNEL_MODULE_
void LouKeInitializePciCommonPacketAnyType(PPCI_COMMON_CONFIG PciCommon);
void LouKeInitializePciCommonPacketAnyType(PPCI_COMMON_CONFIG PciCommon);
PPCI_DEVICE_GROUP LouKeHalOpenPciCompanions(PPCI_DEVICE_OBJECT PDEV);
bool LouKeHalIsDevicePcie(PPCI_DEVICE_OBJECT PDEV);
uint8_t LouKeHalFindCompatibility(PPCI_DEVICE_OBJECT PDEV, int32_t Capability);
PPCI_DEVICE_GROUP* LouKeOpenPciDeviceGroup(PPCI_COMMON_CONFIG PciConfig); 
uint8_t LouKeGetPciCountByType(PPCI_COMMON_CONFIG PciConfig);
void LouKeHalRegisterPciDevice(PPCI_DEVICE_OBJECT PDEV);
PPCI_CONTEXT LouKeHalPciSaveContext(PPCI_DEVICE_OBJECT PDEV);
void LouKeHalPciRestoreContext(PPCI_CONTEXT PciContext);
void LouKeHalPciClearMaster(PPCI_DEVICE_OBJECT PDEV);
LOUSTATUS LouKeHalPciSetMmio(PPCI_DEVICE_OBJECT PDEV);
void LouKeHalAcpiShutdown();
#endif
#endif
#ifdef __cplusplus
}
#endif
#endif //HAL_H