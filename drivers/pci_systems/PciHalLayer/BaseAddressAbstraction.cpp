//Copyright GPL-2 Tyler Grenier (2024 - 2026)
#include <LouDDK.h>

#include <Hal.h>

LOUAPI void LouKePciDbgPrint(char* format, ...);

#define BUS PDEV->bus
#define SLOT PDEV->slot
#define FUNCTION PDEV->func

static uint64_t IoMemEnd = 0;

LOUAPI uint64_t GetIoMemEnd(){
    return IoMemEnd;
}

LOUAPI
uint16_t LouKeCreatIoPort(
    uint16_t PortSize
);

uint32_t LouKeReadBarValue(PPCI_DEVICE_OBJECT PDEV, uint8_t BarNumber);
void LouKeWriteBarValue(PPCI_DEVICE_OBJECT PDEV, uint8_t BarNumber, uint32_t Value);

LOUAPI void GetPciConfiguration(ULONG Group, ULONG SystemIoBusNumber,ULONG SlotNumber,ULONG Function,PPCI_COMMON_CONFIG ConfigBuffer){
    ConfigBuffer->Header.VendorID = pciConfigReadWord( Group,SystemIoBusNumber, SlotNumber, Function, 0x00);
    ConfigBuffer->Header.DeviceID = pciConfigReadWord( Group,SystemIoBusNumber, SlotNumber, Function, 0x02);
    ConfigBuffer->Header.Command = pciConfigReadWord( Group,SystemIoBusNumber, SlotNumber, Function, 0x04);
    ConfigBuffer->Header.Status = pciConfigReadWord( Group,SystemIoBusNumber, SlotNumber, Function, 0x06);

    ConfigBuffer->Header.RevisionID = pciConfigReadByte(Group ,SystemIoBusNumber, SlotNumber, Function, 0x08);
    ConfigBuffer->Header.ProgIf = pciConfigReadByte(Group ,SystemIoBusNumber, SlotNumber, Function, 0x09);
    ConfigBuffer->Header.SubClass = pciConfigReadByte(Group,SystemIoBusNumber, SlotNumber, Function, 0x0A);
    ConfigBuffer->Header.BaseClass = pciConfigReadByte(Group ,SystemIoBusNumber, SlotNumber, Function, 0x0B);
    ConfigBuffer->Header.CacheLineSize = pciConfigReadByte(Group ,SystemIoBusNumber, SlotNumber, Function, 0x0C);
    ConfigBuffer->Header.LatencyTimer = pciConfigReadByte(Group ,SystemIoBusNumber, SlotNumber, Function, 0x0D);
    ConfigBuffer->Header.HeaderType = pciConfigReadByte(Group ,SystemIoBusNumber, SlotNumber, Function, 0x0E);
    ConfigBuffer->Header.BIST = pciConfigReadByte(Group ,SystemIoBusNumber, SlotNumber, Function, 0x0F);

    if(ConfigBuffer->Header.HeaderType == 0x00){
        ConfigBuffer->Header.u.type0.BaseAddresses[0] = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x10);
        ConfigBuffer->Header.u.type0.BaseAddresses[1] = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x14);
        ConfigBuffer->Header.u.type0.BaseAddresses[2] = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x18);
        ConfigBuffer->Header.u.type0.BaseAddresses[3] = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x1C);
        ConfigBuffer->Header.u.type0.BaseAddresses[4] = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x20);
        ConfigBuffer->Header.u.type0.BaseAddresses[5] = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x24);

        ConfigBuffer->Header.u.type0.CIS = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x28);
        ConfigBuffer->Header.u.type0.SubVendorID = pciConfigReadWord(Group, SystemIoBusNumber, SlotNumber, Function, 0x2C);
        ConfigBuffer->Header.u.type0.SubSystemID = pciConfigReadWord(Group, SystemIoBusNumber, SlotNumber, Function, 0x2E);
        ConfigBuffer->Header.u.type0.ROMBaseAddress = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x30);
            
        ConfigBuffer->Header.u.type0.CapabilitiesPtr = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x34);            
        ConfigBuffer->Header.u.type0.InterruptLine = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, 0, 0x3C);
        ConfigBuffer->Header.u.type0.InterruptPin = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x3D);
        ConfigBuffer->Header.u.type0.MinimumGrant = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x3E);
        ConfigBuffer->Header.u.type0.MaximumLatency = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x3F);
    }
    else if(ConfigBuffer->Header.HeaderType == 0x01){
        ConfigBuffer->Header.u.type1.BaseAddresses[0] = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x10);
        ConfigBuffer->Header.u.type1.BaseAddresses[1] = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x14);

        ConfigBuffer->Header.u.type1.PrimaryBus = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x18);
        ConfigBuffer->Header.u.type1.SecondaryBus = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x19);
        ConfigBuffer->Header.u.type1.SubordinateBus = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x1A);
        ConfigBuffer->Header.u.type1.SecondaryLatency = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x1B);

        ConfigBuffer->Header.u.type1.IOBase = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x1C);
        ConfigBuffer->Header.u.type1.IOLimit = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x1D);

        ConfigBuffer->Header.u.type1.SecondaryStatus = pciConfigReadWord(Group, SystemIoBusNumber, SlotNumber, Function, 0x1E);
        ConfigBuffer->Header.u.type1.MemoryBase = pciConfigReadWord(Group, SystemIoBusNumber, SlotNumber, Function, 0x20);
        ConfigBuffer->Header.u.type1.MemoryLimit = pciConfigReadWord(Group, SystemIoBusNumber, SlotNumber, Function, 0x22);
        ConfigBuffer->Header.u.type1.PrefetchBase = pciConfigReadWord(Group, SystemIoBusNumber, SlotNumber, Function, 0x24);
        ConfigBuffer->Header.u.type1.PrefetchLimit = pciConfigReadWord(Group, SystemIoBusNumber, SlotNumber, Function, 0x26);
          
        ConfigBuffer->Header.u.type1.PrefetchBaseUpper32 = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x28);
        ConfigBuffer->Header.u.type1.PrefetchLimitUpper32 = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x2C);

        ConfigBuffer->Header.u.type1.IOBaseUpper16 = pciConfigReadWord(Group, SystemIoBusNumber, SlotNumber,Function, 0x30);
        ConfigBuffer->Header.u.type1.IOLimitUpper16 = pciConfigReadWord(Group, SystemIoBusNumber, SlotNumber, Function, 0x32);

        ConfigBuffer->Header.u.type1.CapabilitiesPtr = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x34);

        ConfigBuffer->Header.u.type1.ROMBaseAddress = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x38);

        ConfigBuffer->Header.u.type1.InterruptLine = pciConfigReadByte(Group,SystemIoBusNumber, SlotNumber, Function, 0x3C);
        ConfigBuffer->Header.u.type1.InterruptPin = pciConfigReadByte(Group, SystemIoBusNumber, SlotNumber, Function, 0x3D);

        ConfigBuffer->Header.u.type1.BridgeControl = pciConfigReadWord(Group, SystemIoBusNumber, SlotNumber, Function, 0x3E);

    }
    else if(ConfigBuffer->Header.HeaderType == 0x02){
        ConfigBuffer->Header.u.type2.SocketRegistersBaseAddress = pci_read(Group, SystemIoBusNumber, SlotNumber, Function, 0x10);

        //TODO: Finish this            

    }
}

