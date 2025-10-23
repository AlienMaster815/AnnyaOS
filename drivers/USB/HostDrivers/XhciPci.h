/* SPDX-License-Identifier: GPL-2.0 */

/*
 * xHCI host controller driver
 *
 * Copyright (C) 2008 Intel Corp.
 *
 * Author: Sarah Sharp
 * Some code borrowed from the Linux EHCI driver.
 */

#define _KERNEL_MODULE_
#ifndef _XHCI_PCI_H
#define _XHCI_PCI_H
#include <LouDDK.h>

NTSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    PDEVICE_OBJECT PlatformDevice
);

#endif