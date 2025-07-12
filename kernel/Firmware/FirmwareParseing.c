#define _EFI_CORE_C
#include <LouAPI.h>
#include <bootloader/grub/multiboot2.h>

static LOUSINE_EFI_CORE_STRUCTURE Efi;

static mutex_t EfiMasterMutex = {0};

PLOUSINE_EFI_CORE_STRUCTURE LouKeAcquireEfiMaster(){
	MutexLock(&EfiMasterMutex);
	return &Efi;
}

void LouKeReleaseEfiMaster(){
	MutexUnlock(&EfiMasterMutex);
}

#define SMB_SIGNATURE 0x424D53 // 'S', 'M', 'B' in little-endian
#define APM_SIGNATURE 0x4D5041 // 'A', 'P', 'M' in little-endian

static uintptr_t EFI_TABLE = 0x00;
static uintptr_t RSDP_MASTER = 0x00;
static uint8_t TYPE_MASTER = 0x00;

static spinlock_t FirmwareLock;

uintptr_t LouKeGetRsdp(){
	return RSDP_MASTER;
}

typedef struct PACKED _ACPI_STD_HEADER {
	char Signature[4];
	uint32_t Size;
	uint8_t Revision;
	uint8_t Checksum;
	char OEMID[6];
	char OEMTABLEID[8];
	uint32_t OEMRevision;
	uint32_t CRevision;
}ACPI_STD_HEADER, * PACPI_STD_HEADER;

typedef struct PACKED _XSDT_TABLE{
    char Signature[4];       // 'XSDT'
    uint32_t Length;         // Length of the entire XSDT, including the header and all entries
    uint8_t Revision;        // ACPI revision
    uint8_t Checksum;        // Checksum of the entire XSDT
    char OEMID[6];           // OEM ID
    char OEMTableID[8];      // OEM Table ID
    uint32_t OEMRevision;    // OEM Revision number
    uint32_t CreatorID;      // ID of the table's creator
    uint32_t CreatorRevision;// Revision of the creator's utility
} XSDT_TABLE;


typedef struct PACKED _RSDP_Descriptor {
	char signature[8];          // Signature, should be "RSD PTR "
	uint8_t checksum;           // Checksum of the first 20 bytes
	char oem_id[6];             // OEM ID
	uint8_t revision;           // ACPI revision (1 for ACPI 1.0)
	uint32_t rsdt_address;      // 32-bit physical address of the RSDT
}RSDP_Descriptor, * PRSDP_Descriptor;


typedef struct PACKED _RSDP_Descriptor2 {
	char signature[8];          // Signature, should be "RSD PTR "
	uint8_t checksum;           // Checksum of the first 20 bytes
	char oem_id[6];             // OEM ID
	uint8_t revision;           // ACPI revision (1 for ACPI 1.0)
	uint32_t rsdt_address;      // 32-bit physical address of the RSDT
	uint32_t length;            // Total length of the RSDP structure
	uint64_t xsdt_address;      // 64-bit physical address of the XSDT (ACPI 2.0+)
	uint8_t extended_checksum;  // Checksum of entire structure including extended part (ACPI 2.0+)
	uint8_t reserved[3];        // Reserved, must be zero
}RSDP_Descriptor2, * PRSDP_Descriptor2;


static struct multiboot_tag_apm* APM_MASTER = 0x00;


LOUSTATUS LouKeSetEfiTable(uint64_t Address) {
    struct multiboot_tag_efi64* TableHeader = (struct multiboot_tag_efi64*)Address;
    
    // Cast the 32-bit pointer to a 64-bit pointer
	EnforceSystemMemoryMap((uint64_t)(uintptr_t)TableHeader->pointer, TableHeader->size);
	EFI_TABLE = (uint64_t)(uintptr_t)TableHeader->pointer;

    return STATUS_SUCCESS;  // Assuming LOUSTATUS_SUCCESS is your success code
}

