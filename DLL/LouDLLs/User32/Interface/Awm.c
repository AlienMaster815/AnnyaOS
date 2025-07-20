#include "Awm.h"

static PDRSD_CLIP* PlaneBackgrounds = 0x00;
static HANDLE MousePng = 0x00;
static HMODULE CODECShModule = 0;
static HMODULE FREETYPEModule = 0;
static HANDLE (*AnnyaOpenPngA)(string);
static LOUSTATUS (*InitializePNGHandleing)();
static HMODULE Msvcrt = 0;
static int64_t MouseX = 0;
static int64_t MouseY = 0;

static PDRSD_CLIP* TaskBars = 0;
static HANDLE StartButtonPng = 0x00;
static PDRSD_CLIP* GenericButtonClips = 0;
static PAWM_CLIP_TREE GenericButtonTree = 0;
static HANDLE (*AnnyaOpenBmpA)(string);

//Globals
HANDLE BackgroundImage = 0x00;
HANDLE (*AnnyaPaintClipWithBmp)(HANDLE, HANDLE, size_t, size_t, size_t, size_t) = 0x00;
HANDLE (*AnnyaCreateClipFromPng)(void*, HANDLE);

//192 dark greay
//198 ligt grey

static AWM_WINDOW_TRACKER_ENTRY AwmMasterTracker = {0};
static mutex_t AwmMasterTrackerMutex = {0};
static AWM_PLANE_TRACKER PlaneTracker = {0};
static mutex_t AwmPlaneTrackerMutex = {0};
static HWND BackgroundWindow = 0x00;
static HWND TaskbarWindow = 0x00;
static PDRSD_CLIP* MouseClips = 0x00;
static HWND StartButton = 0x00;
static HWND FileExplorerButon = 0x00;
static HANDLE FolderPng = 0x00;


static int64_t DesktopCurrentX = 0;
static int64_t DesktopCurrentY = 0;
int64_t DesktopCurrentWidth = 0;
int64_t DesktopCurrentHeight = 0;



SIZE AwmGetPlaneCount(){
    return PlaneTracker.PlaneCount;
}

PDRSD_PLANE_QUERY_INFORMATION AwmGetPlaneInformation(){
    return PlaneTracker.PlaneInformation;
}

PAWM_CLIP_TREE FindEnclosingClip(PAWM_CLIP_TREE Tree, PDRSD_CLIP InnerClip) {
    PAWM_CLIP_TREE Best = 0x00;

    while (Tree) {
        PDRSD_CLIP Clip = Tree->Clip;
        if (
            (Clip->X <= InnerClip->X) &&
            (Clip->Y <= InnerClip->Y) &&
            ((Clip->X + Clip->Width) >= (InnerClip->X + InnerClip->Width)) &&
            ((Clip->Y + Clip->Height) >= (InnerClip->Y + InnerClip->Height))
        ) {
            PAWM_CLIP_TREE ChildMatch = NULL;
            if (Tree->SubPlane.NextHeader) {
                ChildMatch = FindEnclosingClip((PAWM_CLIP_TREE)Tree->SubPlane.NextHeader, InnerClip);
            }
            Best = ChildMatch ? ChildMatch : Tree;
        }
        Tree = (PAWM_CLIP_TREE)Tree->CurrentPlane.NextHeader;
    }
    return Best;
}


PAWM_CLIP_TREE FindClipAtPoint(PAWM_CLIP_TREE Tree, INT64 X, INT64 Y){
    PAWM_CLIP_TREE Best = 0x00;    
    while (Tree) {
        PDRSD_CLIP Clip = Tree->Clip;
        if (
            (Clip->X <= X) &&
            (Clip->Y <= Y) &&
            ((Clip->X + Clip->Width) >= (X)) &&
            ((Clip->Y + Clip->Height) >= (Y))
        ) {
            PAWM_CLIP_TREE ChildMatch = NULL;
            if (Tree->SubPlane.NextHeader) {
                ChildMatch = FindClipAtPoint((PAWM_CLIP_TREE)Tree->SubPlane.NextHeader, X, Y);
            }
            Best = ChildMatch ? ChildMatch : Tree;
        }
        Tree = (PAWM_CLIP_TREE)Tree->CurrentPlane.NextHeader;
    }
    return Best;
}