LOUAPI void LouKeHalGetPciConfiguration(PPCI_DEVICE_OBJECT PDEV, PPCI_COMMON_CONFIG Config){
    GetPciConfiguration(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, Config);
}

static spinlock_t Lock;

DRIVER_IMPORT 
LOUSTATUS PciHalRegisterPciDevice(
    PPCI_DEVICE_OBJECT PDEV,
    string RegistryEntry,
    string DeviceManagerString
);

void InitializeBARHalLayer(){
    LouKeCreateFastObjectClass("PCICONFIG", 256, sizeof(PCI_COMMON_CONFIG), GET_ALIGNMENT(PCI_COMMON_CONFIG), 0 , KERNEL_GENERIC_MEMORY);
}

void LouKeHalRegisterPciDevice(
    PPCI_DEVICE_OBJECT PDEV
){
    LouKePciDbgPrint("PCI BUS:%h :: SLOT:%h :: FUNC:%h\n", PDEV->bus, PDEV->slot, PDEV->func);

    UNUSED PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)LouKeAllocateFastObject("PCICONFIG");
    if(!Config){
        Config = (PPCI_COMMON_CONFIG)LouKeMallocType(PCI_COMMON_CONFIG, KERNEL_GENERIC_MEMORY);
    } 
    UNUSED uint32_t BarSize = 0x00;
    UNUSED uint8_t Flags;
    UNUSED LouKIRQL OldIrql;

    //interrupts are an issue for this process turn them off and spinlock
    LouKeAcquireSpinLock(&Lock, &OldIrql);

    //get the pci configurations for the device
    GetPciConfiguration(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, Config);

    PDEV->CommonConfig = (void*)Config;

    if(!(Config->Header.HeaderType & 0x7F)){
        LouKePciDbgPrint("General PCI Device Detected\n");
        for(size_t i = 0 ; i < 6; i++){
            if(!(Config->Header.u.type0.BaseAddresses[i] & 1)){
                if((((Config->Header.u.type0.BaseAddresses[i] >> 1) & 0x03) == 0x02) && (i != 5)){
                    //handle 64 bit
                    Config->BarFlags[i] = Config->Header.u.type0.BaseAddresses[i] & 0x0F;
                    Config->RawBarBase[i] = (Config->Header.u.type0.BaseAddresses[i] & ~(0xF)) | ((uint64_t)Config->Header.u.type0.BaseAddresses[i + 1] << 32);
                    Config->BarSize[i] = 0x00;
                    LouKePciDbgPrint("64 Bit MMIO Base:%h\n", Config->RawBarBase[i]);
                    i++;
                }else if(((Config->Header.u.type0.BaseAddresses[i] >> 1) & 0x03) == 0x02){
                    LouKePciDbgPrint("WARNING:64 Bit BAR Is Not Allowed On Bar 5\n");
                }
                else if(Config->Header.u.type0.BaseAddresses[i] & ~(0xF)){
                    //handle 16 bit and 32 bit NOTE:remapping is done through paging
                    Config->BarFlags[i] = Config->Header.u.type0.BaseAddresses[i] & 0x0F;
                    Config->RawBarBase[i] = Config->Header.u.type0.BaseAddresses[i] & ~(0xF);
                    Config->BarSize[i] = 0x00;
                    if(!((Config->Header.u.type0.BaseAddresses[i] >> 1) & 0x03)){
                        LouKePciDbgPrint("32 Bit MMIO Base:%h\n", Config->RawBarBase[i]);
                    }else if(((Config->Header.u.type0.BaseAddresses[i] >> 1) & 0x03) == 0x01){
                        LouKePciDbgPrint("16 Bit MMIO Base:%h\n", Config->RawBarBase[i]);

                    }else {
                        LouKePciDbgPrint("WARNING:Unkonwn BAR Type MMIO Base:%h\n", Config->RawBarBase[i]);
                    }
                }else{
                    LouKePciDbgPrint("WARNING:Unused BAR:%d\n", i);
                }    
            }else{
                Config->RawBarBase[i] = Config->Header.u.type0.BaseAddresses[i] & ~(0x3);
                Config->BarFlags[i] = Config->Header.u.type0.BaseAddresses[i] & 0x3;
                LouKePciDbgPrint("IO Base:%h\n", Config->RawBarBase[i]);
                Config->BarSize[i] = 0x00;
            }
        }
    }else{
        LouKePciDbgPrint("WARNING:PCI Header Type Unkown\n");
    }

    PciHalRegisterPciDevice(
        PDEV,
        0x00,
        0x00
    );

    LouKeReleaseSpinLock(&Lock, &OldIrql);
}

