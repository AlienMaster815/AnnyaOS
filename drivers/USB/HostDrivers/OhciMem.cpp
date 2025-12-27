#include "OHCI.h"

LOUSTATUS
OhciAllocateDma(
    size_t  Size,
    size_t  Alignment,
    PVOID*  Out
){
    if((!Out) || (!Alignment) || (!Size)){
        return STATUS_INVALID_PARAMETER;
    }
    PVOID Result = LouKeMallocExPhy32(Size, Alignment, KERNEL_DMA_MEMORY);
    UINT64 PhyAddress;
    RequestPhysicalAddress((UINT64)Result, &PhyAddress);
    if((PhyAddress + Size) > UINT32_MAX){
        LouPrint("OHCI.SYS:Unable To Allocate 32 Bit Memmory\n");
        LouKeFreePhy32(Result);
        *Out = 0x00; 
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    *Out = Result;
    return STATUS_SUCCESS;
}

void OhciFreeDma(
    PVOID VAddress
){
    LouKeFreePhy32(VAddress);
}

UINT32 OhciGetDmaAddress(
    PVOID VAddress
){
    UINT64 PhyAddress;
    RequestPhysicalAddress((UINT64)VAddress, &PhyAddress);
    return (UINT32)(UINTPTR)PhyAddress;
}