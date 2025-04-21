#include <LouAPI.h>

int isprint(int c) {
    return (c >= 32 && c <= 126);  // Printable ASCII range
}

int isxdigit(int c) {
    return ((c >= '0' && c <= '9') ||
            (c >= 'a' && c <= 'f') ||
            (c >= 'A' && c <= 'F'));
}

int isdigit(int c) {
    return (c >= '0' && c <= '9');
}

int isspace(int c) {
    return (c == ' '  || c == '\f' || c == '\n' ||
            c == '\r' || c == '\t' || c == '\v');
}
