//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "OHCI.h"

LOUSTATUS 
OhciInitialzeHcca(
    PUSB_HCD_OBJECT HcdObject
){
    POHCI_DEVICE OhciDevice = (POHCI_DEVICE)HcdObject->HcdPrivateData;
    if(OhciDevice->HccaAddress){
        return STATUS_SUCCESS;
    }

    POHCI_OPERATIONAL_REGISTERS OpReg = OhciDevice->OperationalRegisters;
    UINT64 PhyAddress;
    LOUSTATUS Status;
    PVOID Out;
        
    Status = OhciAllocateDma(HcdObject, 256, 256, &Out);
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:Unable To Allocate HCCA Memory\n");
        return Status;
    }
    OhciDevice->HccaAddress = (UINT64)(UINT8*)Out;
    OhciDevice->OperationalRegisters->HcHCCA = OhciGetDmaAddress((PVOID)(UINT8*)OhciDevice->HccaAddress);
    return STATUS_SUCCESS;
}


LOUSTATUS OhciInitializeDefaultControl(
    PUSB_HCD_OBJECT HcdObject
){
    LouPrint("OHCI.SYS:OhciInitializeLists()\n");
    POHCI_DEVICE OhciDevice = (POHCI_DEVICE)HcdObject->HcdPrivateData;
    if(OhciDevice->DefaultControlEd){
        return STATUS_SUCCESS;
    }
    LOUSTATUS Status;
    UINT32 DmaAddress;
    OHCI_ED_INITIALIZOR Initializor = {0};
    POHCI_ENDPOINT_DESCRIPTOR EdOut;
    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;

    Initializor.FunctionAddress = 0;
    Initializor.EndpointNumber = 0;
    Initializor.Direction = OHCI_ED_DIRECTION_GFTD0;
    Initializor.MaximumPacketSize = 8;
    Initializor.Skip = 1;

    Status = OhciCreateControlED(
        HcdObject,
        &EdOut,
        &Initializor
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:Could Not Add Default Control ED\n");
        return Status;
    }
    OhciDevice->DefaultControlEd = EdOut;
    DmaAddress = OhciGetDmaAddress(EdOut);
    OpRegs->HcControlHeadED = DmaAddress;

    LouPrint("OHCI.SYS:OhciInitializeLists() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}


LOUSTATUS OhciResetHcdDevice(PUSB_HCD_OBJECT HcdObject){
    LouPrint("OHCI.SYS:OhciResetHcdDevice()\n");
    LOUSTATUS       Status;
    UINT32          Fm;
    UINT16          FrameInterval;
    UINT16          PeriodicStart;
    POHCI_DEVICE    OhciDevice = (POHCI_DEVICE)HcdObject->HcdPrivateData;

    Status = OhciInitializeDefaultControl(HcdObject);
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:Error Initializing Lists\n");
        return STATUS_SUCCESS;
    }

    OhciDevice->Fminterval = OhciDevice->OperationalRegisters->HcFmInterval;
    OhciDevice->OperationalRegisters->HcCommandStatus |= OHCI_COMMAND_STATUS_HCR;

    Status = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer((PVOID)&OhciDevice->OperationalRegisters->HcCommandStatus),
        10,
        OHCI_COMMAND_STATUS_HCR,
        0
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:Ohci Controller Hung On Reset\n");
        return STATUS_IO_DEVICE_ERROR;
    }

    OhciDevice->OperationalRegisters->HcFmInterval = OhciDevice->Fminterval;
    
    LouKIRQL Irql;
    LouKeRaiseIrql(HIGH_LEVEL, &Irql);
    OhciDevice->OperationalRegisters->HcControl = SET_OHCI_CONTROL_HCFS(OhciDevice->OperationalRegisters->HcControl, OHCI_HCFS_USBRESET);
    sleep(10);
    OhciDevice->OperationalRegisters->HcControl = SET_OHCI_CONTROL_HCFS(OhciDevice->OperationalRegisters->HcControl , OHCI_HCFS_USBRESUME);
    sleep(10);
    LouKeLowerIrql(Irql);

    if(OhciDevice->OperationalRegisters->HcCommandStatus & OHCI_COMMAND_STATUS_HCR){
        LouPrint("OHCI.SYS:ERROR:Host Re Entered Reset\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    else if(OhciDevice->OperationalRegisters->HcFmInterval != OhciDevice->Fminterval){
        LouPrint("OHCI.SYS:ERROR:Host Clock Stuck\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    else if(GET_OHCI_CONTROL_HCFS(OhciDevice->OperationalRegisters->HcControl) != OHCI_HCFS_USBRESUME){
        LouPrint("OHCI.SYS:ERROR:Host Did Not Re Enter Resume\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    LouPrint("OHCI.SYS:Host Initialized Successfully\n");

    OhciInitialzeHcca(HcdObject);
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:ERROR Unable To Initialize Device Data\n");
        return Status;
    }

    Fm = OhciDevice->OperationalRegisters->HcFmInterval;
    FrameInterval = Fm & 0x3FFF;   // mask bits 0–13
    PeriodicStart = (FrameInterval * 9) / 10;
    OhciDevice->OperationalRegisters->HcPeriodicStart = PeriodicStart;
    OhciDevice->OperationalRegisters->HcRhStatus |= OHCI_RH_STATUS_LPSC;

    OhciDevice->OperationalRegisters->HcControl = SET_OHCI_CONTROL_HCFS(OhciDevice->OperationalRegisters->HcControl , OHCI_HCFS_USBOPERATIONAL);

    if(GET_OHCI_CONTROL_HCFS(OhciDevice->OperationalRegisters->HcControl) != OHCI_HCFS_USBOPERATIONAL){
        LouPrint("OHCI.SYS:ERROR:Host Did Not Become Operational\n");
        return STATUS_IO_DEVICE_ERROR;
    }
        
    LouPrint("OHCI.SYS:OhciResetHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS OhciStartHcdDevice(PUSB_HCD_OBJECT HcdObject){
    LouPrint("OHCI.SYS:OhciStartHcdDevice()\n");
    LOUSTATUS                   Status;
    POHCI_DEVICE                OhciDevice = (POHCI_DEVICE)HcdObject->HcdPrivateData;
    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;

    if(GET_OHCI_CONTROL_HCFS(OpRegs->HcControl) == OHCI_HCFS_USBSUSPEND){
        OpRegs->HcControl = SET_OHCI_CONTROL_HCFS(OpRegs->HcControl, OHCI_HCFS_USBOPERATIONAL);
        Status = LouKeWaitForUlongRegisterConditionMs(
            (PULONG)LouKeCastToUnalignedPointer((PVOID)&OpRegs->HcControl),
            10,
            OHCI_CONTROL_HCFS,
            OHCI_HCFS_USBOPERATIONAL
        );
        if(Status != STATUS_SUCCESS){
            LouPrint("OHCI.SYS:ERROR Unable To Set Host To Operational State\n");
            return Status;
        }
    }else if(GET_OHCI_CONTROL_HCFS(OpRegs->HcControl) != OHCI_HCFS_USBOPERATIONAL){
        LouPrint("OHCI.SYS:ERROR Function Given An Invalid Controller State\n");
        return STATUS_INVALID_PARAMETER;
    }

    if((!OpRegs->HcFmInterval) || (!OpRegs->HcPeriodicStart)){
        LouPrint("OHCI.SYS:Fatal Controller Error\n"); //this is initialized in controller reset if its 0 here then there was a critical error
        return STATUS_IO_DEVICE_ERROR;
    }

        UINT32 IoMask = 0;

    if(OhciDevice->ControlEDs.Peers.NextHeader){
        OpRegs->HcControlHeadED = OhciGetDmaAddress(((POHCI_ED_LIST)OhciDevice->ControlEDs.Peers.NextHeader)->Ed);
        IoMask |= OHCI_CONTROL_CLE;
    } 
    if(OpRegs->HcBulkHeadED){
        IoMask |= OHCI_CONTROL_BLE;
    }

    OpRegs->HcControl |= IoMask | OHCI_CONTROL_PLE;// | OHCI_CONTROL_IE;

    LouPrint("OHCI.SYS:OhciStartHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}


LOUSTATUS OhciStopHcdDevice(PUSB_HCD_OBJECT HcdObject){
    LouPrint("OHCI.SYS:OhciStopHcdDevice()\n");
    POHCI_DEVICE OhciDevice = (POHCI_DEVICE)HcdObject->HcdPrivateData;
    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;    
    UINT32 Tmp;
    LOUSTATUS Status;
    
    OpRegs->HcInterruptDisable = 0xFFFFFFFF;
    OpRegs->HcInterruptStatus = 0xFFFFFFFF;

    LouKIRQL Irql;
    LouKeRaiseIrql(HIGH_LEVEL, &Irql);

    Tmp = OpRegs->HcControl;
    Tmp &= ~(OHCI_CONTROL_CLE | OHCI_CONTROL_BLE | OHCI_CONTROL_PLE | OHCI_CONTROL_IE);
    OpRegs->HcControl = Tmp;

    sleep(20);

    OpRegs->HcControl = SET_OHCI_CONTROL_HCFS(OpRegs->HcControl , OHCI_HCFS_USBSUSPEND);

    Status = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer((PVOID)&OpRegs->HcControl),
        10,
        OHCI_CONTROL_HCFS,
        OHCI_HCFS_USBSUSPEND
    );
    LouKeLowerIrql(Irql);

    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:OhciStopHcdDevice():Unable To Stop Host Conroller\n");
        return  Status;
    }
    LouPrint("OHCI.SYS:OhciStopHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS OhciHcdCreateEndpoint(PUSB_HCD_OBJECT Hcd, PUSB_ENDPOINT_OBJECT NewEndpoint){
    UINT8                   UsbAddress = UsbCoreGetEndpointDeviceAddress(NewEndpoint);
    UINT8                   EndpointID = UsbCoreGetEndpointId(NewEndpoint);
    UINT8                   PipeType = UsbCoreGetEndpointsPipeType(NewEndpoint);
    USB_ENDPOINT_DIRECTION  Direction = NewEndpoint->Direction;




    LouPrint("OhciHcdCreateEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS OhciHcdDestroyEndpoint(PUSB_ENDPOINT_OBJECT Endpoint){
    LouPrint("OhciHcdDestroyEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS OhciHcdChangeEndpointPacketSize(PUSB_ENDPOINT_OBJECT Endpoint, SIZE PacketSize){
    LouPrint("OhciHcdChangeEndpointPacketSize()\n");    
    while(1)
    return STATUS_SUCCESS;
}


SIZE OhciGetHcdRhPortCount(PUSB_HCD_OBJECT Hcd){
    LouPrint("OhciGetHcdRhPortCount():HERE\n");
    while(1);
}

RHPORT_STATUS OhciGetHcdRhPortStatus(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("OhciGetHcdRhPortStatus\n");
    while(1);
    return RHPORT_STATUS_NEEDS_RESET;
}

LOUSTATUS OhciResetRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("OhciResetRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS OhciStartRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("OhciStartRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS OhciStopRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("OhciStopRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS OhciPrepTransfer(PUSB_TRANSFER_OBJECT Transfer){
    LouPrint("OhciPrepTransfer()\n");
    while(1);
    return STATUS_SUCCESS;
}


LOUSTATUS OhciCommitTransfer(PUSB_TRANSFER_OBJECT Transfer){
    LouPrint("OhciCommitTransfer()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS OhciGetTransferStatus(PUSB_TRANSFER_OBJECT Transfer){
    LouPrint("OhciGetTransferStatus()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS OhciCleanupTransfer(PUSB_TRANSFER_OBJECT Transfer){
    LouPrint("OhciCleanupTransfer()\n");
    while(1);
    return STATUS_SUCCESS;
}
