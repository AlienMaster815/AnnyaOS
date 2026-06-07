#include "Xhci.h"

UINT32 XhciGetUsbCommand(
    PXHCI_DEVICE    Device
){
    return Device->OperationalRegisters->UsbCommand;
}

void XhciSetUsbCommand(
    PXHCI_DEVICE    Device,
    UINT32          Value
){
    Device->OperationalRegisters->UsbCommand = Value;
}

UINT32 XhciGetUsbStatus(
    PXHCI_DEVICE    Device
){
    return Device->OperationalRegisters->UsbStatus;
}

void XhciSetUsbStatus(
    PXHCI_DEVICE    Device,
    UINT32          Value
){
    Device->OperationalRegisters->UsbStatus = Value;
}

UINT32 XhciGetUsbPageSize(
    PXHCI_DEVICE    Device
){
    return Device->OperationalRegisters->PageSize;
}

void XhciSetUsbPageSize(
    PXHCI_DEVICE    Device,
    UINT32          Value
){
    Device->OperationalRegisters->PageSize = Value;
}

UINT32 XhciGetDncCtrl(
    PXHCI_DEVICE    Device
){
    return Device->OperationalRegisters->DncCtrl;
}

void XhciSetDncCtrl(
    PXHCI_DEVICE    Device,
    UINT32          Value
){
    Device->OperationalRegisters->DncCtrl = Value;
}

UINT32 XhciGetCrcr(
    PXHCI_DEVICE    Device
){
    return Device->OperationalRegisters->Crcr;
}

void XhciSetCrcr(
    PXHCI_DEVICE    Device,
    UINT32          Value
){
    Device->OperationalRegisters->Crcr = Value;
}

UINT64 XhciGetDcbaap(
    PXHCI_DEVICE    Device
){
    return Device->OperationalRegisters->Dcbaap;
}

void XhciSetDcbaap(
    PXHCI_DEVICE    Device,
    UINT64          Value
){
    Device->OperationalRegisters->Dcbaap = Value;
}

UINT32 XhciGetConfig(
    PXHCI_DEVICE    Device
){
    return Device->OperationalRegisters->Config;
}

void XhciSetConfig(
    PXHCI_DEVICE    Device,
    UINT32          Value
){
    Device->OperationalRegisters->Config = Value;
}



LOUSTATUS XhciInitializeDevice(
    PXHCI_DEVICE Device
){
    LouPrint("XHCI.SYS:XhciInitializeDevice()\n");
    


    LouPrint("XHCI.SYS:XhciInitializeDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}