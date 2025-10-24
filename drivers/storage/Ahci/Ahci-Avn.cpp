#define _KERNEL_MODULE_
#include <LouDDK.h>
#include "AhciMod.h"

// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *  ahci.c - AHCI SATA support
 *
 *  Maintained by:  Tejun Heo <tj@kernel.org>
 *    		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *  Copyright 2004-2005 Red Hat, Inc.
 *
 * libata documentation is available via 'make {ps|pdf}docs',
 * as Documentation/driver-api/libata.rst
 *
 * AHCI hardware documentation:
 * http://www.intel.com/technology/serialata/pdf/rev1_0.pdf
 * http://www.intel.com/technology/serialata/pdf/rev1_1.pdf
 */

LOUSTATUS AhciAvnHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    LouPrint("AhciAvnHardReset");
    while(1);
    return STATUS_SUCCESS;
}