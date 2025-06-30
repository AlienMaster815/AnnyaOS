#ifndef _ANNYA_API_H
#define _ANNYA_API_H

#define _USER_MODE_CODE_

#include <stdalign.h>
#define GET_ALIGNMENT(x) (alignof(x))

#define ROUND_UP(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_UP64(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_DOWN64(value, multiple) \
    ((value) / (multiple) * (multiple))

#define LOUSTATUS uint32_t

//#include "USRSPC/API/WinAPItypes.h"
#include "kernel/SystemCalls.h"
#include <stdint.h>
#include <stdbool.h>
#include <USRSPC/UserThreads.h>

typedef char* string;


#ifdef __cplusplus
extern "C"{
#endif


typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef void* PTHREAD;

#define LOU_EXPORT __declspec(dllexport)

#include <WinAPI/NtAPI/ntstatus.h>
#include <WinAPI/Win32/WinAPIStdType.h>
#include <FileHandleing/Bitmap.h>
#include <windows.h>
#include "WinAPI/Win32/wmsdk/wmfsdk/wmfsdk.h"



typedef void*       HWND;
typedef void*       HMENU;
typedef uint16_t    MSG;
typedef void*       LOUDISPMSG;

typedef void* HANDLE;
typedef void* HMODULE;

#ifndef _TIME_T_
#define _TIME_T_
typedef struct _TIME_T{
    uint8_t Month;
    uint8_t Day;
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
    uint16_t MilliSeconds;
}TIME_T, * PTIME_T;
#endif

typedef void (__cdecl *FunctionVector)(void);

typedef struct  _ListHeader{
    struct _ListHeader* LastHeader;
    struct _ListHeader* NextHeader;
}ListHeader, * PListHeader;

typedef struct _MSVC_CRITICAL_SECTION_DEBUG_DATA{
    uint16_t                                SectionType;
    uint16_t                                CBTI;
    struct _MSVC_CRITICAL_SECTION*          MsvcCriticalSection;
    ListHeader                              ProcessLockList;
    uint32_t                                LockListEntryCount;
    uint32_t                                ContentionCount;
    uint32_t                                SpareData[2];
}MSVC_CRITICAL_SECTION_DEBUG_DATA, * PMSVC_CRITICAL_SECTION_DEBUG_DATA;

typedef struct _MSVC_CRITICAL_SECTION{
    PMSVC_CRITICAL_SECTION_DEBUG_DATA       DebuggingInfo;
    long                                    LockCount;
    long                                    RecusionCount;
    HANDLE                                  ThreadWithPossesion;
    HANDLE                                  Semaphore;
    uint32_t                                SpinCount;
}MSVC_CRITICAL_SECTION, * PMSVC_CRITICAL_SECTION;

#define MSVC_CRITICAL_SECTION_FLAG_NO_DEBUG_INFORMATION     0x01000000
#define MSVC_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN             0x02000000
#define MSVC_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION    0x04000000
#define MSVC_CRITICAL_SECTION_FLAG_RESOURCE_TYPE            0x08000000
#define MSVC_CRITICAL_SECTION_FLAG_FORCE_DEBUG_INFORMATION  0x10000000
#define MSVC_CRITICAL_SECTION_ALL_FLAG_MASK                 0xFF000000
#define MSVC_CRITICAL_SECTION_FLAG_RESERVED_FLAGS           0xE0000000

#define MSVC_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION_DYNAMIC_SPIN (MSVC_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION | MSVC_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN)

#define HEAP_NO_SERIALIZE               0x00000001
#define HEAP_GROWABLE                   0x00000002
#define HEAP_GENERATE_EXCEPTIONS        0x00000004
#define HEAP_ZERO_MEMORY                0x00000008
#define HEAP_REALLOC_IN_PLACE_ONLY      0x00000010
#define HEAP_TAIL_CHECKING_ENABLED      0x00000020
#define HEAP_FREE_CHECKING_ENABLED      0x00000040
#define HEAP_DISABLE_COALESCE_ON_FREE   0x00000080
#define HEAP_CREATE_ALIGN_16            0x00010000
#define HEAP_CREATE_ENABLE_TRACING      0x00020000
#define HEAP_CREATE_ENABLE_EXECUTE      0x00040000

typedef struct _WIN_API_SECUTIY_ATTRIBUTES{
    uint32_t    Length;
    void*       SecurityDescriptor;
    bool        HandleIsInherited;
}WIN_API_SECUTIY_ATTRIBUTES, * PWIN_API_SECUTIY_ATTRIBUTES;

typedef struct _WIN_API_STARTUP_INFOA{
    uint32_t    StructureSize; // = 0x40;
    string      Reserved;
    string      Desktop;
    string      Title;
    //the following is currently 
    //implemented in the kernel
    //as uint16 because i havent
    //heard of a screen bigger 
    //than 0xFFFF pixels
    uint32_t    windowX;
    uint32_t    WindowY;
    uint32_t    WindowXSize;
    uint32_t    WindowYSize;
    //endof uint16_t kernel implementation
    uint32_t    WindowXCharecterCount;
    uint32_t    WindowYCharecterCount;
    uint32_t    FillAttribute;
    uint32_t    Flags;
    uint16_t    ShowWindow;
    uint16_t    Reserved2;
    uint8_t*    Reserved3; //aka lpReserved2
    void*       StdInput;
    void*       StdOutput;
    void*       StdError;
}WIN_API_STARTUP_INFOA, * PWIN_API_STARTUP_INFOA;

typedef struct _WIN_API_PROCESS_INFORMATION{
    void*       ProcessHandle;
    void*       ThreadHandle;
    uint32_t    ProcessIdentification;
    uint32_t    ThreadIdentification;
}WIN_API_PROCESS_INFORMATION, * PWIN_API_PROCESS_INFORMATION;


#ifndef _USER_32_

//Copy Changes of the following to the Annya.h system from Awm.h


__declspec(dllexport)
void AwmUpdateState(PSYSTEM_STATE_STACK State);

//__declspec(dllimport)
//uint64_t AnnyaRegisterCallbackProcedure(
//    void* CallbackHandler
//);

__declspec(dllimport)
HWND 
CreateWindowA(
    LPCSTR      ClassName,
    LPCSTR      WindowName,
    DWORD       Style,
    int64_t     X,
    int64_t     Y,
    uint32_t    Width,
    uint32_t    Height,
    HWND        ParrentHandle,
    HMENU       Menu,
    HINSTANCE   Instance,
    LPVOID      Parameter
);

__declspec(dllimport)
void* malloc(size_t BytesNeeded);





__declspec(dllimport)
PWINDHANDLE AnnyaCreateCanvasBuffer(
    int64_t x, int64_t y,
    uint32_t Width, uint32_t Height,
    uintptr_t ParentWindow,
    PWINDOW_CHARECTERISTICS Charecteristics
);


#endif


#ifndef _LOUDLL_


__declspec(dllexport)
void LouUpdateClipSubState(
    void* Clip,
    size_t X, size_t Y, 
    size_t Width, size_t Height
);

__declspec(dllimport)
void LouGetSystemUpdate(PSYSTEM_STATE_STACK StateStack);

__declspec(dllimport)
void 
LouUpdateShadoClipState(
    void* Clip, 
    void* Shadow
);

__declspec(dllimport)
void LouGenericFreeHeap(void* Heap, void* Address);

__declspec(dllimport)
void*
LouDrsdGetPlaneInformation(size_t* CountHandle);

__declspec(dllimport)
void*
LouGlobalUserMallocEx(size_t Size, uint64_t Alignment);

__declspec(dllimport)
void LouGlobalUserFree(void* Addr);

#define LouGlobalUserMallocArray(type, count) (type*)LouGlobalUserMallocEx((ROUND_UP64(sizeof(type), GET_ALIGNMENT(type))) * (count), GET_ALIGNMENT(type))
#define LouGlobalUserMallocType(Type) (Type*)LouGlobalUserMallocEx(sizeof(Type), GET_ALIGNMENT(Type))

__declspec(dllimport)
void*
LouGlobalUserMalloc(size_t Size);

__declspec(dllimport)
void 
LouExitDosMode();

__declspec(dllimport)
int strncmp(const char* str1, const char* str2, size_t n);

__declspec(dllimport)
void
LouCloseFile(
    FILE* ClosingFile
);

__declspec(dllimport)
void*
LouMemCpy(
    void* OutStream,
    void* InStream,
    size_t ByteCount
);

__declspec(dllimport)
LOUSTATUS 
LouSwapEndianess(
    void* InStreamTmp, 
    void* OutStreamTmp, 
    size_t StreamSize
);

__declspec(dllimport)
void* LouGenericAllocateHeapEx(
    void* Heap, 
    size_t AllocationSize,
    size_t Alginment
);

__declspec(dllimport)
void* AnnyaGetLibraryFunctionN(string ModuleName,string FunctionName);

__declspec(dllimport)
void* AnnyaGetLibraryFunctionH(HANDLE ModuleHandle, string FunctionName);

__declspec(dllimport)
void* LouVirtualAllocUser(
    size_t      CommitSize,     //allocated PhysicalMemory
    size_t      ReservedSize,   //AllocatedVirtual
    uint64_t    PageFlags
);

__declspec(dllimport)
FILE*
LouOpenFileA(
    string FileName
);

__declspec(dllimport)
int LouPrint(char* Str, ...);

__declspec(dllimport)
void 
LouDrsdSyncScreen(void* Chain);

__declspec(dllimport)
void LouUpdateClipState(void* Clip);

__declspec(dllimport)
void* LouDrsdCreateClip(
    void* Plane, 
    size_t X, size_t Y, 
    size_t Width, size_t Height, 
    uint8_t R, uint8_t G, uint8_t B, uint8_t A
);

__declspec(dllimport)
PTHREAD AnnyaCreateThread(DWORD (*Function)(PVOID), PVOID FunctionParameters);

__declspec(dllimport)
void AnnyaDestroyThread(PTHREAD Thread);

__declspec(dllimport)
int _vsprintf(
    char* Buffer, 
    size_t BufferCount, 
    const string Format, 
    ...
);

__declspec(dllimport)
void GetRtcTimeData(TIME_T* PTIME);

__declspec(dllimport)
void AnnyaUpdateButton(
    int64_t x, int64_t y,
    uint32_t Width, uint32_t Height,
    PBUTTONHANDLE HBUTTON
);

__declspec(dllimport)
void LouTrashAndDumpProcess();

__declspec(dllimport)
void* LouGenericAllocateHeapEx(void* Heap, size_t AllocationSize, size_t Alignment);

#endif


#ifndef _KERNEL32_

__declspec(dllimport)
void EnterCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

__declspec(dllimport)
NTSTATUS DeleteCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

__declspec(dllimport)
NTSTATUS LeaveCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

__declspec(dllimport)
HMODULE LoadLibraryA(string DllName);

__declspec(dllimport)
HMODULE LoadLibraryW(wchar_t* DllName);

__declspec(dllimport)
HMODULE LoadLibraryExA(
    string DllName, 
    HANDLE File, 
    DWORD Flags
);

__declspec(dllimport)
HMODULE LoadLibraryExyW(
    wchar_t* DllName, 
    HANDLE File, 
    DWORD Flags
);
#endif

#ifndef _KERNELBASE_H

__declspec(dllimport)
void InitializeCriticalSectionEx(
    PMSVC_CRITICAL_SECTION CriticalSection, 
    uint32_t SpinCount, 
    uint32_t Flags
);

#endif

#ifndef NTDLL_H

__declspec(dllimport)
NTSTATUS RtlInitializeCriticalSectionEx(
    PMSVC_CRITICAL_SECTION CriticalSection,
    uint32_t SpinCount,
    uint32_t Flags
);

__declspec(dllimport)
NTSTATUS RtlEnterCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

__declspec(dllimport)
NTSTATUS RtlLeaveCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

__declspec(dllimport)
void* GetProcessHeap();

__declspec(dllimport)
uint16_t NtGetProcessorCount();

__declspec(dllimport)
void* RtlAllocateHeapEx(
    PVOID       HeapHandle,
    uint64_t    HeapAllocationFlags,
    size_t      HeapSize,
    size_t      Alignment
);

#endif

#ifdef __cplusplus    
}
#endif

typedef void* HINSTANCE;

#include <stdint.h>

#ifndef _ANNYA_DLL_CALL_REASONS
#define _ANNYA_DLL_CALL_REASONS
    #define DLL_PROCESS_ATTACH 1
    #define DLL_PROCESS_DETACH 0
    #define DLL_THREAD_ATTACH  2
    #define DLL_THREAD_DETACH  3
#endif



#ifdef IS_X86_64

#else

#endif
#endif
