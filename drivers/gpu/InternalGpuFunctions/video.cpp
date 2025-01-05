#include "VBOX/VBoxVGA.h"
#include <Hal.h>

void InitializeAmdGpu(P_PCI_DEVICE_OBJECT PDEV);

void InitializeVgaDevice(
	P_PCI_DEVICE_OBJECT PDEV
);

bool IsVGA(uint8_t bus,uint8_t slot,uint8_t function) {

	PCI_DEVICE_OBJECT VGADev;

	VGADev.bus = bus;
	VGADev.slot = slot;
	VGADev.func = function;

	if(( LouKePciReadHeaderType(&VGADev) == 0)
	&&	((LouKePciReadClass(&VGADev) == 0 && LouKePciReadSubClass(&VGADev) == 1) ||
		(LouKePciReadClass(&VGADev) == 0x03 && LouKePciReadSubClass(&VGADev) == 0x00))
		){
		InitializeVgaDevice(
			&VGADev
		);
		return true;
	}

	return false;
}


LOUSTATUS VBoxPciProbe(P_PCI_DEVICE_OBJECT PDEV);
LOUSTATUS InitializeGenericVgaDriver(P_PCI_DEVICE_OBJECT PDEV);
LOUSTATUS InitVMWareSVGA(P_PCI_DEVICE_OBJECT PDEV);

// Function to initialize the VGA device
void InitializeVgaDevice(P_PCI_DEVICE_OBJECT PDEV) {	
	
	LouPrint("Found A Video Controller\n");

	uint16_t VendorID = PciGetVendorID(PDEV->bus, PDEV->slot);
	uint16_t DeviceID = PciGetDeviceID(PDEV->bus, PDEV->slot, PDEV->func);

	PDEV->VendorID = VendorID;
	PDEV->DeviceID = DeviceID;

	if(VendorID == 0x80EE){
		PreVBoxVGAInit(PDEV);
		InitializeVirtualBoxVgaAdapter(PDEV);
		return;
	}
	if(VendorID == 0x15AD){
		InitVMWareSVGA(PDEV);
	}
	
}

LOUDDK_API_ENTRY
LOUSTATUS AmdGpuInit(P_PCI_DEVICE_OBJECT PDEV);

LOUDDK_API_ENTRY
LOUSTATUS SetupInitialVideoDevices(){

	LouPrint("Setting Up Video Devices\n");
	PCI_COMMON_CONFIG Config;
	Config.Header.VendorID = ANY_PCI_ID;
	Config.Header.DeviceID = ANY_PCI_ID;
	Config.Header.u.type0.SubVendorID = ANY_PCI_ID;
	Config.Header.u.type0.SubSystemID = ANY_PCI_ID;
	Config.Header.BaseClass = 0x03;
	Config.Header.SubClass = ANY_PCI_CLASS;
	Config.Header.ProgIf = ANY_PCI_CLASS;

	uint8_t NumberOfPciDevices;


	UNUSED PPCI_DEVICE_GROUP VideoDevices = LouKeOpenPciDeviceGroup(&Config);

	if(VideoDevices){
		NumberOfPciDevices = LouKeGetPciCountByType(&Config);
		for(uint8_t i = 0 ; i < NumberOfPciDevices; i++){
			P_PCI_DEVICE_OBJECT PDEV = VideoDevices[i].PDEV;
			UNUSED PPCI_COMMON_CONFIG PConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;

			switch(PConfig->Header.VendorID){
				case 0x80EE:
					PreVBoxVGAInit(PDEV);
					InitializeVirtualBoxVgaAdapter(PDEV);
					continue;
				case 0x15AD:
					InitVMWareSVGA(PDEV);
					continue;
				case 0x1002:
					//AmdGpuInit(PDEV);
					continue;
				default:
					continue;
			}
		}
		LouKeClosePciDeviceGroup(VideoDevices);
		VideoDevices = 0x00;
	}


	Config.Header.VendorID = 0x1002;
	Config.Header.DeviceID = ANY_PCI_ID;
	Config.Header.u.type0.SubVendorID = ANY_PCI_ID;
	Config.Header.u.type0.SubSystemID = ANY_PCI_ID;
	Config.Header.BaseClass = 0x12;
	Config.Header.SubClass = ANY_PCI_CLASS;
	Config.Header.ProgIf = ANY_PCI_CLASS;

	VideoDevices = LouKeOpenPciDeviceGroup(&Config);
	if(VideoDevices){
		NumberOfPciDevices = LouKeGetPciCountByType(&Config);
		for(uint8_t i = 0 ; i < NumberOfPciDevices; i++){
			//P_PCI_DEVICE_OBJECT PDEV = VideoDevices[i].PDEV;
			//AmdGpuInit(PDEV);
		}
		LouKeClosePciDeviceGroup(VideoDevices);
	}	

	return STATUS_SUCCESS;
}