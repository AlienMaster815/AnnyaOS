// SPDX-License-Identifier: GPL-2.0-only
/*
 * AnnyaOS USB Core Subsystem
 *
 * This subsystem was inspired by the design of the Linux USB core and USB
 * host controller stack originally developed by:
 *
 *   - Johannes Erdfelt        <johannes@erdfelt.com>
 *   - Greg Kroah-Hartman      <gregkh@linuxfoundation.org>
 *   - Alan Stern              <stern@rowland.harvard.edu>
 *   - David Brownell          (USB-OTG work)
 *   - Sarah Sharp             (USB 3.x / xHCI development)
 *
 * This implementation is an original reimplementation for the
 * Lousine Kernel architecture used by AnnyaOS. It was developed from
 * public documentation including:
 *
 *   - USB 1.1 / 2.0 / 3.x specifications (USB.org)
 *   - Intel UHCI and EHCI specifications
 *   - AMD/VIA OHCI controller specifications
 *   - xHCI specification (eXtensible Host Controller Interface)
 *   - Public chipset datasheets
 *
 * No Linux source code was copied into this implementation.
 * Structural similarity exists only due to USB specification requirements.
 *
 * Copyright (C) 2025  Tyler Grenier (AlienMaster815)
 * AnnyaOS Project — https://github.com/AlienMaster815/AnnyaOS
 *
 * Licensed under GPL-2.0-only. See COPYING for details.
 */

#include <LouDDK.h>
#include <Hal.h>
#include <usb.h>
#include "Hcd.h"

void LouKeUsbEnableEnpoint(
    PUSB_DEVICE                 UsbDevice,
    PUSB_HOST_ENDPOINT          Ep,
    BOOL                        ResetEp
);

static bool UsbDeviceAuthorized(PUSB_DEVICE Device, PUSB_HOST_CONTROLLER_DEVICE Hcd){

	if (!Device->Parent){
		return true;
    }

    switch(Hcd->DevicePolicy){
        case USB_DEVICE_AUTHORITY_NONE:
        default: 
            return false;
        case USB_DEVICE_AUTHORITY_ALL:
            return true;
    }

    return false;
}

PUSB_DEVICE LouKeAllocateUsbDevice(
    PUSB_DEVICE Parrent,
    PUSB_BUS    Bus,
    UINT64      Port
){
    PUSB_DEVICE NewDevice;
    PUSB_HOST_CONTROLLER_DEVICE Hcd = UsbBusToHcd(Bus);
    UNUSED UINT64 RawPort = Port;
    
    NewDevice = LouKeMallocType(USB_DEVICE, KERNEL_GENERIC_MEMORY);

    if(!LouKeUsbGetHcd(Hcd)){
        LouKeFree(NewDevice);
        return 0x00;
    }

    if((Hcd->HcdDriver->LouKeMallocDevice) && (Parrent) && (!Hcd->HcdDriver->LouKeMallocDevice(Hcd, NewDevice))){
        LouKeUsbPutHcd(Hcd);
        LouKeFree(NewDevice);
        return 0x00;
    }

    NewDevice->UsbDeviceState = USB_STATE_ATTACHED;
    NewDevice->LowPowerModeDisableCount = 1;
    LouKeSetAtomic(&NewDevice->UrbNumber, 0);

    NewDevice->Endpoint0.EndpointDescriptor.Length = USB_DT_ENDPOINT_SIZE;
    NewDevice->Endpoint0.EndpointDescriptor.DescriptorType = USB_DT_ENDPOINT;
    NewDevice->UsbBus = Bus;

    LouKeUsbEnableEnpoint(NewDevice, &NewDevice->Endpoint0, false);
    NewDevice->UsbDeviceFlags1 |= 1;//submitable

    if(UsbDeviceAuthorized(NewDevice, Hcd)){
        NewDevice->UsbDeviceFlags1 |= (1 << 4); //authorized
    }
    return NewDevice;
}
