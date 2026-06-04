#include "Pci.h"

static BOOLEAN PciDebugOn = false;
static PMCFG_TABLE McfgTable = 0x00;
static SIZE McfgEntryCount = 0;
static SIZE MaxGroups = 0;
static mutex_t EcamRemapsLock = {0};

typedef struct _PCIE_ECAM_REMAPS{
    ListHeader  Peers;
    UINT16      Group;
    UINT8       Bus;
    UINT8       Slot;
    UINT8       Function;
    UINT32*     Phy;
    UINT32*     Virt;
}PCIE_ECAM_REMAPS, * PPCIE_ECAM_REMAPS;

static ListHeader EcamRemapList = {0};

static UINT32* PciHalMapEcamDevice(
    UINT16  Group,
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function,
    UINT32* PhyAddress
){
    PPCIE_ECAM_REMAPS NewEcamRemap = LouKeMallocType(PCIE_ECAM_REMAPS, KERNEL_GENERIC_MEMORY);
    NewEcamRemap->Group = Group;
    NewEcamRemap->Bus = Bus;
    NewEcamRemap->Slot = Slot;
    NewEcamRemap->Function = Function;
    NewEcamRemap->Phy = PhyAddress;
    NewEcamRemap->Virt = LouVMallocEx(4096, KILOBYTE_PAGE);
    LouKeMapContinuousMemoryBlockKB((UINTPTR)PhyAddress, (UINTPTR)NewEcamRemap->Virt, 4096, KERNEL_DMA_MEMORY);
    MutexLock(&EcamRemapsLock);
    LouKeListAddTail(&NewEcamRemap->Peers, &EcamRemapList);
    MutexUnlock(&EcamRemapsLock);
    return NewEcamRemap->Virt;
}

static void PciHalUnMapEcamDevice(PVOID VirtualAddress){
    PPCIE_ECAM_REMAPS TmpRemamp;
    MutexLock(&EcamRemapsLock);
    ForEachListEntry(TmpRemamp, &EcamRemapList, Peers){
        if(TmpRemamp->Virt == VirtualAddress){
            LouKeListDeleteItem(&TmpRemamp->Peers);
            LouKeFree(TmpRemamp);
            LouKeUnMapContinuousMemoryBlock((UINTPTR)VirtualAddress, 4096);
            LouFree(VirtualAddress);
            break;
        }
    }
    MutexUnlock(&EcamRemapsLock);
}

void PciHalPciDbgPrint(char* format, ...){
    if(PciDebugOn){
        va_list args;
        va_start(args, format);
        LouPrintEx(format, args);
        va_end(args);
    }
}

static BOOLEAN PcieGroupExists(UINT16 Group){
    if(!Group){
        return true;
    }
    else if(!McfgTable){
        return false;
    }
    for(SIZE i = 0 ; i < McfgEntryCount; i++){
        if(RangeInterferes(
            Group, 1, 
            McfgTable->TableEntries[i].Group,
            1
        )){
            return true;
        }
    }
    return false;
}

static SIZE PcieGetMaxGroups(){
    SIZE Groups = 1;
    for(SIZE i = 0 ; i < McfgEntryCount; i++){
        Groups = MAX(Groups, McfgTable->TableEntries[i].Group + 1);
    }
    return Groups;
}

UINT32* PciHalGetNativePciPhysicalAddress(
    UINT16  Group, 
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    for(SIZE i = 0 ; i < McfgEntryCount; i++){
        if(
            (
                RangeInterferes(
                    Group, 1, 
                    McfgTable->TableEntries[i].Group,
                    1
                )
            ) && (
                RangeInterferes(
                    Bus, 1,
                    McfgTable->TableEntries[i].StartBus,
                    (McfgTable->TableEntries[i].EndBus - McfgTable->TableEntries[i].StartBus) + 1
                )
            ) 
        ){
            Bus -= McfgTable->TableEntries[i].StartBus;
            return (UINT32*)((UINTPTR)McfgTable->TableEntries[i].ConfigurationBaseAddress + (((UINTPTR)Bus) << 20 | (UINTPTR)Slot << 15 | (UINTPTR)Function << 12));
        }
    }
    return 0x00;
}

