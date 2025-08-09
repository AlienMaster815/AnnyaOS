#include "WinCreation.h"

extern AWM_PLANE_TRACKER PlaneTracker;
void InitializeBackgroundWindows(PWINDOW_HANDLE WindowHandle);


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

    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){

        NewWindow->MainWindow[i] = LouDrsdCreateClip(
            (void*)PlaneTracker.PlaneInformation[i].Plane,
            0,0,
            (size_t)PlaneTracker.PlaneInformation[i].Width,
            (size_t)PlaneTracker.PlaneInformation[i].Height,
            0,0xC0,0xC0, 0xFF
        );

    }

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
    if(!strcmp(ClassName, DEKSTOP_BACKGROUND)){

    }

    return (PWINDHANDLE)0x00;
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
