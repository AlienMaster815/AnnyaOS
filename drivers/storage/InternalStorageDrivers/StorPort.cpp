#include <LouDDK.h>
#include <Hal.h>

bool IsPataCheck(uint8_t bus, uint8_t slot, uint8_t function);
void InitializeAtaDevice();

LOUSTATUS InitializeScsiDevice(P_PCI_DEVICE_OBJECT PDEV);

LOUDDK_API_ENTRY
void LOUSB_DRIVER_INIT(
	P_PCI_DEVICE_OBJECT USB_DEV
);

LOUDDK_API_ENTRY
void FindAnyHiddenUsbSystems();

LOUSTATUS InitializeGenericAtaDevice(P_PCI_DEVICE_OBJECT PDEV);

//static bool AhciDriverLoaded = false;
//static PDRIVER_OBJECT AhciDriverObject = 0x00;

//NTSTATUS AhciDriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryEntry);
uint64_t LouKeGetLdmModuleDeviceID(PPCI_COMMON_CONFIG Config, PLOUSINE_PCI_DEVICE_TABLE DeviceTable);
KERNEL_IMPORT void* LouKeGetBootDevice(size_t Index);
LOUSTATUS LouKeInitializeNetworkManager();
KERNEL_IMPORT size_t GetBootDeviceCount();
KERNEL_IMPORT size_t LouKeGetBootDeviceIndex(void* Config);
KERNEL_IMPORT DRIVER_MODULE_ENTRY LouKeLoadBootKernelModule(uintptr_t Base, void** DriverObject, size_t DriverObjectSize);

LOUDDK_API_ENTRY 
LOUSTATUS LookForStorageDevices(){


    PCI_COMMON_CONFIG Config;
	Config.Header.VendorID = ANY_PCI_ID;
	Config.Header.DeviceID = ANY_PCI_ID;
	Config.Header.u.type0.SubVendorID = ANY_PCI_ID;
	Config.Header.u.type0.SubSystemID = ANY_PCI_ID;
	Config.Header.BaseClass = ANY_PCI_CLASS;
	Config.Header.SubClass = ANY_PCI_CLASS;
	Config.Header.ProgIf = ANY_PCI_CLASS;

	UNUSED uint8_t NumberOfPciDevices = LouKeGetPciCountByType(&Config);
	UNUSED PPCI_DEVICE_GROUP* FirstWaveDevices = LouKeOpenPciDeviceGroup(&Config);
    size_t BootDeviceCount = GetBootDeviceCount();
    size_t DeviceIndex;
    for(size_t i = 0 ; i < NumberOfPciDevices; i++){
        DeviceIndex = LouKeGetBootDeviceIndex((void*)FirstWaveDevices[i]->PDEV->CommonConfig);
        if(DeviceIndex < BootDeviceCount){
            FirstWaveDevices[i]->PDEV->DeviceManaged = true;
            void* DriverBase = LouKeGetBootDevice(DeviceIndex);
            
            PDRIVER_OBJECT DriverObject;
            DRIVER_MODULE_ENTRY Driver = LouKeLoadBootKernelModule((uintptr_t)DriverBase, (void**)&DriverObject, sizeof(DRIVER_OBJECT));
            if(!DriverObject->DriverExtension){
                DriverObject->DriverExtension = LouKeMallocType(DRIVER_EXTENSION,  KERNEL_GENERIC_MEMORY);
                Driver(DriverObject, (PUNICODE_STRING)0x00);
            }
            PDEVICE_OBJECT PlatformDevice = (PDEVICE_OBJECT)LouKeMallocType(DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
            if(DriverObject->DriverUsingLkdm){
                PlatformDevice->PDEV = FirstWaveDevices[i]->PDEV;
                if(DriverObject->DeviceTable){ 
                    PlatformDevice->DeviceID = LouKeGetLdmModuleDeviceID((PPCI_COMMON_CONFIG)FirstWaveDevices[i]->PDEV->CommonConfig, (PLOUSINE_PCI_DEVICE_TABLE)DriverObject->DeviceTable);
                }
            }
            DriverObject->DriverExtension->AddDevice(DriverObject, PlatformDevice);
        }
    }
    LouKeClosePciDeviceGroup(FirstWaveDevices);
    LouPrint("Done Scanning For Storage Devices\n");
    return STATUS_SUCCESS;
}