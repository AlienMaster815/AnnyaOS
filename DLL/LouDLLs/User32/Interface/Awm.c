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
    void (*UpdateClipSubState)(void* Clip, size_t X, size_t Y, size_t Width, size_t Height);
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
static HANDLE GenericButtonPng = 0x00;
static PDRSD_CLIP* GenericButtonClips = 0;
static PAWM_CLIP_TREE GenericButtonTree = 0;
static HANDLE (*AnnyaOpenBmpA)(string);
static HANDLE BackgroundImage = 0x00;
static HANDLE (*AnnyaPaintClipWithBmp)(HANDLE, HANDLE, size_t, size_t, size_t, size_t) = 0x00;
static HANDLE FolderPng = 0x00;
static PDRSD_CLIP* FolderClips = 0x00;

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
            Tree->UpdateClipSubState((void*)Tree->Clip, X, Y, Width, Height);
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
    AnnyaOpenBmpA = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaOpenBmpA");
    AnnyaPaintClipWithBmp = AnnyaGetLibraryFunctionN("CODECS.DLL", "AnnyaPaintClipWithBmp");

    MousePng = AnnyaOpenPngA("C:/ANNYA/MOUSE.PNG");
    FolderPng = AnnyaOpenPngA("C:/ANNYA/FOLDER.PNG");
    GenericButtonPng = AnnyaOpenPngA("C:/ANNYA/BUTTON.PNG");
    BackgroundImage = AnnyaOpenBmpA("C:/ANNYA/PROFILES/DEFAULT/BG/ANNYA.BMP");
    LouPrint("InitializeDependencies() STATUS_SUCCESS\n");

}


AWM_STATUS InitializeAwmUserSubsystem(){
    LouPrint("InitializeAwmUserSubsystem()\n");
 
    InitializeDependencies();

    PlaneTracker.PlaneInformation = (PDRSD_PLANE_QUERY_INFORMATION)LouDrsdGetPlaneInformation(&PlaneTracker.PlaneCount);
    size_t BgImageScalingY = 0;
    size_t BgImageScalingX = 0;
    LouPrint("Plane Count:%d\n", PlaneTracker.PlaneCount);
    PlaneBackgrounds = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    MouseClips = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    GenericButtonClips = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    FolderClips = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    TaskBars = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    ClipTrees = LouGlobalUserMallocArray(AWM_CLIP_TREE, PlaneTracker.PlaneCount);
    PAWM_CLIP_TREE TaskBarTree = LouGlobalUserMallocArray(AWM_CLIP_TREE, PlaneTracker.PlaneCount);
    PAWM_CLIP_TREE GenericButtonTree = LouGlobalUserMallocArray(AWM_CLIP_TREE, PlaneTracker.PlaneCount);
    PAWM_CLIP_TREE FolderTree = LouGlobalUserMallocArray(AWM_CLIP_TREE, PlaneTracker.PlaneCount);
    LouPrint("Allocation Finished\n");

    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){
        if(PlaneTracker.PlaneInformation[i].Width > DesktopCurrentWidth){
            DesktopCurrentWidth = PlaneTracker.PlaneInformation[i].Width; 
        }
        if(PlaneTracker.PlaneInformation[i].Height > DesktopCurrentHeight){
            DesktopCurrentHeight = PlaneTracker.PlaneInformation[i].Height; 
        }
        LouPrint("Desktop Geometry Calculation:%d Of :%d\n", i + 1, PlaneTracker.PlaneCount);
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
            PlaneTracker.PlaneInformation[i].Height - 35,
            PlaneTracker.PlaneInformation[i].Width, 
            35,
            192, 192, 192, 255
        );
        AwmGetImageScaleingCentered(
            ((PCODECS_TYPE_QUERY)BackgroundImage)->HandleInformation.ImageHandleData.Width, 
            ((PCODECS_TYPE_QUERY)BackgroundImage)->HandleInformation.ImageHandleData.Height, 
            PlaneTracker.PlaneInformation[i].Width, 
            PlaneTracker.PlaneInformation[i].Height,
            &BgImageScalingX, &BgImageScalingY
        );
        AnnyaPaintClipWithBmp(
            BackgroundImage, PlaneBackgrounds[i], 
            AwmGetImageCenteredX(((PCODECS_TYPE_QUERY)BackgroundImage)->HandleInformation.ImageHandleData.Width, PlaneTracker.PlaneInformation[i].Width, BgImageScalingX),
            AwmGetImageCenteredY(((PCODECS_TYPE_QUERY)BackgroundImage)->HandleInformation.ImageHandleData.Height, PlaneTracker.PlaneInformation[i].Height, BgImageScalingY),
            BgImageScalingX, BgImageScalingY
        );
        LouUpdateClipState((void*)PlaneBackgrounds[i]);
        LouUpdateClipState((void*)TaskBars[i]);
        GenericButtonClips[i] = AnnyaCreateClipFromPng((void*)PlaneTracker.PlaneInformation[i].Plane, GenericButtonPng);
        GenericButtonClips[i]->X = 1;
        GenericButtonClips[i]->Y = PlaneTracker.PlaneInformation[i].Height - 33;
        LouUpdateClipState((void*)GenericButtonClips[i]);
        FolderClips[i] = AnnyaCreateClipFromPng((void*)PlaneTracker.PlaneInformation[i].Plane, FolderPng);
        
        FolderClips[i]->X = 68;
        FolderClips[i]->Y = PlaneTracker.PlaneInformation[i].Height - 31;
        LouUpdateShadowClipState((void*)FolderClips[i]);

        MouseClips[i] = AnnyaCreateClipFromPng((void*)PlaneTracker.PlaneInformation[i].Plane, MousePng);
        LouUpdateShadowClipState((void*)MouseClips[i]);

        TaskBarTree[i].Clip = TaskBars[i];
        TaskBarTree[i].UpdateClipSubState = LouUpdateClipSubState;
        GenericButtonTree[i].Clip = GenericButtonClips[i];
        GenericButtonTree[i].UpdateClipSubState = LouUpdateClipSubState;
        FolderTree[i].Clip = FolderClips[i];
        FolderTree[i].UpdateClipSubState = LouUpdateShadowClipSubState;
        ClipTrees[i].Clip = PlaneBackgrounds[i];
        ClipTrees[i].UpdateClipSubState = LouUpdateClipSubState;
        
        ClipTrees[i].SubPlane.NextHeader = (PListHeader)&TaskBarTree[i];
        TaskBarTree[i].SubPlane.NextHeader = (PListHeader)&GenericButtonTree[i];
        GenericButtonTree[i].CurrentPlane.NextHeader = (PListHeader)&FolderTree[i]; 
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