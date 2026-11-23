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
    POHCI_ED_LIST               EdHandleOut;
    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;

    Initializor.FunctionAddress = 0;
    Initializor.EndpointNumber = 0;
    Initializor.Direction = OHCI_ED_DIRECTION_GFTD0;
    Initializor.MaximumPacketSize = 8;
    Initializor.Skip = 1;

    Status = OhciCreateControlED(
        HcdObject,
        &EdHandleOut,
        &Initializor
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:Could Not Add Default Control ED\n");
        return Status;
    }
    OhciDevice->DefaultControlEd = (POHCI_ENDPOINT_DESCRIPTOR)EdHandleOut->Ed;
    DmaAddress = OhciGetDmaAddress(EdHandleOut->Ed);
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

LOUSTATUS OhciHcdCreateEndpoint(PUSB_HCD_OBJECT HcdObject, PUSB_ENDPOINT_OBJECT NewEndpoint){
    LouPrint("OhciHcdCreateEndpoint()\n");
    UINT8                       UsbAddress = UsbCoreGetEndpointDeviceAddress(NewEndpoint);
    UINT8                       EndpointID = UsbCoreGetEndpointId(NewEndpoint);
    UINT8                       PipeType = UsbCoreGetEndpointsPipeType(NewEndpoint);
    ULONG                       Port = UsbCoreGetPortFromEndpoint(NewEndpoint);
    USB_ENDPOINT_DIRECTION      Direction = NewEndpoint->Direction;
    UINT32                      PortStatus = ((POHCI_DEVICE)HcdObject->HcdPrivateData)->OperationalRegisters->HcRhPortStatus[Port];; 
    BOOLEAN                     LowSpeed = 0;
    OHCI_ED_INITIALIZOR         Initializor = {0};
    POHCI_ED_LIST               EdHandleOut;
    LOUSTATUS                   Status;
    POHCI_ED_PRIVATE_DATA       EdPrivateData = LouKeMallocType(OHCI_ED_PRIVATE_DATA, KERNEL_GENERIC_MEMORY);
    if(!EdPrivateData){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    if(UsbAddress){
        POHCI_ENDPOINT_DESCRIPTOR Ed = ((POHCI_DEVICE)HcdObject->HcdPrivateData)->Device0Ed;
        LowSpeed = (Ed->Dword0 & (OHCI_ED_S_MASK << OHCI_ED_S_SHIFT)) ? 1 : 0;
    }
    
    Initializor.FunctionAddress = UsbAddress;
    Initializor.EndpointNumber = EndpointID;
    if(Direction == USB_ENDPOINT_DIRECTION_IO){
        Initializor.Direction = 0;
    }else{
        Initializor.Direction = (Direction == USB_ENDPOINT_DIRECTION_IN) ? 2 : 1;
    }
    Initializor.MaximumPacketSize = 8;
    Initializor.Speed = (UINT8)LowSpeed;
    switch(PipeType){
        case USB_PIPE_TYPE_CONTROL:{
            Status = OhciCreateControlED(
                HcdObject,
                &EdHandleOut,
                &Initializor
            );
            break;
        }
        default:
            Status = STATUS_INVALID_PARAMETER;
            break;
    }
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:Could Not Add Default Control ED\n");
        return Status;
    }

    EdPrivateData->EdHandle = EdHandleOut;

    NewEndpoint->HcdEndpointPrivateData = (PVOID)EdPrivateData;

    if(!UsbAddress){
        ((POHCI_DEVICE)HcdObject->HcdPrivateData)->Device0Ed = (POHCI_ENDPOINT_DESCRIPTOR)EdHandleOut->Ed;
    }

    LouPrint("OhciHcdCreateEndpoint():STATUS_SUCCESS\n");
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

SIZE OhciGetHcdRhPortCount(PUSB_HCD_OBJECT HcdObject){
    return (SIZE)(((POHCI_DEVICE)HcdObject->HcdPrivateData)->OperationalRegisters->HcRhDescriptorA) & 0xFF; 
}

RHPORT_STATUS OhciGetHcdRhPortStatus(PUSB_HCD_OBJECT HcdObject, UINT32 Port){
    POHCI_DEVICE OhciDevice = (POHCI_DEVICE)HcdObject->HcdPrivateData;
    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;
    UINT32 PortStatus = OpRegs->HcRhPortStatus[Port];
    if(!(PortStatus & OHCI_PORT_STATUS_CCS)){
        return RHPORT_STATUS_NO_DEVICE;
    }
    if(!(PortStatus & OHCI_PORT_STATUS_PES)){
        return RHPORT_STATUS_NEEDS_RESET;
    }
    if(PortStatus & OHCI_PORT_STATUS_PSS){
        return RHPORT_STATUS_IDLE;
    }
    return RHPORT_STATUS_RUNNING;
}

LOUSTATUS OhciResetRhPort(PUSB_HCD_OBJECT HcdObject, UINT32 Port){
    POHCI_DEVICE                OhciDevice = (POHCI_DEVICE)HcdObject->HcdPrivateData;
    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;
    UINT32                      PortStatus;
    POHCI_ENDPOINT_DESCRIPTOR   Ed = OhciDevice->Device0Ed;
    UINT8                       LowSpeed = 0;
    LOUSTATUS                   Status;
    OpRegs->HcRhPortStatus[Port] = OHCI_PORT_STATUS_PRS;
    Status = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer((PVOID)&OpRegs->HcRhPortStatus[Port]),
        100,
        OHCI_PORT_STATUS_PRS,
        0
    );

    if(Status != STATUS_SUCCESS){
        return Status;
    } 

    PortStatus = OpRegs->HcRhPortStatus[Port];

    LowSpeed = (PortStatus & (OHCI_PORT_STATUS_LSDA)) ? 1 : 0;

    Ed->Dword0 &= ~(OHCI_ED_S_MASK << OHCI_ED_S_SHIFT);
    Ed->Dword0 |= (LowSpeed << OHCI_ED_S_SHIFT);

    sleep(10);

    LouPrint("OhciResetRhPort()\n");
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
    PUSB_DEVICE_OBJECT          UsbDevice = Transfer->UsbDevice;
    PUSB_HCD_OBJECT             HcdDevice = UsbDevice->Hcd;
    POHCI_DEVICE                OhciDevice = (POHCI_DEVICE)HcdDevice->HcdPrivateData;
    USB_TRANSFER_OBJECT_TYPE    TransferType = Transfer->ObjectType;
    POHCI_TRANSFER_PRIVATE_DATA TransferPrivateData = LouKeMallocType(OHCI_TRANSFER_PRIVATE_DATA, KERNEL_GENERIC_MEMORY);  
    LOUSTATUS                   Status;
    if(!TransferPrivateData){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    
    Transfer->HcdPrivateData = (PVOID)TransferPrivateData;

    Status = OhciCreateSetupTD(
        HcdDevice,
        OhciGetDmaAddress(Transfer->SetupData),
        &TransferPrivateData->Setup
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    if(!Transfer->TransferSize){
        Status = OhciCreateStatusTD(
            HcdDevice,
            &TransferPrivateData->Setup,
            2,
            &TransferPrivateData->DumbyID
        );
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        TransferPrivateData->DumbyID = (POHCI_TD_LIST)TransferPrivateData->DumbyID->Peers.NextHeader;
        return STATUS_SUCCESS;
    }
    LouPrint("OhciPrepTransfer():HERE\n"); //TODO: setup TD's for transfer
    while(1);    
    return STATUS_SUCCESS;
}


LOUSTATUS OhciCommitTransfer(PUSB_TRANSFER_OBJECT Transfer){
    PUSB_DEVICE_OBJECT          UsbDevice = Transfer->UsbDevice;
    PUSB_HCD_OBJECT             HcdObject = UsbDevice->Hcd;
    POHCI_DEVICE                OhciDevice = (POHCI_DEVICE)HcdObject->HcdPrivateData;
    POHCI_TRANSFER_PRIVATE_DATA TransferPrivateData = (POHCI_TRANSFER_PRIVATE_DATA)Transfer->HcdPrivateData;
    POHCI_TD_LIST               DumbyID = TransferPrivateData->DumbyID;
    USB_TRANSFER_OBJECT_TYPE    TransferType = Transfer->ObjectType;
    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;

    if(TransferType == USB_TRANSFER_OBJECT_CONTROL){
        PUSB_ENDPOINT_OBJECT Endpoint = Transfer->Pipe->EndpointObject[0];
        POHCI_ED_PRIVATE_DATA EndpointData = (POHCI_ED_PRIVATE_DATA)Endpoint->HcdEndpointPrivateData;
        POHCI_ENDPOINT_DESCRIPTOR Ed = (POHCI_ENDPOINT_DESCRIPTOR)EndpointData->EdHandle->Ed;
        POHCI_TD_LIST OldDumby = (POHCI_TD_LIST)EndpointData->EdHandle->Tds.Peers.NextHeader;
        EndpointData->EdHandle->Tds.Peers.NextHeader = (PListHeader)DumbyID;
        TransferPrivateData->DoneHeadID = OldDumby;
        
        OhciSetEdSkip(Ed, true);

        memcpy(OldDumby->Td, TransferPrivateData->Setup.Td, sizeof(OHCI_TRANSFER_DESCRIPTOR));
        OldDumby->Peers.NextHeader = TransferPrivateData->Setup.Peers.NextHeader;

        OhciSetEdTail(Ed, OhciGetDmaAddress(DumbyID->Td));

        OhciSetEdSkip(Ed, false);

        OpRegs->HcCommandStatus = OHCI_COMMAND_STATUS_CLF;

        return STATUS_SUCCESS;
    }

    LouPrint("OhciCommitTransfer():HERE\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS OhciGetTransferStatus(PUSB_TRANSFER_OBJECT Transfer){
    PUSB_DEVICE_OBJECT          UsbDevice = Transfer->UsbDevice;
    PUSB_HCD_OBJECT             HcdObject = UsbDevice->Hcd;
    POHCI_TRANSFER_PRIVATE_DATA TransferPrivateData = (POHCI_TRANSFER_PRIVATE_DATA)Transfer->HcdPrivateData;
    POHCI_TD_LIST               DumbyID = TransferPrivateData->DumbyID;
    USB_TRANSFER_OBJECT_TYPE    TransferType = Transfer->ObjectType;

    if(TransferType == USB_TRANSFER_OBJECT_CONTROL){
        PUSB_ENDPOINT_OBJECT      Endpoint = Transfer->Pipe->EndpointObject[0];
        POHCI_ED_PRIVATE_DATA     EndpointData = (POHCI_ED_PRIVATE_DATA)Endpoint->HcdEndpointPrivateData;
        POHCI_ENDPOINT_DESCRIPTOR Ed = (POHCI_ENDPOINT_DESCRIPTOR)EndpointData->EdHandle->Ed;

        LouKeMemoryBarrier();

        UINT32 HeadP = Ed->Dword2;
        UINT32 TailDummyPhys = OhciGetDmaAddress(DumbyID->Td);
        BOOLEAN Halted = (Ed->Dword2 & 0x01) ? true : false;

        if(!Halted && (HeadP != TailDummyPhys)){
            return STATUS_NO_WORK_DONE;
        }
        POHCI_TD_LIST CurrentTdNode = TransferPrivateData->DoneHeadID;
        while(CurrentTdNode && (CurrentTdNode != DumbyID)){
            POHCI_TRANSFER_DESCRIPTOR Td = (POHCI_TRANSFER_DESCRIPTOR)CurrentTdNode->Td;
            UINT8 Cc = (UINT8)((Td->Dword0 >> OHCI_TD_CC_SHIFT) & OHCI_TD_CC_MASK);
            if(Cc != 0x00){
                return STATUS_UNSUCCESSFUL;
            }
            CurrentTdNode = (POHCI_TD_LIST)CurrentTdNode->Peers.NextHeader;
        }
        return STATUS_SUCCESS;
    }

    LouPrint("OhciGetTransferStatus():HERE\n");
    while(1);
    return STATUS_SUCCESS;
}


LOUSTATUS OhciCleanupTransfer(PUSB_TRANSFER_OBJECT Transfer){
    PUSB_DEVICE_OBJECT          UsbDevice = Transfer->UsbDevice;
    PUSB_HCD_OBJECT             HcdObject = UsbDevice->Hcd;
    POHCI_TRANSFER_PRIVATE_DATA TransferPrivateData = (POHCI_TRANSFER_PRIVATE_DATA)Transfer->HcdPrivateData;
    POHCI_TD_LIST               DumbyID = TransferPrivateData->DumbyID;
    if(TransferPrivateData->Setup.Td){
        OhciFreeDma(HcdObject, TransferPrivateData->Setup.Td);
    }
    POHCI_TD_LIST Current = TransferPrivateData->DoneHeadID;
    while(Current && (Current != DumbyID)){
        POHCI_TD_LIST Next = (POHCI_TD_LIST)Current->Peers.NextHeader;
        if(Current->Td){
            OhciFreeDma(HcdObject, Current->Td);
        }
        LouKeFree(Current);
        Current = Next;
    }
    LouKeFree(TransferPrivateData);
    return STATUS_SUCCESS;
}

