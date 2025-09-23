#include "ntdll.h"

NTDLL_API 
NTSTATUS
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
NTSTATUS
WINAPI
RtlMultiByteToUnicodeSize(
    DWORD* Size,
    string Str,
    DWORD  Length
){

    return STATUS_SUCCESS;
}

NTDLL_API 
NTSTATUS
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
NTSTATUS 
WINAPI 
RtlUnicodeToMultiByteSize(
    DWORD* Size,
    LPWSTR Str,
    DWORD  Length
){    
    //TODO:
    return STATUS_SUCCESS;
}

NTDLL_API
WCHAR  
RtlAnsiCharToUnicodeChar(
    string* Strp
) {
    
    //TODO:
    return 0;
}

NTDLL_API
NTSTATUS
WINAPI
RtlUpcaseUnicodeToMultiByteN(
    string  Destination,
    DWORD   DestinationLength,
    DWORD*  ResultLength,
    LPWSTR  Source,
    DWORD   SourceLength
){

}