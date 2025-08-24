#include <LouDDK.h>
#include <NtAPI.h>
#include <Hal.h>

#define BUS PDEV->bus
#define SLOT PDEV->slot
#define FUNCTION PDEV->func

static uint64_t IoMemEnd = 0;

KERNEL_IMPORT uint64_t GetIoMemEnd(){
    return IoMemEnd;
}

KERNEL_IMPORT
uint16_t LouKeCreatIoPort(
    uint16_t PortSize
);

uint32_t LouKeReadBarValue(PPCI_DEVICE_OBJECT PDEV, uint8_t BarNumber);
void LouKeWriteBarValue(PPCI_DEVICE_OBJECT PDEV, uint8_t BarNumber, uint32_t Value);

KERNEL_IMPORT void GetPciConfiguration(ULONG Group, ULONG SystemIoBusNumber,ULONG SlotNumber,ULONG Function,PPCI_COMMON_CONFIG ConfigBuffer){
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

KERNEL_IMPORT void LouKeHalGetPciConfiguration(PPCI_DEVICE_OBJECT PDEV, PPCI_COMMON_CONFIG Config){
    GetPciConfiguration(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, Config);
}

static spinlock_t Lock;

KERNEL_IMPORT
LOUSTATUS RegisterPciDeviceToDeviceManager(
    PPCI_DEVICE_OBJECT PDEV,
    string RegistryEntry,
    string DeviceManagerString
);

static POOL PciConfigPool = 0x00;

void InitializeBARHalLayer(){
    PciConfigPool = LouKeCreateFixedPool(0xFFFF, sizeof(PCI_COMMON_CONFIG), GET_ALIGNMENT(PCI_COMMON_CONFIG), "PCIConfig Pool", 0 , KERNEL_GENERIC_MEMORY);
}

void LouKeHalRegisterPciDevice(
    PPCI_DEVICE_OBJECT PDEV
){

    LouPrint("PCI BUS:%h :: SLOT:%h :: FUNC:%h\n", PDEV->bus, PDEV->slot, PDEV->func);

    UNUSED PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)LouKeMallocFromFixedPool(PciConfigPool);
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

    if(Config->Header.HeaderType == 0){

        for(uint8_t i = 0 ; i < 6; i++){

                Flags = Config->Header.u.type0.BaseAddresses[i] & 0x1;
                if(Flags == 0){
                    Flags = (Config->Header.u.type0.BaseAddresses[i] >> 1) & 0x03;
                    if(Flags == 0){
                        //32
                        if(Config->Header.u.type0.BaseAddresses[i] == 0x00){
                            continue;
                        }
                        LouPrint("Device Is 32 Bit MmIO\n");
                        Flags = (Config->Header.u.type0.BaseAddresses[i] >> 3) & 0x01;
                        if(Flags == 1){
                            LouPrint("Device Caheable\n");
                            LouKeWriteBarValue(PDEV, i , 0xFFFFFFFF);
                            BarSize = pci_read(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, BAR0_OFFSET + (4 * i)) & ~(0x0F);
                            BarSize = (~(BarSize & ~(0x0F))) + 1;
                            LouKeWriteBarValue(PDEV, i , Config->Header.u.type0.BaseAddresses[i]);
                            EnforceSystemMemoryMap(
                                Config->Header.u.type0.BaseAddresses[i] & ~(0xF),
                                BarSize
                            );
                            
                            Config->BarBase[i] = Config->Header.u.type0.BaseAddresses[i] & ~(0x0F);
                            Config->BarSize[i] = BarSize;
                            if(IoMemEnd < (Config->BarBase[i] + Config->BarSize[i])){
                                IoMemEnd = Config->BarBase[i] + Config->BarSize[i];
                            }
                            uint64_t Tmp = 0x00;
                            Tmp = (uint64_t)LouVMallocEx(Config->BarSize[i] , Config->BarBase[i]);
                            LouKeMapContinuousMemoryBlock(Config->BarBase[i], Tmp, ROUND_UP64(Config->BarSize[i], KILOBYTE_PAGE), KERNEL_DMA_MEMORY);
                            Config->BarBase[i] = Tmp;
                            
                        }
                        else{
                            LouPrint("Device Uncaheable\n");

                            LouKeWriteBarValue(PDEV, i , 0xFFFFFFFF);
                            BarSize = pci_read(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, BAR0_OFFSET + (4 * i)) & ~(0x0F);
                            BarSize = (~(BarSize & ~(0x0F))) + 1;
                            LouKeWriteBarValue(PDEV, i , Config->Header.u.type0.BaseAddresses[i]);
                            EnforceSystemMemoryMap(
                                Config->Header.u.type0.BaseAddresses[i] & ~(0x0F),
                                BarSize
                            );

                            Config->BarBase[i] = Config->Header.u.type0.BaseAddresses[i] & ~(0x0F);
                            Config->BarSize[i] = BarSize;
                            if(IoMemEnd < (Config->BarBase[i] + Config->BarSize[i])){
                                IoMemEnd = Config->BarBase[i] + Config->BarSize[i];
                            }
                            uint64_t Tmp = 0x00;
                            Tmp = (uint64_t)LouVMallocEx(Config->BarSize[i] , Config->BarBase[i]);
                            LouKeMapContinuousMemoryBlock(Config->BarBase[i], Tmp, ROUND_UP64(Config->BarSize[i], KILOBYTE_PAGE), KERNEL_DMA_MEMORY);
                            Config->BarBase[i] = Tmp;
                        }
                    }
                    else if(Flags == 1){
                        //16
                    }
                    else if(Flags == 2){
                        if(Config->Header.u.type0.BaseAddresses[i] == 0x00){
                            i++;
                            continue;
                        }
                        LouPrint("Device Is 64 Bit MmIO\n");
                        uint32_t BarLo = Config->Header.u.type0.BaseAddresses[i];
                        uint32_t BarHi = Config->Header.u.type0.BaseAddresses[i + 1];
                        uint64_t Bar64 = ((uint64_t)BarHi << 32) | (BarLo & ~(0xF));

                        LouKeWriteBarValue(PDEV, i, 0xFFFFFFFF);
                        LouKeWriteBarValue(PDEV, i + 1, 0xFFFFFFFF);
                        uint32_t SizeLo = pci_read(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, BAR0_OFFSET + (4 * i)) & ~(0xF);
                        uint32_t SizeHi = pci_read(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, BAR0_OFFSET + (4 * (i + 1)));
                        uint64_t Size64 = ((uint64_t)SizeHi << 32) | SizeLo;
                        Size64 = (~Size64) + 1;

                        LouKeWriteBarValue(PDEV, i, BarLo);
                        LouKeWriteBarValue(PDEV, i + 1, BarHi);

                        EnforceSystemMemoryMap(Bar64, Size64);

                        Config->BarSize[i] = Size64;

                        if (IoMemEnd < (Bar64 + Size64)) {
                            IoMemEnd = Bar64 + Size64;
                        }

                        uint64_t Tmp = (UINT64)LouVMallocEx(Size64, Bar64);
                        LouKeMapContinuousMemoryBlock(Bar64, Tmp, ROUND_UP64(Size64, KILOBYTE_PAGE), KERNEL_DMA_MEMORY);
                        Config->BarBase[i] = Tmp;

                        i++;
                }
            }
            else{
                //LouKeWriteBarValue(PDEV, i, 0xFFFFFFFF);
                //uint32_t BVal = LouKeReadBarValue(PDEV, i);
                //BarSize = (~(BVal & 0xFFFFFFFC)) + 1;  // Mask out the lower 2 bits and invert
                //LouKeWriteBarValue(PDEV, i, (LouKeCreatIoPort(BarSize) & 0xFFFFFFFC) | 0x1);

            }
        }
    }
    
    PDEV->CommonConfig = (void*)Config;

    RegisterPciDeviceToDeviceManager(
        PDEV,
        0x00,
        0x00
    );

    LouKeReleaseSpinLock(&Lock, &OldIrql);
}


