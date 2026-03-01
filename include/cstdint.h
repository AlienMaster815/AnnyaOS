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

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef char                int8_t;
typedef short               int16_t;
typedef int                 int32_t;
typedef long long           int64_t;

typedef uint8_t             UINT8;
typedef uint16_t            UINT16, WORD;
typedef uint32_t            UINT32, DWORD, INTEGER;
typedef unsigned int        ULONG;
typedef unsigned int        UINT;
typedef char                CHAR, INT8;
typedef wchar_t             WCHAR, * PWCHAR, * LPWSTR;
typedef wchar_t             WCHAR, * LPWSTR;
typedef short               INT16; 
typedef int                 INT32; 
typedef long long           INT64; 

typedef unsigned long long  UINT64, ULONGLONG, * PULONGLONG, QWORD;
typedef long long           LONGLONG, * PLONGLONG;
typedef void*               PVOID;

#define PACKED __attribute__((packed))

#ifdef __x86_64__
typedef uint64_t    size_t;
typedef uint64_t    uintptr_t;
#endif

#ifdef __i386__
typedef uint32_t    size_t;
typedef uint32_t    uintptr_t;
#endif

typedef size_t      SIZE_T; 
typedef uintptr_t   UINTPTR;

typedef struct _uint48_t{
    uint32_t    LowDWord;
    uint16_t    HighWord;
}uint48_t;


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

typedef void* PVOID;

#ifdef __cplusplus
}
#endif
#endif