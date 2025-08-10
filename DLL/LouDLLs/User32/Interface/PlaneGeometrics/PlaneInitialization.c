#include "../Awm.h"

static INT64 vDesktopCurrentWidth = 0;
static INT64 vDesktopCurrentHeight = 0;
static PDRSD_CLIP* PlaneBackgrounds = 0x00;

extern int64_t DesktopCurrentX;
extern int64_t DesktopCurrentY;
extern int64_t DesktopCurrentWidth;
extern int64_t DesktopCurrentHeight;
extern AWM_PLANE_TRACKER PlaneTracker;
extern PDRSD_CLIP* XButtonClips;
extern PDRSD_CLIP* MouseClips;
bool MirrorAllScreens = true;
static HWND BackgroundWindow = 0x00;

void InitializeBackgroundWindows(PWINDOW_HANDLE WindowHandle){
    for(size_t i = 0 ; i < WindowHandle->PlaneCount; i++){
        PlaneBackgrounds[i] = WindowHandle->MainWindow[i];
    }

}

void InitializePlaneTracker(
    HINSTANCE   hInstance
){

    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){
        DesktopCurrentWidth += PlaneTracker.PlaneInformation[i].Width;
        if(PlaneTracker.PlaneInformation[i].Height > DesktopCurrentHeight){
            DesktopCurrentHeight = PlaneTracker.PlaneInformation[i].Height;
        }
    }

    INT64 Tmp = 0;
    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){
        //LouPrint("PlaneX:%d::PlaneY:%d\n", Tmp, DesktopCurrentHeight);
        PlaneTracker.PlaneInformation[i].X = Tmp;
        PlaneTracker.PlaneInformation[i].Y = 0;
        Tmp += PlaneTracker.PlaneInformation[i].Width;
    }

    DesktopCurrentX = PlaneTracker.PlaneInformation[0].X;
    DesktopCurrentY = PlaneTracker.PlaneInformation[0].Y;

    LouPrint("X:%h :: Y:%h\n", DesktopCurrentX, DesktopCurrentY);

    vDesktopCurrentWidth = DesktopCurrentWidth * 3;
    vDesktopCurrentHeight = DesktopCurrentHeight * 3;

    XButtonClips = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    MouseClips = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    PlaneBackgrounds = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    
    LouDrsdSetPlaneInformation(PlaneTracker.PlaneInformation);

    BackgroundWindow = CreateWindowA(
                            DEKSTOP_BACKGROUND,
                            "DesktopBackground",
                            WS_VISIBLE | WS_DISABLED,
                            0,0, 0, 0, //dimentions ignored
                            0x00, 0x00, hInstance, 0x00 
                        );

    InitializeBackgroundWindows(BackgroundWindow);

    ShowWindow((HWND)BackgroundWindow, SW_SHOW);

    UpdateWindow(BackgroundWindow);
    
    /*
    //LouPrin t("Desktop  Width:%d ::  Height:%d\n", DesktopCurrentWidth, DesktopCurrentHeight);
    //LouPrint("Desktop vWidth:%d :: vHeight:%d\n", vDesktopCurrentWidth, vDesktopCurrentHeight);
    */
}