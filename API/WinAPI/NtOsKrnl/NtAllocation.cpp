#include <LouDDK.h>

LOUDDK_API_ENTRY
NTSTATUS
NtAllocateLocallyUniqueId(
    PLUID Luid
){
    
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS
NtAllocateUuids(
    PULARGE_INTEGER Time,
    PULONG Range,
    PULONG Sequnce,
    PCHAR Seed
){



    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS
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
