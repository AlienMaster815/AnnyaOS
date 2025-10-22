#ifndef _WINTERNL_H
#define _WINTERNL_H

#include "ntdef.h"
#include "windef.h"
#include "../NtAPI/ntstatus.h"
#include "winnt.h"

typedef const char*     PCSZ;
typedef char*           LPSTR;
typedef short           CSHORT, * PCSHORT;
typedef unsigned int    ULONG; 
typedef int             LONG; 
typedef ULONG_PTR       KAFFINITY, *PKAFFINITY;
typedef PVOID           HMODULE;

#ifndef _LARGE_INTEGERS_
#define _LARGE_INTEGERS_

#if defined(MIDL_PASS)
typedef struct _LARGE_INTEGER {
    LONGLONG QuadPart;
} LARGE_INTEGER;
#else // MIDL_PASS
typedef union _LARGE_INTEGER {
    struct {
        ULONG LowPart;
        LONG HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        ULONG LowPart;
        LONG HighPart;
    } u;
    LONGLONG QuadPart;
} LARGE_INTEGER;
#endif //MIDL_PASS

#if defined(MIDL_PASS)
typedef struct _LARGE_INTEGER {
    LONGLONG QuadPart;
} LARGE_INTEGER;
#else // MIDL_PASS
typedef union _ULARGE_INTEGER {
    struct {
        ULONG LowPart;
        ULONG HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        ULONG LowPart;
        ULONG HighPart;
    } u;
    LONGLONG QuadPart;
} ULARGE_INTEGER;
#endif //MIDL_PASS
#endif

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

#define CROSS_PROCESS_LIST_FLUSH 0x80000000
#define CROSS_PROCESS_LIST_ENTRY(list,pos) ((CROSS_PROCESS_WORK_ENTRY *)((char *)(list) + ((pos) & ~CROSS_PROCESS_LIST_FLUSH)))

struct _ARM64EC_NT_CONTEXT;

typedef struct _CHPE_V2_CPU_AREA_INFO{
    BOOL                            InSimulation;
    BOOL                            InSyscallCallback;
    UINT64                          EmulatorStackBase;
    UINT64                          EmulatorStackLimit;
    struct _ARM64EC_NT_CONTEXT*     Amd64Context;
    ULONG*                          SuspendDoorbell;
    UINT64                          LoadingModuleFlag;
    PVOID                           EmulatorData[4];
    UINT64                          EmulatorDataInline;
}CHPE_V2_CPU_AREA_INFO, * PCHPE_V2_CPU_AREA_INFO;

typedef struct _CHPEV2_PROCESS_INFO{
    ULONG                       Wow64ExecuteFlags;
    USHORT                      NativeMachineType;
    USHORT                      EmulatedMachineType;
    HANDLE                      SectionHandle;
    PCROSS_PROCESS_WORK_LIST    CrossProcessWorkList;
    PVOID                       Undocumented;
}CHPEV2_PROCESS_INFO, * PCHPEV2_PROCESS_INFO;

#define TEB_ACTIVE_FRAME_CONTEXT_FLAG_EXTENDED 0x00000001
#define TEB_ACTIVE_FRAME_FLAG_EXTENDED         0x00000001

typedef NTSTATUS (WINAPI * KERNEL_CALLBACK_FUNCTION)(void *, ULONG);

