#include "LouDll.h"

int LouPrint(char* Str, ...);
void LouYeildExecution();

LOUDLL_API
void LouGetSystemUpdate(PSYSTEM_STATE_STACK StateStack){
    uint64_t KulaPacket[2] = {0};
    KulaPacket[1] = (uint64_t)StateStack;
    while(!KulaPacket[0]){
        LouCALL(LOUGETSYSTEMSTATE, (uint64_t)&KulaPacket, 0);
    }
}

static LOUSINE_USER_SHARED_MESSAGE UserMessages = {0};
static mutex_t MessageMutex = {0};

LOUDLL_API
SET_OPTIMIZATION(3)
void 
SendMessageToUserMode(
    PLOUSINE_USER_SHARED_MESSAGE NewMessage
){
    PLOUSINE_USER_SHARED_MESSAGE Tmp = &UserMessages;
    MutexLock(&MessageMutex);
    while(Tmp->Peers.NextHeader){
        Tmp = (PLOUSINE_USER_SHARED_MESSAGE)Tmp->Peers.NextHeader;
        if((uintptr_t)Tmp == (uintptr_t)NewMessage){
            MutexUnlock(&MessageMutex);
            return;
        }
    }
    Tmp->Peers.NextHeader = (PListHeader)NewMessage;
    MutexUnlock(&MessageMutex);
}

LOUDLL_API
SET_OPTIMIZATION(3)
bool 
LouUserGetMessage(
    HANDLE*                         Message,
    LOUSINE_USER_MESSAGE_TYPE       Type,
    LOUSINE_USER_MESSAGE_PRIORITY   Priority
){
    MutexSynchronize(&MessageMutex);
    PLOUSINE_USER_SHARED_MESSAGE Prev = &UserMessages;
    PLOUSINE_USER_SHARED_MESSAGE Tmp = (PLOUSINE_USER_SHARED_MESSAGE)Prev->Peers.NextHeader;

    if (!Tmp) {
        LouYeildExecution();
        *Message = 0x00;
        return true;
    }

    while (Tmp) {
        if (!MutexIsLocked(&Tmp->MessageMutex)) {
            bool typeMatch    = (Type == ANY_EVENT_TYPE)    || (Tmp->MessageType == Type);
            bool priorityMatch = (Priority == ANY_PRIORITY) || (Tmp->MessagePriority == Priority);

            if (typeMatch && priorityMatch) {
                *Message = (HANDLE)Tmp;
                Prev->Peers.NextHeader = Tmp->Peers.NextHeader;
                MutexLock(&Tmp->MessageMutex);
                return true;
            }
        }

        Prev = Tmp;
        Tmp = (PLOUSINE_USER_SHARED_MESSAGE)Tmp->Peers.NextHeader;
    }
    LouYeildExecution();
    *Message = 0x00;
    return true;
}

static LOUSINE_MESSAGE_HANDLER MessageHandlers[LOUSINE_USER_MESSAGE_COUNT] = {
    0,
};

LOUDLL_API
SET_OPTIMIZATION(3)
void 
LouRegisterMouseHandler(
    LOUSINE_MESSAGE_HANDLER     MessageHandler,
    LOUSINE_USER_MESSAGE_TYPE   MessageType
){
    if(MessageType >= LOUSINE_USER_MESSAGE_COUNT){
        return;
    }
    MessageHandlers[MessageType] = MessageHandler;
}

LOUDLL_API
SET_OPTIMIZATION(3)
void
LouUserDispatchMessage(
    HANDLE MessageHandle
){
    PLOUSINE_USER_SHARED_MESSAGE Message = (PLOUSINE_USER_SHARED_MESSAGE)MessageHandle;
    if(!Message){
        LouYeildExecution();
        return;
    }
    if(MessageHandlers[Message->MessageType]){
        MessageHandlers[Message->MessageType](Message);
    }else{
        LouPrint("Handler For Message:%h Does Not Exist Message Not Handled\n", Message->MessageType);    
    }
    MutexUnlock(&Message->MessageMutex);
}
