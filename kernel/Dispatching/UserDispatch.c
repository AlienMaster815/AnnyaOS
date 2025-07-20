#include <LouAPI.h>

static void (*SendUserMessage)(PLOUSINE_USER_SHARED_MESSAGE) = 0x00;

PLOUSINE_USER_SHARED_MESSAGE LouKeCreateNewUserMessage(
    LOUSINE_USER_MESSAGE_TYPE       MessageType,
    LOUSINE_USER_MESSAGE_PRIORITY   Priority
){
    if(!SendUserMessage){
        SendUserMessage = (void(*)(PLOUSINE_USER_SHARED_MESSAGE))LouKeLinkerGetAddress("LOUDLL.DLL", "SendMessageToUserMode");
    }
    PLOUSINE_USER_SHARED_MESSAGE NewMessage = LouKeMallocType(LOUSINE_USER_SHARED_MESSAGE, USER_GENERIC_MEMORY);
    NewMessage->MessageType = MessageType;
    NewMessage->MessagePriority = Priority;
    return NewMessage;
}

void LouKeDispatchNewUserMessage(
    PLOUSINE_USER_SHARED_MESSAGE Message
){
    if(!SendUserMessage){
        return;
    }
    SendUserMessage(Message);
}