typedef struct _PEB{
    BOOL                            InheritedAddressSpace;
    BOOL                            ReadImageFileExecOptions;
    BOOL                            BeingDebugged;
    UCHAR                           ImageUsedLargePages             : 1;
    UCHAR                           IsProtectedProcess              : 1;
    UCHAR                           IsImageDynamicallyRelocated     : 1;
    UCHAR                           SkipPatchingUser32Forwarders    : 1;
    UCHAR                           IsPackagedProcess               : 1;
    UCHAR                           IsAppContainer                  : 1;
    UCHAR                           IsProtectedProcessLight         : 1;
    UCHAR                           IsLongPathAwareProcess          : 1;
    HANDLE                          Mutant;
    HMODULE                         ImageBaseAddress;
    PPEB_LDR_DATA                   LoaderData;
    PRTL_USER_PROCESS_PARAMETERS    ProcessParameters;
    PVOID                           SubsystemData;
    HANDLE                          ProcessHeap;
    PRTL_CRITICAL_SECTION           FastPebLock;
    PVOID                           AtlThunkSListPtr;
    PVOID                           IFEOKey;
    ULONG                           ProcessInJob                    : 1;
    ULONG                           ProcessInitializing             : 1;
    ULONG                           ProcessUsingVEH                 : 1;
    ULONG                           ProcessUsingVCH                 : 1;
    ULONG                           ProcessUsingFTH                 : 1;
    ULONG                           ProcessPreviouslyThrottled      : 1;
    ULONG                           ProcessCurrentlyThrottled       : 1;
    ULONG                           ProcessImagesHotPatched         : 1;
    ULONG                           ReservedBits0                   : 24;
    KERNEL_CALLBACK_FUNCTION*       KernelCallbackTable;
    ULONG                           Reserved;
    ULONG                           AtlThunkSListPtr32;
    PVOID                           ApiSetMap;
    ULONG                           TlsExpansionCounter;
    PRTL_BITMAP                     TlsBitmap;                  
    ULONG                           TlsBitmapBits[2];
    PVOID                           ReadOnlySharedMemoryBase;
    PVOID                           SharedData;
    PVOID*                          ReadOnlyStaticServerData;
    PVOID                           AnsiCodePageData;
    PVOID                           OemCodePageData;
    PVOID                           UnicodeCaseTableData;
    ULONG                           NumberOfProcessors;
    ULONG                           NtGlobalFlag;
    LARGE_INTEGER                   CriticalSectionTimeout;
    SIZE_T                          HeapSegmentReserve;
    SIZE_T                          HeapSegmentCommit;
    SIZE_T                          HeapDeCommitTotalFreeThreshold;
    SIZE_T                          HeapDeCommitFreeBlockThreshold;
    ULONG                           NumberOfHeaps;
    ULONG                           MaximumNumberOfHeaps;
    PVOID*                          ProcessHeaps;
    PVOID                           GdiSharedHandleTable;
    PVOID                           ProcessStarterHelper;
    PVOID                           GdiDCAttributeList;
    PVOID                           LoaderLock;
    ULONG                           OSMajorVersion;
    ULONG                           OSMinorVersion;
    ULONG                           OSBuildNumber;
    ULONG                           OSPlatformId;
    ULONG                           ImageSubSystem;
    ULONG                           ImageSubSystemMajorVersion;
    ULONG                           ImageSubSystemMinorVersion;
    KAFFINITY                       ActiveProcessAffinityMask;
#ifndef _WIN32
    ULONG                           GdiHandleBuffer[60];
#else
    ULONG                           GdiHandleBuffer[34];
#endif
    PVOID                           PostProcessInitRoutine;
    PRTL_BITMAP                     TlsExpansionBitmap;
    ULONG                           TlsExpansionBitmapBits[32];
    ULONG                           SessionId;
    ULARGE_INTEGER                  AppCompatFlags;
    ULARGE_INTEGER                  AppCompatFlagsUser;
    PVOID                           ShimData;
    PVOID                           AppCompatInfo;
    UNICODE_STRING                  CSDVersion;
    PVOID                           ActivationContextData;
    PVOID                           ProcessAssemblyStorageMap;
    PVOID                           SystemDefaultActivationData;
    PVOID                           SystemAssemblyStorageMap;
    SIZE_T                          MinimumStackCommit;
    PVOID                           SparePointers[2];
    PVOID                           PatchLoaderData;
    PCHPEV2_PROCESS_INFO            ChpeV2ProcessInfo;
    ULONG                           AppModelFeatureState;
    ULONG                           SpareUlongs[2];
    USHORT                          ActiveCodePage;
    USHORT                          OemCodePage;
    USHORT                          UseCaseMapping;
    USHORT                          UnusedNlsField;
    PVOID                           WerRegistrationData;
    PVOID                           WerShipAssertPtr;
    PVOID                           EcCodeBitMap;
    PVOID                           ImageHeaderHash;
    ULONG                           HeapTracingEnabled          : 1;
    ULONG                           CritSecTracingEnabled       : 1;
    ULONG                           LibLoaderTracingEnabled     : 1;
    ULONG                           SpareTracingBits            : 29;
    ULONGLONG                       CsrServerReadOnlySharedMemoryBase;
    ULONG                           TppWorkerpListLock;
    LIST_ENTRY                      TppWorkerpList;
    PVOID                           WaitOnAddressHashTable[0x80];
    PVOID                           TelemetryCoverageHeader;
    ULONG                           CloudFileFlags;
    ULONG                           CloudFileDiagFlags;
    CHAR                            PlaceholderCompatibilityMode;
    CHAR                            PlaceholderCompatibilityModeReserved[7];
    PVOID                           LeapSecondData;
    ULONG                           LeapSecondFlags;
    ULONG                           NtGlobalFlag2;
}PEB, * PPEB;



