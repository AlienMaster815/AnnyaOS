
#include <LouDDK.h>
#include <Hal.h>

static spinlock_t ScanLock;

void ScanSystemForBusses() {

	LouPrint("Scanning for PCI Bridges\n");
	LouKIRQL Irql;
    LouKeAcquireSpinLock(&ScanLock, &Irql);

    PCI_COMMON_CONFIG Config;
	Config.Header.VendorID = ANY_PCI_ID;
	Config.Header.DeviceID = ANY_PCI_ID;
	Config.Header.u.type0.SubVendorID = ANY_PCI_ID;
	Config.Header.u.type0.SubSystemID = ANY_PCI_ID;
	Config.Header.BaseClass = 0x06;//bridges
	Config.Header.SubClass = ANY_PCI_CLASS;
	Config.Header.ProgIf = ANY_PCI_CLASS;

	uint8_t NumberOfPciDevices = LouKeGetPciCountByType(&Config);

	UNUSED PPCI_DEVICE_GROUP* SecondWaveDevices = LouKeOpenPciDeviceGroup(&Config);
    for(uint8_t i = 0 ; i < NumberOfPciDevices; i++){
        P_PCI_DEVICE_OBJECT PDEV = SecondWaveDevices[i]->PDEV;
        UNUSED PPCI_COMMON_CONFIG PConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
		//LouPrint("Bus:%d :: Slot:%d :: Function:%d :: SubClass:%h\n",PDEV->bus, PDEV->slot, PDEV->func, PConfig->Header.SubClass);

		//LouPrint("Parent Bus:%d\n", LouKeReadPciUint8(PDEV, 0x18));
		//LouPrint("Child  Bus:%d\n", LouKeReadPciUint8(PDEV, 0x19));
		//LouPrint("Child  End:%d\n", LouKeReadPciUint8(PDEV, 0x1A));

		uint16_t cmd = LouKeReadPciUint16(PDEV, 0x04);
		cmd |= 0x07; // Enable I/O, Mem, Bus Master
		cmd &= ~(1 << 10);
		LouKeWritePciUint16(PDEV, 0x04, cmd);	
    }
	//bus 0 slot 3 function 0
	LouKeClosePciDeviceGroup(SecondWaveDevices);
    LouKeReleaseSpinLock(&ScanLock, &Irql);
}