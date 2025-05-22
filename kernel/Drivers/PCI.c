#include <LouAPI.h>

typedef struct _ACPI_MCFG_ALLOCATION{
    uint64_t    BaseAddress;
    uint16_t    PCISegmentGroupNumber;
    uint8_t     StartBusNumber;
    uint8_t     EndBusNumber;
    uint32_t    Reserved;
} ACPI_MCFG_ALLOCATION, * PACPI_MCFG_ALLOCATION;

UNUSED static uint16_t MaxGroupCount = 0;
UNUSED static PCIE_SYSTEM_MANAGER Psm = {0};
UNUSED static mutex_t PsmLock; 

uint16_t GetPciGroupCount(){
    return MaxGroupCount;
}

PPCIE_SYSTEM_MANAGER GetPcieGroupHandle(uint16_t GroupItem){
    PPCIE_SYSTEM_MANAGER Result = &Psm;
    for(uint16_t i = 0; i < GroupItem; i++){
        Result = (PPCIE_SYSTEM_MANAGER)Result->Neighbors.NextHeader;
    }
    return Result;
}

void AddPcieGroup(ACPI_MCFG_ALLOCATION* PciManagerData){

    PPCIE_SYSTEM_MANAGER TmpPsm = &Psm;
    for(size_t i = 0 ; i < MaxGroupCount; i++){
        if(!TmpPsm->Neighbors.NextHeader){
            //using LouMallocEx Because we arent in a stable position to LouKeMallocEx
            TmpPsm->Neighbors.NextHeader = (PListHeader)LouMallocEx(sizeof(PCIE_SYSTEM_MANAGER), GET_ALIGNMENT(PCIE_SYSTEM_MANAGER));
        }
        TmpPsm = (PPCIE_SYSTEM_MANAGER)TmpPsm->Neighbors.NextHeader;
    }
    TmpPsm->BaseAddress = PciManagerData->BaseAddress;
    TmpPsm->PCISegmentGroupNumber = PciManagerData->PCISegmentGroupNumber;
    TmpPsm->StartBusNumber = PciManagerData->StartBusNumber;
    TmpPsm->EndBusNumber = PciManagerData->EndBusNumber;
    
    LouPrint("BaseAddress:%h\n", TmpPsm->BaseAddress);
    LouPrint("PCISegmentGroupNumber:%h\n", TmpPsm->PCISegmentGroupNumber);
    LouPrint("StartBusNumber:%h\n", TmpPsm->StartBusNumber);
    LouPrint("EndBusNumber:%h\n", TmpPsm->EndBusNumber);
    //place Group on stack for heavy recursion
    uint16_t Group = TmpPsm->PCISegmentGroupNumber;
    //same with Mapping location
    uint64_t PcieMMIO = 0x00;
    MaxGroupCount++;

    for(uint8_t Bus = TmpPsm->StartBusNumber ; Bus <= TmpPsm->EndBusNumber; Bus++){
        for(uint8_t Slot = 0 ; Slot < 32; Slot++){
            for(uint8_t Function = 0 ; Function < 8; Function++){ 
                PcieMMIO = PcieConfigAddress(Group, Bus, Slot, Function, 0); 
                LouPrint("PcieMMIO:%h\n", PcieMMIO);
                if(!PcieMMIO){
                    //TODO: add to broken entries :: But Not a problem yet
                    continue;
                }
                //sanity map address
                LouMapAddress(PcieMMIO, PcieMMIO, KERNEL_PAGE_WRITE_UNCAHEABLE_PRESENT, KILOBYTE_PAGE);
            }
        }
    }
    while(1);
}

uint32_t pci_read(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset) {
    uint32_t address;
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

    volatile uint32_t* PcieReg = (volatile uint32_t*)PcieConfigAddress(Group, bus, slot, func, offset);;
    uint32_t Result;
    
    if((uintptr_t)PcieReg != ((uintptr_t)-1)){
        Result = *PcieReg;
        return Result;        
    }

    // Create the PCI configuration address
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
        (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));

    // Write the address to the PCI configuration address register
    outl(PCI_CONFIG_ADDRESS_PORT, address);
    // Read and return the data from the PCI configuration data register
    return inl(PCI_CONFIG_DATA_PORT);
}

void write_pci(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t function, uint32_t offset, uint32_t value) {
    
    
    volatile uint32_t* PcieReg = (volatile uint32_t*)PcieConfigAddress(Group, bus, slot, function, offset);;
    
    if((uintptr_t)PcieReg != ((uintptr_t)-1)){
        *PcieReg = value;
        return;
    }

    
    // Calculate the address based on bus, device, function, and offset
    uint32_t address = (1U << 31) | ((uint32_t)bus << 16) | ((uint32_t)slot << 11) | ((uint32_t)function << 8) | (offset & 0xFC);
    // Write to PCI configuration space
    outl(address, value);
}

uint16_t pciConfigReadWord(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset) {
    uint32_t address;
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint16_t tmp = 0;

    volatile uint16_t* PcieReg = (volatile uint16_t*)PcieConfigAddress(Group, bus, slot, func, offset);;
    uint16_t Result;
    
    if((uintptr_t)PcieReg != ((uintptr_t)-1)){
        Result = *PcieReg;
        return Result;        
    }

    // Create configuration address as per Figure 1
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
        (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));

    // Write out the address
    outl(0xCF8, address);
    // Read in the data
    // (offset & 2) * 8) = 0 will choose the first word of the 32-bit register
    tmp = (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
    return tmp;
}