typedef struct _TEB{                                                                
    //NT_TIB                          Tib;
    PVOID                           EnvironmentPointer;
    CLIENT_ID                       ClientId;
    PVOID                           ActiveRpcHandle;
    PVOID                           ThreadLocalStoragePointer;
    PPEB                            Peb;
    ULONG                           LastErrorValue;
    ULONG                           CountOfOwnedCriticalSections;
    PVOID                           CsrClientThread;
    PVOID                           Win32ThreadInfo;
    ULONG                           User32Reserved[26];
    ULONG                           UserReserved[5];
    PVOID                           WOW32Reserved;
    ULONG                           CurrentLocale;
    ULONG                           FpSoftwareStatusRegister;
    PVOID                           ReservedForDebuggerInstrumentation[16];
#ifndef _WIN32
    PVOID                           SystemReserved1[30];
#else
    PVOID                           SystemReserved1[26];
#endif
    char                            PlaceholderCompatibilityMode;
    char                            PlaceholderReserved[10];
    DWORD                           ProxiedProcessId;
    ACTIVATION_CONTEXT_STACK        ActivationContextStack;
    UCHAR                           WorkingOnBehalfOfTicket[8];
    LONG                            ExceptionCode;
    ACTIVATION_CONTEXT_STACK*       ActivationContextStackPointer;
    ULONG_PTR                       InstrumentationCallbackSp;
    ULONG_PTR                       InstrumentationCallbackPreviousPc;
    ULONG_PTR                       InstrumentationCallbackPreviousSp;
#ifndef _WIN32
    ULONG                           TxFsContext;
    BOOL                            InstrumentationCallbackDisabled;
    BOOL                            UnalignedLoadStoreExceptions;
#else
    BOOL                            InstrumentationCallbackDisabled;
    BYTE                            SpareBytes1[23];
    ULONG                           TxFsContext;
#endif
    GDI_TEB_BATCH                   GdiTebBatch;
    CLIENT_ID                       RealClientId;
    HANDLE                          GdiCachedProcessHandle;
    ULONG                           GdiClientPID;
    ULONG                           GdiClientTID;
    PVOID                           GdiThreadLocaleInfo;
    ULONG_PTR                       Win32ClientInfo[62];
    PVOID                           glDispatchTable[233];
    PVOID                           glReserved1[29];
    PVOID                           glReserved2;
    PVOID                           glSectionInfo;
    PVOID                           glSection;
    PVOID                           glTable;
    PVOID                           glCurrentRC;
    PVOID                           glContext;
    ULONG                           LastStatusValue;
    UNICODE_STRING                  StaticUnicodeString;
    WCHAR                           StaticUnicodeBuffer[261];
    PVOID                           DeallocationStack;
    PVOID                           TlsSlots[64];
    LIST_ENTRY                      TlsLinks;
    PVOID                           Vdm;
    PVOID                           ReservedForNtRpc;
    PVOID                           DbgSsReserved[2];
    ULONG                           HardErrorMode;
#ifndef _WIN32
    PVOID                           Instrumentation[11];
#else
    PVOID                           Instrumentation[9];
#endif
    GUID                            ActivityId;
    PVOID                           SubProcessTag;
    PVOID                           PerflibData;
    PVOID                           EtwTraceData;
    PVOID                           WinSockData;
    ULONG                           GdiBatchCount;
    ULONG                           IdealProcessorValue;
    ULONG                           GuaranteedStackBytes;
    PVOID                           ReservedForPerf;
    PVOID                           ReservedForOle;
    ULONG                           WaitingOnLoaderLock;
    PVOID                           SavedPriorityState;
    ULONG_PTR                       ReservedForCodeCoverage;
    PVOID                           ThreadPoolData;
    PVOID*                          TlsExpansionSlots;
#ifndef _WIN32
    union {
        PVOID                       DeallocationBStore;
        CHPE_V2_CPU_AREA_INFO*      ChpeV2CpuAreaInfo;
    }                               DUMMYUNIONNAME;
    PVOID                           BStoreLimit;
#endif
    ULONG                           MuiGeneration;
    ULONG                           IsImpersonating;
    PVOID                           NlsCache;
    PVOID                           ShimData;
    ULONG                           HeapVirtualAffinity;
    PVOID                           CurrentTransactionHandle;
    TEB_ACTIVE_FRAME*               ActiveFrame;
    TEB_FLS_DATA*                   FlsSlots;
    PVOID                           PreferredLanguages;
    PVOID                           UserPrefLanguages;
    PVOID                           MergedPrefLanguages;
    ULONG                           MuiImpersonation;
    USHORT                          CrossTebFlags;
    union {
        USHORT                      SameTebFlags;
        struct {
            USHORT                  SafeThunkCall           : 1;
            USHORT                  InDebugPrint            : 1;
            USHORT                  HasFiberData            : 1;
            USHORT                  SkipThreadAttach        : 1;
            USHORT                  WerInShipAssertCode     : 1;
            USHORT                  RanProcessInit          : 1;
            USHORT                  ClonedThread            : 1;
            USHORT                  SuppressDebugMsg        : 1;
            USHORT                  DisableUserStackWalk    : 1;
            USHORT                  RtlExceptionAttached    : 1;
            USHORT                  InitialThread           : 1;
            USHORT                  SessionAware            : 1;
            USHORT                  LoadOwner               : 1;
            USHORT                  LoaderWorker            : 1;
            USHORT                  SkipLoaderInit          : 1;
            USHORT                  SkipFileAPIBrokering    : 1;
        };
    };
    PVOID                           TxnScopeEnterCallback;
    PVOID                           TxnScopeExitCallback;
    PVOID                           TxnScopeContext;
    ULONG                           LockCount;
    LONG                            WowTebOffset;
    PVOID                           ResourceRetValue;
    PVOID                           ReservedForWdf;
    ULONGLONG                       ReservedForCrt;
    GUID                            EffectiveContainerId;
} TEB, *PTEB;

//647

#endif //_WINTERNL_H