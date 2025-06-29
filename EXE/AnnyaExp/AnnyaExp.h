#ifndef _ANNYA_EXP_H
#define _ANNYA_EXP_H
#include <Annya.h>
#include <USRSPC/DRSD.h>

//the following is copied data from User32.Dll:Awm.h
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

//End of copy


__declspec(dllimport) AWM_STATUS InitializeAwmUserSubsystem();

#endif