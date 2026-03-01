#include <LouDDK.h>

LOUDDK_API_ENTRY
LOUSTATUS
NtAllocateLocallyUniqueId(
    PLUID Luid
){
    
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
LOUSTATUS
NtAllocateUuids(
    PULARGE_INTEGER Time,
    PULONG Range,
    PULONG Sequnce,
    PCHAR Seed
){



    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
LOUSTATUS
NtAllocateVirtualMemory(
    HANDLE ProcessHandle,
    PVOID BaseAddress,
    ULONG_PTR ZeroBits,
    PSIZE_T RegionSize,
    ULONG AllocationType,
    ULONG Protect
){


    return STATUS_SUCCESS;
}
