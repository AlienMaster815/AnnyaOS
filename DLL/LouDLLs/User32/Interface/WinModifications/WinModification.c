#include "WinModification.h"

USER32_API
LOUSTATUS 
AwmHookCalbackToWindow(
    HWND WindowHandle, 
    ANNYA_WINDOW_CALLBACK Callback
){
    PWINDOW_HANDLE Window = (PWINDOW_HANDLE)WindowHandle;
    if(Window->WinApiHandleChecksum != WindowHandle){
        return STATUS_INVALID_PARAMETER;
    }
    MutexLock(&Window->CallbackMutex);
    ANNYA_WINDOW_CALLBACK* NewCallStack = LouGlobalUserMallocArray(ANNYA_WINDOW_CALLBACK, Window->CallbackCount + 1);
    LouMemCpy(NewCallStack, Window->WindowCallbacks, sizeof(ANNYA_WINDOW_CALLBACK) * Window->CallbackCount);
    NewCallStack[Window->CallbackCount] = Callback;
    LouGlobalUserFree(Window->WindowCallbacks);
    Window->WindowCallbacks = NewCallStack;
    Window->CallbackCount++;
    MutexUnlock(&Window->CallbackMutex);
    return STATUS_SUCCESS;
}

LRESULT WindowModificationWndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam){

    LouPrint("WindowModificationWndProc()\n");
    while(1);
}