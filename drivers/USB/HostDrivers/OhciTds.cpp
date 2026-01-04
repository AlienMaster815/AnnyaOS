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
    Td->Dword2 |= (Initializor->NextTD & 0xFFFFFFF0);
    Td->Dword3 |= (Initializor->BufferEnd);

    LouPrint("OHCI.SYS:OhciInitializeTransferDescriptor() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS OhciCreateTD(
    POHCI_TRANSFER_DESCRIPTOR*  TransferDescriptor,
    POHCI_TD_INITIALIZOR        Initializor
){
    LouPrint("OHCI.SYS:OhciCreateTD()\n");
    if((!TransferDescriptor) || (!Initializor)){
        LouPrint("OHCI.SYS:Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }

    LOUSTATUS Status;
    POHCI_TRANSFER_DESCRIPTOR Td;
    PVOID Out;

    Status = OhciAllocateDma(
        sizeof(OHCI_TRANSFER_DESCRIPTOR), 
        16, 
        &Out
    );
    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Could Not Allocate TD\n");
        return Status;
    }

    Td = (POHCI_TRANSFER_DESCRIPTOR)Out;
    *TransferDescriptor = Td;

    Status = OhciInitializeTransferDescriptor(
        Td,
        Initializor
    );
    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Could Not Initialize Descriptor\n");
        return Status;
    }

    LouPrint("OHCI.SYS:OhciCreateTD() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

void TraverseAndAddTd(
    POHCI_TRANSFER_DESCRIPTOR   Td,
    POHCI_TD_LIST               TdList
){
    while(TdList->Peers.NextHeader){
        TdList = (POHCI_TD_LIST)TdList->Peers.NextHeader;
    }
    TdList->Peers.NextHeader = (PListHeader)LouKeMallocType(OHCI_TD_LIST, KERNEL_GENERIC_MEMORY);
    ((POHCI_TD_LIST)TdList->Peers.NextHeader)->Peers.LastHeader = (PListHeader)TdList;
    UINT32 DmaAddress = OhciGetDmaAddress(Td);
    POHCI_TRANSFER_DESCRIPTOR LastTd = (POHCI_TRANSFER_DESCRIPTOR)TdList->Td;

    if(LastTd){
        LastTd->Dword2 &=  ~(0xFFFFFFF0); 
        LastTd->Dword2 |=  DmaAddress & 0xFFFFFFF0;
    }

    TdList = (POHCI_TD_LIST)TdList->Peers.NextHeader;
    TdList->Td = (PVOID)Td;
}

LOUSTATUS OhciCreateSetupTD(
    PUSB_HOST_IO_PACKET     IoPacket,
    POHCI_ED_LIST           EdItem
){  
    LouPrint("OHCI.SYS:OhciCreateSetupTD()\n");

    PVOID Out;
    LOUSTATUS Status = OhciAllocateDma(8, 16, &Out);
    POHCI_TRANSFER_INFO SetUp = (POHCI_TRANSFER_INFO)Out;

    SetUp->RequestType = IoPacket->RequestType;
    SetUp->Request = IoPacket->Request;
    SetUp->Value = IoPacket->Value;
    SetUp->Index = IoPacket->Index;
    SetUp->Length = IoPacket->Length;

    UINT32 Cbp = OhciGetDmaAddress(SetUp);
    UINT32 Be = Cbp + 7;

    OHCI_TD_INITIALIZOR Initializor = {0};

    Initializor.BufferRounding = 1;
    Initializor.DirectionPID = OHCI_TD_DIRECTION_SETUP;
    Initializor.CurrentBufferPointer = Cbp;
    Initializor.BufferEnd = Be;

    POHCI_TRANSFER_DESCRIPTOR Td;
    
    Status = OhciCreateTD(
        &Td,
        &Initializor
    );

    TraverseAndAddTd(
        Td,
        &EdItem->Tds
    );
    
    LouPrint("OHCI.SYS:OhciCreateSetupTD() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

static void InitializeDataTD(
    PUSB_HOST_IO_PACKET     IoPacket,
    POHCI_ED_LIST           EdItem,
    POHCI_TD_INITIALIZOR    Initializor,
    UINT16                  Index, 
    UINT16                  Length
){
    PUSB_FUNCTION_DEVICE FunctionDevice = IoPacket->FunctionDevice;
    POHCI_IO_PACKET_PRIVATE_DATA IoData = (POHCI_IO_PACKET_PRIVATE_DATA)FunctionDevice->PrivateHostFunctionData;
    UINT32 DmaAddress = OhciGetDmaAddress(IoData->DmaOut);

    DmaAddress += Index;

    if(Initializor->DirectionPID == OHCI_TD_DIRECTION_OUT){
        memcpy(
            (PVOID)((UINT64)IoData->DmaOut + (UINT64)Index), 
            (PVOID)((UINT64)IoPacket->Data + (UINT64)Index), 
            Length
        );
    }

    Initializor->CurrentBufferPointer = DmaAddress;
    Initializor->BufferEnd = DmaAddress + (Length - 1);

    POHCI_TRANSFER_DESCRIPTOR Td;
    
    OhciCreateTD(
        &Td,
        Initializor
    );

    TraverseAndAddTd(
        Td,
        &EdItem->Tds
    );

}

LOUSTATUS OhciCreateDataTDs(
    PUSB_HOST_IO_PACKET     IoPacket,
    POHCI_ED_LIST           EdItem
){
    LouPrint("OHCI.SYS:OhciCreateDataTDs()\n");

    LOUSTATUS Status;
    PUSB_FUNCTION_DEVICE FunctionDevice;
    POHCI_IO_PACKET_PRIVATE_DATA IoData;
    UINT16 i;
    OHCI_TD_INITIALIZOR Initializor = {0};

    if((!IoPacket->Data) || (!IoPacket->Length)){
        goto _OHCI_DATA_TD_SKIP;
    }
    
    FunctionDevice = IoPacket->FunctionDevice;
    IoData = (POHCI_IO_PACKET_PRIVATE_DATA)FunctionDevice->PrivateHostFunctionData;
    
    Status = OhciAllocateDma(IoPacket->Length, 16 , &IoData->DmaOut);
    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Unable To Allocate DMA\n");
        return Status;
    }

    Initializor.DataToggle = 1; //DATA1
    Initializor.DirectionPID = ((IoPacket->RequestType & (USB_XFER_D2H << USB_REQUEST_XFER_DIRECTION_SHIFT)) ? OHCI_TD_DIRECTION_IN : OHCI_TD_DIRECTION_OUT);

    for(
        i = 0; 
        (IoPacket->Length - i) > FunctionDevice->MaxPacketSize;
        i += FunctionDevice->MaxPacketSize
    ){

        InitializeDataTD(
            IoPacket,
            EdItem,
            &Initializor,
            i,
            FunctionDevice->MaxPacketSize
        );

        Initializor.DataToggle = 2;//CARRY : Im using redundancy for simplicity here

    }

    InitializeDataTD(
        IoPacket,
        EdItem,
        &Initializor,
        i,
        IoPacket->Length - i
    );

    _OHCI_DATA_TD_SKIP:
    LouPrint("OHCI.SYS:OhciCreateDataTDs() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS OhciCreateStatusTD(
    PUSB_HOST_IO_PACKET     IoPacket,
    POHCI_ED_LIST           EdItem
){
    LouPrint("OHCI.SYS:OhciCreateStatusTD()\n");

    LouPrint("OHCI.SYS:OhciCreateStatusTD() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}