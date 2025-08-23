#include <LouDDK.h>
#include <NtAPI.h>
#include "../Processors.h"
KERNEL_IMPORT void ioapic_unmask_irq(uint8_t irq) ;
// Structure representing the lower 32 bits of an IOAPIC redirection table entry
typedef struct {
    uint32_t vector : 8;          // Bits 0-7
    uint32_t delivery_mode : 3;   // Bits 8-10
    uint32_t destination_mode : 1;// Bit 11
    uint32_t delivery_status : 1; // Bit 12
    uint32_t polarity : 1;        // Bit 13
    uint32_t remote_irr : 1;      // Bit 14
    uint32_t trigger_mode : 1;    // Bit 15
    uint32_t mask : 1;            // Bit 16
    uint32_t reserved : 15;       // Bits 17-31
} IOAPICRedirectionEntryLow;

// Structure representing the upper 32 bits of an IOAPIC redirection table entry
typedef struct {
    uint32_t reserved : 24;       // Bits 0-23
    uint32_t destination : 8;     // Bits 24-31
} IOAPICRedirectionEntryHigh;

// Structure representing a full IOAPIC redirection table entry
typedef struct {
    IOAPICRedirectionEntryLow low;
    IOAPICRedirectionEntryHigh high;
} IOAPICRedirectionEntry;


typedef struct _ACPI_TABLE_HEADER {
    char Signature[4];        // "APIC"
    uint32_t Length;          // Length of the table, including the header
    uint8_t Revision;
    uint8_t Checksum;
    char OEMID[6];
    char OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
} ACPI_TABLE_HEADER, * PACPI_TABLE_HEADER;

typedef struct _ACPI_MADT {
    ACPI_TABLE_HEADER Header;
    uint32_t LocalApicAddress;
    uint32_t Flags;
    // Followed by a variable number of APIC structures
} ACPI_MADT, * PACPI_MADT;

typedef struct _ACPI_MADT_ENTRY_HEADER {
    uint8_t Type;
    uint8_t Length;
} ACPI_MADT_ENTRY_HEADER, * PACPI_MADT_ENTRY_HEADER;

typedef struct _ACPI_MADT_LOCAL_APIC {
    ACPI_MADT_ENTRY_HEADER Header;
    uint8_t ProcessorID;
    uint8_t APICID;
    uint32_t Flags;
} ACPI_MADT_LOCAL_APIC, * PACPI_MADT_LOCAL_APIC;

typedef struct _ACPI_MADT_IO_APIC {
    ACPI_MADT_ENTRY_HEADER Header;
    uint8_t IOAPICID;
    uint8_t Reserved;
    uint32_t IOAPICAddress;
    uint32_t GlobalSystemInterruptBase;
} ACPI_MADT_IO_APIC, * PACPI_MADT_IO_APIC;

typedef struct _ACPI_MADT_INTERRUPT_SOURCE_OVERRIDE {
    ACPI_MADT_ENTRY_HEADER Header;
    uint8_t Bus;
    uint8_t Source;
    uint32_t GlobalSystemInterrupt;
    uint16_t Flags;
} ACPI_MADT_INTERRUPT_SOURCE_OVERRIDE, * PACPI_MADT_INTERRUPT_SOURCE_OVERRIDE;

typedef struct _ACPI_MADT_NMI {
    ACPI_MADT_ENTRY_HEADER Header;
    uint16_t Flags;
    uint32_t GlobalSystemInterrupt;
} ACPI_MADT_NMI, * PACPI_MADT_NMI;

typedef struct _ACPI_MADT_LOCAL_APIC_NMI {
    ACPI_MADT_ENTRY_HEADER Header;
    uint8_t ProcessorID;
    uint16_t Flags;
    uint8_t LocalAPICLint;
} ACPI_MADT_LOCAL_APIC_NMI, * PACPI_MADT_LOCAL_APIC_NMI;

typedef struct _ACPI_MADT_LOCAL_APIC_ADDRESS_OVERRIDE {
    ACPI_MADT_ENTRY_HEADER Header;
    uint16_t Reserved;
    uint64_t LocalApicAddress;
} ACPI_MADT_LOCAL_APIC_ADDRESS_OVERRIDE, * PACPI_MADT_LOCAL_APIC_ADDRESS_OVERRIDE;

typedef struct {
    uint32_t ioapic_id;
    uint64_t ioapic_address;
    uint32_t gsi_base;
    uint64_t ioapic_vaddress;
} IOAPICInfo;

#define IOAPIC_REGSEL  0x00  // IOAPIC Register Select
#define IOAPIC_WIN     0x10  // IOAPIC Window
#define IOAPIC_REDIRECTION_TABLE_BASE 0x10


PACPI_MADT_IO_APIC GetIoApicHandleFromIrq(UINT8 Irq);

static UINT8 TotalApicInterrupts = 0;

void SetTotalIoApicInterrupts(UINT8 TotalInterrupts){
    TotalApicInterrupts = TotalInterrupts;
}

static inline volatile uint32_t* IoApicMmio(uint64_t ioapic_base, uint32_t offset) {
    return (volatile uint32_t*)((uintptr_t)ioapic_base + offset);
}

uint32_t IoApicRead(uint64_t ioapic_base, uint32_t reg) {
    *IoApicMmio(ioapic_base, IOAPIC_REGSEL) = reg;
    return *IoApicMmio(ioapic_base, IOAPIC_WIN);    
}

