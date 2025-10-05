#include <Compiler.h>

LPWSTR LouKeForkWcsStr(LPWSTR Str){
    size_t Len = wcslen(Str);
    LPWSTR New = LouKeMallocArray(WCHAR, Len + 1, KERNEL_GENERIC_MEMORY);
    New[Len] = L'\0';
    wcscpy(New, Str);
    return New;
}

LPWSTR LouKeForkWcsStr_s(LPWSTR Str, size_t Len){
    LPWSTR New = LouKeMallocArray(WCHAR, Len + 1, KERNEL_GENERIC_MEMORY);
    New[Len] = L'\0';
    wcsncpy(New, Str, Len);
    return New;
}