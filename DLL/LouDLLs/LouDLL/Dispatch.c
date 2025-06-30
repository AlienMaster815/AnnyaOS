#include "LouDll.h"

int LouPrint(char* Str, ...);

LOUDLL_API
void LouGetSystemUpdate(PSYSTEM_STATE_STACK StateStack){
    uint64_t KulaPacket[2] = {0};
    KulaPacket[1] = (uint64_t)StateStack;
    while(!KulaPacket[0]){
        LouCALL(LOUGETSYSTEMSTATE, (uint64_t)&KulaPacket, 0);
    }
}