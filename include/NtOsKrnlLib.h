#ifndef _NTOSKRNL_LIB
#define _NTOSKRNL_LIB

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _KERNEL_MODULE_
#include <stdarg.h>

//well start with defining the Runtimes
int64_t RtlUnicodeToMultiByteSize(uint32_t* size, wchar_t* src, int32_t length);
int64_t RtlUnicodeToMultiByteN(void* dest, uint32_t destSize, uint32_t* bytesCopied, wchar_t* src, int32_t srcSize);
uint64_t RtlUnicodeToUTF8N(char* utf8Dest, int32_t utf8MaxBytes, uint32_t* utf8BytesWritten, const wchar_t* utf16Src, char strictCheck);
uint64_t CountUnicodeToUTF8(const wchar_t* utf16Src, int32_t utf16Length, uint32_t* utf8Size);
void* RtlpIsUtf8Process(char arg1);
//Now Processes
int64_t PsIsServerSilo(void* arg1);
void* PsGetCurrentServerSiloGlobals();
//Now Wc
int64_t wcstombs(void* dest, wchar_t* src, uint32_t maxBytes);
uint64_t wcstoul(wchar_t* arg1, int64_t* arg2, int32_t arg3);
uint64_t wcstoxlX(int64_t arg1, wchar_t* arg2, wchar_t** arg3, int32_t base, int32_t flags, int32_t is_unsigned);
uint64_t _wchartodigit(wchar_t arg1);
uint64_t _iswctype_l(wchar_t wchar, wchar_t charClass);
uint64_t wctomb(void* mbStr, wchar_t wchar) ;
int64_t _wctomb_s_l(int32_t* pRetValue, void* mbStr, int64_t sizeInBytes, wchar_t wchar);
int64_t wcscmp(wchar_t* arg1, wchar_t* arg2);
int64_t wcslen(wchar_t* WString);
wchar_t* wcsstr(wchar_t* haystack, wchar_t* needle) ;
int64_t wcsspn(wchar_t* arg1, wchar_t* arg2);
wchar_t* wcsrchr(wchar_t* arg1, wchar_t arg2);
wchar_t* wcscat(wchar_t* dest, wchar_t* src);
uint64_t wcscat_s(wchar_t* dest, int64_t dest_size, wchar_t* src);
wchar_t* wcschr(wchar_t* str, wchar_t ch);
wchar_t* wcscpy(wchar_t* dest, const wchar_t* src);
uint64_t wcscpy_s(wchar_t* dest, int64_t destSize, const wchar_t* src);
int64_t wcscspn(const wchar_t* str1, const wchar_t* str2);
wchar_t* wcsncat(wchar_t* dest, const wchar_t* src, int64_t count);
uint64_t wcsncat_s(wchar_t* dest, int64_t dest_size, const wchar_t* src, int64_t count);
uint64_t wcsncmp(const wchar_t* str1, const wchar_t* str2, int64_t count);
wchar_t* wcsncpy(wchar_t* dest, const wchar_t* src, int64_t count);
uint64_t wcsncpy_s(wchar_t* dest, int64_t dest_size, const wchar_t* src, int64_t count);
size_t wcsnlen(const wchar_t* str, size_t max_len);
wchar_t* LouKeCharToWchar(const char* src);
int swprintf_s(wchar_t* Buffer, size_t BufferCount, wchar_t* Format, ...);
int swprintf(wchar_t* Buffer, size_t BufferCount, wchar_t* Format, ...);
string strtok_s(
    string str,
    string Delimiters,
    string* Context
);

string strstr(
   string str,
   string strSearch
);

size_t strspn(
   string str,
   string strCharSet
);

string strrchr(
   string str,
   int c
);

int sscanf_s(
    char *buffer,
    char *format, 
    va_list va_arg
);

int _sscanf_s_l(
    char *buffer,
    char *format,
    va_list va_arg
);

int swscanf_s(
    wchar_t* buffer,
    wchar_t* format, 
    va_list va_arg
);
int _swscanf_s_l(
    wchar_t* buffer,
    wchar_t* format, 
    va_list va_arg
);

int strncpy_s(
    string Destination,
    size_t ElementsCount,
    string Source,
    size_t Count
);

string strcpy(
    string Destination,
    string Source
);

int strncat_s(
    string Destination,
    size_t NumElements,
    string Source,
    size_t Count
);

string strncat(
    string Destination,
    string Source,
    size_t Count
);

int strcpy_s(
    string Destination,
    size_t DestinationSize,
    string Source
);

int strcat_s(
    string Destination,
    size_t Elements,
    string Source
);

string strcat(
    string Destination,
    string Source
);


void *memmove(void *dest, const void *src, size_t n);

void srand(
    unsigned int seed
);

int rand();

float sqrtf(
    float x
);

double sqrt(
    double x
);

//Add To Table

int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, ...);

int sprintf(char *buffer, const char *format, ...);

int vsprintf(char *buffer, const char *format, va_list args);

NTSTATUS HeadlessDispatch(
    uint32_t DispatchCommand, 
    uint32_t* CommandData, 
    uint64_t Flags, 
    uint8_t* HeadlessLocal, 
    uint64_t* size
);

void RtlRaiseStatus(LOUSTATUS Status);
 
int64_t InterlockedPushListSList(
    uint64_t* InputList, 
    uint64_t  Unused2,
    uint64_t* OutputList,
    uint16_t  Unused4
);

int512_t InitializeSListHead(__int128* InitData);



#else //Is Kernel Module

#endif //KernelModues
#ifdef __cplusplus
}
#endif
#endif //NTLIB