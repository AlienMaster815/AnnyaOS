#include <LouDDK.h>
#include <Hal.h>

#define NOT_A_PCI_DEVICE 0xFFFF 


bool isUsb(uint8_t bus, uint8_t slot, uint8_t function);
bool IsVGA(uint8_t bus, uint8_t slot, uint8_t function);
bool IsSerial(uint8_t bus, uint8_t slot, uint8_t function);
bool IsEithernet(uint8_t bus, uint8_t slot, uint8_t function);
bool IsChipset(uint8_t bus, uint8_t slot, uint8_t function);
bool IsAudioDevice(uint8_t bus, uint8_t slot, uint8_t function);
bool IsAGPDevice(uint8_t bus, uint8_t slot, uint8_t function);
bool isVirtualizationDevice(uint8_t bus, uint8_t slot, uint8_t function);

void RegisterUnkownDevice(uint8_t bus,uint8_t device,uint8_t function);
bool PciExternalModuleScan(uint8_t bus, uint8_t slot, uint8_t func);

LOUDDK_API_ENTRY void scan_pci_bridges();

DRIVER_IO_FUNCTION P_PCIBuffer PCI::PCI_Read(P_PCIDEV Device) {
    P_PCIBuffer PCIBuff = (P_PCIBuffer)Lou_Alloc_Mem(sizeof(PCIBuffer));


    return PCIBuff;
}

DRIVER_IO_FUNCTION void PCI::PCI_Write(P_PCIDEV Device, P_PCIBuffer buffer) {

}

bool IsPciBus(uint8_t bus, uint8_t slot, uint8_t func);

LOUDDK_API_ENTRY void checkBus(uint8_t bus) {
    uint8_t device;

    for (device = 0; device < 32; device++) {
        checkDevice(bus, device);
    }
}


LOUDDK_API_ENTRY void checkDevice(uint8_t bus, uint8_t device) {

    uint8_t function = 0;
    uint16_t vendorID = PciGetVendorID(bus, device);

    if (vendorID == NOT_A_PCI_DEVICE) return; // Device doesn't exist
    checkFunction(bus, device, function);
    //LouPrint("PCI Device Found Vedor Is: %h and Device Is: %h\n", vendorID, PciGetDeviceID( bus , device, function));
    uint8_t headerType = getHeaderType(bus, device, function);

    if ((headerType & 0x80) != 0) {
        LouPrint("Device Is MultiFunction\n");
        // It's a multi-function device, so check remaining functions
        for (function = 0; function < 8; function++) {
            if (PciGetVendorID(bus, device) != NOT_A_PCI_DEVICE) {
                checkFunction(bus, device, function);
                if (PciGetDeviceID(bus,device,function) == NOT_A_PCI_DEVICE) continue;
                else {
                    P_PCI_DEVICE_OBJECT PDev = (P_PCI_DEVICE_OBJECT)LouMalloc(sizeof(PCI_DEVICE_OBJECT));
                    LouPrint("Multi Function PCI Device Found Vedor Is: %h and Device Is: %h\n", vendorID, PciGetDeviceID(bus, device, function));
                    PDev->bus = bus;
                    PDev->slot = device;
                    PDev->func = function;
                    LouKeHalRegisterPciDevice(
                        PDev
                    );
                }
            }
        }
    }
    else{
        P_PCI_DEVICE_OBJECT PDev = (P_PCI_DEVICE_OBJECT)LouMalloc(sizeof(PCI_DEVICE_OBJECT));
        LouPrint("Single Function PCI Device Found Vedor Is: %h and Device Is: %h\n", vendorID, PciGetDeviceID(bus, device, function));
        PDev->bus = bus;
        PDev->slot = device;
        PDev->func = function;
        LouKeHalRegisterPciDevice(
            PDev
        );
    }   
}



LOUDDK_API_ENTRY void checkFunction(uint8_t bus, uint8_t device, uint8_t function) {
    uint8_t baseClass;
    uint8_t subClass;
    uint8_t secondaryBus;



    baseClass = getBaseClass(bus, device, function);
    subClass = getSubClass(bus, device, function);
    if ((baseClass == 0x6) && (subClass == 0x4)) {
        secondaryBus = getSecondaryBus(bus, device, function);
        checkBus(secondaryBus);
    }
}


