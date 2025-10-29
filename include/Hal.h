#ifndef _HAL_H
#define _HAL_H

typedef struct _PCI_MANAGER_DATA{
    ListHeader Neigbors;
    PPCI_DEVICE_OBJECT PDEV;
    string RegistryEntry;
    string DeviceManagerString;
}PCI_MANAGER_DATA, * PPCI_MANAGER_DATA, PCI_DEVICE_GROUP,* PPCI_DEVICE_GROUP;

typedef struct _LINUX_PCI_DEVICE_ID {
    uint32_t vendor, device;		/* Vendor and device ID or PCI_ANY_ID*/
    uint32_t subvendor, subdevice;	/* Subsystem ID's or PCI_ANY_ID */
    uint32_t Class, class_mask;	/* (class,subclass,prog-if) triplet */
    uint64_t Flags;	    /* Data private to the driver */
}LINUX_PCI_DEVICE_ID, * PLINUX_PCI_DEVICE_ID;


    #ifdef __cplusplus

        #include <LouDDK.h>

        #ifndef _KERNEL_MODULE_

            void LouKeInitializePciCommonPacketAnyType(PPCI_COMMON_CONFIG PciCommon);

            PPCI_DEVICE_GROUP LouKeHalOpenPciCompanions(
                PPCI_DEVICE_OBJECT PDEV
            );

            #define LouKeHalClosePciCompanions(x) LouKeFree((RAMADD)x)

            LOUDDK_API_ENTRY
            bool LouKeHalIsDevicePcie(
                PPCI_DEVICE_OBJECT PDEV
            );

            LOUDDK_API_ENTRY 
            uint8_t LouKeHalFindCompatibility(
                PPCI_DEVICE_OBJECT PDEV,
                int32_t Capability
            );

            LOUDDK_API_ENTRY 
            PPCI_DEVICE_GROUP* LouKeOpenPciDeviceGroup(
                PPCI_COMMON_CONFIG PciConfig
            ); 

            #define LouKeClosePciDeviceGroup(x) LouKeFree((uint8_t*)x)

            LOUDDK_API_ENTRY 
            uint8_t LouKeGetPciCountByType(
                PPCI_COMMON_CONFIG PciConfig
            );
            
            LOUDDK_API_ENTRY void* LouKeHalGetPciVirtualBaseAddress(
                PPCI_COMMON_CONFIG Config,
                uint8_t BarNumber
            );

            LOUDDK_API_ENTRY void LouKeHalRegisterPciDevice(
                PPCI_DEVICE_OBJECT PDEV
            );

            LOUDDK_API_ENTRY PPCI_CONTEXT LouKeHalPciSaveContext(
                PPCI_DEVICE_OBJECT PDEV
            );

            LOUDDK_API_ENTRY void LouKeHalPciRestoreContext(
                PPCI_CONTEXT PciContext
            );

            LOUDDK_API_ENTRY void LouKeHalPciClearMaster(
                PPCI_DEVICE_OBJECT PDEV
            );

            LOUDDK_API_ENTRY
            LOUSTATUS LouKeHalPciSetMmio(PPCI_DEVICE_OBJECT PDEV);

            LOUDDK_API_ENTRY void LouKeHalPciSetMaster(PPCI_DEVICE_OBJECT PDEV);


            LOUDDK_API_ENTRY uint64_t LouKeHalLinuxPciCheckForCompatibleConfiguration(
                PPCI_COMMON_CONFIG PciSearch, 
                PLINUX_PCI_DEVICE_ID LinuxCmpatibleDirectory
            );

            LOUDDK_API_ENTRY LOUSTATUS LouKeHalEnablePciDevice(PPCI_DEVICE_OBJECT PDEV);

            LOUDDK_API_ENTRY
            int LouKeHalMallocPciIrqVectors(
                PPCI_DEVICE_OBJECT PDEV, 
                int RequestedVectors, 
                uint64_t Flags
            );

            KERNEL_IMPORT LOUSTATUS LouKeRegisterDevice(
                PPCI_DEVICE_OBJECT PDEV, 
                SYSTEM_DEVICE_IDENTIFIER Sdi,
                string LRE, //optional
                void* KeyData, //optional
                void* DevicePrivateData
            );

            KERNEL_IMPORT
            void LouKeHalGetPciConfiguration(
                PPCI_DEVICE_OBJECT PDEV, 
                PPCI_COMMON_CONFIG Config
            );



            LOUDDK_API_ENTRY void LouKeHalPciEnableInterrupts(PPCI_DEVICE_OBJECT PDEV);
            LOUDDK_API_ENTRY void LouKeHalPciDisableInterrupts(PPCI_DEVICE_OBJECT PDEV);

            LOUDDK_API_ENTRY void LouKeHalAcpiShutdown();

            LOUDDK_API_ENTRY size_t LouKeHalGetPciBaseAddressSize(
               PPCI_DEVICE_OBJECT PciConfig,
                uint8_t BarNum  
            );
            
            void LouKeInitializePciCommonPacketAnyType(PPCI_COMMON_CONFIG PciCommon);
            
            KERNEL_IMPORT void* LouKePciGetIoRegion(
                PPCI_DEVICE_OBJECT PDEV, 
                uint8_t BarNumber,
                size_t BarOffset
            );

            KERNEL_IMPORT LOUSTATUS LouKePassVramToDrsdMemoryManager(PDRSD_DEVICE Device, void* VramBase, size_t size, void* PAddress);

            LOUDDK_API_ENTRY uint64_t LouKePciGetVirtualBarAddress(uint64_t PhyAddress);

            LOUDDK_API_ENTRY
            PPCI_DEVICE_OBJECT 
            LouKeHalGetPDEV(
                uint16_t Group, 
                uint8_t Bus, 
                uint8_t Slot, 
                uint8_t Function
            );

            LOUDDK_API_ENTRY
            UINT16 
            LouKeHalGetChipsetVendor();

        #else 
            KERNEL_EXPORT uint64_t LouKeHalLinuxPciCheckForCompatibleConfiguration(
                PPCI_COMMON_CONFIG PciSearch, 
                PLINUX_PCI_DEVICE_ID LinuxCmpatibleDirectory
            );
            KERNEL_EXPORT void GetPciConfiguration(ULONG DeviceGroup, ULONG SystemIoBusNumber,ULONG SlotNumber,ULONG Function,PPCI_COMMON_CONFIG ConfigBuffer);
            KERNEL_EXPORT LOUSTATUS LouKeHalEnablePciDevice(PPCI_DEVICE_OBJECT PDEV);

            KERNEL_EXPORT void* LouKeHalGetPciVirtualBaseAddress(
                PPCI_COMMON_CONFIG Config,
                uint8_t BarNumber
            );

            KERNEL_EXPORT PPCI_CONTEXT LouKeHalPciSaveContext(
                PPCI_DEVICE_OBJECT PDEV
            );

            KERNEL_EXPORT void LouKeHalPciRestoreContext(
                PPCI_CONTEXT PciContext
            );

            KERNEL_EXPORT void LouKeHalPciClearMaster(
                PPCI_DEVICE_OBJECT PDEV
            );

            KERNEL_EXPORT
            int LouKeHalMallocPciIrqVectors(
                PPCI_DEVICE_OBJECT PDEV, 
                int RequestedVectors, 
                uint64_t Flags
            );

            KERNEL_EXPORT void LouKeHalPciSetMaster(PPCI_DEVICE_OBJECT PDEV);

            KERNEL_EXPORT LOUSTATUS LouKeRegisterDevice(
                PPCI_DEVICE_OBJECT PDEV, 
                SYSTEM_DEVICE_IDENTIFIER Sdi,
                string LRE, //optional
                void* KeyData, //optional
                void* DevicePrivateData
            );
            KERNEL_EXPORT size_t LouKeHalGetPciBaseAddressSize(
                PPCI_DEVICE_OBJECT PciConfig,
                uint8_t BarNum  
            );

            KERNEL_EXPORT void LouKeHalAcpiShutdown();

            KERNEL_EXPORT void* LouKePciGetIoRegion(
                PPCI_DEVICE_OBJECT PDEV, 
                uint8_t BarNumber,
                size_t BarOffset
            );

            KERNEL_EXPORT LOUSTATUS LouKePassVramToDrsdMemoryManager(PDRSD_DEVICE Device, void* VramBase, size_t size , void* PAddress);

            KERNEL_EXPORT
            void LouKeHalGetPciConfiguration(
                PPCI_DEVICE_OBJECT PDEV, 
                PPCI_COMMON_CONFIG Config
            );

            KERNEL_EXPORT
            PPCI_DEVICE_OBJECT 
            LouKeHalGetPDEV(
                uint16_t Group, 
                uint8_t Bus, 
                uint8_t Slot, 
                uint8_t Function
            );

            KERNEL_EXPORT
            UINT16 
            LouKeHalGetChipsetVendor();

        #endif
    #else

    void LouKeHalAcpiShutdown();

    #endif
#endif //HAL_H