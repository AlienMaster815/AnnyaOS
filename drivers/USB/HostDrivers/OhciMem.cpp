//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "OHCI.h"

LOUSTATUS
OhciAllocateDma(
    PUSB_HCD_OBJECT HcdObject,
    size_t          Size,
    size_t          Alignment,
    PVOID*          Out
){
    if((!HcdObject) || (!Out) || (!Alignment) || (!Size)){
        return STATUS_INVALID_PARAMETER;
    }
    *Out = LouKeDmaDeviceAllocateDmaMemory(&HcdObject->DmaDevice, Size, Alignment);
    if(!(*Out)){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    return STATUS_SUCCESS;
}

void OhciFreeDma(
    PUSB_HCD_OBJECT HcdObject,
    PVOID           VAddress
){
    LouKeDmaDeviceFreeDmaMemory(&HcdObject->DmaDevice, VAddress);
}

UINT32 OhciGetDmaAddress(
    PVOID VAddress
){
    UINT64 PhyAddress;
    RequestPhysicalAddress((UINT64)VAddress, &PhyAddress);
    return (UINT32)(UINTPTR)PhyAddress;
}