KERNEL_EXPORT
LOUSTATUS
LouKeHalMapPciResourceEx(
    PPCI_DEVICE_OBJECT  PDEV, 
    uint8_t             Bar, 
    UINT64              Size,
    UINT64              PageFlags
){
    PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)PDEV->CommonConfig; 
    if(Config->BarSize[Bar] || Config->BarBase[Bar] || (Config->BarFlags[Bar] & 0x01)){
        return STATUS_UNSUCCESSFUL;
    }
    UINT64  RoundBase = ROUND_DOWN64(Config->RawBarBase[Bar], KILOBYTE_PAGE);
    UINT64  RoundOffset = Config->RawBarBase[Bar] - RoundBase;
    UINT64  RoundSize = ROUND_UP64(Size + RoundOffset, KILOBYTE_PAGE);
    PVOID NewVAddress = LouVMallocEx(RoundSize, KILOBYTE_PAGE);
    if(!NewVAddress){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    LouKeMapContinuousMemoryBlock(RoundBase, (UINT64)NewVAddress, RoundSize, PageFlags);
    Config->BarBase[Bar] = (UINT64)NewVAddress + RoundOffset;
    Config->BarSize[Bar] = Size;
    
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS
LouKeHalMapPciResource(
    PPCI_DEVICE_OBJECT  PDEV,
    uint8_t             Bar,
    UINT64              PageFlags
){
    UINT64 TotalBarSize = 0x00;    
    PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)PDEV->CommonConfig; 
    if(!Config->RawBarBase[Bar]){
        LouKePciDbgPrint("WARNING:Unconfigured Or 64 Bit BAR\n");
        return STATUS_UNSUCCESSFUL;
    }
    if(!(Config->Header.HeaderType & 0x7F)){
        if(!(Config->Header.u.type0.BaseAddresses[Bar] & 1)){
            if((((Config->Header.u.type0.BaseAddresses[Bar] >> 1) & 0x03) == 0x02) && (Bar != 5)){
                //handle 64 bit
                UINT32 Low = Config->Header.u.type0.BaseAddresses[Bar];
                UINT32 High = Config->Header.u.type0.BaseAddresses[Bar + 1];
                UINT32 SzLow;
                UINT32 SzHigh;
                LouKeWritePciUint32(PDEV, 0x10 + Bar * 4, 0xFFFFFFFF);
                LouKeWritePciUint32(PDEV, 0x10 + (Bar + 1) * 4, 0xFFFFFFFF);

                SzLow = LouKeReadPciUint32(PDEV, 0x10 + Bar * 4);
                SzHigh = LouKeReadPciUint32(PDEV, 0x10 + (Bar + 1) * 4);

                LouKeWritePciUint32(PDEV, 0x10 + Bar * 4, Low);
                LouKeWritePciUint32(PDEV, 0x10 + (Bar + 1) * 4, High);

                TotalBarSize = ((UINT64)SzHigh << 32) | (SzLow & 0xFFFFFFF0);
                TotalBarSize = (~TotalBarSize + 1);
            }else if(((Config->Header.u.type0.BaseAddresses[Bar] >> 1) & 0x03) == 0x02){
                LouKePciDbgPrint("WARNING:64 Bit BAR Is Not Allowed On Bar 5\n");
                return STATUS_UNSUCCESSFUL;
            }
            else if(Config->Header.u.type0.BaseAddresses[Bar] & ~(0xF)){
                //handle 16 bit and 32 bit NOTE:remapping is done through paging
                if(!((Config->Header.u.type0.BaseAddresses[Bar] >> 1) & 0x03)){
                    LouKeWritePciUint32(PDEV, 0x10 + Bar * 4, 0xFFFFFFFF);
                    TotalBarSize = LouKeReadPciUint32(PDEV, 0x10 + Bar * 4);
                    LouKeWritePciUint32(PDEV, 0x10 + Bar * 4, Config->Header.u.type0.BaseAddresses[Bar]);
                    TotalBarSize &= 0xFFFFFFF0;
                    TotalBarSize = (~TotalBarSize + 1) & 0xFFFFFFFF;
                }else if(((Config->Header.u.type0.BaseAddresses[Bar] >> 1) & 0x03) == 0x01){
                    LouKeWritePciUint32(PDEV, 0x10 + Bar * 4, 0xFFFFFFFF);
                    TotalBarSize = LouKeReadPciUint32(PDEV, 0x10 + Bar * 4);
                    LouKeWritePciUint32(PDEV, 0x10 + Bar * 4, Config->Header.u.type0.BaseAddresses[Bar]);
                    TotalBarSize &= 0xFFF0;
                    TotalBarSize = (~TotalBarSize + 1) & 0xFFFF;
                }else {
                    LouKePciDbgPrint("WARNING:Unkonwn BAR Type MMIO Base:%d\n", Bar);
                    return STATUS_UNSUCCESSFUL;
                }
            }else{
                LouKePciDbgPrint("WARNING:Unused BAR:%d\n", Bar);
                return STATUS_UNSUCCESSFUL;
            }    
        }else{
            return STATUS_UNSUCCESSFUL;
        }
    }else{
        LouKePciDbgPrint("WARNING:PCI Header Type Unkown\n");
    }
    return LouKeHalMapPciResourceEx(PDEV, Bar, TotalBarSize, PageFlags);
}   

void* LouKeHalPnpInitializeBaseRegister(
    PPCI_DEVICE_OBJECT PDEV,
    uint8_t BarNum
){
    //LouKeWriteBarValue(PDEV, BarNum, 0xFFFFFFFF);
    uint32_t BarValue = LouKeReadBarValue(PDEV, BarNum);

    LouKePciDbgPrint("Bar Value Is:%h\n", BarValue);

    while(1);
    return 0x00;
}

LOUAPI uint64_t GetAllocationBlockSize(uint64_t Address);

KERNEL_EXPORT 
size_t 
LouKeHalGetPciBaseAddressSize(
    PPCI_DEVICE_OBJECT PDEV,
    uint8_t BarNum  
){
    return (size_t)(((PPCI_COMMON_CONFIG)PDEV->CommonConfig)->BarSize[BarNum]);
}

KERNEL_EXPORT 
void* 
LouKePciGetIoRegion(
    PPCI_DEVICE_OBJECT PDEV, 
    uint8_t BarNumber,
    size_t BarOffset
){
    return (void*)(((PPCI_COMMON_CONFIG)PDEV->CommonConfig)->BarBase[BarNumber] + BarOffset);
}
