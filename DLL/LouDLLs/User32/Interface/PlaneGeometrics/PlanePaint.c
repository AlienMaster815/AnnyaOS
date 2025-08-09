#include "../Awm.h"

extern AWM_PLANE_TRACKER PlaneTracker;
extern bool MirrorAllScreens;


void CalculateRedrawsMirrored(PDRSD_PLANE_QUERY_INFORMATION PlaneInfo, PDRSD_CLIP Clip){

}


void AwmUpdateWindowToScreen(PWINDOW_HANDLE Window){
    size_t PlaneCount = Window->PlaneCount;
    if(MirrorAllScreens || Window->Mirrored){
        for(size_t i = 0 ; i < PlaneCount; i++){
            CalculateRedrawsMirrored(
                &PlaneTracker.PlaneInformation[i],
                Window->MainWindow[i]
            );
        }
    }
}