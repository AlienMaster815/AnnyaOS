#ifndef _LDM_DDK_H
#define _LDM_DDK_H
#ifdef __cplusplus
extern "C" {
#endif

#include <Ldm.h>

typedef struct _SIGNAL_REG_VALUE {
	UINT8*  RegName;
	UINT32  MsrAddr;
	UINT64  Value;
}SIGNAL_REG_VALUE, * PSIGNAL_REG_VALUE;

typedef struct _LHEA_ACPI_HEADER {
	UINT32  Signature;
	UINT32  Length;
	UINT8   Revision;
	UINT8   Checksum;
	UINT8   OemId[6];
	UINT64  OemTableId;
	UINT32  OemRevision;
	UINT32  CreatorId;
	UINT32  CreatorRevision;
} LHEA_ACPI_HEADER, * PLHEA_ACPI_HEADER;



#ifdef __cplusplus
}
#endif
#endif