void pciConfigWriteWord(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset, uint16_t value) {
    uint32_t address;
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

    volatile uint16_t* PcieReg = (volatile uint16_t*)PcieConfigAddress(Group, bus, slot, func, offset);;
    
    if((uintptr_t)PcieReg != ((uintptr_t)-1)){
        *PcieReg = value;
        return;        
    }

    // Create configuration address as per Figure 1
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
        (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));

    // Write out the address
    outl(0xCF8, address);

    // Read the current 32-bit value at the specified address
    uint32_t currentValue = inl(0xCFC);

    // Clear the bits corresponding to the 16-bit value we are about to write
    currentValue &= ~((uint32_t)0xFFFF << ((offset & 2) * 8));

    // Set the bits with the new 16-bit value
    currentValue |= (uint32_t)value << ((offset & 2) * 8);

    // Write the modified value back to the PCI configuration space
    outl(0xCFC, currentValue);
}



uint32_t pciConfigAddress(uint8_t bus, uint8_t device, uint8_t function, uint32_t reg) {
    // Construct the address for PCI configuration space access
    return (1U << 31) | (bus << 16) | (device << 11) | (function << 8) | (reg & 0xFC);
}

uintptr_t PcieConfigAddress(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function, uint32_t reg) {
    MutexLock(&PsmLock);
    PPCIE_SYSTEM_MANAGER TmpPsm = &Psm;
    for(size_t i = 0; i < MaxGroupCount; i++){
        if((TmpPsm->PCISegmentGroupNumber == Group) && (TmpPsm->StartBusNumber <= bus) && (TmpPsm->EndBusNumber >= bus)){
            uintptr_t BaseAddress = TmpPsm->BaseAddress;
            MutexUnlock(&PsmLock);
            if(BaseAddress == 0x00){
                return (uintptr_t)-1;        
            }
            return BaseAddress + ((((bus * 256) + (device * 8) + function) * 4096) + reg);
        }else if(TmpPsm->Neighbors.NextHeader){
            TmpPsm = (PPCIE_SYSTEM_MANAGER)TmpPsm->Neighbors.NextHeader;
        }
    }
    MutexUnlock(&PsmLock);
    return (uintptr_t)-1;
}

uint8_t pciConfigReadByte(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function, uint32_t reg) {
    
    volatile uint8_t* PcieReg = (volatile uint8_t*)PcieConfigAddress(Group, bus, device, function, reg);;
    uint8_t Result;
    
    if((uintptr_t)PcieReg != ((uintptr_t)-1)){
        Result = *PcieReg;
        return Result;        
    }
    
    // Calculate the address for PCI configuration space access
    uint32_t address = pciConfigAddress(bus, device, function, reg);

    // Write the address to the address port
    outl(PCI_CONFIG_ADDRESS_PORT, address);

    // Read and return the byte from the data port
    return inb(PCI_CONFIG_DATA_PORT + (reg & 3));
}

void pciConfigWriteByte(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function, uint32_t reg, uint8_t value) {
    
    volatile uint8_t* PcieReg = (volatile uint8_t*)PcieConfigAddress(Group, bus, device, function, reg);;
    
    if((uintptr_t)PcieReg != ((uintptr_t)-1)){
        *PcieReg = value;
        return;        
    }
    
    // Calculate the address for PCI configuration space access
    uint32_t address = pciConfigAddress(bus, device, function, reg);

    // Write the address to the address port
    outl(PCI_CONFIG_ADDRESS_PORT, address);

    // Read the current 32-bit value at the specified address
    uint32_t currentValue = inl(PCI_CONFIG_DATA_PORT);

    // Clear the bits corresponding to the byte we are about to write
    currentValue &= ~((uint32_t)0xFF << ((reg & 3) * 8));

    // Set the bits with the new byte value
    currentValue |= (uint32_t)value << ((reg & 3) * 8);

    // Write the modified value back to the PCI configuration space
    outl(PCI_CONFIG_DATA_PORT, currentValue);
}


uint8_t getBaseClass(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function) {
    // Offset 0xB in the PCI configuration space contains the base class
    return pciConfigReadByte(Group, bus, device, function, 0xB);
}

uint8_t getSubClass(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function) {
    // Offset 0xA in the PCI configuration space contains the subclass
    return pciConfigReadByte(Group, bus, device, function, 0xA);
}

uint8_t getSecondaryBus(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function) {
    // Offset 0x19 in the PCI configuration space contains the Secondary Bus Number
    return pciConfigReadByte(Group, bus, device, function, 0x19);
}


uint8_t getHeaderType(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function) {
    // Assuming pciConfigReadByte is a function to read a byte from PCI configuration space
    // You might need to replace it with the appropriate function from your hardware access library
    uint8_t headerType;

    if (function == 0) {
        // For function 0, directly read the header type from offset 0xE
        headerType = pciConfigReadByte(Group, bus, device, function, 0xE); // Offset 0xE contains header type
    }
    else {
        // For non-function 0, read the header type from offset 0x0E in the multi-function header
        headerType = pciConfigReadByte(Group, bus, device, 0, 0xE); // Offset 0xE contains header type
    }

    return headerType;
}

uint16_t PciGetVendorID(uint16_t Group, uint8_t bus, uint8_t slot) {
    UNUSED uint16_t vendor, device;
    /* Try and read the first configuration register. Since there are no
     * vendors that == 0xFFFF, it must be a non-existent device. */
    if ((vendor = pciConfigReadWord(Group, bus, slot, 0, 0)) != 0xFFFF) {
        device = pciConfigReadWord(Group, bus, slot, 0, 2);
        //TODO: Is Vendor Part Of System
    } return (vendor);
}


// Function to retrieve the device ID of a PCI device
uint16_t PciGetDeviceID(uint16_t Group, uint8_t bus ,uint8_t slot,uint8_t func) {
    // Read the vendor ID from the PCI configuration space
    uint32_t data = pci_read(Group, bus, slot, func, 0x00);
    // Extract and return the vendor ID
    return (data >> 16) & 0xFFFF;
}