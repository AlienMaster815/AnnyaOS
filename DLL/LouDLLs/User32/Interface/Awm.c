#include "Awm.h"

typedef int FT_Error;
typedef void* FT_Library;

USER32_API
BOOL 
UpdateWindow(
    HWND WindowHandle
);

static HANDLE MousePng = 0x00;
static HMODULE CODECShModule = 0;
static HMODULE FREETYPEModule = 0;
static HANDLE (*AnnyaOpenPngA)(string);
static LOUSTATUS (*InitializePNGHandleing)();
static HMODULE Msvcrt = 0;

static bool LeftMouseDown = false;
static bool RightMouseDown = false;

static PDRSD_CLIP* TaskBars = 0;
static HANDLE StartButtonPng = 0x00;
static PDRSD_CLIP* GenericButtonClips = 0;
static PAWM_CLIP_TREE GenericButtonTree = 0;
static HANDLE (*AnnyaOpenBmpA)(string);

static HINSTANCE AwmInstance = 0x00;

static bool InterfaceDualClick = false;

static PWINDOW_HANDLE LastInstance = 0x00; 

//Globals
HANDLE BackgroundImage = 0x00;
HANDLE (*AnnyaPaintClipWithBmp)(HANDLE, HANDLE, size_t, size_t, size_t, size_t) = 0x00;
HANDLE (*AnnyaCreateClipFromPng)(void*, HANDLE);

//192 dark greay
//198 ligt grey

static AWM_WINDOW_TRACKER_ENTRY AwmMasterTracker = {0};
static mutex_t AwmMasterTrackerMutex = {0};
AWM_PLANE_TRACKER PlaneTracker = {0};
static mutex_t AwmPlaneTrackerMutex = {0};
static HWND TaskbarWindow = 0x00;
PDRSD_CLIP* MouseClips = 0x00;
static HWND StartButton = 0x00;
static HWND FileExplorerButon = 0x00;
static HANDLE FolderPng = 0x00;
static HMENU StartMenu = 0x00;
static bool StartButtonDown = false;

int64_t DesktopCurrentX = 0;
int64_t DesktopCurrentY = 0;
int64_t DesktopCurrentWidth = 0;
int64_t DesktopCurrentHeight = 0;

static HANDLE XButtonPng = 0x00;
PDRSD_CLIP* XButtonClips = 0x00;

static DWORD (*AnnyaExplorerFileManager)(PVOID);

void InitializeFreeType();
void InitializePlaneTracker(HINSTANCE hInstance);
void AwmUpdateWindowToScreen(PWINDOW_HANDLE Window);

USER32_API
BOOL
ShowWindow(
    HWND        WindowHandle,
    INTEGER     nCmdShow
){
    PWINDOW_HANDLE Window = (PWINDOW_HANDLE)WindowHandle;
    if(nCmdShow & SW_SHOW){
        Window->Visable = true;
        Window->WindowVisability = nCmdShow;
        return true;
    }

    return false;
}

USER32_API
BOOL 
UpdateWindow(
    HWND WindowHandle
){
    PWINDOW_HANDLE Window = (PWINDOW_HANDLE)WindowHandle;
    
    if(Window->Visable){
        AwmUpdateWindowToScreen(Window);
        return true;    
    }

    return false;
}

static void InitializeDependencies(){
    LOUSTATUS Status;
    LouPrint("InitializeDependencies()\n");

    Msvcrt = LoadLibraryA("C:/ANNYA/SYSTEM64/MSVCRT.DLL");

    LouPrint("Loading CODECS.DLL\n");

    CODECShModule = LoadLibraryA("C:/ANNYA/SYSTEM64/CODECS.DLL");

    if(!CODECShModule){
        LouPrint("CODECS.DLL Could Not Be Found\n");
        while(1);
    }

    LouPrint("Loading FREETYPE.DLL\n");

    FREETYPEModule = LoadLibraryA("C:/ANNYA/FREETYPE.DLL");
    if(!FREETYPEModule){
        LouPrint("FREETYPE.DLL Could Not Be Loaded\n");
        while(1);
    }

    InitializePNGHandleing = AnnyaGetLibraryFunctionN("CODECS.DLL", "InitializePNGHandleing");
    Status = InitializePNGHandleing();  
    if(Status != STATUS_SUCCESS){
        LouPrint("Critical Error Initializig CODECS.DLL\n");
        while(1);
    }

    InitializeFreeType();

    AnnyaOpenPngA = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaOpenPngA");
    AnnyaCreateClipFromPng = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaCreateClipFromPng");
    AnnyaOpenBmpA = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaOpenBmpA");
    AnnyaPaintClipWithBmp = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaPaintClipWithBmp");

    MousePng = AnnyaOpenPngA("C:/ANNYA/MOUSE.PNG");
    FolderPng = AnnyaOpenPngA("C:/ANNYA/FOLDER.PNG");
    StartButtonPng = AnnyaOpenPngA("C:/ANNYA/START.PNG");
    BackgroundImage = AnnyaOpenBmpA("C:/ANNYA/PROFILES/DEFAULT/BG/ANNYA.BMP");
    XButtonPng = AnnyaOpenPngA("C:/ANNYA/XBUTTON.PNG");
    LouPrint("Initiailizing FreeType\n");

    AnnyaExplorerFileManager = AnnyaGetLibraryFunctionN("ANNYAEXP.EXE", "AnnyaExplorerFileManager");
    LouPrint("AnnyaExplorerFileManager()%h\n", AnnyaExplorerFileManager);

    LouPrint("InitializeDependencies() STATUS_SUCCESS\n");

}

