#include <NtAPI.h>


//Define Used Internal Kernel Functions

LOUSTATUS TRANSLATE_STATUS(LOUSTATUS Status);

LOUAPI
LOUSTATUS LouKeGetSystemFirmwareTable(
	ULONG FirmwareTableProviderSignature,
	ULONG FirmwareTabeId,
	PVOID FirmwareTableBuffer,
	ULONG BufferLength,
	PULONG ReturnLength);



LOUSTATUS
__stdcall
AuxKlibEnumerateSystemFirmwareTables(
	 ULONG FirmwareTableProviderSignature,
	 PVOID FirmwareTableBuffer,
	 ULONG BufferLength,
	 PULONG ReturnLength
) {



	return STATUS_SUCCESS;
}


LOUSTATUS AuxKlibGetBugCheckData(
	 PKBUGCHECK_DATA BugCheckData
) {

	return STATUS_SUCCESS;
}

PIMAGE_EXPORT_DIRECTORY AuxKlibGetImageExportDirectory(
	 PVOID ImageBase
) {


	return 0;
}



LOUSTATUS AuxKlibGetSystemFirmwareTable(
	      ULONG  FirmwareTableProviderSignature,
	      ULONG  FirmwareTableID,
	 PVOID  FirmwareTableBuffer,
	      ULONG  BufferLength,
	 PULONG ReturnLength
) {
	LOUSTATUS LouKStatus = STATUS_SUCCESS;
	LOUSTATUS DriverApiTranslatedStatus = STATUS_SUCCESS;
	
	LouKStatus = LouKeGetSystemFirmwareTable(
		FirmwareTableProviderSignature,
		FirmwareTableID,
		FirmwareTableBuffer,
		BufferLength,
		ReturnLength);

	DriverApiTranslatedStatus = (LOUSTATUS)LouKStatus;

	return DriverApiTranslatedStatus;
}



LOUSTATUS AuxKlibInitialize() {


	return STATUS_SUCCESS;
}

LOUSTATUS AuxKlibQueryModuleInformation(
	       PULONG BufferSize,
	            ULONG  ElementSize,
			PVOID  QueryInfo
) {


	return STATUS_SUCCESS;
}