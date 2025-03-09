#include <LouDDK.h>
#include <NtAPI.h>

typedef struct {
    char Signature[4];        // Table identifier (e.g., "MCFG")
    uint32_t Length;          // Length of the table, including the header
    uint8_t Revision;
    uint8_t Checksum;
    char OEMID[6];
    char OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
} ACPI_TABLE_HEADER;

typedef struct _ACPI_MCFG{
    ACPI_TABLE_HEADER Header;
    uint64_t Reserved;
    // Followed by a variable number of MCFG Configuration Base Address Allocation structures
    ACPI_MCFG_ALLOCATION Allocations[];
} ACPI_MCFG, * PACPI_MCFG;

KERNEL_IMPORT
void AddPcieGroup(PACPI_MCFG_ALLOCATION PciManagerData);

LOUDDK_API_ENTRY LOUSTATUS InitMCFG() {
    LOUSTATUS Status = LOUSTATUS_GOOD;
    uint8_t* Buffer = (uint8_t*)LouMalloc(ACPIBUFFER);
    ULONG ReturnLength = 0x000;
    Status = AuxKlibGetSystemFirmwareTable(
        'ACPI',
        'MCFG',
        Buffer,
        ACPIBUFFER,
        &ReturnLength
    );

    if (Status == LOUSTATUS_GOOD) {
        LouPrint("PCIe Supported Initializing PCIe systems\n");
        volatile PACPI_MCFG Mcfg = (PACPI_MCFG)Buffer;
        size_t NumberOfEntries = (Mcfg->Header.Length - 44) / sizeof(ACPI_MCFG_ALLOCATION);
        LouPrint("Number Of MCFG Entries:%d\n", NumberOfEntries);
        for(size_t i = 0 ; i < NumberOfEntries; i++){
            AddPcieGroup(&Mcfg->Allocations[i]);
        }
        while(1);
    }

    LouFree(Buffer);
    return Status;
}
