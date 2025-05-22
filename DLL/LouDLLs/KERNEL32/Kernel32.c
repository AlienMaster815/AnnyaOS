#define _KERNEL32_
#include <Annya.h>

#define KERNEL32_API __declspec(dllexport)

KERNEL32_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}


KERNEL32_API
void DeleteCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection){
    LouPrint("DeleteCriticalSection()\n");
    while(1);
}

KERNEL32_API
NTSTATUS 
EnterCriticalSection(
    PMSVC_CRITICAL_SECTION CriticalSection
){
    return RtlEnterCriticalSection(CriticalSection);//tailcall
}

KERNEL32_API
void GetLastError(){
    LouPrint("GetLastError()\n");
    while(1);
}

__declspec(dllimport)
void InitializeCriticalSectionEx(PMSVC_CRITICAL_SECTION CriticalSection, uint32_t Reserved, uint32_t Flags);


KERNEL32_API
void InitializeCriticalSection(){
    LouPrint("InitializeCriticalSection()\n");
    while(1);
}

KERNEL32_API
void IsDBCSLeadByteEx(){
    LouPrint("IsDBCSLeadByteEx()\n");
    while(1);
}

KERNEL32_API
void LeaveCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection){
    RtlLeaveCriticalSection(CriticalSection);
}

KERNEL32_API
void MultiByteToWideChar(){
    LouPrint("MultiByteToWideChar()\n");
    while(1);
}

KERNEL32_API
void Sleep(){
    LouPrint("Sleep()\n");
    while(1);
}

KERNEL32_API
void TlsGetValue(){
    LouPrint("TlsGetValue()\n");
    while(1);
}

KERNEL32_API
void VirtualProtect(){
    LouPrint("VirtualProtect()\n");
    while(1);
}

KERNEL32_API
void VirtualQuery(){
    LouPrint("VirtualQuery()\n");
    while(1);
}

KERNEL32_API
void WideCharToMultiByte(){
    LouPrint("WideCharToMultiByte()\n");
    while(1);
}

static mutex_t LoadLibraryAMutex;

KERNEL32_API
HANDLE LoadLibraryA(string DllName){
    MutexLock(&LoadLibraryAMutex);
    uint64_t KulaPacket[3] = {0};
    KulaPacket[1] = (uint64_t)DllName;
    while(KulaPacket[0] == 0){
        LouCALL(LOULOADLIBRARYA, (uint64_t)&KulaPacket, 0);
    }
    MutexSynchronize(&LoadLibraryAMutex);
    return (HANDLE)KulaPacket[2];
}

KERNEL32_API 
void ReleaseLoadLibraryALock(){
    MutexUnlock(&LoadLibraryAMutex);
}

KERNEL32_API
void LoadLibraryW(wchar_t* DllName){

    LouPrint("LoadLibraryW()\n");
    while(1);
}



KERNEL32_API
void LoadLibraryExA(
    string DllName, 
    HANDLE File, 
    DWORD Flags
){

    LouPrint("LoadLibraryExA()\n");
    while(1);
}


KERNEL32_API
void LoadLibraryExyW(
    wchar_t* DllName, 
    HANDLE File, 
    DWORD Flags
){

    LouPrint("LoadLibraryExW()\n");
    while(1);
}