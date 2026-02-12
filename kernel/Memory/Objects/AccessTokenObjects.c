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