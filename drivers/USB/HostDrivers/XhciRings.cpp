#include "Xhci.h"

LOUSTATUS XhciInitializeRingManager(
    PXHCI_DEVICE        XhciDevice,
    PXHCI_RING_MANAGER  RingManager,
    SIZE                RingMembers,
    SIZE                RingAlignment
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
    LouKeSetAtomicBoolean(&RingManager->RingFull, false);
    MutexUnlock(&RingManager->RingLock);
    RingManager->RingEnqueuePointer = 0;
    if(RingManager->VirtualRing){
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

    XhciEncodeLinkTrb(
        (PXHCI_LINK_TRB)&RingManager->VirtualRing[RingMembers],
        (UINT64)(UINT8*)&RingManager->PhysicalRing[0],
        0,
        1,
        1,
        0,
        0
    );
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
    return XhciInitializeRingManager(
        XhciDevice,
        &XhciDevice->CommandRingManager,
        256,
        64
    );
}