#include "Awm.h"

typedef int FT_Error;
typedef void* FT_Library;

USER32_API
BOOL 
UpdateWindow(
    HWND WindowHandle
);

static PDRSD_CLIP* PlaneBackgrounds = 0x00;
static HANDLE MousePng = 0x00;
static HMODULE CODECShModule = 0;
static HMODULE FREETYPEModule = 0;
static HANDLE (*AnnyaOpenPngA)(string);
static LOUSTATUS (*InitializePNGHandleing)();
static HMODULE Msvcrt = 0;
static int64_t MouseX = 0;
static int64_t MouseY = 0;
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
static AWM_PLANE_TRACKER PlaneTracker = {0};
static mutex_t AwmPlaneTrackerMutex = {0};
static HWND BackgroundWindow = 0x00;
static HWND TaskbarWindow = 0x00;
static PDRSD_CLIP* MouseClips = 0x00;
static HWND StartButton = 0x00;
static HWND FileExplorerButon = 0x00;
static HANDLE FolderPng = 0x00;
static HMENU StartMenu = 0x00;
static bool StartButtonDown = false;

static int64_t DesktopCurrentX = 0;
static int64_t DesktopCurrentY = 0;
int64_t DesktopCurrentWidth = 0;
int64_t DesktopCurrentHeight = 0;

static HANDLE XButtonPng = 0x00;
PDRSD_CLIP* XButtonClips = 0x00;

static DWORD (*AnnyaExplorerFileManager)(PVOID);

void InitializeFreeType();

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
            ((Clip->X + Clip->Width) > (InnerClip->X + InnerClip->Width)) &&
            ((Clip->Y + Clip->Height) > (InnerClip->Y + InnerClip->Height))
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

PDRSD_CLIP FindClip(INT64 X, INT64 Y){
    for(SIZE i = 0; i < PlaneTracker.PlaneCount; i++){
        PAWM_CLIP_TREE ClipTree = &((PWINDOW_HANDLE)BackgroundWindow)->ClipTreeHandle[i];
        ClipTree = FindClipAtPoint(ClipTree, X, Y);
        if(ClipTree){
            return ClipTree->Clip;
        }   
    }
    return 0x00;
}

