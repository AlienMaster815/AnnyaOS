#ifndef _STRING_H
#define _STRING_H

#include <Unicode.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <cstdint.h>

#define string char*
#define LOUSTR char*
#define StrCmpCast const char*
#define StrCmpTrue 0

#define CHAR_HEIGHT 16

#define SupportedCharecters 49 * 2

typedef struct {
    char character;    
    uint16_t width;
    wchar_t pixels[CHAR_HEIGHT];
} CharMapping;

#ifndef _USER_MODE_CODE_

void* memcpy(void* destination, const void* source, size_t num);
int strncmp(const char* str1, const char* str2, size_t n);
int strcmp(const char* str1, const char* str2);
int memcmp(const void* ptr1, const void* ptr2, size_t num);
KERNEL_EXPORT char* strncpy(char* dest, const char* src, size_t n);
char* strcpy(char* dest, const char* src);
char* strcat(char* dest, const char* src);
KERNEL_EXPORT size_t strlen(const char* str);
size_t wstrlen(const wchar_t* str);
unsigned long strtoul(const char* nptr, char** endptr, int base);

int32_t stringToInt32(const char* str);
uint32_t stringToUnsignedInt32(const char* str);
int16_t stringToInt16(const char* str);
uint16_t stringToUnsignedInt16(const char* str);
int64_t stringToInt64(const char* str);
uint64_t stringToUnsignedInt64(const char* str);
int8_t stringToInt8(const char* str);
uint8_t stringToUnsignedInt8(const char* str);
char* LouKeCharArrayToString(char* ConvertingString, uint16_t ArraySize);
void UIntToString(unsigned int num, char* str);
void reverse_string(string str, int length);
void double_to_string(string Buffer, long double value);
void float_to_string(string Buffer, float value);
void long_double_to_string(string Buffer, long double value);
char* ConvertWCharToChar(const wchar_t* wstr);
void LouKeStrLowerToUpper(string Format);
int isprint(int ch);
int _vsnprintf(char *buffer, size_t buffer_size, const char *format, ...);
int toupper(int c);
int tolower(int c);
int isxdigit(int c);
int isspace(int c);
int isdigit(int c);

int StdIoPrintf(const char* Format, ...);
int StdIoSPrintf(char* Buffer, const char* Format, ...);
int StdIoSnPrintf(char* Buffer, size_t Count, const char* Format, ...);
int StdIoVsnPrintf(char* Buffer, size_t Count, const char* Format, va_list Arguments);
int StdIoVPrintf(const char* Format, va_list Arguments);
KERNEL_EXPORT void* memset(void* dest, int value, size_t count);
string LouKeCombineStr_s(string String1, size_t Str1Size, string String2, size_t Str2Size);
string LouKeCombineStr(string String1, string String2);
string LouKeAddFileToPath(string Path, string FileName);
string LouKeAddFileToPath_s(string Path, size_t PathLength, string FileName, size_t FileNameLength);
int strncat_s(string Destination, size_t NumElements, string Source, size_t Count);
string strncat(string Destination, string Source, size_t Count);
int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, ...);
char* strstr(char* String1, char* String2);
int snprintf(char* String, size_t Size, const char* Format, ...);
#define strstart(s1, s2) (!strncmp(s1 , s2, strlen(s2)))

LOUSTR StrFingFirstFromEndSafe(LOUSTR String, LOUSTR Token, int64_t Limit);
LOUSTR StrFingFirstFromEnd(LOUSTR String, LOUSTR Token);

#else 

#ifndef _LOUDLL_
ANNA_IMPORT void* LouMemSet(void* dest, int value, size_t count);
#else 
void* LouMemSet(void* dest, int value, size_t count);
int strncmp(const char* str1, const char* str2, size_t n);
#endif

#endif
#ifdef __cplusplus
}
#endif
#endif
