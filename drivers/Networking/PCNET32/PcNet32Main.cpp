
#define _KERNEL_MODULE_

#include <LouDDK.h>
#include "PCNETII.h"

UNUSED LOUSINE_PCI_DEVICE_TABLE PcNet32SupportedDevices[] = {
    {.VendorID = 0x1022, .DeviceID = 0x2000, .SimpleEntry = true},
    {.VendorID = 0x1022, .DeviceID = 0x2625, .SimpleEntry = true},
    {.VendorID = 0x1022, .DeviceID = 0x2627, .SimpleEntry = true},
    {.VendorID = 0x103C, .DeviceID = 0x1064, .SimpleEntry = true},
    {0},
};


LOUDDK_API_ENTRY
LOUSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){

    DriverObject->DeviceTable = (uintptr_t)PcNet32SupportedDevices;

    return STATUS_SUCCESS;
}

