#include "EHCI.h"

//TODO: Add support for 64 bit supported systems

static LOUSTATUS
EhciAllocateDma32(
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
        LouPrint("EHCI.SYS:Unable To Allocate 32 Bit Memmory\n");
        LouKeFreePhy32(Result);
        *Out = 0x00; 
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    *Out = Result;
    return STATUS_SUCCESS;
}


LOUSTATUS EhciAllocateDma(
    PEHCI_DEVICE    EhciDevice,
    SIZE            size, 
    SIZE            Alignment,
    PVOID*          Out
){
    //if(EhciDevice->Dma64Supported){
        //if((!Out) || (!Alignment) || (!size)){
        //    return STATUS_INVALID_PARAMETER;
        //}
        //*Out = LouKeMallocEx(size, Alignment, KERNEL_DMA_MEMORY);
        //return STATUS_SUCCESS; 
    //}

    return EhciAllocateDma32(size, Alignment, Out);
}

UINTPTR EhciGetDmaAddress(
    PVOID VAddress
){
    UINT64 PhyAddress;
    RequestPhysicalAddress((UINT64)VAddress, &PhyAddress);
    return (UINTPTR)PhyAddress;
}

void EhciFreeDma(PEHCI_DEVICE EhciDevice, PVOID VAddress){
    //if(EhciDevice->Dma64Supported){
    //    LouKeFree(VAddress);
    //    return;
    //}
    LouKeFreePhy32(VAddress);
}

LOUSTATUS 
EhciAllocatePeriodicFrameListBase(
    PEHCI_DEVICE    EhciDevice
){
    LOUSTATUS Status;
    PEHCI_HOST_OPERATIONAL_REGISTERS OpRegs = EhciDevice->OperationalRegisters;
    PVOID Out;
    
    Status = EhciAllocateDma(EhciDevice, 4 * KILOBYTE, 4 * KILOBYTE, &Out);
    if(Status != STATUS_SUCCESS){
        LouPrint("EHCI.SYS:Could Not Allocate Resources For Periodic Frame List\n");
        return Status;
    }
    
    EhciDevice->PeriodicFrameListBase = (UINTPTR)Out;

    UINT32* Tmp = (UINT32*)EhciDevice->PeriodicFrameListBase;
    for(size_t i = 0 ; i < 1024; i++){
        Tmp[i] = EHCI_PFLE_TERMINATE_BIT;
    }
    OpRegs->FrameListBaseAddress = EhciGetDmaAddress((PVOID)EhciDevice->PeriodicFrameListBase);    

    return STATUS_SUCCESS;
}

LOUSTATUS 
EhciAllocateAsyncHead(
    PEHCI_DEVICE EhciDevice
){
    LOUSTATUS Status;
    PVOID Out;
    PEHCI_HOST_OPERATIONAL_REGISTERS OpRegs = EhciDevice->OperationalRegisters;
    Status = EhciAllocateDma(EhciDevice, 64, 32, &Out);
    if(Status != STATUS_SUCCESS){
        LouPrint("EHCI.SYS:Unable To Allocate Resources For Async Qh\n");
        return Status;
    }

    EhciDevice->AshQHAddress = (UINTPTR)Out;
    PEHCI_QH Qh = (PEHCI_QH)EhciDevice->AshQHAddress;

    UINT32 DmaAddress = (UINT32)EhciGetDmaAddress((PVOID)EhciDevice->AshQHAddress);
    if((DmaAddress & 0xFFFFFFE0) != DmaAddress){
        LouPrint("EHCI.SYS:Alignment For Dma Got Corrupted\n");
        return STATUS_INVALID_ADDRESS;
    }
    Qh->HLink = 0;//DmaAddress | (1 << 3);
    Qh->EpChar = (2 << 11) | (1 << 13) | (64 << 16);

    Qh->EpCaps = 0;
    Qh->CurrentQtd = 0;
    Qh->NextQtd = 1;
    Qh->AltNextQtd = 1;
    Qh->Token = 0;

    OpRegs->NextAsyncListAddress = DmaAddress;

    return STATUS_SUCCESS;
}