LOUDDK_API_ENTRY void PCI_Scan_Bus(){
    LouPrint("Scanning PCI Bus\n");
    for(uint8_t i = 0 ; i < 255; i++){
        checkBus(i);
    }
}

// C Land

P_PCIBuffer PCI_Read(P_PCIDEV Device) {
    P_PCIBuffer PCIBuff;
    PCI Read;
    PCIBuff = Read.PCI_Read(Device);
    return PCIBuff;
}

void PCI_Write(P_PCIDEV Device, P_PCIBuffer buffer) {
    PCI Write;
    Write.PCI_Write(Device, buffer);
}

LOUDDK_API_ENTRY uint8_t LouKeReadPciUint8(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset){
    return pciConfigReadByte(PDEV->bus,PDEV->slot,PDEV->func, Offset);
}

LOUDDK_API_ENTRY uint16_t LouKeReadPciUint16(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset){
    return pciConfigReadWord(PDEV->bus,PDEV->slot,PDEV->func, Offset);

}

LOUDDK_API_ENTRY uint32_t LouKeReadPciUint32(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset){
    return pci_read(PDEV->bus,PDEV->slot,PDEV->func, Offset);
}


LOUDDK_API_ENTRY void LouKeWritePciUint8(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint8_t Value){
    pciConfigWriteByte(PDEV->bus,PDEV->slot,PDEV->func,Offset,Value);
}

LOUDDK_API_ENTRY void LouKeWritePciUint16(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint16_t Value){
    pciConfigWriteWord(PDEV->bus, PDEV->slot,PDEV->func,Offset,Value);
}

LOUDDK_API_ENTRY void LouKeWritePciUint32(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint32_t Value){
    write_pci(PDEV->bus,PDEV->slot,PDEV->func, Offset, Value);
}

LOUDDK_API_ENTRY void ScanForVideoHardware(){

}

bool IsPataCheck(uint8_t bus, uint8_t slot, uint8_t function);
void InitializeAtaDevice();

LOUSTATUS InitializeScsiDevice(P_PCI_DEVICE_OBJECT PDEV);

LOUDDK_API_ENTRY
void LOUSB_DRIVER_INIT(
	P_PCI_DEVICE_OBJECT USB_DEV
);

LOUDDK_API_ENTRY
void FindAnyHiddenUsbSystems();

LOUSTATUS ProbePiixDevice(P_PCI_DEVICE_OBJECT PDEV);

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

            if(PConfig->Header.SubClass == 0x01){
                //InitializeAtaDevice();
                ProbePiixDevice(PDEV);
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

KERNEL_IMPORT 
void LouKeRunOnNewStack(void (*func)(void*), void* FunctionParameters, size_t stack_size) ;

LOUDDK_API_ENTRY 
void LouKeMapPciMemory(){
    PCI_Scan_Bus();
}

LOUSTATUS LouKeInitializeNetworkManager();

void LouKePs2Parse();

static spinlock_t ScanLock;

KERNEL_IMPORT
void InitializePs2Mouse();

KERNEL_IMPORT
void EnablePs2Keyboard();

LOUDDK_API_ENTRY
void ScanTheRestOfHarware(){
    //LouPrint("Scanning For All Other Hardware\n");
    //LouKeInitializeNetworkManager();
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&ScanLock, &Irql);
   
    EnablePs2Keyboard();

    InitializePs2Mouse();

    LouKeReleaseSpinLock(&ScanLock, &Irql);
    
}

KERNEL_IMPORT
bool LouKeSeachPreLoadedSystemModules(P_PCI_DEVICE_OBJECT PDEV);

bool IsAtaController(P_PCI_DEVICE_OBJECT PDEV);
void InitializeAtaDevice();
bool IsAhciController(P_PCI_DEVICE_OBJECT PDEV);
LOUSTATUS InitializeStartupAhciImplementation(P_PCI_DEVICE_OBJECT PDEV);