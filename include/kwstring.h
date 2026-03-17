#ifndef _KWSTRING_H
#define _KWSTRING_H
#ifdef __cplusplus
extern "C" {
#endif    

#include <WinAPI/Win32/winternl.h>

#define WINAPI __stdcall

typedef int errno_t;
#define EINVAL      22
#define ERANGE      34
#define STRUNCATE   80

#define _TRUNCATE ((size_t)-1)

#ifndef _USER_MODE_CODE_

KERNEL_EXPORT 
int
_wcsicmp(
    LPCWSTR String1,
    LPCWSTR String2
);

KERNEL_EXPORT 
LPWSTR _wcslwr(
    LPWSTR Str
);

KERNEL_EXPORT 
size_t 
wcslen(LPCWSTR str);

KERNEL_EXPORT 
size_t wcsnlen(const WCHAR *str, size_t len);

KERNEL_EXPORT 
errno_t
_wcslwr_s(
    LPWSTR Str, 
    size_t Length 
);


KERNEL_EXPORT 
int
_wcsnicmp(LPWSTR str1, LPWSTR str2, size_t n);

KERNEL_EXPORT 
LPWSTR 
_wcsupr(
    LPWSTR Str
);


KERNEL_EXPORT 
errno_t 
_wcsupr_s(
    LPWSTR Str, 
    size_t Length
);

 
KERNEL_EXPORT 
LPWSTR
wcscpy(
    LPWSTR Destination,
    LPWSTR Source
);

KERNEL_EXPORT 
errno_t wcscpy_s(
    LPWSTR Destination,
    size_t Length, 
    LPWSTR Source
);

KERNEL_EXPORT 
LPWSTR 
wcscat(
    LPWSTR Destination,
    LPWSTR Source
);


KERNEL_EXPORT 
errno_t
wcscat_s(
    LPWSTR Destination,
    size_t Length,
    LPWSTR Source
);


KERNEL_EXPORT 
LPWSTR 
wcschr(
    LPWSTR Str,
    WCHAR  Token
);

KERNEL_EXPORT 
int
wcscmp(
    LPWSTR Str1,
    LPWSTR Str2
);


KERNEL_EXPORT 
size_t 
wcscspn(
    LPWSTR Str,
    LPWSTR Reject
);

KERNEL_EXPORT 
LPWSTR 
wcsncat(
    LPWSTR Str1,
    LPWSTR Str2,
    size_t Length
);

KERNEL_EXPORT 
errno_t
wcsncat_s(
    LPWSTR Destination, 
    size_t Length, 
    LPWSTR Source, 
    size_t Count
);

KERNEL_EXPORT 
int 
wcsncmp(
    LPWSTR String1,
    LPWSTR String2,
    size_t Length
);


KERNEL_EXPORT 
LPWSTR 
wcsncpy(
    LPWSTR String1,
    LPWSTR String2,
    size_t Length
);


KERNEL_EXPORT 
errno_t
wcsncpy_s(
    LPWSTR Destination,
    size_t Length,
    LPWSTR Source,
    size_t Count
);


KERNEL_EXPORT 
LPWSTR 
wcsrchr(
    LPWSTR Str,
    WCHAR  Token
);


KERNEL_EXPORT 
LPWSTR
wcspbrk(
    LPWSTR Str,
    LPWSTR Accept
);

KERNEL_EXPORT 
size_t
wcsspn(
    LPWSTR Str,
    LPWSTR Accept
);

KERNEL_EXPORT 
LPWSTR 
wcsstr(
    LPWSTR Str,
    LPWSTR Sub
);


KERNEL_EXPORT 
LPWSTR 
wcstok(
    LPWSTR Str,
    LPWSTR Deliminator
);


KERNEL_EXPORT 
LPWSTR 
wcstok_s(
    LPWSTR Str,
    LPWSTR Deliminator,
    LPWSTR* Context
);

KERNEL_EXPORT 
size_t 
wcstombs(
    string Destination,
    LPWSTR Source,
    size_t Length
);


KERNEL_EXPORT 
size_t 
mbstowcs(
    LPWSTR Destination,
    string Source,
    size_t Length
);


KERNEL_EXPORT 
int 
iswctype(
    WCHAR           Wc,
    unsigned short  Type
);


KERNEL_EXPORT 
int 
iswalnum(
    WCHAR Wc
);


KERNEL_EXPORT 
int 
iswalpha(
    WCHAR Wc
);

KERNEL_EXPORT 
int 
iswascii(
    WCHAR Wc
);


KERNEL_EXPORT 
int 
iswdigit(
    WCHAR Wc
);


KERNEL_EXPORT 
int
iswgraph(
   WCHAR Wc
);


KERNEL_EXPORT 
int 
iswlower(
    WCHAR Wc
);


KERNEL_EXPORT 
int 
iswprint(
    WCHAR Wc
);


KERNEL_EXPORT 
int 
iswspace(
    WCHAR Wc
);

 
KERNEL_EXPORT 
int 
iswxdigit(
    WCHAR Wc
);


KERNEL_EXPORT 
long 
wcstol(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
);

KERNEL_EXPORT 
unsigned long 
wcstoul(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
);


KERNEL_EXPORT 
INT64 
wcstoi64(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
);


KERNEL_EXPORT 
UINT64 
wcstoui64(
    LPWSTR  Str,
    LPWSTR* End,
    int     Base
);


KERNEL_EXPORT 
LPWSTR 
_ultow(
    unsigned long   V, 
    LPWSTR          Str,
    int             Radix
);

KERNEL_EXPORT 
LPWSTR 
_ltow(
    long    V,
    LPWSTR  Str,
    int     Radix    
);

KERNEL_EXPORT 
LPWSTR
_itow(
    int     Value,
    LPWSTR  Str,
    int     Radix
);

KERNEL_EXPORT 
LPWSTR 
_ui64tow(
    UINT64  Value,
    LPWSTR  Str,
    int     Radix
);

KERNEL_EXPORT 
LPWSTR 
_i64tow(
    INT64  Value,
    LPWSTR  Str,
    int     Radix
);


KERNEL_EXPORT 
errno_t
_ui64tow_s(
    UINT64  Value,
    LPWSTR  Str, 
    size_t  Length,
    int     Radix
);


KERNEL_EXPORT 
errno_t
_ultow_s(
    unsigned long   Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
);


KERNEL_EXPORT 
errno_t
_i64tow_s(
    INT64   Value,
    LPWSTR  Str, 
    size_t  Length,
    int     Radix
);

KERNEL_EXPORT 
errno_t
_ltow_s(
    long            Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
);


KERNEL_EXPORT 
errno_t
_itow_s(
    int             Value,
    LPWSTR          Str,
    size_t          Length,
    int             Radix
);

KERNEL_EXPORT 
long 
_wtol(
    LPWSTR Str
);

KERNEL_EXPORT 
int 
_wtoi(
    LPWSTR Str
);
 
KERNEL_EXPORT 
UINT64
_wtoi64(
    LPWSTR Str
);


KERNEL_EXPORT 
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

KERNEL_EXPORT 
errno_t
_wmakepath_s(
    LPWSTR Path,
    size_t Length,
    LPWSTR Drive,
    LPWSTR Directory,
    LPWSTR FileName,
    LPWSTR Extention
);



KERNEL_EXPORT 
LPWSTR LouKeCreateCombineWcsStr(
    LPWSTR Str1, 
    LPWSTR Str2
);

KERNEL_EXPORT 
errno_t
_ui64towUppr_s(
    UINT64  Value,
    LPWSTR  Str, 
    size_t  Length,
    int     Radix
);

#ifndef _KERNEL_MODULE_
LPWSTR LouKeForkWcsStr(LPWSTR Str);
LPWSTR LouKeForkWcsStr_s(LPWSTR Str, size_t Len);
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif