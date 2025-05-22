#include <LouAPI.h>

//the following code was recreated from documentation
//and research of the C std library

#define PRINTF_NTOA_BUFFER_SIZE             32
#define PRINTF_FTOA_BUFFER_SIZE             32
#define PRINTF_DEFUALT_FLOAT_PRECISION      6
#define PRINTF_MAX_FLOAT                    1e9
#define PRINTF_FLAG_ZEROPAD                 (1 << 0)
#define PRINTF_FLAG_LEFT                    (1 << 1)
#define PRINTF_FLAG_PLUS                    (1 << 2)
#define PRINTF_FLAG_SPACE                   (1 << 3)
#define PRINTF_FLAG_HASH                    (1 << 4)
#define PRINTF_FLAG_UPPERCASE               (1 << 5)
#define PRINTF_FLAG_CHAR                    (1 << 6)
#define PRINTF_FLAG_SHORT                   (1 << 7)
#define PRINTF_FLAG_LONG                    (1 << 8)
#define PRINTF_FLAG_LONG_LONG               (1 << 9)
#define PRINTF_FLAG_PRECISION               (1 << 10)
#define PRINTF_FLAG_ADAPT_EXPONENT          (1 << 11)

typedef void (*OUTPUT_FUNCTION)(char Charecter, void* Buffer, size_t Index, size_t Length);

typedef struct _OUTPUT_FUNCTION_WRAPPER{
    void    (*Function)(char Charecter, void* Arguments);
    void*   Arguments;
}OUTPUT_FUNCTION_WRAPPER, * POUTPUT_FUNCTION_WRAPPER;

static inline void InternalOutputBuffer(char Charecter, void* Buffer, size_t Index, size_t Length){
    if(Index < Length){
        ((string)Buffer)[Index] = Charecter;
    }
}

static inline void InternalOutputNull(char Charecter, void* Buffer, size_t Index, size_t Length){

}

static inline void InternalOutputCharecter(char Charecter, void* Buffer, size_t Index, size_t Length){
    if(Charecter){
        char Foo[2] = {'\0'};
        Foo[0] = Charecter;
        LouPrint(Foo);
    }
}

static inline void InternalOutputFunction(char Charecter, void* Buffer, size_t Index, size_t Length){
    if(Charecter){
        ((POUTPUT_FUNCTION_WRAPPER)Buffer)->Function(Charecter, ((POUTPUT_FUNCTION_WRAPPER)Buffer)->Arguments);
    }
}

static inline uint32_t InternalStrlenSafe(const string Str, size_t MaxLength){
    size_t Index = 0;
    while(Index < MaxLength){
        if(Str[Index] == '\0'){
            break;
        }
        Index++;
    }   
    return Index;
}

static inline bool InternalIsDigit(char Charecter){
    return ((Charecter >= '0') && (Charecter <= '9'));
}

UNUSED static uint32_t InternalAsciiToInt(const string* Strp){
    uint32_t i = 0;
    while(InternalIsDigit(**Strp)){
        i = i * 10 + (uint32_t)(*((*Strp)++) - '0');
    }
    return i;
}

UNUSED static size_t InternalOutputReversedString(
    OUTPUT_FUNCTION OutFunction, 
    string Buffer, 
    size_t Index, 
    size_t MaxLength,
    const char*  CBuffer,
    size_t Length, 
    uint32_t Width, 
    uint32_t Flags
){
    const size_t StartIndex = Index;

    if((!(Flags & PRINTF_FLAG_LEFT)) && (!(Flags & PRINTF_FLAG_ZEROPAD))){
        for(size_t i = Length; i < Width; i++){
            OutFunction(' ', Buffer, Index++, MaxLength);
        }
    }

    while(Length){
        OutFunction(CBuffer[--Length], Buffer, Index++, MaxLength);
    }

    if(Flags & PRINTF_FLAG_LEFT){
        while((Index - StartIndex) < Width){
            OutFunction(' ', Buffer, Index++, MaxLength);
        }
    }

    return Index;
}

