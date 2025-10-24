#include <LouAPI.h>

/*
 * NTDLL wide-char functions
 *
 * Copyright 2000 Alexandre Julliard
 * Copyright 2000 Jon Griffiths
 * Copyright 2003 Thomas Mertes
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */
 

#define WINAPI __stdcall

typedef int errno_t;
#define EINVAL      22
#define ERANGE      34
#define STRUNCATE   80

#define _TRUNCATE ((size_t)-1)


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

static 
int
wctoint(
    WCHAR Wc
){
    int i;
    static const WCHAR Zeroes[] = {
        0x0660, 0x06F0, 0x0966, 0x09E6, 0x0A66, 0x0AE6, 0x0B66, 0x0C66, 0x0CE6,
        0x0D66, 0x0E50, 0x0ED0, 0x0F20, 0x1040, 0x17E0, 0x1810, 0xFF10
    };

    if(('0' <= Wc) && (Wc <= '9')){
        return Wc - '0';
    }
    else if(('A' <= Wc) && (Wc <= 'Z')){
        return Wc - 'A' + 10;
    }
    else if(('a' <= Wc) && (Wc <= 'z')){
        return Wc - 'a' + 10;
    }
    for(i = 0 ; (i < 17) && (Wc >= Zeroes[i]); i++){
        if((Zeroes[i] <= Wc) && (Wc <= (Zeroes[i] + 9))){
            return Wc - Zeroes[i];
        }
    }
    return -1;
}


int
_wcsicmp(
    LPCWSTR String1,
    LPCWSTR String2
){
    size_t i = 0;
    for(;;){
	    WCHAR Char1 = ((String1[i] >= 'A') && (String1[i] <= 'Z')) ? String1[i] + 32 : String1[i]; 
    	WCHAR Char2 = ((String2[i] >= 'A') && (String2[i] <= 'Z')) ? String2[i] + 32 : String2[i];
        if((Char1 != Char2) || (!String1[i])){
  	        return (Char1 - Char2);
	    }
        i++;
    }
    return 0;
}


LPWSTR _wcslwr(
    LPWSTR Str
){
    LPWSTR Result = Str;
    for(;*Str; Str++){
        if((*Str >= 'A') && (*Str <= 'Z')){
	       *Str += ('a' - 'A');
        }
    }
    return Result;
}


size_t 
wcslen(LPCWSTR str){
    const WCHAR *s = str;
    while (*s) s++;
    return s - str;
}

size_t wcsnlen(const WCHAR *str, size_t len){
    const WCHAR *s;
    for (s = str; len && *s; s++, len--) ;
    return s - str;
}


errno_t
_wcslwr_s(
    LPWSTR Str, 
    size_t Length 
){
    if (!Str) return 22;
    else if (wcsnlen(Str, Length) == Length){
        *Str = 0;
        return 22;
    }
    _wcslwr(Str);
    return 0;
}


int
_wcsnicmp(LPWSTR str1, LPWSTR str2, size_t n){
    int Result = 0;
    for ( ; n > 0; n--, str1++, str2++){
        WCHAR ch1 = (*str1 >= 'A' && *str1 <= 'Z') ? *str1 + 32 : *str1;
        WCHAR ch2 = (*str2 >= 'A' && *str2 <= 'Z') ? *str2 + 32 : *str2;
        if ((Result = ch1 - ch2) ||  !*str1) break;
    }
    return Result;
}


LPWSTR 
_wcsupr(
    LPWSTR Str
){
    LPWSTR Result = Str;
    for(;*Str; Str++){
        if((*Str >= 'a') && (*Str <= 'z')){
            *Str += 'A' - 'a';
        }
    }    
    return Result;
}


errno_t 
_wcsupr_s(
    LPWSTR Str, 
    size_t Length
){
    if(!Str){
        return EINVAL;
    }
    else if(wcsnlen(Str, Length) == Length){
        *Str = 0;
        return EINVAL;
    }
    _wcsupr(Str);
    return 0;
}

 
LPWSTR
wcscpy(
    LPWSTR Destination,
    LPWSTR Source
){
    LPWSTR Tmp = Destination;
    while((*Tmp++ = *Source++));
    return Destination;
}


