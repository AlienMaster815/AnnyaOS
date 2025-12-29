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

/*LOUSTATUS OhciCreateEndpoint(
    POHCI_DEVICE    OhciDevice,
    UINT8           FunctionAddress,
    UINT8           EndpointNumber,
    UINT8           Direction,
    BOOL            LowSpeed,
    OHCI_ED_TYPE    EdType
){
    LOUSTATUS Status;
    PVOID NewEp;

    Status = OhciAllocateDma(sizeof(OHCI_ENDPOINT_DESCRIPTOR), 16, &NewEp);
    if(!NT_SUCCESS(Status)){
        return Status;
    }
    OHCI_ED_INITIALIZOR EpInit = {0};

    EpInit.FunctionAddress = FunctionAddress;
    EpInit.EndpointNumber = EndpointNumber;
    EpInit.Direction = Direction;


    return STATUS_SUCCESS;
}*/

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

    LouPrint("OHCI.SYS:OhciInitializeFunctionDevice() STATUS_SUCCESS\n");
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

    OhciDevice->OperationalRegisters->HcCommandStatus |= OHCI_COMMAND_STATUS_OCR;
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
    OhciDevice->OperationalRegisters->HcControl = SET_OHCI_COTROL_HCFS(OhciDevice->OperationalRegisters->HcControl , OHCI_HCFS_USBRESUME);

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

    OhciDevice->OperationalRegisters->HcControl &= ~((1 << OHCI_CONTROL_CLE_BIT) | (1 << OHCI_CONTROL_BLE_BIT) | (1 << OHCI_CONTROL_PLE_BIT)); 

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
