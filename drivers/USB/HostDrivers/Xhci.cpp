#include "Xhci.h"

void XhciInterruptHandler(uint64_t UsbHostData){
    LouPrint("XhciInterruptHandler()\n");
    while(1);
}

LOUSTATUS XhciResetHostController(PUSB_HOST_DEVICE HostDevice){

    LOUSTATUS Status;
    PXHCI_DEVICE XhciDevice = LouKeUsbHostDeviceToXhciDevice(HostDevice);
    PXHCI_OPERATIONAL_REGISTERS OpRegs = XhciDevice->OperationalRegisters;
    UINT32 Tmp = OpRegs->UsbCommand;
    Tmp |= XHCI_USBCMD_HCRST;
    OpRegs->UsbCommand = Tmp;

    Status = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer(&OpRegs->UsbStatus),
        1000,
        XHCI_USBSTS_CNR,
        0
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:XhciResetHostController() CNR Did Not Clear\n");
        while(1);
    }

    Status = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer(&OpRegs->UsbCommand),
        1000,
        XHCI_USBCMD_HCRST,
        0
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:XhciResetHostController() HCRST Did Not Clear\n");
        while(1);
    }
    if(XhciDevice->Capabilities.MaxScratchpageBufs && !XhciDevice->VirtualScratchpadAddress){
        Status = XhciAllocateDmaMemory(XhciDevice, XhciDevice->Capabilities.MaxScratchpageBufs * OpRegs->PageSize, 64, &XhciDevice->VirtualScratchpadAddress);
        if(Status != STATUS_SUCCESS){
            LouPrint("XHCI.SYS:XhciResetHostController():Unable To Allocate Scratchpad Buffer\n");
            while(1);
        }
    }
    if(XhciDevice->Capabilities.MaxScratchpageBufs && !XhciDevice->VirtualScratchpadArrayAddress){
        Status = XhciAllocateDmaMemory(XhciDevice, XhciDevice->Capabilities.MaxScratchpageBufs * sizeof(UINT64), 64, &XhciDevice->VirtualScratchpadArrayAddress);
        if(Status != STATUS_SUCCESS){
            LouPrint("XHCI.SYS:XhciResetHostController():Unable To Allocate Scratchpad Array Buffer\n");
            while(1);
        }
    }

    UINT64 ScratchpadDma = 0x00; 
    UINT64 ScratchpadArrayDma = 0x00; 
    if(XhciDevice->VirtualScratchpadAddress && XhciDevice->VirtualScratchpadArrayAddress){
        ScratchpadDma = XhciGetDmaAddress(XhciDevice->VirtualScratchpadAddress);
        for(SIZE i = 0 ; i < XhciDevice->Capabilities.MaxScratchpageBufs; i++){
            ((UINT64*)XhciDevice->VirtualScratchpadArrayAddress)[i] = ScratchpadDma + (i + GET_XHCI_PAGE_SIZE(OpRegs->PageSize));
        }
        ScratchpadArrayDma = XhciGetDmaAddress(XhciDevice->VirtualScratchpadArrayAddress);
    }
    
    if(!XhciDevice->VirtualDcbaapAddress){
        Status = XhciAllocateDmaMemory(XhciDevice, XHCI_DEVICE_CONTEXT_BASE_ADDRESS_ARRAY_ALLOCATION_SIZE(XhciDevice->Capabilities.MaxSlots), 64, &XhciDevice->VirtualDcbaapAddress);//round up to page size
        if(Status != STATUS_SUCCESS){
            LouPrint("XHCI.SYS:XhciResetHostController() Unable To Allocate Dcbaa\n");
            while(1);
        }
    }

    ((UINT64*)XhciDevice->VirtualDcbaapAddress)[0] = ScratchpadArrayDma; 

    UINT64 DcbaaDma = XhciGetDmaAddress(XhciDevice->VirtualDcbaapAddress);

    OpRegs->Dcbaap = DcbaaDma;

    Tmp = OpRegs->Config;
    Tmp &= ~(XHCI_CONFIG_MAX_SLOTS_EN);
    Tmp |= ((XhciDevice->Capabilities.MaxSlots & XHCI_CONFIG_MAX_SLOTS_EN_MASK) << XHCI_CONFIG_MAX_SLOTS_EN_SHIFT);
    OpRegs->Config = Tmp;

    XhciAllocateDmaMemory(XhciDevice, XHCI_COMMAND_RING_SEGMENT_SIZE, XHCI_COMMAND_RING_SEGMENT_BOUNDRY, &XhciDevice->VirtualCommandRingAddress);
    if(!XhciDevice->VirtualCommandRingAddress){
        LouPrint("XHCI.SYS:XhciResetHostController():Unable To Allocate CRCR Register\n");
        while(1);
    }
    UINT64 CrcrDma = XhciGetDmaAddress(XhciDevice->VirtualCommandRingAddress);
    Tmp = OpRegs->Crcr;
    Tmp &= ~(XHCI_CRCR_CRP);
    Tmp |= CrcrDma & XHCI_CRCR_CRP;
    OpRegs->Crcr = Tmp;

    XhciAllocateDmaMemory(XhciDevice, XHCI_EVENT_RING_SEGMENT_TABLE_SIZE, XHCI_EVENT_RING_SEGMENT_TABLE_ALIGNMENT, &XhciDevice->VirtualErstbaAddress);

    PXHCI_ERDP_VA_POINTER XhciErdp = LouKeMallocType(XHCI_ERDP_VA_POINTER, KERNEL_GENERIC_MEMORY);
    XhciErdp->TableEntry = (PXHCI_EVENT_RING_SEGMENT_TABLE_ENTRY)XhciDevice->VirtualErstbaAddress;
    XhciAllocateDmaMemory(XhciDevice, XHCI_EVENT_RING_SEGMENT_SIZE , XHCI_EVENT_RING_SEGMENT_BOUNDRY, &XhciErdp->VirtualErdp);
    if(!XhciErdp->VirtualErdp){
        LouPrint("XHCI.SYS:XhciResetHostController():Unable To Allocate Event Ring Register\n");
        while(1);
    }
    UINT64 ErdpDma = XhciGetDmaAddress(XhciErdp->VirtualErdp);
    XhciErdp->TableEntry->SegmentBuffer = ErdpDma;
    XhciErdp->TableEntry->SegmentSize = 4096;

    PXHCI_RUNTIME_REGISTERS RunRegs = XhciDevice->RuntimeRegisters;

    RunRegs->Irqx[0].Erstba = XhciGetDmaAddress(XhciDevice->VirtualErstbaAddress);
    RunRegs->Irqx[0].Erstsz = 1;
    RunRegs->Irqx[0].Erdp = ErdpDma;
    RunRegs->Irqx[0].Imod = 4000;
    RunRegs->Irqx[0].Iman = XHCI_INT_REG_IMAN_IP;
    
    Tmp = OpRegs->UsbCommand;
    Tmp |= XHCI_USBCMD_INTE;
    OpRegs->UsbCommand = Tmp;

    LouPrint("XHCI.SYS:XhciResetHostController():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS XhciStopHostController(PUSB_HOST_DEVICE HostDevice){
    LouPrint("XHCI.SYS:XhciStopHostController()\n");
    LOUSTATUS Status;
    PXHCI_DEVICE XhciDevice = LouKeUsbHostDeviceToXhciDevice(HostDevice);
    PXHCI_OPERATIONAL_REGISTERS OpRegs = XhciDevice->OperationalRegisters;
    UINT32 Tmp = OpRegs->UsbCommand;
    Tmp &= ~(XHCI_USBCMD_RUN_STOP);
    OpRegs->UsbCommand = Tmp;

    Status = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer(&OpRegs->UsbStatus),
        1000,
        XHCI_USBSTS_HCH,
        XHCI_USBSTS_HCH
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:XhciStopHostController():HCH Timeout\n");
        return Status;
    }

    LouPrint("XHCI.SYS:XhciStopHostController():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS XhciStartHostController(PUSB_HOST_DEVICE HostDevice){
    LouPrint("XHCI.SYS:XhciStartHostController()\n");
    LOUSTATUS Status;
    PXHCI_DEVICE XhciDevice = LouKeUsbHostDeviceToXhciDevice(HostDevice);
    PXHCI_OPERATIONAL_REGISTERS OpRegs = XhciDevice->OperationalRegisters;
    UINT32 Tmp = OpRegs->UsbCommand;
    Tmp |= XHCI_USBCMD_RUN_STOP;
    OpRegs->UsbCommand = Tmp;

    Status = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer(&OpRegs->UsbStatus),
        1000,
        XHCI_USBSTS_HCH,
        0
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("XHCI.SYS:XhciStartHostController():HCH Timeout\n");
        return Status;
    }

    LouPrint("XHCI.SYS:XhciStartHostController():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS XhciProbeRootHub(PUSB_HOST_DEVICE HostDevice){

    LouPrint("XhciProbeRootHub()\n");
    while(1);   
    return STATUS_SUCCESS;
}

LOUSTATUS XhciCommitRequest(PUSB_HOST_IO_PACKET IoPacket){

    LouPrint("XhciCommitRequest()\n");
    while(1);
    return STATUS_SUCCESS;
}