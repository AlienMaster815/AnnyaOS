#include "kernel32.h"

KERNEL32_API
void 
DeleteCriticalSection(
    PVOID   CriticalSection
){
    LouPrint("DeleteCriticalSection()\n");
    while(1);
}

KERNEL32_API
void 
EnterCriticalSection(
    PVOID   CriticalSection
){
    LouPrint("EnterCriticalSection()\n");
    while(1);
}

KERNEL32_API
BOOL 
DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){


    return true;
}