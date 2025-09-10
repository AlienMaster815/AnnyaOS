#include "WinCreation.h"

extern AWM_PLANE_TRACKER PlaneTracker;
void InitializeBackgroundWindows(PWINDOW_HANDLE WindowHandle);
extern HANDLE (*AnnyaCreateClipFromPng)(HANDLE);
extern HWND BackgroundWindow;
extern int64_t DesktopCurrentWidth;
extern int64_t DesktopCurrentHeight;
extern int64_t DesktopCurrentX;
extern int64_t DesktopCurrentY;
extern bool MirrorAllScreens;
extern HANDLE BackgroundImage;
extern HANDLE (*AnnyaCodecsPaintClipFromImageHandle)(HANDLE, HANDLE, size_t, size_t, size_t, size_t);

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
    
    size_t BackgroundWdth = (size_t)AnnyaCodecsImageHandleToWidth(BackgroundImage);
    size_t BackgroundHeight = (size_t)AnnyaCodecsImageHandleToHeight(BackgroundImage);
    size_t WidthTScale;
    size_t HeightTScale;
    size_t Tx;
    size_t Ty;
    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){

        NewWindow->MainWindow[i] = LouDrsdCreateClip(
            PlaneTracker.PlaneInformation[i].X,
            PlaneTracker.PlaneInformation[i].Y,
            PlaneTracker.PlaneInformation[i].Width,
            PlaneTracker.PlaneInformation[i].Height,
            0,0xC0,0xC0, 0xFF
        );
        AwmGetImageScaleingCentered(
            BackgroundWdth, BackgroundHeight, 
            PlaneTracker.PlaneInformation[i].Width, 
            PlaneTracker.PlaneInformation[i].Height,
            &WidthTScale, &HeightTScale
        );
        Tx = AwmGetImageCenteredX(
            BackgroundWdth,  
            PlaneTracker.PlaneInformation[i].Width, 
            WidthTScale
        );
        Ty = AwmGetImageCenteredY(
            BackgroundHeight, 
            PlaneTracker.PlaneInformation[i].Height,
            HeightTScale
        );

        AnnyaCodecsPaintClipFromImageHandle(
            BackgroundImage, 
            NewWindow->MainWindow[i],
            Tx, 
            Ty,
            WidthTScale,
            HeightTScale
        );

    }

    return NewWindow;
}

static PWINDOW_HANDLE CreateDesktopTaskTrayWindow(){
    PWINDOW_HANDLE NewWindow = LouGlobalUserMallocType(WINDOW_HANDLE);
    PWINDOW_HANDLE Desktop = (PWINDOW_HANDLE)BackgroundWindow;
    NewWindow->MainWindow = LouGlobalUserMallocArray(PDRSD_CLIP, PlaneTracker.PlaneCount);
    NewWindow->PlaneCount = PlaneTracker.PlaneCount;
    NewWindow->Mirrored = true;

    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){

        NewWindow->MainWindow[i] = LouDrsdCreateClip(
            0,
            (Desktop->MainWindow[i]->Height + Desktop->MainWindow[i]->Y) - 35,
            Desktop->MainWindow[i]->Width,
            35,
            192,192,192, 0xFF
        );

    }
    return NewWindow;
}



static PWINDOW_HANDLE CreateCanvasButton(
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
    PWINDOW_HANDLE NewWindow = LouGlobalUserMallocType(WINDOW_HANDLE);

    if(ParrentHandle){
        PWINDOW_HANDLE Parrent = (PWINDOW_HANDLE)ParrentHandle;
        if(Parrent->Mirrored || MirrorAllScreens){
            NewWindow->MainWindow = LouGlobalUserMallocArray(PDRSD_CLIP, Parrent->PlaneCount);
            NewWindow->PlaneCount = Parrent->PlaneCount;
            PANNYA_CANVAS_BUTTON_PARAM Params = (PANNYA_CANVAS_BUTTON_PARAM)Parameter;
            for(size_t i = 0 ; i < NewWindow->PlaneCount; i++){
                if(Params->CanvasDataId == PNG){
                    NewWindow->MainWindow[i] = AnnyaCreateClipFromPng(Params->CanvasData);
                    NewWindow->MainWindow[i]->X = Parrent->MainWindow[i]->X + X;
                    NewWindow->MainWindow[i]->Y = Parrent->MainWindow[i]->Y + Y;
                }
            }

        }

    }
    return NewWindow;
}

static 
PWINDOW_HANDLE 
AwmCreateWinAPIWindow(
    DWORD       ExStyle,
    LPCSTR      ClassName,
    LPCSTR      WindowName,
    DWORD       Style,
    int         X,
    int         Y,
    int         Width,
    int         Height,
    HWND        ParrentHandle,
    HMENU       Menu,
    HINSTANCE   Instance,
    LPVOID      Parameters
){

    LouPrint("AwmCreateWinAPIWindow\n");
    while(1);
    return 0x00;
}

USER32_API
HWND
CreateWindowExA(
    DWORD       ExStyle,
    LPCSTR      ClassName,
    LPCSTR      WindowName,
    DWORD       Style,
    int         X,
    int         Y,
    int         Width,
    int         Height,
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
    }else if(!strcmp(ClassName, CANVAS_BUTTON)){
        NewWindow = CreateCanvasButton(
            ExStyle,
            ClassName,
            WindowName,
            Style,
            X, Y,
            Width,
            Height,
            ParrentHandle,
            Menu,
            Instance,
            Parameter
        );
    }else{
        NewWindow = AwmCreateWinAPIWindow(
            ExStyle,
            ClassName,
            WindowName,
            Style,
            X,Y,
            Width, 
            Height,
            ParrentHandle,
            Menu,
            Instance,
            Parameter
        );
    }

    if(NewWindow){
        NewWindow->WindowStyle = Style;
        NewWindow->ExtendedWindowStyle = ExStyle;
        NewWindow->WindowClass = ClassName;
        NewWindow->WindowName = WindowName;
        NewWindow->WinApiHandleChecksum = NewWindow;
        if(strcmp(ClassName, TRAY_WINDOW)){
            AwmHookCalbackToWindow(
                NewWindow, 
                WindowModificationWndProc
            );
        }
        AwmInitializeWindowToTracker((PWINDOW_HANDLE)ParrentHandle, NewWindow);
        return (PWINDHANDLE)NewWindow;
    }

    LouPrint("CreateWindowExA");
    while(1);
    return 0x00;
}

USER32_API
HWND 
CreateWindowA(
    LPCSTR      ClassName,
    LPCSTR      WindowName,
    DWORD       Style,
    int         X,
    int         Y,
    int         Width,
    int         Height,
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
