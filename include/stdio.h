#ifndef _STDIO_H
#define _STDIO_H

#include <cstdint.h>

#ifdef __cplusplus
extern "C" {
#endif
#ifndef _USER_MODE_CODE_

int LouPrint(char* format, ...);

void 
uintToHexString(
    uint64_t number, 
    char* hexString
);

void 
LouKePrintLittleEndianBufferDecimal(
    uintptr_t DataPointer,
    uint64_t Offset,
    uint64_t Length
);

void 
LouKePrintLittleEndianBufferHex(
    uintptr_t DataPointer,
    uint64_t Offset,
    uint64_t Length
);

void 
LouKePrintLittleEndianBufferBinary(
    uintptr_t DataPointer,
    uint64_t Offset,
    uint64_t Length
);

void 
LouKePrintLittleEndianBufferString(
    uintptr_t DataPointer,
    uint64_t Offset,
    uint64_t Length
);

bool 
LouKeIsLittleEndianBufferEqualTo(
    uintptr_t DataPointer,
    uintptr_t CheckBuffer,
    uint64_t Offset,
    uint64_t Length
);

#endif
#ifdef __cplusplus
}
#endif
#endif