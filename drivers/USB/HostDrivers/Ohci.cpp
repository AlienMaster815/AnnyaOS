#include "OHCI.h"


LOUSTATUS 
OhciInitialzeHcca(
    POHCI_DEVICE    OhciDevice
){
    if(OhciDevice->HccaAddress){
        return STATUS_SUCCESS;
    }

    POHCI_OPERATIONAL_REGISTERS OpReg = OhciDevice->OperationalRegisters;
    UINT64 PhyAddress;
    LOUSTATUS Status;

    Status = OhciAllocateDma(256, 256, (PVOID*)&OhciDevice->HccaAddress);
    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Unable To Allocate HCCA Memory\n");
        return Status;
    }

    OhciDevice->OperationalRegisters->HcHCCA = OhciGetDmaAddress((PVOID)OhciDevice->HccaAddress);

    return STATUS_SUCCESS;
}



LOUSTATUS OhciInitializeFunctionDevice(PUSB_FUNCTION_DEVICE FunctionDevice){
    LouPrint("OHCI.SYS:OhciInitializeFunctionDevice()\n");
    PUSB_HOST_DEVICE HostDevice = UsbFunctionDeviceToHcd(FunctionDevice);
    POHCI_DEVICE OhciDevice = UsbHcdToOhciDevice(HostDevice);
    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;
    LOUSTATUS Status;
    UINT8   Port = FunctionDevice->PortNumber;
    UINT32  Tmp = OHCI_PORT_STATUS_PRS;

    OpRegs->HcRhPortStatus[Port] = Tmp;

    Status = LouKeWaitForUlongRegisterCondition(
        (PULONG)LouKeCastToUnalignedPointer(&OpRegs->HcRhPortStatus[Port]), //it actually is aligned the compiler just gives a warning
        100,
        OHCI_PORT_STATUS_PRS,
        0
    );

    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Port:%d Hung On PRS Command\n", Port);
        return STATUS_TIMEOUT;
    }
    

    Tmp = OpRegs->HcRhPortStatus[Port];
    if(Tmp & OHCI_PORT_STATUS_PRSC){
        OpRegs->HcRhPortStatus[Port] = OHCI_PORT_STATUS_PRSC;
    }

    Tmp = OpRegs->HcRhPortStatus[Port];
    if(!(Tmp & OHCI_PORT_STATUS_PES)){
        OpRegs->HcRhPortStatus[Port] = OHCI_PORT_STATUS_PES;
    }
    FunctionDevice->PortEnabled = true;

    Tmp = OpRegs->HcRhPortStatus[Port];
    if(Tmp & OHCI_PORT_STATUS_PESC){
        OpRegs->HcRhPortStatus[Port] = OHCI_PORT_STATUS_PESC;
    }

    Tmp = OpRegs->HcRhPortStatus[Port];

    if(Tmp & OHCI_PORT_STATUS_LSDA){
        LouPrint("OHCI.SYS:Device Is Low Speed\n");
        FunctionDevice->FunctionSpeed = UsbLowSpeedFunction;
    }else{
        LouPrint("OHCI.SYS:Device Is Full Speed\n");
        FunctionDevice->FunctionSpeed = UsbFullSpeedFunction;
    }

    UINT8 Data[16] = {0};
    USB_HOST_IO_PACKET IoPacket = {0};

    OHCI_IO_PACKET_PRIVATE_DATA IoData = {0};

    IoData.EdItem = (POHCI_ED_LIST)OhciDevice->ControlEDs.Peers.NextHeader;

    FunctionDevice->PrivateHostFunctionData = &IoData;

    Status = LouKeUsbGetDescriptorRequest(
        FunctionDevice,
        &IoPacket,
        USB_DESCRIPTOR_TYPE_DEVICE,
        0,
        16,
        0,
        Data
    );    
    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Error Getting Descriptor\n");
        return Status;
    }

    

    LouPrint("OHCI.SYS:OhciInitializeFunctionDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}

static const USB_FUNCTION_OPERATIONS FunctionOperations = {
    .UsbInitializeFunctionDevice = OhciInitializeFunctionDevice,
};

LOUSTATUS OhciProbeRootHub(PUSB_HOST_DEVICE HostDevice){
    LouPrint("OHCI.SYS:OhciProbeRootHub()\n");
    LOUSTATUS Status;
    POHCI_DEVICE OhciDevice = UsbHcdToOhciDevice(HostDevice);
    USB_FUNCTION_DEVICE UsbDescriptor;
    UINT32 HcRhDescriptorA;
    UINT8 Ports;

    HcRhDescriptorA = OhciDevice->OperationalRegisters->HcRhDescriptorA;
    Ports = HcRhDescriptorA & 0x0F;

    LouPrint("OHCI.SYS:Ports:%d\n", Ports);

    for(size_t i = 0 ; i < Ports; i++){
        UINT32 TmpPortStatus = OhciDevice->OperationalRegisters->HcRhPortStatus[i];

        if(TmpPortStatus & OHCI_PORT_STATUS_CCS){
            LouPrint("OHCI.SYS:Port:%d Is Connected To Somthing\n", i);
            UsbDescriptor.PortNumber = i;
            UsbDescriptor.Operations = FunctionOperations;
            UsbDescriptor.MaxPacketSize = 8;
            Status = LouKeUsbAddDeviceToHcd(
                HostDevice,
                &HostDevice->RootHub.FunctionDevice,
                &UsbDescriptor
            );

            if(!NT_SUCCESS(Status)){
                LouPrint("OHCI.SYS:Error Adding Device To Host\n");
                return Status;
            }
        }
    }

    LouPrint("OHCI.SYS:OhciProbeRootHub() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS OhciResetHostController(PUSB_HOST_DEVICE HostDevice){
    LouPrint("OHCI.SYS:OhciResetHostController()\n");
    LouPrint("OHCI.SYS:Bringing Up Controller\n");
    LOUSTATUS Status;
    UINT32 Fm;
    UINT16 FrameInterval;
    UINT16 PeriodicStart;

    POHCI_DEVICE OhciDevice = UsbHcdToOhciDevice(HostDevice);

    OhciDevice->Fminterval = OhciDevice->OperationalRegisters->HcFmInterval;
    OhciDevice->OperationalRegisters->HcCommandStatus |= OHCI_COMMAND_STATUS_HCR;

    Status = LouKeWaitForUlongRegisterCondition(
        (PULONG)LouKeCastToUnalignedPointer(&OhciDevice->OperationalRegisters->HcCommandStatus),//it actually is aligned the compiler just gives a warning
        10,
        OHCI_COMMAND_STATUS_HCR,
        0
    );

    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Ohci Controller Hung On Reset\n");
        LouKeFree(OhciDevice);
        return Status;
    }

    OhciDevice->OperationalRegisters->HcFmInterval = OhciDevice->Fminterval;
    
    OhciDevice->OperationalRegisters->HcControl = SET_OHCI_COTROL_HCFS(OhciDevice->OperationalRegisters->HcControl , OHCI_HCFS_USBRESET);
    sleep(10);
    OhciDevice->OperationalRegisters->HcControl = SET_OHCI_COTROL_HCFS(OhciDevice->OperationalRegisters->HcControl , OHCI_HCFS_USBRESUME);
    sleep(10);

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


    Status = OhciInitialzeHcca(OhciDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("OHCI.SYS:ERROR Unable To Initialize Device Data\n");
        return Status;
    }

    Fm = OhciDevice->OperationalRegisters->HcFmInterval;
    FrameInterval = Fm & 0x3FFF;   // mask bits 0–13
    PeriodicStart = (FrameInterval * 9) / 10;
    OhciDevice->OperationalRegisters->HcPeriodicStart = PeriodicStart;
    OhciDevice->OperationalRegisters->HcRhStatus |= OHCI_RH_STATUS_LPSC;

    OhciDevice->OperationalRegisters->HcControl = SET_OHCI_COTROL_HCFS(OhciDevice->OperationalRegisters->HcControl , OHCI_HCFS_USBOPERATIONAL);

    if(GET_OHCI_CONTROL_HCFS(OhciDevice->OperationalRegisters->HcControl) != OHCI_HCFS_USBOPERATIONAL){
        LouPrint("OHCI.SYS:ERROR:Host Did Not Become Operational\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    
    LouPrint("OHCI.SYS:OhciResetHostController() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS OhciStopHostController(PUSB_HOST_DEVICE HostDevice){
    LouPrint("OHCI.SYS:OhciStopHostController()\n");
    POHCI_DEVICE OhciDevice = UsbHcdToOhciDevice(HostDevice);
    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;    
    UINT32 Tmp;
    LOUSTATUS Status;
    MutexLock(&HostDevice->ExlusiveOwnership);

    OpRegs->HcInterruptDisable = 0xFFFFFFFF;
    OpRegs->HcInterruptStatus = 0xFFFFFFFF;

    Tmp = OpRegs->HcControl;
    Tmp &= ~(OHCI_CONTROL_CLE | OHCI_CONTROL_BLE | OHCI_CONTROL_PLE | OHCI_CONTROL_IE);
    OpRegs->HcControl = Tmp;

    sleep(20);

    OpRegs->HcControl = SET_OHCI_COTROL_HCFS(OpRegs->HcControl , OHCI_HCFS_USBSUSPEND);

    Status = LouKeWaitForUlongRegisterCondition(
        (PULONG)LouKeCastToUnalignedPointer(&OpRegs->HcControl),
        10,
        OHCI_CONTROL_HCFS,
        OHCI_HCFS_USBSUSPEND
    );

    MutexUnlock(&HostDevice->ExlusiveOwnership);
    if(!NT_SUCCESS(Status)){
        return  Status;
    }
    LouPrint("OHCI.SYS:OhciStopHostController() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS OhciStartHostController(PUSB_HOST_DEVICE HostDevice){
    LouPrint("OHCI.SYS:OhciStartHostController()\n");
    LOUSTATUS Status;
    POHCI_DEVICE OhciDevice = UsbHcdToOhciDevice(HostDevice);
    POHCI_OPERATIONAL_REGISTERS OpRegs = OhciDevice->OperationalRegisters;

    if(GET_OHCI_CONTROL_HCFS(OpRegs->HcControl) == OHCI_HCFS_USBSUSPEND){
        OpRegs->HcControl = SET_OHCI_COTROL_HCFS(OpRegs->HcControl , OHCI_HCFS_USBOPERATIONAL);
        Status = LouKeWaitForUlongRegisterCondition(
            (PULONG)LouKeCastToUnalignedPointer(&OpRegs->HcControl),
            10,
            OHCI_CONTROL_HCFS,
            OHCI_HCFS_USBOPERATIONAL
        );
        if(!NT_SUCCESS(Status)){
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

    //OpRegs->HcInterruptEnable = 0xFFFFFFFF;

    UINT32 IoMask = 0;

    if(OpRegs->HcControlHeadED){
        IoMask |= OHCI_CONTROL_CLE;
    } 
    if(OpRegs->HcBulkHeadED){
        IoMask |= OHCI_CONTROL_BLE;
    }

    OpRegs->HcControl |= IoMask | OHCI_CONTROL_PLE | OHCI_CONTROL_IE;


    LouPrint("OHCI.SYS:OhciStartHostController() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

void OhciInterruptHandler(uint64_t UsbHostData){
    LouPrint("OHCI.SYS:OhciInterruptHandler()\n");
    POHCI_DEVICE OhciDevice = (POHCI_DEVICE)UsbHostData;

    LouPrint("OHCI.SYS:%h\n", OhciDevice->OperationalRegisters->HcInterruptStatus);

    while(1);
}

LOUSTATUS OhciInitializeDefaultControl(
    POHCI_DEVICE OhciDevice
){
    LouPrint("OHCI.SYS:OhciInitializeLists()\n");
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
        OhciDevice,
        &EdOut,
        &Initializor
    );
    if(!NT_SUCCESS(Status)){
        LouPrint("OHCI.SYS:Could Not Add Default Control ED\n");
        return Status;
    }
    DmaAddress = OhciGetDmaAddress(EdOut);
    OpRegs->HcControlHeadED = DmaAddress;

    LouPrint("OHCI.SYS:OhciInitializeLists() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS OhciCommitRequest(
    PUSB_HOST_IO_PACKET IoPacket
){
    LouPrint("OHCI.SYS:OhciCommitRequest()\n");
    POHCI_IO_PACKET_PRIVATE_DATA IoData;
    PUSB_FUNCTION_DEVICE FunctionDevice = IoPacket->FunctionDevice;
    IoData = (POHCI_IO_PACKET_PRIVATE_DATA)FunctionDevice->PrivateHostFunctionData;
    POHCI_ED_LIST EdItem = (POHCI_ED_LIST)IoData->EdItem;

    MutexLock(&EdItem->EdLock);

    
    if(IoPacket->TransferType == USB_TRANSFER_TYPE_CONTROL){
        OhciCreateSetupTD(IoPacket, EdItem);
        OhciCreateDataTDs(IoPacket, EdItem);
        OhciCreateStatusTD(IoPacket, EdItem);
        

    
    }else{
        LouPrint("OHCI.SYS:Invalid Parameter\n");
        return STATUS_INVALID_PARAMETER;
    }    
            

    MutexUnlock(&EdItem->EdLock);
    LouPrint("OHCI.SYS:OhciCommitRequest() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;  
}