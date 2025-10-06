#include <Compiler.h>

size_t
Lou_wcslen(LPCWSTR str){
    const WCHAR *s = str;
    while (*s) s++;
    return s - str;
}

int 
Lou_wcsncmp(
    LPWSTR String1,
    LPWSTR String2,
    size_t Length
){
    if(Length <= 0){
        return 0;
    }
    while((--Length > 0) && (*String1 && (*String1 == *String2))){
        String1++;
        String2++;
    }
    return *String1 - *String2;
}

LPWSTR 
Lou_wcschr(
    LPWSTR Str,
    WCHAR  Token
){
    do{ 
        if(*Str == Token){
            return (LPWSTR)(UINTPTR)Str;
        } 
    }while(*Str++);
    return 0x00;
}


LPWSTR
Lou_wcspbrk(
    LPWSTR Str,
    LPWSTR Accept
){
    for(;*Str;Str++){
        if(Lou_wcschr(Accept, *Str)){
            return (LPWSTR)(UINTPTR)Str;
        }
    }
    return 0x00;
}

int
Lou_wcscmp(
    LPWSTR Str1,
    LPWSTR Str2
){
    while(*Str1 && (*Str1 == *Str2)){
        Str1++;
        Str2++;
    }
    return *Str1 - *Str2;
}

LPWSTR 
Lou_wcsncpy(
    LPWSTR String1,
    LPWSTR String2,
    size_t Length
){
    size_t i;
    for(i = 0 ; i < Length; i++){
        if(!(String1[i] = String2[i]))break;
    }
    for(; i < Length; i++){
        String1[i] = 0;
    }
    return String1;
}

LPWSTR
Lou_wcscpy(
    LPWSTR Destination,
    LPWSTR Source
){
    LPWSTR Tmp = Destination;
    while((*Tmp++ = *Source++));
    return Destination;
}

LPWSTR LouKeForkWcsStr(LPWSTR Str){
    size_t Len = Lou_wcslen(Str);
    LPWSTR New = LouKeMallocArray(WCHAR, Len + 1, KERNEL_GENERIC_MEMORY);
    New[Len] = L'\0';
    Lou_wcscpy(New, Str);
    return New;
}

LPWSTR LouKeForkWcsStr_s(LPWSTR Str, size_t Len){
    LPWSTR New = LouKeMallocArray(WCHAR, Len + 1, KERNEL_GENERIC_MEMORY);
    New[Len] = L'\0';
    Lou_wcsncpy(New, Str, Len);
    return New;
}

int LouKeCompareLpwstrFromRaw(
    LOU_STRING  Search, 
    LPWSTR      RawStream, 
    size_t      Length
){
    LPWSTR New = LouKeMallocArray(WCHAR, Length + 1, KERNEL_GENERIC_MEMORY);
    for(size_t i = 0 ; i < Length; i++){
        New[i] = (WCHAR)Search[i];
    }
    int Result = Lou_wcsncmp(New, RawStream, Length);
    LouKeFree(New);
    return Result;
}

void SanityCheck(LPWSTR Str, size_t Length){
    for(size_t i = 0 ; i < Length; i++){
        printf("%c", (char)Str[i]);
    }
    printf("\n");
}

LPWSTR LouKeCreateLpwstr(LOU_STRING Str){
    size_t Length = strlen(Str);
    LPWSTR Result = LouKeMallocArray(WCHAR, Length + 1 , KERNEL_GENERIC_MEMORY);
    for(size_t i = 0 ; i < Length; i++){
        Result[i] = (WCHAR)Str[i];
    }
    return Result;
}

LPWSTR 
Lou_wcsstr(
    LPWSTR Str,
    LPWSTR Sub
){
    while(*Str){
            LPWSTR P1 = Str;
            LPWSTR P2 = Sub;
            while((*P1) && (*P2) && (*P1 == *P2)){
                P1++;
                P2++;
            }
            if(!*P2){
                return (LPWSTR)Str;
            }

        Str++;
    }
    return 0x00;
}

LPWSTR 
Lou_wcsnstr(
    LPWSTR Str,
    LPWSTR Sub,
    size_t Length
){
    for(size_t i = 0 ; i < Length; i++){
            LPWSTR P1 = Str;
            LPWSTR P2 = Sub;
            while((*P1) && (*P2) && (*P1 == *P2)){
                P1++;
                P2++;
            }
            if(!*P2){
                return (LPWSTR)Str;
            }

        Str++;
    }
    return 0x00;
}
