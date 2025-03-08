#include <LouDDK.h>
#include <NtAPI.h> 

LOUSTATUS InitializeXhciDevice(
    P_PCI_DEVICE_OBJECT PDEV
);

void InitializeOhciDevice(P_PCI_DEVICE_OBJECT PDEV);

LOUDDK_API_ENTRY
void LOUSB_DRIVER_INIT(
	P_PCI_DEVICE_OBJECT USB_DEV
) {
	LouPrint("Initializing USB Driver\n");

	PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)USB_DEV->CommonConfig;

	switch(Config->Header.ProgIf){

		case 0x10:  
            InitializeOhciDevice(USB_DEV);
			return;
		case 0x20:
            LouPrint("Initializing EHCI Device\n");
            while(1){

            }

		case 0x30:
            InitializeXhciDevice(USB_DEV);
		default:
			return;
	}

}
