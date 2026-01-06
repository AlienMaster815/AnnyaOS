/*
; Copyright(C) 2023 Tyler Grenier
*/

#ifdef __x86_64__
    #include <limits.h>
#endif

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <drivers/display/vga.h>

void LouKeDebuggerCommunicationsSendCharecter(char Charecter);

int _vsnprintf(char *buffer, size_t buffer_size, const char *format, ...);

#define INCREASE_Y 16+1
#define INCREASE_X 16+1

void print_binary64(uint64_t number);
void print_binary32(uint32_t number);
void print_binary16(uint16_t number);
void print_binary8(uint8_t number);
void intToString(uint64_t num, char* str);
void sintToString(int64_t num, char* str);
//void uintToLittleEndianHexString(uint64_t number, char* hexString);
void uintToHexString(uint64_t number, char* hexString);

static spinlock_t PrintLock; 

void print_binary64(uint64_t number) {
    for(uint8_t BitMask = 0; BitMask < 64; BitMask++){
        if(number & (1 << (63 - BitMask))){
            LouKeDebuggerCommunicationsSendCharecter('1');
            LouKeOsDosPrintCharecter('1');
        }else{
            LouKeDebuggerCommunicationsSendCharecter('0');
            LouKeOsDosPrintCharecter('1');
        }
    }
}

void print_binary32(uint32_t number) {
    for(uint8_t BitMask = 0; BitMask < 32; BitMask++){
        if(number & (1 << (31 - BitMask))){
            LouKeDebuggerCommunicationsSendCharecter('1');
            LouKeOsDosPrintCharecter('1');
        }else{
            LouKeDebuggerCommunicationsSendCharecter('0');
            LouKeOsDosPrintCharecter('0');
        }
    }
}

void print_binary16(uint16_t number) {
    for(uint8_t BitMask = 0; BitMask < 16; BitMask++){
        if(number & (1 << (15 - BitMask))){
            LouKeDebuggerCommunicationsSendCharecter('1');
            LouKeOsDosPrintCharecter('1');
        }else{
            LouKeDebuggerCommunicationsSendCharecter('0');
            LouKeOsDosPrintCharecter('0');
        }
    }
}

void print_binary8(uint8_t number) {
    for(uint8_t BitMask = 0; BitMask < 8; BitMask++){
        if(number & (1 << (7 - BitMask))){
            LouKeDebuggerCommunicationsSendCharecter('1');
            LouKeOsDosPrintCharecter('1');
        }else{
            LouKeDebuggerCommunicationsSendCharecter('0');
            LouKeOsDosPrintCharecter('0');
        }
    }
}

__stdcall
int LouPrint_s(char* format, va_list args){

    char PrintString[21] = {0};
    while (*format) {
        if (*format == '%') {
            format++; // Move past '%'
            switch (*format) {
                case 'd': {
                    int64_t num = va_arg(args, int64_t);
                    intToString((uint64_t)num, PrintString);
                    char* p = PrintString;
                    while (*p != '\0') {
                        LouKeDebuggerCommunicationsSendCharecter(*p);
                        LouKeOsDosPrintCharecter(*p);
                        p++;
                    }
                    break;
                }
                case 's': {
                    if(format[1] == 'd'){
                        format++;
                        int64_t num = va_arg(args, int64_t);
                        sintToString((uint64_t)num, PrintString);
                        char* p = PrintString;
                        while (*p != '\0') {
                            LouKeDebuggerCommunicationsSendCharecter(*p);
                            LouKeOsDosPrintCharecter(*p);
                            p++;
                        }
                    }else{
                        char* text = va_arg(args, char*);
                        while (*text != '\0') {
                            LouKeDebuggerCommunicationsSendCharecter(*text);
                            LouKeOsDosPrintCharecter(*text);
                            text++;
                        }
                    }
                    break;
                }
                case 'c': {
                    char c = va_arg(args, int);
                    LouKeDebuggerCommunicationsSendCharecter(c);
                    LouKeOsDosPrintCharecter(c);
                    break;
                }
                case 'h': {                 
                    int64_t num = va_arg(args, uint64_t);                    
                    uintToHexString((uint64_t)num, PrintString);
                    char* p = PrintString;
                    while (*p  != '\0') {
                        LouKeDebuggerCommunicationsSendCharecter(*p);
                        LouKeOsDosPrintCharecter(*p);
                        p++;
                    }
                    break;
                }
                case 'b': {
                    format++;
                    switch (*format) {
                        case 'l': {
                            uint64_t num = va_arg(args, int64_t);
                            print_binary64(num);
                            break;
                        }
                        case 'i': {
                            uint64_t num = va_arg(args, int64_t);
                            print_binary32((uint32_t)num);
                            break;
                        }
                        case 's': {
                            uint64_t num = va_arg(args, int64_t);
                            print_binary16((uint16_t)num);
                            break;
                        }
                        case 'c': {
                            uint64_t num = va_arg(args, int64_t);
                            print_binary8((uint8_t)num);
                            break;
                        }
                        default: {
                            format--;
                            break;
                        }
                    }
                    break;
                }
                case 'f': {
                    format++;
                    switch (*format) {
                        case 'l': {
                            long double num = va_arg(args, long double);
                            char str[21];
                            long_double_to_string(str, num);
                            char* p = str;
                            while (*p  != '\0') {
                                LouKeDebuggerCommunicationsSendCharecter(*p);
                                LouKeOsDosPrintCharecter(*p);
                                p++;
                            }
                            break;
                        }
                        case 'd': {
                            double num = va_arg(args, double);
                            char str[21];
                            double_to_string(str, num);
                            char* p = str;
                            while (*p  != '\0') {
                                LouKeDebuggerCommunicationsSendCharecter(*p);
                                LouKeOsDosPrintCharecter(*p);
                                p++;
                            }
                            break;
                        }
                        default: {
                            format--;
                            float num = va_arg(args, double);
                            char str[21];
                            float_to_string(str, num);
                            char* p = str;
                            while (*p  != '\0') {
                                LouKeDebuggerCommunicationsSendCharecter(*p);
                                LouKeOsDosPrintCharecter(*p);
                                p++;
                            }
                            break;
                        }
                    }
                    break;
                }
                default: {
                    LouKeDebuggerCommunicationsSendCharecter('%');
                    LouKeDebuggerCommunicationsSendCharecter(*format);
                    LouKeOsDosPrintCharecter('%');
                    LouKeOsDosPrintCharecter(*format);
                    break;
                }
            }
            format++; // Move to the next character in the format string
        } else {    
            LouKeDebuggerCommunicationsSendCharecter(*format);
            LouKeOsDosPrintCharecter(*format);
            format++;
        }
    }
    LouKeOsDosUpdateMapping();
    return 0;
}


int _LouPrint(char* format, ...){
    int result = -1;
    va_list args;
    va_start(args, format);
    result = LouPrint_s(format, args);
    va_end(args);
    return result;
}

bool UsingSmp = false;

INTEGER 
GetCurrentCpuTrackMember();

int LouPrint(char* format, ...) {
    LouKIRQL OldLevel;

    LouKeAcquireSpinLock(&PrintLock ,&OldLevel);
    int result = 0;
    if(UsingSmp){
        _LouPrint("CPU:%d : ", (UINT64)GetCurrentCpuTrackMember());
    }
    va_list args;
    va_start(args, format);
    result = LouPrint_s(format, args);
    va_end(args);
    LouKeReleaseSpinLock(&PrintLock ,&OldLevel);
    return result;
}


void LouKeInitializeSmpLouPrint(){
    UsingSmp = true;
    LouKeMemoryBarrier();
}