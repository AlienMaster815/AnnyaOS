#include <LouDDK.h>
#include <stdarg.h>


const WCHAR WcharMap[] = {
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x8400, 
    0x8400, 0x8400, 0x8400, 0x8400, 0x8400, 0x8400, 0x8400, 0x8400, 
    0x8400, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x8101, 
    0x8101, 0x8101, 0x8101, 0x8101, 0x8101, 0x0101, 0x0101, 0x0101, 
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 
    0x0101, 0x0101, 0x0101, 0x0101, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x8201, 0x8201, 0x8201, 0x8201, 0x8201, 0x8201, 
    0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 
    0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 
    0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 
    0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 
    0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 
    0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x4800, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1400, 0x1400, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1400, 0x1000, 0x1000, 0x1000, 
    0x1000, 0x1000, 0x1000, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 
    0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 
    0x0101, 0x0101, 0x1000, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 
    0x0101, 0x0101, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 
    0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 
    0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 
    0x0201, 0x0201, 0x1000, 0x0201, 0x0201, 0x0201, 0x0201, 0x0201, 
    0x0201, 0x0201, 0x0101, 0x0101, 0x9090, 0x9090
};

static const wchar_t* RtlCharecterMap = WcharMap;


static 
WCHAR 
tolowerTransfermationHelper(
    WCHAR SourceCharacter,
    WCHAR MaskingValue
){

    if((SourceCharacter != 0xFFFF) && (SourceCharacter < 0x100)){
        return (WCHAR)WcharMap[SourceCharacter] & MaskingValue;
    }

    return 0x00;
}

LOUDDK_API_ENTRY 
WCHAR 
RtlUpcaseUnicodeChar(
    WCHAR SourceCharacter
){
    if(SourceCharacter < 0x61){
        return SourceCharacter;
    }
    if(SourceCharacter <= 0x7A){
        return (wchar_t)((uint32_t)SourceCharacter - 0x20);
    }

    uint64_t RtlCharecterMapR = (uint64_t)RtlCharecterMap;
    uint32_t TmpSourceCharacter = SourceCharacter;
    if(!RtlCharecterMap){
        return 0x00;
    }

    wchar_t Result = *(wchar_t*)(RtlCharecterMapR + ((uint64_t)((uint32_t)*(uint16_t*)(RtlCharecterMapR + ((uint64_t)((uint32_t)*(uint16_t*)(RtlCharecterMapR + ((uint64_t)SourceCharacter >> 8 << 1)) + (TmpSourceCharacter >> 4 & 0xf)) << 1)) + (TmpSourceCharacter & 0xf)) << 1));
 
    return (wchar_t)(Result + SourceCharacter);
}

LOUDDK_API_ENTRY
wchar_t towupper(wchar_t wc) {
    return RtlUpcaseUnicodeChar(wc);
}


LOUDDK_API_ENTRY
wchar_t towlower(wchar_t wc) {
    wchar_t Result = wc;
    if(!tolowerTransfermationHelper(wc, 1)){
        return Result;
    }
    return Result + 0x20;
}





#define VSPRINTF_S_OVERFLOW (((size_t)Buffer - (size_t)BufferStart) + Addition) > BufferCount
LOUDDK_API_ENTRY
void intToString(uint64_t num, char* str);
LOUDDK_API_ENTRY
void uintToHexString(uint64_t number, char* hexString);



LOUDDK_API_ENTRY
int vswprintf_s(wchar_t* Buffer, size_t BufferCount, wchar_t* Format, va_list args);

LOUDDK_API_ENTRY
int swprintf(wchar_t* Buffer, size_t BufferCount, wchar_t* Format, ...){
    va_list va_arg;
    va_start(va_arg, Format);
    int result = vswprintf_s(Buffer, BufferCount, Format, va_arg);
    va_end(va_arg);
    return result;
}

LOUDDK_API_ENTRY
int swprintf_s(wchar_t* Buffer, size_t BufferCount, wchar_t* Format, ...){
    va_list va_arg;
    va_start(va_arg, Format);
    int result = vswprintf_s(Buffer, BufferCount, Format, va_arg);
    va_end(va_arg);
    return result;
}

LOUDDK_API_ENTRY
int vswprintf_s(wchar_t* Buffer, size_t BufferCount, wchar_t* Format, va_list args) {

    size_t Index = 0;
    size_t Addition = 0;
    if((!Buffer) || (BufferCount == 0)){
        return -1;
    }
    UNUSED wchar_t* BufferStart = Buffer;

    while((Format[Index]) && (((size_t)Buffer - (size_t)BufferStart) < BufferCount)){
        if(Format[Index] == L'%'){
                Index++; // Move past '%'
                                    
                if((wcsncmp(&Format[Index], L"s", wcslen(L"S")) == 0) || (wcsncmp(&Format[Index], L"S", wcslen(L"S")) == 0)){
                    const wchar_t* strArg = va_arg(args, const wchar_t*);
                    Addition = wcslen((wchar_t*)strArg);
                    if(VSPRINTF_S_OVERFLOW){
                        return -1;
                    }
                    wcsncpy(Buffer, strArg, Addition);
                    Buffer += Addition;
                    Index += 1;
                }

                else if((wcsncmp(&Format[Index], L"x", wcslen(L"x")) == 0) || (wcsncmp(&Format[Index], L"X", wcslen(L"X")) == 0)){
                    int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                    char hexString[21];                    
                    uintToHexString((uint64_t)num, hexString);
                    wchar_t* Foo = LouKeCharToWchar(hexString);
                    Addition = wcslen(Foo);
                    if(VSPRINTF_S_OVERFLOW){
                        return -1;
                    }
                    wcsncpy(Buffer, Foo, Addition);
                    Buffer += Addition;
                    Index += 1;
                }
                else if((wcsncmp(&Format[Index], L"#x", wcslen(L"#x")) == 0) || (wcsncmp(&Format[Index], L"#X", wcslen(L"#X")) == 0)){
                    int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                    char hexString[21];                    
                    uintToHexString((uint64_t)num, hexString);
                    wchar_t* Foo = LouKeCharToWchar(hexString);
                    Addition = wcslen(Foo);
                    if(VSPRINTF_S_OVERFLOW){
                        return -1;
                    }
                    wcsncpy(Buffer, Foo, Addition);
                    Buffer += Addition;
                    Index += 2;
                }
                else if((wcsncmp(&Format[Index], L"02X", wcslen(L"02x")) == 0x00) || 
                        (wcsncmp(&Format[Index], L"02X", wcslen(L"02X")) == 0x00) ||
                        (wcsncmp(&Format[Index], L"04X", wcslen(L"04x")) == 0x00) ||
                        (wcsncmp(&Format[Index], L"04X", wcslen(L"04x")) == 0x00) ||
                        (wcsncmp(&Format[Index], L"08X", wcslen(L"08x")) == 0x00) ||
                        (wcsncmp(&Format[Index], L"08X", wcslen(L"08x")) == 0x00)) {

                    int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                    char hexString[21];                    
                    uintToHexString((uint64_t)num, hexString);
                    wchar_t* Foo = LouKeCharToWchar(hexString);
                    Addition = wcslen(Foo);
                    if(VSPRINTF_S_OVERFLOW){
                        return -1;
                    }
                    wcsncpy(Buffer, Foo, Addition);
                    Buffer += Addition;
                    Index += 3;
                }
                else if((wcsncmp(&Format[Index], L"d", wcslen(L"d")) == 0) || (wcsncmp(&Format[Index], L"D", wcslen(L"D")) == 0) ||
                        (wcsncmp(&Format[Index], L"u", wcslen(L"u")) == 0) || (wcsncmp(&Format[Index], L"U", wcslen(L"U")) == 0)){
                        int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                        char hexString[21];                    
                        intToString((uint64_t)num, hexString);
                        wchar_t* Foo = LouKeCharToWchar(hexString);
                        Addition = wcslen(Foo);
                        if(VSPRINTF_S_OVERFLOW){
                            return -1;
                        }
                        wcsncpy(Buffer, Foo, Addition);
                        Buffer += Addition;
                        Index += 1;
                }
                else if((wcsncmp(&Format[Index], L"ld", wcslen(L"ld")) == 0) || (wcsncmp(&Format[Index], L"LD", wcslen(L"LD")) == 0) || 
                        (wcsncmp(&Format[Index], L"lu", wcslen(L"lu")) == 0) || (wcsncmp(&Format[Index], L"LU", wcslen(L"LU")) == 0) ||
                        (wcsncmp(&Format[Index], L"hd", wcslen(L"hd")) == 0) || (wcsncmp(&Format[Index], L"HD", wcslen(L"HD")) == 0) ||
                        (wcsncmp(&Format[Index], L"hu", wcslen(L"hu")) == 0) || (wcsncmp(&Format[Index], L"HU", wcslen(L"HU")) == 0)){
                        int64_t num = va_arg(args, int64_t); // get the Number in integer Form
                        char hexString[21];                    
                        intToString((uint64_t)num, hexString);
                        wchar_t* Foo = LouKeCharToWchar(hexString);
                        Addition = wcslen(Foo);
                        if(VSPRINTF_S_OVERFLOW){
                            return -1;
                        }
                        wcsncpy(Buffer, Foo, Addition);
                        Buffer += Addition;
                        Index += 2;
                }
                else{
                    Index--;
                    *Buffer = Format[Index];
                    Index++;
                    Buffer++;
                }
            }
    }

    return (int)((size_t)Buffer - (size_t)BufferStart);
}