LOUSTATUS LouKeSetSmbios(uintptr_t SMBIOS) {
	return LOUSTATUS_GOOD;
}

LOUSTATUS LouKeSetRsdp(uintptr_t RSDP,uint8_t Type) {

	RSDP_MASTER = RSDP;
	TYPE_MASTER = Type;

	//LouPrint("RSDP Address Is:%d:Version:%d\n",RSDP_MASTER,TYPE_MASTER);

	return LOUSTATUS_GOOD;
}

LOUSTATUS LouKeSetApm(struct multiboot_tag_apm* APM) {

	APM_MASTER = APM;
	return LOUSTATUS_GOOD;
}


LOUSTATUS LouKeGetSystemFirmwareTableProviderSignature(
	unsigned long FirmwareTableProviderSignature, 
	uintptr_t* TablePointer,
	uintptr_t* TableExtended,
	uint8_t* Type) {

	LouKIRQL OldIrql;
	LouKeAcquireSpinLock(&FirmwareLock, &OldIrql);

	LOUSTATUS Status = (LOUSTATUS)STATUS_INVALID_PARAMETER;


	if ('ACPI' == FirmwareTableProviderSignature) {
		
		PRSDP_Descriptor Rsdp = (PRSDP_Descriptor)RSDP_MASTER;

		if (strncmp("RSD PTR", (const char*)Rsdp->signature, 7) != 0) {
			LouKeReleaseSpinLock(&FirmwareLock, &OldIrql);
			return (LOUSTATUS)STATUS_FIRMWARE_IMAGE_INVALID;
		}
		if (TYPE_MASTER == 1) {


			*TablePointer = (uintptr_t)Rsdp->rsdt_address;
			*Type = TYPE_MASTER;
			if ((*TablePointer != 0) && (Type != 0)) {
				Status = LOUSTATUS_GOOD;
			}
		}
		else {

			PRSDP_Descriptor2 Rsdp2 = (PRSDP_Descriptor2)Rsdp;

			*TablePointer = (uintptr_t)Rsdp2->rsdt_address;
			*TableExtended = (uintptr_t)Rsdp2->xsdt_address;
			*Type = TYPE_MASTER;
			if ((*TablePointer != 0) && (Type != 0)) {
				Status = LOUSTATUS_GOOD;
			}
		}
	}
	else if (SMB_SIGNATURE == FirmwareTableProviderSignature) {

	}
	else if (APM_SIGNATURE == FirmwareTableProviderSignature) {
		*TablePointer = (uintptr_t)APM_MASTER;
		*Type = 0;
		if (*TablePointer != 0) {
			Status = LOUSTATUS_GOOD;
		}
	}
	LouKeReleaseSpinLock(&FirmwareLock, &OldIrql);

	return Status;
}

