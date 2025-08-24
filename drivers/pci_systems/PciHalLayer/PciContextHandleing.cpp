#include <LouDDK.h>
#include <NtAPI.h>
#include <Hal.h>

void SetPciConfiguration(ULONG SystemIoBusNumber, ULONG SlotNumber, ULONG Function, PPCI_COMMON_CONFIG ConfigBuffer) {
    // Writing the values back into PCI Configuration Space
    pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x00, ConfigBuffer->Header.VendorID);
    pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x02, ConfigBuffer->Header.DeviceID);
    pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x04, ConfigBuffer->Header.Command);
    pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x06, ConfigBuffer->Header.Status);

    pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x08, ConfigBuffer->Header.RevisionID);
    pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x09, ConfigBuffer->Header.ProgIf);
    pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x0A, ConfigBuffer->Header.SubClass);
    pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x0B, ConfigBuffer->Header.BaseClass);
    pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x0C, ConfigBuffer->Header.CacheLineSize);
    pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x0D, ConfigBuffer->Header.LatencyTimer);
    pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x0E, ConfigBuffer->Header.HeaderType);
    pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x0F, ConfigBuffer->Header.BIST);

    if (ConfigBuffer->Header.HeaderType == 0x00) {
        // Writing Type 0 (general PCI device) configuration
        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x10, ConfigBuffer->Header.u.type0.BaseAddresses[0]);
        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x14, ConfigBuffer->Header.u.type0.BaseAddresses[1]);
        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x18, ConfigBuffer->Header.u.type0.BaseAddresses[2]);
        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x1C, ConfigBuffer->Header.u.type0.BaseAddresses[3]);
        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x20, ConfigBuffer->Header.u.type0.BaseAddresses[4]);
        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x24, ConfigBuffer->Header.u.type0.BaseAddresses[5]);

        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x28, ConfigBuffer->Header.u.type0.CIS);
        pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x2C, ConfigBuffer->Header.u.type0.SubVendorID);
        pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x2E, ConfigBuffer->Header.u.type0.SubSystemID);
        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x30, ConfigBuffer->Header.u.type0.ROMBaseAddress);
        
        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x34, ConfigBuffer->Header.u.type0.CapabilitiesPtr);
        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x3C, ConfigBuffer->Header.u.type0.InterruptLine);
        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x3D, ConfigBuffer->Header.u.type0.InterruptPin);
        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x3E, ConfigBuffer->Header.u.type0.MinimumGrant);
        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x3F, ConfigBuffer->Header.u.type0.MaximumLatency);
    }
    else if (ConfigBuffer->Header.HeaderType == 0x01) {
        // Writing Type 1 (PCI-to-PCI bridge) configuration
        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x10, ConfigBuffer->Header.u.type1.BaseAddresses[0]);
        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x14, ConfigBuffer->Header.u.type1.BaseAddresses[1]);

        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x18, ConfigBuffer->Header.u.type1.PrimaryBus);
        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x19, ConfigBuffer->Header.u.type1.SecondaryBus);
        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x1A, ConfigBuffer->Header.u.type1.SubordinateBus);
        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x1B, ConfigBuffer->Header.u.type1.SecondaryLatency);

        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x1C, ConfigBuffer->Header.u.type1.IOBase);
        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x1D, ConfigBuffer->Header.u.type1.IOLimit);

        pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x1E, ConfigBuffer->Header.u.type1.SecondaryStatus);
        pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x20, ConfigBuffer->Header.u.type1.MemoryBase);
        pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x22, ConfigBuffer->Header.u.type1.MemoryLimit);
        pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x24, ConfigBuffer->Header.u.type1.PrefetchBase);
        pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x26, ConfigBuffer->Header.u.type1.PrefetchLimit);

        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x28, ConfigBuffer->Header.u.type1.PrefetchBaseUpper32);
        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x2C, ConfigBuffer->Header.u.type1.PrefetchLimitUpper32);

        pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x30, ConfigBuffer->Header.u.type1.IOBaseUpper16);
        pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x32, ConfigBuffer->Header.u.type1.IOLimitUpper16);

        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x34, ConfigBuffer->Header.u.type1.CapabilitiesPtr);
        write_pci(0 ,SystemIoBusNumber, SlotNumber, Function, 0x38, ConfigBuffer->Header.u.type1.ROMBaseAddress);

        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x3C, ConfigBuffer->Header.u.type1.InterruptLine);
        pciConfigWriteByte(0 ,SystemIoBusNumber, SlotNumber, Function, 0x3D, ConfigBuffer->Header.u.type1.InterruptPin);
        pciConfigWriteWord(0 ,SystemIoBusNumber, SlotNumber, Function, 0x3E, ConfigBuffer->Header.u.type1.BridgeControl);
    }
    else if (ConfigBuffer->Header.HeaderType == 0x02) {
        // For CardBus Bridges, similar logic can be used (not yet implemented).
    }
}

PPCI_CONTEXT LouKeHalPciSaveContext(PPCI_DEVICE_OBJECT PDEV){

    PPCI_CONTEXT SavedContext = LouKeMallocType(PCI_CONTEXT, KERNEL_GENERIC_MEMORY);
    GetPciConfiguration(PDEV->Group, PDEV->bus,PDEV->slot, PDEV->func, (PPCI_COMMON_CONFIG)LouKeCastToUnalignedPointer(&SavedContext->PciConfig));
    SavedContext->PDEV = (void*)PDEV;

    return SavedContext;
}

void LouKeHalPciRestoreContext(PPCI_CONTEXT PciContext){

    UNUSED PPCI_COMMON_CONFIG PciConfig = (PPCI_COMMON_CONFIG)LouKeCastToUnalignedPointer(&PciContext->PciConfig);
    PPCI_DEVICE_OBJECT PDEV = (PPCI_DEVICE_OBJECT)PciContext->PDEV;

    SetPciConfiguration(PDEV->bus, PDEV->slot, PDEV->func, PciConfig);

    LouFree((RAMADD)PciContext);
}

void LouKeHalPciClearMaster(PPCI_DEVICE_OBJECT PDEV){
        // Read the current value of the PCI Command Register (offset 0x04)
    uint16_t command_reg = pciConfigReadWord(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, 0x04);

    // Clear the Bus Master bit (bit 2)
    command_reg &= ~0x0004;

    // Write the modified value back to the PCI Command Register
    pciConfigWriteWord(0 ,PDEV->bus, PDEV->slot, PDEV->func, 0x04, command_reg);
}

LOUDDK_API_ENTRY void LouKeHalPciSetMaster(PPCI_DEVICE_OBJECT PDEV){
         // Read the current value of the PCI Command Register (offset 0x04)
    uint16_t command_reg = pciConfigReadWord(PDEV->Group, PDEV->bus, PDEV->slot, PDEV->func, 0x04);

    command_reg |= 0x0004;

    // Write the modified value back to the PCI Command Register
    pciConfigWriteWord(0 ,PDEV->bus, PDEV->slot, PDEV->func, 0x04, command_reg);   
}

LOUDDK_API_ENTRY void LouKeHalPciEnableInterrupts(PPCI_DEVICE_OBJECT PDEV){
    LouKeWritePciCommandRegister(PDEV,LouKeReadPciCommandRegister(PDEV) & ~(1 << 10));
}
LOUDDK_API_ENTRY void LouKeHalPciDisableInterrupts(PPCI_DEVICE_OBJECT PDEV){
    LouKeWritePciCommandRegister(PDEV,LouKeReadPciCommandRegister(PDEV) | (1 << 10));
}