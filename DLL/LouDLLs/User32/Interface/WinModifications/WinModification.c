#include "WinModification.h"

__declspec(dllimport)
void LouDrsdDrawLine32(
    PDRSD_CLIP Clip, 
    UINT32 X1, UINT32 Y1,
    UINT32 X2, UINT32 Y2, 
    UINT32 Color
);


void AwmHandleStartButtonEvent(PWINDOW_HANDLE StartNutton, bool Click);
void AwmHandelFileExplorerEvent(PWINDOW_HANDLE Handle, bool Click);

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

void 
AwmWindowDrawLine(
    PWINDOW_HANDLE  WindowHandle,
    INT64           X1,
    INT64           Y1,
    INT64           X2,
    INT64           Y2,
    UINT8           R,
    UINT8           G,
    UINT8           B,
    UINT8           A
){
    SIZE PlaneCount = WindowHandle->PlaneCount;
    SIZE i = 0;
    UINT32 Color = DRSD_CORE_TRANSLATE_COLOR(R, G, B, A);
    for(; i < PlaneCount; i++){
        LouDrsdDrawLine32(
            WindowHandle->MainWindow[i], 
            X1, Y1, 
            X1 + X2 >= WindowHandle->MainWindow[i]->Width ? WindowHandle->MainWindow[i]->Width - X1 : X2, 
            Y1 + Y2 >= WindowHandle->MainWindow[i]->Height ? WindowHandle->MainWindow[i]->Height - Y2 : Y2, 
            Color
        );
    }
}

LRESULT WindowModificationWndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam){
    PWINDOW_HANDLE TmpWindow = (PWINDOW_HANDLE)WindowHandle;
    switch(Message){
        case WM_LBUTTON_DOWN:{
            if(!strcmp(TmpWindow->WindowName, "StartButton")){
                AwmHandleStartButtonEvent((PWINDOW_HANDLE)WindowHandle, true);
            }
            if(!strcmp(TmpWindow->WindowName, "FileExplorer")){
                AwmHandelFileExplorerEvent((PWINDOW_HANDLE)WindowHandle, true);
            }
            break;
        }
    }
    return 0;
}