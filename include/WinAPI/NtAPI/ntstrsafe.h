#ifndef NTSTRSAFE_H
#define NTSTRSAFE_H

#include <NtAPI.h>

NTSTRSAFEDDI RtlStringCbCatA(
    LOUSTRSAFE_PSTR  pszDest,
        size_t          cbDest,
        LOUSTRSAFE_PCSTR pszSrc
);

NTSTRSAFEDDI RtlStringCbCatExA(
    LOUSTRSAFE_PSTR  pszDest,
                  size_t          cbDest,
        LOUSTRSAFE_PCSTR pszSrc,
       LOUSTRSAFE_PSTR  *ppszDestEnd,
       size_t          *pcbRemaining,
                  DWORD           dwFlags
);


NTSTRSAFEDDI RtlStringCbCatExW(
    LOUSTRSAFE_PWSTR  pszDest,
                  size_t           cbDest,
        LOUSTRSAFE_PCWSTR pszSrc,
       LOUSTRSAFE_PWSTR  *ppszDestEnd,
       size_t           *pcbRemaining,
                  DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCbCatNA(
    LOUSTRSAFE_PSTR pszDest,
        size_t         cbDest,
        STRSAFE_PCNZCH pszSrc,
            size_t         cbToAppend
);

NTSTRSAFEDDI RtlStringCbCatNExA(
    LOUSTRSAFE_PSTR pszDest,
                  size_t         cbDest,
        STRSAFE_PCNZCH pszSrc,
                      size_t         cbToAppend,
       LOUSTRSAFE_PSTR *ppszDestEnd,
       size_t         *pcbRemaining,
                  DWORD          dwFlags
);

NTSTRSAFEDDI RtlStringCbCatNExW(
    LOUSTRSAFE_PWSTR pszDest,
                  size_t          cbDest,
        STRSAFE_PCNZWCH pszSrc,
                      size_t          cbToAppend,
       LOUSTRSAFE_PWSTR *ppszDestEnd,
       size_t          *pcbRemaining,
                  DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCbCatNW(
    LOUSTRSAFE_PWSTR pszDest,
        size_t          cbDest,
        STRSAFE_PCNZWCH pszSrc,
            size_t          cbToAppend
);

NTSTRSAFEDDI RtlStringCbCatW(
    LOUSTRSAFE_PWSTR  pszDest,
        size_t           cbDest,
        LOUSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlStringCbCopyA(
   LOUSTRSAFE_PSTR  pszDest,
    size_t          cbDest,
    LOUSTRSAFE_PCSTR pszSrc
);

NTSTRSAFEDDI RtlStringCbCopyExA(
   LOUSTRSAFE_PSTR  pszDest,
              size_t          cbDest,
    LOUSTRSAFE_PCSTR pszSrc,
   LOUSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcbRemaining,
              DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCbCopyExW(
   LOUSTRSAFE_PWSTR  pszDest,
              size_t           cbDest,
    LOUSTRSAFE_PCWSTR pszSrc,
   LOUSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcbRemaining,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCbCopyNA(
   LOUSTRSAFE_PSTR pszDest,
    size_t         cbDest,
    STRSAFE_PCNZCH pszSrc,
        size_t         cbToCopy
);

NTSTRSAFEDDI RtlStringCbCopyNExA(
   LOUSTRSAFE_PSTR pszDest,
              size_t         cbDest,
    STRSAFE_PCNZCH pszSrc,
                  size_t         cbToCopy,
   LOUSTRSAFE_PSTR *ppszDestEnd,
   size_t         *pcbRemaining,
              DWORD          dwFlags
);

NTSTRSAFEDDI RtlStringCbCopyNExW(
   LOUSTRSAFE_PWSTR pszDest,
              size_t          cbDest,
    STRSAFE_PCNZWCH pszSrc,
                  size_t          cbToCopy,
   LOUSTRSAFE_PWSTR *ppszDestEnd,
   size_t          *pcbRemaining,
              DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCbCopyNW(
   LOUSTRSAFE_PWSTR pszDest,
    size_t          cbDest,
    STRSAFE_PCNZWCH pszSrc,
        size_t          cbToCopy
);

NTSTRSAFEDDI RtlStringCbCopyUnicodeString(
   LOUSTRSAFE_PWSTR  pszDest,
    size_t           cbDest,
    PCUNICODE_STRING SourceString
);

NTSTRSAFEDDI RtlStringCbCopyUnicodeStringEx(
             LOUSTRSAFE_PWSTR  pszDest,
              size_t           cbDest,
              PCUNICODE_STRING SourceString,
             LOUSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcbRemaining,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCbCopyW(
   LOUSTRSAFE_PWSTR  pszDest,
    size_t           cbDest,
    LOUSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlStringCbLengthA(
   STRSAFE_PCNZCH psz,
   size_t         cbMax,
       size_t         *pcbLength
);

NTSTRSAFEDDI RtlStringCbLengthW(
   STRSAFE_PCNZWCH psz,
   size_t          cbMax,
       size_t          *pcbLength
);



NTSTRSAFEDDI RtlStringCbPrintfA(
   LOUSTRSAFE_PSTR  pszDest,
    size_t          cbDest,
    LOUSTRSAFE_PCSTR pszFormat,
        ...
);

NTSTRSAFEDDI RtlStringCbPrintfExA(
   LOUSTRSAFE_PSTR  pszDest,
              size_t          cbDest,
   LOUSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcbRemaining,
              DWORD           dwFlags,
    LOUSTRSAFE_PCSTR pszFormat,
                  ...
);

NTSTRSAFEDDI RtlStringCbPrintfExW(
   LOUSTRSAFE_PWSTR  pszDest,
              size_t           cbDest,
   LOUSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcbRemaining,
              DWORD            dwFlags,
    LOUSTRSAFE_PCWSTR pszFormat,
                  ...
);

NTSTRSAFEDDI RtlStringCbPrintfW(
   LOUSTRSAFE_PWSTR  pszDest,
    size_t           cbDest,
    LOUSTRSAFE_PCWSTR pszFormat,
        ...
);

NTSTRSAFEDDI RtlStringCbVPrintfA(
   LOUSTRSAFE_PSTR  pszDest,
    size_t          cbDest,
    LOUSTRSAFE_PCSTR pszFormat,
    va_list         argList
);

NTSTRSAFEDDI RtlStringCbVPrintfExA(
   LOUSTRSAFE_PSTR  pszDest,
              size_t          cbDest,
   LOUSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcbRemaining,
              DWORD           dwFlags,
    LOUSTRSAFE_PCSTR pszFormat,
              va_list         argList
);

NTSTRSAFEDDI RtlStringCbVPrintfExW(
   LOUSTRSAFE_PWSTR  pszDest,
              size_t           cbDest,
   LOUSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcbRemaining,
              DWORD            dwFlags,
    LOUSTRSAFE_PCWSTR pszFormat,
              va_list          argList
);

NTSTRSAFEDDI RtlStringCbVPrintfW(
   LOUSTRSAFE_PWSTR  pszDest,
    size_t           cbDest,
    LOUSTRSAFE_PCWSTR pszFormat,
    va_list          argList
);

NTSTRSAFEDDI RtlStringCchCatA(
    LOUSTRSAFE_PSTR  pszDest,
        size_t          cchDest,
        LOUSTRSAFE_PCSTR pszSrc
);

NTSTRSAFEDDI RtlStringCchCatExA(
    LOUSTRSAFE_PSTR  pszDest,
                  size_t          cchDest,
                  LOUSTRSAFE_PCSTR pszSrc,
       LOUSTRSAFE_PSTR  *ppszDestEnd,
       size_t          *pcchRemaining,
                  DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCchCatExW(
    LOUSTRSAFE_PWSTR  pszDest,
                  size_t           cchDest,
                  LOUSTRSAFE_PCWSTR pszSrc,
       LOUSTRSAFE_PWSTR  *ppszDestEnd,
       size_t           *pcchRemaining,
                  DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCchCatNA(
    LOUSTRSAFE_PSTR pszDest,
        size_t         cchDest,
        STRSAFE_PCNZCH pszSrc,
            size_t         cchToAppend
);

NTSTRSAFEDDI RtlStringCchCatNExA(
    LOUSTRSAFE_PSTR pszDest,
                  size_t         cchDest,
        STRSAFE_PCNZCH pszSrc,
                      size_t         cchToAppend,
       LOUSTRSAFE_PSTR *ppszDestEnd,
       size_t         *pcchRemaining,
                  DWORD          dwFlags
);

NTSTRSAFEDDI RtlStringCchCatNExW(
    LOUSTRSAFE_PWSTR pszDest,
                  size_t          cchDest,
        STRSAFE_PCNZWCH pszSrc,
                      size_t          cchToAppend,
       LOUSTRSAFE_PWSTR *ppszDestEnd,
       size_t          *pcchRemaining,
                  DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCchCatNW(
    LOUSTRSAFE_PWSTR pszDest,
        size_t          cchDest,
        STRSAFE_PCNZWCH pszSrc,
            size_t          cchToAppend
);

NTSTRSAFEDDI RtlStringCchCatW(
    LOUSTRSAFE_PWSTR  pszDest,
        size_t           cchDest,
        LOUSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlStringCchCopyA(
   LOUSTRSAFE_PSTR  pszDest,
    size_t          cchDest,
    LOUSTRSAFE_PCSTR pszSrc
);

NTSTRSAFEDDI RtlStringCchCopyExA(
   LOUSTRSAFE_PSTR  pszDest,
              size_t          cchDest,
    LOUSTRSAFE_PCSTR pszSrc,
   LOUSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcchRemaining,
              DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCchCopyExW(
   LOUSTRSAFE_PWSTR  pszDest,
              size_t           cchDest,
    LOUSTRSAFE_PCWSTR pszSrc,
   LOUSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcchRemaining,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCchCopyNA(
   LOUSTRSAFE_PSTR pszDest,
    size_t         cchDest,
    STRSAFE_PCNZCH pszSrc,
        size_t         cchToCopy
);

NTSTRSAFEDDI RtlStringCchCopyNExA(
   LOUSTRSAFE_PSTR pszDest,
              size_t         cchDest,
    STRSAFE_PCNZCH pszSrc,
                  size_t         cchToCopy,
   LOUSTRSAFE_PSTR *ppszDestEnd,
   size_t         *pcchRemaining,
              DWORD          dwFlags
);

NTSTRSAFEDDI RtlStringCchCopyNExW(
   LOUSTRSAFE_PWSTR pszDest,
              size_t          cchDest,
    STRSAFE_PCNZWCH pszSrc,
                  size_t          cchToCopy,
   LOUSTRSAFE_PWSTR *ppszDestEnd,
   size_t          *pcchRemaining,
              DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCchCopyNW(
   LOUSTRSAFE_PWSTR pszDest,
    size_t          cchDest,
    STRSAFE_PCNZWCH pszSrc,
        size_t          cchToCopy
);

NTSTRSAFEDDI RtlStringCchCopyUnicodeString(
   LOUSTRSAFE_PWSTR  pszDest,
    size_t           cchDest,
    PCUNICODE_STRING SourceString
);

NTSTRSAFEDDI RtlStringCchCopyUnicodeStringEx(
             LOUSTRSAFE_PWSTR  pszDest,
              size_t           cchDest,
              PCUNICODE_STRING SourceString,
             LOUSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcchRemaining,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCchCopyW(
   LOUSTRSAFE_PWSTR  pszDest,
    size_t           cchDest,
    LOUSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlStringCchLengthA(
   STRSAFE_PCNZCH psz,
   size_t         cchMax,
       size_t         *pcchLength
);

NTSTRSAFEDDI RtlStringCchLengthW(
   STRSAFE_PCNZWCH psz,
   size_t          cchMax,
       size_t          *pcchLength
);

NTSTRSAFEDDI RtlStringCchPrintfA(
   LOUSTRSAFE_PSTR  pszDest,
    size_t          cchDest,
    LOUSTRSAFE_PCSTR pszFormat,
        ...
);

NTSTRSAFEDDI RtlStringCchPrintfExA(
   LOUSTRSAFE_PSTR  pszDest,
              size_t          cchDest,
   LOUSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcchRemaining,
              DWORD           dwFlags,
              LOUSTRSAFE_PCSTR pszFormat,
                  ...
);

NTSTRSAFEDDI RtlStringCchPrintfExW(
   LOUSTRSAFE_PWSTR  pszDest,
              size_t           cchDest,
   LOUSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcchRemaining,
              DWORD            dwFlags,
              LOUSTRSAFE_PCWSTR pszFormat,
                  ...
);

NTSTRSAFEDDI RtlStringCchPrintfW(
   LOUSTRSAFE_PWSTR  pszDest,
    size_t           cchDest,
    LOUSTRSAFE_PCWSTR pszFormat,
        ...
);

NTSTRSAFEDDI RtlStringCchVPrintfA(
   LOUSTRSAFE_PSTR  pszDest,
    size_t          cchDest,
    LOUSTRSAFE_PCSTR pszFormat,
    va_list         argList
);

NTSTRSAFEDDI RtlStringCchVPrintfExA(
             LOUSTRSAFE_PSTR  pszDest,
              size_t          cchDest,
   LOUSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcchRemaining,
              DWORD           dwFlags,
    LOUSTRSAFE_PCSTR pszFormat,
              va_list         argList
);

NTSTRSAFEDDI RtlStringCchVPrintfExW(
             LOUSTRSAFE_PWSTR  pszDest,
              size_t           cchDest,
   LOUSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcchRemaining,
              DWORD            dwFlags,
    LOUSTRSAFE_PCWSTR pszFormat,
              va_list          argList
);

NTSTRSAFEDDI RtlStringCchVPrintfW(
   LOUSTRSAFE_PWSTR  pszDest,
    size_t           cchDest,
    LOUSTRSAFE_PCWSTR pszFormat,
    va_list          argList
);

NTSTRSAFEDDI RtlUnalignedStringCbLengthW(
              STRSAFE_PCUNZWCH psz,
              size_t           cbMax,
   size_t           *pcbLength
);


NTSTRSAFEDDI RtlUnalignedStringCchLengthW(
              STRSAFE_PCUNZWCH psz,
              size_t           cchMax,
   size_t           *pcchLength
);

NTSTRSAFEDDI RtlUnicodeStringCat(
    PUNICODE_STRING  DestinationString,
        PCUNICODE_STRING SourceString
);

NTSTRSAFEDDI RtlUnicodeStringCatEx(
          PUNICODE_STRING  DestinationString,
              PCUNICODE_STRING SourceString,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);


NTSTRSAFEDDI RtlUnicodeStringCatString(
    PUNICODE_STRING  DestinationString,
        LOUSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlUnicodeStringCatStringEx(
          PUNICODE_STRING  DestinationString,
              LOUSTRSAFE_PCWSTR pszSrc,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);


NTSTRSAFEDDI RtlUnicodeStringCbCatN(
    PUNICODE_STRING  DestinationString,
        PCUNICODE_STRING SourceString,
        size_t           cbToAppend
);


NTSTRSAFEDDI RtlUnicodeStringCbCatNEx(
          PUNICODE_STRING  DestinationString,
              PCUNICODE_STRING SourceString,
              size_t           cbToAppend,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);


NTSTRSAFEDDI RtlUnicodeStringCbCatStringN(
    PUNICODE_STRING  DestinationString,
        LOUSTRSAFE_PCWSTR pszSrc,
        size_t           cbToAppend
);


NTSTRSAFEDDI RtlUnicodeStringCbCatStringNEx(
          PUNICODE_STRING  DestinationString,
              LOUSTRSAFE_PCWSTR pszSrc,
              size_t           cbToAppend,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);


NTSTRSAFEDDI RtlUnicodeStringCbCopyN(
   PUNICODE_STRING  DestinationString,
    PCUNICODE_STRING SourceString,
    size_t           cbToCopy
);

NTSTRSAFEDDI RtlUnicodeStringCbCopyNEx(
             PUNICODE_STRING  DestinationString,
              PCUNICODE_STRING SourceString,
              size_t           cbToCopy,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlUnicodeStringCbCopyStringN(
   PUNICODE_STRING  DestinationString,
    LOUSTRSAFE_PCWSTR pszSrc,
    size_t           cbToCopy
);

NTSTRSAFEDDI RtlUnicodeStringCbCopyStringNEx(
             PUNICODE_STRING  DestinationString,
              LOUSTRSAFE_PCWSTR pszSrc,
              size_t           cbToCopy,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlUnicodeStringCchCatN(
    PUNICODE_STRING  DestinationString,
        PCUNICODE_STRING SourceString,
        size_t           cchToAppend
);

NTSTRSAFEDDI RtlUnicodeStringCchCatNEx(
          PUNICODE_STRING  DestinationString,
              PCUNICODE_STRING SourceString,
              size_t           cchToAppend,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlUnicodeStringCchCatStringN(
    PUNICODE_STRING  DestinationString,
        LOUSTRSAFE_PCWSTR pszSrc,
        size_t           cchToAppend
);


NTSTRSAFEDDI RtlUnicodeStringCchCatStringNEx(
          PUNICODE_STRING  DestinationString,
              LOUSTRSAFE_PCWSTR pszSrc,
              size_t           cchToAppend,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);


NTSTRSAFEDDI RtlUnicodeStringCchCopyN(
   PUNICODE_STRING  DestinationString,
    PCUNICODE_STRING SourceString,
    size_t           cchToCopy
);


NTSTRSAFEDDI RtlUnicodeStringCchCopyNEx(
             PUNICODE_STRING  DestinationString,
              PCUNICODE_STRING SourceString,
              size_t           cchToCopy,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);


NTSTRSAFEDDI RtlUnicodeStringCchCopyStringN(
   PUNICODE_STRING  DestinationString,
    LOUSTRSAFE_PCWSTR pszSrc,
    size_t           cchToCopy
);


NTSTRSAFEDDI RtlUnicodeStringCchCopyStringNEx(
             PUNICODE_STRING  DestinationString,
              LOUSTRSAFE_PCWSTR pszSrc,
              size_t           cchToCopy,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlUnicodeStringCopy(
   PUNICODE_STRING  DestinationString,
    PCUNICODE_STRING SourceString
);

NTSTRSAFEDDI RtlUnicodeStringCopyEx(
             PUNICODE_STRING  DestinationString,
              PCUNICODE_STRING SourceString,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlUnicodeStringCopyString(
   PUNICODE_STRING  DestinationString,
    LOUSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlUnicodeStringCopyStringEx(
             PUNICODE_STRING  DestinationString,
              LOUSTRSAFE_PCWSTR pszSrc,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);


NTSTRSAFEDDI RtlUnicodeStringInit(
            PUNICODE_STRING  DestinationString,
   LOUSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlUnicodeStringInitEx(
            PUNICODE_STRING  DestinationString,
   LOUSTRSAFE_PCWSTR pszSrc,
             DWORD            dwFlags
);

NTSTRSAFEDDI RtlUnicodeStringPrintf(
   PUNICODE_STRING  DestinationString,
    LOUSTRSAFE_PCWSTR pszFormat,
        ...
);

NTSTRSAFEDDI RtlUnicodeStringPrintfEx(
             PUNICODE_STRING  DestinationString,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags,
              LOUSTRSAFE_PCWSTR pszFormat,
                  ...
);

NTSTRSAFEDDI RtlUnicodeStringValidate(
   PCUNICODE_STRING SourceString
);

NTSTRSAFEDDI RtlUnicodeStringValidateEx(
   PCUNICODE_STRING SourceString,
   DWORD            dwFlags
);

NTSTRSAFEDDI RtlUnicodeStringVPrintf(
   PUNICODE_STRING  DestinationString,
    LOUSTRSAFE_PCWSTR pszFormat,
    va_list          argList
);

NTSTRSAFEDDI RtlUnicodeStringVPrintfEx(
             PUNICODE_STRING  DestinationString,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags,
              LOUSTRSAFE_PCWSTR pszFormat,
              va_list          argList
);



#endif