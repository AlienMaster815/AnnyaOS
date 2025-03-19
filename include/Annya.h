#ifndef _ANNYA_API_H
#define _ANNYA_API_H

#define _USER_MODE_CODE_

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

typedef void*    HWND;
typedef uint16_t MSG;

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
    unsigned long*                          SpinCount;
}MSVC_CRITICAL_SECTION, * PMSVC_CRITICAL_SECTION;

#define MSVC_CRITICAL_SECTION_FLAG_NO_DEBUG_INFORMATION     0x01000000
#define MSVC_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN             0x02000000
#define MSVC_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION    0x04000000
#define MSVC_CRITICAL_SECTION_FLAG_RESOURCE_TYPE            0x08000000
#define MSVC_CRITICAL_SECTION_FLAG_FORCE_DEBUG_INFORMATION  0x10000000
#define MSVC_CRITICAL_SECTION_ALL_FLAG_MASK                 0xFF000000
#define MSVC_CRITICAL_SECTION_FLAG_RESERVED_FLAGS           0xE0000000

#define MSVC_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION_DYNAMIC_SPIN (MSVC_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION | MSVC_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN)

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

//__declspec(dllimport)
//uint64_t AnnyaRegisterCallbackProcedure(
//    void* CallbackHandler
//);

__declspec(dllimport)
void* malloc(size_t BytesNeeded);

__declspec(dllimport)
PBITMAP_HANDLE AnnyaOpenBitmapImage(
    string FileName
);

__declspec(dllimport)
void DrawDesktopBackground(FILE* FileHandle, uint16_t FileType);

__declspec(dllimport)
PBUTTONHANDLE AnnyaCreateButton(
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    uintptr_t ParentWindow,
    uintptr_t Charecteristics
);

__declspec(dllimport)
void AnnyaChangeCanvasBufferColor(
    volatile PWINDHANDLE WindowHandle,
    uint16_t r,
    uint16_t g,
    uint16_t b,
    uint16_t a //not used yet but added for futrue proof
);

__declspec(dllimport)
volatile PWINDHANDLE AnnyaCreateCanvasBuffer(
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    uintptr_t ParentWindow,
    PWINDOW_CHARECTERISTICS Charecteristics
);


#endif


#ifndef _LOUDLL_
__declspec(dllimport)
int LouPrint(char* Str, ...);

__declspec(dllimport)
uint16_t AnnyaGetScreenBufferWidth();

__declspec(dllimport)
uint16_t AnnyaGetScreenBufferHeight();

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
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    PBUTTONHANDLE HBUTTON
);

#endif


#ifndef _KERNEL32_

__declspec(dllimport)
void DeleteCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

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
