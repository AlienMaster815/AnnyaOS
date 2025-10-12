#ifndef _KWSTRING_H
#define _KWSTRING_H

#ifndef _KERNEL_MODULE_

#ifndef __cplusplus
#include <LouAPI.h>
#else 
#include <LouDDK.h>
extern "C" {
#endif    


#define WINAPI __stdcall

typedef int errno_t;
#define EINVAL      22
#define ERANGE      34
#define STRUNCATE   80

#define _TRUNCATE ((size_t)-1)



int
_wcsicmp(
    LPCWSTR String1,
    LPCWSTR String2
);

LPWSTR _wcslwr(
    LPWSTR Str
);

size_t 
wcslen(LPCWSTR str);

size_t wcsnlen(const WCHAR *str, size_t len);

errno_t
_wcslwr_s(
    LPWSTR Str, 
    size_t Length 
);


int
_wcsnicmp(LPWSTR str1, LPWSTR str2, size_t n);

LPWSTR 
_wcsupr(
    LPWSTR Str
);


errno_t 
_wcsupr_s(
    LPWSTR Str, 
    size_t Length
);

 
LPWSTR
wcscpy(
    LPWSTR Destination,
    LPWSTR Source
);

errno_t wcscpy_s(
    LPWSTR Destination,
    size_t Length, 
    LPWSTR Source
);

LPWSTR 
wcscat(
    LPWSTR Destination,
    LPWSTR Source
);


errno_t
wcscat_s(
    LPWSTR Destination,
    size_t Length,
    LPWSTR Source
);


LPWSTR 
wcschr(
    LPWSTR Str,
    WCHAR  Token
);

int
wcscmp(
    LPWSTR Str1,
    LPWSTR Str2
);


size_t 
wcscspn(
    LPWSTR Str,
    LPWSTR Reject
);

LPWSTR 
wcsncat(
    LPWSTR Str1,
    LPWSTR Str2,
    size_t Length
);

errno_t
wcsncat_s(
    LPWSTR Destination, 
    size_t Length, 
    LPWSTR Source, 
    size_t Count
);

int 
wcsncmp(
    LPWSTR String1,
    LPWSTR String2,
    size_t Length
);


LPWSTR 
wcsncpy(
    LPWSTR String1,
    LPWSTR String2,
    size_t Length
);


errno_t
wcsncpy_s(
    LPWSTR Destination,
    size_t Length,
    LPWSTR Source,
    size_t Count
);


LPWSTR 
wcsrchr(
    LPWSTR Str,
    WCHAR  Token
);


LPWSTR
wcspbrk(
    LPWSTR Str,
    LPWSTR Accept
);

size_t
wcsspn(
    LPWSTR Str,
    LPWSTR Accept
);

LPWSTR 
wcsstr(
    LPWSTR Str,
    LPWSTR Sub
);


LPWSTR 
wcstok(
    LPWSTR Str,
    LPWSTR Deliminator
);


LPWSTR 
wcstok_s(
    LPWSTR Str,
    LPWSTR Deliminator,
    LPWSTR* Context
);

size_t 
wcstombs(
    string Destination,
    LPWSTR Source,
    size_t Length
);


size_t 
mbstowcs(
    LPWSTR Destination,
    string Source,
    size_t Length
);


int 
iswctype(
    WCHAR           Wc,
    unsigned short  Type
);


int 
iswalnum(
    WCHAR Wc
);


int 
iswalpha(
    WCHAR Wc
);

int 
iswascii(
    WCHAR Wc
);


int 
iswdigit(
    WCHAR Wc
);


int
iswgraph(
   WCHAR Wc
);


int 
iswlower(
    WCHAR Wc
);


int 
iswprint(
    WCHAR Wc
);


int 
iswspace(
    WCHAR Wc
);

 
int 
iswxdigit(
    WCHAR Wc
);


long 
wcstol(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
);

unsigned long 
wcstoul(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
);


INT64 
wcstoi64(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
);


UINT64 
wcstoui64(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
);


LPWSTR 
_ultow(
    unsigned long   V, 
    LPWSTR          Str,
    int             Radix
);

LPWSTR 
_ltow(
    long    V,
    LPWSTR  Str,
    int     Radix    
);

LPWSTR
_itow(
    int     Value,
    LPWSTR  Str,
    int     Radix
);

LPWSTR 
_ui64tow(
    UINT64  Value,
    LPWSTR  Str,
    int     Radix
);

LPWSTR 
_i64tow(
    INT64  Value,
    LPWSTR  Str,
    int     Radix
);


errno_t
_ui64tow_s(
    UINT64  Value,
    LPWSTR  Str, 
    size_t  Length,
    int     Radix
);


errno_t
_ultow_s(
    unsigned long   Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
);


errno_t
_i64tow_s(
    INT64   Value,
    LPWSTR  Str, 
    size_t  Length,
    int     Radix
);

errno_t
_ltow_s(
    long            Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
);


errno_t
_itow_s(
    int             Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
);

long 
_wtol(
    LPWSTR Str
);

int 
_wtoi(
    LPWSTR Str
);
 
UINT64
_wtoi64(
    LPWSTR Str
);


errno_t
_wsplitpath_s(
    LPWSTR InPath, 
    LPWSTR Drive,
    size_t SzDrive,
    LPWSTR Directory,
    size_t SzDirectory,
    LPWSTR FileName,
    size_t SzFileName,
    LPWSTR Extention,
    size_t SzExtention
);

errno_t
_wmakepath_s(
    LPWSTR Path,
    size_t Length,
    LPWSTR Drive,
    LPWSTR Directory,
    LPWSTR FileName,
    LPWSTR Extention
);

LPWSTR LouKeForkWcsStr(LPWSTR Str);
LPWSTR LouKeForkWcsStr_s(LPWSTR Str, size_t Len);

#ifdef __cplusplus
}
#endif

#else
//#include <LouDDK.h>


#endif
#endif