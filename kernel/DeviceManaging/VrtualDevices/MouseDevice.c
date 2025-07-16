#include <LouAPI.h>

static PSYSTEM_STATE_STACK SystemState = 0x00;
//static bool FirstDraw = true;

void LouKeMouseMoveEventUpdate(int64_t X, int64_t Y, BOOL RightClick, BOOL LeftClick){
    if(SystemState){
        SystemState->MouseState.MouseX += X;
        SystemState->MouseState.MouseY += Y;
    }
    PLOUSINE_USER_SHARED_MESSAGE Message = LouKeCreateNewUserMessage(
        MOUSE_EVENT_TYPE,
        HIGH_PRIORITY
    );
 
    Message->MouseEvent.X = X;
    Message->MouseEvent.Y = Y;
    Message->MouseEvent.RightClick = RightClick;
    Message->MouseEvent.LeftClick = LeftClick;
    LouKeDispatchNewUserMessage(
        Message
    );

}



void LouKeUpdateMouseState(PSYSTEM_STATE_STACK State){
    SystemState = State;
}