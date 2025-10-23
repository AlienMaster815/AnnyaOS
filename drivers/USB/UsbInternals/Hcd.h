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

#ifndef _HCD_H
#define _HCD_H

#include <LouDDK.h>
#include <usb.h>
#include <Hal.h>

#define HCD_BUFFER_POOLS 4

BOOL AmdUsbHcdHasWakeupQuirk(PPCI_DEVICE_OBJECT PDEV);

LOUSTATUS
LouKeCreateHcdBuffer(
    PUSB_HOST_CONTROLLER_DEVICE Hcd
);

LOUSTATUS 
LouKeUsbAddHcd(
    PUSB_HOST_CONTROLLER_DEVICE Hcd,
    UINT8                       Irq
);

void LouKeUsbNotifyAddBus(PUSB_BUS Bus);

PUSB_DEVICE LouKeAllocateUsbDevice(
    PUSB_DEVICE Parrent,
    PUSB_BUS    Bus,
    UINT64      Port
);

void LouKeUsbHcdResetEndpoint(
    PUSB_DEVICE         Device,
    PUSB_HOST_ENDPOINT  Ep
);

static inline PUSB_HOST_CONTROLLER_DEVICE UsbBusToHcd(PUSB_BUS Bus){
    return CONTAINER_OF(Bus, USB_HOST_CONTROLLER_DEVICE, UsbSelf);
}

PUSB_HOST_CONTROLLER_DEVICE LouKeUsbGetHcd(PUSB_HOST_CONTROLLER_DEVICE Hcd);

void LouKeUsbPutHcd(PUSB_HOST_CONTROLLER_DEVICE Hcd);

void LouKeUsbEnableEnpoint(
    PUSB_DEVICE         UsbDevice,
    PUSB_HOST_ENDPOINT  Ep,
    BOOL                ResetEp
);

static inline INTEGER LouKeUsbGetEndpointNumber(
    PUSB_ENDPOINT_DESCRIPTOR Ep
){
    return Ep->EndpointAddress & USB_ENDPOINT_NUMBER_MASK;
}

static inline INTEGER LouKeUsbEndpointDirOut(
    PUSB_ENDPOINT_DESCRIPTOR Ep
){
    return ((Ep->EndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT);
}

static inline INTEGER LouKeUsbEndpointDirIn(
    PUSB_ENDPOINT_DESCRIPTOR Ep
){
    return ((Ep->EndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN);
}

static inline INTEGER LouKeUsbEndpointXferControl(
    PUSB_ENDPOINT_DESCRIPTOR Ep
){
    return ((Ep->EndpointAddress & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_CONTROL);
}

static 
inline 
bool 
AmdHcdResumeBug(
    PPCI_DEVICE_OBJECT PDEV, 
    const USB_HOST_CONTROLLER_DRIVER* HcdDriver
){

    if(!AmdUsbHcdHasWakeupQuirk(PDEV)){
        return false;
    }if(HcdDriver->DriverFlags & (HCD_USB1_1 | HCD_USB3_0)){
        return true;
    }
    return false;
}

LOUSTATUS LouKeUsbPhyRoothubCalibration(PUSB_PHY_LAYER_ROOTHUB_CHAIN PhyRootHub);

#define UsbSetToggle(Device, Ep, Out, Bit) ((Device)->Toggle[Out] = (((Device)->Toggle[Out] & ~((1) << Ep)) | ((Bit) << Ep)))

#endif