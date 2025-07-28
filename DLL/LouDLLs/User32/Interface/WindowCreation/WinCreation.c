#include "WinCreation.h"

void InitializeWindowToWindowManager(PWINDOW_HANDLE WindowHandle);
SIZE AwmGetPlaneCount();

extern HANDLE (*AnnyaPaintClipWithBmp)(HANDLE, HANDLE, size_t, size_t, size_t, size_t);
extern HANDLE (*AnnyaCreateClipFromPng)(void*,HANDLE);
extern HANDLE BackgroundImage;
extern int64_t DesktopCurrentWidth;
extern int64_t DesktopCurrentHeight;
//0,0, SCREEN_WIDTH, SCREEN_HEIGHT,

PDRSD_PLANE_QUERY_INFORMATION AwmGetPlaneInformation();

static void AddPngToWindow(
    PWINDOW_HANDLE Window, 
    HANDLE Png,
    INT64 X,
    INT64 Y
){
    Window->WinApiHandleChecksum = (HWND)Window; 
    Window->PlaneCount = AwmGetPlaneCount();
    Window->MainWindow = LouGlobalUserMallocArray(PDRSD_CLIP, Window->PlaneCount);
    PDRSD_PLANE_QUERY_INFORMATION Info = AwmGetPlaneInformation();
    Window->ClipTreeHandle = LouGlobalUserMallocArray(AWM_CLIP_TREE, Window->PlaneCount);
    
    for(SIZE i = 0; i < Window->PlaneCount; i++){
        Window->MainWindow[i] = AnnyaCreateClipFromPng((PVOID)Info[i].Plane, Png);
        Window->MainWindow[i]->X = X;
        Window->MainWindow[i]->Y = Y;
        Window->ClipTreeHandle[i].Clip = Window->MainWindow[i];
        Window->ClipTreeHandle[i].UpdateClipSubState = LouUpdateShadowClipSubState;
    } 
    AwmHookCalbackToWindow(Window, WindowModificationWndProc);
}

static void GenericWindowHandleInit(
    PWINDOW_HANDLE Window,
    INT64  X, 
    INT64  Y, 
    UINT32 Width, 
    UINT32 Height,
    UINT8 R, 
    UINT8 G, 
    UINT8 B,
    UINT8 A
){ 

    Window->WinApiHandleChecksum = (HWND)Window; 
    Window->PlaneCount = AwmGetPlaneCount();
    Window->MainWindow = LouGlobalUserMallocArray(PDRSD_CLIP,Window->PlaneCount);
    PDRSD_PLANE_QUERY_INFORMATION Info = AwmGetPlaneInformation();
    Window->ClipTreeHandle = LouGlobalUserMallocArray(AWM_CLIP_TREE, Window->PlaneCount);

    for(SIZE i = 0; i < Window->PlaneCount; i++){
        Window->MainWindow[i] = LouDrsdCreateClip(
            (PVOID)Info[i].Plane,
            X, Y, 
            Width, 
            Height,
            R, G, B, A
        );
        Window->ClipTreeHandle[i].Clip = Window->MainWindow[i];
        Window->ClipTreeHandle[i].UpdateClipSubState = LouUpdateClipSubState;
    } 
    AwmHookCalbackToWindow(Window, WindowModificationWndProc);
}