PWINDOW_HANDLE AwmFindWindowAtPoint(INT64 X, INT64 Y){
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

void MoveWindowTheFrontRec(PWINDOW_HANDLE WindowHandle){
    for(size_t i = 0 ; i < WindowHandle->PlaneCount; i++){
        PAWM_CLIP_TREE Tree = &WindowHandle->ClipTreeHandle[i];
        if(!Tree->CurrentPlane.NextHeader){
            continue;
        }
        PAWM_CLIP_TREE Last = (PAWM_CLIP_TREE)Tree->CurrentPlane.LastHeader;
        PAWM_CLIP_TREE Next = (PAWM_CLIP_TREE)Tree->CurrentPlane.NextHeader;
        PAWM_CLIP_TREE UpDirectory = 0x00;
        if(Last){
            Last->CurrentPlane.NextHeader = (PListHeader)Next;
        }else{
            UpDirectory = (PAWM_CLIP_TREE)Tree->SubPlane.LastHeader;
            Tree->SubPlane.LastHeader = 0x00;
            UpDirectory->SubPlane.NextHeader = (PListHeader)Next;
            Next->SubPlane.LastHeader = (PListHeader)UpDirectory;
            Next->SubPlane.NextHeader = Tree->SubPlane.NextHeader;
            Tree->SubPlane.NextHeader = 0x00;   
        }
        Next->CurrentPlane.LastHeader = (PListHeader)Last;

        PAWM_CLIP_TREE Enclosing = FindEnclosingClip(
            &((PWINDOW_HANDLE)BackgroundWindow)->ClipTreeHandle[i],
            WindowHandle->MainWindow[i]
        );
        Tree->SubPlane.NextHeader = NULL;
        Tree->CurrentPlane.NextHeader = NULL;

        if (!Enclosing) {
            PAWM_CLIP_TREE Root = &((PWINDOW_HANDLE)BackgroundWindow)->ClipTreeHandle[i];
            PAWM_CLIP_TREE Chain = (PAWM_CLIP_TREE)Root;
            PAWM_CLIP_TREE LastClip = 0x00;

            while (Chain->CurrentPlane.NextHeader) {
                LastClip = Chain;
                Chain = (PAWM_CLIP_TREE)Chain->CurrentPlane.NextHeader;
            }

            Chain->CurrentPlane.NextHeader = (PListHeader)Tree;
            Tree->CurrentPlane.LastHeader = (PListHeader)Chain;
        } else {
            PAWM_CLIP_TREE Chain = (PAWM_CLIP_TREE)Enclosing->SubPlane.NextHeader;
            if(!Chain){
                Enclosing->SubPlane.NextHeader = (PListHeader)Tree;
                Tree->SubPlane.LastHeader = (PListHeader)Enclosing;
            }else{
                PAWM_CLIP_TREE LastClip = 0x00;
                while (Chain->CurrentPlane.NextHeader) {
                    LastClip = Chain;
                    Chain = (PAWM_CLIP_TREE)Chain->CurrentPlane.NextHeader;
                }
                Chain->CurrentPlane.NextHeader = (PListHeader)Tree;
                Tree->CurrentPlane.LastHeader = (PListHeader)Chain;
            }

        }

    }
}

void MoveWindowTheFront(PWINDOW_HANDLE WindowHandle){
    MoveWindowTheFrontRec(WindowHandle);
    PCHILD_WINDOW_TRACKER Children = &WindowHandle->Children;
    while(Children->Peers.NextHeader){
        MoveWindowTheFrontRec(Children->Child);
        Children = (PCHILD_WINDOW_TRACKER)Children->Peers.NextHeader;
    }
}

void UpdateWindowToDesktop(PWINDOW_HANDLE WindowHandle){
    MoveWindowTheFront(WindowHandle);
    MoveWindowTheFront(TaskbarWindow);
    
}

void InitializeWindowToWindowManager(PWINDOW_HANDLE WindowHandle) {

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

        PAWM_CLIP_TREE NewClip = (PAWM_CLIP_TREE)&WindowHandle->ClipTreeHandle[i];
        NewClip->Clip = Clip;
        NewClip->SubPlane.NextHeader = NULL;
        NewClip->CurrentPlane.NextHeader = NULL;

        if (!Enclosing) {
            PAWM_CLIP_TREE Root = &((PWINDOW_HANDLE)BackgroundWindow)->ClipTreeHandle[i];
            PAWM_CLIP_TREE Chain = (PAWM_CLIP_TREE)Root;
            PAWM_CLIP_TREE LastClip = 0x00;

            while (Chain->CurrentPlane.NextHeader) {
                LastClip = Chain;
                Chain = (PAWM_CLIP_TREE)Chain->CurrentPlane.NextHeader;
            }

            Chain->CurrentPlane.NextHeader = (PListHeader)NewClip;
            NewClip->CurrentPlane.LastHeader = (PListHeader)Chain;
        } else {
            PAWM_CLIP_TREE Chain = (PAWM_CLIP_TREE)Enclosing->SubPlane.NextHeader;
            if(!Chain){
                Enclosing->SubPlane.NextHeader = (PListHeader)NewClip;
                NewClip->SubPlane.LastHeader = (PListHeader)Enclosing;
            }else{
                PAWM_CLIP_TREE LastClip = 0x00;
                while (Chain->CurrentPlane.NextHeader) {
                    LastClip = Chain;
                    Chain = (PAWM_CLIP_TREE)Chain->CurrentPlane.NextHeader;
                }
                Chain->CurrentPlane.NextHeader = (PListHeader)NewClip;
                NewClip->CurrentPlane.LastHeader = (PListHeader)Chain;
            }

        }

        LouPrint("Window Installed To Window Manager:%s\n", WindowHandle->WindowName);
    }

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
    MutexLock(&AwmMasterTrackerMutex);
    
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
    MutexUnlock(&AwmMasterTrackerMutex);
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
            }
            Window->Visable = true;
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
                CalculateRedraws(
                    Window->MainWindow[i]->X,
                    Window->MainWindow[i]->Y,
                    Window->MainWindow[i]->Width,
                    Window->MainWindow[i]->Height
                );
                if(MouseClips[i]){
                    LouUpdateShadowClipState((void*)MouseClips[i]);
                }
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

