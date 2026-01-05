#include "EHCI.h"

LOUSTATUS EhciStopHostController(PEHCI_DEVICE EhciDevice){
    LouPrint("EHCI.SYS:EhciStopHostController()\n");
    if(!EhciDevice){
        LouPrint("EHCI.SYS:EhciStopHostController() EINVAL_PARAM\n");
        return STATUS_INVALID_PARAMETER;
    }
    PEHCI_HOST_OPERATIONAL_REGISTERS OpRegs = EhciDevice->OperationalRegisters;
    LOUSTATUS Status;
    if(!EHCI_GET_USBSTS_HC_HALTED(OpRegs->UsbStatus)){
        OpRegs->UsbCommand = EHCI_SET_USBCMD_RS(OpRegs->UsbCommand, 0);
        Status = LouKeWaitForUlongRegisterCondition(
            (PULONG)LouKeCastToUnalignedPointer(&OpRegs->UsbStatus), //this is not unaligned the compiler is a bitch
            10,
            EHCI_USBSTS_HC_HALTED,
            1
        );
        if(Status != STATUS_SUCCESS){
            LouPrint("EHCI.SYS:Ehci Controller Failed To Halt\n");
            return Status;
        }

    }
    LouPrint("EHCI.SYS:EhciStopHostController() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS EhciResetController(PEHCI_DEVICE EhciDevice){
    LouPrint("EHCI.SYS:EhciResetController()\n");
    if(!EhciDevice){
        LouPrint("EHCI.SYS:EhciResetController() EINVAL_PARAM\n");
        return STATUS_INVALID_PARAMETER;
    }

    PEHCI_HOST_OPERATIONAL_REGISTERS OpRegs = EhciDevice->OperationalRegisters;
    LOUSTATUS Status;

    OpRegs->UsbCommand = EHCI_SET_USBCMD_HCRESET(OpRegs->UsbCommand, 1);
    Status = LouKeWaitForUlongRegisterCondition(
        (PULONG)LouKeCastToUnalignedPointer(&OpRegs->UsbCommand), //this is not unaligned the compiler is a bitch
        10,
        EHCI_USBCMD_HCRESET,
        0
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("EHCI.SYS:Ehci Controller Failed To Reset\n");
        return Status;
    }
    LouPrint("EHCI.SYS:EhciResetController() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

