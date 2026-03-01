#include <LouDDK.h>
#include <NtAPI.h>

LOUDDK_API_ENTRY LOUSTATUS LouKeGetSystemFirmwareTableProviderSignature(
	unsigned long FirmwareTableProvicerSignature,
	uintptr_t* TablePointer,
	uintptr_t* TableExtendedPointer,
	uint8_t* Type
);

LOUDDK_API_ENTRY LOUSTATUS LouKeGetSystemFirmwareTableId(
	unsigned long FirmwareTableId,
	unsigned long FirmwareTableProiderSignature,
	uintptr_t* TablePointer,
	uintptr_t* TableExtendedPointer,
	uint8_t* Type
);

LOUDDK_API_ENTRY LOUSTATUS LouKeGetSystemFirmwareTableBuffer(
	uint32_t SystemType,
	void* FirmwareTableBufferSrc,
	void* FirmwareTableBufferDest,
	unsigned int* BufferLength
);

LOUDDK_API_ENTRY
LOUSTATUS LouKeGetSystemFirmwareTable(
	ULONG FirmwareTableProviderSignature,
	ULONG FirmwareTabeId,
	PVOID FirmwareTableBuffer,
	ULONG BufferLength,
	PULONG ReturnLength) {
		
	LOUSTATUS Status = STATUS_SUCCESS;
	uintptr_t TablePointer = 0x0000, TableExtendedPointer = 0x0000;
	uint8_t Type;


	Status = LouKeGetSystemFirmwareTableProviderSignature(
		FirmwareTableProviderSignature, 
		&TablePointer, 
		&TableExtendedPointer,
		&Type
	);

	if (Status != STATUS_SUCCESS) {
		LouPrint("Firmware Table Provider Signature Could Not BeFound:ID NUMBER:%u\n",FirmwareTableProviderSignature);
		return Status;
	}

	Status = LouKeGetSystemFirmwareTableId(
		FirmwareTabeId,
		FirmwareTableProviderSignature,
		&TablePointer,
		&TableExtendedPointer,
		&Type
	);
	if (Status != STATUS_SUCCESS) {
		LouPrint("Firmware Table Id Could Not Be Found:ID NUMBER:%u\n",FirmwareTabeId);
		return Status;
	}



	Status = LouKeGetSystemFirmwareTableBuffer(
		FirmwareTableProviderSignature,
		(void*)TablePointer,
		FirmwareTableBuffer,
		&BufferLength
	);
	


	if (Status != STATUS_SUCCESS) {
		LouPrint("Firmware Table Could Not Be Created\nREASON: ");
		if(Status == (LOUSTATUS)STATUS_BUFFER_TOO_SMALL)LouPrint("Buffer Too Small\n");
		return Status;
	}

	*ReturnLength = BufferLength;


	return Status;
}
 