LOUDDK_API_ENTRY
int tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

LOUDDK_API_ENTRY
int toupper(int c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }
    return c;
}

LOUDDK_API_ENTRY
int sscanf_s(
    char *buffer,
    char *format, 
    va_list va_arg
){

    return -1;
};

LOUDDK_API_ENTRY
int _sscanf_s_l(
    char *buffer,
    char *format,
    va_list va_arg
){

    return -1;
}

LOUDDK_API_ENTRY
int swscanf_s(
    wchar_t* buffer,
    wchar_t* format, 
    va_list va_arg
){

    return -1;
}

LOUDDK_API_ENTRY
int _swscanf_s_l(
    wchar_t* buffer,
    wchar_t* format, 
    va_list va_arg
){

    return -1;
}

LOUDDK_API_ENTRY
float sqrtf(
    float x
) {
    //if (x < 0.0f) {
    //    // Handle negative input (NaN or an error in your system)
    //    return -1.0f; // Or define a specific error value
    //}

    //float result = x;
    //float half = 0.5f * x;

    // Use the Newton-Raphson method for approximation
    // Initial guess
    //int32_t i = *(int32_t*)&result;          // Interpret float bits as int
    //i = 0x5f3759df - (i >> 1);               // Initial magic number
    //result = *(float*)&i;                    // Convert bits back to float
    //result = result * (1.5f - (half * result * result)); 
    //result = result * (1.5f - (half * result * result)); 
    //result = result * (1.5f - (half * result * result)); 
    //result = result * (1.5f - (half * result * result)); 
    //result = result * (1.5f - (half * result * result)); 

    return 0;//x * result;
}

LOUDDK_API_ENTRY
double sqrt(
    double x
) {
    //if (x < 0.0) {
    //    // Handle negative input (NaN or error)
    //    return -1.0; // Or return an appropriate error code or NaN
    //}

    //double result = x;
    //double half = 0.5 * x;

    // Use the Newton-Raphson method for approximation
    // Initial guess
    //int64_t i = *(int64_t*)&result;          // Interpret double bits as int
    //i = 0x5fe6ec85e7de30da - (i >> 1);       // Initial magic number
    //result = *(double*)&i;                   // Convert bits back to double
    //result = result * (1.5 - (half * result * result)); // First iteration
    //result = result * (1.5 - (half * result * result)); // Second iteration

    // Refine the result
    return 0;//x * result;
}

LOUDDK_API_ENTRY
int sprintf_s(
    char *buffer, 
    size_t sizeOfBuffer, 
    const char *format, 
    ...
) {
    if ((buffer == 0x00) || (format == 0x00) || (sizeOfBuffer == 0)) {
        return -EINVAL; // Invalid argument
    }

    va_list args;
    va_start(args, format);

    // Use vsnprintf to safely format the string into the buffer
    int result = _vsnprintf(buffer, sizeOfBuffer, format, args);

    va_end(args);

    // If result is negative, an encoding error occurred
    if (result < 0) {
        return -1; // Error
    }

    // Check if the result exceeds the buffer size
    if ((size_t)result >= sizeOfBuffer) {
        buffer[0] = '\0'; // Null-terminate the buffer in case of overflow
        return -ERANGE;   // Indicate the buffer was too small
    }

    return result; // Return the number of characters written
}

LOUDDK_API_ENTRY
int vsprintf(char *buffer, const char *format, va_list args) {
    if ((buffer == 0x00) || (format == 0x00)) {
        return -1; // Error: Invalid arguments
    }

    // Use vsnprintf with a large enough buffer size to avoid truncation
    // Since this is the non-safe version, we assume buffer is large enough.
    return _vsnprintf(buffer, (size_t)-1, format, args);
}

LOUDDK_API_ENTRY
int sprintf(char *buffer, const char *format, ...) {
    if ((buffer == 0x00) || (format == 0x00)) {
        return -1; // Error: Invalid arguments
    }

    va_list args;
    va_start(args, format);

    // Use vsprintf to format the string into the buffer
    int result = vsprintf(buffer, format, args);

    va_end(args);

    return result; // Return the number of characters written
}


LOUDDK_API_ENTRY
void *memmove(void *dest, const void *src, size_t n) {
    if (dest == 0x00 || src == 0x00) {
        return 0x00; // Handle invalid arguments
    }

    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    if (d < s) {
        // Copy forward if the destination starts before the source
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else if (d > s) {
        // Copy backward if the destination starts after the source
        for (size_t i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }

    return dest;
}


int LouWStrnCpy(PWSTR WString, ULONG StrLen, PWSTR StringCopy){
    for(ULONG i = 0 ; i < StrLen; i++){
        WString[i] = StringCopy[i];
    }
    return 0;
}