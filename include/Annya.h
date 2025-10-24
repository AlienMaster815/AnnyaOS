#ifndef _ANNYA_API_H
#define _ANNYA_API_H

#define WINAPI __stdcall

#define _USER_MODE_CODE_

#include <WinAPI/Win32/winternl.h>

#include <cstdint.h>
#include <stdalign.h>


#define GET_ALIGNMENT(x) (alignof(x))
#define FORCE_ALIGNMENT(alignment) __attribute__((aligned(alignment)))

#define ROUND_UP(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_UP64(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_DOWN64(value, multiple) \
    ((value) / (multiple) * (multiple))

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

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
#include <WinAPI/Win32/winnls.h>

typedef unsigned int UINT;
typedef unsigned short USHORT, * PUSHORT;

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

typedef struct _ListHeader{
    struct _ListHeader* NextHeader;
    struct _ListHeader* LastHeader;
}ListHeader, * PListHeader;

struct _AWM_CLIP_TREE;

#ifndef LONG
//typedef int LONG;
#endif

typedef LONG    LRESULT;
typedef PVOID   WNDPROC;

typedef LRESULT (*ANNYA_WINDOW_CALLBACK)(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam);

struct _WINDOW_HANDLE;

typedef struct _CHILD_WINDOW_TRACKER{
    ListHeader              Peers;
    struct _WINDOW_HANDLE*  Child;
}CHILD_WINDOW_TRACKER, * PCHILD_WINDOW_TRACKER;

typedef struct _WINDOW_HANDLE{
    PWINDOW_CHARECTERISTICS Charecteristics;
    INT64                   X;
    INT64                   Y;
    UINT32                  Width;
    UINT32                  Height;
    UINT32*                 WindowBuffer;    
    string                  WindowName;
    SIZE                    PlaneCount;
    struct _DRSD_CLIP**     MainWindow;
    struct _WINDOW_HANDLE*  ParentWindow;
    mutex_t                 ChildTrackerMutex;
    CHILD_WINDOW_TRACKER    Children;
    struct _AWM_CLIP_TREE*  ClipTreeHandle;
    DWORD                   WindowStyle;
    BOOL                    Visable;
    BOOL                    Mirrored;
    INTEGER                 WindowVisability;
    mutex_t                 CallbackMutex;
    SIZE                    CallbackCount;
    ANNYA_WINDOW_CALLBACK*  WindowCallbacks;
    string                  WindowClass;
    HWND                    WinApiHandleChecksum; //used for winAPI applications and to check the indegrity of the AnnyaHandle
    PVOID                   Parameter;
    HINSTANCE               Instance;
    HMENU                   Menu;
    DWORD                   ExtendedWindowStyle;
    UINT64                  ThreadID;
}WINDOW_HANDLE, * PWINDOW_HANDLE;

#define TRAY_WINDOW             "AnnyaShell_TrayWnd"
#define DEKSTOP_BACKGROUND      "AnnyaDekstopBackground"
#define CANVAS_BUTTON           "AnnyaCanvasButton"
#define ANNYA_GENERIC_WINDOW    "AnnyaOSShellWindow"

#define RTL_CRITICAL_SECTION_FLAG_NO_DEBUG_INFORMATION     0x01000000
#define RTL_ACTIVATION_CONTEXT_STACK_FRAME_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN             0x02000000
#define RTL_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION    0x04000000
#define RTL_CRITICAL_SECTION_FLAG_RESOURCE_TYPE            0x08000000
#define RTL_CRITICAL_SECTION_FLAG_FORCE_DEBUG_INFORMATION  0x10000000
#define RTL_CRITICAL_SECTION_ALL_FLAG_MASK                 0xFF000000
#define RTL_CRITICAL_SECTION_FLAG_RESERVED_FLAGS           0xE0000000

#define RTL_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION_DYNAMIC_SPIN (RTL_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION | RTL_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN)

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



//Pivate Data for Shell/Annya API Windows
typedef struct _ANNYA_DESKTOP_SETUP_PACKET{
    ANNYA_WINDOW_CALLBACK WindowCallback;
}ANNYA_DESKTOP_SETUP_PACKET, * PANNYA_DESKTOP_SETUP_PACKET;

