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

LOUSTATUS OhciCreateED(
    POHCI_ENDPOINT_DESCRIPTOR*  EndpointDescriptor,
    POHCI_ED_INITIALIZOR        Initializor
){
    LOUSTATUS Status;
    LouPrint("OHCI.SYS:OhciCreateED()\n");
    if((!EndpointDescriptor) || (!Initializor)){
        LouPrint("OHCI.SYS:Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }
    
    PVOID                       Out;
    POHCI_ENDPOINT_DESCRIPTOR   Ed;
    
    Status = OhciAllocateDma(
        sizeof(OHCI_ENDPOINT_DESCRIPTOR),
        16,
        &Out
    );
    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Unable To Allocate Memory\n");
        return Status;
    }
    Ed = (POHCI_ENDPOINT_DESCRIPTOR)Out;
    *EndpointDescriptor = Ed;

    Status = OhciInitializeEndpointDescriptor(
        Ed,
        Initializor
    );

    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Could Not Create ED\n");
        return Status;
    }

    LouPrint("OHCI.SYS:OhciCreateED() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

static void TraverseListAndAdd(
    POHCI_DEVICE                OhciDevice,
    POHCI_ED_LIST               EndpointList,
    UINT32                      IoMask,
    POHCI_ENDPOINT_DESCRIPTOR   Ed
){
    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;
    POHCI_ENDPOINT_DESCRIPTOR   LastEd;
    UINT32 Tmp = OpRegs->HcControl & IoMask;
    OpRegs->HcControl &= ~(IoMask);
    POHCI_ED_LIST EdList = EndpointList;
    UINT32 DmaAddress; 
    while(EdList->Peers.NextHeader){
        EdList = (POHCI_ED_LIST)EdList->Peers.NextHeader;
    }
    
    EdList->Peers.NextHeader = (PListHeader)LouKeMallocType(OHCI_ED_LIST, KERNEL_GENERIC_MEMORY);
    ((POHCI_ED_LIST)EdList->Peers.NextHeader)->Peers.LastHeader = (PListHeader)EdList;
    LastEd = (POHCI_ENDPOINT_DESCRIPTOR)EdList->Ed;
    
    EdList = (POHCI_ED_LIST)EdList->Peers.NextHeader;

    EdList->Ed = (PVOID)Ed;


    if(LastEd){
        DmaAddress = OhciGetDmaAddress((PVOID)Ed);
        LastEd->Dword3 = ((DmaAddress & (OHCI_ED_NEXTED_MASK)));
    }

    Ed->Dword3 = 0;

    OpRegs->HcControl |= Tmp;
}

static void AddToControlList(
    POHCI_DEVICE                OhciDevice,
    POHCI_ENDPOINT_DESCRIPTOR   Ed
){
    TraverseListAndAdd(
        OhciDevice,
        &OhciDevice->ControlEDs,
        OHCI_CONTROL_CLE,
        Ed
    );
}

LOUSTATUS OhciCreateControlED(
    POHCI_DEVICE                OhciDevice,
    POHCI_ENDPOINT_DESCRIPTOR*  EdOut,
    POHCI_ED_INITIALIZOR        Initializor
){
    LOUSTATUS Status;

    LouPrint("OHCI.SYS:OhciCreateControlED()\n");

    if((!OhciDevice) || (!Initializor) || (!EdOut)){
        LouPrint("OHCI.SYS:Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }

    POHCI_ENDPOINT_DESCRIPTOR Ed;

    Status = OhciCreateED(
        &Ed,
        Initializor
    );

    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Could Not Create ED\n");
        return Status;
    }

    *EdOut = Ed;

    AddToControlList(
        OhciDevice,
        Ed
    );

    LouPrint("OHCI.SYS:OhciCreateControlED() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

static void AddToBulkList(
    POHCI_DEVICE                OhciDevice,
    POHCI_ENDPOINT_DESCRIPTOR   Ed
){
    TraverseListAndAdd(
        OhciDevice,
        &OhciDevice->BulkEDs,
        OHCI_CONTROL_BLE,
        Ed
    );
}

LOUSTATUS OhciCreateBulkED(
    POHCI_DEVICE                OhciDevice, 
    POHCI_ENDPOINT_DESCRIPTOR*  EdOut,
    POHCI_ED_INITIALIZOR        Initializor
){
    LOUSTATUS Status;

    LouPrint("OHCI.SYS:OhciCreateBulkED()\n");

    if((!OhciDevice) || (!Initializor)){
        LouPrint("OHCI.SYS:Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }

    POHCI_ENDPOINT_DESCRIPTOR Ed;

    Status = OhciCreateED(
        &Ed,
        Initializor
    );

    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Could Not Create ED\n");
        return Status;
    }

    *EdOut = Ed;

    AddToBulkList(
        OhciDevice,
        Ed
    );

    LouPrint("OHCI.SYS:OhciCreateBulkED() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

static void AddToIsochIntList(
    POHCI_DEVICE                OhciDevice,
    POHCI_ENDPOINT_DESCRIPTOR   Ed,
    UINT8                       Vector
){
    TraverseListAndAdd(
        OhciDevice,
        &OhciDevice->IsochIntEDs[Vector],
        (OHCI_CONTROL_IE | OHCI_CONTROL_PLE),
        Ed
    );
}

LOUSTATUS OhciCreateIsochIntED(
    POHCI_DEVICE                OhciDevice, 
    POHCI_ENDPOINT_DESCRIPTOR*  EdOut,
    POHCI_ED_INITIALIZOR        Initializor,
    UINT8                       Vector
){
    LOUSTATUS Status;

    LouPrint("OHCI.SYS:OhciCreateIsochIntED()\n");

    if((!OhciDevice) || (!Initializor)){
        LouPrint("OHCI.SYS:Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }

    POHCI_ENDPOINT_DESCRIPTOR Ed;

    Status = OhciCreateED(
        &Ed,
        Initializor
    );

    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Could Not Create ED\n");
        return Status;
    }

    *EdOut = Ed;

    AddToIsochIntList(
        OhciDevice,
        Ed,
        Vector
    );

    LouPrint("OHCI.SYS:OhciCreateIsochIntED() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

static POHCI_ED_LIST FindEDHead(
    POHCI_ED_LIST ListItem
){
    while(ListItem->Peers.LastHeader){
        ListItem = (POHCI_ED_LIST)ListItem->Peers.LastHeader;
    }
    
    return ListItem;
}

static void OhciTraversAndUnlinkED(
    POHCI_DEVICE    OhciDevice,
    POHCI_ED_LIST   ListItem,
    UINT32          IoMask
){

    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;
    UINT32 Tmp = OpRegs->HcControl & IoMask;
    OpRegs->HcControl &= ~(IoMask);

    POHCI_ED_LIST LastItem, NextItem;
    POHCI_ENDPOINT_DESCRIPTOR LastED, NextED;

    LastItem = (POHCI_ED_LIST)ListItem->Peers.LastHeader;
    NextItem = (POHCI_ED_LIST)ListItem->Peers.NextHeader;
    
    LastED = (POHCI_ENDPOINT_DESCRIPTOR)LastItem->Ed;


    if((LastED) && (NextItem)){ //Last Item will always exist but not Next Item
        NextED = (POHCI_ENDPOINT_DESCRIPTOR)NextItem->Ed; //if next item exist so does an ED only the anchor dosent have an ED
        UINT32 DmaAddress = OhciGetDmaAddress((PVOID)NextED);
        LastED->Dword3 = (DmaAddress & OHCI_ED_NEXTED_MASK);
    }else if(LastED){
        LastED->Dword3 = 0;
    }

    LastItem->Peers.NextHeader = (PListHeader)NextItem;
    if(NextItem){
        NextItem->Peers.LastHeader = (PListHeader)LastItem;
    }    

    OpRegs->HcControl |= Tmp;
}

LOUSTATUS OhciDestroyED(
    POHCI_DEVICE    OhciDevice,
    POHCI_ED_LIST   ListItem
){
    LouPrint("OHCI.SYS:OhciDestroyED()\n");

    POHCI_ED_LIST ListHead = FindEDHead(ListItem);
    UINT32 IoMask;

    if(ListHead == &OhciDevice->ControlEDs){
        IoMask = OHCI_CONTROL_CLE;
    }else if(ListHead == &OhciDevice->BulkEDs){
        IoMask = OHCI_CONTROL_BLE;
    }
    else{
        for(size_t i = 0; i < 32; i++){
            if(ListHead == &OhciDevice->IsochIntEDs[i]){
                IoMask = (OHCI_CONTROL_IE | OHCI_CONTROL_PLE);
                //i dont trust breaks in this compiler, deal with it
                goto _INTERRUPT_LIST_FOUND;
            }
        }
        LouPrint("OHCI.SYS:Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }
    _INTERRUPT_LIST_FOUND:

    OhciTraversAndUnlinkED(
        OhciDevice,
        ListItem,
        IoMask
    );

    OhciFreeDma((PVOID)ListItem->Ed);
    LouKeFree(ListItem);

    LouPrint("OHCI.SYS:OhciDestroyED() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}