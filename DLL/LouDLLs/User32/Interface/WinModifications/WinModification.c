#include "WinModification.h"

__declspec(dllimport)
void LouDrsdDrawLine32(
    PDRSD_CLIP Clip, 
    UINT32 X1, UINT32 Y1,
    UINT32 X2, UINT32 Y2, 
    UINT32 Color
);

void UpdateWindowToDesktop(PWINDOW_HANDLE WindowHandle);
void CalculateRedraws(int64_t X, int64_t Y, int64_t Width, int64_t Height);

void AwmHandleStartButtonEvent(PWINDOW_HANDLE StartNutton, bool Click);
void AwmHandelFileExplorerEvent(PWINDOW_HANDLE Handle, bool Click);
USER32_API
BOOL 
UpdateWindow(
    HWND WindowHandle
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

#define WINDOW_DEFACTO_MOVABLE_REQUIREMENT  (WS_CAPTION | WS_SYSMENU) //required for movment
#define WINDOW_HAS_MOVMENT_DISQUALIFIERS    (WS_DISABLED | WS_CHILD)//disqualifes movment

static bool WindowGrabbed = false;
static PWINDOW_HANDLE GrabbedWindow = 0x00;

static void AwmCheckMovableWindowLbuttonDownEvent(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam){
    UINT16 X = (uintptr_t)lParam & 0xFFFF;
    UINT16 Y = ((uintptr_t)lParam >> 16) & 0xFFFF;

    for(size_t i = 0 ; i < ((PWINDOW_HANDLE)WindowHandle)->PlaneCount; i++){
        if((Y < 25) && (X < (((PWINDOW_HANDLE)WindowHandle)->MainWindow[i]->Width - (6 + 18)))){
            GrabbedWindow = WindowHandle;
            WindowGrabbed = true;
            return;
        }
    }

}

PWINDOW_HANDLE AwmCheckIfWindowIsGrabbed(){
    if(!WindowGrabbed){
        return 0x00;
    }
    return GrabbedWindow;
}

void AwmSignalEndofGrabEvent(){
    WindowGrabbed = false;
}


LRESULT WindowModificationWndProc(WNDPROC LastFunc, HWND WindowHandle, UINT32 Message, WPARAM wParam, LPARAM lParam){
    PWINDOW_HANDLE TmpWindow = (PWINDOW_HANDLE)WindowHandle;
    switch(Message){
        case WM_LBUTTON_DOWN:{
            if(!strcmp(TmpWindow->WindowName, "StartButton")){
                AwmHandleStartButtonEvent((PWINDOW_HANDLE)WindowHandle, true);
            }
            else if(!strcmp(TmpWindow->WindowName, "FileExplorer")){
                AwmHandelFileExplorerEvent((PWINDOW_HANDLE)WindowHandle, true);
            }else{
                if ((TmpWindow->WindowStyle & WINDOW_DEFACTO_MOVABLE_REQUIREMENT) &&
                    !(TmpWindow->WindowStyle & WINDOW_HAS_MOVMENT_DISQUALIFIERS)) {
                    if(WindowGrabbed){
                        break;
                    }
                    AwmCheckMovableWindowLbuttonDownEvent(LastFunc, WindowHandle, Message, wParam, lParam);
                }
                if(!(TmpWindow->WindowStyle & WINDOW_HAS_MOVMENT_DISQUALIFIERS) && (!WindowGrabbed)){
                    UpdateWindowToDesktop(TmpWindow);
                    for(size_t i = 0 ; i < TmpWindow->PlaneCount; i++){
                        CalculateRedraws(
                            TmpWindow->MainWindow[i]->X, 
                            TmpWindow->MainWindow[i]->Y, 
                            TmpWindow->MainWindow[i]->Width, 
                            TmpWindow->MainWindow[i]->Height
                        );                
                    }
                    UpdateWindow(
                        TmpWindow
                    );

                }
            }

            break;
        }

    }
    return 0;
}

