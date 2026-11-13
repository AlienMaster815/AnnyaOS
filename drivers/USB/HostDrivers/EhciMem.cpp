//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "Ehci.h"

static LOUSINE_DMA_DEVICE EhciDataStructure = {
    .DmaDeviceFlags = LOUSINE_DMA_DEVICE_FLAGS_SCATTER_DMA_SUPPORTED,
    .MaxScatterCount = 8320,
    .AllocatorData = {
        .DmaLimit = 32,
        .DmaThreshold = 64 * KILOBYTE,
    },
};

static LOUSTATUS AllocateDmaMemoryFromDevice(
    PLOUSINE_DMA_DEVICE DmaDevice,
    SIZE                AllocationSize,
    SIZE                Alignment,
    PVOID*              Out
){  
    if(
        (!DmaDevice) || (!AllocationSize) ||
        (!Alignment) || (!Out)
    ){
        return STATUS_INVALID_PARAMETER;
    }
    PVOID Tmp = LouKeDmaDeviceAllocateDmaMemory(DmaDevice, AllocationSize, Alignment);
    if(!Tmp){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    *Out = Tmp;
    return STATUS_SUCCESS;
}

static LOUSTATUS FreeDmaMemoryFromDevice(
    PLOUSINE_DMA_DEVICE DmaDevice,
    PVOID               Address
){
    if((!DmaDevice) || (!Address)){
        return STATUS_INVALID_PARAMETER;
    }
    LouKeDmaDeviceFreeDmaMemory(DmaDevice, Address);
    return STATUS_SUCCESS;
}

LOUSTATUS EhciInitializeEhciMemoryManagement(
    PEHCI_DEVICE_OBJECT EhciObject
){

    memcpy(&EhciObject->DataStructureDmaDev, &EhciDataStructure, sizeof(LOUSINE_DMA_DEVICE));
    memcpy(&EhciObject->MainDmaDev, &EhciDataStructure, sizeof(LOUSINE_DMA_DEVICE));
    if(EhciObject->EhciDeviceCapabilities.EhciMiscFlags & EHCI_DEVICE_CAPABILITIES_MISC_FLAG_64BIT_DMA){
        EhciObject->MainDmaDev.AllocatorData.DmaLimit = 64;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS EhciAllocateDmaMemoryForDataStructures(
    PEHCI_DEVICE_OBJECT     EhciObject,
    SIZE                    AllocationSize,
    SIZE                    AllocationAlignment,
    PVOID*                  Out
){
    return AllocateDmaMemoryFromDevice(&EhciObject->DataStructureDmaDev, AllocationSize, AllocationAlignment, Out); 
}

LOUSTATUS EhciFreeDmaMemoryForDataStructures(
    PEHCI_DEVICE_OBJECT     EhciObject,
    PVOID                   Address
){
    return FreeDmaMemoryFromDevice(&EhciObject->DataStructureDmaDev, Address);
}

LOUSTATUS EhciAllocateDmaMemory(
    PEHCI_DEVICE_OBJECT     EhciObject,
    SIZE                    AllocationSize,
    SIZE                    AllocationAlignment,
    PVOID*                  Out
){
    return AllocateDmaMemoryFromDevice(&EhciObject->MainDmaDev, AllocationSize, AllocationAlignment, Out); 
}

LOUSTATUS EhciFreeDmaMemory(
    PEHCI_DEVICE_OBJECT     EhciObject,
    PVOID                   Address
){
    return FreeDmaMemoryFromDevice(&EhciObject->MainDmaDev, Address);
}

UINTPTR EhciGetDmaAddress(
    PVOID VAddress
){
    UINT64 PhyAddress;
    RequestPhysicalAddress((UINT64)VAddress, &PhyAddress);
    return (UINTPTR)PhyAddress;
}

LOUSTATUS 
EhciAllocatePeriodicFrameListBase(
    PEHCI_DEVICE_OBJECT    EhciObject
){
    LOUSTATUS   Status;
    PVOID       Flb;
    UINT32*     Tmp;
    Status = EhciAllocateDmaMemoryForDataStructures(EhciObject, sizeof(UINT32) * 1024, KILOBYTE_PAGE, &Flb);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    Tmp = (UINT32*)Flb;
    EhciObject->VirtualFrameListBase = Flb;
    for(size_t i = 0 ; i < 1024; i++){
        Tmp[i] = EHCI_PFLE_TERMINATE_BIT;
    }
    return STATUS_SUCCESS;
}

void EhciResetPeriodicFrameList(PVOID FrameListBaseAddress){
    UINT32* Tmp = (UINT32*)FrameListBaseAddress;
    for(size_t i = 0 ; i < 1024; i++){
        Tmp[i] = EHCI_PFLE_TERMINATE_BIT;
    }
}

/*

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
*/