PWINDOW_HANDLE AwmFindWindowFromClip(PDRSD_CLIP Clip, SIZE i){
    PAWM_WINDOW_TRACKER_ENTRY Tmp = &AwmMasterTracker;
    while(Tmp){
        if(Tmp->WindowHandle){
            if((uintptr_t)Tmp->WindowHandle->MainWindow[i] == (uintptr_t)Clip){
                return Tmp->WindowHandle; 
            }
        }
        Tmp = (PAWM_WINDOW_TRACKER_ENTRY)Tmp->Peers.NextHeader;
    }
    return 0x00;
}

PWINDOW_HANDLE AwmFineWindowAtPoint(INT64 X, INT64 Y){
    PWINDOW_HANDLE Result = 0x00;
    for(SIZE i = 0; i < PlaneTracker.PlaneCount; i++){
        PAWM_CLIP_TREE ClipTree = &((PWINDOW_HANDLE)BackgroundWindow)->ClipTreeHandle[i];
        ClipTree = FindClipAtPoint(ClipTree, X, Y);
        Result = AwmFindWindowFromClip(ClipTree->Clip, i);
        if(Result){
            return Result;
        }
    }
    return 0x00;
}

void InitializeWindowToWindowManager(PWINDOW_HANDLE WindowHandle) {
    MutexLock(&AwmMasterTrackerMutex);

    PAWM_WINDOW_TRACKER_ENTRY Tmp = &AwmMasterTracker;
    while (Tmp->Peers.NextHeader) {
        Tmp = (PAWM_WINDOW_TRACKER_ENTRY)Tmp->Peers.NextHeader;
    }

    PAWM_WINDOW_TRACKER_ENTRY NewEntry = (PAWM_WINDOW_TRACKER_ENTRY)LouGlobalUserMallocType(AWM_WINDOW_TRACKER_ENTRY);
    Tmp->Peers.NextHeader = (PListHeader)NewEntry;
    NewEntry->WindowHandle = WindowHandle;
    NewEntry->Peers.NextHeader = NULL;

    for (SIZE i = 0; i < WindowHandle->PlaneCount; i++) {
        PDRSD_CLIP Clip = WindowHandle->MainWindow[i];

        PAWM_CLIP_TREE Enclosing = FindEnclosingClip(
            &((PWINDOW_HANDLE)BackgroundWindow)->ClipTreeHandle[i],
            Clip
        );

        PAWM_CLIP_TREE NewClip = (PAWM_CLIP_TREE)LouGlobalUserMallocType(AWM_CLIP_TREE);
        NewClip->Clip = Clip;
        NewClip->SubPlane.NextHeader = NULL;
        NewClip->CurrentPlane.NextHeader = NULL;

        if (!Enclosing) {
            PAWM_CLIP_TREE Root = &((PWINDOW_HANDLE)BackgroundWindow)->ClipTreeHandle[i];
            PAWM_CLIP_TREE* Chain = (PAWM_CLIP_TREE*)&Root->CurrentPlane.NextHeader;
            while (*Chain) {
                Chain = (PAWM_CLIP_TREE*)&(*Chain)->CurrentPlane.NextHeader;
            }
            *Chain = NewClip;
        } else {
            PAWM_CLIP_TREE* Chain = (PAWM_CLIP_TREE*)&Enclosing->SubPlane.NextHeader;
            while (*Chain) {
                Chain = (PAWM_CLIP_TREE*)&(*Chain)->CurrentPlane.NextHeader;
            }
            *Chain = NewClip;
        }

        LouPrint("Window Installed To Window Manager:%s\n", WindowHandle->WindowName);
    }

    MutexUnlock(&AwmMasterTrackerMutex);
}

