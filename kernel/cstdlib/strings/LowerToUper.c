#include <LouAPI.h>

void LouKeStrLowerToUpper(string Format){
    while (*Format) {
        if (*Format >= 'a' && *Format <= 'z') {
            *Format -= 32;
        }
        Format++;
    }
}