#include "../Awm.h"

extern AWM_PLANE_TRACKER PlaneTracker;
extern bool MirrorAllScreens;


void CalculateRedrawsMirrored(PDRSD_PLANE_QUERY_INFORMATION PlaneInfo, PDRSD_CLIP Clip){

}

void AwmUpdateSubWindowToScreen(PWINDOW_HANDLE Window, INT64 X, INT64 Y, INT64 Width, INT64 Height){

    if(Window->Mirrored){
        for(size_t i = 0 ; i < Window->PlaneCount; i++){
            LouUpdateShadowClipSubState(Window->MainWindow[i], X, Y, Width, Height);
        }
    }

}