#ifndef _USER_32_

//Copy Changes of the following to the Annya.h system from Awm.h

__declspec(dllimport)
BOOL 
UpdateWindow(
    HWND WindowHandle
);

__declspec(dllimport)
BOOL
ShowWindow(
    HWND        WindowHandle,
    INTEGER     nCmdShow
);

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
    int         X,
    int         Y,
    int         Width,
    int         Height,
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

__declspec(dllimport)
void 
LouDrsdClipToClip(
    struct _DRSD_CLIP* BackClip,
    struct _DRSD_CLIP* FrontClip,
    INT64 X,
    INT64 Y
);

__declspec(dllimport)
void 
LouUpdateClipLocation(struct _DRSD_CLIP* Clip, INT64 DeltaX, INT64 DeltaY);

__declspec(dllimport)
int strcmp(const char* str1, const char* str2);

__declspec(dllimport)
void LouUpdateShadowClipSubState(
    void* Clip, 
    size_t X, size_t Y, 
    size_t Width, size_t Height
);

__declspec(dllimport)
void LouYeildExecution();

__declspec(dllimport)
void LouUpdateClipSubState(
    void* Clip,
    size_t X, size_t Y, 
    size_t Width, size_t Height
);

__declspec(dllimport)
void LouGetSystemUpdate(PSYSTEM_STATE_STACK StateStack);

__declspec(dllimport)
void 
LouUpdateShadowClipState(
    void* Clip
);

__declspec(dllimport)
void LouGenericFreeHeap(void* Heap, void* Address);

__declspec(dllimport)
void*
LouDrsdGetPlaneInformation(size_t* CountHandle);

__declspec(dllimport)
LOUSTATUS
LouDrsdSetPlaneInformation(void* Context);

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
LouDrsdSyncScreen();

__declspec(dllimport)
void LouUpdateClipState(void* Clip);

__declspec(dllimport)
void* LouDrsdCreateClip(
    INT64 X, INT64 Y, 
    INT64 Width, INT64 Height, 
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
#ifndef _LOUDLL_

__declspec(dllimport)
void* AnnyaNtGetProcessHeap();

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

#ifndef _KERNEL32_
__declspec(dllimport)
void* GetProcessHeap();
#endif

__declspec(dllimport)
uint16_t NtGetProcessorCount();

__declspec(dllimport)
void* RtlAllocateHeapEx(
    PVOID       HeapHandle,
    uint64_t    HeapAllocationFlags,
    size_t      HeapSize,
    size_t      Alignment
);

__declspec(dllimport)
void* 
RtlAllocateHeap(
    PVOID       HeapHandle,
    uint64_t    HeapAllocationFlags,
    size_t      HeapSize
);

#endif
#endif

#ifdef __cplusplus    
}
#endif

typedef void* HINSTANCE;

#include <stdint.h>
#include <Dispatching.h>

#define LouKeMemoryBarrier() asm volatile("mfence" : : : "memory")
#define LouKePauseMemoryBarrier() asm volatile("pause" : : : "memory")

#ifndef _ANNYA_DLL_CALL_REASONS
#define _ANNYA_DLL_CALL_REASONS
    #define DLL_PROCESS_ATTACH 1
    #define DLL_PROCESS_DETACH 0
    #define DLL_THREAD_ATTACH  2
    #define DLL_THREAD_DETACH  3
#endif

