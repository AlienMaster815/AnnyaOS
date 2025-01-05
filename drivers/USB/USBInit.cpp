#include <LouDDK.h>
#include <NtAPI.h> 

LOUSTATUS InitializeOhciHostController(
    P_PCI_DEVICE_OBJECT PDEV
);

LOUSTATUS InitializeXhciDevice(
    P_PCI_DEVICE_OBJECT PDEV
);

LOUDDK_API_ENTRY
void LOUSB_DRIVER_INIT(
	P_PCI_DEVICE_OBJECT USB_DEV
) {
	LouPrint("Initializing USB Driver\n");

	PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)USB_DEV->CommonConfig;

	switch(Config->Header.ProgIf){

		case 0x10:


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

#pragma pack(push, 1)
typedef struct _FIRM_TABLE_GROUP {
    char DeviceName[8];
    char HardwareID[16];
    char CompatibleID[16];    
    uint64_t MMIOBaseAddress;
    uint64_t MMIOSize;
    uint16_t IOPortBase;
    uint16_t IOPortSize;
    uint8_t IRQ;
    uint8_t IRQTrigger;
    uint8_t PowerState;
    uint8_t SleepState;           
} FIRM_TABLE_GROUP, *PFIRM_TABLE_GROUP;
#pragma pack(pop)


KERNEL_IMPORT
PFIRM_TABLE_GROUP LouKeGetDeviceGroupFirmwareTables(
    string HardwareID,
    uint64_t* NumberOfDevices
);
