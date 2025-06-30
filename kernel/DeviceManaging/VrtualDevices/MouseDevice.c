#include <LouAPI.h>

static PSYSTEM_STATE_STACK SystemState = 0x00;
//static bool FirstDraw = true;

void LouKeMouseMoveEventUpdate(int64_t X, int64_t Y){
    if(SystemState){
        SystemState->MouseState.MouseX += X;
        SystemState->MouseState.MouseY += Y;
    }
}


void LouKeMouseClickEventUpdate(bool Right, bool Left){
    if(SystemState){
        SystemState->MouseState.RightClick = Right;
        SystemState->MouseState.LeftClick = Left;
    }
}


void LouKeUpdateMouseState(PSYSTEM_STATE_STACK State){
    SystemState = State;
}