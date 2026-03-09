#ifndef _STDIO_H
#define _STDIO_H

#include <cstdint.h>
#include <Modulation.h>

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

KERNEL_EXPORT uint8_t   inb(uint64_t port);
KERNEL_EXPORT void      outb(uint64_t port, uint8_t data);
KERNEL_EXPORT void      insb(uint16_t port, void *buf, unsigned long count);
KERNEL_EXPORT void      outsb(uint16_t port, const void *buf, unsigned long count);

KERNEL_EXPORT uint16_t  inw(uint64_t port);
KERNEL_EXPORT void      outw(uint64_t port, uint16_t data);
KERNEL_EXPORT void      insw(uint16_t port, void *buf, unsigned long count);
KERNEL_EXPORT void      outsw(uint16_t port, const void *buf, unsigned long count);

KERNEL_EXPORT uint32_t  inl(uint64_t port);
KERNEL_EXPORT void      outl(uint64_t port, uint32_t  data);
KERNEL_EXPORT void      insl(uint16_t port, void *buf, unsigned long count);
KERNEL_EXPORT void      outsl(uint16_t port, const void *buf, unsigned long count);

void outbSlow(uint64_t port,uint8_t data);


#endif
#ifdef __cplusplus
}
#endif
#endif