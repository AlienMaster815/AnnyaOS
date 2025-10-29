#include <Compiler.h>
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

#define MINLONG ((long)0x80000000)
#define MAXLONG ((long)0x7FFFFFFF)

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
Lou_wctoint(
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
Lou_wcslen(LPWSTR str){
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

LPWSTR
Lou_wcspbrk_s(
    LPWSTR Str,
    size_t StrLen,
    LPWSTR Accept,
    size_t AcceptLen
){
    if (!Str || !Accept) {
        return 0x00;
    }
    for (size_t i = 0; i < StrLen && Str[i]; i++) {
        WCHAR ch = Str[i];
        for (size_t j = 0; j < AcceptLen && Accept[j]; j++) {
            if (Accept[j] == ch) {
                return (LPWSTR)(Str + i);
            }
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


long 
Lou_wcstol(
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
    while(Lou_iswspace(*Str)){
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
        (!Lou_wctoint(*Str)) && 
        ((Str[1] == 'x') || (Str[1] == 'X'))
    ){
        Base = 16;
        Str += 2;
    }
    if(Base == 0){
        Base = Lou_wctoint(*Str) ? 10 : 8;
    }
    while(*Str){
        int V = Lou_wctoint(*Str);
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
Lou_wcstoul(
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
    while(Lou_iswspace(*Str)){
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
        (!Lou_wctoint(*Str)) && 
        ((Str[1] == 'x') || (Str[1] == 'X'))
    ){
        Base = 16;
        Str += 2;
    }
    if(Base == 0){
        Base = Lou_wctoint(*Str) ? 10 : 8;
    }
    while(*Str){
        int V = Lou_wctoint(*Str);
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
Lou_wcstoi64(
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
    while(Lou_iswspace(*Str)){
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
        (!Lou_wctoint(*Str)) && 
        ((Str[1] == 'x') || (Str[1] == 'X'))
    ){
        Base = 16;
        Str += 2;
    }
    if(Base == 0){
        Base = Lou_wctoint(*Str) ? 10 : 8;
    }
    while(*Str){
        int V = Lou_wctoint(*Str);
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
Lou_wcstoui64(
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
    while(Lou_iswspace(*Str)){
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
        (!Lou_wctoint(*Str)) && 
        ((Str[1] == 'x') || (Str[1] == 'X'))
    ){
        Base = 16;
        Str += 2;
    }
    if(Base == 0){
        Base = Lou_wctoint(*Str) ? 10 : 8;
    }
    while(*Str){
        int V = Lou_wctoint(*Str);
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
Lou__ultow(
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
Lou__ltow(
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
Lou__itow(
    int     Value,
    LPWSTR  Str,
    int     Radix
){
    return Lou__ltow(Value, Str, Radix);
}


LPWSTR 
Lou__ui64tow(
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
Lou__i64tow(
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
Lou__ui64tow_s(
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
Lou__ultow_s(
    unsigned long   Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
){
    return Lou__ui64tow_s(Value, Str, Length, Radix);
}


errno_t
Lou__i64tow_s(
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
Lou__ltow_s(
    long            Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
){
    if((Value < 0) && (Radix == 10)){
        return Lou__i64tow_s((INT64)Value, Str, Length, Radix);
    }
    return Lou__ui64tow_s((UINT64)Value, Str, Length, Radix);
}


errno_t
Lou__itow_s(
    int             Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
){
    if((Value < 0) && (Radix == 10)){
        return Lou__i64tow_s((INT64)Value, Str, Length, Radix);
    }
    return Lou__ui64tow_s((UINT64)Value, Str, Length, Radix);
}


long 
Lou__wtol(
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
Lou__wtoi(
    LPWSTR Str
){
    return (int)Lou__wtol(Str);
}

 
UINT64
Lou__wtoi64(
    LPWSTR Str
){
    UINT64  TotalRun = 0;
    BOOL    Negative = false;
    while(Lou_iswspace(*Str)){
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

UINT64
Lou__wtoh64(
    LPWSTR Str
){
    UINT64 TotalRun = 0;
    BOOL   Negative  = FALSE;

    while (Lou_iswspace(*Str)) {
        Str++;
    }

    if (*Str == L'+') {
        Str++;
    } else if (*Str == L'-') {
        Negative = TRUE;
        Str++;
    }

    if (Str[0] == L'0' && (Str[1] == L'x' || Str[1] == L'X')) {
        Str += 2;
    }

    while ((*Str >= L'0' && *Str <= L'9') ||
           (*Str >= L'a' && *Str <= L'f') ||
           (*Str >= L'A' && *Str <= L'F')) {

        UINT8 nibble;

        if (*Str <= L'9')
            nibble = (UINT8)(*Str - L'0');
        else if (*Str <= L'F')
            nibble = (UINT8)(*Str - L'A' + 10);
        else
            nibble = (UINT8)(*Str - L'a' + 10);

        TotalRun = (TotalRun << 4) | nibble;
        Str++;
    }
    return Negative ? (UINT64)(-(INT64)TotalRun) : TotalRun;
}

UINT64
Lou__wtoh64_s(
    LPWSTR Str,
    size_t  Length
){
    UINT64 TotalRun = 0;
    BOOL   Negative = FALSE;
    size_t i = 0;

    while (i < Length && Lou_iswspace(Str[i])) {
        i++;
    }
    if (i < Length) {
        if (Str[i] == L'+') {
            i++;
        } else if (Str[i] == L'-') {
            Negative = TRUE;
            i++;
        }
    }
    if ((i + 1) < Length && Str[i] == L'0' &&
        (Str[i + 1] == L'x' || Str[i + 1] == L'X')) {
        i += 2;
    }
    for (; i < Length; i++) {
        WCHAR ch = Str[i];
        UINT8 nibble;

        if (ch >= L'0' && ch <= L'9') {
            nibble = (UINT8)(ch - L'0');
        } else if (ch >= L'a' && ch <= L'f') {
            nibble = (UINT8)(ch - L'a' + 10);
        } else if (ch >= L'A' && ch <= L'F') {
            nibble = (UINT8)(ch - L'A' + 10);
        } else {
            break;
        }

        TotalRun = (TotalRun << 4) | nibble;
    }
    return Negative ? (UINT64)(-(INT64)TotalRun) : TotalRun;
}


UINT64
Lou__wtoi64_s(
    LPWSTR Str,
    size_t  Length
){
    UINT64 TotalRun = 0;
    BOOL   Negative = FALSE;
    size_t i = 0;
    while (i < Length && Lou_iswspace(Str[i])) {
        i++;
    }
    if (i < Length) {
        if (Str[i] == L'+') {
            i++;
        } else if (Str[i] == L'-') {
            Negative = TRUE;
            i++;
        }
    }
    for (; i < Length; i++) {
        WCHAR ch = Str[i];
        if (ch < L'0' || ch > L'9') {
            break;
        }
        TotalRun = (TotalRun * 10) + (UINT64)(ch - L'0');
    }
    return Negative ? (UINT64)(-(INT64)TotalRun) : TotalRun;
}
