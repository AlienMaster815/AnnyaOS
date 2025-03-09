#include <LouAPI.h>

typedef struct _PCIE_SYSTEM_MANAGER{
    ListHeader  Neighbors;
    uint64_t    BaseAddress;
    uint16_t    PCISegmentGroupNumber;
    uint8_t     StartBusNumber;
    uint8_t     EndBusNumber;
}PCIE_SYSTEM_MANAGER, * PPCIE_SYSTEM_MANAGER;

UNUSED static uint16_t MaxGroupCount = 0;
UNUSED static PCIE_SYSTEM_MANAGER Psm;
UNUSED static mutex_t PsmLock; 
UNUSED static bool UsingPCIE = false;

void AddPcieGroup(PACPI_MCFG_ALLOCATION PciManagerData){



}

uint32_t pci_read(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset) {
    uint32_t address;
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

    // Create the PCI configuration address
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
        (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));

    // Write the address to the PCI configuration address register
    outl(PCI_CONFIG_ADDRESS_PORT, address);
    // Read and return the data from the PCI configuration data register
    return inl(PCI_CONFIG_DATA_PORT);
}

void write_pci(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t function, uint32_t offset, uint32_t value) {
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
    // Calculate the address for PCI configuration space access
    uint32_t address = pciConfigAddress(bus, device, function, reg);

    // Write the address to the address port
    outl(PCI_CONFIG_ADDRESS_PORT, address);

    // Read and return the byte from the data port
    return inb(PCI_CONFIG_DATA_PORT + (reg & 3));
}

void pciConfigWriteByte(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function, uint32_t reg, uint8_t value) {
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

#define PCI_COMMAND_OFFSET 0x04
#define PCI_ENABLE_BIT     0x02


bool EnablePciDevice(P_PCI_DEVICE_OBJECT PDEV, unsigned long flags) {
    uint32_t address;
    uint16_t command;

    // Construct the configuration address
    address = (1U << 31) | (PDEV->bus << 16) | (PDEV->slot << 11) | (PDEV->func << 8) | PCI_COMMAND_OFFSET;

    // Write the configuration address to the address port
    outl(PCI_CONFIG_ADDRESS_PORT, address);

    // Read the device's command register
    command = inw(PCI_CONFIG_DATA_PORT);

    // Set the enable bit if the corresponding flag is set
    if (flags & PCI_ENABLE_BIT) {
        command |= PCI_ENABLE_BIT;
    }

    // Write the modified command register back to the device
    outw(PCI_CONFIG_DATA_PORT, command);

    // Check if the device is enabled
    if (flags & PCI_ENABLE_BIT) {
        // Read the device's command register again
        command = inw(PCI_CONFIG_DATA_PORT);
        return (command & PCI_ENABLE_BIT) != 0;
    }
    else {
        // If we didn't try to enable the device, consider it enabled
        return true;
    }
}

