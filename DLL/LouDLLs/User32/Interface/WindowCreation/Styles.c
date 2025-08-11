#include "WinCreation.h"

__declspec(dllimport)
void LouDrsdDrawLine32(
    PDRSD_CLIP Clip, 
    INT64 X1, INT64 Y1,
    INT64 X2, INT64 Y2, 
    UINT32 Color
);

__declspec(dllimport)
void LouDrsdPutPixel32(
    PDRSD_CLIP Clip,
    INT64 X, INT64 Y,
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