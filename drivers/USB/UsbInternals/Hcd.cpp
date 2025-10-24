// SPDX-License-Identifier: GPL-2.0-only
/*
 * AnnyaOS USB Core Subsystem
 *
 * This subsystem is derived from the Linux USB core implementation
 * and has been ported into the Lousine Kernel architecture for use
 * in AnnyaOS. Structural and logical behavior is largely based on
 * the Linux USB stack to maintain hardware compatibility across
 * UHCI, OHCI, EHCI, and xHCI host controllers.
 *
 * Significant portions were adapted from the original Linux USB
 * core developed by the following contributors:
 *
 *   - Johannes Erdfelt        <johannes@erdfelt.com>
 *   - Greg Kroah-Hartman      <gregkh@linuxfoundation.org>
 *   - Alan Stern              <stern@rowland.harvard.edu>
 *   - David Brownell          (USB-OTG subsystem)
 *   - Sarah Sharp             (USB 3.x and xHCI implementation)
 *
 * Original Linux code is licensed under GPLv2. This port
 * complies with the GPLv2 by preserving the license and attributions.
 * Modifications, restructuring, and kernel integration were performed
 * for the AnnyaOS environment.
 *
 * Copyright (C) 2025
 * Tyler Grenier (AlienMaster815)
 * AnnyaOS Project — https://github.com/AlienMaster815/AnnyaOS
 */


#include <LouDDK.h>
#include <usb.h>
#include <Hal.h>
#include "Hcd.h"

extern mutex_t UsbPortPeerMutex;

static PIDENTIFICATION_RANGE UsbIdRange = 0x00;

UNUSED static void LouKeUsbHcdGivebackUrbEx(PURB Urb){
    UNUSED PUSB_HOST_CONTROLLER_DEVICE Hcd = UsbBusToHcd(Urb->UsbDevice->UsbBus);
    UNUSED PUSB_ANCHOR Anchor = Urb->Anchor;
    UNUSED int Status = Urb->UnlinkedErrorCode;


}

static LOUSTATUS LouKeUsbGivebackUrbBh(PLOUQ_WORK Work){

    PGIVEBACK_URB_BH Bh = CONTAINER_OF(Work, GIVEBACK_URB_BH, Bh);
    LouKIRQL Irql;

    LouKeAcquireSpinLock(&Bh->BhLock, &Irql);
    Bh->Running = true;
    PURB Urbs = (PURB)Bh->Urbs.NextHeader;    
    PURB UrbsFollower = Urbs;
    Bh->Urbs.NextHeader = 0x00;
    LouKeReleaseSpinLock(&Bh->BhLock, &Irql);

    while(Urbs){

        Bh->CompletingEndpoint = Urbs->Endpoint;
        LouKeUsbHcdGivebackUrbEx(Urbs);
        Bh->CompletingEndpoint = 0x00;
        UrbsFollower = Urbs;
        Urbs = (PURB)Urbs->UrbList.NextHeader;
        UrbsFollower->UrbList.NextHeader = 0x00;
    }

    LouKeAcquireSpinLock(&Bh->BhLock, &Irql);
    if(!Bh->Urbs.NextHeader){
        //LouKeStartWork(,&bh->Bh);
    }
    Bh->Running = false;
    LouKeReleaseSpinLock(&Bh->BhLock, &Irql);
    return STATUS_SUCCESS;
}

UNUSED static void LouKeUsbInitializeGivebackUrb(
    PGIVEBACK_URB_BH Bh
){
    LouKeLouQInitializeWork(&Bh->Bh, LouKeUsbGivebackUrbBh);
}

static void LouKeInitializeUsbBus(PUSB_BUS UsbBus){
    memset(&UsbBus->DeviceMap, 0, sizeof(UsbBus->DeviceMap));
    UsbBus->NextDeviceNumber = 1;
    UsbBus->RootHub = 0x00;
    UsbBus->BusNumber = -1;
    UsbBus->BandwithAllocated = 0;
    UsbBus->BandwithInterrupts = 0;
    UsbBus->BandwithIsoc = 0;
}

