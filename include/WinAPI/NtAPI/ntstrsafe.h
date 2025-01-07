#ifndef NTSTRSAFE_H
#define NTSTRSAFE_H

#include <NtAPI.h>

NTSTRSAFEDDI RtlStringCbCatA(
    NTSTRSAFE_PSTR  pszDest,
        size_t          cbDest,
        NTSTRSAFE_PCSTR pszSrc
);

NTSTRSAFEDDI RtlStringCbCatExA(
    NTSTRSAFE_PSTR  pszDest,
                  size_t          cbDest,
        NTSTRSAFE_PCSTR pszSrc,
       NTSTRSAFE_PSTR  *ppszDestEnd,
       size_t          *pcbRemaining,
                  DWORD           dwFlags
);


NTSTRSAFEDDI RtlStringCbCatExW(
    NTSTRSAFE_PWSTR  pszDest,
                  size_t           cbDest,
        NTSTRSAFE_PCWSTR pszSrc,
       NTSTRSAFE_PWSTR  *ppszDestEnd,
       size_t           *pcbRemaining,
                  DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCbCatNA(
    NTSTRSAFE_PSTR pszDest,
        size_t         cbDest,
        STRSAFE_PCNZCH pszSrc,
            size_t         cbToAppend
);

NTSTRSAFEDDI RtlStringCbCatNExA(
    NTSTRSAFE_PSTR pszDest,
                  size_t         cbDest,
        STRSAFE_PCNZCH pszSrc,
                      size_t         cbToAppend,
       NTSTRSAFE_PSTR *ppszDestEnd,
       size_t         *pcbRemaining,
                  DWORD          dwFlags
);

NTSTRSAFEDDI RtlStringCbCatNExW(
    NTSTRSAFE_PWSTR pszDest,
                  size_t          cbDest,
        STRSAFE_PCNZWCH pszSrc,
                      size_t          cbToAppend,
       NTSTRSAFE_PWSTR *ppszDestEnd,
       size_t          *pcbRemaining,
                  DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCbCatNW(
    NTSTRSAFE_PWSTR pszDest,
        size_t          cbDest,
        STRSAFE_PCNZWCH pszSrc,
            size_t          cbToAppend
);

NTSTRSAFEDDI RtlStringCbCatW(
    NTSTRSAFE_PWSTR  pszDest,
        size_t           cbDest,
        NTSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlStringCbCopyA(
   NTSTRSAFE_PSTR  pszDest,
    size_t          cbDest,
    NTSTRSAFE_PCSTR pszSrc
);

NTSTRSAFEDDI RtlStringCbCopyExA(
   NTSTRSAFE_PSTR  pszDest,
              size_t          cbDest,
    NTSTRSAFE_PCSTR pszSrc,
   NTSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcbRemaining,
              DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCbCopyExW(
   NTSTRSAFE_PWSTR  pszDest,
              size_t           cbDest,
    NTSTRSAFE_PCWSTR pszSrc,
   NTSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcbRemaining,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCbCopyNA(
   NTSTRSAFE_PSTR pszDest,
    size_t         cbDest,
    STRSAFE_PCNZCH pszSrc,
        size_t         cbToCopy
);

NTSTRSAFEDDI RtlStringCbCopyNExA(
   NTSTRSAFE_PSTR pszDest,
              size_t         cbDest,
    STRSAFE_PCNZCH pszSrc,
                  size_t         cbToCopy,
   NTSTRSAFE_PSTR *ppszDestEnd,
   size_t         *pcbRemaining,
              DWORD          dwFlags
);

NTSTRSAFEDDI RtlStringCbCopyNExW(
   NTSTRSAFE_PWSTR pszDest,
              size_t          cbDest,
    STRSAFE_PCNZWCH pszSrc,
                  size_t          cbToCopy,
   NTSTRSAFE_PWSTR *ppszDestEnd,
   size_t          *pcbRemaining,
              DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCbCopyNW(
   NTSTRSAFE_PWSTR pszDest,
    size_t          cbDest,
    STRSAFE_PCNZWCH pszSrc,
        size_t          cbToCopy
);

NTSTRSAFEDDI RtlStringCbCopyUnicodeString(
   NTSTRSAFE_PWSTR  pszDest,
    size_t           cbDest,
    PCUNICODE_STRING SourceString
);

NTSTRSAFEDDI RtlStringCbCopyUnicodeStringEx(
             NTSTRSAFE_PWSTR  pszDest,
              size_t           cbDest,
              PCUNICODE_STRING SourceString,
             NTSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcbRemaining,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCbCopyW(
   NTSTRSAFE_PWSTR  pszDest,
    size_t           cbDest,
    NTSTRSAFE_PCWSTR pszSrc
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
   NTSTRSAFE_PSTR  pszDest,
    size_t          cbDest,
    NTSTRSAFE_PCSTR pszFormat,
        ...
);

NTSTRSAFEDDI RtlStringCbPrintfExA(
   NTSTRSAFE_PSTR  pszDest,
              size_t          cbDest,
   NTSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcbRemaining,
              DWORD           dwFlags,
    NTSTRSAFE_PCSTR pszFormat,
                  ...
);

NTSTRSAFEDDI RtlStringCbPrintfExW(
   NTSTRSAFE_PWSTR  pszDest,
              size_t           cbDest,
   NTSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcbRemaining,
              DWORD            dwFlags,
    NTSTRSAFE_PCWSTR pszFormat,
                  ...
);

NTSTRSAFEDDI RtlStringCbPrintfW(
   NTSTRSAFE_PWSTR  pszDest,
    size_t           cbDest,
    NTSTRSAFE_PCWSTR pszFormat,
        ...
);

NTSTRSAFEDDI RtlStringCbVPrintfA(
   NTSTRSAFE_PSTR  pszDest,
    size_t          cbDest,
    NTSTRSAFE_PCSTR pszFormat,
    va_list         argList
);

NTSTRSAFEDDI RtlStringCbVPrintfExA(
   NTSTRSAFE_PSTR  pszDest,
              size_t          cbDest,
   NTSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcbRemaining,
              DWORD           dwFlags,
    NTSTRSAFE_PCSTR pszFormat,
              va_list         argList
);

NTSTRSAFEDDI RtlStringCbVPrintfExW(
   NTSTRSAFE_PWSTR  pszDest,
              size_t           cbDest,
   NTSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcbRemaining,
              DWORD            dwFlags,
    NTSTRSAFE_PCWSTR pszFormat,
              va_list          argList
);

NTSTRSAFEDDI RtlStringCbVPrintfW(
   NTSTRSAFE_PWSTR  pszDest,
    size_t           cbDest,
    NTSTRSAFE_PCWSTR pszFormat,
    va_list          argList
);

NTSTRSAFEDDI RtlStringCchCatA(
    NTSTRSAFE_PSTR  pszDest,
        size_t          cchDest,
        NTSTRSAFE_PCSTR pszSrc
);

NTSTRSAFEDDI RtlStringCchCatExA(
    NTSTRSAFE_PSTR  pszDest,
                  size_t          cchDest,
                  NTSTRSAFE_PCSTR pszSrc,
       NTSTRSAFE_PSTR  *ppszDestEnd,
       size_t          *pcchRemaining,
                  DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCchCatExW(
    NTSTRSAFE_PWSTR  pszDest,
                  size_t           cchDest,
                  NTSTRSAFE_PCWSTR pszSrc,
       NTSTRSAFE_PWSTR  *ppszDestEnd,
       size_t           *pcchRemaining,
                  DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCchCatNA(
    NTSTRSAFE_PSTR pszDest,
        size_t         cchDest,
        STRSAFE_PCNZCH pszSrc,
            size_t         cchToAppend
);

NTSTRSAFEDDI RtlStringCchCatNExA(
    NTSTRSAFE_PSTR pszDest,
                  size_t         cchDest,
        STRSAFE_PCNZCH pszSrc,
                      size_t         cchToAppend,
       NTSTRSAFE_PSTR *ppszDestEnd,
       size_t         *pcchRemaining,
                  DWORD          dwFlags
);

NTSTRSAFEDDI RtlStringCchCatNExW(
    NTSTRSAFE_PWSTR pszDest,
                  size_t          cchDest,
        STRSAFE_PCNZWCH pszSrc,
                      size_t          cchToAppend,
       NTSTRSAFE_PWSTR *ppszDestEnd,
       size_t          *pcchRemaining,
                  DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCchCatNW(
    NTSTRSAFE_PWSTR pszDest,
        size_t          cchDest,
        STRSAFE_PCNZWCH pszSrc,
            size_t          cchToAppend
);

NTSTRSAFEDDI RtlStringCchCatW(
    NTSTRSAFE_PWSTR  pszDest,
        size_t           cchDest,
        NTSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlStringCchCopyA(
   NTSTRSAFE_PSTR  pszDest,
    size_t          cchDest,
    NTSTRSAFE_PCSTR pszSrc
);

NTSTRSAFEDDI RtlStringCchCopyExA(
   NTSTRSAFE_PSTR  pszDest,
              size_t          cchDest,
    NTSTRSAFE_PCSTR pszSrc,
   NTSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcchRemaining,
              DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCchCopyExW(
   NTSTRSAFE_PWSTR  pszDest,
              size_t           cchDest,
    NTSTRSAFE_PCWSTR pszSrc,
   NTSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcchRemaining,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCchCopyNA(
   NTSTRSAFE_PSTR pszDest,
    size_t         cchDest,
    STRSAFE_PCNZCH pszSrc,
        size_t         cchToCopy
);

NTSTRSAFEDDI RtlStringCchCopyNExA(
   NTSTRSAFE_PSTR pszDest,
              size_t         cchDest,
    STRSAFE_PCNZCH pszSrc,
                  size_t         cchToCopy,
   NTSTRSAFE_PSTR *ppszDestEnd,
   size_t         *pcchRemaining,
              DWORD          dwFlags
);

NTSTRSAFEDDI RtlStringCchCopyNExW(
   NTSTRSAFE_PWSTR pszDest,
              size_t          cchDest,
    STRSAFE_PCNZWCH pszSrc,
                  size_t          cchToCopy,
   NTSTRSAFE_PWSTR *ppszDestEnd,
   size_t          *pcchRemaining,
              DWORD           dwFlags
);

NTSTRSAFEDDI RtlStringCchCopyNW(
   NTSTRSAFE_PWSTR pszDest,
    size_t          cchDest,
    STRSAFE_PCNZWCH pszSrc,
        size_t          cchToCopy
);

NTSTRSAFEDDI RtlStringCchCopyUnicodeString(
   NTSTRSAFE_PWSTR  pszDest,
    size_t           cchDest,
    PCUNICODE_STRING SourceString
);

NTSTRSAFEDDI RtlStringCchCopyUnicodeStringEx(
             NTSTRSAFE_PWSTR  pszDest,
              size_t           cchDest,
              PCUNICODE_STRING SourceString,
             NTSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcchRemaining,
              DWORD            dwFlags
);

NTSTRSAFEDDI RtlStringCchCopyW(
   NTSTRSAFE_PWSTR  pszDest,
    size_t           cchDest,
    NTSTRSAFE_PCWSTR pszSrc
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
   NTSTRSAFE_PSTR  pszDest,
    size_t          cchDest,
    NTSTRSAFE_PCSTR pszFormat,
        ...
);

NTSTRSAFEDDI RtlStringCchPrintfExA(
   NTSTRSAFE_PSTR  pszDest,
              size_t          cchDest,
   NTSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcchRemaining,
              DWORD           dwFlags,
              NTSTRSAFE_PCSTR pszFormat,
                  ...
);

NTSTRSAFEDDI RtlStringCchPrintfExW(
   NTSTRSAFE_PWSTR  pszDest,
              size_t           cchDest,
   NTSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcchRemaining,
              DWORD            dwFlags,
              NTSTRSAFE_PCWSTR pszFormat,
                  ...
);

NTSTRSAFEDDI RtlStringCchPrintfW(
   NTSTRSAFE_PWSTR  pszDest,
    size_t           cchDest,
    NTSTRSAFE_PCWSTR pszFormat,
        ...
);

NTSTRSAFEDDI RtlStringCchVPrintfA(
   NTSTRSAFE_PSTR  pszDest,
    size_t          cchDest,
    NTSTRSAFE_PCSTR pszFormat,
    va_list         argList
);

NTSTRSAFEDDI RtlStringCchVPrintfExA(
             NTSTRSAFE_PSTR  pszDest,
              size_t          cchDest,
   NTSTRSAFE_PSTR  *ppszDestEnd,
   size_t          *pcchRemaining,
              DWORD           dwFlags,
    NTSTRSAFE_PCSTR pszFormat,
              va_list         argList
);

NTSTRSAFEDDI RtlStringCchVPrintfExW(
             NTSTRSAFE_PWSTR  pszDest,
              size_t           cchDest,
   NTSTRSAFE_PWSTR  *ppszDestEnd,
   size_t           *pcchRemaining,
              DWORD            dwFlags,
    NTSTRSAFE_PCWSTR pszFormat,
              va_list          argList
);

NTSTRSAFEDDI RtlStringCchVPrintfW(
   NTSTRSAFE_PWSTR  pszDest,
    size_t           cchDest,
    NTSTRSAFE_PCWSTR pszFormat,
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
        NTSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlUnicodeStringCatStringEx(
          PUNICODE_STRING  DestinationString,
              NTSTRSAFE_PCWSTR pszSrc,
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
        NTSTRSAFE_PCWSTR pszSrc,
        size_t           cbToAppend
);


NTSTRSAFEDDI RtlUnicodeStringCbCatStringNEx(
          PUNICODE_STRING  DestinationString,
              NTSTRSAFE_PCWSTR pszSrc,
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
    NTSTRSAFE_PCWSTR pszSrc,
    size_t           cbToCopy
);

NTSTRSAFEDDI RtlUnicodeStringCbCopyStringNEx(
             PUNICODE_STRING  DestinationString,
              NTSTRSAFE_PCWSTR pszSrc,
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
        NTSTRSAFE_PCWSTR pszSrc,
        size_t           cchToAppend
);


NTSTRSAFEDDI RtlUnicodeStringCchCatStringNEx(
          PUNICODE_STRING  DestinationString,
              NTSTRSAFE_PCWSTR pszSrc,
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
    NTSTRSAFE_PCWSTR pszSrc,
    size_t           cchToCopy
);


NTSTRSAFEDDI RtlUnicodeStringCchCopyStringNEx(
             PUNICODE_STRING  DestinationString,
              NTSTRSAFE_PCWSTR pszSrc,
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
    NTSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlUnicodeStringCopyStringEx(
             PUNICODE_STRING  DestinationString,
              NTSTRSAFE_PCWSTR pszSrc,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags
);


NTSTRSAFEDDI RtlUnicodeStringInit(
            PUNICODE_STRING  DestinationString,
   NTSTRSAFE_PCWSTR pszSrc
);

NTSTRSAFEDDI RtlUnicodeStringInitEx(
            PUNICODE_STRING  DestinationString,
   NTSTRSAFE_PCWSTR pszSrc,
             DWORD            dwFlags
);

NTSTRSAFEDDI RtlUnicodeStringPrintf(
   PUNICODE_STRING  DestinationString,
    NTSTRSAFE_PCWSTR pszFormat,
        ...
);

NTSTRSAFEDDI RtlUnicodeStringPrintfEx(
             PUNICODE_STRING  DestinationString,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags,
              NTSTRSAFE_PCWSTR pszFormat,
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
    NTSTRSAFE_PCWSTR pszFormat,
    va_list          argList
);

NTSTRSAFEDDI RtlUnicodeStringVPrintfEx(
             PUNICODE_STRING  DestinationString,
   PUNICODE_STRING  RemainingString,
              DWORD            dwFlags,
              NTSTRSAFE_PCWSTR pszFormat,
              va_list          argList
);



#endif