#ifndef _KERNEL_AUXILERY_H
#define _KERNEL_AUXILERY_H
#ifdef __cplusplus
extern "C" {
#endif

#include <Ldm/CommonTypes.h>

typedef struct _AUX_MODULE_BASIC_INFO {
	PVOID ImageBase;
}AUX_MODULE_BASIC_INFO,* PAUX_MODULE_BASIC_INFO;

#define AUX_KLIB_MODULE_PATH_LEN 256

typedef struct _AUX_MODULE_EXTENDED_INFO {
	AUX_MODULE_BASIC_INFO  BasicInfo;
	ULONG				   ImageSize;
	USHORT				   FileNameOffset;
	UCHAR				   FullPathName[AUX_KLIB_MODULE_PATH_LEN];
}AUX_MODULE_EXTENDED_INFO,* PAUX_MODULE_EXTENDED_INFO;

struct RawSMBIOSData
{
	BYTE  Used20CallingMethod;
	BYTE  SMBIOSMajorVersion;
	BYTE  SMBIOSMinorVersion;
	BYTE  DmiRevision;
	DWORD  Length;
	BYTE  SMBIOSTableData[];
};


typedef struct _KBUGCHECK_DATA {
	ULONG     BugCheckDataSize;
	ULONG     BugCheckCode;
	ULONG_PTR Parameter1;
	ULONG_PTR Parameter2;
	ULONG_PTR Parameter3;
	ULONG_PTR Parameter4;
} KBUGCHECK_DATA, * PKBUGCHECK_DATA;

LOUSTATUS
__stdcall
AuxKlibEnumerateSystemFirmwareTables(
	ULONG FirmwareTableProviderSignature,
	PVOID FirmwareTableBuffer,
	ULONG BufferLength,
	PULONG ReturnLength
);

LOUSTATUS AuxKlibGetBugCheckData(
	PKBUGCHECK_DATA BugCheckData
);

PIMAGE_EXPORT_DIRECTORY AuxKlibGetImageExportDirectory(
	PVOID ImageBase
);

LOUSTATUS AuxKlibGetSystemFirmwareTable(
	ULONG  FirmwareTableProviderSignature,
	ULONG  FirmwareTableID,
	PVOID  FirmwareTableBuffer,
	ULONG  BufferLength,
	PULONG ReturnLength
);

LOUSTATUS AuxKlibInitialize();


LOUSTATUS AuxKlibQueryModuleInformation(
	PULONG BufferSize,
	ULONG  ElementSize,
	PVOID  QueryInfo
);


#ifdef __cplusplus
}
#endif
#endif