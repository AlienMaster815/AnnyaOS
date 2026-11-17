#include "Xhci.h"



LOUSTATUS XhciInitializeRingManager(
    PXHCI_DEVICE        XhciDevice,
    PXHCI_RING_MANAGER  RingManager,
    SIZE                RingMembers,
    SIZE                RingAlignment,
    BOOLEAN             CreatingLinkAtEnd
){
    if(
        (!XhciDevice) || (!RingManager) || 
        (!RingMembers) || (!RingAlignment) || 
        (RingMembers > UINT8_MAX)
    ){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS   Status;
    UINT64      Tmp64;
    PVOID       TmpPvoid;
    RingManager->Pcs = 1;
    MutexUnlock(&RingManager->RingLock);
    RingManager->RingEnqueuePointer = 0;
    RingManager->CurrentUsedEntries = 0x00;
    RingManager->RingMembers = RingMembers;
    if(RingManager->VirtualRing){
        memset(RingManager->VirtualRing, 0, sizeof(XHCI_GENERIC_TRB) * RingMembers);
        if(CreatingLinkAtEnd){
            XhciEncodeLinkTrb(
                (PXHCI_LINK_TRB)&RingManager->VirtualRing[RingMembers - 1],
                (UINT64)(UINT8*)&RingManager->PhysicalRing[0],
                0,
                1,
                1,
                0,
                0
            );   
        }
        return STATUS_SUCCESS;
    }
    Status = XhciAllocateTransferDmaMemory(XhciDevice, sizeof(XHCI_GENERIC_TRB) * RingMembers, RingAlignment, &TmpPvoid);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    RingManager->VirtualRing = (PXHCI_GENERIC_TRB)(UINT8*)TmpPvoid;
    Status = RequestPhysicalAddress(
        (UINT64)(UINT8*)TmpPvoid,
        &Tmp64
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    RingManager->PhysicalRing = (PXHCI_GENERIC_TRB)(UINT8*)Tmp64;
    if(CreatingLinkAtEnd){
        XhciEncodeLinkTrb(
            (PXHCI_LINK_TRB)&RingManager->VirtualRing[RingMembers - 1],
            (UINT64)(UINT8*)&RingManager->PhysicalRing[0],
            0,
            1,
            1,
            0,
            0
        );   
    }
    return STATUS_SUCCESS;
}

LOUSTATUS 
XhciInitializeTransferRingManager(
    PXHCI_DEVICE                XhciDevice,
    PXHCI_DEVICE_PRIVATE_DATA   PrivateData
){    
    LOUSTATUS Status;
    if((!XhciDevice) || (!PrivateData)){
        return STATUS_INVALID_PARAMETER;
    }
    Status = XhciInitializeRingManager(
        XhciDevice,
        &PrivateData->TransferRing,
        0xFF,
        64,
        true
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    LouPrint("XHCI.SYS:New Transfer Ring:%h\n", &PrivateData->TransferRing.PhysicalRing[0]);
    return STATUS_SUCCESS;
}

LOUSTATUS 
XhciInitializeCommandRingManager(
    PXHCI_DEVICE XhciDevice
){
    LOUSTATUS Status;
    if(!XhciDevice){
        return STATUS_INVALID_PARAMETER;
    }
    Status = XhciInitializeRingManager(
        XhciDevice,
        &XhciDevice->CommandRingManager,
        0xFF,
        64,
        true
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    LouPrint("XHCI.SYS:New Command Ring:%h\n", &XhciDevice->CommandRingManager.PhysicalRing[0]);
    return STATUS_SUCCESS;  
}

LOUSTATUS 
XhciResetCommandRing(
    PXHCI_DEVICE    XhciDevice
){
    LOUSTATUS Status;
    if(!XhciDevice){
        return STATUS_INVALID_PARAMETER;
    }
    Status = XhciInitializeRingManager(
        XhciDevice,
        &XhciDevice->CommandRingManager,
        0xFF,
        64,
        true
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    LouPrint("XHCI.SYS:Reset Command Ring:%h\n", &XhciDevice->CommandRingManager.PhysicalRing[0]);
    return STATUS_SUCCESS;
}



LOUSTATUS XhciAllocateCommandTrb(
    PXHCI_DEVICE        XhciDevice,
    PTRB_RING_HANDLE    TrbHandle
){
    if((!XhciDevice) || (!TrbHandle)){
        return STATUS_INVALID_PARAMETER;
    }
    if((XhciDevice->CommandRingManager.RingMembers - 1) == XhciDevice->CommandRingManager.RingEnqueuePointer){
        XhciEncodeLinkTrb(
            (PXHCI_LINK_TRB)&XhciDevice->CommandRingManager.VirtualRing[XhciDevice->CommandRingManager.RingMembers - 1],
            (UINT64)(UINT8*)&XhciDevice->CommandRingManager.PhysicalRing[0],
            0,
            XhciDevice->CommandRingManager.Pcs,
            1,
            0,
            0
        );  
        XhciDevice->CommandRingManager.Pcs = (XhciDevice->CommandRingManager.Pcs + 1) % 2;
        XhciDevice->CommandRingManager.RingEnqueuePointer = 0;
    }
    TrbHandle->RingEntry = XhciDevice->CommandRingManager.RingEnqueuePointer;
    TrbHandle->TrbCycleBit = XhciDevice->CommandRingManager.Pcs;
    TrbHandle->Trb = (PXHCI_GENERIC_TRB)&XhciDevice->CommandRingManager.VirtualRing[XhciDevice->CommandRingManager.RingEnqueuePointer++];
    return STATUS_SUCCESS;
}

LOUSTATUS XhciGetNextEventTrb(
    PXHCI_DEVICE        XhciDevice,
    PTRB_RING_HANDLE    TrbHandle
){
    if((!XhciDevice) || (!TrbHandle)){
        return STATUS_INVALID_PARAMETER;
    }
    if(XhciDevice->EventRingManager.RingMembers == XhciDevice->EventRingManager.RingEnqueuePointer){
        XhciDevice->EventRingManager.Pcs = (XhciDevice->EventRingManager.Pcs + 1) % 2;
        XhciDevice->EventRingManager.RingEnqueuePointer = 0;
    }
    PXHCI_GENERIC_TRB Trb = (PXHCI_GENERIC_TRB)&XhciDevice->EventRingManager.VirtualRing[XhciDevice->EventRingManager.RingEnqueuePointer];
    if(((Trb->DWord[3] >> XHCI_NORMAL_TRB_CYCLE_BIT_SHIFT) & XHCI_NORMAL_TRB_CYCLE_BIT_MASK) != XhciDevice->EventRingManager.Pcs){
        return STATUS_NO_WORK_DONE;
    }
    TrbHandle->RingEntry = XhciDevice->EventRingManager.RingEnqueuePointer;
    TrbHandle->TrbCycleBit = XhciDevice->EventRingManager.Pcs;
    TrbHandle->Trb = Trb;
    XhciDevice->EventRingManager.RingEnqueuePointer++;

    SIZE NextIndex = XhciDevice->EventRingManager.RingEnqueuePointer % XhciDevice->EventRingManager.RingMembers;
    UINT64 NewErdp = (UINT64)(UINT8*)&XhciDevice->EventRingManager.PhysicalRing[NextIndex];
    XhciDevice->RuntimeRegisters->Irqx[0].Erdp = NewErdp | (1ULL << 3);
    return STATUS_SUCCESS;
}

LOUSTATUS
XhciInitializeEventRingManager(
    PXHCI_DEVICE    XhciDevice
){
    LOUSTATUS Status;
    if(!XhciDevice){
        return STATUS_INVALID_PARAMETER;
    }
    Status = XhciInitializeRingManager(
        XhciDevice,
        &XhciDevice->EventRingManager,
        0xFF,
        64,
        false
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    PXHCI_EVENT_RING_SEGMENT_TABLE_ENTRY Table = (PXHCI_EVENT_RING_SEGMENT_TABLE_ENTRY)XhciDevice->VirtualErstbaAddress;
    Table->SegmentBuffer = (UINT64)(UINT8*)&XhciDevice->EventRingManager.PhysicalRing[0]; 
    Table->SegmentSize = 0xFF;
    LouKeMemoryBarrier();
    LouPrint("XHCI.SYS:New Event Segment Buffer:%h\n", Table->SegmentBuffer);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciResetEventRing(PXHCI_DEVICE XhciDevice){
    LOUSTATUS Status;
    if(!XhciDevice){
        return STATUS_INVALID_PARAMETER;
    }
    Status = XhciInitializeRingManager(
        XhciDevice,
        &XhciDevice->EventRingManager,
        0xFF,
        64,
        false
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    PXHCI_EVENT_RING_SEGMENT_TABLE_ENTRY Table = (PXHCI_EVENT_RING_SEGMENT_TABLE_ENTRY)XhciDevice->VirtualErstbaAddress;
    Table->SegmentBuffer = (UINT64)(UINT8*)&XhciDevice->EventRingManager.PhysicalRing[0]; 
    Table->SegmentSize = 0xFF;
    LouKeMemoryBarrier();
    LouPrint("XHCI.SYS:Reset Event Segment Buffer:%h\n", Table->SegmentBuffer);
    return STATUS_SUCCESS;
}


 