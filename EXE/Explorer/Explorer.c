#include <windows.h>
/*#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>



#ifndef _EXPLORER_API
#define _EXPLORER_API

#define ANNYA_BACKGROUND_WINDOW_CLASS "AnnyaOSDesktop"
#define ANNYA_BACKGROUND_TASKBAR_CLASS "AnnyaOSTaskbar"

#define EXPERR_NO_MONITORS -1
#define EXPERR_EINVAL -2
#endif


#ifndef _LIST_HEADER_API
#define _LIST_HEADER_API
typedef struct _LIST_HEADER {
    struct _LIST_HEADER*    NextHeader;
    struct _LIST_HEADER*    LastHeader;
}LIST_HEADER, * PLIST_HEADER;
#endif

#ifndef _VIRTUAL_SCREEN_API
#define _VIRTUAL_SCREEN_API
typedef struct _VIRTUAL_SCEEN_TRACKER {
    LIST_HEADER     Peers;
    HMONITOR        Monitor;
    HDC             DeviceContext;
    LPARAM          MonitorEnumProcData;
    RECT            FullDimentions;
    RECT            WorkDimentions;
    HWND            DesktopWindow;
    HWND            TaskbarWindow;
}VIRTUAL_SCEEN_TRACKER, * PVIRTUAL_SCEEN_TRACKER;

typedef struct _MONITOR_INITIALIZATION_PARAMETERS {
    HINSTANCE       Instance;
}MONITOR_INITIALIZATION_PARAMETERS, * PMONITOR_INITIALIZATION_PARAMETERS;

#endif

static int TotalVirtualScreens = 0x00;
static int GlobalOriginX = 0x00;
static int GlobalOriginY = 0x00;
static int GlobalScreenWidth = 0x00;
static int GlobalScreenHeight = 0x00;
static VIRTUAL_SCEEN_TRACKER ScreenList = {0};
static PVIRTUAL_SCEEN_TRACKER PrimaryMonitor = 0x00;

static PVIRTUAL_SCEEN_TRACKER ExpAllocVScreenTracker(){
    PVIRTUAL_SCEEN_TRACKER TmpTracker = &ScreenList;
    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PVIRTUAL_SCEEN_TRACKER)TmpTracker->Peers.NextHeader;
    }
    TmpTracker->Peers.NextHeader = (PLIST_HEADER)malloc(sizeof(VIRTUAL_SCEEN_TRACKER));
    if(!TmpTracker->Peers.NextHeader){
        return NULL;
    }
    memset(TmpTracker->Peers.NextHeader, 0, sizeof(VIRTUAL_SCEEN_TRACKER));
    return (PVIRTUAL_SCEEN_TRACKER)TmpTracker->Peers.NextHeader;
}

static void ExpFreeVScreenTracker(PVIRTUAL_SCEEN_TRACKER Tracker){
    PVIRTUAL_SCEEN_TRACKER TmpTracker = &ScreenList;
    PVIRTUAL_SCEEN_TRACKER Follower = TmpTracker;
    while(TmpTracker->Peers.NextHeader){
        Follower = TmpTracker;
        TmpTracker = (PVIRTUAL_SCEEN_TRACKER)TmpTracker->Peers.NextHeader;
        if((UINT64)TmpTracker == (UINT64)Tracker){
            Follower->Peers.NextHeader = TmpTracker->Peers.NextHeader;
            free(TmpTracker);
            return;
        }
    }
}

static void ExpFreeAllVScreenTrackers(){
    PVIRTUAL_SCEEN_TRACKER TmpTracker = (PVIRTUAL_SCEEN_TRACKER)ScreenList.Peers.NextHeader;
    PVIRTUAL_SCEEN_TRACKER Follower;
    while(TmpTracker){
        Follower = TmpTracker;
        TmpTracker = (PVIRTUAL_SCEEN_TRACKER)TmpTracker->Peers.NextHeader;
        free(Follower);
    }
}

int ExpForEachMonitor(
    int (*Function)(PVIRTUAL_SCEEN_TRACKER,PVOID),
    PVOID Param
){
    if(!Function){
        return EXPERR_EINVAL;
    }
    int Status;
    PVIRTUAL_SCEEN_TRACKER TmpTracker = (PVIRTUAL_SCEEN_TRACKER)&ScreenList;
    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PVIRTUAL_SCEEN_TRACKER)TmpTracker->Peers.NextHeader;
        Status = Function(TmpTracker, Param);
        if(Status){
            return Status;
        }
    }
    return 0x00;
}

void ExpDebugPrint(char* Str, ...){
    CHAR Buffer[1024] = {0};
    va_list Args;
    va_start(Args, Str);
    vsnprintf(Buffer, sizeof(Buffer), Str, Args);
    va_end(Args);
    MessageBoxA(
        NULL,
        Buffer,
        MB_OK, MB_ICONINFORMATION
    );
}

BOOL CALLBACK StartupMonitorEnumerationProcedure(
    HMONITOR    Monitor,
    HDC         DeviceContext,
    LPRECT      Dimentions,
    LPARAM      Data
){

    MONITORINFO Mi = {0};
    PVIRTUAL_SCEEN_TRACKER NewTracker = ExpAllocVScreenTracker();
    
    if(!NewTracker){
        return FALSE;
    }

    Mi.cbSize = sizeof(Mi);

    GetMonitorInfo(Monitor, &Mi);

    NewTracker->Monitor = Monitor;
    NewTracker->DeviceContext = DeviceContext;
    NewTracker->MonitorEnumProcData = Data;

    NewTracker->FullDimentions = Mi.rcMonitor;
    NewTracker->WorkDimentions = Mi.rcWork;

    if(Mi.dwFlags & MONITORINFOF_PRIMARY){
        PrimaryMonitor = NewTracker;
    }

    return TRUE;
}

LRESULT CALLBACK BackgroundWindowProcedure(
    HWND    BackgroundWindow,
    UINT    Message,
    WPARAM  WideParameter,
    LPARAM  LongParameter
){

    switch(Message){
        case WM_PAINT:{
            SetWindowPos(
                BackgroundWindow, 
                HWND_BOTTOM,
                0,0,0,0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE
            );
            PAINTSTRUCT Ps;
            HDC Hdc = BeginPaint(BackgroundWindow, &Ps);

            RECT Rc;
            GetClientRect(BackgroundWindow, &Rc);
            
            HBRUSH Brush = CreateSolidBrush(RGB(0, 128, 128));
            FillRect(Hdc, &Rc, Brush);
            DeleteObject(Brush);
            
            EndPaint(BackgroundWindow, &Ps);
            return 0;
        }
        default:
            return DefWindowProc(BackgroundWindow, Message, WideParameter, LongParameter); 

    }
}

LRESULT CALLBACK TaskbarWindowProcedure(
    HWND    TaskbarWindow,
    UINT    Message,
    WPARAM  WideParameter,
    LPARAM  LongParameter
){

    switch(Message){
        case WM_PAINT:{
            PAINTSTRUCT Ps;
            HDC Hdc = BeginPaint(TaskbarWindow, &Ps);

            RECT Rc;
            GetClientRect(TaskbarWindow, &Rc);
            
            HBRUSH Brush = CreateSolidBrush(RGB(128, 128, 128));
            FillRect(Hdc, &Rc, Brush);
            DeleteObject(Brush);
            
            EndPaint(TaskbarWindow, &Ps);
            return 0;
        }
        default:
            return DefWindowProc(TaskbarWindow, Message, WideParameter, LongParameter); 

    }
}

int ExpInitializeMonitor(PVIRTUAL_SCEEN_TRACKER Tracker, PVOID Params){

    PMONITOR_INITIALIZATION_PARAMETERS InitParams = (PMONITOR_INITIALIZATION_PARAMETERS)Params;
    Tracker->DesktopWindow = CreateWindowExA(
        WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW,
        ANNYA_BACKGROUND_WINDOW_CLASS,
        NULL,
        WS_POPUP,
        Tracker->FullDimentions.left, Tracker->FullDimentions.top,
        Tracker->FullDimentions.right - Tracker->FullDimentions.left, Tracker->FullDimentions.bottom - Tracker->FullDimentions.top,
        NULL,
        NULL,
        InitParams->Instance,
        NULL
    );

    ShowWindow(
        Tracker->DesktopWindow,
        SW_SHOW
    );
    


    //Tracker->TaskbarWindow = CreateWindowExA(

    //);
    

    return 0;
}*/