static void UpdateMouseClip(int64_t X, int64_t Y){

}

static INT64 gMouseX = 0, gMouseY = 0;

void AwmHandleStartButtonEvent(PWINDOW_HANDLE Handle, bool Click){

}


void AwmHandelFileExplorerEvent(PWINDOW_HANDLE Handle, bool Click){

}

void AwmMoveWindow(PWINDOW_HANDLE Window, INT64* pDeltaX, INT64* pDeltaY){
    
}

static 
void 
MouseEventHandler(
    PLOUSINE_USER_SHARED_MESSAGE MessageHandle
){
    /*PLOUSINE_MOUSE_EVENT_MESSAGE MouseEvent = &MessageHandle->MouseEvent;
    
    INT64 DeltaX = MouseEvent->X;
    INT64 DeltaY = MouseEvent->Y;

    BOOL RightClick = MouseEvent->RightClick;
    BOOL LeftClick  = MouseEvent->LeftClick;

    MouseEvent->X = 0;
    MouseEvent->Y = 0;
    MouseEvent->LeftClick = 0;
    MouseEvent->RightClick = 0;

    if((gMouseX + DeltaX) < DesktopCurrentX){
        DeltaX = -gMouseX;
    }else if((gMouseX + DeltaX) > (DesktopCurrentX + DesktopCurrentWidth)){
        DeltaX = (DesktopCurrentX + DesktopCurrentWidth) - gMouseX;
    }
    if((gMouseY + DeltaY) < DesktopCurrentY){
        DeltaY = -gMouseY;
    }else if((gMouseY + DeltaY) > (DesktopCurrentY + DesktopCurrentHeight)){
        DeltaY = (DesktopCurrentY + DesktopCurrentHeight) - gMouseY;
    }

    //LouPrint("X:%d, Y:%d\n", gMouseX, gMouseY);

    PWINDOW_HANDLE GrabbedWindow = AwmCheckIfWindowIsGrabbed();
    if(GrabbedWindow){
        AwmMoveWindow(GrabbedWindow, &DeltaX, &DeltaY);
    }

    gMouseY += DeltaY;
    gMouseX += DeltaX;

    UpdateMouseClip(gMouseX, gMouseY);

    if(RightClick && !RightMouseDown){
        InterfaceDualClick = false;
        RightMouseDown = true;
        PWINDOW_HANDLE WinHandle = AwmFindWindowAtPoint(gMouseX, gMouseY);
        if(WinHandle != StartButton){
            AwmHandleStartButtonEvent(StartButton, false);
        }
        if(WinHandle){
            if(WinHandle->WindowName){
            
            }
        }else{

        }
    }else if(!RightClick && RightMouseDown){
        InterfaceDualClick = false;

        RightMouseDown = false;
    }
    if(LeftClick && (!LeftMouseDown)){
        LeftMouseDown = true;
        PWINDOW_HANDLE WinHandle = AwmFindWindowAtPoint(gMouseX, gMouseY);
        if(LastInstance == WinHandle){
            InterfaceDualClick = true;
        }else {
            InterfaceDualClick = false;
        }
        LastInstance = WinHandle;
        if(WinHandle != StartButton){
            AwmHandleStartButtonEvent(StartButton, false);
        }
        if(WinHandle){
            if(WinHandle->WindowName){
                PDRSD_CLIP TmpClip = FindClip(gMouseX, gMouseY);
                uint16_t XRelative = (gMouseX - TmpClip->X);
                uint16_t YRelative = (gMouseY - TmpClip->Y);
                MutexLock(&WinHandle->CallbackMutex);
                for(size_t i = 0 ; i < WinHandle->CallbackCount; i++){
                    if(i){
                        WinHandle->WindowCallbacks[i](&WinHandle->WindowCallbacks[i-1], WinHandle, WM_LBUTTON_DOWN,  (void*)(uintptr_t)MK_LBUTTON,  (void*)(uintptr_t)((uint32_t)XRelative | (uint32_t)(YRelative << 16)));
                    }else{
                        WinHandle->WindowCallbacks[i](0x00, WinHandle, WM_LBUTTON_DOWN, (void*)(uintptr_t)MK_LBUTTON, (void*)(uintptr_t)((uint32_t)XRelative | (uint32_t)(YRelative << 16)));
                    }
                }
                MutexUnlock(&WinHandle->CallbackMutex);
            }
            else return;
            LouPrint("WINDOW CLICKED:%s\n", WinHandle->WindowName);
        }
        
    }else if(!LeftClick && LeftMouseDown){
        PWINDOW_HANDLE GrabbedWindow = AwmCheckIfWindowIsGrabbed();
        if(GrabbedWindow){
            AwmSignalEndofGrabEvent();    
        }
        LeftMouseDown = false;
        PWINDOW_HANDLE WinHandle = AwmFindWindowAtPoint(gMouseX, gMouseY);
        if(LastInstance == WinHandle){
            InterfaceDualClick = true;
        }else {
            InterfaceDualClick = false;
        }
        LastInstance = WinHandle;
        if(WinHandle && WinHandle->WindowName){
            PDRSD_CLIP TmpClip = FindClip(gMouseX, gMouseY);
            uint16_t XRelative = (gMouseX - TmpClip->X);
            uint16_t YRelative = (gMouseY - TmpClip->Y);
            MutexLock(&WinHandle->CallbackMutex);
            for(size_t i = 0 ; i < WinHandle->CallbackCount; i++){
                if(i){
                    WinHandle->WindowCallbacks[i](&WinHandle->WindowCallbacks[i-1], WinHandle, WM_LBUTTON_UP,  (void*)(uintptr_t)MK_LBUTTON,  (void*)(uintptr_t)((uint32_t)XRelative | (uint32_t)(YRelative << 16)));
                }else{
                    WinHandle->WindowCallbacks[i](0x00, WinHandle, WM_LBUTTON_UP, (void*)(uintptr_t)MK_LBUTTON, (void*)(uintptr_t)((uint32_t)XRelative | (uint32_t)(YRelative << 16)));
                }
            }
            MutexUnlock(&WinHandle->CallbackMutex);
        }
    }*/
}


