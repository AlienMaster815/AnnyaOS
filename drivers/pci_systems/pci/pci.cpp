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

LOUDDK_API_ENTRY
void checkBus(uint16_t Group, uint8_t bus) {

    for (size_t device = 0; device < 32; device++) {
        checkDevice(Group, bus, device);
    }
}

PPCI_DEVICE_OBJECT LouKeAllocPciDevObject(){
    return (PPCI_DEVICE_OBJECT)LouKeMallocFromFixedPool(PciDeicePool);
}

void LouKeFreePciDevObject(PPCI_DEVICE_OBJECT PDEV){
    LouKeFreeFromFixedPool(PciDeicePool, (PVOID)(UINT8*)PDEV);
}

LOUDDK_API_ENTRY void checkDevice(uint16_t Group, uint8_t bus, uint8_t device) {
    //LouPrint("Here\n");

    uint8_t function = 0;
    uint16_t vendorID = PciGetVendorID(Group, bus, device);

    if (vendorID == NOT_A_PCI_DEVICE) return; // Device doesn't exist
    uint8_t headerType = getHeaderType(Group, bus, device, function);
    LouPrint("HeaderType:%d\n", headerType);
    if ((headerType & 0x80) != 0) {
        LouPrint("Device Is MultiFunction\n");
        // It's a multi-function device, so check remaining functions
        for (function = 0; function < 8; function++) {
            if (PciGetVendorID(Group, bus, device) != NOT_A_PCI_DEVICE) {
                if (PciGetDeviceID(Group, bus, device, function) == NOT_A_PCI_DEVICE) continue;
                else {
                    PPCI_DEVICE_OBJECT PDev = (PPCI_DEVICE_OBJECT)LouKeMallocFromFixedPool(PciDeicePool);
                    if(!PDev){
                        PDev = LouKeMallocType(PCI_DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);                    
                    }
                    LouPrint("Multi Function PCI Device Found Vedor Is: %h and Device Is: %h\n", vendorID, PciGetDeviceID(Group, bus, device, function));
                    PDev->Group = Group;
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
        PPCI_DEVICE_OBJECT PDev = (PPCI_DEVICE_OBJECT)LouKeMallocFromFixedPool(PciDeicePool);
        if(!PDev){
            PDev = (PPCI_DEVICE_OBJECT)LouKeMallocType(PCI_DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
        }
        LouPrint("Single Function PCI Device Found Vedor Is: %h and Device Is: %h\n", vendorID, PciGetDeviceID(Group, bus, device, function));
        PDev->Group = Group;
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

KERNEL_IMPORT size_t LouKeGetMcfgCount(void* Table);

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
    Count = LouKeGetMcfgCount((void*)McfgTable);
    bool PcieDevice;
    for (uint8_t i = 0; i < 255; i++) {
        PcieDevice = false;
        for (size_t j = 0; j < Count; j++) {
            if ((McfgTable->TableEntries[j].Group == 0) && (McfgTable->TableEntries[j].ConfigurationBaseAddress)) {
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

}

// C Land

LOUDDK_API_ENTRY uint8_t LouKeReadPciUint8(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset){
    UINT32 Tmp = 0;
    if(PDEV->EcamDevice){
        PDEV->EcamOperations.PcieReadEcam(PDEV, Offset, sizeof(UINT8), &Tmp);
        return (UINT8)Tmp;
        if(PDEV->Group)return UINT8_MAX;
    }
    return pciConfigReadByte(PDEV->Group, PDEV->bus,PDEV->slot,PDEV->func, Offset);
}

LOUDDK_API_ENTRY uint16_t LouKeReadPciUint16(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset){
    UINT32 Tmp = 0;
    if(PDEV->EcamDevice){
        PDEV->EcamOperations.PcieReadEcam(PDEV, Offset, sizeof(UINT16), &Tmp);
        return (UINT16)Tmp;
        if(PDEV->Group)return UINT16_MAX;
    }
    return pciConfigReadWord(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, Offset);
}

LOUDDK_API_ENTRY uint32_t LouKeReadPciUint32(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset){
    UINT32 Tmp = 0;
    if(PDEV->EcamDevice){
        PDEV->EcamOperations.PcieReadEcam(PDEV, Offset, sizeof(UINT16), &Tmp);
        return (UINT32)Tmp;
        if(PDEV->Group)return UINT32_MAX;
    }
    return pci_read(PDEV->Group, PDEV->bus,PDEV->slot,PDEV->func, Offset);
}


LOUDDK_API_ENTRY void LouKeWritePciUint8(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint8_t Value){
    if(PDEV->EcamDevice){
        PDEV->EcamOperations.PcieWriteEcam(PDEV, Offset, sizeof(UINT8), (UINT32)Value);
        if(PDEV->Group)return;
    }
    pciConfigWriteByte(PDEV->Group, PDEV->bus,PDEV->slot,PDEV->func,Offset,Value);
}

LOUDDK_API_ENTRY void LouKeWritePciUint16(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint16_t Value){
    if(PDEV->EcamDevice){
        PDEV->EcamOperations.PcieWriteEcam(PDEV, Offset, sizeof(UINT16), (UINT32)Value);
        if(PDEV->Group)return;
    }
    pciConfigWriteWord(PDEV->Group, PDEV->bus, PDEV->slot,PDEV->func,Offset,Value);
}

LOUDDK_API_ENTRY void LouKeWritePciUint32(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint32_t Value){
    if(PDEV->EcamDevice){
        PDEV->EcamOperations.PcieWriteEcam(PDEV, Offset, sizeof(UINT32), (UINT32)Value);
        if(PDEV->Group)return;
    }
    write_pci(PDEV->Group, PDEV->bus,PDEV->slot,PDEV->func, Offset, Value);
}


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
void LouKeReleasePciDriverPath(string Path);
string LouKeAcquirePciDriverPath(PPCI_COMMON_CONFIG Config);
LOUDDK_API_ENTRY
void ScanTheRestOfHarware(){
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
        PPCI_DEVICE_OBJECT PDEV = SecondWaveDevices[i]->PDEV;
        if(PDEV->DeviceManaged){
            continue;
        }
        PPCI_COMMON_CONFIG PConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
        string DriverPath = 0x00;
        DriverPath = LouKeAcquirePciDriverPath(PConfig);
        if(!DriverPath){
            continue;
        }
        PDRIVER_OBJECT DriverObject;
        DRIVER_MODULE_ENTRY Driver = LouKeLoadKernelModule(DriverPath, (void**)&DriverObject, sizeof(DRIVER_OBJECT));
        if(!DriverObject->DriverExtension){
            DriverObject->DriverExtension = (PDRIVER_EXTENSION)LouKeMallocType(DRIVER_EXTENSION, KERNEL_GENERIC_MEMORY);
            Driver(DriverObject, (PUNICODE_STRING)DriverPath);
        }
        struct _DEVICE_OBJECT* PlatformDevice = (struct _DEVICE_OBJECT*)LouKeMallocType(DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
        if(DriverObject->DriverUsingLkdm){
            PlatformDevice->PDEV = PDEV;
            if(DriverObject->DeviceTable){ 
                PlatformDevice->DeviceID = LouKeGetLdmModuleDeviceID(PConfig, (PLOUSINE_PCI_DEVICE_TABLE)DriverObject->DeviceTable);
            }
        }
        DriverObject->DriverExtension->AddDevice(DriverObject, PlatformDevice);
        LouKeReleasePciDriverPath(DriverPath);
    }
}

KERNEL_IMPORT
bool LouKeSeachPreLoadedSystemModules(PPCI_DEVICE_OBJECT PDEV);

bool IsAtaController(PPCI_DEVICE_OBJECT PDEV);
void InitializeAtaDevice();
bool IsAhciController(PPCI_DEVICE_OBJECT PDEV);
LOUSTATUS InitializeStartupAhciImplementation(PPCI_DEVICE_OBJECT PDEV);

LOUDDK_API_ENTRY
void LouKeSantyCheckPciDevices(){

    PCI_COMMON_CONFIG Config;
    LouKeInitializePciCommonPacketAnyType(&Config);

    UINT16 Members = LouKeGetPciCountByType(&Config);

    if(!Members){
        for(size_t i = 0; i < 255; i++){
            checkBus(0, i);
        }
    }

}
