#include "msvcrt.h"

MSVCRT_API
void
__C_specific_handler(){
    LouPrint("__C_specific_handler()\n");
    while(1);
}

MSVCRT_API
void 
__getmainargs(){
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
__set_app_type(){
    LouPrint("__set_app_type()\n");
    while(1);
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
_commode(){
    LouPrint("_commode()\n");
    while(1);
}

MSVCRT_API
void 
_fmode(){
    LouPrint("_fmode()\n");
    while(1);
}

MSVCRT_API
void 
_initterm(){
    LouPrint("_initterm()\n");
    while(1);
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
void 
calloc(){
    LouPrint("calloc()\n");
    while(1);
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
free(){
    LouPrint("free()\n");
    while(1);
}

MSVCRT_API
void
fwrite(){
    LouPrint("fwrite()\n");
    while(1);
}

MSVCRT_API
void 
malloc(){
    LouPrint("malloc()\n");
    while(1);
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


    return true;
}