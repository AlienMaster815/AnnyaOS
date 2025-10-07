#include <Compiler.h>

#define C1_UPPER		                    0x0001
#define C1_LOWER		                    0x0002
#define C1_DIGIT		                    0x0004
#define C1_SPACE		                    0x0008
#define C1_PUNCT		                    0x0010
#define C1_CNTRL		                    0x0020
#define C1_BLANK		                    0x0040
#define C1_XDIGIT		                    0x0080
#define C1_ALPHA		                    0x0100
#define C1_defineD		                    0x0200

static const unsigned short wctypes[256] = {
    //0x00 
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    0x0020, 0x0068, 0x0028, 0x0028, 0x0028, 0x0028, 0x0020, 0x0020,
    //0x10 
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    //0x20 
    0x0048, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    //0x30 
    0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084,
    0x0084, 0x0084, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    //0x40 
    0x0010, 0x0181, 0x0181, 0x0181, 0x0181, 0x0181, 0x0181, 0x0101,
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
    //0x50 
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
    0x0101, 0x0101, 0x0101, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    //0x60 
    0x0010, 0x0182, 0x0182, 0x0182, 0x0182, 0x0182, 0x0182, 0x0102,
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102,
    //0x70 
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102,
    0x0102, 0x0102, 0x0102, 0x0010, 0x0010, 0x0010, 0x0010, 0x0020,
    //0x80
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    //0x90
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    //0xA0
    0x0048, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    //0xB0
    0x0010, 0x0010, 0x0014, 0x0014, 0x0010, 0x0010, 0x0010, 0x0010,
    0x0010, 0x0014, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    //0xC0
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
    //0xD0
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0010,
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0102,
    //0xE0
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102,
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102,
    //0xF0
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0010,
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102
};

int 
Lou_iswctype(
    WCHAR           Wc,
    unsigned short  Type
){
    if(Wc > 256)return 0;
    return wctypes[Wc] & Type;
}

int 
Lou_iswspace(
    WCHAR Wc
){
    return Lou_iswctype(Wc, C1_SPACE);
}


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

void PrintDocumentBuffer(LPWSTR Str, size_t Length){
    for(size_t i = 0 ; i < Length; i++){
        printf("%c", (char)Str[i]);
    }
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
    if(!Str || !Sub || !*Sub){
        return 0x00;
    }

    size_t sublen = Lou_wcslen(Sub);
    if(sublen > Length){
        return 0x00;
    }

    for(size_t i = 0; i + sublen <= Length && Str[i]; i++) {
        if (Lou_wcsncmp(&Str[i], Sub, sublen) == 0) {
            return &Str[i];
        }
    }
    return 0x00;
}

