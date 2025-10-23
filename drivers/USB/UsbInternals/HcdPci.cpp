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

BOOL AmdUsbHcdHasWakeupQuirk(PPCI_DEVICE_OBJECT PDEV);


LOUDDK_API_ENTRY
LOUSTATUS 
LouKeUsbHcdPciProbe(
    PPCI_DEVICE_OBJECT PDEV, 
    const USB_HOST_CONTROLLER_DRIVER* HcdDriver
){
    LOUSTATUS Status;
    PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
    LouPrint("LouKeUsbHcdPciProbe()\n");
    if(!HcdDriver){
        return STATUS_INVALID_PARAMETER;
    }

    if(LouKeHalEnablePciDevice(PDEV) != STATUS_SUCCESS){
        return STATUS_NO_SUCH_DEVICE;
    }

    if((HcdDriver->DriverFlags & HCD_MASK) < HCD_USB3_0){
        LouPrint("HcdPci.cpp:Unfinished Function\n");//TODO:
        while(1);
    } 

    PUSB_HOST_CONTROLLER_DEVICE Hcd = LouKeCreateUsbHostControllerDevice(HcdDriver, PDEV);
    if(!Hcd){
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto _USB_HCD_PROBE_FAILED_RELEASE_IRQS;
    }

    Hcd->AmdResumeBug = AmdHcdResumeBug(PDEV, HcdDriver);

    if(HcdDriver->DriverFlags & (HCD_MEMORY)){
        //non UHCI
        Hcd->IoRegionBase   = (UINTPTR)LouKePciGetIoRegion(PDEV, 0, 0x00);
        Hcd->IoRegionLimit  = LouKeHalGetPciBaseAddressSize(PDEV, 0);

        if(!Hcd->IoRegionBase){
            Status = STATUS_DEVICE_CONFIGURATION_ERROR;
            goto _HCD_FAILED_RELEASE_HCD;
        }

    }else{
        //UHCI...
    }

    if(LouKeHalEnablePciDevice(PDEV) != STATUS_SUCCESS){
        Status = STATUS_DEVICE_CONFIGURATION_ERROR;
        goto _HCD_FAILED_RELEASE_HCD;
    }

    if(Config->Header.SubClass == 0x20){

    }else{
        Status = LouKeUsbAddHcd(Hcd, 0);
    }

    LouPrint("LouKeUsbHcdPciProbe() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;

_HCD_FAILED_RELEASE_HCD:


_USB_HCD_PROBE_FAILED_RELEASE_IRQS:
    if((HcdDriver->DriverFlags & HCD_MASK) < HCD_USB3_0){
        LouPrint("HcdPci.cpp:Unfinished Function\n");//TODO:
        while(1);
    } 
    return Status;
}