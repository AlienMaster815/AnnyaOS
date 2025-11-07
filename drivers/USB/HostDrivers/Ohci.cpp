#include "OHCI.h"

LOUSTATUS OhciCreateEdPool(
    POHCI_DEVICE    OhciDevice
){
    POHCI_ED_POOL TmpPool = &OhciDevice->EdPool;

    UINT64 NewPoolAddress = (UINT64)LouKeMallocPhysicalEx(OHCI_ED_POOL_SIZE * sizeof(OHCI_ED_TRACKER), GET_ALIGNMENT(OHCI_ED_TRACKER), KERNEL_DMA_MEMORY);

    if(NewPoolAddress > UINT32_MAX){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    POOL NewPool = LouKeCreateGenericPool(
        NewPoolAddress,
        NewPoolAddress,
        OHCI_ED_POOL_SIZE * sizeof(OHCI_ED_TRACKER),
        KERNEL_DMA_MEMORY
    );

    while(TmpPool->Peers.NextHeader){
        TmpPool = (POHCI_ED_POOL)TmpPool->Peers.NextHeader;
    }


    if(!TmpPool->EdPool){
        TmpPool->EdPool = NewPool;
        return STATUS_SUCCESS;
    }

    TmpPool->Peers.NextHeader = (PListHeader)LouKeMallocType(OHCI_ED_POOL ,KERNEL_GENERIC_MEMORY); 
    TmpPool = (POHCI_ED_POOL)TmpPool->Peers.NextHeader;
    TmpPool->EdPool = NewPool;

    return STATUS_SUCCESS;
}

PVOID OhciAllocateEndpoint(
    POHCI_DEVICE OhciDevice
){
    POHCI_ED_POOL TmpPool = &OhciDevice->EdPool;
    PVOID Result = 0x00;
    while(!Result && TmpPool){
        Result = LouKeMallocFromDynamicPoolEx(TmpPool->EdPool, OHCI_ED_POOL_SIZE, GET_ALIGNMENT(OHCI_ED_TRACKER));
        TmpPool = (POHCI_ED_POOL)TmpPool->Peers.NextHeader;
    } 
    return Result;
}

LOUSTATUS OhciInitializeEndpointDescriptor(
    POHCI_ENDPOINT_DESCRIPTOR   EndpointDescriptor,
    POHCI_ED_INITIALIZOR        Initializor
){
    if((!EndpointDescriptor) || (!Initializor)){
        return STATUS_INVALID_PARAMETER;
    }
    
    memset(EndpointDescriptor, 0, sizeof(OHCI_ENDPOINT_DESCRIPTOR));

    EndpointDescriptor->Dword0 |= ((Initializor->FunctionAddress & (OHCI_ED_FA_MASK)) << (OHCI_ED_FA_SHIFT));
    EndpointDescriptor->Dword0 |= ((Initializor->EndpointNumber & (OHCI_ED_EN_MASK)) << (OHCI_ED_EN_SHIFT));
    EndpointDescriptor->Dword0 |= ((Initializor->Direction & (OHCI_ED_D_MASK)) << (OHCI_ED_D_SHIFT));
    EndpointDescriptor->Dword0 |= ((Initializor->Speed & (OHCI_ED_S_MASK)) << OHCI_ED_S_SHIFT);
    EndpointDescriptor->Dword0 |= ((Initializor->Skip & (OHCI_ED_K_MASK)) << (OHCI_ED_K_SHIFT));
    EndpointDescriptor->Dword0 |= ((Initializor->Format & (OHCI_ED_F_MASK)) << (OHCI_ED_F_SHIFT));
    EndpointDescriptor->Dword0 |= ((Initializor->MaximumPacketSize & (OHCI_ED_MPS_MASK)) << (OHCI_ED_MPS_SHIFT));
    EndpointDescriptor->Dword1 |= ((Initializor->TDQueueTailPointer & (OHCI_ED_TAILP_MASK)));
    EndpointDescriptor->Dword2 |= ((Initializor->Halted & (OHCI_ED_H_MASK)) << (OHCI_ED_H_SHIFT));
    EndpointDescriptor->Dword2 |= ((Initializor->ToggleCarry & (OHCI_ED_C_MASK)) << (OHCI_ED_C_SHIFT));
    EndpointDescriptor->Dword2 |= ((Initializor->TDQueueHeadPointer & (OHCI_ED_HEADP_MASK)));
    EndpointDescriptor->Dword3 |= ((Initializor->NextED & (OHCI_ED_NEXTED_MASK)));
    
    return STATUS_SUCCESS;
}

LOUSTATUS OhciCreateEndpoint(
    POHCI_DEVICE    OhciDevice,
    UINT8           FunctionAddress,
    UINT8           EndpointNumber,
    UINT8           Direction,
    BOOL            LowSpeed,
    OHCI_ED_TYPE    EdType
){



    return STATUS_SUCCESS;
}

LOUSTATUS 
OhciInitialzeEndpointHeaders(
    POHCI_DEVICE    OhciDevice
){
    POHCI_OPERATIONAL_REGISTERS OpReg = OhciDevice->OperationalRegisters;

    OhciDevice->HccaAddress = (UINT64)LouKeMallocPhysicalEx(256, 256, KERNEL_DMA_MEMORY);
    if(OhciDevice->HccaAddress >= UINT32_MAX){
        LouPrint("No Free 32 bit Address\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    //TODO: interrupt descriptors

    return STATUS_SUCCESS;
}