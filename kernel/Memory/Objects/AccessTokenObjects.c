#include "ObjectManager.h"

LOUSTATUS LouKeZwRegisterAccessTokenToObjectManager(
    PLOUSINE_ACCESS_TOKEN   AccessToken,
    int                     MaxHandles
){
    return LouKeRegisterObjectToObjectManager(
        (PVOID)AccessToken,
        sizeof(LOUSINE_ACCESS_TOKEN),
        "LOUSINE_ACCESS_TOKEN",
        MaxHandles,
        0x00
    );
}

LOUSTATUS LouKeZwGetAccessTokenData(PLOUSINE_ACCESS_TOKEN* Out, HANDLE TokenHandle){
    if((!Out) || (!TokenHandle)){
        return STATUS_INVALID_PARAMETER;
    }
    POBJECT_HEADER Header = LouKeGetObjectHEaderFromHandle(TokenHandle);
    *Out = (PLOUSINE_ACCESS_TOKEN)Header->ObjectPointer;
    return STATUS_SUCCESS;
}