#ifndef _ANNYAS_WINDOW_MANAGEMENT_H
#define _ANNYAS_WINDOW_MANAGEMENT_H
#include "User32.h"
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

typedef AWM_STATUS(*WINDOW_CALLBACK)(struct _WINDOW_HANDLE*, AWM_CALL_REASON ,union _AWM_CALLBACK_DATA*) ; 

typedef struct _WINDOW_HANDLE{
    PWINDOW_CHARECTERISTICS Charecteristics;
    struct _DRSD_CLIP*      MainWindow;
    struct _WINDOW_HANDLE*  ParentWindow;
    struct _WINDOW_HANDLE*  Children;
    WINDOW_CALLBACK         WindowCallback;
    HWND                    WinApiHandleChecksum; //used for winAPI applications and to check the indegrity of the AnnyaHandle
}WINDOW_HANDLE, * PWINDOW_HANDLE;

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

USER32_API AWM_STATUS InitializeAwmUserSubsystem();

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

#define CreateWindow(Class, WindowName, Style, X, Y, Width, Height, Parrent, Menu, Instance, Param) CreateWindowA(Class, WindowName, Style, X, Y, Width, Height, Parrent, Menu, Instance, Param)

//endof Export Copy

//the following is private AWM data



//endof Private Data
#endif