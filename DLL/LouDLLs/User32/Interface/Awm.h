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

typedef HWND HMENU; 

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
#define ANNYA_GENERIC_WINDOW    "AnnyaOSShellWindow"

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

#define AWM_BASE                0xFFFF0000
#define AWM_POSITION_WINDOW     (AWM_BASE + 0)


USER32_API
LOUSTATUS 
AwmHookCalbackToWindow(
    HWND Window, 
    ANNYA_WINDOW_CALLBACK Callback
);

LRESULT WindowModificationWndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam);

void 
AwmWindowDrawLine(
    PWINDOW_HANDLE  WindowHandle,
    INT64           X1,
    INT64           Y1,
    INT64           X2,
    INT64           Y2,
    UINT8           R,
    UINT8           G,
    UINT8           B,
    UINT8           A
);

void AwmInitializeWindowStyle(
    PWINDOW_HANDLE  Window,
    DWORD           ExStyle, 
    DWORD           Style
);

void AwmSignalEndofGrabEvent();
PWINDOW_HANDLE AwmCheckIfWindowIsGrabbed();
void AwmMoveWindow(PWINDOW_HANDLE Window, INT64* DeltaX, INT64* DeltaY);

PDRSD_CLIP CreateClipFromString(
    string Str, 
    PVOID FaceHandle, 
    SIZE CharecterWidth, 
    SIZE CharecterHeight, 
    PDRSD_CLIP BackgroundClip, 
    INT64 BackX, 
    INT64 BackY
);

PDRSD_CLIP CreateClipFromStringEx(
    string      Str, 
    PVOID       FaceHandle, 
    SIZE        CharecterWidth, 
    SIZE        CharecterHeight, 
    SIZE        SpaceWidth,
    SIZE        SpaceHeight,
    PDRSD_CLIP  BackgroundClip, 
    INT64       BackX, 
    INT64       BackY
);

PVOID AnnyaGetFont(string FontPath);

USER32_API
BOOL
ShowWindow(
    HWND        WindowHandle,
    INTEGER     nCmdShow
);

USER32_API
BOOL 
UpdateWindow(
    HWND WindowHandle
);

static inline bool IsAreaInsidePlane(
    INT64 X1, INT64 Y1, INT64 Width1, INT64 Height1,
    INT64 X2, INT64 Y2, INT64 Width2, INT64 Height2
){
    if(
        (X1 >= X2) && (Y1 >= Y2) && ((Width1 + X1) <= (X2 + Width2)) && ((Height1 + Y1) <= (Y2 + Height2))
    ){
        return true;
    }
    return false;
}




void AwmInitializeWindowToTracker(
    PWINDOW_HANDLE Parrent,
    PWINDOW_HANDLE Child
);

void AwmUpdateLocationArea(
    INT64 X, INT64 Y,
    INT64 Width, INT64 Height
);

void AwmUpdateSubWindowToScreen(PWINDOW_HANDLE Window, INT64 X, INT64 Y, INT64 Width, INT64 Height);
void AwmRedrawArea(PWINDOW_HANDLE Window, INT64 X, INT64 Y, INT64 Width, INT64 Height);

#endif