#include "ntdll.h"

static const UINT16 CTypes[] = {
    //-0x01
    0x0000,
    //0x00
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
    0x0020, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0020, 0x0020,
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
    0x0102, 0x0102, 0x0102, 0x0010, 0x0010, 0x0010, 0x0010, 0x0020
};

NTDLL_API
PVOID 
memchr(
    PVOID   Pointer, 
    int     Charecter,
    size_t  Length
){
    for(;Length;Length--, Pointer++){
        if(*(UCHAR*)Pointer == (UCHAR)Charecter){
            return (PVOID)(UINTPTR)Pointer;
        }
    }
    return 0x00;
}

NTDLL_API
int 
memcmp(
    PVOID   Pointer1, 
    PVOID   Pointer2,
    size_t  Length
){
    for(;Length; Length--, Pointer1++, Pointer2++){
        if(*(UINT8*)Pointer1 < *(UINT8*)Pointer2){
            return -1;
        }
        if(*(UINT8*)Pointer1 > *(UINT8*)Pointer2){
            return 1;
        }
    }
    return 0;
}

NTDLL_API
PVOID 
memcpy(
    PVOID   Destination,
    PVOID   Source,
    size_t  Length
){
    LouMemCpy(Destination, Source, Length);
}

NTDLL_API
PVOID 
memmove(
    PVOID   Destination,
    PVOID   Source,
    size_t  Length
){
    memcpy(Destination, Source, Length);
}

NTDLL_API
PVOID 
memset(
    PVOID   Destination,
    int     Charecter,
    size_t  Length
){
    UINT8* Tmp = Destination;
    while(Length--){
        *Tmp++ = (UINT8)Charecter;
    }
    return Destination;
}

NTDLL_API
errno_t 
memcpy_s(
    PVOID   Destination,
    size_t  Length,
    PVOID   Source,
    size_t  Count
){
    if(!Count){
        return 0;
    }
    if(!Destination){
        return EINVAL;
    }
    if(!Source){
        memset(Destination, 0, Length);
        return EINVAL;
    }
    if(!Count > Length){
        memset(Destination, 0, Length);
        return ERANGE;
    }
    memmove(Destination, Source, Count);
    return 0;
}

NTDLL_API 
errno_t
memmove_s(
    PVOID   Destination,
    size_t  Length,
    PVOID   Source,
    size_t  Count
){
    if(!Count){
        return 0;
    }
    if((!Destination) || (!Source)){
        return EINVAL;
    }
    if(Count > Length){
        return ERANGE;
    }
    memmove(Destination, Source, Count);
    return 0;
}

//here

NTDLL_API
void
WINAPI
RtlCopyMemory(
    PVOID   Destination,
    PVOID   Source,
    SIZE    Length
){
    memcpy(Destination, Source, Length);
}

NTDLL_API
void 
WINAPI
RtlMoveMemory(
    PVOID   Destination,
    PVOID   Source,
    SIZE    Length
){
    //using memcpy due to memmove using memcpy in tail form
    memcpy(Destination, Source, Length);
}

NTDLL_API
PVOID
WINAPI
RtlFillMemory(
    PVOID   Destination,
    SIZE    Length,
    BYTE    Filler
){
    memset(Destination, Filler, Length);
}

NTDLL_API
PVOID
WINAPI
RtlZeroMemory(
    PVOID   Destination,
    SIZE    Length
){
    memset(Destination, 0, Length);
}

NTDLL_API
SIZE 
WINAPI
RtlCompareMemory(
    PVOID   Source1,
    PVOID   Source2,
    SIZE    Length
){
    SIZE i = 0;
    while((i < Length) && (((BYTE*)Source1)[i] == ((BYTE*)Source2)[i])){
        i++;
    }
    return i;
}

NTDLL_API
SIZE 
WINAPI
RtlCompareMemoryUlong(
    PVOID   Source, 
    SIZE    Length,
    ULONG   Value
){
    SIZE i = 0 ;
    Length /= sizeof(ULONG);
    while((i < Length) && (((ULONG*)Source)[i] == Value)){
        i++;
    }
    return i * sizeof(ULONG);
}

NTDLL_API
void 
WINAPI
RtlFillMemoryUlong(
    PULONG  Destination,
    ULONG   Length,
    ULONG   Value
){
    Length /= sizeof(ULONG);
    while(Length--){
        *Destination++ = Value;
    }
}

