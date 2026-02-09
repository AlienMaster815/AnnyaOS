#ifndef _STRING_H
#define _STRING_H
#include <stddef.h>
#include <stdint.h>

#define string char*
#define LOUSTR char*
#define StrCmpCast const char*
#define StrCmpTrue 0

#ifndef __cplusplus
#ifndef _KERNEL_MODULE_
void* memcpy(void* destination, const void* source, size_t num);
int strncmp(const char* str1, const char* str2, size_t n);
int strcmp(const char* str1, const char* str2);
int memcmp(const void* ptr1, const void* ptr2, size_t num);
char* strncpy(char* dest, const char* src, size_t n);
char* strcpy(char* dest, const char* src);
char* strcat(char* dest, const char* src);
size_t strlen(const char* str);
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
void* memset(void* dest, int value, size_t count);
string LouKeCombineStr_s(string String1, size_t Str1Size, string String2, size_t Str2Size);
string LouKeCombineStr(string String1, string String2);
string LouKeAddFileToPath(string Path, string FileName);
string LouKeAddFileToPath_s(string Path, size_t PathLength, string FileName, size_t FileNameLength);

#define strstart(s1, s2) (!strncmp(s1 , s2, strlen(s2)))

#endif
#else
#include <LouDDK.h>
#ifndef _KERNEL_MODULE_
KERNEL_IMPORT void LouKeStrLowerToUpper(string Format);
KERNEL_IMPORT void* memcpy(void* destination, const void* source, size_t num);
KERNEL_IMPORT int strncmp(const char* str1, const char* str2, size_t n);
KERNEL_IMPORT int strcmp(const char* str1, const char* str2);
KERNEL_IMPORT int memcmp(const void* ptr1, const void* ptr2, size_t num);
KERNEL_IMPORT char* strncpy(char* dest, const char* src, size_t n);
KERNEL_IMPORT size_t strlen(const char* str);
KERNEL_IMPORT size_t wstrlen(const wchar_t* str);
KERNEL_IMPORT int32_t stringToInt32(const char* str);
KERNEL_IMPORT uint32_t stringToUnsignedInt32(const char* str);
KERNEL_IMPORT int16_t stringToInt16(const char* str);
KERNEL_IMPORT uint16_t stringToUnsignedInt16(const char* str);
KERNEL_IMPORT int64_t stringToInt64(const char* str);
KERNEL_IMPORT uint64_t stringToUnsignedInt64(const char* str);
KERNEL_IMPORT int8_t stringToInt8(const char* str);
KERNEL_IMPORT uint8_t stringToUnsignedInt8(const char* str);
KERNEL_IMPORT char* LouKeCharArrayToString(char* ConvertingString, uint16_t ArraySize);
KERNEL_IMPORT void UIntToString(unsigned int num, char* str);
KERNEL_IMPORT void reverse_string(string str, int length);
KERNEL_IMPORT void double_to_string(string Buffer, long double value);
KERNEL_IMPORT void float_to_string(string Buffer, float value);
KERNEL_IMPORT void long_double_to_string(string Buffer, long double value);
KERNEL_IMPORT char* ConvertWCharToChar(const wchar_t* wstr);
KERNEL_IMPORT int _vsnprintf(char *buffer, size_t buffer_size, const char *format, ...);
KERNEL_IMPORT string LouKeCombineStr_s(string String1, size_t Str1Size, string String2, size_t Str2Size);
KERNEL_IMPORT string LouKeCombineStr(string String1, string String2);
KERNEL_IMPORT string LouKeAddFileToPath(string Path, string FileName);
KERNEL_IMPORT string LouKeAddFileToPath_s(string Path, size_t PathLength, string FileName, size_t FileNameLength);
#endif
#endif

#define CHAR_HEIGHT 16

#define SupportedCharecters 49 * 2

typedef struct {
    char character;    
    uint16_t width;
    wchar_t pixels[CHAR_HEIGHT];
} CharMapping;

#endif
