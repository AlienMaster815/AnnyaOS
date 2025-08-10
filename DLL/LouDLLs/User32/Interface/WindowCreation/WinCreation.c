#include "WinCreation.h"

extern AWM_PLANE_TRACKER PlaneTracker;
void InitializeBackgroundWindows(PWINDOW_HANDLE WindowHandle);

extern int64_t DesktopCurrentWidth;
extern int64_t DesktopCurrentHeight;
extern int64_t DesktopCurrentX;
extern int64_t DesktopCurrentY;

static void CreateGenericWindowHandle(
    PWINDOW_HANDLE WindowHandle, 
    INT64 X, INT64 Y, 
    UINT32 Width, UINT32 Height, 
    UINT8 R, UINT8 G, UINT8 B
){

    WindowHandle->X = X;
    WindowHandle->Y = Y;
    WindowHandle->Width = Width;
    WindowHandle->Height = Height;



}

static PWINDOW_HANDLE CreateDesktopBackgroundWindow(){
    PWINDOW_HANDLE NewWindow = LouGlobalUserMallocType(WINDOW_HANDLE);
    NewWindow->MainWindow = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    NewWindow->PlaneCount = PlaneTracker.PlaneCount;
    NewWindow->Mirrored = true;
    NewWindow->X = DesktopCurrentX;
    NewWindow->Y = DesktopCurrentY;
    NewWindow->Width = (UINT32)DesktopCurrentWidth;
    NewWindow->Height = (UINT32)DesktopCurrentHeight;

    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){

        NewWindow->MainWindow[i] = LouDrsdCreateClip(
            PlaneTracker.PlaneInformation[i].X,
            PlaneTracker.PlaneInformation[i].Y,
            (size_t)PlaneTracker.PlaneInformation[i].Width,
            (size_t)PlaneTracker.PlaneInformation[i].Height,
            0,0xC0,0xC0, 0xFF
        );

    }

    return NewWindow;
}

static PWINDOW_HANDLE CreateDesktopTaskTrayWindow(){
    PWINDOW_HANDLE NewWindow = LouGlobalUserMallocType(WINDOW_HANDLE);



    return NewWindow;
}

USER32_API
HWND
CreateWindowExA(
    DWORD       ExStyle,
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
    PWINDOW_HANDLE NewWindow = 0x00;
    if(!strcmp(ClassName, DEKSTOP_BACKGROUND)){
        return CreateDesktopBackgroundWindow();
    }else if(!strcmp(ClassName, TRAY_WINDOW)){
        NewWindow = CreateDesktopTaskTrayWindow();
    }



    return (PWINDHANDLE)NewWindow;
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
    return CreateWindowExA(
        0,
        ClassName,
        WindowName,
        Style,
        X, Y,
        Width, Height,
        ParrentHandle,
        Menu,
        Instance,
        Parameter
    );
}