LOUSTATUS LouKeGetSystemFirmwareTableId(
	unsigned long FirmwareTableId,
	unsigned long FirmwareTableProviderSignature,
	uintptr_t* TablePointer,
	uintptr_t* TableExtendedPointer,
	uint8_t* Type
) {
	LOUSTATUS Status = (LOUSTATUS)STATUS_UNSUCCESSFUL;
	uint64_t PhyCheck = 0;
	char MasterString[sizeof(int)];

	LouKIRQL OldIrql;
	LouKeAcquireSpinLock(&FirmwareLock, &OldIrql);

	if (FirmwareTableProviderSignature == 'ACPI') {
		UIntToString(FirmwareTableId, MasterString);
		// Calculate the end address of the table

		if (FirmwareTableId == 'XSDT') {
			*TablePointer = *TableExtendedPointer;
			Status = LOUSTATUS_GOOD;
			LouKeReleaseSpinLock(&FirmwareLock, &OldIrql);
			return Status;
		}
		if (FirmwareTableId == 'RSDT') {
			Status = LOUSTATUS_GOOD;
			LouKeReleaseSpinLock(&FirmwareLock, &OldIrql);
			return Status;
		}
		
		if(*TableExtendedPointer != 0x00){
			XSDT_TABLE* GenericTable2 = (XSDT_TABLE*)(*TableExtendedPointer);
			
			// Calculate the number of table entries

			// Now you can iterate through the entries
			for (
				uint64_t i = ((uint64_t)GenericTable2 + sizeof(XSDT_TABLE)); 
				i < ((uint64_t)GenericTable2 + GenericTable2->Length) ; 
				i+= sizeof(uint64_t)
				) {
				
				if(*(uint64_t*)i == 0x00)continue;

				ACPI_STD_HEADER* table = (ACPI_STD_HEADER*)(uint8_t*)*(uint64_t*)(uint8_t*)i;
				RequestPhysicalAddress((uint64_t)(uintptr_t)&table->Signature[0], &PhyCheck);
				//LouPrint("Table At:%h\n", *(uint64_t*)i);
				//LouPrint("Signature:%h\n", &table->Signature[0]);
				//LouPrint("PhyCheck:%h\n", PhyCheck);
				//LouPrint("Table Name:%s\n\n",&table->Signature[0]);
				if((uintptr_t)(uint8_t*)&table->Signature[0] != PhyCheck){
					//some systems on real hardware faild to get detected by grub so we will map whatever data is not mapped
					LouKeMapContinuousMemoryBlock((uint64_t)&table->Signature[0], (uint64_t)&table->Signature[0], KILOBYTE_PAGE, WRITEABLE_PAGE | PRESENT_PAGE);
				}
				if ((strncmp((const string)&table->Signature[0], (const string)MasterString, 4) == 0) && (strlen((const string)&table->Signature[0]) != 0)) {
					*TablePointer = (uintptr_t)table;
					Status = LOUSTATUS_GOOD;
					LouKeReleaseSpinLock(&FirmwareLock, &OldIrql);
					return Status;
				}
			}
		}
		if(*TablePointer != 0x00){
			//PACPI_STD_HEADER GenericTable = (PACPI_STD_HEADER)(*TablePointer);

		}
	}
	else if (FirmwareTableProviderSignature == SMB_SIGNATURE) {
		// Handle SMBIOS signatures
	}
	else if (FirmwareTableProviderSignature == APM_SIGNATURE) {
		// Handle APM signatures
	}
	LouKeReleaseSpinLock(&FirmwareLock, &OldIrql);
	return STATUS_INVALID_PARAMETER;
}



LOUSTATUS LouKeGetSystemFirmwareTableBuffer(
	uint32_t SystemType,
	void* FirmwareTableBufferSrc,
	void* FirmwareTableBufferDest, 
	unsigned long* BufferLength
) {
	LouKIRQL OldIrql;
	LouKeAcquireSpinLock(&FirmwareLock, &OldIrql);

	uint32_t ResultBufferLength = *BufferLength;
	
	if (SystemType == 'ACPI') {
		PACPI_STD_HEADER Fubar = (PACPI_STD_HEADER)FirmwareTableBufferSrc;

		if (Fubar->Size > ResultBufferLength){
			//LouPrint("Error Exspecting Size:%h\n", Fubar->Size);
			LouKeReleaseSpinLock(&FirmwareLock, &OldIrql);
			return (LOUSTATUS)STATUS_BUFFER_TOO_SMALL;
		}
		else if ((ResultBufferLength >= Fubar->Size) || (ResultBufferLength == 0))ResultBufferLength = Fubar->Size;
	}

	memcpy(FirmwareTableBufferDest, FirmwareTableBufferSrc, ResultBufferLength);

	*BufferLength = ResultBufferLength;
	LouKeReleaseSpinLock(&FirmwareLock, &OldIrql);
	return LOUSTATUS_GOOD;
}

typedef struct {
    EFI_GUID 	VendorGuid;
    void* 		VendorTable;
} EFI_CONFIGURATION_TABLE;