PUSB_HOST_CONTROLLER_DEVICE
LouKeCreateUsbHostControllerDeviceEx(
    const USB_HOST_CONTROLLER_DRIVER*   Driver,
    PPCI_DEVICE_OBJECT                  SystemDevice,
    PPCI_DEVICE_OBJECT                  Device,
    PUSB_HOST_CONTROLLER_DEVICE         PrimaryHcd
){

    SIZE DeviceObjectSize =  ROUND_UP64(sizeof(USB_HOST_CONTROLLER_DEVICE), GET_ALIGNMENT(UINT64));
    PUSB_HOST_CONTROLLER_DEVICE Hcd = (PUSB_HOST_CONTROLLER_DEVICE)LouKeMallocEx(DeviceObjectSize + Driver->HcdPrivateSize , GET_ALIGNMENT(USB_HOST_CONTROLLER_DEVICE), KERNEL_GENERIC_MEMORY);
    Hcd->PrivateData = (PVOID)((UINTPTR)Hcd + (UINTPTR)DeviceObjectSize);
    if(!PrimaryHcd){
        Hcd->Address0Mutex = LouKeMallocType(mutex_t, KERNEL_GENERIC_MEMORY);
        Hcd->BandwithMutex = LouKeMallocType(mutex_t, KERNEL_GENERIC_MEMORY);
        Device->DevicePrivateData = (UINTPTR)Hcd;
    }else{
        Hcd->PrimaryHcd = PrimaryHcd;
        Hcd->Address0Mutex = PrimaryHcd->Address0Mutex;
        Hcd->BandwithMutex = PrimaryHcd->BandwithMutex;
        Hcd->PrimaryHcd = PrimaryHcd;
        Hcd->SharedHcd = PrimaryHcd;
        PrimaryHcd->SharedHcd = Hcd;
        Device->DevicePrivateData = (UINTPTR)Hcd; 
    }
    
    LouKeInitializeUsbBus(&Hcd->UsbSelf);
    Hcd->UsbSelf.ControllerDevice = Device;
    Hcd->UsbSelf.SystemDevice = SystemDevice;
    Hcd->UsbSelf.BusName = Driver->DeviceDescription;

    Hcd->HcdDriver = (PUSB_HOST_CONTROLLER_DRIVER)Driver;
    Hcd->Speed  = Driver->DriverFlags & HCD_MASK;
    Hcd->ProductDescriptor = (Driver->ProductDescriptor) ? Driver->ProductDescriptor : (string)"USB Host Controller";
    return Hcd;
}

PUSB_HOST_CONTROLLER_DEVICE
LouKeCreateUsbHostControllerDevice(
    const USB_HOST_CONTROLLER_DRIVER*   Driver,
    PPCI_DEVICE_OBJECT                  PDEV
){
    return LouKeCreateUsbHostControllerDeviceEx(Driver, PDEV, PDEV, 0x00);
}

static UINT8 UsbDeviceDefaultAuthority = USB_DEVICE_AUTHORITY_ALL;

static 
LOUSTATUS
LouKeUsbRegisterBus(
    PUSB_BUS Bus
){
    INTEGER BusNumber;
    if(!UsbIdRange){
        UsbIdRange = LouKeCreateIdentificationRange(0, 256);
    }
    BusNumber = LouKeAcquireIdFromRange(UsbIdRange, (PVOID)Bus);
    
    if(BusNumber == (INTEGER)-1){
        LouPrint("USB ERROR: Unable To Acquire ID For Bus:%h\n", Bus);
        return STATUS_UNSUCCESSFUL;
    }

    LouPrint("Bus:%h Is Now Tied To ID:%d\n", Bus, BusNumber);
    Bus->BusNumber = BusNumber;

    
    //MABYE_TODO: add notifier

    return STATUS_SUCCESS;
}

