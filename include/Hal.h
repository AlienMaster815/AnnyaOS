#ifndef _HAL_H
#define _HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <drivers/pci.h>

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