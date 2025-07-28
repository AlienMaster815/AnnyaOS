// Annya.exp.cpp : Defines the entry point for the application.
//x86_64-w64-mingw32-gcc -shared -o AnnyaExp.exe AnnyaExp.c -m64 -nostdlib -nodefaultlibs -L../../UserLibraries -lLouDll -luser32 -I../../Include

#include "AnnyaExp.h"

static SYSTEM_STATE_STACK StateStack = {0};

LRESULT WndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam);

//typedef LRESULT (*ANNYA_WINDOW_CALLBACK)(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam);

static ANNYA_DESKTOP_SETUP_PACKET InterfaceSetup = {0};


__declspec(dllexport)
DWORD AnnyaExplorerFileManager(PVOID Args){
    PANNYA_EXPLORER_INIT_PACKET InitPacket = (PANNYA_EXPLORER_INIT_PACKET)Args;
    
    //HWND TestWindow = CreateWindowA(
    //    ANNYA_GENERIC_WINDOW,
    //    "TestWindow",
    //    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    //    30,
    //    30,
    //    500,
    //    500,
    //    0x00,
    //    0x00,
    //    InitPacket->Instance,
    //    0x00
    //);

    //ShowWindow(TestWindow, SW_SHOW);
    //UpdateWindow(TestWindow); 

    HANDLE Message = 0x00;
    while(LouUserGetMessage(&Message, ANY_EVENT_TYPE, ANY_PRIORITY)){
        LouUserDispatchMessage(Message);
    }

    LouGlobalUserFree(Args);
    return 0;
}

int WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     CommandLine,
    int       CmdShow 
){
    LouPrint("AnnyaExp Created With Instance:%h\n", hInstance);

    InterfaceSetup.WindowCallback = WndProc;

    LouExitDosMode();
    InitializeAwmUserSubsystem(hInstance, &InterfaceSetup);
    LouGetSystemUpdate(&StateStack);

    HANDLE Message = 0x00;

    LouPrint("AnnyaExp:Entering Main Loop\n");
    while(LouUserGetMessage(&Message, ANY_EVENT_TYPE, ANY_PRIORITY)){
        LouUserDispatchMessage(Message);
    }
    return (int)-1;

}


LRESULT WndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam){

    

}