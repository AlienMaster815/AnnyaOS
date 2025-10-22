#ifndef _WINTERNL_H
#define _WINTERNL_H

#include "ntdef.h"
#include "windef.h"
#include "../NtAPI/ntstatus.h"
#include "winnt.h"

typedef const char*     PCSZ;
typedef char*           LPSTR;
typedef short           CSHORT, * PCSHORT;
typedef unsigned long   ULONG; 
typedef long            LONG; 


#ifndef __STRING_DEFINED__
#define __STRING_DEFINED__
typedef struct _STRING{
    USHORT  Length;
    USHORT  MaximumLength;
    LPSTR   Buffer;
}STRING, * PSTRING, *LPSTRING,
    ANSI_STRING, * PANSI_STRING, * LPANSI_STRING,
        OEM_STRING, * POEM_STRING, * LPOEM_STRING;

typedef const STRING* PCANSI_STRING;
typedef const STRING* PCOEM_STRING;
#endif

#ifndef __UNICODE_STRING_DEFINED__
#define __UNICODE_STRING_DEFINED__
typedef struct _UNICODE_STRING{
    USHORT  Length;
    USHORT  MaximumLength;
    LPWSTR  Buffer;
}UNICODE_STRING, * PUNICODE_STRING, * LPUNICODE_STRING;
typedef const UNICODE_STRING* PCUNICODE_STRING;
typedef const UNICODE_STRING CUNICODE_STRING;
#endif

#ifndef _FILETIME_
#define _FILETIME_
typedef struct _FILETIME{
    DWORD   LowDateTime;
    DWORD   HighDateTime;
}FILETIME, * PFILETIME, * LPFILETIME;
#endif

typedef struct _RTL_SYSTEM_TIME{
    WORD    Year;
    WORD    Month;
    WORD    DayOfTheWeek;
    WORD    Day;
    WORD    Hour;
    WORD    Minute;
    WORD    Second;
    WORD    Millisecond;
}RTL_SYSTEM_TIME, * PRTL_SYSTEM_TIME, * LPRTL_SYSTEM_TIME;

typedef struct _RTL_TIME_ZONE_INFORMATION{
    LONG                Bias;
    WCHAR               StandardName[32];
    RTL_SYSTEM_TIME     StandardDate;
    LONG                StandardBias;
    WCHAR               DaylightName[32];
    RTL_SYSTEM_TIME     DaylightDate;
    LONG                DaylightBias;
}RTL_TIME_ZONE_INFORMATION, * PRTL_TIME_ZONE_INFORMATION;

typedef struct _RTL_TIME_DYNAMIC_ZONE_INFORMATION{
    LONG                Bias;
    WCHAR               StandardName[32];
    RTL_SYSTEM_TIME     StandardDate;
    LONG                StandardBias;
    WCHAR               DaylightName[32];
    RTL_SYSTEM_TIME     DaylightDate;
    LONG                DaylightBias;
    WCHAR               TimeZoneKeyName[128];
    BOOL                DynamicDaylightTimeDisabled;
}RTL_TIME_DYNAMIC_ZONE_INFORMATION, * PRTL_TIME_DYNAMIC_ZONE_INFORMATION;

typedef struct _CLIENT_ID{
    HANDLE  UniqueProcess;
    HANDLE  UniqueThread;
}CLIENT_ID, * PCLIENT_ID;

typedef struct _CURDIR{
    UNICODE_STRING  DosPath;
    PVOID           Handle;
}CURDIR, * PCURDIR;

typedef struct _RTL_DRIVE_LETTER_CURDIR{
    USHORT          Flags;
    USHORT          Length;
    ULONG           TimeStamp;
    UNICODE_STRING  DosPath;
}RTL_DRIVE_LETTER_CURDIR, * PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_RELATIVE_NAME{
    UNICODE_STRING  RelativeName;
    HANDLE          ContainerDirectory;
    PVOID           CurDirReference;
}RTL_RELATIVE_NAME, * PRTL_RELATIVE_NAME;

