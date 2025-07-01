#include "Awm.h"

typedef struct _AWM_WINDOW_TRACKER_ENTRY{
    ListHeader      Peers;
    PWINDOW_HANDLE  WindowHandle;
}AWM_WINDOW_TRACKER_ENTRY, * PAWM_WINDOW_TRACKER_ENTRY;

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
}AWM_CLIP_TREE, * PAWM_CLIP_TREE;


typedef struct _AWM_PLANE_TRACKER{
    PDRSD_PLANE_QUERY_INFORMATION   PlaneInformation;
    size_t                          PlaneCount;
}AWM_PLANE_TRACKER, * PAWM_PLANE_TRACKER;

static AWM_WINDOW_TRACKER_ENTRY AwmMasterTracker = {0};
static atomic_t AwmMasterTrackerMutex = {0};
static AWM_PLANE_TRACKER PlaneTracker = {0};
static atomic_t AwmPlaneTrackerMutex = {0};
static PDRSD_CLIP* PlaneBackgrounds = 0x00;
static HANDLE MousePng = 0x00;
static HMODULE CODECShModule = 0;
static HANDLE (*AnnyaOpenPngA)(string);
static LOUSTATUS (*InitializePNGHandleing)();
static HMODULE Msvcrt = 0;
static HANDLE (*AnnyaCreateClipFromPng)(void*,HANDLE);
static PDRSD_CLIP* MouseClips = 0x00;
static int64_t MouseX = 0;
static int64_t MouseY = 0;
static int64_t DesktopCurrentX = 0;
static int64_t DesktopCurrentY = 0;
static int64_t DesktopCurrentWidth = 0;
static int64_t DesktopCurrentHeight = 0;
static PAWM_CLIP_TREE ClipTrees;
static PDRSD_CLIP* TaskBars = 0;

//192 dark greay
//198 ligt grey

void RedrawClipTree(PAWM_CLIP_TREE Tree, int64_t X, int64_t Y, int64_t Width, int64_t Height) {
    while (Tree) {
        if (
            (Tree->Clip->X < (X + Width)) &&
            ((Tree->Clip->X + Tree->Clip->Width) > X) &&
            (Tree->Clip->Y < (Y + Height)) &&
            ((Tree->Clip->Y + Tree->Clip->Height) > Y)
        ) {
            LouUpdateClipSubState((void*)Tree->Clip, X, Y, Width, Height);
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
        PAWM_CLIP_TREE RootTree = &ClipTrees[i];
        if (RootTree) {
            RedrawClipTree(RootTree, X, Y, Width, Height);
        }
    }
}

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
){
    LouPrint("CreateWindowA()\n");
    while(1);
    return (PWINDHANDLE)0x00;
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

    AnnyaOpenPngA = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaOpenPngA");
    AnnyaCreateClipFromPng = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaCreateClipFromPng");

    MousePng = AnnyaOpenPngA("C:/ANNYA/MOUSE.PNG");

    LouPrint("InitializeDependencies() STATUS_SUCCESS\n");

}


AWM_STATUS InitializeAwmUserSubsystem(){
    LouPrint("InitializeAwmUserSubsystem()\n");
 
    InitializeDependencies();

    PlaneTracker.PlaneInformation = (PDRSD_PLANE_QUERY_INFORMATION)LouDrsdGetPlaneInformation(&PlaneTracker.PlaneCount);

    LouPrint("Plane Count:%d\n", PlaneTracker.PlaneCount);

    PlaneBackgrounds = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    MouseClips = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    TaskBars = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    ClipTrees = LouGlobalUserMallocArray(AWM_CLIP_TREE, PlaneTracker.PlaneCount);
    PAWM_CLIP_TREE TaskBarTree = LouGlobalUserMallocArray(AWM_CLIP_TREE, PlaneTracker.PlaneCount);

    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){
        if(PlaneTracker.PlaneInformation[i].Width > DesktopCurrentWidth){
            DesktopCurrentWidth = PlaneTracker.PlaneInformation[i].Width; 
        }
        if(PlaneTracker.PlaneInformation[i].Height > DesktopCurrentHeight){
            DesktopCurrentHeight = PlaneTracker.PlaneInformation[i].Height; 
        }
        PlaneBackgrounds[i] = (PDRSD_CLIP)LouDrsdCreateClip(
            (void*)PlaneTracker.PlaneInformation[i].Plane,
            0, 0, 
            PlaneTracker.PlaneInformation[i].Width, 
            PlaneTracker.PlaneInformation[i].Height,
            0, 128,128, 255
        );
        TaskBars[i] = LouDrsdCreateClip(
            (void*)PlaneTracker.PlaneInformation[i].Plane,
            0,
            PlaneTracker.PlaneInformation[i].Height - 30,
            PlaneTracker.PlaneInformation[i].Width, 
            30,
            192, 192, 192, 255
        );
        LouUpdateClipState((void*)PlaneBackgrounds[i]);
        LouUpdateClipState((void*)TaskBars[i]);
        MouseClips[i] = AnnyaCreateClipFromPng((void*)PlaneTracker.PlaneInformation[i].Plane, MousePng);
        LouUpdateShadowClipState((void*)MouseClips[i]);
        TaskBarTree[i].Clip = TaskBars[i];
        ClipTrees[i].Clip = PlaneBackgrounds[i];
        ClipTrees[i].SubPlane.NextHeader = (PListHeader)&TaskBarTree[i];
        LouDrsdSyncScreen((void*)MouseClips[i]->ChainOwner);        
    }
    LouPrint("InitializeAwmUserSubsystem() STATUS_SUCCESS\n");
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

USER32_API
void AwmUpdateState(PSYSTEM_STATE_STACK State){
    if(State->MouseState.MouseX < DesktopCurrentX){
        State->MouseState.MouseX = DesktopCurrentX;
    }else if(State->MouseState.MouseX > (DesktopCurrentX + DesktopCurrentWidth)){
        State->MouseState.MouseX = (DesktopCurrentX + DesktopCurrentWidth);
    }
    if(State->MouseState.MouseY < DesktopCurrentY){
        State->MouseState.MouseY = DesktopCurrentY;
    }else if(State->MouseState.MouseY > (DesktopCurrentY + DesktopCurrentHeight)){
        State->MouseState.MouseY = (DesktopCurrentY + DesktopCurrentHeight);
    }
    UpdateMouseClip(State->MouseState.MouseX, State->MouseState.MouseY);
}