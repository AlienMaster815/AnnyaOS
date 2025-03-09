#include <LouDDK.h>
#include <Hal.h>

#define NOT_A_PCI_DEVICE 0xFFFF 

static bool UsingPCIe = false;

void SetPCIeMode(){
    UsingPCIe = true;
}

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


bool IsPciBus(uint8_t bus, uint8_t slot, uint8_t func);

LOUDDK_API_ENTRY void checkBus(uint16_t Group, uint8_t bus) {
    uint8_t device;

    for (device = 0; device < 32; device++) {
        checkDevice(Group, bus, device);
    }
}


LOUDDK_API_ENTRY void checkDevice(uint16_t Group, uint8_t bus, uint8_t device) {

    uint8_t function = 0;
    uint16_t vendorID = PciGetVendorID(Group, bus, device);

    if (vendorID == NOT_A_PCI_DEVICE) return; // Device doesn't exist
    checkFunction(Group, bus, device, function);
    //LouPrint("PCI Device Found Vedor Is: %h and Device Is: %h\n", vendorID, PciGetDeviceID( bus , device, function));
    uint8_t headerType = getHeaderType(Group, bus, device, function);

    if ((headerType & 0x80) != 0) {
        LouPrint("Device Is MultiFunction\n");
        // It's a multi-function device, so check remaining functions
        for (function = 0; function < 8; function++) {
            if (PciGetVendorID(Group, bus, device) != NOT_A_PCI_DEVICE) {
                checkFunction(Group, bus, device, function);
                if (PciGetDeviceID(Group, bus, device, function) == NOT_A_PCI_DEVICE) continue;
                else {
                    P_PCI_DEVICE_OBJECT PDev = (P_PCI_DEVICE_OBJECT)LouKeMallocEx(sizeof(PCI_DEVICE_OBJECT), GET_ALIGNMENT(PCI_DEVICE_OBJECT), WRITEABLE_PAGE | PRESENT_PAGE);
                    LouPrint("Multi Function PCI Device Found Vedor Is: %h and Device Is: %h\n", vendorID, PciGetDeviceID(Group, bus, device, function));
                    PDev->bus = bus;
                    PDev->slot = device;
                    PDev->func = function;
                    PDev->InterruptLine = LouKeGetPciInterruptLine(PDev);
                    PDev->InterruptPin = LouKeGetPciInterruptPin(PDev);
                    LouKeHalRegisterPciDevice(
                        PDev
                    );
                }
            }
        }
    }
    else{
        P_PCI_DEVICE_OBJECT PDev = (P_PCI_DEVICE_OBJECT)LouKeMallocEx(sizeof(PCI_DEVICE_OBJECT), GET_ALIGNMENT(PCI_DEVICE_OBJECT), WRITEABLE_PAGE | PRESENT_PAGE);
        LouPrint("Single Function PCI Device Found Vedor Is: %h and Device Is: %h\n", vendorID, PciGetDeviceID(Group, bus, device, function));
        PDev->bus = bus;
        PDev->slot = device;
        PDev->func = function;
        PDev->InterruptLine = LouKeGetPciInterruptLine(PDev);
        PDev->InterruptPin = LouKeGetPciInterruptPin(PDev);
        LouKeHalRegisterPciDevice(
            PDev
        );
    }   
}



LOUDDK_API_ENTRY void checkFunction(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function) {
    uint8_t baseClass;
    uint8_t subClass;
    uint8_t secondaryBus;

    baseClass = getBaseClass(Group, bus, device, function);
    subClass = getSubClass(Group, bus, device, function);
    if ((baseClass == 0x6) && (subClass == 0x4)) {
        secondaryBus = getSecondaryBus(Group, bus, device, function);
        checkBus(Group, secondaryBus);
    }
}


LOUDDK_API_ENTRY void PCI_Scan_Bus(){
    LouPrint("Scanning PCI Bus\n");
    for(uint8_t i = 0 ; i < 255; i++){
        checkBus(0, i);
    }
}

// C Land

LOUDDK_API_ENTRY uint8_t LouKeReadPciUint8(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset){
    return pciConfigReadByte(PDEV->Group, PDEV->bus,PDEV->slot,PDEV->func, Offset);
}

LOUDDK_API_ENTRY uint16_t LouKeReadPciUint16(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset){
    return pciConfigReadWord(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, Offset);

}

