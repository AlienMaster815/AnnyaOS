#include <LouDDK.h>
#include <LouACPI.h>
#include <Hal.h>

#define NOT_A_PCI_DEVICE 0xFFFF 

static POOL PciDeicePool = 0x00; 

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
    //LouPrint("Here\n");

    uint8_t function = 0;
    uint16_t vendorID = PciGetVendorID(Group, bus, device);

    if (vendorID == NOT_A_PCI_DEVICE) return; // Device doesn't exist
    //LouPrint("PCI Device Found Vedor Is: %h and Device Is: %h\n", vendorID, PciGetDeviceID( bus , device, function));
    uint8_t headerType = getHeaderType(Group, bus, device, function);

    if ((headerType & 0x80) != 0) {
        LouPrint("Device Is MultiFunction\n");
        // It's a multi-function device, so check remaining functions
        for (function = 0; function < 8; function++) {
            if (PciGetVendorID(Group, bus, device) != NOT_A_PCI_DEVICE) {
                if (PciGetDeviceID(Group, bus, device, function) == NOT_A_PCI_DEVICE) continue;
                else {
                    P_PCI_DEVICE_OBJECT PDev = (P_PCI_DEVICE_OBJECT)LouKeMallocFromFixedPool(PciDeicePool);
                    if(!PDev){
                        PDev = LouKeMallocType(PCI_DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);                    
                    }
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
        P_PCI_DEVICE_OBJECT PDev = (P_PCI_DEVICE_OBJECT)LouKeMallocFromFixedPool(PciDeicePool);
        if(!PDev){
            PDev = (P_PCI_DEVICE_OBJECT)LouKeMallocType(PCI_DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
        }
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



KERNEL_IMPORT
uint16_t GetPciGroupCount();

KERNEL_IMPORT
PPCIE_SYSTEM_MANAGER GetPcieGroupHandle(uint16_t GroupItem);

typedef struct _ACPI_MCFG_ALLOCATION{
    uint64_t    BaseAddress;
    uint16_t    PCISegmentGroupNumber;
    uint8_t     StartBusNumber;
    uint8_t     EndBusNumber;
} ACPI_MCFG_ALLOCATION, * PACPI_MCFG_ALLOCATION;

KERNEL_IMPORT void AddPcieGroup(ACPI_MCFG_ALLOCATION* PciManagerData);

LOUDDK_API_ENTRY void PCI_Scan_Bus(){

    LouPrint("Scanning PCI Bus\n");
    
    //uint16_t GroupIndex = 0;
    size_t Count = 0x00;
    //PPCIE_SYSTEM_MANAGER Psm = 0x00;
    

    PMCFG_TABLE McfgTable = (PMCFG_TABLE)LouKeAquireAcpiTable(PCI_EXSPRESS_MEMORY_MAPPED_CONFIGURATION);
    if(!McfgTable){
        for(uint8_t i = 0 ; i < 255; i++){
            checkBus(0, i);
        }
        return;
    }
    Count = GET_MCFG_ENTRY_COUNT(McfgTable);
    bool PcieDevice;
    for (uint8_t i = 0; i < 255; i++) {
        PcieDevice = false;
        for (size_t j = 0; j < Count; j++) {
            if (McfgTable->TableEntries[j].Group == 0) {
                if (RangeInterferes(i, 0, McfgTable->TableEntries[j].StartBus, McfgTable->TableEntries[j].EndBus)) {
                    PcieDevice = true;
                    break;
                }
            }
        }
        if (!PcieDevice) {
            checkBus(0, i);
        }
    }

    LouPrint("MCFG Entry Count:%h\n", Count); 
    for(size_t i = 0 ; i < Count; i++){
        ACPI_MCFG_ALLOCATION* NewGroup = LouKeMallocType(ACPI_MCFG_ALLOCATION, KERNEL_GENERIC_MEMORY);
        NewGroup->BaseAddress = McfgTable->TableEntries[i].ConfigurationBaseAddress;
        NewGroup->PCISegmentGroupNumber = McfgTable->TableEntries[i].Group;
        NewGroup->StartBusNumber = McfgTable->TableEntries[i].StartBus;
        NewGroup->EndBusNumber = McfgTable->TableEntries[i].EndBus;
        AddPcieGroup(NewGroup);
        for(size_t j = McfgTable->TableEntries[i].StartBus ; j < McfgTable->TableEntries[i].EndBus; j++){
            checkBus(McfgTable->TableEntries[i].Group, j);
        }
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

void InitializeBARHalLayer();

LOUDDK_API_ENTRY 
void LouKeMapPciMemory(){
    PciDeicePool = LouKeCreateFixedPool(0xFFFF, sizeof(PCI_DEVICE_OBJECT), GET_ALIGNMENT(PCI_DEVICE_OBJECT), "PDEV Pool", 0, KERNEL_GENERIC_MEMORY);
    InitializeBARHalLayer();
    PCI_Scan_Bus();
}

LOUSTATUS LouKeInitializeNetworkManager();

void LouKePs2Parse();

//static spinlock_t ScanLock;

uint64_t LouKeGetLdmModuleDeviceID(PPCI_COMMON_CONFIG Config, PLOUSINE_PCI_DEVICE_TABLE DeviceTable);

LOUDDK_API_ENTRY
void ScanTheRestOfHarware(){
    //LouKIRQL Irql;
    //LouKeAcquireSpinLock(&ScanLock, &Irql);

    PCI_COMMON_CONFIG Config;
	Config.Header.VendorID = ANY_PCI_ID;
	Config.Header.DeviceID = ANY_PCI_ID;
	Config.Header.u.type0.SubVendorID = ANY_PCI_ID;
	Config.Header.u.type0.SubSystemID = ANY_PCI_ID;
	Config.Header.BaseClass = ANY_PCI_CLASS;
	Config.Header.SubClass = ANY_PCI_CLASS;
	Config.Header.ProgIf = ANY_PCI_CLASS;

	uint8_t NumberOfPciDevices = LouKeGetPciCountByType(&Config);

	PPCI_DEVICE_GROUP* SecondWaveDevices = LouKeOpenPciDeviceGroup(&Config);
    for(uint8_t i = 0 ; i < NumberOfPciDevices; i++){
        P_PCI_DEVICE_OBJECT PDEV = SecondWaveDevices[i]->PDEV;
        if(PDEV->DeviceManaged){
            continue;
        }
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
                DriverObject->DriverExtension = (PDRIVER_EXTENSION)LouKeMallocType(DRIVER_EXTENSION, KERNEL_GENERIC_MEMORY);
                Driver(DriverObject, (PUNICODE_STRING)DriverPath);
            }
            PDEVICE_OBJECT PlatformDevice = (PDEVICE_OBJECT)LouKeMallocType(DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
            if(DriverObject->DriverUsingLkdm){
                PlatformDevice->PDEV = PDEV;
                if(DriverObject->DeviceTable){ 
                    PlatformDevice->DeviceID = LouKeGetLdmModuleDeviceID(PConfig, (PLOUSINE_PCI_DEVICE_TABLE)DriverObject->DeviceTable);
                }
            }
            DriverObject->DriverExtension->AddDevice(DriverObject, PlatformDevice);
        }
    }
    //LouKeReleaseSpinLock(&ScanLock, &Irql);    
}

KERNEL_IMPORT
bool LouKeSeachPreLoadedSystemModules(P_PCI_DEVICE_OBJECT PDEV);

bool IsAtaController(P_PCI_DEVICE_OBJECT PDEV);
void InitializeAtaDevice();
bool IsAhciController(P_PCI_DEVICE_OBJECT PDEV);
LOUSTATUS InitializeStartupAhciImplementation(P_PCI_DEVICE_OBJECT PDEV);
