#include "OHCI.h"


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

/*LOUSTATUS OhciCreateEndpoint(
    POHCI_DEVICE    OhciDevice,
    UINT8           FunctionAddress,
    UINT8           EndpointNumber,
    UINT8           Direction,
    BOOL            LowSpeed,
    OHCI_ED_TYPE    EdType
){
    LOUSTATUS Status;
    PVOID NewEp;

    Status = OhciAllocateDma(sizeof(OHCI_ENDPOINT_DESCRIPTOR), 16, &NewEp);
    if(!NT_SUCCESS(Status)){
        return Status;
    }
    OHCI_ED_INITIALIZOR EpInit = {0};

    EpInit.FunctionAddress = FunctionAddress;
    EpInit.EndpointNumber = EndpointNumber;
    EpInit.Direction = Direction;


    return STATUS_SUCCESS;
}*/

LOUSTATUS 
OhciInitialzeHcca(
    POHCI_DEVICE    OhciDevice
){
    POHCI_OPERATIONAL_REGISTERS OpReg = OhciDevice->OperationalRegisters;
    UINT64 PhyAddress;
    LOUSTATUS Status;

    Status = OhciAllocateDma(256, 256, (PVOID*)&OhciDevice->HccaAddress);
    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Unable To Allocate HCCA Memory\n");
        return Status;
    }

    OhciDevice->OperationalRegisters->HcHCCA = OhciGetDmaAddress((PVOID)OhciDevice->HccaAddress);

    return STATUS_SUCCESS;
}

LOUSTATUS 
OhciInitializePort(
    POHCI_DEVICE    Device,
    UINT8           Port
){
    POHCI_OPERATIONAL_REGISTERS OpRegs = Device->OperationalRegisters;    
    LOUSTATUS Status;
    //TODO:use an io timer
    UINT32 Tmp;
    Tmp = (OHCI_PORT_STATUS_PRS);
    OpRegs->HcRhPortStatus[Port] = Tmp;

    Status = LouKeWaitForUlongRegisterCondition(
        (PULONG)LouKeCastToUnalignedPointer(&OpRegs->HcRhPortStatus[Port]), //it actually is aligned the compiler just gives a warning
        100,
        OHCI_PORT_STATUS_PRS,
        0
    );

    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Port:%d Hung On PRS Command\n", Port);
        return STATUS_TIMEOUT;
    }
    

    Tmp = OpRegs->HcRhPortStatus[Port];
    if(Tmp & OHCI_PORT_STATUS_PRSC){
        OpRegs->HcRhPortStatus[Port] = OHCI_PORT_STATUS_PRSC;
    }

    Tmp = OpRegs->HcRhPortStatus[Port];
    if(!(Tmp & OHCI_PORT_STATUS_PES)){
        OpRegs->HcRhPortStatus[Port] = OHCI_PORT_STATUS_PES;
    }
    Device->Port[Port].PortEnabled = true;

    Tmp = OpRegs->HcRhPortStatus[Port];
    if(Tmp & OHCI_PORT_STATUS_PESC){
        OpRegs->HcRhPortStatus[Port] = OHCI_PORT_STATUS_PESC;
    }

    Tmp = OpRegs->HcRhPortStatus[Port];

    if(Tmp & OHCI_PORT_STATUS_LSDA){
        LouPrint("OHCI.SYS:Device Is Low Speed\n");
        Device->Port[Port].LowSpeed = true;
    }else{
        LouPrint("OHCI.SYS:Device Is Full Speed\n");
        Device->Port[Port].LowSpeed = false;
    }

    //while(1);
    return STATUS_SUCCESS;
}

