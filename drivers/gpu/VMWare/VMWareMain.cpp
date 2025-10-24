/*
 * This is a clean-room reimplementation of the VirtualBox VBE/VMSVGA driver,
 * originally developed by Oracle Corporation and released under the MIT license.
 *
 * This implementation is based on independent research and observation of the
 * Linux kernel's `vboxvideo` driver and related specifications. No code was
 * directly copied or translated.
 *
 * All identifiers, register names, and behavior are derived from public
 * documentation or reverse-engineered from hardware behavior.
 *
 * Copyright (C) 2025 Tyler Grenier
 * Licensed under the GNU GPLv2
 */

#define _KERNEL_MODULE_
#include <LouDDK.h>

static LOUSINE_PCI_DEVICE_TABLE PiixPciDeviceTable[] = {
    //PATA Devices
    {0x15AD, 0x0405, ANY_PCI_ID, ANY_PCI_ID, 0, 0, 0},
    {0x15AD, 0x0406, ANY_PCI_ID, ANY_PCI_ID, 0, 0, 0},
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
    DriverObject->DeviceTable = (uintptr_t)PiixPciDeviceTable;
    LouPrint("VMWGPU::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}