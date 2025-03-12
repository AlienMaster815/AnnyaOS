#define _MSVCRT_
//#include <Annya.h>

#define MSVCRT_API __declspec(dllexport)

__declspec(dllimport)
int LouPrint(char* Str, ...);

MSVCRT_API
void ___lc_codepage_func(){
    LouPrint("___lc_codepage_func()\n");
    while(1);
}

MSVCRT_API 
void ___mb_cur_max_func(){
    LouPrint("___mb_cur_max_func()\n");
    while(1);
}

MSVCRT_API
void __iob_func(){
    LouPrint("__iob_func()\n");
    while(1);
}

MSVCRT_API
void _amsg_exit(){
    _amsg_exit("_amsg_exit()\n");
    while(1);
}

MSVCRT_API
void _errno(){
    LouPrint("_errno()\n");
    while(1);
}

MSVCRT_API
void _initterm(){
    LouPrint("_initterm()\n");
    while(1);
}


MSVCRT_API 
void _lock(){
    LouPrint("_lock()\n");
    while(1);
}

MSVCRT_API
void _lseeki64(){
    LouPrint("_lseeki64()\n");
    while(1);
}

MSVCRT_API
void _unlock(){
    LouPrint("_unlock()\n");
    while(1);
}

MSVCRT_API
void _wopen(){
    LouPrint("_wopen()\n");
    while(1);
}

MSVCRT_API
void abort(){
    LouPrint("abort()\n");
    while(1);
}

MSVCRT_API
void calloc(){
    LouPrint("calloc()\n");
    while(1);
}

MSVCRT_API
void fputc(){
    LouPrint("fputc()\n");
    while(1);
}

MSVCRT_API
void free(){
    LouPrint("free()\n");
    while(1);
}

MSVCRT_API
void fwrite(){
    LouPrint("fwrite()\n");
    while(1);
}

MSVCRT_API 
void localeconv(){
    LouPrint("localeconv()\n");
    while(1);
}

MSVCRT_API
void malloc(){
    LouPrint("malloc()\n");
    while(1);
}

MSVCRT_API
void memchr(){
    LouPrint("memchr()\n");
    while(1);
}

MSVCRT_API 
void memcpy(){
    LouPrint("memcpy()\n");
    while(1);
}

MSVCRT_API 
void memmove(){
    LouPrint("memmove()\n");
    while(1);
}

MSVCRT_API 
void memset(){
    LouPrint("memset()\n"); 
    while(1);   
}

MSVCRT_API
void realloc(){
    LouPrint("realloc()\n");
    while(1);
}

MSVCRT_API
void strerror(){
    LouPrint("strerror()\n");
    while(1);
}

MSVCRT_API
void strlen(){
    LouPrint("strlen()\n");
    while(1);
}

MSVCRT_API
void strncmp(){
    LouPrint("strncmp()\n");
    while(1);
}

MSVCRT_API
void vfprintf(){
    LouPrint("vfprintf()\n");
    while(1);
}

MSVCRT_API
void wcslen(){
    LouPrint("wcslen()\n");
    while(1);
}

MSVCRT_API
void wcstombs(){
    LouPrint("wcstombs()\n");
    while(1);
}

MSVCRT_API
void _write(){
    LouPrint("_write()\n");
    while(1);
}

MSVCRT_API
void _read(){
    LouPrint("_read()\n");
    while(1);
}

MSVCRT_API
void _open(){
    LouPrint("_open()\n");
    while(1);
}

MSVCRT_API
void _close(){
    LouPrint("_close()\n");
    while(1);
}