typedef struct _RTL_BITMAP{
    ULONG           SizeOfBitMap;
    PULONG          Buffer;
}RTL_BITMAP, * PRTL_BITMAP;

typedef const RTL_BITMAP* PCRTL_BITMAP;

typedef struct _RTL_BITMAP_RUN{
    ULONG       StartingIndex;
    ULONG       NumberOfBits;
}RTL_BITMAP_RUN, * PRTL_BITMAP_RUN;

typedef const RTL_BITMAP_RUN* PCRTL_BITMAP_RUN;

typedef struct _RTL_USER_PROCESS_PARAMETERS{
    ULONG                       AllocationSize;
    ULONG                       Size;
    ULONG                       Flags;
    ULONG                       DebugFlags;
    ULONG                       ConsoleHandle;
    ULONG                       ConsoleFlags;
    HANDLE                      StdInput;
    HANDLE                      StdOutput;
    HANDLE                      StdError;
    CURDIR                      CurrentDirectory;
    UNICODE_STRING              DllPath;
    UNICODE_STRING              ImagePath;
    UNICODE_STRING              CommandLine;
    LPWSTR                      Enviornment;
    ULONG                       WindowX;
    ULONG                       WindowY;
    ULONG                       WindowXSize;
    ULONG                       WindowYSize;
    ULONG                       WindowXCountChars;
    ULONG                       WindowYCountChars;
    ULONG                       WindowFillAttribute;
    ULONG                       WindowFlags;
    ULONG                       ShowWindow;
    UNICODE_STRING              WindowTitle;
    UNICODE_STRING              Desktop;
    UNICODE_STRING              ShellInfo;
    UNICODE_STRING              RuntimeInfo;
    RTL_DRIVE_LETTER_CURDIR     DriveLetterCurrentDirectory[0x20];
    ULONG_PTR                   EnviornmentSize;
    ULONG_PTR                   EnviornmentVersion;
    PVOID                       PackageDependecyData;
    ULONG                       ProcessGroupID;
    ULONG                       LoaderThreads;
}RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;

#define PROCESS_PARAMETERS_FLAG_NORMALIZED 1

typedef struct _PEB_LDR_DATA{
    ULONG       Length;
    BOOL        Initialized;
    PVOID       SsHandle;
    LIST_ENTRY  InLoadOrderModuleList;
    LIST_ENTRY  InMemoryOrderModuleList;
    LIST_ENTRY  InInitializationOrderModuleList;
    PVOID       EntryInProgress;
    BOOL        ShutDownInProgress;
    HANDLE      ShutDownThreadID;
}PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _GDI_TEB_BATCH{
    ULONG       Offset;
    HANDLE      Hdc;
    ULONG       Buffer[0x136];
}GDI_TEB_BATCH, * PGDI_TEB_BATCH;

struct _ACTIVATION_CONTEXT;

typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME{
    struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME* Previous;
    struct _ACTIVATION_CONTEXT*                 ActivationContext;
    ULONG                                       Flags;
}RTL_ACTIVATION_CONTEXT_STACK_FRAME, * PRTL_ACTIVATION_CONTEXT_STACK_FRAME;

typedef struct _RTL_CALLER_ALLOCATED_ACTIVATION_CONTEXT_STACK_FRAME_EXTENDED{
    SIZE                                    Size;
    ULONG                                   Format;
    RTL_ACTIVATION_CONTEXT_STACK_FRAME      StackFrame;
    PVOID                                   Extra1;
    PVOID                                   Extra2;
    PVOID                                   Extra3;
    PVOID                                   Extra4;
}RTL_CALLER_ALLOCATED_ACTIVATION_CONTEXT_STACK_FRAME_EXTENDED, 
    * PRTL_CALLER_ALLOCATED_ACTIVATION_CONTEXT_STACK_FRAME_EXTENDED;

