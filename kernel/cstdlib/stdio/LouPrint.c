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

void VgaPutCharecterRgb(char Charecter, PWINDHANDLE Handle, uint8_t r, uint8_t g, uint8_t b);
bool LouUpdateTextWindow(PWINDHANDLE WindowHandle,TEXT_WINDOW_EVENT Update);

int _vsnprintf(char *buffer, size_t buffer_size, const char *format, ...);
static PWINDHANDLE DebugWindow = 0x00; 

#define INCREASE_Y 16+1
#define INCREASE_X 16+1

static bool DRSD_EGA_OVERIDE = false;

void DRSD_OVERIDE_EGA(){
    DRSD_EGA_OVERIDE = true;
}

void DRSD_EGA_RELEASE(){
    DRSD_EGA_OVERIDE = false;
}

bool AttatchWindowToKrnlDebug(
    PWINDHANDLE WindowToAtttch
){

    if(DebugWindow != 0x00){
        return false;
    }
    DebugWindow = WindowToAtttch;
    //LouPrint("Lousine Kernel Debugger Succesfully Attatched To Window Handle(%h)\n", WindowToAtttch);
    if(DebugWindow == 0x00){
        return false;
    }

    DebugWindow->ForgroundColor.r = 0;
    DebugWindow->ForgroundColor.g = 0;
    DebugWindow->ForgroundColor.b = 0;

    LouUpdateWindow(DebugWindow->CurrentX, DebugWindow->CurrentY,DebugWindow->CurrentWidth,DebugWindow->CurrentHeight, DebugWindow);
    return true;
}

bool DetatchWindowToKrnlDebug(PWINDHANDLE WindowSecurityCheck){
    if(WindowSecurityCheck != DebugWindow){
        LouPrint("ERROR COULD NOT DETATCH :: ACCESS DENIED TO WINDOW HANDLE:%h", WindowSecurityCheck);
        return false;
    }
    DebugWindow = 0x00;
    return true;   
}

#ifdef __x86_64__
void print_binary64(uint64_t number);
void print_binary32(uint32_t number);
void print_binary16(uint16_t number);
void print_binary8(uint8_t number);
void intToString(uint64_t num, char* str);
//void uintToLittleEndianHexString(uint64_t number, char* hexString);
void uintToHexString(uint64_t number, char* hexString);

static spinlock_t PrintLock; 
static spinlock_t PrintPanicLock; 

int LouPrintEGA(string Str, va_list Args);

void print_binary64(uint64_t number) {
    for(uint8_t BitMask = 0; BitMask < 64; BitMask++){
        if(number & (1 << (63 - BitMask))){
            VgaPutCharecterRgb('1', DebugWindow, 0, 255, 0);
        }else{
            VgaPutCharecterRgb('0', DebugWindow, 0, 255, 0);
        }
    }
}

void print_binary32(uint32_t number) {
    for(uint8_t BitMask = 0; BitMask < 32; BitMask++){
        if(number & (1 << (31 - BitMask))){
            VgaPutCharecterRgb('1', DebugWindow, 0, 255, 0);
        }else{
            VgaPutCharecterRgb('0', DebugWindow, 0, 255, 0);
        }
    }
}

void print_binary16(uint16_t number) {
    for(uint8_t BitMask = 0; BitMask < 16; BitMask++){
        if(number & (1 << (15 - BitMask))){
            VgaPutCharecterRgb('1', DebugWindow, 0, 255, 0);
        }else{
            VgaPutCharecterRgb('0', DebugWindow, 0, 255, 0);
        }
    }
}


void print_binary8(uint8_t number) {
    for(uint8_t BitMask = 0; BitMask < 8; BitMask++){
        if(number & (1 << (7 - BitMask))){
            VgaPutCharecterRgb('1', DebugWindow, 0, 255, 0);
        }else{
            VgaPutCharecterRgb('0', DebugWindow, 0, 255, 0);
        }
    }
}


