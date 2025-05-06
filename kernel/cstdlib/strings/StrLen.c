#include <stddef.h>

size_t strlen(const char* str) {
    const char* ptr = str;
    while (*ptr != '\0') {
        ++ptr;
    }
    return ptr - str;
}


size_t wstrlen(const wchar_t* str){
    const wchar_t* ptr = str;
    while (*ptr != L'\0') {
        ++ptr;
    }
    return ptr - str;
}