//Windows Styles according to WINAPI Reference Manual
//https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles
#define WS_BORDER	            0x00800000L	//The window has a thin-line border
#define WS_CAPTION	            0x00C00000L	//The window has a title bar (includes the WS_BORDER style).
#define WS_CHILD	            0x40000000L	//The window is a child window. A window with this style cannot have a menu bar. This style cannot be used with the WS_POPUP style.
#define WS_CHILDWINDOW	        0x40000000L	//Same as the WS_CHILD style.
#define WS_CLIPCHILDREN	        0x02000000L	//Excludes the area occupied by child windows when drawing occurs within the parent window. This style is used when creating the parent window.
#define WS_CLIPSIBLINGS	        0x04000000L	//Clips child windows relative to each other; that is, when a particular child window receives a WM_PAINT message, the WS_CLIPSIBLINGS style clips all other overlapping child windows out of the region of the child window to be updated. If WS_CLIPSIBLINGS is not specified and child windows overlap, it is possible, when drawing within the client area of a child window, to draw within the client area of a neighboring child window.
#define WS_DISABLED	            0x08000000L	//The window is initially disabled. A disabled window cannot receive input from the user. To change this after a window has been created, use the EnableWindow function.
#define WS_DLGFRAME	            0x00400000L	//The window has a border of a style typically used with dialog boxes. A window with this style cannot have a title bar.
#define WS_GROUP	            0x00020000L	//The window is the first control of a group of controls. The group consists of this first control and all controls defined after it, up to the next control with the WS_GROUP style. The first control in each group usually has the WS_TABSTOP style so that the user can move from group to group. The user can subsequently change the keyboard focus from one control in the group to the next control in the group by using the direction keys.
//You can turn this style on and off to change dialog box navigation. To change this style after a window has been created, use the SetWindowLong function.
#define WS_HSCROLL	            0x00100000L	//The window has a horizontal scroll bar.
#define WS_ICONIC	            0x20000000L	//The window is initially minimized. Same as the WS_MINIMIZE style.
#define WS_MAXIMIZE	            0x01000000L	//The window is initially maximized.
#define WS_MAXIMIZEBOX	        0x00010000L	//The window has a maximize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified.
#define WS_MINIMIZE	            0x20000000L	//The window is initially minimized. Same as the WS_ICONIC style.
#define WS_MINIMIZEBOX	        0x00020000L	//The window has a minimize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified.
#define WS_OVERLAPPED	        0x00000000L	//The window is an overlapped window. An overlapped window has a title bar and a border. Same as the WS_TILED style.
#define WS_OVERLAPPEDWINDOW	    (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)	//The window is an overlapped window. Same as the WS_TILEDWINDOW style.
#define WS_POPUP	            0x80000000L	//The window is a pop-up window. This style cannot be used with the WS_CHILD style.
#define WS_POPUPWINDOW	        (WS_POPUP | WS_BORDER | WS_SYSMENU)	//The window is a pop-up window. The WS_CAPTION and WS_POPUPWINDOW styles must be combined to make the window menu visible.
#define WS_SIZEBOX	            0x00040000L	//The window has a sizing border. Same as the WS_THICKFRAME style.
#define WS_SYSMENU	            0x00080000L	//The window has a window menu on its title bar. The WS_CAPTION style must also be specified.
#define WS_TABSTOP	            0x00010000L	//The window is a control that can receive the keyboard focus when the user presses the TAB key. Pressing the TAB key changes the keyboard focus to the next control with the WS_TABSTOP style.
//You can turn this style on and off to change dialog box navigation. To change this style after a window has been created, use the SetWindowLong function. For user-created windows and modeless dialogs to work with tab stops, alter the message loop to call the IsDialogMessage function.
#define WS_THICKFRAME	        0x00040000L	//The window has a sizing border. Same as the WS_SIZEBOX style.
#define WS_TILED	            0x00000000L	//The window is an overlapped window. An overlapped window has a title bar and a border. Same as the WS_OVERLAPPED style.
#define WS_TILEDWINDOW	        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)	//The window is an overlapped window. Same as the WS_OVERLAPPEDWINDOW style.
#define WS_VISIBLE	            0x10000000L	//The window is initially visible.
//This style can be turned on and off by using the ShowWindow or SetWindowPos function.
#define WS_VSCROLL	            0x00200000L	//The window has a vertical scroll bar.

#define SCREEN_HEIGHT   UINT32_MAX
#define SCREEN_WIDTH    UINT32_MAX

