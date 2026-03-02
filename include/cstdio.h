#ifndef _STDIO_H
#define _STDIO_H

#include <cstdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* FILE;

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

uint8_t inb(uint64_t port);
void outb(uint64_t port, uint8_t data);
uint16_t inw(uint64_t port);
void outw(uint64_t port, uint16_t data);
uint32_t inl(uint64_t port);
void outl(uint64_t port, uint32_t  data);
void outbSlow(uint64_t port,uint8_t data);


#endif
#ifdef __cplusplus
}
#endif
#endif