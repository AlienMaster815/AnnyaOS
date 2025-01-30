
#define _KERNEL_MODULE_

#include <LouDDK.h>


LOUDDK_API_ENTRY
LOUSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){



    return STATUS_SUCCESS;
}


