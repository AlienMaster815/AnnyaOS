#include <LouDDK.h>
#include <NtAPI.h> 

LOUSTATUS InitializeXhciDevice(
    P_PCI_DEVICE_OBJECT PDEV
);

void InitializeOhciDevice(P_PCI_DEVICE_OBJECT PDEV);
void InitializeEhciDevice(P_PCI_DEVICE_OBJECT PDEV);

LOUDDK_API_ENTRY
void LOUSB_DRIVER_INIT(
	P_PCI_DEVICE_OBJECT USB_DEV
) {
	LouPrint("Initializing USB Driver\n");

	PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)USB_DEV->CommonConfig;

	if((Config->Header.VendorID == PCI_VENDOR_ID_STMICRO) && (Config->Header.DeviceID == 0xCC00)){
		InitializeEhciDevice(USB_DEV);	
		return;		
	}

	switch(Config->Header.ProgIf){

		case 0x10:  
            InitializeOhciDevice(USB_DEV);
			return;
		case 0x20:
			InitializeEhciDevice(USB_DEV);			
			return;
		case 0x30:
            InitializeXhciDevice(USB_DEV);
			return;
		default:
			LouPrint("Unrecognized USB Device\n");
			return;
	}

}
