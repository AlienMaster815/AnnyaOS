#include <LouDDK.h>

LOUAPI
LOUSTATUS
NtAllocateLocallyUniqueId(
    PLUID Luid
){
    
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS
NtAllocateUuids(
    PULARGE_INTEGER Time,
    PULONG Range,
    PULONG Sequnce,
    PCHAR Seed
){



    return STATUS_SUCCESS;
}

LOUAPI
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
