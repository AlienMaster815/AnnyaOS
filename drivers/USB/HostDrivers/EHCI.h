#define _KERNEL_MODULE_
#ifndef _EHCI_H
#define _EHCI_H

#include <LouDDK.h>

typedef struct _EHCI_CAPABILITY_REGISTERS{
    UINT8       CapLength;
    UINT8       Reserved1;
    UINT16      HciVersion;
    UINT32      HcsParams;
    UINT32      HccParams;
    UINT64      HcspPortRoute;
}EHCI_CAPABILITY_REGISTERS, * PEHCI_CAPABILITY_REGISTERS;

typedef struct _EHCI_HOST_OPERATIONAL_REGISTERS{
    UINT32      UsbCommand;             //USBCMD
    UINT32      UsbStatus;              //USBSTS
    UINT32      UsbInterruptEnable;     //USBINTR
    UINT32      UsbFrameIndex;          //FRINDEX
    UINT32      ControlDsSegment;       //CTRLDSSEGMENT
    UINT32      FrameListBaseAddress;   //PERIODICLISTBASE
    UINT32      NextAsyncListAddress;   //ASYNCLISTADDR
    UINT8       Reserved[0x3F - 0x1C];
    UINT32      ConfigFlag;             //CONFIGFLAG
    UINT32      PortStatusControl[];    //PORTSC      
}EHCI_HOST_OPERATIONAL_REGISTERS, * PEHCI_HOST_OPERATIONAL_REGISTERS;

typedef struct _EHCI_DEVICE{
    PPCI_DEVICE_OBJECT                  PDEV;
    PEHCI_CAPABILITY_REGISTERS          Capabilities;
    PEHCI_HOST_OPERATIONAL_REGISTERS    OperationalRegisters;
}EHCI_DEVICE, * PEHCI_DEVICE;




#endif