typedef struct {
    uint64_t 	Signature;
    uint8_t 	Checksum;
    uint8_t 	OEMID[6];
    uint8_t 	Revision;
    uint32_t 	RsdtAddress;
    uint32_t 	Length;
    uint64_t 	XsdtAddress;
    uint8_t 	ExtendedChecksum;
    uint8_t 	Reserved[3];
} RSDP_DESCRIPTOR_2;


RSDP_DESCRIPTOR_2* find_rsdp_from_efi_table(uint64_t efi_system_table_address) {
    EFI_SYSTEM_TABLE *SystemTable = (EFI_SYSTEM_TABLE *)efi_system_table_address;
    EFI_CONFIGURATION_TABLE *ConfigTable = (EFI_CONFIGURATION_TABLE *)SystemTable->Tables;

    EFI_GUID Acpi20TableGuid = { 0x8868e871, 0xe4f1, 0x11d3, { 0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81 } };
    EFI_GUID AcpiTableGuid = { 0xeb9d2d30, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x00, 0x0c, 0x29, 0x27, 0x81, 0x98 } };

    for (uint64_t i = 0; i < SystemTable->TableCount; i++) {
        if (memcmp(&ConfigTable[i].VendorGuid, &Acpi20TableGuid, sizeof(EFI_GUID)) == 0 ||
            memcmp(&ConfigTable[i].VendorGuid, &AcpiTableGuid, sizeof(EFI_GUID)) == 0) {
            return (RSDP_DESCRIPTOR_2 *)ConfigTable[i].VendorTable;
        }
    }

    return NULL;  // RSDP not found
}

static uint64_t EfiMemMap = 0x00;

void SetEfiMap(uint64_t Map){
	EfiMemMap = Map;
}



//static EFI_GUID SMBIOS_GUID = { 0xEB9D2D31, 0x2D88, 0x11D3, { 0x9A, 0x16, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D } };

bool LouKeMapEfiMemory(){

	if(EfiMemMap){
		//LouPrint("We Got Somthing\n");
		struct multiboot_tag_efi_mmap* Map = (struct multiboot_tag_efi_mmap*)EfiMemMap;

		//LouPrint("DescVer:%d\n", Map->descr_vers);
		//LouPrint("DescSize:%d\n", Map->descr_size);

		static EFI_MEMORY_DESCRIPTOR* Desc;

		for(uint64_t i = 16; i < (Map->size); i += Map->descr_size){
			
			Desc = (EFI_MEMORY_DESCRIPTOR*)(EfiMemMap + i);
			switch(Desc->Type){
				case(0):
				case(3):
				case(4):
				case(5):
				case(6):
				case(8):
				case(9):
				case(10):
				case(11):
				case(12):
				case(13):
				case(14):
					EnforceSystemMemoryMap(Desc->PhysicalStart, 4096 * Desc->NumberOfPages);
					EnforceSystemMemoryMap(Desc->VirtualStart, 4096 * Desc->NumberOfPages);
				default: continue;
			}
		}
		LouMapAddress(EFI_TABLE, EFI_TABLE, KERNEL_PAGE_WRITE_PRESENT, KILOBYTE_PAGE);
		UNUSED EFI_SYSTEM_TABLE* EfiSystemTable = (EFI_SYSTEM_TABLE*)EFI_TABLE;
		UNUSED EFI_CONFIGURATION_TABLE* configTable = (EFI_CONFIGURATION_TABLE*)EfiSystemTable->Tables;

		return true;
	}
	return false;
}
#define BIOS_START 0xF0000
#define BIOS_END   0xFFFFF
void InitializeSmBiosSystem(void* Entry);
void InitializeDmiSystem();

void LouKeHandleSystemIsBios(){	
    InitializeSmBiosSystem(0x00);
	InitializeDmiSystem();
}

void* GetEfiTable(){
	return (void*)EFI_TABLE;
}

void InitializeEfiCore(){

	//LouPrint("InitializeEfiCore()\n");
	//while(1);
    //InitializeSmBiosSystem(0x00);
}