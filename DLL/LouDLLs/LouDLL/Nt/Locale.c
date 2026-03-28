//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "ntdll.h"
#include "privlocal.h"

NTDLL_API 
LOUSTATUS
WINAPI
RtlMultiByteToUnicodeN(
    LPWSTR  Destination,
    DWORD   DestinationLength,
    DWORD*  ResultLength,
    string  Src,
    DWORD   SrcLength
){

    return STATUS_SUCCESS;
}

NTDLL_API
LOUSTATUS
WINAPI
RtlMultiByteToUnicodeSize(
    DWORD* Size,
    string Str,
    DWORD  Length
){

    return STATUS_SUCCESS;
}

NTDLL_API 
LOUSTATUS
WINAPI
RtlUnicodeToMultiByteN(
    string  Destination,
    DWORD   DestinationLength,
    DWORD*  ResultLength,
    LPWSTR  Source,
    DWORD   SrcLength
){
    //TODO
    return STATUS_SUCCESS;
}

NTDLL_API
LOUSTATUS 
WINAPI 
RtlUnicodeToMultiByteSize(
    DWORD* Size,
    LPWSTR Str,
    DWORD  Length
){    
    //TODO:
    return STATUS_SUCCESS;
}