void IoApicWrite(uint64_t ioapic_base, uint32_t reg, uint32_t value) {
    *IoApicMmio(ioapic_base, IOAPIC_REGSEL) = reg;
    *IoApicMmio(ioapic_base, IOAPIC_WIN) = value;
}

KERNEL_IMPORT uint8_t GetTotalHardwareInterrupts(){
    return TotalApicInterrupts;
}

KERNEL_IMPORT uint8_t FindTrueIRQ(uint8_t IRQ);


LOUDDK_API_ENTRY void IoApicConfigureEntryFlags(
    uint8_t     irq,
    uint16_t    Flags
){
    uint32_t Polarity = Flags & 0x03;
    uint32_t Trigger  = (Flags >> 2) & 0x03;
    PACPI_MADT_IO_APIC IoApic = GetIoApicHandleFromIrq(irq);
    irq = irq - IoApic->GlobalSystemInterruptBase;

    uint32_t index = IOAPIC_REDIRECTION_TABLE_BASE + (2 * irq);
    uint32_t high_index = index + 1;
    uint32_t low = IoApicRead(IoApic->IOAPICAddress, index);
    uint32_t high = IoApicRead(IoApic->IOAPICAddress, high_index);

    //LouPrint("Polarity:%d : Trigger:%d\n", Polarity, Trigger);

    if(Polarity & 0x01){
        low &= ~(1 << 13);
        low |= ((Polarity >> 1) << 13);
    }
    if (Trigger & 0x01) {
        low &= ~(1 << 15);
        low |= ((Trigger >> 1) << 15);
    }

    IoApicWrite(IoApic->IOAPICAddress, index, low);
    IoApicWrite(IoApic->IOAPICAddress, high_index, high);

}

KERNEL_IMPORT void IoApicUnmaskIrq(uint8_t tirq) {

    uint8_t irq = FindTrueIRQ(tirq); //finds the interrupt based on if there is a overide

    PACPI_MADT_IO_APIC IoApic = GetIoApicHandleFromIrq(irq);

    //gets the offset of the irq register in the ioapic
    irq = irq - IoApic->GlobalSystemInterruptBase;

    uint32_t index = IOAPIC_REDIRECTION_TABLE_BASE + (2 * irq);
    uint32_t high_index = index + 1;

    // Read the current redirection entry
    uint32_t low = IoApicRead(IoApic->IOAPICAddress, index);
    uint32_t high = IoApicRead(IoApic->IOAPICAddress, high_index);

    // Clear the mask bit (16th bit) to unmask the interrupt
    low &= ~0x10000;
    
    //LouPrint("high:%bi\n", high);
    //LouPrint("low :%bi\n", low);

    // Write back the updated values
    IoApicWrite(IoApic->IOAPICAddress, index, low);
    IoApicWrite(IoApic->IOAPICAddress, high_index, high);
}


// Function to mask a given IRQ in the I/O APIC
KERNEL_IMPORT void IoApicMaskIrq(uint8_t tirq) {
    
    uint8_t irq = FindTrueIRQ(tirq); //finds the interrupt based on if there is a overide
    PACPI_MADT_IO_APIC IoApic = GetIoApicHandleFromIrq(irq);
    
    //gets the offset of the irq register in the ioapic
    irq = irq - IoApic->GlobalSystemInterruptBase;

    uint32_t index = IOAPIC_REDIRECTION_TABLE_BASE + (2 * irq);
    uint32_t high_index = index + 1;

    // Read the current redirection entry
    uint32_t low = IoApicRead(IoApic->IOAPICAddress, index);
    uint32_t high = IoApicRead(IoApic->IOAPICAddress, high_index);

    // Set the mask bit (16th bit) to mask the interrupt
    low |= 0x10000;

    IoApicWrite(IoApic->IOAPICAddress, index, low);
    IoApicWrite(IoApic->IOAPICAddress, high_index, high);
}




bool InitializeIoApic(PACPI_MADT_IO_APIC IoApic){
    LouPrint("Starting IO/APIC:%d At Address:%h\n", IoApic->IOAPICID, IoApic->IOAPICAddress);
    LouPrint("Creating An Address In Virtual Memory\n");
    UINT64 IoApicBase  = (uint64_t)LouKeMallocPageEx32(KILOBYTE_PAGE, 1,KERNEL_PAGE_WRITE_UNCAHEABLE_PRESENT, IoApic->IOAPICAddress);
    IoApic->IOAPICAddress = IoApicBase;
    UINT8 InterruptCount = (IoApicRead(IoApicBase, 0x01) >> 16) + 1;
    if(IoApic->GlobalSystemInterruptBase == TotalApicInterrupts){
        TotalApicInterrupts += InterruptCount;
    }
    
    LouPrint("Number Of Interrupts That are handled:%d\n", InterruptCount);
    LouPrint("Initializing IO/APIC To A Operating State\n");
    for (uint8_t irq = 0; irq < InterruptCount; irq++) {
        uint32_t index = IOAPIC_REDIRECTION_TABLE_BASE + (2 * irq);
        uint32_t high_index = index + 1;
        
        uint32_t high = 0;
        IoApicWrite(IoApicBase, high_index, high);

        uint32_t low = (irq + 0x20) | 0x10000;
        IoApicWrite(IoApicBase, index, low);

    }
    return true;
}