void RedrawClipTree(PAWM_CLIP_TREE Tree, int64_t X, int64_t Y, int64_t Width, int64_t Height) {
    while (Tree) {
        if (
            (Tree->Clip->X < (X + Width)) &&
            ((Tree->Clip->X + Tree->Clip->Width) > X) &&
            (Tree->Clip->Y < (Y + Height)) &&
            ((Tree->Clip->Y + Tree->Clip->Height) > Y)
        ) {
            if(Tree->UpdateClipSubState){
                Tree->UpdateClipSubState((void*)Tree->Clip, X, Y, Width, Height);
            }else{
                LouUpdateShadowClipSubState((void*)Tree->Clip, X, Y, Width, Height);
            }
        }
        if (Tree->SubPlane.NextHeader) {
            RedrawClipTree((PAWM_CLIP_TREE)Tree->SubPlane.NextHeader, X, Y, Width, Height);
        }
        Tree = (PAWM_CLIP_TREE)Tree->CurrentPlane.NextHeader;
    }
}

void CalculateRedraws(int64_t X, int64_t Y, int64_t Width, int64_t Height){
    /*
    // Clip Tree Example
    // DESKTOP ; CurrentPlane Object
    // | 
    // V
    // Window1 -> Window Ornament ; SubPlane Object
    // |                |  
    // |                V  
    // |           ChildOranment ; Current Plane Object 
    // V
    // Window2 -> Window Ornament ; Sub Plane Object
    // CurrentPlane Object
    */
    
    for (size_t i = 0; i < PlaneTracker.PlaneCount; i++) {
        PAWM_CLIP_TREE RootTree = &((PWINDOW_HANDLE)BackgroundWindow)->ClipTreeHandle[i];
        if (RootTree) {
            RedrawClipTree(RootTree, X, Y, Width, Height);
        }
    }
}

USER32_API
BOOL
ShowWindow(
    HWND        WindowHandle,
    INTEGER     nCmdShow
){
    PWINDOW_HANDLE Window = (PWINDOW_HANDLE)WindowHandle;

    SIZE Planes = Window->PlaneCount;
    BOOL WasVisable = Window->Visable;
    Window->WindowVisability = nCmdShow; 
    switch(nCmdShow){
        case SW_SHOW:{
            for(SIZE i = 0 ; i < Planes; i++){
                LouUpdateShadowClipState((PVOID)Window->MainWindow[i]);
                Window->Visable = true;
            }
        }
    }

    return WasVisable;
}

USER32_API
BOOL 
UpdateWindow(
    HWND WindowHandle
){
    PWINDOW_HANDLE Window = (PWINDOW_HANDLE)WindowHandle;
    SIZE PlaneCount = Window->PlaneCount;
    SIZE i = 0;
    if(!Window->Visable){
        return true;
    }

    switch(Window->WindowVisability){
        case SW_SHOW:{
            for(;i < PlaneCount; i++){
                LouUpdateShadowClipState((PVOID)Window->MainWindow[i]);
                LouDrsdSyncScreen(Window->MainWindow[i]->ChainOwner);
            }
            return true;
        }
        default :
            LouPrint("UpdateWindow\n");
            while(1);
    }
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

    InitializePNGHandleing = AnnyaGetLibraryFunctionN("CODECS.DLL", "InitializePNGHandleing");
    Status = InitializePNGHandleing();  
    if(Status != STATUS_SUCCESS){
        LouPrint("Critical Error Initializig CODECS.DLL\n");
        while(1);
    }

    FREETYPEModule = LoadLibraryA("C:/ANNYA/FREETYPE.DLL");
    //if(FREETYPEModule){
    //    LouPrint("KICK FUCKIN ASS DUDE\n");
    //}

    //while(1);

    AnnyaOpenPngA = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaOpenPngA");
    AnnyaCreateClipFromPng = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaCreateClipFromPng");
    AnnyaOpenBmpA = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaOpenBmpA");
    AnnyaPaintClipWithBmp = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaPaintClipWithBmp");

    MousePng = AnnyaOpenPngA("C:/ANNYA/MOUSE.PNG");
    FolderPng = AnnyaOpenPngA("C:/ANNYA/FOLDER.PNG");
    StartButtonPng = AnnyaOpenPngA("C:/ANNYA/START.PNG");
    BackgroundImage = AnnyaOpenBmpA("C:/ANNYA/PROFILES/DEFAULT/BG/ANNYA.BMP");
    LouPrint("InitializeDependencies() STATUS_SUCCESS\n");

}

