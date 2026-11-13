//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "Ehci.h"

void EhciResetPeriodicFrameList(PVOID FrameListBaseAddress);

static LOUSTATUS _EhciStopHcdDevice(PUSB_HCD_OBJECT HcdObject){
    PEHCI_DEVICE_OBJECT EhciObject = (PEHCI_DEVICE_OBJECT)HcdObject->HcdPrivateData;
    PEHCI_HOST_OPERATIONAL_REGISTERS OpRegs = EhciObject->OperationalRegisters;
    UINT32 Command = OpRegs->UsbCommand;
    UINT32 Status = OpRegs->UsbStatus;
    if((!(Command & EHCI_USBCMD_RS)) && (Status & EHCI_USBSTS_HC_HALTED)){
        return STATUS_SUCCESS;
    }
    Command &= ~(EHCI_USBCMD_RS);
    OpRegs->UsbCommand = Command;

    return LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer((PVOID)&OpRegs->UsbStatus),
        5000,
        EHCI_USBSTS_HC_HALTED,
        EHCI_USBSTS_HC_HALTED
    );
}

LOUSTATUS EhciResetHcdDevice(PUSB_HCD_OBJECT HcdObject){
    LouPrint("EHCI.SYS:EhciResetHcdDevice()\n");
    PEHCI_DEVICE_OBJECT EhciObject = (PEHCI_DEVICE_OBJECT)HcdObject->HcdPrivateData;
    PEHCI_HOST_OPERATIONAL_REGISTERS OpRegs = EhciObject->OperationalRegisters;
    UINT32 Command;
    UINT32 Status;
    LOUSTATUS LouStatus = _EhciStopHcdDevice(HcdObject);
    if(LouStatus != STATUS_SUCCESS){
        LouPrint("EHCI.SYS:Unable To Stop Controller\n");
        return LouStatus;
    }
    Command = OpRegs->UsbCommand;
    Command |= EHCI_USBCMD_HCRESET;
    OpRegs->UsbCommand = Command;

    LouStatus = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer((PVOID)&OpRegs->UsbCommand),
        5000,
        EHCI_USBCMD_HCRESET,
        0
    );
    if(LouStatus != STATUS_SUCCESS){
        return LouStatus;
    }

    //TODO: Enable Interrupts

    EhciResetPeriodicFrameList(EhciObject->VirtualFrameListBase);

    OpRegs->FrameListBaseAddress = EhciGetDmaAddress(EhciObject->VirtualFrameListBase);

    Command = OpRegs->UsbCommand;

    Command &= ~(EHCI_USBCMD_ITC);
    Command |= (1 << EHCI_USBCMD_ITC_SHIFT);
    
    OpRegs->UsbCommand = Command;

    LouPrint("EHCI.SYS:EhciResetHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS EhciStartHcdDevice(PUSB_HCD_OBJECT HcdObject){
    LouPrint("EHCI.SYS:EhciStartHcdDevice()\n");
    PEHCI_DEVICE_OBJECT EhciObject = (PEHCI_DEVICE_OBJECT)HcdObject->HcdPrivateData; 
    PEHCI_HOST_OPERATIONAL_REGISTERS OpRegs = EhciObject->OperationalRegisters;
    UINT32 Command = OpRegs->UsbCommand;
    Command |= (EHCI_USBCMD_RS);
    OpRegs->UsbCommand = Command;
    OpRegs->ConfigFlag = 1;

    LOUSTATUS Status = LouKeWaitForUlongRegisterConditionMs(
        (PULONG)LouKeCastToUnalignedPointer((PVOID)&OpRegs->UsbStatus),
        5000,
        EHCI_USBSTS_HC_HALTED,
        0
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("EHCI.SYS:Unable To Start Device\n");
        return Status;
    }

    LouPrint("EHCI.SYS:EhciStartHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS EhciStopHcdDevice(PUSB_HCD_OBJECT HcdObject){
    LouPrint("EHCI.SYS:EhciStopHcdDevice()\n");
    LOUSTATUS Status = _EhciStopHcdDevice(HcdObject);
    if(Status != STATUS_SUCCESS){
        LouPrint("EHCI.SYS:Unable To Stop Controller\n");
        return Status;
    }
    LouPrint("EHCI.SYS:EhciStopHcdDevice():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS EhciHcdCreateEndpoint(PUSB_HCD_OBJECT Hcd, PUSB_ENDPOINT_OBJECT NewEndpoint){
    LouPrint("EHCI.SYS:EhciHcdCreateEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS EhciHcdDestroyEndpoint(PUSB_ENDPOINT_OBJECT Endpoint){
    LouPrint("EHCI.SYS:EhciHcdDestroyEndpoint()\n");
    while(1);
    return STATUS_SUCCESS;
}


RHPORT_STATUS EhciGetHcdRhPortStatus(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("EHCI.SYS:EhciGetHcdRhPortStatus()\n");
    while(1);
    return RHPORT_STATUS_NEEDS_RESET;
}

LOUSTATUS EhciResetRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("EHCI.SYS:EhciResetRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS EhciStartRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("EHCI.SYS:EhciStartRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS EhciStopRhPort(PUSB_HCD_OBJECT Hcd, UINT32 Port){
    LouPrint("EHCI.SYS:EhciStopRhPort()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS EhciPrepTransfer(PUSB_TRANSFER_DATA Transfer){
    LouPrint("EHCI.SYS:EhciPrepTransfer()\n");
    while(1);
    return STATUS_SUCCESS;
}


LOUSTATUS EhciCommitTransfer(PUSB_TRANSFER_DATA Transfer){
    LouPrint("EHCI.SYS:EhciCommitTransfer()\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS EhciInterruptHandler(UINT64 Data){
    LouPrint("EHCI.SYS:EhciInterruptHandler()\n");
    while(1);
    return STATUS_SUCCESS;
}