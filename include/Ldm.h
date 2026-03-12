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
    KernelMode = 0,
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

typedef PSTR LOUSTRSAFE_PSTR;
typedef PCSTR LOUSTRSAFE_PCSTR;
typedef PWSTR LOUSTRSAFE_PWSTR;
typedef PCWSTR LOUSTRSAFE_PCWSTR;
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

typedef enum _LOU_PRODUCT_TYPE{
    LouProductAnnyaLou  = 1,
    LouProductLanManLou = 2,
    LouProductServer    = 3,
}LOU_PRODUCT_TYPE, * PLOU_PRODUCT_TYPE;

typedef enum _ALTERNATIVE_ARCHITECTURE_TYPE{
    StandardDesign  = 0,
    NEC98x86        = 1,
    EndAlternitives = 2,
}ALTERNATIVE_ARCHITECTURE_TYPE, * PALTERNATIVE_ARCHITECTURE_TYPE;

typedef 
void 
PHYSICAL_COUNTER_EVENT_BUFFER_OVERFLOW_HANDLER(
    PVOID   EventBuffer,
    SIZE    EntrySize,
    SIZE    EntryCount,
    HANDLE  Owner
);
typedef PHYSICAL_COUNTER_EVENT_BUFFER_OVERFLOW_HANDLER* PPHYSICAL_COUNTER_EVENT_BUFFER_OVERFLOW_HANDLER;

typedef 
void 
PHYSICAL_COUNTER_OVERFLOW_HANDLER(
    ULONGLONG   OverflowBits,
    HANDLE      Owner
);
typedef PHYSICAL_COUNTER_OVERFLOW_HANDLER* PPHYSICAL_COUNTER_OVERFLOW_HANDLER;

typedef PVOID PKTHREAD;

#include <Ldm/Bdcb.h>

typedef 
void
BOOT_DRIVER_CALLBACK_FUNCTION(
    PVOID                   CallbackContext,
    BDCB_CALLBACK_TYPE      CallType,
    PBDCB_IMAGE_INFORMATION ImageInformation
);
typedef BOOT_DRIVER_CALLBACK_FUNCTION* PBOOT_DRIVER_CALLBACK_FUNCTION;

typedef 
void 
DRIVER_REINITIALIZE(
    PDRIVER_OBJECT  DriverObject,
    PVOID           Context,
    ULONG           Count
);
typedef DRIVER_REINITIALIZE* PDRIVER_REINITIALIZE;

typedef ULONGLONG LOGICAL;

typedef 
void
EXPAND_STACK_CALLOUT(
    PVOID   Parameter
);
typedef EXPAND_STACK_CALLOUT* PEXPAND_STACK_CALLOUT;

typedef ULONG KPRIORITY;

typedef UCHAR KDPC_IMPORTANCE;

typedef struct  _PHYSICAL_MEMORY_RANGE{
    PHYSICAL_ADDRESS    BaseAddress;
    LARGE_INTEGER       NumberOfBytes;
}PHYSICAL_MEMORY_RANGE, * PPHYSICAL_MEMORY_RANGE;

typedef 
LOUSTATUS
GET_LOCATION_STRING(
    PVOID           Context,
    PUNICODE_STRING LocationString
);
typedef GET_LOCATION_STRING* PGET_LOCATION_STRING;

typedef PVOID ESILO;
typedef ESILO* PESILO;

typedef 
void
SILO_CONTEXT_CLEANUP_CALLBACK(
    PVOID   SiloContext
);
typedef SILO_CONTEXT_CLEANUP_CALLBACK* PSILO_CONTEXT_CLEANUP_CALLBACK;

typedef PVOID EJOB;
typedef EJOB* PEJOB;

typedef PVOID           SILO_MONITOR;
typedef SILO_MONITOR    PSILO_MONITOR;

typedef 
void
CREATE_THREAD_NOTIFY_ROUTINE(
    HANDLE  ProcessID,
    HANDLE  ThreadID,
    BOOLEAN Create
);
typedef CREATE_THREAD_NOTIFY_ROUTINE* PCREATE_THREAD_NOTIFY_ROUTINE;

typedef struct _IMAGE_INFO{
	union{
		ULONG       Properties;
		struct {
			ULONG   ImageAddressingMode     : 8;
			ULONG   SystemModeImage         : 1;
			ULONG   ImageMappedToAllPids    : 1;
			ULONG   ExtendedInfoPresent     : 1;
			ULONG   MachineTypeMismatch     : 1;
			ULONG   ImageSignatureLevel     : 4;
			ULONG   ImageSignatureType      : 3;
			ULONG   ImagePartialMap         : 1;
			ULONG   Reserved                : 12;
		};
	};
	PVOID           ImageBase;
	ULONG           ImageSelector;
	SIZE_T          ImageSize;
	ULONG           ImageSectionNumber;
} IMAGE_INFO, * PIMAGE_INFO;


typedef 
void 
LOAD_IMAGE_NOTIFY_ROUTINE(
    PUNICODE_STRING FullImageName,
    HANDLE          ProcessID,
    PIMAGE_INFO     ImageInfo
);
typedef void* PLOAD_IMAGE_NOTIFY_ROUTINE;


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