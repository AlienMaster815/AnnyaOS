//Copyright (2026) GPL-2 Tyler Grenier
#ifndef _CSTDINT_H
#define _CSTDINT_H

typedef char        CHAR,     BYTE,  INT8,  int8_t,  *PCHAR,    *PBYTE,     *PINT8;
typedef short       SHORT,    WORD,  INT16, int16_t, *PSHORT,   *PWORD,     *PINT16;
typedef int         INTEGER,  DWORD, INT32, int32_t, *PINTEGER, *PDWORD,    *PINT32, INT,    *PINT;

//this file assumes System V ABI AKA 32 bit long and 64 bit long long so long is long long for Msv ABI Compatibility

typedef long long   LONGLONG, LONG,  QWORD, INT64,    int64_t,  *PLONGLONG, *PLONG, *PQWORD, *PINT64;


typedef unsigned char        UCHAR,     UBYTE,  UINT8,  uint8_t,  *PUCHAR,    *PUBYTE,     *PUINT8;
typedef unsigned short       USHORT,    UWORD,  UINT16, uint16_t, *PUSHORT,   *PUWORD,     *PUINT16;
typedef unsigned int         UINTEGER,  UDWORD, UINT32, uint32_t, *PUINTEGER, *PUDWORD,    *PUINT32, UINT,    *PUINT;

//this file assumes System V ABI AKA 32 bit long and 64 bit long long so long is long long for Msv ABI Compatibility

typedef unsigned long long   ULONGLONG, ULONG,  UQWORD, UINT64,    uint64_t,  *PULONGLONG, *PULONG, *PUQWORD, *PUINT64, SIZE, size_t, uintptr_t, UINTPTR;


typedef const char        CCHAR,     CBYTE,  CINT8,  cint8_t,  *PCCHAR,    *PCBYTE,     *PCINT8;
typedef const short       CSHORT,    CWORD,  CINT16, cint16_t, *PCSHORT,   *PCWORD,     *PCINT16;
typedef const int         CINTEGER,  CDWORD, CINT32, cint32_t, *PCINTEGER, *PCDWORD,    *PCINT32, CINT,    *PCINT;

//this file assumes System V ABI AKA 32 bit long and 64 bit long long so long is long long for Msv ABI Compatibility

typedef const long long   CLONGLONG, CLONG,  CQWORD, CINT64,    cint64_t,  *PCLONGLONG, *PCLONG, *PCQWORD, *PCINT64;

typedef const unsigned char        CUCHAR,     CUBYTE,  CUINT8,  cuint8_t,  *PCUCHAR,    *PCUBYTE,     *PCUINT8;
typedef const unsigned short       CUSHORT,    CUWORD,  CUINT16, cuint16_t, *PCUSHORT,   *PCUWORD,     *PCUINT16;
typedef const unsigned int         CUINTEGER,  CUDWORD, CUINT32, cuint32_t, *PCUINTEGER, *PCUDWORD,    *PCUINT32, CUINT,    *PCUINT;

//this file assumes System V ABI AKA 32 bit long and 64 bit long long so long is long long for Msv ABI Compatibility

typedef const unsigned long long   CULONGLONG, CULONG,  CUQWORD, CUINT64,    cuint64_t,  *PCULONGLONG, *PCULONG, *PCUQWORD, *PCUINT64, CSIZE, csize_t;

typedef void* PVOID;
typedef const void* PCVOID;

typedef char bool;

#define false 0
#define true  1
#define FALSE false
#define TRUE  

#endif
