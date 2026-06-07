#include "Xhci.h"

UINT32 XhciGetPortxPsc(
    PXHCI_DEVICE    Device,
    UINT8           Port
){
    return Device->OperationalRegisters->Ports[Port].PortStatusControl;
}

void XhciSetPortxPsc(
    PXHCI_DEVICE    Device,
    UINT8           Port,
    UINT32          Value
){
    Device->OperationalRegisters->Ports[Port].PortStatusControl = Value;
}

UINT32 XhciGetPortxPmsc(
    PXHCI_DEVICE    Device,
    UINT8           Port
){
    return Device->OperationalRegisters->Ports[Port].PortPMSC;
}

void XhciSetPortxPmsc(
    PXHCI_DEVICE    Device,
    UINT8           Port,
    UINT32          Value
){
    Device->OperationalRegisters->Ports[Port].PortPMSC = Value;
}

UINT32 XhciGetPortxLi(
    PXHCI_DEVICE    Device,
    UINT8           Port
){
    return Device->OperationalRegisters->Ports[Port].PortLI;
}

void XhciSetPortxLi(
    PXHCI_DEVICE    Device,
    UINT8           Port,
    UINT32          Value
){
    Device->OperationalRegisters->Ports[Port].PortLI = Value;
}

UINT32 XhciGetPortxHlpmc(
    PXHCI_DEVICE    Device,
    UINT8           Port
){
    return Device->OperationalRegisters->Ports[Port].PortHLPMC;
}

void XhciSetPortxHlpmc(
    PXHCI_DEVICE    Device,
    UINT8           Port,
    UINT32          Value
){
    Device->OperationalRegisters->Ports[Port].PortHLPMC = Value; 
}
