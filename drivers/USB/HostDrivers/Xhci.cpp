#include "Xhci.h"

static LOUSTATUS _XhciStopHcdDevice(PUSB_HCD_OBJECT HcdDevice){
    PXHCI_DEVICE XhciDevice = (PXHCI_DEVICE)HcdDevice->HcdPrivateData;
    UINT32 UsbCommand = XhciDevice->OperationalRegisters->UsbCommand;    
    UsbCommand &= ~(XHCI_USBCMD_RUN_STOP);
    XhciDevice->OperationalRegisters->UsbCommand = UsbCommand;
    sleep(2);
    return LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer((PVOID)&XhciDevice->OperationalRegisters->UsbStatus),
        10,
        XHCI_USBSTS_HCH,
        XHCI_USBSTS_HCH
    );
}

LOUSTATUS XhciInterruptHandler(UINT64 Data){
    //TODO Expand on this to be more usefull
    PXHCI_DEVICE XhciDevice = (PXHCI_DEVICE)(UINT8*)Data;
    UINT32 UsbStatus = XhciDevice->OperationalRegisters->UsbStatus;
    if(!(UsbStatus & XHCI_USBSTS_EINT)){
        return STATUS_SUCCESS;
    }
    PXHCI_RUNTIME_REGISTERS Runtime = XhciDevice->RuntimeRegisters;
    Runtime->Irqx[0].Iman = 1;
    UsbStatus = XHCI_USBSTS_EINT;
    XhciDevice->OperationalRegisters->UsbStatus = UsbStatus;
    return STATUS_SUCCESS;
}