errno_t wcscpy_s(
    LPWSTR Destination,
    size_t Length, 
    LPWSTR Source
){
    size_t i;
    if((!Destination) || (!Length)){
        return EINVAL;
    }
    else if(!Source){
        *Destination = 0;
        return EINVAL;
    }

    for(i = 0 ; i < Length; i++){
        if(!(Destination[i] = Source[i]))return 0;
    }

    return ERANGE;
}


LPWSTR 
wcscat(
    LPWSTR Destination,
    LPWSTR Source
){
    wcscpy(Destination + wcslen(Destination), Source);
    return Destination;
}


errno_t
wcscat_s(
    LPWSTR Destination,
    size_t Length,
    LPWSTR Source
){

    size_t i , j;
    if((!Destination) || (!Length)){
        return EINVAL;
    }
    else if(!Source){
        *Destination = 0;
        return EINVAL;
    }
    for(i = 0; i < Length; i++){
        if(!Destination[i]){
            break;
        }
    }
    for(j = 0 ; (j + i) < Length; j++){
        if(!(Destination[j + i] = Source[j]))return 0;
    }
    *Destination = 0;
    return ERANGE;
}


LPWSTR 
wcschr(
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


int
wcscmp(
    LPWSTR Str1,
    LPWSTR Str2
){
    while(*Str1 && (*Str1 == *Str2)){
        Str1++;
        Str2++;
    }
    return *Str1 - *Str2;
}


size_t 
wcscspn(
    LPWSTR Str,
    LPWSTR Reject
){
    LPWSTR Tmp;
    for(Tmp = Str; *Tmp; Tmp++){
        if(wcschr(Reject, *Tmp)){
            break;
        }
    }
    return Tmp - Str;
}


LPWSTR 
wcsncat(
    LPWSTR Str1,
    LPWSTR Str2,
    size_t Length
){
    LPWSTR Result = Str1;

    while(*Str1){
        Str1++;
    }
    while(Length-- > 0){
        if(!(*Str1++ = *Str2++)){
            return Result;
        }
    }
    *Str1 = 0;
    return Result;
}


errno_t
wcsncat_s(
    LPWSTR Destination, 
    size_t Length, 
    LPWSTR Source, 
    size_t Count
){
    size_t i, j;
    if((!Destination) || (!Length)){
        return EINVAL;
    }
    if(!Count){
        return 0;
    }
    if(Source){
        *Destination = 0;
        return EINVAL;
    }
    for(i = 0; i < Length; i++){
        if(!(Destination[i])){
            break;
        }
    }
    if(i == Length){
        *Destination = 0;
        return EINVAL;
    }

    for(j = 0; (j + i) < Length; j++){
        if((Count == _TRUNCATE) && ((j + i) == (Length - 1))){
            Destination[j + i] = 0;
            return STRUNCATE;
        }
        else if((j == Count) || (!(Destination[j + i] = Source[j]))){
            Destination[j + i] = 0;
            return 0;
        }
    }
    *Destination = 0;
    return ERANGE;
}


int 
wcsncmp(
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
wcsncpy(
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


errno_t
wcsncpy_s(
    LPWSTR Destination,
    size_t Length,
    LPWSTR Source,
    size_t Count
){
    size_t i, End;
    if(!Count){
        if((Destination) && (Length)){
            *Destination = 0;
        }
        return 0x00;
    }
    else if((!Destination) || (!Length)){
        return EINVAL;
    } 
    else if(!Source){
        *Destination = 0;
        return EINVAL;
    }

    if((Count != _TRUNCATE) && (Count < Length)){
        End = Count;
    }else{
        End = Length - 1;
    }
    for(i = 0 ; i < End; i++){
        if(!(Destination[i] = Source[i]))return 0;
    }

    if(Count == _TRUNCATE){
        *Destination = 0;
        return STRUNCATE;
    }
    else if(End == Count){
        *Destination = 0;
        return 0;
    }
    *Destination = 0;
    return ERANGE;
}


LPWSTR 
wcsrchr(
    LPWSTR Str,
    WCHAR  Token
){
    LPWSTR Result = 0x00;
    do{
        if(*Str == Token){
            Result = (LPWSTR)(UINTPTR)Str;
        }
    }while(*Str++);
    return Result;
}


LPWSTR
wcspbrk(
    LPWSTR Str,
    LPWSTR Accept
){
    for(;*Str;Str++){
        if(wcschr(Accept, *Str)){
            return (LPWSTR)(UINTPTR)Str;
        }
    }
    return 0x00;
}



size_t
wcsspn(
    LPWSTR Str,
    LPWSTR Accept
){
    LPWSTR Tmp;
    for(Tmp = Str; *Tmp; Tmp++){
        if(!wcschr(Accept, *Tmp)){
            break;
        }
    }
    return Tmp - Str;
}


LPWSTR 
wcsstr(
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
wcsnstr(
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


LPWSTR 
wcstok(
    LPWSTR Str,
    LPWSTR Deliminator
){
    LPWSTR Next = 0x00;
    LPWSTR Result;

    if(!Str){
        if(!(Str = Next)){
            return  0x00;
        }
    }
    while((*Str) && (wcschr(Deliminator, *Str))){
        Str++;
    }
    if(!*Str){
        return 0x00;
    }
    Result = Str++;
    while((*Str) && (!wcschr(Deliminator, *Str))){
        Str++;
    }
    if(*Str){
        *Str++ = 0;
    }
    Next = Str;
    return Result;
}


LPWSTR 
wcstok_s(
    LPWSTR Str,
    LPWSTR Deliminator,
    LPWSTR* Context
){
    LPWSTR Next;
    if((!Deliminator) || (!Context)){
        return 0x00;
    }
    if(!Str){
        if(!(*Context)){
            return 0x00;
        }
        Str = *Context;
    }
    while(*Str && wcschr(Deliminator, *Str)){
        Str++;
    }
    if(!(*Str)){
        *Context = Str;
        return 0x00;
    }
    Next = Str + 1;
    while((*Next) && (!wcschr(Deliminator, *Next))){
        Next++;
    }
    if(*Next){
        *Next++ = 0;
    }
    *Context = Next;
    return Str;
}


size_t 
wcstombs(
    string Destination,
    LPWSTR Source,
    size_t Length
){
    return 0x00;
    /*DWORD Result;

    if(!Destination){
        RtlUnicodeToMultiByteSize(&Result, Source, wcslen(Source) * sizeof(WCHAR));
        return (size_t)Result;
    }else{
        if(Length <= 0){
            return 0x00;
        }
        RtlUnicodeToMultiByteN(Destination, Length, &Result, Source, wcslen(Source) * sizeof(WCHAR));
        if(Result < Length){
            Destination[Result] = 0;
        }
    }
    return Result;*/
}


size_t 
mbstowcs(
    LPWSTR Destination,
    string Source,
    size_t Length
){
    return 0x00;
    /*DWORD Result;
    if(!Destination){
        RtlMultiByteToUnicodeSize(&Result, Source, strlen(Source));
    }else{
        if(Length <= 0){
            return 0;
        }
        RtlMultiByteToUnicodeN(Destination, Length * sizeof(WCHAR), &Result, Source, strlen(Source));
        if((Result / sizeof(WCHAR)) < Length){
            Destination[Result / sizeof(WCHAR)] = 0;
        }
    }
    return Result / sizeof(WCHAR);*/
}


int 
iswctype(
    WCHAR           Wc,
    unsigned short  Type
){
    if(Wc > 256)return 0;
    return wctypes[Wc] & Type;
}


int 
iswalnum(
    WCHAR Wc
){
    return iswctype(Wc, C1_ALPHA | C1_UPPER | C1_LOWER | C1_DIGIT);
}


int 
iswalpha(
    WCHAR Wc
){
    return iswctype(Wc, C1_ALPHA | C1_UPPER | C1_LOWER);
}


int 
iswascii(
    WCHAR Wc
){
    return Wc < 0x80;
}


int 
iswdigit(
    WCHAR Wc
){  
    return iswctype(Wc, C1_DIGIT);
}


int
iswgraph(
   WCHAR Wc
){  
    return iswctype(Wc, C1_ALPHA | C1_UPPER | C1_LOWER | C1_DIGIT | C1_PUNCT);
}


int 
iswlower(
    WCHAR Wc
){
    return iswctype(Wc, C1_LOWER);
}


int 
iswprint(
    WCHAR Wc
){
    return iswctype(Wc, C1_ALPHA | C1_UPPER | C1_LOWER | C1_DIGIT | C1_PUNCT | C1_BLANK);
}


int 
iswspace(
    WCHAR Wc
){
    return iswctype(Wc, C1_SPACE);
}

 
int 
iswxdigit(
    WCHAR Wc
){
    return iswctype(Wc, C1_DIGIT);
}


long 
wcstol(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
){
    BOOL Negative = false;
    BOOL Empty = true;
    long Result = 0;

    if((Base < 0) || (Base == 1) || (Base > 36)){
        return 0;
    }
    if(End){
        *End = (LPWSTR)Str;
    }
    while(iswspace(*Str)){
        Str++;
    }
    if(*Str == '-'){
        Negative = false;
        Str++;
    }
    else if(*Str == '+'){
        Str++;
    }
    if(
        ((Base == 0) || (Base == 16)) && 
        (!wctoint(*Str)) && 
        ((Str[1] == 'x') || (Str[1] == 'X'))
    ){
        Base = 16;
        Str += 2;
    }
    if(Base == 0){
        Base = wctoint(*Str) ? 10 : 8;
    }
    while(*Str){
        int V = wctoint(*Str);
        if((V < 0) || (V >= Base)){
            break;
        }
        if(Negative){
            V = -V;
        } 
        Str++;
        Empty = false;

        if((!Negative) && ((Result > (MAXLONG / Base)) || ((Result * Base) > (MAXLONG - V)))){
            Result = MAXLONG;
        } 
        else if((Negative) && ((Result > (MINLONG / Base)) || ((Result * Base) > (MINLONG - V)))){
            Result = MINLONG;
        }
        else{
            Result = Result * Base + V;
        }
    }
    if((End) && (!Empty)){
        *End = (LPWSTR)Str;
    }
    return Result;
}


unsigned long 
wcstoul(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
){
    BOOL Empty = true;
    unsigned long Result = 0;

    if((Base < 0) || (Base == 1) || (Base > 36)){
        return 0;
    }
    if(End){
        *End = (LPWSTR)Str;
    }
    while(iswspace(*Str)){
        Str++;
    }
    if(*Str == '-'){
        Str++;
    }
    else if(*Str == '+'){
        Str++;
    }
    if(
        ((Base == 0) || (Base == 16)) && 
        (!wctoint(*Str)) && 
        ((Str[1] == 'x') || (Str[1] == 'X'))
    ){
        Base = 16;
        Str += 2;
    }
    if(Base == 0){
        Base = wctoint(*Str) ? 10 : 8;
    }
    while(*Str){
        int V = wctoint(*Str);
        if((V < 0) || (V >= Base)){
            break;
        }
        Str++;
        Empty = false;

        if((Result > (UINT32_MAX / Base)) || ((Result * Base) > (UINT32_MAX - V))){
            Result = UINT32_MAX;
        } 
        else{
            Result = Result * Base + V;
        }
    }
    if((End) && (!Empty)){
        *End = (LPWSTR)Str;
    }
    return Result;
}



INT64 
wcstoi64(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
){
    BOOL Negative = false;
    BOOL Empty = true;
    INT64 Result = 0;

    if((Base < 0) || (Base == 1) || (Base > 36)){
        return 0;
    }
    if(End){
        *End = (LPWSTR)Str;
    }
    while(iswspace(*Str)){
        Str++;
    }
    if(*Str == '-'){
        Negative = false;
        Str++;
    }
    else if(*Str == '+'){
        Str++;
    }
    if(
        ((Base == 0) || (Base == 16)) && 
        (!wctoint(*Str)) && 
        ((Str[1] == 'x') || (Str[1] == 'X'))
    ){
        Base = 16;
        Str += 2;
    }
    if(Base == 0){
        Base = wctoint(*Str) ? 10 : 8;
    }
    while(*Str){
        int V = wctoint(*Str);
        if((V < 0) || (V >= Base)){
            break;
        }
        if(Negative){
            V = -V;
        } 
        Str++;
        Empty = false;

        if((!Negative) && ((Result > (INT64_MAX / Base)) || ((Result * Base) > (INT64_MAX - V)))){
            Result = INT64_MAX;
        } 
        else if((Negative) && ((Result > (INT64_MIN / Base)) || ((Result * Base) > (INT64_MIN - V)))){
            Result = INT64_MIN;
        }
        else{
            Result = Result * Base + V;
        }
    }
    if((End) && (!Empty)){
        *End = (LPWSTR)Str;
    }
    return Result;
}


UINT64 
wcstoui64(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
){
    BOOL Empty = true;
    UINT64 Result = 0;

    if((Base < 0) || (Base == 1) || (Base > 36)){
        return 0;
    }
    if(End){
        *End = (LPWSTR)Str;
    }
    while(iswspace(*Str)){
        Str++;
    }
    if(*Str == '-'){
        Str++;
    }
    else if(*Str == '+'){
        Str++;
    }
    if(
        ((Base == 0) || (Base == 16)) && 
        (!wctoint(*Str)) && 
        ((Str[1] == 'x') || (Str[1] == 'X'))
    ){
        Base = 16;
        Str += 2;
    }
    if(Base == 0){
        Base = wctoint(*Str) ? 10 : 8;
    }
    while(*Str){
        int V = wctoint(*Str);
        if((V < 0) || (V >= Base)){
            break;
        }
        Str++;
        Empty = false;

        if((Result > (UINT64_MAX / Base)) || ((Result * Base) > (UINT64_MAX - V))){
            Result = UINT64_MAX;
        } 
        else{
            Result = Result * Base + V;
        }
    }
    if((End) && (!Empty)){
        *End = (LPWSTR)Str;
    }
    return Result;
}


LPWSTR 
_ultow(
    unsigned long   V, 
    LPWSTR          Str,
    int             Radix
){
    WCHAR   Buffer[33];
    LPWSTR  Position; 
    WCHAR   Digit;

    Position = &Buffer[32];
    *Position = '\0';

    do{
        Digit = V % Radix;
        V = V / Radix;
        if(Digit < 10){
            *--Position = '0' + Digit;
        }else{
            *--Position = 'a' + Digit - 10;
        }
    }while(V != 0L);

    if(Str != 0x00){
        memcpy(Str, Position, (&Buffer[32] - Position + 1) * sizeof(WCHAR));
    }
    return Str;
}


LPWSTR 
_ltow(
    long    V,
    LPWSTR  Str,
    int     Radix    
){
    ULONG   Val;
    int     Negative;
    WCHAR   Buffer[33];
    LPWSTR  Position;
    WCHAR   Digit;

    if((V < 0) && (Radix == 10)){
        Negative = 1;
        Val = -V;
    }
    else{
        Negative = 0;
        Val = V;
    }

    Position = &Buffer[32];
    *Position = '\0';

    do {
	    Digit = Val % Radix;
	    Val = Val / Radix;
	    if (Digit < 10) {
	        *--Position = '0' + Digit;
	    } else {
	        *--Position = 'a' + Digit - 10;
	    }
    } while (Val != 0L);
    if(Negative){
        *--Position = '-';
    }
    if(Str != 0x00){
        memcpy(Str, Position, (&Buffer[32] - Position + 1) * sizeof(WCHAR));
    }
    return Str;
}


LPWSTR
_itow(
    int     Value,
    LPWSTR  Str,
    int     Radix
){
    return _ltow(Value, Str, Radix);
}


LPWSTR 
_ui64tow(
    UINT64  Value,
    LPWSTR  Str,
    int     Radix
){
    WCHAR   Buffer[65];
    LPWSTR  Position;
    int     Digit;

    Position = &Buffer[64];
    *Position = '\0';

    do{
        Digit = Value % Radix;
        Value = Value / Radix;
        if(Digit < 10){
            *--Position = '0' + Digit;
        }else{
            *--Position = 'a' + Digit - 10;
        }
    }while(Value != 0L);
    if(Str != 0x00){
        memcpy(Str, Position, (&Buffer[64] - Position + 1) * sizeof(WCHAR));
    }
    return Str;
}


LPWSTR 
_i64tow(
    INT64   Value,
    LPWSTR  Str,
    int     Radix
){
    UINT64  Val;
    int     Negative;
    WCHAR   Buffer[65];
    LPWSTR  Position;
    int     Digit;

    if((Value < 0) && (Radix == 10)){
        Negative = 1;
        Val = -Value;
    }else{
        Negative = 0;
        Val = Value;
    }

    Position = &Buffer[64];
    *Position = '\0';

    do{
        Digit = Val % Radix;
        Val = Val / Radix;
        if(Digit < 10){
            *--Position = '0' + Digit;
        }else{
            *--Position = 'a' + Digit - 10;
        }
    }while(Val != 0L);

    if(Negative){
        *--Position = '-';
    }

    if(Str != 0x00){
        memcpy(Str, Position, (&Buffer[64] - Position + 1) * sizeof(WCHAR));
    }
    return Str;
}


errno_t
_ui64tow_s(
    UINT64  Value,
    LPWSTR  Str, 
    size_t  Length,
    int     Radix
){
    WCHAR   Buffer[65];
    LPWSTR  Position;   
    int     Digit;
    if((!Str) || (!Length)){
        return EINVAL;
    }
    else if((Radix < 2) || (Radix > 36)){
        *Str = 0;
        return EINVAL;
    }
    Position = &Buffer[64];
    *Position = 0;
    do{
        Digit = Value % Radix;
        Value = Value / Radix;
        if(Digit < 10){
            *--Position = '0' + Digit;
        }else{
            *--Position = 'a' + Digit - 10;
        }
    }while(Value != 0);
    if((size_t)(&Buffer[64] - Position) > (size_t)Length){
        *Str = 0;
        return ERANGE;
    }
    memcpy(Str, Position, (&Buffer[64] - Position) * sizeof(WCHAR));
    return 0;
}

errno_t
_ui64towUppr_s(
    UINT64  Value,
    LPWSTR  Str, 
    size_t  Length,
    int     Radix
){
    errno_t Result = _ui64tow_s(Value, Str, Length, Radix);
    if(Result){
        return Result;
    }
    return _wcsupr_s(Str, Length); 
}

errno_t
_ultow_s(
    unsigned long   Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
){
    return _ui64tow_s(Value, Str, Length, Radix);
}


errno_t
_i64tow_s(
    INT64   Value,
    LPWSTR  Str, 
    size_t  Length,
    int     Radix
){
    WCHAR   Buffer[65];
    LPWSTR  Position;   
    int     Digit;
    int     Negative;
    INT64   Val;

    if((!Str) || (!Length)){
        return EINVAL;
    }
    else if((Radix < 2) || (Radix > 36)){
        *Str = 0;
        return EINVAL;
    }

    Position = &Buffer[64];
    *Position = 0;

    if((Value < 0) && (Radix == 10)){
        Negative = 1;
        Val = -Value; 
    }else{
        Negative = 0;
        Val = Value;
    }

    do{
        Digit = Val % Radix;
        Val = Val / Radix;
        if(Digit < 10){
            *--Position = '0' + Digit;
        }else{
            *--Position = 'a' + Digit - 10;
        }
    }while(Val != 0);
    if(Negative){
        *--Position = '-';
    }
    if((size_t)(&Buffer[64] - Position) > (size_t)Length){
        *Str = 0;
        return ERANGE;
    }
    memcpy(Str, Position, (&Buffer[64] - Position) * sizeof(WCHAR));
    return 0;
}


errno_t
_ltow_s(
    long            Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
){
    if((Value < 0) && (Radix == 10)){
        return _i64tow_s((INT64)Value, Str, Length, Radix);
    }
    return _ui64tow_s((UINT64)Value, Str, Length, Radix);
}


errno_t
_itow_s(
    int             Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
){
    if((Value < 0) && (Radix == 10)){
        return _i64tow_s((INT64)Value, Str, Length, Radix);
    }
    return _ui64tow_s((UINT64)Value, Str, Length, Radix);
}


long 
_wtol(
    LPWSTR Str
){
    ULONG   TotalRun = 0;
    BOOL    Negative = false;
    if(*Str == '+'){
        Str++;
    }else if(*Str == '-'){
        Negative = true;
        Str++;
    }
    while((*Str >= '0') && (*Str <= '9')){
        TotalRun = TotalRun * 10 + *Str - '0';
        Str++;
    }
    return Negative ? -TotalRun : TotalRun;
}


int 
_wtoi(
    LPWSTR Str
){
    return (int)_wtol(Str);
}

 
UINT64
_wtoi64(
    LPWSTR Str
){
    UINT64  TotalRun = 0;
    BOOL    Negative = false;
    while(iswspace(*Str)){
        Str++;
    }
    if(*Str == '+'){
        Str++;
    }else if(*Str == '-'){
        Negative = true;
        Str++;
    }
    while((*Str >= '0') && (*Str <= '9')){
        TotalRun = TotalRun * 10 + *Str - '0';
        Str++;
    }
    return Negative ? -TotalRun : TotalRun;
}


errno_t
_wsplitpath_s(
    LPWSTR InPath, 
    LPWSTR Drive,
    size_t SzDrive,
    LPWSTR Directory,
    size_t SzDirectory,
    LPWSTR FileName,
    size_t SzFileName,
    LPWSTR Extention,
    size_t SzExtention
){
    LPWSTR Position;
    LPWSTR End;

    if(
        (!InPath) || ((!Drive) && (SzDrive)) || 
        ((Drive) && (!SzDrive)) || 
        ((!Directory) && (SzDirectory)) ||
        ((Directory) && (!SzDirectory)) ||
        ((!FileName) && (SzFileName)) ||
        ((FileName) && (!SzFileName)) ||
        ((!Extention) && (SzExtention)) ||
        ((Extention) && (!SzExtention))
    ){
        return EINVAL;
    }

    if((InPath[0]) && (InPath[1] == ':')){
        if(Drive){
            if(SzDrive <= 2){
                goto _SPLITPATH_ERROR;
            }
            Drive[0] = InPath[0];
            Drive[1] = InPath[1];
            Drive[2] = 0;
        }
        InPath += 2;
    }    
    else if(Drive){
        Drive[0] = '\0';
    }

    End = 0x00;

    for(Position = InPath; *Position; Position++){
        if((*Position == '/') || (*Position == '\\')){
            End = Position + 1;
        }
    }

    if(End){
        if(Directory){
            if((size_t)SzDirectory <= (size_t)(End - InPath)){
                goto _SPLITPATH_ERROR;
            }
            memcpy(Directory, InPath, (End - InPath) * sizeof(WCHAR));
            Directory[End - InPath] = 0;
        }
        InPath = End;
    }
    else if(Directory){
        *Directory = 0;
    }
    
    End = 0x00;

    for(Position = InPath; *Position; Position++){
        if(*Position == '.'){
            End = Position;
        }
    }

    if(!End){
        End = Position;
    }

    if(FileName){
        if((size_t)SzFileName <= (size_t)(End - InPath)){
            goto _SPLITPATH_ERROR;
        }
        memcpy(FileName, InPath, (End - InPath) * sizeof(WCHAR));
        FileName[End - InPath] = 0;
    }

    if(Extention){
        if(SzExtention <= wcslen(End)){
            goto _SPLITPATH_ERROR;
        }
        wcscpy(Extention, End);
    }
    return 0;

    _SPLITPATH_ERROR:
        if(Drive) {
            *Drive = 0;
        }
        if(Directory){
            *Directory = 0;
        }
        if(FileName){
            *FileName = 0;
        }
        if(Extention){
            *Extention = 0;
        }
        return ERANGE;
}


errno_t
_wmakepath_s(
    LPWSTR Path,
    size_t Length,
    LPWSTR Drive,
    LPWSTR Directory,
    LPWSTR FileName,
    LPWSTR Extention
){

    LPWSTR Position = Path;
    if((!Path) || (!Length)){
        return EINVAL;
    }

    if((Drive) && (Drive[0])){
        if(Length <= 2){
            goto _MAKE_PATH_RANGE;
        }
        *Position++ = Drive[0];
        *Position++ = ':';
        Length -= 2;
    }

    if((Directory) && (Directory[0])){
        unsigned int Len = wcslen(Directory);
        unsigned int Seperator = ((Directory[Len - 1] != '/') && (Directory[Len - 1] != '\\'));
        unsigned int CopyLen = MIN(Length - 1, Len);
        if(Length < 2){
            goto _MAKE_PATH_RANGE;
        }
        memcpy(Position, Directory, CopyLen * sizeof(WCHAR));
        if(Length <= Len){
            goto _MAKE_PATH_RANGE;
        }
        Position += CopyLen;
        Length -= CopyLen;
        if(Seperator){
            if(Length < 2){
                goto _MAKE_PATH_RANGE;
            }
            *Position++ = '\\';
            Length -= 1;
        }
    }    

    if((FileName) && (FileName[0])){
        unsigned int Len = wcslen(FileName);
        unsigned int CopyLen = MIN(Length -1, Len);
        if(Length < 2){
            goto _MAKE_PATH_RANGE;
        }
        memcpy(Position, FileName, CopyLen * sizeof(WCHAR));
        if(Length <= Len){
            goto _MAKE_PATH_RANGE;
        }
        Position += Len;
        Length -= Len;
    }

    if((Extention) && (Extention[0])){
        unsigned int Len = wcslen(Extention);
        unsigned int Period = (Extention[0] != '.');
        unsigned int CopyLen;
        if(Length < 2){
            goto _MAKE_PATH_RANGE;
        }
        if(Period){
            *Position++ = '.';
            Length -= 1;
        }
        CopyLen = MIN(Length - 1, Len);
        memcpy(Position, Extention, CopyLen * sizeof(WCHAR));
        if(Length <= Len){
            goto _MAKE_PATH_RANGE;
        }
        Position += CopyLen;
    }    

    *Position = 0;
    return 0;
    
    _MAKE_PATH_RANGE:
        Path[0] = 0;
        return ERANGE;
}

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

LPWSTR LouKeCreateCombineWcsStr(
    LPWSTR Str1, 
    LPWSTR Str2
){
    size_t size = wcslen(Str1);
    size += wcslen(Str2) + 1;
    LPWSTR NewString;
    NewString = LouKeForkWcsStr_s(Str1, size);
    wcscat(NewString, Str2);
    return NewString;
}   

