#ifndef _LOUSTRSAFE_H
#define _LOUSTRSAFE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <Ldm.h>

KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCatA(LOUSTRSAFE_PSTR  pszDest, size_t cbDest, LOUSTRSAFE_PCSTR pszSrc);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCatExA(LOUSTRSAFE_PSTR pszDest,size_t cbDest, LOUSTRSAFE_PCSTR pszSrc, LOUSTRSAFE_PSTR* ppszDestEnd, size_t* pcbRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCatExW(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, LOUSTRSAFE_PCWSTR pszSrc, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcbRemaining,DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCatNA(LOUSTRSAFE_PSTR pszDest, size_t cbDest, STRSAFE_PCNZCH pszSrc, size_t cbToAppend);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCatNExA(LOUSTRSAFE_PSTR pszDest, size_t cbDest, STRSAFE_PCNZCH pszSrc, size_t cbToAppend, LOUSTRSAFE_PSTR* ppszDestEnd, size_t* pcbRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCatNExW(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, STRSAFE_PCNZWCH pszSrc, size_t cbToAppend, LOUSTRSAFE_PWSTR *ppszDestEnd, size_t* pcbRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCatNW(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, STRSAFE_PCNZWCH pszSrc, size_t cbToAppend);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCatW(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, LOUSTRSAFE_PCWSTR pszSrc);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCopyA(LOUSTRSAFE_PSTR  pszDest, size_t cbDest, LOUSTRSAFE_PCSTR pszSrc);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCopyExA(LOUSTRSAFE_PSTR  pszDest, size_t cbDest, LOUSTRSAFE_PCSTR pszSrc, LOUSTRSAFE_PSTR* ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCopyExW(LOUSTRSAFE_PWSTR  pszDest, size_t cbDest, LOUSTRSAFE_PCWSTR pszSrc, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcbRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCopyNA(LOUSTRSAFE_PSTR pszDest, size_t cbDest, STRSAFE_PCNZCH pszSrc, size_t cbToCopy);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCopyNExA(LOUSTRSAFE_PSTR pszDest, size_t cbDest, STRSAFE_PCNZCH pszSrc, size_t cbToCopy, LOUSTRSAFE_PSTR* ppszDestEnd, size_t* pcbRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCopyNExW(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, STRSAFE_PCNZWCH pszSrc, size_t cbToCopy, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcbRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCopyNW(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, STRSAFE_PCNZWCH pszSrc, size_t cbToCopy);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCopyUnicodeString(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, PCUNICODE_STRING SourceString);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCopyUnicodeStringEx(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, PCUNICODE_STRING SourceString, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcbRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbCopyW(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, LOUSTRSAFE_PCWSTR pszSrc);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbLengthA(STRSAFE_PCNZCH psz, size_t cbMax, size_t* pcbLength);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbLengthW(STRSAFE_PCNZWCH psz, size_t cbMax, size_t* pcbLength);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbPrintfA(LOUSTRSAFE_PSTR pszDest, size_t cbDest, LOUSTRSAFE_PCSTR pszFormat, ...);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbPrintfExA(LOUSTRSAFE_PSTR pszDest, size_t cbDest, LOUSTRSAFE_PSTR* ppszDestEnd, size_t* pcbRemaining, DWORD dwFlags, LOUSTRSAFE_PCSTR pszFormat, ...);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbPrintfExW(LOUSTRSAFE_PWSTR pszDest,size_t cbDest, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcbRemaining, DWORD dwFlags, LOUSTRSAFE_PCWSTR pszFormat, ...);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbPrintfW(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, LOUSTRSAFE_PCWSTR pszFormat, ...);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbVPrintfA(LOUSTRSAFE_PSTR pszDest, size_t cbDest, LOUSTRSAFE_PCSTR pszFormat,va_list argList);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbVPrintfExA(LOUSTRSAFE_PSTR pszDest, size_t cbDest, LOUSTRSAFE_PSTR* ppszDestEnd, size_t* pcbRemaining, DWORD dwFlags, LOUSTRSAFE_PCSTR pszFormat, va_list argList);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbVPrintfExW(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcbRemaining, DWORD dwFlags, LOUSTRSAFE_PCWSTR pszFormat, va_list argList);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCbVPrintfW(LOUSTRSAFE_PWSTR pszDest, size_t cbDest, LOUSTRSAFE_PCWSTR pszFormat, va_list argList);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCatA(LOUSTRSAFE_PSTR  pszDest, size_t cchDest, LOUSTRSAFE_PCSTR pszSrc);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCatExA(LOUSTRSAFE_PSTR pszDest, size_t cchDest, LOUSTRSAFE_PCSTR pszSrc, LOUSTRSAFE_PSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCatExW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, LOUSTRSAFE_PCWSTR pszSrc, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCatNA(LOUSTRSAFE_PSTR pszDest, size_t cchDest, STRSAFE_PCNZCH pszSrc, size_t cchToAppend);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCatNExA(LOUSTRSAFE_PSTR pszDest, size_t cchDest, STRSAFE_PCNZCH pszSrc, size_t cchToAppend, LOUSTRSAFE_PSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCatNExW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, STRSAFE_PCNZWCH pszSrc, size_t cchToAppend, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCatNW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, STRSAFE_PCNZWCH pszSrc, size_t cchToAppend);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCatW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, LOUSTRSAFE_PCWSTR pszSrc);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCopyA(LOUSTRSAFE_PSTR pszDest, size_t cchDest, LOUSTRSAFE_PCSTR pszSrc);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCopyExA(LOUSTRSAFE_PSTR pszDest, size_t cchDest, LOUSTRSAFE_PCSTR pszSrc, LOUSTRSAFE_PSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCopyExW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, LOUSTRSAFE_PCWSTR pszSrc, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCopyNA(LOUSTRSAFE_PSTR pszDest, size_t cchDest, STRSAFE_PCNZCH pszSrc, size_t cchToCopy);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCopyNExA(LOUSTRSAFE_PSTR pszDest, size_t cchDest, STRSAFE_PCNZCH pszSrc, size_t cchToCopy, LOUSTRSAFE_PSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCopyNExW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, STRSAFE_PCNZWCH pszSrc, size_t cchToCopy, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCopyNW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, STRSAFE_PCNZWCH pszSrc, size_t cchToCopy);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCopyUnicodeString(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, PCUNICODE_STRING SourceString);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCopyUnicodeStringEx(LOUSTRSAFE_PWSTR  pszDest, size_t cchDest, PCUNICODE_STRING SourceString, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchCopyW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, LOUSTRSAFE_PCWSTR pszSrc);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchLengthA(STRSAFE_PCNZCH psz, size_t cchMax, size_t* pcchLength);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchLengthW(STRSAFE_PCNZWCH psz, size_t cchMax, size_t* pcchLength);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchPrintfA(LOUSTRSAFE_PSTR pszDest, size_t cchDest, LOUSTRSAFE_PCSTR pszFormat, ...);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchPrintfExA(LOUSTRSAFE_PSTR pszDest, size_t cchDest, LOUSTRSAFE_PSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags, LOUSTRSAFE_PCSTR pszFormat, ...);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchPrintfExW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags, LOUSTRSAFE_PCWSTR pszFormat, ...);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchPrintfW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, LOUSTRSAFE_PCWSTR pszFormat, ...);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchVPrintfA(LOUSTRSAFE_PSTR pszDest, size_t cchDest, LOUSTRSAFE_PCSTR pszFormat, va_list argList);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchVPrintfExA(LOUSTRSAFE_PSTR pszDest, size_t cchDest, LOUSTRSAFE_PSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags, LOUSTRSAFE_PCSTR pszFormat, va_list argList);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchVPrintfExW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, LOUSTRSAFE_PWSTR* ppszDestEnd, size_t* pcchRemaining, DWORD dwFlags, LOUSTRSAFE_PCWSTR pszFormat, va_list argList);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlStringCchVPrintfW(LOUSTRSAFE_PWSTR pszDest, size_t cchDest, LOUSTRSAFE_PCWSTR pszFormat, va_list argList);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnalignedStringCbLengthW(STRSAFE_PCUNZWCH psz, size_t cbMax, size_t* pcbLength);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnalignedStringCchLengthW(STRSAFE_PCUNZWCH psz, size_t cchMax, size_t* pcchLength);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCat(PUNICODE_STRING DestinationString, PCUNICODE_STRING SourceString);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCatEx(PUNICODE_STRING DestinationString, PCUNICODE_STRING SourceString, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCatString(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCatStringEx(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCbCatN(PUNICODE_STRING  DestinationString, PCUNICODE_STRING SourceString, size_t cbToAppend);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCbCatNEx(PUNICODE_STRING DestinationString, PCUNICODE_STRING SourceString, size_t cbToAppend, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCbCatStringN(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc, size_t cbToAppend);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCbCatStringNEx(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc, size_t cbToAppend, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCbCopyN(PUNICODE_STRING DestinationString, PCUNICODE_STRING SourceString, size_t cbToCopy);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCbCopyNEx(PUNICODE_STRING  DestinationString, PCUNICODE_STRING SourceString, size_t cbToCopy, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCbCopyStringN(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc, size_t cbToCopy);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCbCopyStringNEx(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc, size_t cbToCopy, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCchCatN(PUNICODE_STRING DestinationString, PCUNICODE_STRING SourceString, size_t cchToAppend);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCchCatNEx(PUNICODE_STRING DestinationString, PCUNICODE_STRING SourceString, size_t cchToAppend, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCchCatStringN(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc, size_t cchToAppend);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCchCatStringNEx(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc, size_t cchToAppend, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCchCopyN(PUNICODE_STRING DestinationString, PCUNICODE_STRING SourceString, size_t cchToCopy);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCchCopyNEx(PUNICODE_STRING DestinationString, PCUNICODE_STRING SourceString, size_t cchToCopy, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCchCopyStringN(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc, size_t cchToCopy);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCchCopyStringNEx(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc, size_t cchToCopy, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCopy(PUNICODE_STRING DestinationString, PCUNICODE_STRING SourceString);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCopyEx(PUNICODE_STRING DestinationString, PCUNICODE_STRING SourceString, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCopyString(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringCopyStringEx(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc, PUNICODE_STRING RemainingString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringInit(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringInitEx(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszSrc, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringPrintf(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszFormat, ...);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringPrintfEx(PUNICODE_STRING DestinationString, PUNICODE_STRING RemainingString, DWORD dwFlags, LOUSTRSAFE_PCWSTR pszFormat, ...);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringValidate(PCUNICODE_STRING SourceString);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringValidateEx(PCUNICODE_STRING SourceString, DWORD dwFlags);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringVPrintf(PUNICODE_STRING DestinationString, LOUSTRSAFE_PCWSTR pszFormat, va_list argList);
KERNEL_EXPORT LOUSTRSAFEDDI LouKeRtlUnicodeStringVPrintfEx(PUNICODE_STRING DestinationString, PUNICODE_STRING RemainingString, DWORD dwFlags, LOUSTRSAFE_PCWSTR pszFormat, va_list argList);


#ifdef __cplusplus
}
#endif
#endif