#define SW_HIDE             0	//Hides the window and activates another window.
#define SW_SHOWNORMAL       1
#define SW_NORMAL           1	//Activates and displays a window. If the window is minimized, maximized, or arranged, the system restores it to its original size and position. An application should specify this flag when displaying the window for the first time.
#define SW_SHOWMINIMIZED    2	//Activates the window and displays it as a minimized window.
#define SW_SHOWMAXIMIZED    3
#define SW_MAXIMIZE         3	//Activates the window and displays it as a maximized window.
#define SW_SHOWNOACTIVATE   4	//Displays a window in its most recent size and position. This value is similar to SW_SHOWNORMAL, except that the window is not activated.
#define SW_SHOW             5	//Activates the window and displays it in its current size and position.
#define SW_MINIMIZE         6	//Minimizes the specified window and activates the next top-level window in the Z order.
#define SW_SHOWMINNOACTIVE  7	//Displays the window as a minimized window. This value is similar to SW_SHOWMINIMIZED, except the window is not activated.
#define SW_SHOWNA           8	//Displays the window in its current size and position. This value is similar to SW_SHOW, except that the window is not activated.
#define SW_RESTORE          9	//Activates and displays the window. If the window is minimized, maximized, or arranged, the system restores it to its original size and position. An application should specify this flag when restoring a minimized window.
#define SW_SHOWDEFAULT      10	//Sets the show state based on the SW_ value specified in the STARTUPINFO structure passed to the CreateProcess function by the program that started the application.
#define SW_FORCEMINIMIZE    11	//Minimizes a window, even if the thread that owns the window is not responding. This flag should only be used when minimizing windows from a different thread.
//endof Private Data

#define WM_LBUTTON_DOWN 0x0201
#define WM_LBUTTON_UP   0x0202
#define MK_LBUTTON      0x0001

#define CLIP_WIDTH      UINT64_MAX
#define CLIP_HEIGHT     UINT64_MAX

