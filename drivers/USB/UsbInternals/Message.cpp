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
#include <Hal.h>
#include <usb.h>
#include "Hcd.h"

void LouKeUsbEnableEnpoint(
    PUSB_DEVICE                 UsbDevice,
    PUSB_HOST_ENDPOINT          Ep,
    BOOL                        ResetEp
){
    UNUSED INTEGER EpNumber = LouKeUsbGetEndpointNumber(&Ep->EndpointDescriptor);
    UNUSED INTEGER Out = LouKeUsbEndpointDirOut(&Ep->EndpointDescriptor);
    UNUSED INTEGER Xfer = LouKeUsbEndpointXferControl(&Ep->EndpointDescriptor);

    if(ResetEp){
        LouKeUsbHcdResetEndpoint(UsbDevice, Ep);
    } 

    if((Out) || (Xfer)){
        UsbDevice->OutputEndpoint[EpNumber] = Ep;
    }
    if((!Out) || (Xfer)){
        UsbDevice->InputEndpoint[EpNumber] = Ep;
    }
    Ep->Enabled = 1;
}