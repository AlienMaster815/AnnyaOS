#ifndef _WCS_EXTENTIONS
#define _WCS_EXTENTIONS

typedef const LPWSTR LPCWSTR;
typedef uintptr_t UINTPTR;

size_t
Lou_wcslen(
    LPCWSTR Str  
);

int 
Lou_wcsncmp(
    LPWSTR String1,
    LPWSTR String2,
    size_t Length
);

int
Lou_wcscmp(
    LPWSTR Str1,
    LPWSTR Str2
);

LPWSTR 
Lou_wcsncpy(
    LPWSTR String1,
    LPWSTR String2,
    size_t Length
);

LPWSTR
Lou_wcscpy(
    LPWSTR Destination,
    LPWSTR Source
);

LPWSTR 
Lou_wcschr(
    LPWSTR Str,
    WCHAR  Token
);

LPWSTR
Lou_wcspbrk(
    LPWSTR Str,
    LPWSTR Accept
);

LPWSTR
Lou_wcspbrk_s(
    LPWSTR Str,
    size_t StrLen,
    LPWSTR Accept,
    size_t AcceptLen
);

UINT64
Lou__wtoi64_s(
    LPCWSTR Str,
    size_t  Length
);

LPWSTR LouKeForkWcsStr_s(LPWSTR Str, size_t Len);
LPWSTR LouKeForkWcsStr(LPWSTR Str);

void SanityCheck(LPWSTR Str, size_t Length);

int LouKeCompareLpwstrFromRaw(
    LOU_STRING  Search, 
    LPWSTR      RawStream, 
    size_t      Length
);

LPWSTR LouKeCreateLpwstr(LOU_STRING Str);

LPWSTR 
Lou_wcsstr(
    LPWSTR Str,
    LPWSTR Sub
);

void PrintDocumentBuffer(LPWSTR Str, size_t Length);

int 
Lou_iswspace(
    WCHAR Wc
);

UINT64
Lou__wtoh64(
    LPCWSTR Str
);

UINT64
Lou__wtoh64_s(
    LPCWSTR Str,
    size_t  Length
);

#endif