void PciHalLegacyFallbackCheckSlot(    
    UINT8   Bus,
    UINT8   Slot
){
    UINT16 VendorID = LegacyPciGetVendorIdEx(Bus, Slot, 0);
    UINT8 HeaderType = LegacyPciGetHeaderTypeEx(Bus, Slot, 0);

    if(VendorID == 0xFFFF){
        return;
    }
    //LouPrint("VendorID:%h\n", (UINT64)VendorID);

    PPCI_DEVICE_OBJECT NewPciDevice = (PPCI_DEVICE_OBJECT)LouKeAllocateFastObject("PDEV");
    NewPciDevice->Group = 0;
    NewPciDevice->Bus = Bus;
    NewPciDevice->Slot = Slot;
    NewPciDevice->Function = 0;

    //LouPrint("HeaderType:%h\n", (UINT64)HeaderType);

    NewPciDevice->Dispatch = PciLegacyDispatch;

    PciHalRegisterPciDevice(NewPciDevice);

    if((HeaderType & 0x03) == 1){
        PciHalInitializePciBridge(NewPciDevice);
    }

    if(HeaderType & (1 << 7) && (HeaderType != 0xFF)){
        for(SIZE i = 1; i < 8; i++){
            VendorID = LegacyPciGetVendorIdEx(Bus, Slot, i);
            HeaderType = LegacyPciGetHeaderTypeEx(Bus, Slot, i);

            if(VendorID == 0xFFFF){
                continue;
            }

            //LouPrint("VendorID:%h\n", (UINT64)VendorID);

            NewPciDevice = (PPCI_DEVICE_OBJECT)LouKeAllocateFastObject("PDEV");
            
            NewPciDevice->Group = 0;
            NewPciDevice->Bus = Bus;
            NewPciDevice->Slot = Slot;
            NewPciDevice->Function = i;

            //LouPrint("HeaderType:%h\n", (UINT64)HeaderType);
            
            NewPciDevice->Dispatch = PciLegacyDispatch;
            
            PciHalRegisterPciDevice(NewPciDevice);
            
            if((HeaderType & 0x03) == 1){
                PciHalInitializePciBridge(NewPciDevice);
            }
        }
    }
}

BOOLEAN PciHalNativeCheckSlot(    
    UINT32* EcamDeviceBase,
    UINT16  Group,
    UINT8   Bus,
    UINT8   Slot
){
    UINT16 VendorID = NativePciGetVendorIdEx(EcamDeviceBase);
    UINT8 HeaderType = NativePciGetHeaderTypeEx(EcamDeviceBase);
    
    if(VendorID == 0xFFFF){
        return false;
    }

    //LouPrint("VendorID:%h\n", (UINT64)VendorID);

    PPCI_DEVICE_OBJECT NewPciDevice = (PPCI_DEVICE_OBJECT)LouKeAllocateFastObject("PDEV");
    NewPciDevice->EcamDeviceBase = EcamDeviceBase;
    NewPciDevice->Group = Group;
    NewPciDevice->Bus = Bus;
    NewPciDevice->Slot = Slot;
    NewPciDevice->Function = 0;

    //LouPrint("HeaderType:%h\n", (UINT64)HeaderType);

    NewPciDevice->Dispatch = PciNativeDispatch;

    //LouPrint("HeaderType:%h\n", (UINT64)HeaderType);

    PciHalRegisterPciDevice(NewPciDevice);

    if((HeaderType & 0x03) == 1){
        PciHalInitializePciBridge(NewPciDevice);
    }

    if(HeaderType & (1 << 7) && (HeaderType != 0xFF)){
        for(SIZE i = 1; i < 8; i++){
            EcamDeviceBase = PciHalGetNativePciPhysicalAddress(
                Group,
                Bus,
                Slot,
                i
            );
            if(!EcamDeviceBase){
                continue;
            }
            //PciHalPciDbgPrint("PCI.SYS:Group:%d::Bus:%d::Slot:%d:Ecam:%h\n", (UINT64)Group, (UINT64)Bus, (UINT64)i, (UINT64)EcamDeviceBase);
            EcamDeviceBase = PciHalMapEcamDevice(Group, Bus, i, 0, EcamDeviceBase);
            //PciHalPciDbgPrint("PCI.SYS:Group:%d::Bus:%d::Slot:%d:Ecam:%h\n", (UINT64)Group, (UINT64)Bus, (UINT64)i, (UINT64)EcamDeviceBase);

            VendorID = NativePciGetVendorIdEx(EcamDeviceBase);
            HeaderType = NativePciGetHeaderTypeEx(EcamDeviceBase);

            if(VendorID == 0xFFFF){
                PciHalUnMapEcamDevice(EcamDeviceBase);
                continue;
            }

            NewPciDevice = (PPCI_DEVICE_OBJECT)LouKeAllocateFastObject("PDEV");
            NewPciDevice->EcamDeviceBase = EcamDeviceBase;
            NewPciDevice->Group = 0;
            NewPciDevice->Bus = Bus;
            NewPciDevice->Slot = Slot;
            NewPciDevice->Function = i;

            //LouPrint("HeaderType:%h\n", (UINT64)HeaderType);
            
            NewPciDevice->Dispatch = PciNativeDispatch;
            
            PciHalRegisterPciDevice(NewPciDevice);

            if((HeaderType & 0x03) == 1){
                PciHalInitializePciBridge(NewPciDevice);
            }
        }
    }
    return true;
}

