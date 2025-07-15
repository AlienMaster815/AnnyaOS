#ifndef _ANNYAS_WINDOW_MANAGEMENT_H
#define _ANNYAS_WINDOW_MANAGEMENT_H
#include "../User32.h"
#include <USRSPC/DRSD.h>

//Copy Changes of the following to the AnnyaExp.h system from Awm.h

typedef enum {
    AWM_OK = 0,
    AWM_ERROR = -1,
    AWM_FATAL = -2,
}AWM_STATUS;

typedef enum {
    AWM_WINDOW_UPDTAE = 0,
    AWM_MANGER_RESET = 1,
    AWM_INTERFACE_CHANGE = 1,
}AWM_CALL_REASON;

union _AWM_CALLBACK_DATA; 
struct _WINDOW_HANDLE;



typedef struct _DRSD_PLANE_QUERY_INFORMATION{
    uint64_t            Plane;
    uint64_t            Chain;
    size_t              X;
    size_t              Y;
    size_t              Width;
    size_t              Height;
}DRSD_PLANE_QUERY_INFORMATION, * PDRSD_PLANE_QUERY_INFORMATION;


typedef struct _AWM_CLIP_TREE{
    ListHeader  CurrentPlane;
    ListHeader  SubPlane;
    PDRSD_CLIP  Clip;
    void (*UpdateClipSubState)(void* Clip, size_t X, size_t Y, size_t Width, size_t Height);
}AWM_CLIP_TREE, * PAWM_CLIP_TREE;


typedef struct _AWM_PLANE_TRACKER{
    PDRSD_PLANE_QUERY_INFORMATION   PlaneInformation;
    SIZE                            PlaneCount;
}AWM_PLANE_TRACKER, * PAWM_PLANE_TRACKER;



typedef struct _WINDOW_HANDLE{
    PWINDOW_CHARECTERISTICS Charecteristics;
    SIZE                    PlaneCount;
    struct _DRSD_CLIP**     MainWindow;
    struct _WINDOW_HANDLE*  ParentWindow;
    struct _WINDOW_HANDLE*  Children;
    PAWM_CLIP_TREE          ClipTreeHandle;
    DWORD                   WindowStyle;
    BOOL                    Visable;
    INTEGER                 WindowVisability;
    mutex_t                 CallbackMutex;
    SIZE                    CallbackCount;
    ANNYA_WINDOW_CALLBACK*  WindowCallbacks;
    HWND                    WinApiHandleChecksum; //used for winAPI applications and to check the indegrity of the AnnyaHandle
}WINDOW_HANDLE, * PWINDOW_HANDLE;

typedef struct _AWM_WINDOW_TRACKER_ENTRY{
    ListHeader      Peers;
    PWINDOW_HANDLE  WindowHandle;
}AWM_WINDOW_TRACKER_ENTRY, * PAWM_WINDOW_TRACKER_ENTRY;


typedef struct _AWM_WINDOW_UPDATE_DATA{
    PWINDOW_HANDLE          WindowHandle;
    int64_t                 NewX;
    int64_t                 NewY;
    uint32_t                NewWidth;
    uint32_t                NewHeight;
}AWM_WINDOW_UPDATE_DATA, * PAWM_WINDOW_UPDATE_DATA;

typedef struct _AWM_INTERFACE_CHANGE_DATA{
    struct _DRSD_PLANE*     Plane;
    bool                    MirrorPlane;
    int64_t                 NewX;
    int64_t                 NewY;
    uint32_t                NewWidth;
    uint32_t                NewHeight;
}AWM_INTERFACE_CHANGE_DATA, * PAWM_INTERFACE_CHANGE_DATA;

typedef union _AWM_CALLBACK_DATA{
    AWM_WINDOW_UPDATE_DATA      WindowUpdateData;
    AWM_INTERFACE_CHANGE_DATA   InterfaceChangeData;
}AWM_CALLBACK_DATA, *PAWM_CALLBACK_DATA;

//endof Copy

//any updates in this region must have exports to the other Dlls From User32

USER32_API 
AWM_STATUS 
InitializeAwmUserSubsystem(
    HINSTANCE                       hInstance,
    PANNYA_DESKTOP_SETUP_PACKET     InterfaceSetup
);

USER32_API
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

size_t AwmGetImageCenteredX(size_t ImageWidth, size_t ScreenHeight, size_t Scale);
size_t AwmGetImageCenteredY(size_t ImageHeight, size_t ScreenHeight, size_t Scale);
void AwmGetImageScaleingCentered(
    size_t ImageWidth, size_t ImageHeight, 
    size_t ScreenHeight, size_t ScreenWidth,
    size_t* XScaling, size_t* YScaling
);

#define CreateWindow(Class, WindowName, Style, X, Y, Width, Height, Parrent, Menu, Instance, Param) CreateWindowA(Class, WindowName, Style, X, Y, Width, Height, Parrent, Menu, Instance, Param)

//endof Export Copy

//the following is private AWM data

#define TRAY_WINDOW             "AnnyaShell_TrayWnd"
#define DEKSTOP_BACKGROUND      "AnnyaDekstopBackground"
#define CANVAS_BUTTON           "AnnyaCanvasButton"

typedef struct _ANNYA_CANVAS_BUTTON_PARAM{
    CODEC_HANDLE_IMAGE_SUBTYPE      CanvasDataId;
    HANDLE                          CanvasData;
}ANNYA_CANVAS_BUTTON_PARAM, * PANNYA_CANVAS_BUTTON_PARAM;

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


USER32_API
LOUSTATUS 
AwmHookCalbackToWindow(
    HWND Window, 
    ANNYA_WINDOW_CALLBACK Callback
);

LRESULT WindowModificationWndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam);



#endif