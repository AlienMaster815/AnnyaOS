#include "kernel32.h"



KERNEL32_API
void
GetStartupInfoA(
    PVOID StartupInfoA
){
    LouPrint("GetStartupInfoA()\n");
    while(1);
}

KERNEL32_API
DWORD 
GetLastError(){
    LouPrint("GetLastError()\n");
    while(1);
    return 0x00;
}

KERNEL32_API
void 
InitializeCriticalSection(
    PVOID   CriticalSection
){
    LouPrint("InitializeCriticalSection()\n");
    while(1);
}

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
void 
LeaveCriticalSection(
    PVOID   CriticalSection
){
    LouPrint("LeaveCriticalSection()\n");
    while(1);
}

KERNEL32_API
void
SetUnhandledExceptionFilter(){
    LouPrint("SetUnhandledExceptionFilter()\n");
    while(1);
}

KERNEL32_API
void 
Sleep(){
    LouPrint("Sleep()\n");
    while(1);
}

KERNEL32_API
void 
TlsGetValue(){
    LouPrint("TlsGetValue()\n");
    while(1);
}

KERNEL32_API
void 
VirtualProtect(){
    LouPrint("VirtualProtect()\n");
    while(1);
}

KERNEL32_API
void 
VirtualQuery(){
    LouPrint("VirtualQuery()\n");
    while(1);
}

KERNEL32_API
BOOL 
DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){


    return true;
}