void* LouKeHalPnpInitializeBaseRegister(
    PPCI_DEVICE_OBJECT PDEV,
    uint8_t BarNum
){
    //LouKeWriteBarValue(PDEV, BarNum, 0xFFFFFFFF);
    uint32_t BarValue = LouKeReadBarValue(PDEV, BarNum);

    LouPrint("Bar Value Is:%h\n", BarValue);

    while(1);
    return 0x00;
}

KERNEL_IMPORT uint64_t GetAllocationBlockSize(uint64_t Address);

KERNEL_IMPORT 
size_t LouKeHalGetPciBaseAddressSize(
    PPCI_COMMON_CONFIG PciConfig,
    uint8_t BarNum  
){
    return (size_t)PciConfig->BarSize[BarNum];
}

KERNEL_IMPORT 
void* LouKePciGetIoRegion(
    PPCI_DEVICE_OBJECT PDEV, 
    uint8_t BarNumber,
    size_t BarOffset
){
    return (void*)(((PPCI_COMMON_CONFIG)PDEV->CommonConfig)->BarBase[BarNumber] + BarOffset);
}

LOUDDK_API_ENTRY
SET_OPTIMIZATION(0) 
uint64_t 
LouKePciGetVirtualBarAddress(uint64_t PhyAddress){

    PCI_COMMON_CONFIG Config;
	Config.Header.VendorID = ANY_PCI_ID;
	Config.Header.DeviceID = ANY_PCI_ID;
	Config.Header.u.type0.SubVendorID = ANY_PCI_ID;
	Config.Header.u.type0.SubSystemID = ANY_PCI_ID;
	Config.Header.BaseClass = ANY_PCI_CLASS;
	Config.Header.SubClass = ANY_PCI_CLASS;
	Config.Header.ProgIf = ANY_PCI_CLASS;

	uint8_t NumberOfPciDevices = LouKeGetPciCountByType(&Config);
    uint64_t Result = 0x00;
    uint64_t TmpBarAddress = 0x00;
    uint64_t Flags;
	PPCI_DEVICE_GROUP* PciDevices = LouKeOpenPciDeviceGroup(&Config);
    for(uint8_t i = 0 ; i < NumberOfPciDevices; i++){
        PPCI_DEVICE_OBJECT PDEV = PciDevices[i]->PDEV;
        PPCI_COMMON_CONFIG TmpConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
        for(uint8_t j = 0 ; j < 6; j++){
            Flags = TmpConfig->Header.u.type0.BaseAddresses[j] & 0x1;
            if(Flags == 0){
                Flags = (TmpConfig->Header.u.type0.BaseAddresses[j] >> 1) & 0x03;
                if(Flags == 0){
                    if(TmpConfig->Header.u.type0.BaseAddresses[j] == 0x00){
                        continue;
                    }
                    TmpBarAddress = TmpConfig->Header.u.type0.BaseAddresses[j] & ~(0xF);
                    if(RangeInterferes(PhyAddress, 1, TmpBarAddress, TmpConfig->BarSize[j])){
                        Result = (PhyAddress - TmpBarAddress) + TmpConfig->BarBase[j];
                        break;
                    }
                }
                else if(Flags == 2){
                    if(TmpConfig->Header.u.type0.BaseAddresses[i] == 0x00){
                        i++;
                        continue;
                    }
                    uint32_t BarLo = TmpConfig->Header.u.type0.BaseAddresses[j];
                    uint32_t BarHi = TmpConfig->Header.u.type0.BaseAddresses[j + 1];
                    TmpBarAddress  = ((uint64_t)BarHi << 32) | (BarLo & ~(0xF));
                    if(RangeInterferes(PhyAddress, 1, TmpBarAddress, TmpConfig->BarSize[j])){
                        Result = (PhyAddress - TmpBarAddress) + TmpConfig->BarBase[j];
                        break;
                    }
                }
            }
        }
        if(Result){
            break;
        }
    }

    LouKeClosePciDeviceGroup(PciDevices);
    return Result;
}