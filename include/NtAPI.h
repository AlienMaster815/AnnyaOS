#pragma once

#ifndef _NTAPI_H
#define _NTAPI_H

#ifndef _KERNEL_ENTRY_
#define _KERNEL_ENTRY_
#define KERNEL_ENTRY extern "C"
#endif

#ifdef _KERNEL_MODULE_
#pragma warning(push)
#pragma warning(disable: 4083) // Disable specific warning
#pragma warning(disable: 4005) // Disable macro redefinition warning
#pragma warning(push)
#pragma warning(disable: 5051) // Disable C5051 warning
#endif

#include <stdint.h>

#ifndef _GUID_TYPE
#define _GUID_TYPE
typedef struct _GUID {
	unsigned char DataByte[16];
} GUID,* LPGUID, UUID, * PGUID, * PUUID;
#endif

#include <WDKSubsystem/Debuging/debuging.h>
#include <WDKSubsystem/Types/DebugTypes.h>
#include <WinAPI/WinAPITypes/CommonTypes.h>
#include <WinAPI/WinAPITypes/WDFLDRTypes.h>
#include <KernelAPI/WDFLDR.h>
#include <WinAPI/NtAPI/NtAPIFunc.h>

#define ACPI 1094930505
#define SMBIOS 837766737983
#define APM 658077

#ifndef _KERNEL_MODULE_
KERNEL_IMPORT void GetPciConfiguration(ULONG Group, ULONG SystemIoBusNumber,ULONG SlotNumber, ULONG Function ,PPCI_COMMON_CONFIG ConfigBuffer);
#else
KERNEL_EXPORT void GetPciConfiguration(ULONG Group, ULONG SystemIoBusNumber,ULONG SlotNumber, ULONG Function ,PPCI_COMMON_CONFIG ConfigBuffer);

#ifndef _ANNYA_DLL_CALL_REASONS
#define _ANNYA_DLL_CALL_REASONS
    #define DLL_PROCESS_ATTACH 1
    #define DLL_PROCESS_DETACH 0
    #define DLL_THREAD_ATTACH  2
    #define DLL_THREAD_DETACH  3
#endif


#endif

#endif
