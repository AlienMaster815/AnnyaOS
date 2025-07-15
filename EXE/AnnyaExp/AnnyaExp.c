// Annya.exp.cpp : Defines the entry point for the application.
//x86_64-w64-mingw32-gcc -shared -o AnnyaExp.exe AnnyaExp.c -m64 -nostdlib -nodefaultlibs -L../../UserLibraries -lLouDll -luser32 -I../../Include

#include "AnnyaExp.h"

static SYSTEM_STATE_STACK StateStack = {0};

LRESULT WndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam);

//typedef LRESULT (*ANNYA_WINDOW_CALLBACK)(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam);

static ANNYA_DESKTOP_SETUP_PACKET InterfaceSetup = {0};


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

    LouPrint("AnnyaExp:Entering Main Loop\n");
    while(1){
        AwmUpdateState(&StateStack);
    }
    return (int)-1;

}


LRESULT WndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam){

    

}