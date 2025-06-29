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

    MousePng = AnnyaOpenPngA("C:/ANNYA/MOUSE.PNG");

    LouPrint("InitializeDependencies() STATUS_SUCCESS\n");
    while(1);
}


AWM_STATUS InitializeAwmUserSubsystem(){
    LouPrint("InitializeAwmUserSubsystem()\n");
 
    InitializeDependencies();

    PlaneTracker.PlaneInformation = (PDRSD_PLANE_QUERY_INFORMATION)LouDrsdGetPlaneInformation(&PlaneTracker.PlaneCount);

    LouPrint("Plane Count:%d\n", PlaneTracker.PlaneCount);

    PlaneBackgrounds = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);

    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){
        PlaneBackgrounds[i] = (PDRSD_CLIP)LouDrsdCreateClip(
            (void*)PlaneTracker.PlaneInformation[i].Plane,
            0, 0, 
            PlaneTracker.PlaneInformation[i].Width, 
            PlaneTracker.PlaneInformation[i].Height,
            0, 128,128, 255
        );
        LouUpdateClipState((void*)PlaneBackgrounds[i]);
        LouDrsdSyncScreen((void*)PlaneBackgrounds[i]->ChainOwner);
    }

    LouPrint("InitializeAwmUserSubsystem() STATUS_SUCCESS\n");
}
