#include <stdint.h>
#include <stdbool.h>

//unsigned long strtoul(const char* nptr, char** endptr, int base) {
//    unsigned long result = 0;
//    const char* p = nptr;

    // Skip whitespace
//    while (*p == ' ' || *p == '\t') {
//        p++;
//    }

    // Optional sign
//    bool negative = false;
//    if (*p == '+') {
//        p++;
//    } else if (*p == '-') {
//        negative = true;
//        p++;
//    }

//    // Handle base detection (0x, 0)
//    if ((base == 0 || base == 16) && p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
//        base = 16;
//        p += 2;
//    } else if (base == 0 && *p == '0') {
//        base = 8;
//        p++;
//    } else if (base == 0) {
//        base = 10;
//    }

//    // Convert digits
//    while (1) {
//        char c = *p;
//        int digit;

//        if (c >= '0' && c <= '9')
//            digit = c - '0';
//        else if (c >= 'A' && c <= 'Z')
//            digit = c - 'A' + 10;
//        else if (c >= 'a' && c <= 'z')
//            digit = c - 'a' + 10;
//        else
//           break;/

//        if (digit >= base)
//            break;

//        result = result * base + digit;
//        p++;
//    }

//    if (endptr)
//        *endptr = (char*)p;

//    return negative ? -result : result;
//}

int isprint(int ch) {
    return (ch >= 0x20 && ch <= 0x7E);
}

int isxdigit(int c) {
    return ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'F') ||
            (c >= 'a' && c <= 'f'));
}

int isspace(int c) {
    return (c == ' '  || c == '\t' || c == '\n' ||
            c == '\v' || c == '\f' || c == '\r');
}

int isdigit(int c) {
    return (c >= '0' && c <= '9');
}
