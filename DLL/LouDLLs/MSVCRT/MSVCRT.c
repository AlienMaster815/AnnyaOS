#include "MSVCRT.h"

void InitializeMsvcrtHeap();

MSVCRT_API
void* msvcrt_heap_alloc(
    uint64_t AllocationFlags,
    size_t AllocationSize
);

void MsvcInitializeLockSystem();

MSVCRT_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    MsvcInitializeLockSystem();
    InitializeMsvcrtHeap();
    return TRUE;
}


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
int* _errno(){
    LouPrint("_errno()\n");
    while(1);
    return 0;
}

MSVCRT_API
void _initterm(FunctionVector Begining, FunctionVector End){
    //LouPrint("_initterm()\n");
    void (**Functions)() = (void (**)())Begining;

    while (Functions < (void (**)())End) { 
        if (*Functions) {
            (*Functions)();
        }
        Functions++; 
    }
    //LouPrint("_initterm() STATUS_SUCCESS\n");
}



MSVCRT_API
void _lseeki64(){
    LouPrint("_lseeki64()\n");
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
void fputc(){
    LouPrint("fputc()\n");
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
void memchr(){
    LouPrint("memchr()\n");
    while(1);
}

__declspec(dllimport)
void*
LouMemCpy(
    void* OutStream,
    void* InStream,
    size_t ByteCount
);

MSVCRT_API 
size_t memcpy(void* To, void* From, size_t Size){
    LouMemCpy(To, From, Size);
    return  Size;
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
size_t strlen(const char* str) {
    const char* ptr = str;
    while (*ptr != '\0') {
        ++ptr;
    }
    return ptr - str;
}

MSVCRT_API
int strncmp(const char* str1, const char* str2, size_t n) {

    // Compare characters until we reach the specified number of characters (n)
    while (n > 0) {
        // Compare the current characters in both strings
        char c1 = *str1++;
        char c2 = *str2++;

        // If the characters are equal or both are null terminators, continue
        if (c1 == c2 || c1 == '\0' || c2 == '\0') {
            // If we've compared n characters or reached the end of either string, return 0
            if (n == 1 || (c1 == '\0' && c2 == '\0')) {
                return 0;
            }
        }
        else {
            // The characters are not equal, return the difference
            return c1 - c2;
        }

        // Decrement the remaining characters to compare
        n--;
    }

    // If we've reached here, the first n characters are equal

    return 0;
}

MSVCRT_API
int strcmp(const char* str1, const char* str2) {

    // Compare characters until we reach the specified number of characters (n)
    while (1) {
        // Compare the current characters in both strings
        char c1 = *str1++;
        char c2 = *str2++;

        // If the characters are equal or both are null terminators, continue
        if (c1 == c2 || c1 == '\0' || c2 == '\0') {
            // If we've compared n characters or reached the end of either string, return 0
            if (c1 == '\0' && c2 == '\0') {
                return 0;
            }
        }
        else {
            // The characters are not equal, return the difference
            return c1 - c2;
        }
    }

    // If we've reached here, the first n characters are equal

    return 0;
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
