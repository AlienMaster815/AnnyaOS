#include "OHCI.h"


UINT8 OhciGetHcRevision(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql; 
    UINT8       Revision;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    Revision = OhciDevice->OperationalRegisters->HcRevision;
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return Revision & 0xFF;
}

void OhciSetHcRevision(
    POHCI_DEVICE    OhciDevice,
    UINT8           Revision
){
    //ditch the top 6 bits they arent writeable
    LouKIRQL Irql;
    Revision &= ~(0xFC);
    UINT32 Result;    
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    Result = OhciDevice->OperationalRegisters->HcRevision;
    Result &= ~(0x03);
    Result |= Revision;
    OhciDevice->OperationalRegisters->HcRevision = Result;
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

void OhciWriteHcControl(
    POHCI_DEVICE    OhciDevice,
    UINT16          Control
){
    Control &= ~(0xF800);
    LouKIRQL Irql;
    UINT32 Result;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    Result = OhciDevice->OperationalRegisters->HcControl;
    Result &= ~(0x07FF);
    Result |= Control;
    OhciDevice->OperationalRegisters->HcControl = Result;
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

