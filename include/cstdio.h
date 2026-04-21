#ifndef _STDIO_H
#define _STDIO_H

#include <cstdint.h>
#include <Modulation.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* FILE;


typedef struct _IO_MAP_OBJECT{ //reading and writing for this structure is in Ldm/miniport.h
    union{
        PVOID   MmIoAddress;
        PVOID   SharedAddress;
    };
    BOOL        Mmio;
}IO_MAP_OBJECT, * PIO_MAP_OBJECT;

#define IO_MAP_OBJECT_INITIALIZE_SYSTEM_ADDRESS(IoAddr) { \
    .SharedAddress = IoAddr, \
    .Mmio = false, \
}

#define IO_MAP_OBJECT_INITIALIZE_MMIO_ADDRESS(IoAddr) { \
    .MmIoAddress = IoAddr, \
    .Mmio = true, \
}

static inline void LouKeIoMapObjSetSystemAddress(PIO_MAP_OBJECT IoMapObject, PVOID Vaddress){
    IoMapObject->SharedAddress = Vaddress;
    IoMapObject->Mmio = false;
}

static inline void LouKeIoMapObjSetMmioAddress(PIO_MAP_OBJECT IoMapObject, PVOID Vaddress){
    IoMapObject->MmIoAddress = Vaddress;
    IoMapObject->Mmio = true;
}

static inline BOOLEAN LouKeIoMapObjIsEqual(
    PIO_MAP_OBJECT Obj1,
    PIO_MAP_OBJECT Obj2
){
    if(Obj1->Mmio != Obj2->Mmio){
        return false;
    }
    if(Obj1->Mmio){
        return (Obj1->MmIoAddress == Obj2->MmIoAddress);
    }
    return (Obj1->SharedAddress == Obj2->SharedAddress);
}

static inline BOOLEAN LouKeIoMapObjIsNull(
    PIO_MAP_OBJECT Object
){
    if(Object->Mmio){
        return !Object->MmIoAddress;
    }
    return !Object->SharedAddress;
}

static inline BOOLEAN LouKeIoMapObjIsSet(
    PIO_MAP_OBJECT Object
){
    return !LouKeIoMapObjIsNull(Object);
}

static inline void LouKeIoMapObjIncrement(
    PIO_MAP_OBJECT  Object,
    SIZE            Incrementor
){
    if(Object->Mmio){
        Object->MmIoAddress = (PVOID)((UINTPTR)Object->MmIoAddress + Incrementor);
    }else{
        Object->SharedAddress = (PVOID)((UINTPTR)Object->SharedAddress + Incrementor);
    }
}

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