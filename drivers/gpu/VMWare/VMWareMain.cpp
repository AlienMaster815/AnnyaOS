// SPDX-License-Identifier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright (c) 2009-2025 Broadcom. All Rights Reserved. The term
 * “Broadcom” refers to Broadcom Inc. and/or its subsidiaries.
 *
 **************************************************************************/


#include "VMWareMain.h"

static LOUSINE_PCI_DEVICE_TABLE VmwPciDeviceTable[] = {
    {.VendorID = PCI_VENDOR_ID_VMWARE, .DeviceID = VMWGFX_PCI_ID_SVGA2, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_VMWARE, .DeviceID = VMWGFX_PCI_ID_SVGA3, .SimpleEntry = true},
    {0},
};

LOUDDK_API_ENTRY
VOID
UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("Unloaded VBOXGPU\n");
}

LOUDDK_API_ENTRY
NTSTATUS
AddDevice(PDRIVER_OBJECT DriverObject, struct _DEVICE_OBJECT* PlatformDevice){
    LouPrint("VMWGPU::AddDevice()\n");



    LouPrint("VMWGPU::AddDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS
DriverEntry(
    PDRIVER_OBJECT DriverObject, 
    PUNICODE_STRING RegistryEntry
){

    LouPrint("VMWGPU::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)VmwPciDeviceTable;
    LouPrint("VMWGPU::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}