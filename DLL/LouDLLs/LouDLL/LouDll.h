#ifndef _LOUDLL_
#define _LOUDLL_
#define _INCLUDE_DRSD_LIBRARY_

#include <Annya.h>
#include <stdarg.h>
#include <USRSPC/DRSD.h>

#define LOUDLL_API __declspec(dllexport)

#define SET_OPTIMIZATION(x) __attribute__((optimize(x)))

LOUDLL_API
void LouGlobalUserFree(void* Addr);

void* AnnyaNtGetProcessHeap();
NTSTATUS RtlInitializeCriticalSectionEx(
    PMSVC_CRITICAL_SECTION CriticalSection,
    uint32_t SpinCount,
    uint32_t Flags
);

NTSTATUS RtlEnterCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

NTSTATUS RtlLeaveCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection);

uint16_t NtGetProcessorCount();

void* RtlAllocateHeapEx(
    PVOID       HeapHandle,
    uint64_t    HeapAllocationFlags,
    size_t      HeapSize,
    size_t      Alignment
);

void* 
RtlAllocateHeap(
    PVOID       HeapHandle,
    uint64_t    HeapAllocationFlags,
    size_t      HeapSize
);

void* AnnyaNtGetProcessHeap();

int
_wcsicmp(
    LPCWSTR String1,
    LPCWSTR String2
);

int 
_wcslwr_s(
    LPWSTR Str, 
    size_t Length 
);

LPWSTR _wcslwr(
    LPWSTR Str
);

size_t
wcslen(
    LPCWSTR Str  
);

size_t wcsnlen(const WCHAR *str, size_t len);

int _wcsnicmp(LPCWSTR str1, LPCWSTR str2, size_t n);

#endif