static HWND AwmCreateBackgroundWindow(){
    PWINDOW_HANDLE NewWindow = LouGlobalUserMallocType(WINDOW_HANDLE);
    NewWindow->WindowStyle = WS_VISIBLE | WS_DISABLED;
    GenericWindowHandleInit(NewWindow, 0, 0, DesktopCurrentWidth, DesktopCurrentHeight, 0, 128, 128, 255);
    size_t BgImageScalingY = 0;
    size_t BgImageScalingX = 0;

    SIZE ClipCount = NewWindow->PlaneCount;
    PDRSD_PLANE_QUERY_INFORMATION Info = AwmGetPlaneInformation();

    for(SIZE i = 0 ; i < ClipCount; i++){
        AwmGetImageScaleingCentered(
            ((PCODECS_TYPE_QUERY)BackgroundImage)->HandleInformation.ImageHandleData.Width, 
            ((PCODECS_TYPE_QUERY)BackgroundImage)->HandleInformation.ImageHandleData.Height, 
            Info[i].Width, 
            Info[i].Height,
            &BgImageScalingX, &BgImageScalingY
        );

        AnnyaPaintClipWithBmp(
            BackgroundImage, NewWindow->MainWindow[i], 
            AwmGetImageCenteredX(((PCODECS_TYPE_QUERY)BackgroundImage)->HandleInformation.ImageHandleData.Width, Info[i].Width, BgImageScalingX),
            AwmGetImageCenteredY(((PCODECS_TYPE_QUERY)BackgroundImage)->HandleInformation.ImageHandleData.Height, Info[i].Height, BgImageScalingY),
            BgImageScalingX, BgImageScalingY
        );
    }

    return(HWND)NewWindow;
}

static HWND AwmCreateTaskbarWindow(
    DWORD       Style,
    HWND        ParrentHandle,
    HMENU       Menu,
    HINSTANCE   Instance,
    LPVOID      Parameter
){
    PWINDOW_HANDLE NewWindow = LouGlobalUserMallocType(WINDOW_HANDLE);
    NewWindow->WindowStyle = Style;
    GenericWindowHandleInit(
        NewWindow,
        0,
        DesktopCurrentHeight - 35,
        DesktopCurrentWidth, 
        35,
        192, 192, 192, 255
    );

    return (HWND)NewWindow;
}

HWND AwmCreateCanvasButton(
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
    NewWindow->WindowStyle = Style;

    switch(((PANNYA_CANVAS_BUTTON_PARAM)Parameter)->CanvasDataId){
        case PNG:{
            AddPngToWindow(
                NewWindow,
                ((PANNYA_CANVAS_BUTTON_PARAM)Parameter)->CanvasData,
                X,
                Y
            );
        }
    }

    return (HWND)NewWindow;
}

bool AwmIsClassFromAnnyaOs(string ClassName){
    if((!strcmp(ClassName, DEKSTOP_BACKGROUND)) || (!strcmp(ClassName, TRAY_WINDOW)) || (!strcmp(ClassName, CANVAS_BUTTON))){
        return true;
    }
    return false;
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
        return AwmCreateBackgroundWindow();
    }else if(!strcmp(ClassName, TRAY_WINDOW)){
        NewWindow = AwmCreateTaskbarWindow(
            Style,
            ParrentHandle,
            Menu,
            Instance,
            Parameter
        );
    }else if(!strcmp(ClassName, CANVAS_BUTTON)){
        NewWindow = AwmCreateCanvasButton(
            ClassName, WindowName,
            Style,
            X, Y,
            Width, Height,
            ParrentHandle,
            Menu,
            Instance,
            Parameter
        );
    }else if(!strcmp(ClassName, ANNYA_GENERIC_WINDOW)){
        NewWindow = LouGlobalUserMallocType(WINDOW_HANDLE);
        GenericWindowHandleInit(
            NewWindow,
            X, Y,
            Width, Height,
            192, 
            192, 
            192,
            255
        );
    }

    if(NewWindow){
        NewWindow->WindowName = WindowName;
        NewWindow->WindowStyle = Style;
        NewWindow->ExtendedWindowStyle = ExStyle;
        NewWindow->WindowClass = ClassName;
        NewWindow->Parameter = Parameter;
        NewWindow->ParentWindow = (PWINDOW_HANDLE)ParrentHandle;
        NewWindow->Menu = Menu;
        NewWindow->Instance = Instance;
        if(!AwmIsClassFromAnnyaOs(ClassName)){
            AwmInitializeWindowStyle(NewWindow, ExStyle, Style);
        }
        InitializeWindowToWindowManager(NewWindow);
        LouPrint("Created New Window:%s\n", WindowName);
        return NewWindow;
    }

    LouPrint("CreateWindowA()\n");
    while(1);
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
