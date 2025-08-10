#include "WinCreation.h"

__declspec(dllimport)
void LouDrsdDrawLine32(
    PDRSD_CLIP Clip, 
    UINT32 X1, UINT32 Y1,
    UINT32 X2, UINT32 Y2, 
    UINT32 Color
);

__declspec(dllimport)
void LouDrsdPutPixel32(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y,
    UINT32 Color
);

extern PDRSD_CLIP XButtonClip; 
//0,0, SCREEN_WIDTH, SCREEN_HEIGHT,



void AwmDrawOverlappedWindow(
    PWINDOW_HANDLE WindowHandle
){

}

void AwmInitializeWindowStyle(
    PWINDOW_HANDLE  Window,
    DWORD           ExStyle, 
    DWORD           Style
){



}