//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "ntdll.h"

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