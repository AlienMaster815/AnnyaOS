#include "../Awm.h"

extern int64_t DesktopCurrentX;
extern int64_t DesktopCurrentY;
extern int64_t DesktopCurrentWidth;
extern int64_t DesktopCurrentHeight;
extern AWM_PLANE_TRACKER PlaneTracker;

static INT64 vDesktopCurrentWidth = 0;
static INT64 vDesktopCurrentHeight = 0;

void InitializePlaneTracker(){
    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){
        DesktopCurrentWidth += PlaneTracker.PlaneInformation[i].Width;
        if(PlaneTracker.PlaneInformation[i].Height > DesktopCurrentHeight){
            DesktopCurrentHeight = PlaneTracker.PlaneInformation[i].Height;
        }
    }
    vDesktopCurrentWidth = DesktopCurrentWidth * 3;
    vDesktopCurrentHeight = DesktopCurrentHeight * 3;

    INT64 Tmp = DesktopCurrentWidth;
    for(size_t i = 0; i < PlaneTracker.PlaneCount; i++){
        //LouPrint("PlaneX:%d::PlaneY:%d\n", Tmp, DesktopCurrentHeight);
        PlaneTracker.PlaneInformation[i].X = Tmp;
        PlaneTracker.PlaneInformation[i].Y = DesktopCurrentHeight;
        Tmp += PlaneTracker.PlaneInformation[i].Width;
    }



    //LouPrint("Desktop  Width:%d ::  Height:%d\n", DesktopCurrentWidth, DesktopCurrentHeight);
    //LouPrint("Desktop vWidth:%d :: vHeight:%d\n", vDesktopCurrentWidth, vDesktopCurrentHeight);

}