LOUDDK_API_ENTRY uint32_t LouKeReadPciUint32(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset){
    return pci_read(PDEV->Group, PDEV->bus,PDEV->slot,PDEV->func, Offset);
}


LOUDDK_API_ENTRY void LouKeWritePciUint8(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint8_t Value){
    pciConfigWriteByte(PDEV->Group, PDEV->bus,PDEV->slot,PDEV->func,Offset,Value);
}

LOUDDK_API_ENTRY void LouKeWritePciUint16(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint16_t Value){
    pciConfigWriteWord(PDEV->Group, PDEV->bus, PDEV->slot,PDEV->func,Offset,Value);
}

LOUDDK_API_ENTRY void LouKeWritePciUint32(P_PCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint32_t Value){
    write_pci(PDEV->Group, PDEV->bus,PDEV->slot,PDEV->func, Offset, Value);
}

LOUDDK_API_ENTRY void ScanForVideoHardware(){

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


uint64_t LouKeGetLdmModuleDeviceID(PPCI_COMMON_CONFIG Config, PLOUSINE_PCI_DEVICE_TABLE DeviceTable);

LOUDDK_API_ENTRY
void ScanTheRestOfHarware(){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&ScanLock, &Irql);

    PCI_COMMON_CONFIG Config;
	Config.Header.VendorID = ANY_PCI_ID;
	Config.Header.DeviceID = ANY_PCI_ID;
	Config.Header.u.type0.SubVendorID = ANY_PCI_ID;
	Config.Header.u.type0.SubSystemID = ANY_PCI_ID;
	Config.Header.BaseClass = ANY_PCI_CLASS;
	Config.Header.SubClass = ANY_PCI_CLASS;
	Config.Header.ProgIf = ANY_PCI_CLASS;

	uint8_t NumberOfPciDevices = LouKeGetPciCountByType(&Config);

	UNUSED PPCI_DEVICE_GROUP* SecondWaveDevices = LouKeOpenPciDeviceGroup(&Config);
    for(uint8_t i = 0 ; i < NumberOfPciDevices; i++){
        P_PCI_DEVICE_OBJECT PDEV = SecondWaveDevices[i]->PDEV;
        PPCI_COMMON_CONFIG PConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;

        if(PConfig->Header.VendorID == 0x1102){
            LouPrint("Device ID:%h\n", PConfig->Header.DeviceID);
            while(1);
        }
        string DriverPath = 0x00;
        while(1){
            DriverPath = ParseLousineDriverManifestForCompatibleDriver(PConfig, DriverPath);
            if(!DriverPath){
                break;
            }
            PDRIVER_OBJECT DriverObject;
            DRIVER_MODULE_ENTRY Driver = LouKeLoadKernelModule(DriverPath, (void**)&DriverObject, sizeof(DRIVER_OBJECT));
            if(!DriverObject->DriverExtension){
                DriverObject->DriverExtension = (PDRIVER_EXTENSION)LouKeMallocEx(sizeof(DRIVER_EXTENSION), GET_ALIGNMENT(DRIVER_EXTENSION), WRITEABLE_PAGE | PRESENT_PAGE);
                Driver(DriverObject, (PUNICODE_STRING)DriverPath);
            }
            PDEVICE_OBJECT PlatformDevice = (PDEVICE_OBJECT)LouKeMallocEx(sizeof(DEVICE_OBJECT), GET_ALIGNMENT(DEVICE_OBJECT), WRITEABLE_PAGE | PRESENT_PAGE);
            if(DriverObject->DriverUsingLkdm){
                PlatformDevice->PDEV = PDEV;
                if(DriverObject->DeviceTable){ 
                    PlatformDevice->DeviceID = LouKeGetLdmModuleDeviceID(PConfig, (PLOUSINE_PCI_DEVICE_TABLE)DriverObject->DeviceTable);
                }
            }
            DriverObject->DriverExtension->AddDevice(DriverObject, PlatformDevice);
        }
    }
    LouKeReleaseSpinLock(&ScanLock, &Irql);    
}

KERNEL_IMPORT
bool LouKeSeachPreLoadedSystemModules(P_PCI_DEVICE_OBJECT PDEV);

bool IsAtaController(P_PCI_DEVICE_OBJECT PDEV);
void InitializeAtaDevice();
bool IsAhciController(P_PCI_DEVICE_OBJECT PDEV);
LOUSTATUS InitializeStartupAhciImplementation(P_PCI_DEVICE_OBJECT PDEV);
