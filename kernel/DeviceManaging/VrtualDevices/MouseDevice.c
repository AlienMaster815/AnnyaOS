#include <LouAPI.h>


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

void LouKeMouseUpdateInput(PLOUSINE_USER_SHARED_MESSAGE Message, INT64 X, INT64 Y, BOOL RightClick, BOOL LeftClick){

    if(MutexIsLocked(&Message->MessageMutex)){
        return;
    }

    Message->MouseEvent.X += X;
    Message->MouseEvent.Y += Y;

    Message->MouseEvent.RightClick = RightClick;
    Message->MouseEvent.LeftClick = LeftClick;
    
    LouKeMouseMoveEventUpdate(Message);

}


void LouKeInitializeMouseHandling(){
    LouKeCreateWorkQueue(0x00, SUBSYSTEM_WORK, "MouseWork");
}