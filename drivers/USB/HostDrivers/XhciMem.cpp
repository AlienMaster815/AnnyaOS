#include "Xhci.h"


LOUSTATUS
XhciAllocateDmaMemory32(
    SIZE    Size,
    SIZE    Alignment,
    PVOID*  Out
){
    if(!Size || !Alignment || !Out){
        return STATUS_INVALID_PARAMETER;
    }

    PVOID Result = LouKeMallocExPhy32(Size, Alignment, KERNEL_DMA_MEMORY);
    UINT64 PhyAddress;
    RequestPhysicalAddress((UINT64)Result, &PhyAddress);
    if((PhyAddress + Size) > UINT32_MAX){
        LouPrint("XHCI.SYS:Unable To Allocate 32 Bit Memmory\n");
        LouKeFreePhy32(Result);
        *Out = 0x00; 
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    *Out = Result;
    return STATUS_SUCCESS;
}

LOUSTATUS
XhciAllocateDmaMemory64(
    SIZE    Size,
    SIZE    Alignment,
    PVOID*  Out
){
    if(!Size || !Alignment || !Out){
        return STATUS_INVALID_PARAMETER;
    }

    *Out = LouKeMallocEx(Size, Alignment, KERNEL_DMA_MEMORY);

    return STATUS_SUCCESS;
}

LOUSTATUS
XhciAllocateDmaMemory(
    PXHCI_DEVICE    Device,
    SIZE            Size,
    SIZE            Alignment,
    PVOID*          Out
){
    return Device->XhciAllocationFunction(Size, Alignment, Out);
}
void XhciFreeDmaMemory64(PVOID Address){
    LouKeFree(Address);
}   

void XhciFreeDmaMemory32(PVOID Address){
    LouKeFreePhy32(Address);
}

void 
XhciFreeDmaMemory(
    PXHCI_DEVICE    Device,
    PVOID           Address
){
    Device->XhciFreeFunction(Address);
}

UINT64 XhciGetDmaAddress(
    PVOID Address
){
    UINT64 Result;
    RequestPhysicalAddress((UINT64)Address, &Result);
    return Result;
}

LOUSTATUS XhciInitializeMemoryManagement(
    PXHCI_DEVICE Device
){
    if(!Device){
        return STATUS_INVALID_PARAMETER;
    }

    if(Device->Capabilities.Dma64Supported){
        Device->XhciAllocationFunction = XhciAllocateDmaMemory64;
        Device->XhciFreeFunction = XhciFreeDmaMemory64;
    }else{
        Device->XhciAllocationFunction = XhciAllocateDmaMemory32;
        Device->XhciFreeFunction = XhciFreeDmaMemory32;
    }



    return STATUS_SUCCESS;
}