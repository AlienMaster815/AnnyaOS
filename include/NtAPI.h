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

typedef struct _OBJECT_ATTRIBUTES{
    ULONG               Length;
    HANDLE              RootDirectory;
    PCUNICODE_STRING    ObjectName;
    ULONG               Attributes;
    PVOID               SecurityDescriptor;
    PVOID               SecurityQualityOfService;
}OBJECT_ATTRIBUTES, * POBJECT_ATTRIBUTES;

typedef struct _CURDIR{
    UNICODE_STRING      DosPath;
    HANDLE              Handle;
}CURDIR, * PCURDIR;

typedef struct _WIN_STRING{
    USHORT Length;
    USHORT MaximumLength;
    PCHAR  Buffer;
}WIN_STRING, * PWIN_STRING,
     ANSI_STRING, *PANSI_STRING, 
        OEM_STRING, *POEM_STRING;

typedef struct _RTL_DRIVE_LETTER_CURDIR{
    USHORT  Flags;
    USHORT  Length;
    ULONG   TimeStamp;
    STRING  DosPath;
}RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

#define RTL_MAX_DRIVE_LETTERS 32

typedef struct _RTL_USER_PROCESS_PARAMETERS{
    ULONG                       MaximumLength;
    ULONG                       Length;
    ULONG                       Flags;
    ULONG                       DebugFlags;
    HANDLE                      ConsoleHandle;
    ULONG                       ConsoleFlags;
    HANDLE                      StandardInput;
    HANDLE                      StandardOutput;
    HANDLE                      StandardError;
    CURDIR                      CurrentDirectory;
    UNICODE_STRING              DllPath;
    UNICODE_STRING              ImagePathName;
    UNICODE_STRING              CommandLine;
    PVOID                       Enviornment;
    ULONG                       StartingX;
    ULONG                       StartingY;
    ULONG                       CountX;
    ULONG                       CountY;
    ULONG                       CountCharsX;
    ULONG                       CountCharsY;
    ULONG                       FillAttribute;
    ULONG                       WindowFlag;
    ULONG                       ShowWindowFlags;
    UNICODE_STRING              WindowTitle;
    UNICODE_STRING              DesktopInfo;
    UNICODE_STRING              ShellInfo;
    UNICODE_STRING              RuntimeData;
    RTL_DRIVE_LETTER_CURDIR     CurrentDirectory[RTL_MAX_DRIVE_LETTERS];
    ULONG_PTR                   EnviornmentSize;
    ULONG_PTR                   EnviornmentVersion;
    PVOID                       PackageDependencyData;
    ULONG                       ProcessGroupId;
    ULONG                       LoaderThreads;
    UNICODE_STRING              RedirectionDllName;
    UNICODE_STRING              HeapPartitionName;
    unsigned long long*         DefaultThreadPoolCpuSetMask;
    ULONG                       DefaultThreadPoolCpuSetCount;
    ULONG                       DefualtThreadPoolhreadMaximum;
    ULONG                       HeapMemoryType;
}RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;

typedef enum _PS_CREATE_STATE{
    PsCreateInitialState = 0,
    PsCreateFailOnFileOpen = 1,
    PsCreateFailOnSectionCreate = 2,
    PsCreateFailExeFormat = 3,
    PsCreateFailMachineMismatch = 4,
    PsCreateFailExeName = 5,
    PsCreateSuccess = 6,
    PsCreateMaximumStates = 7,
}PS_CREATE_STATE;

typedef struct _PS_CREATE_INFO{
    SIZE                        Size;
    PS_CREATE_STATE             State;
    union{
        struct {
            union{
                ULONG           InitFlags;
                struct{
                    UCHAR       WriteOutputOnExit               : 1;
                    UCHAR       DetectManifest                  : 1;
                    UCHAR       IFEOSkipDebugger                : 1;
                    UCHAR       IFEODoNotPropagateKeyState      : 1;
                    UCHAR       SpareBits1                      : 4;
                    UCHAR       SpareBits2                      : 8;
                    USHORT      ProhibitedImageCharacteristics  : 16;
                };
            };
            ACCESS_MASK         AditionalFileAccess;
        }InitialState;
        struct{
            HANDLE              FileHandle;
        }FailSection;
        struct{
            USHORT              DllCharecteristics;
        }ExeFormat;
        struct{
            HANDLE              IEFOKey;
        }ExeName;
        struct{
            union{
                ULONG           OuputFlags;
                struct{
                    UCHAR       ProtectedProcess                : 1;
                    UCHAR       AddressSpaceOverride            : 1;
                    UCHAR       DevOverrideEnabled              : 1;
                    UCHAR       ManifestDetected                : 1;
                    UCHAR       ProtectedProcessLight           : 1;
                    UCHAR       SpareBits1                      : 3;
                    UCHAR       SpareBits2                      : 8;
                    USHORT      SpareBits3                      : 16;
                };
            };
            HANDLE              FileHandle;
            HANDLE              SectionHandle;
            unsigned long long  UserProcessParametersNative;
            ULONG               UserProcessParametersWow64;
            ULONG               CurrentParameterFlags;
            ULONG               PebAddressNative;
            unsigned long long  ManifestAddress;
            ULONG               ManifestSize;
        }SuccessState;
    };
}PS_CREATE_INFO, * PPS_CREATE_INFO;

typedef struct _PS_ATTRIBUTE
{
    ULONG_PTR           Attribute;
    SIZE                Size;
    union
    {
        ULONG_PTR       Value;
        PVOID           ValuePtr;
    };
    SIZE*               ReturnLength;
} PS_ATTRIBUTE, *PPS_ATTRIBUTE;

typedef struct _PS_ATTRIBUTE_LIST{
    SIZE                        TotalLength;
    PS_ATTRIBUTE                Attributes[1];
}PS_ATTRIBUTE_LIST, * PPS_ATTRIBUTE_LIST;

#endif

#endif
