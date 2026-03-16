#ifndef _C_STD_INTEGERS_H
#define _C_STD_INTEGERS_H
#ifdef __cplusplus
extern "C" {
#include <cstddef>
typedef bool                BOOL;
#else
#include <stdbool.h>
typedef bool                BOOL;
typedef unsigned short      wchar_t;     
#endif

typedef unsigned char       uint8_t,    UCHAR;
typedef unsigned short      uint16_t,   USHORT;
typedef unsigned int        uint32_t,   UINT;
typedef unsigned long       ULONG, * PULONG, ULONG32, * PULONG32;
typedef unsigned long long  uint64_t,   ULONGLONG;

typedef char                int8_t;
typedef short               int16_t;
typedef int                 int32_t;
typedef long                LONG;
typedef long long           int64_t;

typedef uint8_t             UINT8, BYTE;
typedef uint16_t            UINT16, WORD;
typedef unsigned int        UINT;
typedef char                CHAR, INT8;
typedef wchar_t             WCHAR, * PWCHAR, * LPWSTR;
typedef wchar_t             WCHAR, * LPWSTR;
typedef short               INT16; 
typedef int                 INT32; 
typedef long long           INT64; 

typedef unsigned long long  UINT64, ULONGLONG, * PULONGLONG, QWORD, DWORD64, * PDWORD64;
typedef long long           LONGLONG, * PLONGLONG;
typedef void*               PVOID;

typedef int32_t  INTEGER, INT32, LONG32, LOUSTRSAFEDDI, INT;
typedef uint32_t DWORD32, UINT32, DWORD, UINT, 
    * PDWORD32, * PUINT32, * PDWORD, * PUINT;

typedef unsigned long *DWORD_PTR;
typedef int32_t* HALF_PTR;
typedef unsigned int* UINT_PTR;
typedef long* LONG_PTR;
typedef int64_t* POINTER_64; // 32 in 32 bit
typedef int32_t* POINTER_32;

#define VOID void

#define PACKED __attribute__((packed))

#ifdef __x86_64__
typedef uint64_t    size_t;
typedef uint64_t    uintptr_t;
typedef int64_t     SSIZE_T;
#endif

#ifdef __i386__
typedef uint32_t    size_t;
typedef uint32_t    uintptr_t;
typedef int32_t     SSIZE_T;
#endif

typedef size_t      SIZE, SIZE_T, * PSIZE_T; 
typedef uintptr_t   UINTPTR;

typedef struct _uint48_t{
    uint32_t    LowDWord;
    uint16_t    HighWord;
}uint48_t;

typedef __int128 int128_t, INT128, * PINT128;

typedef struct _INT_512{
    __int128 low;  // Lower 128 bits
    __int128 high; // Higher 128 bits
} int512_t, INT_512, * PINT_512;


#define GetStructureSize(p, member, count) \
    ((size_t)((uintptr_t)(&((p)->member[count])) - (uintptr_t)(p)))


#define UINT64_MAX  0xFFFFFFFFFFFFFFFF
#define UINT32_MAX  0xFFFFFFFF
#define UINT16_MAX  0xFFFF
#define UINT8_MAX   0xFF

#define INT64_MAX   0x7FFFFFFFFFFFFFFF
#define INT32_MAX   0x7FFFFFFF
#define INT16_MAX   0x7FFF
#define INT8_MAX    0x7F

#define INT64_MIN   -0x7FFFFFFFFFFFFFFF
#define INT32_MIN   -0x7FFFFFFF
#define INT16_MIN   -0x7FFF
#define INT8_MIN    -0x7F

typedef void* PVOID, * LPVOID;

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))


typedef union _LARGE_INTEGER {
    struct {
        DWORD    LowPart;
        LONG     HighPart;
    } u;
    struct {
        DWORD    LowPart;
        LONG     HighPart;
    } DUMMYSTRUCTNAME;
    LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;


#ifdef __cplusplus
}
#endif
#endif