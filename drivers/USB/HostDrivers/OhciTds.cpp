#include "OHCI.h"

static UINT8 OhciGetTdBufferRounding(POHCI_TRANSFER_DESCRIPTOR Td){
    return (UINT8)((Td->Dword0 >> OHCI_TD_R_SHIFT) & OHCI_TD_R_MASK);
}

static void OhciSetTdBufferRounding(POHCI_TRANSFER_DESCRIPTOR Td, UINT8 Value){
    Td->Dword0 &= ~(OHCI_TD_R_MASK << OHCI_TD_R_SHIFT);
    Td->Dword0 |= ((Value & OHCI_TD_R_MASK) << OHCI_TD_R_SHIFT);
}

static UINT8 OhciGetTdDirectionAndPid(POHCI_TRANSFER_DESCRIPTOR Td){
    return  (UINT8)((Td->Dword0 >> OHCI_TD_DP_SHIFT) & OHCI_TD_DP_MASK);
}

static void OhciSetTdDirectionAndPid(POHCI_TRANSFER_DESCRIPTOR Td, UINT8 Value){
    Td->Dword0 &= ~(OHCI_TD_DP_MASK << OHCI_TD_DP_SHIFT);
    Td->Dword0 |= ((Value & OHCI_TD_DP_MASK) << OHCI_TD_DP_SHIFT);
}

static UINT8 OhciGetTdDelayInterrupt(POHCI_TRANSFER_DESCRIPTOR Td){
    return (UINT8)((Td->Dword0 >> OHCI_TD_DI_SHIFT) & OHCI_TD_DI_MASK);
}

static void OhciSetTdDelayInterrupt(POHCI_TRANSFER_DESCRIPTOR Td, UINT8 Value){
    Td->Dword0 &= ~(OHCI_TD_DI_MASK << OHCI_TD_DI_SHIFT);
    Td->Dword0 |= ((Value & OHCI_TD_DI_MASK) << OHCI_TD_DI_SHIFT);
}

static UINT8 OhciGetTdDataToggle(POHCI_TRANSFER_DESCRIPTOR Td){
    return (UINT8)((Td->Dword0 >> OHCI_TD_T_SHIFT) & OHCI_TD_T_MASK);
}

static void OhciSetTdDataToggle(POHCI_TRANSFER_DESCRIPTOR Td, UINT8 Value){
    Td->Dword0 &= ~(OHCI_TD_T_MASK << OHCI_TD_T_SHIFT);
    Td->Dword0 |= ((Value & OHCI_TD_T_MASK) << OHCI_TD_T_SHIFT);
}

static UINT8 OhciGetTdErrorCount(POHCI_TRANSFER_DESCRIPTOR Td){
    return (UINT8)((Td->Dword0 >> OHCI_TD_EC_SHIFT) & OHCI_TD_EC_MASK);
}

static void OhciSetTdErrorCount(POHCI_TRANSFER_DESCRIPTOR Td, UINT8 Value){
    Td->Dword0 &= ~(OHCI_TD_EC_MASK << OHCI_TD_EC_SHIFT);
    Td->Dword0 |= ((Value & OHCI_TD_EC_MASK) << OHCI_TD_EC_SHIFT);
}

static UINT8 OhciGetTdConditionCode(POHCI_TRANSFER_DESCRIPTOR Td){
    return (UINT8)((Td->Dword0 >> OHCI_TD_CC_SHIFT) & OHCI_TD_CC_MASK); 
}

static void OhciSetTdConditionCode(POHCI_TRANSFER_DESCRIPTOR Td, UINT8 Value){
    Td->Dword0 &= ~(OHCI_TD_CC_MASK << OHCI_TD_CC_SHIFT);
    Td->Dword0 |= ((Value & OHCI_TD_CC_MASK) << OHCI_TD_CC_SHIFT);
}

static UINT32 OhciGetTdCurrentBufferPointer(POHCI_TRANSFER_DESCRIPTOR Td){
    return Td->Dword1;
}