typedef struct _ACTIVATION_CONTEXT_STACK{
    PRTL_ACTIVATION_CONTEXT_STACK_FRAME     ActiveFrame;
    LIST_ENTRY                              FrameListCache;
    ULONG                                   Flags;
    ULONG                                   NextCookieSequenceNumber;
    ULONG_PTR                               StackID; 
}ACTIVATION_CONTEXT_STACK, * PACTIVATION_CONTEXT_STACK;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT{
    ULONG               Flags;
    const char*         FrameName;
}TEB_ACTIVE_FRAME_CONTEXT, * PTEB_ACTIVE_FRAME_CONTEXT;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT_EX{
    TEB_ACTIVE_FRAME_CONTEXT        BasicContext;
    const char*                     SourceLocation;
}TEB_ACTIVE_FRAME_CONTEXT_EX, * PTEB_ACTIVE_FRAME_CONTEXT_EX;

typedef struct _TEB_ACTIVE_FRAME{
    ULONG                           Flags;
    struct _TEB_ACTIVE_FRAME*       Previous;
    PTEB_ACTIVE_FRAME_CONTEXT       Context;
}TEB_ACTIVE_FRAME, * PTEB_ACTIVE_FRAME;

typedef struct _TEB_ACTIVE_FRAME_EX{
    TEB_ACTIVE_FRAME    BasicFrame;
    PVOID               ExtentionIdentifier;
}TEB_ACTIVE_FRAME_EX, * PTEB_ACTIVE_FRAME_EX;

typedef struct _FLS_CALLBACK{
    PVOID                       Undocumented;
    PFLS_CALLBACK_FUNCTION      Callback;
}FLS_CALLBACK, * PFLS_CALLBACK;

typedef struct _FLS_INFO_CHUNK{
    ULONG           Count;
    FLS_CALLBACK    Callbacks[1];
}FLS_INFO_CHUNK, * PFLS_INFO_CHUNK;

typedef struct _GLOBAL_FLS_DATA{
    FLS_INFO_CHUNK      FlsCallbackChunks[8];
    LIST_ENTRY          FlsListHeader;
    ULONG               FlsHighIndex;
}GLOBAL_FLS_DATA, * PGLOBAL_FLS_DATA;

typedef struct _TEB_FLS_DATA{
    LIST_ENTRY      FlsListEntry;
    PVOID*          FlsDataChunks[8];
}TEB_FLS_DATA, * PTEB_FLS_DATA;

typedef struct _CROSS_PROCESS_WORK_ENTRY{
    UINT            Next;
    UINT            Id;
    ULONGLONG       Address;
    ULONGLONG       Size;
    UINT            Args[4];
}CROSS_PROCESS_WORK_ENTRY, * PCROSS_PROCESS_WORK_ENTRY;

typedef union _CROSS_PROCESS_WORK_HDR{
    struct {
        UINT    First;
        UINT    Counter;
    };
    volatile    LONGLONG Hdr;
}CROSS_PROCESS_WORK_HDR, * PCROSS_PROCESS_WORK_HDR;

typedef struct _CROSS_PROCESS_WORK_LIST{
    CROSS_PROCESS_WORK_HDR      FreeList;
    CROSS_PROCESS_WORK_HDR      WorkList;
    ULONGLONG                   Undocumented[4];    
    CROSS_PROCESS_WORK_ENTRY    Entries[1];
}CROSS_PROCESS_WORK_LIST, * PCROSS_PROCESS_WORK_LIST;

typedef enum{
    CrossProcessPreVirtualAlloc    = 0,
    CrossProcessPostVirtualAlloc   = 1,
    CrossProcessPreVirtualFree     = 2,
    CrossProcessPostVirtualFree    = 3,
    CrossProcessPreVirtualProtect  = 4,
    CrossProcessPostVirtualProtect = 5,
    CrossProcessFlushCache         = 6,
    CrossProcessFlushCacheHeavy    = 7,
    CrossProcessMemoryWrite        = 8,
}CROSS_PROCESS_NOTIFICATION;

//347

#endif //_WINTERNL_H