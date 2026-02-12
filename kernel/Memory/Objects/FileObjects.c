#include "ObjectManager.h"

LOUSTATUS LouKeRegisterFileToObjectManager(
    FILE*                   File,
    LOUSTR                  FileName,
    int                     MaxHandles,
    PSECURITY_DESCRIPTOR    SecurityDescriptor
){
    return LouKeRegisterObjectToObjectManager(
        (PVOID)File,
        fsize(File),
        FileName,
        MaxHandles,
        SecurityDescriptor
    );
}