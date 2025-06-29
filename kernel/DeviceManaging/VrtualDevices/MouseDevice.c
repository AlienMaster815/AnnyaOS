#include <LouAPI.h>

static inline void DrawMouse(int64_t x, int64_t y){

}

static inline void UnDrawMouse(int64_t x, int64_t y){

}

//static bool FirstDraw = true;

void LouKeMouseMoveEventUpdate(int64_t X, int64_t Y){

}


void LouKeMouseClickEventUpdate(bool Right, bool Left){

}

void MouseDrawWork(uint64_t NullDataDontUse){
    //if(!FirstDraw){
    //    UnDrawMouse(LastMouseXCursor, LastMouseYCursor);    
    //}else{
    //    FirstDraw = false;
    //}
    //LastMouseXCursor = MouseXCursor;
    //LastMouseYCursor = MouseYCursor;
    //DrawMouse(MouseXCursor, MouseYCursor);
    //LouKeDrsdSyncScreens();
}

void LouKeInitializeMouseManagemet(){
    //LouKeInitializeIntervalWork(
    //    MouseDrawWork,
    //    0x00,
    //    16
    //);
}