void AwmHandleStartButtonEvent(PWINDOW_HANDLE Handle, bool Click){
    if((Click) && (!StartButtonDown)){
        AwmWindowDrawLine(Handle, 0, 0, CLIP_WIDTH, 0, 0, 0, 0, 255);
        AwmWindowDrawLine(Handle, 0, 0, 0, CLIP_HEIGHT, 0, 0, 0, 255);
        StartButtonDown = true;
        UpdateWindow(Handle);
        //TODO Create Start Menu
    }else if(StartButtonDown){ //destroy
        AwmWindowDrawLine(Handle, 0, 0, CLIP_WIDTH, 0, 255, 255, 255, 255);
        AwmWindowDrawLine(Handle, 0, 0, 0, CLIP_HEIGHT, 255, 255, 255, 255);
        StartButtonDown = false;
        UpdateWindow(Handle);
        //TODO Destroy Start Menu
    }
}


void AwmHandelFileExplorerEvent(PWINDOW_HANDLE Handle, bool Click){
    if(InterfaceDualClick){
        if(AnnyaExplorerFileManager){
            PANNYA_EXPLORER_INIT_PACKET NewPacket = LouGlobalUserMallocType(ANNYA_EXPLORER_INIT_PACKET);
            NewPacket->Instance = (HINSTANCE)LouGlobalUserMallocType(HINSTANCE);
            AnnyaCreateThread(AnnyaExplorerFileManager, NewPacket);
        }
    }
}

void AwmMoveWindow(PWINDOW_HANDLE Window, INT64 DeltaX, INT64 DeltaY){
    size_t PlaneCount = Window->PlaneCount;
    INT64 LastX;
    INT64 LastY;
    INT64 LastWidth;
    INT64 LastHeight;
    for(size_t i = 0 ; i < PlaneCount; i++){
        LastX = Window->MainWindow[i]->X;
        LastY = Window->MainWindow[i]->Y;
        LastWidth = Window->MainWindow[i]->Width;
        LastHeight = Window->MainWindow[i]->Height;
        if(DesktopCurrentX >= (LastX + DeltaX)){
            DeltaX = 0;
        }
        if(DesktopCurrentY >= (LastY + DeltaY)){
            DeltaY = 0;
        }
        LouUpdateClipLocation(Window->MainWindow[i], (UINT32)(LastX + DeltaX), (UINT32)(LastY + DeltaY));
        UpdateWindowToDesktop(Window);
        CalculateRedraws(LastX, LastY, LastWidth, LastHeight);
    }
    UpdateWindow(
        Window
    );
}

static 
void 
MouseEventHandler(
    PLOUSINE_USER_SHARED_MESSAGE MessageHandle
){
    PLOUSINE_MOUSE_EVENT_MESSAGE MouseEvent = &MessageHandle->MouseEvent;
    
    INT64 DeltaX = MouseEvent->X;
    INT64 DeltaY = MouseEvent->Y;
    gMouseX += DeltaX;
    gMouseY += DeltaY;

    BOOL RightClick = MouseEvent->RightClick;
    BOOL LeftClick  = MouseEvent->LeftClick;

    //write 0s for the request to complete
    MouseEvent->X = 0;
    MouseEvent->Y = 0;
    MouseEvent->LeftClick = 0;
    MouseEvent->RightClick = 0;

    if(gMouseX < DesktopCurrentX){
        DeltaX = 0;
        gMouseX = DesktopCurrentX;
    }else if(gMouseX > (DesktopCurrentX + DesktopCurrentWidth)){
        DeltaX = 0;
        gMouseX = (DesktopCurrentX + DesktopCurrentWidth);
    }
    if(gMouseY < DesktopCurrentY){
        DeltaY = 0;
        gMouseY = DesktopCurrentY;
    }else if(gMouseY > (DesktopCurrentY + DesktopCurrentHeight)){
        DeltaY = 0;
        gMouseY = (DesktopCurrentY + DesktopCurrentHeight);
    }
    //LouPrint("X:%d, Y:%d\n", gMouseX, gMouseY);
    UpdateMouseClip(gMouseX, gMouseY);

    PWINDOW_HANDLE GrabbedWindow = AwmCheckIfWindowIsGrabbed();
    if(GrabbedWindow){
        AwmMoveWindow(GrabbedWindow, DeltaX, DeltaY);
    }

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
    }
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
    
    XButtonClips = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
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

    LouRegisterMouseHandler(&MouseEventHandler, MOUSE_EVENT_TYPE);

    LouPrint("InitializeAwmUserSubsystem() STATUS_SUCCESS\n");
}



