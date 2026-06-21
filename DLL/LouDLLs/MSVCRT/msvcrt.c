#include "msvcrt.h"

MSVCRT_API int _commode = COMMODE_O_NO_COMMIT;
MSVCRT_API int _fmode = FMODE_O_TEXT;
static int AppType = 0;
static string Path = "";

MSVCRT_API
void
__C_specific_handler(){
    LouPrint("__C_specific_handler()\n");
    while(1);
}

MSVCRT_API
void 
__getmainargs(
    int*            ArgCount,
    char***         Argv,
    char***         Env,
    int             DoWildCard,
    PSTARTUPINFOA   StartupInfo
){
    LouPrint("__getmainargs()\n");
    while(1);
}

MSVCRT_API
void
__initenv(){
    LouPrint("__initenv()\n");
    while(1);
}

MSVCRT_API
void 
__iob_func(){
    LouPrint("__iob_func()\n");
    while(1);
}

MSVCRT_API
void 
__set_app_type(
    int Type
){
    AppType = Type;
    switch(Type){
        case SET_APP_TYPE_CONSOLE_APP:{
            //TODO Initialize Application to a Console API
            LouPrint("__set_app_type() _CONSOLE\n");
            while(1);
        }
        default:
            break;
    }
}

MSVCRT_API
void 
__setusermatherr(){
    LouPrint("__setusermatherr()\n");
    while(1);
}

MSVCRT_API
void 
_acmdln(){
    LouPrint("_acmdln()\n");
    while(1);
}

MSVCRT_API
void
_amsg_exit(){
    LouPrint("_amsg_exit()\n");
    while(1);
}

MSVCRT_API
void
_cexit(){
    LouPrint("_cexit()\n");
    while(1);
}



MSVCRT_API
void 
_initterm(
    PVFV* StartFunction,
    PVFV* EndFunction
){
    for(; StartFunction < EndFunction; StartFunction++){
        if(*StartFunction){
            (*StartFunction)();
        }
    }
}

MSVCRT_API
void 
_ismbblead(){
    LouPrint("_ismbblead()\n");
    while(1);
}

MSVCRT_API
void 
_onexit(){
    LouPrint("_onexit()\n");
    while(1);
}

MSVCRT_API
void 
abort(){
    LouPrint("abort()\n");
    while(1);
}

MSVCRT_API
void* 
calloc(size_t count, size_t size){
    size_t total = count * size;
    void* ptr = LouGeneralAllocateMemory((UINT64)total);
    if (ptr) memset(ptr, 0, total);
    return ptr;
}

MSVCRT_API
void 
exit(){
    LouPrint("exit()\n");
    while(1);
}

MSVCRT_API
void 
fprintf(){
    LouPrint("fprintf()\n");
    while(1);
}

MSVCRT_API
void 
free(void* ptr){
    if (ptr) LouFree(ptr);
}

MSVCRT_API
void
fwrite(){
    LouPrint("fwrite()\n");
    while(1);
}

MSVCRT_API
void* 
malloc(size_t size){
    return LouGeneralAllocateMemory((UINT64)size);
}

MSVCRT_API
void 
memcpy(){
    LouPrint("memcpy()\n");
    while(1);
}

MSVCRT_API
void 
signal(){
    LouPrint("signal()\n");
    while(1);
}

MSVCRT_API
void 
strlen(){
    LouPrint("strlen()\n");
    while(1);
}

MSVCRT_API
void 
strncmp(){
    LouPrint("strncmp()\n");
    while(1);
}

MSVCRT_API
void 
vfprintf(){
    LouPrint("vfprintf()\n");
    while(1);
}

MSVCRT_API
BOOL 
DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){

    switch(ul_reason_for_call){
        case DLL_PROCESS_ATTACH:{



            LouPrint("MSVCRT.DLL Attatched To New Process\n");
            break;
        }
    }

    return true;
}