#include <LouDDK.h>
#include <NtAPI.h>


typedef struct __attribute__((packed)) _ACPI_TABLE_HEADER {
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

typedef struct __attribute__((packed)) _ACPI_GENERIC_ADDRESS{
    uint8_t AddressSpaceID;
    uint8_t RegisterBitWidth;
    uint8_t RegisterBitOffset;
    uint8_t AccessSize;
    uint64_t Address;
} ACPI_GENERIC_ADDRESS;


typedef struct __attribute__((packed)) _ACPI_FADT{
    ACPI_TABLE_HEADER Header;
    uint32_t FirmwareCtrl;
    uint32_t Dsdt;
    uint8_t Reserved;
    uint8_t PreferredPowerManagementProfile;
    uint16_t SciInterrupt;
    uint32_t SmiCommandPort;
    uint8_t AcpiEnable;
    uint8_t AcpiDisable;
    uint8_t S4BiosReq;
    uint8_t PStateControl;
    uint32_t Pm1aEventBlock;
    uint32_t Pm1bEventBlock;
    uint32_t Pm1aControlBlock;
    uint32_t Pm1bControlBlock;
    uint32_t Pm2ControlBlock;
    uint32_t PmTimerBlock;
    uint32_t Gpe0Block;
    uint32_t Gpe1Block;
    uint8_t Pm1EventLength;
    uint8_t Pm1ControlLength;
    uint8_t Pm2ControlLength;
    uint8_t PmTimerLength;
    uint8_t Gpe0Length;
    uint8_t Gpe1Length;
    uint8_t Gpe1Base;
    uint8_t CStateControl;
    uint16_t WorstC2Latency;
    uint16_t WorstC3Latency;
    uint16_t FlushSize;
    uint16_t FlushStride;
    uint8_t DutyOffset;
    uint8_t DutyWidth;
    uint8_t DayAlarm;
    uint8_t MonthAlarm;
    uint8_t Century;
    uint16_t BootArchitectureFlags;
    uint8_t Reserved2;
    uint32_t Flags;
    // ACPI 2.0+ fields
    ACPI_GENERIC_ADDRESS ResetReg;
    uint8_t ResetValue;
    uint8_t Reserved3[3];
    uint64_t XFirmwareCtrl;
    uint64_t XDsdt;
    ACPI_GENERIC_ADDRESS XPm1aEventBlock;
    ACPI_GENERIC_ADDRESS XPm1bEventBlock;
    ACPI_GENERIC_ADDRESS XPm1aControlBlock;
    ACPI_GENERIC_ADDRESS XPm1bControlBlock;
    ACPI_GENERIC_ADDRESS XPm2ControlBlock;
    ACPI_GENERIC_ADDRESS XPmTimerBlock;
    ACPI_GENERIC_ADDRESS XGpe0Block;
    ACPI_GENERIC_ADDRESS XGpe1Block;
} ACPI_FADT , * PACPI_FADT;


#define SLP_EN 0x2000  // Sleep enable bit

static spinlock_t AcpiLock;
static PACPI_FADT FadtCopy = 0x00;

LOUDDK_API_ENTRY LOUSTATUS InitFADT(){

    LOUSTATUS Status = STATUS_UNSUCCESSFUL;


    uint8_t* Buffer = (uint8_t*)LouKeMalloc(ACPIBUFFER, WRITEABLE_PAGE | PRESENT_PAGE);
    ULONG ReturnLength = 0x0000;

    Status = AuxKlibGetSystemFirmwareTable(
        'ACPI',
        'FADT',
        Buffer,
        ACPIBUFFER,
        &ReturnLength
    );

    if (Status != LOUSTATUS_GOOD) {
        Status = AuxKlibGetSystemFirmwareTable(
            'ACPI',
            'FACP',
            Buffer,
            ACPIBUFFER,
            &ReturnLength
        );
    }

    // Assuming Buffer now contains the FADT table
    if (Status == LOUSTATUS_GOOD) {
        ACPI_FADT* fadt = (ACPI_FADT*)Buffer;
        FadtCopy = (ACPI_FADT*)LouKeMallocEx(ReturnLength, KILOBYTE_PAGE, WRITEABLE_PAGE | PRESENT_PAGE);
        memcpy((void*)FadtCopy,(void*)fadt, ReturnLength);
        LouKeFree((RAMADD)fadt);
    }
    else {
        LouKeFree(Buffer);
        return STATUS_UNSUCCESSFUL;
    }

    return LOUSTATUS_GOOD;
}

uint16_t AcpiGetTypeAS5(){


    return 0;
}

LOUDDK_API_ENTRY
void LouKeHalAcpiShutdown(){
    //later we will make a higher function for waiting for a good moment
    //lock acpi
    LouKIRQL LouIrl;
    LouKeAcquireSpinLock(&AcpiLock, &LouIrl);
    uint16_t SlpTypeAS5 = AcpiGetTypeAS5();
    outw(FadtCopy->Pm1aControlBlock, SlpTypeAS5 | SLP_EN);
    //we dont return from this
    sleep(10000);
    asm("hlt");
}