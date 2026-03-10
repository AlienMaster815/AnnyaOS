#ifndef _LDM_H
#define _LDM_H

#include <Ldm/CommonTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OPAQUE_ARRAY_SIZE 1

typedef struct _OFFSETINSTANCEDATAANDLENGTH {
    ULONG OffsetInstanceData;
    ULONG LengthInstanceData;
} OFFSETINSTANCEDATAANDLENGTH, * POFFSETINSTANCEDATAANDLENGTH;

typedef enum {
    KernelMode,
    UserMode,
}KPROCESSOR_MODE;

typedef UCHAR KIRQL;

typedef struct _FILE_INTERNAL_INFORMATION{
    LARGE_INTEGER   IndexNumber;
}FILE_INTERNAL_INFORMATION, * PFILE_INTERNAL_INFORMATION;

typedef struct _PREPARSE_DATA_BUFFER{
    ULONG           ReparseTag;
    USHORT          ReparseDataLength;
    USHORT          Reserved;
    union{
        struct {
            USHORT  SubstituteNameOffset;
            USHORT  SubstituteNameLength;
            USHORT  PrintNameOffset;
            USHORT  PrintNameLength;
            ULONG   Flags;
            WCHAR   PathBuffer[1];
        }SymbolicLinkReparseBuffer;
        struct {
            USHORT  SubstituteNameOffset;
            USHORT  SubstituteNameLength;
            USHORT  PrintNameOffset;
            USHORT  PrintNameLength;
            WCHAR   PathBuffer[1];
        }MountPointReparseBuffer;
        struct{
            UCHAR DataBuffer;
        }GenericReparseBuffer;
    };
}PREPARSE_DATA_BUFFER, * PPREPARSE_DATA_BUFFER;

typedef struct _FILE_TIMESTAMPS{
    LARGE_INTEGER   CreationTime;
    LARGE_INTEGER   LastAccessTime;
    LARGE_INTEGER   LastWriteTime;
    LARGE_INTEGER   ChangeTime;
}FILE_TIMESTAMPS, * PFILE_TIMESTAMPS;

typedef BOOLEAN* PBOOLEAN;

typedef enum _OBJECT_INFORMATION_CLASS{
    ObjectBasicInformation = 0,
    ObjectTypeInformation = 2,
}OBJECT_INFORMATION_CLASS;

typedef enum _MEMORY_INFORMATION_CLASS{
    MemoryBasicInformation = 0,
}MEMORY_INFORMATION_CLASS;

typedef const WCHAR* PCWCH;
typedef const CHAR* PCCH;

typedef enum _VIRTUAL_MEMORY_INFORMATION_CLASS{ 
    VmPrefetchInformation = 0,
    VmPagePriorityInformation,
    VmConfigCallTargetInformation,
}VIRTUAL_MEMORY_INFORMATION_CLASS;

typedef struct _MEMORY_RANGE_ENTRY{
    PVOID   VirtualAddrress;
    SIZE    NumberOfBytes;   
}MEMORY_RANGE_ENTRY, * PMEMORY_RANGE_ENTRY;

typedef const char* PCSZ;

typedef const LPGUID LPCGUID;

typedef enum _EMULATOR_PORT_ACCESS_TYPE{
    Uchar = 0,
    Ushort,
    Ulong,
}EMULATOR_PORT_ACCESS_TYPE, * PEMULATOR_PORT_ACCESS_TYPE;

typedef PSTR NTSTRSAFE_PSTR;
typedef PCSTR NTSTRSAFE_PCSTR;
typedef PWSTR NTSTRSAFE_PWSTR;
typedef PCWSTR NTSTRSAFE_PCWSTR;
typedef const char* PCNZCH;
typedef const wchar_t* PCNZWCH;
typedef PCNZCH STRSAFE_PCNZCH;
typedef PCNZWCH STRSAFE_PCNZWCH;
typedef PCUNZWCH STRSAFE_PCUNZWCH;
typedef HANDLE PEPHANDLE;

typedef struct _ACPI_METHOD_ARGUMENT{
    UINT16      Type;
    UINT16      Length;
    union{
        ULONG   Argument;
        UINT8   Data[OPAQUE_ARRAY_SIZE];
    };
}ACPI_METHOD_ARGUMENT, * PACPI_METHOD_ARGUMENT; 

typedef HANDLE* POHANDLE;

typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

typedef VOID(*PINTERFACE_REFERENCE)(PVOID Context);
typedef VOID(*PINTERFACE_DEREFERENCE)(PVOID Context);

typedef ULONG NODE_REQUIREMENT;


#include <Ldm/Drives.h>

#include <Ldm/Dma.h>

#include <Ldm/miniport.h>

#include <Hal.h>

#include <Ldm/PepFramework.h>

#include <Ldm/Lmilib.h>


#ifdef __cplusplus
}
#endif
#endif