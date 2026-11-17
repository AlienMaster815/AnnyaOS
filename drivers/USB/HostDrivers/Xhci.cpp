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
    XhciDevice->OperationalRegisters->Crcr = (UINT64)(UINT8*)&XhciDevice->CommandRingManager.PhysicalRing[0] | 1;

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

LOUSTATUS XhciHcdCreateEndpoint(PUSB_HCD_OBJECT HcdObject, PUSB_ENDPOINT_OBJECT NewEndpoint){
    UINT8 DeviceAddress = UsbCoreGetEndpointDeviceAddress(NewEndpoint);
    if(!DeviceAddress){
        return STATUS_SUCCESS;
    }
    UINT8 EndpointID = UsbCoreGetEndpointId(NewEndpoint);
    if(!EndpointID){
        return STATUS_SUCCESS;
    }



    LouPrint("XHCI.SYS:XhciHcdCreateEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciHcdDestroyEndpoint(PUSB_ENDPOINT_OBJECT Endpoint){
    UINT8 DeviceAddress = UsbCoreGetEndpointDeviceAddress(Endpoint);
    if(!DeviceAddress){
        return STATUS_SUCCESS;
    }
    UINT8 EndpointID = UsbCoreGetEndpointId(Endpoint);
    if(!EndpointID){
        return STATUS_SUCCESS;
    }



    LouPrint("XHCI.SYS:XhciHcdDestroyEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}

SIZE XhciGetHcdRhPortCount(PUSB_HCD_OBJECT HcdObject){
    PXHCI_DEVICE XhciDevice = (PXHCI_DEVICE)HcdObject->HcdPrivateData;
    return XhciDevice->Capabilities.MaxPorts;
}   

RHPORT_STATUS XhciGetHcdRhPortStatus(PUSB_HCD_OBJECT HcdObject, UINT32 Port){
    if(Port >= XhciGetHcdRhPortCount(HcdObject)){
        return RHPORT_STATUS_NO_DEVICE;
    }
    PXHCI_DEVICE XhciDevice = (PXHCI_DEVICE)HcdObject->HcdPrivateData;
    UINT32 PortSc = XhciDevice->OperationalRegisters->Ports[Port].PortStatusControl; 
    UINT32 Pls;

    if(!(PortSc & XHCI_PORTSC_CSS)){
        return RHPORT_STATUS_NO_DEVICE;
    }

    if(!(PortSc & XHCI_PORTSC_PED)){
        return RHPORT_STATUS_NEEDS_RESET;
    }
    Pls = ((PortSc >> XHCI_PORTSC_PLS_SHIFT) & XHCI_PORTSC_PLS_MASK); 
    if(Pls == XHCI_PLS_U0_STATE){
        return RHPORT_STATUS_RUNNING;
    }

    if((Pls >= XHCI_PLS_U1_STATE) && (Pls <= XHCI_PLS_U3_STATE)){
        return RHPORT_STATUS_IDLE;
    } 

    return RHPORT_STATUS_NEEDS_RESET;
}

LOUSTATUS XhciResetRhPort(PUSB_HCD_OBJECT HcdObject, UINT32 Port){
    if(Port >= XhciGetHcdRhPortCount(HcdObject)){
        return STATUS_NO_SUCH_DEVICE;
    }
    PXHCI_DEVICE XhciDevice = (PXHCI_DEVICE)HcdObject->HcdPrivateData;
    PULONG PortScReg = (PULONG)LouKeCastToUnalignedPointer((PVOID)&XhciDevice->OperationalRegisters->Ports[Port].PortStatusControl); 
    ULONG PortSc = *PortScReg;    
    if(!(PortSc & XHCI_PORTSC_CSS)){
        return STATUS_NO_SUCH_DEVICE;
    }
    PortSc = (PortSc & XHCI_PORTSC_PRESERVE_MASK) | XHCI_PORTSC_PR | XHCI_PORTSC_PRC;
    *PortScReg = PortSc;

    LOUSTATUS Status = LouKeWaitForUlongRegisterConditionMs(
        PortScReg,
        5000,
        XHCI_PORTSC_PR | XHCI_PORTSC_PRC, 
        XHCI_PORTSC_PRC
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    *PortScReg = (((*PortScReg) & XHCI_PORTSC_PRESERVE_MASK) | XHCI_PORTSC_PRC);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciStartRhPort(PUSB_HCD_OBJECT HcdObject, UINT32 Port){
    if(Port >= XhciGetHcdRhPortCount(HcdObject)){
        return STATUS_NO_SUCH_DEVICE;
    }
    PXHCI_DEVICE XhciDevice = (PXHCI_DEVICE)HcdObject->HcdPrivateData;
    PULONG PortScReg = (PULONG)LouKeCastToUnalignedPointer((PVOID)&XhciDevice->OperationalRegisters->Ports[Port].PortStatusControl);
    ULONG PortSc = *PortScReg;

    if(!(PortSc & XHCI_PORTSC_CSS)){
        return STATUS_NO_SUCH_DEVICE;
    }
    ULONG Pls = ((PortSc >> XHCI_PORTSC_PLS_SHIFT) & XHCI_PORTSC_PLS_MASK);
    if((PortSc & XHCI_PORTSC_PED) && (Pls == XHCI_PLS_U0_STATE)){
        return STATUS_SUCCESS;
    }
    if(!(PortSc & XHCI_PORTSC_PP)){
        *PortScReg = (PortSc & XHCI_PORTSC_PRESERVE_MASK) | XHCI_PORTSC_PP;
        LOUSTATUS Status = LouKeWaitForUlongRegisterConditionMs(
            PortScReg,
            100,
            XHCI_PORTSC_PP,
            XHCI_PORTSC_PP
        );
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        PortSc = *PortScReg;
        Pls = ((PortSc >> XHCI_PORTSC_PLS_SHIFT) & XHCI_PORTSC_PLS_MASK);
    }
    if((PortSc & XHCI_PORTSC_PED) && (Pls >= XHCI_PLS_U1_STATE) && (Pls <= XHCI_PLS_U3_STATE)){
        ULONG Next = (PortSc & (XHCI_PORTSC_PRESERVE_MASK & ~(XHCI_PORTSC_PLS_MASK << XHCI_PORTSC_PLS_SHIFT)));
        Next |= (XHCI_PLS_U0_STATE << XHCI_PORTSC_PLS_SHIFT) | XHCI_PORTSC_LWS;
        *PortScReg = Next;

        return LouKeWaitForUlongRegisterConditionMs(
            PortScReg,
            100,
            (XHCI_PORTSC_PLS_MASK << XHCI_PORTSC_PLS_SHIFT),
            (XHCI_PLS_U0_STATE << XHCI_PORTSC_PLS_SHIFT)
        );
    }
    return XhciResetRhPort(HcdObject, Port);
}

LOUSTATUS XhciStopRhPort(PUSB_HCD_OBJECT HcdObject, UINT32 Port){
    if(Port >= XhciGetHcdRhPortCount(HcdObject)){
        return STATUS_NO_SUCH_DEVICE;
    }
    PXHCI_DEVICE XhciDevice = (PXHCI_DEVICE)HcdObject->HcdPrivateData;
    PULONG PortScReg = (PULONG)LouKeCastToUnalignedPointer((PVOID)&XhciDevice->OperationalRegisters->Ports[Port].PortStatusControl);
    ULONG PortSc = *PortScReg;
    if(!(PortSc & XHCI_PORTSC_CSS)){
        return STATUS_NO_SUCH_DEVICE;
    }
    ULONG Pls = ((PortSc >> XHCI_PORTSC_PLS_SHIFT) & XHCI_PORTSC_PLS_MASK);
    if(!(PortSc & XHCI_PORTSC_PED) || (Pls == XHCI_PLS_U3_STATE)){
        return STATUS_SUCCESS;
    }
    ULONG Next = (PortSc & (XHCI_PORTSC_PRESERVE_MASK & ~XHCI_PORTSC_PLS));
    Next |= (XHCI_PLS_U3_STATE << XHCI_PORTSC_PLS_SHIFT) | XHCI_PORTSC_LWS;
    *PortScReg = Next;
    LOUSTATUS Status = LouKeWaitForUlongRegisterConditionMs(
        PortScReg,
        100,
        XHCI_PORTSC_PLS,
        (XHCI_PLS_U3_STATE << XHCI_PORTSC_PLS_SHIFT)
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    *PortScReg = ((*PortScReg) & XHCI_PORTSC_PRESERVE_MASK) | XHCI_PORTSC_PLC;
    return STATUS_SUCCESS;
}

LOUSTATUS XhciDeviceAllocateAddress(
    PUSB_HCD_OBJECT     HcdObject, 
    PUSB_DEVICE_OBJECT  Device
){
    PXHCI_DEVICE XhciDevice = (PXHCI_DEVICE)HcdObject->HcdPrivateData;
    UINT32 Slot;
    SIZE CtxSize = XhciDevice->Capabilities.Context64Byte ? 64 : 32;
    PXHCI_DEVICE_PRIVATE_DATA PrivateData = LouKeMallocType(XHCI_DEVICE_PRIVATE_DATA, KERNEL_GENERIC_MEMORY);
    UINT32 PortSc = XhciDevice->OperationalRegisters->Ports[Device->PortNumber].PortStatusControl;
    UINT32 PortSpeed = (PortSc >> 10) & 0xF;

    Device->PortSpeed = PortSpeed;
    Device->HcdPrivateData = (PVOID)PrivateData;

    LOUSTATUS Status = XhciAllocateTransferDmaMemory(XhciDevice, CtxSize * 32, 64, &PrivateData->SlotContextOutData);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    Status = XhciAllocateTransferDmaMemory(XhciDevice, CtxSize * 33, 64, &PrivateData->SlotContextInData);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    Status = XhciInitializeTransferRingManager(XhciDevice, PrivateData);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    Status = XhciEnableSlot(XhciDevice, &Slot);
    if(Status != STATUS_SUCCESS){
        LouPrint("XhciDeviceAllocateAddress():FAILED_ES\n");
        while(1);
    }

    PrivateData->SlotID = Slot;

    UINT64* Dcbaa = (UINT64*)(UINT8*)XhciDevice->VirtualDcbaapAddress;
    Dcbaa[Slot] = (UINT64)(UINT8*)XhciGetDmaAddress(PrivateData->SlotContextOutData);

    UINT32* InputCtrlCtx = (UINT32*)((UINT8*)PrivateData->SlotContextInData + (0 * CtxSize));
    UINT32* SlotCtx      = (UINT32*)((UINT8*)PrivateData->SlotContextInData + (1 * CtxSize));
    UINT32* Ep0Context   = (UINT32*)((UINT8*)PrivateData->SlotContextInData + (2 * CtxSize));

    InputCtrlCtx[0] = 0;
    InputCtrlCtx[1] = 0x3;

    SlotCtx[0] = (1 << 27) | (PortSpeed << 20);
    SlotCtx[1] = (((Device->PortNumber + 1) & 0xFF) << 16);

    UINT32 MaxPacketSize = 8;
    if(PortSpeed == 3){
        MaxPacketSize = 64;
    }
    else if(PortSpeed >= 4){
        MaxPacketSize = 512;
    }

    Ep0Context[1] = (MaxPacketSize << 16) | (4 << 3) | (3 << 1);

    UINT64 RingPhys = (UINT64)(UINT8*)&PrivateData->TransferRing.PhysicalRing[0];
    Ep0Context[2] = ((UINT32)(RingPhys & UINT32_MAX)) | 1;
    Ep0Context[3] = (UINT32)((RingPhys >> 32) & UINT32_MAX);
    Ep0Context[4] = 8;

    LouKeMemoryBarrier();

    TRB_RING_HANDLE RingHandle;
    TRB_RING_HANDLE EventHandle;
    UINT64 InputCtxPhys = (UINT64)(UINT8*)XhciGetDmaAddress(PrivateData->SlotContextInData);

    MutexLock(&XhciDevice->CommandRingManager.RingLock);
    MutexLock(&XhciDevice->EventRingManager.RingLock);

    Status = XhciAllocateCommandTrb(XhciDevice, &RingHandle);
    if(Status != STATUS_SUCCESS){
        LouPrint("XhciDeviceAllocateAddress():FAILED_ALLOC_TRB\n");
        while(1);
    }

    RingHandle.Trb->DWord[0] = (UINT32)(InputCtxPhys & UINT32_MAX);
    RingHandle.Trb->DWord[1] = (UINT32)((InputCtxPhys >> 32) & UINT32_MAX);
    RingHandle.Trb->DWord[2] = 0;
    RingHandle.Trb->DWord[3] = ((Slot & 0xFF) << 24) | (11 << 10) | (RingHandle.TrbCycleBit & 1);

    LouKeMemoryBarrier();
    XhciDevice->DoorbellRegisters->Doorbell[0] = 0;

_TRY_AGAIN:
    SIZE Timeout = 5000;
    Status = XhciGetNextEventTrb(XhciDevice, &EventHandle);
    while((Status != STATUS_SUCCESS) && (Timeout)){
        Status = XhciGetNextEventTrb(XhciDevice, &EventHandle);
        sleep(100);
        Timeout -= 100;
    }

    if(Status != STATUS_SUCCESS){
        LouPrint("XhciDeviceAllocateAddress():NO EVENT\n");
        while(1);
    }

    UINT8 TrbType = (EventHandle.Trb->DWord[3] >> 10) & 0x3F;
    if(TrbType != 33){
        goto _TRY_AGAIN;
    }

    UINT8 CompletionCode = (EventHandle.Trb->DWord[2] >> 24) & 0xFF;
    if(CompletionCode != 1){
        LouPrint("XhciDeviceAllocateAddress():BAD COMPLETION:%d\n", CompletionCode);
        while(1);
    }

    MutexUnlock(&XhciDevice->CommandRingManager.RingLock);
    MutexUnlock(&XhciDevice->EventRingManager.RingLock);

    UINT32* OutSlotCtx = (UINT32*)PrivateData->SlotContextOutData;
    UINT8 AssignedAddress = OutSlotCtx[3] & 0xFF;
    Device->DeviceAddress = AssignedAddress;

    return STATUS_SUCCESS;
}



LOUSTATUS XhciPrepTransfer(PUSB_TRANSFER_OBJECT Transfer){
    if(!Transfer->UsbDevice->DeviceAddress){
        return STATUS_INVALID_PARAMETER;
    }


    return STATUS_SUCCESS;
}

LOUSTATUS XhciCommitTransfer(PUSB_TRANSFER_OBJECT Transfer){
    if(!Transfer->UsbDevice->DeviceAddress){
        return STATUS_INVALID_PARAMETER;
    }


    return STATUS_SUCCESS;
}

LOUSTATUS XhciGetTransferStatus(PUSB_TRANSFER_OBJECT Transfer){
    if(!Transfer->UsbDevice->DeviceAddress){
        return STATUS_INVALID_PARAMETER;
    }


    return STATUS_NO_WORK_DONE;
}

LOUSTATUS XhciCleanupTransfer(PUSB_TRANSFER_OBJECT Transfer){
    if(!Transfer->UsbDevice->DeviceAddress){
        return STATUS_INVALID_PARAMETER;
    }

    return STATUS_SUCCESS;
}