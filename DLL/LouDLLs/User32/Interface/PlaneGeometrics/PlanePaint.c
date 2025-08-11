#include "../Awm.h"

extern AWM_PLANE_TRACKER PlaneTracker;
extern bool MirrorAllScreens;


void CalculateRedrawsMirrored(PDRSD_PLANE_QUERY_INFORMATION PlaneInfo, PDRSD_CLIP Clip){

}

void AwmUpdateSubWindowToScreen(PWINDOW_HANDLE Window, INT64 X, INT64 Y, INT64 Width, INT64 Height){

    INT64 Tx, Ty, Tw, Th;
    for(size_t i = 0 ; i < Window->PlaneCount; i++){
        LouUpdateShadowClipSubState(
            Window->MainWindow[i], 
            0, 0, 
            Window->MainWindow[i]->Width, Window->MainWindow[i]->Height
        );
    }

}


void AwmRedrawArea(PWINDOW_HANDLE Window, INT64 X, INT64 Y, INT64 Width, INT64 Height){
    AwmUpdateSubWindowToScreen(Window, X, Y, Width, Height);
    PCHILD_WINDOW_TRACKER Tmp = &Window->Children;
    while(Tmp->Peers.NextHeader){
        Tmp = (PCHILD_WINDOW_TRACKER)Tmp->Peers.NextHeader;
        AwmRedrawArea(Tmp->Child, X, Y, Width, Height);
    }
}