UNUSED static size_t InternalNtoaFormat(
    OUTPUT_FUNCTION OutFunction, string Buffer, 
    size_t Index, size_t MaxLength, 
    string Buffer2, size_t Length, 
    bool Negative, uint32_t Base, 
    uint32_t Prec, uint32_t Width, 
    uint32_t Flags
){

    if(!(Flags & PRINTF_FLAG_LEFT)){
        if((Width) && (Flags & PRINTF_FLAG_ZEROPAD) && (Negative || (Flags & (PRINTF_FLAG_PLUS | PRINTF_FLAG_SPACE)))){
            Width--;
        }
        while((Length < Prec) && (Length < PRINTF_NTOA_BUFFER_SIZE)){
            Buffer2[Length++] = '0';
        }
        while((Flags & PRINTF_FLAG_ZEROPAD) && (Length < Width) && (Length < PRINTF_NTOA_BUFFER_SIZE)){
            Buffer2[Length++] = '0';
        }
    }

    if(Flags & PRINTF_FLAG_HASH){
        if(!(Flags & PRINTF_FLAG_PRECISION) && Length && ((Length == Prec) || (Length == Width))){
            Length--;
            if(Length && (Base == 16)){
                Length--;
            }
        }
        if((Base == 16) && !(Flags & PRINTF_FLAG_UPPERCASE) && (Length < PRINTF_NTOA_BUFFER_SIZE)){
            Buffer2[Length++] = 'x';
        }else if((Base == 16) && (Flags & PRINTF_FLAG_UPPERCASE) && (Length < PRINTF_NTOA_BUFFER_SIZE)){
            Buffer2[Length++] = 'X';
        }else if((Base == 2) && (Length < PRINTF_NTOA_BUFFER_SIZE)){
            Buffer2[Length++] = 'b';
        }
        if(Length < PRINTF_NTOA_BUFFER_SIZE){
            Buffer2[Length++] = '0';
        }
    }

    if(Length < PRINTF_NTOA_BUFFER_SIZE){
        if(Negative){
            Buffer2[Length++] = '-';
        }else if(Flags & PRINTF_FLAG_PLUS){
            Buffer2[Length++] = '+';
        }else if(Flags & PRINTF_FLAG_SPACE){
            Buffer2[Length++] = ' ';
        }
    }
    return InternalOutputReversedString(OutFunction, Buffer, Index, MaxLength, Buffer2, Length, Width, Flags);
}

UNUSED static size_t InternalNtoaLong(
    OUTPUT_FUNCTION OutFunction, string Buffer,
    size_t Index, size_t MaxLength,
    unsigned long Value, bool Negative,
    unsigned long Base, uint32_t Prec, 
    uint32_t Width, uint32_t Flags
){
    char StackBuffer[PRINTF_NTOA_BUFFER_SIZE];
    size_t Length = 0;
    char Digit = 0;

    if(!Value){
        Flags &= ~(PRINTF_FLAG_HASH);
    }

    if(!(Flags & PRINTF_FLAG_PRECISION) || Value){
        do{ 
            Digit = (char)(Value % Base);
            StackBuffer[Length++] = Digit < 10 ? '0' + Digit : ((Flags & PRINTF_FLAG_UPPERCASE) ? 'A' : 'a') + Digit - 10;
            Value /= Base;
        }while(Value && (Length < PRINTF_NTOA_BUFFER_SIZE));
    }
    return InternalNtoaFormat(OutFunction, Buffer, Index, MaxLength, StackBuffer, Length, Negative, (unsigned int)Base, Prec, Width, Flags);
}

UNUSED static size_t InternalNtoaLongLong(
    OUTPUT_FUNCTION OutFunction, string Buffer,
    size_t Index, size_t MaxLength,
    unsigned long long Value, bool Negative,
    unsigned long long Base, uint32_t Prec, 
    uint32_t Width, uint32_t Flags 
){
    char StackBuffer[PRINTF_NTOA_BUFFER_SIZE];
    size_t Length = 0;
    char Digit = 0;
    if(!Value){
        Flags &= ~(PRINTF_FLAG_HASH);
    }

    if(!(Flags & PRINTF_FLAG_PRECISION) || Value){
        do{
            Digit = (char)(Value % Base);
            StackBuffer[Length++] = Digit < 10 ? '0' + Digit : ((Flags & PRINTF_FLAG_UPPERCASE) ? 'A' : 'a' + Digit - 10);
            Value /= Base;
        }while(Value && (Length < PRINTF_NTOA_BUFFER_SIZE));
    }
    return InternalNtoaFormat(OutFunction, Buffer, Index, MaxLength, StackBuffer, Length, Negative, (unsigned int)Base, Prec, Width, Flags);
}

