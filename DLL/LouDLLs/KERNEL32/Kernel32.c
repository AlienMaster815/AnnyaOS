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
HANDLE LoadLibraryExA(
    string DllName, 
    HANDLE File, 
    DWORD Flags
){
    uint64_t KulaPacket[4] = {0};
    KulaPacket[1] = (uint64_t)DllName;
    KulaPacket[3] = (uint64_t)LouGlobalUserMallocType(mutex_t);
    MutexLock((mutex_t*)KulaPacket[3]);
    while(KulaPacket[0] == 0){
        LouCALL(LOULOADLIBRARYA, (uint64_t)&KulaPacket, 0);
    }
    MutexSynchronize((mutex_t*)KulaPacket[3]);
    LouGlobalUserFree((void*)KulaPacket[3]);
    return (HANDLE)KulaPacket[2];
}

KERNEL32_API
HANDLE LoadLibraryA(string DllName){
    return LoadLibraryExA(DllName, 0, 0);
}

KERNEL32_API 
void ReleaseLoadLibraryALock(mutex_t* Lock){
    MutexUnlock(Lock);
}

KERNEL32_API
void LoadLibraryW(wchar_t* DllName){

    LouPrint("LoadLibraryW()\n");
    while(1);
}


KERNEL32_API
void LoadLibraryExW(
    wchar_t* DllName, 
    HANDLE File, 
    DWORD Flags
){

    LouPrint("LoadLibraryExW()\n");
    while(1);
}


KERNEL32_API 
BOOL 
CloseHandle(HANDLE Handle){

    LouPrint("CloseHandle()\n");
    while(1);
    return true;
}

KERNEL32_API 
HANDLE 
CreateFileA(
    LPCSTR                    FileName,
    UINT32                    DesiredAccess,
    UINT32                    ShareMode,
    PVOID /*LPSECURITY_ATTRIBUTES*/     SecurityAttributes,
    UINT32                    CreationDisposition,
    UINT32                    FlagsAndAttributes,
    HANDLE                    TemplateFile
){

    LouPrint("CreateFileA()\n");
    while(1);
    return 0x00;
}

KERNEL32_API
HANDLE 
CreateFileMappingA(){


    LouPrint("CreateFileMappingA()\n");
    while(1);
    return 0x00;
}

KERNEL32_API
void 
GetFileSizeEx(){

    LouPrint("GetFileSizeEx()\n");
    while(1);   
}

KERNEL32_API
void
GetProcAddress(){
    LouPrint("GetProcAddress\n");
    while(1);  
}


KERNEL32_API
void* 
GetProcessHeap(){
    return AnnyaNtGetProcessHeap();
}


KERNEL32_API
void* 
HeapAlloc(PVOID Foo, uint64_t Bar, size_t Too){
    return RtlAllocateHeap(Foo, Bar, Too);
}

KERNEL32_API
void HeapFree(){

    LouPrint("LouFree\n");
    while(1);
}

KERNEL32_API
void
HeapReAlloc(){
    LouPrint("HeapReAlloc()\n");
    while(1);
}

KERNEL32_API
void
MapViewOfFile(){
    LouPrint("MapViewOfFile()\n");
    while(1);
}

KERNEL32_API
void 
ReadFile(){

    LouPrint("ReadFile\n");
    while(1);
}

KERNEL32_API
void 
UnmapViewOfFile(){

    LouPrint("UnmapViewOfFile()\n");
    while(1);
}