static void UpdateMouseClip(int64_t X, int64_t Y){
    if((MouseX != X) || (MouseY != Y)){
        
        for(size_t i = 0 ; i < PlaneTracker.PlaneCount; i++){
            MouseClips[i]->X = X;
            MouseClips[i]->Y = Y;
            CalculateRedraws(MouseX, MouseY, MouseClips[i]->Width, MouseClips[i]->Height);
            LouUpdateShadowClipState((void*)MouseClips[i]);
            LouDrsdSyncScreen((void*)MouseClips[i]->ChainOwner);
        }
        MouseX = X;
        MouseY = Y;
    }
}

static INT64 gMouseX = 0, gMouseY = 0;

static 
void 
MouseEventHandler(
    PLOUSINE_USER_SHARED_MESSAGE MessageHandle
){
    PLOUSINE_MOUSE_EVENT_MESSAGE MouseEvent = &MessageHandle->MouseEvent;
    gMouseX += MouseEvent->X;
    gMouseY += MouseEvent->Y;
    BOOL RightClick = MouseEvent->RightClick;
    BOOL LeftClick  = MouseEvent->LeftClick;
    

    if(gMouseX < DesktopCurrentX){
        gMouseX = DesktopCurrentX;
    }else if(gMouseX > (DesktopCurrentX + DesktopCurrentWidth)){
        gMouseX = (DesktopCurrentX + DesktopCurrentWidth);
    }
    if(gMouseY < DesktopCurrentY){
        gMouseY = DesktopCurrentY;
    }else if(gMouseY > (DesktopCurrentY + DesktopCurrentHeight)){
        gMouseY = (DesktopCurrentY + DesktopCurrentHeight);
    }
    //LouPrint("X:%d, Y:%d\n", gMouseX, gMouseY);
    UpdateMouseClip(gMouseX, gMouseY);

    if(RightClick){

    }
    if(LeftClick){
        PWINDOW_HANDLE WinHandle = AwmFineWindowAtPoint(gMouseX, gMouseY);
        if(WinHandle){
            if(WinHandle->WindowName){
                LouPrint("WINDOW CLICKED:%s\n", WinHandle->WindowName);
            }
        }

    }

}

USER32_API
AWM_STATUS 
InitializeAwmUserSubsystem(
    HINSTANCE                       hInstance,
    PANNYA_DESKTOP_SETUP_PACKET     InterfaceSetup
){
    LouPrint("InitializeAwmUserSubsystem()\n");
 
    InitializeDependencies();

    PlaneTracker.PlaneInformation = (PDRSD_PLANE_QUERY_INFORMATION)LouDrsdGetPlaneInformation(&PlaneTracker.PlaneCount);

    MouseClips = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);

    LouPrint("Allocation Finished\n");
    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){
        if(PlaneTracker.PlaneInformation[i].Width > DesktopCurrentWidth){
            DesktopCurrentWidth = PlaneTracker.PlaneInformation[i].Width; 
        }
        if(PlaneTracker.PlaneInformation[i].Height > DesktopCurrentHeight){
            DesktopCurrentHeight = PlaneTracker.PlaneInformation[i].Height; 
        }
    }

    BackgroundWindow = CreateWindowA(
                            DEKSTOP_BACKGROUND,
                            "DesktopBackground",
                            WS_VISIBLE | WS_DISABLED,
                            0,0, 0, 0,
                            0x00, 0x00, hInstance, 0x00 
                        );

    ShowWindow(BackgroundWindow, SW_SHOW);
    
    UpdateWindow(BackgroundWindow);

    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){

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

    LouRegisterMouseHandler(&MouseEventHandler, MOUSE_EVENT_TYPE);

    LouPrint("InitializeAwmUserSubsystem() STATUS_SUCCESS\n");
}