__stdcall
int LouPrint_s(char* format, va_list args){
    
    if(DRSD_EGA_OVERIDE){
        return LouPrintEGA(format, args);
    }
    if(DebugWindow != 0x00){
    LouKIRQL OldLevel;
    LouKeAcquireSpinLock(&PrintLock ,&OldLevel);
    while (*format) {
        if (*format == '%') {
            format++; // Move past '%'
            switch (*format) {
                case 'd': {
                    int64_t num = va_arg(args, int64_t);
                    char* str = (char*)LouMalloc(21);
                    intToString((uint64_t)num, str);
                    char* p = str;
                    while (*p != '\0') {
                        VgaPutCharecterRgb(*p++, DebugWindow, 0, 255, 0);
                    }
                    LouFree((RAMADD)str);
                    break;
                }
                case 's': {
                    char* text = va_arg(args, char*);
                    while (*text != '\0') {
                        VgaPutCharecterRgb(*text++, DebugWindow, 0, 255, 0);
                    }
                    break;
                }
                case 'c': {
                    char c = va_arg(args, int);
                    VgaPutCharecterRgb(c, DebugWindow, 0, 255, 0);
                    break;
                }
                case 'h': {
                    int64_t num = va_arg(args, uint64_t);
                    char* hexString = (char*)LouMalloc(21);
                    uintToHexString((uint64_t)num, hexString);
                    char* p = hexString;
                    while (*p  != '\0') {
                        VgaPutCharecterRgb(*p++, DebugWindow, 0, 255, 0);
                    }
                    LouFree((RAMADD)hexString);
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
                            char* str = (char*)LouMalloc(21);
                            long_double_to_string(str, num);
                            char* p = str;
                            while (*p  != '\0') {
                                VgaPutCharecterRgb(*p++, DebugWindow, 0, 255, 0);
                            }
                            LouFree((RAMADD)str);
                            break;
                        }
                        case 'd': {
                            double num = va_arg(args, double);
                            char str[21];
                            double_to_string(str, num);
                            char* p = str;
                            while (*p  != '\0') {
                                VgaPutCharecterRgb(*p++, DebugWindow, 0, 255, 0);
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
                                VgaPutCharecterRgb(*p++, DebugWindow, 0, 255, 0);
                            }
                            break;
                        }
                    }
                    break;
                }
                default: {
                    VgaPutCharecterRgb('%', DebugWindow, 0, 255, 0);
                    VgaPutCharecterRgb(*format, DebugWindow, 0, 255, 0);
                    break;
                }
            }
            format++; // Move to the next character in the format string
        } else {
            VgaPutCharecterRgb(*format++, DebugWindow, 0, 255, 0);
        }
    }
    LouKeReleaseSpinLock(&PrintLock ,&OldLevel);
    }

    return 0;
}

int LouPrint(char* format, ...) {
    int result = -1;
    va_list args;
    va_start(args, format);
    result = LouPrint_s(format, args);
    va_end(args);
    return result;
}
int LouPanicEGA(char* format, va_list args);

int LouPrintPanic(char* format, ...) {
    LouKIRQL OldLevel;
    LouKeAcquireSpinLock(&PrintPanicLock ,&OldLevel);

    va_list args;
    va_start(args, format);

    if(DRSD_EGA_OVERIDE){
        LouKeReleaseSpinLock(&PrintPanicLock ,&OldLevel);
        return LouPanicEGA(format, args);
    }
    if(DebugWindow != 0x00){
    while (*format) {
        if (*format == '%') {
            format++; // Move past '%'
            switch (*format) {
                case 'd': {
                    int64_t num = va_arg(args, int64_t);
                    char str[21];
                    intToString((uint64_t)num, str);
                    char* p = str;
                    while (*p != '\0') {
                        VgaPutCharecterRgb(*p++, DebugWindow, 0, 255, 0);
                    }
                    break;
                }
                case 's': {
                    char* text = va_arg(args, char*);
                    while (*text != '\0') {
                        VgaPutCharecterRgb(*text++, DebugWindow, 0, 255, 0);
                    }
                    break;
                }
                case 'c': {
                    char c = va_arg(args, int);
                    VgaPutCharecterRgb(c, DebugWindow, 0, 255, 0);
                    break;
                }
                case 'h': {
                    int64_t num = va_arg(args, uint64_t);
                    char hexString[21];
                    uintToHexString((uint64_t)num, hexString);
                    char* p = hexString;
                    while (*p  != '\0') {
                        VgaPutCharecterRgb(*p++, DebugWindow, 0, 255, 0);
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
                                VgaPutCharecterRgb(*p++, DebugWindow, 0, 255, 0);
                            }
                            break;
                        }
                        case 'd': {
                            double num = va_arg(args, double);
                            char str[21];
                            double_to_string(str, num);
                            char* p = str;
                            while (*p  != '\0') {
                                VgaPutCharecterRgb(*p++, DebugWindow, 0, 255, 0);
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
                                VgaPutCharecterRgb(*p++, DebugWindow, 0, 255, 0);
                            }
                            break;
                        }
                    }
                    break;
                }
                default: {
                    VgaPutCharecterRgb('%', DebugWindow, 0, 255, 0);
                    VgaPutCharecterRgb(*format, DebugWindow, 0, 255, 0);
                    break;
                }
            }
            format++; // Move to the next character in the format string
        } else {
            VgaPutCharecterRgb(*format++, DebugWindow, 0, 255, 0);
        }
    }

    }
    va_end(args);
    LouKeReleaseSpinLock(&PrintPanicLock ,&OldLevel);
    return 0;
}

#endif

#ifdef __i386__
void intToString(uint32_t num, char* str);
//void uintToLittleEndianHexString(uint32_t number, char* hexString);
void uintToHexString(uint32_t number, char* hexString);

 int LouPrint(char* format, ...){

 }
#endif