static void OhciSetTdCurrentBufferPointer(POHCI_TRANSFER_DESCRIPTOR Td, UINT32 Address){
    Td->Dword1 = Address;
}

static UINT32 OhciGetTdNextTd(POHCI_TRANSFER_DESCRIPTOR Td){
    return Td->Dword2 & 0xFFFFFFF0;
}

static void OhciSetTdNextTd(POHCI_TRANSFER_DESCRIPTOR Td, UINT32 Address){
    Td->Dword2 = Address & 0xFFFFFFF0;
}

static UINT32 OhciGetTdBufferEnd(POHCI_TRANSFER_DESCRIPTOR Td){
    return Td->Dword3;
}

static void OhciSetTdBufferEnd(POHCI_TRANSFER_DESCRIPTOR Td, UINT32 Address){
    Td->Dword3 = Address;
}

LOUSTATUS OhciInitializeTransferDescriptor(
    POHCI_TRANSFER_DESCRIPTOR   Td,
    POHCI_TD_INITIALIZOR        Initializor
){
    //LouPrint("OHCI.SYS:OhciInitializeTransferDescriptor()\n");
    if((!Td) || (!Initializor)){
        LouPrint("OHCI.SYS:Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }

    memset(Td, 0, sizeof(OHCI_TRANSFER_DESCRIPTOR));

    OhciSetTdBufferRounding(Td, Initializor->BufferRounding);
    OhciSetTdDirectionAndPid(Td, Initializor->DirectionPID);
    OhciSetTdDelayInterrupt(Td, Initializor->DelayInterrupt);
    OhciSetTdDataToggle(Td, Initializor->DataToggle);
    OhciSetTdErrorCount(Td, Initializor->ErrorCount);
    OhciSetTdConditionCode(Td, Initializor->ConditionCode);
    OhciSetTdCurrentBufferPointer(Td, Initializor->CurrentBufferPointer);
    OhciSetTdNextTd(Td, Initializor->NextTD);
    OhciSetTdBufferEnd(Td, Initializor->BufferEnd);

    //LouPrint("OHCI.SYS:OhciInitializeTransferDescriptor() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS OhciCreateTD(
    POHCI_TRANSFER_DESCRIPTOR*  TransferDescriptor,
    POHCI_TD_INITIALIZOR        Initializor
){
    //LouPrint("OHCI.SYS:OhciCreateTD()\n");
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
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:Could Not Allocate TD\n");
        return Status;
    }

    Td = (POHCI_TRANSFER_DESCRIPTOR)Out;
    *TransferDescriptor = Td;

    Status = OhciInitializeTransferDescriptor(
        Td,
        Initializor
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:Could Not Initialize Descriptor\n");
        return Status;
    }

    //LouPrint("OHCI.SYS:OhciCreateTD() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

void TraverseAndAddTd(
    POHCI_TRANSFER_DESCRIPTOR   Td,
    POHCI_TD_LIST               TdList,
    POHCI_TD_LIST*              TdOut
){
    while(TdList->Peers.NextHeader){
        TdList = (POHCI_TD_LIST)TdList->Peers.NextHeader;
    }
    TdList->Peers.NextHeader = (PListHeader)LouKeMallocType(OHCI_TD_LIST, KERNEL_GENERIC_MEMORY);
    ((POHCI_TD_LIST)TdList->Peers.NextHeader)->Peers.LastHeader = (PListHeader)TdList;
    UINT32 DmaAddress = OhciGetDmaAddress(Td);
    POHCI_TRANSFER_DESCRIPTOR LastTd = (POHCI_TRANSFER_DESCRIPTOR)TdList->Td;

    if(LastTd){
        OhciSetTdNextTd(LastTd, DmaAddress);
    }

    TdList = (POHCI_TD_LIST)TdList->Peers.NextHeader;
    TdList->Td = (PVOID)Td;
    if(TdOut){
        *TdOut = TdList;
    }
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
    Initializor.ConditionCode = 0xF;

    POHCI_TRANSFER_DESCRIPTOR Td;
    Status = OhciCreateTD(
        &Td,
        &Initializor
    );

    POHCI_TD_LIST TdOut;

    TraverseAndAddTd(
        Td,
        &EdItem->Tds,
        &TdOut
    );

    TdOut->DmaVAddress = (PVOID)SetUp;
    TdOut->DmaSize = 8;

    EdItem->TdCount++;
    
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
    Initializor->ConditionCode = 0xF;

    POHCI_TRANSFER_DESCRIPTOR Td;
    
    OhciCreateTD(
        &Td,
        Initializor
    );

    POHCI_TD_LIST TdOut;

    TraverseAndAddTd(
        Td,
        &EdItem->Tds,
        &TdOut
    );

    TdOut->DmaVAddress = (PVOID)((UINT64)IoData->DmaOut + (UINT64)Index);
    TdOut->DmaSize = Length;

    EdItem->TdCount++;
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
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:Unable To Allocate DMA\n");
        return Status;
    }

    Initializor.DataToggle = 1; //DATA1
    Initializor.DirectionPID = ((IoPacket->RequestType & (USB_XFER_D2H << USB_REQUEST_XFER_DIRECTION_SHIFT)) ? OHCI_TD_DIRECTION_IN : OHCI_TD_DIRECTION_OUT);
    Initializor.ConditionCode = 0xF;

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

    OHCI_TD_INITIALIZOR Initializor = {0};
    // STATUS stage always uses DATA1
    Initializor.DataToggle = 1;

    Initializor.CurrentBufferPointer = 0;
    Initializor.BufferEnd = 0;
    Initializor.ConditionCode = 0xF;


    if(IoPacket->Length == 0){
        Initializor.DirectionPID = OHCI_TD_DIRECTION_IN;
    } else {
        if(IoPacket->RequestType & (USB_XFER_D2H << USB_REQUEST_XFER_DIRECTION_SHIFT)){
            Initializor.DirectionPID = OHCI_TD_DIRECTION_OUT;
        } else {
            Initializor.DirectionPID = OHCI_TD_DIRECTION_IN;
        }
    }

    POHCI_TRANSFER_DESCRIPTOR Td;
    LOUSTATUS Status = OhciCreateTD(
        &Td,
        &Initializor
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:Failed to create STATUS TD\n");
        return Status;
    }

    POHCI_TD_LIST TdOut;

    TraverseAndAddTd(
        Td,
        &EdItem->Tds,
        &TdOut
    );

    TdOut->DmaVAddress = 0x00;
    TdOut->DmaSize = 0x00;

    EdItem->TdCount++;


    LouPrint("OHCI.SYS:OhciCreateStatusTD() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS
OhciCreateDummyTD(
    POHCI_ED_LIST EdItem
){
    OHCI_TD_INITIALIZOR Initializor;

    Initializor.BufferRounding = 0;
    Initializor.DirectionPID  = 0;
    Initializor.DelayInterrupt = 0;
    Initializor.DataToggle = 0;
    Initializor.ErrorCount = 0;
    Initializor.ConditionCode = 0xF;
    Initializor.CurrentBufferPointer = 0;
    Initializor.NextTD = 0;
    Initializor.BufferEnd = 0;

    POHCI_TRANSFER_DESCRIPTOR Td;
    LOUSTATUS Status = OhciCreateTD(&Td, &Initializor);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    POHCI_TD_LIST TdOut;

    TraverseAndAddTd(
        Td,
        &EdItem->Tds,
        &TdOut
    );

    TdOut->DmaVAddress = 0x00;
    TdOut->DmaSize = 0x00;

    EdItem->TdCount++;

    return STATUS_SUCCESS;
}



void OhciDestroySetupTD(PUSB_HOST_IO_PACKET IoPacket, POHCI_ED_LIST EdItem){

    POHCI_TD_LIST SetupTd = (POHCI_TD_LIST)EdItem->Tds.Peers.NextHeader;
    POHCI_TRANSFER_DESCRIPTOR Td = (POHCI_TRANSFER_DESCRIPTOR)SetupTd->Td;
    UINT8 Cc = OhciGetTdConditionCode(Td);

    if(Cc){
        LouPrint("CC Error Code:%h\n", Cc);
        while(1);
    }
    IoPacket->ConditionCode = Cc;
    EdItem->Tds.Peers.NextHeader = SetupTd->Peers.NextHeader;
    EdItem->TdCount--;

    if(SetupTd->DmaVAddress){
        OhciFreeDma(SetupTd->DmaVAddress);
        SetupTd->DmaVAddress = 0x00;
        SetupTd->DmaSize = 0x00;
    }

    if(SetupTd->Td){
        OhciFreeDma(SetupTd->Td);
    }

    LouKeFree(SetupTd);

}

void OhciDestroyDataTDs(PUSB_HOST_IO_PACKET IoPacket, POHCI_ED_LIST EdItem){
    POHCI_TD_LIST DataTD = (POHCI_TD_LIST)EdItem->Tds.Peers.NextHeader;
    POHCI_TRANSFER_DESCRIPTOR Td = (POHCI_TRANSFER_DESCRIPTOR)DataTD->Td;
    POHCI_IO_PACKET_PRIVATE_DATA IoData = (POHCI_IO_PACKET_PRIVATE_DATA)IoPacket->FunctionDevice->PrivateHostFunctionData;

    if(IoPacket->RequestType & (USB_XFER_D2H << USB_REQUEST_XFER_DIRECTION_SHIFT)){
        memcpy(
            (PVOID)((UINT64)IoPacket->Data), 
            (PVOID)((UINT64)IoData->DmaOut), 
            IoPacket->Length
        );
    }

    while(((POHCI_TD_LIST)DataTD->Peers.NextHeader)->Peers.NextHeader){
        if(OhciGetTdConditionCode(Td) || OhciGetTdCurrentBufferPointer(Td)){
            LouPrint("CC :%h\n", OhciGetTdConditionCode(Td));
            LouPrint("CBP:%h\n", OhciGetTdCurrentBufferPointer(Td));
        }

        if(DataTD->Td){
            OhciFreeDma(DataTD->Td);
        }

        LouKeFree(DataTD);

        DataTD = (POHCI_TD_LIST)DataTD->Peers.NextHeader;
        EdItem->Tds.Peers.NextHeader = (PListHeader)DataTD;
        EdItem->TdCount--;
        POHCI_TRANSFER_DESCRIPTOR Td = (POHCI_TRANSFER_DESCRIPTOR)DataTD->Td;
    }

    OhciFreeDma(IoData->DmaOut);

}

static void DestroyTDHelper(POHCI_ED_LIST EdItem){
    POHCI_TD_LIST TdList = (POHCI_TD_LIST)EdItem->Tds.Peers.NextHeader;
    POHCI_TRANSFER_DESCRIPTOR Td = (POHCI_TRANSFER_DESCRIPTOR)TdList->Td;

    EdItem->Tds.Peers.NextHeader = TdList->Peers.NextHeader;
    EdItem->TdCount--;

    if(TdList->DmaVAddress){
        OhciFreeDma(TdList->DmaVAddress);
        TdList->DmaVAddress = 0x00;
        TdList->DmaSize = 0x00;
    }

    if(TdList->Td){
        OhciFreeDma(TdList->Td);
    }

    LouKeFree(TdList);
    
}

void OhciDestroyStatusTD(POHCI_ED_LIST EdItem){
    DestroyTDHelper(EdItem);
}

void OhciDestroyDummyTD(POHCI_ED_LIST EdItem){
    DestroyTDHelper(EdItem);
}