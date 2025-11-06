#ifndef _UHCI_H
#define _UHCI_H

#include <LouDDK.h>

#define UHCI_USBCMD         0x00 //Usb Command Register Read/Write                      WORD
#define UHCI_USBSTS         0x02 //Usb Status Read/Clear On Write                       WORD
#define UHCI_USBINTR        0x04 //Usb Interrupt Enable Read/Write                      WORD
#define UHCI_FRNUM          0x06 //Usb Frame Number Read/Write                          WORD
#define UHCI_FRBASEADD      0x08 //Usb Frame List Base Address Read/Write               DWORD //use WORD Writes 
#define UHCI_SOFMOD         0x0C //Usb Start Of Frame Modify Read/Write                 BYTE  //use WORD Writes
#define UHCI_PORTSC1        0x10 //Usb Port 1 Status Control Read/Clear On Write        WORD
#define UHCI_PORTSC2        0x12 //Usb Port 2 Status Control Read/Clear On Write        WORD 

#define UHCI_FRBASEADD_LOW  0x00
#define UHCI_FRBASEADD_HIGH 0x02

typedef struct _UHCI_DEVICE{
    PPCI_DEVICE_OBJECT      PDEV;
    UINT16                  IoBase;
    spinlock_t              IoLock;
    UINT8                   SerialBusReleaseNumber; //PCI Offset 0x60
    UINTPTR                 IoBaseAddress;          //BAR 0x04
}UHCI_DEVICE, * PUHCI_DEVICE;



//move the rest to C++ files

void UhciWriteFrameBaseAddress(
    PUHCI_DEVICE    UhciDevice,
    UINT32          Address
){
    LouKIRQL Irql;
    UINT16 IoBase = UhciDevice->IoBase;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    outw(IoBase + UHCI_FRBASEADD + UHCI_FRBASEADD_LOW, Address & 0xFFFF);
    outw(IoBase + UHCI_FRBASEADD + UHCI_FRBASEADD_HIGH, (Address >> 16) & 0xFFFF);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
}

UINT32 UchiReadFrameBaseAddress(
    PUHCI_DEVICE    UhciDevice
){
    LouKIRQL Irql;
    UINT16 IoBase = UhciDevice->IoBase;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    UINT32 Address = inw(IoBase + UHCI_FRBASEADD + UHCI_FRBASEADD_LOW);
    Address |= ((UINT32)inw(IoBase + UHCI_FRBASEADD + UHCI_FRBASEADD_HIGH)) << 16;
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
    return Address;
}

void UhciWriteStartOfFrameModify(
    PUHCI_DEVICE    UchiDevice,
    UINT8           FrameNumber
){
    LouKIRQL Irql;
    UINT16 IoBase = UhciDevice->IoBase;
    UINT16 IoFrameNumber = (UINT16)FrameNumber;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    outw(IoBase + UHCI_FRNUM, IoFrameNumber);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
}

UINT8 UhciReadStartOfFrameModify(
    PUHCI_DEVICE UhciDevice
){
    LouKIRQL Irql;
    UINT16  IoBase = UhciDevice->IoBase;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    UINT16  IoFrameNumber = inw(IoBase + UHCI_SOFMOD);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
    return IoFrameNumber & 0xFF;
}

void UhciWriteUsbCommand(
    PUHCI_DEVICE    UhciDevice,
    UINT16          Command
){
    LouKIRQL Irql;
    UINT16 IoBase = UhciDevice->IoBase,
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    outw(IoBase + UHCI_USBCMD, Command);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
}

UINT16 UhciReadUsbCommand(
    PUHCI_DEVICE UhciDevice
){
    LouKIRQL Irql;
    UINT16 IoBase = UhciDevice->IoBase;
    UINT16 Command;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    Command = inw(IoBase + UHCI_USBCMD);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
    return Command;
}

void UhciClearUsbStatus(
    PUHCI_DEVICE    UhciDevice,
    UINT16          ClearMask
){
    LouKIRQL Irql;
    UINT16 IoBase = UhciDevice->IoBase;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    outw(IoBase + UHCI_USBSTS, ClearMask);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
}

UINT16 UhciReadUsbStatus(
    PUHCI_DEVICE    UhciDevice
){
    LouKIRQL    Irql;
    UINT16      Status;
    UINT16      IoBase = UhciDevice->IoBase;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    Status = inw(IoBase + UHCI_USBSTS);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
    return Status;
}

void UhciWriteInterruptEnable(
    PUHCI_DEVICE    UhciDevice,
    UINT16          InterruptEnable
){
    LouKIRQL    Irql;
    UINT16      IoBase = UhciDevice->IoBase;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    outw(IoBase + UHCI_USBINTR, InterruptEnable);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
}

UINT16 UhciReadInterruptEnable(
    PUHCI_DEVICE    UhciDevice
){
    LouKIRQL    Irql;
    UINT16      IoBase = UhciDevice->IoBase;
    UINT16      InterruptEnable;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    InterruptEnable = inw(IoBase + UHCI_USBINTR);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
    return InterruptEnable;
}

UINT16 UhciReadFrameNumber(
    PUHCI_DEVICE    UhciDevice
){
    LouKIRQL Irql;
    UINT16  IoBase = UhciDevice->IoBase;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    UINT16  IoFrameNumber = inw(IoBase + UHCI_FRNUM);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
    return IoFrameNumber;
}

void UhciWriteFrameNumber(
    PUHCI_DEVICE    UhciDevice,
    UINT16          FrameNumber
){
    LouKIRQL    Irql;
    UINT16      IoBase = UhciDevice->IoBase;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    outw(IoBase + UHCI_FRNUM,FrameNumber);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
}

UINT16 UhciReadPortStatusControl1(
    PUHCI_DEVICE    UhciDevice  
){
    LouKIRQL Irql;
    UINT16 IoBase = UhciDevice->IoBase;
    UINT16 StsCtrl;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    StsCtrl = inw(IoBase + UHCI_PORTSC1);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
    return StsCtrl;
}

void UhciClearPortStatusControl1(
    PUHCI_DEVICE    UhciDevice  
    UINT16          ClearMask
){
    LouKIRQL Irql;
    UINT16 IoBase = UhciDevice->IoBase;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    outw(IoBase + UHCI_PORTSC1, ClearMask);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
}


UINT16 UhciReadPortStatusControl2(
    PUHCI_DEVICE    UhciDevice
){
    LouKIRQL Irql;
    UINT16 IoBase = UhciDevice->IoBase;
    UINT16 StsCtrl;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    StsCtrl = inw(IoBase + UHCI_PORTSC2);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
    return StsCtrl;
}

void UhciClearPortStatusControl2(
    PUHCI_DEVICE    UhciDevice  
    UINT16          ClearMask
){
    LouKIRQL Irql;
    UINT16 IoBase = UhciDevice->IoBase;
    LouKeAcquireSpinLock(&UhciDevice->IoLock, &Irql);
    outw(IoBase + UHCI_PORTSC2, ClearMask);
    LouKeReleaseSpinLock(&UhciDevice->IoLock, &Irql);
}



#endif