#include "Xhci.h"

static void XhciEncodeTrbData(
    PXHCI_GENERIC_TRB   Trb,
    UINT32              DWord0,
    UINT32              DWord1,
    UINT32              DWord2,
    UINT32              DWord3
){
    Trb->DWord[0] = DWord0;
    Trb->DWord[1] = DWord1;
    Trb->DWord[2] = DWord2;
    LouKeMemoryBarrier();
    Trb->DWord[3] = DWord3;
}

void 
XhciEncodeNoOpTrb(
    PXHCI_NO_OP_TRB NoOpTrb,
    UINT16          InterrupterTarget,
    UINT8           CycleBit,
    UINT8           EvaluateNextTrb,
    UINT8           ChainBit,
    UINT8           InterruptOnCompletion
){
    XhciEncodeTrbData(
        (PXHCI_GENERIC_TRB)NoOpTrb,
        0, 0,
        (InterrupterTarget & XHCI_NO_OP_TRB_INTERRUPT_TARGET_MASK) << XHCI_NO_OP_TRB_INTERRUPT_TARGET_SHIFT,
        ((CycleBit & XHCI_NO_OP_TRB_CYCLE_BIT_MASK) << XHCI_NO_OP_TRB_CYCLE_BIT_SHIFT) | ((EvaluateNextTrb & XHCI_NO_OP_TRB_ENT_MASK) << XHCI_NO_OP_TRB_ENT_SHIFT) | ((ChainBit & XHCI_NO_OP_TRB_CH_MASK) << XHCI_NO_OP_TRB_CH_SHIFT) | ((InterruptOnCompletion & XHCI_NO_OP_TRB_IOC_MASK) << XHCI_NO_OP_TRB_IOC_SHIFT) | (XHCI_TRB_TYPE_NO_OP << XHCI_NO_OP_TRB_TYPE_SHIFT)  
    );
}

void  
XhciEncodeLinkTrb(
    PXHCI_LINK_TRB  LinkTrb,
    UINT64          RingSegmentPointer,
    UINT16          InterrupterTarget,
    UINT8           CycleBit,
    UINT8           ToggleCycle,
    UINT8           ChainBit,
    UINT8           InterruptOnCompletion
){
    XhciEncodeTrbData(
        (PXHCI_GENERIC_TRB)LinkTrb,
        RingSegmentPointer & UINT32_MAX, 
        (RingSegmentPointer >> 32) & UINT32_MAX,
        (InterrupterTarget & XHCI_LINK_TRB_INTERRUPTER_TARGET_MASK) << XHCI_LINK_TRB_INTERRUPTER_TARGET_SHIFT,
        ((CycleBit & XHCI_LINK_TRB_CYCLE_BIT_MASK) << XHCI_LINK_TRB_CYCLE_BIT_SHIFT) | ((ToggleCycle & XHCI_LINK_TRB_TOGGLE_BIT_MASK) << XHCI_LINK_TRB_TOGGLE_BIT_SHIFT) | ((ChainBit & XHCI_LINK_TRB_CHAIN_BIT_MASK) << XHCI_LINK_TRB_CHAIN_BIT_SHIFT) | ((InterruptOnCompletion & XHCI_LINK_TRB_IOC_MASK) << XHCI_LINK_TRB_IOC_SHIFT) | (XHCI_TRB_TYPE_LINK_TRB << XHCI_LINK_TRB_TRB_TYPE_SHIFT)
    );
}