void PciHalInitializePciBus(
    UINT16  Group,
    UINT8   Bus
){
    PciHalPciDbgPrint("PCI.SYS:Scaning Group:%d::Bus:%d\n", (UINT64)Group, (UINT64)Bus);
    for(SIZE i = 0 ; i < 32; i++){
        BOOLEAN Success = false;
        UINT32* EcamDeviceBase = PciHalGetNativePciPhysicalAddress(
            Group,
            Bus,
            i,
            0
        );
        if(EcamDeviceBase){
            //PciHalPciDbgPrint("PCI.SYS:Group:%d::Bus:%d::Slot:%d:Ecam:%h\n", (UINT64)Group, (UINT64)Bus, (UINT64)i, (UINT64)EcamDeviceBase);
            EcamDeviceBase = PciHalMapEcamDevice(Group, Bus, i, 0, EcamDeviceBase);
            //PciHalPciDbgPrint("PCI.SYS:Group:%d::Bus:%d::Slot:%d:Ecam:%h\n", (UINT64)Group, (UINT64)Bus, (UINT64)i, (UINT64)EcamDeviceBase);
            Success = PciHalNativeCheckSlot(
                EcamDeviceBase,
                Group,
                Bus,
                i
            );
        }
        if((!Group) && (!Success)){
            PciHalLegacyFallbackCheckSlot(
                Bus,
                i
            );
        }
    }
}

void PciHalInitializePciBridge(
    PPCI_DEVICE_OBJECT PDEV
){
    PciHalInitializePciBus(
        PDEV->Group,
        PciHalBridgeDeviceGetSecondaryBusNumber(PDEV)
    );
}

LOUSTATUS PciEntry(){
    HANDLE PciDebugKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\DEBUG\\PCI_DEBUG", 0x00);
    BYTE DbgValue = 0;
    LouKeReadRegistryByteValue(PciDebugKey, &DbgValue);
    PciDebugOn = DbgValue ? true : false;

    PciHalPciDbgPrint("PCI.SYS:PciEntry()\n");

    PciHalPciDbgPrint("PCI.SYS:Initializing PCI Objects\n");

    LouKeCreateFastObjectClass("PDEV", 256, sizeof(PCI_DEVICE_OBJECT), GET_ALIGNMENT(PCI_DEVICE_OBJECT), 0, KERNEL_GENERIC_MEMORY);
    LouKeCreateFastObjectClass("PCICONFIG", 256, sizeof(PCI_COMMON_CONFIG), GET_ALIGNMENT(PCI_COMMON_CONFIG), 0 , KERNEL_GENERIC_MEMORY);
    
    PciHalPciDbgPrint("PCI.SYS:Acquirng MCFG Table\n");

    McfgTable = (PMCFG_TABLE)LouKeAcquireAcpiTable(ACPI_SIG_MCFG);

    if(McfgTable){
        McfgEntryCount = LouKeGetMcfgCount((void*)McfgTable);
    }else{
        PciHalPciDbgPrint("PCI.SYS:WARNING No MCFG Table Detected On System\n");
    }

    PciHalPciDbgPrint("PCI.SYS:Getting Max Groups\n");
    
    MaxGroups = PcieGetMaxGroups();

    PciHalPciDbgPrint("PCI.SYS:Max Groups:%d\n", MaxGroups);


    PciHalPciDbgPrint("PCI.SYS:Scanning PCI Bus\n");

    
    for(SIZE i = 0 ; i < MaxGroups; i++){
        if(PcieGroupExists(i)){
            PciHalInitializePciBus(
                i,
                0
            );
        }
    }
    
    PciHalPciDbgPrint("PCI.SYS:PciEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}