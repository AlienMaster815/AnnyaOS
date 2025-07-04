// Annya.exp.cpp : Defines the entry point for the application.
//x86_64-w64-mingw32-gcc -shared -o AnnyaExp.exe AnnyaExp.c -m64 -nostdlib -nodefaultlibs -L../../UserLibraries -lLouDll -luser32 -I../../Include

#include "AnnyaExp.h"

static SYSTEM_STATE_STACK StateStack = {0};

int WndProc(void* hwnd, uint32_t uMsg, void* WParam, void* LParam);

int WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     CommandLine,
    int       CmdShow 
){
    LouPrint("AnnyaExp Created With Instance:%h\n", hInstance);

    LouExitDosMode();
    InitializeAwmUserSubsystem();
    LouGetSystemUpdate(&StateStack);

    while(1){
        AwmUpdateState(&StateStack);
    }
    return (int)-1;

}


int WndProc(void* hwnd, uint32_t uMsg, void* WParam, void* LParam){

}