void LouKeUsbHcdResetEndpoint(
    PUSB_DEVICE         Device,
    PUSB_HOST_ENDPOINT  Ep
){
    PUSB_HOST_CONTROLLER_DEVICE Hcd = UsbBusToHcd(Device->UsbBus);
    if(Hcd->HcdDriver->ResetEndpoint){
        Hcd->HcdDriver->ResetEndpoint(Hcd, Ep);
        return;
    }

    INTEGER EpNumber = LouKeUsbGetEndpointNumber(&Ep->EndpointDescriptor);
    INTEGER Out = LouKeUsbEndpointDirOut(&Ep->EndpointDescriptor);
    INTEGER Xfer = LouKeUsbEndpointXferControl(&Ep->EndpointDescriptor);

    UsbSetToggle(Device, EpNumber, Out, 0);
    if(Xfer){
        UsbSetToggle(Device, EpNumber, !Out, 0);
    }

}

LOUSTATUS 
LouKeUsbAddHcd(
    PUSB_HOST_CONTROLLER_DEVICE Hcd,
    UINT8                       Irq
){
    LOUSTATUS Status = STATUS_SUCCESS;
    UNUSED PUSB_DEVICE RhDev;
    UNUSED PUSB_HOST_CONTROLLER_DEVICE SharedHcd;
    UNUSED INTEGER SkipPhyLayerInit;
    UNUSED BOOL IsPrimaryHcd = !Hcd->PrimaryHcd;

    Hcd->DevicePolicy = UsbDeviceDefaultAuthority;
    if(Hcd->DevicePolicy == USB_DEVICE_AUTHORITY_WIRED){
        Hcd->DevicePolicy = USB_DEVICE_AUTHORITY_ALL;
    }

    Hcd->Flags |= 1;            //HW ACCESSABLE
    Hcd->Flags |= (1 << 7);     //INTERFACE AUTHORIZED
    
    Status = LouKeCreateHcdBuffer(Hcd);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = LouKeUsbRegisterBus(&Hcd->UsbSelf);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    RhDev = LouKeAllocateUsbDevice(0x00, &Hcd->UsbSelf, 0);
    MutexLock(&UsbPortPeerMutex);
    Hcd->UsbSelf.RootHub = RhDev;
    MutexUnlock(&UsbPortPeerMutex);

    RhDev->RxLanes = 1;
    RhDev->TxLanes = 1;
    RhDev->SspRate = USB_SSP_GEN_UNKOWN;

    switch(Hcd->Speed){
        case HCD_USB1_1:
            RhDev->Speed = USB_SPEED_FULL;
            break;
        case HCD_USB2_0:
            RhDev->Speed = USB_SPEED_FULL;
            break;
        case HCD_USB3_0:
            RhDev->Speed = USB_SPEED_SUPER;
            break;
        case HCD_USB3_2:
            RhDev->RxLanes = 2;
            RhDev->TxLanes = 2;
            RhDev->SspRate = USB_SSP_GEN_2x1;
            RhDev->Speed = USB_SPEED_SUPER_PLUS;
            break;
        case HCD_USB3_1:
            RhDev->SspRate = USB_SSP_GEN_2x1;
            RhDev->Speed = USB_SPEED_SUPER_PLUS;
            break;
        default:
            LouPrint("ERROR:Speed\n");
            while(1);
    }

    Hcd->Flags |= (1 << 5); //roothub running

    if(Hcd->HcdDriver->ResetHcd){
        Status = Hcd->HcdDriver->ResetHcd(Hcd);
        if(Status != STATUS_SUCCESS){
            LouPrint("Roothub Failed To Reset\n");
            while(1);
        }
    }

    Hcd->Flags |= (1 << 2);//is polable

    Hcd->HCDS |= (1 << 1);
 
    //TODO: Root hub Can Wakeup

    LouKeUsbInitializeGivebackUrb(&Hcd->HighPriorityBh);
    Hcd->HighPriorityBh.HighPriority = true;
    LouKeUsbInitializeGivebackUrb(&Hcd->LowPriorityBh);


    return Status;
}

PUSB_HOST_CONTROLLER_DEVICE LouKeUsbGetHcd(PUSB_HOST_CONTROLLER_DEVICE Hcd){
    if(Hcd){
        LouKeAcquireReference(&Hcd->KRef);
    }
    return Hcd;
}

void LouKeUsbPutHcd(PUSB_HOST_CONTROLLER_DEVICE Hcd){
    if(Hcd){
        LouKeReleaseReferece(&Hcd->KRef);
    }
}