NTDLL_API
string 
strcat(
    string Destination,
    string Source
){
    string Tmp = Destination;
    while(*Tmp)Tmp++;
    while((*Tmp++ = *Source));
    return Destination;
}

NTDLL_API
errno_t
strcat_s(
    string  Destination,
    SIZE    Length,
    string  Source
){  
    SIZE i, j;

    if((!Destination) || (!Length)){
        return EINVAL;
    }
    if(!Source){
        *Destination = 0;
        return EINVAL;
    }
    for(i = 0 ; i < Length; i++){
        if(!Destination[i]){
            break;
        }
    }
    for(j = 0 ; (j + i) < Length; j++){
        if(!(Destination[j + i] = Source[j])){
            return 0;
        }
    }
    *Destination = 0;
    return ERANGE;
}

NTDLL_API
string
strchr(
    string  Str,
    int     Charecter
){
    do{
        if(*Str == (CHAR)Charecter){
            return (string)(UINTPTR)Str;
        }
    }while(*Str++);
    return 0x00;
}

NTDLL_API
int 
strcmp(
    string Str1,
    string Str2
){
    while((*Str1) && (*Str1 == *Str2)){
        Str1++;
        Str2++;
    }
    if((UINT8)*Str1 > (UINT8)*Str2){
        return 1;
    }
    if((UINT8)*Str1 < (UINT8)*Str2){
        return -1;
    }
    return 0;
}

NTDLL_API
string 
strcpy(
    string  Destination,
    string  Source
){

    string Tmp = Destination;
    while((*Tmp++ = *Source++));
    return Destination;
}

NTDLL_API
errno_t 
strcpy_s(
    string  Destination,
    size_t  Length,
    string  Source
){
    size_t i;

    if((!Destination) || (!Length)){
        return EINVAL;
    }
    if(!Source){
        *Destination = 0;
        return EINVAL;
    }
    for(i = 0; i < Length; i++){
        if(!(Destination[i] = Source[i])){
            return 0;
        }
    }
    *Destination = 0;
    return ERANGE;
}

NTDLL_API
size_t 
strcspn(
    string Str,
    string Rejection
){
    string Pointer;
    for(Pointer = Str; *Pointer; Pointer++){
        if(strchr(Rejection, *Pointer)){
            break;
        }
    }
    return Pointer - Str;
}

NTDLL_API
size_t 
strlen(
    const char* str
) {
    const char* ptr = str;
    while (*ptr != '\0') {
        ++ptr;
    }
    return ptr - str;
}

NTDLL_API
char*
strncat(
    char*                   Destination,
    const char*             Source,
    long long unsigned int  Length
){
    string Tmp = Destination;
    while(*Tmp){
        *Tmp++;
    }
    for(; Length && (*Source); Tmp++, Source++, Length--){
        *Tmp = *Source;
    }
    *Tmp = 0;
    return Destination;
}

