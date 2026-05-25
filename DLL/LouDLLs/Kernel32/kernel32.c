#include "kernel32.h"

ANNA_IMPORT PUSER_PROCESS_HEAP LouDllHeap;

KERNEL32_API
ATOM
AddAtomW(
    LPCWSTR String
){
    ATOM Result = 0x00;
    LOUSTATUS Status = LouAddAtomEx(String, wcslen(String), &Result, ADD_ATOM_FLAG_LOCAL);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    return Result;
}

KERNEL32_API
ATOM 
AddAtomA(
    LPCSTR String
){
    ATOM Result = 0x00;
    PWSTR NewString = (PWSTR)LouRtlAllocateHeapEx(LouDllHeap, (strlen(String) + 1) * sizeof(WCHAR), GET_ALIGNMENT(WCHAR), 0x00);
    LouMemSet(NewString, 0, (strlen(String) + 1) * sizeof(WCHAR));
    for(SIZE i = 0 ; String[i]; i++){
        NewString[i] = (WCHAR)String[i];
    }
    Result = AddAtomW(NewString);
    LouRtlFreeHeap(LouDllHeap, NewString, 0x00);
    return Result;
}


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

    if(ul_reason_for_call == DLL_PROCESS_ATTACH){
        LouPrint("KERNEL32.DLL:Attatched To New Process\n");
    }

    return true;
}