#ifndef _STRING_H
#define _STRING_H
#include <stddef.h>
#include <stdint.h>

#define string char*
#define StrCmpCast const char*
#define StrCmpTrue 0

#ifndef __cplusplus
#ifndef _KERNEL_MODULE_
void* memcpy(void* destination, const void* source, size_t num);
int strncmp(const char* str1, const char* str2, size_t n);
int strcmp(const char* str1, const char* str2);
int memcmp(const void* ptr1, const void* ptr2, size_t num);
char* strncpy(char* dest, const char* src, size_t n);
size_t strlen(const char* str);

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
int _vsnprintf(char *buffer, size_t buffer_size, const char *format, ...);
#endif
#else
#include <LouDDK.h>
#ifndef _KERNEL_MODULE_
KERNEL_IMPORT void* memcpy(void* destination, const void* source, size_t num);
KERNEL_IMPORT int strncmp(const char* str1, const char* str2, size_t n);
KERNEL_IMPORT int strcmp(const char* str1, const char* str2);
KERNEL_IMPORT int memcmp(const void* ptr1, const void* ptr2, size_t num);
KERNEL_IMPORT char* strncpy(char* dest, const char* src, size_t n);
KERNEL_IMPORT size_t strlen(const char* str);

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
#endif
#endif
#define CHAR_WIDTH 16
#define CHAR_HEIGHT 16

#define SupportedCharecters 48 * 2

typedef struct {
    char character;    
    uint16_t width;
    wchar_t pixels[CHAR_HEIGHT];
} CharMapping;

#endif