UNUSED static int InternalVsnPrintf(
    OUTPUT_FUNCTION OutFunction, string Buffer, 
    const size_t MaxLength, const string Format,
    va_list Arguments
){
    int W = 0;
    int Prec2 = 0;
    uint32_t Flags = 0;
    uint32_t Width = 0;
    uint32_t Prec = 0;
    uint32_t N = 0;
    size_t Index = 0;
    uint32_t Base = 0;

    if(!Buffer){
        OutFunction = InternalOutputNull;
    }

    while(*Format){
        if(*Format != '%'){
            OutFunction(*Format, Buffer, Index++, MaxLength);
            Format++;
            continue;
        }else{
            Format++;
        }
        Flags = 0;
        do {
            switch(*Format){
                case '0': {Flags |= PRINTF_FLAG_ZEROPAD; Format++; N = 1; break;}
                case '-': {Flags |= PRINTF_FLAG_LEFT   ; Format++; N = 1; break;}
                case '+': {Flags |= PRINTF_FLAG_PLUS   ; Format++; N = 1; break;}
                case ' ': {Flags |= PRINTF_FLAG_SPACE  ; Format++; N = 1; break;}
                case '#': {Flags |= PRINTF_FLAG_HASH   ; Format++; N = 1; break;}
                default:{ N = 0; break;};
            }
        }while(N);
    }

    Width = 0;
    if(InternalIsDigit(*Format)){
        Width = InternalAsciiToInt(&Format);
    }else if (*Format == '*'){
        W = va_arg(Arguments, int);
        if(W < 0){
            Flags |= PRINTF_FLAG_LEFT;
            Width = (uint32_t)-W;
        }else{
            Width = (uint32_t)W;
        }
        Format++;
    }

    Prec = 0;
    if(*Format == '.'){
        Flags |= PRINTF_FLAG_PRECISION;
        Format++;
        if(InternalIsDigit(*Format)){
            Prec = InternalAsciiToInt(&Format);
        }else if(*Format == '*'){
            Prec2 = (int)va_arg(Arguments, int);
            Prec = Prec2 > 0 ? (unsigned int)Prec2 : 0;
            Format++;
        }
    }

    switch(*Format){
        case 'l':{
            Flags |= PRINTF_FLAG_LONG;
            Format++;
            if(*Format == 'l'){
                Flags |= PRINTF_FLAG_LONG_LONG;
                Format++; 
            } 
            break;
        }
        case 'h':{
            Flags |= PRINTF_FLAG_SHORT;
            Format++;
            if(*Format == 'h'){
                Flags |= PRINTF_FLAG_CHAR;
                Format++;
            }
            break;
        }
        case 't':
        case 'j':
        case 'z':{
            Flags |= PRINTF_FLAG_LONG_LONG;
            Format++;
            break;
        }
        default:
            break;
    }

    switch (*Format){
        case 'd':
        case 'i':
        case 'u':
        case 'x':
        case 'X':
        case 'o':
        case 'b':{
            if((*Format == 'x') || (*Format == 'X')){
                Base = 16;
            }else if(*Format == 'o'){
                Base = 8;
            }else if(*Format == 'b'){
                Base = 2;
            }
            else {
                Base = 10;
            }

            if(*Format == 'X'){
                Flags |= PRINTF_FLAG_UPPERCASE;
            }

            if((*Format != 'i') && (*Format != 'd')){
                Flags &= ~(PRINTF_FLAG_PLUS | PRINTF_FLAG_SPACE);
            }

            if(Flags & PRINTF_FLAG_PRECISION){
                Flags &= ~(PRINTF_FLAG_ZEROPAD);
            }

            if((*Format == 'i') || (*Format == 'd')){
                if(Flags & PRINTF_FLAG_LONG_LONG){
                    long long Value = va_arg(Arguments, long long);
                    Index = InternalNtoaLongLong(OutFunction, Buffer, Index, MaxLength, (unsigned long long)((Value > 0) ? Value : 0 - Value), Value < 0, Base, Prec, Width, Flags);
                }else if(Flags & PRINTF_FLAG_LONG){
                    long Value = va_arg(Arguments, long);
                    Index = InternalNtoaLong(OutFunction, Buffer, Index, MaxLength, (unsigned long)((Value > 0) ? Value : 0 - Value), Value < 0, Base, Prec, Width, Flags);
                }else{
                    int Value = ((Flags & PRINTF_FLAG_CHAR) ? (char)va_arg(Arguments, int) : (Flags & PRINTF_FLAG_SHORT) ? (short int)va_arg(Arguments, int) : va_arg(Arguments, int));
                    Index = InternalNtoaLong(OutFunction, Buffer, Index, MaxLength, (unsigned long)((Value > 0) ? Value : 0 - Value), Value < 0, Base, Prec, Width, Flags);
                }
            }else {
                if(Flags & PRINTF_FLAG_LONG_LONG){
                    Index = InternalNtoaLongLong(OutFunction, Buffer, Index, MaxLength, va_arg(Arguments, unsigned long long), false, Base, Prec, Width, Flags);
                }else if(Flags & PRINTF_FLAG_LONG){
                    Index = InternalNtoaLong(OutFunction, Buffer, Index, MaxLength, va_arg(Arguments, unsigned long), false, Base, Prec, Width, Flags);
                }else{
                    unsigned int Value = ((Flags & PRINTF_FLAG_CHAR) ? (unsigned char)va_arg(Arguments, unsigned int) : (Flags & PRINTF_FLAG_SHORT) ? (unsigned short int)va_arg(Arguments, unsigned int) : va_arg(Arguments, unsigned int));
                    Index = InternalNtoaLong(OutFunction, Buffer, Index, MaxLength, Value, false, Base, Prec, Width, Flags);
                }
            }
            Format++;
            break;


        }
        case 'c':{
            unsigned int l = 0;
            if(!(Flags & PRINTF_FLAG_LEFT)){
                while(l++ < Width){
                    OutFunction(' ', Buffer, Index++, MaxLength);
                }
            }
            Format++;
            break;
        }
        case 's':{
            string p = va_arg(Arguments, string);
            unsigned int l = InternalStrlenSafe(p, Prec ? Prec : (size_t)-1);
            if(Flags & PRINTF_FLAG_PRECISION){
                l = (l < Prec ? l : Prec);
            }   
            if(!(Flags & PRINTF_FLAG_LEFT)){
                while(l++ < Width){
                    OutFunction(' ', Buffer, Index++, MaxLength);
                }
            }
            while((*p != 0) && (!(Flags & PRINTF_FLAG_PRECISION) || Prec--)){
                OutFunction(*(p++), Buffer, Index++, MaxLength);
            }
            if(Flags & PRINTF_FLAG_LEFT){
                while(l++ < Width){
                    OutFunction(' ', Buffer, Index++, MaxLength);
                }
            }
            Format++;
            break;
        }

        case 'p':{
            Width = sizeof(void*) * 2;
            Flags |= (PRINTF_FLAG_ZEROPAD | PRINTF_FLAG_UPPERCASE);
            Index = InternalNtoaLongLong(OutFunction, Buffer, Index, MaxLength, (uintptr_t)va_arg(Arguments, void*), false, 16, Prec, Width, Flags);
            Format++;
            break;
        }
        case '%':{
            OutFunction('%', Buffer, Index++, MaxLength);
            Format++;
            break;
        }
        default:{
            OutFunction(*Format, Buffer, Index++, MaxLength);
            Format++;
            break;
        }
    }

    OutFunction((char)0, Buffer, (Index < MaxLength) ? Index : (MaxLength - 1), MaxLength);

    return (int)Index;
}

