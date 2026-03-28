//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

const WCHAR DESKTOP_WINDOW_CLASS_NAME[] =  L"AnnyaExp Desktop Window Class";

LRESULT CALLBACK DesktopWindowProcedure(HWND Window, UINT Message, WPARAM WordParam, LPARAM LongParam);

static HBRUSH DefaultDesktopBackGround; 

int WINAPI WinMain(
    HINSTANCE   Instance,
    HINSTANCE   PrevInstance,
    LPSTR       CommandLine,
    int         nCmdShow
) {
    
    DefaultDesktopBackGround = CreateSolidBrush(RGB(0, 128, 128)); 
    WNDCLASS Wc = {0};
    Wc.lpfnWndProc = DesktopWindowProcedure;
    Wc.hInstance = Instance;
    Wc.lpszClassName = DESKTOP_WINDOW_CLASS_NAME;
    Wc.hbrBackground = DefaultDesktopBackGround;
    
    RegisterClass(&Wc);

    HWND DesktopWindow = CreateWindowEx(
        0,
        DESKTOP_WINDOW_CLASS_NAME,
        L"AnnyaExp Desktop Window",
        WS_POPUP | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        600,
        480,
        NULL,
        NULL,
        Instance,
        NULL
    );

    if(!DesktopWindow){
        return 0x00;
    }

    ShowWindow(DesktopWindow, nCmdShow);
    UpdateWindow(DesktopWindow);

    MSG Message = {0};

    while(GetMessage(&Message, NULL, 0 , 0 ) > 0){
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }

    return 0;
}

LRESULT 
CALLBACK 
DesktopWindowProcedure(
    HWND    Window, 
    UINT    Message, 
    WPARAM  WordParam, 
    LPARAM  LongParam
){

    switch(Message){
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        //case WM_PAINT:{
        //    PAINTSTRUCT Ps;
        //    HDC Hdc = BeginPaint(Window, &Ps);
        //    FillRect(Hdc, &Ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
        //    EndPaint(Window, &Ps);
        //    return 0;
        //}
    }

    return DefWindowProc(Window,Message, WordParam, LongParam);
}
