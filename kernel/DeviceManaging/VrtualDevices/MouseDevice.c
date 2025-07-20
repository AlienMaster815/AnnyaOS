#include <LouAPI.h>

static PSYSTEM_STATE_STACK SystemState = 0x00;
//static bool FirstDraw = true;

PLOUSINE_USER_SHARED_MESSAGE LouKeMouseAllocateMessageDevice(){
    return LouKeCreateNewUserMessage(
        MOUSE_EVENT_TYPE,
        HIGH_PRIORITY
    );
}

void LouKeMouseMoveEventUpdate(PLOUSINE_USER_SHARED_MESSAGE Message){
    LouKeDispatchNewUserMessage(
        Message
    );
}

void LouKeMouseUpdateInput(PLOUSINE_USER_SHARED_MESSAGE Message, INT32 X, INT32 Y, BOOL RightClick, BOOL LeftClick){

    if(Message->MouseEvent.X){
        Message->MouseEvent.X += X;
    }else{
        Message->MouseEvent.X = X;
    }
    if(Message->MouseEvent.Y){
        Message->MouseEvent.Y += Y;
    }else{
        Message->MouseEvent.Y = Y;
    }

    Message->MouseEvent.RightClick = RightClick;
    Message->MouseEvent.LeftClick = LeftClick;
    
    LouKeMouseMoveEventUpdate(Message);

}

void LouKeUpdateMouseState(PSYSTEM_STATE_STACK State){
    SystemState = State;
}