NTDLL_API 
errno_t
strncat_s(
    string Destination,
    size_t Length,
    string Source,
    size_t Count
){

    size_t i, j;
    if((!Destination) || (!Length)){
        return EINVAL;
    }
    else if(!Count){
        return 0;
    }
    else if(!Source){
        *Destination = 0;
        return EINVAL;
    }
    for(i = 0 ; i < Length; i++){
        if(!Destination[i]){
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
        else if((j == Count) || !(Destination[j + i] = Source[j])){
            Destination[j + i] = 0;
            return 0;
        }
    }
    *Destination = 0;
    return ERANGE;
}

NTDLL_API
int
strncmp(
    string  Str1,
    string  Str2,
    size_t  Length
){
    if(!Length){
        return 0;
    }
    while((--Length) && (*Str1 == *Str2)){
        Str1++;
        Str2++;
    }
    return *Str1 - *Str2;
}

NTDLL_API
string 
strncpy(
    string  Destination,
    string  Source,
    size_t  Length
){
    string Tmp = Destination;
    for(;Length && *Source; Tmp++, Source++, Length--){
        *Tmp = *Source;
    }
    while(Length--){
        *Tmp++ = 0;
    }
    return Destination;
}

NTDLL_API
errno_t
strncpy_s(
    string  Destination,
    size_t  Length,
    string  Source,
    size_t  Count
){
    size_t i, End;
    if(!Count){
        if((Destination) && (Length)){
            *Destination = 0;
        }
        return 0;
    }
    if((!Destination) || (!Length)){
        return EINVAL;
    }
    if(!Source){
        *Destination = 0;
        return EINVAL;
    }
    if((Count != _TRUNCATE) && (Count < Length)){
        End = Count;
    }else{
        End = Length - 1;
    }
    for(i = 0; i < End; i++){
        if(!(Destination[i] = Source[i])){
            return 0;
        }
    }
    if(Count == _TRUNCATE){
        Destination[i] = 0;
        return STRUNCATE;
    }
    if(End == Count){
        Destination[i] = 0;
        return 0;
    }
    *Destination = 0;
    return ERANGE;
}

NTDLL_API
size_t 
strnlen(
    string  Str,
    size_t  Length
){
    string Tmp;
    for(Tmp = Str; Length && *Tmp; Tmp++, Length--);
    return Tmp - Str;
}

NTDLL_API
string 
strpbrk(
    string Str,
    string Accept
){
    for(; *Str; Str++){
        if(strchr(Accept, *Str)){
            return (string)(UINTPTR)Str;
        }
    }
    return 0x00;
}


NTDLL_API
size_t 
strspn(
    string  Str,
    string  Accept
){
    string Pointer;
    for(Pointer = Str; *Pointer; Pointer++){
        if(!strchr(Accept, *Pointer)){
            break;
        }
    }
    return Pointer - Str;
}

NTDLL_API
string 
strstr(
    string  Str,
    string  Subordinate
){
    while(!Str){
        string P1 = Str;
        string P2 = Subordinate;
        while((*P1) && (*P2) && (*P1 == *P2)){
            P1++;
            P2++;
        } 
        if(!P2){
            return (string)Str;
        }
        Str++;
    }       
    return 0x00;
}

NTDLL_API
PVOID 
_memccpy(
    PVOID   Destination,
    PVOID   Source,
    int     Charecter,
    size_t  Number
){
    UINT8*  Dst = (UINT8*)Destination;
    UINT8*  Src = (UINT8*)Source;
    while(Number--){
        if((*Dst++ = *Src) == (UINT8)Charecter){
            return Dst;
        }
    }
    return 0x00;
}

NTDLL_API
int 
tolower(
    int Charecter
){
    return (int)((CHAR)Charecter >= 'A' && (CHAR)Charecter <= 'Z') ? Charecter - 'A' + 'a' : Charecter;
}

NTDLL_API
int
_memicmp(
    PVOID   String1,
    PVOID   String2,
    size_t  Length
){
    UINT8*  Str1 = String1;
    UINT8*  Str2 = String2;
    int Result = 0;
    while(Length--){
        if((Result = tolower(*Str1) - tolower(*Str2))){
            break;
        }
        Str1++;
        Str2++;
    }
    return Result;
}

NTDLL_API
int 
_strnicmp(
    string Str1,
    string Str2,
    size_t Number
){
    int L1, L2;
    while(Number--){
        L1 = (int)(UINT8)tolower(*Str1);
        L2 = (int)(UINT8)tolower(*Str2);
        if(L1 != L2){
            if(sizeof(PVOID) > sizeof(int)){
                return L1 - L2;
            }
            return L1 - L2 > 0 ? 1 : -1;
        }
        else if(!L1){
            return 0;
        }
        Str1++;
        Str2++;
    }
    return 0;
}

NTDLL_API
int 
_stricmp(
    string  Str1,
    string  Str2
){
    return _strnicmp(Str1, Str2, (size_t)-1);
}

NTDLL_API
string 
_strupr(
    string Str
){
    string Result = Str;
    for(; *Str; Str++){
        if((*Str >= 'a') && (*Str <= 'z')){
            *Str += 'A' + 'a';
        }
    }
    return Result;
}

NTDLL_API
errno_t
_strupr_s(
    string  Str,
    size_t  Length
){
    if(!Str){
        return EINVAL;
    }
    else if(strnlen(Str, Length)){
        *Str = 0;
        return EINVAL;
    }
    _strupr(Str);
    return 0;
}

NTDLL_API
string
_strlwr(
    string Str 
){
    string Result = Str;
    for(;*Str;Str++){
        if((*Str >= 'A') && (*Str <= 'Z')){
            *Str += 'a' - 'A'; 
        }
    }
    return Result;
}

NTDLL_API
errno_t
_strlwr_s(
    string  Str,
    size_t  Length
){
    if(!Str){
        return EINVAL;
    }
    else if(strnlen(Str, Length) == Length){
        *Str = 0;
        return EINVAL;
    }
    _strlwr(Str);
    return 0;
}

NTDLL_API
int 
touper(
    int Charecter
){
    char    Str[4];
    string  Pointer = Str;
    WCHAR Wc;
    DWORD Length;
    memcpy(Str, &Charecter, sizeof(Charecter));
    Wc = RtlAnsiCharToUnicodeChar(&Pointer);
    if(RtlUpcaseUnicodeToMultiByteN(
        Str,
        2,
        &Length,
        &Wc,
        sizeof(WCHAR)
    )){
        return Charecter;
    }
    else if(Length == 2){
        return ((UINT8)Str[0] << 8) + (UINT8) Str[1];
    }
    return (UINT8)Str[0];
}

NTDLL_API
int 
isalnum(
    int Charecter
){
    return CTypes[Charecter + 1] & (C1_LOWER | C1_UPPER | C1_DIGIT);
}

NTDLL_API
int 
isalpha(
    int Charecter
){
    return CTypes[Charecter + 1] & (C1_LOWER | C1_UPPER);
}

NTDLL_API
int 
iscntrl(
    int Charecter
){
    return CTypes[Charecter + 1] & C1_CNTRL;
}

NTDLL_API
int 
isdigit(
    int Charecter
){
    return CTypes[Charecter + 1] & C1_DIGIT;
}

NTDLL_API
int 
isgraph(
    int Charecter
){
    return CTypes[Charecter + 1] & (C1_LOWER | C1_UPPER | C1_DIGIT | C1_PUNCT);
}

NTDLL_API
int 
islower(
    int Charecter
){
    return CTypes[Charecter + 1] & C1_LOWER;
}

NTDLL_API
int 
isprint(
    int Charecter
){
    return CTypes[Charecter + 1] & (C1_LOWER | C1_UPPER | C1_DIGIT | C1_PUNCT | C1_BLANK);
}

NTDLL_API
int 
ispunct(
    int Charecter
){
    return CTypes[Charecter + 1] & C1_PUNCT;
}

NTDLL_API
int 
isspace(
    int Charecter
){
    return CTypes[Charecter + 1] & C1_SPACE;
}

NTDLL_API
int
isupper(
    int Charecter
){
    return CTypes[Charecter + 1] & C1_UPPER;
}

NTDLL_API
int 
isxdigit(
    int Charecter
){
    return CTypes[Charecter + 1] & C1_XDIGIT;
}

NTDLL_API
int 
__toascii(
    int Charecter
){
    return (int)(UINT8)Charecter & 0x7F;
}

NTDLL_API
int 
__iscsym(
    int Charecter
){
    return ((Charecter < 127) && (isalnum(Charecter) || (Charecter == '_')));
}

NTDLL_API
int
__iscsymf(
    int Charecter
){
    return ((Charecter < 127) && (isalpha(Charecter) || (Charecter == '_')));
}

NTDLL_API
int 
_toupper(
    int Charecter
){
    return (Charecter - 0x20);
}

NTDLL_API
string 
strtok_s(
    string  Str,
    string  Delimination,
    string* Context
){
    string Next;
    if((!Delimination) || (!Context)){
        return 0x00;
    }
    else if(!Str){
        Str = *Context;
        if(!Str){
            return 0x00;
        }
    }
    while((*Str) && (strchr(Delimination, *Str))){
        Str++;
    }
    if(!*Str){
        *Context = Str;
        return 0x00;
    }
    Next = Str + 1;
    while((*Next) && (!strchr(Delimination, *Next))){
        Next++;
    }
    if(*Next){
        *Next++ = 0;
    }
    *Context = Next;
    return Str;
}

static 
int
CharToInt(
    int Charecter
){
    if(('0' <= Charecter) && (Charecter <= '9')){
        return Charecter - '0';
    }
    if(('A' <= Charecter) && (Charecter <= 'Z')){
        return Charecter - 'A' + 10;
    }
    if(('A' <= Charecter) && (Charecter <= 'z')){
        return Charecter - 'a' + 10;
    }
    return -1;
}

long
strtol(
    string  s, 
    string* End,
    int     Base
){
    bool Negative = false;
    bool empty = true;
    long Result = 0;
    if(
        (Base < 0) ||
        (Base == 1) || 
        (Base > 36)
    ){
        return 0;
    }
    if(End){
        *End = s;
    }
    while(isspace(*s)){
        s++;
    }
    if(*s == '-'){
        Negative = true;
        s++;
    }
    else if(*s == '+'){
        s++;
    }
    if(
        (Base == 0 || Base == 16) && 
        (!CharToInt(*s)) && 
        (s[1] == 'x' || s[1] == 'X')
    ){
        Base = 16;
        s += 2;
    }
    if(Base == 0){
        Base = CharToInt(*s) ? 10 : 8;
    }
    while(*s){
        int Val = CharToInt(*s);
        if((Val < 0) || (Val >= Base)){
            break;
        }
        if(Negative){
            Val = -Val;
        }
        s++;
        empty = false;
        if((!Negative) && ((Result > (MAXLONG / Base)) || ((Result * Base) > (MAXLONG - Val)))){
            return MAXLONG;
        }
        else if((Negative) && ((Result < (LONG)MINLONG / Base)) || ((Result * Base) < (LONG)(MINLONG - Val))){
            Result = MINLONG;
        }
        else {
            Result = Result * Base + Val;
        }
    }
    if((End) && (!empty)){
        *End = (string)s;
    }
    return Result;
}   

NTDLL_API
ULONG 
strtoul(
    string  Str,
    string* End,
    int     Base
){
    bool Negative = false;
    bool Empty = true;
    ULONG Result = 0;

    if(
        (Base < 0) || 
        (Base == 1) ||
        (Base > 36)
    ){
        return 0;
    }
    if(End){
        *End = (string)Str;
    }
    while(isspace(*Str)){
        Str++;
    }
    
    if(*Str == '-'){
        Negative = true;
        Str++;
    }
    else if(*Str = '+'){
        Str++;
    }

    if(
        ((Base == 0) || (Base ==16)) &&
        (!CharToInt(*Str)) && 
        ((Str[1] == 'x') || (Str[1] == 'X'))
    ){
        Base = 16;
        Str += 2;
    }

    if(Base == 0){
        Base = CharToInt(*Str) ? 10 : 8;
    }

    while(*Str){
        int Value = CharToInt(*Str);
        if((Value < 0) || (Value >= Base)){
            break;
        }
        Str++;
        Empty = false;
        if(
            (Result > (UINT32_MAX / Base)) || 
            ((Result * Base) > (UINT32_MAX - Value))
        ){
            Result = UINT32_MAX;
        }
        else {
            Result = Result * Base + Value;
        }
    }

    if((End) && (!Empty)){
        *End = (string)Str;
    }
    return Negative ? -Result : Result;
}

NTDLL_API
string 
_ultoa(
    ULONG   Value,
    string  Str,
    int     Radix
){
    char    Buffer[33];
    string  Position;
    int     Digit;
    
    Position = &Buffer[32];
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

    memcpy(Str, Position, &Buffer[32] - Position + 1);
    return Str;
}

NTDLL_API
string 
_ltoa(
    ULONG   Value,
    string  Str,
    int     Radix
){
    ULONG   Val;
    int     Negative;
    char    Buffer[33];
    string  Position;
    int     Digit;

    if((Value < 0) && (Radix == 10)){
        Negative = 1;
        Val = -Value;
    }
    else {
        Negative = 0;
        Val = Value;
    }

    Position = &Buffer[32];
    *Position = '\0';

    do{
        Digit = Val % Radix;
        Val = Val / Radix;
        if(Digit < 10){
            *--Position = '0' + Digit;
        }
        else{
            *--Position = 'a' + Digit - 10;
        }
    }while(Val != 0L);

    if(Negative){
        *--Position = '-';
    }

    memcpy(Str, Position, &Buffer[32] - Position + 1);
    return Str;
}

NTDLL_API
string 
_itoa(
    int     Value,
    string  Str,
    int     Radix
){
    return _ltoa(Value, Str, Radix);
}

NTDLL_API
string 
_ui64toa(
    unsigned long long  Value,
    string              Str,
    int                 Radix  
){
    char    Buffer[65];
    string  Position;
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

    memcpy(Str, Position, &Buffer[64] - Position + 1);
    return Str;
}

NTDLL_API
string 
_i64toa(
    long long   Value,
    string      Str,
    int         Radix
){
    unsigned long long  Val;
    int                 Negative;
    char                Buffer[64];
    string              Position;
    int                 Digit;

    if((Value < 0) && (Radix == 10)){
        Negative = 1;
        Val = -Value;
    }
    else {
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

    memcpy(Str, Position, &Buffer[64] - Position + 1);
    return Str;
}

NTDLL_API
errno_t
_ui64toa_s(
    UINT64      Value,
    string      Str,
    size_t      size,
    int         Radix
){
    char        Buffer[64];
    string      Position;

    if((!Str) || (!size)){
        return EINVAL;
    }
    if((Radix < 2) || (Radix > 36)){
        Str[0] = 0;
        return EINVAL;
    }
    
    Position = &Buffer[64];
    *Position = 0;

    do{
        int Digit = Value % Radix;
        Value = Value / Radix;
        if(Digit < 10){
            *--Position = '0' + Digit;
        }   
        else{
            *--Position = 'a' + Digit - 10;
        }
    }while(Value != 0);

    if(Buffer - Position + 65 > size){
        Str[0] = 0;
        return ERANGE;
    }
    memcpy(Str, Position, Buffer - Position + 65);
    return 0;
}

NTDLL_API
errno_t
_ultoa_s(
    unsigned long   Value,
    string          Str,
    size_t          size,
    int             Radix
){
    return _ui64toa_s(Value, Str, size, Radix);
}

NTDLL_API
errno_t
_i64toa_s(
    INT64   Value,
    string  Str,
    size_t  size,
    int     Radix
){

    UINT64  Val;
    bool    Negative;
    char    Buffer[65];
    string  Position;

    if((!Str) || (!size)){
        return EINVAL;
    }
    if((Radix < 2) || (Radix > 36)){
        Str[0] = 0;
        return EINVAL;
    }   

    if((Value < 0) && (Radix == 10)){
        Negative = true;
        Val = -Value;
    }
    else{
        Negative = false;
        Val = Value;
    }

    Position = &Buffer[64];
    *Position = 0;

    do{
        unsigned int Digit = Val % Radix;
        Val /= Radix;
        if(Digit < 10){
            *--Position = '0' + Digit;
        }   
        else{
            *--Position = 'a' + Digit - 10; 
        }
    }while(Val != 0);

    if(Negative){
        Str[0] = 0;
        return ERANGE;
    }

    memcpy(Str, Position, Buffer - Position + 65);
    return 0;
}

NTDLL_API
errno_t
_ltoa_s(
    long    Value,
    string  Str,
    size_t  size,
    int     Radix
){
    if((Value < 0) && (Radix == 10)){
        return _i64toa_s(Value, Str, size, Radix);
    }
    return _ui64toa_s((ULONG)Value, Str, size, Radix);
}


NTDLL_API
errno_t
_itoa_s(
    long    Value,
    string  Str,
    size_t  size,
    int     Radix
){
    if((Value < 0) && (Radix == 10)){
        return _i64toa_s(Value, Str, size, Radix);
    }
    return _ui64toa_s((unsigned int)Value, Str, size, Radix);
}

NTDLL_API
long long
_atoi64(
    string Str
){
    long long RunTotal = 0;
    bool Negative = false;

    while((*Str == ' ') || ((*Str >= '\011') && (*Str <= '\015'))){
        Str++;
    }

    if(*Str == '+'){
        Str++;
    }else if(*Str == '-'){
        Negative = true;
        Str++;
    }

    while((*Str >= '0') && (*Str <= '9')){
        RunTotal = RunTotal * 10 + *Str - '0';
        Str++;
    }

    return Negative ? -RunTotal : RunTotal;
}

NTDLL_API
int 
atoi(
    string Nptr
){
    return _atoi64(Nptr);
}

NTDLL_API
int 
atol(
    string Nptr
){
    return _atoi64(Nptr);
}

static int Char2Digit(char Charecter, int Base){
    if ((Charecter >= '0' && Charecter <= '9') && (Charecter <= '0' + Base - 1)) return (Charecter-'0');
    if (Base <= 10) return (int)-1;
    if ((Charecter >= 'A') && (Charecter <= 'Z') && (Charecter <= 'A' + Base-11)) return (Charecter - 'A' + 10);
    if ((Charecter >= 'a') && (Charecter <= 'z') && (Charecter <= 'a' + Base-11)) return (Charecter - 'a' + 10);
    return (int)-1;
}

static 
int
_vsscanf(
    string  Str,
    string  Format,
    va_list Args
){
    int Round = 0;
    int Consumed = 0;
    int Nch;

    if(!*Format){
        return 0;
    }

    Nch = (Consumed++, *Str++);

    if(Nch == '\0'){
        //return EOF;
    }

    //1492

}

//1479