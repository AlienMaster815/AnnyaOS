#include "ntdll.h"

static const UINT16 NtWcTypes[256] = {
    //00
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    0x0020, 0x0068, 0x0028, 0x0028, 0x0028, 0x0028, 0x0020, 0x0020,
    //10
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    //20
    0x0048, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    //30
    0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084,
    0x0084, 0x0084, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    //40
    0x0010, 0x0181, 0x0181, 0x0181, 0x0181, 0x0181, 0x0181, 0x0101,
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
    //50
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
    0x0101, 0x0101, 0x0101, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    //60
    0x0010, 0x0182, 0x0182, 0x0182, 0x0182, 0x0182, 0x0182, 0x0102,
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102,
    //70
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102,
    0x0102, 0x0102, 0x0102, 0x0010, 0x0010, 0x0010, 0x0010, 0x0020,
    //80
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    //90
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    //A0 
    0x0048, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    //B0
    0x0010, 0x0010, 0x0014, 0x0014, 0x0010, 0x0010, 0x0010, 0x0010,
    0x0010, 0x0014, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    //C0
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
    //D0
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0010,
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0102,
    //E0
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102,
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102,
    //F0
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0010,
    0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102, 0x0102,
}; 

NTDLL_API
int 
_wcsicmp(LPCWSTR String1, LPCWSTR String2){
    wchar_t Char1, Char2;
    size_t i = 0;
    while(1){
        Char1 = ((String1[i] >= 'A') && (String1[i] <= 'Z')) ? String1[i] + 32 : String1[i];
        Char2 = ((String2[i] >= 'A') && (String2[i] <= 'Z')) ? String2[i] + 32 : String2[i];
        if((Char1 !=Char2) || (!*String1)){
            return Char1 - Char2;
        }
        i++;
    }
    return 0x00;
}

NTDLL_API
size_t 
wcsnlen(
    LPCWSTR Str,
    size_t Length
){
    size_t i = 0;
    while((Str[i]) && (Length)){
        i++;
        Length--;
    }
    return i - (size_t)Str;
}

NTDLL_API
LPWSTR 
_wcslwr(
    LPWSTR Str
){
    LPWSTR Result = Str;
    for ( ; *Str; Str++) if (*Str >= 'A' && *Str <= 'Z') *Str += 'a' - 'A';
    return Result;
}

NTDLL_API
int 
_wcslwr_s(wchar_t* Str, size_t Length){

    if(!Str){
        return 22;//EINVAL
    }

    if(wcsnlen(Str, Length) == Length){
        *Str = 0x00;
        return 22;//EINVAL
    }

    _wcslwr(Str);

    return 0x00;
}

NTDLL_API
LPWSTR 
_wcsupr(
    LPWSTR Str
){
    LPWSTR Result = Str;
    for ( ; *Str; Str++) if (*Str >= 'a' && *Str <= 'z') *Str += 'A' - 'a';
    return Result;
}

NTDLL_API
int 
_wcsupr_s(
    LPWSTR Str,
    size_t Length
){

    if(!Str){
        return 22;//EINVAL
    }

    if(wcsnlen(Str, Length) == Length){
        *Str = 0x00;
        return 22;//EINVAL
    }

    _wcsupr(Str);
    return 0x00;
}

NTDLL_API
LPWSTR
wcscpy(
    LPWSTR Destination, 
    LPWSTR Source
){
    LPWSTR Tmp = Destination;
    while((*Tmp++ = *Source++));
    return Destination;
}

NTDLL_API
int
wcscpy_s(
    LPWSTR  Destination,
    size_t  Length,
    LPCWSTR Source
){
    size_t i;
    if((!Destination) || (!Length) || (!Source)){
        if(Destination) {
            *Destination = 0;
        }
        return 22; //EINVAL:
    }

    for(i = 0 ; i < Length; i++){
        if(!(Destination[i] = Source[i]))return 0;
    }
    *Destination = 0;
    return 34;//ERANGE
}

NTDLL_API
size_t 
wcslen(
    LPCWSTR Str
){
    LPWSTR Tmp = Str;
    while(*Tmp){
        Tmp++;
    }
    return (size_t)Tmp - (size_t)Str;
}

NTDLL_API
LPWSTR
wcscat(
    LPWSTR  Destination,
    LPCWSTR Source
){
    wcscpy(Destination + wcslen(Destination), Source);
    return Destination;
}
NTDLL_API
int 
wcscat_s(
    wchar_t*            Destination,
    size_t              Length,
    const wchar_t*      Source
){
    size_t i, j;
    if((!Destination) || (!Length) || (!Source)){
        if(Destination){
            *Destination = 0;
        } 
        return 22;//EINVAL
    } 
    for(i = 0; i < Length; i++){
        if(!Destination[i]){
            break;
        }
    }
    for(j = 0; (j + i) < Length; j++){
        if(!(Destination[j + i] = Source[j])){
            return 0;
        }
    }
    return 34;//ERANGE
}

//256