int WINAPI WinMain(
    HINSTANCE   Instance,
    HINSTANCE   Previous,
    LPSTR       CommandLine,
    int         CmdShow
) {

    MSG Message;

    //GlobalOriginX = GetSystemMetrics(SM_XVIRTUALSCREEN);
    //GlobalOriginY = GetSystemMetrics(SM_YVIRTUALSCREEN);
    //GlobalScreenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN); 
    //GlobalScreenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    //TotalVirtualScreens = GetSystemMetrics(SM_CMONITORS);

    //if(!TotalVirtualScreens){
    //    return EXPERR_NO_MONITORS;
    //}

    //EnumDisplayMonitors(
    //    NULL,
    //    NULL,
    //    StartupMonitorEnumerationProcedure,
    //    0
    //);

    //WNDCLASSA DesktopClass = {0};
    //DesktopClass.lpfnWndProc = BackgroundWindowProcedure;
    //DesktopClass.hInstance = Instance;
    //DesktopClass.lpszClassName = ANNYA_BACKGROUND_WINDOW_CLASS;

    //WNDCLASSA TaskbarClass = {0};
    //TaskbarClass.lpfnWndProc = TaskbarWindowProcedure;
    //TaskbarClass.hInstance = Instance;
    //TaskbarClass.lpszClassName = ANNYA_BACKGROUND_TASKBAR_CLASS;

    //RegisterClassA(&DesktopClass);

    //RegisterClassA(&TaskbarClass);

    //MONITOR_INITIALIZATION_PARAMETERS InitParams = {
    //    .Instance = Instance,
    //};

    //ExpForEachMonitor(
    //    ExpInitializeMonitor,
    //    &InitParams
    //);

    //ExpInitializeMonitor((PVIRTUAL_SCEEN_TRACKER)ScreenList.Peers.NextHeader, &InitParams);

    //ExpDebugPrint("System Initialized Successfully");



    while(GetMessage(&Message, NULL, 0, 0)){
        DispatchMessage(&Message);
    }

    //ExpFreeAllVScreenTrackers();

    return 0x00;
}
