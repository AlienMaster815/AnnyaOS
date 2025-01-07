#include <NtAPI.h>


//Define Used Internal Kernel Functions

NTSTATUS TRANSLATE_STATUS(LOUSTATUS Status);

LOUDDK_API_ENTRY
LOUSTATUS LouKeGetSystemFirmwareTable(
	ULONG FirmwareTableProviderSignature,
	ULONG FirmwareTabeId,
	PVOID FirmwareTableBuffer,
	ULONG BufferLength,
	PULONG ReturnLength);



NTSTATUS
__stdcall
AuxKlibEnumerateSystemFirmwareTables(
	 ULONG FirmwareTableProviderSignature,
	 PVOID FirmwareTableBuffer,
	 ULONG BufferLength,
	 PULONG ReturnLength
) {



	return STATUS_SUCCESS;
}


NTSTATUS AuxKlibGetBugCheckData(
	 PKBUGCHECK_DATA BugCheckData
) {

	return STATUS_SUCCESS;
}

PIMAGE_EXPORT_DIRECTORY AuxKlibGetImageExportDirectory(
	 PVOID ImageBase
) {


	return 0;
}



NTSTATUS AuxKlibGetSystemFirmwareTable(
	      ULONG  FirmwareTableProviderSignature,
	      ULONG  FirmwareTableID,
	 PVOID  FirmwareTableBuffer,
	      ULONG  BufferLength,
	 PULONG ReturnLength
) {
	LOUSTATUS LouKStatus = LOUSTATUS_GOOD;
	NTSTATUS DriverApiTranslatedStatus = STATUS_SUCCESS;
	
	LouKStatus = LouKeGetSystemFirmwareTable(
		FirmwareTableProviderSignature,
		FirmwareTableID,
		FirmwareTableBuffer,
		BufferLength,
		ReturnLength);

	DriverApiTranslatedStatus = (NTSTATUS)LouKStatus;

	return DriverApiTranslatedStatus;
}



NTSTATUS AuxKlibInitialize() {


	return STATUS_SUCCESS;
}

NTSTATUS AuxKlibQueryModuleInformation(
	       PULONG BufferSize,
	            ULONG  ElementSize,
			PVOID  QueryInfo
) {


	return STATUS_SUCCESS;
}