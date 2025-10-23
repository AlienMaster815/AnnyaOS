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
#include <usb.h>
#include <Hal.h>
#include "Hcd.h"

BOOL AmdUsbHcdHasWakeupQuirk(PPCI_DEVICE_OBJECT PDEV){

    UINT16 VendorID = (((PPCI_COMMON_CONFIG)PDEV->CommonConfig)->Header.VendorID);

    if(LouKeHalGetChipsetVendor() == 0x1002){
        switch(VendorID){
            case 0x1E49:
            case 0x2063:
                return true;
        }
    }
    return false;
}