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

UINT32 OhciReadHcCommandStatus(
    POHCI_DEVICE    OhciDevice
){
    UINT32 Result;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    Result = OhciDevice->OperationalRegisters->HcCommandStatus;
    Result &= ~(0xFFFCFFF0);
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return Result;
}

void OhciWriteHcCommandStatus(
    POHCI_DEVICE    OhciDevice,
    UINT32          CommandStatus
){
    UINT32 Result;
    LouKIRQL Irql;
    CommandStatus &= ~(0xFFFCFFF0);    
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    Result = OhciDevice->OperationalRegisters->HcCommandStatus;
    Result &= (0xFFFCFFF0);
    Result |= CommandStatus;
    OhciDevice->OperationalRegisters->HcCommandStatus = Result;
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcInterruptStatus(
    POHCI_DEVICE    OhciDevice
){
    UINT32      Result;
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    Result = OhciDevice->OperationalRegisters->HcInterruptStatus;
    Result &= ~(0x3FFFFF80);
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return Result;
}

void OhciWriteHcInterruptStatus(
    POHCI_DEVICE    OhciDevice,
    UINT32          InterruptStatus
){
    InterruptStatus &= ~(0x3FFFFF80);
    UINT32 Result;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    Result = OhciDevice->OperationalRegisters->HcInterruptStatus;
    Result &= (0x3FFFFF80);
    Result |= InterruptStatus;
    OhciDevice->OperationalRegisters->HcInterruptStatus = InterruptStatus;
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}


void OhciWriteHcInterruptEnable(
    POHCI_DEVICE    OhciDevice,
    UINT32          InterruptEnable
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcInterruptEnable(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcInterruptDisable(
    POHCI_DEVICE    OhciDevice,
    UINT32          InterruptDisable
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcInterruptDisable(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcHCCA(
    POHCI_DEVICE    OhciDevice,
    UINT32          HCCA
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcHCCA(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

UINT32 OhciReadHcPeriodCurrentED(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcPeriodCurrentED(
    POHCI_DEVICE    OhciDevice,
    UINT32          PeriodCurrentED
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcControlHeadED(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciReadHcControlHeadED(
    POHCI_DEVICE    OhciDevice,
    UINT32          ControlHeadED
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcControlCurrentED(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcControlCurrentED(
    POHCI_DEVICE    OhciDevice,
    UINT32          ControlCurrentED
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcBulkHeadED(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcBulkHeadED(
    POHCI_DEVICE    OhciDevice,
    UINT32          BulkHeadED
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcBulkCurrentED(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcBulkCurrentED(
    POHCI_DEVICE    OhciDevice,
    UINT32          BulkCurrentED
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadDoneHead(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteDoneHead(
    POHCI_DEVICE    OhciDevice,
    UINT32          DoneHead
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcFmInterval(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcFmInterval(
    POHCI_DEVICE    OhciDevice,
    UINT32          HcFmInterval
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcFmRemaining(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcFmRemaining(
    POHCI_DEVICE    OhciDevice,
    UINT32          HcFmRemaining
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcPeriodicStart(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcPeriodicStart(
    POHCI_DEVICE    OhciDevice,
    UINT32          PeriodicStart
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcLSThreashold(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcLSThreashold(
    POHCI_DEVICE    OhciDevice,
    UINT32          LSThreshold
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcRhDescriptorA(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcRhDescriptorA(
    POHCI_DEVICE    OhciDevice,
    UINT32          RhDescriptorA
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcRhDescriptorB(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcRhDescriptorB(
    POHCI_DEVICE    OhciDevice,
    UINT32          RhDescriptorB
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcRhStatus(
    POHCI_DEVICE    OhciDevice
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcRhStatus(
    POHCI_DEVICE    OhciDevice,
    UINT32          RhStatus
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}

UINT32 OhciReadHcRhPortStatus(
    POHCI_DEVICE    OhciDevice,
    UINT8           Port
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
    return 0;
}

void OhciWriteHcRhPortStatus(
    POHCI_DEVICE    OhciDevice,
    UINT8           Port,
    UINT32          RhStatus
){
    LouKIRQL    Irql;
    LouKeAcquireSpinLock(&OhciDevice->IoLock, &Irql);
    
    LouKeReleaseSpinLock(&OhciDevice->IoLock, &Irql);
}