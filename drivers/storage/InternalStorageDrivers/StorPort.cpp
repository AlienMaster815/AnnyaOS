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

LOUSTATUS InitializeAhciDevice(P_PCI_DEVICE_OBJECT PDEV);

LOUDDK_API_ENTRY 
LOUSTATUS LookForStorageDevices(){
    LouPrint("Scanning For Storage Devices\n");

	PCI_COMMON_CONFIG Config;
	Config.Header.VendorID = ANY_PCI_ID;
	Config.Header.DeviceID = ANY_PCI_ID;
	Config.Header.u.type0.SubVendorID = ANY_PCI_ID;
	Config.Header.u.type0.SubSystemID = ANY_PCI_ID;
	Config.Header.BaseClass = 0x01;
	Config.Header.SubClass = ANY_PCI_CLASS;
	Config.Header.ProgIf = ANY_PCI_CLASS;

	uint8_t NumberOfPciDevices = LouKeGetPciCountByType(&Config);

	UNUSED PPCI_DEVICE_GROUP StorageDevices = LouKeOpenPciDeviceGroup(&Config);
	if(StorageDevices){

        for(uint8_t i = 0 ; i < NumberOfPciDevices; i++){
            P_PCI_DEVICE_OBJECT PDEV = StorageDevices[i].PDEV;
            PPCI_COMMON_CONFIG PConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;

            if(PConfig->Header.SubClass == 0x06){
                InitializeAhciDevice(PDEV);
            }

            if(PConfig->Header.SubClass == 0x01){
                InitializeGenericAtaDevice(PDEV);
            }

            if((PConfig->Header.SubClass == 0x00) || (PConfig->Header.SubClass == 0x07)){
                InitializeScsiDevice(PDEV);
            }
        }

    }

    LouKeClosePciDeviceGroup(StorageDevices);

    Config.Header.BaseClass = 0x0C;
    Config.Header.SubClass = 0x03;

    NumberOfPciDevices = LouKeGetPciCountByType(&Config);
    StorageDevices = LouKeOpenPciDeviceGroup(&Config);
	if(StorageDevices){
        for(uint8_t i = 0 ; i < NumberOfPciDevices; i++){
            //P_PCI_DEVICE_OBJECT PDEV = StorageDevices[i].PDEV;
            //LOUSB_DRIVER_INIT(PDEV);
        }
    }

    LouKeClosePciDeviceGroup(StorageDevices);

    LouPrint("Done Scanning For Storage Devices\n");

    return STATUS_SUCCESS;
}