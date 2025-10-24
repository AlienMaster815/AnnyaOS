typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#ifndef BOOL_T
#define BOOL_T
#include <stdbool.h>
typedef bool BOOL;
#endif 

typedef uint8_t     UINT8;//,  BYTE;
typedef uint16_t    UINT16, WORD;
typedef uint32_t    UINT32, DWORD, INTEGER;
typedef unsigned int       ULONG;
typedef unsigned int UINT;
typedef char        CHAR, INT8;
#ifndef _USER_MODE_CODE_ 
#ifndef __cplusplus
typedef uint16_t wchar_t;     
#endif
typedef wchar_t WCHAR, * PWCHAR, * LPWSTR;
#endif
typedef wchar_t     WCHAR, * LPWSTR;
typedef short       INT16; 
typedef int         INT32; 
typedef long long   INT64; 

typedef unsigned long long UINT64, ULONGLONG, * PULONGLONG, QWORD;
typedef long long LONGLONG, * PLONGLONG;

typedef UINT64 UINTPTR;

typedef void* PVOID;

#define PACKED __attribute__((packed))

#ifndef _SIZE_T_
#define _SIZE_T_
#define SIZE_T size_t
#endif