LOUSTATUS XhciResetHcdDevice(PUSB_HCD_OBJECT HcdDevice){
    LouPrint("XHCI.SYS:XhciResetHcdDevice()\n");
    LOUSTATUS Status = _XhciStopHcdDevice(HcdDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("XhciResetHcdDevice():Unable To Stop The HCD\n");
        while(1);
    }
    PXHCI_DEVICE XhciDevice = (PXHCI_DEVICE)HcdDevice->HcdPrivateData;
    UINT32 Tmp32;
    UINT32 UsbCommand = XhciDevice->OperationalRegisters->UsbCommand;
    UsbCommand |= XHCI_USBCMD_HCRST;
    XhciDevice->OperationalRegisters->UsbCommand = UsbCommand;
    sleep(2);
    Status = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer((PVOID)&XhciDevice->OperationalRegisters->UsbCommand),
        500,
        XHCI_USBCMD_HCRST,
        0
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("XhciResetHcdDevice():Unable To Reset HCD\n");
        while(1);
    }
    Status = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer((PVOID)&XhciDevice->OperationalRegisters->UsbStatus),
        500,
        XHCI_USBSTS_CNR,
        0
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("XhciResetHcdDevice():Unable To Reset HCD\n");
        while(1);
    }
    Status = XhciResetCommandRing(XhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("XhciResetHcdDevice():Unable To Reset Command Ring\n");
        while(1);
    }
    Status = XhciResetEventRing(XhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("XhciResetHcdDevice():Unable To Reset Event Ring\n");
        while(1);
    }
    Tmp32 = XhciDevice->OperationalRegisters->Config;
    Tmp32 &= ~(XHCI_CONFIG_MAX_SLOTS_EN);
    Tmp32 |= ((XhciDevice->Capabilities.MaxSlots & XHCI_CONFIG_MAX_SLOTS_EN_MASK) << XHCI_CONFIG_MAX_SLOTS_EN_SHIFT);
    XhciDevice->OperationalRegisters->Config = Tmp32;

    XhciDevice->OperationalRegisters->Dcbaap = XhciGetDmaAddress(XhciDevice->VirtualDcbaapAddress);
    XhciDevice->OperationalRegisters->Crcr = (UINT64)(UINT8*)&XhciDevice->CommandRingManager.PhysicalRing[0];

    PXHCI_EVENT_RING_SEGMENT_TABLE_ENTRY Table = (PXHCI_EVENT_RING_SEGMENT_TABLE_ENTRY)XhciDevice->VirtualErstbaAddress;
    XhciDevice->RuntimeRegisters->Irqx[0].Erstsz = 1;
    XhciDevice->RuntimeRegisters->Irqx[0].Erdp = Table->SegmentBuffer;
    XhciDevice->RuntimeRegisters->Irqx[0].Erstba = XhciGetDmaAddress(Table);

    UsbCommand = XhciDevice->OperationalRegisters->UsbCommand;
    UsbCommand |= XHCI_USBCMD_INTE; 
    XhciDevice->OperationalRegisters->UsbCommand = UsbCommand;

    Tmp32 = XhciDevice->RuntimeRegisters->Irqx[0].Iman;
    Tmp32 |= XHCI_INT_REG_IMAN_IE;
    XhciDevice->RuntimeRegisters->Irqx[0].Iman = Tmp32;
    
    LouKeMemoryBarrier();

    //LouPrint("XHCI.SYS:DCBAAP:%h\n", XhciDevice->OperationalRegisters->Dcbaap);
    //LouPrint("XHCI.SYS:CRCR  :%h\n", XhciDevice->OperationalRegisters->Crcr);
    //LouPrint("XHCI.SYS:ERSTBA:%h\n", XhciDevice->RuntimeRegisters->Irqx[0].Erstba);
    //LouPrint("XHCI.SYS:ERSTSZ:%h\n", XhciDevice->RuntimeRegisters->Irqx[0].Erstsz);
    //LouPrint("XHCI.SYS:ERDP  :%h\n", XhciDevice->RuntimeRegisters->Irqx[0].Erdp);

    LouPrint("XHCI.SYS:XhciResetHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}


LOUSTATUS XhciStartHcdDevice(PUSB_HCD_OBJECT HcdObject){
    LouPrint("XHCI.SYS:XhciStartHcdDevice()\n");
    LOUSTATUS Status;
    PXHCI_DEVICE XhciDevice = (PXHCI_DEVICE)HcdObject->HcdPrivateData;
    UINT32 UsbCommand = XhciDevice->OperationalRegisters->UsbCommand; 
    UsbCommand |= XHCI_USBCMD_RUN_STOP;
    XhciDevice->OperationalRegisters->UsbCommand = UsbCommand;
    Status = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer((PVOID)&XhciDevice->OperationalRegisters->UsbStatus),
        500,
        XHCI_USBSTS_HCH,
        0
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:XhciStartHcdDevice():Failed To Start Controller\n");
        while(1);
    }

    LouPrint("XHCI.SYS:XhciStartHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS XhciStopHcdDevice(PUSB_HCD_OBJECT HcdObject){
    LouPrint("XHCI.SYS:XhciStopHcdDevice()\n");
    while(1);
    LouPrint("XHCI.SYS:XhciStopHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS XhciHcdCreateEndpoint(PUSB_HCD_OBJECT Hcd, PUSB_ENDPOINT_OBJECT NewEndpoint){
    LouPrint("XHCI.SYS:XhciHcdCreateEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciHcdDestroyEndpoint(PUSB_ENDPOINT_OBJECT Endpoint){
    LouPrint("XHCI.SYS:XhciHcdDestroyEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}

RHPORT_STATUS XhciGetHcdRhPortStatus(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("XHCI.SYS:XhciGetHcdRhPortStatus()\n");
    while(1);
    return RHPORT_STATUS_NEEDS_RESET;
}

LOUSTATUS XhciResetRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("XHCI.SYS:XhciResetRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciStartRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("XHCI.SYS:XhciStartRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciStopRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("XHCI.SYS:XhciStopRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciPrepTransfer(PUSB_TRANSFER_DATA Transfer){
    LouPrint("XHCI.SYS:XhciPrepTransfer()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciCommitTransfer(PUSB_TRANSFER_DATA Transfer){
    LouPrint("XHCI.SYS:XhciCommitTransfer()\n");
    while(1);
    return STATUS_SUCCESS;
}
