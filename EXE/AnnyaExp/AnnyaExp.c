// Annya.exp.cpp : Defines the entry point for the application.
//x86_64-w64-mingw32-gcc -shared -o AnnyaExp.exe AnnyaExp.c -m64 -nostdlib -nodefaultlibs -L../../UserLibraries -lLouDll -luser32 -I../../Include

#include "AnnyaExp.h"

#define ANNYAEXP_API __declspec(dllexport)


static SYSTEM_STATE_STACK StateStack = {0};

ANNYAEXP_API LRESULT WndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam);

//typedef LRESULT (*ANNYA_WINDOW_CALLBACK)(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam);

static ANNYA_DESKTOP_SETUP_PACKET InterfaceSetup = {0};

ANNYAEXP_API
DWORD 
AnnyaExplorerFileManager(PVOID Args){
    PANNYA_EXPLORER_INIT_PACKET InitPacket = (PANNYA_EXPLORER_INIT_PACKET)Args;
    HWND ExplorerFmWindow = CreateWindowA(
        ANNYA_GENERIC_WINDOW,
        "File Explorer",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        10,
        10,
        400,
        400,
        0x00,
        0x00,
        InitPacket->Instance,
        0x00
    );

    ShowWindow(ExplorerFmWindow, SW_SHOW);
    UpdateWindow(ExplorerFmWindow); 

    HANDLE Message = 0x00;
    while(LouUserGetMessage(&Message, ANY_EVENT_TYPE, ANY_PRIORITY)){
        LouUserDispatchMessage(Message);
    }

    LouGlobalUserFree(Args);
    return 0;
}

ANNYAEXP_API
int 
WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     CommandLine,
    int       CmdShow 
){
    LouPrint("AnnyaExp Created With Instance:%h\n", hInstance);

    InterfaceSetup.WindowCallback = WndProc;

    LouExitDosMode();
    InitializeAwmUserSubsystem(hInstance, &InterfaceSetup);

    HANDLE Message = 0x00;

    LouPrint("AnnyaExp:Entering Main Loop\n");
    while(LouUserGetMessage(&Message, ANY_EVENT_TYPE, ANY_PRIORITY)){
        LouUserDispatchMessage(Message);
    }
    return (int)-1;

}

ANNYAEXP_API
LRESULT 
WndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam){

    

}