//Copyright GPL-2 Tyler Grenier (2024 - 2026)
#include <LouDDK.h>
#include <Hal.h>

bool IsPataCheck(uint8_t bus, uint8_t slot, uint8_t function);
void InitializeAtaDevice();

LOUSTATUS InitializeScsiDevice(PPCI_DEVICE_OBJECT PDEV);

LOUAPI
void LOUSB_DRIVER_INIT(
	PPCI_DEVICE_OBJECT USB_DEV
);

LOUAPI
void FindAnyHiddenUsbSystems();

LOUSTATUS InitializeGenericAtaDevice(PPCI_DEVICE_OBJECT PDEV);

//static bool AhciDriverLoaded = false;
//static PDRIVER_OBJECT AhciDriverObject = 0x00;

//LOUSTATUS AhciDriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryEntry);
LOUAPI void* LouKeGetBootDevice(size_t Index);
LOUSTATUS LouKeInitializeNetworkManager();
LOUAPI size_t GetBootDeviceCount();
LOUAPI DRIVER_MODULE_ENTRY LouKeLoadBootKernelModule(uintptr_t Base, void** DriverObject, size_t DriverObjectSize);

size_t LouKeGetBootDeviceIndex(PPCI_COMMON_CONFIG Config);
