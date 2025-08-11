#include "../Awm.h"

extern AWM_PLANE_TRACKER PlaneTracker;
extern bool MirrorAllScreens;


void CalculateRedrawsMirrored(PDRSD_PLANE_QUERY_INFORMATION PlaneInfo, PDRSD_CLIP Clip){

}

void AwmUpdateSubWindowToScreen(PWINDOW_HANDLE Window, INT64 X, INT64 Y, INT64 Width, INT64 Height){

    if((Window->Mirrored) || (MirrorAllScreens)){
        INT64 Tx, Ty, Tw, Th;
        for(size_t i = 0 ; i < Window->PlaneCount; i++){
            if ((X >= (Window->MainWindow[i]->X + Window->MainWindow[i]->Width))  || ((X + Width)  <= Window->MainWindow[i]->X) ||
                (Y >= (Window->MainWindow[i]->Y + Window->MainWindow[i]->Height)) || ((Y + Height) <= Window->MainWindow[i]->Y)) {
                continue;
            }
            Tx = MAX(X, Window->MainWindow[i]->X);
            Ty = MAX(Y, Window->MainWindow[i]->Y);
            Tw = MIN((Width + X) - Tx, Window->MainWindow[i]->Width);
            Th = MIN((Height + Y) - Ty, Window->MainWindow[i]->Height);
            if (Tw <= 0 || Th <= 0){
                continue;
            }
            LouUpdateShadowClipSubState(
                Window->MainWindow[i], 
                Tx - Window->MainWindow[i]->X, Ty - Window->MainWindow[i]->Y, 
                Tw, Th
            );
        }
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