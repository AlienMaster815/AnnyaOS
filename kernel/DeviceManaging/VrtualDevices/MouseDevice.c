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



void LouKeUpdateMouseState(PSYSTEM_STATE_STACK State){
    SystemState = State;
}