int StdIoPrintf(const char* Format, ...){
    int Result = 0;
    char Buffer[1];
    va_list Arguments;
    va_start(Arguments, Format);
    Result = InternalVsnPrintf(InternalOutputCharecter, Buffer, (size_t)-1, Format, Arguments);
    va_end(Arguments);
    return Result;
}
int StdIoSPrintf(char* Buffer, const char* Format, ...){
    int Result = 0;
    va_list Arguments;
    va_start(Arguments, Format);
    Result = InternalVsnPrintf(InternalOutputBuffer, Buffer, (size_t)-1, Format, Arguments);
    va_end(Arguments);
    return Result;
}
int StdIoSnPrintf(char* Buffer, size_t Count, const char* Format, ...){
    int Result = 0;
    va_list Arguments;
    va_start(Arguments, Format);
    Result = InternalVsnPrintf(InternalOutputBuffer, Buffer, Count, Format, Arguments);
    va_end(Arguments);
    return Result;
}
int StdIoVsnPrintf(char* Buffer, size_t Count, const char* Format, va_list Arguments){
    return InternalVsnPrintf(InternalOutputBuffer, Buffer, Count, Format, Arguments);
}
int StdIoVPrintf(const char* Format, va_list Arguments){
    char Buffer[1];
    return InternalVsnPrintf(InternalOutputCharecter, Buffer, (size_t)-1, Format, Arguments);
}