#include "OHCI.h"

LOUSTATUS OhciInitializeTransferDescriptor(
    POHCI_TRANSFER_DESCRIPTOR   Td,
    POHCI_TD_INITIALIZOR        Initializor
){
    LouPrint("OHCI.SYS:OhciInitializeTransferDescriptor()\n");
    if((!Td) || (!Initializor)){
        LouPrint("OHCI.SYS:Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }

    memset(Td, 0, sizeof(OHCI_TRANSFER_DESCRIPTOR));

    Td->Dword0 |= ((Initializor->BufferRounding & OHCI_TD_R_MASK) << OHCI_TD_R_SHIFT);
    Td->Dword0 |= ((Initializor->DirectionPID & OHCI_TD_DP_MASK) << OHCI_TD_DP_SHIFT);
    Td->Dword0 |= ((Initializor->DelayInterrupt & OHCI_TD_DI_MASK) << OHCI_TD_DI_SHIFT);
    Td->Dword0 |= ((Initializor->DataToggle & OHCI_TD_T_MASK) << OHCI_TD_T_SHIFT);
    Td->Dword0 |= ((Initializor->ErrorCount & OHCI_TD_EC_MASK) << OHCI_TD_EC_SHIFT);
    Td->Dword0 |= ((Initializor->ConditionCode & OHCI_TD_CC_MASK) << OHCI_TD_CC_SHIFT);
    Td->Dword1 |= (Initializor->CurrentBufferPointer);
    Td->Dword2 |= (Initializor->CurrentBufferPointer & 0xFFFFFFF0);
    Td->Dword3 |= (Initializor->BufferEnd);

    LouPrint("OHCI.SYS:OhciInitializeTransferDescriptor() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS OhciCreateTD(
    POHCI_TRANSFER_DESCRIPTOR*  Td,
    POHCI_TD_INITIALIZOR        Initializor
){
    LouPrint("OHCI.SYS:OhciCreateTD()\n");

    

    LouPrint("OHCI.SYS:OhciCreateTD() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}