//https://learn.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles
#define WS_EX_ACCEPTFILES 0x00000010L //The window accepts drag-drop files.
#define WS_EX_APPWINDOW 0x00040000L //Forces a top-level window onto the taskbar when the window is visible.
#define WS_EX_CLIENTEDGE 0x00000200L //The window has a border with a sunken edge.
#define WS_EX_COMPOSITED 0x02000000L //Paints all descendants of a window in bottom-to-top painting order using double-buffering. Bottom-to-top painting order allows a descendent window to have translucency (alpha) and transparency (color-key) effects, but only if the descendent window also has the WS_EX_TRANSPARENT bit set. Double-buffering allows the window and its descendents to be painted without flicker. This cannot be used if the window has a class style of CS_OWNDC, CS_CLASSDC, or CS_PARENTDC. Windows 2000: This style is not supported.
#define WS_EX_CONTEXTHELP 0x00000400L //The title bar of the window includes a question mark. When the user clicks the question mark, the cursor changes to a question mark with a pointer. If the user then clicks a child window, the child receives a WM_HELP message. The child window should pass the message to the parent window procedure, which should call the WinHelp function using the HELP_WM_HELP command. The Help application displays a pop-up window that typically contains help for the child window. WS_EX_CONTEXTHELP //cannot be used with the WS_MAXIMIZEBOX or WS_MINIMIZEBOX styles.
#define WS_EX_CONTROLPARENT 0x00010000L //The window itself contains child windows that should take part in dialog box navigation. If this style is specified, the dialog manager recurses into children of this window when performing navigation operations such as handling the TAB key, an arrow key, or a keyboard mnemonic.
#define WS_EX_DLGMODALFRAME 0x00000001L //The window has a double border; the window can, optionally, be created with a title bar by specifying the WS_CAPTION style in the dwStyle parameter.
#define WS_EX_LAYERED 0x00080000L //The window is a layered window. This style cannot be used if the window has a class style of either CS_OWNDC or CS_CLASSDC. Windows 8: The WS_EX_LAYERED style is supported for top-level windows and child windows. Previous Windows versions support WS_EX_LAYERED only for top-level windows.
#define WS_EX_LAYOUTRTL 0x00400000L //If the shell language is Hebrew, Arabic, or another language that supports reading order alignment, the horizontal origin of the window is on the right edge. Increasing horizontal values advance to the left.
#define WS_EX_LEFT 0x00000000L //The window has generic left-aligned properties. This is the default.
#define WS_EX_LEFTSCROLLBAR 0x00004000L //If the shell language is Hebrew, Arabic, or another language that supports reading order alignment, the vertical scroll bar (if present) is to the left of the client area. For other languages, the style is ignored.
#define WS_EX_LTRREADING 0x00000000L //The window text is displayed using left-to-right reading-order properties. This is the default.
#define WS_EX_MDICHILD 0x00000040L //The window is a MDI child window.
#define WS_EX_NOACTIVATE 0x08000000L
//A top-level window created with this style does not become the foreground window when the user clicks it. The system does not bring this window to the foreground when the user minimizes or closes the foreground window.
//The window should not be activated through programmatic access or via keyboard navigation by accessible technology, such as Narrator.
//To activate the window, use the SetActiveWindow or SetForegroundWindow function.
//The window does not appear on the taskbar by default. To force the window to appear on the taskbar, use the WS_EX_APPWINDOW style.
#define WS_EX_NOINHERITLAYOUT 0x00100000L //The window does not pass its window layout to its child windows.
#define WS_EX_NOPARENTNOTIFY 0x00000004L //The child window created with this style does not send the WM_PARENTNOTIFY message to its parent window when it is created or destroyed.
#define WS_EX_NOREDIRECTIONBITMAP 0x00200000L //The window does not render to a redirection surface. This is for windows that do not have visible content or that use mechanisms other than surfaces to provide their visual.
#define WS_EX_OVERLAPPEDWINDOW  (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE) //The window is an overlapped window.
#define WS_EX_PALETTEWINDOW (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST) //The window is palette window, which is a modeless dialog box that presents an array of commands.
#define WS_EX_RIGHT 0x00001000L //The window has generic "right-aligned" properties. This depends on the window class. This style has an effect only if the shell language is Hebrew, Arabic, or another language that supports reading-order alignment; otherwise, the style is ignored. Using the WS_EX_RIGHT style for static or edit controls has the same effect as using the SS_RIGHT or ES_RIGHT style, respectively. Using this style with button controls has the same effect as using BS_RIGHT and BS_RIGHTBUTTON styles.
#define WS_EX_RIGHTSCROLLBAR 0x00000000L //The vertical scroll bar (if present) is to the right of the client area. This is the default.
#define WS_EX_RTLREADING 0x00002000L //If the shell language is Hebrew, Arabic, or another language that supports reading-order alignment, the window text is displayed using right-to-left reading-order properties. For other languages, the style is ignored.
#define WS_EX_STATICEDGE 0x00020000L //The window has a three-dimensional border style intended to be used for items that do not accept user input.
#define WS_EX_TOOLWINDOW 0x00000080L //The window is intended to be used as a floating toolbar. A tool window has a title bar that is shorter than a normal title bar, and the window title is drawn using a smaller font. A tool window does not appear in the taskbar or in the dialog that appears when the user presses ALT+TAB. If a tool window has a system menu, its icon is not displayed on the title bar. However, you can display the system menu by right-clicking or by typing ALT+SPACE.
#define WS_EX_TOPMOST 0x00000008L //The window should be placed above all non-topmost windows and should stay above them, even when the window is deactivated. To add or remove this style, use the SetWindowPos function.
#define WS_EX_TRANSPARENT 0x00000020L //The window should not be painted until siblings beneath the window (that were created by the same thread) have been painted. The window appears transparent because the bits of underlying sibling windows have already been painted. To achieve transparency without these restrictions, use the SetWindowRgn function.
#define WS_EX_WINDOWEDGE 0x00000100L


#define WINAPI __stdcall

typedef int errno_t;
#define EINVAL      22
#define ERANGE      34
#define STRUNCATE   80

#define _TRUNCATE ((size_t)-1)

#include "../DLL/LouDLLs/GDI32/AnnyaGdi.h"
#include "../DLL/LouDLLs/User32/AnnyaUser.h"

#ifdef IS_X86_64

#else

#endif
#endif
