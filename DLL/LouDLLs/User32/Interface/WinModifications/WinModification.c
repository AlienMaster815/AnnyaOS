#include "WinModification.h"

__declspec(dllimport)
void LouDrsdDrawLine32(
    PDRSD_CLIP Clip, 
    INT64 X1, INT64 Y1,
    INT64 X2, INT64 Y2, 
    UINT32 Color
);


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



#define WINDOW_DEFACTO_MOVABLE_REQUIREMENT  (WS_CAPTION | WS_SYSMENU) //required for movment
#define WINDOW_HAS_MOVMENT_DISQUALIFIERS    (WS_DISABLED | WS_CHILD)//disqualifes movment




LRESULT WindowModificationWndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam){

    return 0;
}

