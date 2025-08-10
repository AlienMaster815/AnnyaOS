#include "../Awm.h"

static PDRSD_CLIP PlaneBackground = 0x00;

extern int64_t DesktopCurrentX;
extern int64_t DesktopCurrentY;
extern int64_t DesktopCurrentWidth;
extern int64_t DesktopCurrentHeight;
extern AWM_PLANE_TRACKER PlaneTracker;
extern PDRSD_CLIP XButtonClip;
extern PDRSD_CLIP MouseClip;
bool MirrorAllScreens = true;
HWND BackgroundWindow = 0x00;

void InitializeBackgroundWindows(PWINDOW_HANDLE WindowHandle){

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

    XButtonClip = LouGlobalUserMallocType(DRSD_CLIP);
    MouseClip = LouGlobalUserMallocType(DRSD_CLIP);
    PlaneBackground = LouGlobalUserMallocType(DRSD_CLIP);
    
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