USER32_API
AWM_STATUS 
InitializeAwmUserSubsystem(
    HINSTANCE                       hInstance,
    PANNYA_DESKTOP_SETUP_PACKET     InterfaceSetup
){
    LouPrint("InitializeAwmUserSubsystem()\n");
    AwmInstance = hInstance;
    InitializeDependencies();

    PlaneTracker.PlaneInformation = (PDRSD_PLANE_QUERY_INFORMATION)LouDrsdGetPlaneInformation(&PlaneTracker.PlaneCount);
    InitializePlaneTracker(hInstance);

    

    /*

    LouPrint("Allocation Finished\n");

    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){
        XButtonClips[i] = AnnyaCreateClipFromPng((void*)PlaneTracker.PlaneInformation[i].Plane, XButtonPng); 
        MouseClips[i] = AnnyaCreateClipFromPng((void*)PlaneTracker.PlaneInformation[i].Plane, MousePng);
        LouUpdateShadowClipState((void*)MouseClips[i]);
        LouDrsdSyncScreen((void*)MouseClips[i]->ChainOwner);

    }

    TaskbarWindow = CreateWindowA(
        TRAY_WINDOW,
        "TaskTray",
        WS_VISIBLE | WS_DISABLED,
        0,0, 0, 0,
        0x00, 0x00, hInstance, 0x00 
    );
    
    ShowWindow(TaskbarWindow, SW_SHOW);

    UpdateWindow(TaskbarWindow);

    ANNYA_CANVAS_BUTTON_PARAM TmpButtonData = {
        0,
    };

    TmpButtonData.CanvasDataId  = PNG;
    TmpButtonData.CanvasData    = StartButtonPng;

    StartButton = CreateWindowA(
        CANVAS_BUTTON,
        "StartButton",
        WS_VISIBLE | WS_CHILD,
        1,
        DesktopCurrentHeight - 33,
        0,0, //height and width ignored
        TaskbarWindow,
        0x00,
        hInstance,
        &TmpButtonData
    );

    ShowWindow(StartButton, SW_SHOW);

    UpdateWindow(StartButton);

    TmpButtonData.CanvasDataId  = PNG;
    TmpButtonData.CanvasData    = FolderPng;

    FileExplorerButon = CreateWindowA(
        CANVAS_BUTTON,
        "FileExplorer",
        WS_VISIBLE | WS_CHILD,
        68,
        DesktopCurrentHeight - 31,
        0,0, //height and width ignored
        TaskbarWindow,
        0x00,
        hInstance,
        &TmpButtonData
    );

    ShowWindow(FileExplorerButon, SW_SHOW);

    UpdateWindow(FileExplorerButon); 

    LouRegisterMouseHandler(&MouseEventHandler, MOUSE_EVENT_TYPE);*/

    LouPrint("InitializeAwmUserSubsystem() STATUS_SUCCESS\n");
}



